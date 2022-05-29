//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#ifndef _ITS_CAPI_NETWORK_UA_COMMON_H_
#define _ITS_CAPI_NETWORK_UA_COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tct_common.h"

//Add test package related includes here
#include "user-awareness.h"
#include "user-awareness-type.h"

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/
//Add global variables here
ua_monitor_h g_hMonitor;
ua_user_h g_hUser;
ua_service_h g_hService;
bool g_bUaInit;
bool g_bFeatureByPass;
bool g_bIsUaFeatureSupported;
ua_service_h g_hService;
bool g_bCallBackHit;
GMainLoop *g_pMainLoop;
static char g_hServiceStr[] = {"ua.service.default"};


//Add Macros here
#define GMAINTIMEOUT                      30000 //30 seconds
#define API_NAMESPACE                     "UA_ITC"
#define UA_FEATURE                        "http://tizen.org/feature/user_awareness"
#define UA_LOCATION_FEATURE               "http://tizen.org/feature/user_awareness.location"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureByPass )\
	{\
		return 0;\
	}\
	if ( !g_bUaInit )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of capi_network_ua_service failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
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
#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	int nTtimeoutId = g_timeout_add(GMAINTIMEOUT, UaCallbackTimeout, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTtimeoutId);\
	g_pMainLoop = NULL;\
}
//Add CallBack function declarations here


//Add helper function declarations here
char* UaGetError(int nRet);
gboolean UaCallbackTimeout(gpointer data);
char* UaGetEnumMacTypeString(int nVal);
char* UaGetEnumSensorString(int nVal);
char* UaGetDetectionModeString(int nVal);
/** @} */
#endif  //_ITS_CAPI_NETWORK_UA_COMMON_H_
