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


int g_nFail_ewk_policy_decision_cookie_get = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_url_get = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_scheme_get = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_host_get = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_http_method_get = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_use = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_ignore = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_type_get = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_navigation_type_get = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_response_mime_get = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_response_headers_get = INITIALIZE_FAIL;
int g_nFail_ewk_policy_decision_response_status_code_get = INITIALIZE_FAIL;

/**
* @function			Webkit_EFL_PolicyDecision_Callback_LoadFinished
* @description		Accept policy Cookie Manager callback for Loading Finished
* @parameter		void *data, Evas_Object *webview, void *arg
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_LoadFinished(void *data, Evas_Object *webview, void *arg)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback_LoadFinished success\\n", __LINE__, API_NAMESPACE);
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_LoadError
* @description		Accept policy Cookie Manager callback for Loading Error
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_LoadError(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback_LoadError occurs\\n", __LINE__, API_NAMESPACE);
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_cookie_get
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_cookie_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_cookie_get invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_cookie_get = 0;
	if ( pPolicyDecision )
	{
		const char* pValue = NULL;
		//Target API
		pValue = ewk_policy_decision_cookie_get(pPolicyDecision);
		if ( pValue == NULL )
		{
			g_nFail_ewk_policy_decision_cookie_get++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_cookie_get returned NULL value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_cookie_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_url_get
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_url_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_url_get invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_url_get = 0;
	if ( pPolicyDecision )
	{
		const char* pValue = NULL;
		//Target API
		pValue = ewk_policy_decision_url_get(pPolicyDecision);
		if ( pValue == NULL )
		{
			g_nFail_ewk_policy_decision_url_get++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_url_get returned NULL value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_url_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_scheme_get
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_scheme_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_scheme_get invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_scheme_get = 0;
	if ( pPolicyDecision )
	{
		const char* pValue = NULL;
		//Target API
		pValue = ewk_policy_decision_scheme_get(pPolicyDecision);
		if ( pValue == NULL )
		{
			g_nFail_ewk_policy_decision_scheme_get++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_scheme_get returned NULL value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_scheme_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_host_get
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_host_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_host_get invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_host_get = 0;
	if ( pPolicyDecision )
	{
		const char* pValue = NULL;

		//Target API
		pValue = ewk_policy_decision_host_get(pPolicyDecision);
		if ( pValue == NULL )
		{
			g_nFail_ewk_policy_decision_host_get++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_host_get returned NULL value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_host_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_http_method_get
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_http_method_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_http_method_get invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_http_method_get = 0;
	if ( pPolicyDecision )
	{
		const char* pValue = NULL;

		//Target API
		pValue = ewk_policy_decision_http_method_get(pPolicyDecision);
		if ( pValue == NULL )
		{
			g_nFail_ewk_policy_decision_http_method_get++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_http_method_get returned NULL value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_http_method_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_use
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_use(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_use invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_use = 0;
	if ( pPolicyDecision )
	{
		Eina_Bool bResult = EINA_FALSE;
		//Target API
		bResult = ewk_policy_decision_use(pPolicyDecision);
		if ( EINA_TRUE != bResult )
		{
			g_nFail_ewk_policy_decision_use++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_use returned false error value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_use = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_ignore
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_ignore(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_ignore invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_ignore = 0;
	if ( pPolicyDecision )
	{
		Eina_Bool bResult = EINA_FALSE;
		//Target API
		bResult = ewk_policy_decision_ignore(pPolicyDecision);
		if ( EINA_TRUE != bResult )
		{
			g_nFail_ewk_policy_decision_ignore++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_ignore returned false error value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_ignore = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_type_get
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_type_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_type_get invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_type_get = 0;
	if ( pPolicyDecision )
	{
		Ewk_Policy_Decision_Type eDecisionType = EWK_POLICY_DECISION_USE;
		//Target API
		eDecisionType = ewk_policy_decision_type_get(pPolicyDecision);
		if ( (eDecisionType != EWK_POLICY_DECISION_USE) && (eDecisionType != EWK_POLICY_DECISION_DOWNLOAD) && (eDecisionType != EWK_POLICY_DECISION_IGNORE) )
		{
			g_nFail_ewk_policy_decision_type_get++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_type_get returned wrong value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_type_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_navigation_type_get
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_navigation_type_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_navigation_type_get invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_navigation_type_get = 0;
	if ( pPolicyDecision )
	{
		Ewk_Policy_Navigation_Type eDecisionType = EWK_POLICY_NAVIGATION_TYPE_LINK_CLICKED;
		//Target API
		eDecisionType = ewk_policy_decision_navigation_type_get(pPolicyDecision);
		if ( (eDecisionType != EWK_POLICY_NAVIGATION_TYPE_LINK_CLICKED) && (eDecisionType != EWK_POLICY_NAVIGATION_TYPE_FORM_SUBMITTED) && \
			(eDecisionType != EWK_POLICY_NAVIGATION_TYPE_BACK_FORWARD) && (eDecisionType != EWK_POLICY_NAVIGATION_TYPE_RELOAD) && \
			(eDecisionType != EWK_POLICY_NAVIGATION_TYPE_FORM_RESUBMITTED) && (eDecisionType != EWK_POLICY_NAVIGATION_TYPE_OTHER) )
		{
			g_nFail_ewk_policy_decision_navigation_type_get++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_navigation_type_get returned wrong value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_navigation_type_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_response_mime_get
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_response_mime_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_response_mime_get invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_response_mime_get = 0;
	if ( pPolicyDecision )
	{
		const char* pValue = NULL;

		//Target API
		pValue = ewk_policy_decision_response_mime_get(pPolicyDecision);
		if ( pValue == NULL )
		{
			g_nFail_ewk_policy_decision_response_mime_get++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_response_mime_get returned NULL value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_response_mime_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_response_headers_get
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_response_headers_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_response_headers_get invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_response_headers_get = 0;
	if ( pPolicyDecision )
	{
		const Eina_Hash* pValue = NULL;
		//Target API
		pValue = ewk_policy_decision_response_headers_get(pPolicyDecision);
		if ( pValue == NULL )
		{
			g_nFail_ewk_policy_decision_response_headers_get++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_response_headers_get returned NULL value\\n", __LINE__, API_NAMESPACE);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_response_headers_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function			Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_response_status_code_get
* @description		Policy Decision callback
* @parameter		void* data, Evas_Object* webview, void* event_info
* @return			none
*/
void Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_response_status_code_get(void* data, Evas_Object* webview, void* event_info)
{
	FPRINTF("[Line : %d][%s] Webkit_EFL_PolicyDecision_Callback for ewk_policy_decision_response_status_code_get invoked\\n", __LINE__, API_NAMESPACE);
	Ewk_Policy_Decision* pPolicyDecision = (Ewk_Policy_Decision*)event_info;
	g_nFail_ewk_policy_decision_response_status_code_get = 0;
	if ( pPolicyDecision )
	{
		int nValue = 0;
		//Target API
		nValue = ewk_policy_decision_response_status_code_get(pPolicyDecision);
		if ( RESPONSE_STATUS_CODE_SUCCESS != nValue )
		{
			g_nFail_ewk_policy_decision_response_status_code_get++;
			FPRINTF("[Line : %d][%s] ewk_policy_decision_response_status_code_get returned incorrect status value; expected value = %d, returned value = %d\\n", __LINE__, API_NAMESPACE, RESPONSE_STATUS_CODE_SUCCESS, nValue);
			Webkit_EFL_main_loop_quit();
			return;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to get Policy Decision\\n", __LINE__, API_NAMESPACE);
		g_nFail_ewk_policy_decision_response_status_code_get = INITIALIZE_FAIL;
	}
	Webkit_EFL_main_loop_quit();
}

/**
* @function 		ITs_webkit_efl_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_webkit_efl_desicion_startup(void)
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
void ITs_webkit_efl_desicion_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Webkit2_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type: auto
//& purpose: Returns cookie from policy decision object
/**
* @testcase 			ITc_ewk_policy_decision_cookie_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns cookie from policy decision object
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_cookie_get in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_cookie_get
* @passcase				When ewk_policy_decision_cookie_get return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_cookie_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,navigation,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_cookie_get, NULL);
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, POLICY_DECISION_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_cookie_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns URL from policy decision object
/**
* @testcase 			ITc_ewk_policy_decision_url_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns URL from policy decision object
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_url_get in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_url_get
* @passcase				When ewk_policy_decision_url_get return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_url_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,navigation,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_url_get, NULL);
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, POLICY_DECISION_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_url_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns Scheme from policy decision object
/**
* @testcase 			ITc_ewk_policy_decision_scheme_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns Scheme from policy decision object
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_scheme_get in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_scheme_get
* @passcase				When ewk_policy_decision_scheme_get return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_scheme_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,navigation,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_scheme_get, NULL);
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, POLICY_DECISION_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_scheme_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns Host from policy decision object
/**
* @testcase 			ITc_ewk_policy_decision_host_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns Host from policy decision object
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_host_get in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_host_get
* @passcase				When ewk_policy_decision_host_get return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_host_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,navigation,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_host_get, NULL);
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, POLICY_DECISION_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_host_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns HTTP Method from policy decision object
/**
* @testcase 			ITc_ewk_policy_decision_http_method_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns HTTP Method from policy decision object
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_http_method_get in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_http_method_get
* @passcase				When ewk_policy_decision_http_method_get return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_http_method_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,navigation,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_http_method_get, NULL);
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, POLICY_DECISION_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_http_method_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Accepts the action which triggers decision
/**
* @testcase 			ITc_ewk_policy_decision_use_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Accepts the action which triggers decision
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_use in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_use
* @passcase				When ewk_policy_decision_use return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_use_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,navigation,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_use, NULL);
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, POLICY_DECISION_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_use > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Ignores the action which triggers decision
/**
* @testcase 			ITc_ewk_policy_decision_ignore_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Ignores the action which triggers decision
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_ignore in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_ignore
* @passcase				When ewk_policy_decision_ignore return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_ignore_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,navigation,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_ignore, NULL);
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, POLICY_DECISION_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_ignore > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns a policy type from Policy Decision object
/**
* @testcase 			ITc_ewk_policy_decision_type_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns a policy type from Policy Decision object
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_type_get in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_type_get
* @passcase				When ewk_policy_decision_type_get return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_type_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,navigation,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_type_get, NULL);
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, POLICY_DECISION_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_type_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns a navigation type from Policy Decision object
/**
* @testcase 			ITc_ewk_policy_decision_navigation_type_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns a navigation type from Policy Decision object
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_navigation_type_get in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_navigation_type_get
* @passcase				When ewk_policy_decision_navigation_type_get return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_navigation_type_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,navigation,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_navigation_type_get, NULL);
	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, POLICY_DECISION_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,navigation,decide", NULL);
	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_navigation_type_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns mime type for response data from policy decision object
/**
* @testcase 			ITc_ewk_policy_decision_response_mime_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns mime type for response data from policy decision object
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_response_mime_get in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_response_mime_get
* @passcase				When ewk_policy_decision_response_mime_get return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_response_mime_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,response,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_response_mime_get, NULL);

	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, LAUNCH_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,response,decide", NULL);

		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,response,decide", NULL);

	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_response_mime_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns HTTP headers for response data from policy decision object
/**
* @testcase 			ITc_ewk_policy_decision_response_headers_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns HTTP headers for response data from policy decision object
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_response_headers_get in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_response_headers_get
* @passcase				When ewk_policy_decision_response_headers_get return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_response_headers_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,response,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_response_headers_get, NULL);

	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, LAUNCH_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,response,decide", NULL);

		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,response,decide", NULL);

	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_response_headers_get > 0 )
	{
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns HTTP status code for response data from policy decision object
/**
* @testcase 			ITc_ewk_policy_decision_response_status_code_get_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description	 		Returns HTTP status code for response data from policy decision object
* @scenario				Create Webkit View\n
*						Call ewk_policy_decision_response_status_code_get in callback\n
*						Destroy webkit view
* @apicovered			ewk_policy_decision_response_status_code_get
* @passcase				When ewk_policy_decision_response_status_code_get return correct value
* @failcase				If target API didn't return correct value
* @precondition			NA
* @postcondition		NA
*/
int ITc_ewk_policy_decision_response_status_code_get_p(void)
{
	START_TEST;
	if ( false == Webkit_EFLCreateWebKitView() )
	{
		return 1;
	}

	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError, NULL);
	evas_object_smart_callback_add(objWebkit_EFL_view.webview,"policy,response,decide", Webkit_EFL_PolicyDecision_Callback_GetPolicy_ewk_policy_decision_response_status_code_get, NULL);

	if ( EINA_TRUE != ewk_view_url_set(objWebkit_EFL_view.webview, LAUNCH_URL) )
	{
		FPRINTF("[Line : %d][%s] Unable to set Policy Decision URL through ewk_view_url_set API call\\n", __LINE__, API_NAMESPACE);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
		evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,response,decide", NULL);
		Webkit_EFLDestroyWebKitView();
		return 1;
	}

	Webkit_EFL_main_loop_begin();
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,finished", Webkit_EFL_PolicyDecision_Callback_LoadFinished);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "load,error", Webkit_EFL_PolicyDecision_Callback_LoadError);
	evas_object_smart_callback_del(objWebkit_EFL_view.webview, "policy,response,decide", NULL);

	Webkit_EFLDestroyWebKitView();
	if ( g_nFail_ewk_policy_decision_response_status_code_get > 0 )
	{
		return 1;
	}
	return 0;
}
/** @} */
/** @} */
