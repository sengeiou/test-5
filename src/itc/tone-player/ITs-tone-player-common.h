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
#ifndef _ITS_TONE_PLAYER_COMMON_H_
#define _ITS_TONE_PLAYER_COMMON_H_

#include "tct_common.h"
#include <tone_player.h>
#include <sound_manager.h>

/** @addtogroup itc-tone-player
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE		"TONE_PLAYER_ITC"
#define DURATION			1000

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n",__LINE__, API_NAMESPACE ,__FUNCTION__);\
}

char* SoundType(sound_type_e nRet);
char* TonePlayerGetType(tone_type_e nRet);
char* TonePlayerGetError(int nRet);
char* SoundManagerGetError(int nRet);
char* SoundManagerGetStreamType(int nRet);

/** @} */
#endif //_ITS_TONE_PLAYER_COMMON_H_
