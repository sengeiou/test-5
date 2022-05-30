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
#ifndef _ITS_NSD_COMMON_H_
#define _ITS_NSD_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <dns-sd.h>
#include <ssdp.h>
#include <glib.h>
#include <app.h>
/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

#define FEATURE_SSDP			"http://tizen.org/feature/network.service_discovery.ssdp"
#define FEATURE_DNSSD			"http://tizen.org/feature/network.service_discovery.dnssd"
#define GMAINTIMEOUT			20000 
#define API_NAMESPACE			"NSD_ITC"
#define TIMEOUT_CB				20000

bool g_bNsdInitialize;
bool g_bFeatureNotSupported;
bool g_bFeatureSupported;
bool g_bFeatureMismatched;
bool g_bCallbackResult;
GMainLoop *g_pMainLoop;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureNotSupported)\
	{\
		FPRINTF("[Line : %d][%s][ NOT SUPPORTED ] Required feature of SSDP is not supported. So leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( g_bFeatureMismatched )\
	{\
		FPRINTF("[Line : %d][%s] Feature Mismatch in SSDP. So leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	if ( !g_bNsdInitialize )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of ssdn initialize failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define CHECK_HANDLE_INT(Handle, API) {\
	if ( Handle < 0)\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is less than zero\\n", __LINE__, API_NAMESPACE, API);\
	return 1;\
}\
}

#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pMainLoop = NULL;\
}

gboolean Timeout(gpointer data);
char* NsdDnsSdGetError(int nRet);
char* NsdSsdpGetError(int nRet);
/** @} */
#endif  //_ITS_NSD_COMMON_H_
