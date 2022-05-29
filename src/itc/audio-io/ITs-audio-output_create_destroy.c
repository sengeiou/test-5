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
#include "ITs-audio-output-common.h"

#define SAMPLE_RATE_44100 44100
#define SAMPLE_RATE_48000 48000
#define SAMPLE_RATE_192000 192000


typedef struct audio_output_condition_s
{
    int sampleRate;
    audio_channel_e channelType;
    audio_sample_type_e sampleType;
} audioOutputCond;


/** @addtogroup itc-audio-output
*  @ingroup itc
*  @{
*/
//& set: Audiooutput1

/**
* @function 		ITs_audio_input1_startup
* @description	 	Called before each test, creates Audio handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_audio_output1_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Audio_IO_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_audio_input1_cleanup
* @description	 	Called after each test, destroys Audio handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_audio_output1_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Audio_IO_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-audio-output-testcases
*  @brief 		Integration testcases for module audio-output
*  @ingroup 	itc-audio-output
*  @{
*/
//& purpose:To create an audio device instance and to return an output handle to record PCM and to release it
//& type: auto
/**
* @testcase 			ITc_audio_out_create_new_destroy_p
* @since_tizen			3.0
* @author				SRID(sk.roy)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To create an audio device instance and to return an output handle to record PCM and to release it
* @scenario				Create an audio device\n
*						Create a local audio handle\n
*						Destroy the audio handle
* @apicovered			audio_out_create_new, audio_out_destroy
* @passcase				When audio_out_create_new and audio_out_destroy are successful.
* @failcase				If target API audio_out_create_new fails or any precondition API fails.
* @precondition			Audio handle must be created
* @postcondition		Audio handle must be released
*/
int ITc_audio_out_create_new_destroy_p(void)
{
	START_TEST_NO_CHECK;

	audio_out_h pstAudioOutputHandle;
	int enum_counter = 0;
	audioOutputCond audioCond[] = {
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE },
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_U8 },
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE },
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_U8 },
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE },
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_U8 },
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S16_LE },
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_U8 },
		{ SAMPLE_RATE_44100, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S24_LE },    /* since 5.0 */
		{ SAMPLE_RATE_48000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S24_32_LE }, /* since 5.0 */
		{ SAMPLE_RATE_192000, AUDIO_CHANNEL_STEREO, AUDIO_SAMPLE_TYPE_S32_LE },    /* since 5.5 */
	};
	int enum_size = sizeof(audioCond) / sizeof(audioCond[0]);

	for (enum_counter =0 ; enum_counter < enum_size; enum_counter++) {
		int nRet = audio_out_create_new(audioCond[enum_counter].sampleRate, audioCond[enum_counter].channelType, audioCond[enum_counter].sampleType, &pstAudioOutputHandle);
		if ( nRet != AUDIO_IO_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] audio_out_create_new failed for eAudioChannel = %u, eAudioSampleRate = %d, error returned = %s\\n", __LINE__, API_NAMESPACE, audioCond[enum_counter].channelType, audioCond[enum_counter].sampleRate, AudioOutputGetError(nRet));
			return 1;
		}
		if(pstAudioOutputHandle == NULL)
		{
			FPRINTF("[Line : %d][%s] audio_out_create_new failed for eAudioChannel = %u, eAudioSampleRate = %d, error returned = %s\\n", __LINE__, API_NAMESPACE, audioCond[enum_counter].channelType, audioCond[enum_counter].sampleRate, AudioOutputGetError(nRet));
			return 1;
		}

		nRet = audio_out_destroy(pstAudioOutputHandle);
		if ( nRet != AUDIO_IO_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] audio_out_destroy failed for eAudioChannel = %u, eAudioSampleRate = %d, error returned = %s\\n", __LINE__, API_NAMESPACE, audioCond[enum_counter].channelType, audioCond[enum_counter].sampleRate, AudioOutputGetError(nRet));
			return 1;
		}
	}

	return 0;
}
/** @} */
/** @} */
