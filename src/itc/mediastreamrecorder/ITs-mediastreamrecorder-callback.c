//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-mediastreamrecorder-common.h"

//& set: Mediastreamrecoder

/** @addtogroup itc-mediastreamrecoder
*  @ingroup itc
*  @{
*/

streamrecorder_h g_hCallRecorder = NULL;

/**
* @function 		Streamrecorder_consume_completed_cb_p
* @description	 	Callback Function
* @parameter		void *buffer, void *user_data
* @return 			NA
*/
void Streamrecorder_consume_completed_cb_p(void *buffer, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Streamrecorder_consume_completed_cb_p callback\\n", __LINE__, API_NAMESPACE);
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @function 		Streamrecorder_error_cb_p
* @description	 	Callback Function
* @parameter		streamrecorder_error_e error, streamrecorder_state_e current_state, void *user_data
* @return 			NA
*/
void Streamrecorder_error_cb_p(streamrecorder_error_e error, streamrecorder_state_e current_state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Streamrecorder_error_cb_p callback\\n", __LINE__, API_NAMESPACE);
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @function 		StreamRecorder_recording_limit_reached_cb_p
* @description	 	Callback Function
* @parameter		streamrecorder_recording_limit_type_e type,  void *user_data
* @return 			NA
*/
void StreamRecorder_recording_limit_reached_cb_p(streamrecorder_recording_limit_type_e type,  void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside StreamRecorder_recording_limit_reached_cb_p callback\\n", __LINE__, API_NAMESPACE);
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @function 		StreamRecorder_recording_status_cb_p
* @description	 	Callback Function
* @parameter		unsigned long long elapsed_time, unsigned long long file_size,  void *user_data
* @return 			NA
*/
void StreamRecorder_recording_status_cb_p(unsigned long long elapsed_time, unsigned long long file_size,  void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside StreamRecorder_recording_status_cb_p callback\\n", __LINE__, API_NAMESPACE);
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @function 		StreamRecorder_notify_cb_p
* @description	 	Callback Function
* @parameter		streamrecorder_state_e previous , streamrecorder_state_e current , streamrecorder_notify_e notification,  void *user_data
* @return 			NA
*/
void StreamRecorder_notify_cb_p(streamrecorder_state_e previous , streamrecorder_state_e current , streamrecorder_notify_e notification,  void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside StreamRecorder_notify_cb_p callback\\n", __LINE__, API_NAMESPACE);
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @function 		StreamRecorder_supported_video_resolution_cb_p
* @description	 	Callback Function
* @parameter		int width, int height, void *user_data
* @return 			NA
*/
bool StreamRecorder_supported_video_resolution_cb_p(int width, int height, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside StreamRecorder_supported_video_resolution_cb_p callback\\n", __LINE__, API_NAMESPACE);
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
    return true;
}

/**
* @function 		StreamRecorder_supported_video_encoder_cb_p
* @description	 	Callback Function
* @parameter		streamrecorder_video_codec_e codec, void *user_data
* @return 			NA
*/
bool StreamRecorder_supported_video_encoder_cb_p(streamrecorder_video_codec_e codec, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside StreamRecorder_supported_video_encoder_cb_p callback\\n", __LINE__, API_NAMESPACE);
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
    return true;
}
/**
* @function 		StreamRecorder_supported_audio_encoder_cb_p
* @description	 	Callback Function
* @parameter		streamrecorder_audio_codec_e codec, void *user_data
* @return 			NA
*/
bool StreamRecorder_supported_audio_encoder_cb_p(streamrecorder_audio_codec_e codec, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside StreamRecorder_supported_audio_encoder_cb_p callback\\n", __LINE__, API_NAMESPACE);
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
    return true;
}

/**
* @function 		Streamrecorder_supported_file_format_cb_p
* @description	 	Callback Function
* @parameter		streamrecorder_file_format_e format , void *user_data
* @return 			NA
*/
bool StreamRecorder_supported_file_format_cb_p(streamrecorder_file_format_e format , void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside StreamRecorder_supported_file_format_cb_p callback\\n", __LINE__, API_NAMESPACE);
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
    return true;
}

/**
 * @function 		ITs_mediastreamrecorder_callback_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_mediastreamrecorder_callback_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_mediastreamrecorder_callback_startup\\n", __LINE__, API_NAMESPACE);
#endif
	if ( !TCTCheckSystemInfoFeatureSupported(STREAMRECORDER_FEATURE, API_NAMESPACE) )
	{
		if ( streamrecorder_create(&g_hRecorder) != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bMismatch = true;
		}
		else
		{
			g_bStreamRecorderNotSupported = true;
		}
		return;
	}

	g_bMediaStrRecorderConnect= true;
	int nRet = streamrecorder_create(&g_hCallRecorder);
	if ( nRet != STREAMRECORDER_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] streamrecorder_create fail in startup \\n", __LINE__, API_NAMESPACE);
		g_bMediaStrRecorderConnect = false;
		return;
	}
	else if(g_hCallRecorder == NULL)
	{
		FPRINTF("[Line : %d][%s] g_hCallRecorder is null in startup \\n", __LINE__, API_NAMESPACE);
		g_bMediaStrRecorderConnect = false;
		return;
	}
}


/**
 * @function 		ITs_mediastreamrecorder_callback_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_mediastreamrecorder_callback_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_mediastreamrecorder_callback_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_bMediaStrRecorderConnect)
	{
		streamrecorder_destroy(g_hCallRecorder);
		g_bMediaStrRecorderConnect = NULL;
	}
}

/** @addtogroup itc-mediastreamrecoder-testcases
*  @brief 		Integration testcases for module mediastreamrecoder
*  @ingroup 	itc-mediastreamrecoder
*  @{
*/

//& type: auto
//& purpose:  scenario to Retrieves all supported file formats by invoking a specific callback for each supported file format
/**
* @testcase 			ITc_streamrecorder_foreach_supported_file_format_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Retrieves all supported file formats by invoking a specific callback for each supported file format
* @scenario				create recorder handle \n
*						Retrieves all supported file format \n
* 						destroy recorder handle
* @apicovered			streamrecorder_foreach_supported_file_format
* @passcase				if streamrecorder_foreach_supported_file_format passes
* @failcase				if streamrecorder_foreach_supported_file_format fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_foreach_supported_file_format_p(void)
{
	START_TEST;

	g_bCheckCb = false;
    int nIotconTimeoutId = 0;

    int nRet = streamrecorder_foreach_supported_file_format(g_hCallRecorder, StreamRecorder_supported_file_format_cb_p, "file format");
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_foreach_supported_file_format", StreamRecorderGetError(nRet));

	RUN_POLLING_LOOP;
	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to Retrieves all supported audio encoders by invoking a specific callback for each supported audio encoder.
/**
* @testcase 			ITc_streamrecorder_foreach_supported_audio_encoder_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Retrieves all supported audio encoders by invoking a specific callback for each supported audio encoder.
* @scenario				create recorder handle \n
*						Retrieves all supported audio encoders \n
* 						destroy recorder handle
* @apicovered			streamrecorder_foreach_supported_audio_encoder
* @passcase				if streamrecorder_foreach_supported_audio_encoder passes
* @failcase				if streamrecorder_foreach_supported_audio_encoder fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_foreach_supported_audio_encoder_p(void)
{
	START_TEST;

	g_bCheckCb = false;
    int nIotconTimeoutId = 0;

    int nRet = streamrecorder_foreach_supported_audio_encoder(g_hCallRecorder, StreamRecorder_supported_audio_encoder_cb_p, "audio");
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_foreach_supported_audio_encoder", StreamRecorderGetError(nRet));

	RUN_POLLING_LOOP;
	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to Retrieves all supported video encoders by invoking a specific callback for each supported video encoder
/**
* @testcase 			ITc_streamrecorder_foreach_supported_video_encoder_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Retrieves all supported video encoders by invoking a specific callback for each supported video encoder
* @scenario				create recorder handle \n
*						Retrieves all supported video encoders \n
* 						destroy recorder handle
* @apicovered			streamrecorder_foreach_supported_video_encoder
* @passcase				if streamrecorder_foreach_supported_video_encoder passes
* @failcase				if streamrecorder_foreach_supported_video_encoder fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_foreach_supported_video_encoder_p(void)
{
	START_TEST;

	g_bCheckCb = false;
    int nIotconTimeoutId = 0;

    int nRet = streamrecorder_foreach_supported_video_encoder(g_hCallRecorder, StreamRecorder_supported_video_encoder_cb_p, "video");
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_foreach_supported_video_encoder", StreamRecorderGetError(nRet));

	RUN_POLLING_LOOP;
	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to Retrieves all supported video resolutions by invoking callback function once for each supported video resolution
/**
* @testcase 			ITc_streamrecorder_foreach_supported_video_resolution_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Retrieves all supported video resolutions by invoking callback function once for each supported video resolution
* @scenario				create recorder handle \n
*						Retrieves all supported video resolutions \n
* 						destroy recorder handle
* @apicovered			streamrecorder_foreach_supported_video_resolution
* @passcase				if streamrecorder_foreach_supported_video_resolution passes
* @failcase				if streamrecorder_foreach_supported_video_resolution fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_foreach_supported_video_resolution_p(void)
{
	START_TEST;

	g_bCheckCb = false;
    int nIotconTimeoutId = 0;

    int nRet = streamrecorder_foreach_supported_video_resolution(g_hCallRecorder,StreamRecorder_supported_video_resolution_cb_p, "video");
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_foreach_supported_video_resolution", StreamRecorderGetError(nRet));

	RUN_POLLING_LOOP;
	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to Registers and Unregisters the callback function that will be invoked when the streamrecorder get some notification.
/**
* @testcase 			ITc_streamrecorder_set_unset_notify_cb_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Registers and Unregisters the callback function that will be invoked when the streamrecorder get some notification.
* @scenario				create recorder handle \n
*						Registers and Unregisters the callback function \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_notify_cb,streamrecorder_unset_notify_cb
* @passcase				if streamrecorder_set_notify_cb and streamrecorder_unset_notify_cb passes
* @failcase				if streamrecorder_set_notify_cb or streamrecorder_unset_notify_cb fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_unset_notify_cb_p(void)
{
	START_TEST;

	g_bCheckCb = false;

    if(SetParamCall(g_hCallRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] SetParamCall fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	char pPath[PATH_LEN] = {0};
	if ( false == StreamRecoderAppendToAppDataPath(MEDIA_PATH_AUDIO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

    int nRet = streamrecorder_set_filename(g_hCallRecorder, pPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_filename", StreamRecorderGetError(nRet));

	nRet = streamrecorder_prepare(g_hCallRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_prepare", StreamRecorderGetError(nRet));

	nRet = streamrecorder_set_notify_cb(g_hCallRecorder, StreamRecorder_notify_cb_p, "notify");
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_notify_cb", StreamRecorderGetError(nRet));

	nRet = streamrecorder_start(g_hCallRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_start", StreamRecorderGetError(nRet));

	if(CreatePacketAndFormatDataCall(g_hCallRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] CreatePacketAndFormatDataCall fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = streamrecorder_unset_notify_cb(g_hCallRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unset_notify_cb", StreamRecorderGetError(nRet));

	nRet = streamrecorder_cancel(g_hCallRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_cancel", StreamRecorderGetError(nRet));

	nRet = streamrecorder_unprepare(g_hCallRecorder);
	PRINT_RESULT_NORETURN(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unprepare", StreamRecorderGetError(nRet));

	DestroyPacketAndFormatData();

	return 0;
}

//& type: auto
//& purpose:  scenario to Registers and Unregisters a callback function to be invoked when the recording information changes
/**
* @testcase 			ITc_streamrecorder_set_unset_recording_status_cb_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Registers and Unregisters a callback function to be invoked when the recording information changes
* @scenario				create recorder handle \n
*						Registers and Unregisters the callback function \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_recording_status_cb,streamrecorder_unset_recording_status_cb
* @passcase				if streamrecorder_set_recording_status_cb and streamrecorder_unset_recording_status_cb passes
* @failcase				if streamrecorder_set_recording_status_cb or streamrecorder_unset_recording_status_cb fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_unset_recording_status_cb_p(void)
{
	START_TEST;

    int nIotconTimeoutId = 0;

	int nRet = streamrecorder_set_recording_status_cb(g_hCallRecorder, StreamRecorder_recording_status_cb_p, "record");
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_recording_status_cb", StreamRecorderGetError(nRet));

    if(SetParamCall(g_hCallRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] SetParamCall fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	char pPath[PATH_LEN] = {0};
	if ( false == StreamRecoderAppendToAppDataPath(MEDIA_PATH_AUDIO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

    nRet = streamrecorder_set_filename(g_hCallRecorder, pPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_filename", StreamRecorderGetError(nRet));

	nRet = streamrecorder_prepare(g_hCallRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_prepare", StreamRecorderGetError(nRet));

	nRet = streamrecorder_start(g_hCallRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_start", StreamRecorderGetError(nRet));

	if(CreatePacketAndFormatDataCall(g_hCallRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] CreatePacketAndFormatDataCall fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bCheckCb = false;
	RUN_POLLING_LOOP;
	if ( g_bCheckCb != true )
	{
		FPRINTF("[Line : %d][%s] Failed to call callback\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = streamrecorder_unset_recording_status_cb(g_hCallRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unset_recording_status_cb", StreamRecorderGetError(nRet));

	nRet = streamrecorder_cancel(g_hCallRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_cancel", StreamRecorderGetError(nRet));

	nRet = streamrecorder_unprepare(g_hCallRecorder);
	PRINT_RESULT_NORETURN(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unprepare", StreamRecorderGetError(nRet));

	DestroyPacketAndFormatData();
	return 0;
}

//& type: auto
//& purpose:  scenario to Registers and Unregisters the callback function to be run when reached the recording limit
/**
* @testcase 			ITc_streamrecorder_set_unset_recording_limit_reached_cb_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Registers and Unregisters the callback function to be run when reached the recording limit
* @scenario				create recorder handle \n
*						Registers and Unregisters the callback function \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_recording_limit_reached_cb,streamrecorder_unset_recording_limit_reached_cb
* @passcase				if streamrecorder_set_recording_limit_reached_cb and streamrecorder_unset_recording_limit_reached_cb passes
* @failcase				if streamrecorder_set_recording_limit_reached_cb or streamrecorder_unset_recording_limit_reached_cb fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_unset_recording_limit_reached_cb_p(void)
{
	START_TEST;

	g_bCheckCb = false;

	int nRet = streamrecorder_set_recording_limit(g_hCallRecorder,STREAMRECORDER_RECORDING_LIMIT_TYPE_SIZE,0);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_recording_limit", StreamRecorderGetError(nRet));

    nRet = streamrecorder_set_recording_limit_reached_cb(g_hCallRecorder, StreamRecorder_recording_limit_reached_cb_p, "limit");
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_recording_limit_reached_cb", StreamRecorderGetError(nRet));

	if(SetParamCall(g_hCallRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] SetParamCall fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	char pPath[PATH_LEN] = {0};
	if ( false == StreamRecoderAppendToAppDataPath(MEDIA_PATH_AUDIO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

    nRet = streamrecorder_set_filename(g_hCallRecorder, pPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_filename", StreamRecorderGetError(nRet));

	nRet = streamrecorder_prepare(g_hCallRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_prepare", StreamRecorderGetError(nRet));

	nRet = streamrecorder_start(g_hCallRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_start", StreamRecorderGetError(nRet));

	if(CreatePacketAndFormatDataCall(g_hCallRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] CreatePacketAndFormatDataCall fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = streamrecorder_unset_recording_limit_reached_cb(g_hCallRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unset_recording_limit_reached_cb", StreamRecorderGetError(nRet));

	nRet = streamrecorder_cancel(g_hCallRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_cancel", StreamRecorderGetError(nRet));

	nRet = streamrecorder_unprepare(g_hCallRecorder);
	PRINT_RESULT_NORETURN(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unprepare", StreamRecorderGetError(nRet));

	DestroyPacketAndFormatData();
	return 0;
}

//& type: auto
//& purpose:  scenario to Registers and Unregisters callback function to be called when an asynchronous operation error occurred
/**
* @testcase 			ITc_streamrecorder_set_unset_error_cb_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Registers and Unregisters callback function to be called when an asynchronous operation error occurred
* @scenario				create recorder handle \n
*						Registers and Unregisters the callback function \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_error_cb,streamrecorder_unset_error_cb
* @passcase				if streamrecorder_set_error_cb and streamrecorder_unset_error_cb passes
* @failcase				if streamrecorder_set_error_cb or streamrecorder_unset_error_cb fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_unset_error_cb_p(void)
{
	START_TEST;

    int nRet = streamrecorder_set_error_cb(g_hCallRecorder, Streamrecorder_error_cb_p, "error");
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_error_cb", StreamRecorderGetError(nRet));

	if(SetParamCall(g_hCallRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] SetParam fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	char pPath[PATH_LEN] = {0};
	if ( false == StreamRecoderAppendToAppDataPath(MEDIA_DUMMY_PATH, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = streamrecorder_set_filename(g_hCallRecorder, pPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_filename", StreamRecorderGetError(nRet));

	nRet = streamrecorder_prepare(g_hCallRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_prepare", StreamRecorderGetError(nRet));

	nRet = streamrecorder_start(g_hCallRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_start", StreamRecorderGetError(nRet));

	nRet = streamrecorder_unset_error_cb(g_hCallRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unset_error_cb", StreamRecorderGetError(nRet));

	nRet = streamrecorder_cancel(g_hCallRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_cancel", StreamRecorderGetError(nRet));

	nRet = streamrecorder_unprepare(g_hCallRecorder);
	PRINT_RESULT_NORETURN(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unprepare", StreamRecorderGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to Registers and Unregisters callback function to be called when asynchronous buffers are consumed
/**
* @testcase 			ITc_streamrecorder_set_unset_buffer_consume_completed_cb_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Registers and Unregisters callback function to be called when asynchronous buffers are consumed
* @scenario				create recorder handle \n
*						Registers and Unregisters the callback function \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_buffer_consume_completed_cb,streamrecorder_unset_buffer_consume_completed_cb
* @passcase				if streamrecorder_set_buffer_consume_completed_cb and streamrecorder_unset_buffer_consume_completed_cb passes
* @failcase				if streamrecorder_set_buffer_consume_completed_cb or streamrecorder_unset_buffer_consume_completed_cb fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_unset_buffer_consume_completed_cb_p(void)
{
	START_TEST;

	g_bCheckCb = false;
    int nIotconTimeoutId = 0;

    int nRet = streamrecorder_set_buffer_consume_completed_cb(g_hCallRecorder, Streamrecorder_consume_completed_cb_p, "buffer");
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_buffer_consume_completed_cb", StreamRecorderGetError(nRet));

	if(SetParamCall(g_hCallRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] SetParam fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	char pPath[PATH_LEN] = {0};
	if ( false == StreamRecoderAppendToAppDataPath(MEDIA_PATH_AUDIO, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

    nRet = streamrecorder_set_filename(g_hCallRecorder, pPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_filename", StreamRecorderGetError(nRet));

	nRet = streamrecorder_prepare(g_hCallRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_prepare", StreamRecorderGetError(nRet));

	nRet = streamrecorder_start(g_hCallRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_start", StreamRecorderGetError(nRet));

	if(CreatePacketAndFormatDataCall(g_hCallRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] CreatePacketAndFormatData fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	RUN_POLLING_LOOP;
	if ( g_bCheckCb != true )
	{
		FPRINTF("[Line : %d][%s] Failed to call callback\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = streamrecorder_unset_buffer_consume_completed_cb(g_hCallRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unset_buffer_consume_completed_cb", StreamRecorderGetError(nRet));

	nRet = streamrecorder_cancel(g_hCallRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_cancel", StreamRecorderGetError(nRet));

	nRet = streamrecorder_unprepare(g_hCallRecorder);
	PRINT_RESULT_NORETURN(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unprepare", StreamRecorderGetError(nRet));

	DestroyPacketAndFormatData();
	return 0;
}
/** @} */
/** @} */
