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
#ifndef _ITS_HTTP_COMMON_H_
#define _ITS_HTTP_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <fcntl.h>
#include <net_connection.h>
#include <system_info.h>
#include <http.h>
#include <glib.h>

#define API_NAMESPACE			"HTTP_ITC"
#define MICROSECONDS_PER_SECOND	1000000
#define MINCOUNT				1
#define TIMEOUT_CB				30000
#define HTTP_FEATURE 			"http://tizen.org/feature/network.internet"

GMainLoop *g_pHttpMainLoop;
bool g_bFeatureUnsupported;
bool g_bHttpInit;
bool g_bCallbackHit;

#ifdef WEARABLE
#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if(g_bFeatureUnsupported)\
	{\
		FPRINTF("[Line : %d][%s] Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( !g_bHttpInit )\
	{\
		FPRINTF("[Line : %d][%s] Iotcon connection failed , Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}
#else 
#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bHttpInit )\
{\
	FPRINTF("[Line : %d][%s] Precondition of http failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}
#endif

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	FreeResource;\
	return 1;\
}\
}

#define RUN_POLLING_LOOP {\
	if ( !g_bCallbackHit )\
{\
	g_pHttpMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, httpTimeout, g_pHttpMainLoop);\
	g_main_loop_run(g_pHttpMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pHttpMainLoop = NULL;\
}\
}


/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

//Add helper function declarations here



gboolean httpTimeout(gpointer data);
char* HttpGetError(int nRet);

/** @} */
#endif  //_ITS_HTTP_COMMON_H_
