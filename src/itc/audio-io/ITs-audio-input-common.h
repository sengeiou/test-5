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
#ifndef _ITS_AUDIO_INPUT_COMMON_H_
#define _ITS_AUDIO_INPUT_COMMON_H_

#include "tct_common.h"
#include <media/audio_io.h>
#include <glib-object.h>
#include <glib-2.0/glib.h>
#include <sound_manager.h>

/** @addtogroup itc-audio-input
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE			"AUDIO_IO_ITC"
#define SAMPLE_RATE				44100
#define MAX_SAMPLE_RATE			192000
#define MIN_SAMPLE_RATE			8000
#define MICROPHONE_FEATURE		"http://tizen.org/feature/microphone"

bool g_bFeatureSupported;
int g_AudioInputRet;

#define START_TEST_NO_CHECK { \
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define START_TEST { \
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bAudioCreation ) { \
		FPRINTF("[Line : %d][%s] ret = %x, notsupported = %d", __LINE__, API_NAMESPACE, g_AudioInputRet, g_bFeatureSupported);\
		if ( g_AudioInputRet == TIZEN_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false) {\
			FPRINTF("[Line : %d][%s] Feature Not Supported!!!\\n", __LINE__, API_NAMESPACE);\
			return 0; \
		} \
		FPRINTF("[Line : %d][%s] Precondition of audio create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1; \
	} \
}

char *AudioChannel(audio_channel_e nRet);	
char *AudioSampleRate(audio_sample_type_e nRet);	
char *AudioInputGetError(int nRet);
char* SoundManagerGetError(int nRet);
/** @} */
#endif  //_ITS_AUDIO_INPUT_COMMON_H_


