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

/** @addtogroup itc-recorder-attr
*  @ingroup itc
*  @{
*/

/**
* @function 		ITs_recorder_attr_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_recorder_attr_startup(void)
{

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
	ecore_main_loop_glib_integrate();

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Recorder_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_recorder_attr_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_recorder_attr_cleanup(void)
{
	sleep(SLEEP_TIME);

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Recorder_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& purpose: Sets and Gets the number of the audio channel
//& type: auto
/**
* @testcase 			ITc_recorder_attr_set_get_audio_channel_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to Sets and Gets the number of the audio channel
* @scenario				Create Audio recorder\n
*						Sets the number of the audio channel\n
*						Gets the number of the audio channel
* @apicovered			recorder_attr_set_audio_channel, recorder_attr_get_audio_channel
* @passcase				If it sets the number of the audio channel to record successfully and gets it successfully
* @failcase 			If recorder_attr_set_audio_channel or recorder_attr_get_audio_channel fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_attr_set_get_audio_channel_p(void)
{

	START_TEST;
	int nChannelCount;

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
	int nRet = recorder_attr_set_audio_channel(g_pstRecorder,1);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_audio_channel", RecorderGetError(nRet), DestroyRecorderHandler());

	usleep(2000);

	// Target API
	nRet = recorder_attr_get_audio_channel(g_pstRecorder, &nChannelCount);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_get_audio_channel", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( nChannelCount != 1 )
	{
		FPRINTF("[Line : %d][%s] recorder_attr_set_get_audio_channel mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		DestroyRecorderHandler();
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}

	return 0;
}
//& purpose: Sets and Gets the audio device for recording
//& type: auto
/**
* @testcase 			ITc_recorder_attr_set_get_audio_device_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to Sets and Gets the audio device for recording
* @scenario				Create Audio recorder\n
*						Sets audio device for recording\n
*						Gets audio device for recording
* @apicovered			recorder_attr_set_audio_device, recorder_attr_get_audio_device
* @passcase				If it sets the audio device to record successfully and gets it successfully
* @failcase 			If recorder_attr_set_audio_device or recorder_attr_get_audio_device fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_attr_set_get_audio_device_p(void)
{
	START_TEST;
	recorder_audio_device_e device;

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
	int nRet = recorder_attr_set_audio_device(g_pstRecorder,RECORDER_AUDIO_DEVICE_MIC);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_audio_device", RecorderGetError(nRet), DestroyRecorderHandler());

	// Target API
	nRet = recorder_attr_get_audio_device(g_pstRecorder, &device);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_get_audio_device", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( device != RECORDER_AUDIO_DEVICE_MIC )
	{
		FPRINTF("[Line : %d][%s] recorder_attr_set_get_audio_device mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		DestroyRecorderHandler();
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the bitrate of audio encoder
//& type: auto
/**
* @testcase 			ITc_recorder_attr_set_get_audio_encoder_bitrate_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to Sets and Gets the bitrate of audio encoder
* @scenario				Create Audio recorder\n
*						Sets the bitrate of audio encoder\n
*						Gets the bitrate of audio encoder
* @apicovered			recorder_attr_set_audio_encoder_bitrate, recorder_attr_get_audio_encoder_bitrate
* @passcase				If it sets and gets the bitrate of audio encoder successfully
* @failcase 			If recorder_attr_set_audio_encoder_bitrate or recorder_attr_get_audio_encoder_bitrate fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_attr_set_get_audio_encoder_bitrate_p(void)
{
	START_TEST;
	int nSetBitRate = 12200, nGetBitRate;

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
	int nRet = recorder_attr_set_audio_encoder_bitrate(g_pstRecorder, nSetBitRate);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_audio_encoder_bitrate", RecorderGetError(nRet), DestroyRecorderHandler());

	// Target API
	nRet = recorder_attr_get_audio_encoder_bitrate(g_pstRecorder, &nGetBitRate);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_get_audio_encoder_bitrate", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( nGetBitRate != nSetBitRate )
	{
		FPRINTF("[Line : %d][%s] recorder_attr_set_get_audio_encoder_bitrate mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		DestroyRecorderHandler();
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the sampling rate of audio stream
//& type: auto
/**
* @testcase 			ITc_recorder_attr_set_get_audio_samplerate_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to Sets and Gets the sampling rate of audio stream
* @scenario				Create Audio recorder\n
*						Sets the sampling rate of audio stream\n
*						Gets the sampling rate of audio stream
* @apicovered			recorder_attr_set_audio_samplerate, recorder_attr_get_audio_samplerate
* @passcase				If it sets and gets the sampling rate of audio stream successfully
* @failcase 			If recorder_attr_set_audio_samplerate or recorder_attr_get_audio_samplerate fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_attr_set_get_audio_samplerate_p(void)
{
	START_TEST;
	int nSamplerate;

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
	int nRet = recorder_attr_set_audio_samplerate(g_pstRecorder,100);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_audio_samplerate", RecorderGetError(nRet), DestroyRecorderHandler());

	// Target API
	nRet = recorder_attr_get_audio_samplerate(g_pstRecorder, &nSamplerate);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_get_audio_samplerate", RecorderGetError(nRet), DestroyRecorderHandler());

	if ( nSamplerate != 100 )
	{
		FPRINTF("[Line : %d][%s] recorder_attr_set_get_audio_samplerate mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		DestroyRecorderHandler();
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the video orientation in a video meta-data tag
//& type: auto
/**
* @testcase 			ITc_recorder_attr_set_get_orientation_tag_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to Sets and Gets the video orientation in a video meta-data tag
* @scenario				Create Video recorder\n
*						Sets the video orientation in a video meta-data tag\n
*						Gets the video orientation in a video meta-data tag
* @apicovered			recorder_attr_set_orientation_tag, recorder_attr_get_orientation_tag
* @passcase				If it sets and gets the video orientation in a video meta-data tag successfully
* @failcase 			If recorder_attr_set_orientation_tag or recorder_attr_get_orientation_tag fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_attr_set_get_orientation_tag_p(void)
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
	if( g_bCamFeatureNotSupported || g_bVideoRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_videorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	recorder_rotation_e eSetOrientation = RECORDER_ROTATION_90, eGetOrientation;

	// Target API
	int nRet = recorder_attr_set_orientation_tag(g_pstRecorder, eSetOrientation);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_orientation_tag", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());

	// Target API
	nRet = recorder_attr_get_orientation_tag(g_pstRecorder, &eGetOrientation);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_get_orientation_tag", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());
	if ( eGetOrientation != eSetOrientation)
	{
		FPRINTF("[Line : %d][%s] recorder_attr_set_get_orientation_tag mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
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

//& purpose: Sets and Gets the recording motion rate
//& type: auto
/**
* @testcase 			ITc_recorder_attr_set_get_recording_motion_rate_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to Sets and Gets the recording motion rate
* @scenario				Create Video recorder\n
*						Sets the recording motion rate\n
*						Gets the recording motion rate
* @apicovered			recorder_attr_set_recording_motion_rate, recorder_attr_get_recording_motion_rate
* @passcase				If it sets and gets the recording motion rate successfully
* @failcase 			If recorder_attr_set_recording_motion_rate or recorder_attr_get_recording_motion_rate fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_attr_set_get_recording_motion_rate_p(void)
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
	if(  g_bCamFeatureNotSupported || g_bVideoRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_videorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	double nSetMotionRate = 1, nGetMotionRate;

	// Target API
	int nRet = recorder_attr_set_recording_motion_rate(g_pstRecorder, nSetMotionRate);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_recording_motion_rate", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());

	// Target API
	nRet = recorder_attr_get_recording_motion_rate(g_pstRecorder, &nGetMotionRate);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_get_recording_motion_rate", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());
	if ( nGetMotionRate != nSetMotionRate )
	{
		FPRINTF("[Line : %d][%s] recorder_attr_set_get_recording_motion_rate mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
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

//& purpose: Sets and Gets the maximum size of recording file
//& type: auto
/**
* @testcase 			ITc_recorder_attr_set_get_size_limit_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to Sets and Gets the maximum size of recording file
* @scenario				Create Video recorder\n
*						Sets the maximum size of recording file\n
*						Gets the maximum size of recording file
* @apicovered			recorder_attr_set_size_limit, recorder_attr_get_size_limit
* @passcase				If it sets and gets the maximum size of recording file successfully
* @failcase 			If recorder_attr_set_size_limit or recorder_attr_get_size_limit fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_attr_set_get_size_limit_p(void)
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
	if( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_audiorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nSetSizeLimit = 0, nGetSizeLimit;

	// Target API
	int nRet = recorder_attr_set_size_limit(g_pstRecorder, nSetSizeLimit);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_size_limit", RecorderGetError(nRet), DestroyRecorderHandler());

	// Target API
	nRet = recorder_attr_get_size_limit(g_pstRecorder, &nGetSizeLimit);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_get_size_limit", RecorderGetError(nRet), DestroyRecorderHandler());

	if ( nGetSizeLimit != nSetSizeLimit )
	{
		FPRINTF("[Line : %d][%s] recorder_attr_set_get_size_limit mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		DestroyRecorderHandler();
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the time limit of recording file
//& type: auto
/**
* @testcase 			ITc_recorder_attr_set_get_time_limit_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				- Create Audio recorder
- Sets the time limit of recording file
- Gets the time limit of recording file
* @description			to Sets and Gets the time limit of recording file
* @apicovered			recorder_attr_set_time_limit, recorder_attr_get_time_limit
* @passcase				If it sets and gets the time limit of recording file successfully
* @failcase 			If recorder_attr_set_time_limit or recorder_attr_get_time_limit fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_attr_set_get_time_limit_p(void)
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
	if( g_bAudioRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_videorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nSetTimeLimit = 0, nGetTimeLimit;

	// Target API
	int nRet = recorder_attr_set_time_limit(g_pstRecorder, nSetTimeLimit);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_time_limit", RecorderGetError(nRet), DestroyRecorderHandler());

	// Target API
	nRet = recorder_attr_get_time_limit(g_pstRecorder, &nGetTimeLimit);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_get_time_limit", RecorderGetError(nRet), DestroyRecorderHandler());
	if ( nGetTimeLimit != nSetTimeLimit )
	{
		FPRINTF("[Line : %d][%s] recorder_attr_set_get_time_limit mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		DestroyRecorderHandler();
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}

//& purpose: Sets and Gets the bitrate of video encoder
//& type: auto
/**
* @testcase 			ITc_recorder_attr_set_get_video_encoder_bitrate_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Video recorder\n
*						Sets the bitrate of video encoder\n
*						Gets the bitrate of video encoder
* @description			to Sets and Gets the bitrate of video encoder
* @apicovered			recorder_attr_set_video_encoder_bitrate, recorder_attr_get_video_encoder_bitrate
* @passcase				If it sets and gets the bitrate of video encoder successfully
* @failcase 			If recorder_attr_set_video_encoder_bitrate or recorder_attr_set_video_encoder_bitrate fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_attr_set_get_video_encoder_bitrate_p(void)
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
	if( g_bCamFeatureNotSupported || g_bVideoRecFeatureNotSupported )
	{
		FPRINTF("[Line : %d][%s][Not supported] system_info_get_platform_bool and recorder_create_videorecorder returned Unsupported feature capability for Recorder\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nSetBitRate = 100, nGetBitRate;

	// Target API
	int nRet = recorder_attr_set_video_encoder_bitrate(g_pstRecorder, nSetBitRate);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_video_encoder_bitrate", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());

	// Target API
	nRet = recorder_attr_get_video_encoder_bitrate(g_pstRecorder, &nGetBitRate);
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_get_video_encoder_bitrate", RecorderGetError(nRet), camera_destroy(g_pstCamera);DestroyRecorderHandler());

	if ( nGetBitRate != nSetBitRate )
	{
		FPRINTF("[Line : %d][%s] recorder_attr_set_get_video_encoder_bitrate mismatched, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
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

//& purpose: Sets mute state of recorder and check if it is muted
//& type: auto
/**
* @testcase 			ITc_recorder_attr_mute_p
* @since_tizen 			2.3
* @author				SRID(anshul1.jain)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @scenario				Create Audio recorder\n
*						Sets mute state of recorder\n
*						Check if it is muted
* @description			to Set mute state of recorder and check if it is muted
* @apicovered			recorder_attr_set_mute, recorder_attr_is_muted
* @passcase				If it Sets mute state of recorder and check if it is muted successfully
* @failcase 			If recorder_attr_set_mute or recorder_attr_is_muted fails
* @precondition			The recorder state must be RECORDER_STATE_CREATED
* @postcondition		NA
*/
int ITc_recorder_attr_mute_p(void)
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
	int nRet = recorder_attr_set_mute(g_pstRecorder,true );
	PRINT_RESULT_CLEANUP(RECORDER_ERROR_NONE, nRet, "recorder_attr_set_mute", RecorderGetError(nRet), DestroyRecorderHandler());

	// Target API
	bool bValue;
	bValue = recorder_attr_is_muted(g_pstRecorder);
	if ( bValue != true )
	{
		FPRINTF("[Line : %d][%s] recorder_attr_is_muted failed, error returned\\n", __LINE__, API_NAMESPACE);
		DestroyRecorderHandler();
		return 1;
	}
	if ( DestroyRecorderHandler() == false )
	{
		return 1;
	}
	return 0;
}
/** @} */
/** @} */
