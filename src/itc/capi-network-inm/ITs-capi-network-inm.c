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
#include "ITs-capi-network-inm-common.h"

/** @addtogroup itc-capi-network-inm
*  @ingroup itc
*  @{
*/

//& set: Inm

/**
* @function 		PrintUrlResult
* @description	 	Helper function
* @parameter		inm_reachable_urls_check_result_e err
* @return 		char pointer
*/
static inline char * PrintUrlResult(inm_reachable_urls_check_result_e err)
{
	switch (err) {
	case INM_REACHABLE_URL_CHECK_RESULT_SUCCESS:
		return "SUCCESS\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_MALFORMED_URL:
		return "MALFORMED_URL error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_DNS_RESOLVE:
		return "DNS_RESOLVE error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_TCP_CONNECT:
		return "TCP_CONNECT error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_SSL:
		return "SSL error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_HTTP:
		return "HTTP error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_FILE_NOT_FOUND:
		return "FILE_NOT_FOUND error\n";
	case INM_REACHABLE_URL_CHECK_RESULT_ERROR_UNKNOWN:
		return "UNKNOWN error\n";
	}
}

/**
* @function 		InmReachableUrlsCheckResultDefaultCallback
* @description	 	Callback
* @parameter		inm_reachable_urls_check_result_e result, const char *url, void *user_data
* @return 		NA
*/
static void InmReachableUrlsCheckResultDefaultCallback(inm_reachable_urls_check_result_e result, const char *url, void *user_data)
{
	g_bDefaultUrlFound = (result == INM_REACHABLE_URL_CHECK_RESULT_SUCCESS);
	FPRINTF("[Line : %d][%s] %s %s\\n", __LINE__, API_NAMESPACE, url, PrintUrlResult(result));
	QUIT_GMAIN_LOOP;
}

/**
* @function 		InmDefaultDnsLookupResultCallback
* @description	 	Callback
* @parameter		bool found, void *user_data
* @return 		NA
*/
static void InmDefaultDnsLookupResultCallback(bool found, void *user_data)
{
	g_bDnsLookupFinished = found;
	FPRINTF("[Line : %d][%s] DNS lookup accomplished\\n", __LINE__, API_NAMESPACE);
	QUIT_GMAIN_LOOP;
}

/**
* @function 		InmDefaultGatewayFoundCallback
* @description	 	Callback
* @parameter		bool found, const char *ip, void *user_data
* @return 		NA
*/
static void InmDefaultGatewayFoundCallback(bool found, const char *ip, void *user_data)
{
	g_bGatewayFound = found;
	FPRINTF("[Line : %d][%s] Gateway %s found\\n", __LINE__, API_NAMESPACE, ip);
	QUIT_GMAIN_LOOP;
}

/**
* @function 		InmArpRequestIpFoundCallback
* @description	 	Callback
* @parameter		bool found, const char *ip, void *user_data
* @return 		NA
*/
static void InmArpRequestIpFoundCallback(bool found, const char *ip, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);
	if (g_strcmp0(ip, g_pszArpRequestedIpStr) == 0) {
		g_bArpRequestedIpFound = found;
		FPRINTF("[Line : %d][%s] ARP requested %s found\\n", __LINE__, API_NAMESPACE, ip);
	}
	QUIT_GMAIN_LOOP;
}

/**
* @function 		ITs_inm_startup
* @description	 	Called before each test
* @parameter		NA
* @return 		NA
*/
void ITs_inm_startup(void)
{
	g_bFeatureInm = TCTCheckSystemInfoFeatureSupported(FEATURE_INM, API_NAMESPACE);
	g_bFeatureWifi = TCTCheckSystemInfoFeatureSupported(FEATURE_WIFI, API_NAMESPACE);
	g_bFeatureEthernet = TCTCheckSystemInfoFeatureSupported(FEATURE_ETHERNET, API_NAMESPACE);
	g_bFeatureTelephony = TCTCheckSystemInfoFeatureSupported(FEATURE_TELEPHONY, API_NAMESPACE);
	g_bFeatureBttethering = TCTCheckSystemInfoFeatureSupported(FEATURE_BT_TETHERING, API_NAMESPACE);

	g_hInm = NULL;
	g_bInmCreation = false;
	g_bFeatureAllNotSupported = false;
	g_bIsFeatureMismatched = false;
	g_bFeatureNotSupported = false;

	int nRet = inm_initialize(&g_hInm);
	if(!g_bFeatureInm)
	{
		if(nRet != INM_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] inm_initialize failed due to feature mismatch.\\n", __LINE__, API_NAMESPACE);
			g_bIsFeatureMismatched = true;
			return;
		}
		else
		{
			g_bFeatureNotSupported = true;
			return;
		}
	}
	else
	{
		if(nRet != INM_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] inm_initialize failed. Error returned = %s\\n", __LINE__, API_NAMESPACE, InmGetError(nRet));
			return;
		}
	}
	if(g_hInm == NULL)
	{
		FPRINTF("[Line : %d][%s] inm_initialize failed. Handle returned = %d, nRet = %s\\n", __LINE__, API_NAMESPACE, g_hInm, InmGetError(nRet));
		return;
	}


	nRet = inm_get_current_connection(g_hInm, &g_hConnection);
	if ((g_bFeatureTelephony == false) && (g_bFeatureWifi == false) && (g_bFeatureBttethering == false) && (g_bFeatureEthernet == false) && (g_bFeatureInm == false))
	{
		g_bFeatureAllNotSupported = true;
		FPRINTF("[Line : %d][%s] No feature is supported\\n", __LINE__, API_NAMESPACE);
		dlog_print(DLOG_INFO, "NativeTCT", "[Line : %d][%s] no feature is supported", __LINE__, API_NAMESPACE);
	}
	else if (nRet != INM_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Fail to get current profile or service. Error = %s, g_hConnection = %d\\n", __LINE__, API_NAMESPACE, InmGetError(nRet), g_hConnection);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Fail to get current profile or service", __LINE__, API_NAMESPACE);
		return;
	}

	if(g_hConnection == NULL)
	{
		FPRINTF("[Line : %d][%s] Fail to get current profile or service.\\n", __LINE__, API_NAMESPACE);
		return;
	}

	g_bInmCreation = true;
	return;
}

/**
* @function 		ITs_inm_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 		NA
*/
void ITs_inm_cleanup(void)
{
	if(g_hInm != NULL)
	{
		int nRet = inm_deinitialize(g_hInm);
		g_hInm = NULL;
	}
}


/** @addtogroup itc-inm-testcases
*  @brief 		Integration testcases for module capi-network-inm
*  @ingroup 	itc-inm
*  @{
*/

/**
* @testcase 			ITc_inm_set_unset_ethernet_cable_state_changed_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset ethernet cable state-changed callback
* @scenario			Ethernet cable state-changed callback is set and then unset
* @apicovered			inm_set_ethernet_cable_state_changed_cb, inm_unset_ethernet_cable_state_changed_cb
* @passcase			When inm_set_ethernet_cable_state_changed_cb, inm_unset_ethernet_cable_state_changed_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of ethernet cable state-changed callbacks
//& type: auto
int ITc_inm_set_unset_ethernet_cable_state_changed_cb_p(void)
{
	START_TEST;

	int nRet;

	nRet = inm_set_ethernet_cable_state_changed_cb(g_hInm, InmSetEthernetCableStateChangedCallback, NULL);
	if(!g_bFeatureEthernet)
	{
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_set_ethernet_cable_state_changed_cb", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_set_ethernet_cable_state_changed_cb", InmGetError(nRet));

	nRet = inm_unset_ethernet_cable_state_changed_cb(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_unset_ethernet_cable_state_changed_cb", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_get_ethernet_cable_state
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Get ethernet cable state
* @scenario			Ethernet cable state gotten
* @apicovered			inm_get_ethernet_cable_state
* @passcase			When inm_get_ethernet_cable_state is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get ethernet cable state-changed
//& type: auto
int ITc_inm_get_ethernet_cable_state_p(void)
{
	START_TEST;

	int nRet;
	inm_ethernet_cable_state_e eCableState;

	nRet = inm_get_ethernet_cable_state(g_hInm, &eCableState);
	if(!g_bFeatureEthernet) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_ethernet_cable_state", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_ethernet_cable_state", InmGetError(nRet));
	if(!(eCableState == INM_ETHERNET_CABLE_STATE_DETACHED || eCableState == INM_ETHERNET_CABLE_STATE_ATTACHED))
	{
		FPRINTF("[Line : %d][%s] %s failed. CableState value = %d\\n", __LINE__, API_NAMESPACE, "inm_get_ethernet_cable_state", eCableState);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_set_unset_wifi_module_state_changed_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset wifi module state-changed callback
* @scenario			Wifi module state-changed callback is set and then unset
* @apicovered			inm_set_wifi_module_state_changed_cb, inm_unset_wifi_module_state_changed_cb
* @passcase			When inm_set_wifi_module_state_changed_cb, inm_unset_wifi_module_state_changed_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of wifi module state-changed callbacks
//& type: auto
int ITc_inm_set_unset_wifi_module_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_set_wifi_module_state_changed_cb(g_hInm, InmWifiStateChangedCallback, NULL);
	if(!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_set_wifi_module_state_changed_cb", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_set_wifi_module_state_changed_cb", InmGetError(nRet));

	nRet = inm_unset_wifi_module_state_changed_cb(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_unset_wifi_module_state_changed_cb", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_get_wifi_module_state
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Get wifi module state
* @scenario			Wifi module cable state is gotten
* @apicovered			inm_get_wifi_module_state
* @passcase			When inm_get_wifi_module_state is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get wifi module state
//& type: auto
int ITc_inm_get_wifi_module_state_p(void)
{
	START_TEST;

	inm_wifi_module_state_e eModuleState;
	int nRet = INM_ERROR_NONE;

	nRet = inm_get_wifi_module_state(g_hInm, &eModuleState);
	if(!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_wifi_module_state", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_wifi_module_state", InmGetError(nRet));
	if(eModuleState < INM_WIFI_MODULE_STATE_DETACHED || eModuleState > INM_WIFI_MODULE_STATE_ATTACHED)
	{
		FPRINTF("[Line : %d][%s] %s failed. ModuleState value = %d\\n", __LINE__, API_NAMESPACE, "inm_get_wifi_module_state", eModuleState);
		return 1;
	}

	return 0;
}


/**
* @testcase 			ITc_inm_set_unset_ip_conflict_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset ip conflict callback
* @scenario			Ip conflict callback is set and then unset
* @apicovered			inm_set_ip_conflict_cb, inm_unset_ip_conflict_cb
* @passcase			When inm_set_ip_conflict_cb, inm_unset_ip_conflict_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of ip conflict callbacks
//& type: auto
int ITc_inm_set_unset_ip_conflict_cb_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_set_ip_conflict_cb(g_hInm, InmSetIpConflictCallback, NULL);
	if(!g_bFeatureWifi && !g_bFeatureEthernet) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_set_ip_conflict_cb", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_set_ip_conflict_cb", InmGetError(nRet));

	nRet = inm_unset_ip_conflict_cb(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_unset_ip_conflict_cb", InmGetError(nRet));

	return 0;
}


/**
* @testcase 			ITc_inm_ip_conflict_detect_is_enabled
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Checks whether ip conflict detection is enabled or not
* @scenario			IP conflict detection is checked
* @apicovered			inm_ip_conflict_detect_is_enabled
* @passcase			When inm_ip_conflict_detect_is_enabled is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to whether ip conflict detection is enabled or not
//& type: auto
int ITc_inm_ip_conflict_detect_is_enabled_p(void)
{
	START_TEST;

	bool bState = false;

	int nRet = inm_ip_conflict_detect_is_enabled(g_hInm, &bState);
	if(!g_bFeatureWifi && !g_bFeatureEthernet) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_ip_conflict_detect_is_enabled", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_ip_conflict_detect_is_enabled", InmGetError(nRet));

	return 0;
}


/**
* @testcase 			ITc_inm_get_ip_conflict_state
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Checks IP conflict state
* @scenario			IP conflict state is checked
* @apicovered			inm_get_ip_conflict_state
* @passcase			When inm_get_ip_conflict_state is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to check IP conflict state
//& type: auto
int ITc_inm_get_ip_conflict_state_p(void)
{
	START_TEST;

	inm_ip_conflict_state_e eConflictState;

	int nRet = inm_get_ip_conflict_state(g_hInm, &eConflictState);
	if(!g_bFeatureWifi && !g_bFeatureEthernet) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_ip_conflict_state", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_ip_conflict_state", InmGetError(nRet));
	if(eConflictState < INM_IP_CONFLICT_STATE_UNKNOWN || eConflictState > INM_IP_CONFLICT_STATE_CONFLICT_DETECTED)
	{
		FPRINTF("[Line : %d][%s] %s failed. ConflictState value = %d\\n", __LINE__, API_NAMESPACE, "inm_get_ip_conflict_state", eConflictState);
		return 1;
	}

	return 0;
}


/**
* @testcase 			ITc_inm_get_statistics
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets INM statistics
* @scenario			INM statistics are gotten
* @apicovered			inm_get_statistics
* @passcase			When inm_get_statistics is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get INM statistics
//& type: auto
int ITc_inm_get_statistics_p(void)
{
	START_TEST;

	unsigned long long llStat=0;
	int nRet = INM_ERROR_NONE;

	inm_statistics_type_e eStatType[] = {
	INM_STATISTICS_TYPE_LAST_RECEIVED_DATA,
	INM_STATISTICS_TYPE_LAST_SENT_DATA,
	INM_STATISTICS_TYPE_TOTAL_RECEIVED_DATA,
	INM_STATISTICS_TYPE_TOTAL_SENT_DATA
	};

	inm_connection_type_e eConnectionType[] = {
	INM_CONNECTION_TYPE_WIFI,
	INM_CONNECTION_TYPE_CELLULAR,
	};

	bool bConnectionTypeFeatureChecks[] = {
	g_bFeatureWifi,
	g_bFeatureTelephony
	};

	int nStatTypeSize = sizeof(eStatType)/sizeof(eStatType[0]);
	int nConnectionTypeSize = sizeof(eConnectionType)/sizeof(eConnectionType[0]);

	for(int connectionTypeIndex = 0; connectionTypeIndex < nConnectionTypeSize; connectionTypeIndex++)
	{
		for(int statTypeIndex = 0; statTypeIndex < nStatTypeSize; statTypeIndex++)
		{
			llStat=0;
			nRet = inm_get_statistics(g_hInm, eConnectionType[connectionTypeIndex], eStatType[statTypeIndex], &llStat);
			if(!bConnectionTypeFeatureChecks[connectionTypeIndex])
			{
				PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_statistics", InmGetError(nRet));
				return 0;
			}
			PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_statistics", InmGetError(nRet));

// This variable needs to be checked whether within range.
/*			if(llStat< 0)
			{
				FPRINTF("[Line : %d][%s] %s failed. Stat value = %ull\\n", __LINE__, API_NAMESPACE, "inm_get_statistics", llStat);
				return 1;
			}
*/
		}
	}

	return 0;
}


/**
* @testcase 			ITc_inm_reset_statistics
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Resets INM statistics
* @scenario			INM statistics are reset
* @apicovered			inm_reset_statistics
* @passcase			When inm_reset_statistics is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to reset INM statistics
//& type: auto
int ITc_inm_reset_statistics_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	inm_statistics_type_e eStatType[] = {
	INM_STATISTICS_TYPE_LAST_RECEIVED_DATA,
	INM_STATISTICS_TYPE_LAST_SENT_DATA,
	INM_STATISTICS_TYPE_TOTAL_RECEIVED_DATA,
	INM_STATISTICS_TYPE_TOTAL_SENT_DATA
	};

	inm_connection_type_e eConnectionType[] = {
	INM_CONNECTION_TYPE_WIFI,
	INM_CONNECTION_TYPE_CELLULAR,
	};

	bool bConnectionTypeFeatureChecks[] = {
	g_bFeatureWifi,
	g_bFeatureTelephony
	};

	int nStatTypeSize = sizeof(eStatType)/sizeof(eStatType[0]);
	int nConnectionTypeSize = sizeof(eConnectionType)/sizeof(eConnectionType[0]);

	for(int connectionTypeIndex = 0; connectionTypeIndex < nConnectionTypeSize; connectionTypeIndex++)
	{
		for(int statTypeIndex = 0; statTypeIndex < nStatTypeSize; statTypeIndex++)
		{
			nRet = inm_reset_statistics(g_hInm, eConnectionType[connectionTypeIndex], eStatType[statTypeIndex]);
			if(!bConnectionTypeFeatureChecks[connectionTypeIndex])
			{
				PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_statistics", InmGetError(nRet));
				return 0;
			}
			PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_reset_statistics", InmGetError(nRet));
		}
	}

	return 0;
}


/**
* @testcase 			ITc_inm_set_unset_congestion_level_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset congestion level callback
* @scenario			Congestion level callback is set and then unset
* @apicovered			inm_set_congestion_level_cb, inm_unset_congestion_level_cb
* @passcase			When inm_set_congestion_level_cb, inm_unset_congestion_level_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of congestion level callbacks
//& type: auto
int ITc_inm_set_unset_congestion_level_cb_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_set_congestion_level_cb(g_hInm, InmSetCongestionLevelCallback, NULL);
	if (!g_bFeatureTelephony && !g_bFeatureWifi && !g_bFeatureEthernet) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_set_congestion_level_cb", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_set_congestion_level_cb", InmGetError(nRet));

	nRet = inm_unset_congestion_level_cb(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_unset_congestion_level_cb", InmGetError(nRet));

	return 0;
}


/**
* @testcase 			ITc_inm_get_congestion_level
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets congestion level
* @scenario			Congestion level is gotten
* @apicovered			inm_get_congestion_level
* @passcase			When inm_get_congestion_level are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get the congestion level
//& type: auto
int ITc_inm_get_congestion_level_p(void)
{
	START_TEST;

	inm_congestion_level_e eCongestionLevel;

	int nRet = inm_get_congestion_level(g_hInm, &eCongestionLevel);
	if (!g_bFeatureTelephony && !g_bFeatureWifi && !g_bFeatureEthernet) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_congestion_level", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_congestion_level", InmGetError(nRet));
	if(eCongestionLevel < INM_CONGESTION_LEVEL_VERY_HIGH || eCongestionLevel > INM_CONGESTION_LEVEL_LOW)
	{
		FPRINTF("[Line : %d][%s] %s failed. CongestionLevel value = %d\\n", __LINE__, API_NAMESPACE, "inm_get_congestion_level", eCongestionLevel);
		return 1;
	}

	return 0;
}


/**
* @testcase 			ITc_inm_set_unset_retry_tx_rate_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset retry tx rate callback
* @scenario			Retry tx rate callback is set and then unset
* @apicovered			inm_set_retry_tx_rate_cb, inm_unset_retry_tx_rate_cbs
* @passcase			When inm_set_retry_tx_rate_cb, inm_unset_retry_tx_rate_cbs are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of retry tx rate callbacks
//& type: auto
int ITc_inm_set_unset_retry_tx_rate_cb_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_set_retry_tx_rate_cb(g_hInm, InmSetRetryTxRateCallback, NULL);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_set_retry_tx_rate_cb", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_set_retry_tx_rate_cb", InmGetError(nRet));

	nRet = inm_unset_retry_tx_rate_cb(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_unset_retry_tx_rate_cb", InmGetError(nRet));

	return 0;
}


/**
* @testcase 			ITc_inm_get_retry_tx_rate
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets retry tx rate
* @scenario			Retry tx rate is gotten
* @apicovered			inm_get_retry_tx_rate
* @passcase			When inm_get_retry_tx_rate is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get retry tx rate
int ITc_inm_get_retry_tx_rate_p(void)
{
	START_TEST;

	int nTxRate = -1;
	int nRet = INM_ERROR_NONE;

	nRet = inm_get_retry_tx_rate(g_hInm, &nTxRate);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_retry_tx_rate", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_retry_tx_rate", InmGetError(nRet));
	if(nTxRate < 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. TxRate value = %d\\n", __LINE__, API_NAMESPACE, "inm_get_congestion_level", nTxRate);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_set_unset_channel_interference_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset channel interference callback
* @scenario			Channel interference callback is set and then unset
* @apicovered			inm_set_channel_interference_cb, inm_unset_channel_interference_cb
* @passcase			When inm_set_channel_interference_cb, inm_unset_channel_interference_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of channel interference callbacks
//& type: auto
int ITc_inm_set_unset_channel_interference_cb_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_set_channel_interference_cb(g_hInm, InmSetChannelInterferenceCallback, NULL);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_set_channel_interference_cb", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_set_channel_interference_cb", InmGetError(nRet));

	nRet = inm_unset_channel_interference_cb(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_unset_channel_interference_cb", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_get_channel_interference
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Get channel interference
* @scenario			Channel interference is gotten
* @apicovered			inm_get_channel_interference
* @passcase			When inm_get_channel_interference is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get channel interference
//& type: auto
int ITc_inm_get_channel_interference_p(void)
{
	START_TEST;

	double nInterference = -1;
	int nRet = INM_ERROR_NONE;

	nRet = inm_get_channel_interference(g_hInm, &nInterference);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_channel_interference", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_channel_interference", InmGetError(nRet));
	if(nInterference < 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. Interference value = %d\\n", __LINE__, API_NAMESPACE, "inm_get_congestion_level", nInterference);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_set_unset_cellular_state_changed_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset cellular state-changed callback
* @scenario			Cellular state-changed callback is set and then unset
* @apicovered			inm_set_cellular_state_changed_cb, inm_unset_cellular_state_changed_cb
* @passcase			When inm_set_cellular_state_changed_cb, inm_unset_cellular_state_changed_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of cellular state-changed callbacks
//& type: auto
int ITc_inm_set_unset_cellular_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_set_cellular_state_changed_cb(g_hInm, InmSetCellularStateChangedCallback, NULL);
	if (!g_bFeatureTelephony) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_set_cellular_state_changed_cb", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_set_cellular_state_changed_cb", InmGetError(nRet));

	nRet = inm_unset_cellular_state_changed_cb(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_unset_cellular_state_changed_cb", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_get_cellular_state
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets cellular state
* @scenario			Cellular state is gotten
* @apicovered			inm_get_cellular_state
* @passcase			When inm_get_cellular_state is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get cellular state
//& type: auto
int ITc_inm_get_cellular_state_p(void)
{
	START_TEST;

	inm_cellular_state_e eCellularState;

	int nRet = inm_get_cellular_state(g_hInm, &eCellularState);
	if (!g_bFeatureTelephony) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_cellular_state", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_cellular_state", InmGetError(nRet));
	if(eCellularState < INM_CELLULAR_STATE_DEACTIVATED || eCellularState > INM_CELLULAR_STATE_CONNECTED)
	{
		FPRINTF("[Line : %d][%s] %s failed. CellularState value = %d\\n", __LINE__, API_NAMESPACE, "inm_get_cellular_state", eCellularState);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_set_unset_wifi_state_changed_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset wifi state-changed callback
* @scenario			Wifi state-changed callback is set and then unset
* @apicovered			inm_set_wifi_state_changed_cb, inm_unset_wifi_state_changed_cb
* @passcase			When inm_set_wifi_state_changed_cb, inm_unset_wifi_state_changed_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of wifi state-changed callbacks
//& type: auto
int ITc_inm_set_unset_wifi_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_set_wifi_state_changed_cb(g_hInm, InmSetWifiStateChangedCallback, NULL);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_set_wifi_state_changed_cb", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_set_wifi_state_changed_cb", InmGetError(nRet));

	nRet = inm_unset_wifi_state_changed_cb(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_unset_wifi_state_changed_cb", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_get_wifi_state
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets wifi state
* @scenario			Wifi state is gotten
* @apicovered			inm_get_wifi_state
* @passcase			When inm_get_wifi_state is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get wifi state
//& type: auto
int ITc_inm_get_wifi_state_p(void)
{
	START_TEST;

	inm_wifi_state_e eWifiState;
	int nRet = INM_ERROR_NONE;

	nRet = inm_get_wifi_state(g_hInm, &eWifiState);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_wifi_state", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_wifi_state", InmGetError(nRet));
	if(eWifiState < INM_WIFI_STATE_DEACTIVATED || eWifiState > INM_WIFI_STATE_CONNECTED)
	{
		FPRINTF("[Line : %d][%s] %s failed. WifiState value = %d\\n", __LINE__, API_NAMESPACE, "inm_get_wifi_state", eWifiState);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_set_unset_ethernet_state_changed_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset ethernet state-changed callback
* @scenario			Ethernet state-changed callback is set and then unset
* @apicovered			inm_set_ethernet_state_changed_cb, inm_unset_ethernet_state_changed_cb
* @passcase			When inm_set_ethernet_state_changed_cb, inm_unset_ethernet_state_changed_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of ethernet state-changed callbacks
//& type: auto
int ITc_inm_set_unset_ethernet_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_set_ethernet_state_changed_cb(g_hInm, InmSetEthernetStateChangedCallback, NULL);
	if (!g_bFeatureEthernet) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_set_ethernet_state_changed_cb", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_set_ethernet_state_changed_cb", InmGetError(nRet));

	nRet = inm_unset_ethernet_state_changed_cb(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_unset_ethernet_state_changed_cb", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_get_ethernet_state
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets ethernet state
* @scenario			Ethernet state is gotten
* @apicovered			inm_get_ethernet_state
* @passcase			When inm_get_ethernet_state is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get ethernet state
//& type: auto
int ITc_inm_get_ethernet_state_p(void)
{
	START_TEST;

	inm_ethernet_state_e eEthernetState;
	int nRet = INM_ERROR_NONE;

	nRet = inm_get_ethernet_state(g_hInm, &eEthernetState);
	if (!g_bFeatureEthernet) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_ethernet_state", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_ethernet_state", InmGetError(nRet));
	if(eEthernetState < INM_ETHERNET_STATE_DEACTIVATED || eEthernetState > INM_ETHERNET_STATE_CONNECTED)
	{
		FPRINTF("[Line : %d][%s] %s failed. EthernetState value = %d\\n", __LINE__, API_NAMESPACE, "inm_get_ethernet_state", eEthernetState);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_get_current_connection
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets current connection
* @scenario			Current connection is gotten
* @apicovered			inm_get_current_connection
* @passcase			When inm_get_current_connection is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get current connection
//& type: auto
int ITc_inm_get_current_connection_p(void)
{
	START_TEST;

	inm_connection_h hProfile;

	int nRet = inm_get_current_connection(g_hInm, &hProfile);
	if (g_bFeatureAllNotSupported) {
		if(hProfile != NULL)
			inm_connection_destroy(&hProfile);
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_current_connection", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_current_connection", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "inm_get_current_connection");

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_clone_destroy
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Clone and destroy connection
* @scenario			Connection is cloned and destroyed
* @apicovered			inm_connection_clone, inm_connection_destroy
* @passcase			When inm_connection_clone, inm_connection_destroy are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to clone and destroy connections
//& type: auto
int ITc_inm_connection_clone_destroy_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	inm_connection_h hProfileCloned = NULL;
	inm_connection_h hProfileOrigin = NULL;

	nRet = InmGetAnyProfile(&hProfileOrigin);
	if(nRet == FEATURE_NOT_SUPPORTED)
		return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfileOrigin, "InmGetAnyProfile");

	nRet = inm_connection_clone(&hProfileCloned, hProfileOrigin);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_connection_clone", InmGetError(nRet));
	CHECK_HANDLE(hProfileCloned, "inm_connection_clone");

	nRet = inm_connection_destroy(&hProfileOrigin);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	nRet = inm_connection_destroy(&hProfileCloned);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_destroy_connection_iterator
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Destroys connection iterator
* @scenario			Connection iterator is destroyed
* @apicovered			inm_get_connection_iterator, inm_destroy_connection_iterator
* @passcase			When inm_get_connection_iterator, inm_destroy_connection_iterator are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to destroy connection iterator
//& type: auto
int ITc_inm_get_destroy_connection_iterator_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;
	inm_connection_iterator_h hConnectionIterator = NULL;

	nRet = inm_get_connection_iterator(g_hInm, &hConnectionIterator);
	if (g_bFeatureAllNotSupported) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_destroy_connection_iterator", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_connection_iterator", InmGetError(nRet));
	CHECK_HANDLE(hConnectionIterator, "inm_get_connection_iterator");

	nRet = inm_destroy_connection_iterator(hConnectionIterator);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_destroy_connection_iterator", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_iterator_next
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets next element in connection iterator
* @scenario			Next element in connection iterator is gotten
* @apicovered			inm_connection_iterator_next
* @passcase			When inm_connection_iterator_next are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get next element in the connection iterator
//& type: auto
int ITc_inm_connection_iterator_next_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;
	inm_connection_iterator_h hConnectionIterator = NULL;
	inm_connection_h hProfile = NULL;

	nRet = inm_get_connection_iterator(g_hInm, &hConnectionIterator);
	if (g_bFeatureAllNotSupported) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_get_connection_iterator", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_get_connection_iterator", InmGetError(nRet));
	CHECK_HANDLE(hConnectionIterator, "inm_get_connection_iterator");

	nRet = inm_connection_iterator_next(hConnectionIterator, &hProfile);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_connection_iterator_next", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "inm_get_connection_iterator");

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_id
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets connection ID
* @scenario			Connection ID is gotten
* @apicovered			inm_connection_get_id
* @passcase			When inm_connection_get_id is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection id
//& type: auto
int ITc_inm_connection_get_id_p(void)
{
	START_TEST;

	char *pszId = NULL;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_id(hProfile, &pszId);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_connection_get_id", InmGetError(nRet));
	CHECK_HANDLE_CLEANUP(pszId, "inm_connection_get_id", FREE_MEMORY_TC(pszId));
	FREE_MEMORY_TC(pszId);

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_name
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets connection name
* @scenario			Connection name is gotten
* @apicovered			inm_connection_get_name
* @passcase			When inm_connection_get_name is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection name
//& type: auto
int ITc_inm_connection_get_name_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;
	char *pszName = NULL;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_name(hProfile, &pszName);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_connection_get_name", InmGetError(nRet));
	CHECK_HANDLE_CLEANUP(pszName, "inm_connection_get_name", FREE_MEMORY_TC(pszName));
	FREE_MEMORY_TC(pszName);

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_type
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets connection type
* @scenario			Connection type is gotten
* @apicovered			inm_connection_get_type
* @passcase			When inm_connection_get_type is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection type
//& type: auto
int ITc_inm_connection_get_type_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;
	inm_connection_type_e eConnectionType;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_type(hProfile, &eConnectionType);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_connection_get_type", InmGetError(nRet));
	if(eConnectionType < INM_CONNECTION_TYPE_DISCONNECTED || eConnectionType > INM_CONNECTION_TYPE_NET_PROXY)
	{
		FPRINTF("[Line : %d][%s] %s failed. ConnectionType value = %d\\n", __LINE__, API_NAMESPACE, "inm_connection_get_type", eConnectionType);
		if(hProfile != NULL)
		{
			inm_connection_destroy(&hProfile);
		}
		return 1;
	}

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_network_interface_name
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets connection Network Interface name
* @scenario			Connection Network Interface name is gotten
* @apicovered			inm_connection_get_network_interface_name
* @passcase			When inm_connection_get_network_interface_name is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection network interface name
//& type: auto
int ITc_inm_connection_get_network_interface_name_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;
	char *pszInterfaceName = NULL;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_network_interface_name(hProfile, &pszInterfaceName);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_network_interface_name", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(pszInterfaceName, "inm_connection_get_network_interface_name", inm_connection_destroy(&hProfile));
	FREE_MEMORY_TC(pszInterfaceName);

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_state
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets connection state
* @scenario			Connection state is gotten
* @apicovered			inm_connection_get_state
* @passcase			When inm_connection_get_state is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection state
//& type: auto
int ITc_inm_connection_get_state_p(void)
{
	START_TEST;

	inm_connection_state_e eConnectionState;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_state(hProfile, &eConnectionState);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_state", InmGetError(nRet), inm_connection_destroy(&hProfile));
	if(eConnectionState < INM_CONNECTION_STATE_DISCONNECTED || eConnectionState > INM_CONNECTION_STATE_CONNECTED)
	{
		FPRINTF("[Line : %d][%s] %s failed. ConnectionState value = %d\\n", __LINE__, API_NAMESPACE, "inm_connection_get_state", eConnectionState);
		if(hProfile != NULL)
			inm_connection_destroy(&hProfile);
		return 1;
	}

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_ipv6_state
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Get ipv6 state
* @scenario			Connection ipv6 state is gotten
* @apicovered			inm_connection_get_ipv6_state
* @passcase			When inm_connection_get_ipv6_state is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection ipv6 state
//& type: auto
int ITc_inm_connection_get_ipv6_state_p(void)
{
	START_TEST;

	inm_connection_state_e eConnectionState;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_ipv6_state(hProfile, &eConnectionState);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_ipv6_state", InmGetError(nRet), inm_connection_destroy(&hProfile));
	if(eConnectionState < INM_CONNECTION_STATE_DISCONNECTED || eConnectionState > INM_CONNECTION_STATE_CONNECTED)
	{
		FPRINTF("[Line : %d][%s] %s failed. ConnectionState value = %d\\n", __LINE__, API_NAMESPACE, "inm_connection_get_ipv6_state", eConnectionState);
		if(hProfile != NULL)
			inm_connection_destroy(&hProfile);
		return 1;
	}

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_ip_config_type
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Get ip config type
* @scenario			Connection IP config type is gotten
* @apicovered			inm_connection_get_ip_config_type
* @passcase			When inm_connection_get_ip_config_type is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get ip config type
//& type: auto
int ITc_inm_connection_get_ip_config_type_p(void)
{
	START_TEST;

	inm_ip_config_type_e eIpConfType;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_ip_config_type(hProfile, INM_ADDRESS_FAMILY_IPV4, &eIpConfType);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_ip_config_type", InmGetError(nRet),inm_connection_destroy(&hProfile));
	if(eIpConfType < INM_IP_CONFIG_TYPE_NONE || eIpConfType > INM_IP_CONFIG_TYPE_FIXED)
	{
		FPRINTF("[Line : %d][%s] %s failed. IpConfType value = %d\\n", __LINE__, API_NAMESPACE, "inm_connection_get_ip_config_type", eIpConfType);
		if(hProfile != NULL)
			inm_connection_destroy(&hProfile);
		return 1;
	}

	nRet = inm_connection_get_ip_config_type(hProfile, INM_ADDRESS_FAMILY_IPV6, &eIpConfType);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_connection_get_ip_config_type", InmGetError(nRet));
	if(eIpConfType < INM_IP_CONFIG_TYPE_NONE || eIpConfType > INM_IP_CONFIG_TYPE_FIXED)
	{
		FPRINTF("[Line : %d][%s] %s failed. IpConfType value = %d\\n", __LINE__, API_NAMESPACE, "inm_connection_get_ip_config_type", eIpConfType);
		if(hProfile != NULL)
			inm_connection_destroy(&hProfile);
		return 1;
	}

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_ip_address
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets IP address
* @scenario			Connection IP address is gotten
* @apicovered			inm_connection_get_ip_address
* @passcase			When inm_connection_get_ip_address is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection ip address
//& type: auto
int ITc_inm_connection_get_ip_address_p(void)
{
	START_TEST;

	inm_connection_state_e eConnectionState;
	char *pszIpAddr = NULL;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_ip_address(hProfile, INM_ADDRESS_FAMILY_IPV4, &pszIpAddr);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_ip_address", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(pszIpAddr, "inm_connection_get_ip_address", inm_connection_destroy(&hProfile));
	FREE_MEMORY_TC(pszIpAddr);

	nRet = inm_connection_get_ipv6_state(hProfile, &eConnectionState);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_ipv6_state", InmGetError(nRet), inm_connection_destroy(&hProfile));
	if (eConnectionState == INM_CONNECTION_STATE_CONNECTED) {
		nRet = inm_connection_get_ip_address(hProfile, INM_ADDRESS_FAMILY_IPV6, &pszIpAddr);
		PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_ip_address", InmGetError(nRet),inm_connection_destroy(&hProfile));
		CHECK_HANDLE_CLEANUP(pszIpAddr, "inm_connection_get_ip_address", inm_connection_destroy(&hProfile));
		FREE_MEMORY_TC(pszIpAddr);
	}

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_subnet_mask
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets subnet mask
* @scenario			Connection subnet mask is gotten
* @apicovered			inm_connection_get_subnet_mask
* @passcase			When inm_connection_get_subnet_mask is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection subnet mask
//& type: auto
int ITc_inm_connection_get_subnet_mask_p(void)
{
	START_TEST;

	char *pszIpAddr = NULL;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_subnet_mask(hProfile, INM_ADDRESS_FAMILY_IPV4, &pszIpAddr);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_subnet_mask", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(pszIpAddr, "inm_connection_get_subnet_mask", inm_connection_destroy(&hProfile));
	FREE_MEMORY_TC(pszIpAddr);

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_gateway_address
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Get gateway address
* @scenario			Gateway address is gotten
* @apicovered			inm_connection_get_gateway_address
* @passcase			When inm_connection_get_gateway_address is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get gateway address
//& type: auto
int ITc_inm_connection_get_gateway_address_p(void)
{
	START_TEST;

	inm_connection_state_e eConnectionState;
	char *pszIpAddr = NULL;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_gateway_address(hProfile, INM_ADDRESS_FAMILY_IPV4, &pszIpAddr);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_gateway_address", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(pszIpAddr, "inm_connection_get_gateway_address", inm_connection_destroy(&hProfile));
	FREE_MEMORY_TC(pszIpAddr);
	nRet = inm_connection_get_ipv6_state(hProfile, &eConnectionState);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_ipv6_state", InmGetError(nRet), inm_connection_destroy(&hProfile));
	if (eConnectionState == INM_CONNECTION_STATE_CONNECTED) {
		nRet = inm_connection_get_gateway_address(hProfile, INM_ADDRESS_FAMILY_IPV6, &pszIpAddr);
		PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_gateway_address", InmGetError(nRet), inm_connection_destroy(&hProfile));
		CHECK_HANDLE_CLEANUP(pszIpAddr, "inm_connection_get_gateway_address", inm_connection_destroy(&hProfile));
		FREE_MEMORY_TC(pszIpAddr);
	}

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_dhcp_server_address
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets DHCP server address
* @scenario			Connection DHCP server address is gotten
* @apicovered			inm_connection_get_dhcp_server_address
* @passcase			When inm_connection_get_dhcp_server_address is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Connection DHCP server address
//& type: auto
int ITc_inm_connection_get_dhcp_server_address_p(void)
{
	START_TEST;

	char *pszIpAddr = NULL;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_dhcp_server_address(hProfile, INM_ADDRESS_FAMILY_IPV4, &pszIpAddr);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_dhcp_server_address", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(pszIpAddr, "inm_connection_get_dhcp_server_address", inm_connection_destroy(&hProfile));
	FREE_MEMORY_TC(pszIpAddr);

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_dhcp_lease_duration
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets DHCP lease duration
* @scenario			Connection DHCP lease duration is gotten
* @apicovered			inm_connection_get_dhcp_lease_duration
* @passcase			When inm_connection_get_dhcp_lease_duration are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection DHCP lease duration
//& type: auto
int ITc_inm_connection_get_dhcp_lease_duration_p(void)
{
	START_TEST;

	int nDhcpLeaseDuration = -1;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_dhcp_lease_duration(hProfile, INM_ADDRESS_FAMILY_IPV4, &nDhcpLeaseDuration);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_dhcp_lease_duration", InmGetError(nRet), inm_connection_destroy(&hProfile));
	if(nDhcpLeaseDuration < 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. DHCP Lease Duration obtained = %d\\n", __LINE__, API_NAMESPACE, "inm_connection_get_proxy_type", nDhcpLeaseDuration);
		if(hProfile != NULL)
			inm_connection_destroy(&hProfile);
		return 1;
	}

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_dns_address
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets DNS address
* @scenario			Connection DNS address is gotten
* @apicovered			inm_connection_get_dns_address
* @passcase			When inm_connection_get_dns_address is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get DNS address
//& type: auto
int ITc_inm_connection_get_dns_address_p(void)
{
	START_TEST;

	char *pszIpAddr = NULL;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_dns_address(hProfile, 1, INM_ADDRESS_FAMILY_IPV4, &pszIpAddr);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_dns_address", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(pszIpAddr, "inm_connection_get_dns_address", FREE_MEMORY_TC(pszIpAddr));
	FREE_MEMORY_TC(pszIpAddr);

	nRet = inm_connection_get_dns_address(hProfile, 2, INM_ADDRESS_FAMILY_IPV6, &pszIpAddr);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_dns_address", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(pszIpAddr, "inm_connection_get_dns_address", inm_connection_destroy(&hProfile));
	FREE_MEMORY_TC(pszIpAddr);

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_proxy_type
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets proxy type
* @scenario			Connection proxy type is gotten
* @apicovered			inm_connection_get_proxy_type
* @passcase			When inm_connection_get_proxy_type is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get proxy type
//& type: auto
int ITc_inm_connection_get_proxy_type_p(void)
{
	START_TEST;

	inm_proxy_type_e eProxyType;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_proxy_type(hProfile, &eProxyType);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_proxy_type", InmGetError(nRet), inm_connection_destroy(&hProfile));
	if(eProxyType < INM_PROXY_TYPE_DIRECT || eProxyType > INM_PROXY_TYPE_MANUAL)
	{
		FPRINTF("[Line : %d][%s] %s failed. ProxyType value = %d\\n", __LINE__, API_NAMESPACE, "inm_connection_get_proxy_type", eProxyType);
		if(hProfile != NULL)
			inm_connection_destroy(&hProfile);
		return 1;
	}

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_proxy_address
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets proxy address
* @scenario			Connection proxy address is gotten
* @apicovered			inm_connection_get_proxy_address
* @passcase			When inm_connection_get_proxy_address is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to connection proxy address
//& type: auto
int ITc_inm_connection_get_proxy_address_p(void)
{
	START_TEST;

	char *pszIpAddr = NULL;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_proxy_address(hProfile, INM_ADDRESS_FAMILY_IPV4, &pszIpAddr);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_proxy_address", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(pszIpAddr, "inm_connection_get_proxy_address", inm_connection_destroy(&hProfile));
	FREE_MEMORY_TC(pszIpAddr);

	nRet = inm_connection_get_proxy_address(hProfile, INM_ADDRESS_FAMILY_IPV6, &pszIpAddr);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_proxy_address", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(pszIpAddr, "inm_connection_get_proxy_address", inm_connection_destroy(&hProfile));
	FREE_MEMORY_TC(pszIpAddr);

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_dns_config_type
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets DNS config type
* @scenario			Connection DNS config type is gotten
* @apicovered			inm_connection_get_dns_config_type
* @passcase			When inm_connection_get_dns_config_type is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get DNS config type
//& type: auto
int ITc_inm_connection_get_dns_config_type_p(void)
{
	START_TEST;

	inm_dns_config_type_e eDnsConfType;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_get_dns_config_type(hProfile, INM_ADDRESS_FAMILY_IPV4, &eDnsConfType);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_dns_config_type", InmGetError(nRet), inm_connection_destroy(&hProfile));
	if(eDnsConfType < INM_DNS_CONFIG_TYPE_NONE || eDnsConfType > INM_DNS_CONFIG_TYPE_DYNAMIC)
	{
		FPRINTF("[Line : %d][%s] %s failed. DnsConfType value = %d\\n", __LINE__, API_NAMESPACE, "inm_connection_get_dns_config_type", eDnsConfType);
		if(hProfile != NULL)
			inm_connection_destroy(&hProfile);
		return 1;
	}

	nRet = inm_connection_get_dns_config_type(hProfile, INM_ADDRESS_FAMILY_IPV6, &eDnsConfType);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_dns_config_type", InmGetError(nRet), inm_connection_destroy(&hProfile));
	if(eDnsConfType < INM_DNS_CONFIG_TYPE_NONE || eDnsConfType > INM_DNS_CONFIG_TYPE_DYNAMIC)
	{
		FPRINTF("[Line : %d][%s] %s failed. DnsConfType value = %d\\n", __LINE__, API_NAMESPACE, "inm_connection_get_dns_config_type", eDnsConfType);
		if(hProfile != NULL)
			inm_connection_destroy(&hProfile);
		return 1;
	}

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_get_prefix_length
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets connection prefix length
* @scenario			Connection prefix length is gotten
* @apicovered			inm_connection_get_prefix_length
* @passcase			When inm_connection_get_prefix_length is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection prefix length
//& type: auto
int ITc_inm_connection_get_prefix_length_p(void)
{
	START_TEST;

	int nLength=0;
	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_get_current_connection(g_hInm, &hProfile);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_get_current_connection", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(hProfile, "inm_get_current_connection", inm_connection_destroy(&hProfile));

	nRet = inm_connection_get_prefix_length(hProfile, INM_ADDRESS_FAMILY_IPV6, &nLength);
        PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_get_current_connection", InmGetError(nRet), inm_connection_destroy(&hProfile));
        CHECK_HANDLE_CLEANUP(hProfile, "inm_get_current_connection", inm_connection_destroy(&hProfile));
        if(nLength<0)
        {
                FPRINTF("[Line : %d][%s] %s failed. Length = %d\\n", __LINE__, API_NAMESPACE, "inm_connection_get_prefix_length", nLength);
                if(hProfile != NULL)
                        inm_connection_destroy(&hProfile);
                return 1;
        }

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_refresh
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Refreshes connection
* @scenario			Connection is refreshed
* @apicovered			inm_connection_refresh
* @passcase			When inm_connection_refresh are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to refresh connection
//& type: auto
int ITc_inm_connection_refresh_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_refresh(hProfile);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_refresh", InmGetError(nRet), inm_connection_destroy(&hProfile));

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_connection_set_unset_state_changed_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset state-changed callback
* @scenario			State-changed callback is set and then unset
* @apicovered			inm_connection_set_state_changed_cb, inm_connection_unset_state_changed_cb
* @passcase			When inm_connection_set_state_changed_cb, inm_connection_unset_state_changed_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of state-changed callbacks
//& type: auto
int ITc_inm_connection_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;
	inm_connection_h hProfile = NULL;

	nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	PRINT_RESULT(nRet, INM_ERROR_NONE, "InmGetAnyProfile", InmGetError(nRet));
	CHECK_HANDLE(hProfile, "InmGetAnyProfile");

	nRet = inm_connection_set_state_changed_cb(hProfile, InmConnectionStateChangedCallback, NULL);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_set_state_changed_cb", InmGetError(nRet), inm_connection_destroy(&hProfile));

	nRet = inm_connection_unset_state_changed_cb(hProfile);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_unset_state_changed_cb", InmGetError(nRet), inm_connection_destroy(&hProfile));

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_set_unset_scan_state_changed_cb
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Set and unset scan state-changed callback
* @scenario			Scan state-changed callback is set and then unset
* @apicovered			inm_wifi_set_scan_state_changed_cb, inm_wifi_unset_scan_state_changed_cb
* @passcase			When inm_wifi_set_scan_state_changed_cb, inm_wifi_unset_scan_state_changed_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test setting and unsetting of scan state-changed callbacks
//& type: auto
int ITc_inm_wifi_set_unset_scan_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_set_scan_state_changed_cb(g_hInm, InmWifiScanStateChangedCallback, NULL);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_set_scan_state_changed_cb", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_set_scan_state_changed_cb", InmGetError(nRet));

	nRet = inm_wifi_unset_scan_state_changed_cb(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_unset_scan_state_changed_cb", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_get_scan_state
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets the scan state
* @scenario			Connection scan state is gotten
* @apicovered			inm_wifi_get_scan_state
* @passcase			When inm_wifi_get_scan_state is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connection scan state
//& type: auto
int ITc_inm_wifi_get_scan_state_p(void)
{
	START_TEST;

	inm_wifi_scan_state_e eScanState;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_get_scan_state(g_hInm, &eScanState);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_get_scan_state", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_get_scan_state", InmGetError(nRet));
	if(eScanState < INM_WIFI_SCAN_STATE_NOT_SCANNING || eScanState > INM_WIFI_SCAN_STATE_SCANNING)
	{
		FPRINTF("[Line : %d][%s] %s failed. ScanState value = %d\\n", __LINE__, API_NAMESPACE, "inm_wifi_get_scan_state", eScanState);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_get_connected_ap
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets connected wifi ap
* @scenario			Connected wifi ap is gotten
* @apicovered			inm_wifi_get_connected_ap
* @passcase			When inm_wifi_get_connected_ap are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get connected wifi ap
//& type: auto
int ITc_inm_wifi_get_connected_ap_p(void)
{
	START_TEST;

	inm_connection_h hAP = NULL;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_get_connected_ap(g_hInm, &hAP);
	if (!g_bFeatureWifi) {
		if(hAP != NULL)
			inm_connection_destroy(&hAP);
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_get_connected_ap", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_get_connected_ap", InmGetError(nRet));
	CHECK_HANDLE(hAP, "inm_wifi_get_connected_ap");

	nRet = inm_connection_destroy(&hAP);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_foreach_found_ap
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Finds ap for each wifi connection
* @scenario			AP for each wifi connection is gotten
* @apicovered			inm_wifi_foreach_found_ap
* @passcase			When inm_wifi_foreach_found_ap is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get ap for each wifi connection
//& type: auto
int ITc_inm_wifi_foreach_found_ap_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_foreach_found_ap(g_hInm, InmForeachFoundApCallback, NULL);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_foreach_found_ap", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_foreach_found_ap", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_essid
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets essid for wifi ap
* @scenario			Essid for wifi ap is gotten
* @apicovered			inm_wifi_ap_get_essid
* @passcase			When inm_wifi_ap_get_essid is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get essid for wifi ap
//& type: auto
int ITc_inm_wifi_ap_get_essid_p(void)
{
	START_TEST;

	char *pszEssid = NULL;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_get_essid(g_hConnection, &pszEssid);
	if (!g_bFeatureWifi) {
		FREE_MEMORY_TC(pszEssid);
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_essid", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_essid", InmGetError(nRet));
	CHECK_HANDLE(pszEssid, "inm_wifi_ap_get_essid");

	FREE_MEMORY_TC(pszEssid);
	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_raw_ssid
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets raw ssid for wifi ap
* @scenario			Raw SSID for wifi ap is gotten
* @apicovered			inm_wifi_ap_get_raw_ssid
* @passcase			When inm_wifi_ap_get_raw_ssid is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get raw ssid for wifi ap
//& type: auto
int ITc_inm_wifi_ap_get_raw_ssid_p(void)
{
	START_TEST;

	char *pszRawSsid = NULL;
	int nRawSsidLen;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_get_raw_ssid(g_hConnection, &pszRawSsid, &nRawSsidLen);
	if (!g_bFeatureWifi) {
		FREE_MEMORY_TC(pszRawSsid);
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_raw_ssid", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_raw_ssid", InmGetError(nRet), FREE_MEMORY_TC(pszRawSsid));
	CHECK_HANDLE_CLEANUP(pszRawSsid, "inm_wifi_ap_get_raw_ssid", FREE_MEMORY_TC(pszRawSsid));
	FREE_MEMORY_TC(pszRawSsid);

	if(nRawSsidLen < 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. RawSsid Length = %d\\n", __LINE__, API_NAMESPACE, "inm_wifi_ap_get_raw_ssid", nRawSsidLen);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_bssid
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets bssid for wifi ap
* @scenario			BSSID for wifi ap is gotten
* @apicovered			inm_wifi_ap_get_bssid
* @passcase			When inm_wifi_ap_get_bssid is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get bssid for wifi ap
//& type: auto
int ITc_inm_wifi_ap_get_bssid_p(void)
{
	START_TEST;

	char *pszBssid = NULL;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_get_bssid(g_hConnection, &pszBssid);
	if (!g_bFeatureWifi) {
		FREE_MEMORY_TC(pszBssid);
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_bssid", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_bssid", InmGetError(nRet), FREE_MEMORY_TC(pszBssid));
	CHECK_HANDLE_CLEANUP(pszBssid, "inm_wifi_ap_get_bssid", FREE_MEMORY_TC(pszBssid));

	FREE_MEMORY_TC(pszBssid);

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_rssi
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets RSSI for wifi ap
* @scenario			RSSI for wifi ap is gotten
* @apicovered			inm_wifi_ap_get_rssi
* @passcase			When inm_wifi_ap_get_rssi is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get RSSI for wifi ap
//& type: auto
int ITc_inm_wifi_ap_get_rssi_p(void)
{
	START_TEST;

	int nRssi = 1;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_get_rssi(g_hConnection, &nRssi);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_rssi", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_rssi", InmGetError(nRet));
	if(nRssi >= 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. Rssi Length = %d\\n", __LINE__, API_NAMESPACE, "inm_wifi_ap_get_raw_ssid", nRssi);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_rssi_level
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Get RSSI level for wifi ap
* @scenario			RSSI level for wifi ap is gotten
* @apicovered			inm_wifi_ap_get_rssi_level
* @passcase			When inm_wifi_ap_get_rssi_level is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get RSSI level for wifi ap
//& type: auto
int ITc_inm_wifi_ap_get_rssi_level_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;
	inm_wifi_rssi_level_e eRssiLevel;

	nRet = inm_wifi_ap_get_rssi_level(g_hConnection, &eRssiLevel);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_rssi_level", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_rssi_level", InmGetError(nRet));
	if(eRssiLevel < INM_WIFI_RSSI_LEVEL_0 || eRssiLevel > INM_WIFI_RSSI_LEVEL_4)
	{
		FPRINTF("[Line : %d][%s] %s failed. Rssi Level = %d\\n", __LINE__, API_NAMESPACE, "inm_wifi_ap_get_rssi_level", eRssiLevel);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_frequency
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets frequency of wifi ap
* @scenario			Frequency of wifi ap is gotten
* @apicovered			inm_set_ethernet_cable_state_changed_cb, inm_unset_ethernet_cable_state_changed_cb
* @passcase			When inm_set_ethernet_cable_state_changed_cb, inm_unset_ethernet_cable_state_changed_cb are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get frequency of wifi ap
//& type: auto
int ITc_inm_wifi_ap_get_frequency_p(void)
{
	START_TEST;

	int nFrequency = -1;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_get_frequency(g_hConnection, &nFrequency);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_frequency", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_frequency", InmGetError(nRet));

	if(nFrequency < 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. Frequency = %d\\n", __LINE__, API_NAMESPACE, "inm_wifi_ap_get_frequency", nFrequency);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_max_speed
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets max speed for wifi ap
* @scenario			Max speed for wifi ap is gotten
* @apicovered			inm_wifi_ap_get_max_speed
* @passcase			When inm_wifi_ap_get_max_speed is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get max speed for wifi sp
//& type: auto
int ITc_inm_wifi_ap_get_max_speed_p(void)
{
	START_TEST;

	int nSpeed = -1;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_get_max_speed(g_hConnection, &nSpeed);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_max_speed", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_max_speed", InmGetError(nRet));

	if(nSpeed < 0)
	{
		FPRINTF("[Line : %d][%s] %s failed. Speed = %d\\n", __LINE__, API_NAMESPACE, "inm_wifi_ap_get_max_speed", nSpeed);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_is_favorite
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Checks whether wifi ap is favourite or not
* @scenario			Wifi ap is checked for favourites
* @apicovered			inm_wifi_ap_is_favorite
* @passcase			When inm_wifi_ap_is_favorite is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to check if wifi ap is favourite or not
//& type: auto
int ITc_inm_wifi_ap_is_favorite_p(void)
{
	START_TEST;

	bool bFavorite = false;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_is_favorite(g_hConnection, &bFavorite);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_is_favorite", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_is_favorite", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_is_passpoint
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Checks whether wifi ap is passpoint or not
* @scenario			Wifi ap is checked for passpoint
* @apicovered			inm_wifi_ap_is_passpoint
* @passcase			When inm_wifi_ap_is_passpoint is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to check whether wifi ap is a passpoint or not
//& type: auto
int ITc_inm_wifi_ap_is_passpoint_p(void)
{
	START_TEST;

	bool bPasspoint = false;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_is_passpoint(g_hConnection, &bPasspoint);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_is_passpoint", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_is_passpoint", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_security_type
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets security type for wifi ap
* @scenario			Security type for wifi ap is gotten
* @apicovered			inm_wifi_ap_get_security_type
* @passcase			When inm_wifi_ap_get_security_type are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get security type of wifi ap
//& type: auto
int ITc_inm_wifi_ap_get_security_type_p(void)
{
	START_TEST;

	inm_wifi_security_type_e eWifiSecurityType;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_get_security_type(g_hConnection, &eWifiSecurityType);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_security_type", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_security_type", InmGetError(nRet));
	if(eWifiSecurityType < INM_WIFI_SECURITY_TYPE_NONE || eWifiSecurityType > INM_WIFI_SECURITY_TYPE_FT_PSK)
	{
		FPRINTF("[Line : %d][%s] %s failed. WifiSecurityType value = %d\\n", __LINE__, API_NAMESPACE, "inm_wifi_ap_get_rssi_level", eWifiSecurityType);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_encryption_type
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets encryption type for wifi ap
* @scenario			Encryption type for wifi ap is gotten
* @apicovered			inm_wifi_ap_get_encryption_type
* @passcase			When inm_wifi_ap_get_encryption_type is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get encryption type of wifi ap
//& type: auto
int ITc_inm_wifi_ap_get_encryption_type_p(void)
{
	START_TEST;

	inm_wifi_encryption_type_e eWifiEncryptionType;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_get_encryption_type(g_hConnection, &eWifiEncryptionType);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_encryption_type", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_encryption_type", InmGetError(nRet));
	if(eWifiEncryptionType < INM_WIFI_ENCRYPTION_TYPE_NONE || eWifiEncryptionType > INM_WIFI_ENCRYPTION_TYPE_TKIP_AES_MIXED)
	{
		FPRINTF("[Line : %d][%s] %s failed. WifiEncryptionType value = %d\\n", __LINE__, API_NAMESPACE, "inm_wifi_ap_get_rssi_level", eWifiEncryptionType);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_is_passphrase_required
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Checks whether passphrase is required for wifi ap
* @scenario			Wifi ap is checked for passphrase requirement
* @apicovered			inm_wifi_ap_is_passphrase_required
* @passcase			When inm_wifi_ap_is_passphrase_required is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to check if passphrase is required for wifi ap
//& type: auto
int ITc_inm_wifi_ap_is_passphrase_required_p(void)
{
	START_TEST;

	bool bRequired;
	int nRet = INM_ERROR_NONE;
	inm_wifi_security_type_e eWifiSecurityType;

	nRet = inm_wifi_ap_get_security_type(g_hConnection, &eWifiSecurityType);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_security_type", InmGetError(nRet));
		return 0;
	}

	if(eWifiSecurityType != INM_WIFI_SECURITY_TYPE_EAP)
	{
		nRet = inm_wifi_ap_is_passphrase_required(g_hConnection, &bRequired);
		PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_is_passphrase_required", InmGetError(nRet));
	}
	else
	{
		 FPRINTF("[Line : %d][%s] API \"%s\" cannot be checked. Wifi Security Type = INM_WIFI_SECURITY_TYPE_EAP\\n", __LINE__, API_NAMESPACE, "inm_wifi_ap_is_passphrase_required");
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_is_wps_supported
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Checks whether wps is supported by wifi ap
* @scenario			Wifi ap is checked for wps support
* @apicovered			inm_wifi_ap_is_wps_supported
* @passcase			When inm_wifi_ap_is_wps_supported are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to check whether wps is supported by wifi ap
//& type: auto
int ITc_inm_wifi_ap_is_wps_supported_p(void)
{
	START_TEST;

	bool bSupported;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_is_wps_supported(g_hConnection, &bSupported);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_is_wps_supported", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_is_wps_supported", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_disconnect_reason
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets reason for wifi disconnect
* @scenario			Reason for wifi disconnect is gottens
* @apicovered			inm_wifi_ap_get_disconnect_reason
* @passcase			When inm_wifi_ap_get_disconnect_reason are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get wifi disconnect reason
//& type: auto
int ITc_inm_wifi_ap_get_disconnect_reason_p(void)
{
	START_TEST;

	inm_wifi_disconnect_reason_e eDisconnectReason = 1;
	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_get_disconnect_reason(g_hConnection, &eDisconnectReason);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_disconnect_reason", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_disconnect_reason", InmGetError(nRet));
	if(InmGetDisconnectReason(eDisconnectReason) == NULL)
	{
		FPRINTF("[Line : %d][%s] %s failed. Disconnect reason = %d\\n", __LINE__, API_NAMESPACE, "inm_wifi_ap_get_disconnect_reason", eDisconnectReason);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_get_assoc_status_code
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets assoc status code for wifi ap
* @scenario			Assoc status code for wifi ap is gotten
* @apicovered			inm_wifi_ap_get_assoc_status_code
* @passcase			When inm_wifi_ap_get_assoc_status_code are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to get assoc status code for wifi ap
//& type: auto
int ITc_inm_wifi_ap_get_assoc_status_code_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;
	inm_wifi_assoc_status_code_e eStatusCode;

	nRet = inm_wifi_ap_get_assoc_status_code(g_hConnection, &eStatusCode);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_get_assoc_status_code", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_get_assoc_status_code", InmGetError(nRet));
	if(eStatusCode < INM_WLAN_STATUS_SUCCESS || eStatusCode > INM_WLAN_STATUS_ASSOC_DENIED_NO_VHT)
	{
		FPRINTF("[Line : %d][%s] %s failed. StatusCode value = %d\\n", __LINE__, API_NAMESPACE, "inm_wifi_ap_get_rssi_level", eStatusCode);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_wifi_ap_foreach_vsie
* @since_tizen			5.0
* @author        		SRID(samuel.peter)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Checks wifi ap for each vsie
* @scenario			Wifi ap is checked for each vsie
* @apicovered			inm_wifi_ap_foreach_vsie
* @passcase			When inm_wifi_ap_foreach_vsie is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to check wifi ap for each vsie
//& type: auto
int ITc_inm_wifi_ap_foreach_vsie_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_wifi_ap_foreach_vsie(g_hConnection, InmWifiApForeachVsieCallback, NULL);
	if (!g_bFeatureWifi) {
		PRINT_RESULT_CHECK(nRet, INM_ERROR_NOT_SUPPORTED, "inm_wifi_ap_foreach_vsie", InmGetError(nRet));
		return 0;
	}
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_wifi_ap_foreach_vsie", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_refresh_links_p
* @since_tizen			5.5
* @author        		SRID(karanam.s)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Refreshes link information held by a handle.
* @scenario			Refreshes link information held by a handle.
* @apicovered			inm_refresh_links
* @passcase			When inm_refresh_links is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Refreshes link information held by a handle.
//& type: auto
int ITc_inm_refresh_links_p(void)
{
	START_TEST;

	int nRet = INM_ERROR_NONE;

	nRet = inm_refresh_links(g_hInm);	//target API
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_refresh_links", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_arp_request_set_get_packet_interval_p
* @since_tizen			5.5
* @author        		SRID(karanam.s)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Sets and gets the ARP packet interval which is used to find targets IP on local network.
* @scenario			Sets and gets the ARP packet interval which is used to find targets IP on local network.
* @apicovered			inm_arp_request_set_packet_interval, inm_arp_request_get_packet_interval
* @passcase			When inm_arp_request_set_packet_interval and inm_arp_request_get_packet_interval is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Sets and gets the ARP packet interval which is used to find targets IP on local network.
//& type: auto
int ITc_inm_arp_request_set_get_packet_interval_p(void)
{
	START_TEST;

	int nSetInterval = ARP_REQUEST_PACKET_INTERVAL;
	int nGetInterval = -1;

	int nRet = inm_arp_request_set_packet_interval(g_hInm, nSetInterval);	//target API
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_arp_request_set_packet_interval", InmGetError(nRet));

	nRet = inm_arp_request_get_packet_interval(g_hInm, &nGetInterval);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_arp_request_get_packet_interval", InmGetError(nRet));
	if(nGetInterval != nSetInterval) {
		FPRINTF("[Line : %d][%s] SetInterval %d not equal to GetInterval %d.\\n", __LINE__, API_NAMESPACE, nSetInterval, nGetInterval);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_arp_request_start_stop_p
* @since_tizen			5.5
* @author        		SRID(karanam.s)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Starts and stops sending ARP packets to find a target_ip.
* @scenario			Starts and stops sending ARP packets to find a target_ip.
* @apicovered			inm_arp_request_start, inm_arp_request_stop
* @passcase			When inm_arp_request_start and inm_arp_request_stop is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Starts and stops sending ARP packets to find a target_ip.
//& type: auto

int ITc_inm_arp_request_start_stop_p(void)
{
	START_TEST;

	inm_connection_h hProfile = NULL;
	g_bArpRequestedIpFound = false;
	g_pszArpRequestedIpStr = NULL;

	int nRet = InmGetAnyProfile(&hProfile);
        if(nRet == FEATURE_NOT_SUPPORTED)
                return 0;

	nRet = inm_connection_get_gateway_address(hProfile, INM_ADDRESS_FAMILY_IPV4, &g_pszArpRequestedIpStr);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_connection_get_gateway_address", InmGetError(nRet), inm_connection_destroy(&hProfile));
	CHECK_HANDLE_CLEANUP(g_pszArpRequestedIpStr, "inm_connection_get_gateway_address", inm_connection_destroy(&hProfile));

	nRet = inm_arp_request_start(g_hInm, g_pszArpRequestedIpStr, InmArpRequestIpFoundCallback, NULL);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_arp_request_start", InmGetError(nRet), inm_connection_destroy(&hProfile);FREE_MEMORY_TC(g_pszArpRequestedIpStr));

	RUN_POLLING_LOOP;

	nRet = inm_arp_request_stop(g_hInm, g_pszArpRequestedIpStr);
	PRINT_RESULT_CLEANUP(nRet, INM_ERROR_NONE, "inm_arp_request_stop", InmGetError(nRet), inm_connection_destroy(&hProfile);FREE_MEMORY_TC(g_pszArpRequestedIpStr));

	nRet = inm_connection_destroy(&hProfile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_connection_destroy", InmGetError(nRet));

	FREE_MEMORY_TC(g_pszArpRequestedIpStr);

	if (!g_bArpRequestedIpFound) {
		FPRINTF("[Line : %d][%s] ARP requested IP not found\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_default_gateway_start_stop_checking_p
* @since_tizen			5.5
* @author        		SRID(karanam.s)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Starts and stops to send ARP packets to find gateway during timeout, in seconds.
* @scenario			Starts and stops to send ARP packets to find gateway during timeout, in seconds.
* @apicovered			inm_default_gateway_start_checking, inm_default_gateway_stop_checking
* @passcase			When inm_default_gateway_start_checking and inm_default_gateway_stop_checking is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Starts and stops to send ARP packets to find gateway during timeout, in seconds.
//& type: auto
int ITc_inm_default_gateway_start_stop_checking_p(void)
{
	START_TEST;

	g_bGatewayFound = false;
	int nRet = inm_default_gateway_start_checking(g_hInm, 0, InmDefaultGatewayFoundCallback, NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_default_gateway_start_checking", InmGetError(nRet));

	RUN_POLLING_LOOP;

	nRet = inm_default_gateway_stop_checking(g_hInm);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_default_gateway_stop_checking", InmGetError(nRet));

	if (!g_bGatewayFound) {
		FPRINTF("[Line : %d][%s] Gateway IP not found\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_default_dns_lookup_check_p
* @since_tizen			5.5
* @author        		SRID(karanam.s)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Checks DNS lookup of the target to check whether DNS server is valid or not.
* @scenario			Checks DNS lookup of the target to check whether DNS server is valid or not.
* @apicovered			inm_default_dns_lookup_check
* @passcase			When inm_default_dns_lookup_check is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Checks DNS lookup of the target to check whether DNS server is valid or not.
//& type: auto
int ITc_inm_default_dns_lookup_check_p(void)
{
	START_TEST;

	g_bDnsLookupFinished = false;
	int nRet = inm_default_dns_lookup_check(g_hInm, InmDefaultDnsLookupResultCallback, NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_default_dns_lookup_check", InmGetError(nRet));

	RUN_POLLING_LOOP;

	if (!g_bDnsLookupFinished) {
		FPRINTF("[Line : %d][%s] DNS lookup is not finished\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_inm_reachable_urls_add_remove_url_to_check_p
* @since_tizen			5.5
* @author        		SRID(karanam.s)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Adds URL to check reachability by inm_start_checking_reachable_urls
* @scenario			Adds URL to check reachability by inm_start_checking_reachable_urls
* @apicovered			inm_reachable_urls_add_url_to_check, inm_reachable_urls_remove_url_to_check
* @passcase			When inm_reachable_urls_add_url_to_check and inm_reachable_urls_remove_url_to_check is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Adds URL to check reachability by inm_start_checking_reachable_urls
//& type: auto
int ITc_inm_reachable_urls_add_remove_url_to_check_p(void)
{
	START_TEST;

	int nRet = inm_reachable_urls_add_url_to_check(g_hInm, REACHABILITY_TEST_URL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_reachable_urls_add_url_to_check", InmGetError(nRet));

	nRet = inm_reachable_urls_remove_url_to_check(g_hInm, REACHABILITY_TEST_URL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_reachable_urls_remove_url_to_check", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_reachable_urls_start_stop_checking_p
* @since_tizen			5.5
* @author        		SRID(karanam.s)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Starts to send HTTP GET requests with curl to check reachability of URLs of the given type and stops.
* @scenario			This function just checks if URLs in the list can be reachable once. If you want to check again, you need to call this function 				again with the target URL list.
* @apicovered			inm_reachable_urls_start_checking, inm_reachable_urls_stop_checking
* @passcase			When inm_reachable_urls_start_checking and inm_reachable_urls_stop_checking is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Starts to send HTTP GET requests with curl to check reachability of URLs of the given type and stops.
//& type: auto
int ITc_inm_reachable_urls_start_stop_checking_p(void)
{
	START_TEST;

	g_bDefaultUrlFound = false;

	int nRet = inm_reachable_urls_start_checking(g_hInm, INM_URL_LIST_TYPE_DEFAULT, InmReachableUrlsCheckResultDefaultCallback, NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_reachable_urls_start_checking", InmGetError(nRet));

	RUN_POLLING_LOOP;

	if (!g_bDefaultUrlFound) {
		FPRINTF("[Line : %d][%s] Default URL is not reachable\\n", __LINE__, API_NAMESPACE);
		inm_reachable_urls_stop_checking(g_hInm, INM_URL_LIST_TYPE_DEFAULT);
		return 1;
	}

	nRet = inm_reachable_urls_stop_checking(g_hInm, INM_URL_LIST_TYPE_DEFAULT);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_reachable_urls_stop_checking", InmGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_inm_reachable_urls_is_check_running_p
* @since_tizen			5.5
* @author        		SRID(karanam.s)
* @reviewer     		SRID(manoj.g2)
* @type 			auto
* @description			Gets whether the reachable URLs check is running or not.
* @scenario			Gets whether the reachable URLs check is running or not.
* @apicovered			inm_reachable_urls_is_check_running
* @passcase			When inm_reachable_urls_is_check_running is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Gets whether the reachable URLs check is running or not.
//& type: auto
int ITc_inm_reachable_urls_is_check_running_p(void)
{
	START_TEST;

	bool bIsRunning = FALSE;
	int nRet = inm_reachable_urls_start_checking(g_hInm, INM_URL_LIST_TYPE_DEFAULT, InmReachableUrlsCheckResultDefaultCallback, NULL);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_reachable_urls_start_checking", InmGetError(nRet));

	RUN_POLLING_LOOP;

	nRet = inm_reachable_urls_is_check_running(g_hInm, INM_URL_LIST_TYPE_DEFAULT, &bIsRunning);
	PRINT_RESULT(nRet, INM_ERROR_NONE, "inm_reachable_urls_is_check_running", InmGetError(nRet));
	if (!bIsRunning) {
		FPRINTF("[Line : %d][%s] Url reachability is not running\\n", __LINE__, API_NAMESPACE);
		inm_reachable_urls_stop_checking(g_hInm, INM_URL_LIST_TYPE_DEFAULT);
		return 1;
	}

	nRet = inm_reachable_urls_stop_checking(g_hInm, INM_URL_LIST_TYPE_DEFAULT);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_reachable_urls_stop_checking", InmGetError(nRet));

	return 0;
}

/** @} */
/** @} */
