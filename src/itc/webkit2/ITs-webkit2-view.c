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


bool g_bWebkit_EFL_ScriptExecuted = false;
static bool g_bWebkit_EFL_LoadSuccess = false;
static Ecore_Timer* emergency_exit_timer;
bool bIsInterceptRequestCalled = false;
static char* g_HttpMethod = NULL;


/**
* @function 		Webkit_EFL_LoadError
* @description	 	Callback function to get webkit load error info
* @parameter		data : user data,webview : evas object, event_info : event information
* @return 			NA
*/
static void Webkit_EFL_LoadError(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadError occurs\\n", __LINE__, API_NAMESPACE);
	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		Webkit_EFL_LoadFinished
* @description	 	Callback function to get webkit load finish info
* @parameter		data : user data, eObject : evas object, dataFinished : event information
* @return 			NA
*/
static void Webkit_EFL_LoadFinished(void* data, Evas_Object* eObject, void* dataFinished)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadFinished Success\\n", __LINE__, API_NAMESPACE);
	g_bWebkit_EFL_LoadSuccess = true;
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		Webkit_EFL_LoadProgress
* @description	 	Callback function to get load progress info
* @parameter		data : user data, eObject : evas object, dataFinished : event information
* @return 			NA
*/
static void Webkit_EFL_LoadProgress(void* data, Evas_Object* eObject, void* dataFinished)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadProgress Invoked\\n", __LINE__, API_NAMESPACE);
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		Webkit_EFL_LoadStarted
* @description	 	Callback function to get load started info
* @parameter		data : user data, eObject : evas object, dataFinished : event information
* @return 			NA
*/
static void Webkit_EFL_LoadStarted(void* data, Evas_Object* eObject, void* dataFinished)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadStarted Invoked\\n", __LINE__, API_NAMESPACE);
  ewk_view_suspend(objWebkit_EFL_view.webview);
  ewk_view_resume(objWebkit_EFL_view.webview);
}

/**
* @function 		Webkit_EFL_onTextFound
* @description	 	Callback function to get webkit on text found info
* @parameter		userData : user data, webview : evas object, eventInfo : event information
* @return 			NA
*/
static void Webkit_EFL_onTextFound(void* userData, Evas_Object* webview, void* eventInfo)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_onTextFound Invoked\\n", __LINE__, API_NAMESPACE);
	int* result = (int*)userData;
	int* matchCount = (int*)eventInfo;
	*result = *matchCount;
}

/**
* @function 		Webkit_EFL_LoopQuit
* @description	 	Callback function for exiting ecore main loop
* @parameter		data : user data
* @return 			bool
*/
static Eina_Bool Webkit_EFL_LoopQuit(void* data)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoopQuit Invoked\\n", __LINE__, API_NAMESPACE);
	Webkit_EFL_main_loop_quit();
	return EINA_FALSE;
}

/**
* @function 		Webkit_EFL_ScriptExecutionFinished
* @description	 	Callback function for script_execute
* @parameter		webview : evas object, result_value : result, data : user data
* @return 			NA
*/
static void Webkit_EFL_ScriptExecutionFinished(Evas_Object* webview, const char* result_value, void* data)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_ScriptExecutionFinished Invoked\\n", __LINE__, API_NAMESPACE);

	if ( result_value )
	{
		FPRINTF("[Line : %d][%s] Webkit_EFL_ScriptExecutionFinished : Result Value = %s\\n", __LINE__, API_NAMESPACE, result_value);
	}

	g_bWebkit_EFL_ScriptExecuted = true;

	Webkit_EFL_main_loop_quit();
}

/**
* @function 		Webkit_emergency_exit_func
* @description	 	emrgency exit function
* @parameter		user data
* @return 			NA
*/
static Eina_Bool Webkit_emergency_exit_func(void* user_data) {
	FPRINTF("[Line : %d][%s] Inside Webkit_emergency_exit_func \\n", __LINE__, API_NAMESPACE);
	Ecore_Timer** timer = (Ecore_Timer**)user_data;
	*timer = NULL;
	Webkit_EFL_main_loop_quit();
	return ECORE_CALLBACK_CANCEL;
}

/**
* @function 		Webkit_intercept_request_callback
* @description	 	callback function
* @parameter		Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data
* @return 			NA
*/
static void Webkit_intercept_request_callback(Evas_Object* o, Ewk_Intercept_Request* intercept_request, void* user_data) {
	FPRINTF("[Line : %d][%s] Inside Webkit_intercept_request_callback \\n", __LINE__, API_NAMESPACE);
	g_HttpMethod = (char*)ewk_intercept_request_http_method_get(intercept_request);
	if (g_HttpMethod) {
		g_HttpMethod = strdup(g_HttpMethod);
	}
	bIsInterceptRequestCalled = true;
}

/**
* @function 		ITs_webkit_efl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_view_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif

	emergency_exit_timer = NULL;
	g_HttpMethod = NULL;
	return;
}


/**
* @function 		ITs_webkit_efl_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_view_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}





//& type: auto
//& purpose: Creates a new webkit EFL view object
/**
* @testcase 			ITc_ewk_view_add_p
* @since_tizen			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description	 		Creates a new webkit EFL view object
* @scenario				Create Webkit View\n
*						Destroy Webkit View
* @apicovered			ewk_view_add
* @passcase				When ewk_view_add behaves properly and returns correct value.
* @failcase				If target api fails or return invalid value.
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_add_p(void)
{
	START_TEST;
	elm_init(0, NULL);
	ewk_init();
	elm_config_accel_preference_set("opengl");


	Evas_Object* pWindow = elm_win_add(NULL, "TC Launcher", ELM_WIN_BASIC);
	if ( NULL == pWindow )
	{
		FPRINTF("[Line : %d][%s] Unable to get window from elm_win_add API call\\n", __LINE__, API_NAMESPACE);
		ewk_shutdown();
		elm_shutdown();
		return 1;
	}

	elm_win_title_set(pWindow, "TC Launcher");
	Evas* pEvas = evas_object_evas_get(pWindow);
	if ( NULL == pEvas )
	{
		FPRINTF("[Line : %d][%s] Unable to get evas from evas_object_evas_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_del(pWindow);
		ewk_shutdown();
		elm_shutdown();
		return 1;
	}

	Evas_Object* pWebView = NULL;
	//Target API
	pWebView = ewk_view_add(pEvas);
	if ( NULL == pWebView )
	{
		FPRINTF("[Line : %d][%s] ewk_view_add returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_del(pWindow);
		ewk_shutdown();
		elm_shutdown();
		return 1;
	}

	evas_object_del(pWebView);
	evas_object_del(pWindow);
	ewk_shutdown();
	elm_shutdown();
	return 0;
}




//& type: auto
//& purpose: Gets Ewk context of the view
/**
* @testcase 			ITc_ewk_view_context_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets Ewk context of the view
* @scenario				Create Webkit View\n
*						Destroy Webkit View
* @apicovered			ewk_view_context_get
* @passcase				When ewk_view_context_get behaves properly and returns correct value
* @failcase				If target API fails or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_context_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		FPRINTF("[Line : %d][%s] Unable to get window from elm_win_add API call\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	Ewk_Context* pValue = NULL;
	//Target API
	pValue = ewk_view_context_get(objWebkit_EFL_view.webview);
	if ( pValue == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_view_context_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Returns the current URL string of the view object
/**
* @testcase 			ITc_ewk_view_url_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns the current URL string of the view object
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the URL\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_url_get
* @passcase				When ewk_view_url_get returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_url_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	const char* pURL = NULL;
	//Target API
	pURL = ewk_view_url_get(objWebkit_EFL_view.webview);
	if ( pURL == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(pURL, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_get returned wrong value; expected = %s, returned = %s\\n", __LINE__, API_NAMESPACE, pPath, pURL);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Asked to set the URL string to the view object
/**
* @testcase 			ITc_ewk_view_url_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Asked to set the URL string to the view object
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the URL\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_url_get
* @passcase				When ewk_view_url_set returns success and set value equals the get value
* @failcase				If target API fails or not set the URL properly
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_url_set_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	Eina_Bool bResult = EINA_FALSE;
	const char* pURL = NULL;
	//Target API
	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error status on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pURL = ewk_view_url_get(objWebkit_EFL_view.webview);
	if ( pURL == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(pURL, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_get returned wrong value; expected = %s, returned = %s\\n", __LINE__, API_NAMESPACE, pPath, pURL);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Reload the current view document
/**
* @testcase 			ITc_ewk_view_reload_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Reload the current view document
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Reload the view\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_reload
* @passcase				When ewk_view_reload returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_reload_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResult = EINA_FALSE;
	//Target API
	bResult = ewk_view_reload(objWebkit_EFL_view.webview);
	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_reload returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Asks the main frame to stop loading
/**
* @testcase 			ITc_ewk_view_stop_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Asks the main frame to stop loading
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Stop loading the view\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_stop
* @passcase				When ewk_view_stop returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_stop_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResult = EINA_FALSE;
	//Target API
	bResult = ewk_view_stop(objWebkit_EFL_view.webview);
	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_stop returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets Ewk settings of the view
/**
* @testcase 			ITc_ewk_view_settings_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets Ewk settings of the view
* @scenario				Create Webkit View\n
*						Call API to get value\n
*						Destroy Webkit View
* @apicovered			ewk_view_settings_get
* @passcase				When ewk_view_settings_get behaves properly and returns correct value
* @failcase				If target API fails or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_settings_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		FPRINTF("[Line : %d][%s] Unable to get window from elm_win_add API call\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	Ewk_Settings* pValue = NULL;
	//Target API
	pValue = ewk_view_settings_get(objWebkit_EFL_view.webview);
	if ( pValue == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_view_settings_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Asks the main frame to navigate back in history
/**
* @testcase 			ITc_ewk_view_back_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Asks the main frame to navigate back in history
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Call target API\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_back
* @passcase				When ewk_view_back returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_back_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char pPath1[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE1, pPath1) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);

	Eina_Bool bResult = EINA_FALSE;
	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath1);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath1);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API

	bResult = ewk_view_back(objWebkit_EFL_view.webview);
	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_back returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Asks the main frame to navigate forward in history
/**
* @testcase 			ITc_ewk_view_forward_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Asks the main frame to navigate forward in history
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Navigate back and Call target API\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_back, ewk_view_forward
* @passcase				When ewk_view_forward returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_forward_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char pPath1[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE1, pPath1) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);

	Eina_Bool bResult = EINA_FALSE;
	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath1);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath1);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( EINA_TRUE != ewk_view_back(objWebkit_EFL_view.webview) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_back returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	//Target API
	bResult = ewk_view_forward(objWebkit_EFL_view.webview);
	Webkit_EFL_main_loop_begin();

	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_forward returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}


	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Checks whether the main frame can navigate back one item in history
/**
* @testcase 			ITc_ewk_view_back_possible_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Checks whether the main frame can navigate back one item in history
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Call target API\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_back_possible
* @passcase				When ewk_view_back_possible returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_back_possible_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char pPath1[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE1, pPath1) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);

	Eina_Bool bResult = EINA_FALSE;
	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath1);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath1);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	bResult = ewk_view_back_possible(objWebkit_EFL_view.webview);
	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_back_possible returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}


	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Checks whether the main frame can navigate forward one item in history
/**
* @testcase 			ITc_ewk_view_forward_possible_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Checks whether the main frame can navigate forward one item in history
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Navigate back and Call target API\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_back, ewk_view_forward_possible
* @passcase				When ewk_view_forward_possible returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_forward_possible_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char pPath1[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE1, pPath1) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	Eina_Bool bResult = EINA_FALSE;
	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath1);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath1);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( EINA_TRUE != ewk_view_back(objWebkit_EFL_view.webview) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_back returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	//Target API
	bResult = ewk_view_forward_possible(objWebkit_EFL_view.webview);
	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_forward_possible returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}


	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Clears the back forward list of a page
/**
* @testcase 			ITc_ewk_view_back_forward_list_clear_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Clears the back forward list of a page
* @scenario				Create Webkit View\n
*						Set Content\n
*						Call the API\n
*						Retrieves the BackForward List and validate\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_view_back_forward_list_clear
* @passcase				When ewk_view_back_forward_list_clear clears the page.
* @failcase				If after target API call, the mainframe still allows the item selection.
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_back_forward_list_clear_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	Ewk_Back_Forward_List_Item* pListItem = NULL;

	Eina_Bool bResult = EINA_FALSE;
	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	ewk_view_back_forward_list_clear(objWebkit_EFL_view.webview);
	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pListItem = ewk_back_forward_list_previous_item_get(pList);
	if ( pListItem != NULL )
	{
		FPRINTF("[Line : %d][%s]Faile : Still Able to get previous item after ewk_view_back_forward_list_clear API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pListItem = ewk_back_forward_list_next_item_get(pList);
	if ( pListItem != NULL )
	{
		FPRINTF("[Line : %d][%s]Faile : Still Able to get next item after ewk_view_back_forward_list_clear API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}


	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets the back forward list associated with this view
/**
* @testcase 			ITc_ewk_view_back_forward_list_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the back forward list associated with this view
* @scenario				Create Webkit View\n
*						Set Content\n
*						Call the API\n
*						Retrieves the BackForward List and validate\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get
* @passcase				When ewk_view_back_forward_list_get returns proper value
* @failcase				If after target API returns invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_back_forward_list_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	Ewk_Back_Forward_List* pList = NULL;
	Eina_Bool bResult = EINA_FALSE;
	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets the current title of the main frame
/**
* @testcase 			ITc_ewk_view_title_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the current title of the main frame
* @scenario				Create Webkit View\n
*						Set Content\n
*						Call the API\n
*						Retrieves the value and validate\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_title_get
* @passcase				When ewk_view_title_get returns proper value
* @failcase				If after target API returns invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_title_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);

	const char* pValue = NULL;
	Eina_Bool bResult = EINA_FALSE;
	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pValue = ewk_view_title_get(objWebkit_EFL_view.webview);
	if ( pValue == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_view_title_get API call return NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(SAMPLE_HTML_FILE_TITLE, pValue) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_title_get returned wrong value; expected = %s, returned = %s\\n", __LINE__, API_NAMESPACE, SAMPLE_HTML_FILE_TITLE, pValue);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets the progress status for loading in the main frame
/**
* @testcase 			ITc_ewk_view_load_progress_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the progress status for loading in the main frame
* @scenario				Create Webkit View\n
*						Set Content\n
*						Call the API\n
*						Retrieves the value and validate\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_load_progress_get
* @passcase				When ewk_view_load_progress_get returns proper value
* @failcase				If after target API returns invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_load_progress_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,progress", Webkit_EFL_LoadProgress, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	double dValue = 0.0;
	double dProgressComplete = 1.0;

	Eina_Bool bResult = EINA_FALSE;
	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	//Target API
	dValue = ewk_view_load_progress_get(objWebkit_EFL_view.webview);
	if ( dValue > dProgressComplete || dValue < 0.0 )
	{
		FPRINTF("[Line : %d][%s] ewk_view_load_progress_get returned wrong value = %f\\n", __LINE__, API_NAMESPACE, dValue);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}


	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Set the user agent of the page
/**
* @testcase 			ITc_ewk_view_user_agent_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Set the user agent of the page
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_view_user_agent_set, ewk_view_user_agent_get
* @passcase				When ewk_view_user_agent_set behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_user_agent_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	const char* pValue = NULL;

	//Target API
	bResultSet = ewk_view_user_agent_set(objWebkit_EFL_view.webview, SET_USER_AGENT);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_user_agent_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pValue = ewk_view_user_agent_get(objWebkit_EFL_view.webview);
	if ( pValue == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_view_user_agent_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(SET_USER_AGENT, pValue) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_user_agent_get returned wrong value; expected = %s, returned = %s\\n", __LINE__, API_NAMESPACE, SET_USER_AGENT, pValue);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets user agent string
/**
* @testcase 			ITc_ewk_view_user_agent_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets user agent string
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_view_user_agent_set, ewk_view_user_agent_get
* @passcase				When ewk_view_user_agent_get behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_user_agent_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	const char* pValue = NULL;

	bResultSet = ewk_view_user_agent_set(objWebkit_EFL_view.webview, SET_USER_AGENT);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_user_agent_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pValue = ewk_view_user_agent_get(objWebkit_EFL_view.webview);
	if ( pValue == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_view_user_agent_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(SET_USER_AGENT, pValue) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_user_agent_get returned wrong value; expected = %s, returned = %s\\n", __LINE__, API_NAMESPACE, SET_USER_AGENT, pValue);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets the last known content size
/**
* @testcase 			ITc_ewk_view_contents_size_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the last known content size
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Call the target API\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_contents_size_get
* @passcase				When ewk_view_contents_size_get returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_contents_size_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	// Use Webkit_EFL_LoadFinished with callback, cause we need the same result
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "contents,size,changed", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "contents,size,changed", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "contents,size,changed", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResult = EINA_FALSE;
	Evas_Coord nWidth = 0;
	Evas_Coord nHeight = 0;

	//Target API
	bResult = ewk_view_contents_size_get(objWebkit_EFL_view.webview, &nWidth, &nHeight);
	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_contents_size_get API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "contents,size,changed", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( (nWidth <= 0) || (nHeight <= 0) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_contents_size_get returned incorrect value (width = %d, height = %d)\\n", __LINE__, API_NAMESPACE, (int)nWidth, (int)nHeight);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "contents,size,changed", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "contents,size,changed", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Requests the execution of given script
/**
* @testcase 			ITc_ewk_view_script_execute_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Requests the execution of given script
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Call the target API\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_script_execute
* @passcase				When ewk_view_script_execute gets able to execute it properly
* @failcase				If target API fails or callback not hit.
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_script_execute_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResult = EINA_FALSE;
	//Target API
	bResult = ewk_view_script_execute(objWebkit_EFL_view.webview, TEST_JS_SCRIPT, Webkit_EFL_ScriptExecutionFinished, NULL);
	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_script_execute API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_ScriptExecuted = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_ScriptExecuted )
	{
		FPRINTF("[Line : %d][%s] ewk_view_script_execute callback not invoked\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}


	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}
//& type: auto
//& purpose: Scales the current page, centred at the given point
/**
* @testcase 			ITc_ewk_view_scale_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Scales the current page, centred at the given point
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_view_scale_set, ewk_view_scale_get
* @passcase				When ewk_view_scale_set behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_scale_set_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	double dScaleFactor = SCALE_FACTOR_VALUE;
	double dScaleFactorGet = 0.0;
	Evas_Coord centerX = X_CENTRE;
	Evas_Coord centerY = Y_CENTRE;

	//Target API
	bResultSet = ewk_view_scale_set(objWebkit_EFL_view.webview, dScaleFactor, centerX, centerY);

	ecore_timer_add(TIMEOUT_VALUE, Webkit_EFL_LoopQuit, 0);
	Webkit_EFL_main_loop_begin();

	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scale_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	dScaleFactorGet = ewk_view_scale_get(objWebkit_EFL_view.webview);
	if ( dScaleFactor != dScaleFactorGet )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scale_get returned wrong value; expected = %f, returned = %f\\n", __LINE__, API_NAMESPACE, dScaleFactor, dScaleFactorGet);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets scale factor for the page
/**
* @testcase 			ITc_ewk_view_scale_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets scale factor for the page
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_view_scale_set, ewk_view_scale_get
* @passcase				When ewk_view_scale_get behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_scale_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	double dScaleFactor = SCALE_FACTOR_VALUE;
	double dScaleFactorGet = 0.0;
	Evas_Coord centerX = X_CENTRE;
	Evas_Coord centerY = Y_CENTRE;

	//Target API
	bResultSet = ewk_view_scale_set(objWebkit_EFL_view.webview, dScaleFactor, centerX, centerY);

	ecore_timer_add(TIMEOUT_VALUE, Webkit_EFL_LoopQuit, 0);
	Webkit_EFL_main_loop_begin();

	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scale_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API

	dScaleFactorGet = ewk_view_scale_get(objWebkit_EFL_view.webview);
	if ( dScaleFactor != dScaleFactorGet )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scale_get returned wrong value; expected = %f, returned = %f\\n", __LINE__, API_NAMESPACE, dScaleFactor, dScaleFactorGet);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Exits the fullscreen mode
/**
* @testcase 			ITc_ewk_view_fullscreen_exit_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Exits the fullscreen mode
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Call the target API\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_fullscreen_exit
* @passcase				When ewk_view_fullscreen_exit returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_fullscreen_exit_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	ewk_view_fullscreen_exit(objWebkit_EFL_view.webview);


	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Suspends the operation associated with the view object
/**
* @testcase 			ITc_ewk_view_suspend_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Suspends the operation associated with the view object
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Call the API\n
*						Destroy Webkit View
* @apicovered			ewk_view_suspend
* @passcase				When ewk_view_suspend behaves properly
* @failcase				If target API didn't behave properly
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_suspend_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,started", Webkit_EFL_LoadStarted, NULL);
  evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,started", Webkit_EFL_LoadStarted);
  evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
  evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);

		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,started", Webkit_EFL_LoadStarted);
  evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Resumes the operation associated with the view object after it gets suspended
/**
* @testcase 			ITc_ewk_view_resume_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Resumes the operation associated with the view object after it gets suspended
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Call the API\n
*						Destroy Webkit View
* @apicovered			ewk_view_suspend, ewk_view_resume
* @passcase				When ewk_view_resume behaves properly
* @failcase				If target API didn't behave properly
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_resume_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,started", Webkit_EFL_LoadStarted, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,started", Webkit_EFL_LoadStarted);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,started", Webkit_EFL_LoadStarted);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}



//& type: auto
//& purpose: Requests loading of the given request data
/**
* @testcase 			ITc_ewk_view_url_request_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Requests loading of the given request data
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_request_set
* @passcase				When ewk_view_url_request_set returns success and callback invoked properly
* @failcase				If target API fails or callback not invoked properly
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_url_request_set_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	Eina_Bool bResult = EINA_FALSE;
	//Target API
	bResult = ewk_view_url_request_set(objWebkit_EFL_view.webview, pPath, EWK_HTTP_METHOD_GET, NULL, NULL);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_request_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_request_set returned load error status on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}


	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}
#if defined(MOBILE) ||  defined(TIZENIOT) || defined(TV) //Starts MOBILE or TIZENIOT or TV
//& type: auto
//& purpose: Requests loading the given content on the view object
/**
* @testcase 			ITc_ewk_view_contents_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Requests loading the given content on the view object
* @scenario				Create Webkit View\n
*						Call the target API\n
*						Destroy Webkit View
* @apicovered			ewk_view_contents_set
* @passcase				When ewk_view_contents_set returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_contents_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Eina_Bool bResult = EINA_FALSE;
	//Target API
	bResult = ewk_view_contents_set(objWebkit_EFL_view.webview, SET_CONTENT, strlen(SET_CONTENT), 0, 0, 0);
	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_contents_set returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}
#endif  //End MOBILE or TIZENIOT or TV
//& type: auto
//& purpose: Scrolls the webpage of view
/**
* @testcase 			ITc_ewk_view_scroll_by_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Scrolls the webpage of view
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_view_scroll_by, ewk_view_scale_set, ewk_view_scroll_set, ewk_view_scroll_pos_get
* @passcase				When ewk_view_scroll_by behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_scroll_by_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_SCROLL_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	int nPosX = 0;
	int nPosY = 0;

	bResultSet = ewk_view_scroll_set(objWebkit_EFL_view.webview, 0, 0);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scroll_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

        ecore_timer_add(1.0f, Webkit_EFL_LoopQuit, 0);
        Webkit_EFL_main_loop_begin();
	//Target API
	ewk_view_scroll_by(objWebkit_EFL_view.webview, SCROLL_BY_X, SCROLL_BY_Y);

        ecore_timer_add(1.0f, Webkit_EFL_LoopQuit, 0);
        Webkit_EFL_main_loop_begin();

	bResultSet = ewk_view_scroll_pos_get(objWebkit_EFL_view.webview, &nPosX, &nPosY);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scroll_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( nPosX != SCROLL_BY_X || nPosY != SCROLL_BY_Y )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scale_get returned wrong value; expected = (%d,%d), returned = (%d,%d)\\n", __LINE__, API_NAMESPACE, SCROLL_BY_X, SCROLL_BY_Y, nPosX, nPosY);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets the current scroll position of the view
/**
* @testcase 			ITc_ewk_view_scroll_pos_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the current scroll position of the view
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_view_scale_set, ewk_view_scroll_set, ewk_view_scroll_pos_get
* @passcase				When ewk_view_scroll_pos_get behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_scroll_pos_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_SCROLL_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	int nPosX = 0;
	int nPosY = 0;

	bResultSet = ewk_view_scroll_set(objWebkit_EFL_view.webview, SCROLL_BY_X, SCROLL_BY_Y);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scroll_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

        ecore_timer_add(1.0f, Webkit_EFL_LoopQuit, 0);
        Webkit_EFL_main_loop_begin();

	//Target API
	bResultSet = ewk_view_scroll_pos_get(objWebkit_EFL_view.webview, &nPosX, &nPosY);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scroll_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( nPosX != SCROLL_BY_X || nPosY != SCROLL_BY_Y )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scale_get returned wrong value; expected = (%d,%d), returned = (%d,%d)\\n", __LINE__, API_NAMESPACE, SCROLL_BY_X, SCROLL_BY_Y, nPosX, nPosY);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Sets an absolute scroll position of the view
/**
* @testcase 			ITc_ewk_view_scroll_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Sets an absolute scroll position of the view
* @scenario				Create Webkit View\n
*						Set Value\n
*						Retrieve value\n
*						Validate the set and get values\n
*						Destroy Webkit View
* @apicovered			ewk_view_scale_set, ewk_view_scroll_set, ewk_view_scroll_pos_get
* @passcase				When ewk_view_scroll_set behaves properly and set value equals to value received
* @failcase				If target API fails or value mismatch occurs
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_scroll_set_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_SCROLL_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;
	int nPosX = 0;
	int nPosY = 0;

	//Target API
	bResultSet = ewk_view_scroll_set(objWebkit_EFL_view.webview, SCROLL_BY_X, SCROLL_BY_Y);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scroll_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

        ecore_timer_add(1.0f, Webkit_EFL_LoopQuit, 0);
        Webkit_EFL_main_loop_begin();

	bResultSet = ewk_view_scroll_pos_get(objWebkit_EFL_view.webview, &nPosX, &nPosY);
	if ( bResultSet != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scroll_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( nPosX != SCROLL_BY_X || nPosY != SCROLL_BY_Y )
	{
		FPRINTF("[Line : %d][%s] ewk_view_scale_get returned wrong value; expected = (%d,%d), returned = (%d,%d)\\n", __LINE__, API_NAMESPACE, SCROLL_BY_X, SCROLL_BY_Y, nPosX, nPosY);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}


	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Searches and highlights the given string in the document
/**
* @testcase 			ITc_ewk_view_text_find_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Searches and highlights the given string in the document
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Call the target API\n
*						Destroy Webkit View
* @apicovered			ewk_view_url_set, ewk_view_text_find
* @passcase				When ewk_view_text_find returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_view_text_find_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_FILE_VIEW_TEXT_FIND, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	int nMatchCount = -1;
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "text,found", Webkit_EFL_onTextFound, &nMatchCount);

	Eina_Bool bResult = EINA_FALSE;
	int nActualCount = 3;//apple appeared 3 times in the string

	//Target API
	bResult = ewk_view_text_find(objWebkit_EFL_view.webview, "apple", EWK_FIND_OPTIONS_SHOW_OVERLAY, 100);
	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_text_find returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "text,found", Webkit_EFL_onTextFound);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	while ( nMatchCount < 0 )
	{
		ecore_main_loop_iterate();
	}

	if ( nMatchCount != nActualCount )
	{
		FPRINTF("[Line : %d][%s] ewk_view_text_find returned incorrect count value = %d\\n", __LINE__, API_NAMESPACE, nMatchCount);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "text,found", Webkit_EFL_onTextFound);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}


	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "text,found", Webkit_EFL_onTextFound);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: Sends the orientation of the device
//& type: auto
/**
* @testcase 			ITc_ewk_view_orientation_send_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Sends the orientation of the device
* @scenario				ewk_view_orientation_send
* @apicovered			ewk_view_orientation_send
* @passcase				When ewk_view_orientation_send is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_view_orientation_send_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	ewk_view_orientation_send(objWebkit_EFL_view.webview, PORIENT);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

#if defined(MOBILE) ||  defined(TIZENIOT) || defined(TV)
//& purpose: To clear selected text
//& type: auto
/**
* @testcase 			ITc_ewk_view_text_selection_clear_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			To clear selected text
* @scenario				ewk_view_url_set\n
*						ewk_view_text_selection_text_get\n
*						ewk_view_text_selection_clear
* @apicovered			ewk_view_url_set, ewk_view_text_selection_text_get, ewk_view_text_selection_clear
* @passcase				When ewk_view_text_selection_clear is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_view_text_selection_clear_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_EWK_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	const char* selected_text = ewk_view_text_selection_text_get(objWebkit_EFL_view.webview);
	if (!strlen(selected_text))
	{
		FPRINTF("[Line : %d][%s] pPAth call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;

	}

	ewk_view_text_selection_clear(objWebkit_EFL_view.webview);

	selected_text = ewk_view_text_selection_text_get(objWebkit_EFL_view.webview);
	if (strlen(selected_text))
	{
		FPRINTF("[Line : %d][%s] ewk_view_text_selection_text_get failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;

	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To get the selected text
//& type: auto
/**
* @testcase 			ITc_ewk_view_text_selection_text_get_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			To get the selected text
* @scenario				ewk_view_text_selection_text_get
* @apicovered			ewk_view_text_selection_text_get
* @passcase				When ewk_view_text_selection_text_get is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_view_text_selection_text_get_p(void)
{
	START_TEST;
	const char *pPath = NULL;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	pPath = ewk_view_text_selection_text_get(objWebkit_EFL_view.webview);
	if (pPath == NULL)
	{
		FPRINTF("[Line : %d][%s] ewk_view_text_selection_text_get API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	Webkit_EFLDestroyWebKitView();
	return 0;

}
#endif

//& purpose: To set the current page's visibility
//& type: auto
/**
* @testcase 			ITc_ewk_view_visibility_set_p
* @since_tizen			2.4
* @owner				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			To set the current page's visibility
* @scenario				ewk_view_visibility_set
* @apicovered			ewk_view_visibility_set
* @passcase				When ewk_view_visibility_set is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_view_visibility_set_p(void)
{
	START_TEST;

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Eina_Bool bResultSet = EINA_FALSE;

	//Target API
	bResultSet = ewk_view_visibility_set(objWebkit_EFL_view.webview, EINA_TRUE);
	if (bResultSet != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_visibility_set API call returned false error value\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	Webkit_EFLDestroyWebKitView();
	return 0;

}

//& purpose: To test ewk_view_html_string_load
//& type: auto
/**
* @testcase 			ITc_ewk_view_html_string_load_p
* @since_tizen			2.4
* @owner				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			To test ewk_view_html_string_load
* @scenario				Call ewk_view_html_string_load
* @apicovered			ewk_view_html_string_load
* @passcase				When ewk_view_html_string_load is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_view_html_string_load_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	Eina_Bool bResult = EINA_FALSE;

	bResult = ewk_view_html_string_load(objWebkit_EFL_view.webview, pPath, NULL, NULL);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_html_string_load returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& purpose: To test ewk_view_evaluate_javascript
//& type: auto
/**
* @testcase 			ITc_ewk_view_evaluate_javascript_p
* @since_tizen			3.0
* @owner				SRID(shilpa.j)
* @reviewer				SRID(parshant.v)
* @type					auto
* @description			To test ewk_view_html_string_load
* @scenario				Call ewk_view_evaluate_javascript
* @apicovered			ewk_view_evaluate_javascript
* @passcase				When ewk_view_evaluate_javascript is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_view_evaluate_javascript_p(void)
{
	START_TEST;
	const char* TEST_STRING = "test evaluate javascript";
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);

    if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
    {
        FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
        evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
        evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
        Webkit_EFLDestroyWebKitView();
        return 1;
    }

	Eina_Bool bResult = EINA_FALSE;
	Webkit_EFL_main_loop_begin();

	bResult = ewk_view_evaluate_javascript(objWebkit_EFL_view.webview, "sendResult",TEST_STRING);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_evaluate_javascript returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}
/**
* @function 		Webkit_EFL_message_handler_add
* @description	 	Callback function for received message from JavaScript.
* @parameter		Evas_Object :view, Ewk_Script_Message : evas message
* @return 			NA
*/
static void Webkit_EFL_message_handler_add(Evas_Object* view, Ewk_Script_Message message)
{
	FPRINTF("[Line : %d][%s]Inside callback \"ewk_view_javascript_message_handler_add_cb\"\\n", __LINE__, API_NAMESPACE);
	 const char* name = message.name;
	if (!strcmp(name,"MyJavaScriptInterface"))
	{
        FPRINTF("[Line : %d][%s]Inside callback \"Webkit_EFL_message_handler_add  - Same message received\"\\n", __LINE__, API_NAMESPACE);
    }
	else
	{
        FPRINTF("[Line : %d][%s]Inside callback \"Webkit_EFL_message_handler_add  - Mismatch Received sent message\"\\n", __LINE__, API_NAMESPACE);
	}
	Webkit_EFL_main_loop_quit();
}

//& purpose: To test ITc_ewk_view_javascript_message_handler_add_p
//& type: auto
/**
* @testcase 			ITc_ewk_view_evaluate_javascript_p
* @since_tizen			3.0
* @owner				SRID(shilpa.j)
* @reviewer				SRID(parshant.v)
* @type					auto
* @description			To test ITc_ewk_view_javascript_message_handler_add_p
* @scenario				Call ITc_ewk_view_javascript_message_handler_add_p
* @apicovered			ITc_ewk_view_javascript_message_handler_add_p
* @passcase				When ITc_ewk_view_javascript_message_handler_add_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_view_javascript_message_handler_add_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	Eina_Bool bResult = EINA_FALSE;

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "message,handler,add", Webkit_EFL_message_handler_add, NULL);

	//Webkit_EFL_main_loop_begin();

	bResult = ewk_view_javascript_message_handler_add(objWebkit_EFL_view.webview, Webkit_EFL_message_handler_add,"MyJavaScriptInterface");
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_javascript_message_handler_add returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "message,handler,add", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	g_bWebkit_EFL_LoadSuccess = false;

	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	bResult = ewk_view_script_execute(objWebkit_EFL_view.webview, TEST_JS_SCRIPT, Webkit_EFL_ScriptExecutionFinished, NULL);
	if ( bResult != EINA_TRUE )
	{
		FPRINTF("[Line : %d][%s] ewk_view_script_execute API call returned false error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	g_bWebkit_EFL_ScriptExecuted = false;
	Webkit_EFL_main_loop_begin();

	if ( false == g_bWebkit_EFL_ScriptExecuted )
	{
		FPRINTF("[Line : %d][%s] ewk_view_script_execute callback not invoked\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "message,handler,add", NULL);

	Webkit_EFLDestroyWebKitView();
	return 0;
}
//& purpose: To test ITc_ewk_context_intercept_request_callback_set_p
//& type: auto
/**
* @testcase 			ITc_ewk_context_intercept_request_callback_set_p
* @since_tizen			3.0
* @owner				SRID(sameer.g1)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ewk_context_intercept_request_callback_set
* @scenario				Call ITc_ewk_view_javascript_message_handler_add_p
* @apicovered			ewk_context_intercept_request_callback_set
* @passcase				When ITc_ewk_context_intercept_request_callback_set_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_context_intercept_request_callback_set_p(void)
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

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);
	//evas_object_smart_callback_add(objWebkit_EFL_view.webview, "message,handler,add", Webkit_EFL_message_handler_add, NULL);

	emergency_exit_timer = ecore_timer_add(5, Webkit_emergency_exit_func, &emergency_exit_timer);
	ewk_context_intercept_request_callback_set(ewk_view_context_get(objWebkit_EFL_view.webview), Webkit_intercept_request_callback, NULL);

	if ( ewk_view_url_set(objWebkit_EFL_view.webview, pPath) != EINA_TRUE)
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if(bIsInterceptRequestCalled == false) {
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		FPRINTF("[Line : %d][%s] callback not invoked by ewk_context_intercept_request_callback_set  \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(g_HttpMethod == NULL) {
		FPRINTF("[Line : %d][%s] http method not called \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if(strcmp(g_HttpMethod, expected_method) != 0){
		FPRINTF("[Line : %d][%s] unexpected http method \\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}
//& purpose: To test ITc_ewk_view_focus_set_get_p
//& type: auto
/**
* @testcase 			ITc_ewk_view_focus_set_get_p
* @since_tizen			3.0
* @owner				SRID(manu.tiwari)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			To test ITc_ewk_view_focus_set_get_p
* @scenario				Call ewk_view_focus_set and ewk_view_focus_get api
* @apicovered			ewk_view_focus_set and ewk_view_focus_get
* @passcase				When ITc_ewk_view_focus_set_get_p is successful
* @failcase				If target API fails or return invalid value
* @precondition			None
* @postcondition		None
*/
int ITc_ewk_view_focus_set_get_p(void)
{
    START_TEST;

	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError, NULL);

	Eina_Bool bResult = EINA_FALSE;
	bResult = ewk_view_url_set(objWebkit_EFL_view.webview, pPath);
	if ( EINA_TRUE != bResult )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned false error value on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	Webkit_EFL_main_loop_begin();
	if ( false == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned load error value for %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	bResult = ewk_view_focus_set(objWebkit_EFL_view.webview, EINA_TRUE);
	if (EINA_TRUE != bResult)
	{
		FPRINTF("[Line : %d][%s] ewk_view_focus_set returned error value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
    ecore_timer_add(2.0f, Webkit_EFL_LoopQuit, 0);
    Webkit_EFL_main_loop_begin();

    Eina_Bool focus = ewk_view_focus_get(objWebkit_EFL_view.webview);
	if (EINA_TRUE != focus)
	{
		FPRINTF("[Line : %d][%s] ewk_view_focus_get returned mismatched value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();

    return 0;
}

/** @} */
/** @} */
