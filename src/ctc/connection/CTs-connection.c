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
#include "CTs-connection-common.h"

/** @addtogroup ctc-connection
* @ingroup		ctc
* @{
*/

//& set: Connection

/**
* @function 		CTs_connection_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_connection_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Connection_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		CTs_connection_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_connection_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Connection_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	ctc-connection-testcases
* @brief 		Integration testcases for module connection
* @ingroup		ctc-connection
* @{
*/

//& purpose: Check if network wifi and network telephony features are supported in device.
//& type: auto
/**
* @testcase			CTc_NetworkConnection_FeatureSupport_p
* @since_tizen		2.3
* @author			SRID(sameer.g1)
* @reviewer			SRID(gupta.sanjay)
* @type  			auto 
* @scenario			Check if network wifi and network telephony features are supported in device configurations\n
* 					Call system info API to check required features
* @apicovered		system_info_get_platform_bool
* @passcase			API should return SYSTEM_INFO_ERROR_NONE
* @failcase			API returns negative error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_NetworkConnection_FeatureSupport_p(void)
{
	START_TEST;

	bool bWifiSupport = true;
	bool bMobDataSupport = true;
	bool bBluetoothSupport = true;
	bool bEthernetSupport = true;
	bool bNetworkProxySupport = true;
	
	IS_FEATURE_SUPPORTED(WIFI_FEATURE, bWifiSupport, API_NAMESPACE);
	if ( bWifiSupport )
	{
		FPRINTF("[Line : %d][%s] Wifi Connection feature is supported in the target device\\n", __LINE__, API_NAMESPACE);
	}
	
	IS_FEATURE_SUPPORTED(TELEPHONY_FEATURE, bMobDataSupport, API_NAMESPACE);
	if ( bMobDataSupport )
	{
		FPRINTF("[Line : %d][%s] Mobile Data feature is supported in the target device\\n", __LINE__, API_NAMESPACE);
	}
	
	IS_FEATURE_SUPPORTED(BLUETOOTH_FEATURE, bBluetoothSupport, API_NAMESPACE);
	if ( bBluetoothSupport )
	{
		FPRINTF("[Line : %d][%s] Bluetooth feature is supported in the target device\\n", __LINE__, API_NAMESPACE);
	}
	
	IS_FEATURE_SUPPORTED(ETHERNET_FEATURE, bEthernetSupport, API_NAMESPACE);
	if ( bEthernetSupport )
	{
		FPRINTF("[Line : %d][%s] Ethernet feature is supported in the target device\\n", __LINE__, API_NAMESPACE);
	}
	
	IS_FEATURE_SUPPORTED(NETPROXY_FEATURE, bNetworkProxySupport, API_NAMESPACE);
	if ( bNetworkProxySupport )
	{
		FPRINTF("[Line : %d][%s] Network Proxy feature is supported in the target device\\n", __LINE__, API_NAMESPACE);
	}
	
	if ( !bWifiSupport && !bMobDataSupport && !bBluetoothSupport && !bEthernetSupport && !bNetworkProxySupport )
	{
		FPRINTF("[Line : %d][%s] None of Wi-Fi Connection, Mobile Data, Bluetooth, Ethernet, Network Proxy feature is supported in the target device\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

/** @} */ //end of ctc-connection
/** @} */ //end of ctc-connection-testcases
