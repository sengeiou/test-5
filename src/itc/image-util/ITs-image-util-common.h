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
#ifndef _ITS_IMAGE_UTIL_COMMON_H_
#define _ITS_IMAGE_UTIL_COMMON_H_

#include "tct_common.h"

#include <glib-object.h>
#include <glib-2.0/glib.h>

#include <image_util.h>
#include <media_packet.h>
#include <media_format.h>
#include <app.h>
#include <stdio.h>

/** @addtogroup itc-image-util
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"IMAGE_UTIL_ITC"
#define PATH_LEN                    1024
#define TIMEOUT_CB					5000
#define MICROSECONDS_PER_SECOND		1000000

#define SAMPLE_FILE_PATH            "Image_01.jpg"
#define OUTPUT_FILE_PATH            "output.jpg"
#define SAMPLE_PNG_FILE_PATH		"sample.png"
#define SAMPLE_GIF_FILE_PATH		"sample.gif"
#define SAMPLE_BMP_FILE_PATH		"sample.bmp"
#define SAMPLE_HEIF_FILE_PATH		"sample.heic"

#define QUALITY                     100
#define X                           5
#define Y                           5                   

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE,__FUNCTION__);\
}

#define START_TEST_ANIM {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE,__FUNCTION__);\
	if( g_bStartUpSuccess == false )\
	{\
		FPRINTF("[Line : %d][%s] Startup failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
}

#define RUN_POLLING_LOOP {\
	g_pPushMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, timeout_func, g_pPushMainLoop);\
	g_main_loop_run(g_pPushMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pPushMainLoop = NULL;\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define CHECK_RETURN_CLEANUP(nVal, API, FreeResource) {\
	if(nVal < 0)\
	{\
		FPRINTF("\\n[Line : %d][%s] %s failed, return value is less than zero \n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

bool g_bStartUpSuccess;
GMainLoop *g_pPushMainLoop;
static GMainLoop *g_mainloop = NULL;
static int g_timeout_id = 0;
gboolean timeout_func(gpointer data);
void signal_for_async();
void wait_for_async();

char *ImageUtilRotaion(image_util_rotation_e nRet);
char *ImageUtilColorspace(image_util_colorspace_e nRet);
char* ImageUtilGetError(int nRet);
char* ImageUtilScale(image_util_scale_e nRet);
bool ImageUtilAppendToAppDataPath(char* pInputPath, char* pFinalPath);
bool ImageUtilGetDataPath(char* pPath);
char* MediaToolsGetError(int nRet);
char* MediaFormatGetError(int nRet);
int ImageUtilEncodeRunSetUp(image_util_image_h *stDecodedImage, image_util_encode_h *stHandle, char *pPath);
int ImageUtilAnimEncodeRunSetUp(image_util_image_h *stDecodedImage, char *pPath);
char *ImageUtilGetTestPath(const char *base_dir, const char *filename);
/** @} */
#endif  //_ITS_IMAGE_UTIL_COMMON_H_
