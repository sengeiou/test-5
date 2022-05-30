//
// Copyright (c) 2022 Samsung Electronics Co., Ltd.
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
#ifndef _ITS_MEDIAEDITOR_COMMON_H_
#define _ITS_MEDIAEDITOR_COMMON_H_

#include "tct_common.h"
#include <glib.h>
#include <media_editor.h>
#include <dlog.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"MEDIAEDITOR_ITC"
#define TIMEOUT_CB	40000
#define GET_DISPLAY(x) (void*)(x)
#define FEATURE_NAME_DISPLAY "http://tizen.org/feature/display"

#define START_TEST {\
	FPRINTF("[Line:%d][%s] Starting test check initialize : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Starting test check initialize : %s", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if (!g_bMediaEditorHandleCreated) {\
		FPRINTF("[Line : %d][%s] Precondition of mediaeditor failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR,"NativeTCT", "[Line:%d][%s] Precondition Failed", __LINE__, API_NAMESPACE);\
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

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if (!Handle) {\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

bool g_bMediaEditorHandleCreated;
bool g_bMediaEditorCallback;
GMainLoop *g_pMainLoop;

mediaeditor_h g_hMediaEditorHandle;
gboolean Timeout(gpointer data);
char* MediaEditorGetError(int nErrorType);
char* MediaEditorGetState(int nRet);

/** @} */
#endif  //_ITS_MEDIAEDITOR_COMMON_H_
