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
#include "ITs-audio-input-common.h"
#define SAMPLE_RATE_44100 44100
#define SAMPLE_RATE_48000 48000
#define SAMPLE_RATE_192000 192000


typedef struct audio_input_condition_s
{
    int sampleRate;
    audio_channel_e channelType;
    audio_sample_type_e sampleType;
} audioInputCond;

/** @addtogroup itc-audio-input
*  @ingroup itc
*  @{
*/
//& set: AudioInput1

/**
* @function 		ITs_audio_input1_startup
* @description	 	Called before each test, creates Audio handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_audio_input1_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Audio_IO_p\\n", __LINE__, API_NAMESPACE);
#endif

	IS_FEATURE_SUPPORTED(MICROPHONE_FEATURE, g_bFeatureSupported, API_NAMESPACE);
	return;
}

/**
* @function 		ITs_audio_input1_cleanup
* @description	 	Called after each test, destroys Audio handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_audio_input1_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Audio_IO_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-audio-input-testcases
*  @brief 		Integration testcases for module audio-input
*  @ingroup 	itc-audio-input
*  @{
*/

//& purpose:To create an audio device instance and to return an input handle to record PCM and to release it
//& type: auto 
/**
* @testcase 			ITc_audio_in_create_destroy_p
* @since_tizen			2.3
* @author				SRID(sk.roy)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To create an audio device instance and to return an input handle to record PCM and to release it
* @scenario				Create an audio device\n
*						Create a local audio handle\n
*						Destroy the audio handle
* @apicovered			audio_in_create, audio_in_destroy
* @passcase				When audio_in_create and audio_in_destroy are successful.
* @failcase				If target API audio_in_create fails or any precondition API fails.
* @precondition			Audio handle must be created
* @postcondition		Audio handle must be released
*/
int ITc_audio_in_create_destroy_p(void)
{
	START_TEST_NO_CHECK;

	audio_in_h pstAudioInputHandle = NULL;
	int enum_counter = 0;
	int nRet = -1;
	audioInputCond audioCond[] = {
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE },
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_U8 },
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE },
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_U8 },
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE },
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_U8 },
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE },
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_U8 },
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S24_LE },      /* since 5.0 */
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S24_32_LE },   /* since 5.0 */
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_3, AUDIO_SAMPLE_TYPE_S16_LE },     /* since 5.5 */
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_4, AUDIO_SAMPLE_TYPE_S24_LE },     /* since 5.5 */
		{ SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_5, AUDIO_SAMPLE_TYPE_S24_32_LE }, /* since 5.5 */
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_6, AUDIO_SAMPLE_TYPE_S32_LE },     /* since 5.5 */
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_7, AUDIO_SAMPLE_TYPE_S24_LE },     /* since 5.5 */
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_8, AUDIO_SAMPLE_TYPE_S32_LE },     /* since 5.5 */
		{ SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_9, AUDIO_SAMPLE_TYPE_S16_LE },    /* since 6.5 */
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_10, AUDIO_SAMPLE_TYPE_S24_LE },    /* since 6.5 */
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_11, AUDIO_SAMPLE_TYPE_S24_32_LE }, /* since 6.5 */
		{ SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_12, AUDIO_SAMPLE_TYPE_S32_LE },   /* since 6.5 */
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_13, AUDIO_SAMPLE_TYPE_S16_LE },    /* since 6.5 */
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_MULTI_14, AUDIO_SAMPLE_TYPE_S24_LE },    /* since 6.5 */
		{ SAMPLE_RATE_192000, AUDIO_CHANNEL_MULTI_15, AUDIO_SAMPLE_TYPE_S24_32_LE },/* since 6.5 */
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_MULTI_16, AUDIO_SAMPLE_TYPE_S32_LE }     /* since 6.5 */
	};
	int enum_size = sizeof(audioCond) / sizeof(audioCond[0]);
	for (enum_counter =0 ; enum_counter < enum_size; enum_counter++) {
		nRet = audio_in_create(audioCond[enum_counter].sampleRate, audioCond[enum_counter].channelType, audioCond[enum_counter].sampleType, &pstAudioInputHandle);
		if ( nRet != AUDIO_IO_ERROR_NONE )
		{
			if ( nRet == TIZEN_ERROR_NOT_SUPPORTED && g_bFeatureSupported == false )
			{
				FPRINTF("[Line : %d][%s] audio_in_create returns NOT SUPPORTED correctly", __LINE__, API_NAMESPACE);
				continue;
			}
			FPRINTF("[Line : %d][%s] audio_in_create failed for eAudioChannel = %u and eAudioSampleRate = %d, error returned = %s\\n", __LINE__, API_NAMESPACE, audioCond[enum_counter].channelType, audioCond[enum_counter].sampleRate, AudioInputGetError(nRet));
			return 1;
		}
		if(pstAudioInputHandle == NULL)
		{
			FPRINTF("[Line : %d][%s] audio_in_create failed for eAudioChannel = %u and eAudioSampleRate = %d, pstAudioInputHandle is NULL\\n", __LINE__, API_NAMESPACE, audioCond[enum_counter].channelType, audioCond[enum_counter].sampleRate);
			return 1;
		}
		nRet = audio_in_destroy(pstAudioInputHandle);
		if ( nRet != AUDIO_IO_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] audio_in_destroy failed for eAudioChannel = %u and eAudioSampleRate = %d, error returned = %s\\n", __LINE__, API_NAMESPACE, audioCond[enum_counter].channelType, audioCond[enum_counter].sampleRate, AudioInputGetError(nRet));
			return 1;
}
	}

	return 0;
}

/** @} */
/** @} */
