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
#ifndef _ITS_WAV_PLAYER_COMMON_H_
#define _ITS_WAV_PLAYER_COMMON_H_

#include "tct_common.h"
#include <glib.h>
#include <glib-object.h>
#include <app.h>
#include <wav_player.h>
#include <sound_manager.h>

/** @addtogroup itc-wav-player
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"WAV_PLAYER_ITC"
#define PATH_LEN					1024
#define MICROSECONDS_PER_SECOND		1000000
#define TESTFILE					"WavPlayerTest.wav"
#define SLEEP						5000000
#define TIMEOUT_CB					15000

#define START_TEST {\
	FPRINTF("\\n[Line : %d][%s] Starting test : %s\\n", __LINE__,API_NAMESPACE,__FUNCTION__);\
}

#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, WavPlayerCallbackTimeout, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pMainLoop = NULL;\
}

char* SoundType(sound_type_e nRet);
char* WavPlayerGetError(int nRet);
char* SoundManagerGetError(int nRet);
bool WavPlayerGetDataPath(char* pPath);
bool WavPlayerAppendToAppDataPath(char* pInputPath, char* pFinalPath);

/** @} */
#endif  //_ITS_WAV_PLAYER_COMMON_H_
