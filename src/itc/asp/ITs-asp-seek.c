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

//& set: Asp-seek

/** @addtogroup itc-asp
*  @ingroup itc
*  @{
*/

static asp_seek_service_h g_hSeekSvc = NULL;

/************************/
/** Callback Functions **/
/************************/

static void AspSeekSearchResultCb(int error_code, asp_seek_service_h seek_service, const char *service_mac, unsigned int adv_id, asp_wps_type_e config_method,
                                  const char *instance_name, const char *service_info, int info_size, unsigned char status, void *user_data)
{
}


/**
 * @function 		ITs_asp_seek_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_asp_seek_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int nRet = remove(ERR_LOG);
		PRINT_RESULT_NORETURN(0, nRet, "ITs_asp_seek_startup -remove", "Remove failed for ERR_LOG");
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

	char *pszServiceType = "Display";
	nRet = asp_seek_create(pszServiceType, &g_hSeekSvc);
	if( nRet != ASP_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] asp_seek_create API failed in Precondition, returned error %s \\n", __LINE__, API_NAMESPACE, AspOutputGetError(nRet));
		g_bAspInit = false;
		return;
	}
	if( g_hSeekSvc == NULL )
	{
		FPRINTF("[Line : %d][%s] asp_seek_create API failed in Precondition, service handle created is NULL \\n", __LINE__, API_NAMESPACE);
		g_bAspInit = false;
	}
	return;
}

/**
 * @function 		ITs_asp_seek_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_asp_seek_cleanup(void)
{
	if(g_bAspInit)
	{
		if( g_hSeekSvc )
		{
			asp_seek_destroy(g_hSeekSvc);
			g_hSeekSvc = NULL;
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

//& purpose: Adds and removes the information for a service to be sought
//& type : auto
/**
* @testcase 			ITc_asp_seek_add_remove_info_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Adds and removes the information for a service to be sought
* @scenario				Adds and removes the information for a service to be sought
* @apicovered			asp_seek_add_info, asp_seek_remove_info
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create seek service handle
* @postcondition		Call API asp_deinitialize and destroy seek service handle
*/
int ITc_asp_seek_add_remove_info_p(void)
{
    START_TEST;
	
	char *pszKey = "hdcp=2,mode=dual";
	
	int nRet = asp_seek_add_info(g_hSeekSvc, pszKey);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_seek_add_info", AspOutputGetError(nRet));

	nRet = asp_seek_remove_info(g_hSeekSvc, pszKey);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_seek_remove_info", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Sets the discovery mechanism for a service to be sought
//& type : auto
/**
* @testcase 			ITc_asp_seek_set_discovery_tech_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the discovery mechanism for a service to be sought
* @scenario				Sets the discovery mechanism for a service to be sought
* @apicovered			asp_seek_set_discovery_tech
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create seek service handle
* @postcondition		Call API asp_deinitialize and destroy seek service handle
*/
int ITc_asp_seek_set_discovery_tech_p(void)
{
    START_TEST;
	
	int nEnumCount = 0, nIterator = 0;
	asp_discovery_tech_e eArrDiscoveryTech[] = { ASP_DISCOVERY_TECH_P2P,      /**< Use Wi-Fi P2P for discovery mechanism */
												 ASP_DISCOVERY_TECH_BLE,      /**< Use BLE for discovery mechanism */
												 ASP_DISCOVERY_TECH_NFC,      /**< Use NFC for discovery mechanism */
												 ASP_DISCOVERY_TECH_INFRA,    /**< Use Wi-Fi Infrastructured for discovery mechanism */
												 ASP_DISCOVERY_TECH_NAN   };  /**< Use Wi-Fi NAN for discovery mechanism */
	
	
	nEnumCount = sizeof(eArrDiscoveryTech) / sizeof(eArrDiscoveryTech[0]);

	for(nIterator = 0; nIterator < nEnumCount; nIterator++)
	{
		int nRet = asp_seek_set_discovery_tech(g_hSeekSvc, eArrDiscoveryTech[nIterator]);
		PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_seek_set_discovery_tech", AspOutputGetError(nRet));
	}
	
	return 0;
}

//& purpose:Sets the preferred connection for a service to be sought
//& type : auto
/**
* @testcase 			ITc_asp_seek_set_preferred_connection_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Sets the preferred connection for a service to be sought
* @scenario				Sets the preferred connection for a service to be sought
* @apicovered			asp_seek_set_preferred_connection
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create seek service handle
* @postcondition		Call API asp_deinitialize and destroy seek service handle
*/
int ITc_asp_seek_set_preferred_connection_p(void)
{
    START_TEST;
	
	int nPreferredConnection = 1;
	
	int nRet = asp_seek_set_preferred_connection(g_hSeekSvc, nPreferredConnection);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_seek_set_preferred_connection", AspOutputGetError(nRet));
	
	return 0;
}

//& purpose: Starts and stops to seek services on peer devices.
//& type : auto
/**
* @testcase 			ITc_asp_seek_start_stop_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Starts and stops to seek services on peer devices
* @scenario				Starts and stops to seek services on peer devices
* @apicovered			asp_seek_start, asp_seek_stop
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create seek service handle
* @postcondition		Call API asp_deinitialize and destroy seek service handle
*/
int ITc_asp_seek_start_stop_p(void)
{
    START_TEST;
	int nRet = asp_seek_start(g_hSeekSvc);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_seek_start", AspOutputGetError(nRet));

	nRet = asp_seek_stop(g_hSeekSvc);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_seek_stop", AspOutputGetError(nRet));
	
	return 0;
}
										   
//& purpose: Registers and unregisters the callback function that will be invoked when a service found
//& type : auto
/**
* @testcase 			ITc_asp_seek_set_unset_search_result_cb_p
* @since_tizen			4.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Registers and unregisters the callback function that will be invoked when a service found
* @scenario				Registers and unregisters the callback function that will be invoked when a service found
* @apicovered			asp_seek_set_search_result_cb, asp_seek_unset_search_result_cb
* @passcase				When APIs return ASP_ERROR_NONE
* @failcase				When APIs not return ASP_ERROR_NONE
* @precondition			Call API asp_initialize and create seek service handle
* @postcondition		Call API asp_deinitialize and destroy seek service handle
*/
int ITc_asp_seek_set_unset_search_result_cb_p(void)
{
    START_TEST;
	
	int nRet = asp_seek_set_search_result_cb(AspSeekSearchResultCb, NULL);
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_seek_set_search_result_cb", AspOutputGetError(nRet));
	
	nRet = asp_seek_unset_search_result_cb();
	PRINT_RESULT(ASP_ERROR_NONE, nRet, "asp_seek_unset_search_result_cb", AspOutputGetError(nRet));
	
	return 0;
}
/** @} */
/** @} */