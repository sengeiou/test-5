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
#ifndef _ITS_MEDIASTREAMRECORDER_COMMON_H_
#define _ITS_MEDIASTREAMRECORDER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <media/streamrecorder.h>
#include <system_info.h>
#include <dlog.h>
#include <glib.h>
#include <stdbool.h>
#include <math.h>
#include <app.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/
#define TIMEOUT_CB					10000
#define GMAINTIMEOUT				30000
#define PATH_LEN					1024
#define MEDIA_PATH_AUDIO			"short.mp3"
#define MEDIA_FILE_PATH				"I420_352x288.yuv"
#define API_NAMESPACE				"MEDIASTREAMRECORDER_ITC"
#define STREAMRECORDER_FEATURE		"http://tizen.org/feature/multimedia.stream_recorder"
#define SLEEP_TIME					3
#define MEDIA_DUMMY_PATH			"hello.mp4"
#define MAX_MEDIA_PACKET_CNT		20

bool g_bMediaStrRecorderConnect;
bool g_bCheckCb;
bool g_bStreamRecorderNotSupported;
bool g_bMismatch;
GMainLoop *g_pMainLoop;
gboolean TimeoutFunction(gpointer data);
long int g_ncount;
streamrecorder_h g_hRecorder;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bStreamRecorderNotSupported)\
	{\
		FPRINTF("[Line : %d][%s] Required feature of stream recorder is not supported. So leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( g_bMismatch )\
	{\
		FPRINTF("[Line : %d][%s] MediaStreaRecorder feature checker and streamrecorder_create returned different value. So leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	if ( !g_bMediaStrRecorderConnect )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of connecting to stream recorder failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nIotconTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nIotconTimeoutId);\
	g_pMainLoop = NULL;\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}


char* StreamRecorderGetError(int nRet);
char* MediaFormatGetError(int nRet);
bool StreamRecorderGetDataPath(char* pAppDataPath);
bool StreamRecoderAppendToAppDataPath(char* pInputPath, char* pFinalPath);
int SetParam(streamrecorder_h g_hRecorder);
char* MediaPacketGetError(int nRet);
int CreatePacketAndFormatData(streamrecorder_h g_hRecorder);
void DestroyPacketAndFormatData(void);
int SetParamCall(streamrecorder_h g_hCallRecorder);
int CreatePacketAndFormatDataCall(streamrecorder_h g_hCallRecorder);
/** @} */
#endif  //_ITS_MEDIASTREAMRECORDER_COMMON_H_
