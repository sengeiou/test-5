//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include "ITs-capi-network-ua-common.h"

//& set: CapiNetwork-ua

/** @addtogroup itc-capi-network-ua
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_capi_network_ua_location_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_network_ua_location_startup(void)
{
	g_bUaInit = false;
	g_bIsUaFeatureSupported = false;
	g_bFeatureByPass = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	int nRet = UA_ERROR_NONE;

	g_bIsUaFeatureSupported = TCTCheckSystemInfoFeatureSupported(UA_FEATURE, API_NAMESPACE);

	nRet = ua_initialize();
	if(!g_bIsUaFeatureSupported)
	{
		if ( nRet != UA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ua_initialize failed to return UA_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			return;
		}

		FPRINTF("[%s:%d] feature and ua_initialize is unsupported\\n", __FILE__, __LINE__);
		g_bFeatureByPass = true;
		return;
	}
	else if (nRet == UA_ERROR_NONE || nRet == UA_ERROR_ALREADY_DONE)
		g_bUaInit = true;
	else
	{
		FPRINTF("[%s:%d] ua_initialize failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bUaInit = false;
	}
}


/**
 * @function 		ITs_capi_network_ua_location_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_network_ua_location_cleanup(void)
{
	int nRet = UA_ERROR_NONE;

	if (g_bIsUaFeatureSupported && g_bUaInit)
	{
		nRet = ua_deinitialize();
		if ( nRet != UA_ERROR_NONE )
		{
			FPRINTF("[%s:%d] ua_deinitialize failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		}
	}
	return;
}

//& purpose: Set location period
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_monitor_set_location_period_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Set location period
* @scenario				Set location period
* @apicovered			ua_monitor_set_location_period
* @passcase				If ua_monitor_set_location_period is successfull
* @failcase 			If ua_monitor_set_location_period or any precondition fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_monitor_set_location_period_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_monitor_h hMonitor = NULL;
	// Feature is specific to ua_monitor_set_location_period api
	bool bIsUaLocationFeatureSupported = TCTCheckSystemInfoFeatureSupported(UA_LOCATION_FEATURE, API_NAMESPACE);

	nRet = ua_monitor_create(&hMonitor);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_create", UaGetError(nRet));
	CHECK_HANDLE(hMonitor, "ua_monitor_create");

	//Target API
	nRet = ua_monitor_set_location_period(hMonitor, 500);
	if (!bIsUaLocationFeatureSupported) 
	{
		if ( nRet != UA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ua_monitor_set_location_period failed to return UA_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			ua_monitor_destroy(hMonitor);
			return 1;
		}
		else
		{
			FPRINTF("[%s:%d] feature is unsupported and ua_monitor_set_location_period also returned not supported\\n", __FILE__, __LINE__);
			ua_monitor_destroy(hMonitor);
			return 0;
		}
	}
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_set_location_period", UaGetError(nRet));

	nRet = ua_monitor_destroy(hMonitor);
	PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_monitor_destroy", UaGetError(nRet));

	return 0;
}