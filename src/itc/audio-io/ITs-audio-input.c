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

/** @addtogroup itc-audio-input
*  @ingroup itc
*  @{
*/

audio_in_h g_pstAudioInputHandle;
bool g_bAudioCreation;
static bool g_bAudioIoStreamCallback = false;
int g_nPeekFailCount = 0;
int g_nDropFailCount = 0;
static GMainLoop *g_pMainLoop;

gboolean Timeout_Function(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

/**
* @function 		ITs_audio_input_startup
* @description	 	Called before each test, creates Audio handle
* @parameter		NA
* @return 			NA
*/
void ITs_audio_input_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Audio_IO_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bFeatureSupported = false;
	g_bAudioCreation = false;
	audio_channel_e eAudioChannel = AUDIO_CHANNEL_STEREO;
	audio_sample_type_e eAudioSampleRate = AUDIO_SAMPLE_TYPE_S24_LE;

	IS_FEATURE_SUPPORTED(MICROPHONE_FEATURE, g_bFeatureSupported, API_NAMESPACE);

	g_AudioInputRet = audio_in_create(SAMPLE_RATE, eAudioChannel,eAudioSampleRate, &g_pstAudioInputHandle);
	if ( g_AudioInputRet == AUDIO_IO_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] audio_in_create created successfully\\n", __LINE__, API_NAMESPACE);
		g_bAudioCreation = true;
	}
	else
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] audio_in_create creation failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AudioInputGetError(g_AudioInputRet));
#endif
	}
	return;
}

/**
* @function 		ITs_audio_input_cleanup
* @description	 	Called after each test, destroys Audio handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_audio_input_cleanup(void)
{
	if ( g_bAudioCreation )
	{
		int nRet = audio_in_destroy (g_pstAudioInputHandle);
		if ( nRet != AUDIO_IO_ERROR_NONE )
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] audio_in_destroy failed, error returned = %s \\n", __LINE__, API_NAMESPACE, AudioInputGetError(nRet));
#endif
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Audio_IO_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function			AudioIoStreamCallback
* @description		Called when audio handle stream is created.
* @parameter[IN]	The audio handle
* @parameter[IN]	Size in bytes
* @parameter[IN]	The user data passed from the callback registration function			
* @return			NA
*/
void AudioIoStreamCallback(audio_in_h g_pstAudioInputHandle, size_t nBytes, void *userdata)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] AudioIoStreamCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bAudioIoStreamCallback = true;
}

/**
* @function			AudioIoStreamCallbackPeekDrop
* @description		Called when audio handle stream is registered and audio is prepared.
* @parameter[IN]	The audio handle
* @parameter[IN]	Size in bytes
* @parameter[IN]	The user data passed from the callback registration function			
* @return			NA
*/
void AudioIoStreamCallbackPeekDrop(audio_in_h g_pstAudioInputHandle, size_t nBytes, void *userdata)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] AudioIoStreamCallback is called\\n", __LINE__, API_NAMESPACE);
#endif

	g_bAudioIoStreamCallback = true;
	const void *pszBuffer = NULL;
	unsigned int punLength = 0;

	int nRet = audio_in_peek(g_pstAudioInputHandle, &pszBuffer, &punLength);
	if ( nRet != AUDIO_IO_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] audio_in_peek failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AudioInputGetError(nRet));
		return;
	}
	if ( pszBuffer == NULL )
	{
		FPRINTF("[Line : %d][%s] audio_in_peek failed,as pszBuffer is NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRet = audio_in_drop(g_pstAudioInputHandle);
	if ( nRet != AUDIO_IO_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] audio_in_drop failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AudioInputGetError(nRet));
		return;
	}

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @function			AudioIoStateChangedCallback
* @description		Called when audio handle stream is created.
* @parameter[IN]	The audio handle
* @parameter[IN]	Size in bytes
* @parameter[IN]	The user data passed from the callback registration function
* @return			NA
*/
void AudioIoStateChangedCallback(audio_in_h g_pstAudioInputHandle, audio_io_state_e eCurrent,audio_io_state_e ePrevious, bool BPolicy, void *userdata)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] AudioIoStateChangedCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
}
/**
* @function 		test_sound_manager_stream_focus_state_changed_cb
* @description	 	callback function
* @parameter		sound_stream_info_h stream_info, sound_stream_focus_mask_e focus_mask, sound_stream_focus_state_e focus_state, sound_stream_focus_change_reason_e reason, int sound_behavior, const char *extra_info, void *user_data
* @return 			NA
*/
static void test_sound_manager_stream_focus_state_changed_cb(sound_stream_info_h stream_info,
															sound_stream_focus_mask_e focus_mask,
															sound_stream_focus_state_e focus_state,
															sound_stream_focus_change_reason_e reason,
															int sound_behavior,
															const char *extra_info,
															void *user_data)
{
	FPRINTF("[Line : %d][%s]Inside callback \"test_sound_manager_stream_focus_state_changed_cb\"\\n", __LINE__, API_NAMESPACE);
}

/** @addtogroup itc-audio-input-testcases
*  @brief 		Integration testcases for module audio-input
*  @ingroup 	itc-audio-input
*  @{
*/

//& purpose: Prepare reading audio input by starting buffering the audio data and Unprepare by stopping that . 
//& type: auto
/**
* @testcase 				ITc_audio_in_prepare_unprepare_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Prepare reading audio input by starting buffering the audio data and unprepare by stopping that . 
* @scenario					Start buffering of audio data\n
*							Read audio input\n
*							Stop buffering of audio data
* @apicovered				audio_in_prepare, audio_in_unprepare
* @passcase					When audio_in_prepare and audio_in_unprepare are successful
* @failcase					If target API audio_in_create fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_in_prepare_unprepare_p(void)
{
	START_TEST;

	//Target API
	int nRet = audio_in_prepare(g_pstAudioInputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_prepare", AudioInputGetError(nRet));

	nRet = audio_in_unprepare(g_pstAudioInputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_unprepare", AudioInputGetError(nRet));

	return 0;
}

//& purpose: To get the size to be allocated for audio input buffer 
//& type: auto
/**
* @testcase 				ITc_audio_in_get_buffer_size_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To get the size to be allocated for audio input buffer
* @scenario					Get the size of buffer\n
*							Allocate it to audio input buffer
* @apicovered				audio_in_get_buffer_size
* @passcase					When audio_in_get_buffer_size is successful
* @failcase					If target API audio_in_get_buffer_size fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_in_get_buffer_size_p(void)
{
	START_TEST;

	int nSize;

	// Target API
	int nRet = audio_in_get_buffer_size( g_pstAudioInputHandle, &nSize);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_get_buffer_size", AudioInputGetError(nRet));
	if ( nSize == -1 )
	{
		FPRINTF("[Line : %d][%s] audio_in_get_buffer_size is unsuccessful, error returned = buffer size is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] audio_in_get_buffer_size is successful\\n", __LINE__, API_NAMESPACE);
#endif	
	}
	return 0;
}

//& purpose: To read audio data from the audio input buffer 
//& type: auto
/**
* @testcase 				ITc_audio_in_read_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To read audio data from the audio input buffer
* @scenario					Prepare reading input audio\n
*							Read audio data from buffer\n
*							Unprepare reading of input audio 
* @apicovered				audio_in_read, audio_in_prepare, audio_in_get_buffer_size, audio_in_unprepare
* @passcase					When audio_in_read is successful
* @failcase					If target API audio_in_read fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_in_read_p(void)
{
	START_TEST;

	int unSize = 0;
	char *pszbuffer = NULL;

	int nRet = audio_in_prepare(g_pstAudioInputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_prepare", AudioInputGetError(nRet));

	nRet = audio_in_get_buffer_size(g_pstAudioInputHandle, &unSize);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_in_get_buffer_size", AudioInputGetError(nRet), audio_in_unprepare(g_pstAudioInputHandle););
	
	if(unSize == 0)
	{
		FPRINTF("[Line : %d][%s]audio_in_get_buffer_size failed. unSize = 0\\n", __LINE__, API_NAMESPACE);
		audio_in_unprepare(g_pstAudioInputHandle);
		return 1;
	}
	pszbuffer = (char *) calloc (unSize, sizeof(char));
	if(pszbuffer == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to allocate memory\\n", __LINE__, API_NAMESPACE);
		audio_in_unprepare(g_pstAudioInputHandle);
		return 1;
	}
	// Target API
	nRet = audio_in_read(g_pstAudioInputHandle, (void*) pszbuffer, unSize);
	if ( nRet < 0 )
	{ 
		FILE* fp = fopen("/root/test.raw", "wb+");
		if(NULL == fp)
		{
			FREE_MEMORY(pszbuffer);
			return 1;
		}
		fwrite(pszbuffer, unSize, sizeof(char), fp);
		fclose(fp);

		FPRINTF("[Line : %d][%s]FAIL, size=%d, nRet=%d\\n", __LINE__, API_NAMESPACE, unSize, nRet);
		FREE_MEMORY(pszbuffer);
		audio_in_unprepare(g_pstAudioInputHandle);
		return 1;
	}
	else 
	{
		FPRINTF("[Line : %d][%s]PASS, size=%d, nRet=%d\\n", __LINE__, API_NAMESPACE, unSize, nRet);
	}

	FREE_MEMORY(pszbuffer);
	audio_in_unprepare(g_pstAudioInputHandle);
	return 0;
}

//& purpose: To get the channel type of audio input data stream
//& type: auto
/**
* @testcase 				ITc_audio_in_get_channel_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To get the channel type of audio input data stream. 
* @scenario					Get channel type\n
*							Check whether its mono or stereo 
* @apicovered				audio_in_get_channel
* @passcase					When audio_in_get_channel is successful
* @failcase					If target API audio_in_get_channel, fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_in_get_channel_p(void)
{
	START_TEST;
	
	audio_channel_e eAudioChannel;
	
	// Target API
	int nRet = audio_in_get_channel(g_pstAudioInputHandle,&eAudioChannel);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_get_channel", AudioInputGetError(nRet));
	
	if(eAudioChannel != AUDIO_CHANNEL_MONO && eAudioChannel != AUDIO_CHANNEL_STEREO)
	{
		FPRINTF("[Line : %d][%s] audio_in_get_channel failed. Invalid audio channel returned\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& purpose: To get the sample audio format of audio input data stream.
//& type: auto
/**
* @testcase 				ITc_audio_in_get_sample_type_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To get the channel type of audio input data stream. 
* @scenario					Get input data stream\n
*							Get the sample audio format 
* @apicovered				audio_in_get_sample_type
* @passcase					When audio_in_get_sample_type is successful
* @failcase					If target API audio_in_get_sample_type fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_in_get_sample_type_p(void)
{
	START_TEST;
	audio_sample_type_e eAudioSampleRate;

	// Target API
	int nRet = audio_in_get_sample_type(g_pstAudioInputHandle,&eAudioSampleRate);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_get_sample_type", AudioInputGetError(nRet));
	
	if(eAudioSampleRate != AUDIO_SAMPLE_TYPE_U8 && eAudioSampleRate != AUDIO_SAMPLE_TYPE_S16_LE && eAudioSampleRate != AUDIO_SAMPLE_TYPE_S24_LE   && eAudioSampleRate != AUDIO_SAMPLE_TYPE_S24_32_LE)
	{
		FPRINTF("[Line : %d][%s] audio_in_get_sample_type failed. Invalid sample type returned\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& purpose: To get the sample rate of audio input data stream.
//& type: auto
/**
* @testcase 				ITc_audio_in_get_sample_rate_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To get the channel type of audio input data stream. 
* @scenario					gets input data stream \n
*							gets the sample rate
* @apicovered				audio_in_get_sample_rate
* @passcase					When audio_in_get_sample_rate is successful
* @failcase					If target API audio_in_get_sample_rate fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_in_get_sample_rate_p(void)
{
	START_TEST;

	int nSample_rate;
	
	// Target API
	int nRet = audio_in_get_sample_rate(g_pstAudioInputHandle,&nSample_rate);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_get_sample_rate", AudioInputGetError(nRet));
	
	if(nSample_rate < MIN_SAMPLE_RATE  || nSample_rate > MAX_SAMPLE_RATE)
	{
		FPRINTF("[Line : %d][%s] audio_in_get_sample_rate failed. Invalid sample rate returned\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& purpose: Peek from audio in buffer and then drop it.
//& type: auto
/**
* @testcase 				ITc_audio_in_peek_drop_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Peek from audio in buffer and then drop it.
* @scenario					The input handle to the audio input\n
*							Buffer length to be given
* @apicovered				audio_in_peek, audio_in_set_stream_cb, audio_in_prepare, audio_in_unset_stream_cb
* @passcase					When audio_in_peek are successful
* @failcase					If target API audio_in_peek fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_in_peek_drop_p(void)
{
	START_TEST;

	int nTtimeoutId = 0;
	g_pMainLoop = g_main_loop_new(NULL, false);

	int nRet = audio_in_set_stream_cb(g_pstAudioInputHandle, AudioIoStreamCallbackPeekDrop, NULL);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_set_stream_cb", AudioInputGetError(nRet));

	g_bAudioIoStreamCallback = false;
	nRet = audio_in_prepare(g_pstAudioInputHandle);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_in_prepare", AudioInputGetError(nRet), audio_in_unset_stream_cb(g_pstAudioInputHandle));

	nTtimeoutId = g_timeout_add(5000, Timeout_Function, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);

	if ( g_bAudioIoStreamCallback == false )
	{
		FPRINTF("[Line : %d][%s] audio_in_peek failed, unable to invoke callback\\n", __LINE__, API_NAMESPACE);
		audio_in_unset_stream_cb(g_pstAudioInputHandle);
		audio_in_unprepare(g_pstAudioInputHandle);
		return 1;
	}

	nRet = audio_in_unset_stream_cb (g_pstAudioInputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_unset_stream_cb", AudioInputGetError(nRet));
	
	audio_in_unprepare(g_pstAudioInputHandle);
	return 0;
}

//& purpose: Sets and Un-sets an asynchronous callback function to handle recording PCM data.
//& type: auto
/**
* @testcase 				ITc_audio_in_set_unset_stream_cb_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets and Un-sets an asynchronous callback function to handle recording PCM data.
* @scenario					Get the handle to the audio input\n
*							The callback function to register\n
*							The user data is passed to callback function
* @apicovered				audio_in_set_stream_cb, audio_in_unset_stream_cb
* @passcase					When audio_in_set_stream_cb is successful
* @failcase					If target API audio_in_set_stream_cb or audio_in_unset_stream_cb fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_in_set_unset_stream_cb_p(void)
{
	START_TEST;

	g_bAudioIoStreamCallback = false;

	// Target API
	int nRet = audio_in_set_stream_cb(g_pstAudioInputHandle, AudioIoStreamCallback, NULL);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_set_stream_cb", AudioInputGetError(nRet));

	usleep(5000);
	nRet = audio_in_unset_stream_cb (g_pstAudioInputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_unset_stream_cb", AudioInputGetError(nRet));
	
	return 0;
}

//& purpose: Pauses buffering of audio data from the device..
//& type: auto
/**
* @testcase 				ITc_audio_in_resume_pause_p
* @since_tizen				3.0
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Pauses buffering of audio data from the device.
* @scenario					Get the handle to the audio input\n
* @apicovered				audio_in_resume, audio_in_pause
* @passcase					When audio_in_resume and audio_in_pause are successful
* @failcase					If audio_in_resume, audio_in_pause or any supporting API fails
* @precondition				Audio handle must be created and the state should be #AUDIO_IO_STATE_RUNNING.
* @postcondition			Audio handle must be released and the state will be #AUDIO_IO_STATE_PAUSED.
*/
int ITc_audio_in_resume_pause_p(void)
{
	START_TEST;

	int nRet = audio_in_prepare(g_pstAudioInputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_prepare", AudioInputGetError(nRet));

	sleep(2);

	// Target API
	nRet = audio_in_pause(g_pstAudioInputHandle);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_in_pause", AudioInputGetError(nRet), audio_in_unprepare(g_pstAudioInputHandle));

	sleep(2);

	// Target API
	nRet = audio_in_resume(g_pstAudioInputHandle);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_in_resume", AudioInputGetError(nRet), audio_in_unprepare(g_pstAudioInputHandle));

	nRet = audio_in_unprepare(g_pstAudioInputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_unprepare", AudioInputGetError(nRet));

	return 0;
}

//& purpose: Flushes and discards buffered audio data from the input stream.
//& type: auto
/**
* @testcase 				ITc_audio_in_flush_p
* @since_tizen				2.4
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Flushes and discards buffered audio data from the input stream.
* @scenario					Get the handle to the audio input\n
* @apicovered				audio_in_flush, audio_in_prepare, audio_in_get_buffer_size, audio_in_unprepare
* @passcase					When audio_in_flush is successful
* @failcase					If target API audio_in_flush fails or any precondition API fails
* @precondition				Audio handle must be created and the state should be #AUDIO_IO_STATE_RUNNING or #AUDIO_IO_STATE_PAUSED.
* @postcondition			Audio handle must be released
*/
int ITc_audio_in_flush_p(void)
{
	START_TEST;
	int unSize = 0;
	char *pszbuffer = NULL;

	int nRet = audio_in_prepare(g_pstAudioInputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_prepare", AudioInputGetError(nRet));

	nRet = audio_in_get_buffer_size(g_pstAudioInputHandle, &unSize);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_get_buffer_size", AudioInputGetError(nRet));
	
	if(unSize == 0)
	{
		FPRINTF("[Line : %d][%s] audio_in_get_buffer_size failed, unSize = 0\\n", __LINE__, API_NAMESPACE);
		audio_in_unprepare(g_pstAudioInputHandle);
		return 1;
	}
	pszbuffer = (char *) calloc (unSize, sizeof(char));
	if(pszbuffer == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to allocate memory\\n", __LINE__, API_NAMESPACE);
		audio_in_unprepare(g_pstAudioInputHandle);
		return 1;
	}
	nRet = audio_in_read(g_pstAudioInputHandle, (void*) pszbuffer, unSize);
	if ( nRet < 0 )
	{
		FILE* fp = fopen("/root/test.raw", "wb+");
		if(fp)
		{
			fwrite(pszbuffer, unSize, sizeof(char), fp);
			fclose(fp);
		}

		FPRINTF("[Line : %d][%s]FAIL, size=%d, nRet=%d\\n", __LINE__, API_NAMESPACE, unSize, nRet);
		FREE_MEMORY(pszbuffer);
		audio_in_unprepare(g_pstAudioInputHandle);
		return 1;
	}
	else
	{
		FPRINTF("[Line : %d][%s]PASS, size=%d, nRet=%d\\n", __LINE__, API_NAMESPACE, unSize, nRet);
	}

	// Target API
	nRet = audio_in_flush(g_pstAudioInputHandle);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_in_flush", AudioInputGetError(nRet), FREE_MEMORY(pszbuffer); audio_in_unprepare(g_pstAudioInputHandle););

	FREE_MEMORY(pszbuffer);

	nRet = audio_in_unprepare(g_pstAudioInputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_unprepare", AudioInputGetError(nRet));

	return 0;
}

//& purpose: Sets the state changed callback function to the audio input handle.
//& type: auto
/**
* @testcase 				ITc_audio_in_set_unset_state_changed_cb_p
* @since_tizen				3.0
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets the state changed callback function to the audio input handle.
* @scenario					Get the handle to the audio input\n
*							The callback function to register\n
*							The user data is passed to callback function
* @apicovered				audio_in_set_state_changed_cb, audio_in_unset_state_changed_cb
* @passcase					When audio_in_set_state_changed_cb is successful
* @failcase					If target API audio_in_set_state_changed_cb or audio_in_unset_state_changed_cb fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_in_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	// Target API
	int nRet = audio_in_set_state_changed_cb(g_pstAudioInputHandle, AudioIoStateChangedCallback, NULL);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_set_state_changed_cb", AudioInputGetError(nRet));

	usleep(5000);
	nRet = audio_in_unset_state_changed_cb (g_pstAudioInputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_unset_state_changed_cb", AudioInputGetError(nRet));

	return 0;
}

//& purpose: Sets the sound stream information to the audio input.
//& type: auto
/**
* @testcase 				ITc_audio_in_set_sound_stream_info_p
* @since_tizen				3.0
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets the sound stream information to the audio input.
* @scenario					Get the handle to the audio input\n
*							call manager for sound stream is called
*							The callback function to register\n
*							The user data is passed to callback function
* @apicovered				audio_in_set_sound_stream_info
* @passcase					When audio_in_set_sound_stream_info is successful
* @failcase					If target API audio_in_set_sound_stream_info fails or any precondition API fails
* @precondition				Audio handle must be created and sound_manager_create_stream_information must b called and state should be in IDLE atate.
* @postcondition			Audio handle must be released and sound_manager_destroy_stream_information must be called.
*/
int ITc_audio_in_set_sound_stream_info_p(void)
{
	START_TEST;

	sound_stream_info_h hStreamInfo = NULL;
	int nRet = -1, nEnumCount = 0, nIterator = 0;

	sound_stream_type_e arrStreamType[] = {
		SOUND_STREAM_TYPE_MEDIA,				/**< Sound stream type for media */
		//SOUND_STREAM_TYPE_SYSTEM,				/**< Sound stream type for system */
		//SOUND_STREAM_TYPE_ALARM,				/**< Sound stream type for alarm */
		//SOUND_STREAM_TYPE_NOTIFICATION,			/**< Sound stream type for notification */
		//SOUND_STREAM_TYPE_EMERGENCY,			/**< Sound stream type for emergency */
		//SOUND_STREAM_TYPE_VOICE_INFORMATION,	/**< Sound stream type for voice information */
		SOUND_STREAM_TYPE_VOICE_RECOGNITION,	/**< Sound stream type for voice recognition */
		//SOUND_STREAM_TYPE_RINGTONE_VOIP,		/**< Sound stream type for ring-tone for VoIP */
		SOUND_STREAM_TYPE_VOIP					/**< Sound stream type for VoIP */
	};
	nEnumCount = sizeof(arrStreamType) / sizeof(arrStreamType[0]);

	for ( nIterator = 0; nIterator < nEnumCount; nIterator++ )
	{
		nRet = sound_manager_create_stream_information(arrStreamType[nIterator], test_sound_manager_stream_focus_state_changed_cb, NULL, &hStreamInfo);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

		nRet = audio_in_set_sound_stream_info(g_pstAudioInputHandle, hStreamInfo);
		PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_in_set_sound_stream_info", AudioInputGetError(nRet), sound_manager_destroy_stream_information(hStreamInfo));

		nRet = sound_manager_destroy_stream_information(hStreamInfo);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information\\n", SoundManagerGetError(nRet));
	}

	return 0;
}

//& purpose: Sets and gets the volume of audio input.
//& type: auto
/**
* @testcase                             ITc_audio_in_set_get_volume_p
* @since_tizen                          6.0
* @author                                       SRID(raghu.mendu)
* @reviewer                                     SRID(shobhit.v)
* @type                                         auto
* @description                          Sets/Gets the volume to/from the audio input.
* @scenario                                     Get the handle to the audio input\n
* @apicovered                           audio_in_set_volume
*						audio_in_get_volume
* @passcase                                     When audio_in_set_volume and audio_in_get_volume are successful and
*						the value returned from audio_in_get_volume is equal to the value set in audio_in_set_volume
* @failcase                                     When target APIs audio_in_set_volume and audio_in_get_volume or preconditions fail and
*                                               the value returned from audio_in_get_volume is not equal to the value set in audio_in_set_volume
* @precondition                         Audio handle must be created.
* @postcondition                        Audio handle must be destroyed.
*/
int ITc_audio_in_set_get_volume_p(void)
{
    START_TEST;

    int nRet;
    double nGetVolume;
    double nSetVolume[] = { 0.0, 2.0, 0.7, 1.5 };
    int nCount = 4;
    int i = 0;
    audio_in_h hInputHandle = NULL;

    nRet = audio_in_create(SAMPLE_RATE, AUDIO_CHANNEL_MONO, AUDIO_SAMPLE_TYPE_S16_LE, &hInputHandle);
    PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_in_create", AudioInputGetError(nRet));
    CHECK_HANDLE(hInputHandle, "audio_in_create");

    for(i = 0; i < nCount; i++)
    {
        //Target API
        nRet = audio_in_set_volume(hInputHandle, nSetVolume[i]);
        PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_in_set_volume", AudioInputGetError(nRet), audio_in_destroy(hInputHandle));

        //Target API
        nRet = audio_in_get_volume(hInputHandle, &nGetVolume);
        PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_in_get_volume", AudioInputGetError(nRet), audio_in_destroy(hInputHandle));
        PRINT_RESULT_CLEANUP(nSetVolume[i], nGetVolume, "audio_in_get_volume", "input and output volume are different", audio_in_destroy(hInputHandle));
    }

    audio_in_destroy(hInputHandle);

    return 0;
}
/** @} */
/** @} */
