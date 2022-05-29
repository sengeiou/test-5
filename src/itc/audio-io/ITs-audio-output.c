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

/** @addtogroup itc-audio-output
*  @ingroup itc
*  @{
*/

//& set: AudioOutput

audio_out_h g_pstAudioOutputHandle;
bool g_bAudioCreation;
bool g_bAudioIoInterruptedCallback;
bool g_bAudioOutputStreamCallback;
bool g_bAudioIoInterruptedCbCallback = false;

/**
* @function 		ITs_audio_output_startup
* @description	 	Called before each test, creates Audio handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_audio_output_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Audio_IO_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet;
	audio_channel_e eAudioChannel = AUDIO_CHANNEL_STEREO;
	audio_sample_type_e eAudioSampleRate = AUDIO_SAMPLE_TYPE_S24_LE;

	if ((nRet = audio_out_create_new(SAMPLE_RATE, eAudioChannel, eAudioSampleRate, &g_pstAudioOutputHandle)) == AUDIO_IO_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] audio_out_create_new handle created successfully\\n", __LINE__, API_NAMESPACE);
		g_bAudioCreation = true;
	}
	else
	{
		FPRINTF("[Line : %d][%s] audio_out_create_new creation failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AudioOutputGetError(nRet));
		g_bAudioCreation = false;
	}
	return;
}

/**
* @function 		ITs_audio_output_cleanup
* @description	 	Called after each test, destroys Audio handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_audio_output_cleanup(void)
{
	if ( g_bAudioCreation )
	{
		int nRet = audio_out_destroy (g_pstAudioOutputHandle);
		if ( nRet != AUDIO_IO_ERROR_NONE )
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] audio_out_destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, AudioOutputGetError(nRet));
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
void AudioOutputStreamCallback(audio_out_h g_pstAudioOutputStreamCallback, size_t nBytes, void *userdata)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] AudioOutStreamCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bAudioOutputStreamCallback = true;
}

/**
* @function			AudioOutputStateChangedCallback
* @description		Called when audio state changed.
* @parameter[IN]	The audio handle
* @parameter[IN]	Size in bytes
* @parameter[IN]	The user data passed from the callback registration function
* @return			NA
*/
void AudioOutputStateChangedCallback(audio_in_h g_pstAudioInputHandle, audio_io_state_e eCurrent,audio_io_state_e ePrevious, bool BPolicy, void *userdata)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] AudioOutputStateChangedCallback is called\\n", __LINE__, API_NAMESPACE);
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

/** @addtogroup itc-audio-output-testcases
*  @brief 		Integration testcases for module audio-output
*  @ingroup 	itc-audio-output
*  @{
*/
//& purpose:To prepare reading audio output by starting buffering the audio data and un Prepare by stopping that .
//& type: auto
/**
* @testcase 				ITc_audio_out_prepare_unprepare_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To prepare reading audio output by starting buffering the audio data and un-Prepare by stopping that . 
* @scenario					Start buffering of audio data\n
*							Read audio output\n
*							Stop buffering of audio data
* @apicovered				audio_out_prepare, audio_out_unprepare						
* @passcase					When audio_out_unprepare and audio_out_unprepare are successful
* @failcase					If target API audio_out_prepare fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_out_prepare_unprepare_p(void)
{
	START_TEST;
	int nRet = audio_out_prepare(g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_prepare", AudioOutputGetError(nRet));

	nRet = audio_out_unprepare(g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_unprepare", AudioOutputGetError(nRet));
	return 0;
}

//& purpose:To get the size to be allocated for audio output buffer 
//& type: auto
/**
* @testcase 				ITc_audio_out_get_buffer_size_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To get the size to be allocated for audio output buffer
* @scenario					Get the size of buffer\n
*							Allocate it to audio output buffer
* @apicovered				audio_out_get_buffer_size						
* @passcase					When audio_out_get_buffer_size is successful
* @failcase					If target API audio_out_get_buffer_size fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_out_get_buffer_size_p(void)
{
	START_TEST;
	int nSize = 0;
	int nRet = audio_out_get_buffer_size( g_pstAudioOutputHandle, &nSize);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_get_buffer_size", AudioOutputGetError(nRet));
	if ( nSize == -1 )
	{
		FPRINTF("[Line : %d][%s] audio_out_get_buffer_size is unsuccessful, error returned = buffer size is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] audio_out_get_buffer_size is successful\\n", __LINE__, API_NAMESPACE);
#endif
	}
	return 0;
}

//& purpose: To get the channel type of audio output data stream
//& type: auto
/**
* @testcase 				ITc_audio_out_get_channel_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To get the channel type of audio output data stream. 
* @scenario					Get channel type\n
*							Checks whether its mono or stereo
* @apicovered				audio_out_get_channel
* @passcase					When audio_out_get_channel is successful
* @failcase					If target API audio_out_get_channel fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_out_get_channel_p(void)
{
	START_TEST;
	audio_channel_e eAudioChannel;
	int nRet = audio_out_get_channel(g_pstAudioOutputHandle, &eAudioChannel);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_get_channel", AudioOutputGetError(nRet));
	
	if(eAudioChannel != AUDIO_CHANNEL_MONO && eAudioChannel != AUDIO_CHANNEL_STEREO)
	{
		FPRINTF("[Line : %d][%s] audio_out_get_channel failed. Invalid audio channel returned\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& purpose: To get the sample audio format of audio output data stream.
//& type: auto
/**
* @testcase 				ITc_audio_out_get_sample_type_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To get the channel type of audio output data stream. 
* @scenario					Get output data stream\n
*							Get the sample audio format
* @apicovered				audio_out_get_sample_type				
* @passcase					When audio_out_get_sample_type is successful
* @failcase					If target API audio_out_get_sample_type fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_out_get_sample_type_p(void)
{
	START_TEST;
	audio_sample_type_e eAudioSampleRate;
	int nRet = audio_out_get_sample_type(g_pstAudioOutputHandle, &eAudioSampleRate);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_get_sample_type", AudioOutputGetError(nRet));
	
	if(eAudioSampleRate != AUDIO_SAMPLE_TYPE_U8 && eAudioSampleRate != AUDIO_SAMPLE_TYPE_S16_LE && eAudioSampleRate != AUDIO_SAMPLE_TYPE_S24_LE &&  eAudioSampleRate != AUDIO_SAMPLE_TYPE_S24_32_LE)
	{
		FPRINTF("[Line : %d][%s] audio_out_get_sample_type failed. Invalid sample type returned\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& purpose: To get the sample rate of audio output data stream.
//& type: auto
/**
* @testcase 				ITc_audio_out_get_sample_rate_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To get the channel type of audio output data stream. 
* @scenario					Get output data stream\n
*							Get the sample rate
* @apicovered				audio_out_get_sample_rate				
* @passcase					When audio_out_get_sample_rate is successful
* @failcase					If target API audio_out_get_sample_rate fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_out_get_sample_rate_p(void)
{
	START_TEST;
	int nSample_rate;
	int nRet = audio_out_get_sample_rate(g_pstAudioOutputHandle,&nSample_rate);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_get_sample_rate", AudioOutputGetError(nRet));
	
	if(nSample_rate < MIN_SAMPLE_RATE  || nSample_rate > MAX_SAMPLE_RATE)
	{
		FPRINTF("[Line : %d][%s] audio_out_get_sample_rate failed. Invalid sample rate returned\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& purpose: To get the sound type supported by the audio output device. 
//& type: auto
/**
* @testcase 				ITc_audio_out_get_sound_type_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To get the channel type of audio output data stream. 
* @scenario					Get the type of sound
* @apicovered				audio_out_get_sound_type				
* @passcase					When audio_out_get_sound_type is successful
* @failcase					If target API audio_out_get_sound_type fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_out_get_sound_type_p(void)
{
	START_TEST;
	sound_type_e eSoundType = -1;
	int nRet = audio_out_get_sound_type(g_pstAudioOutputHandle,&eSoundType);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_get_sound_type", AudioOutputGetError(nRet));
	
	if(eSoundType < 0  || eSoundType > 7)
	{
		FPRINTF("[Line : %d][%s] audio_out_get_sound_type failed. Invalid sound type returned\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}


//& purpose:To start writing the audio data to the device
//& type: auto
/**
* @testcase 				ITc_audio_out_write_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				To start writing the audio data to the device
* @scenario					Prepares writing output audio\n
*							Write audio data from buffer\n
*							Return Written data size on success
* @apicovered				audio_out_prepare, audio_out_unprepare, audio_out_write, audio_out_get_buffer_size
* @passcase					When audio_out_write is successful
* @failcase					If target API audio_out_write fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_out_write_p(void)
{
	START_TEST;
	int unSize = 0;
	char *pszbuffer = NULL;

	int nRet = audio_out_prepare(g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_prepare", AudioOutputGetError(nRet));

	nRet = audio_out_get_buffer_size(g_pstAudioOutputHandle, &unSize);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_out_get_buffer_size", AudioOutputGetError(nRet), audio_out_unprepare(g_pstAudioOutputHandle););
	if(unSize == 0)
	{
		FPRINTF("[Line : %d][%s] audio_out_get_buffer_size failed, unSize = 0\\n", __LINE__, API_NAMESPACE);
		audio_out_unprepare(g_pstAudioOutputHandle);
		return 1;
	}
	pszbuffer = (char *) calloc (unSize, sizeof(char));
	if(pszbuffer == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to allocate memory\\n", __LINE__, API_NAMESPACE);
		audio_out_unprepare(g_pstAudioOutputHandle);
		return 1;
	}
	// Target API
	nRet = audio_out_write(g_pstAudioOutputHandle, (void*) pszbuffer, unSize);
	if ( nRet < 0 )
	{
		FPRINTF("[Line : %d][%s] FAIL, size=%d, nRet=%d\\n", __LINE__, API_NAMESPACE, unSize, nRet);
		FREE_MEMORY(pszbuffer);
		audio_out_unprepare(g_pstAudioOutputHandle);
		return 1;
	}
	else 
	{
		FPRINTF("[Line : %d][%s] PASS, size=%d, nRet=%d\\n", __LINE__, API_NAMESPACE, unSize, nRet);
	}

	FREE_MEMORY(pszbuffer);

	nRet = audio_out_unprepare(g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_unprepare", AudioOutputGetError(nRet));

	return 0;
}

//& purpose: Sets and Un-sets an asynchronous callback function to handle recording PCM data.
//& type: auto
/**
* @testcase 				ITc_audio_out_set_unset_stream_cb_p
* @since_tizen				2.3
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets and Un-sets an asynchronous callback function to handle recording PCM data.
* @scenario					Get the handle to the audio output\n
*							The callback function to register\n
*							The user data is passed to callback function
* @apicovered				audio_out_set_stream_cb, audio_out_unset_stream_cb				
* @passcase					When audio_out_set_stream_cb is successful
* @failcase					If target API audio_out_set_stream_cb or audio_out_unset_stream_cb fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_out_set_unset_stream_cb_p(void)
{
	START_TEST;
	g_bAudioOutputStreamCallback = false;

	// Target API
	int nRet = audio_out_set_stream_cb(g_pstAudioOutputHandle, AudioOutputStreamCallback, NULL);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_set_stream_cb", AudioOutputGetError(nRet));

	usleep(5000);
	nRet = audio_out_unset_stream_cb (g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_unset_stream_cb", AudioOutputGetError(nRet));
	return 0;
}

//& purpose: Sets the sound stream information to the audio output.
//& type: auto
/**
* @testcase 				ITc_audio_out_set_sound_stream_info_p
* @since_tizen				3.0
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets the sound stream information to the audio output.
* @scenario					Get the handle to the audio output\n
*							call manager for sound stream is called
*							The callback function to register\n
*							The user data is passed to callback function
* @apicovered				audio_out_set_sound_stream_info
* @passcase					When audio_out_set_sound_stream_info is successful
* @failcase					If target API audio_out_set_sound_stream_info fails or any precondition API fails
* @precondition				Audio handle must be created and sound_manager_create_stream_information must b called and state should be in IDLE state..
* @postcondition			Audio handle must be released and sound_manager_destroy_stream_information must be called.
*/
int ITc_audio_out_set_sound_stream_info_p(void)
{
	START_TEST;

	sound_stream_info_h hStreamInfo = NULL;
	int nRet = -1, nEnumCount = 0, nIterator = 0;

	sound_stream_type_e arrStreamType[] = {
		SOUND_STREAM_TYPE_MEDIA,				/**< Sound stream type for media */
		SOUND_STREAM_TYPE_SYSTEM,				/**< Sound stream type for system */
		SOUND_STREAM_TYPE_ALARM,				/**< Sound stream type for alarm */
		SOUND_STREAM_TYPE_NOTIFICATION,			/**< Sound stream type for notification */
		SOUND_STREAM_TYPE_EMERGENCY,			/**< Sound stream type for emergency */
		SOUND_STREAM_TYPE_VOICE_INFORMATION,	/**< Sound stream type for voice information */
		//SOUND_STREAM_TYPE_VOICE_RECOGNITION,	/**< Sound stream type for voice recognition */
		SOUND_STREAM_TYPE_RINGTONE_VOIP,		/**< Sound stream type for ringtone for VoIP */
		SOUND_STREAM_TYPE_VOIP					/**< Sound stream type for VoIP */
	};
	nEnumCount = sizeof(arrStreamType) / sizeof(arrStreamType[0]);

	for(nIterator = 0; nIterator < nEnumCount; nIterator++)
	{
		nRet = sound_manager_create_stream_information(arrStreamType[nIterator], test_sound_manager_stream_focus_state_changed_cb, NULL, &hStreamInfo);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetOutputError(nRet));

		nRet = audio_out_set_sound_stream_info(g_pstAudioOutputHandle, hStreamInfo);
		PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_out_set_sound_stream_info", AudioOutputGetError(nRet), sound_manager_destroy_stream_information(hStreamInfo));

		nRet = sound_manager_destroy_stream_information(hStreamInfo);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information\\n", SoundManagerGetOutputError(nRet));
	}

	return 0;
}

//& purpose: Pauses feeding of audio data to the device.
//& type: auto
/**
* @testcase 				ITc_audio_out_resume_pause_p
* @since_tizen				3.0
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Pauses feeding of audio data to the device.
* @scenario					Get the handle of audio output
* @apicovered				audio_out_resume, audio_out_pause
* @passcase					When audio_out_resume and audio_out_pause are successful
* @failcase					If audio_out_resume, audio_out_pause or any supporting API fails
* @precondition				Audio handle must be created and the state will be #AUDIO_IO_STATE_RUNNING.
* @postcondition			Audio handle must be released and the state should be #AUDIO_IO_STATE_PAUSED.
*/
int ITc_audio_out_resume_pause_p(void)
{
	START_TEST;

	int nRet = audio_out_prepare(g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_prepare", AudioOutputGetError(nRet));

	sleep(2);
	nRet = audio_out_pause(g_pstAudioOutputHandle);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_out_pause", AudioOutputGetError(nRet), audio_out_unprepare(g_pstAudioOutputHandle));

	sleep(2);
	nRet = audio_out_resume(g_pstAudioOutputHandle);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_out_resume", AudioOutputGetError(nRet), audio_out_unprepare(g_pstAudioOutputHandle));

	nRet = audio_out_unprepare(g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_unprepare", AudioOutputGetError(nRet));

	return 0;
}

//& purpose: Drains buffered audio data from the output stream.
//& type: auto
/**
* @testcase 				ITc_audio_out_drain_p
* @since_tizen				2.4
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Drains buffered audio data from the output stream.
* @scenario					Get the type of sound
* @apicovered				audio_out_drain, audio_out_prepare, audio_out_get_buffer_size,audio_out_write, audio_out_unprepare
* @passcase					When audio_out_drain is successful
* @failcase					If target API audio_out_drain fails or any precondition API fails
* @precondition				Audio handle must be created and the state should be #AUDIO_IO_STATE_RUNNING or #AUDIO_IO_STATE_PAUSED.
* @postcondition			Audio handle must be released.
*/
int ITc_audio_out_drain_p(void)
{
	START_TEST;
	int unSize = 0;
	char *pszbuffer = NULL;

	int nRet = audio_out_prepare(g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_prepare", AudioOutputGetError(nRet));

	nRet = audio_out_get_buffer_size(g_pstAudioOutputHandle, &unSize);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_out_get_buffer_size", AudioOutputGetError(nRet), audio_out_unprepare(g_pstAudioOutputHandle););
	if(unSize == 0)
	{
		FPRINTF("[Line : %d][%s] audio_out_get_buffer_size failed, unSize = 0\\n", __LINE__, API_NAMESPACE);
		audio_out_unprepare(g_pstAudioOutputHandle);
		return 1;
	}
	
	pszbuffer = (char *) calloc (unSize, sizeof(char));
	if(pszbuffer == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to allocate memory\\n", __LINE__, API_NAMESPACE);
		audio_out_unprepare(g_pstAudioOutputHandle);
		return 1;
	}
	nRet = audio_out_write(g_pstAudioOutputHandle, (void*) pszbuffer, unSize);
	if ( nRet < 0 )
	{
		FPRINTF("[Line : %d][%s] FAIL, size=%d, nRet=%d\\n", __LINE__, API_NAMESPACE, unSize, nRet);
		FREE_MEMORY(pszbuffer);
		audio_out_unprepare(g_pstAudioOutputHandle);
		return 1;
	}
	else
	{
		FPRINTF("[Line : %d][%s] PASS, size=%d, nRet=%d\\n", __LINE__, API_NAMESPACE, unSize, nRet);
	}

	// Target API
	nRet = audio_out_drain(g_pstAudioOutputHandle);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_out_drain", AudioOutputGetError(nRet), FREE_MEMORY(pszbuffer); audio_out_unprepare(g_pstAudioOutputHandle););

	FREE_MEMORY(pszbuffer);

	nRet = audio_out_unprepare(g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_unprepare", AudioOutputGetError(nRet));

	return 0;
}
//& purpose: Flushes and discards buffered audio data from the output stream.
//& type: auto
/**
* @testcase 				ITc_audio_out_flush_p
* @since_tizen				2.4
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Flushes and discards buffered audio data from the output stream.
* @scenario					Get the type of sound
* @apicovered				audio_out_flush
* @passcase					When audio_out_flush is successful
* @failcase					If target API audio_out_flush fails or any precondition API fails
* @precondition				Audio handle must be created and the state should be #AUDIO_IO_STATE_RUNNING or #AUDIO_IO_STATE_PAUSED.
* @postcondition			Audio handle must be released
*/
int ITc_audio_out_flush_p(void)
{
	START_TEST;
	int unSize = 0;
	char *pszbuffer = NULL;

	int nRet = audio_out_prepare(g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_prepare", AudioOutputGetError(nRet));

	nRet = audio_out_get_buffer_size(g_pstAudioOutputHandle, &unSize);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_out_get_buffer_size", AudioOutputGetError(nRet), audio_out_unprepare(g_pstAudioOutputHandle););
	if(unSize == 0)
	{
		FPRINTF("[Line : %d][%s] audio_out_get_buffer_size failed, unSize = 0\\n", __LINE__, API_NAMESPACE);
		audio_out_unprepare(g_pstAudioOutputHandle);
		return 1;
	}
	pszbuffer = (char *) calloc (unSize, sizeof(char));
	if(pszbuffer == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to allocate memory\\n", __LINE__, API_NAMESPACE);
		audio_out_unprepare(g_pstAudioOutputHandle);
		return 1;
	}
	nRet = audio_out_write(g_pstAudioOutputHandle, (void*) pszbuffer, unSize);
	if ( nRet < 0 )
	{
		FPRINTF("[Line : %d][%s] FAIL, size=%d, nRet=%d\\n", __LINE__, API_NAMESPACE, unSize, nRet);
		FREE_MEMORY(pszbuffer);
		audio_out_unprepare(g_pstAudioOutputHandle);
		return 1;
	}
	else
	{
		FPRINTF("[Line : %d][%s] PASS, size=%d, nRet=%d\\n", __LINE__, API_NAMESPACE, unSize, nRet);
	}

	// Target API
	nRet = audio_out_flush(g_pstAudioOutputHandle);
	PRINT_RESULT_CLEANUP(AUDIO_IO_ERROR_NONE, nRet, "audio_out_flush", AudioOutputGetError(nRet), FREE_MEMORY(pszbuffer); audio_out_unprepare(g_pstAudioOutputHandle););

	FREE_MEMORY(pszbuffer);

	nRet = audio_out_unprepare(g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_unprepare", AudioOutputGetError(nRet));
	return 0;
}

//& purpose: Sets and Un-sets an asynchronous callback function to handle recording PCM data.
//& type: auto
/**
* @testcase 				ITc_audio_out_set_unset_state_changed_cb_p
* @since_tizen				3.0
* @author					SRID(sk.roy)
* @reviewer					SRID(gupta.sanjay)
* @type 					auto
* @description				Sets and Un-sets an asynchronous callback function to handle recording PCM data.
* @scenario					Get the handle to the audio output\n
*							The callback function to register\n
*							The user data is passed to callback function
* @apicovered				audio_out_set_state_changed_cb, audio_out_unset_state_changed_cb
* @passcase					When audio_out_set_state_changed_cb is successful
* @failcase					If target API audio_out_set_state_changed_cb or audio_out_unset_state_changed_cb fails or any precondition API fails
* @precondition				Audio handle must be created
* @postcondition			Audio handle must be released
*/
int ITc_audio_out_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	// Target API
	int nRet = audio_out_set_state_changed_cb(g_pstAudioOutputHandle, AudioOutputStateChangedCallback, NULL);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_set_state_changed_cb", AudioOutputGetError(nRet));

	nRet = audio_out_unset_state_changed_cb (g_pstAudioOutputHandle);
	PRINT_RESULT(AUDIO_IO_ERROR_NONE, nRet, "audio_out_unset_state_changed_cb", AudioOutputGetError(nRet));
	return 0;
}

/** @} */
/** @} */
