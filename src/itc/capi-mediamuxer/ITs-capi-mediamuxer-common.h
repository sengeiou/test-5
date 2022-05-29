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
#ifndef _ITS_MEDIAMUXER_COMMON_H_
#define _ITS_MEDIAMUXER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <fcntl.h>
#include <mediamuxer.h>
#include <storage.h>
#include <glib-2.0/glib.h>

/** @addtogroup itc-mediamuxer
*  @ingroup itc
*  @{
*/

bool g_bMediamuxerCreation;

#define API_NAMESPACE			"MEDIAMUXER_ITC"
#define MAXENUMSIZE			50
#define SETENUM				1
#define GETENUM				0
#define TRACK_INDEX 			1
#define POSITION 			2000
#define CODEC_DATA 			"video/x-h264, stream-format=(string)avc, alignment=(string)au, level=(string)5.1, profile=(string)high, codec_data=(buffer)01640033ffe1001b67640033ac5624161bf9b011000003000100000300328f1831898001000468eebcb0, width=(int)352, height=(int)198, framerate=(fraction)25/1, pixel-aspect-ratio=(fraction)1/1"
#define SIZE	 			300
#define TIMEOUT_CB			15000

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bMediamuxerCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of mediamuxer failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define RUN_POLLING_LOOP {\
        g_pMediaMuxerMainLoop = g_main_loop_new(NULL, false);\
        nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout_Function, g_pMediaMuxerMainLoop);\
        g_main_loop_run(g_pMediaMuxerMainLoop);\
        g_source_remove(nTimeoutId);\
        g_pMediaMuxerMainLoop = NULL;\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

char* MediamuxerGetState(mediamuxer_state_e state);
char* MediamuxerGetError(mediamuxer_error_e error);
char* MediamuxerGetFormat(mediamuxer_output_format_e format);
int MediamuxerExtractNal(FILE *fd, unsigned char* nal);

/** @} */
#endif  //_ITS_MEDIAMUXER_COMMON_H_
