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
#include "ITs-wifi-direct-common.h"

//& set: WifiDirect

/** @addtogroup itc-wifi-direct
*  @ingroup itc
*  @{
*/

static bool g_bWifi_direct_service_state_changed_callback_invoked = false;
static bool g_bWifi_direct_discovery_state_changed_callback_invoked = false;
static bool g_bWifi_direct_device_state_changed_callback_invoked = false;
static bool g_bWifi_direct_state_changed_callback_invoked = false;
static bool g_bWifi_direct_peer_found_callback_invoked = false;
static bool g_bWifi_direct_client_ip_address_assigned_callback_invoked = false;
static bool g_bWifi_direct_connection_state_changed_callback_invoked = false;
static bool g_bWifi_direct_GetPeer = false;
static bool g_bWifi_callback_invoked = false;
static char g_szSSID[ARRAY_SIZE] = {0};
static char g_szMacAdd[ARRAY_SIZE] = {0};
static bool g_bCallbackResult = false;

static bool g_bReadFeatureStatusDone = false;

wifi_direct_discovery_state_e g_discovery_state = WIFI_DIRECT_ONLY_LISTEN_STARTED;
wifi_direct_service_discovery_state_e g_service_discovery_state = WIFI_DIRECT_SERVICE_DISCOVERY_FINISHED;
wifi_direct_device_state_e g_device_state = WIFI_DIRECT_DEVICE_STATE_DEACTIVATED;
wifi_direct_state_e g_state = WIFI_DIRECT_STATE_DEACTIVATED;
wifi_direct_connection_state_e g_connection_state = WIFI_DIRECT_CONNECTION_REQ;

/**
* @function 		wifi_direct_service_state_changed_callback
* @description	 	Callback function to indicate change in service state
* @parameter		int error_code - error value, wifi_direct_service_discovery_state_e device_state - Current state, wifi_direct_service_type_e service_type - Service type, void* response_data - response received, const char* mac_address - Mac address, void* user_data - User data
* @return 			NA
*/
void wifi_direct_service_state_changed_callback(int error_code, wifi_direct_service_discovery_state_e service_state, wifi_direct_service_type_e service_type, void* response_data, const char* mac_address, void* user_data)
{
	FPRINTF("[Line : %d][%s] wifi_direct_service_state_changed_callback is invoked; error_code = %d, service_state = %d, service_type = %d, mac_address = %s\\n", __LINE__, API_NAMESPACE, error_code, service_state, service_type, mac_address);
	g_bWifi_direct_service_state_changed_callback_invoked = true;
	g_service_discovery_state = service_state;
	g_bCallbackResult = true;
	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		wifi_direct_discovery_state_changed_callback
* @description	 	Callback function to indicate change in discovery state
* @parameter		int error_code - error value, wifi_direct_discovery_state_e discovery_state - Current state, void* user_data - user data passed
* @return 			NA
*/
void wifi_direct_discovery_state_changed_callback(int error_code, wifi_direct_discovery_state_e discovery_state, void* user_data)
{
	FPRINTF("[Line : %d][%s] wifi_direct_discovery_state_changed_callback invoked; error_code = %d, discovery_state = %d\\n", __LINE__, API_NAMESPACE, error_code, discovery_state);
	g_bWifi_direct_discovery_state_changed_callback_invoked = true;
	g_discovery_state = discovery_state;
	g_bCallbackResult = true;
	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		wifi_direct_device_state_changed_callback
* @description	 	Callback function to indicate change in device state
* @parameter		int error_code - error value, wifi_direct_device_state_e device_state - Current state, void* user_data - user data passed
* @return 			NA
*/
void wifi_direct_device_state_changed_callback(int error_code, wifi_direct_device_state_e device_state, void* user_data)
{
	FPRINTF("[Line : %d][%s] wifi_direct_device_state_changed_callback invoked; error_code = %d, device_state = %d\\n", __LINE__, API_NAMESPACE, error_code, device_state);
	g_bWifi_direct_device_state_changed_callback_invoked = true;
	g_bCallbackResult = true;
	g_device_state = device_state;

	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		wifi_direct_peer_found_callback
* @description	 	Callback function to indicate peer found
* @parameter		int error_code - error value, wifi_direct_discovery_state_e device_state - Current state, const char* mac_address - mac address, void* user_data - user data passed
* @return 			NA
*/
void wifi_direct_peer_found_callback(int error_code, wifi_direct_discovery_state_e discovery_state, const char* mac_address, void* user_data)
{
	FPRINTF("[Line : %d][%s] wifi_direct_peer_found_callback invoked; error_code = %d, discovery_state = %d, mac_address = %s\\n", __LINE__, API_NAMESPACE, error_code, discovery_state, mac_address);
	g_bWifi_direct_peer_found_callback_invoked = true;

	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		wifi_direct_peer_found_callback_GetPeer
* @description	 	Callback function to indicate peer found and find peer
* @parameter		int error_code - error value, wifi_direct_discovery_state_e device_state - Current state, const char* mac_address - mac address, void* user_data - user data passed
* @return 			NA
*/
void wifi_direct_peer_found_callback_GetPeer(int error_code, wifi_direct_discovery_state_e discovery_state, const char* mac_address, void* user_data)
{
	FPRINTF("[Line : %d][%s] wifi_direct_peer_found_callback_GetPeer invoked; error_code = %d, discovery_state = %d, mac_address = %s\\n", __LINE__, API_NAMESPACE, error_code, discovery_state, mac_address);

	char* pMacAddr = (char*)user_data;
	if ( (NULL == pMacAddr) || (NULL == mac_address))
	{
		FPRINTF("[Line : %d][%s] wifi_direct_peer_found_callback_GetPeer invoked but with NULL user_data/mac_address\\n", __LINE__, API_NAMESPACE);
		return;
	}

	if ( (discovery_state == WIFI_DIRECT_DISCOVERY_FOUND) && (0 == strcmp(pMacAddr, mac_address)))
	{
		g_bWifi_direct_GetPeer = true;

		if ( g_pMainLoop != NULL )
		{
			g_main_loop_quit(g_pMainLoop);
			g_main_loop_unref(g_pMainLoop);
			g_pMainLoop = NULL;
		}
	}
}

/**
* @function 		wifi_direct_client_ip_address_assigned_callback
* @description	 	Callback function to indicate ip address assigned
* @parameter		const char *mac_address, const char *ip_address, const char *interface_address, void *user_data
* @return 			NA
*/
void wifi_direct_client_ip_address_assigned_callback(const char *mac_address, const char *ip_address, const char *interface_address, void *user_data)
{
	FPRINTF("[Line : %d][%s] wifi_direct_client_ip_address_assigned_callback invoked; mac_address = %s, ip_address = %s, interface_address = %s\\n", __LINE__, API_NAMESPACE, mac_address, ip_address, interface_address);
	g_bWifi_direct_client_ip_address_assigned_callback_invoked = true;

	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		wifi_direct_connection_state_changed_callback
* @description	 	Callback function to indicate change in device state
* @parameter		int error_code - error value, wifi_direct_connection_state_e connection_state - Current state, const char *mac_address - Mac address, void* response_data - Response received
* @return 			NA
*/
void wifi_direct_connection_state_changed_callback(int error_code, wifi_direct_connection_state_e connection_state, const char *mac_address, void* response_data)
{
	FPRINTF("[Line : %d][%s] wifi_direct_connection_state_changed_callback invoked; error_code = %d, connection_state = %d, mac_address = %s\\n", __LINE__, API_NAMESPACE, error_code, connection_state, mac_address);
	g_bWifi_direct_connection_state_changed_callback_invoked = true;
	g_bCallbackResult = true;

	g_connection_state = connection_state;
	if ( mac_address != NULL )
	{
		strncpy(g_szMacAdd, mac_address, strlen(mac_address)+1);
	}

	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function             WifiDirectPeerInfoConnectionStateChangedCb
* @description          Callback function to indicate change in peer connection state
* @parameter            wifi_direct_error_e error_code, wifi_direct_connection_state_e connection_state, wifi_direct_connection_state_cb_data_s data_s, void *user_data
* @return               NA
*/

static void WifiDirectPeerInfoConnectionStateChangedCb(wifi_direct_error_e error_code, wifi_direct_connection_state_e connection_state, wifi_direct_connection_state_cb_data_s data_s, void *user_data)
{
        FPRINTF("[Line : %d][%s] WifiDirectPeerInfoConnectionStateChangedCb invoked; error_code = %d, connection_state = %d %s\\n", __LINE__, API_NAMESPACE, error_code, connection_state);
}

/**
* @function 		WifiDirectPersistentGroupCb
* @description	 	callback function to terminate g_main loop
* @parameter		wifi_direct_wps_type_e type : wps type,
*					void *user_datadata : user data sent to callback
* @return 			true for next iteration, false otherwise
*/
static bool WifiDirectSupportedWpsTypeCb(wifi_direct_wps_type_e type, void *user_data)
{
	FPRINTF("[Line : %d][%s] Supported wifi_direct_wps_type_e type = %d,\\n", __LINE__, API_NAMESPACE, (int) type);
	g_bWifi_callback_invoked = true;

	if ( user_data != NULL )
	{
		*( (wifi_direct_wps_type_e *)user_data) = type;
	}
	return true;
}

/**
* @function 		WifiDirectPersistentGroupCb
* @description	 	callback function to terminate g_main loop
* @parameter		const char *mac_address : Mac address,
*					const char *ssid : SSID
*					void *user_datadata : user data sent to callback
* @return 			true for next iteration, false otherwise
*/
static bool WifiDirectPersistentGroupCb(const char *mac_address, const char *ssid, void *user_data)
{
	FPRINTF("[Line : %d][%s] persistent group mac address = %s, ssid = %s\\n", __LINE__, API_NAMESPACE, mac_address, ssid);
	g_bWifi_callback_invoked = true;
	if ( mac_address != NULL )
	{
		if (strcmp(mac_address, g_szMacAdd) == 0)
		{
			if ( ssid != NULL )
			{
				strncpy(g_szSSID, ssid, strlen(ssid)+1);
				*((bool *)user_data) = true;	// the one which will be removed is found
			}
			return false;
		}
	}

	return true;
}


/**
* @function 		WifiDirectDiscoveredPeerCb
* @description	 	callback function to terminate g_main loop when peer discovered
* @parameter		wifi_direct_discovered_peer_info_s *peer - information of peer
*					void *user_datadata : user data sent to callback
* @return 			true for next iteration, false otherwise
*/
static bool WifiDirectDiscoveredPeerCb(wifi_direct_discovered_peer_info_s *peer, void *user_data)
{
	FPRINTF("[Line : %d][%s]WifiDirectDiscoveredPeerCb invoked\\n", __LINE__, API_NAMESPACE);
	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}

	return false;
}
/**
* @function 		wifi_direct_state_changed_callback
* @description	 	Callback function to indicate change in device state
* @parameter		wifi_direct_state_e state - Current state, void* user_data - user data passed
* @return 			NA
*/
void wifi_direct_state_changed_callback(wifi_direct_state_e state, void* user_data)
{
	FPRINTF("[Line : %d][%s] wifi_direct_device_state_changed_callback invoked; state = %d\\n", __LINE__, API_NAMESPACE, state);
	g_bWifi_direct_state_changed_callback_invoked = true;
	g_bCallbackResult = true;
	g_state = state;

	if ( g_pMainLoop != NULL )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		ITs_wifi_direct_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_wifi_direct_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Wifi_Direct_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( false == g_bReadFeatureStatusDone )
	{
		g_bFeatureWifiDirect = TCTCheckSystemInfoFeatureSupported(FEATURE_WIFI_DIRECT, API_NAMESPACE);
		g_bFeatureWifiDirectDisplay = TCTCheckSystemInfoFeatureSupported(FEATURE_WIFI_DIRECT_DISPLAY, API_NAMESPACE);
		g_bFeatureWifiDirectSrvcDiscovery = TCTCheckSystemInfoFeatureSupported(FEATURE_WIFI_DIRECT_SVC_DISC, API_NAMESPACE);
		g_bReadFeatureStatusDone = true;
	}

	g_bSkipTestCaseWithPass = false;

	sleep(PROCESS_TIME);
}

/**
* @function 		ITs_wifi_direct_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_wifi_direct_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Wifi_Direct_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-wifi-direct-testcases
*  @brief 		Integration testcases for module wifi-direct
*  @ingroup 	itc-wifi-direct
*  @{
*/

//& purpose: Initialises the wifi-direct service
//& type: auto
/**
* @testcase 			ITc_wifi_direct_initialize_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Initialises the wifi-direct service
* @scenario				Initialize wifi-direct\n
*						De initialize wifi-direct
* @apicovered			wifi_direct_initialize, wifi_direct_deinitialize
* @passcase				When wifi_direct_initialize is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_initialize_p(void)
{
	START_TEST;

	//Target API
	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& purpose: De-Initialises the wifi-direct service
//& type: auto
/**
* @testcase 			ITc_wifi_direct_deinitialize_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			De-Initialises the wifi-direct service
* @scenario				Initialize wifi-direct\n
*						De initialize wifi-direct
* @apicovered			wifi_direct_initialize, wifi_direct_deinitialize
* @passcase				When wifi_direct_initialize and wifi_direct_deinitialize is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_deinitialize_p(void)
{
	START_TEST;
	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	//Target API
	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}




//& type: auto
//& purpose: Initialize Wifi-direct display
/**
* @testcase 			ITc_wifi_direct_init_deinit_display_p
* @type 				auto
* @since_tizen			2.4
* @author				SRID(sk.pal)
* @reviewer				SRID(gupta.sanjay)
* @description			Initialize and deinitialize Wifi-direct display
* @scenario				initialize wifi-direct\n
*						Initialize Wifi-direct display\n
*						deinitialize wifi-direct display
* @apicovered			wifi_direct_init_display, wifi_direct_deinit_display
* @passcase				When wifi_direct_init_display and wifi_direct_deinit_display is successful and returns some address
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_init_deinit_display_p(void)
{
	
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	int nRet = wifi_direct_init_display();
	if ( !g_bFeatureWifiDirectDisplay )
        {
                if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
                {
                        FPRINTF("[Line : %d][%s] wifi_direct_init_display returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
                        WifiDirectTerminateService();
                        return 1;
                }
                else
                {
                        FPRINTF("[Line : %d][%s]wifi_direct_init_display API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
                        WifiDirectTerminateService();
                        return 0;
                }
        }
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_init_display", WifiDirectGetError(nRet), WifiDirectTerminateService());
	
	nRet = wifi_direct_deinit_display();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinit_display", WifiDirectGetError(nRet), 	WifiDirectTerminateService());
	WifiDirectTerminateService();
	return 0;
}


//& type: auto
//& purpose: Set and Get Wifi-direct display parameters
/**
* @testcase 			ITc_wifi_direct_set_get_display_p
* @type 				auto
* @since_tizen			5.0
* @author				SRID(j.abhishek)
* @reviewer				SRID(nibha.sharma)
* @description			set and get Wifi-direct display parameters
* @scenario				initialize wifi-direct\n
*						set Wifi-direct display\n
*						get Wifi-direct display parameters\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_display, wifi_direct_get_display
* @passcase				When wifi_direct_set_display and wifi_direct_get_display
*					are successful
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_get_display_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	
	int nRet = wifi_direct_init_display();
	if ( !g_bFeatureWifiDirectDisplay )
        {
                if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
                {
                        FPRINTF("[Line : %d][%s] wifi_direct_init_display returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
                        WifiDirectTerminateService();
                        return 1;
                }
                else
                {
                        FPRINTF("[Line : %d][%s]wifi_direct_init_display API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
                        WifiDirectTerminateService();
                        return 0;
                }
        }
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_init_display", WifiDirectGetError(nRet), WifiDirectTerminateService());

	wifi_direct_display_type_e eDisplayType;
	int nPort = -1;
	int nSetHDCP = 1;
	int nGetHDCP = -1;

	nRet = wifi_direct_set_display(WIFI_DIRECT_DISPLAY_TYPE_SOURCE, WIFI_TYPE_SOURCE, nSetHDCP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_display:WIFI_DIRECT_DISPLAY_TYPE_SOURCE ", WifiDirectGetError(nRet), WifiDirectTerminateService());

	nRet = wifi_direct_get_display(&eDisplayType, &nPort, &nGetHDCP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_display", WifiDirectGetError(nRet), WifiDirectTerminateService());
	if( (eDisplayType != WIFI_DIRECT_DISPLAY_TYPE_SOURCE) || (nPort != WIFI_TYPE_SOURCE) || (nSetHDCP != nGetHDCP) )
	{
		FPRINTF("[Line : %d][%s]wifi_direct_get_display API returned display type or port is not matching\\n", __LINE__, API_NAMESPACE);
		WifiDirectTerminateService();
		return 1;
	}

	nRet = wifi_direct_set_display(WIFI_DIRECT_DISPLAY_TYPE_PRISINK, WIFI_TYPE_PRIMARY_SINK, nSetHDCP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_display :WIFI_DIRECT_DISPLAY_TYPE_PRISINK", WifiDirectGetError(nRet), 	WifiDirectTerminateService());
	
	nRet = wifi_direct_get_display(&eDisplayType, &nPort, &nGetHDCP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_display", WifiDirectGetError(nRet), WifiDirectTerminateService());
	if( (eDisplayType != WIFI_DIRECT_DISPLAY_TYPE_PRISINK) || (nPort != WIFI_TYPE_PRIMARY_SINK) || (nSetHDCP != nGetHDCP) )
	{
		FPRINTF("[Line : %d][%s]wifi_direct_get_display API returned display type or port is not matching\\n", __LINE__, API_NAMESPACE);
		WifiDirectTerminateService();
		return 1;
	}

	nRet = wifi_direct_set_display(WIFI_DIRECT_DISPLAY_TYPE_SECSINK, WIFI_TYPE_SECONDARY_SINK, nSetHDCP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_display:WIFI_DIRECT_DISPLAY_TYPE_SECSINK", WifiDirectGetError(nRet), 	WifiDirectTerminateService());
	
	nRet = wifi_direct_get_display(&eDisplayType, &nPort, &nGetHDCP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_display", WifiDirectGetError(nRet), WifiDirectTerminateService());
	if( (eDisplayType != WIFI_DIRECT_DISPLAY_TYPE_SECSINK) || (nPort != WIFI_TYPE_SECONDARY_SINK) || (nSetHDCP != nGetHDCP) )
	{
		FPRINTF("[Line : %d][%s]wifi_direct_get_display API returned display type or port is not matching\\n", __LINE__, API_NAMESPACE);
		WifiDirectTerminateService();
		return 1;
	}

	nRet = wifi_direct_set_display(WIFI_DIRECT_DISPLAY_TYPE_DUAL, WIFI_TYPE_DUAL_ROLE, nSetHDCP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_display:WIFI_DIRECT_DISPLAY_TYPE_DUAL", WifiDirectGetError(nRet), 	WifiDirectTerminateService());

	nRet = wifi_direct_get_display(&eDisplayType, &nPort, &nGetHDCP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_display", WifiDirectGetError(nRet), WifiDirectTerminateService());
	if( (eDisplayType != WIFI_DIRECT_DISPLAY_TYPE_DUAL) || (nPort != WIFI_TYPE_DUAL_ROLE) || (nSetHDCP != nGetHDCP) )
	{
		FPRINTF("[Line : %d][%s]wifi_direct_get_display API returned display type or port is not matching\\n", __LINE__, API_NAMESPACE);
		WifiDirectTerminateService();
		return 1;
	}

	nRet = wifi_direct_deinit_display();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinit_display", WifiDirectGetError(nRet), 	WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}


//& type: auto
//& purpose: Set and Get Wifi-direct display availability
/**
* @testcase 			ITc_wifi_direct_set_get_display_availability_p
* @type 				auto
* @since_tizen			5.0
* @author				SRID(j.abhishek)
* @reviewer				SRID(nibha.sharma)
* @description			set and get Wifi-direct display availability
* @scenario				initialize wifi-direct\n
*					set Wifi-direct display availability\n
*					get Wifi-direct display availability\n
*					deinitialize wifi-direct
* @apicovered			wifi_direct_set_display_availability, wifi_direct_get_display_availability
*@passcase			When wifi_direct_set_display_availability and wifi_direct_get_display_availability
*				are successful
* @failcase			If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_get_display_availability_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	int nRet = WIFI_DIRECT_ERROR_NONE;
	bool bIsAavailable = TRUE;

	nRet = wifi_direct_set_display_availability(bIsAavailable);
	if ( !g_bFeatureWifiDirectDisplay )
        {
                if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
                {
                        FPRINTF("[Line : %d][%s] wifi_direct_set_display_availability returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
                        WifiDirectTerminateService();
                        return 1;
                }
                else
                {
                        FPRINTF("[Line : %d][%s]wifi_direct_set_display_availability API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
                        WifiDirectTerminateService();
                        return 0;
                }
        }
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_display_availability", WifiDirectGetError(nRet), WifiDirectTerminateService());

	nRet = wifi_direct_get_display_availability(&bIsAavailable);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_display_availability", WifiDirectGetError(nRet), WifiDirectTerminateService());

	if (!bIsAavailable)
	{
		FPRINTF("[Line : %d][%s] wifi_direct_get_display_availability returned bIsAavailable FALSE \\n", __LINE__, API_NAMESPACE, bIsAavailable);
		WifiDirectTerminateService();
		return 1;
	}
	WifiDirectTerminateService();
	return 0;
}


//& purpose: Gets the supported WPS mode
//& type: auto
/**
* @testcase 			ITc_wifi_direct_get_supported_wps_mode_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the supported WPS mode
* @scenario				Initialize wifi-direct\n
*						Calls wifi_direct_get_supported_wps_mode\n
*						De initialize wifi-direct
* @apicovered			wifi_direct_get_supported_wps_mode
* @passcase				When wifi_direct_get_supported_wps_mode is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_get_supported_wps_mode_p(void)
{
	START_TEST;

	int nWps_mode = 0;
	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	//Target API
	nRet = wifi_direct_get_supported_wps_mode(&nWps_mode);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_supported_wps_mode", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& purpose: get each supported WPS types
//& type: auto
/**
* @testcase 			ITc_wifi_direct_foreach_supported_wps_types_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			get each supported WPS types
* @scenario				Initialize wifi-direct\n
*						Get each supported wps types\n
*						De initialize wifi-direct
* @apicovered			wifi_direct_initialize, wifi_direct_foreach_supported_wps_types, wifi_direct_deinitialize
* @passcase				When wifi_direct_foreach_supported_wps_types is successful and invokes callback
* @failcase				If target API fails or callback is not invoked
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_foreach_supported_wps_types_p(void)
{
	START_TEST;

	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	g_bWifi_callback_invoked = false;
	nRet = wifi_direct_foreach_supported_wps_types(WifiDirectSupportedWpsTypeCb, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_foreach_supported_wps_types", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	if ( false == g_bWifi_callback_invoked )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_foreach_supported_wps_types failed, as callback is not invoked\\n", __LINE__, API_NAMESPACE);
		wifi_direct_deinitialize();
		return 1;
	}

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}


//& type: auto
//& purpose: Get local WPS type
/**
* @testcase 			ITc_wifi_direct_get_local_wps_type_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Get local WPS type
* @scenario				Initialize wifi-direct\n
*						Get local WPS type\n
*						De initialize wifi-direct
* @apicovered			wifi_direct_initialize, wifi_direct_deinitialize
* @passcase				When wifi_direct_get_local_wps_type is successful and gives some wps type
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_get_local_wps_type_p(void)
{
	START_TEST;

	wifi_direct_wps_type_e eLocalType;
	int nLocalType = -1;

	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	nRet = wifi_direct_get_local_wps_type(&eLocalType);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_local_wps_type", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	if ( nLocalType == (int)eLocalType )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_get_local_wps_type failed, wrong value returned\\n", __LINE__, API_NAMESPACE);
		wifi_direct_deinitialize();
		return 1;
	}

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}
//& type: auto
//& purpose: Set and Get wps config
/**
* @testcase                     ITc_wifi_direct_set_wps_config_method_p
* @type                         auto
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(shilpa.j)
* @description                  Get/set wps config method
* @scenario                     Initialize wifi-direct\n
*                               Set & Get wps config \n
*                               De initialize wifi-direct
* @apicovered                   wifi_direct_set_wps_config_method, wifi_direct_get_wps_config_method
* @passcase                     When wifi_direct_get_wps_config_method is successful and gives config non Negative
* @failcase                     If target API fails
* @precondition                 none
* @postcondition                none
*/

int ITc_wifi_direct_set_get_wps_config_method_p(void)
{
        START_TEST;
	wifi_direct_config_method_type_e CONFIG_METHOD_ARR[]=
        {
                WIFI_DIRECT_CONFIG_METHOD_DEFAULT,
                WIFI_DIRECT_CONFIG_METHOD_PBC,
                WIFI_DIRECT_CONFIG_METHOD_PIN_DISPLAY,
                WIFI_DIRECT_CONFIG_METHOD_PIN_KEYPAD
        };
        int nWpsConfigMethod = -1;
        int nWpsConfigDefaultValue = 7;
	int nSize = sizeof(CONFIG_METHOD_ARR)/sizeof(CONFIG_METHOD_ARR[0]);
        int nCounter = 0;

        int nRet = wifi_direct_initialize();
        CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
        PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

        nRet = wifi_direct_activate();
        PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_activate", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_set_wps_config_method(WIFI_DIRECT_CONFIG_METHOD_DEFAULT);
        PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_wps_config_method", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_get_wps_config_method(&nWpsConfigMethod);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_wps_config_method", WifiDirectGetError(nRet), wifi_direct_deinitialize());

        if(nWpsConfigMethod != nWpsConfigDefaultValue)
	{
		FPRINTF("[Line : %d][%s] wifi_direct_get_wps_config_method failed, wrong value returned\\n", __LINE__, API_NAMESPACE);
		wifi_direct_deinitialize();
		return 1;
	}

        for( nCounter = 1; nCounter<nSize; nCounter++)
	{
		nRet = wifi_direct_set_wps_config_method(CONFIG_METHOD_ARR[nCounter]);
		PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_wps_config_method", WifiDirectGetError(nRet), wifi_direct_deinitialize());

		nRet = wifi_direct_get_wps_config_method(&nWpsConfigMethod);
		PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_wps_config_method", WifiDirectGetError(nRet), wifi_direct_deinitialize());

		if(nWpsConfigMethod != CONFIG_METHOD_ARR[nCounter])
		{
			FPRINTF("[Line : %d][%s] wifi_direct_get_wps_config_method failed, wrong value returned\\n", __LINE__, API_NAMESPACE);
			wifi_direct_deinitialize();
			return 1;
		}
	}
	nRet = wifi_direct_deactivate();
        PRINT_RESULT_NORETURN(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deactivate", WifiDirectGetError(nRet));

        nRet = wifi_direct_deinitialize();
        PRINT_RESULT_NORETURN(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
        return 0;
}
//& type: auto
//& purpose: Create group with ssid
/**
* @testcase                     ITc_wifi_direct_create_group_with_ssid_p
* @type                         auto
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(shilpa.j)
* @description                  Create group with ssid
* @scenario                     Initialize wifi-direct\n
*                               Create group ssid \n
*                               De initialize wifi-direct
* @apicovered                   wifi_direct_create_group_with_ssid
* @passcase                     wifi_direct_create_group_with_ssid is successful and return no error.
* @failcase                     If target API fails
* @precondition                 none
* @postcondition                none
*/

int ITc_wifi_direct_create_group_with_ssid_p(void)
{
        START_TEST;

        int nRet = wifi_direct_initialize();
        CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
        PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	nRet = wifi_direct_activate();
        PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_activate", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	const char *pszSsid = "Tizen";
        nRet = wifi_direct_create_group_with_ssid(pszSsid);
        PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_create_group_with_ssid", WifiDirectGetError(nRet), wifi_direct_deinitialize());

        nRet = wifi_direct_deactivate();
        PRINT_RESULT_NORETURN(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deactivate", WifiDirectGetError(nRet));

        nRet = wifi_direct_deinitialize();
        PRINT_RESULT_NORETURN(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));

        return 0;
}

//& type: auto
//& purpose: Set and get intent per type
/**
* @testcase                     ITc_wifi_direct_set_get_go_intent_per_type_p
* @type                         auto
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(shilpa.j)
* @description                  set and get internet per type;
* @scenario                     Initialize wifi-direct\n
*                               set and get peer connection info\n
*                               De initialize wifi-direc
* @apicovered                   wifi_direct_set_go_intent_per_type, wifi_direct_get_go_intent_per_type
* @passcase                     wifi_direct_get_go_intent_per_type is successful and  no error.
* @failcase                     If target API fails
* @precondition                 none
* @postcondition                none
*/
int ITc_wifi_direct_set_get_go_intent_per_type_p(void)
{
        START_TEST;

        int nRet = wifi_direct_initialize();
        CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
        PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

        int nGoIntent = 7;
        int nType = 1;

        nRet = wifi_direct_set_go_intent_per_type(nType, nGoIntent);
        PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_go_intent_per_type", WifiDirectGetError(nRet), wifi_direct_deinitialize());


        nGoIntent = -1;
        int nRetGoIntent = 7;

        nRet = wifi_direct_get_go_intent_per_type(nType, &nGoIntent);
        PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_go_intent_per_type", WifiDirectGetError(nRet), wifi_direct_deinitialize());

        if(nGoIntent != nRetGoIntent )
        {
                FPRINTF("[Line : %d][%s] wifi_direct_get_go_intent_per_type failed, wrong value returned\\n", __LINE__, API_NAMESPACE);
                wifi_direct_deinitialize();
                return 1;
        }


        nRet = wifi_direct_deinitialize();
        PRINT_RESULT_NORETURN(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));

        return 0;
}

//& type: auto
//& purpose: Set and Unset Peer info connection
/**
* @testcase                     ITc_wifi_direct_set_unset_peer_info_connection_state_changed_cb_p
* @type                         auto
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(shilpa.j)
* @description                  set and unset peer connection info
* @scenario                     Initialize wifi-direct\n
*                               set and get peer connection info\n
*                               De initialize wifi-direct
* @apicovered                   wifi_direct_initialize, wifi_direct_deinitialize
* @passcase                     wifi_direct_set_peer_info_connection_state_changed_cb & wifi_direct_unset_peer_info_connection_state_changed_cb
                                is successful and  no error.
* @failcase                     If target API fails
* @precondition                 none
* @postcondition                none
*/

int ITc_wifi_direct_set_unset_peer_info_connection_state_changed_cb_p(void)
{
        START_TEST;

        int nRet = wifi_direct_initialize();
        CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
        PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

        nRet = wifi_direct_set_peer_info_connection_state_changed_cb(WifiDirectPeerInfoConnectionStateChangedCb, NULL);
        PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_peer_info_connection_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deinitialize());

        nRet = wifi_direct_unset_peer_info_connection_state_changed_cb();
        PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_peer_info_connection_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deinitialize());

        nRet = wifi_direct_deinitialize();
        PRINT_RESULT_NORETURN(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));

        return 0;
}
//& type: auto
//& purpose: Get local device mac address
/**
* @testcase 			ITc_wifi_direct_get_mac_address_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Get local device mac address
* @scenario				Initialize wifi-direct\n
*						Get local device mac address\n
*						De initialize wifi-direct
* @apicovered			wifi_direct_get_mac_address, wifi_direct_deinitialize
* @passcase				When wifi_direct_get_mac_address is successful and returns some address
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_get_mac_address_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	
	char *pszMacAddress = NULL;
	int nRet = wifi_direct_get_mac_address(&pszMacAddress);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_mac_address", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	if ( NULL == pszMacAddress )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_get_mac_address failed, wrong value returned\\n", __LINE__, API_NAMESPACE);
		WifiDirectTerminateService();
		return 1;
	}

	FREE_MEMORY(pszMacAddress);	
	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Set/Get max clients
/**
* @testcase 			ITc_wifi_direct_set_get_max_clients_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Set/Get max clients
* @scenario				initialize wifi-direct\n
*						get initial max clients\n
*						set max clients\n
*						get max clients (match with above set value)\n
* 							set original value of max clients\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_initialize, wifi_direct_set_max_clients, wifi_direct_get_max_clients, wifi_direct_deinitialize
* @passcase				When wifi_direct_set_max_clients and wifi_direct_get_max_clients is successful and value matches
* @failcase				If wifi_direct_set_max_clients or wifi_direct_get_max_clients fails or value between set/get is mismatched
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_get_max_clients_p(void)
{
	START_TEST;

	int nOrigMaxClients, nGetMaxClients, nSetMaxClients=2;
	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	nRet = wifi_direct_get_max_clients(&nOrigMaxClients);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_max_clients", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_set_max_clients(nSetMaxClients);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_max_clients", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_get_max_clients(&nGetMaxClients);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_max_clients", WifiDirectGetError(nRet), wifi_direct_deinitialize());


	nRet = wifi_direct_set_max_clients(nOrigMaxClients);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_max_clients", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Get wifi direct primary device type
/**
* @testcase 			ITc_wifi_direct_get_primary_device_type_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Get wifi direct primary device type
* @scenario				initialize wifi-direct\n
*						Get wifi direct primary device type\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_initialize, wifi_direct_deinitialize
* @passcase				When wifi_direct_get_primary_device_type is successful and gives some wps type
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_get_primary_device_type_p(void)
{
	START_TEST;

	wifi_direct_primary_device_type_e eDeviceType;
	int nDeviceType = -1;

	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	nRet = wifi_direct_get_primary_device_type(&eDeviceType);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_primary_device_type", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	if ( nDeviceType == (int)eDeviceType )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_get_primary_device_type failed, wrong value returned\\n", __LINE__, API_NAMESPACE);
		wifi_direct_deinitialize();
		return 1;
	}

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Set/Get WPS type request
/**
* @testcase 			ITc_wifi_direct_set_get_req_wps_type_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Set/Get max clients
* @scenario				initialize wifi-direct\n
*						get initial req wps type\n
*						set req wps type\n
*						get req wps type (match with above set value)\n
* 							set original value of req wps type\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_initialize, wifi_direct_set_req_wps_type, wifi_direct_get_req_wps_type, wifi_direct_deinitialize
* @passcase				When wifi_direct_set_req_wps_type and wifi_direct_get_req_wps_type is successful and value matches
* @failcase				If wifi_direct_set_req_wps_type or wifi_direct_get_req_wps_type fails or value between set/get is mismatched
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_get_req_wps_type_p(void)
{
	START_TEST;

	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	wifi_direct_wps_type_e eOriginalType, eSetType, eGetType;
	g_bWifi_callback_invoked = false;
	nRet = wifi_direct_foreach_supported_wps_types(WifiDirectSupportedWpsTypeCb, (void*)(&eSetType));
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_foreach_supported_wps_types", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	if ( !g_bWifi_callback_invoked )
	{
		FPRINTF("[Line : %d][%s] [Not Supported] no wps type supported\\n", __LINE__, API_NAMESPACE);
		wifi_direct_deinitialize();
		return 0;
	}

	nRet = wifi_direct_get_req_wps_type(&eOriginalType);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_req_wps_type", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_set_req_wps_type(eSetType);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_req_wps_type", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_get_req_wps_type(&eGetType);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_req_wps_type", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_set_req_wps_type(eOriginalType);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_req_wps_type", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Get wifi direct secondary device type
/**
* @testcase 			ITc_wifi_direct_get_secondary_device_type_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Get wifi direct secondary device type
* @scenario				initialize wifi-direct\n
*						Get wifi direct secondary device type\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_initialize, wifi_direct_deinitialize
* @passcase				When wifi_direct_get_secondary_device_type is successful and gives some wps type
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_get_secondary_device_type_p(void)
{
	START_TEST;

	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	wifi_direct_secondary_device_type_e eDeviceType;
	int nDeviceType = -1;
	nRet = wifi_direct_get_secondary_device_type(&eDeviceType);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_secondary_device_type", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	if ( nDeviceType == (int)eDeviceType )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_get_secondary_device_type failed, wrong value returned\\n", __LINE__, API_NAMESPACE);
		wifi_direct_deinitialize();
		return 1;
	}

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Get local device ssid
/**
* @testcase 			ITc_wifi_direct_get_ssid_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Get local device ssid
* @scenario				initialize wifi-direct\n
*						Get local device ssid\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_initialize, wifi_direct_get_ssid, wifi_direct_deinitialize
* @passcase				When wifi_direct_get_ssid is successful and returns some address
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_get_ssid_p(void)
{
	START_TEST;

	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	char *pszSsid = NULL;

	nRet = wifi_direct_get_ssid(&pszSsid);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_ssid", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	if ( NULL == pszSsid )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_get_ssid failed, wrong value returned\\n", __LINE__, API_NAMESPACE);
		wifi_direct_deinitialize();
		return 1;
	}
	FREE_MEMORY(pszSsid);

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Set autoconnection mode and check the autoconnection mode
/**
* @testcase 			ITc_wifi_direct_set_auto_connectionmode_is_auto_connection_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Set/Get max clients
* @scenario				initialize wifi-direct\n
*						set auto connection mode\n
*						Check the state of auto connection mode\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_autoconnection_mode, wifi_direct_is_autoconnection_mode
* @passcase				When wifi_direct_set_autoconnection_mode and wifi_direct_is_autoconnection_mode is successful and value matches
* @failcase				If wifi_direct_set_autoconnection_mode or wifi_direct_is_autoconnection_mode fails or value is mismatched
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_auto_connectionmode_is_auto_connection_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	bool bSetAutoConnection = true;
	bool bIsAutoConnection = false;

	int nRet = wifi_direct_set_autoconnection_mode(bSetAutoConnection);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_autoconnection_mode", WifiDirectGetError(nRet), WifiDirectTerminateService());

	nRet = wifi_direct_is_autoconnection_mode(&bIsAutoConnection);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_is_autoconnection_mode", WifiDirectGetError(nRet), WifiDirectTerminateService());
	if (bIsAutoConnection != bSetAutoConnection)
	{
		FPRINTF("[Line : %d][%s]set/get value mismatched\\n", __LINE__, API_NAMESPACE);
		WifiDirectTerminateService();
		return 1;
	}

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: check if device is listening only
/**
* @testcase 			ITc_wifi_direct_is_discoverable_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			check if device is listening only
* @scenario				initialize wifi-direct\n
*						check if device is discoverable only\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_initialize, wifi_direct_is_discoverable, wifi_direct_deinitialize
* @passcase				When wifi_direct_is_discoverable is successful
* @failcase				If wifi_direct_is_discoverable fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_is_discoverable_p(void)
{
	START_TEST;

	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	bool bIsDiscoverable = false;
	nRet = wifi_direct_is_discoverable(&bIsDiscoverable);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_is_discoverable", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Set and Unset Device state change callback
/**
* @testcase 			ITc_wifi_direct_set_unset_device_state_changed_cb_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Set and Unset Device state change callback
* @scenario				initialize wifi-direct\n
*						Set callbacks\n
*						activates wifi-direct\n
*						deactivates wifi-direct\n
*						Unset callbacks\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_device_state_changed_cb, wifi_direct_unset_device_state_changed_cb
* @passcase				When wifi_direct_set_device_state_changed_cb and wifi_direct_set_device_state_changed_cb are successful and behave properly
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_unset_device_state_changed_cb_p(void)
{
	START_TEST;

	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	nRet = wifi_direct_set_device_state_changed_cb(wifi_direct_device_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_device_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	//Target API
	nRet = wifi_direct_unset_device_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_device_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Activates and Deactivates the wifi-direct service
/**
* @testcase 			ITc_wifi_direct_activate_deactivate_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Activates and deactivates the wifi-direct service
* @scenario				initialize wifi-direct\n
*						activates wifi-direct\n
*						deactivates wifi-direct\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_activate, wifi_direct_deactivate
* @passcase				When wifi_direct_activate and wifi_direct_deactivate is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_activate_deactivate_p(void)
{
	START_TEST;
	int nTimeoutId = 0;
	
	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));
	
	nRet = wifi_direct_set_device_state_changed_cb(wifi_direct_device_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_device_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	
	wifi_direct_state_e state = WIFI_DIRECT_STATE_DEACTIVATED;
	nRet = wifi_direct_get_state(&state);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_state", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	if ( state == WIFI_DIRECT_STATE_ACTIVATED )
	{
		nRet = wifi_direct_deactivate();
		PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deactivate", WifiDirectGetError(nRet), wifi_direct_unset_device_state_changed_cb();wifi_direct_deinitialize());
		RUN_POLLING_LOOP("wifi_direct_set_device_state_changed_cb_deactivate");	
		if ( g_bCallbackResult == false )
		{
			FPRINTF("[Line : %d][%s] Unable to invoke callback\\n", __LINE__, API_NAMESPACE);
			wifi_direct_unset_device_state_changed_cb();
			wifi_direct_deinitialize();
			return 1;
		}
		if ( g_device_state != WIFI_DIRECT_DEVICE_STATE_DEACTIVATED )
		{
			FPRINTF("[Line : %d][%s] wifi_direct_activate callback returned wrong device state = %d\\n", __LINE__, API_NAMESPACE, g_device_state);
			wifi_direct_unset_device_state_changed_cb();
			wifi_direct_deinitialize();
			return 1;
		}
	}

	g_bCallbackResult = false;

	//Target API
	nRet = wifi_direct_activate();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_activate", WifiDirectGetError(nRet), wifi_direct_unset_device_state_changed_cb();wifi_direct_deinitialize());
	
	RUN_POLLING_LOOP("wifi_direct_set_device_state_changed_cb_activate");	
	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Unable to invoke callback\\n", __LINE__, API_NAMESPACE);
		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return 1;
	}
	if ( g_device_state != WIFI_DIRECT_DEVICE_STATE_ACTIVATED )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_activate callback returned wrong device state =%d\\n", __LINE__, API_NAMESPACE, g_device_state);
		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return 1;
	}

	nTimeoutId = 0;
	
	g_bCallbackResult = false;
	//Target API
	nRet = wifi_direct_deactivate();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deactivate", WifiDirectGetError(nRet), wifi_direct_unset_device_state_changed_cb();wifi_direct_deinitialize());
	RUN_POLLING_LOOP("wifi_direct_set_device_state_changed_cb_deactivate");	
	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Unable to invoke callback\\n", __LINE__, API_NAMESPACE);
		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return 1;
	}
	if ( g_device_state != WIFI_DIRECT_DEVICE_STATE_DEACTIVATED )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_activate callback returned wrong device state = %d\\n", __LINE__, API_NAMESPACE, g_device_state);
		wifi_direct_unset_device_state_changed_cb();
		wifi_direct_deinitialize();
		return 1;
	}

	nRet = wifi_direct_unset_device_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_device_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Enable/Disable wifi-direct display(miracst) service
/**
* @testcase 			ITc_wifi_direct_init_miracast_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Enable/Disable wifi-direct display(miracst) service
* @scenario				initialize wifi-direct, activate wifi-direct\n
*						Enable wifi-direct display(miracst) service\n
*						Disable wifi-direct display(miracst) service\n
*						deactivate wifi-direct, deinitialize wifi-direct
* @apicovered			wifi_direct_init_miracast
* @passcase				When wifi_direct_init_miracast is successful and returns some address
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_init_miracast_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	int nRet = wifi_direct_init_miracast(true);
	if ( !g_bFeatureWifiDirectDisplay )
        {
                if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
                {
                        FPRINTF("[Line : %d][%s] wifi_direct_init_miracast returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
                        WifiDirectTerminateService();
                        return 1;
                }
                else
                {
                        FPRINTF("[Line : %d][%s]wifi_direct_init_miracast API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
                        WifiDirectTerminateService();
                        return 0;
                }
        }
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_init_miracast", WifiDirectGetError(nRet), WifiDirectTerminateService());

	nRet = wifi_direct_init_miracast(false);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_init_miracast", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Get wifi direct state
/**
* @testcase 			ITc_wifi_direct_get_state_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			get subnet mask
* @scenario				initialize wifi-direct, activate wifi direct\n
*						get state, state must be activated\n
*						deactivate wifi-direct, deinitialize wifi-direct
* @apicovered			wifi_direct_get_state
* @passcase				When wifi_direct_get_state is successful and gives correct state
* @failcase				If wifi_direct_get_state fails or incorrect state is returned
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_get_state_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	wifi_direct_state_e eState = WIFI_DIRECT_STATE_DEACTIVATED;

	int nRet = wifi_direct_get_state(&eState);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_state", WifiDirectGetError(nRet), WifiDirectTerminateService());

	if ( eState < WIFI_DIRECT_STATE_ACTIVATED )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_get_state failed, wrong state returned %d\\n", __LINE__, API_NAMESPACE, (int)eState);
		WifiDirectTerminateService();
		return 1;
	}

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: check if device is listening only
/**
* @testcase 			ITc_wifi_direct_is_listening_only_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			check if device is listening only
* @scenario				initialize wifi-direct\n
*						check if device is listening only\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_is_listening_only
* @passcase				When wifi_direct_is_listening_only is successful
* @failcase				If wifi_direct_is_listening_only fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_is_listening_only_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	bool bIsListening = false;

	int nRet = wifi_direct_is_listening_only(&bIsListening);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_is_listening_only", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Creates and destroys wifi direct group
/**
* @testcase 			ITc_wifi_direct_create_destroy_group_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			get network interface name
* @scenario				initialize wifi-direct, activates wifi-direct\n
*						creates group\n
*						destroys group\n
*						deactivates wifi-direct, deinitialize wifi-direct
* @apicovered			wifi_direct_create_group, wifi_direct_destroy_group
* @passcase				When wifi_direct_get_network_interface_name is successful and returns some address
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_create_destroy_group_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	int nTimeoutId = 0;
	

	int nRet = wifi_direct_set_connection_state_changed_cb(wifi_direct_connection_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_connection_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());
	g_bCallbackResult = false;
	nRet = wifi_direct_create_group();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_create_group", WifiDirectGetError(nRet), wifi_direct_unset_connection_state_changed_cb();WifiDirectTerminateService());
	RUN_POLLING_LOOP("wifi_direct_connection_state_changed_callback");
	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Unable to invoke callback\\n", __LINE__, API_NAMESPACE);
		WifiDirectTerminateService();
		return 1;
	}
	nRet = wifi_direct_destroy_group();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_destroy_group", WifiDirectGetError(nRet), wifi_direct_unset_connection_state_changed_cb();WifiDirectTerminateService());

	nRet = wifi_direct_unset_connection_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_connection_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Creates and destroys wifi direct group
/**
* @testcase 			ITc_wifi_direct_is_autonomous_group_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			get network interface name
* @scenario				initialize wifi-direct, activates wifi-direct\n
*						creates group\n
*						check if group is autonomous\n
*						destroys group\n
*						deactivates wifi-direct, deinitialize wifi-direct
* @apicovered			wifi_direct_is_autonomous_group, wifi_direct_set_connection_state_changed_cb
* @passcase				When wifi_direct_get_network_interface_name is successful and returns some address
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_is_autonomous_group_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	int nTimeoutId = 0;
	

	int nRet = wifi_direct_set_connection_state_changed_cb(wifi_direct_connection_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_connection_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());
	g_bCallbackResult = false;

	nRet = wifi_direct_create_group();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_create_group", WifiDirectGetError(nRet), wifi_direct_unset_connection_state_changed_cb();WifiDirectTerminateService());

	bool bIsAutonomous = false;
	nRet = wifi_direct_is_autonomous_group(&bIsAutonomous);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_is_autonomous_group", WifiDirectGetError(nRet), wifi_direct_destroy_group();wifi_direct_unset_connection_state_changed_cb();WifiDirectTerminateService());
	RUN_POLLING_LOOP("wifi_direct_connection_state_changed_callback");
	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Unable to invoke callback\\n", __LINE__, API_NAMESPACE);
		wifi_direct_unset_connection_state_changed_cb();
		wifi_direct_destroy_group();
		WifiDirectTerminateService();
		return 1;
	}
	
	nRet = wifi_direct_unset_connection_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_connection_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_destroy_group();WifiDirectTerminateService());

	nRet = wifi_direct_destroy_group();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_destroy_group", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Check if its group owner
/**
* @testcase 			ITc_wifi_direct_is_group_owner_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Check if its group owner
* @scenario				initialize wifi-direct, activates wifi-direct\n
*						creates group\n
*						Check if its group owner\n
*						destroys group\n
*						deactivates wifi-direct, deinitialize wifi-direct
* @apicovered			wifi_direct_is_group_owner, wifi_direct_set_connection_state_changed_cb
* @passcase				When wifi_direct_get_network_interface_name is successful and returns some address
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_is_group_owner_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	int nTimeoutId = 0;
	
	int nRet = wifi_direct_set_connection_state_changed_cb(wifi_direct_connection_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_connection_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());
	g_bCallbackResult = false;

	nRet = wifi_direct_create_group();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_create_group", WifiDirectGetError(nRet), wifi_direct_unset_connection_state_changed_cb();WifiDirectTerminateService());

	bool bIsOwner = false;
	nRet = wifi_direct_is_group_owner(&bIsOwner);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_is_group_owner", WifiDirectGetError(nRet), wifi_direct_unset_connection_state_changed_cb();wifi_direct_destroy_group();WifiDirectTerminateService());
	RUN_POLLING_LOOP("wifi_direct_connection_state_changed_callback");	
	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Unable to invoke callback\\n", __LINE__, API_NAMESPACE);
		wifi_direct_unset_connection_state_changed_cb();
		wifi_direct_destroy_group();
		WifiDirectTerminateService();
		return 1;
	}

	nRet = wifi_direct_unset_connection_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_connection_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_destroy_group();WifiDirectTerminateService());

	nRet = wifi_direct_destroy_group();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_destroy_group", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Sets/Gets the name of a local device
/**
* @testcase 			ITc_wifi_direct_set_get_device_name_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Sets/Gets the name of a local device
* @scenario				initialize and activate wifi-direct\n
*						Set the name of a local device\n
*						Get the name of a local device\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_device_name, wifi_direct_get_device_name
* @passcase				When wifi_direct_set_device_name, wifi_direct_get_device_name are successful and invokes callback
* @failcase				If target API fails or callback is not invoked
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_get_device_name_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	char* pszSetDeviceName = "TestWifi";
	char* pszGetDeviceName = NULL;

	int nRet = wifi_direct_set_device_name(pszSetDeviceName); // Target API
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_device_name", WifiDirectGetError(nRet), WifiDirectTerminateService());

	nRet = wifi_direct_get_device_name(&pszGetDeviceName);// Target API
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_device_name", WifiDirectGetError(nRet), WifiDirectTerminateService());

	FREE_MEMORY(pszGetDeviceName);	
	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Sets/Gets the intent of the group owner
/**
* @testcase 			ITc_wifi_direct_set_get_group_owner_intent_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Sets/Gets the intent of the group owner
* @scenario				initialize and activate wifi-direct\n
*						Set the intent of the group owner\n
*						Get the intent of the group owner\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_group_owner_intent, wifi_direct_get_group_owner_intent
* @passcase				When wifi_direct_set_group_owner_intent, wifi_direct_get_group_owner_intent are successful and invokes callback
* @failcase				If target API fails or callback is not invoked
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_get_group_owner_intent_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	int nSetIntent = 8;
	int nGetIntent;

	int nRet = wifi_direct_set_group_owner_intent(nSetIntent); // Target API
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_group_owner_intent", WifiDirectGetError(nRet), WifiDirectTerminateService());

	nRet = wifi_direct_get_group_owner_intent(&nGetIntent);// Target API
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_group_owner_intent", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Sets or updates the WPS PIN number user expects
/**
* @testcase 			ITc_wifi_direct_set_wps_pin_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Sets or updates the WPS PIN number user expects
* @scenario				initialize and activate wifi-direct\n
*						Set WPS pin\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_wps_pin
* @passcase				When wifi_direct_set_wps_pin is successful
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_wps_pin_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	char* pszSetWpsPin = "1234";

	int nRet = wifi_direct_set_wps_pin(pszSetWpsPin); // Target API
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_wps_pin", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Gets the information of discovered peers
/**
* @testcase 			ITc_wifi_direct_foreach_discovered_peers_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Gets the information of connected peers
* @scenario				initialize and activate wifi-direct\n
*						discover peer\n
*						Get the information of discovered peers\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_foreach_discovered_peers
* @passcase				When wifi_direct_foreach_discovered_peers is successful
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_foreach_discovered_peers_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	int nRet = wifi_direct_foreach_discovered_peers(WifiDirectDiscoveredPeerCb, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_foreach_discovered_peers", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Gets the information of discovered peers
/**
* @testcase 			ITc_wifi_direct_foreach_persistent_groups_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Gets the information of connected peers
* @scenario				initialize and activate wifi-direct\n
*						discover peer\n
*						Get the information of discovered peers\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_foreach_persistent_groups
* @passcase				When wifi_direct_foreach_persistent_groups is successful
* @failcase				If target API fails
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_foreach_persistent_groups_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	int nRet = wifi_direct_foreach_persistent_groups(WifiDirectPersistentGroupCb,NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_foreach_persistent_groups", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}


//& type: auto
//& purpose: Register/Deregister the wifi-direct service
/**
* @testcase 			ITc_wifi_direct_register_deregister_service_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Register/Deregister the wifi-direct service
* @scenario				initialize wifi-direct\n
*						activates wifi-direct\n
*						register wifi-direct service\n
*						deregister wifi-direct service\n
*						deactivates wifi-direct\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_register_service, wifi_direct_deregister_service
* @passcase				When wifi_direct_register_service and wifi_direct_deregister_service is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_register_deregister_service_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	unsigned int nServiceID = 0;

	//Target API
	int nRet = wifi_direct_register_service(WIFI_DIRECT_SERVICE_TYPE_UPNP, WIFI_DIRECT_INFORMATION_OF_SERVICE1, WIFI_DIRECT_INFORMATION_OF_SERVICE2, &nServiceID);
	if ( !g_bFeatureWifiDirectSrvcDiscovery )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] wifi_direct_register_service returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
			WifiDirectTerminateService();
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] wifi_direct_register_service API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
			WifiDirectTerminateService();
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_register_service", WifiDirectGetError(nRet), WifiDirectTerminateService());

	//Target API
	nRet = wifi_direct_deregister_service(nServiceID);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deregister_service", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Start Discovery to find all P2P capable devices and cancel discovery
/**
* @testcase 			ITc_wifi_direct_start_cancel_discovery_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Start Discovery to find all P2P capable devices
* @scenario				initialize wifi-direct\n
*						activates wifi-direct\n
*						Set callbacks\n
*						Start Discovery\n
*						Cancel Discovery\n
*						Unset callbacks\n
*						deactivates wifi-direct\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_start_discovery, wifi_direct_cancel_discovery
* @passcase				When wifi_direct_start_discovery is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_start_cancel_discovery_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	int nTimeoutId = 0;
	
	int nRet = wifi_direct_set_discovery_state_changed_cb(wifi_direct_discovery_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_discovery_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());
	g_bCallbackResult = false;
	g_discovery_state = WIFI_DIRECT_ONLY_LISTEN_STARTED;

	//Target API
	nRet = wifi_direct_start_discovery(false, 0);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_start_discovery", WifiDirectGetError(nRet), wifi_direct_unset_discovery_state_changed_cb();WifiDirectTerminateService());
	RUN_POLLING_LOOP("wifi_direct_discovery_state_changed_callback");
	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Unable to invoke callback\\n", __LINE__, API_NAMESPACE);
		wifi_direct_unset_discovery_state_changed_cb();
		WifiDirectTerminateService();
		return 1;
	}
	
	if ( g_discovery_state != WIFI_DIRECT_DISCOVERY_STARTED )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_start_discovery callback returned wrong discovery state =%d\\n", __LINE__, API_NAMESPACE, g_discovery_state);
		wifi_direct_unset_discovery_state_changed_cb();
		WifiDirectTerminateService();
		return 1;
	}

	//Target API
	nRet = wifi_direct_cancel_discovery();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_start_discovery", WifiDirectGetError(nRet), wifi_direct_unset_discovery_state_changed_cb();WifiDirectTerminateService());

	nRet = wifi_direct_unset_discovery_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_discovery_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Set and Unset Discovery state change callback
/**
* @testcase 			ITc_wifi_direct_set_unset_discovery_state_changed_cb_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Set and Unset Discovery state change callback
* @scenario				initialize wifi-direct\n
*						activates wifi-direct\n
*						Set callbacks\n
*						Start Discovery\n
*						Cancel Discovery\n
*						Unset callbacks\n
*						deactivates wifi-direct\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_discovery_state_changed_cb, wifi_direct_unset_discovery_state_changed_cb
* @passcase				When wifi_direct_set_discovery_state_changed_cb and wifi_direct_set_discovery_state_changed_cb are successful and behave properly
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_unset_discovery_state_changed_cb_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	int nTimeoutId = 0;
	
	g_bWifi_direct_discovery_state_changed_callback_invoked = false;
	g_discovery_state = WIFI_DIRECT_ONLY_LISTEN_STARTED;
	g_bCallbackResult = false;

	//Target API
	int nRet = wifi_direct_set_discovery_state_changed_cb(wifi_direct_discovery_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_discovery_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());

	nRet = wifi_direct_start_discovery(false, 0);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_start_discovery", WifiDirectGetError(nRet), wifi_direct_unset_discovery_state_changed_cb();WifiDirectTerminateService());
	RUN_POLLING_LOOP("wifi_direct_discovery_state_changed_callback");
	if (false == g_bWifi_direct_discovery_state_changed_callback_invoked)
	{
		FPRINTF("[Line : %d][%s] Unable to get call back for wifi_direct_start_discovery\\n", __LINE__, API_NAMESPACE);
		wifi_direct_unset_discovery_state_changed_cb();
		WifiDirectTerminateService();
		return 1;
	}

	if ( g_discovery_state != WIFI_DIRECT_DISCOVERY_STARTED )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_start_discovery callback returned wrong discovery state =%d\\n", __LINE__, API_NAMESPACE, g_discovery_state);
		wifi_direct_unset_discovery_state_changed_cb();
		WifiDirectTerminateService();
		return 1;
	}

	nRet = wifi_direct_cancel_discovery();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_start_discovery", WifiDirectGetError(nRet), wifi_direct_unset_discovery_state_changed_cb();WifiDirectTerminateService());

	nRet = wifi_direct_unset_discovery_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_discovery_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Set and Unset Peer Found callback
/**
* @testcase 			ITc_wifi_direct_set_unset_peer_found_cb_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Set and Unset Peer Found callback
* @scenario				initialize wifi-direct\n
*						activates wifi-direct\n
*						Set callbacks\n
*						Start Discovery\n
*						Cancel Discovery\n
*						Unset callbacks\n
*						deactivates wifi-direct\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_peer_found_cb, wifi_direct_unset_peer_found_cb
* @passcase				When wifi_direct_set_peer_found_cb and wifi_direct_set_peer_found_cb are successful and behave properly
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_unset_peer_found_cb_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}


	//Target API
	int nRet = wifi_direct_set_peer_found_cb(wifi_direct_peer_found_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_peer_found_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());

	//Target API
	nRet = wifi_direct_unset_peer_found_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_peer_found_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Start Service Discovery and then Cancel Service Discovery
/**
* @testcase 			ITc_wifi_direct_start_cancel_discovery_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Start Service Discovery and Cancel
* @scenario				initialize wifi-direct\n
*						activates wifi-direct\n
*						Set callbacks\n
*						Start Service Discovery\n
*						Cancel Service Discovery\n
*						Unset callbacks\n
*						deactivates wifi-direct\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_start_service_discovery, wifi_direct_cancel_service_discovery
* @passcase				When wifi_direct_start_service_discovery is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_start_cancel_service_discovery_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	
	int nTimeoutId = 0;
	
	unsigned int nServiceID = 0;
	int nRet = wifi_direct_register_service(WIFI_DIRECT_SERVICE_TYPE_UPNP, WIFI_DIRECT_INFORMATION_OF_SERVICE1, WIFI_DIRECT_INFORMATION_OF_SERVICE2, &nServiceID);
	if ( !g_bFeatureWifiDirectSrvcDiscovery )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] wifi_direct_register_service returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
			WifiDirectTerminateService();
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] wifi_direct_register_service API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
			WifiDirectTerminateService();
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_register_service", WifiDirectGetError(nRet), WifiDirectTerminateService());

	nRet = wifi_direct_set_service_state_changed_cb(wifi_direct_service_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_service_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deregister_service(nServiceID);WifiDirectTerminateService());

	g_service_discovery_state = WIFI_DIRECT_SERVICE_DISCOVERY_FINISHED;
	g_bWifi_direct_service_state_changed_callback_invoked = false;

	//Target API
	nRet = wifi_direct_start_service_discovery(0, WIFI_DIRECT_SERVICE_TYPE_UPNP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_start_service_discovery", WifiDirectGetError(nRet), wifi_direct_unset_service_state_changed_cb();wifi_direct_deregister_service(nServiceID);WifiDirectTerminateService());
	RUN_POLLING_LOOP("wifi_direct_service_state_changed_callback");	
	if ( !g_bWifi_direct_service_state_changed_callback_invoked )
	{
		FPRINTF("[Line : %d][%s] Unable to get call back for wifi_direct_start_service_discovery\\n", __LINE__, API_NAMESPACE);
		wifi_direct_cancel_service_discovery(0, WIFI_DIRECT_SERVICE_TYPE_UPNP);
		wifi_direct_unset_service_state_changed_cb();
		wifi_direct_deregister_service(nServiceID);		
		return 1;
	}
	if ( g_service_discovery_state != WIFI_DIRECT_SERVICE_DISCOVERY_STARTED )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_start_service_discovery callback returned wrong service discovery state =%d\\n", __LINE__, API_NAMESPACE, g_service_discovery_state);
		wifi_direct_cancel_service_discovery(0, WIFI_DIRECT_SERVICE_TYPE_UPNP);
		wifi_direct_unset_service_state_changed_cb();
		wifi_direct_deregister_service(nServiceID);
		return 1;
	}

	//Target API
	nRet = wifi_direct_cancel_service_discovery(0, WIFI_DIRECT_SERVICE_TYPE_UPNP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_cancel_service_discovery", WifiDirectGetError(nRet), wifi_direct_unset_service_state_changed_cb();wifi_direct_deregister_service(nServiceID);WifiDirectTerminateService());

	nRet = wifi_direct_unset_service_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_service_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deregister_service(nServiceID);WifiDirectTerminateService());

	nRet = wifi_direct_deregister_service(nServiceID);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deregister_service", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Set and Unset Service state change callback
/**
* @testcase 			ITc_wifi_direct_set_unset_service_state_changed_cb_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Set and Unset Service state change callback
* @scenario				initialize wifi-direct\n
*						Set callbacks\n
*						activates wifi-direct\n
*						deactivates wifi-direct\n
*						Unset callbacks\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_service_state_changed_cb, wifi_direct_unset_service_state_changed_cb
* @passcase				When wifi_direct_set_service_state_changed_cb and wifi_direct_set_service_state_changed_cb are successful and behave properly
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_unset_service_state_changed_cb_p(void)
{
	START_TEST;
	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	int nTimeoutId = 0;
	
	unsigned int nServiceID = 0;
	int nRet = wifi_direct_register_service(WIFI_DIRECT_SERVICE_TYPE_UPNP, WIFI_DIRECT_INFORMATION_OF_SERVICE1, WIFI_DIRECT_INFORMATION_OF_SERVICE2, &nServiceID);
	if ( !g_bFeatureWifiDirectSrvcDiscovery )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] wifi_direct_register_service returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
			WifiDirectTerminateService();
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] wifi_direct_register_service API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, WifiDirectGetError(nRet));
			WifiDirectTerminateService();
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_register_service", WifiDirectGetError(nRet), WifiDirectTerminateService());

	g_service_discovery_state = WIFI_DIRECT_SERVICE_DISCOVERY_FINISHED;
	g_bWifi_direct_service_state_changed_callback_invoked = false;

	//Target API
	nRet = wifi_direct_set_service_state_changed_cb(wifi_direct_service_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_service_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deregister_service(nServiceID);WifiDirectTerminateService());

	nRet = wifi_direct_start_service_discovery(0, WIFI_DIRECT_SERVICE_TYPE_UPNP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_start_service_discovery", WifiDirectGetError(nRet), wifi_direct_unset_service_state_changed_cb();wifi_direct_deregister_service(nServiceID);WifiDirectTerminateService());
	RUN_POLLING_LOOP("wifi_direct_service_state_changed_callback");	
	if ( !g_bWifi_direct_service_state_changed_callback_invoked )
	{
		FPRINTF("[Line : %d][%s] Unable to get call back for wifi_direct_start_service_discovery\\n", __LINE__, API_NAMESPACE);
		wifi_direct_cancel_service_discovery(0, WIFI_DIRECT_SERVICE_TYPE_UPNP);
		wifi_direct_unset_service_state_changed_cb();
		wifi_direct_deregister_service(nServiceID);		
		return 1;
	}
	if ( g_service_discovery_state != WIFI_DIRECT_SERVICE_DISCOVERY_STARTED )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_start_service_discovery callback returned wrong service discovery state =%d\\n", __LINE__, API_NAMESPACE, g_service_discovery_state);
		wifi_direct_cancel_service_discovery(0, WIFI_DIRECT_SERVICE_TYPE_UPNP);
		wifi_direct_unset_service_state_changed_cb();
		wifi_direct_deregister_service(nServiceID);
		return 1;
	}

	nRet = wifi_direct_cancel_service_discovery(0, WIFI_DIRECT_SERVICE_TYPE_UPNP);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_cancel_service_discovery", WifiDirectGetError(nRet), wifi_direct_unset_service_state_changed_cb();wifi_direct_deregister_service(nServiceID);WifiDirectTerminateService());

	nRet = wifi_direct_unset_service_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_service_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deregister_service(nServiceID);WifiDirectTerminateService());

	nRet = wifi_direct_deregister_service(nServiceID);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deregister_service", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Start Discovery to find all P2P capable devices with specific channel
/**
* @testcase 			ITc_wifi_direct_start_discovery_specific_channel_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Start Discovery to find all P2P capable devices with specific channel
* @scenario				initialize wifi-direct\n
*						activates wifi-direct\n
*						Set callbacks\n
*						Start Discovery for specific channel\n
*						Cancel Discovery\n
*						Unset callbacks\n
*						deactivates wifi-direct\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_start_discovery_specific_channel
* @passcase				When wifi_direct_start_discovery_specific_channel is successful and return valid data
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_start_discovery_specific_channel_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}
	int nTimeoutId = 0;
	
	int nRet = wifi_direct_set_discovery_state_changed_cb(wifi_direct_discovery_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_discovery_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());

	g_bWifi_direct_discovery_state_changed_callback_invoked = false;
	g_discovery_state = WIFI_DIRECT_ONLY_LISTEN_STARTED;
	g_bCallbackResult = false;

	//Target API
	nRet = wifi_direct_start_discovery_specific_channel(false, 0, WIFI_DIRECT_DISCOVERY_FULL_SCAN);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_start_discovery_specific_channel", WifiDirectGetError(nRet), wifi_direct_unset_discovery_state_changed_cb();WifiDirectTerminateService());
	RUN_POLLING_LOOP("wifi_direct_discovery_state_changed_callback");	
	if (false == g_bWifi_direct_discovery_state_changed_callback_invoked)
	{
		FPRINTF("[Line : %d][%s] Unable to get call back for wifi_direct_start_discovery\\n", __LINE__, API_NAMESPACE);
		wifi_direct_unset_discovery_state_changed_cb();
		WifiDirectTerminateService();
		return 1;
	}

	if ( g_discovery_state != WIFI_DIRECT_DISCOVERY_STARTED )
	{
		FPRINTF("[Line : %d][%s] wifi_direct_start_discovery callback returned wrong discovery state =%d\\n", __LINE__, API_NAMESPACE, g_discovery_state);
		wifi_direct_unset_discovery_state_changed_cb();
		WifiDirectTerminateService();
		return 1;
	}

	nRet = wifi_direct_cancel_discovery();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_start_discovery", WifiDirectGetError(nRet), wifi_direct_unset_discovery_state_changed_cb();WifiDirectTerminateService());

	nRet = wifi_direct_unset_discovery_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_discovery_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

//& type: auto
//& purpose: Set and Unset Client IP Address Assigned state change callback
/**
* @testcase 			ITc_wifi_direct_set_unset_client_ip_address_assigned_cb_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Set and Unset Client IP Address Assigned state change callback
* @scenario				initialize wifi-direct\n
*						Set callbacks\n
*						activates wifi-direct\n
*						deactivates wifi-direct\n
*						Unset callbacks\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_client_ip_address_assigned_cb, wifi_direct_unset_client_ip_address_assigned_cb
* @passcase				When wifi_direct_set_client_ip_address_assigned_cb and wifi_direct_set_client_ip_address_assigned_cb are successful and behave properly
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_unset_client_ip_address_assigned_cb_p(void)
{
	START_TEST;

	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));

	g_bWifi_direct_client_ip_address_assigned_callback_invoked = false;

	//Target API
	nRet = wifi_direct_set_client_ip_address_assigned_cb(wifi_direct_client_ip_address_assigned_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_client_ip_address_assigned_cb", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	//Target API
	nRet = wifi_direct_unset_client_ip_address_assigned_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_client_ip_address_assigned_cb", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Set and Unset Connection state change callback
/**
* @testcase 			ITc_wifi_direct_set_unset_connection_state_changed_cb_p
* @type 				auto
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer				SRID(gupta.sanjay)
* @description			Set and Unset Connection state change callback
* @scenario				initialize wifi-direct\n
*						Set callbacks\n
*						activates wifi-direct\n
*						deactivates wifi-direct\n
*						Unset callbacks\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_connection_state_changed_cb, wifi_direct_unset_connection_state_changed_cb
* @passcase				When wifi_direct_set_connection_state_changed_cb and wifi_direct_set_connection_state_changed_cb are successful and behave properly
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_unset_connection_state_changed_cb_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	//Target API
	int nRet = wifi_direct_set_connection_state_changed_cb(wifi_direct_connection_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_connection_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());

	//Target API
	nRet = wifi_direct_unset_connection_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_connection_state_changed_cb", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}


//& type: auto
//& purpose: Set auto group removal
/**
* @testcase 			ITc_wifi_direct_set_auto_group_removal_p
* @type 				auto
* @since_tizen			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @description			Set auto group removal
* @scenario				initialize wifi-direct\n
*						wifi_direct_set_auto_group_removal
* @apicovered			wifi_direct_set_auto_group_removal
* @passcase				When wifi_direct_set_auto_group_removal successful and behave properly
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_auto_group_removal_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	//Target API
	int nRet = wifi_direct_set_auto_group_removal(true);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_auto_group_removal", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}


//& type: auto
//& purpose: Set/Get session timer
/**
* @testcase 			ITc_wifi_direct_set_get_session_timer_p
* @type 				auto
* @since_tizen			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @description			Set/Get session timer
* @scenario				initialize wifi-direct\n
*						wifi_direct_set_session_timer, wifi_direct_get_session_timer
* @apicovered			wifi_direct_set_session_timer, wifi_direct_get_session_timer
* @passcase				When wifi_direct_set_session_timer ,wifi_direct_get_session_timer successful and behave properly
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_get_session_timer_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	int ntimeSec = 10;
	int nGetTimer = 0 ;
	
	//Target API
	int nRet = wifi_direct_set_session_timer(ntimeSec);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_session_timer", WifiDirectGetError(nRet), WifiDirectTerminateService());

	//Target API
	nRet = wifi_direct_get_session_timer(&nGetTimer);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_session_timer", WifiDirectGetError(nRet), WifiDirectTerminateService());
	
	if(nGetTimer != ntimeSec)
	{
		FPRINTF("[Line : %d][%s] wifi_direct_get_session_timer error  = value returned [ %d ] is not correct\\n", __LINE__, API_NAMESPACE, nGetTimer);
		return 1;
	}
	
	WifiDirectTerminateService();
	return 0;
}
//& type: auto
//& purpose: Set and Unset state change callback
/**
* @testcase 			ITc_wifi_direct_set_unset_state_changed_cb_p
* @type 				auto
* @since_tizen			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(a.pandia)
* @description			Set and Unset state change callback
* @scenario				initialize wifi-direct\n
*						Set callbacks\n
*						activates wifi-direct\n
*						check callback hit
*						Unset callbacks\n
*						deinitialize wifi-direct
* @apicovered			wifi_direct_set_state_changed_cb, wifi_direct_unset_state_changed_cb
* @passcase				When wifi_direct_set_state_changed_cb and wifi_direct_unset_state_changed_cb are successful and behave properly
* @failcase				If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	int nRet = wifi_direct_initialize();
	CHECK_UNSUPPORTED_ERROR_RETURN(g_bFeatureWifiDirect, "wifi_direct_initialize");
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_initialize", WifiDirectGetError(nRet));
	
    //Target API
	nRet = wifi_direct_set_state_changed_cb(wifi_direct_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_set_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	
	wifi_direct_state_e state = WIFI_DIRECT_STATE_DEACTIVATED;
	nRet = wifi_direct_get_state(&state);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_get_state", WifiDirectGetError(nRet), wifi_direct_deinitialize());
	if ( state == WIFI_DIRECT_STATE_ACTIVATED )
	{
		nRet = wifi_direct_deactivate();
		PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_deactivate", WifiDirectGetError(nRet), wifi_direct_unset_state_changed_cb();wifi_direct_deinitialize());
		RUN_POLLING_LOOP("wifi_direct_set_state_changed_cb_deactivate");	
		if ( g_bCallbackResult == false )
		{
			FPRINTF("[Line : %d][%s] Unable to invoke callback\\n", __LINE__, API_NAMESPACE);
			wifi_direct_unset_state_changed_cb();
			wifi_direct_deinitialize();
			return 1;
		}
	}
	g_bCallbackResult = false;
	
	nRet = wifi_direct_activate();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_activate", WifiDirectGetError(nRet), wifi_direct_unset_state_changed_cb();wifi_direct_deinitialize());
	
	RUN_POLLING_LOOP("wifi_direct_set_state_changed_cb_activate");	
	if ( g_bCallbackResult == false )
	{
		FPRINTF("[Line : %d][%s] Unable to invoke callback\\n", __LINE__, API_NAMESPACE);
		wifi_direct_unset_state_changed_cb();
		wifi_direct_deinitialize();
		return 1;
	}
	//Target API
	nRet = wifi_direct_unset_state_changed_cb();
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_unset_state_changed_cb", WifiDirectGetError(nRet), wifi_direct_deinitialize());

	nRet = wifi_direct_deinitialize();
	PRINT_RESULT(WIFI_DIRECT_ERROR_NONE, nRet, " wifi_direct_deinitialize", WifiDirectGetError(nRet));
	return 0;
}

//& purpose: Adds, Gets and Remove the Wi-Fi Vendor Specific Information Element (VSIE) of all frame type.
//& type: auto
/**
* @testcase 			ITc_wifi_direct_add_get_remove_vsie_p
* @since_tizen			4.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Adds, Gets and Remove the Wi-Fi Vendor Specific Information Element\n
*				(VSIE) of all frame type.
* @scenario			Initialize wifi-direct\n
*				Calls wifi_direct_add_vsie, wifi_direct_get_vsie, wifi_direct_remove_vsie
* @apicovered			wifi_direct_add_vsie, wifi_direct_get_vsie, wifi_direct_remove_vsie
* @passcase			When wwifi_direct_add_vsie, wifi_direct_get_vsie, wifi_direct_remove_vsie\n
*				are successful and return valid data
* @failcase			If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/
int ITc_wifi_direct_add_get_remove_vsie_p(void)
{
	START_TEST;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	int nRet = WIFI_DIRECT_ERROR_NONE, nEnumLoopCount = 0;
	const char *set_vsie_str = "dd0f0000f00f0002060102055b54565d20";
	char *get_vsie_str = NULL;

	wifi_direct_vsie_frames_e eWifiDirectVSIEFrameId = -1;

	int arrWifiDirectVSIEFrameIdValues[] = {
		WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_REQ,		/**< P2P probe request frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_PROBE_RESP,		/**< P2P probe response frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_GO_PROBE_RESP,	/**< P2P group owner probe response frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_GO_BEACON,		/**< P2P probe request frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_PD_REQ,		/**< P2P provision discovery request frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_PD_RESP,		/**< P2P provision discovery response frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_GO_NEG_REQ,		/**< P2P probe request frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_GO_NEG_RESP,		/**< P2P group owner negotiation response frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_GO_NEG_CONF,		/**< P2P group owner negotiation confirmation frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_INV_REQ,		/**< P2P invitation request frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_INV_RESP,		/**< P2P invitation response frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_ASSOC_REQ,		/**< P2P association request frame **/
		WIFI_DIRECT_VSIE_FRAME_P2P_ASSOC_RESP,		/**< P2P association response frame **/
		WIFI_DIRECT_VSIE_FRAME_ASSOC_REQ		/**< Association request frame **/
	};

	int nFrameIdCount = sizeof(arrWifiDirectVSIEFrameIdValues) / sizeof(arrWifiDirectVSIEFrameIdValues[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nFrameIdCount; nEnumLoopCount++ )
	{
		eWifiDirectVSIEFrameId = arrWifiDirectVSIEFrameIdValues[nEnumLoopCount];

		nRet = wifi_direct_add_vsie(eWifiDirectVSIEFrameId, set_vsie_str);
		if ( nRet != WIFI_DIRECT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] wifi_direct_add_vsie failed for Frame Id = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, WifiDirectGetVSIEFrameID(eWifiDirectVSIEFrameId), WifiDirectGetError(nRet));
			return 1;
		}

		nRet = wifi_direct_get_vsie(eWifiDirectVSIEFrameId, &get_vsie_str);
		if ( nRet != WIFI_DIRECT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] wifi_direct_get_vsie failed for Frame Id = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, WifiDirectGetVSIEFrameID(eWifiDirectVSIEFrameId), WifiDirectGetError(nRet));
			FREE_MEMORY(get_vsie_str);
			return 1;
		}

		if(strcmp(get_vsie_str, set_vsie_str))
		{
			FPRINTF("[Line : %d][%s] wifi_direct_get_vsie error = value returned [ %s ] is not correct\\n", __LINE__, API_NAMESPACE, get_vsie_str);
			FREE_MEMORY(get_vsie_str);
			return 1;
		}

		nRet = wifi_direct_remove_vsie(eWifiDirectVSIEFrameId, set_vsie_str);
		if ( nRet != WIFI_DIRECT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] wifi_direct_remove_vsie failed for Frame Id = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, WifiDirectGetVSIEFrameID(eWifiDirectVSIEFrameId), WifiDirectGetError(nRet));
			FREE_MEMORY(get_vsie_str);
			return 1;
		}
		FREE_MEMORY(get_vsie_str);
	}

	WifiDirectTerminateService();
	return 0;
}

//& purpose: Starts discovery to find all P2P capable devices using specified frequency, asynchronous.
//& type: auto
/**
* @testcase 			ITc_wifi_direct_start_discovery_specific_freq_p
* @since_tizen			4.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Starts discovery to find all P2P capable devices using specified frequency, asynchronous.
* @scenario			Initialize wifi-direct\n
*				Invoke wifi_direct_start_discovery_specific_freq with valid parameters.\n
* @apicovered			wifi_direct_start_discovery_specific_freq
* @passcase			Whenwifi_direct_start_discovery_specific_freq is successful and return valid data
* @failcase			If target API fails or return invalid value
* @precondition			none
* @postcondition		none
*/

int ITc_wifi_direct_start_discovery_specific_freq_p(void)
{
	int nRet = WIFI_DIRECT_ERROR_NONE;
	bool listen_only = false;
	int timeout = 10;
	int frequency = 2412;

	if ( false == WifiDirectReadyService() )
	{
		if ( true == g_bSkipTestCaseWithPass )
		{
			return 0;
		}
		return 1;
	}

	nRet = wifi_direct_start_discovery_specific_freq(listen_only, timeout, frequency);
	PRINT_RESULT_CLEANUP(WIFI_DIRECT_ERROR_NONE, nRet, "wifi_direct_start_discovery_specific_freq", WifiDirectGetError(nRet), WifiDirectTerminateService());

	WifiDirectTerminateService();
	return 0;
}

/** @} */

