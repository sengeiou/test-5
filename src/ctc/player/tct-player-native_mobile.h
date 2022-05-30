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
#ifndef __TCT_PLAYER-NATIVE_H__
#define __TCT_PLAYER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void CTs_capi_media_player_startup(void);
extern void CTs_capi_media_player_cleanup(void);

extern int CTc_Player_IsSupportedSpeaker_p(void);
extern int CTc_Player_SpeakerVolumeControlUp_p(void);
extern int CTc_Player_SpeakerVolumeControlDown_p(void);
extern int CTc_Player_SpeakerVolumeControlMute_p(void);

testcase tc_array[] = {
	{"CTc_Player_IsSupportedSpeaker_p",CTc_Player_IsSupportedSpeaker_p,CTs_capi_media_player_startup,CTs_capi_media_player_cleanup},
	{"CTc_Player_SpeakerVolumeControlUp_p",CTc_Player_SpeakerVolumeControlUp_p,CTs_capi_media_player_startup,CTs_capi_media_player_cleanup},
	{"CTc_Player_SpeakerVolumeControlDown_p",CTc_Player_SpeakerVolumeControlDown_p,CTs_capi_media_player_startup,CTs_capi_media_player_cleanup},
	{"CTc_Player_SpeakerVolumeControlMute_p",CTc_Player_SpeakerVolumeControlMute_p,CTs_capi_media_player_startup,CTs_capi_media_player_cleanup},
	{NULL, NULL}
};

#endif // __TCT_PLAYER-NATIVE_H__
