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

#ifndef _WIFI_MANAGER_COMMON_H_
#define _WIFI_MANAGER_COMMON_H_

#include <tct_common.h>
#include <wifi-manager.h>
#include <system_info.h>
#include <glib.h>
#include <dlog.h>


#define WIFI_MANAGER_DEBUG			1
#define CONFIG_VALUE_LEN_MAX		1024
#define GMAINTIMEOUT 				10000
#define PRE_CONNECT_RETRY 			3
#define WIFI_ACTIVATION_RETRY 		2
#define WIFI_CONFIG_LEN				64
#define WIFI_AP_NAME				"AccessPoint"
#define WIFI_AP_PASSPHRASE			"Passphrase"
#define WIFI_EAP_USERNAME			"EAPUserName"
#define WIFI_EAP_PASSPHRASE			"EAPPassphrase"
#define WIFI_EAP_CA_CERT			"EAPCACertificate"
#define WIFI_CONFIG_NAME			"ConfigName"
#define WIFI_CONFIG_PASSWORD		"ConfigPass"
#define WIFI_CONFIG_PROXY			"192.168.1.1"
#define WIFI_CONFIG_AN_ID			"Identity"
#define WIFI_CONFIG_IDENTITY		"username@domain.edu"
#define WIFI_CONFIG_SUBJECT_MATCH	"/CN=server.example.com"
#define WIFI_CONFIG_CA_CERT_FILE 	"/etc/ssl/certs/ca-certificates.crt"
#define WIFI_CONFIG_PRIVATE_KEY_FILE 	"/etc/ssl/certs/client.key"
#define WIFI_CONFIG_PRIVATE_KEY 	"-----BEGIN RSA PRIVATE KEY-----\
									MIIEpQIBAAKCAQEA3Tz2mr7SZiAMfQyuvBjM9Oi..Z1BjP5CE/Wm/Rr500P\
									engiVoWc/hkj8SBHZz1n1xLN7KDf8ySU06MDggB..hJ+gXJKy+gf3mF5Kmj\
									DtkpjGHQzPF6vOe907y5NQLvVFGXUq/FIJZxB8k..fJdHEm2M4=\
									-----END RSA PRIVATE KEY-----"
#define WIFI_CONFIG_CLIENT_CERT 	"-----BEGIN CERTIFICATE-----\
									MIICnjCCAgegAwIBAgIBAjANBgkqhkiG9w0BAQUFADBXMQswCQYDVQQGEwJBVTET\
									fr+gVfGD6NCsP2t0t5q74/dOBmormD+clrFEj4jDzcWm3XTemkl7QQhnktRG4kQjNFE=\
									-----END CERTIFICATE-----"
#define FEATURE_WIFI				"http://tizen.org/feature/network.wifi"
#define FEATURE_WIFI_TDLS			"http://tizen.org/feature/network.wifi.tdls"
#define CALLBACK_RETURN				"callback return"
#define VALID_VALUE					"valid value check"

GMainLoop *g_pMainLoop;
guint g_nTimeoutId;
int g_nCallbackRet;

bool g_bFeatureWifi;
bool g_bFeatureWifiTDLS;

wifi_manager_h g_hWifi;
wifi_manager_ap_h g_hWifiAP;
wifi_manager_config_h g_hWifiConfig;

#define RUN_GMAIN_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	g_nTimeoutId = g_timeout_add(GMAINTIMEOUT, wifi_manager_callback_timeout, g_pMainLoop);\
	FPRINTF("[Line:%d][%s] Run mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pMainLoop);\
	dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Run mainloop [%p]", __LINE__, __FUNCTION__, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(g_nTimeoutId);\
	g_pMainLoop = NULL;\
}

#define QUIT_GMAIN_LOOP {\
	if (g_pMainLoop)\
{\
		FPRINTF("[Line:%d][%s] Quit mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pMainLoop);\
		dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Quit mainloop [%p]", __LINE__, __FUNCTION__, g_pMainLoop);\
		g_main_loop_quit(g_pMainLoop);\
		g_pMainLoop = NULL;\
}\
}

#define PRINT_RETURN(api, ret) {\
	if (WIFI_MANAGER_DEBUG) {\
		FPRINTF("[%s:%d] %s returned = %s\\n",\
			__FILE__, __LINE__, api, wifi_manager_get_error(ret));\
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s returned = %s",\
			__FILE__, __LINE__, api, wifi_manager_get_error(ret));\
	}\
}

#define CHECK_RETURN(api, ret, val) {\
	if (ret != val) {\
		FPRINTF("[%s:%d] %s failed, error returned = %s\\n",\
			__FILE__, __LINE__, api, wifi_manager_get_error(ret));\
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] %s failed, error returned = %s",\
			__FILE__, __LINE__, api, wifi_manager_get_error(ret));\
		return 1;\
	} else {\
		FPRINTF("[%s:%d] %s\\n",\
			__FILE__, __LINE__, api);\
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s",\
			__FILE__, __LINE__, api);\
	}\
}

gboolean wifi_manager_callback_timeout(gpointer data);
char* wifi_manager_get_error(int error);
bool wifi_manager_get_value_from_configfile(char* key, char* value);

bool wifi_manager_check_feature_supported(char *key);
void wifi_manager_activated_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_deactivated_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_activated_with_picker_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_scanned_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_background_scanned_callback(wifi_manager_error_e result, void* user_data);
bool wifi_manager_foreach_found_ap_callback(wifi_manager_ap_h ap, void *user_data);
void wifi_manager_scanned_specific_ap_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_bssid_scanned_callback(wifi_manager_error_e result, void* user_data);
bool wifi_manager_foreach_found_specific_ap_callback(wifi_manager_ap_h ap, void *user_data);
bool wifi_manager_foreach_found_bssid_ap_callback(wifi_manager_ap_h ap, void *user_data);
bool wifi_manager_found_ap_callback(wifi_manager_ap_h ap, void *user_data);
void wifi_manager_connected_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_disconnected_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_device_state_changed_callback(wifi_manager_device_state_e state, void* user_data);
void wifi_manager_scan_state_changed_callback(wifi_manager_scan_state_e state, void* user_data);
void wifi_manager_connection_state_changed_callback(wifi_manager_connection_state_e state, wifi_manager_ap_h ap, void* user_data);
void wifi_manager_rssi_level_changed_callback(wifi_manager_rssi_level_e rssi_level, void* user_data);
bool wifi_manager_foreach_configuration_cb(const wifi_manager_config_h config, void *user_data);
void wifi_manager_tdls_state_changed_callback(wifi_manager_tdls_state_e state, char* peer_mac_addr, void* user_data);
void wifi_manager_tdls_discovered_callback(wifi_manager_tdls_discovery_state_e state, char* peer_mac_addr, void* user_data);
bool wifi_manager_ap_ipv6_address_callback(char *ipv6_address, void *user_data);
void wifi_manager_forget_ap_callback(wifi_manager_connection_state_e state, wifi_manager_ap_h ap, void *user_data);
void wifi_manager_forget_ap_async_callback(wifi_manager_error_e result, void *user_data);
void wifi_manager_multi_scan_callback(wifi_manager_error_e result, void* user_data);
void wifi_manager_ip_conflict_callback(char *mac, wifi_manager_ip_conflict_state_e state, void *user_data);
bool wifi_manager_ap_foreach_vsie_callback(unsigned char *vsie_bytes, int vsie_len, void *user_data);
bool wifi_manager_ap_foreach_bssid_list_callback(const char *bssid, int rssii, int freq, void *user_data);

int wifi_manager_pre_activate(void);
int wifi_manager_pre_deactivate(void);
int wifi_manager_pre_connect(void);

#endif  /* _WIFI_MANAGER_COMMON_H_ */

