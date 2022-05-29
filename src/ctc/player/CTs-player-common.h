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
#ifndef _CTS_PLAYER_COMMON_H_
#define _CTS_PLAYER_COMMON_H_

/* 
* Preconditions for these CTs-Test-cases
* 
* - when there is mentioned "earphone" in testcase, an earphone should be connected with the devie
* - when there is mentioned "speaker" in testcase, earphone should be removed from the device
*/

#include "tct_common.h"

#include <player.h>
#include <stdbool.h>
#include <math.h>
#include <glib.h>
#include <glib-object.h>
#include <stdint.h>
#include <runtime_info.h>
#include "app.h"

/** @addtogroup ctc-player
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE 						"PLAYER_CTC"
#define WAIT_TIME							5
#define MAX_SPEAKER_VOLUME_CONTROL			5
#define MAX_EARPHONE_VOLUME_CONTROL			5
#define MEDIA_AUDIO							"MediaPlayer.mp3"
#define INTERNET_FEATURE					"http://tizen.org/feature/network.internet"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define RUN_POLLING_LOOP {\
	g_MainLoopPlayer = g_main_loop_new (NULL, 0);\
	g_nPlayerWaitLoopCounter = 0;\
	g_timeout_add_seconds(1, (GSourceFunc)PlayerGmainLoopCallBack, "Player data");\
	g_main_loop_run(g_MainLoopPlayer);\
}

#define CLEAR_GLOOP {\
	g_main_loop_unref(g_MainLoopPlayer);\
	g_MainLoopPlayer = NULL;\
}

typedef enum MediaType
{
	MeidaType_Audio = 0,
	MediaType_Video
} MediaTypeEnumeration;

// Global variables
player_h g_PlayerHandler;
GMainLoop* g_MainLoopPlayer;
int g_nPlayerWaitLoopCounter;
bool g_bIsConnectedEarphone;

//Add helper function declarations here

char* PlayerGetError(int nResult);
char* PlayerGetState(player_state_e eState);
bool PlayerInitialization(bool bPrepare, MediaTypeEnumeration eMediaType);
bool PlayerDestroy(bool bIsUnprepare);
bool PlayerSetVolume(float *pfPreserveLeftVol, float *pfPreserveRightVol, float fSetLeftVol, float fSetRightVol);
gboolean PlayerGmainLoopCallBack(gpointer data);
void RuntimeErrorInfo(char *pszApiName, int nResult);
char* MediaPlayerGetDataPath(char *pszFileName);

/** @} */ //end of ctc-player

#endif  //_CTS_PLAYER_COMMON_H_
