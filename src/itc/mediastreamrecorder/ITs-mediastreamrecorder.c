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

//& set: Mediastreamrecorder

/** @addtogroup itc-mediastreamrecorder
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_mediastreamrecorder_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_mediastreamrecorder_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_mediastreamrecoder_startup\\n", __LINE__, API_NAMESPACE);
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
	int nRet = streamrecorder_create(&g_hRecorder);
	if ( nRet != STREAMRECORDER_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] streamrecorder_create fail in startup \\n", __LINE__, API_NAMESPACE);
		g_bMediaStrRecorderConnect = false;
		return;
	}
	else if(g_hRecorder == NULL)
	{
		FPRINTF("[Line : %d][%s] g_hRecorder is null in startup \\n", __LINE__, API_NAMESPACE);
		g_bMediaStrRecorderConnect = false;
		return;
	}
}


/**
 * @function 		ITs_mediastreamrecorder_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_mediastreamrecorder_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_mediastreamrecoder_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_bMediaStrRecorderConnect)
	{
		streamrecorder_destroy(g_hRecorder);
		g_bMediaStrRecorderConnect = NULL;
	}
}

/** @addtogroup itc-mediastreamrecorder-testcases
*  @brief 		Integration testcases for module mediastreamrecorder
*  @ingroup 	itc-mediastreamrecorder
*  @{
*/

//& type: auto
//& purpose:  scenario to create & destroy stream recorder handle
/**
* @testcase 			ITc_streamrecorder_create_destroy_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to create & destroy stream recorder handle
* @scenario				create recorder handle \n
* 						destroy recorder handle
* @apicovered			streamrecorder_create, streamrecorder_destroy
* @passcase				if streamrecorder_create and streamrecorder_destroy passes
* @failcase				if streamrecorder_create or streamrecorder_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_streamrecorder_create_destroy_p(void)
{
	START_TEST;
	
	streamrecorder_h hRecorder = NULL;
	
	int nRet = streamrecorder_create(&hRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_create", StreamRecorderGetError(nRet));
	CHECK_HANDLE(hRecorder,"streamrecorder_create");
	
	nRet = streamrecorder_destroy(hRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_destroy", StreamRecorderGetError(nRet));
	
    return 0;
}

//& type: auto
//& purpose:  scenario to Prepares and Unprepares the streamrecorder for recording
/**
* @testcase 			ITc_streamrecorder_prepare_unprepare_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Prepares and Unprepares the streamrecorder for recording
* @scenario				create recorder handle \n
*						Set diferent video parameters \n
*						Prepare & Unprepare streamrecorder \n
* 						destroy recorder handle
* @apicovered			streamrecorder_prepare, streamrecorder_unprepare
* @passcase				if streamrecorder_prepare and streamrecorder_unprepare passes
* @failcase				if streamrecorder_prepare or streamrecorder_unprepare fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_prepare_unprepare_p(void)
{
	START_TEST;
			
	if(SetParam(g_hRecorder)!=0)
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
	
    int nRet = streamrecorder_set_filename(g_hRecorder, pPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_filename", StreamRecorderGetError(nRet));
		
    nRet = streamrecorder_prepare(g_hRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_prepare", StreamRecorderGetError(nRet));
	
    nRet = streamrecorder_unprepare(g_hRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unprepare", StreamRecorderGetError(nRet));
	
    return 0;
}

//& type: auto
//& purpose:  scenario to start and cancel the streamrecorder for recording
/**
* @testcase 			ITc_streamrecorder_start_cancel_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to start and cancel the streamrecorder for recording
* @scenario				create recorder handle \n
*						Set diferent video parameters \n
*						start and cancel streamrecorder \n
* 						destroy recorder handle
* @apicovered			streamrecorder_start, streamrecorder_cancel
* @passcase				if streamrecorder_start and streamrecorder_cancel passes
* @failcase				if streamrecorder_start or streamrecorder_cancel fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_start_cancel_p(void)
{
	START_TEST;
	     	
	if(SetParam(g_hRecorder)!=0)
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
	
    int nRet = streamrecorder_set_filename(g_hRecorder, pPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_filename", StreamRecorderGetError(nRet));
	
	nRet = streamrecorder_prepare(g_hRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_prepare", StreamRecorderGetError(nRet));
	
	nRet = streamrecorder_start(g_hRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_start", StreamRecorderGetError(nRet));
	
	nRet = streamrecorder_cancel(g_hRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_cancel", StreamRecorderGetError(nRet));	
		
	nRet = streamrecorder_unprepare(g_hRecorder);
	PRINT_RESULT_NORETURN(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unprepare", StreamRecorderGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to pause the streamrecorder for recording
/**
* @testcase 			ITc_streamrecorder_pause_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to pause the streamrecorder for recording
* @scenario				create recorder handle \n
*						Set diferent video parameters \n
*						pause streamrecorder \n
* 						destroy recorder handle
* @apicovered			streamrecorder_pause
* @passcase				if streamrecorder_pause passes
* @failcase				if streamrecorder_pause fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_pause_p(void)
{
	START_TEST;
	
    if(SetParam(g_hRecorder)!=0)
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
	
	int nRet = streamrecorder_set_video_resolution(g_hRecorder, 352, 288);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_resolution", StreamRecorderGetError(nRet));
	
	nRet = streamrecorder_set_video_framerate(g_hRecorder, 30);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_framerate", StreamRecorderGetError(nRet));
		
    nRet = streamrecorder_set_filename(g_hRecorder, pPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_filename", StreamRecorderGetError(nRet));
	
	nRet = streamrecorder_prepare(g_hRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_prepare", StreamRecorderGetError(nRet));
	 
	nRet = streamrecorder_start(g_hRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_start", StreamRecorderGetError(nRet));

	if(CreatePacketAndFormatData(g_hRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] CreatePacketAndFormatData fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
		
    nRet = streamrecorder_pause(g_hRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_pause", StreamRecorderGetError(nRet));
	
    nRet = streamrecorder_cancel(g_hRecorder);
    PRINT_RESULT_NORETURN(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_cancel", StreamRecorderGetError(nRet));
	
	DestroyPacketAndFormatData();
	
	nRet = streamrecorder_unprepare(g_hRecorder);
	PRINT_RESULT_NORETURN(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unprepare", StreamRecorderGetError(nRet));

    return 0;
}

//& type: auto
//& purpose:  scenario to commit the streamrecorder for recording
/**
* @testcase 			ITc_streamrecorder_commit_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to commit the streamrecorder for recording
* @scenario				create recorder handle \n
*						Set diferent video parameters \n
*						commit streamrecorder \n
* 						destroy recorder handle
* @apicovered			streamrecorder_commit
* @passcase				if streamrecorder_commit passes
* @failcase				if streamrecorder_commit fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_commit_p(void)
{
	START_TEST;
	
	int nWidth = 352;
	int nHeight = 288;
	int nFrameCount = 30;
	
    if(SetParam(g_hRecorder)!=0)
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
	
	int nRet = streamrecorder_set_video_resolution(g_hRecorder, nWidth, nHeight);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_resolution", StreamRecorderGetError(nRet));
	
	nRet = streamrecorder_set_video_framerate(g_hRecorder, nFrameCount);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_framerate", StreamRecorderGetError(nRet));
		
    nRet = streamrecorder_set_filename(g_hRecorder, pPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_filename", StreamRecorderGetError(nRet));
	
	nRet = streamrecorder_prepare(g_hRecorder);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_prepare", StreamRecorderGetError(nRet));
	 
	nRet = streamrecorder_start(g_hRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_start", StreamRecorderGetError(nRet));

	if(CreatePacketAndFormatData(g_hRecorder)!=0)
	{
		FPRINTF("[Line : %d][%s] CreatePacketAndFormatData fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
    nRet = streamrecorder_commit(g_hRecorder);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_commit", StreamRecorderGetError(nRet));
	
    nRet = streamrecorder_cancel(g_hRecorder);
    PRINT_RESULT_NORETURN(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_cancel", StreamRecorderGetError(nRet));
	
	DestroyPacketAndFormatData();
	
	nRet = streamrecorder_unprepare(g_hRecorder);
	PRINT_RESULT_NORETURN(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_unprepare", StreamRecorderGetError(nRet));

    return 0;
}

//& type: auto
//& purpose:  scenario to Sets the video source as live buffer to be used for recording
/**
* @testcase 			ITc_streamrecorder_enable_source_buffer_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets the video source as live buffer to be used for recording
* @scenario				create recorder handle \n
*						Sets the video source as live buffer \n
* 						destroy recorder handle
* @apicovered			streamrecorder_enable_source_buffer
* @passcase				if streamrecorder_enable_source_buffer passes
* @failcase				if streamrecorder_enable_source_buffer fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_enable_source_buffer_p(void)
{
	START_TEST;
	
	int nRet = -1 ,nEnumLoopCount = 0;
	
	streamrecorder_source_e eSetSource[] = {
		STREAMRECORDER_SOURCE_VIDEO,           /**< Video only */
		STREAMRECORDER_SOURCE_AUDIO,           /**< Audio only */
		STREAMRECORDER_SOURCE_VIDEO_AUDIO,    /**< Video and Audio */
	};
	int nSourceCount = sizeof(eSetSource) / sizeof(eSetSource[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nSourceCount; nEnumLoopCount++ )
	{

		nRet = streamrecorder_enable_source_buffer(g_hRecorder, eSetSource[nEnumLoopCount]);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));
	}	
	return 0;
}

//& type: auto
//& purpose:  scenario to Gets the streamrecorder's current state.
/**
* @testcase 			ITc_streamrecorder_get_state_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Gets the streamrecorder's current state.
* @scenario				create recorder handle \n
*						Gets the video source as live buffer \n
* 						destroy recorder handle
* @apicovered			streamrecorder_get_state
* @passcase				if streamrecorder_get_state passes
* @failcase				if streamrecorder_get_state fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_get_state_p(void)
{
	START_TEST;
		
	int nRet = -1 ,nEnumLoopCount = 0;
	streamrecorder_state_e eGetState = STREAMRECORDER_STATE_NONE;
	
	streamrecorder_source_e eSetSource[] = {
		STREAMRECORDER_SOURCE_VIDEO,           /**< Video only */
		STREAMRECORDER_SOURCE_AUDIO,           /**< Audio only */
		STREAMRECORDER_SOURCE_VIDEO_AUDIO,    /**< Video and Audio */
	};
	int nSourceCount = sizeof(eSetSource) / sizeof(eSetSource[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nSourceCount; nEnumLoopCount++ )
	{

		nRet = streamrecorder_enable_source_buffer(g_hRecorder, eSetSource[nEnumLoopCount]);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));
		
		nRet = streamrecorder_get_state(g_hRecorder, &eGetState);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));
	}		
    return 0;
}

//& type: auto
//& purpose:  scenario to Sets and Gets the file path to record.
/**
* @testcase 			ITc_streamrecorder_set_get_filename_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets and Gets the file path to record.
* @scenario				create recorder handle \n
*						set and get filename \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_filename, streamrecorder_get_filename
* @passcase				if streamrecorder_set_filename and streamrecorder_get_filename passes
* @failcase				if streamrecorder_set_filename or streamrecorder_get_filename fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_filename_p(void)
{
	START_TEST;
	
    char* pszGetPath = NULL;
	
    char pszSetPath[PATH_LEN] = {0};
	if ( false == StreamRecoderAppendToAppDataPath(MEDIA_PATH_AUDIO, pszSetPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
    int nRet = streamrecorder_set_filename(g_hRecorder, pszSetPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_filename", StreamRecorderGetError(nRet));

    nRet = streamrecorder_get_filename(g_hRecorder,&pszGetPath);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_filename", StreamRecorderGetError(nRet));
	if ( strcmp(pszGetPath, pszSetPath) != 0 )
    {
        FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
        FREE_MEMORY(pszGetPath);
        return 1;
    }
	FREE_MEMORY(pszGetPath);
	
    return 0;
}

//& type: auto
//& purpose:  scenario to Sets and Gets the file format to record
/**
* @testcase 			ITc_streamrecorder_set_get_file_format_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets and Gets the file format to record
* @scenario				create recorder handle \n
*						set and get file format \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_file_format, streamrecorder_get_file_format
* @passcase				if streamrecorder_set_file_format and streamrecorder_get_file_format passes
* @failcase				if streamrecorder_set_file_format or streamrecorder_get_file_format fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_file_format_p(void)
{
	START_TEST;
	int nEnumLoopCount = 0, nMisMatchCount = 0;
	int nRet = streamrecorder_enable_source_buffer(g_hRecorder, STREAMRECORDER_SOURCE_VIDEO);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));
	streamrecorder_file_format_e ret_format;
	streamrecorder_file_format_e format[] = {
				STREAMRECORDER_FILE_FORMAT_3GP,      /**< AMR codec */
				STREAMRECORDER_FILE_FORMAT_MP4,          /**< AAC codec */
				STREAMRECORDER_FILE_FORMAT_AMR,           /**< PCM codec */
				STREAMRECORDER_FILE_FORMAT_WAV
	};
	int nEncodeCount = sizeof(format) / sizeof(format[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nEncodeCount; nEnumLoopCount++ )
	{
		nRet = streamrecorder_set_file_format(g_hRecorder, format[nEnumLoopCount]);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_file_format", StreamRecorderGetError(nRet));
	
		nRet = streamrecorder_get_file_format(g_hRecorder,&ret_format);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_file_format", StreamRecorderGetError(nRet));
		if ( ret_format != format[nEnumLoopCount])
		{
			FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
			nMisMatchCount ++;
		}
	}
	if(nMisMatchCount > 0)
	{
		return 1;
	}
    return 0;
}


//& type: auto
//& purpose:  scenario to  Sets and Gets the audio codec for encoding an audio stream.
/**
* @testcase 			ITc_streamrecorder_set_get_audio_encoder_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to  Sets and Gets the audio codec for encoding an audio stream.
* @scenario				create recorder handle \n
*						Sets and Gets the audio codec \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_audio_encoder, streamrecorder_get_audio_encoder
* @passcase				if streamrecorder_set_audio_encoder and streamrecorder_get_audio_encoder passes
* @failcase				if streamrecorder_set_audio_encoder or streamrecorder_get_audio_encoder fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_audio_encoder_p(void)
{
	START_TEST;
	
	int nRet = -1 ,nEnumLoopCount = 0, nMisMatchCount = 0;
	streamrecorder_audio_codec_e eGetCodec;
	streamrecorder_audio_codec_e eSetCodec[] = {
				STREAMRECORDER_AUDIO_CODEC_AMR,      /**< AMR codec */
				STREAMRECORDER_AUDIO_CODEC_AAC,          /**< AAC codec */
				STREAMRECORDER_AUDIO_CODEC_PCM           /**< PCM codec */
	};
	int nEncodeCount = sizeof(eSetCodec) / sizeof(eSetCodec[0]);

	nRet = streamrecorder_enable_source_buffer(g_hRecorder,STREAMRECORDER_SOURCE_AUDIO);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));

	for ( nEnumLoopCount = 0; nEnumLoopCount < nEncodeCount; nEnumLoopCount++ )
	{

		nRet = streamrecorder_set_audio_encoder(g_hRecorder, eSetCodec[nEnumLoopCount]);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_audio_encoder", StreamRecorderGetError(nRet));

		nRet = streamrecorder_get_audio_encoder(g_hRecorder, &eGetCodec);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_audio_encoder", StreamRecorderGetError(nRet));
		if ( eGetCodec != eSetCodec[nEnumLoopCount])
		{
			FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
			nMisMatchCount ++;
		}
	}	
	if(nMisMatchCount > 0)
	{
		return 1;
	}
 
    return 0;
}

//& type: auto
//& purpose:  scenario to Sets and Gets the resolution of the video recording.
/**
* @testcase 			ITc_streamrecorder_set_get_video_resolution_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets and Gets the resolution of the video recording.
* @scenario				create recorder handle \n
*						Sets and Gets the resolution \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_video_resolution, streamrecorder_get_video_resolution
* @passcase				if streamrecorder_set_video_resolution and streamrecorder_get_video_resolution passes
* @failcase				if streamrecorder_set_video_resolution or streamrecorder_get_video_resolution fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_video_resolution_p(void)
{
	START_TEST;
    int nSetWidth  = 1280;
    int nSetHeight = 720;
	int nGetHeight = 0;
    int nGetWidth  = 0;

    int nRet = streamrecorder_set_video_resolution(g_hRecorder, nSetWidth, nSetHeight);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_resolution", StreamRecorderGetError(nRet));

    nRet = streamrecorder_get_video_resolution(g_hRecorder, &nGetWidth, &nGetHeight);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_video_resolution", StreamRecorderGetError(nRet));
	
	if ( (nSetHeight != nGetHeight) || ( nSetWidth != nGetWidth))
    {
        FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
        return 1;
    }
    return 0;
}


//& type: auto
//& purpose:  scenario to Sets and Gets the video codec for encoding video stream.
/**
* @testcase 			ITc_streamrecorder_set_get_video_encoder_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets and Gets the video codec for encoding video stream.
* @scenario				create recorder handle \n
*						Sets and Gets the video codec \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_video_encoder, streamrecorder_get_video_encoder
* @passcase				if streamrecorder_set_video_encoder and streamrecorder_get_video_encoder passes
* @failcase				if streamrecorder_set_video_encoder or streamrecorder_get_video_encoder fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_video_encoder_p(void)
{
	START_TEST;
	
	int nRet = -1 ,nEnumLoopCount = 0, nMisMatchCount = 0;
	streamrecorder_video_codec_e eGetCodec;
	streamrecorder_video_codec_e eSetCodec[] = {
			STREAMRECORDER_VIDEO_CODEC_H263,    /**< H263 codec */
			STREAMRECORDER_VIDEO_CODEC_MPEG4,   /**< MPEG4 codec */
	};
	int nEncodeCount = sizeof(eSetCodec) / sizeof(eSetCodec[0]);

	nRet = streamrecorder_enable_source_buffer(g_hRecorder,STREAMRECORDER_SOURCE_VIDEO);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));

	for ( nEnumLoopCount = 0; nEnumLoopCount < nEncodeCount; nEnumLoopCount++ )
	{

		nRet = streamrecorder_set_video_encoder(g_hRecorder, eSetCodec[nEnumLoopCount]);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_encoder", StreamRecorderGetError(nRet));
	
		nRet = streamrecorder_get_video_encoder(g_hRecorder, &eGetCodec);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_video_encoder", StreamRecorderGetError(nRet));
		if ( eGetCodec != eSetCodec[nEnumLoopCount])
		{
			FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
			nMisMatchCount ++;
		}
	}	
	if(nMisMatchCount > 0)
	{
		return 1;
	}
    return 0;
}

//& type: auto
//& purpose:  scenario to Sets and Gets the video source format
/**
* @testcase 			ITc_streamrecorder_set_get_video_source_format_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets and Gets the video source format
* @scenario				create recorder handle \n
*						Sets and Gets the video source format \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_video_source_format, streamrecorder_get_video_source_format
* @passcase				if streamrecorder_set_video_source_format and streamrecorder_get_video_source_format passes
* @failcase				if streamrecorder_set_video_source_format or streamrecorder_get_video_source_format fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_video_source_format_p(void)
{
	START_TEST;
		
	int nRet = -1 ,nEnumLoopCount = 0, nMisMatchCount = 0;
	streamrecorder_video_source_format_e eGetFormat;
	streamrecorder_video_source_format_e eSetFormat[] = {
				STREAMRECORDER_VIDEO_SOURCE_FORMAT_INVALID,   /**< Invalid pixel format */
				STREAMRECORDER_VIDEO_SOURCE_FORMAT_NV12,           /**< NV12 pixel format */
				STREAMRECORDER_VIDEO_SOURCE_FORMAT_NV21,           /**< NV12 pixel format */
				STREAMRECORDER_VIDEO_SOURCE_FORMAT_I420,           /**< I420 pixel format */
	};
	int nEncodeCount = sizeof(eSetFormat) / sizeof(eSetFormat[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nEncodeCount; nEnumLoopCount++ )
	{

		nRet = streamrecorder_enable_source_buffer(g_hRecorder, STREAMRECORDER_SOURCE_VIDEO);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));
	
		nRet = streamrecorder_set_video_source_format(g_hRecorder, eSetFormat[nEnumLoopCount]);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_source_format", StreamRecorderGetError(nRet));

		nRet = streamrecorder_get_video_source_format(g_hRecorder, &eGetFormat);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_video_source_format", StreamRecorderGetError(nRet));
		if ( eSetFormat[nEnumLoopCount] != eGetFormat)
		{
			FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
			nMisMatchCount ++;
    
		}	
	}
	if(nMisMatchCount > 0)
	{
		return 1;
	}
    return 0;
}

//& type: auto
//& purpose:  scenario to Sets  and Gets the recording frame rate.
/**
* @testcase 			ITc_streamrecorder_set_get_video_framerate_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets  and Gets the recording frame rate.
* @scenario				create recorder handle \n
*						Sets  and Gets the recording frame rate \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_video_framerate, streamrecorder_get_video_framerate
* @passcase				if streamrecorder_set_video_framerate and streamrecorder_get_video_framerate passes
* @failcase				if streamrecorder_set_video_framerate or streamrecorder_get_video_framerate fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_video_framerate_p(void)
{
	START_TEST;
	
	int nSetVal = 30;
	int nGetVal = 0;
	
	int nRet = streamrecorder_enable_source_buffer(g_hRecorder, STREAMRECORDER_SOURCE_VIDEO);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));
	
	nRet = streamrecorder_set_video_framerate(g_hRecorder, nSetVal);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_framerate", StreamRecorderGetError(nRet));

    nRet = streamrecorder_get_video_framerate(g_hRecorder, &nGetVal);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_video_framerate", StreamRecorderGetError(nRet));
	if ( nSetVal != nGetVal)
	{
		FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

    return 0;
}

//& type: auto
//& purpose:  scenario to Sets and Gets the maximum size of a recording file.
/**
* @testcase 			ITc_streamrecorder_set_get_recording_limit_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets and Gets the maximum size of a recording file.
* @scenario				create recorder handle \n
*						Sets and Gets the maximum size of a recording files \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_recording_limit, streamrecorder_get_recording_limit
* @passcase				if streamrecorder_set_recording_limit and streamrecorder_get_recording_limit passes
* @failcase				if streamrecorder_set_recording_limit or streamrecorder_get_recording_limit fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_recording_limit_p(void)
{
	START_TEST;

	int nSetLimit = 1000;
	int nGetLimit = 0;
	
	int nRet = -1 ,nEnumLoopCount = 0, nMisMatchCount = 0;
	streamrecorder_recording_limit_type_e eSetLimit[] = {
				STREAMRECORDER_RECORDING_LIMIT_TYPE_TIME,        /**< Time limit (second) of recording file */
				STREAMRECORDER_RECORDING_LIMIT_TYPE_SIZE,        /**< Size limit (kilo bytes [KB]) of recording file */
	};
	int nLimitCount = sizeof(eSetLimit) / sizeof(eSetLimit[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nLimitCount; nEnumLoopCount++ )
	{

		nRet = streamrecorder_set_recording_limit(g_hRecorder, eSetLimit[nEnumLoopCount], nSetLimit);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_recording_limit", StreamRecorderGetError(nRet));

		nRet = streamrecorder_get_recording_limit(g_hRecorder, eSetLimit[nEnumLoopCount], &nGetLimit);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_recording_limit", StreamRecorderGetError(nRet));
		if ( nSetLimit != nGetLimit)
		{
			FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
			nMisMatchCount ++;
		}
	}
	if(nMisMatchCount > 0)
	{
		return 1;
	} 
    return 0;
}

//& type: auto
//& purpose:  scenario to Sets and Gets the sampling rate of an audio stream.
/**
* @testcase 			ITc_streamrecorder_set_get_audio_samplerate_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets and Gets the sampling rate of an audio stream.
* @scenario				create recorder handle \n
*						Sets and Gets the sampling rate of an audio stream \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_audio_samplerate, streamrecorder_get_audio_samplerate
* @passcase				if streamrecorder_set_audio_samplerate and streamrecorder_get_audio_samplerate passes
* @failcase				if streamrecorder_set_audio_samplerate or streamrecorder_get_audio_samplerate fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_audio_samplerate_p(void)
{
	START_TEST;
	
	int nSetSampleRate = 11111;
	int nGetSampleRate = 0;

    int nRet = streamrecorder_set_audio_samplerate(g_hRecorder, nSetSampleRate);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_audio_samplerate", StreamRecorderGetError(nRet));

    nRet = streamrecorder_enable_source_buffer(g_hRecorder, STREAMRECORDER_SOURCE_AUDIO);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));
	
    nRet = streamrecorder_get_audio_samplerate(g_hRecorder, &nGetSampleRate);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_audio_samplerate", StreamRecorderGetError(nRet));
	if ( nSetSampleRate != nGetSampleRate)
    {
        FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
        return 1;
    }
    return 0;
}

//& type: auto
//& purpose:  scenario to Sets and Gets the bitrate of an audio encoder
/**
* @testcase 			ITc_streamrecorder_set_get_audio_encoder_bitrate_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets and Gets the bitrate of an audio encoder
* @scenario				create recorder handle \n
*						Sets and Gets the bitrate \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_audio_encoder_bitrate, streamrecorder_get_audio_encoder_bitrate
* @passcase				if streamrecorder_set_audio_encoder_bitrate and streamrecorder_get_audio_encoder_bitrate passes
* @failcase				if streamrecorder_set_audio_encoder_bitrate or streamrecorder_get_audio_encoder_bitrate fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_audio_encoder_bitrate_p(void)
{
	START_TEST;
	
	int nSetBitRate = 11111;
	int nGetBitRate = 0;

    int nRet = streamrecorder_enable_source_buffer(g_hRecorder, STREAMRECORDER_SOURCE_AUDIO);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));
	
    nRet = streamrecorder_set_audio_encoder_bitrate(g_hRecorder, nSetBitRate);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_audio_encoder_bitrate", StreamRecorderGetError(nRet));

    nRet = streamrecorder_get_audio_encoder_bitrate(g_hRecorder, &nGetBitRate);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_audio_encoder_bitrate", StreamRecorderGetError(nRet));
	if ( nSetBitRate != nGetBitRate)
    {
        FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    return 0;
}

//& type: auto
//& purpose:  scenario to Sets and Gets the bitrate of a video encoder.
/**
* @testcase 			ITc_streamrecorder_set_get_video_encoder_bitrate_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets and Gets the bitrate of a video encoder
* @scenario				create recorder handle \n
*						Sets and Gets the bitrate \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_video_encoder_bitrate, streamrecorder_get_video_encoder_bitrate
* @passcase				if streamrecorder_set_video_encoder_bitrate and streamrecorder_get_video_encoder_bitrate passes
* @failcase				if streamrecorder_set_video_encoder_bitrate or streamrecorder_get_video_encoder_bitrate fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_video_encoder_bitrate_p(void)
{
	START_TEST;
	
	int nSetEncBitRate = 0;
	int nGetEncBitRate = 0;

    int nRet = streamrecorder_set_video_encoder_bitrate(g_hRecorder, nSetEncBitRate);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_video_encoder_bitrate", StreamRecorderGetError(nRet));

    nRet = streamrecorder_get_video_encoder_bitrate(g_hRecorder, &nGetEncBitRate);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_video_encoder_bitrate", StreamRecorderGetError(nRet));
	if ( nSetEncBitRate != nGetEncBitRate)
    {
        FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
        return 1;
    }

    return 0;
}

//& type: auto
//& purpose:  scenario to Sets and Gets the number of the audio channel
/**
* @testcase 			ITc_streamrecorder_set_get_audio_channel_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Sets and Gets the number of the audio channel
* @scenario				create recorder handle \n
*						Sets and Gets the number of the audio channel \n
* 						destroy recorder handle
* @apicovered			streamrecorder_set_audio_channel, streamrecorder_get_audio_channel
* @passcase				if streamrecorder_set_audio_channel and streamrecorder_get_audio_channel passes
* @failcase				if streamrecorder_set_audio_channel or streamrecorder_get_audio_channel fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_audio_channel_p(void)
{
	START_TEST;
	
	int nSetChannelVal = 1;
	int nGetChannelVal = 0;

    int nRet = streamrecorder_enable_source_buffer(g_hRecorder, STREAMRECORDER_SOURCE_AUDIO);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));

    nRet = streamrecorder_set_audio_channel(g_hRecorder, nSetChannelVal);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_audio_channel", StreamRecorderGetError(nRet));
	
    nRet = streamrecorder_get_audio_channel(g_hRecorder, &nGetChannelVal);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_audio_channel", StreamRecorderGetError(nRet));
	if ( nSetChannelVal != nGetChannelVal)
    {
        FPRINTF("[Line : %d][%s] value mismatch \\n", __LINE__, API_NAMESPACE);
        return 1;
    }
    return 0;
}

//& type: auto
//& purpose:  scenario to Pushes buffer to StreamRecorder to record audio/video
/**
* @testcase 			ITc_streamrecorder_push_stream_buffer_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to Pushes buffer to StreamRecorder to record audio/video
* @scenario				create recorder handle \n
*						Pushes buffer to StreamRecorder to record audio/video \n
* 						destroy recorder handle
* @apicovered			streamrecorder_push_stream_buffer
* @passcase				if streamrecorder_push_stream_buffer passes
* @failcase				if streamrecorder_push_stream_buffer fails
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_push_stream_buffer_p(void)
{
	START_TEST;
	
    media_packet_h hPcktHandle = NULL;
    media_format_h hFormatHandle = NULL;
	int nWidth = 352;
	int nHeight = 288;
	
	int nRet = media_format_create(&hFormatHandle);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_create", MediaFormatGetError(nRet));
	CHECK_HANDLE(hFormatHandle,"media_format_create");
		
	nRet = media_format_set_video_mime(hFormatHandle, MEDIA_FORMAT_I420);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_mime", MediaFormatGetError(nRet));
		
    nRet = media_format_set_video_width(hFormatHandle, nWidth);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_width", MediaFormatGetError(nRet));
		
    nRet = media_format_set_video_height(hFormatHandle, nHeight);
	PRINT_RESULT(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_set_video_height", MediaFormatGetError(nRet));
		
	nRet = media_packet_create(hFormatHandle, NULL, NULL, &hPcktHandle);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_create", MediaPacketGetError(nRet));
	CHECK_HANDLE(hPcktHandle,"media_packet_create");
        
    nRet = media_packet_alloc(hPcktHandle);
	PRINT_RESULT(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_alloc", MediaPacketGetError(nRet));
	
	nRet = streamrecorder_enable_source_buffer(g_hRecorder, STREAMRECORDER_SOURCE_VIDEO);
    PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_enable_source_buffer", StreamRecorderGetError(nRet));
	
	nRet = streamrecorder_push_stream_buffer(g_hRecorder, hPcktHandle);
	PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_push_stream_buffer", StreamRecorderGetError(nRet));
	
	nRet = media_format_unref(hFormatHandle);
    PRINT_RESULT_NORETURN(MEDIA_FORMAT_ERROR_NONE, nRet, "media_format_unref", MediaFormatGetError(nRet));
	hFormatHandle = NULL;

    nRet = media_packet_destroy(hPcktHandle);
    PRINT_RESULT_NORETURN(MEDIA_PACKET_ERROR_NONE, nRet, "media_packet_destroy", MediaPacketGetError(nRet));
	hPcktHandle = NULL;
	        	
	return 0;
}

//& type: auto
//& purpose:  To set and get the recording mode.
/**
* @testcase 			ITc_streamrecorder_set_get_mode_p
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @since_tizen 			6.0
* @description			Sets and gets the recording mode.
* @scenario				Sets the recording mode \n
* 						Gets the recording mode
* @apicovered			streamrecorder_set_mode, streamrecorder_get_mode
* @passcase				if set and get values are same.
* @failcase				if set and get values are not same.
* @precondition			stream recorder should be created
* @postcondition		stream recorder should be destroy
*/
int ITc_streamrecorder_set_get_mode_p(void)
{
	START_TEST;

	int nRet = -1;

	streamrecorder_mode_e eStreamRecorderType[] = {
		STREAMRECORDER_MODE_STREAM_BUFFER,
		STREAMRECORDER_MODE_DEVICE_LOOPBACK
	};

	int nSize = sizeof(eStreamRecorderType) / sizeof(eStreamRecorderType[0]);

	for ( int nCount = 0; nCount < nSize; nCount++)
	{
		streamrecorder_mode_e eMode = -1;

		nRet = streamrecorder_set_mode(g_hRecorder, eStreamRecorderType[nCount]);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_set_mode", StreamRecorderGetError(nRet));

		nRet = streamrecorder_get_mode(g_hRecorder, &eMode);
		PRINT_RESULT(STREAMRECORDER_ERROR_NONE, nRet, "streamrecorder_get_mode", StreamRecorderGetError(nRet));

		if(eMode != eStreamRecorderType[nCount])
		{
			FPRINTF("[Line : %d][%s] value mismatch set mode = %d, get mode = %d\\n", __LINE__, API_NAMESPACE, eStreamRecorderType[nCount], eMode);
			return 1;
		}
	}
	return 0;
}

/** @} */
/** @} */
