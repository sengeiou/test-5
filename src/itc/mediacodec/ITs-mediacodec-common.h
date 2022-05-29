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
#ifndef _ITS__MEDIACODEC_COMMON_H_
#define _ITS__MEDIACODEC_COMMON_H_

//Add test package related includes here

#include "tct_common.h"

#include <media_codec.h>
#include <glib-2.0/glib.h>
#include <pthread.h>
#include <Ecore.h>
#include <app.h>

/** @addtogroup itc-mediacodec
* @ingroup		itc
* @{
*/

#define API_NAMESPACE 			"MEDIA_CODEC_ITC"
#define SLEEP_TIME				1
#define TIMEOUT					30000
#define FRAME_COUNT				15
#define MEDIACODEC_FEATURE		"http://tizen.org/feature/multimedia.media_codec"

bool g_bIsMediaCodecValidHandle;
media_packet_h hInputBuff;
media_packet_h hOutputBuff;
media_format_h hFormat;

static GMainLoop *g_pMainLoop;

#define RUN_POLLING_LOOP(szApiName) {\
	int nTimeoutId = 0;\
	g_pMainLoop = g_main_loop_new(NULL, false); \
	nTimeoutId = g_timeout_add(TIMEOUT, MediaCodecTimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pMainLoop = NULL; \
}

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bMediaCodecNotSupported)\
	{\
		FPRINTF("[Line : %d][%s] Required feature of mediacodec is not supported. So leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( g_bMismatch )\
	{\
		FPRINTF("[Line : %d][%s] MediaCodec_Check_System_Info_Feature_Supported and mediacodec_create returned different value. So leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	if ( !g_bIsMediaCodecValidHandle )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of mediacodec failed so leaving test\\n", __LINE__, API_NAMESPACE);\
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

char* MediaCodecGetError(int nRet);
unsigned int GetDataFromFile(unsigned char *DataPointer);
gboolean MediaCodecTimeoutFunction(gpointer data);

/** @} */ //end of itc-mediacodec

#endif  //_ITS__MEDIACODEC_COMMON_H_
