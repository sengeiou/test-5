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
#include "ITs-recorder-common.h"

/** @addtogroup itc-recorder
*  @ingroup itc
*  @{
*/

//& set: Recorder

bool g_bRecorderCreation;
bool g_bRecorderPreviewStarted;
bool g_bRecorderErrorCallback;
bool g_bRecorderAudioStreamCallback;
bool g_bRecorderInterruptCompletedCallback;
bool g_bRecorderInterruptedCallback;
bool g_bRecorderRecordingLimitReachedCallback;
bool g_bRecorderRecordingStatusCallback;
bool g_bRecorderStateChangedCallback;
bool g_bRecorderSupportedVideoEncoderCallback;
bool g_bRecorderSupportedVideoResolutionCallback;
bool g_bStateChange;
bool g_bVideoEncodeDecisionCallback;

/**
* @function 		ITs_recorder_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_recorder_startup(void)
{

	g_bCamFeatureNotSupported = false;
	g_bAudioRecFeatureNotSupported = false;
	g_bVideoRecFeatureNotSupported = false;
		
	ecore_main_loop_glib_integrate();
	g_bIsCameraFeatureSupported = TCTCheckSystemInfoFeatureSupported(CAMERA_FEATURE, API_NAMESPACE);
	if ( !g_bIsCameraFeatureSupported )
	{
		g_bCamFeatureNotSupported = true;
	}

	g_bIsAudioRecordingFeatureSupported = TCTCheckSystemInfoFeatureSupported(AUDIO_RECORDING_FEATURE, API_NAMESPACE);
	if ( !g_bIsAudioRecordingFeatureSupported )
	{
		g_bAudioRecFeatureNotSupported = true;
	}
	g_bIsVideoRecordingFeatureSupported = TCTCheckSystemInfoFeatureSupported(VIDEO_RECORDING_FEATURE, API_NAMESPACE);
	if ( !g_bIsVideoRecordingFeatureSupported )
	{
		g_bVideoRecFeatureNotSupported = true;
	}
	
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Recorder_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		ITs_recorder_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_recorder_cleanup(void)
{
	sleep(SLEEP_TIME);

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Recorder_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		device_state_Changed_callback
* @description	 	callback function for device state change
* @parameter		recorder_type_e type, recorder_device_state_e state, void *user_data
* @return 			NA
*/
static void device_state_changed_callback(recorder_type_e type, recorder_device_state_e state, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Inside callback \"device_state_changed_callback\"\\n", __LINE__, API_NAMESPACE);
#endif

	g_bStateChange = true;
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
}

/**
* @function 		recorder_muxed_stream_callback
* @description	 	callback function for device state change
* @parameter		void *stream, int size, unsigned long long offset, void *user_data
* @return 			NA
*/
static void recorder_muxed_stream_callback(void *stream, int size, unsigned long long offset, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Inside callback \"recorder_muxed_stream_callback\"\\n", __LINE__, API_NAMESPACE);
#endif

	g_bStateChange = true;
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
}

/**
* @function 		sound_stream_focus_state_changed_callback
* @description	 	callback function for stream focus state change
* @parameter		stream : stream info, focus_mask, focus_state, focus change reason: reason for change, behavior, extra_info, user_data : user data
* @return 			NA
*/
static void sound_stream_focus_state_changed_callback(sound_stream_info_h stream_info,
													sound_stream_focus_mask_e focus_mask,
													sound_stream_focus_state_e focus_state,
													sound_stream_focus_change_reason_e reason,
													int sound_behavior,
													const char *extra_info,
													void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] Inside callback \"sound_stream_focus_state_changed_callback\"\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}

}

/**
* @function 		RecorderInterruptedCallback
* @description	 	callback function for capturing if recorder is interrupted according to a policy
* @parameter		recorder_policy_e policy, recorder_state_e previous, recorder_state_e current, void *user_data
* @return 			NA
*/
static void RecorderInterruptedCallback(recorder_policy_e policy, recorder_state_e previous, recorder_state_e current, void *user_data)
{
	g_bRecorderInterruptedCallback = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] RecorderInterruptedCallback callback is called\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
}

/**
* @function 		RecorderErrorCallback
* @description	 	callback function for capturing asynchronous operation error occurred
* @parameter		recorder_error_e error, recorder_state_e current_state, void *user_data
* @return 			NA
*/
static void RecorderErrorCallback(recorder_error_e error, recorder_state_e current_state, void *user_data)
{
	g_bRecorderErrorCallback = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] RecorderErrorCallback callback is called\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
}

/**
* @function 		RecorderRecordingLimitReachedCallback
* @description	 	callback function for capturing if reached recording limit
* @parameter		recorder_recording_limit_type_e type, void *user_data
* @return 			NA
*/
static void RecorderRecordingLimitReachedCallback(recorder_recording_limit_type_e type, void *user_data)
{
	g_bRecorderRecordingLimitReachedCallback = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] RecorderRecordingLimitReachedCallback callback is called\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
}

/**
* @function 		RecorderRecordingStatusCallback
* @description	 	callback function for capturing if recording information changes
* @parameter		unsigned long long elapsed_time, unsigned long long file_size, void *user_data
* @return 			NA
*/
static void RecorderRecordingStatusCallback(unsigned long long elapsed_time, unsigned long long file_size, void *user_data)
{
	g_bRecorderRecordingStatusCallback = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] RecorderRecordingStatusCallback callback is called\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
}

/**
* @function 		RecorderStateChangedCallback
* @description	 	callback function for capturing if the recorder state changes
* @parameter		recorder_state_e previous, recorder_state_e current, bool by_policy, void *user_data
* @return 			NA
*/
static void RecorderStateChangedCallback(recorder_state_e previous, recorder_state_e current, bool by_policy, void *user_data)
{
	g_bRecorderStateChangedCallback = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] RecorderStateChangedCallback callback is called\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
}

/**
* @function 		RecorderAudioStreamCallback
* @description	 	callback function for capturing audio stream data
* @parameter		void *stream, int size, audio_sample_type_e format, int channel, unsigned int timestamp, void *user_data
* @return 			NA
*/
static void RecorderAudioStreamCallback(void *stream, int size, audio_sample_type_e format, int channel, unsigned int timestamp, void *user_data)
{
	g_bRecorderAudioStreamCallback = true;
#if DEBUG
	FPRINTF("[Line : %d][%s] RecorderAudioStreamCallback callback is called\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
}

/**
* @function 		RecorderSupportedVideoEncoderCallback
* @description	 	callback function for retrieving all supported video encoders
* @parameter		recorder_video_codec_e codec, void *user_data
* @return 			NA
*/
static bool RecorderSupportedVideoEncoderCallback(recorder_video_codec_e codec, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] RecorderSupportedVideoEncoderCallback callback is called\\n", __LINE__, API_NAMESPACE);
#endif

	g_bRecorderSupportedVideoEncoderCallback = true;

	bool ret = true;
	if ( user_data != NULL )
	{
		*( (recorder_video_codec_e *)user_data) = codec;
		return false;
	}
	return ret;
}

/**
* @function 		RecorderSupportedVideoResolutioCallback
* @description	 	callback function for retrieving all supported video resolutions
* @parameter		int width, int height, void *user_data
* @return 			NA
*/
static bool RecorderSupportedVideoResolutionCallback(int width, int height, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] RecorderSupportedVideoResolutionCallback callback is called\\n", __LINE__, API_NAMESPACE);
#endif

	g_bRecorderSupportedVideoResolutionCallback = true;

	g_nWidth = width;
	g_nHeight = height;

	return false;
}

/**
* @function 		VideoEncodeDecisionCallback
* @description	 	Called when each video frame is delivered before encoding
* @parameter		recorder_video_data_s *frame, void *user_data
* @return 			NA
*/
static bool VideoEncodeDecisionCallback(recorder_video_data_s *frame, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] VideoEncodeDecisionCallback callback is called\\n", __LINE__, API_NAMESPACE);
#endif

	g_bVideoEncodeDecisionCallback = true;

	return true;
}

/** @addtogroup itc-recorder-testcases
*  @brief 		Integration testcases for module recorder
*  @ingroup 	itc-recorder
*  @{
*/

//& purpose: Creates the audio recorder
//& type: auto
/**
* @testcase 			ITc_recorder_create_audiorecorder_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to create audio recorder and destroy it
* @scenario				Create Audio recorder\n
*						Destroy recorder
* @apicovered			recorder_create_audiorecorder, recorder_destroy
* @passcase				If recorder gets created successfully
* @failcase 			If recorder_create_audiorecorder or recorder_destroy fails
* @precondition			NA
* @postcondition		The recorder state will be RECORDER_STATE_CREATED
*/
int ITc_recorder_create_audiorecorder_p(void)
{
	START_TEST;
	// Target API
	int nRet = recorder_create_audiorecorder(&g_pstRecorder);
	if ( g_bAudioRecFeatureNotSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] recorder_create_audiorecorder returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
			return 1;
		}

		FPRINTF("[Line : %d][%s] recorder_create_audiorecorder API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		return 0;
	}

	PRINT_RESULT(RECORDER_ERROR_NONE, nRet, "recorder_create_audiorecorder", RecorderGetError(nRet));

	// Target API
	nRet = recorder_destroy(g_pstRecorder);
	if ( g_bAudioRecFeatureNotSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] recorder_destroy returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
			return 1;
		}

		FPRINTF("[Line : %d][%s] recorder_destroy API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		return 0;
	}

	PRINT_RESULT(RECORDER_ERROR_NONE, nRet, "recorder_destroy", RecorderGetError(nRet));
	return 0;
}

//& purpose: Creates the video recorder
//& type: auto
/**
* @testcase 			ITc_recorder_create_videorecorder_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to create video recorder and destroy it
* @scenario				Create Video recorder\n
*						Destroy recorder
* @apicovered			recorder_create_videorecorder, recorder_destroy
* @passcase				If recorder gets created successfully
* @failcase 			If recorder_create_videorecorder or recorder_destroy fails
* @precondition			NA
* @postcondition		The recorder state will be RECORDER_STATE_CREATED
*/
int ITc_recorder_create_videorecorder_p(void)
{
	START_TEST;

	int nRet = camera_create(CAMERA_DEVICE_CAMERA0, &g_pstCamera);
	if ( g_bCamFeatureNotSupported  )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] camera_create returned 0x%x error for unsupported feature\\n", __LINE__, API_NAMESPACE, nRet);
			return 1;
		}
		FPRINTF("[Line : %d][%s] camera_create API call correctly returned TIZEN_ERROR_NOT_SUPPORTED for unsupported feature\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	// Target API
	nRet = recorder_create_videorecorder(g_pstCamera, &g_pstRecorder);
	if (g_bVideoRecFeatureNotSupported  )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] recorder_create_videorecorder returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
			camera_destroy(g_pstCamera);;
			return 1;;
		}
		FPRINTF("[Line : %d][%s] recorder_create_videorecorder API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		camera_destroy(g_pstCamera);
		return 0;
	}

	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_create_videorecorder", RecorderGetError(nRet), camera_destroy(g_pstCamera));

	// Target API
	nRet = recorder_destroy(g_pstRecorder);
	if (g_bCamFeatureNotSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] recorder_destroy returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
			camera_destroy(g_pstCamera);
			return 1;
		}
		FPRINTF("[Line : %d][%s] recorder_destroy API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		camera_destroy(g_pstCamera);
		return 0;
	}

	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_destroy", RecorderGetError(nRet), camera_destroy(g_pstCamera));

	nRet = camera_destroy(g_pstCamera);
	if ( nRet != CAMERA_ERROR_NONE )
	{
		FPRINTF( "[Line : %d][%s] camera_destroy failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Prepare and unprepare the recorder
//& type: auto
/**
* @testcase 			ITc_recorder_prepare_unprepare_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to prepare and unprepare recorder
* @scenario				Create audio recorder\n
*						Prepares recorder\n
*						Destroy recorder
* @apicovered			recorder_set_audio_encoder, recorder_set_file_format, recorder_prepare and recorder_unprepare
* @passcase				If recorder gets prepared successfully
* @failcase 			If recorder does not get prepared successfully
* @precondition			The recorder state should be RECORDER_STATE_CREATED by recorder_create_videorecorder(), recorder_create_audiorecorder() or recorder_unprepare().
* @postcondition		The recorder state will be RECORDER_STATE_READY. If recorder handle is created by recorder_create_videorecorder(), camera state will be changed to CAMERA_STATE_PREVIEW.
*/
int ITc_recorder_prepare_unprepare_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int user_data[USER_DATA_MAX];
	recorder_audio_codec_e codec;
	memset(user_data, 0, sizeof(int) * USER_DATA_MAX);	
	recorder_file_format_e eSetFileFormat = -1;

	
	int nRet = recorder_foreach_supported_audio_encoder(g_pstRecorder, RecorderSupportedAudioEncoderCallback, &codec);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_audio_encoder", RecorderGetError(nRet), DestroyRecorderHandler());	
		
	if ((int)codec >= 0 && (int)codec < ITC_AUDIO_CODEC_NUM) {
	
		user_data[USER_DATA_AUDIO_CODEC] = (int)codec;
		int nRet = recorder_foreach_supported_file_format(g_pstRecorder, RecorderSupportedFileFormatCallback, user_data);
		PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_file_format", RecorderGetError(nRet), DestroyRecorderHandler());	
		eSetFileFormat = (recorder_file_format_e)user_data[USER_DATA_FILE_FORMAT];		
	}else{
		FPRINTF("[Line : %d][%s] failed, error = RECORDER_ERROR_NOT_SUPPORTED", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}
	
	nRet = recorder_set_audio_encoder(g_pstRecorder, codec);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_audio_encoder", RecorderGetError(nRet), DestroyRecorderHandler());

	nRet = recorder_set_file_format(g_pstRecorder,eSetFileFormat);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_file_format", RecorderGetError(nRet), DestroyRecorderHandler());

	//Target API
	nRet = recorder_prepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_prepare", RecorderGetError(nRet), DestroyRecorderHandler());

	//Target API
	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());
	
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Starts and cancels the recorder
//& type: auto
/**
* @testcase 			ITc_recorder_start_cancel_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to start and cancel recorder
* @scenario				Create audio recorder\n
*						Starts recorder\n
*						Cancels it and then destroy it
* @apicovered			recorder_start, recorder_cancel, recorder_get_state and recorder_unprepare
* @passcase				If recorder gets started successfully
* @failcase 			If recorder does not get started successfully
* @precondition			The recorder state must be RECORDER_STATE_READY by recorder_prepare() or RECORDER_STATE_PAUSED by recorder_pause()
* @postcondition		The recorder state will be RECORDER_STATE_RECORDING
*/
int ITc_recorder_start_cancel_p(void)
{
	START_TEST;
	recorder_state_e state;

	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	// Target API
	int nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_get_state(g_pstRecorder, &state);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_state", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	if ( state != RECORDER_STATE_RECORDING )
	{
		FPRINTF("[Line : %d][%s] recorder_get_state failed to return RECORDER_STATE_RECORDING, state returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetState(state));
		recorder_cancel(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	// Target API
	nRet = recorder_cancel(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_cancel", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Starts and commit the recorder
//& type: auto
/**
* @testcase 			ITc_recorder_start_commit_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to start and commit recorder
* @scenario				Create audio recorder\n
*						Starts recorder\n
*						Commits it and then destroy it
* @apicovered			recorder_start, recorder_commit, recorder_get_state, recorder_unprepare and recorder_cancel
* @passcase				If recorder gets commit successfully
* @failcase 			If recorder does not get commit successfully
* @precondition			The recorder state must be RECORDER_STATE_READY by recorder_prepare() or RECORDER_STATE_PAUSED by recorder_pause()
* @postcondition		The recorder state will be RECORDER_STATE_RECORDING
*/
int ITc_recorder_start_commit_p(void)
{
	START_TEST;
	recorder_state_e state;

	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	int nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	// Target API
	nRet = recorder_commit(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_commit", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_get_state(g_pstRecorder, &state);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_state", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	if ( state!= RECORDER_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] recorder_get_state failed to return RECORDER_STATE_READY, state returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetState(state));
		recorder_cancel(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Gets the recorder's current state
//& type: auto
/**
* @testcase 			ITc_recorder_get_state_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get the recorder's current state
* @scenario				Create Audio recorder\n
*						Gets the recorder's current state and destroy recorder
* @apicovered			recorder_get_state
* @passcase				if it gets the recorder's current state successfully
* @failcase 			If recorder_get_state fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED by recorder_create() or recorder_unprepare()
* @postcondition		NA
*/
int ITc_recorder_get_state_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	// Target API
	recorder_state_e state;
	int nRet = recorder_get_state(g_pstRecorder, &state);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_state", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Pause the recorder
//& type: auto
/**
* @testcase 			ITc_recorder_pause_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to pause the recorder
* @scenario				Create Audio recorder\n
*						Gets the recorder's ready\n
*						Starts the recorder\n
*						Pause the recorder and then destroy recorder
* @apicovered			recorder_start, recorder_get_state, recorder_unprepare, recorder_pause and recorder_cancel
* @passcase				if it gets the recorder's paused successfully
* @failcase 			If recorder_pause fails
* @precondition			The recorder state must be RECORDER_STATE_RECORDING
* @postcondition		The recorder state will be RECORDER_STATE_PAUSED
*/
int ITc_recorder_pause_p(void)
{
	START_TEST;
	recorder_state_e state;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	int nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	// Target API
	nRet = recorder_pause(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_pause", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	nRet = recorder_get_state(g_pstRecorder, &state);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_state", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	if ( state!= RECORDER_STATE_PAUSED )
	{
		FPRINTF("[Line : %d][%s] recorder_get_state failed to return RECORDER_STATE_PAUSED, state returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetState(state));
		recorder_cancel(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	nRet = recorder_cancel(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_cancel", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the file path to record
//& type: auto
/**
* @testcase 			ITc_recorder_set_filename_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to Sets and Gets the file path to record
* @scenario				Create Audio recorder\n
*						Sets the file path to record\n
*						Gets the file path to record
* @apicovered			recorder_set_filename, recorder_get_filename
* @passcase				if it sets the file path to record successfully and gets it successfully
* @failcase 			If recorder_set_filename or recorder_get_filename fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED by recorder_create() or recorder_unprepare()
* @postcondition		NA
*/
int ITc_recorder_set_get_filename_p(void)
{
	START_TEST;
	char* pchGetFilename = NULL;

	GetFileName();
	char* pchSetFilename = strdup(g_RecorderFile);
	if(NULL ==pchSetFilename)
	{
		FPRINTF("[Line : %d][%s] geting pchSetFilename failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	FREE_MEMORY(g_RecorderFile);

	if ( CreateAudioRecorder() == false )
	{
		FREE_MEMORY(pchSetFilename);
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pchSetFilename);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported || g_bCamFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pchSetFilename);
		return 0;
	}

	// Target API
	int nRet = recorder_set_filename(g_pstRecorder,pchSetFilename);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_filename", RecorderGetError(nRet), DestroyRecorderHandler();FREE_MEMORY(pchSetFilename););

	// Target API
	nRet = recorder_get_filename(g_pstRecorder, &pchGetFilename);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_filename", RecorderGetError(nRet), DestroyRecorderHandler();FREE_MEMORY(pchSetFilename));
	if ( strcmp(pchSetFilename, pchGetFilename) != 0)
	{
		FPRINTF("[Line : %d][%s] recorder_set_get_filename mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		DestroyRecorderHandler();
		FREE_MEMORY(pchSetFilename);
		return 1;
	}

	FREE_MEMORY(pchSetFilename);
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the audio codec for encoding audio stream
//& type: auto
/**
* @testcase 			ITc_recorder_set_get_audio_encoder_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Audio recorder\n
*						Sets the audio codec for encoding audio stream\n
*						Gets the audio codec for encoding audio stream
* @description			to Sets and Gets the audio codec for encoding audio stream
* @apicovered			recorder_set_audio_encoder, recorder_get_audio_encoder
* @passcase				If it sets and gets the audio codec for encoding audio stream successfully
* @failcase 			If recorder_set_audio_encoder or recorder_get_audio_encoder fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_set_get_audio_encoder_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	recorder_audio_codec_e eSetAudioCoder = -2, eGetAudioCoder;	
	int user_data[USER_DATA_MAX];	
	memset(user_data, 0, sizeof(int) * USER_DATA_MAX);	
	
	int nRet = recorder_foreach_supported_audio_encoder(g_pstRecorder, RecorderSupportedAudioEncoderCallback, &eSetAudioCoder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_audio_encoder", RecorderGetError(nRet), DestroyRecorderHandler());	
		
	if ((int)eSetAudioCoder >= 0 && (int)eSetAudioCoder < ITC_AUDIO_CODEC_NUM) {
	
		user_data[USER_DATA_AUDIO_CODEC] = (int)eSetAudioCoder;
		int nRet = recorder_foreach_supported_file_format(g_pstRecorder, RecorderSupportedFileFormatCallback, user_data);
		PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_file_format", RecorderGetError(nRet), DestroyRecorderHandler());	
	}else{
		FPRINTF("[Line : %d][%s] failed, error = RECORDER_ERROR_NOT_SUPPORTED", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}	
	
	// Target API
	nRet = recorder_set_audio_encoder(g_pstRecorder, eSetAudioCoder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_audio_encoder", RecorderGetError(nRet), DestroyRecorderHandler());

	// Target API
	nRet = recorder_get_audio_encoder(g_pstRecorder, &eGetAudioCoder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_audio_encoder", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( eGetAudioCoder != eSetAudioCoder )
	{
		FPRINTF("[Line : %d][%s] recorder_set_get_audio_encoder mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		DestroyRecorderHandler();
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the video codec for encoding video stream
//& type: auto
/**
* @testcase 			ITc_recorder_set_get_video_encoder_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Video recorder\n
*						Sets the video codec for encoding video stream\n
*						Gets the video codec for encoding video stream
* @description			to Sets and Gets the video codec for encoding video stream
* @apicovered			recorder_set_video_encoder, recorder_get_video_encoder, camera_destroy and recorder_get_video_encoder
* @passcase				If it sets and gets the video codec for encoding video stream successfully
* @failcase 			If recorder_attr_set_video_encoder or recorder_attr_get_video_encoder fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_set_get_video_encoder_p(void)
{
	START_TEST;
	if ( CreateVideoRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_videorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bCamFeatureNotSupported || g_bVideoRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_videorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	g_bRecorderSupportedVideoEncoderCallback = false;
	recorder_video_codec_e eSetVideoCoder = -1, eGetVideoCoder = -1;
	int nRet = recorder_foreach_supported_video_encoder(g_pstRecorder, RecorderSupportedVideoEncoderCallback, &eSetVideoCoder);
	if ( nRet != RECORDER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] recorder_foreach_supported_video_encoder failed, error returned = %s", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		return 1;
	}
	else if((eSetVideoCoder<RECORDER_VIDEO_CODEC_H263)||(eSetVideoCoder>RECORDER_VIDEO_CODEC_THEORA))
	{
		FPRINTF("[Line : %d][%s] recorder_foreach_supported_video_encoder failed,Invalid Output", __LINE__, API_NAMESPACE);
		return 1;
	}

	if (!g_bRecorderSupportedVideoEncoderCallback)
	{
		FPRINTF("[Line : %d][%s] recorder_foreach_supported_video_encoder_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Target API
	nRet = recorder_set_video_encoder(g_pstRecorder, eSetVideoCoder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_video_encoder", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());

	// Target API
	nRet = recorder_get_video_encoder(g_pstRecorder, &eGetVideoCoder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_video_encoder", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());
	if ( eGetVideoCoder != eSetVideoCoder )
	{
		FPRINTF("[Line : %d][%s] recorder_set_get_video_encoder mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		DestroyRecorderHandler();
		camera_destroy(g_pstCamera);
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		camera_destroy(g_pstCamera);
		return 1;
	}

	nRet = camera_destroy(g_pstCamera);
	if ( nRet != CAMERA_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] camera_destroy failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the resolution of video recording
//& type: auto
/**
* @testcase 			ITc_recorder_set_get_video_resolution_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Video recorder\n
*						Sets the resolution of video recording\n
*						Gets the resolution of video recording
* @description			to Sets and Gets the resolution of video recording
* @apicovered			recorder_set_video_resolution, recorder_get_video_resolution
* @passcase				If it sets and gets the resolution of video recording successfully
* @failcase 			If recorder_set_video_resolution or recorder_get_video_resolution fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_set_get_video_resolution_p(void)
{
	START_TEST;
	if ( CreateVideoRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_videorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bCamFeatureNotSupported || g_bVideoRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_videorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = recorder_foreach_supported_video_resolution(g_pstRecorder, RecorderSupportedVideoResolutionCallback, NULL);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_video_resolution", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());
	if (!g_bRecorderSupportedVideoResolutionCallback)
	{
		FPRINTF("[Line : %d][%s] recorder_foreach_supported_video_resolution_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		camera_destroy(g_pstCamera);
		return 1;
	}
	// Target API
	nRet = recorder_set_video_resolution(g_pstRecorder, g_nWidth, g_nHeight);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_video_resolution", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());

	usleep(2000);

	// Target API
	int nWidth, nHeight;
	nRet = recorder_get_video_resolution(g_pstRecorder, &nWidth, &nHeight);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_video_resolution", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());

	if ( nWidth != g_nWidth || nHeight != g_nHeight )
	{
		FPRINTF("[Line : %d][%s] recorder_set_get_video_resolution mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		camera_destroy(g_pstCamera);
		DestroyRecorderHandler();
		return 1;
	}

	if ( DestroyRecorderHandler() == false )
	{
		camera_destroy(g_pstCamera);
		return 1;
	}

	nRet = camera_destroy(g_pstCamera);
	if ( nRet != CAMERA_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] camera_destroy failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the file format for recording media stream
//& type: auto
/**
* @testcase 			ITc_recorder_set_get_file_format_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Video recorder\n
*						Sets the file format for recording media stream\n
*						Gets the file format for recording media stream
* @description			to Sets and Gets the file format for recording media stream
* @apicovered			recorder_set_file_format, recorder_get_file_format
* @passcase				If it sets and gets the file format for recording media stream successfully
* @failcase 			If recorder_set_file_format or recorder_get_file_format fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_set_get_file_format_p(void)
{
	START_TEST;
	if ( CreateVideoRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_videorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bCamFeatureNotSupported || g_bVideoRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_videorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int user_data[USER_DATA_MAX];
	recorder_audio_codec_e codec;
	memset(user_data, 0, sizeof(int) * USER_DATA_MAX);	
	recorder_file_format_e eSetFileFormat = -1, eGetFileFormat;

	
	int nRet = recorder_foreach_supported_audio_encoder(g_pstRecorder, RecorderSupportedAudioEncoderCallback, &codec);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_audio_encoder", RecorderGetError(nRet), DestroyRecorderHandler());	
		
	if ((int)codec >= 0 && (int)codec < ITC_AUDIO_CODEC_NUM) {
	
		user_data[USER_DATA_AUDIO_CODEC] = (int)codec;
		int nRet = recorder_foreach_supported_file_format(g_pstRecorder, RecorderSupportedFileFormatCallback, user_data);
		PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_file_format", RecorderGetError(nRet), DestroyRecorderHandler());	
		eSetFileFormat = (recorder_file_format_e)user_data[USER_DATA_FILE_FORMAT];		
	}else{
		FPRINTF("[Line : %d][%s] failed, error = RECORDER_ERROR_NOT_SUPPORTED", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}		

	// Target API
	nRet = recorder_set_file_format(g_pstRecorder, eSetFileFormat);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_file_format", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());

	// Target API
	nRet = recorder_get_file_format(g_pstRecorder, &eGetFileFormat);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_file_format", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());
	if ( eGetFileFormat != eSetFileFormat )
	{
		FPRINTF("[Line : %d][%s] recorder_set_get_file_format mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		DestroyRecorderHandler();
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		camera_destroy(g_pstCamera);
		return 1;
	}

	nRet = camera_destroy(g_pstCamera);
	if ( nRet != CAMERA_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] camera_destroy failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Gets the peak audio input level that was sampled since the last call to this function
//& type: auto
/**
* @testcase 			ITc_recorder_get_audio_level_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Video recorder\n
*						Gets the peak audio input level that was sampled since the last call to this function
* @description			to get the peak audio input level that was sampled since the last call to this function
* @apicovered			recorder_get_audio_level
* @passcase				If it gets the peak audio input level that was sampled since the last call to this function successfully
* @failcase 			If recorder_get_audio_level fails
* @precondition			The recorder state must be RECORDER_STATE_RECORDING or RECORDER_STATE_PAUSED.
* @postcondition		NA
*/
int ITc_recorder_get_audio_level_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	int nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	// Target API
	double dB = -1.0;
	nRet = recorder_get_audio_level(g_pstRecorder, &dB);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_audio_level", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	if(dB == -1.0)
	{
		FPRINTF( "[Line : %d][%s] recorder_get_audio_level failed,output value is invalid\\n", __LINE__, API_NAMESPACE);
		recorder_cancel(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	nRet = recorder_cancel(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_cancel", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Registers and Unregisters a callback function to be called when recorder is interrupted according to a policy
//& type: auto
/**
* @testcase 			ITc_recorder_set_unset_interrupted_cb_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Audio recorder\n
*						Registers and Unregisters a callback function to be called when recorder is interrupted according to a policy
* @description			to Registers and Unregisters a callback function to be called when recorder is interrupted according to a policy
* @apicovered			recorder_set_interrupted_cb, recorder_unset_interrupted_cb
* @passcase				If it Registers and Unregisters a callback function to be called when recorder is interrupted according to a policy
* @failcase 			If recorder_set_interrupted_cb or recorder_unset_interrupted_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_recorder_set_unset_interrupted_cb_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported || g_bCamFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	g_bRecorderInterruptedCallback = false;

	// Target API
	int nRet = recorder_set_interrupted_cb(g_pstRecorder, RecorderInterruptedCallback, NULL);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_interrupted_cb", RecorderGetError(nRet), DestroyRecorderHandler());

	/** unable to generate required manual interruption for callback invocation, so ignoring callback hit check*/

	// Target API
	nRet = recorder_unset_interrupted_cb(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unset_interrupted_cb", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Registers and Unregisters a callback function to be called when an asynchronous operation error occurred
//& type: auto
/**
* @testcase 			ITc_recorder_set_unset_error_cb_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Audio recorder\n
*						Registers and Unregisters a callback function to be called when an asynchronous operation error occurred
* @description			to Registers and Unregisters a callback function to be called when an asynchronous operation error occurred
* @apicovered			recorder_set_error_cb, recorder_unset_error_cb
* @passcase				If it Registers and Unregisters a callback function to be called when an asynchronous operation error occurred
* @failcase 			If recorder_set_error_cb or recorder_unset_error_cb fails
* @precondition			NA
* @postcondition		This function will invoke recorder_error_cb() when an asynchronous operation error occur.
*/
int ITc_recorder_set_unset_error_cb_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	// Target API
	g_bRecorderErrorCallback = false;
	int nRet = recorder_set_error_cb(g_pstRecorder, RecorderErrorCallback, NULL);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_error_cb", RecorderGetError(nRet), DestroyRecorderHandler());

	/** unable to generate required error for callback invocation, so ignoring callback hit check*/

	// Target API
	nRet = recorder_unset_error_cb(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unset_error_cb", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Registers and Unregisters a callback function to be called when reached recording limit
//& type: auto
/**
* @testcase 			ITc_recorder_set_unset_recording_limit_reached_cb_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Audio recorder\n
*						Registers and Unregisters a callback function to be called when reached recording limit
* @description			to Registers and Unregisters a callback function to be called when reached recording limit
* @apicovered			recorder_set_recording_limit_reached_cb, recorder_unset_recording_limit_reached_cb
* @passcase				If it Registers and Unregisters a callback function to be called when reached recording limit
* @failcase 			If recorder_set_recording_limit_reached_cb or recorder_unset_recording_limit_reached_cb fails
* @precondition			NA
* @postcondition		recorder_recording_limit_reached_cb() will be invoked
*/
int ITc_recorder_set_unset_recording_limit_reached_cb_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	// Target API
	g_bRecorderRecordingLimitReachedCallback = false;
	int nRet = recorder_set_recording_limit_reached_cb(g_pstRecorder, RecorderRecordingLimitReachedCallback, NULL);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_recording_limit_reached_cb", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_attr_set_time_limit(g_pstRecorder,3);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_time_limit", RecorderGetError(nRet), recorder_unset_recording_limit_reached_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), recorder_unset_recording_limit_reached_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	recorder_state_e state;
	nRet = recorder_get_state(g_pstRecorder, &state);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_error_cb", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unset_recording_limit_reached_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	if ( state != RECORDER_STATE_RECORDING )
	{
		FPRINTF("[Line : %d][%s] recorder_get_state failed to return RECORDER_STATE_RECORDING, state returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetState(state));
		recorder_cancel(g_pstRecorder);
		recorder_unset_recording_limit_reached_cb(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	RecorderWaitForAsync();

	if (!g_bRecorderRecordingLimitReachedCallback)
	{
		FPRINTF("[Line : %d][%s] recorder_recording_limit_reached_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		recorder_cancel(g_pstRecorder);
		recorder_unset_recording_limit_reached_cb(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	nRet = recorder_cancel(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_cancel", RecorderGetError(nRet), DestroyRecorderHandler());

	// Target API
	nRet = recorder_unset_recording_limit_reached_cb(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unset_recording_limit_reached_cb", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Registers and Unregisters a callback function to be called when the recording information changes
//& type: auto
/**
* @testcase 			ITc_recorder_set_unset_recording_status_cb_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Audio recorder\n
*						Registers and Unregisters a callback function to be called when the recording information changes
* @description			to Registers and Unregisters a callback function to be called when the recording information changes
* @apicovered			recorder_set_recording_status_cb, recorder_unset_recording_status_cb
* @passcase				If it Registers and Unregisters a callback function to be called when the recording information changes
* @failcase 			If recorder_set_recording_status_cb or recorder_unset_recording_status_cb fails
* @precondition			NA
* @postcondition		recorder_recording_status_cb() will be invoked
*/
int ITc_recorder_set_unset_recording_status_cb_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	// Target API
	g_bRecorderRecordingStatusCallback = false;
	int nRet = recorder_set_recording_status_cb(g_pstRecorder, RecorderRecordingStatusCallback, NULL);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_recording_status_cb", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), recorder_unset_recording_status_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	recorder_state_e state;
	nRet = recorder_get_state(g_pstRecorder, &state);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_state", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unset_recording_status_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	if ( state!= RECORDER_STATE_RECORDING )
	{
		FPRINTF("[Line : %d][%s] recorder_get_state failed to return RECORDER_STATE_RECORDING, state returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetState(state));
		recorder_cancel(g_pstRecorder);
		recorder_unset_recording_status_cb(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	RecorderWaitForAsync();

	if ( !g_bRecorderRecordingStatusCallback )
	{
		FPRINTF("[Line : %d][%s] recorder_recording_status_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		recorder_cancel(g_pstRecorder);
		recorder_unset_recording_status_cb(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	nRet = recorder_cancel(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_cancel", RecorderGetError(nRet), recorder_unset_recording_status_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	// Target API
	nRet = recorder_unset_recording_status_cb(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unset_recording_status_cb", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Registers and Unregisters a callback function to be called when the recorder state changes
//& type: auto
/**
* @testcase 			ITc_recorder_set_unset_state_changed_cb_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Audio recorder\n
*						Registers and Unregisters a callback function to be called when the recorder state changes
* @description			to Registers and Unregisters a callback function to be called when the recorder state changes
* @apicovered			recorder_set_state_changed_cb, recorder_unset_state_changed_cb
* @passcase				If it Registers and Unregisters a callback function to be called when the recorder state changes
* @failcase 			If recorder_set_state_changed_cb or recorder_unset_state_changed_cb fails
* @precondition			NA
* @postcondition		RECORDER_STATE_changed_cb() will be invoked
*/
int ITc_recorder_set_unset_state_changed_cb_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	// Target API
	g_bRecorderStateChangedCallback = false;
	int nRet = recorder_set_state_changed_cb(g_pstRecorder, RecorderStateChangedCallback, NULL);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_state_changed_cb", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), recorder_unset_state_changed_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	recorder_state_e state;
	nRet = recorder_get_state(g_pstRecorder, &state);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_state", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unset_state_changed_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	if ( state != RECORDER_STATE_RECORDING )
	{
		FPRINTF("[Line : %d][%s] recorder_get_state failed to return RECORDER_STATE_RECORDING, state returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetState(state));
		recorder_cancel(g_pstRecorder);
		recorder_unset_state_changed_cb(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	RecorderWaitForAsync();

	if ( !g_bRecorderStateChangedCallback )
	{
		FPRINTF("[Line : %d][%s] RECORDER_STATE_changed_cb failed, error returned = callback not invoked, time out\\n", __LINE__, API_NAMESPACE);
		recorder_cancel(g_pstRecorder);
		recorder_unset_state_changed_cb(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	nRet = recorder_cancel(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_cancel", RecorderGetError(nRet), recorder_unset_state_changed_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	// Target API
	nRet = recorder_unset_state_changed_cb(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unset_state_changed_cb", RecorderGetError(nRet), DestroyRecorderHandler());

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet));

	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Registers and Unregisters a callback function to be called when audio stream data is being delivered
//& type: auto
/**
* @testcase 			ITc_recorder_set_unset_audio_stream_cb_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Audio recorder\n
*						Registers and Unregisters a callback function to be called when audio stream data is being delivered
* @description			to Registers and Unregisters a callback function to be called when audio stream data is being delivered
* @apicovered			recorder_set_audio_stream_cb, recorder_unset_audio_stream_cb
* @passcase				If it Registers and Unregisters a callback function to be called when audio stream data is being delivered
* @failcase 			If recorder_set_audio_stream_cb or recorder_unset_audio_stream_cb fails
* @precondition			The recorder state should be RECORDER_STATE_READY or RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_set_unset_audio_stream_cb_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	// Target API
	g_bRecorderAudioStreamCallback = false;
	int nRet = recorder_set_audio_stream_cb(g_pstRecorder, RecorderAudioStreamCallback, NULL);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_audio_stream_cb", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), recorder_unset_audio_stream_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	recorder_state_e state;
	nRet = recorder_get_state(g_pstRecorder, &state);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_get_state", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unset_audio_stream_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	if ( state != RECORDER_STATE_RECORDING )
	{
		FPRINTF("[Line : %d][%s] recorder_get_state failed to return RECORDER_STATE_RECORDING, state returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetState(state));
		recorder_cancel(g_pstRecorder);
		recorder_unset_audio_stream_cb(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	RecorderWaitForAsync();

	if (!g_bRecorderAudioStreamCallback)
	{
		FPRINTF("[Line : %d][%s] recorder_audio_stream_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		recorder_cancel(g_pstRecorder);
		recorder_unset_audio_stream_cb(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	nRet = recorder_cancel(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_cancel", RecorderGetError(nRet), recorder_unset_audio_stream_cb(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	// Target API
	nRet = recorder_unset_audio_stream_cb(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unset_audio_stream_cb", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Retrieves all supported file formats by invoking a specific callback for each supported file format
//& type: auto
/**
* @testcase 			ITc_recorder_foreach_supported_file_format_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Audio recorder\n
*						Retrieves all supported file formats by invoking a specific callback for each supported file format
* @description			to Retrieve all supported file formats by invoking a specific callback for each supported file format
* @apicovered			recorder_foreach_supported_file_format
* @passcase				If it Retrieves all supported file formats by invoking a specific callback for each supported file format successfully
* @failcase 			If recorder_foreach_supported_file_format fails
* @precondition			NA
* @postcondition		recorder_supported_file_format_cb() will be invoked
*/
int ITc_recorder_foreach_supported_file_format_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int user_data[USER_DATA_MAX];
	recorder_audio_codec_e codec = RECORDER_AUDIO_CODEC_DISABLE;
	memset(user_data, 0, sizeof(int) * USER_DATA_MAX);		

	// Target API		
	int nRet = recorder_foreach_supported_audio_encoder(g_pstRecorder, RecorderSupportedAudioEncoderCallback, &codec);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_audio_encoder", RecorderGetError(nRet), DestroyRecorderHandler());
		
	if ((int)codec >= 0 && (int)codec < ITC_AUDIO_CODEC_NUM) {
	
		user_data[USER_DATA_AUDIO_CODEC] = (int)codec;
		// Target API
		nRet = recorder_foreach_supported_file_format(g_pstRecorder, RecorderSupportedFileFormatCallback, user_data);
		PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_file_format", RecorderGetError(nRet), DestroyRecorderHandler());	
		
		if ( DestroyRecorderHandler() == false )
		{
			return 1;
		}		
	}else{
		FPRINTF("[Line : %d][%s] failed, error = RECORDER_ERROR_NOT_SUPPORTED", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}
	return 0;
}

//& purpose: Retrieves all supported audio encoders by invoking a specific callback for each supported audio encoder
//& type: auto
/**
* @testcase 			ITc_recorder_foreach_supported_audio_encoder_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Audio recorder\n
*						Retrieves all supported audio encoders by invoking a specific callback for each supported audio encoder
* @description			to Retrieve all supported audio encoders by invoking a specific callback for each supported audio encoder.
* @apicovered			recorder_foreach_supported_audio_encoder
* @passcase				If it Retrieves all supported audio encoders by invoking a specific callback for each supported audio encoder.
* @failcase 			If recorder_foreach_supported_audio_encoder fails
* @precondition			NA
* @postcondition		recorder_supported_audio_encoder_cb() will be invoked.
*/
int ITc_recorder_foreach_supported_audio_encoder_p(void)
{
	START_TEST;
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	int user_data[USER_DATA_MAX];
	recorder_audio_codec_e codec = RECORDER_AUDIO_CODEC_DISABLE;
	memset(user_data, 0, sizeof(int) * USER_DATA_MAX);		

	// Target API		
	int nRet = recorder_foreach_supported_audio_encoder(g_pstRecorder, RecorderSupportedAudioEncoderCallback, &codec);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_audio_encoder", RecorderGetError(nRet), DestroyRecorderHandler());
		
	if ((int)codec >= 0 && (int)codec < ITC_AUDIO_CODEC_NUM) {
	
		user_data[USER_DATA_AUDIO_CODEC] = (int)codec;
		nRet = recorder_foreach_supported_file_format(g_pstRecorder, RecorderSupportedFileFormatCallback, user_data);
		PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_file_format", RecorderGetError(nRet), DestroyRecorderHandler());	
		if ( DestroyRecorderHandler() == false )
		{
			return 1;
		}
	}else{
		FPRINTF("[Line : %d][%s] failed, error = RECORDER_ERROR_NOT_SUPPORTED", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}
	
	
	return 0;
}

//& purpose: Retrieves all supported video encoders by invoking a specific callback for each supported video encoder
//& type: auto
/**
* @testcase 			ITc_recorder_foreach_supported_video_encoder_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Video recorder\n
*						Retrieves all supported video encoders by invoking a specific callback for each supported video encoder
* @description			to Retrieves all supported video encoders by invoking a specific callback for each supported video encoder
* @apicovered			recorder_foreach_supported_video_encoder
* @passcase				If it Retrieves all supported video encoders by invoking a specific callback for each supported video encoder
* @failcase 			If recorder_foreach_supported_video_encoder fails
* @precondition			NA
* @postcondition		recorder_supported_video_encoder_cb() will be invoked.
*/
int ITc_recorder_foreach_supported_video_encoder_p(void)
{
	START_TEST;
	if ( CreateVideoRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_videorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bCamFeatureNotSupported  || g_bVideoRecFeatureNotSupported)
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_videorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	recorder_video_codec_e codec = -1;
	
	// Target API
	g_bRecorderSupportedVideoEncoderCallback = false;
	int nRet = recorder_foreach_supported_video_encoder(g_pstRecorder, RecorderSupportedVideoEncoderCallback, &codec);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_video_encoder", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());
	if((codec<0)||(codec>3))
	{
		FPRINTF("[Line : %d][%s] recorder_foreach_supported_video_encoder failed,Invalid Output", __LINE__, API_NAMESPACE);
		return 1;
	}

	if (!g_bRecorderSupportedVideoEncoderCallback)
	{
		FPRINTF("[Line : %d][%s] recorder_foreach_supported_video_encoder_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		camera_destroy(g_pstCamera);
		DestroyRecorderHandler();
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		camera_destroy(g_pstCamera);
		return 1;
	}

	nRet = camera_destroy(g_pstCamera);
	if ( nRet != CAMERA_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] camera_destroy failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Retrieves all supported video resolutions by invoking callback function once for each supported video resolution
//& type: auto
/**
* @testcase 			ITc_recorder_foreach_supported_video_resolution_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Video recorder\n
*						Retrieves all supported video resolutions by invoking callback function once for each supported video resolution
* @description			to Retrieve all supported video resolutions by invoking callback function once for each supported video resolution
* @apicovered			recorder_foreach_supported_video_resolution
* @passcase				If it Retrieves all supported video resolutions by invoking callback function once for each supported video resolution
* @failcase 			If recorder_foreach_supported_video_resolution fails
* @precondition			NA
* @postcondition		This function invokes recorder_supported_video_resolution_cb() repeatedly to retrieve each supported video resolution.
*/
int ITc_recorder_foreach_supported_video_resolution_p(void)
{
	START_TEST;
	if ( CreateVideoRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_videorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bCamFeatureNotSupported  || g_bVideoRecFeatureNotSupported)
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_videorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	// Target API
	g_bRecorderSupportedVideoResolutionCallback = false;
	int nRet = recorder_foreach_supported_video_resolution(g_pstRecorder, RecorderSupportedVideoResolutionCallback, NULL);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_foreach_supported_video_encoder", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());

	if ( !g_bRecorderSupportedVideoResolutionCallback )
	{
		FPRINTF("[Line : %d][%s] recorder_foreach_supported_video_resolution_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		camera_destroy(g_pstCamera);
		DestroyRecorderHandler();
		return 1;
	}

	if ( DestroyRecorderHandler() == false )
	{
		camera_destroy(g_pstCamera);
		return 1;
	}

	nRet = camera_destroy(g_pstCamera);
	if ( nRet != CAMERA_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] camera_destroy failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Set the recorder's sound manager stream information
//& type: auto
/**
* @testcase 			ITc_recorder_set_sound_stream_info_p
* @since_tizen 		3.0
* @author				SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 				auto
* @scenario			Set the recorder's sound manager stream information
* @description		Set the recorder's sound manager stream information
* @apicovered		recorder_set_sound_stream_info
* @passcase		If recorder_set_sound_stream_info passes
* @failcase 			If recorder_set_sound_stream_info fails
* @precondition		The recorder state should be RECORDER_STATE_READY or RECORDER_STATE_CREATED
* @postcondition	NA
*/
int ITc_recorder_set_sound_stream_info_p(void)
{
	START_TEST;

	sound_stream_info_h hStreamInfo = NULL;

	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
        if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, sound_stream_focus_state_changed_callback, NULL, &hStreamInfo);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));
	CHECK_HANDLE(hStreamInfo, "sound_manager_create_stream_information");
		
	// Target API
	nRet = recorder_set_sound_stream_info(g_pstRecorder, hStreamInfo);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_sound_stream_info", RecorderGetError(nRet), DestroyRecorderHandler());

	nRet = sound_manager_destroy_stream_information(hStreamInfo);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));
	
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	
	return 0;
}

//& purpose: To gets the state of recorder device.
//& type: auto
/**
* @testcase 			ITc_recorder_get_device_state_p
* @since_tizen 			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @scenario				To gets the state of recorder device.
* @description			To gets the state of recorder device.
* @apicovered			recorder_get_device_state
* @passcase				If recorder_get_device_state passes
* @failcase 			If recorder_get_device_state fails
* @precondition			The recorder state should be RECORDER_STATE_READY or RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_get_device_state_p(void)
{
	START_TEST;

	recorder_device_state_e eDeviceState = RECORDER_DEVICE_STATE_IDLE;

	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	// Target API
	int nRet = recorder_get_device_state(RECORDER_TYPE_AUDIO, &eDeviceState);
	PRINT_RESULT(RECORDER_ERROR_NONE, nRet, "recorder_get_device_state", RecorderGetError(nRet));
	
	if( eDeviceState != RECORDER_DEVICE_STATE_IDLE && eDeviceState != RECORDER_DEVICE_STATE_RECORDING && eDeviceState != RECORDER_DEVICE_STATE_PAUSED )
	{
		FPRINTF("[Line : %d][%s]invalid recorder state\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	
	return 0;
}

//& purpose: Registers and Unregisters a callback function
//& type: auto
/**
* @testcase 			ITc_recorder_add_remove_device_state_changed_cb_p
* @since_tizen 			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @scenario				Registers and Unregisters a callback function
* @description			Registers and Unregisters a callback function
* @apicovered			recorder_add_device_state_changed_cb, recorder_remove_device_state_changed_cb
* @passcase				If recorder_add_device_state_changed_cb and recorder_remove_device_state_changed_cb passes
* @failcase 			If recorder_add_device_state_changed_cb or recorder_remove_device_state_changed_cb fails
* @precondition			The recorder state should be RECORDER_STATE_READY or RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_add_remove_device_state_changed_cb_p(void)
{
	START_TEST;

	int nId = 0;
	
	if ( CreateAudioRecorder() == false )
	{
		return 1;
	}
	
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}
	
	g_bStateChange = false;
	
	// Target API
 	int nRet = recorder_add_device_state_changed_cb( device_state_changed_callback, NULL, &nId );
	PRINT_RESULT(RECORDER_ERROR_NONE, nRet, "recorder_add_device_state_changed_cb", RecorderGetError(nRet));
	
	nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	
	nRet = recorder_pause(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_pause", RecorderGetError(nRet), recorder_cancel(g_pstRecorder);recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());
	RecorderWaitForAsync();
	if( g_bStateChange == false )
	{
		FPRINTF("[Line : %d][%s]Callback Not Hit\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}
	
	if( nId > 0 )
	{
		nRet = recorder_remove_device_state_changed_cb( nId );
		PRINT_RESULT(RECORDER_ERROR_NONE, nRet, "recorder_remove_device_state_changed_cb", RecorderGetError(nRet));
	}
	
	nRet = recorder_cancel(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_cancel", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder);DestroyRecorderHandler());

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());
	
	if ( DestroyRecorderHandler() == false )
	{
		FPRINTF("[Line : %d][%s]DestroyRecorderHandler returns false\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& purpose: Registers and Unregisters a callback function
//& type: auto
/**
* @testcase 			ITc_recorder_set_unset_muxed_stream_cb_p
* @since_tizen 			4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @scenario				Registers and Unregisters a callback function
* @description			Registers and Unregisters a callback function
* @apicovered			recorder_set_muxed_stream_cb, recorder_unset_muxed_stream_cb
* @passcase				If recorder_set_muxed_stream_cb and recorder_unset_muxed_stream_cb passes
* @failcase 			If recorder_set_muxed_stream_cb or recorder_unset_muxed_stream_cb fails
* @precondition			The recorder state should be RECORDER_STATE_READY or RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_set_unset_muxed_stream_cb_p(void)
{
	START_TEST;

	if ( CreateAudioRecorder() == false )
	{
		FPRINTF("[Line : %d][%s] CreateAudioRecorder function fail so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_audiorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	g_bStateChange = false;

	int nRet = recorder_set_muxed_stream_cb(g_pstRecorder, recorder_muxed_stream_callback, NULL);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_muxed_stream_cb", RecorderGetError(nRet),DestroyRecorderHandler());

	nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), DestroyRecorderHandler());

	RecorderWaitForAsync();
	if( g_bStateChange == false )
	{
		FPRINTF("[Line : %d][%s]Callback Not Hit\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	nRet = recorder_cancel(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_cancel", RecorderGetError(nRet), DestroyRecorderHandler());

	nRet = recorder_unset_muxed_stream_cb(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unset_muxed_stream_cb", RecorderGetError(nRet),DestroyRecorderHandler());

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());

	if ( DestroyRecorderHandler() == false )
	{
		FPRINTF("[Line : %d][%s]DestroyRecorderHandler returns false\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Registers and unregisters a callback function to be called when each video frame is delivered before encoding.
//& type: auto
/**
* @testcase 			ITc_recorder_set_unset_video_encode_decision_cb_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @scenario				This test is for checking parameters valid or not. \n
*						1. Check microphone supported or not. \n
*						2. Set video encode decision callback.
*						3. Unset video encode decision callback.
* @description			To check set and unset video encode decision callback with valid pointer and parameters.
* @apicovered			recorder_set_video_encode_decision_cb, recorder_unset_video_encode_decision_cb
* @passcase				If recorder_set_video_encode_decision_cb and recorder_unset_video_encode_decision_cb passes
* @failcase 			If recorder_set_video_encode_decision_cb, recorder_unset_video_encode_decision_cb fails
* @precondition			The recorder state should be RECORDER_STATE_READY or RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_set_unset_video_encode_decision_cb_p(void)
{
	START_TEST;
	recorder_state_e state;

	if ( CreateVideoRecorder() == false )
	{
		return 1;
	}
	if ( g_bMismatch )
	{
		FPRINTF("[Line : %d][%s] system_info_get_platform_bool and recorder_create_videorecorder returned different feature for Recorder so leaving test\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( g_bCamFeatureNotSupported || g_bVideoRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_videorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}

	g_bVideoEncodeDecisionCallback = false;

	int nRet = recorder_set_video_encode_decision_cb(g_pstRecorder, VideoEncodeDecisionCallback, NULL);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_set_video_encode_decision_cb", RecorderGetError(nRet), recorder_cancel(g_pstRecorder); recorder_unprepare(g_pstRecorder); DestroyRecorderHandler());

	nRet = recorder_start(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_start", RecorderGetError(nRet), recorder_cancel(g_pstRecorder); recorder_unprepare(g_pstRecorder); DestroyRecorderHandler());

	RecorderWaitForAsync();

	if ( !g_bVideoEncodeDecisionCallback )
	{
		FPRINTF("[Line : %d][%s] recorder_set_video_encode_decision_cb failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		recorder_cancel(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		DestroyRecorderHandler();
		return 1;
	}

	nRet = recorder_cancel(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_cancel", RecorderGetError(nRet), recorder_unprepare(g_pstRecorder); DestroyRecorderHandler());

	nRet = recorder_unprepare(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unprepare", RecorderGetError(nRet), DestroyRecorderHandler());

	nRet = recorder_unset_video_encode_decision_cb(g_pstRecorder);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_unset_video_encode_decision_cb", RecorderGetError(nRet), DestroyRecorderHandler());

	if ( DestroyRecorderHandler() == false )
	{
		FPRINTF("[Line : %d][%s]DestroyRecorderHandler returns false\\n", __LINE__, API_NAMESPACE);
	}

	return 0;
}

/** @} */
/** @} */
