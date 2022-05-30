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

#ifndef _INM_COMMON_H_
#define _INM_H_

#include "tct_common.h"
#include <inm.h>
#include <system_info.h>
#include <glib.h>
#include <dlog.h>


/** @addtogroup itc-dlog
*  @ingroup itc
*  @{
*/

bool g_bDlogCreation;

#define INM_DEBUG                   	1
#define GMAINTIMEOUT                	20000
#define TIMEOUT_CB                  	20000
#define API_NAMESPACE			"INM_ITC"
#define MAXENUMSIZE				50
#define SETENUM					1
#define GETENUM					0
#define FEATURE_INM	                "http://tizen.org/feature/network.inm"
#define FEATURE_WIFI                	"http://tizen.org/feature/network.wifi"
#define FEATURE_ETHERNET            	"http://tizen.org/feature/network.ethernet"
#define FEATURE_TELEPHONY          	"http://tizen.org/feature/network.telephony"
#define FEATURE_BT_TETHERING        	"http://tizen.org/feature/network.tethering.bluetooth"
#define FEATURE_NOT_SUPPORTED		999
#define ARP_REQUEST_PACKET_INTERVAL 	5
#define DEFAULT_ARP_REQUEST_IP_STR 	"192.168.0.1"
#define REACHABILITY_TEST_URL		"www.linuxfoundation.org"

bool g_bFeatureInm;
bool g_bFeatureWifi;
bool g_bFeatureEthernet;
bool g_bFeatureTelephony;
bool g_bFeatureBttethering;
bool g_bFeatureAllNotSupported;
bool g_bInmCreation;
bool g_bIsFeatureMismatched;
bool g_nCallbackRet;
bool g_nCallbackFail;
bool g_bFeatureNotSupported;
bool g_bCapiNetworkInmCBHit;

inm_h g_hInm;
inm_h g_hInmHandle;
inm_link_address_h g_hAddressHandle;
inm_link_route_h g_hRouteHandle;
inm_link_h g_hLinkHandle;
inm_connection_h g_hProfileTemp;
inm_connection_h g_hConnection;
GMainLoop *g_pCapiNetworkInmMainLoop;
int nTimeoutId;

bool g_bGatewayFound;
bool g_bDnsLookupFinished;
bool g_bDefaultUrlFound;
char *g_pszArpRequestedIpStr;
bool g_bArpRequestedIpFound;

#define START_TEST {\
	if(g_bFeatureNotSupported)\
	{\
		FPRINTF("[Line:%d][%s] FeatureInm not supported\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
\
	if( g_bIsFeatureMismatched )\
	{\
		FPRINTF("[Line:%d][%s] Feature Mismatch Error\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Mismatch Error", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bInmCreation )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of inm failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}


#define RUN_POLLING_LOOP {\
	g_pCapiNetworkInmMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, CapiNetworkInmTimeout, g_pCapiNetworkInmMainLoop);\
	FPRINTF("[Line:%d][%s] Run mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pCapiNetworkInmMainLoop);\
	g_main_loop_run(g_pCapiNetworkInmMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pCapiNetworkInmMainLoop = NULL;\
}


#define QUIT_GMAIN_LOOP {\
	if (g_pCapiNetworkInmMainLoop)\
{\
	FPRINTF("[Line:%d][%s] Quit mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pCapiNetworkInmMainLoop);\
	g_main_loop_quit(g_pCapiNetworkInmMainLoop);\
}\
}

#define PRINT_RETURN(api, ret) {\
	if (INM_DEBUG) {\
		FPRINTF("[Line : %d][%s] %s returned = %s\\n",\
			__LINE__, API_NAMESPACE, api, InmGetError(ret));\
		dlog_print(DLOG_INFO, "NativeTCT", "[Line : %d][%s] %s returned = %s",\
			__LINE__, API_NAMESPACE, api, InmGetError(ret));\
	}\
}

#define PRINT_RETURN_CLEANUP(api, ret, FreeResource) {\
	if (INM_DEBUG) {\
		FPRINTF("[Line : %d][%s] %s returned = %s\\n",\
			__LINE__, API_NAMESPACE, api, InmGetError(ret));\
		dlog_print(DLOG_INFO, "NativeTCT", "[Line : %d][%s] %s returned = %s",\
			__LINE__, API_NAMESPACE, api, InmGetError(ret));\
		FreeResource;\
	}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define PRINT_RESULT_CHECK(nRetVal, eCompare, API, Error) {\
	if ( nRetVal == eCompare )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
	}\
	else \
	{\
		FPRINTF("[Line : %d][%s] %s failed due to feature support mismatch.\\n", __LINE__, API_NAMESPACE, API);\
		return 1;\
	}\
}

//Add test package related includes here
char* InmGetError(int error);
char* InmGetDisconnectReason(int error);
int InmGetAnyProfile(inm_connection_h *profile);

bool InmConnectionStateChangedCallback(inm_connection_state_e state, void* user_data);
bool InmForeachFoundApCallback(inm_connection_h ap, void *user_data);
void InmSetEthernetCableStateChangedCallback(inm_ethernet_cable_state_e result, void* user_data);
void InmSetIpConflictCallback(char *if_name, char *ip, inm_ip_conflict_state_e state, void *user_data);
void InmWifiStateChangedCallback(inm_wifi_state_e result, void* user_data);
void InmWifiScanStateChangedCallback(inm_wifi_scan_state_e state, void* user_data);
bool InmWifiApForeachVsieCallback(unsigned char *vsie_bytes, int vsie_len, void *user_data);
void InmSetCongestionLevelCallback(inm_congestion_level_e result, void* user_data);
void InmSetRetryTxRateCallback(int rate, void* user_data);
void InmSetChannelInterferenceCallback(int freq, double channel_intf, void* user_data);
void InmSetCellularStateChangedCallback(inm_cellular_state_e result, void* user_data);
void InmSetWifiStateChangedCallback(inm_wifi_state_e result, void* user_data);
void InmSetEthernetStateChangedCallback(inm_ethernet_state_e result, void* user_data);
int InmGetCurrentLink(inm_link_h *hRefLinkHandle);
gboolean CapiNetworkInmTimeout(gpointer data);
/** @} */
#endif  //_ITS_INM_COMMON_H_
