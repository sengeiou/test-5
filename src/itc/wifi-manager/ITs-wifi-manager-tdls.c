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
#include "ITs-wifi-manager-common.h"

//& set: WifiManager

/** @addtogroup itc-wifi-manager
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_wifi_manager_tdls_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_wifi_manager_tdls_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bIsFeatureMismatched = false;
	g_bWifiManagerCreation = false;
	g_bFeatureWifi = TCTCheckSystemInfoFeatureSupported(FEATURE_WIFI, API_NAMESPACE);

	int nRet = wifi_manager_initialize(&g_hWifi);
	if ( !g_bFeatureWifi )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] wifi_manager_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] wifi_manager_initialize is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_initialize is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != WIFI_MANAGER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] wifi_manager_initialize failed, error returned = %s (%d)\\n", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_initialize failed, error returned = %s (%d)", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
		g_bWifiManagerCreation = false;
	}
	else
	{
		g_bWifiManagerCreation = true;
	}
	return;
}


/**
 * @function 		ITs_wifi_manager_tdls_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_wifi_manager_tdls_cleanup(void)
{
	int nRet = wifi_manager_deinitialize(g_hWifi);
	if(nRet != WIFI_MANAGER_ERROR_NONE)
	{
		FPRINTF("[%s:%d] wifi_manager_deinitialize failed, error returned = %s (%d)\\n", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_deinitialize failed, error returned = %s (%d)", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
	}

	return;
}
