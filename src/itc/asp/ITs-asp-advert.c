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

static asp_advert_service_h g_hAdvertSvc = NULL;

/************************/
/** Callback Functions **/
/************************/

static void AspAdvertStatusChangedCb(asp_advert_service_h adv_service, asp_service_status_e status, asp_advert_status_reason_e reason, void *user_data)
{
}


/**
 * @function 		ITs_asp_advert_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_asp_advert_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int nRet = remove(ERR_LOG);
		PRINT_RESULT_NORETURN(0, nRet, "ITs_asp_advert_startup -remove", "Remove failed for ERR_LOG");
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

	char *pszServiceName = "TestAdvertSvc";
	nRet = asp_advert_create(pszServiceName, &g_hAdvertSvc);
	if( nRet != ASP_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] asp_advert_create API failed in Precondition, returned error %s \\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
		g_bAspInit = false;
		return;
	}
	if( g_hAdvertSvc == NULL )
	{
		FPRINTF("[Line : %d][%s] asp_advert_create API failed in Precondition, service handle created is NULL \\n", __LINE__, API_NAMESPACE);
		g_bAspInit = false;
	}
	return;
}

/**
 * @function 		ITs_asp_advert_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_asp_advert_cleanup(void)
{
	if(g_bAspInit)
	{
		if( g_hAdvertSvc )
		{
			asp_advert_destroy(g_hAdvertSvc);
			g_hAdvertSvc = NULL;
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

//& purpose: Sets the service type for a service to be advertised
//& type : auto
/**
* @testcase 			ITc_asp_advert_set_service_type_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the service type for a service to be advertised
* @scenario				Creates and destroyes the description of a service to be advertised
* @apicovered			asp_advert_set_service_type
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_set_service_type_p(void)
{
    START_TEST;
	
	char *pszServiceType = "TestService";
	
	int nRet = asp_advert_set_service_type(g_hAdvertSvc, pszServiceType);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_set_service_type", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Sets auto accept for a service to be advertised
//& type : auto
/**
* @testcase 			ITc_asp_advert_set_auto_accept_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets auto accept for a service to be advertised.
* @scenario				Sets auto accept for a service to be advertised
* @apicovered			asp_advert_set_auto_accept
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_set_auto_accept_p(void)
{
    START_TEST;
	
	bool bAutoAccept = true;
	
	int nRet = asp_advert_set_auto_accept(g_hAdvertSvc, bAutoAccept);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_set_auto_accept", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Adds, gets, and removes the information for a service to be advertised
//& type : auto
/**
* @testcase 			ITc_asp_advert_add_get_remove_info_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Adds and gets the information for a service to be advertised
* @scenario				Adds and gets the information for a service to be advertised
* @apicovered			asp_advert_add_info, asp_advert_get_info, asp_advert_remove_info
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_add_get_remove_info_p(void)
{
    START_TEST;
	
	char *pszKey = "<hdcp,mode>";
	char *pszSetValue = "<2,dual>";
	char *pszGetValue = NULL;
	int nLength;

	int nRet = asp_advert_add_info(g_hAdvertSvc, pszKey, pszSetValue);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_add_info", AspOutputGetError(nRet));

	nRet = asp_advert_get_info(g_hAdvertSvc, pszKey, &nLength, &pszGetValue);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_get_info", AspOutputGetError(nRet));
	
	if( strcmp(pszSetValue, pszGetValue) != 0)
	{
		FPRINTF("[Line : %d][%s] asp_advert_get_info API failed as set and get values are mismatched \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = asp_advert_remove_info(g_hAdvertSvc, pszKey);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_remove_info", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Sets the status for a service to be advertised
//& type : auto
/**
* @testcase 			ITc_asp_advert_set_status_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the status for a service to be advertised
* @scenario				Sets the status for a service to be advertised
* @apicovered			asp_advert_set_status
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_set_status_p(void)
{
    START_TEST;
	
	unsigned char chStatus = 1;
	
	int nRet = asp_advert_set_status(g_hAdvertSvc, chStatus);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_set_status", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Sets the discovery mechanism for a service to be advertised
//& type : auto
/**
* @testcase 			ITc_asp_advert_set_discovery_tech_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the discovery mechanism for a service to be advertised
* @scenario				Sets the discovery mechanism for a service to be advertised
* @apicovered			asp_advert_set_discovery_tech
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_set_discovery_tech_p(void)
{
    START_TEST;
	
	int nEnumCount = 0, nIterator = 0;
	asp_discovery_tech_e eArrDiscoveryTech[] = { ASP_DISCOVERY_TECH_P2P,      /**< Use Wi-Fi P2P for discovery mechanism */
												 ASP_DISCOVERY_TECH_BLE,      /**< Use BLE for discovery mechanism */
												 ASP_DISCOVERY_TECH_NFC,      /**< Use NFC for discovery mechanism */
												 ASP_DISCOVERY_TECH_INFRA ,   /**< Use Wi-Fi Infrastructured for discovery mechanism */
												 ASP_DISCOVERY_TECH_NAN   };  /**< Use Wi-Fi NAN for discovery mechanism */
	
	
	nEnumCount = sizeof(eArrDiscoveryTech) / sizeof(eArrDiscoveryTech[0]);

	for(nIterator = 0; nIterator < nEnumCount; nIterator++)
	{
		int nRet = asp_advert_set_discovery_tech(g_hAdvertSvc, eArrDiscoveryTech[nIterator]);
		PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_set_discovery_tech", AspOutputGetError(nRet));
	}
	
	return 0;
}

//& purpose: Sets the preferred connection for a service to be advertised
//& type : auto
/**
* @testcase 			ITc_asp_advert_set_preferred_connection_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the preferred connection for a service to be advertised
* @scenario				Sets the preferred connection for a service to be advertised
* @apicovered			asp_advert_set_preferred_connection
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_set_preferred_connection_p(void)
{
    START_TEST;
	
	int nPreferredConnection = 1;
	
	int nRet = asp_advert_set_preferred_connection(g_hAdvertSvc, nPreferredConnection);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_set_preferred_connection", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Sets and gets the Wi-Fi P2P role for a service to be advertised
//& type : auto
/**
* @testcase 			ITc_asp_advert_set_get_p2p_role_scheme_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets and gets the Wi-Fi P2P role for a service to be advertised
* @scenario				Sets and gets the Wi-Fi P2P role for a service to be advertised
* @apicovered			asp_advert_set_p2p_role_scheme, asp_advert_get_p2p_role_scheme
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_set_get_p2p_role_scheme_p(void)
{
    START_TEST;
	int nEnumCount = 0, nIterator = 0;
	asp_advert_p2p_role_scheme_e eGetP2pRoleScheme;
	
	asp_advert_p2p_role_scheme_e eArrP2pRoleScheme[] = { ASP_ADVERT_P2P_ROLE_SCHEME_ANY,  	/**< All roles are acceptable */
														 ASP_ADVERT_P2P_ROLE_SCHEME_GO,   	/**< The interface should assume the GO role */
														 ASP_ADVERT_P2P_ROLE_SCHEME_GC };   /**< The interface should assume the GC role */
	
	
	nEnumCount = sizeof(eArrP2pRoleScheme) / sizeof(eArrP2pRoleScheme[0]);

	for(nIterator = 0; nIterator < nEnumCount; nIterator++)
	{
		int nRet = asp_advert_set_p2p_role_scheme(g_hAdvertSvc, eArrP2pRoleScheme[nIterator]);
		PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_set_p2p_role_scheme", AspOutputGetError(nRet));

		nRet = asp_advert_get_p2p_role_scheme(g_hAdvertSvc, &eGetP2pRoleScheme);
		PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_get_p2p_role_scheme", AspOutputGetError(nRet));
		
		if( eArrP2pRoleScheme[nIterator] != eGetP2pRoleScheme)
		{
			FPRINTF("[Line : %d][%s] asp_advert_get_p2p_role_scheme API failed as set and get values are mismatched \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	
	return 0;
}

//& purpose: Sets and gets the P2P configuration method for a service to be advertised
//& type : auto
/**
* @testcase 			ITc_asp_advert_set_get_p2p_config_method_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets and gets the P2P configuration method for a service to be advertised
* @scenario				Sets and gets the P2P configuration method for a service to be advertised
* @apicovered			asp_advert_set_p2p_config_method, asp_advert_get_p2p_config_method
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_set_get_p2p_config_method_p(void)
{
    START_TEST;
	int nEnumCount = 0, nIterator = 0;
	asp_wps_type_e eGetWpsType;
	
	asp_wps_type_e eArrWpsType[] = {	ASP_WPS_TYPE_NONE,         	/**< No WPS type */
										ASP_WPS_TYPE_DEFAULT,      	/**< Default WPS type both P2PS and PIN */
										ASP_WPS_TYPE_PIN_BOTH,     	/**< WPS type PIN code both display and keypad*/
										ASP_WPS_TYPE_PIN_DISPLAY,  	/**< WPS type display PIN code only*/
										ASP_WPS_TYPE_PIN_KEYPAD };  /**< WPS type keypad to input the PIN only*/
	
	nEnumCount = sizeof(eArrWpsType) / sizeof(eArrWpsType[0]);

	for(nIterator = 0; nIterator < nEnumCount; nIterator++)
	{
		int nRet = asp_advert_set_p2p_config_method(g_hAdvertSvc, eArrWpsType[nIterator]);
		PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_set_p2p_config_method", AspOutputGetError(nRet));

		nRet = asp_advert_get_p2p_config_method(g_hAdvertSvc, &eGetWpsType);
		PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_get_p2p_config_method", AspOutputGetError(nRet));
		
		if( eArrWpsType[nIterator] != eGetWpsType)
		{
			FPRINTF("[Line : %d][%s] asp_advert_get_p2p_config_method API failed as set and get values are mismatched \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	
	return 0;
}

//& purpose: Sets the service response for an advertised service
//& type : auto
/**
* @testcase 			ITc_asp_advert_set_p2p_response_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the service response for an advertised service
* @scenario				Sets the service response for an advertised service
* @apicovered			asp_advert_set_p2p_response
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_set_p2p_response_p(void)
{
    START_TEST;
	
	char *pszServiceResp = "TestAdvertSvc";
	int nLen = strlen(pszServiceResp);
	
	int nRet = asp_advert_set_p2p_response(g_hAdvertSvc, pszServiceResp, nLen);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_set_p2p_response", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Starts and Stops a service advertisement
//& type : auto
/**
* @testcase 			ITc_asp_advert_start_stop_advertising_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Starts and Stops a service advertisement
* @scenario				Starts and Stops a service advertisement
* @apicovered			asp_advert_start_advertising, asp_advert_stop_advertising
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_start_stop_advertising_p(void)
{
    START_TEST;
	int nRet = asp_advert_start_advertising(g_hAdvertSvc);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_start_advertising", AspOutputGetError(nRet));

	nRet = asp_advert_stop_advertising(g_hAdvertSvc);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_stop_advertising", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Changes the advertising service status
//& type : auto
/**
* @testcase 			ITc_asp_advert_change_service_status_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Changes the advertising service status
* @scenario				Changes the advertising service status
* @apicovered			asp_advert_start_advertising, asp_advert_change_service_status, asp_advert_stop_advertising
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle and call asp_advert_start_advertising
* @postcondition		Call API asp_advert_stop_advertising, asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_change_service_status_p(void)
{
    START_TEST;
	unsigned char chStatus = 1;
	
	int nRet = asp_advert_start_advertising(g_hAdvertSvc);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_start_advertising", AspOutputGetError(nRet));

	nRet = asp_advert_change_service_status(g_hAdvertSvc, chStatus);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_change_service_status", AspOutputGetError(nRet));
	
	nRet = asp_advert_stop_advertising(g_hAdvertSvc);
	PRINT_RESULT_NORETURN(ASP_ERROR_NONE, nRet, "asp_advert_stop_advertising", AspOutputGetError(nRet));
	
	return 0;
}												
											  
//& purpose: Registers and unregisters the callback function that will invoked when the status of an advertisement to a service is changed
//& type : auto
/**
* @testcase 			ITc_asp_advert_set_unset_status_changed_cb_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Registers and unregisters the callback function that will invoked when the status of an advertisement to a service is changed
* @scenario				Registers and unregisters the callback function that will invoked when the status of an advertisement to a service is changed
* @apicovered			asp_advert_set_status_changed_cb, asp_advert_unset_status_changed_cb
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create adervertize service handle
* @postcondition		Call API asp_deinitialize and destroy adervertize service handle
*/
int ITc_asp_advert_set_unset_status_changed_cb_p(void)
{
    START_TEST;
	
	int nRet = asp_advert_set_status_changed_cb(AspAdvertStatusChangedCb, NULL);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_set_status_changed_cb", AspOutputGetError(nRet));
	
	nRet = asp_advert_unset_status_changed_cb();
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_advert_unset_status_changed_cb", AspOutputGetError(nRet));
	
	return 0;
}

/** @} */
/** @} */