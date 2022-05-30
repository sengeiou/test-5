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
#ifndef _ITS_WIFI_MANAGER_COMMON_H_
#define _ITS_WIFI_MANAGER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <wifi-manager.h>
#include <system_info.h>
#include <glib.h>
#include <dlog.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/


#define API_NAMESPACE               "WIFI_MANAGER_ITC"
#define MICROSECONDS_PER_SECOND     1000000
#define MINCOUNT                    1
#define TIMEOUT_CB                  20000
#define PRE_CONNECT_RETRY           3
#define WIFI_CONFIG_LEN             64
#define WIFI_AP_NAME                "AccessPoint"
#define WIFI_AP_PASSPHRASE          "Passphrase"
#define WIFI_EAP_USERNAME           "EAPUserName"
#define WIFI_EAP_PASSPHRASE         "EAPPassphrase"
#define WIFI_EAP_CA_CERT            "EAPCACertificate"
#define WIFI_CONFIG_NAME            "ConfigName"
#define WIFI_CONFIG_PASSWORD        "ConfigPass"
#define WIFI_CONFIG_PROXY           "192.168.1.1"
#define WIFI_CONFIG_AN_ID           "Identity"
#define WIFI_CONFIG_IDENTITY        "username@domain.edu"
#define WIFI_CONFIG_SUBJECT_MATCH   "/CN=server.example.com"
#define WIFI_CONFIG_CA_CERT_FILE    "/etc/ssl/certs/ca-certificates.crt"
#define WIFI_CONFIG_PRIVATE_KEY_FILE 	"/etc/ssl/certs/client.key"
#define WIFI_CONFIG_PRIVATE_KEY     "-----BEGIN RSA PRIVATE KEY-----\
                                    MIIEpQIBAAKCAQEA3Tz2mr7SZiAMfQyuvBjM9Oi..Z1BjP5CE/Wm/Rr500P\
                                    engiVoWc/hkj8SBHZz1n1xLN7KDf8ySU06MDggB..hJ+gXJKy+gf3mF5Kmj\
                                    DtkpjGHQzPF6vOe907y5NQLvVFGXUq/FIJZxB8k..fJdHEm2M4=\
                                    -----END RSA PRIVATE KEY-----"
#define WIFI_CONFIG_CLIENT_CERT     "-----BEGIN CERTIFICATE-----\
                                    MIICnjCCAgegAwIBAgIBAjANBgkqhkiG9w0BAQUFADBXMQswCQYDVQQGEwJBVTET\
                                    fr+gVfGD6NCsP2t0t5q74/dOBmormD+clrFEj4jDzcWm3XTemkl7QQhnktRG4kQjNFE=\
                                    -----END CERTIFICATE-----"
#define FEATURE_WIFI                "http://tizen.org/feature/network.wifi"
#define FEATURE_WIFI_TDLS           "http://tizen.org/feature/network.wifi.tdls"
#define VALID_VALUE                 "valid value check"


bool g_bFeatureWifi;
bool g_bFeatureWifiTDLS;
bool g_bIsFeatureMismatched;
bool g_bWifiManagerCreation;
bool g_bWifiManagerCB;
bool g_bWifiManagerCBHit;
bool g_bWifiManagerScanFinishCB;
bool g_bWifiManagerVsieCB;

wifi_manager_h g_hWifi;
wifi_manager_ap_h g_hWifiAP;
wifi_manager_config_h g_hWifiConfig;
GMainLoop *g_pWifiManagerMainLoop;
int g_nCallbackRet;
int nTimeoutId;

#define START_TEST_CHECK_INITIALIZE {\
	FPRINTF("[Line:%d][%s] Starting test check initialize : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Starting test check initialize : %s", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bIsFeatureMismatched ) {\
		FPRINTF("[Line:%d][%s] Feature Mismatch Error\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Mismatch Error", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	if ( !g_bFeatureWifi) {\
		FPRINTF("[Line : %d][%s] Feature Unsupported\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Unsupported", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( !g_bWifiManagerCreation ) {\
		FPRINTF("[Line:%d][%s] Precondition Failed\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR,"NativeTCT", "[Line:%d][%s] Precondition Failed", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
	g_pWifiManagerMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, WifiManagerTimeout, g_pWifiManagerMainLoop);\
	FPRINTF("[Line:%d][%s] Run mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pWifiManagerMainLoop);\
	dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Run mainloop [%p]", __LINE__, __FUNCTION__, g_pWifiManagerMainLoop);\
	g_main_loop_run(g_pWifiManagerMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pWifiManagerMainLoop = NULL;\
}


#define QUIT_GMAIN_LOOP {\
	if (g_pWifiManagerMainLoop)\
{\
	FPRINTF("[Line:%d][%s] Quit mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pWifiManagerMainLoop);\
	dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Quit mainloop [%p]", __LINE__, __FUNCTION__, g_pWifiManagerMainLoop);\
	g_main_loop_quit(g_pWifiManagerMainLoop);\
}\
}

#define CHECK_RETURN(val, ret, api, error) {\
	if (ret != val) {\
		FPRINTF("[%s:%d] %s failed, error returned = %s\\n",\
			__FILE__, __LINE__, api, error);\
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] %s failed, error returned = %s",\
			__FILE__, __LINE__, api, error);\
		return 1;\
	} else {\
		FPRINTF("[%s:%d] %s\\n",\
			__FILE__, __LINE__, api);\
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s",\
			__FILE__, __LINE__, api);\
	}\
}

#define PRINT_RETURN(api, ret) {\
		FPRINTF("[%s:%d] %s returned = %s\\n",\
			__FILE__, __LINE__, api, WifiManagerGetError(ret));\
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s returned = %s",\
			__FILE__, __LINE__, api, WifiManagerGetError(ret));\
}


bool wifi_manager_check_feature_supported(char *key);
void wifi_manager_activated_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_activated_callback_without_mainloop(wifi_manager_error_e result, void* user_data);
void wifi_manager_deactivated_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_deactivated_callback_without_mainloop(wifi_manager_error_e result, void* user_data);
void wifi_manager_activated_with_picker_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_scanned_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_background_scanned_callback(wifi_manager_error_e result, void* user_data);
bool wifi_manager_foreach_found_ap_callback(wifi_manager_ap_h ap, void *user_data);
void wifi_manager_scanned_specific_ap_callback(wifi_manager_error_e result, void* user_data);
bool wifi_manager_foreach_found_specific_ap_callback(wifi_manager_ap_h ap, void *user_data);
bool wifi_manager_found_ap_callback(wifi_manager_ap_h ap, void *user_data);
void wifi_manager_connected_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_disconnected_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_device_state_changed_callback(wifi_manager_device_state_e state, void* user_data);
void wifi_manager_connection_state_changed_callback(wifi_manager_connection_state_e state, wifi_manager_ap_h ap, void* user_data);
void wifi_manager_rssi_level_changed_callback(wifi_manager_rssi_level_e rssi_level, void* user_data);
bool wifi_manager_foreach_configuration_cb(const wifi_manager_config_h config, void *user_data);
void wifi_manager_tdls_state_changed_callback(wifi_manager_tdls_state_e state, char* peer_mac_addr, void* user_data);
bool wifi_manager_ap_ipv6_address_callback(char *ipv6_address, void *user_data);
void wifi_manager_scan_state_changed_callback(wifi_manager_scan_state_e state, void* user_data);
void wifi_manager_bssid_scan_finished_callback(wifi_manager_error_e error_code, void *user_data);
bool wifi_manager_foreach_found_bssid_ap_callback(wifi_manager_ap_h ap, void *user_data);
void wifi_manager_multi_scan_callback(wifi_manager_error_e result, void* user_data);
bool wifi_manager_ap_foreach_vsie_callback(unsigned char *vsie_bytes, int vsie_len, void *user_data);
bool wifi_manager_foreach_found_bssid_callback(const char *bssid, int rssi, int freq, void *user_data);
void wifi_manager_forget_ap_async_callback(wifi_manager_error_e result, void *user_data);
int wifi_manager_pre_activate(void);
int wifi_manager_pre_deactivate(void);
int wifi_manager_pre_connect(void);

char* WifiManagerGetError(int nRet);
gboolean WifiManagerTimeout(gpointer data);


/** @} */
#endif  //_ITS_WIFI_MANAGER_COMMON_H_
