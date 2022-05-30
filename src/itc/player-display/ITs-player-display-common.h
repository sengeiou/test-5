//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#ifndef _ITS_PLAYER_DISPLAY_COMMON_H_
#define _ITS_PLAYER_DISPLAY_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include "player.h"
#include <glib.h>
#include <dlfcn.h>

#include <Elementary.h>
#include <app.h>

#define PACKAGE 					"player_display_test"
#define PATH_LEN					1024
#define WIDTH						16
#define HEIGHT						9
#define xVal						5
#define yVal						5
#define API_NAMESPACE				"PLAYER_DISPLAY_ITC"
#define MEDIA_360_PATH 				"test_360.mp4"
#define MEDIA_PATH_VIDEO			"file.mp4"
#define MEDIA_PATH_VIDEO2			"v.mp4"
#define MEDIA_PATH_AUDIO			"short.mp3"
#define MEDIA_PATH_DRC			    "test_drc.ts"
#define INTERNET_FEATURE			"http://tizen.org/feature/network.internet"
#define OPENGL_FEATURE "http://tizen.org/feature/opengles.version.2_0"
#define SPHERICAL_VIDEO_FEATURE "http://tizen.org/feature/multimedia.player.spherical_video"
#define WIFI_FEATURE				"http://tizen.org/feature/network.wifi"
#define TELEPHONY_FEATURE			"http://tizen.org/feature/network.telephony"
#define TIMEOUT						20000

bool g_bIsSupported;
Evas_Object *g_pEvasWindow;
Evas_Object *g_pElmWindow;
Evas_Object *g_pEvasObject;
Evas *g_pEvasCore;

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bPlayerCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of player create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define PRINT_API_ERROR_IN_LOOP_MSG_SINGLE(api) \
	FPRINTF("[Line : %d][%s] %s failed\\n",__LINE__, API_NAMESPACE, #api);

#define PRINT_API_ERROR_IN_LOOP_MSG(api, nRet) \
	FPRINTF("[Line : %d][%s] %s failed with return value: %d\\n",__LINE__, API_NAMESPACE, #api, nRet);

player_h g_player;
char* PlayerGetError(int nRet);
bool PlayerGetDataPath(char* pPath);
bool PlayerAppendToAppDataPath(char* pInputPath, char* pFinalPath);

// Initialization for player handler
bool InitializePlayerHandler(bool bPrepare, int nMediaType);
//Print Player State
void PlayerGetState(player_state_e e);

void CreateEvasWindow();
void createWindow();
void WinDel(void *data, Evas_Object *obj, void *event);

/** @} */
#endif  //_ITS_PLAYER_DISPLAY_COMMON_H_
