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
#ifndef _ITS__COMMON_H_
#define _ITS__COMMON_H_

#include "tct_common.h"

#include <media_packet.h>
#include <media_format.h>
#include <media_packet_pool.h>


#include <glib.h>
#include <app.h>

/** @addtogroup itc-capi-media-tool
*  @ingroup itc
*  @{
*/

#define PATH_LEN					1024
#define API_NAMESPACE	 "CAPI_MEDIA_TOOL_ITC"
#define MEDIA_FILE_PATH "RapGod.mp3"
#define GMAINTIMEOUT	30000 //30 seconds

//GMainLoop *g_loop;

#define START_TEST {\
	FPRINTF("Line : %d][%s] Starting test: %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bMediaTools )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of media tools create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
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
 
char* MediaPacketGetError(int nRet);
char* MediaFormatGetError(int nRet);
char* MediaBufferFlagsGetEnum(media_buffer_flags_e nEnumVal);
char* MediaFormatMimeTypeGetEnum(media_format_mimetype_e nEnumVal);
char* MediaFormatTextTypeGetEnum(media_format_text_type_e nEnumVal);
bool MediaToolGetDataPath(char* pAppDataPath);
bool MediaToolAppendToAppDataPath(char* pInputPath, char* pFinalPath);
int g_nCheckCb;
GMainLoop *g_pMainLoop;

#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	int nTtimeoutId = g_timeout_add(GMAINTIMEOUT, MediaToolCallbackTimeout, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTtimeoutId);\
	g_pMainLoop = NULL;\
}

gboolean MediaToolCallbackTimeout(gpointer data);
/** @} */ 
#endif  //_ITS__COMMON_H_
