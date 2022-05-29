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
#ifndef _ITS_SOUND_POOL_COMMON_H_
#define _ITS_SOUND_POOL_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <media/sound_pool.h>
#include <glib.h>
#include <glib-object.h>
/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/
#define API_NAMESPACE				"SOUND_POOL_ITC"
#define MAX_PATH					1024
#define MAX_POOLS					8
#define DEFAULT_PRIORITY			255
#define DEFAULT_SAMPLE_TAG			"sound_pool_test_file"
#define GMAINTIMEOUT				20000

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bSoundPoolInit )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of Sound-Pool failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define RUN_GMAIN_LOOP {\
	g_pSoundPoolMainLoop = g_main_loop_new(NULL, false);\
	g_nTimeoutId = g_timeout_add(GMAINTIMEOUT, SoundPoolTimeout, g_pSoundPoolMainLoop);\
	g_main_loop_run(g_pSoundPoolMainLoop);\
	g_source_remove(g_nTimeoutId);\
	g_pSoundPoolMainLoop = NULL;\
}

#define QUIT_GMAIN_LOOP {\
	if (g_pSoundPoolMainLoop)\
		g_main_loop_quit(g_pSoundPoolMainLoop);\
}
//Add helper function declarations here
char* SoundPoolGetError(int nRet);
gboolean SoundPoolTimeout(gpointer data);
GMainLoop *g_pSoundPoolMainLoop;
guint g_nTimeoutId;
sound_pool_h g_hPool;
char *g_pFile_path;
static const char *test_file = "a.wav";
bool g_bSoundPoolInit;
bool g_bSoundPoolCreate;
bool g_bSoundPoolLoaded;
bool g_bSoundPoolActivated;
bool g_bCallbackCalled;
/** @} */
#endif  //_ITS_SOUND_POOL_COMMON_H_
