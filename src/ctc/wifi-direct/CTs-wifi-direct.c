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
#include "CTs-wifi-direct-common.h"

/** @addtogroup ctc-wifi-direct
* @ingroup		ctc
* @{
*/

//& set: WifiDirect

/**
* @function 		CTs_wifi_direct_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_wifi_direct_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Wifi_Direct_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_wifi_direct_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_wifi_direct_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Wifi_Direct_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	ctc-wifi-direct-testcases
* @brief 		Integration testcases for module wifi-direct
* @ingroup		ctc-wifi-direct
* @{
*/

/**
* @testcase 		CTc_wifi_direct_check_wifi_support
* @since_tizen		2.3
* @author            SRID(satyajit.a)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @scenario			Check WiFi-direct support\n
* 					If WiFi-direct is supported, check for WiFi support
* @apicovered		system_info_get_platform_bool
* @pass-case		WiFi must be supported if WiFi-direct is supported
* @failcase			WiFi is not supported if WiFi-direct is supported
* @precondition		NA
* @postcondition	NA
*/
int CTc_wifi_direct_check_wifi_support(void)
{
	START_TEST;
	if ( true == TCTCheckSystemInfoFeatureSupported(FEATURE_WIFI_DIRECT, API_NAMESPACE) )
	{
		FPRINTF("[Line : %d][%s] WiFi-Direct is supported\\n", __LINE__, API_NAMESPACE);
		if ( false == TCTCheckSystemInfoFeatureSupported(FEATURE_WIFI, API_NAMESPACE) )
		{
			FPRINTF("[Line : %d][%s] WiFi is not supported while WiFi-Direct is supported\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		FPRINTF("[Line : %d][%s] WiFi is also supported\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

/** @} */ //end of ctc-wifi-direct
/** @} */ //end of ctc-wifi-direct-testcases