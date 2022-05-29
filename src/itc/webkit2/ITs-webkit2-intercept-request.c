//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-webkit2-common.h"

/** @addtogroup itc-webkit2
*  @ingroup itc
*  @{
*/

#define LENGTH_HEADER_BUFFER_SIZE 20
static bool g_bWebkit_EFL_LoadSuccess = false;
static Ecore_Timer* emergency_exit_timer;
bool g_bIsInterceptRequestResponse = false;
static char* g_HttpMethod = NULL;

static const Eina_Hash* g_Headers;
static char* g_AcceptHeader;
static char* g_UserAgentHeader;
static char* url;
static Eina_Bool g_bIgnoreinterceptresult;
static Eina_Bool g_BodySetResult;

static char g_InterceptUrl[] = "http://request.intercept.ewk.api.test/";
static const char g_BodyFormat[] = "<html><head><title>%s</title></head>"
                                  "<body>Hello, Request Intercept!</body></html>";
static const char g_HeadersFormat[] = "200 OK\r\n"
                                     "Content-Type: text/html; charset=UTF-8\r\n"
                                     "Content-Length: %zu\r\n"
                                     "\r\n";
static char g_TitleExpected[] = "BODY SET SUCCESS";
static char* g_BodyDone;
static size_t g_DataToWrite;

static const char g_InterceptUrlAjax[] = "http://request.intercept.ewk.api.test/ajax/";
static const char g_BaseTitle[] = "intercept request";
static const char g_BodyAjaxTestFormat[] =
    "document.title = '%s: ' + this.getResponseHeader('%s')"
    " + ', %s: ' + this.getResponseHeader('%s');";
// static const char body_format_header[] =
    // "<html><head><title>%s</title></head>"
    // "<body><script>"
    // "function ajax_listener() {%s}"
    // "window.onload = function() {"
    // "var ajax = new XMLHttpRequest();"
    // "ajax.onload = ajax_listener;"
    // "ajax.open('GET','%s', true);"
    // "ajax.send();"
    // "}"
    // "</script>"
    // "</body></html>";
static const char g_BodyAjaxDone[] = "dummy ajax payload";
static char* g_BodyAjaxTestDone;
static char* g_BodyAjaxTestDoneStatusSet;
static char* g_BodyDone;
static const char g_Test_header_field_1[] = "TEST_FIELD_1";
static const char g_Test_header_value_1[] = "TEST_VALUE_1";
static const char g_Test_header_field_2[] = "TEST_FIELD_2";
static const char g_Test_header_value_2[] = "TEST_VALUE_2";
static const char g_Expected_title_format[] = "%s: %s, %s: %s";
static char* g_Expected_title_done;
static char* g_HeadersDone;

Eina_Hash* g_HeaderMap;
static Eina_Bool g_Header_add_1_result;
static Eina_Bool g_Header_add_2_result;
static Eina_Bool g_Header_map_add_result;
static Eina_Bool g_Response_set_result = EINA_FALSE;

static int g_StatusCode;
static const char* g_CustomStatusText = "COOL";

static Ewk_Intercept_Request* g_SavedInterceptRequest;
static size_t g_DataWriten;
// default chunk length should be smaller than body length, so we actually test writing in chunks
static const int g_Default_chunk_length = 5;

static Eina_Bool g_Status_set_result =  EINA_FALSE;
static Eina_Bool g_Event_loop_result = EINA_FALSE;

/**
* @function 		webkit_chunk_write
* @description	 	chunk write function
* @parameter		void
* @return 	 	bool
*/
static Eina_Bool webkit_chunk_write() {
	size_t to_write = g_Default_chunk_length < g_DataToWrite ? g_Default_chunk_length : g_DataToWrite;
	if (to_write) {
		const char* chunk = (g_BodyDone + g_DataWriten);
		if (!ewk_intercept_request_response_write_chunk(g_SavedInterceptRequest, chunk, to_write)) {
			g_Event_loop_result = EINA_FALSE;
			Webkit_EFL_main_loop_quit();
			return EINA_FALSE;
		}
		g_DataToWrite -= to_write;
		g_DataWriten += to_write;
		return EINA_TRUE;
	} else {
	// end writing by passing NULL chunk and 0 length
		ewk_intercept_request_response_write_chunk(g_SavedInterceptRequest, NULL, 0);
		return EINA_FALSE;
	}
}

/**
* @function 		webkit_ewk_intercept_request_response_write_chunk_callback
* @description	 	callback function
* @parameter		Evas_Object , Ewk_Intercept_Request , void*  data
* @return 	 	void
*/
static void webkit_ewk_intercept_request_response_write_chunk_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside webkit_ewk_intercept_request_response_write_chunk_callback \\n", __LINE__, API_NAMESPACE);
	g_bIsInterceptRequestResponse = true;
	const char* url = ewk_intercept_request_url_get(intercept_request);
	if (strcmp(url, g_InterceptUrl) == 0) {
		char length_header[LENGTH_HEADER_BUFFER_SIZE];
		snprintf((char*)length_header, LENGTH_HEADER_BUFFER_SIZE - 1, "%d", g_DataToWrite);
		// set headers and let chunk write callback work
		ewk_intercept_request_response_status_set(intercept_request, 200, NULL);
		ewk_intercept_request_response_header_add(intercept_request, "Content-Type", "text/html; charset=UTF-8");
		ewk_intercept_request_response_header_add(intercept_request, "Content-Length", (char*)length_header);
		g_SavedInterceptRequest = intercept_request;
                // Since EFL 1.20, ecore_timer_add does not work on child thread.
                // So write chunk repeatedly using while loop.
                while (webkit_chunk_write());
	} else {
		ewk_intercept_request_ignore(intercept_request);
	}
	g_bIsInterceptRequestResponse = true;
}

/**
* @function 		webkit_intercept_request_response_status_set_callback
* @description	 	callback function
* @parameter		Evas_Object , Ewk_Intercept_Request , void*  data
* @return 	 	void
*/
static void webkit_intercept_request_response_status_set_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside  webkit_intercept_request_response_status_set_callback \\n", __LINE__, API_NAMESPACE);
	const char* url = ewk_intercept_request_url_get(intercept_request);
	const char* body;
	if (strcmp(url, g_InterceptUrl) == 0) {
		body = g_BodyDone;
	} else if (strcmp(url, g_InterceptUrlAjax) == 0) {
		body = g_BodyAjaxDone;
	} else {
		ewk_intercept_request_ignore(intercept_request);
		return;
	}
	int body_length = strlen(body);
	char length_header[LENGTH_HEADER_BUFFER_SIZE];
	snprintf((char*)length_header, LENGTH_HEADER_BUFFER_SIZE - 1, "%d", body_length);
	g_Status_set_result = ewk_intercept_request_response_status_set(intercept_request, g_StatusCode, g_CustomStatusText);
	ewk_intercept_request_response_header_add(intercept_request, "Content-Type", "text/html; charset=UTF-8");
	ewk_intercept_request_response_header_add(intercept_request, "Content-Length", (char*)length_header);
	ewk_intercept_request_response_header_add(intercept_request, "Access-Control-Allow-Origin", "*");
	ewk_intercept_request_response_body_set(intercept_request, body, body_length);
	g_bIsInterceptRequestResponse = true;
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		webkit_intercept_request_response_set_callback
* @description	 	callback function
* @parameter		Evas_Object , Ewk_Intercept_Request , void*  data
* @return 	 	void
*/
static void webkit_intercept_request_response_set_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside  webkit_intercept_request_response_set_callback \\n", __LINE__, API_NAMESPACE);
	g_bIsInterceptRequestResponse = true;
	const char* url = ewk_intercept_request_url_get(intercept_request);
	if (strcmp(url, g_InterceptUrl) == 0) {
		g_Response_set_result = ewk_intercept_request_response_set(intercept_request,g_HeadersDone, g_BodyDone, g_DataToWrite);
	} else {
		ewk_intercept_request_ignore(intercept_request);
	}
}

/**
* @function 		webkit_intercept_request_response_header_map_add_callback
* @description	 	callback function
* @parameter		Evas_Object , Ewk_Intercept_Request , void*  data
* @return 	 	void
*/
static void webkit_intercept_request_response_header_map_add_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside  webkit_intercept_request_response_header_map_add_callback \\n", __LINE__, API_NAMESPACE);
	g_bIsInterceptRequestResponse = true;
	const char* url = ewk_intercept_request_url_get(intercept_request);
	const char* body;
	if (strcmp(url, g_InterceptUrl) == 0) {
		body = g_BodyDone;
	} else if (strcmp(url, g_InterceptUrlAjax) == 0) {
		body = g_BodyAjaxDone;
	} else {
		ewk_intercept_request_ignore(intercept_request);
		return;
	}
	int body_length = strlen(body);
	char length_header[LENGTH_HEADER_BUFFER_SIZE];
	snprintf((char*)length_header, LENGTH_HEADER_BUFFER_SIZE - 1, "%d", body_length);
	ewk_intercept_request_response_status_set(intercept_request, 200, NULL);
	ewk_intercept_request_response_header_add(intercept_request, "Content-Type", "text/html; charset=UTF-8");
	ewk_intercept_request_response_header_add(intercept_request, "Content-Length", (char*)length_header);
	ewk_intercept_request_response_header_add(intercept_request, "Access-Control-Allow-Origin", "*");
	g_Header_map_add_result = ewk_intercept_request_response_header_map_add(intercept_request, g_HeaderMap);
	ewk_intercept_request_response_body_set(intercept_request, body, body_length);
}

/**
* @function 		webkit_intercept_request_response__header_add_callback
* @description	 	callback function
* @parameter		Evas_Object , Ewk_Intercept_Request , void*  data
* @return 	 	void
*/
static void webkit_intercept_request_response_header_add_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside  webkit_intercept_request_response_header_add_callback \\n", __LINE__, API_NAMESPACE);
	const char* url = ewk_intercept_request_url_get(intercept_request);
	const char* body;
	if (strcmp(url, g_InterceptUrl) == 0) {
		body = g_BodyDone;
	} else if (strcmp(url, g_InterceptUrlAjax) == 0) {
		body = g_BodyAjaxDone;
	} else {
		ewk_intercept_request_ignore(intercept_request);
	return;
	}
	int body_length = strlen(body);
	char length_header[LENGTH_HEADER_BUFFER_SIZE];
	snprintf((char*)length_header, LENGTH_HEADER_BUFFER_SIZE - 1, "%d", body_length);
	ewk_intercept_request_response_status_set(intercept_request, 200, NULL);
	ewk_intercept_request_response_header_add(intercept_request, "Content-Type", "text/html; charset=UTF-8");
	ewk_intercept_request_response_header_add(intercept_request, "Content-Length", (char*)length_header);
	ewk_intercept_request_response_header_add(intercept_request, "Access-Control-Allow-Origin", "*");
	g_Header_add_1_result = ewk_intercept_request_response_header_add(intercept_request, g_Test_header_field_1, g_Test_header_value_1);
	g_Header_add_2_result = ewk_intercept_request_response_header_add(intercept_request, g_Test_header_field_2, g_Test_header_value_2);
	ewk_intercept_request_response_body_set(intercept_request, body, body_length);
	g_bIsInterceptRequestResponse = true;
}

/**
* @function 		webkit_intercept_request_ignore_callback
* @description	 	callback function
* @parameter		Evas_Object , Ewk_Intercept_Request , void*  data
* @return 	 	void
*/
static void webkit_intercept_response_body_set_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside webkit_intercept_response_body_set_callback \\n", __LINE__, API_NAMESPACE);
	const char* url = ewk_intercept_request_url_get(intercept_request);
	FPRINTF("[Line : %d] url :: [%s] \\n", __LINE__, url);
	if (strcmp(url, g_InterceptUrl) == 0) {
	    char length_header[LENGTH_HEADER_BUFFER_SIZE];
	    snprintf((char*)length_header, LENGTH_HEADER_BUFFER_SIZE - 1, "%d", g_DataToWrite);
	    ewk_intercept_request_response_status_set(intercept_request, 200, NULL);
	    ewk_intercept_request_response_header_add(intercept_request, "Content-Type", "text/html; charset=UTF-8");
	    ewk_intercept_request_response_header_add(intercept_request, "Content-Length", (char*)length_header);
	    g_BodySetResult = ewk_intercept_request_response_body_set ( intercept_request, g_BodyDone,g_DataToWrite);
	    //ewk_intercept_request_ignore(intercept_request);
	}
	g_bIsInterceptRequestResponse = true;
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		webkit_intercept_request_ignore_callback
* @description	 	callback function
* @parameter		Evas_Object , Ewk_Intercept_Request , void*  data
* @return 	 	void
*/
static void webkit_intercept_request_ignore_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside webkit_intercept_request_ignore_callback \\n", __LINE__, API_NAMESPACE);
	g_bIsInterceptRequestResponse = true;
	g_bIgnoreinterceptresult = ewk_intercept_request_ignore(intercept_request);
}
/**
* @function 		webkit_emergency_exit_func
* @description	 	handle delay
* @parameter		data : user data
* @return 			Eina_Bool
*/
static Eina_Bool webkit_emergency_exit_func(void* user_data) {
	FPRINTF("[Line : %d][%s] Inside webkit_emergency_exit_func \\n", __LINE__, API_NAMESPACE);
	Ecore_Timer** timer = (Ecore_Timer**)user_data;
	*timer = NULL;
	Webkit_EFL_main_loop_quit();
	return ECORE_CALLBACK_CANCEL;
}

/**
* @function 		webkit_emergency_exit_func
* @description	 	handle delay
* @parameter		data : user data
* @return 			Eina_Bool
*/
static void webkit_intercept_request_http_method_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside webkit_intercept_request_http_method_callback \\n", __LINE__, API_NAMESPACE);
	g_HttpMethod = (char*)ewk_intercept_request_http_method_get(intercept_request);
	if (g_HttpMethod) {
		g_HttpMethod = strdup(g_HttpMethod);
	}
	g_bIsInterceptRequestResponse = true;
}

static void webkit_intercept_request_header_get_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside webkit_intercept_request_header_get_callback \\n", __LINE__, API_NAMESPACE);
	g_Headers = ewk_intercept_request_headers_get(intercept_request);
	if (g_Headers) {
	g_AcceptHeader = (char*)eina_hash_find(g_Headers, "Accept");
	if (g_AcceptHeader) {
		g_AcceptHeader = strdup(g_AcceptHeader);
	}
	g_UserAgentHeader = (char*)eina_hash_find(g_Headers, "User-Agent");
	if (g_UserAgentHeader) {
		g_UserAgentHeader = strdup(g_UserAgentHeader);
	}
	}
	g_bIsInterceptRequestResponse = true;
}

static void webkit_intercept_request_url_get_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside webkit_intercept_request_url_get_callback \\n", __LINE__, API_NAMESPACE);
	url = (char*)ewk_intercept_request_url_get(intercept_request);
	if (url) {
		url = strdup(url);
	}
	g_bIsInterceptRequestResponse = true;
}

/**
* @function 		webkit_EFL_LoadError
* @description	 	Callback function to get webkit load error info
* @parameter		data : user data,webview : evas object, event_info : event information
* @return 			NA
*/
static void webkit_EFL_LoadError(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] webkit_EFL_LoadError occurs\\n", __LINE__, API_NAMESPACE);
	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		webkit_EFL_LoadFinished
* @description	 	Callback function to get webkit load finish info
* @parameter		data : user data, eObject : evas object, dataFinished : event information
* @return 			NA
*/
static void webkit_EFL_LoadFinished(void* data, Evas_Object* eObject, void* dataFinished)
{
	FPRINTF("[Line : %d][%s] webkit_EFL_LoadFinished Success\\n", __LINE__, API_NAMESPACE);
	g_bWebkit_EFL_LoadSuccess = true;
	g_Event_loop_result = EINA_TRUE;
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		ITs_webkit_efl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITc_ewk_intercept_request_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_HttpMethod = NULL;
	emergency_exit_timer = NULL;
	g_Headers = NULL;
	g_AcceptHeader = NULL;
	g_UserAgentHeader = NULL;
	g_bIsInterceptRequestResponse = false;
	url = NULL;
	g_bIgnoreinterceptresult = EINA_FALSE;
	g_BodySetResult = EINA_FALSE;
	return;
}


/**
* @function 		ITs_webkit_efl_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITc_ewk_intercept_request_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	url = NULL;
	g_BodyAjaxTestDoneStatusSet = NULL;

	if ( g_HeadersDone != NULL ) {
		free(g_HeadersDone);
	}

	if ( g_UserAgentHeader != NULL){
		free(g_UserAgentHeader);
	}

	if ( g_AcceptHeader != NULL){
		free(g_AcceptHeader);
	}

	if ( emergency_exit_timer != NULL){
		ecore_timer_del(emergency_exit_timer);
		emergency_exit_timer = NULL;
	}
	if( g_BodyDone != NULL){
		free( g_BodyDone );
	}
	if( g_BodyAjaxTestDone != NULL){
		free(g_BodyAjaxTestDone);
	}
	if( g_Expected_title_done != NULL){
		free(g_Expected_title_done);
	}

	return;
}

//& purpose: To test ITc_ewk_intercept_request_http_method_get_p
//& type: auto
/**
* @testcase 			ITc_ewk_intercept_request_http_method_get_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_intercept_request_http_method_get_p
* @apicovered			ewk_intercept_request_http_method_get, ewk_context_intercept_request_callback_set
* @passcase				When ITc_ewk_intercept_request_http_method_get_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_intercept_request_http_method_get_p(void)
{
	START_TEST;

	const char expected_method[] = "GET";
	char pPath[PATH_LEN] = {0,};

	if ( Webkit_EFLCreateWebKitView() == false)
	{
		FPRINTF("[Line : %d][%s] Unable to create EFL webkit view\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError, NULL);


	emergency_exit_timer = ecore_timer_add(5, webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), webkit_intercept_request_http_method_callback , NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, pPath) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if(g_bIsInterceptRequestResponse == false) {
		Webkit_EFLDestroyWebKitView();
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(g_HttpMethod == NULL) {
		FPRINTF("[Line : %d][%s] http method not called \\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if(strcmp(g_HttpMethod, expected_method) != 0){
		FPRINTF("[Line : %d][%s] unexpected http method \\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To test ITc_ewk_intercept_request_header_get_p
//& type: auto
/**
* @testcase 			ITc_ewk_intercept_request_header_get_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_intercept_request_header_get_p
* @apicovered			ewk_intercept_request_header_get, ewk_context_intercept_request_callback_set
* @passcase				When ITc_ewk_intercept_request_header_get_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_intercept_request_header_get_p(void)
{
	START_TEST;

	if ( Webkit_EFLCreateWebKitView() == false)
	{
		FPRINTF("[Line : %d][%s] Unable to create EFL webkit view\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError, NULL);


	emergency_exit_timer = ecore_timer_add(5, webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), webkit_intercept_request_header_get_callback , NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, g_InterceptUrl) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if(g_bIsInterceptRequestResponse == false) {
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(g_Headers == NULL) {
		FPRINTF("[Line : %d][%s] header is null \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if(g_AcceptHeader == NULL) {
		FPRINTF("[Line : %d][%s] g_AcceptHeader is null \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if(strstr(g_AcceptHeader, "text/html") == NULL) {
		FPRINTF("[Line : %d][%s] g_AcceptHeader is empty \\n", __LINE__ , API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if(g_UserAgentHeader == NULL) {
		FPRINTF("[Line : %d][%s] g_UserAgentHeader is null \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if(strcmp(g_UserAgentHeader, ewk_view_user_agent_get(objWebkit_EFL_view.webview))!= 0){
		FPRINTF("[Line : %d][%s] unexpected user agent header \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To test ITc_ewk_intercept_request_ignore_p
//& type: auto
/**
* @testcase 			ITc_ewk_intercept_request_ignore_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_intercept_request_ignore_p
* @apicovered			ewk_intercept_request_ignore, ewk_context_intercept_request_callback_set
* @passcase				When ITc_ewk_intercept_request_ignore_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_intercept_request_ignore_p(void)
{
	START_TEST;

	if ( Webkit_EFLCreateWebKitView() == false)
	{
		FPRINTF("[Line : %d][%s] Unable to create EFL webkit view\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError, NULL);


	emergency_exit_timer = ecore_timer_add(5, webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), webkit_intercept_request_ignore_callback , NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, g_InterceptUrl) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if(g_bIsInterceptRequestResponse == false) {
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(g_bIgnoreinterceptresult == EINA_FALSE){
		FPRINTF("[Line : %d][%s] unexpected result from callback \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}


//& purpose: To test ITc_ewk_intercept_request_url_get_p
//& type: auto
/**
* @testcase 			ITc_ewk_intercept_request_url_get_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_intercept_request_url_get_p
* @apicovered			ewk_intercept_request_url_get, ewk_context_intercept_request_callback_set
* @passcase				When ITc_ewk_intercept_request_url_get_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_intercept_request_url_get_p(void)
{
	START_TEST;

	char pPath[PATH_LEN] = {0,};

	if ( Webkit_EFLCreateWebKitView() == false)
	{
		FPRINTF("[Line : %d][%s] Unable to create EFL webkit view\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError, NULL);


	emergency_exit_timer = ecore_timer_add(5, webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), webkit_intercept_request_url_get_callback , NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, pPath) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if(g_bIsInterceptRequestResponse == false) {
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(strcmp(url, pPath) != 0){
		FPRINTF("[Line : %d][%s] unexpected url path \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To test ITc_ewk_intercept_response_body_set_p
//& type: auto
/**
* @testcase 			ITc_ewk_intercept_response_body_set_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ITc_ewk_intercept_response_body_set_p
* @apicovered			ewk_intercept_request_response_body_set, ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_intercept_response_body_set_p
* @passcase				When ITc_ewk_intercept_response_body_set_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_intercept_request_response_body_set_p(void)
{
	START_TEST;

	if ( Webkit_EFLCreateWebKitView() == false)
	{
		FPRINTF("[Line : %d][%s] Unable to create EFL webkit view\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int size = snprintf(NULL, 0, g_BodyFormat, g_TitleExpected);
  	g_BodyDone = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE(g_BodyDone,"malloc:failure:ITc_ewk_intercept_request_response_body_set_p");
 	snprintf(g_BodyDone, size + 1, g_BodyFormat, g_TitleExpected);
 	g_DataToWrite = strlen(g_BodyDone);

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError, NULL);


	emergency_exit_timer = ecore_timer_add(5, webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), webkit_intercept_response_body_set_callback, NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, g_InterceptUrl) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();


	if(g_bIsInterceptRequestResponse == false) {
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		Webkit_EFL_main_loop_quit();
		return 1;
	}

	if(g_BodySetResult == EINA_FALSE){
		FPRINTF("[Line : %d][%s] unexpected result from callback \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		Webkit_EFL_main_loop_quit();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
	Webkit_EFL_main_loop_quit();
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To test ITc_ewk_intercept_request_response_header_add_p
//& type: auto
/**
* @testcase 			ITc_ewk_intercept_request_response_header_add_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ITc_ewk_intercept_request_response_header_add_p
* @apicovered			ewk_intercept_request_response_header_add, ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_intercept_request_response_header_add_p
* @passcase				When ITc_ewk_intercept_request_response_header_add_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_intercept_request_response_header_add_p(void)
{
	START_TEST;
	g_Header_add_1_result = EINA_FALSE;
  	g_Header_add_2_result = EINA_FALSE;


	if ( Webkit_EFLCreateWebKitView() == false)
	{
		FPRINTF("[Line : %d][%s] Unable to create EFL webkit view\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int size;
  	size = snprintf(NULL, 0, g_BodyAjaxTestFormat, g_Test_header_field_1, g_Test_header_field_1, g_Test_header_field_2, g_Test_header_field_2);
 	g_BodyAjaxTestDone = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE(g_BodyAjaxTestDone,"malloc:failure:ITc_ewk_intercept_request_response_header_add_p");
  	snprintf(g_BodyAjaxTestDone, size+1, g_BodyAjaxTestFormat, g_Test_header_field_1, g_Test_header_field_1, g_Test_header_field_2, g_Test_header_field_2);

	size = snprintf(NULL, 0, g_BodyFormat, g_BaseTitle, g_BodyAjaxTestDone, g_InterceptUrlAjax);
	g_BodyDone = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE_CLEANUP(g_BodyDone,"malloc:failure:ITc_ewk_intercept_request_response_header_add_p",free(g_BodyAjaxTestDone));

	snprintf(g_BodyDone, size+1, g_BodyFormat, g_BaseTitle);

  	size = snprintf(NULL, 0, g_Expected_title_format, g_Test_header_field_1, g_Test_header_value_1, g_Test_header_field_2, g_Test_header_value_2);
  	g_Expected_title_done = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE_CLEANUP(g_Expected_title_done,"malloc:failure:ITc_ewk_intercept_request_response_header_add_p",free(g_BodyAjaxTestDone);free(g_BodyDone));
  	snprintf(g_Expected_title_done, size+1, g_Expected_title_format, g_Test_header_field_1, g_Test_header_value_1, g_Test_header_field_2, g_Test_header_value_2);

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError, NULL);


	emergency_exit_timer = ecore_timer_add(5, webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), webkit_intercept_request_response_header_add_callback, NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, g_InterceptUrl) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();


	if(g_bIsInterceptRequestResponse == false) {
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(g_Header_add_1_result == EINA_FALSE){
		FPRINTF("[Line : %d][%s] unexpected result from callback \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if(g_Header_add_2_result == EINA_FALSE){
		FPRINTF("[Line : %d][%s] unexpected result from callback \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
	Webkit_EFL_main_loop_quit();
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To test ITc_ewk_intercept_request_response_header_map_add_p
//& type: auto
/**
* @testcase 			ITc_ewk_intercept_request_response_header_map_add_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ITc_ewk_intercept_request_response_header_map_add_p
* @apicovered			ewk_intercept_request_response_header_map_add, ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_intercept_request_response_header_map_add_p
* @passcase				When ITc_ewk_intercept_request_response_header_map_add_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_intercept_request_response_header_map_add_p(void)
{
	START_TEST;
	g_Header_add_1_result = EINA_FALSE;
        g_Header_add_2_result = EINA_FALSE;
	g_Header_map_add_result = EINA_FALSE;

	if ( Webkit_EFLCreateWebKitView() == false)
	{
		FPRINTF("[Line : %d][%s] Unable to create EFL webkit view\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int size;
  	size = snprintf(NULL, 0, g_BodyAjaxTestFormat, g_Test_header_field_1, g_Test_header_field_1, g_Test_header_field_2, g_Test_header_field_2);
 	g_BodyAjaxTestDone = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE(g_BodyAjaxTestDone, "Malloc failure:ITc_ewk_intercept_request_response_header_map_add_p")
  	snprintf(g_BodyAjaxTestDone, size+1, g_BodyAjaxTestFormat, g_Test_header_field_1, g_Test_header_field_1, g_Test_header_field_2, g_Test_header_field_2);

	size = snprintf(NULL, 0, g_BodyFormat, g_BaseTitle, g_BodyAjaxTestDone, g_InterceptUrlAjax);
  	g_BodyDone = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE_CLEANUP(g_BodyDone, "Malloc failure :ITc_ewk_intercept_request_response_header_map_add_p",free(g_BodyAjaxTestDone))
	snprintf(g_BodyDone, size+1, g_BodyFormat, g_BaseTitle);

  	size = snprintf(NULL, 0, g_Expected_title_format, g_Test_header_field_1, g_Test_header_value_1, g_Test_header_field_2, g_Test_header_value_2);
  	g_Expected_title_done = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE_CLEANUP(g_Expected_title_done, "Malloc Failure:ITc_ewk_intercept_request_response_header_map_add_p",free(g_BodyAjaxTestDone);free(g_BodyDone))
  	snprintf(g_Expected_title_done, size+1, g_Expected_title_format, g_Test_header_field_1, g_Test_header_value_1, g_Test_header_field_2, g_Test_header_value_2);

	g_HeaderMap = eina_hash_string_small_new(NULL);
  	eina_hash_add(g_HeaderMap, g_Test_header_field_1, g_Test_header_value_1);
  	eina_hash_add(g_HeaderMap, g_Test_header_field_2, g_Test_header_value_2);

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError, NULL);


	emergency_exit_timer = ecore_timer_add(5, webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), webkit_intercept_request_response_header_map_add_callback, NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, g_InterceptUrl) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();


	if(g_bIsInterceptRequestResponse == false) {
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(g_Header_map_add_result == EINA_FALSE){
		FPRINTF("[Line : %d][%s] unexpected result from callback \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
	Webkit_EFL_main_loop_quit();
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To test ITc_ewk_intercept_request_response_set_p
//& type: auto
/**
* @testcase 			ITc_ewk_intercept_request_response_set_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ITc_ewk_intercept_request_response_set_p
* @apicovered			ewk_intercept_request_response_set, ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_intercept_request_response_set_p
* @passcase				When ITc_ewk_intercept_request_response_set_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_intercept_request_response_set_p(void)
{
	START_TEST;
  	char local_title_expected[] = "RESPONSE SET SUCCESS";
	g_Response_set_result = EINA_FALSE;

	if ( Webkit_EFLCreateWebKitView() == false)
	{
		FPRINTF("[Line : %d][%s] Unable to create EFL webkit view\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int size = snprintf(NULL, 0, g_BodyFormat, local_title_expected);
  	g_BodyDone = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE(g_BodyDone, "Malloc failure:ITc_ewk_intercept_request_response_set_p")
  	snprintf(g_BodyDone, size + 1, g_BodyFormat, local_title_expected);
  	g_DataToWrite = strlen(g_BodyDone);

  	size = snprintf(NULL, 0, g_HeadersFormat, g_DataToWrite);
  	g_HeadersDone = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE_CLEANUP(g_HeadersDone, "Malloc failure:ITc_ewk_intercept_request_response_set_p",free(g_BodyDone))
  	snprintf(g_HeadersDone, size + 1, g_HeadersFormat, g_DataToWrite);

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError, NULL);


	emergency_exit_timer = ecore_timer_add(5, webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), webkit_intercept_request_response_set_callback, NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, g_InterceptUrl) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();


	if(g_bIsInterceptRequestResponse == false) {
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(g_Response_set_result == EINA_FALSE){
		FPRINTF("[Line : %d][%s] unexpected result from callback \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if(strcmp(ewk_view_title_get(objWebkit_EFL_view.webview), local_title_expected) != 0){
		FPRINTF("[Line : %d][%s] title mismatched \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
	Webkit_EFL_main_loop_quit();
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To test ITc_ewk_intercept_request_response_status_set_p
//& type: auto
/**
* @testcase 			ITc_ewk_intercept_request_response_status_set_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ITc_ewk_intercept_request_response_status_set_p
* @apicovered			ewk_intercept_request_response_status_set, ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_intercept_request_response_status_set_p
* @passcase				When ITc_ewk_intercept_request_response_status_set_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_intercept_request_response_status_set_p(void)
{
	START_TEST;
	g_BodyAjaxTestDoneStatusSet = "document.title = this.status + ' ' + this.statusText;";
	//g_BodyAjaxTestDone = "document.title = this.status + ' ' + this.statusText;";
	g_Status_set_result = EINA_FALSE;
 	g_StatusCode = 200;

	if ( Webkit_EFLCreateWebKitView() == false)
	{
		FPRINTF("[Line : %d][%s] Unable to create EFL webkit view\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int size = snprintf(NULL, 0, g_BodyFormat, g_BaseTitle, g_BodyAjaxTestDoneStatusSet, g_InterceptUrlAjax);
  	g_BodyDone = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE(g_BodyDone, "Malloc failure:ITc_ewk_intercept_request_response_status_set_p");
	snprintf(g_BodyDone, size+1, g_BodyFormat, g_BaseTitle);

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError, NULL);


	emergency_exit_timer = ecore_timer_add(5, webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), webkit_intercept_request_response_status_set_callback, NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, g_InterceptUrl) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();


	if(g_bIsInterceptRequestResponse == false) {
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(g_Status_set_result == EINA_FALSE){
		FPRINTF("[Line : %d][%s] unexpected result from callback \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
	Webkit_EFL_main_loop_quit();
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To test ITc_ewk_intercept_request_response_write_chunk_p
//& type: auto
/**
* @testcase 			ITc_ewk_intercept_request_response_write_chunk_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ITc_ewk_intercept_request_response_write_chunk_p
* @apicovered			ewk_intercept_request_response_write_chunk, ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_intercept_request_response_write_chunk_p
* @passcase				When ITc_ewk_intercept_request_response_write_chunk_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_intercept_request_response_write_chunk_p(void)
{
	START_TEST;

	if ( Webkit_EFLCreateWebKitView() == false)
	{
		FPRINTF("[Line : %d][%s] Unable to create EFL webkit view\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_SavedInterceptRequest = NULL;
  	g_Event_loop_result = EINA_FALSE;
  	g_DataWriten = 0;
	const char local_title_expected[] = "CHUNKED WRITE SUCCESS";

	int size = snprintf(NULL, 0, g_BodyFormat, local_title_expected);
 	g_BodyDone = (char*)malloc((size + 1) * sizeof(char));
	CHECK_HANDLE(g_BodyDone,"malloc failure:ITc_ewk_intercept_request_response_write_chunk_p");


  	snprintf(g_BodyDone, size + 1, g_BodyFormat, local_title_expected);
  	g_DataToWrite = strlen(g_BodyDone);

	emergency_exit_timer = ecore_timer_add(5, webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), webkit_ewk_intercept_request_response_write_chunk_callback, NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, g_InterceptUrl) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();


	if(g_bIsInterceptRequestResponse == false) {
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	/*if(g_Event_loop_result == EINA_FALSE){
		FPRINTF("[Line : %d][%s] unexpected result from callback \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		Webkit_EFL_main_loop_quit();
		return 1;
	}*/

	if(strcmp(ewk_view_title_get(objWebkit_EFL_view.webview), local_title_expected) != 0){
		FPRINTF("[Line : %d][%s] title mismatched\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
		Webkit_EFL_main_loop_quit();
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", webkit_EFL_LoadError);
	Webkit_EFL_main_loop_quit();
	Webkit_EFLDestroyWebKitView();
	return 0;
}

/** @} */
/** @} */
