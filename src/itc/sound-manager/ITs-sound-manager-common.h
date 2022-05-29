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
#ifndef _ITS_SOUND_MANAGER_COMMON_H_
#define _ITS_SOUND_MANAGER_COMMON_H_

/************************** Headers **********************************************/
#include "tct_common.h"
#include <glib-2.0/glib.h>
#include <sound_manager.h>
#include <dlog.h>
#include <glib.h>
#include <glib-object.h>
#include <app.h>
#include <wav_player.h>

/** @addtogroup itc-sound-manager
*  @ingroup itc
*  @{
*/
/************************************************************************/

// Non-Functional Test Macros

#define FEATURE_MICROPHONE			"http://tizen.org/feature/microphone"
#define API_NAMESPACE				"SOUND_MANAGER_ITC"
#define CALLBACK_DELAY				40000
#define TIMEOUT_CB                  20000
#define TESTFILE					"WavPlayerTest.wav"
#define PATH_LEN					1024
#define SAMPLE_FORMAT_COUNT			4
#define SAMPLE_RATE_COUNT			8

int nTimeoutId;
GMainLoop *g_pSoundManagerMainLoop;

//helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define RUN_POLLING_LOOP {\
        g_pSoundManagerMainLoop = g_main_loop_new(NULL, false);\
        nTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_pSoundManagerMainLoop);\
        FPRINTF("[Line:%d][%s] Run mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pSoundManagerMainLoop);\
        dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Run mainloop [%p]", __LINE__, __FUNCTION__, g_pSoundManagerMainLoop);\
        g_main_loop_run(g_pSoundManagerMainLoop);\
        g_source_remove(nTimeoutId);\
        g_pSoundManagerMainLoop = NULL;\
}

#define QUIT_GMAIN_LOOP {\
        if (g_pSoundManagerMainLoop)\
{\
        FPRINTF("[Line:%d][%s] Quit mainloop [%p]\\n", __LINE__, __FUNCTION__, g_pSoundManagerMainLoop);\
        dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Quit mainloop [%p]", __LINE__, __FUNCTION__, g_pSoundManagerMainLoop);\
        g_main_loop_quit(g_pSoundManagerMainLoop);\
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



#define CHECK_CALLBACK_STATUS(szApiName) {\
	nTimeoutId = g_timeout_add(CALLBACK_DELAY, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\
	if ( g_bCallbackResult == false )\
	{\
		FPRINTF("[Line : %d][%s] After %s, callback has not been invoked\\n", __LINE__, API_NAMESPACE, szApiName);\
		return 1;\
	}\
	else\
	{\
		g_bCallbackResult = false;\
	}\
}
char* SoundManagerGetError(int nRet);
char* SoundManagerGetSoundType(int nRet);
#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE)//Starts MOBILE or TIZENIOT and WEARABLE
char* SoundManagerGetSoundStreamType(int nRet);
char* SoundManagerGetSoundStreamFocusChanged(int nRet);
char* SoundManagerGetSoundStreamFocusFor(int nRet);
char* SoundManagerGetSoundStreamFocusState(int nRet);
#endif//MOBILE or TIZENIOT or WEARABLE
gboolean TimeoutFunction(gpointer data);
bool WavPlayerGetDataPath(char* pPath);
bool WavPlayerAppendToAppDataPath(char* pInputPath, char* pFinalPath);
char* WavPlayerGetError(int nRet);

/** @} */
#endif  //_ITS_SOUND_MANAGER_COMMON_H_
