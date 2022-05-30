//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
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

//& set: WebkitEfl
static bool g_bWebkit_EFL_LoadSuccess = false;

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
* @function 		ITs_webkit_efl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_startup(void)
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
void ITs_webkit_efl_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) || defined(TV)//Starts MOBILE or  TIZENIOT or WEARABLE

/** @addtogroup itc-webkit2-testcases
*  @brief 		Integration testcases for module webkit2
*  @ingroup 	itc-webkit2
*  @{
*/

//& type: auto
//& purpose: Initialise webkit instance
/**
* @testcase 			ITc_webkit_efl_ewk_init_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Initialise webkit instance
* @scenario				Initialise/Increases reference count of webkit instance\n
*						Destroy/Decreases reference count of webkit instance
* @apicovered			ewk_init, ewk_shutdown
* @passcase				When ewk_init returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_webkit_efl_ewk_init_p(void)
{
	START_TEST;

	//Target API
	int nRetValInit = ewk_init();
	if ( nRetValInit <= 0 )
	{
		FPRINTF("[Line : %d][%s] ewk_init failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRetValShutDown = ewk_shutdown();
	if ( nRetValShutDown != (nRetValInit-1) )	// reference count should decrease by 1
	{
		FPRINTF("[Line : %d][%s] ewk_shutdown failed, webkit instance reference count = %d on initialisation and %d on shutdown\\n", __LINE__, API_NAMESPACE, nRetValInit, nRetValShutDown);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Shutdown webkit instance.
/**
* @testcase 			ITc_webkit_efl_ewk_shutdown_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Shutdown webkit instance
* @scenario				Initialise/Increases reference count of webkit instance\n
*						Destroy/Decreases reference count of webkit instance
* @apicovered			ewk_init, ewk_shutdown
* @passcase				When ewk_shutdown returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_webkit_efl_ewk_shutdown_p(void)
{
	START_TEST;
	int nRetValInit = ewk_init();
	if ( nRetValInit <= 0 )
	{
		FPRINTF("[Line : %d][%s] ewk_init failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	//Target API
	int nRetValShutDown = ewk_shutdown();
	if ( nRetValShutDown != (nRetValInit-1) )	// reference count should decrease by 1
	{
		FPRINTF("[Line : %d][%s] ewk_shutdown failed, webkit instance reference count = %d on initialisation and %d on shutdown\\n", __LINE__, API_NAMESPACE, nRetValInit, nRetValShutDown);
		return 1;
	}
	return 0;
}
#endif // End MOBILE or TIZENIOT or WEARABLE
//& type: auto
//& purpose: Returns the current item in the BackForward list
/**
* @testcase 			ITc_ewk_back_forward_list_current_item_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns the current item in the BackForward list
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Retrieves the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_current_item_get
* @passcase				When ewk_back_forward_list_current_item_get returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_current_item_get_p(void)
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

	Ewk_Back_Forward_List_Item* pListItem = NULL;
	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pListItem = ewk_back_forward_list_current_item_get(pList);
	if ( pListItem == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_current_item_get returned NULL value\\n", __LINE__, API_NAMESPACE);
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
//& purpose: Returns the previous item in the BackForward list
/**
* @testcase 			ITc_ewk_back_forward_list_previous_item_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns the previous item in the BackForward list
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Retrieves the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_previous_item_get
* @passcase				When ewk_back_forward_list_previous_item_get returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_previous_item_get_p(void)
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

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath1) )
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
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath1);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Ewk_Back_Forward_List_Item* pListItem = NULL;
	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pListItem = ewk_back_forward_list_previous_item_get(pList);
	if ( pListItem == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_previous_item_get returned NULL value\\n", __LINE__, API_NAMESPACE);
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
//& purpose: Returns the next item in the BackForward list
/**
* @testcase 			ITc_ewk_back_forward_list_next_item_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns the next item in the BackForward list
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Retrieves the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_next_item_get
* @passcase				When ewk_back_forward_list_next_item_get returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_next_item_get_p(void)
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

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath1) )
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
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath1);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( EINA_TRUE != ewk_view_back(objWebkit_EFL_view.webview) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_back returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	Ewk_Back_Forward_List_Item* pListItem = NULL;
	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pListItem = ewk_back_forward_list_next_item_get(pList);
	if ( pListItem == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_next_item_get returned NULL value\\n", __LINE__, API_NAMESPACE);
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
//& purpose: Returns the count of items in the BackForward list
/**
* @testcase 			ITc_ewk_back_forward_list_count_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns the count of items in the BackForward list
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Retrieves the BackForwardList item count
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_count
* @passcase				When ewk_back_forward_list_count returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_count_p(void)
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

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath1) )
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
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath1);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	int nListCount = 0;
	int nActualCnt = 2;//the compare value is '2' because two times url set is done

	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	nListCount = ewk_back_forward_list_count(pList);
	if ( nListCount != nActualCnt )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_count returned incorrect value; expected count = %d, count received = %d\\n", __LINE__, API_NAMESPACE, nActualCnt, nListCount);
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
//& purpose: Returns the item in regard to index position in the BackForward list
/**
* @testcase 			ITc_ewk_back_forward_list_item_at_index_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns the item in regard to index position in the BackForward list
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Retrieves the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_item_at_index_get
* @passcase				When ewk_back_forward_list_item_at_index_get returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_item_at_index_get_p(void)
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

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath1) )
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
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath1);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Ewk_Back_Forward_List_Item* pListItem = NULL;
	const Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pListItem = ewk_back_forward_list_item_at_index_get(pList, -1);
	if ( pListItem == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_at_index_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	const char* pURL = ewk_back_forward_list_item_url_get(pListItem);
	if ( pURL == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_url_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(pPath, pURL) )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_url_get returned different value; expected value = %s, received value = %s\\n", __LINE__, API_NAMESPACE, pPath, pURL);
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
//& purpose: Copies the BackForward list from back items
/**
* @testcase 			ITc_ewk_back_forward_list_n_back_items_copy_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Copies the BackForward list from back items
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Copies the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_n_back_items_copy
* @passcase				When ewk_back_forward_list_n_back_items_copy returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_n_back_items_copy_p(void)
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

	char pPath2[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE2, pPath2) )
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

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath1) )
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
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath1);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath2) )
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
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath2);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	int nCount = 3; //the value is '3' because two times url set is done
	Eina_List* pCopyBackList = NULL;
	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pCopyBackList = ewk_back_forward_list_n_back_items_copy(pList, nCount - 1);
	if ( pCopyBackList == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_n_back_items_copy returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	int nCopyCount = eina_list_count(pCopyBackList);
	if ( (nCount - 1) != nCopyCount )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_n_back_items_copy output incorrect count value; Expected count = %d, Received count = %d\\n", __LINE__, API_NAMESPACE, nCount - 1, nCopyCount);
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
//& purpose: Copies the BackForward list from forward items
/**
* @testcase 			ITc_ewk_back_forward_list_n_forward_items_copy_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Copies the BackForward list from forward items
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Copies the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_n_forward_items_copy
* @passcase				When ewk_back_forward_list_n_forward_items_copy returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_n_forward_items_copy_p(void)
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

	char pPath2[PATH_LEN] = {0,};
	if ( false == Webkit_EFLAppendToDataPathWithFileFormat(SAMPLE_HTML_FILE2, pPath2) )
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

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath1) )
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
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath1);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	g_bWebkit_EFL_LoadSuccess = false;
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, pPath2) )
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
		FPRINTF("[Line : %d][%s] Unable to set view URL; Load error occurs with file : %s\\n", __LINE__, API_NAMESPACE, pPath2);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( EINA_TRUE != ewk_view_back(objWebkit_EFL_view.webview) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_back returned error on API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	if ( EINA_TRUE != ewk_view_back(objWebkit_EFL_view.webview) )
	{
		FPRINTF("[Line : %d][%s] ewk_view_back returned error on successive ewk_view_back API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	int nCount = 1; //the value is '1' because one copy is done
	Eina_List* pCopyBackList = NULL;

	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pCopyBackList = ewk_back_forward_list_n_forward_items_copy(pList, nCount);
	if ( pCopyBackList == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_n_forward_items_copy returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	int nCopyCount = eina_list_count(pCopyBackList);
	if ( nCount != nCopyCount )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_n_forward_items_copy output incorrect count value; Expected count = %d, Received count = %d\\n", __LINE__, API_NAMESPACE, nCount, nCopyCount);
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
//& purpose: Increases the reference count of the item in the BackForward list
/**
* @testcase 			ITc_ewk_back_forward_list_item_ref_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Increases the reference count of the item in the BackForward list
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Retrieves the BackForwardList item
*						References and dereference the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_current_item_get, ewk_back_forward_list_item_ref, ewk_back_forward_list_item_unref
* @passcase				When ewk_back_forward_list_item_ref returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_item_ref_p(void)
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

	Ewk_Back_Forward_List_Item* pListItem = NULL;
	Ewk_Back_Forward_List_Item* pRefItem = NULL;

	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pListItem = ewk_back_forward_list_current_item_get(pList);
	if ( pListItem == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get current item from ewk_back_forward_list_current_item_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	pRefItem = ewk_back_forward_list_item_ref(pListItem);
	if ( pRefItem == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_ref returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	ewk_back_forward_list_item_unref(pRefItem);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Decreases the reference count of the item in the BackForward list
/**
* @testcase 			ITc_ewk_back_forward_list_item_unref_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Decreases the reference count of the item in the BackForward list
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Retrieves the BackForwardList item\n
*						References and dereference the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_current_item_get, ewk_back_forward_list_item_ref, ewk_back_forward_list_item_unref
* @passcase				When ewk_back_forward_list_item_unref executes properly
* @failcase				If target API didn't execute properly
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_item_unref_p(void)
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

	Ewk_Back_Forward_List_Item* pListItem = NULL;
	Ewk_Back_Forward_List_Item* pRefItem = NULL;
	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pListItem = ewk_back_forward_list_current_item_get(pList);
	if ( pListItem == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get current item from ewk_back_forward_list_current_item_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pRefItem = ewk_back_forward_list_item_ref(pListItem);
	if ( pRefItem == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_ref returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	ewk_back_forward_list_item_unref(pRefItem);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Gets the URL of the BackForward list item
/**
* @testcase 			ITc_ewk_back_forward_list_item_url_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the URL of the BackForward list item
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Retrieves the BackForwardList item\n
*						Get the value from the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_current_item_get, ewk_back_forward_list_item_url_get
* @passcase				When ewk_back_forward_list_item_url_get returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_item_url_get_p(void)
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

	Ewk_Back_Forward_List_Item* pListItem = NULL;
	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pListItem = ewk_back_forward_list_current_item_get(pList);
	if ( pListItem == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get current item from ewk_back_forward_list_current_item_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	const char* pItemValue = ewk_back_forward_list_item_url_get(pListItem);
	if ( pItemValue == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_url_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(pPath, pItemValue) )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_url_get returned incorrect value; Expected value = %s, Returned value = %s\\n", __LINE__, API_NAMESPACE, pPath, pItemValue);
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
//& purpose: Gets the original URL of the BackForward list item
/**
* @testcase 			ITc_ewk_back_forward_list_item_original_url_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the original URL of the BackForward list item
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Retrieves the BackForwardList item\n
*						Get the value from the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_current_item_get, ewk_back_forward_list_item_original_url_get
* @passcase				When ewk_back_forward_list_item_original_url_get returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_item_original_url_get_p(void)
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

	Ewk_Back_Forward_List_Item* pListItem = NULL;
	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pListItem = ewk_back_forward_list_current_item_get(pList);
	if ( pListItem == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get current item from ewk_back_forward_list_current_item_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	const char* pItemValue = ewk_back_forward_list_item_original_url_get(pListItem);
	if ( pItemValue == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_original_url_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(pPath, pItemValue) )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_original_url_get returned incorrect value; Expected value = %s, Returned value = %s\\n", __LINE__, API_NAMESPACE, pPath, pItemValue);
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
//& purpose: Gets the title of the BackForward list item
/**
* @testcase 			ITc_ewk_back_forward_list_item_title_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Gets the title of the BackForward list item
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Retrieves the BackForward List\n
*						Retrieves the BackForwardList item\n
*						Get the value from the BackForwardList item
* @apicovered			ewk_view_url_set, ewk_view_back_forward_list_get, ewk_back_forward_list_current_item_get, ewk_back_forward_list_item_title_get
* @passcase				When ewk_back_forward_list_item_title_get returns valid value
* @failcase				If target API fails or return invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_back_forward_list_item_title_get_p(void)
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

	Ewk_Back_Forward_List_Item* pListItem = NULL;
	Ewk_Back_Forward_List* pList = ewk_view_back_forward_list_get(objWebkit_EFL_view.webview);
	if ( pList == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get Ewk_Back_Forward_List list from ewk_view_back_forward_list_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	pListItem = ewk_back_forward_list_current_item_get(pList);
	if ( pListItem == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get current item from ewk_back_forward_list_current_item_get API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	const char* pItemValue = ewk_back_forward_list_item_title_get(pListItem);
	if ( pItemValue == NULL )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_title_get returned NULL value\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	if ( 0 != strcmp(SAMPLE_HTML_FILE_TITLE, pItemValue) )
	{
		FPRINTF("[Line : %d][%s] ewk_back_forward_list_item_title_get returned incorrect value; Expected value = %s, Returned value = %s\\n", __LINE__, API_NAMESPACE, SAMPLE_HTML_FILE_TITLE, pItemValue);
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
