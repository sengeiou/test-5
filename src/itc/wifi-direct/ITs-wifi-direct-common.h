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
#ifndef _ITS_WIFI_DIRECT_COMMON_H_
#define _ITS_WIFI_DIRECT_COMMON_H_

#include "tct_common.h"
#include <glib-object.h>
#include <glib.h>
#include <app.h>
#include <wifi-direct.h>

/** @addtogroup itc-wifi-direct
*  @ingroup itc
*  @{
*/

//Add test package related includes here
#define API_NAMESPACE						"WIFI_DIRECT_ITC"
#define PROCESS_TIME						4			 //4 sec
#define ARRAY_SIZE							1024
#define CALLBACK_DELAY						40000
#define FEATURE_WIFI_DIRECT					"http://tizen.org/feature/network.wifi.direct"
#define FEATURE_WIFI_DIRECT_DISPLAY			"http://tizen.org/feature/network.wifi.direct.display"
#define FEATURE_WIFI_DIRECT_SVC_DISC		"http://tizen.org/feature/network.wifi.direct.service_discovery"
#define WIFI_DIRECT_INFORMATION_OF_SERVICE1	"10"
#define WIFI_DIRECT_INFORMATION_OF_SERVICE2	"uuid:6859dede-8574-59ab-9332-123456789012::upnp:rootdevice"

#define WIFI_TYPE_SOURCE			7236
#define WIFI_TYPE_PRIMARY_SINK		7237
#define WIFI_TYPE_SECONDARY_SINK	7238
#define WIFI_TYPE_DUAL_ROLE			7239

#define MAC_ADDRESS		"0Ab32456d8"
 
extern bool g_bFeatureWifiDirect;
extern bool g_bFeatureWifiDirectDisplay;
extern bool g_bFeatureWifiDirectSrvcDiscovery;
extern bool g_bSkipTestCaseWithPass;

static GMainLoop *g_pMainLoop;

//Add helper function declarations here
#define START_TEST {\
	FPRINTF("[Line : %d][%s]Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define CHECK_UNSUPPORTED_ERROR_RETURN(bSupported, szApi)\
	if ( !bSupported )\
{\
	if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )\
{\
	FPRINTF("[Line : %d][%s] %s returned %s for unsupported feature\\n", __LINE__, API_NAMESPACE, szApi, WifiDirectGetError(nRet));\
	return 1;\
}\
	else\
{\
	FPRINTF("[Line : %d][%s] %s API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, szApi, WifiDirectGetError(nRet));\
	return 0;\
}\
}

#define RUN_POLLING_LOOP(szApiName) {\
	g_pMainLoop = g_main_loop_new(NULL, false); \
	nTimeoutId = g_timeout_add(CALLBACK_DELAY, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pMainLoop = NULL; \
}


char* WifiDirectGetError(int nRet);
bool WifiDirectReadyService();
bool WifiDirectTerminateService();
gboolean TimeoutFunction(gpointer data);
char* WifiDirectGetVSIEFrameID(wifi_direct_vsie_frames_e nFrameId);

/** @} */
#endif  //_ITS_WIFI_DIRECT_COMMON_H_
