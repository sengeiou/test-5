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
#ifndef _ITS_PLAYER_COMMON_H_
#define _ITS_PLAYER_COMMON_H_

#include "tct_common.h"

#include "player.h"
#include <glib.h>
#include <dlfcn.h>

#ifndef TIZENIOT // For Mobile or Wearable
	#include <Elementary.h>
#endif // For Mobile or Wearable

#include <app.h>

/** @addtogroup itc-player
*  @ingroup itc
*  @{
*/

#define PATH_LEN					1024
#define PACKAGE 					"player_test"
#define WIDTH						16
#define HEIGHT						9
#define x						5
#define y						5
#define TIMEOUT						20000
#define SLEEP_TIME					12
#define API_NAMESPACE				"PLAYER_ITC"
#define ES_NUMBER_OF_FEED 			100
#define ES_DEFAULT_VIDEO_PTS_OFFSET	20000000
#define MEDIA_PATH_CORRUPT_FILE		"AWB_header_change_AMR.amr"
#define MEDIA_PATH_VIDEO2			"v.mp4"
#define MEDIA_PATH_VIDEO			"file.mp4"
#define MEDIA_PATH_AUDIO			"short.mp3"
#define MEDIA_PATH_DRC			    "test_drc.ts"
#define MEDIA_PATH_H264				"test.h264"
#define MEDIA_PATH_SUBTITLE			"sub.srt"
#define ES_FEEDING_PATH 			"es_buff://pull_mode"
#define WIFI_FEATURE				"http://tizen.org/feature/network.wifi"
#define TELEPHONY_FEATURE			"http://tizen.org/feature/network.telephony"
#define ETHERNET_FEATURE			"http://tizen.org/feature/network.ethernet"
#define INTERNET_FEATURE			"http://tizen.org/feature/network.internet"
#define OPENGL_FEATURE "http://tizen.org/feature/opengles.version.2_0"
#define SPHERICAL_VIDEO_FEATURE "http://tizen.org/feature/multimedia.player.spherical_video"
#define AUDIO_OFFLOAD_FEATURE "http://tizen.org/feature/multimedia.player.audio_offload"
#define SOUND_STREAM_FEATURE "http://tizen.org/feature/multimedia.player.stream_info"

#define MEDIA_360_PATH 				"test_360.mp4"

#if (defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) || (defined(TV) && defined(_MEDIA_STREAM_API )) ) //Starts MOBILE or TIZENIOT or WEARABLE or TV
media_format_h g_hMediaFormat;
#endif

#ifndef TIZENIOT // For Mobile or Wearable
Evas_Object *g_pEvasWindow;
Evas_Object *g_pEvasObject;
Evas *g_pEvasCore;
#endif // For Mobile or Wearable

FILE *file_src;
int g_nRet;
bool g_bIsSupported;

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

#ifndef TIZENIOT // For Mobile or Wearable
void CreateEvasWindow();
void WinDel(void *data, Evas_Object *obj, void *event);
#endif // For Mobile or Wearable

char* MediaPacketGetError(int nRet);
char* MediaFormatGetError(int nRet);

/** @} */
#endif  //_ITS_PLAYER_COMMON_H_
