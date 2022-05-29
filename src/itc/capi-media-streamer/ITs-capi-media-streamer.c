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
#include "ITs-capi-media-streamer-common.h"
#define FEATURE_NAME_WIFI "http://tizen.org/feature/network.wifi"
#define FEATURE_NAME_TELEPHONY "http://tizen.org/feature/network.telephony"
#define FEATURE_NAME_ETHERNET "http://tizen.org/feature/network.ethernet"

//& set: CapiMedia-streamer

/** @addtogroup itc-capi-media-streamer
*  @ingroup itc
*  @{
*/

#define PLAY_TIME 5

const char *g_pszFilePath = NULL;
static GMainLoop *g_mainloop = NULL;

/**
 * @function 		ITs_capi_media_streamer_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_media_streamer_startup(void)
{
	struct stat stBuff;
	int nRetVal =-1;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		FPRINTF("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		int path_size = strlen(pszValue)+strlen("/res/test_10sec.mp4")+1;
		g_pszFilePath=(char*)calloc(path_size, sizeof(char));
		if (g_pszFilePath == NULL)
                {
                        FPRINTF("[Line : %d][%s] Memory Allocation Failed for g_pszFilePath \\n", __LINE__, API_NAMESPACE);
                        return;
                }
		snprintf(g_pszFilePath, path_size, "%s/res/test_10sec.mp4", pszValue);
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	nRetVal = media_streamer_create(&streamer);
	if(nRetVal < 0)
	{
		FPRINTF("[Line : %d][%s] media_streamer_create failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}

	nRetVal = media_format_create(&vfmt_encoded);
	if(nRetVal < 0)
	{
		FPRINTF("[Line : %d][%s] media_format_create failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}
	nRetVal = media_format_set_video_mime(vfmt_encoded, MEDIA_FORMAT_H263);
	if(nRetVal < 0)
	{
		FPRINTF("[Line : %d][%s] media_format_set_video_mime failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}
	nRetVal = media_format_set_video_width(vfmt_encoded, VIDEO_WIDTH);
	if(nRetVal != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_video_width failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}
	nRetVal = media_format_set_video_height(vfmt_encoded, VIDEO_HEIGHT);
	if(nRetVal != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_video_height failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}
	nRetVal = media_format_set_video_frame_rate(vfmt_encoded, VIDEO_FRAME_RATE);
	if(nRetVal != MEDIA_FORMAT_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] media_format_set_video_frame_rate failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}
	return;
}


/**
 * @function 		ITs_capi_media_streamer_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_media_streamer_cleanup(void)
{
	int nRetVal =-1;
	media_format_unref(vfmt_encoded);
    nRetVal = media_streamer_destroy(streamer);
	if(nRetVal < 0)
	{
		FPRINTF("[Line : %d][%s] media_streamer_destroy failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRetVal), nRetVal);
		return;
	}

	if (g_pszFilePath) {
		free(g_pszFilePath);
		g_pszFilePath = NULL;
	}	


	return;
}

/** @addtogroup itc-capi-media-streamer-testcases
*  @brief 		Integration testcases for module capi-media-streamer
*  @ingroup 	itc-capi-media-streamer
*  @{
*/

/**
* @function 		buffer_status_cb
* @description	 	callback function for buffer status
* @parameter		key: streamer node,buffer status and user data  sent to callback
* @return 			NA
*/

void buffer_status_cb(media_streamer_node_h node,
                      media_streamer_custom_buffer_status_e status,
                      void *user_data) {

	if (status == MEDIA_STREAMER_CUSTOM_BUFFER_UNDERRUN) 
	{
		/* Buffer status cb got underflow */
		char *test = "This is buffer_status_cb test!";

		unsigned int size = strlen(test);

		media_packet_h packet;
		media_packet_create_from_external_memory(vfmt_encoded,(void *)test, size, NULL, NULL, &packet);
		media_streamer_node_push_packet(node, packet);
	} 
	else 
	{
		/* Buffer status cb got overflow */
		media_streamer_node_push_packet(node, NULL);
	}
}

static gboolean timeout_func(gpointer data)
{
	fprintf(stdout, "Loop timeout is finished!\n");
	g_main_loop_quit((GMainLoop *) data);
	return FALSE;
}

static void wait_for_async(unsigned int sec)
{
	g_mainloop = g_main_loop_new(NULL, FALSE);

	g_timeout_add_seconds(sec, timeout_func, g_mainloop);
	g_main_loop_run(g_mainloop);
	g_main_loop_unref(g_mainloop);
	g_mainloop = NULL;
}

/**
* @function 		new_buffer_cb
* @description	 	callback function for new buffer
* @parameter		key: streamer node and user data  sent to callback
* @return 			NA
*/
void new_buffer_cb(media_streamer_node_h node, void *user_data)
{
	char *received_data = NULL;
	media_packet_h packet;

	media_streamer_node_pull_packet(node, &packet);

	media_packet_get_buffer_data_ptr(packet, (void **)&received_data);

	media_packet_destroy(packet);
}
/**
* @function 		interrupted_cb
* @description	 	Called when the media streamer is interrupted
* @parameter		error code: The interrupted error code and user data  sent to callback
* @return 			NA
*/
void interrupted_cb(media_streamer_interrupted_code_e code, void *user_data)
{
	FPRINTF("[Line : %d][%s] interrupted_cb CALLBACK INVOKED", __LINE__, API_NAMESPACE);
}
//& purpose: A purpose of a first positive TC.
//& type: auto
/**
* @testcase 			ITc_capi_media_streamer_prepare_unprepare_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Prepare and unprepare media streamer
* @scenario				create media streamer\n
* 						Prepare media Streamer\n
* 						Unprepare media streamer and Destroy
* @apicovered			media_streamer_prepare\n
						media_streamer_unprepare\n
* @passcase				When media_streamer_create and media_streamer_prepare are successful.
* @failcase				If target API's media_streamer_create or media_streamer_prepare fails or any precondition or postcondition API fails
* @precondition			At least one src and one sink should be added and linked in the streamer
*      					by calling media_streamer_node_create_src(), media_streamer_node_create_sink() and media_streamer_node_link().
* @postcondition		The media streamer state will be #MEDIA_STREANER_STATE_READY.
*/
int ITc_capi_media_streamer_prepare_unprepare_p(void)
{
	START_TEST;
	int ret = -1;
	CHECK_HANDLE(streamer,"ITc_capi_media_streamer_prepare_unprepare_p");
	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_create_src", MediaStreamerGetError(ret));
	CHECK_HANDLE(video_src,"ITc_capi_media_streamer_prepare_unprepare_p_video_src");
	ret = media_streamer_node_add(streamer, video_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_create_Sink", MediaStreamerGetError(ret));
	CHECK_HANDLE(video_sink,"ITc_capi_media_streamer_prepare_unprepare_p_video_sink");
	ret = media_streamer_node_add(streamer, video_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));


	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_link", MediaStreamerGetError(ret));

	ret = media_streamer_prepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_prepare", MediaStreamerGetError(ret));
	wait_for_async(PLAY_TIME);
	ret = media_streamer_unprepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_unprepare", MediaStreamerGetError(ret));
	return 0;
}



/**
* @testcase 			ITc_capi_media_streamer_play_pause_stop_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Play and Pause  media streamer
* @scenario				create media streamer\n
* 						Prepare media Streamer\n
*						Play  media Streamer\n
*						Pause  media Streamer\n
*						Stop  media Streamer\n
* @apicovered			media_streamer_create\n
*						media_streamer_prepare\n
*						media_streamer_play\n
*						media_streamer_pause\n
*						media_streamer_stop\n
*						media_streamer_unprepare
* @passcase				When media_streamer_create and media_streamer_prepare,play,pause,stop are successful.
* @failcase				If target API's media_streamer_create or media_streamer_prepare fails or any precondition or postcondition API fails
* @precondition			The media streamer state must be set to #MEDIA_STREAMER_STATE_PLAYING.
* @postcondition		The media streamer state will be #MEDIA_STREANER_STATE_READY.
*/
int ITc_capi_media_streamer_play_pause_stop_p(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_create_src", MediaStreamerGetError(ret));
	CHECK_HANDLE(video_src,"ITc_capi_media_streamer_prepare_unprepare_p_video_src");
	ret = media_streamer_node_add(streamer, video_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_create_Sink", MediaStreamerGetError(ret));
	CHECK_HANDLE(video_sink,"ITc_capi_media_streamer_prepare_unprepare_p_video_sink");

	ret = media_streamer_node_add(streamer, video_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_link", MediaStreamerGetError(ret));

	ret = media_streamer_prepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_prepare", MediaStreamerGetError(ret));
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_play", MediaStreamerGetError(ret),media_streamer_unprepare(streamer));
	wait_for_async(PLAY_TIME);

	ret = media_streamer_pause(streamer);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_pause", MediaStreamerGetError(ret),media_streamer_unprepare(streamer));
	wait_for_async(PLAY_TIME);
	
	ret = media_streamer_stop(streamer);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_stop", MediaStreamerGetError(ret),media_streamer_unprepare(streamer));
	wait_for_async(PLAY_TIME);
	
	ret = media_streamer_unprepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_unprepare", MediaStreamerGetError(ret));

	return 0;

}

/**
* @testcase 			ITc_capi_media_streamer_get_state_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Prepare and unprepare media streamer
* @scenario				create media streamer\n
* 						Prepare media Streamer\n
*						Play  media Streamer\n
*						Pause  media Streamer\n
*						Get State of Media streamer\n
*						Stop  media Streamer\n
* @apicovered			media_streamer_create\n
*						media_streamer_prepare\n
*						media_streamer_play\n
*						media_streamer_pause\n
*						media_streamer_get_state\n
*						media_streamer_stop\n
*						media_streamer_unprepare
* @passcase				When media_streamer_create and media_streamer_get_state are successful.
* @failcase				If target API's media_streamer_create or media_streamer_prepare fails or any precondition or postcondition API fails
* @precondition			Create a media streamer handle by calling media_streamer_create() function
* @postcondition		The media streamer state will be #MEDIA_STREANER_STATE_READY.
*/
int ITc_capi_media_streamer_get_state_p(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_streamer_state_e state;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_create_src", MediaStreamerGetError(ret));
	CHECK_HANDLE(video_src,"ITc_capi_media_streamer_prepare_unprepare_p_video_src");
	ret = media_streamer_node_add(streamer, video_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_create_Sink", MediaStreamerGetError(ret));
	CHECK_HANDLE(video_sink,"ITc_capi_media_streamer_prepare_unprepare_p_video_sink");

	ret = media_streamer_node_add(streamer, video_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_link", MediaStreamerGetError(ret));

	ret = media_streamer_prepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_prepare", MediaStreamerGetError(ret));
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_play", MediaStreamerGetError(ret),media_streamer_unprepare(streamer));
	wait_for_async(PLAY_TIME);

	ret = media_streamer_pause(streamer);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_pause", MediaStreamerGetError(ret),media_streamer_stop(streamer);media_streamer_unprepare(streamer));
	wait_for_async(PLAY_TIME);
	
	ret = media_streamer_get_state(streamer,&state);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_get_state", MediaStreamerGetError(ret),media_streamer_stop(streamer);media_streamer_unprepare(streamer));
	wait_for_async(PLAY_TIME);
	
	if(state != MEDIA_STREAMER_STATE_PAUSED)
	{		 
		 FPRINTF("[Line : %d][%s] media_streamer_get_state failed \\n", __LINE__, API_NAMESPACE);
                 media_streamer_unprepare(streamer);
		 return 1;
	}
	ret = media_streamer_stop(streamer);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_stop", MediaStreamerGetError(ret),media_streamer_unprepare(streamer));
	wait_for_async(PLAY_TIME);
	
	ret = media_streamer_unprepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_unprepare", MediaStreamerGetError(ret));

	return 0;

}

/**
* @testcase 			ITc_capi_media_streamer_node_create_src_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			media streamer node src creation
* @scenario				media streamer node src create
* @apicovered			media_streamer_node_create_src
* @passcase				When media_streamer_node_create_src is successful.
* @failcase				If target API's media_streamer_create or media_streamer_prepare fails or any precondition or postcondition API fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_capi_media_streamer_node_create_src_p(void)
{
   	START_TEST;
	media_streamer_node_h src =NULL; 
	
	const char *pszKeyCamera = "http://tizen.org/feature/camera";
	const char *pszKeyMic = "http://tizen.org/feature/microphone";
	const char *pszKeyInternet = "http://tizen.org/feature/network.internet";
	bool bValue = false;
	bool bValueWifi = false, bValueTel = false, bValueEth = false;
	int ret;

	media_streamer_node_src_type_e eNodeSrcType[] = { MEDIA_STREAMER_NODE_SRC_TYPE_FILE,           /**<  Local file src type */
													  MEDIA_STREAMER_NODE_SRC_TYPE_HTTP,           /**<  Http src type, Network internet feature is required */
													  MEDIA_STREAMER_NODE_SRC_TYPE_RTSP,           /**<  Rtsp src type, Network internet feature is required */
													  MEDIA_STREAMER_NODE_SRC_TYPE_AUDIO_CAPTURE,  /**<  Audio capture src type, Microphone feature is required */
													  MEDIA_STREAMER_NODE_SRC_TYPE_AUDIO_TEST,     /**<  Audio test src type */
													  MEDIA_STREAMER_NODE_SRC_TYPE_CAMERA,         /**<  Camera src type, Camera feature is required */
													  MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_CAPTURE,  /**<  Video capture src type, Camera feature is required */
													  MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST,     /**<  Video test src type */
													  MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM,         /**<  Custom src type */
													  MEDIA_STREAMER_NODE_SRC_TYPE_ADAPTIVE};       /**<  Adaptive src type */

	int enum_size = sizeof(eNodeSrcType) / sizeof(eNodeSrcType[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		bValue = false;
		FPRINTF("[Line : %d][%s] For node src type = [%d] \\n", __LINE__, API_NAMESPACE, eNodeSrcType[enum_counter]);
		int nRet = media_streamer_node_create_src(eNodeSrcType[enum_counter], &src);
		if (eNodeSrcType[enum_counter] == MEDIA_STREAMER_NODE_SRC_TYPE_CAMERA || eNodeSrcType[enum_counter] == MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_CAPTURE)
		{
			ret = system_info_get_platform_bool(pszKeyCamera, &bValue);
			PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, ret, "system_info_get_platform_bool", SystemInfoGetError(ret));
			if(bValue == false)
			{
				if(nRet != MEDIA_STREAMER_ERROR_NOT_SUPPORTED)
				{
					FPRINTF("[Line : %d][%s] media_streamer_node_create_src API call returned mismatch %s error for unsupported camera feature\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRet));
					return 1;
				}
				else
				{
					FPRINTF("[Line : %d][%s] media_streamer_node_create_src API call correctly returned %s error for unsupported camera feature\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRet));
					continue;
				}
			}
		}
		if (eNodeSrcType[enum_counter] == MEDIA_STREAMER_NODE_SRC_TYPE_AUDIO_CAPTURE)
		{
			ret = system_info_get_platform_bool(pszKeyMic, &bValue);
			PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, ret, "system_info_get_platform_bool", SystemInfoGetError(ret));
			if(bValue == false)
			{
				if(nRet != MEDIA_STREAMER_ERROR_NOT_SUPPORTED)
				{
					FPRINTF("[Line : %d][%s] media_streamer_node_create_src API call returned mismatch %s error for unsupported microphone feature\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRet));
					return 1;
				}
				else
				{
					FPRINTF("[Line : %d][%s] media_streamer_node_create_src API call correctly returned %s error for unsupported microphone feature\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRet));
					continue;
				}
			}
		}
		if (eNodeSrcType[enum_counter] == MEDIA_STREAMER_NODE_SRC_TYPE_HTTP || eNodeSrcType[enum_counter] == MEDIA_STREAMER_NODE_SRC_TYPE_RTSP)
		{
			ret = system_info_get_platform_bool(FEATURE_NAME_WIFI, &bValueWifi);
			PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, ret, "system_info_get_platform_bool", SystemInfoGetError(ret));
		
			ret = system_info_get_platform_bool(FEATURE_NAME_TELEPHONY, &bValueTel);
			PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, ret, "system_info_get_platform_bool", SystemInfoGetError(ret));
			ret = system_info_get_platform_bool(FEATURE_NAME_ETHERNET, &bValueEth);
			PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, ret, "system_info_get_platform_bool", SystemInfoGetError(ret));
			

			if((bValueWifi == false)&&(bValueTel == false)&&(bValueEth == false))
			{
				if(nRet != MEDIA_STREAMER_ERROR_NOT_SUPPORTED)
				{
					FPRINTF("[Line : %d][%s] media_streamer_node_create_src API call returned mismatch %s error for unsupported internet feature\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRet));
					return 1;
				}
				else
				{
					FPRINTF("[Line : %d][%s] media_streamer_node_create_src API call correctly returned %s error for unsupported internet feature\\n", __LINE__, API_NAMESPACE, MediaStreamerGetError(nRet));
					continue;
				}
			}
		}
		PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_node_create_src", MediaStreamerGetError(nRet));
		CHECK_HANDLE(src,"media_streamer_node_create_src");
		
		ret = media_streamer_node_destroy(src);
		PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_destroy", MediaStreamerGetError(ret));
	}
	return 0;
}

/**
* @testcase 			ITc_capi_media_streamer_node_push_packet_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Media streamer node packet push
* @scenario				create media streamer node src\n
* 						Prepare media Streamer\n
* 						Unprepare media streamer and Destroy
* @apicovered			media_streamer_create\n
						media_streamer_prepare\n
						media_streamer_unprepare\n
						media_streamer_destroy
* @passcase				When media_streamer_create and media_streamer_prepare are successful.
* @failcase				If target API's media_streamer_create or media_streamer_prepare fails or any precondition or postcondition API fails
* @precondition			Create a source node handle by calling media_streamer_node_create_src() function
*      					The media streamer state must be set to #MEDIA_STREAMER_STATE_IDLE at least.
* @postcondition		NA
*/
int ITc_capi_media_streamer_node_push_packet_p(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_packet_h packet = NULL;
	const char *test = "This is buffer_status_cb test!";
	media_streamer_node_h custom_src = NULL;

	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &custom_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_src", MediaStreamerGetError(ret));
	CHECK_HANDLE(custom_src,"media_streamer_node_create_src");
	
	media_packet_create_from_external_memory (vfmt_encoded, (void*)test, strlen(test), NULL, NULL, &packet);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_packet_create_from_external_memory", MediaStreamerGetError(ret),media_streamer_node_destroy(custom_src));
	CHECK_HANDLE(packet,"media_packet_create_from_external_memory");

	ret = media_streamer_node_push_packet(custom_src, packet);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_push_packet", MediaStreamerGetError(ret),media_streamer_node_destroy(custom_src));
	
	ret = media_streamer_node_destroy(custom_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_destroy", MediaStreamerGetError(ret));
	return 0;
}


/**
* @testcase 			ITc_capi_media_streamer_node_create_sink_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Prepare and unprepare media streamer
* @scenario				create media streamer node sink\n					
* @apicovered			media_streamer_node_create_sink
* @passcase				When media_streamer_node_create_sink successful.
* @failcase				If target API's media_streamer_node_create_sink fails or any precondition or postcondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_media_streamer_node_create_sink_p(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &video_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_sink", MediaStreamerGetError(ret));
	CHECK_HANDLE(video_sink,"media_streamer_node_create_sink");
	return 0;
}

/**
* @testcase 			ITc_capi_media_streamer_node_pull_packet_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			media streamer node packet pull
* @scenario				create media streamer node src\n
* 						Prepare media Streamer\n
* 						Unprepare media streamer and Destroy
* @apicovered			media_streamer_create\n
						media_streamer_prepare\n
						media_streamer_unprepare\n
						media_streamer_node_add\n
						media_streamer_node_set_pad_format\n
						media_streamer_destroy
* @passcase				When all api are successful.
* @failcase				If target API's media_streamer_create or media_streamer_prepare fails or any precondition or postcondition API fails
* @precondition			At least one src and one sink should be added and linked in the streamer
*      					by calling media_streamer_node_create_src(), media_streamer_node_create_sink() and media_streamer_node_link().
* @postcondition		The media streamer state will be #MEDIA_STREANER_STATE_READY.
*/
int ITc_capi_media_streamer_node_pull_packet_p(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;

	/*********************** app_src *********************************** */
	media_streamer_node_h app_src = NULL;

	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_src", MediaStreamerGetError(ret));
	CHECK_HANDLE(app_src,"media_streamer_node_create_src");
	
	ret = media_streamer_node_add(streamer, app_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));
	/*********************** app_sink *********************************** */
	media_streamer_node_h app_sink = NULL;

	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_sink", MediaStreamerGetError(ret));
	CHECK_HANDLE(app_sink,"media_streamer_node_create_sink");
	
	ret = media_streamer_node_set_pad_format(app_sink, "sink", vfmt_encoded);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_set_pad_format", MediaStreamerGetError(ret));

	ret = media_streamer_node_add(streamer, app_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));
	/*====================Linking ======================================== */
	ret = media_streamer_node_link(app_src, "src", app_sink, "sink");
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_link", MediaStreamerGetError(ret));
	/*====================================================================== */

	ret = media_streamer_src_set_buffer_status_cb(app_src, buffer_status_cb, NULL);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_src_set_buffer_status_cb", MediaStreamerGetError(ret));

	media_streamer_sink_set_data_ready_cb(app_sink, new_buffer_cb, NULL);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_sink_set_data_ready_cb", MediaStreamerGetError(ret));

	ret = media_streamer_prepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_prepare", MediaStreamerGetError(ret));
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_play", MediaStreamerGetError(ret),media_streamer_unprepare(streamer));
	wait_for_async(PLAY_TIME);
	
	ret = media_streamer_unprepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_unprepare", MediaStreamerGetError(ret));
	return 0;
}

/**
* @testcase 			ITc_capi_media_streamer_node_add_remove_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Add and remove media streamer node
* @scenario				create media streamer node\n
*						add media streamer node\n
*						remove media streamer node\n
* 						destroy media streamer node
* @apicovered			media_streamer_node_create\n
						media_streamer_node_add\n
						media_streamer_node_remove\n
						media_streamer_node_destroy
* @passcase				When media_streamer_node_create and media_streamer_node_add, media_streamer_node_remove are successful.
* @failcase				If target API's media_streamer_create or media_streamer_prepare fails or any precondition or postcondition API fails
* @precondition			Create media streamer handle by calling media_streamer_create() function
*      					Create node handle by calling media_streamer_node_create() function
* @postcondition		NA
*/
int ITc_capi_media_streamer_node_add_remove_p(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_streamer_node_h audio_res = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_RESAMPLE, NULL, NULL, &audio_res);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create", MediaStreamerGetError(ret));
	CHECK_HANDLE(audio_res,"media_streamer_node_create");

	ret = media_streamer_node_add(streamer, audio_res);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret),media_streamer_node_destroy(audio_res));

	ret = media_streamer_node_remove(streamer,audio_res);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_remove", MediaStreamerGetError(ret),media_streamer_node_destroy(audio_res));
	
	ret = media_streamer_node_destroy(audio_res);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_destroy", MediaStreamerGetError(ret));
	return 0;
}

/**
* @testcase 			ITc_capi_media_streamer_node_link_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			capi media streamer node link
* @scenario				create media streamer node\n
* 						create media streamer link\n
* 						Destroy media streamer
* @apicovered			media_streamer_node_create\n
						media_streamer_node_add\n
						media_streamer_node_link\n
						media_streamer_node_destroy
* @passcase				When media_streamer_create and media_streamer_prepare are successful.
* @failcase				If target API's media_streamer_create or media_streamer_prepare fails or any precondition or postcondition API fails
* @precondition			Create a source node and a destination node handles
*      					by calling media_streamer_node_create() function,and add the nodes into streamer by calling media_streamer_node_add() function.
* @postcondition		NA
*/
int ITc_capi_media_streamer_node_link_p(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_streamer_node_h audio_res = NULL;
	media_streamer_node_h audio_converter = NULL;

	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_RESAMPLE, NULL, NULL, &audio_res);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create", MediaStreamerGetError(ret));
	CHECK_HANDLE(audio_res,"media_streamer_node_create");
	
	ret = media_streamer_node_add(streamer, audio_res);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret),media_streamer_node_destroy(NULL));

	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_CONVERTER, NULL, NULL, &audio_converter);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create", MediaStreamerGetError(ret));
	CHECK_HANDLE(audio_converter,"media_streamer_node_create");

	ret = media_streamer_node_add(streamer, audio_converter);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret),media_streamer_node_destroy(NULL));

	ret = media_streamer_node_link(audio_converter, "src", audio_res, "sink");
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_link", MediaStreamerGetError(ret),media_streamer_node_destroy(NULL));
	
	ret = media_streamer_node_remove(streamer,audio_res);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_remove", MediaStreamerGetError(ret),media_streamer_node_destroy(audio_res);media_streamer_node_destroy(audio_converter));
	
	ret = media_streamer_node_remove(streamer,audio_converter);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_remove", MediaStreamerGetError(ret),media_streamer_node_destroy(audio_res);media_streamer_node_destroy(audio_converter));
	
	ret = media_streamer_node_destroy(audio_res);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_destroy", MediaStreamerGetError(ret));
	
	ret = media_streamer_node_destroy(audio_converter);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_destroy", MediaStreamerGetError(ret));
	
	return 0;
}

/**
* @testcase 			ITc_capi_media_streamer_node_node_set_get_pad_format_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and get Pad Format
* @scenario				create media streamer node src\n
* 						Add media Streamer node\n
*						create media streamer node sink\n
*						get  media streamer node pad format\n
*						set  media streamer node pad format\n
* 						Unprepare media streamer and Destroy
* @apicovered			media_streamer_node_create_src\n
						media_streamer_node_add\n
						media_streamer_node_set_pad_format\n
						media_streamer_node_get_pad_format
* @passcase				When media_streamer_node_set_pad_format is successful.
* @failcase				If target API's media_streamer_node_set_pad_format fails or any precondition or postcondition API fails
* @precondition			Create a node handle by calling media_streamer_node_createxxx() function
*      					Get pad name by calling media_streamer_node_get_pad_name() function
* @postcondition		NA
*/
int ITc_capi_media_streamer_node_node_set_get_pad_format_p(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_format_h pad_fmt = NULL;
	int width, height, frame_rate;
	media_format_mimetype_e mime = MEDIA_FORMAT_MP3;
	media_streamer_node_h app_src = NULL;
	int width_init, height_init, frame_rate_init;
	media_format_mimetype_e mime_init = MEDIA_FORMAT_MP3;
	media_streamer_node_h app_sink = NULL;

	ret = media_format_get_video_info(vfmt_encoded, &mime_init, &width_init, &height_init, NULL, NULL);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_format_get_video_info", MediaStreamerGetError(ret));
	assert_eq(mime_init, MEDIA_FORMAT_H263);
	assert_eq(width_init, VIDEO_WIDTH);
	assert_eq(height_init, VIDEO_HEIGHT);

	ret = media_format_get_video_frame_rate(vfmt_encoded, &frame_rate_init);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_format_get_video_frame_rate", MediaStreamerGetError(ret));
	assert_eq(frame_rate_init, VIDEO_FRAME_RATE);

	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_src", MediaStreamerGetError(ret));
	CHECK_HANDLE(app_src,"media_streamer_node_create_src");

	ret = media_streamer_node_add(streamer, app_src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_sink", MediaStreamerGetError(ret));
	CHECK_HANDLE(app_sink,"media_streamer_node_create_sink");

	ret = media_streamer_node_set_pad_format(app_src, "src", vfmt_encoded);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_set_pad_format", MediaStreamerGetError(ret));

	ret = media_streamer_node_add(streamer, app_sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	ret = media_streamer_node_link(app_src, "src", app_sink, "sink");
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_link", MediaStreamerGetError(ret));

	ret = media_streamer_node_get_pad_format(app_src, "src", &pad_fmt);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_get_pad_format", MediaStreamerGetError(ret));
	CHECK_HANDLE(pad_fmt,"media_streamer_node_get_pad_format");

	ret = media_format_get_video_info(pad_fmt, &mime, &width, &height, NULL, NULL);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_format_get_video_info", MediaStreamerGetError(ret));
	assert_eq(mime, MEDIA_FORMAT_H263);
	assert_eq(width, VIDEO_WIDTH);
	assert_eq(height, VIDEO_HEIGHT);

	ret = media_format_get_video_frame_rate(pad_fmt, &frame_rate);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_format_get_video_frame_rate", MediaStreamerGetError(ret));
	assert_eq(frame_rate, VIDEO_FRAME_RATE);

	return 0;
}


/**
* @testcase 			ITc_capi_media_streamer_node_get_pad_name_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Get nod pad Name
* @scenario				create media streamer node\n
* 						Add media Streamer node\n
*						get  media streamer node pad name
* @apicovered			media_streamer_node_create\n
*						media_streamer_node_add\n
*						media_streamer_node_get_pad_name
* @passcase				When media_streamer_create and media_streamer_prepare are successful.
* @failcase				If target API's media_streamer_create or media_streamer_prepare fails or any precondition or postcondition API fails
* @precondition			At least one src and one sink should be added and linked in the streamer
*      					by calling media_streamer_node_create_src(), media_streamer_node_create_sink() and media_streamer_node_link().
* @postcondition		The media streamer state will be #MEDIA_STREANER_STATE_READY.
*/
int ITc_capi_media_streamer_node_get_pad_name_p(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char **src_pad_name = NULL;
	int src_pad_num = 0;
	char **sink_pad_name = NULL;
	int sink_pad_num = 0;
	media_streamer_node_h video_pay = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_PAY, NULL, vfmt_encoded, &video_pay);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create", MediaStreamerGetError(ret));
	CHECK_HANDLE(video_pay,"media_streamer_node_create");

	ret = media_streamer_node_add(streamer, video_pay);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	ret = media_streamer_node_get_pad_name(video_pay,&src_pad_name,&src_pad_num,&sink_pad_name,&sink_pad_num);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_get_pad_name", MediaStreamerGetError(ret));
	CHECK_HANDLE(src_pad_name,"media_streamer_node_get_pad_name");
	CHECK_HANDLE(sink_pad_name,"media_streamer_node_get_pad_name");
	CHECK_VALUE_INT(src_pad_num,"media_streamer_node_get_pad_name");
	CHECK_VALUE_INT(sink_pad_num,"media_streamer_node_get_pad_name");
	
	return 0;
}



/**
* @testcase 			ITc_capi_media_streamer_node_set_get_params_p
* @since_tizen			3.0
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			set and get node params
* @scenario				create media streamer node src\n
* 						Add media Streamer node\n
*						get  media streamer node params\n
*						Set  media streamer node params
* @apicovered			media_streamer_node_create_src\n
						media_streamer_node_add\n
						media_streamer_node_set_params\n
						media_streamer_node_get_params
* @passcase				When media_streamer_node_set_params and media_streamer_node_get_params are successful.
* @failcase				If target API's media_streamer_node_set_params or media_streamer_node_get_params fails or any precondition or postcondition API fails
* @precondition			Create a node handle by calling media_streamer_node_createXXX() function.
*      					Get param list to set by calling media_streamer_node_get_params() function.
* @postcondition		NA
*/
int ITc_capi_media_streamer_node_set_get_params_p(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_streamer_node_h vid_test = NULL;
	bundle *param_list = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &vid_test);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_src", MediaStreamerGetError(ret));
	CHECK_HANDLE(vid_test,"media_streamer_node_create_src");

	ret = media_streamer_node_add(streamer,vid_test);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	bundle *params = bundle_create();
	bundle_add_str(params, "is-live", "true");
	bundle_add_str(params, "timestamp-offset", "1024");
	bundle_add_str(params, "xoffset", "150");
	bundle_add_str(params, "yoffset", "200");

	ret = media_streamer_node_get_params(vid_test, &param_list);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_get_params", MediaStreamerGetError(ret));
	CHECK_HANDLE(param_list,"media_streamer_node_get_params");
	ret = media_streamer_node_set_params(vid_test, params);
        PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_set_params", MediaStreamerGetError(ret));
	bundle_free(params);
	return 0;

}

/**
* @testcase 			ITc_capi_media_streamer_set_get_play_position
* @since_tizen			3.0
* @author            	HQ SQE(sangwoo7.lee)
* @reviewer         	HQ SQE(jk79.lee)
* @type 				auto
* @description			Set and get play position of media streamer
* @scenario				create media streamer\n
* 						Prepare media Streamer\n
* 						Set play position\n
* 						Get play position\n
*						Play media Streamer\n
* 						Set play position\n
* 						Get play position\n
*						Pause  media Streamer\n
* 						Set play position\n
* 						Get play position\n
*						Stop  media Streamer\n
* @apicovered			media_streamer_set_play_position\n
*						media_streamer_get_play_position\n
*						media_streamer_create\n
*						media_streamer_prepare\n
*						media_streamer_play\n
*						media_streamer_pause\n
*						media_streamer_stop\n
*						media_streamer_unprepare
* @passcase				When the media streamer can set and get play position
* @failcase				When the media streamer cannot set or get play position
* @precondition			The media streamer state must be one of these: MEDIA_STREAMER_STATE_READY, MEDIA_STREAMER_STATE_PLAYING, or MEDIA_STREAMER_STATE_PAUSED
* @postcondition		N/A
*/
int ITc_capi_media_streamer_set_get_play_position(void)
{
	START_TEST;
	int ret = MEDIA_STREAMER_ERROR_NONE;
	int nSetMillisecond = 6000;
	int nGetMillisecond = -1;
	bool accurate = false;
	media_streamer_node_h src =NULL; 
	media_streamer_node_h sink = NULL;
	
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_src", MediaStreamerGetError(ret));
	CHECK_HANDLE(src,"media_streamer_node_create_src");

	ret = media_streamer_node_set_param(src,MEDIA_STREAMER_PARAM_URI, g_pszFilePath);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_src", MediaStreamerGetError(ret));

	ret = media_streamer_node_add(streamer, src);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_create_sink", MediaStreamerGetError(ret));
	CHECK_HANDLE(sink,"media_streamer_node_create_sink");

	ret = media_streamer_node_set_param(sink, MEDIA_STREAMER_PARAM_USE_TBM, "false");
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_set_param", MediaStreamerGetError(ret));

	ret = media_streamer_node_add(streamer, sink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_node_add", MediaStreamerGetError(ret));

	ret = media_streamer_prepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_prepare", MediaStreamerGetError(ret));
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_play", MediaStreamerGetError(ret));
	wait_for_async(PLAY_TIME);

	sleep(3);
	
	ret = media_streamer_set_play_position(streamer, nSetMillisecond, 1, NULL, streamer);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_set_play_position", MediaStreamerGetError(ret),media_streamer_unprepare(streamer));
	wait_for_async(PLAY_TIME);

	sleep(3);
	
	ret = media_streamer_get_play_position(streamer, &nGetMillisecond);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_get_play_position", MediaStreamerGetError(ret),media_streamer_unprepare(streamer));
	FPRINTF("[Line : %d][%s] Position mismatch. SetValue: %d, GetValue: %d\\n", __LINE__, API_NAMESPACE, nSetMillisecond, nGetMillisecond);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_stop(streamer);
	PRINT_RESULT_CLEANUP(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_stop", MediaStreamerGetError(ret),media_streamer_unprepare(streamer));
	wait_for_async(PLAY_TIME);

	ret = media_streamer_unprepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, ret, "media_streamer_unprepare", MediaStreamerGetError(ret));

	return 0;
}

/**
* @testcase 			ITc_capi_media_streamer_get_duration_p
* @since_tizen			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			get duration
* @scenario				create media streamer node src\n
* 						Add media Streamer node\n
*						get duration
* @apicovered			media_streamer_node_create_src\n
						media_streamer_node_add\n
						media_streamer_get_duration
* @passcase				When media_streamer_get_duration is successful.
* @failcase				If target API's media_streamer_get_duration fails or any precondition or postcondition API fails
* @precondition			Create a node handle by calling media_streamer_node_createXXX() function.
* @postcondition		NA
*/
int ITc_capi_media_streamer_get_duration_p(void)
{
	START_TEST;
		
	int nRet = MEDIA_STREAMER_ERROR_NONE;
	int nTime=0;

	media_streamer_node_h hVideoSrc = NULL;
	media_streamer_node_h hVideoSink = NULL;

	nRet = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &hVideoSrc);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_node_create_src", MediaStreamerGetError(nRet));
	CHECK_HANDLE(hVideoSrc,"media_streamer_node_create_src");

	media_streamer_node_set_param(hVideoSrc,MEDIA_STREAMER_PARAM_URI, g_pszFilePath);

	nRet = media_streamer_node_add(streamer, hVideoSrc);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_node_add", MediaStreamerGetError(nRet));

	nRet = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &hVideoSink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_node_create_sink", MediaStreamerGetError(nRet));
	CHECK_HANDLE(hVideoSink,"media_streamer_node_create_sink");

	nRet = media_streamer_node_add(streamer, hVideoSink);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_node_add", MediaStreamerGetError(nRet));

	nRet = media_streamer_node_link(hVideoSrc, "src", hVideoSink, "sink");
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_node_link", MediaStreamerGetError(nRet));

	nRet = media_streamer_prepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_prepare", MediaStreamerGetError(nRet));
	wait_for_async(PLAY_TIME);

	nRet = media_streamer_play(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_play", MediaStreamerGetError(nRet));
	wait_for_async(PLAY_TIME);

	sleep(5);
	nRet = media_streamer_get_duration(streamer, &nTime);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_get_duration", MediaStreamerGetError(nRet));
	wait_for_async(PLAY_TIME);
	
	FPRINTF("[Line : %d][%s] Duration nTime: %d\\n", __LINE__, API_NAMESPACE, nTime);

	nRet = media_streamer_unprepare(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_unprepare", MediaStreamerGetError(nRet));
	
	return 0;
}
/**
* @testcase 			ITc_capi_media_streamer_set_unset_interrupted_p
* @since_tizen			3.0
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Registered and unregistered a callback function
* @scenario				create media streamer node src\n
* 						Add media Streamer node\n
*						get duration
* @apicovered			media_streamer_set_interrupted_cb\n
						media_streamer_unset_interrupted_cb\n
* @passcase				When media_streamer_set_interrupted_cb and media_streamer_unset_interrupted_cb is successful.
* @failcase				If target API's media_streamer_set_interrupted_cb or media_streamer_set_interrupted_cb fails or any precondition or postcondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_media_streamer_set_unset_interrupted_p(void)
{
	START_TEST;
	
	int nRet = media_streamer_set_interrupted_cb(streamer, interrupted_cb, NULL);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_set_interrupted_cb", MediaStreamerGetError(nRet));
	wait_for_async(PLAY_TIME);
	
	nRet = media_streamer_unset_interrupted_cb(streamer);
	PRINT_RESULT(MEDIA_STREAMER_ERROR_NONE, nRet, "media_streamer_unset_interrupted_cb", MediaStreamerGetError(nRet));
	return 0;
}
/** @} */
/** @} */
