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


int g_nFail_ewk_error_url_get = INITIALIZE_FAIL;
int g_nFail_ewk_error_code_get = INITIALIZE_FAIL;
int g_nFail_ewk_error_description_get = INITIALIZE_FAIL;
int g_nFail_ewk_error_cancellation_get = INITIALIZE_FAIL;

static bool g_bWebkit_EFL_LoadSuccess = false;
char pPath[PATH_LEN] = {0,};

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
* @function			Webkit_EFL_LoadError_ewk_error_url_get
* @description		Load Error callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
static void Webkit_EFL_LoadError_ewk_error_url_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadError_ewk_error_url_get invoked\\n", __LINE__, API_NAMESPACE);

	g_bWebkit_EFL_LoadSuccess = false;

	Ewk_Error* pLoadErrorObj = (Ewk_Error*)event_info;
	g_nFail_ewk_error_url_get = 0;
	if ( pLoadErrorObj )
	{
		const char* pURL = NULL;
		//Target API
		pURL = ewk_error_url_get(pLoadErrorObj);
		if ( pURL == NULL )
		{
			g_nFail_ewk_error_url_get++;
			FPRINTF("[Line : %d][%s] ewk_error_url_get returned NULL value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}

		char pPathURL[PATH_LEN] = {0,};
		Webkit_EFLAppendToDataPathWithFileFormat(INVALID_FILE_PATH, pPathURL);
		if ( 0 != strcmp(pURL, pPathURL) )
		{
			g_nFail_ewk_error_url_get++;
			FPRINTF("[Line : %d][%s] ewk_error_url_get returned incorrect failing URL; expected = %s, returned = %s\\n", __LINE__, API_NAMESPACE, pPathURL, pURL);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get load error object\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_error_url_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_LoadError_ewk_error_code_get
* @description		Load Error callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
static void Webkit_EFL_LoadError_ewk_error_code_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadError_ewk_error_code_get invoked\\n", __LINE__, API_NAMESPACE);

	g_bWebkit_EFL_LoadSuccess = false;
	Ewk_Error* pLoadErrorObj = (Ewk_Error*)event_info;
	g_nFail_ewk_error_code_get = 0;
	if ( pLoadErrorObj )
	{

		Ewk_Error_Code eErrorCode = EWK_ERROR_CODE_UNKNOWN;
		//Target API
		eErrorCode = ewk_error_code_get(pLoadErrorObj);
		if ( (eErrorCode != EWK_ERROR_CODE_BAD_URL) && (eErrorCode != EWK_ERROR_CODE_FAILED_FILE_IO) )
		{
			g_nFail_ewk_error_code_get++;
			FPRINTF("[Line : %d][%s] ewk_error_code_get returned incorrect error code; returned = %d, expected = EWK_ERROR_CODE_BAD_URL or EWK_ERROR_CODE_FAILED_FILE_IO; EWK_ERROR_CODE_UNKNOWN = %d; EWK_ERROR_CODE_BAD_URL = %d\\n", __LINE__, API_NAMESPACE, (int)eErrorCode, (int)EWK_ERROR_CODE_UNKNOWN, (int)EWK_ERROR_CODE_BAD_URL);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get load error object\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_error_code_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_LoadError_ewk_error_description_get
* @description		Load Error callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
static void Webkit_EFL_LoadError_ewk_error_description_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadError_ewk_error_description_get invoked\\n", __LINE__, API_NAMESPACE);

	g_bWebkit_EFL_LoadSuccess = false;
	Ewk_Error* pLoadErrorObj = (Ewk_Error*)event_info;
	g_nFail_ewk_error_description_get = 0;
	if ( pLoadErrorObj )
	{

		const char* pDescription = NULL;
		//Target API
		pDescription = ewk_error_description_get(pLoadErrorObj);
		if ( pDescription == NULL )
		{
			g_nFail_ewk_error_description_get++;
			FPRINTF("[Line : %d][%s] ewk_error_description_get returned NULL value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get load error object\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_error_description_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_LoadError_ewk_error_cancellation_get
* @description		Load Error callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
static void Webkit_EFL_LoadError_ewk_error_cancellation_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_LoadError_ewk_error_cancellation_get invoked\\n", __LINE__, API_NAMESPACE);

	g_bWebkit_EFL_LoadSuccess = false;
	Ewk_Error* pLoadErrorObj = (Ewk_Error*)event_info;
	g_nFail_ewk_error_cancellation_get = 0;
	if ( pLoadErrorObj )
	{
		Eina_Bool eRetBool = EINA_TRUE;
		//Target API
		eRetBool = ewk_error_cancellation_get(pLoadErrorObj);
		if ( eRetBool != EINA_FALSE )
		{
			g_nFail_ewk_error_cancellation_get++;
			FPRINTF("[Line : %d][%s] ewk_error_cancellation_get returned incorrect cancelled status value = EINA_TRUE\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get load error object\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_error_cancellation_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}


/**
* @function 		ITs_webkit_efl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_error_startup(void)
{
	
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}


/**
* @function 		ITs_webkit_efl_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_error_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type: auto
//& purpose: Query failing URL for load error
/**
* @testcase 			ITc_ewk_error_url_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Query failing URL for load error
* @scenario				Create Webkit Context Menu View\n
*						Load Invalid file to invoke load error callback\n
*						Call ewk_error_url_get and validate the result\n
*						Destroy webkit context menu view
* @apicovered			ewk_error_url_get
* @passcase				When ewk_error_url_get behaves properly
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_error_url_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(INVALID_FILE_PATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_url_get, NULL);

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_url_get);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( true == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s]Load Success returns for invalid file url : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_url_get);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_url_get);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_error_url_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Query failing URL for load error
/**
* @testcase 			ITc_ewk_error_code_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Query failing URL for load error
* @scenario				Create Webkit Context Menu View\n
*						Load Invalid file to invoke load error callback\n
*						Call ewk_error_code_get and validate the result\n
*						Destroy webkit context menu view
* @apicovered			ewk_error_code_get
* @passcase				When ewk_error_code_get behaves properly
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_error_code_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(INVALID_FILE_PATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_code_get, NULL);

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_code_get);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( true == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s]Load Success returns for invalid file url : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_code_get);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_code_get);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_error_code_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Query failing URL for load error
/**
* @testcase 			ITc_ewk_error_description_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Query failing URL for load error
* @scenario				Create Webkit Context Menu View\n
*						Load Invalid file to invoke load error callback\n
*						Call ewk_error_description_get and validate the result\n
*						Destroy webkit context menu view
* @apicovered			ewk_error_description_get
* @passcase				When ewk_error_description_get behaves properly
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_error_description_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(INVALID_FILE_PATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_description_get, NULL);

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_description_get);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( true == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s]Load Success returns for invalid file url : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_description_get);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_description_get);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_error_description_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Query failing URL for load error
/**
* @testcase 			ITc_ewk_error_cancellation_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Query failing URL for load error
* @scenario				Create Webkit Context Menu View\n
*						Load Invalid file to invoke load error callback\n
*						Call ewk_error_cancellation_get and validate the result\n
*						Destroy webkit context menu view
* @apicovered			ewk_error_cancellation_get
* @passcase				When ewk_error_cancellation_get behaves properly
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_error_cancellation_get_p(void)
{
	START_TEST;
	char pPath[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(INVALID_FILE_PATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_cancellation_get, NULL);

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_url_set returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_cancellation_get);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( true == g_bWebkit_EFL_LoadSuccess )
	{
		FPRINTF("[Line : %d][%s]Load Success returns for invalid file url : %s\\n", __LINE__, API_NAMESPACE, pPath);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_cancellation_get);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError_ewk_error_cancellation_get);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_error_cancellation_get > 0 )
	{
		return 1;
	}
	return 0;
}

/** @} */
/** @} */