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
* @function			Webkit_EFL_GetAcceptPolicyCallback
* @description		Accept policy Cookie Manager callback
* @parameter		Ewk_Cookie_Accept_Policy policy, void* event_info
* @return			none
*/
void Webkit_EFL_GetAcceptPolicyCallback(Ewk_Cookie_Accept_Policy policy, void* event_info)
{
	Ewk_Cookie_Accept_Policy* pRetPolicy = (Ewk_Cookie_Accept_Policy*)event_info;
	*pRetPolicy = policy;
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		ITs_webkit_efl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_cookies_startup(void)
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
void ITs_webkit_efl_cookies_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type: auto
//& purpose: Set policy\n as the cookie acceptance policy for manager
/**
* @testcase 			ITc_ewk_cookie_manager_accept_policy_set_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Set policy\n as the cookie acceptance policy for manager
* @scenario				Create Webkit View\n
*						Set policy\n\n
*						Check policy in callback\n
*						compare the value\n
*						Destroy Webkit View
* @apicovered			ewk_cookie_manager_accept_policy_set
* @passcase				When ewk_cookie_manager_accept_policy_set behaves properly and set the value
* @failcase				If target API fails unable to set value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_cookie_manager_accept_policy_set_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Cookie_Manager* pCookieManager = ewk_context_cookie_manager_get(ewk_view_context_get(objWebkit_EFL_view.webview));
	if ( pCookieManager == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get cookie manager from ewk_context_cookie_manager_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	//Target API
	ewk_cookie_manager_accept_policy_set(pCookieManager, EWK_COOKIE_ACCEPT_POLICY_ALWAYS);
	Ewk_Cookie_Accept_Policy policy = EWK_COOKIE_ACCEPT_POLICY_NEVER;
	ewk_cookie_manager_accept_policy_async_get(pCookieManager, Webkit_EFL_GetAcceptPolicyCallback, &policy);
	Webkit_EFL_main_loop_begin();

	if ( policy != EWK_COOKIE_ACCEPT_POLICY_ALWAYS )
	{
		FPRINTF("[Line : %d][%s] ewk_cookie_manager_accept_policy_set return incorrect policy; expected = %d, return = %d\\n", __LINE__, API_NAMESPACE, EWK_COOKIE_ACCEPT_POLICY_ALWAYS, policy);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Get policy for the cookie acceptance policy manager
/**
* @testcase 			ITc_ewk_cookie_manager_accept_policy_async_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Get policy for the cookie acceptance policy manager
* @scenario				Create Webkit View\n
*						Set policy\n
*						Check policy in callback\n
*						compare the value\n
*						Destroy Webkit View
* @apicovered			ewk_cookie_manager_accept_policy_async_get
* @passcase				When ewk_cookie_manager_accept_policy_async_get behaves properly and get the value
* @failcase				If target API fails unable to get value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_cookie_manager_accept_policy_async_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	Ewk_Cookie_Manager* pCookieManager = ewk_context_cookie_manager_get(ewk_view_context_get(objWebkit_EFL_view.webview));
	if ( pCookieManager == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get cookie manager from ewk_context_cookie_manager_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	ewk_cookie_manager_accept_policy_set(pCookieManager, EWK_COOKIE_ACCEPT_POLICY_ALWAYS);
	Ewk_Cookie_Accept_Policy policy = EWK_COOKIE_ACCEPT_POLICY_NEVER;

	//Target API
	ewk_cookie_manager_accept_policy_async_get(pCookieManager, Webkit_EFL_GetAcceptPolicyCallback, &policy);
	Webkit_EFL_main_loop_begin();
	if ( policy != EWK_COOKIE_ACCEPT_POLICY_ALWAYS )
	{
		FPRINTF("[Line : %d][%s] ewk_cookie_manager_accept_policy_async_get return incorrect policy; expected = %d, return = %d\\n", __LINE__, API_NAMESPACE, EWK_COOKIE_ACCEPT_POLICY_ALWAYS, policy);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	Webkit_EFLDestroyWebKitView();
	return 0;
}

//& type: auto
//& purpose: Deletes all the cookies of a manager
/**
* @testcase 			ITc_ewk_cookie_manager_cookies_clear_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Deletes all the cookies of a manager
* @scenario				Create Webkit View\n
*						Set URL\n
*						Check Set URL result in callback\n
*						Clear the cookies\n
*						Destroy Webkit View
* @apicovered			ewk_cookie_manager_cookies_clear
* @passcase				When ewk_cookie_manager_cookies_clear behaves properly
* @failcase				If target API didn't behave properly
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_cookie_manager_cookies_clear_p(void)
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

	Ewk_Cookie_Manager* pCookieManager = ewk_context_cookie_manager_get(ewk_view_context_get(objWebkit_EFL_view.webview));
	if ( pCookieManager == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get cookie manager from ewk_context_cookie_manager_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
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
	ewk_cookie_manager_cookies_clear(pCookieManager);

	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_LoadError);
	Webkit_EFLDestroyWebKitView();
	return 0;
}
//& type: auto
//& purpose: Checks whether cookie manager allows cookies for file scheme URLs 
/**
* @testcase 			ITc_ewk_cookie_manager_file_scheme_cookies_allow_set_get_p
* @since_tizen			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description	 		Sets and gets whether cookie manager allows cookies for file scheme URLs 
* @scenario				Sets and gets whether cookie manager allows cookies for file scheme URLs 
* @apicovered			ewk_cookie_manager_file_scheme_cookies_allow_set, ewk_cookie_manager_file_scheme_cookies_allow_get
* @passcase				When ewk_cookie_manager_file_scheme_cookies_allow_set, ewk_cookie_manager_file_scheme_cookies_allow_get behave properly
* @failcase				If target API didn't behave properly
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_cookie_manager_file_scheme_cookies_allow_set_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	Ewk_Cookie_Manager* pCookieManager = ewk_context_cookie_manager_get(ewk_view_context_get(objWebkit_EFL_view.webview));
	if ( pCookieManager == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get cookie manager from ewk_context_cookie_manager_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	ewk_cookie_manager_file_scheme_cookies_allow_set(pCookieManager, EINA_TRUE);
	EventLoopWait(3.0);
	
	Eina_Bool result = ewk_cookie_manager_file_scheme_cookies_allow_get(pCookieManager);
	if ( result == EINA_FALSE )
	{
		FPRINTF("[Line : %d][%s] ewk_cookie_manager_file_scheme_cookies_allow_get failed\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	Webkit_EFLDestroyWebKitView();
	return 0;
}
//& type: auto
//& purpose: Checks ITc_ewk_cookie_manager_persistent_storage_set_p
/**
* @testcase 			ITc_ewk_cookie_manager_persistent_storage_set_p
* @since_tizen			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description	 		Sets the path where non-session cookies are stored persistently
* @scenario				Sets the path where non-session cookies are stored persistently
* @apicovered			ewk_cookie_manager_persistent_storage_set
* @passcase				When ewk_cookie_manager_persistent_storage_set api gets pass
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_cookie_manager_persistent_storage_set_p(void)
{
	START_TEST;
	
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}
	Ewk_Cookie_Manager* pCookieManager = ewk_context_cookie_manager_get(ewk_view_context_get(objWebkit_EFL_view.webview));
	if ( pCookieManager == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to get cookie manager from ewk_context_cookie_manager_get API call\\n", __LINE__, API_NAMESPACE);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}
	
	int CookiePersistentStorage[] = {
		EWK_COOKIE_PERSISTENT_STORAGE_TEXT,		/**< cookies are stored in text file */
		EWK_COOKIE_PERSISTENT_STORAGE_SQLITE,		/**< cookies are stored in SQLite file */
	};
	int nCookieStorageCount = sizeof(CookiePersistentStorage) / sizeof(CookiePersistentStorage[0]);
	int nCookieStorage = 0;
	for ( nCookieStorage = 0;nCookieStorage < nCookieStorageCount;nCookieStorage++ )
	{
		ewk_cookie_manager_persistent_storage_set(pCookieManager, COOKIE_STORAGE_PATH, CookiePersistentStorage[nCookieStorage]);
	}
	
	Webkit_EFLDestroyWebKitView();
	
	return 0;
}
/** @} */
/** @} */
