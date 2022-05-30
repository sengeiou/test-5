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
#ifndef _ITS_CION_COMMON_H_
#define _ITS_CION_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <cion.h>
#include <glib.h>
#include <dlog.h>
#include <app_manager.h>
#include <app_control.h>
#include <app.h>

#define API_NAMESPACE				"CION_ITC"
#define TIMEOUT_CB				60000
#define TIMEOUT_CB1				60000
/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/
#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define START_TEST_PAYLOAD {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bCionPayloadCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of cion failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define RUN_POLLING_LOOP {\
	if(g_bCallbackCalled == false)\
	{\
		g_pMainLoop = g_main_loop_new(NULL, false);\
		g_nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pMainLoop);\
		g_main_loop_run(g_pMainLoop);\
		g_source_remove(g_nTimeoutId);\
		g_pMainLoop = NULL;\
	}\
}

#define RUN_POLLING_LOOP1 {\
	if(g_bCallbackCalled == false)\
	{\
		g_pMainLoop = g_main_loop_new(NULL, false);\
		g_nTimeoutId = g_timeout_add(TIMEOUT_CB1, Timeout, g_pMainLoop);\
		g_main_loop_run(g_pMainLoop);\
		g_source_remove(g_nTimeoutId);\
		g_pMainLoop = NULL;\
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
//Add helper function declarations here
bool g_bCionPayloadCreation;
int g_nTimeoutId;
static GMainLoop *g_pMainLoop = NULL;
bool g_bCallbackCalled;
gboolean Timeout(gpointer data);
char *CionGetError(int nResult);

/** @} */
#endif  //_ITS_CION_COMMON_H_
