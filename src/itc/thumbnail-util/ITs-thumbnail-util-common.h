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
#ifndef _ITS_THUMBNAIL_UTIL_COMMON_H_
#define _ITS_THUMBNAIL_UTIL_COMMON_H_

#include "tct_common.h"
#include <thumbnail_util.h>
#include <glib.h>
#include <app.h>

/** @addtogroup itc-thumbnail-util
* @ingroup		itc
* @{
*/

//Add helper function declarations here
GMainLoop *g_pThumbnailUtilMainLoop;

#define API_NAMESPACE			"THUMBNAIL_UTIL_ITC"
#define TIMEOUT_CB				10000
//#define SAMPLE_FILE_PATH_1		(ThumbnailGetDataPath("Sample_01.jpg"))
//#define SAMPLE_FILE_PATH_2		(ThumbnailGetDataPath("Sample_02.jpg"))
#define SAMPLE_FILE_1			"Sample_01.jpg"
#define SAMPLE_FILE_2			"Sample_02.jpg"
#define PATH_LEN				1024
#define MEDIA_IMAGE_WIDTH		512
#define MEDIA_IMAGE_HEIGHT		288

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test\\n", __LINE__, API_NAMESPACE);\
	if(!g_bThumbnailCreation) {\
		FPRINTF("[Line : %d][%s] Thumbnail handle creation failed in start up for n\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
	g_pThumbnailUtilMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pThumbnailUtilMainLoop);\
	g_main_loop_run(g_pThumbnailUtilMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pThumbnailUtilMainLoop = NULL;\
}

gboolean Timeout(gpointer data);
char* ThumbnailUtilGetError(int nRet);
char* ThumbnailGetDataPath(char *pszFileName);

/** @} */ //end of thumbnail-util

#endif  //_ITS_THUMBNAIL_UTIL_COMMON_H_