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
#include "ITs-asp-common.h"

//& set: Asp-advert

/** @addtogroup itc-asp
*  @ingroup itc
*  @{
*/

static asp_session_h g_hAspSession = NULL;
char *g_pszSessionMac = "00:11:22:33:44:55";
int g_nAdvId = 0x01;

/************************/
/** Callback Functions **/
/************************/

static void AspSessionRequestCb(int error_code, asp_advert_service_h adv_service, asp_session_h session, const char *device_name, const char *info,
                         int info_size, bool get_network_config_pin, const char *network_config_pin, void *user_data)
{ 
}

static void AspSessionConfigRequestCb(int error_code, asp_session_h session, bool get_pin, const char *config_pin, void *user_data)
{ 
}

static void AspSessionConnectStatusCb(int error_code, asp_session_h session, asp_connect_status_e status, const char *deferred_resp, int resp_size, void *user_data)
{ 
}

static void AspSessionStatusCb(int error_code, asp_session_h session, asp_session_state_e state, const char *additional_info, void *user_data)
{ 
}

static void AspSessionPortStatusCb(int error_code, asp_session_h session, const char *ip_address, int port, int proto, asp_port_status_e status, void *user_data)
{ 
}

/**
 * @function 		ITs_asp_session_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_asp_session_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int nRet = remove(ERR_LOG);
		PRINT_RESULT_NORETURN(0, nRet, "ITs_asp_session_startup -remove", "Remove failed for ERR_LOG");
	}
	
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	g_bAspInit = true;
	
	bool bAspFeatureSupported = TCTCheckSystemInfoFeatureSupported(ASP_FEATURE, API_NAMESPACE);
	
	int nRet = asp_initialize();
	
	if( false == bAspFeatureSupported) 
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] asp_initialize API call returned mismatch %s error for unsupported network.asp feature\\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] asp_initialize API call correctly returned %s error for unsupported network.asp feature\\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}

	if( nRet != ASP_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] asp_initialize API failed in Precondition, returned error %s \\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
		g_bAspInit = false;
		return;
	}

	nRet = asp_session_create(g_pszSessionMac, g_nAdvId, &g_hAspSession);
	if( nRet != ASP_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] asp_session_create API failed in Precondition, returned error %s \\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
		g_bAspInit = false;
		return;
	}
	if( g_hAspSession == NULL )
	{
		FPRINTF("[Line : %d][%s] asp_session_create API failed in Precondition, session handle created is NULL \\n", __LINE__, API_NAMESPACE);
		g_bAspInit = false;
	}
	return;
}

/**
 * @function 		ITs_asp_session_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_asp_session_cleanup(void)
{
	if(g_bAspInit)
	{
		if( g_hAspSession )
		{
			asp_session_destroy(g_hAspSession);
			g_hAspSession = NULL;
		}
	
		int nRet = asp_deinitialize();
		if( nRet != ASP_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] asp_deinitialize API failed in Postcondition, returned error %s \\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
		}
	}
	return;
}

/** @addtogroup itc-asp-testcases
*  @brief 		Integration testcases for module asp
*  @ingroup 	itc-asp
*  @{
*/

//& purpose: Gets the session MAC for an Application Service Platform session
//& type : auto
/**
* @testcase 			ITc_asp_session_get_mac_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Gets the session MAC for an Application Service Platform session
* @scenario				Gets the session MAC for an Application Service Platform session
* @apicovered			asp_session_get_mac
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_get_mac_p(void)
{
    START_TEST;
	
	char *pszSesionMac = NULL;
	
	int nRet = asp_session_get_mac(g_hAspSession, &pszSesionMac);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_get_mac", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Gets the ID of an Application Service Platform session
//& type : auto
/**
* @testcase 			ITc_asp_session_get_id_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Gets the ID of an Application Service Platform session
* @scenario				Gets the ID of an Application Service Platform session
* @apicovered			asp_session_get_id
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_get_id_p(void)
{
    START_TEST;
	
	unsigned int nSsessionId ;
	
	int nRet = asp_session_get_id(g_hAspSession, &nSsessionId);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_get_id", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Sets and gets the information for an Application Service Platform session
//& type : auto
/**
* @testcase 			ITc_asp_session_set_get_info_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets and gets the information for an Application Service Platform session
* @scenario				Sets and gets the information for an Application Service Platform session
* @apicovered			asp_session_set_info, asp_session_get_info
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_set_get_info_p(void)
{
    START_TEST;
	
	char *setServiceInfo = "Test Service Info";
	char *getServiceInfo = NULL;
	
	int nRet = asp_session_set_info(g_hAspSession, setServiceInfo);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_set_info", AspOutputGetError(nRet));

	nRet = asp_session_get_info(g_hAspSession, &getServiceInfo);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_get_info", AspOutputGetError(nRet));
	
	if( strcmp(setServiceInfo, getServiceInfo) != 0 )
	{
		FPRINTF("[Line : %d][%s] asp_session_get_info API failed as set and get values are mismatched %s/%s \\n", __LINE__, API_NAMESPACE, setServiceInfo, getServiceInfo);
		return 1;
	}
		
	return 0;
}

//& purpose: Sets and gets the Wi-Fi Direct group role in session
//& type : auto
/**
* @testcase 			ITc_asp_session_set_get_p2p_role_scheme_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets and gets the Wi-Fi Direct group role in session
* @scenario				Sets and gets the Wi-Fi Direct group role in session
* @apicovered			asp_session_set_p2p_role_scheme, asp_session_get_p2p_role_scheme
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_set_get_p2p_role_scheme_p(void)
{
    START_TEST;
	int nEnumCount = 0, nIterator = 0;
	asp_advert_p2p_role_scheme_e eGetP2pRoleScheme;
	
	asp_advert_p2p_role_scheme_e eArrP2pRoleScheme[] = { ASP_ADVERT_P2P_ROLE_SCHEME_GO,   	/**< The interface should assume the GO role */
														 ASP_ADVERT_P2P_ROLE_SCHEME_GC };   /**< The interface should assume the GC role */
	
	
	nEnumCount = sizeof(eArrP2pRoleScheme) / sizeof(eArrP2pRoleScheme[0]);

	for(nIterator = 0; nIterator < nEnumCount; nIterator++)
	{
		FPRINTF("[Line : %d][%s] asp_session_set_p2p_role_scheme API called for param = %d \\n", __LINE__, API_NAMESPACE, eArrP2pRoleScheme[nIterator]);
		
		int nRet = asp_session_set_p2p_role_scheme(g_hAspSession, eArrP2pRoleScheme[nIterator]);
		PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_set_p2p_role_scheme", AspOutputGetError(nRet));

		nRet = asp_session_get_p2p_role_scheme(g_hAspSession, &eGetP2pRoleScheme);
		PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_get_p2p_role_scheme", AspOutputGetError(nRet));
		
		if( eArrP2pRoleScheme[nIterator] != eGetP2pRoleScheme)
		{
			FPRINTF("[Line : %d][%s] asp_session_get_p2p_role_scheme API failed as set and get values are mismatched \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	
	return 0;
}

//& purpose: Sets and gets the Preferred WSC Configuration method
//& type : auto
/**
* @testcase 			ITc_asp_session_set_get_p2p_config_method_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets and gets the Preferred WSC Configuration method
* @scenario				Sets and gets the Preferred WSC Configuration method
* @apicovered			asp_session_set_p2p_config_method, asp_session_get_p2p_config_method
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_set_get_p2p_config_method_p(void)
{
    START_TEST;
	int nEnumCount = 0, nIterator = 0;
	asp_wps_type_e eGetWpsType;
	
	asp_wps_type_e eArrWpsType[] = {	ASP_WPS_TYPE_DEFAULT,      	/**< Default WPS type both P2PS and PIN */
										ASP_WPS_TYPE_PIN_BOTH,     	/**< WPS type PIN code both display and keypad*/
										ASP_WPS_TYPE_PIN_DISPLAY,  	/**< WPS type display PIN code only*/
										ASP_WPS_TYPE_PIN_KEYPAD };  /**< WPS type keypad to input the PIN only*/
	
	nEnumCount = sizeof(eArrWpsType) / sizeof(eArrWpsType[0]);

	for(nIterator = 0; nIterator < nEnumCount; nIterator++)
	{
		FPRINTF("[Line : %d][%s] asp_session_set_p2p_config_method API called for param = %d \\n", __LINE__, API_NAMESPACE, eArrWpsType[nIterator]);
		
		int nRet = asp_session_set_p2p_config_method(g_hAspSession, eArrWpsType[nIterator]);
		PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_set_p2p_config_method", AspOutputGetError(nRet));

		nRet = asp_session_get_p2p_config_method(g_hAspSession, &eGetWpsType);
		PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_get_p2p_config_method", AspOutputGetError(nRet));
		
		if( eArrWpsType[nIterator] != eGetWpsType)
		{
			FPRINTF("[Line : %d][%s] asp_session_get_p2p_config_method API failed as set and get values are mismatched \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	
	return 0;
}

//& purpose: Gets the session close status
//& type : auto
/**
* @testcase 			ITc_asp_session_get_close_status_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Gets the session close status
* @scenario				Gets the session close status
* @apicovered			asp_session_get_close_status
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_get_close_status_p(void)
{
    START_TEST;
	
	int nCloseStatus; ;
	
	int nRet = asp_session_get_close_status(g_hAspSession, &nCloseStatus);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_get_close_status", AspOutputGetError(nRet));
	
	FPRINTF("[Line : %d][%s] asp_session close status is = %d\\n", __LINE__, API_NAMESPACE, nCloseStatus);
	
	return 0;
}

//& purpose: Starts to connect the Application Service Platform session
//& type : auto
/**
* @testcase 			ITc_asp_session_connect_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Starts to connect the Application Service Platform session
* @scenario				Starts to connect the Application Service Platform session
* @apicovered			asp_session_connect
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_connect_p(void)
{
    START_TEST;
	
	int nRet = asp_session_connect(g_hAspSession);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_connect", AspOutputGetError(nRet));
	
	return 0;
}

																				
//& purpose: Registers and unregisters the callback called when ASP session connection is requested
//& type : auto
/**
* @testcase 			ITc_asp_session_set_unset_request_cb_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Registers and unregisters the callback called when ASP session connection is requested
* @scenario				Registers and unregisters the callback called when ASP session connection is requested
* @apicovered			asp_session_set_request_cb, asp_session_unset_request_cb
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_set_unset_request_cb_p(void)
{
    START_TEST;
	
	int nRet = asp_session_set_request_cb(AspSessionRequestCb, NULL);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_set_request_cb", AspOutputGetError(nRet));
	
	nRet = asp_session_unset_request_cb();
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_unset_request_cb", AspOutputGetError(nRet));
	
	return 0;
}


//& purpose: Registers and unregisters the callback called when the session configuration is requested
//& type : auto
/**
* @testcase 			ITc_asp_session_set_unset_config_request_cb_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Registers and unregisters the callback called when the session configuration is requested
* @scenario				Registers and unregisters the callback called when the session configuration is requested
* @apicovered			asp_session_set_config_request_cb, asp_session_unset_config_request_cb
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_set_unset_config_request_cb_p(void)
{
    START_TEST;
	
	int nRet = asp_session_set_config_request_cb(AspSessionConfigRequestCb, NULL);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_set_config_request_cb", AspOutputGetError(nRet));
	
	nRet = asp_session_unset_config_request_cb();
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_unset_config_request_cb", AspOutputGetError(nRet));
	
	return 0;
}


//& purpose: Registers and unregisters the callback called when the state of the session connection is changed
//& type : auto
/**
* @testcase 			ITc_asp_session_set_unset_connect_status_cb_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Registers and unregisters the callback called when the state of the session connection is changed
* @scenario				Registers and unregisters the callback called when the state of the session connection is changed
* @apicovered			asp_session_set_connect_status_cb, asp_session_unset_connect_status_cb
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_set_unset_connect_status_cb_p(void)
{
    START_TEST;
	
	int nRet = asp_session_set_connect_status_cb(AspSessionConnectStatusCb, NULL);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_set_connect_status_cb", AspOutputGetError(nRet));
	
	nRet = asp_session_unset_connect_status_cb();
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_unset_connect_status_cb", AspOutputGetError(nRet));
	
	return 0;
}


//& purpose: Registers and unregisters the callback called when the state of the session is changed
//& type : auto
/**
* @testcase 			ITc_asp_session_set_unset_status_cb_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Registers and unregisters the callback called when the state of the session is changed
* @scenario				Registers and unregisters the callback called when the state of the session is changed
* @apicovered			asp_session_set_status_cb, asp_session_unset_status_cb
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_set_unset_status_cb_p(void)
{
    START_TEST;
	
	int nRet = asp_session_set_status_cb(AspSessionStatusCb, NULL);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_set_status_cb", AspOutputGetError(nRet));
	
	nRet = asp_session_unset_status_cb();
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_unset_status_cb", AspOutputGetError(nRet));
	
	return 0;
}


//& purpose: Registers and unregisters the callback called when the state of the port is changed
//& type : auto
/**
* @testcase 			ITc_asp_session_set_unset_port_status_cb_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Registers and unregisters the callback called when the state of the port is changed
* @scenario				Registers and unregisters the callback called when the state of the port is changed
* @apicovered			asp_session_set_port_status_cb, asp_session_unset_port_status_cb
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create asp session handle
* @postcondition		Call API asp_deinitialize and destroy asp session handle
*/
int ITc_asp_session_set_unset_port_status_cb_p(void)
{
    START_TEST;
	
	int nRet = asp_session_set_port_status_cb(AspSessionPortStatusCb, NULL);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_set_port_status_cb", AspOutputGetError(nRet));
	
	nRet = asp_session_unset_port_status_cb();
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_session_unset_port_status_cb", AspOutputGetError(nRet));
	
	return 0;
}

/** @} */
/** @} */