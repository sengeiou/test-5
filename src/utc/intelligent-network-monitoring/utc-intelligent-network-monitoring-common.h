/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _INTELLIGENT_NETWORK_MONITORING_COMMON_H_
#define _INTELLIGENT_NETWORK_MONITORING_H_

#include <tct_common.h>
#include <inm.h>
#include <system_info.h>
#include <glib.h>
#include <dlog.h>


#define INM_DEBUG                   1
#define GMAINTIMEOUT                7000
#define FEATURE_INM	                "http://tizen.org/feature/network.inm"
#define FEATURE_WIFI                "http://tizen.org/feature/network.wifi"
#define FEATURE_ETHERNET            "http://tizen.org/feature/network.ethernet"
#define FEATURE_TELEPHONY           "http://tizen.org/feature/network.telephony"
#define FEATURE_BT_TETHERING        "http://tizen.org/feature/network.tethering.bluetooth"
#define CALLBACK_RETURN             "callback return"

#define ARP_REQUEST_PACKET_INTERVAL 5
#define DEFAULT_ARP_REQUEST_IP_STR "192.168.0.1"
#define INVALID_ARP_REQUEST_IP_STR "192.0.0.8"
#define REACHABILITY_TEST_URL "www.linuxfoundation.org"

//#define WIFI_EAP_USERNAME           "EAPUserName"
//#define WIFI_EAP_PASSPHRASE         "EAPPassphrase"
//#define WIFI_EAP_CA_CERT            "EAPCACertificate"

GMainLoop *g_pMainLoop;
guint g_nTimeoutId;
int g_nCallbackRet;

bool g_bFeatureInm;
bool g_bFeatureWifi;
bool g_bFeatureEthernet;
bool g_bFeatureTelephony;
bool g_bFeatureBttethering;
bool g_bFeatureAllNotSupported;

inm_h g_hInm;
inm_connection_h profile_temp;
inm_connection_h g_hConnection;
inm_link_h g_hLink;
inm_link_address_h g_hAddress;
inm_link_route_h g_hRoute;

bool g_arp_requested_ip_found;
char *arp_requested_ip_str;
bool g_gateway_found;
bool g_dns_lookup_finished;
bool g_default_url_found;
bool g_user_requested_url_found;

#define RUN_GMAIN_LOOP(timeout_fn, user_data) do {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	g_nTimeoutId = g_timeout_add(GMAINTIMEOUT, (timeout_fn), (user_data));\
	if (INM_DEBUG) {\
		FPRINTF("[%s:%d] Run mainloop [%p]\\n", __FILE__, __LINE__, g_pMainLoop);\
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Run mainloop [%p]", __FILE__, __LINE__, g_pMainLoop);\
	}\
	g_main_loop_run(g_pMainLoop);\
	if (g_nTimeoutId != 0)\
		g_source_remove(g_nTimeoutId);\
		g_nTimeoutId = 0;\
	g_pMainLoop = NULL;\
} while (0)

#define QUIT_GMAIN_LOOP() do {\
		if (g_pMainLoop) {\
			if (INM_DEBUG) {\
				FPRINTF("[%s:%d] Quit mainloop [%p]\\n", __FILE__, __LINE__, g_pMainLoop);\
				dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Quit mainloop [%p]", __FILE__, __LINE__, g_pMainLoop);\
			}\
			g_main_loop_quit(g_pMainLoop);\
		}\
	} while (0)

#define PRINT_RETURN(api, ret) do {\
		if (INM_DEBUG) {\
			FPRINTF("[%s:%d] %s returned = %s\\n",\
				__FILE__, __LINE__, api, inm_get_error(ret));\
			dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] %s returned = %s",\
				__FILE__, __LINE__, api, inm_get_error(ret));\
		}\
	} while (0)

#define CHECK_RETURN(api, ret, val) do{\
		if (INM_DEBUG) {\
			if (ret != val) {\
				FPRINTF("[%s:%d] %s failed, error returned = %s\\n",\
					__FILE__, __LINE__, api, inm_get_error(ret));\
				dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] %s failed, error returned = %s",\
					__FILE__, __LINE__, api, inm_get_error(ret));\
				return 1;\
			} else {\
				PRINT_RETURN(api, ret);\
			}\
		}\
	} while (0)

#define IS_EQUAL(api, src, dst) do{\
		if (INM_DEBUG) {\
			if (src != dst) {\
				FPRINTF("[%s:%d] %s failed, value is not equal\\n",\
					__FILE__, __LINE__, api);\
				dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] %s failed, value is not equal",\
					__FILE__, __LINE__, api);\
				return 1;\
			}\
		}\
	} while (0)

gboolean inm_callback_timeout(gpointer data);
char* inm_get_error(int error);
bool inm_get_value_from_configfile(char* key, char* value);
bool inm_check_feature_supported(char *key);
int inm_get_any_profile(inm_connection_h *profile);
int inm_get_current_link(inm_link_h *link);
int inm_save_any_address(inm_link_h link);
int inm_save_any_route(inm_link_h link);

void inm_wifi_state_changed_callback(inm_wifi_state_e result, void* user_data);
void inm_connection_state_changed_callback(inm_connection_state_e state, void* user_data);
bool inm_foreach_found_ap_callback(inm_connection_h ap, void *user_data);
bool inm_wifi_ap_foreach_vsie_callback(unsigned char *vsie_bytes, int vsie_len, void *user_data);
void inm_set_ethernet_cable_state_changed_callback(inm_ethernet_cable_state_e result, void* user_data);
void inm_set_ip_conflict_callback(char *if_name, char *ip, inm_ip_conflict_state_e state, void *user_data);
void inm_set_congestion_level_callback(inm_congestion_level_e result, void* user_data);
void inm_set_retry_tx_rate_callback(int rate, void* user_data);
void inm_set_channel_interference_callback(int freq, double channel_intf, void* user_data);
void inm_set_cellular_state_changed_callback(inm_cellular_state_e result, void* user_data);
void inm_set_wifi_state_changed_callback(inm_wifi_state_e result, void* user_data);
void inm_set_ethernet_state_changed_callback(inm_ethernet_state_e result, void* user_data);
bool inm_foreach_link_callback(inm_link_h link, void *user_data);
bool inm_foreach_address_callback(inm_link_address_h address, void *user_data);
bool inm_foreach_route_callback(inm_link_route_h route, void *user_data);
#endif  /* _INTELLIGENT_NETWORK_MONITORING_COMMON_H_ */

