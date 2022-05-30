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
#include "ITs-capi-mediamuxer-common.h"

gboolean Timeout_Function(gpointer data);
char *g_uri=NULL;
static char* g_file_path = NULL;
static char* g_file = "sample.mp4";

static char* g_h264_path = NULL;
static char* g_h264_file = "output3.h264";
static GMainLoop *g_pMediaMuxerMainLoop = NULL;
bool g_bCallbackHit = false;
bool g_bCallbackResult = false;



/**
 * @function 		Timeout_Function
 * @description	 	callback function to terminate g_main loop
 * @parameter		data : user data sent to callback
 * @return 			NA
 */
gboolean Timeout_Function(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

/** @addtogroup itc-mediamuxer
 *  @ingroup itc
 *  @{
 */


/**
 * @function 		mediamuxer_error_callback
 * @description	 	Called when error occurs in media muxer.
 * @parameter		mediamuxer error: error, user_data: User data sent to callback
 * @return 			NA
 */
void mediamuxer_error_callback(mediamuxer_error_e error, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"mediamuxer_error_callback\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMediaMuxerMainLoop )
	{
		g_main_loop_quit(g_pMediaMuxerMainLoop);
	}
	FPRINTF("[Line : %d][%s] Outside from callback \"mediamuxer_error_callback\"\\n", __LINE__, API_NAMESPACE);
}

/**
 * @function 		mediamuxer_eos_callback
 * @description	 	Called when end of stream occurs in media muxer.
 * @parameter		user_data: User data sent to callback
 * @return 		NA
 */
void mediamuxer_eos_callback(void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"mediamuxer_eos_callback\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;

	if ( g_pMediaMuxerMainLoop )
	{
		g_main_loop_quit(g_pMediaMuxerMainLoop);
	}
}

//& set: Mediamuxer
/**
 * @function 		ITs_mediamuxer_startup
 * @description	 	Called before each test, set the service boolean true
 * @parameter		NA
 * @return 			NA
 */
void ITs_mediamuxer_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Mediamuxer_p\\n", __LINE__, API_NAMESPACE);
#endif

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		FPRINTF("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		if(g_h264_path == NULL){
			g_h264_path=(char*)malloc(strlen(pszValue)+ strlen( g_h264_file ) + 6);
			snprintf(g_h264_path, strlen("/res/") + strlen(pszValue) + strlen(g_h264_file) + 1, "%s/res/%s", pszValue, g_h264_file );
		}
		if(g_file_path == NULL){
			g_file_path=(char*)malloc(strlen(pszValue)+ strlen( g_file ) + 6);
			snprintf(g_file_path, strlen("/res/") + strlen(pszValue) + strlen(g_file) + 1, "%s/res/%s", pszValue, g_file );
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	if(g_uri == NULL)
		g_uri = g_file_path;
	g_bMediamuxerCreation = true;
	g_bCallbackHit = false;
	g_bCallbackResult = false;
}

/**
 * @function 		ITs_mediamuxer_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_mediamuxer_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Mediamuxer_p\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_h264_path)
	{
		free(g_h264_path);
		g_h264_path = NULL;
	}
}

/** @addtogroup itc-mediamuxer-testcases
 *  @brief 		Integration testcases for module mediamuxer
 *  @ingroup 	itc-mediamuxer
 *  @{
 */

/**
 * @testcase 			ITc_mediamuxer_create_destroy_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Create and destroy a media muxer handle for muxing.
 * @scenario				Create and destroy a media muxer handle for muxing.
 * @apicovered			mediamuxer_create, mediamuxer_destroy
 * @passcase				When API returns MEDIAMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: API to test mediamuxer_create & mediamuxer_destroy
//& type: auto
int ITc_mediamuxer_create_destroy_p(void)
{
	START_TEST;

	mediamuxer_h muxer;

	int nRetVal = mediamuxer_create(&muxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_create", MediamuxerGetError(nRetVal));
	CHECK_HANDLE(muxer, "mediamuxer_create");

	nRetVal = mediamuxer_destroy(muxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_destroy", MediamuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediamuxer_set_data_sink_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Set the sink path of output stream.
 * @scenario				Create media muxer handle for muxing.\n
 set the sink path of output stream.
 * @apicovered			mediamuxer_create, mediamuxer_destroy, mediamuxer_set_data_sink
 * @passcase				When API returns MEDIAMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Set the sink path of output stream.
//& type: auto
int ITc_mediamuxer_set_data_sink_p(void)
{
	START_TEST;

	mediamuxer_h muxer;
	mediamuxer_output_format_e sink_format = MEDIAMUXER_CONTAINER_FORMAT_MP4;

	int nRetVal = mediamuxer_create(&muxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_create", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_set_data_sink(muxer, g_uri, sink_format);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_set_data_sink", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_destroy(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_destroy", MediamuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediamuxer_prepare_unprepare_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Prepare and unprepare the media muxer for muxing.
 * @scenario				Create media muxer handle for muxing.\n
 prepare and unprepare the media muxer for muxing.
 * @apicovered			mediamuxer_create, mediamuxer_destroy, mediamuxer_set_data_source, mediamuxer_prepare, mediamuxer_unprepare
 * @passcase				When API returns MEDIADEMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Prepare the media muxer for muxing.
//& type: auto
int ITc_mediamuxer_prepare_unprepare_p(void)
{
	START_TEST;

	mediamuxer_h muxer = NULL;
	mediamuxer_output_format_e sink_format = MEDIAMUXER_CONTAINER_FORMAT_MP4;

	int nRetVal = mediamuxer_create(&muxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_create", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_set_data_sink(muxer, g_uri, sink_format);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_set_data_sink", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_prepare(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_prepare", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_unprepare(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_unprepare", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_destroy(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_destroy", MediamuxerGetError(nRetVal));

	return 0;
}


/**
 * @testcase 			ITc_mediamuxer_add_close_track_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Add and close the media track of interest to the muxer handle.
 * @scenario				Create media muxer handle for muxing.\n
 add and close the media track of interest to the muxer handle..
 * @apicovered			mediamuxer_create, mediamuxer_destroy, mediamuxer_set_data_sink, mediamuxer_add_track, mediamuxer_close_track
 * @passcase				When API returns MEDIAMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Add and close the media track of interest to the muxer handle.
//& type: auto
int ITc_mediamuxer_add_close_track_p(void)
{
	START_TEST;

	mediamuxer_h muxer;
	media_format_h media_format = NULL;
	int track_index = 1;
	mediamuxer_output_format_e sink_format = MEDIAMUXER_CONTAINER_FORMAT_MP4;

	int nRetVal = mediamuxer_create(&muxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_create", MediamuxerGetError(nRetVal));

	nRetVal = media_format_create(&media_format);;
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_create", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = media_format_set_video_mime(media_format, MEDIA_FORMAT_H264_SP);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_mime", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_set_data_sink(muxer, g_uri, sink_format);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_set_data_sink", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_add_track(muxer, media_format, &track_index);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_add_track", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_close_track(muxer, track_index);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_close_track", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_destroy(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_destroy", MediamuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediamuxer_start_stop_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Start and stop the media muxer.
 * @scenario				Create media muxer handle for muxing.\n
 start and stop the media muxer.
 * @apicovered			mediamuxer_create, mediamuxer_destroy, mediamuxer_set_data_sink, mediamuxer_start, mediamuxer_stop.
 * @passcase				When API returns MEDIAMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Start and stop the media muxer.
//& type: auto
int ITc_mediamuxer_start_stop_p(void)
{
	START_TEST;

	mediamuxer_h muxer;
	mediamuxer_output_format_e format = MEDIAMUXER_CONTAINER_FORMAT_MP4;

	int nRetVal = mediamuxer_create(&muxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_create", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_set_data_sink(muxer, g_uri, format);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_set_data_sink", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_prepare(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_prepare", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_start(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_start", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_stop(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_stop", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_unprepare(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_unprepare", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_destroy(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_destroy", MediamuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediamuxer_write_sample_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Write the media packet of interest to the muxer handle.
 * @scenario				Create media muxer handle for muxing.\n
 write the media packet of interest to the muxer handle.
 * @apicovered			mediamuxer_create, mediamuxer_destroy, mediamuxer_set_data_sink, mediamuxer_start, mediamuxer_stop, mediamuxer_write_sample.
 * @passcase				When API returns MEDIAMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Write the media packet of interest to the muxer handle.
//& type: auto
int ITc_mediamuxer_write_sample_p(void)
{
	START_TEST;
	mediamuxer_h muxer = NULL;
	media_format_h media_format = NULL;
	media_format_h media_format2 = NULL;
	FILE *pvFile;
	unsigned int vsize = 5637;
	unsigned int pts_vid = 0;
	unsigned int dts_vid = 0;
	unsigned int duration_vid = 33000000;
	int track_index_vid = 1;
	media_packet_h vid_pkt;
	unsigned char *dptr;

	mediamuxer_output_format_e  format = MEDIAMUXER_CONTAINER_FORMAT_MP4;

	int nRetVal = mediamuxer_create(&muxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_create", MediamuxerGetError(nRetVal));

	nRetVal = media_format_create(&media_format);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_create", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = media_format_set_video_mime(media_format, MEDIA_FORMAT_H264_SP);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_mime", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_set_data_sink(muxer, g_uri, format);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_set_data_sink", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_add_track(muxer, media_format, &track_index_vid);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_add_track", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_prepare(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_prepare", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_start(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_start", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	pvFile = fopen(g_h264_path, "rb");

	nRetVal = media_format_make_writable(media_format, &media_format2);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_make_writable", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));
	media_format = NULL;

	nRetVal = media_format_set_video_width(media_format2, 640);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_width", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_format_set_video_height(media_format2, 480);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_height", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_format_set_video_frame_rate(media_format2, 30);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_frame_rate", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_create(media_format2, NULL, NULL, &vid_pkt);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_create", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_alloc(vid_pkt);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_alloc", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	media_packet_get_buffer_data_ptr(vid_pkt, (void**)&dptr);
	vsize = fread(dptr, 1, vsize, pvFile);

	nRetVal = media_packet_set_buffer_size(vid_pkt, vsize);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_buffer_size", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_set_pts(vid_pkt, pts_vid);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_pts", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_set_dts(vid_pkt, dts_vid);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_dts", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_set_duration(vid_pkt, duration_vid);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_duration", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = mediamuxer_write_sample(muxer, track_index_vid, vid_pkt);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_write_sample", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_destroy(vid_pkt);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_destroy", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_stop(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_stop", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_unprepare(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_unprepare", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_destroy(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_destroy", MediamuxerGetError(nRetVal));

	fclose(pvFile);
	if (media_format)
		media_format_unref(media_format);
	if (media_format2)
		media_format_unref(media_format2);

	return 0;
}

/**
 * @testcase 			ITc_mediamuxer_get_state_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Get media muxer state.
 * @scenario				Create and destroy a media muxer handle for muxing.\n
 get media muxer state.
 * @apicovered			mediamuxer_create, mediamuxer_get_state, mediamuxer_destroy
 * @passcase				When API returns MEDIAMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Get media muxer state.
//& type: auto
int ITc_mediamuxer_get_state_p(void)
{
	START_TEST;

	mediamuxer_h muxer;
	mediamuxer_state_e state = -1;

	int nRetVal = mediamuxer_create(&muxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_create", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_get_state(muxer, &state);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_get_state", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	if( state < MEDIAMUXER_STATE_NONE || state > MEDIAMUXER_STATE_PAUSED)
	{
		nRetVal = mediamuxer_destroy(muxer);
		PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_destroy", MediamuxerGetError(nRetVal));
		return 1;
	}

	nRetVal = mediamuxer_destroy(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_destroy", MediamuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediamuxer_set_unset_error_cb_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Register and unregister an error callback function to be invoked when an error occurs.
 * @scenario				Create and destroy a media muxer handle for muxing.\n
 register and unregister an error callback function to be invoked when an error occurs.
 * @apicovered			mediamuxer_create, mediamuxer_get_state, mediamuxer_destroy
 * @passcase				When API returns MEDIAMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Register and unregister an error callback function to be invoked when an error occurs.
//& type: auto
int ITc_mediamuxer_set_unset_error_cb_p(void)
{
	START_TEST;

	mediamuxer_h muxer;

	int nRetVal = mediamuxer_create(&muxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_create", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_set_error_cb(muxer, mediamuxer_error_callback, NULL);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_set_error_cb", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_unset_error_cb(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_unset_error_cb", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_destroy(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_destroy", MediamuxerGetError(nRetVal));

	return 0;
}

/**
 * @testcase 			ITc_mediamuxer_pause_resume_p
 * @since_tizen			3.0
 * @author            	SRID(shekhar1.s)
 * @reviewer         	SRID(gupta.sanjay)
 * @type 				auto
 * @description			Pause and resume the media muxer.
 * @scenario				Create media muxer handle for muxing.\n
 pause and resume the media muxer.
 * @apicovered			mediamuxer_create, mediamuxer_destroy, mediamuxer_set_data_sink, mediamuxer_start, mediamuxer_stop, mediamuxer_write_sample, mediamuxer_pause, mediamuxer_resume.
 * @passcase				When API returns MEDIAMUXER_ERROR_NONE.
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: Pause and resume the media muxer.
//& type: auto
int ITc_mediamuxer_pause_resume_p(void)
{
	START_TEST;
	mediamuxer_h muxer = NULL;
	media_format_h media_format = NULL;
	media_format_h media_format2 = NULL;

	FILE *pvFile;
	unsigned int vsize = 5637;
	unsigned int pts_vid = 0;
	unsigned int dts_vid = 0;
	unsigned int duration_vid = 33000000;
	int track_index_vid = 1;
	media_packet_h vid_pkt;
	unsigned char *dptr;

	mediamuxer_output_format_e  format = MEDIAMUXER_CONTAINER_FORMAT_MP4;

	int nRetVal = mediamuxer_create(&muxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_create", MediamuxerGetError(nRetVal));

	nRetVal = media_format_create(&media_format);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_create", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = media_format_set_video_mime(media_format, MEDIA_FORMAT_H264_SP);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_mime", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_set_data_sink(muxer, g_uri, format);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_set_data_sink", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_add_track(muxer, media_format, &track_index_vid);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_add_track", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_prepare(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_prepare", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	nRetVal = mediamuxer_start(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_start", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer));

	pvFile = fopen(g_h264_path, "rb");

	nRetVal = media_format_make_writable(media_format, &media_format2);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_make_writable", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));
	media_format = NULL;

	nRetVal = media_format_set_video_width(media_format2, vsize / 2 + 1);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_width", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_format_set_video_height(media_format2, vsize / 2 + 1);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_height", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_format_set_video_frame_rate(media_format2, 30);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_frame_rate", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_create(media_format2, NULL, NULL, &vid_pkt);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_create", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_alloc(vid_pkt);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_alloc", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	media_packet_get_buffer_data_ptr(vid_pkt, (void**)&dptr);
	vsize = fread(dptr, 1, vsize, pvFile);

	nRetVal = media_packet_set_buffer_size(vid_pkt, vsize);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_buffer_size", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer) ;fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_set_pts(vid_pkt, pts_vid);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_pts", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_set_dts(vid_pkt, dts_vid);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_dts", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_set_duration(vid_pkt, duration_vid);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_duration", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = mediamuxer_write_sample(muxer, track_index_vid, vid_pkt);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_write_sample", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = mediamuxer_pause(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_pause", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = mediamuxer_resume(muxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_resume", MediamuxerGetError(nRetVal), mediamuxer_destroy(muxer);fclose(pvFile);media_format_unref(media_format);media_format_unref(media_format2));

	nRetVal = media_packet_destroy(vid_pkt);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_destroy", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_stop(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_stop", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_unprepare(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_unprepare", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_destroy(muxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_destroy", MediamuxerGetError(nRetVal));
	fclose(pvFile);
	if (media_format)
		media_format_unref(media_format);

	if (media_format2)
		media_format_unref(media_format2);

	return 0;
}


/**
 * @testcase 			ITc_mediamuxer_set_unset_eos_cb_p
 * @since_tizen			4.0
 * @author            		SRID(j.abhishek)
 * @reviewer         		SRID(nibha.sharma)
 * @type 			auto
 * @description			Register and unregister an End of Stream callback function to be invoked when an EOS occurs.
 * @scenario			Create and destroy a media muxer handle for muxing.\n
 * 				register and unregister an error callback function to be invoked when an EOS occurs.
 * @apicovered			mediamuxer_create, mediamuxer_set_eos_cb, mediamuxer_unset_eos_cb, mediamuxer_destroy
 * @passcase			When API returns MEDIAMUXER_ERROR_NONE.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: Register and unregister an End of Stream callback function to be invoked when an EOS occurs.
//& type: auto

int ITc_mediamuxer_set_unset_eos_cb_p(void)
{
	START_TEST;

	mediamuxer_h hMediaMuxer = NULL;
	media_format_h hMediaFormat = NULL;
	media_format_h hMediaFormat2 = NULL;
	FILE *pszvFile;
	media_packet_h hVideoPacket;
	unsigned char *dptr;

	int vsize = 0;
	unsigned int pts_vid = 0;
	unsigned int dts_vid = 0;
	unsigned int duration_vid = 33000000;
	int track_index_vid = 1;
	int nTimeoutId = 0;
	int loop_count;

	mediamuxer_output_format_e  format = MEDIAMUXER_CONTAINER_FORMAT_MP4;

	int nRetVal = mediamuxer_create(&hMediaMuxer);
	PRINT_RESULT(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_create", MediamuxerGetError(nRetVal));
	CHECK_HANDLE(hMediaMuxer, "mediamuxer_create");

	nRetVal = media_format_create(&hMediaFormat);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_create", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer));
	CHECK_HANDLE(hMediaFormat, "media_format_create");

	nRetVal = mediamuxer_set_eos_cb(hMediaMuxer, mediamuxer_eos_callback, NULL);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_set_eos_cb", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);media_format_unref(hMediaFormat));

	nRetVal = media_format_set_video_mime(hMediaFormat, MEDIA_FORMAT_H264_SP);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_mime", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);media_format_unref(hMediaFormat));

	nRetVal = mediamuxer_set_data_sink(hMediaMuxer, g_uri, format);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_set_data_sink", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);media_format_unref(hMediaFormat));

	nRetVal = mediamuxer_add_track(hMediaMuxer, hMediaFormat, &track_index_vid);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_add_track", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);media_format_unref(hMediaFormat));

	nRetVal = mediamuxer_prepare(hMediaMuxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_prepare", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);media_format_unref(hMediaFormat));

	nRetVal = mediamuxer_start(hMediaMuxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_start", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);media_format_unref(hMediaFormat));

	pszvFile = fopen(g_h264_path, "rb");
	CHECK_HANDLE(pszvFile, "fopen");

	nRetVal = media_format_make_writable(hMediaFormat, &hMediaFormat2);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_make_writable", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));
	hMediaFormat = NULL;
	CHECK_HANDLE_CLEANUP(hMediaFormat2, "media_format_make_writable",mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

	nRetVal = media_format_set_video_width(hMediaFormat2, 640);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_width", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

	nRetVal = media_format_set_video_height(hMediaFormat2, 480);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_height", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

	nRetVal = media_format_set_video_frame_rate(hMediaFormat2, 30);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_format_set_video_frame_rate", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

	for (loop_count = 0; loop_count < 50; loop_count++)
	{
		nRetVal = media_packet_create(hMediaFormat2, NULL, NULL, &hVideoPacket);
		PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_create", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));
		CHECK_HANDLE_CLEANUP(hVideoPacket, "media_packet_create",mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

		nRetVal = media_packet_alloc(hVideoPacket);
		PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_alloc", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

		media_packet_get_buffer_data_ptr(hVideoPacket, (void**)&dptr);
		vsize = MediamuxerExtractNal(pszvFile, dptr);

		if (vsize <= 0) {
			if (vsize == -2) {
				FPRINTF("[Line : %d][%s] input NAL is SPS/PPS\\n", __LINE__, API_NAMESPACE);
			} else {
				FPRINTF("[Line : %d][%s] input file read error\\n", __LINE__, API_NAMESPACE);
			}
			media_packet_destroy(hVideoPacket);
			continue;
		}

		nRetVal = media_packet_set_buffer_size(hVideoPacket, vsize);
		PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_buffer_size", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer) ;fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

		nRetVal = media_packet_set_pts(hVideoPacket, pts_vid);
		PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_pts", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));
		pts_vid += duration_vid;

		nRetVal = media_packet_set_dts(hVideoPacket, dts_vid);
		PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_dts", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

		nRetVal = media_packet_set_duration(hVideoPacket, duration_vid);
		PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "media_packet_set_duration", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

		nRetVal = mediamuxer_write_sample(hMediaMuxer, track_index_vid, hVideoPacket);
		PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_write_sample", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

		if (hVideoPacket)
		{
			media_packet_destroy(hVideoPacket);
		}
	}

	nRetVal = mediamuxer_close_track(hMediaMuxer, track_index_vid);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_close_track", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

	RUN_POLLING_LOOP;

	if ( g_bCallbackHit == false)
	{
		FPRINTF("[Line : %d][%s] mediamuxer_set_eos_cb failed, error = callback not invoked \\n", __LINE__, API_NAMESPACE);
		mediamuxer_destroy(hMediaMuxer);
		fclose(pszvFile);
		media_format_unref(hMediaFormat);
		media_format_unref(hMediaFormat2);
		return 1;
	}

	nRetVal = mediamuxer_stop(hMediaMuxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_stop", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_unprepare(hMediaMuxer);
	PRINT_RESULT_NORETURN(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_unprepare", MediamuxerGetError(nRetVal));

	nRetVal = mediamuxer_unset_eos_cb(hMediaMuxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_unset_eos_cb", MediamuxerGetError(nRetVal), mediamuxer_destroy(hMediaMuxer);fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

	nRetVal = mediamuxer_destroy(hMediaMuxer);
	PRINT_RESULT_CLEANUP(MEDIAMUXER_ERROR_NONE, nRetVal, "mediamuxer_unset_eos_cb", MediamuxerGetError(nRetVal), fclose(pszvFile);media_format_unref(hMediaFormat);media_format_unref(hMediaFormat2));

	fclose(pszvFile);
	pszvFile = NULL;

	if (hMediaFormat)
		media_format_unref(hMediaFormat);
	if (hMediaFormat2)
		media_format_unref(hMediaFormat2);

	return 0;
}

/** @} */
/** @} */

