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
#ifndef _ITS_WEBRTC_COMMON_H_
#define _ITS_WEBRTC_COMMON_H_
#define TEST_BUFFERED_AMOUNT_THRESHOLD 65535

//Add test package related includes here
#include "tct_common.h"
#include <glib.h>
#include <webrtc.h>
#include <dlog.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/
//Add helper function defines here
#define API_NAMESPACE				"WEBRTC_ITC"
#define TIMEOUT_CB				10000
//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if (!g_bWebRTCCreation) {\
		FPRINTF("[Line : %d][%s] Precondition of webrtc failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define RUN_POLLING_LOOP(x_mainloop, x_cb_called)\
do {\
	if(x_cb_called)\
		break;\
	x_mainloop = g_main_loop_new(NULL, false);\
	guint timeout_id = g_timeout_add(TIMEOUT_CB, Timeout, x_mainloop);\
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] call g_main_loop_run(), mainloop[%p]", __FUNCTION__, __LINE__, x_mainloop);\
	g_main_loop_run(x_mainloop);\
	g_source_remove(timeout_id);\
	x_mainloop = NULL;\
} while (0)

#define QUIT_LOOP(x_mainloop)\
do {\
	if (!x_mainloop)\
		break;\
	dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] call g_main_loop_quit(), mainloop[%p]", __FUNCTION__, __LINE__, x_mainloop);\
	g_main_loop_quit(x_mainloop);\
} while (0)

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if (!Handle) {\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

typedef struct _callback_data {
	GMainLoop *mainloop;
	bool is_invoked;
} callback_data;

bool g_bWebRTCCreation;
char *g_pszFilePath;
webrtc_h g_hWebRtcHandle;
gboolean Timeout(gpointer data);
char* WebRtcGetError(int nErrorType);
unsigned int GetDataFromFile();
/** @} */
#endif  //_ITS_WEBRTC_COMMON_H_
