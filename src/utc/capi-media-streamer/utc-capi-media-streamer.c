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
#include "assert.h"
#include <string.h>
#include <glib.h>
#include <system_info.h>
#include <media/media_streamer.h>
#include "tct_common.h"

//& set: CapiMedia-streamer
#define API_NAMESPACE "[CAPI_MEDIA_STREAMER]"

#define CAMERA_ID "2"
#define PLAY_TIME 2
#define PACKET_SIZE 1000
#define MAX_PACKETS_TO_SEND 50000
#define CONFIG_VALUE_LEN_MAX 1024
#define RTP_VIDEO_PORT "5000"
#define RTP_AUDIO_PORT "6000"
#define DEFAULT_IP_ADDR "127.0.0.1"
#define MAX_NODES_COUNT 100
#define APPEND_NODE(x) {g_nodes[g_node_counter++] = x; }
#define EXTREMUM 0

#define VIDEO_WIDTH       352
#define VIDEO_HEIGHT      288
#define VIDEO_FRAME_RATE  30

#define AUDIO_CHANNEL     1
#define AUDIO_SAMPLERATE  8000

#define FILE_NAME "test_10sec.mp4"
#define FILE_PATH_PLAYLIST "segments/prog_index.m3u8"
#define DEFAULT_SEGMENT_PATH "/tmp/segment%05d.ts"
#define DEFAULT_PLAYLIST_PATH "/tmp/playlist.m3u8"
#define _FEATURE_NAME_CAMERA             "http://tizen.org/feature/camera"

static bool g_system_info = true;
static media_format_h vfmt_encoded = NULL;
static media_format_h vfmt_raw = NULL;
static media_format_h afmt_encoded = NULL;
static media_format_h vfmt_aenc = NULL;
static media_format_h vfmt_aencm = NULL;
static media_format_h afmt_raw = NULL;
static media_format_h afmt_araw = NULL;
static media_format_h afmt_aenc = NULL;
static media_format_h tsfmt = NULL;
static media_format_h qtfmt = NULL;

static media_streamer_node_h g_nodes[MAX_NODES_COUNT] = { 0, };
static int g_node_counter = 0;

int pull_packet_res = MEDIA_STREAMER_ERROR_NONE;
int buffer_status = -1;

static GMainLoop *g_mainloop = NULL;
static media_streamer_h streamer = NULL;
static char *file_path = NULL;
static char *file_path_playlist = NULL;
const int set_play_pos = 20000;

/**
 * @function		utc_capi_media_streamer_startup
 * @description		Called before each test.
 * @parameter		NA
 * @return		NA
 */
void utc_capi_media_streamer_startup(void)
{

	char *test_file = FILE_NAME;
	char *test_playlist = FILE_PATH_PLAYLIST;
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

	system_info_get_platform_bool(_FEATURE_NAME_CAMERA, &g_system_info);

	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		unsigned int size_of_path = strlen(pszValue) + strlen(test_file) + 6;
		file_path = (char*)malloc(size_of_path);
		if (!file_path) {
			PRINT_UTC_LOG("memory is not alloced");
			return;
		}
		snprintf(file_path, size_of_path, "%s/res/%s", pszValue, test_file);
		unsigned int size_of_path_playlist = strlen(pszValue) + strlen(test_playlist) + 6;
		file_path_playlist = (char*)malloc(size_of_path_playlist);
		if (!file_path_playlist) {
			PRINT_UTC_LOG("memory is not alloced");
			if (file_path) {
				free (file_path);
				file_path = NULL;
			}
			return;
		}
		snprintf(file_path_playlist, size_of_path_playlist, "%s/res/%s", pszValue, test_playlist);
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	ret = media_streamer_create(&streamer);
	if (ret != MEDIA_STREAMER_ERROR_NONE) {
		PRINT_UTC_LOG("fail to create mediastreamer");
		return;
	}

	/* Define video raw format */
	media_format_create(&vfmt_raw);
	media_format_set_video_mime(vfmt_raw, MEDIA_FORMAT_I420);

	media_format_set_video_width(vfmt_raw, VIDEO_WIDTH);
	media_format_set_video_height(vfmt_raw, VIDEO_HEIGHT);
	media_format_set_video_frame_rate(vfmt_raw, VIDEO_FRAME_RATE);

	/* Define video encoded format */
	media_format_create(&vfmt_encoded);
	media_format_set_video_mime(vfmt_encoded, MEDIA_FORMAT_H263);

	media_format_set_video_width(vfmt_encoded, VIDEO_WIDTH);
	media_format_set_video_height(vfmt_encoded, VIDEO_HEIGHT);
	media_format_set_video_frame_rate(vfmt_encoded, VIDEO_FRAME_RATE);

	/* Define encoded video format for adaptive stream */
	media_format_create(&vfmt_aenc);
	media_format_set_video_mime(vfmt_aenc, MEDIA_FORMAT_H264_SP);
	media_format_set_video_width(vfmt_aenc, VIDEO_WIDTH);
	media_format_set_video_height(vfmt_aenc, VIDEO_HEIGHT);
	media_format_set_video_frame_rate(vfmt_aenc, VIDEO_FRAME_RATE);

	/* Define encoded video format for adaptive stream */
	media_format_create(&vfmt_aencm);
	media_format_set_video_mime(vfmt_aencm, MEDIA_FORMAT_MPEG4_SP);
	media_format_set_video_width(vfmt_aencm, VIDEO_WIDTH);
	media_format_set_video_height(vfmt_aencm, VIDEO_HEIGHT);
	media_format_set_video_frame_rate(vfmt_aencm, VIDEO_FRAME_RATE);

	/* Define audio raw format */
	media_format_create(&afmt_raw);
	media_format_set_audio_mime(afmt_raw, MEDIA_FORMAT_PCM);
	media_format_set_audio_channel(afmt_raw, AUDIO_CHANNEL);
	media_format_set_audio_samplerate(afmt_raw, AUDIO_SAMPLERATE);

	/* Define audio raw format for adaptive streaming */
	media_format_create(&afmt_araw);
	media_format_set_audio_mime(afmt_araw, MEDIA_FORMAT_PCM_F32LE);
	media_format_set_audio_channel(afmt_araw, AUDIO_CHANNEL);
	media_format_set_audio_samplerate(afmt_araw, AUDIO_SAMPLERATE);

	/* Define audio encoded format */
	media_format_create(&afmt_encoded);
	media_format_set_audio_mime(afmt_encoded, MEDIA_FORMAT_AMR_NB);
	media_format_set_audio_channel(afmt_encoded, AUDIO_CHANNEL);
	media_format_set_audio_samplerate(afmt_encoded, AUDIO_SAMPLERATE);

	/* Define audio encoded format for adaptive stream */
	media_format_create(&afmt_aenc);
	media_format_set_audio_mime(afmt_aenc, MEDIA_FORMAT_AAC);
	media_format_set_audio_channel(afmt_aenc, AUDIO_CHANNEL);
	media_format_set_audio_samplerate(afmt_aenc, AUDIO_SAMPLERATE);
	media_format_set_audio_aac_type(afmt_aenc, TRUE);

	/* Define mpegts stream format */
	media_format_create(&tsfmt);
	media_format_set_container_mime(tsfmt, MEDIA_FORMAT_CONTAINER_MPEG2TS);

	/* Define MP4 stream format */
	media_format_create(&qtfmt);
	media_format_set_container_mime(qtfmt, MEDIA_FORMAT_CONTAINER_MP4);
}

/**
 * @function		utc_capi_media_streamer_cleanup * @description		Called after each test.
 * @parameter		NA
 * @return		NA
 */
void utc_capi_media_streamer_cleanup(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_format_unref(vfmt_encoded);
	media_format_unref(vfmt_raw);
	media_format_unref(afmt_encoded);
	media_format_unref(afmt_raw);

	ret = media_streamer_unprepare(streamer);
	if (ret != MEDIA_STREAMER_ERROR_NONE)
		PRINT_UTC_LOG("fail to unprepare mediastreamer");

	ret = media_streamer_destroy(streamer);
	if (ret != MEDIA_STREAMER_ERROR_NONE)
		PRINT_UTC_LOG("fail to destroy mediastreamer");

	/* Clean Up Nodes */
	int i = g_node_counter - 1;
	for (; i >= 0; --i) {
		media_streamer_node_destroy(g_nodes[i]);
		g_nodes[i] = NULL;
	}
	g_node_counter = 0;

	if (file_path)
		free (file_path);
	if (file_path_playlist)
		free (file_path_playlist);
}

/* Application source callback */
void buffer_status_cb(media_streamer_node_h node,
                      media_streamer_custom_buffer_status_e status,
                      void *user_data) {

	if (status == MEDIA_STREAMER_CUSTOM_BUFFER_UNDERRUN) {

		/* Buffer status cb got underflow */
		char *test = strdup("This is buffer_status_cb test!");
		media_packet_h packet_to_push;
		media_packet_create_from_external_memory(vfmt_encoded,
		                      (void *)test, strlen(test), NULL, NULL, &packet_to_push);
		media_streamer_node_push_packet(node, packet_to_push);
		free(test);
		media_packet_destroy(packet_to_push);
	} else {
		/* Buffer status cb got overflow */
		media_streamer_node_push_packet(node, NULL);
	}
	buffer_status = status;
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

/* Application sink callback */
void new_buffer_cb(media_streamer_node_h node, void *user_data)
{
	char *received_data = NULL;
	media_packet_h packet = NULL;

	pull_packet_res = media_streamer_node_pull_packet(node, &packet);
	if (packet == NULL)
		return;

	media_packet_get_buffer_data_ptr(packet, (void **)&received_data);

	media_packet_destroy (packet);
	packet = NULL;

	if (received_data == NULL)
		return;

	free(received_data);
	received_data = NULL;

}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_create_p
 * @since_tizen		3.0
 * @description		Creates an instance of media streamer
 *			and passes the handle to the caller.
 */
int utc_media_streamer_create_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_streamer_h streamer2;

	ret = media_streamer_create(&streamer2);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_destroy(streamer2);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_create_n
 * @since_tizen		3.0
 * @description		Creates an instance of media streamer
 *			and passes the handle to the caller.
 */
int utc_media_streamer_create_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_create(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_prepare_p
 * @since_tizen		3.0
 * @description		Sets media streamer state
 *			to MEDIA_STREAMER_STATE_READY.
 */
int utc_media_streamer_prepare_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);
	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);
	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_prepare_n
 * @since_tizen		3.0
 * @description		Sets media streamer state
 *			to MEDIA_STREAMER_STATE_READY.
 */
int utc_media_streamer_prepare_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_prepare(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_unprepare_p
 * @since_tizen		3.0
 * @description		Sets media streamer state
 *			to MEDIA_STREAMER_STATE_IDLE.
 */
int utc_media_streamer_unprepare_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);
	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);
	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_unprepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_unprepare_n
 * @since_tizen		3.0
 * @description		Sets media streamer state
 *			to MEDIA_STREAMER_STATE_IDLE.
 */
int utc_media_streamer_unprepare_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);
	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);
	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_unprepare(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_play_p1
 * @since_tizen		3.0
 * @description		Sets media streamer state
 *			to MEDIA_STREAMER_STATE_PLAYING.
 */
int utc_media_streamer_play_p1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);
	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);
	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_play_p2
 * @since_tizen		3.0
 * @description		Play media streaming.
 */
int utc_media_streamer_play_p2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h rtp_bin = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_RTP, NULL, NULL, &rtp_bin);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(rtp_bin, NULL);
	APPEND_NODE(rtp_bin);
	ret =media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, RTP_VIDEO_PORT);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_HOST, "127.0.0.1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, rtp_bin);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);
	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_enc = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_ENCODER, NULL, vfmt_encoded, &video_enc);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_enc, NULL);
	APPEND_NODE(video_enc);
	ret = media_streamer_node_add(streamer, video_enc);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_pay = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_PAY, vfmt_encoded, NULL, &video_pay);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_pay, NULL);
	APPEND_NODE(video_pay);
	ret = media_streamer_node_add(streamer, video_pay);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	/* ------------------> LINKING ------------------> */
	ret = media_streamer_node_link(video_src, "src", video_enc, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_link(video_enc, "src", video_pay, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_link(video_pay, "src", rtp_bin, "video-in");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);
	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);


	media_streamer_h client = NULL;
	ret = media_streamer_create(&client);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h client_rtp_bin = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_RTP, NULL, NULL, &client_rtp_bin);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(client_rtp_bin, NULL);
	APPEND_NODE(client_rtp_bin);
	ret = media_streamer_node_set_param(client_rtp_bin, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, RTP_VIDEO_PORT);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_pad_format(client_rtp_bin, "video-in-rtp", vfmt_encoded);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(client, client_rtp_bin);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_depay = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_DEPAY, NULL, vfmt_encoded, &video_depay);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_depay, NULL);
	APPEND_NODE(video_depay);
	ret = media_streamer_node_add(client, video_depay);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_dec = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_DECODER, vfmt_encoded, NULL, &video_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_dec, NULL);
	APPEND_NODE(video_dec);
	ret = media_streamer_node_add(client, video_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);
	ret = media_streamer_node_add(client, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	/* ------------------> LINKING ------------------> */
	ret = media_streamer_node_link(video_depay, "src", video_dec, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_link(video_dec, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(client);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(client);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_unprepare(client);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_play_n1
 * @since_tizen		3.0
 * @description		Sets media streamer state
 *			to MEDIA_STREAMER_STATE_PLAYING.
 */
int utc_media_streamer_play_n1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_play(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_play_n2
 * @since_tizen		3.0
 * @description		Sets media streamer state
 *			to MEDIA_STREAMER_STATE_PLAYING.
 */
int utc_media_streamer_play_n2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(src, NULL);
	APPEND_NODE(src);

	ret = media_streamer_node_set_param(src, MEDIA_STREAMER_PARAM_URI, "/some/invalid/path");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	media_streamer_node_h sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(sink, NULL);
	APPEND_NODE(sink);

	ret = media_streamer_node_add(streamer, src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_add(streamer, sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(src, "src", sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_pause_p
 * @since_tizen		3.0
 * @description		Pauses mediastreamer and sets it
 *			state to MEDIA_STREAMER_STATE_PAUSED.
 */
int utc_media_streamer_pause_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);
	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);
	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_pause(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_pause_n
 * @since_tizen		3.0
 * @description		Pauses mediastreamer and sets it
 *			state to MEDIA_STREAMER_STATE_PAUSED.
 */
int utc_media_streamer_pause_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_pause(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_set_position_p
 * @since_tizen		3.0
 * @description		Changes playback position to the defined
 *			time value, asynchronously.
 */
int utc_media_streamer_set_position_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);

	ret = media_streamer_node_set_param(video_src,MEDIA_STREAMER_PARAM_URI, file_path);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_set_play_position(streamer, set_play_pos, 1, NULL, streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_set_position_n1
 * @since_tizen		3.0
 * @description		Changes playback position to the defined
 *			time value, asynchronously.
 */
int utc_media_streamer_set_position_n1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);

	ret = media_streamer_node_set_param(video_src,MEDIA_STREAMER_PARAM_URI, file_path);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_set_play_position(NULL, set_play_pos, 1, NULL, streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	wait_for_async(PLAY_TIME);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_set_position_n2
 * @since_tizen		3.0
 * @description		Changes playback position to the defined
 *			time value, asynchronously.
 */
int utc_media_streamer_set_position_n2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);

	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_set_play_position(streamer, set_play_pos, 1, NULL, streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NOT_SUPPORTED);
	wait_for_async(PLAY_TIME);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_get_position_p
 * @since_tizen		3.0
 * @description		Gets the current position in milliseconds.
 */
int utc_media_streamer_get_position_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	int time = 0;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);

	ret = media_streamer_node_set_param(video_src,MEDIA_STREAMER_PARAM_URI, file_path);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_get_play_position(streamer, &time);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_get_position_n
 * @since_tizen		3.0
 * @description		Gets the current position in milliseconds.
 */
int utc_media_streamer_get_position_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	int time = 0;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);

	ret = media_streamer_node_set_param(video_src,MEDIA_STREAMER_PARAM_URI, file_path);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_get_play_position(NULL, &time);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	wait_for_async(PLAY_TIME);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_get_duration_p1
 * @since_tizen		3.0
 * @description		Gets the duration of mediafile content in milliseconds.
 */
int utc_media_streamer_get_duration_p1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	int time = 0;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);

	ret = media_streamer_node_set_param(video_src,MEDIA_STREAMER_PARAM_URI, file_path);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_get_duration(streamer, &time);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_get_duration_p2
 * @since_tizen		3.0
 * @description		Gets the duration of mediafile content in milliseconds.
 */
int utc_media_streamer_get_duration_p2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	int time = 0;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);

	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_get_duration(streamer, &time);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_eq(time, -1);
	wait_for_async(PLAY_TIME);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_get_duration_n
 * @since_tizen		3.0
 * @description		Gets the duration of mediafile content in milliseconds.
 */
int utc_media_streamer_get_duration_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	int time = 0;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);

	ret = media_streamer_node_set_param(video_src,MEDIA_STREAMER_PARAM_URI, file_path);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_get_duration(NULL, &time);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	wait_for_async(PLAY_TIME);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_stop_p
 * @since_tizen		3.0
 * @description		Stops the media streamer.
 */
int utc_media_streamer_stop_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);
	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);
	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_stop(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_stop_n
 * @since_tizen		3.0
 * @description		Stops the media streamer.
 */
int utc_media_streamer_stop_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_stop(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_destroy_p1
 * @since_tizen		3.0
 * @description		Destroys media streamer.
 */
int utc_media_streamer_destroy_p1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_streamer_h streamer2;

	ret = media_streamer_create(&streamer2);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_destroy(streamer2);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_destroy_p2
 * @since_tizen		3.0
 * @description		Destroys media streamer.
 */
int utc_media_streamer_destroy_p2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_streamer_h streamer2;

	ret = media_streamer_create(&streamer2);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);
	ret = media_streamer_node_add(streamer2, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);
	ret = media_streamer_node_add(streamer2, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer2);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer2);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_unprepare(streamer2);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_destroy(streamer2);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_destroy_n
 * @since_tizen		3.0
 * @description		Destroys media streamer.
 */
int utc_media_streamer_destroy_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_destroy(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_get_state_p
 * @since_tizen		3.0
 * @description		Gets media streamer state.
 */
int utc_media_streamer_get_state_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);
	ret = media_streamer_node_add(streamer, video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_FAKE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);
	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(video_src, "src", video_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_pause(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	media_streamer_state_e state;
	ret = media_streamer_get_state(streamer,&state);

	assert_eq(state, MEDIA_STREAMER_STATE_PAUSED);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_get_state_n
 * @since_tizen		3.0
 * @description		Gets media streamer state.
 */
int utc_media_streamer_get_state_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_state_e state;

	ret = media_streamer_get_state(NULL, &state);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_create_src_p
 * @since_tizen		3.0
 * @description		Creates media streamer source node.
 */
int utc_media_streamer_node_create_src_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_create_src_n1
 * @since_tizen		3.0
 * @description		Creates media streamer source node.
 */
int utc_media_streamer_node_create_src_n1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_create_src_n2
 * @since_tizen		3.0
 * @description		Creates media streamer source node.
 */
int utc_media_streamer_node_create_src_n2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_NONE, &video_src);
	assert_eq(video_src, NULL);

	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_push_packet_p
 * @since_tizen		3.0
 * @description		Pushes packet into custom source node.
 */
int utc_media_streamer_node_push_packet_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h custom_src = NULL;
	media_packet_h packet = NULL;

	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &custom_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(custom_src, NULL);
	APPEND_NODE(custom_src);

	char *test = strdup("This is buffer_status_cb test!");

	media_packet_create_from_external_memory (vfmt_encoded, (void*)test, strlen(test), NULL, NULL, &packet);
	if(!packet) {
		free(test);
	}
	assert_neq(packet, NULL);

	ret = media_streamer_node_push_packet(custom_src, packet);
	media_packet_destroy(packet);
	free(test);

	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_push_packet_n1
 * @since_tizen		3.0
 * @description		Pushes packet into custom source node.
 */
int utc_media_streamer_node_push_packet_n1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_packet_h local_packet = NULL;

	media_streamer_node_h custom_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &custom_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(custom_src, NULL);
	APPEND_NODE(custom_src);

	char *test = strdup("This is buffer_status_cb test!");

	media_packet_create_from_external_memory(vfmt_encoded, (void*)test, strlen(test), NULL, NULL, &local_packet);
	if(!local_packet) {
		free(test);
	}
	assert_neq(local_packet, NULL);

	ret = media_streamer_node_push_packet(NULL, local_packet);

	media_packet_destroy(local_packet);
	free(test);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_push_packet_n2
 * @since_tizen		3.0
 * @description		Pushes packet into custom source node and gets buffer overflow.
 */
int utc_media_streamer_node_push_packet_n2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_packet_h packet = NULL;

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h app_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_sink, NULL);
	APPEND_NODE(app_sink);

	ret = media_streamer_node_set_pad_format(app_sink, "sink", vfmt_encoded);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_add(streamer, app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(app_src, "src", app_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_src_set_buffer_status_cb(app_src, buffer_status_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	int data_size = PACKET_SIZE * sizeof(char);
	char *data = (char *) malloc(data_size);
	media_packet_create_from_external_memory(vfmt_encoded, (void*)data, data_size, NULL, NULL, &packet);
	if(!packet)
		free(data);

	assert_neq(packet, NULL);

	int sent_packets_count = 0;
	while (sent_packets_count < MAX_PACKETS_TO_SEND) {
		++sent_packets_count;
		ret = media_streamer_node_push_packet(app_src, packet);
		if (buffer_status == MEDIA_STREAMER_CUSTOM_BUFFER_OVERFLOW)
			break;
	}
	printf("Send [%d] packets before overflow.", sent_packets_count);

	media_packet_destroy(packet);
	free(data);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_create_sink_p
 * @since_tizen		3.0
 * @description		Creates media streamer sink node.
 */
int utc_media_streamer_node_create_sink_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_create_sink_n1
 * @since_tizen		3.0
 * @description		Creates media streamer sink node.
 */
int utc_media_streamer_node_create_sink_n1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_create_sink_n2
 * @since_tizen		3.0
 * @description		Creates media streamer sink node.
 */
int utc_media_streamer_node_create_sink_n2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_NONE, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(video_sink, NULL);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_pull_packet_p
 * @since_tizen		3.0
 * @description		Pulls packet from custom sink node.
 */
int utc_media_streamer_node_pull_packet_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h app_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_sink, NULL);
	APPEND_NODE(app_sink);

	ret = media_streamer_node_set_pad_format(app_sink, "sink", vfmt_encoded);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_add(streamer, app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(app_src, "src", app_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_src_set_buffer_status_cb(app_src, buffer_status_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_sink_set_data_ready_cb(app_sink, new_buffer_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	/* End of stream */
	ret = media_streamer_node_push_packet(app_src, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_unprepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	assert_eq(pull_packet_res, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_pull_packet_n
 * @since_tizen		3.0
 * @description		Pulls packet from custom sink node.
 */
int utc_media_streamer_node_pull_packet_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_packet_h local_packet = NULL;

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h app_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_sink, NULL);
	APPEND_NODE(app_sink);

	ret = media_streamer_node_set_pad_format(app_sink, "sink", vfmt_encoded);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_add(streamer, app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(app_src, "src", app_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_src_set_buffer_status_cb(app_src, buffer_status_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_sink_set_data_ready_cb(app_sink, new_buffer_cb, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_pull_packet(NULL, &local_packet);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	ret = media_streamer_node_pull_packet(app_sink, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_unprepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_pull_packet(NULL, &local_packet);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	assert_eq(pull_packet_res, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_create_p
 * @since_tizen		3.0
 * @description		Creates media streamer node except
 *			MEDIA_STREAMER_NODE_TYPE_SRC and
 * 			MEDIA_STREAMER_NODE_TYPE_SINK nodes.
 */
int utc_media_streamer_node_create_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h audio_res = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_RESAMPLE, NULL, NULL, &audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(audio_res, NULL);
	APPEND_NODE(audio_res);

	media_streamer_node_h video_pay = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_PAY, vfmt_encoded, NULL, &video_pay);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_pay, NULL);
	APPEND_NODE(video_pay);

	media_streamer_node_h video_enc = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_ENCODER, NULL, vfmt_encoded, &video_enc);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_enc, NULL);
	APPEND_NODE(video_enc);

	media_streamer_node_h video_dec = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_DECODER, vfmt_encoded, NULL, &video_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_dec, NULL);
	APPEND_NODE(video_dec);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_create_n
 * @since_tizen		3.0
 * @description		Creates media streamer node except
 *			MEDIA_STREAMER_NODE_TYPE_SRC and
 * 			MEDIA_STREAMER_NODE_TYPE_SINK nodes.
 */
int utc_media_streamer_node_create_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_RESAMPLE, NULL, NULL, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_add_p
 * @since_tizen		3.0
 * @description		Adds node to media streamer.
 */
int utc_media_streamer_node_add_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h audio_res = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_ENCODER, NULL, afmt_encoded, &audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(audio_res, NULL);
	APPEND_NODE(audio_res);

	ret = media_streamer_node_add(streamer, audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_add_n
 * @since_tizen		3.0
 * @description		Adds node to media streamer.
 */
int utc_media_streamer_node_add_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_node_add(streamer, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_destroy_p
 * @since_tizen		3.0
 * @description		Destroys media streamer node.
 */
int utc_media_streamer_node_destroy_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h audio_res = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_RESAMPLE, NULL, NULL, &audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(audio_res, NULL);

	ret = media_streamer_node_destroy(audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_destroy_n
 * @since_tizen		3.0
 * @description		Destroys media streamer node.
 */
int utc_media_streamer_node_destroy_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_node_destroy(NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_remove_p
 * @since_tizen		3.0
 * @description		Removes media streamer node from streamer.
 */
int utc_media_streamer_node_remove_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h audio_res = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_RESAMPLE, NULL, NULL, &audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(audio_res, NULL);
	APPEND_NODE(audio_res);

	ret = media_streamer_node_add(streamer, audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_remove(streamer,audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_remove_n
 * @since_tizen		3.0
 * @description		Removes media streamer node from streamer.
 */
int utc_media_streamer_node_remove_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	ret = media_streamer_node_remove(streamer,NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_link_p
 * @since_tizen		3.0
 * @description		Links two media streamer nodes.
 */
int utc_media_streamer_node_link_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h audio_res = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_RESAMPLE, NULL, NULL, &audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(audio_res, NULL);
	APPEND_NODE(audio_res);

	ret = media_streamer_node_add(streamer, audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h audio_converter = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_CONVERTER, NULL, NULL, &audio_converter);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(audio_converter, NULL);
	APPEND_NODE(audio_converter);

	ret = media_streamer_node_add(streamer, audio_converter);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(audio_converter, "src", audio_res, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_link_n
 * @since_tizen		3.0
 * @description		Links two media streamer nodes.
 */
int utc_media_streamer_node_link_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h audio_res = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_RESAMPLE, NULL, NULL, &audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(audio_res, NULL);
	APPEND_NODE(audio_res);

	ret = media_streamer_node_add(streamer, audio_res);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h audio_converter = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_CONVERTER, NULL, NULL, &audio_converter);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(audio_converter, NULL);
	APPEND_NODE(audio_converter);

	ret = media_streamer_node_add(streamer, audio_converter);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(NULL, "src", audio_res, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_set_pad_format_p
 * @since_tizen		3.0
 * @description		Sets media format for pad of media streamer node.
 */
int utc_media_streamer_node_set_pad_format_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h app_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_sink, NULL);
	APPEND_NODE(app_sink);

	ret = media_streamer_node_add(streamer, app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_set_pad_format(app_sink, "sink", vfmt_encoded);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_set_pad_format_n
 * @since_tizen		3.0
 * @description		Sets media format for pad of media streamer node.
 */
int utc_media_streamer_node_set_pad_format_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h app_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_sink, NULL);
	APPEND_NODE(app_sink);

	ret = media_streamer_node_add(streamer, app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_set_pad_format(app_sink, "sink", NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_get_pad_format_p
 * @since_tizen		3.0
 * @description		Gets media format for pad of media streamer node.
 */
int utc_media_streamer_node_get_pad_format_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	int width_init, height_init, frame_rate_init;
	media_format_mimetype_e mime_init = MEDIA_FORMAT_H263;

	ret = media_format_get_video_info(vfmt_encoded, &mime_init, &width_init, &height_init, NULL, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_format_get_video_frame_rate(vfmt_encoded, &frame_rate_init);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_set_pad_format(app_src, "src", vfmt_encoded);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h app_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_sink, NULL);
	APPEND_NODE(app_sink);

	ret = media_streamer_node_add(streamer, app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_set_pad_format(app_sink, "sink", vfmt_encoded);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(app_src, "src", app_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_format_h pad_fmt = NULL;
	int width, height, frame_rate;
	media_format_mimetype_e mime = MEDIA_FORMAT_MAX;

	ret = media_streamer_node_get_pad_format(app_src, "src", &pad_fmt);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(pad_fmt, NULL);

	ret = media_format_get_video_info(pad_fmt, &mime, &width, &height, NULL, NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_format_get_video_frame_rate(pad_fmt, &frame_rate);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	assert_neq(mime, EXTREMUM);
	assert_neq(width, EXTREMUM);
	assert_neq(height, EXTREMUM);
	assert_neq(frame_rate, EXTREMUM);

	assert_eq(mime_init, mime);
	assert_eq(width_init, width);
	assert_eq(height_init, height);
	assert_eq(frame_rate_init, frame_rate);

	media_format_unref(pad_fmt);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_get_pad_format_n1
 * @since_tizen		3.0
 * @description		Gets media format for pad of media streamer node.
 */
int utc_media_streamer_node_get_pad_format_n1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_format_h pad_fmt = NULL;

	ret = media_streamer_node_get_pad_format(app_src, "sink", &pad_fmt);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);

	media_format_unref(pad_fmt);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_get_pad_format_n2
 * @since_tizen		3.0
 * @description		Gets media format for pad of media streamer node.
 */
int utc_media_streamer_node_get_pad_format_n2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_format_h pad_fmt = NULL;

	ret = media_streamer_node_get_pad_format(NULL, "src", &pad_fmt);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	ret = media_streamer_node_get_pad_format(app_src, NULL, &pad_fmt);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	ret = media_streamer_node_get_pad_format(app_src, "src", NULL);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	assert_eq(pad_fmt, NULL);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_get_pad_format_n3
 * @since_tizen		3.0
 * @description		Gets media format for pad of media streamer node.
 */
int utc_media_streamer_node_get_pad_format_n3(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_format_h pad_fmt = NULL;

	ret = media_streamer_node_get_pad_format(app_src, "src", &pad_fmt);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);

	assert_eq(pad_fmt, NULL);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_get_pad_format_n4
 * @since_tizen		3.0
 * @description		Gets media format for pad of media streamer node.
 */
int utc_media_streamer_node_get_pad_format_n4(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h app_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_sink, NULL);
	APPEND_NODE(app_sink);

	ret = media_streamer_node_add(streamer, app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(app_src, "src", app_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_format_h pad_fmt = NULL;

	ret = media_streamer_node_get_pad_format(app_sink, "sink", &pad_fmt);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);

	assert_eq(pad_fmt, NULL);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_get_pad_format_n5
 * @since_tizen		3.0
 * @description		Gets media format for pad of media streamer node.
 */
int utc_media_streamer_node_get_pad_format_n5(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h app_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CUSTOM, &app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_src, NULL);
	APPEND_NODE(app_src);

	ret = media_streamer_node_add(streamer, app_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h app_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(app_sink, NULL);
	APPEND_NODE(app_sink);

	ret = media_streamer_node_add(streamer, app_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_node_link(app_src, "src", app_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_format_h pad_fmt = NULL;

	ret = media_streamer_node_get_pad_format(app_sink, "sink", &pad_fmt);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(pad_fmt, NULL);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_pad_name_p
 * @since_tizen		3.0
 * @description		Gets names of media streamer node pads.
 */
int utc_media_streamer_node_get_pad_name_p(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_pay = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_PAY, vfmt_encoded, NULL, &video_pay);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_pay, NULL);
	APPEND_NODE(video_pay);

	ret = media_streamer_node_add(streamer, video_pay);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	char **src_pad_name = NULL;
	int src_pad_num = 0;
	char **sink_pad_name = NULL;
	int sink_pad_num = 0;

	ret = media_streamer_node_get_pad_name(video_pay,&src_pad_name,&src_pad_num,&sink_pad_name,&sink_pad_num);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	assert_neq(src_pad_name, NULL);
	assert_neq(src_pad_num, 0);
	assert_neq(sink_pad_name, NULL);
	assert_neq(sink_pad_num, 0);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_pad_name_n
 * @since_tizen		3.0
 * @description		Gets names of media streamer node pads.
 */
int utc_media_streamer_node_get_pad_name_n(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_pay = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_PAY, vfmt_encoded, NULL, &video_pay);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_pay, NULL);
	APPEND_NODE(video_pay);

	ret = media_streamer_node_add(streamer, video_pay);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	char **src_pad_name = NULL;
	int src_pad_num = 0;
	char **sink_pad_name = NULL;
	int sink_pad_num = 0;

	ret = media_streamer_node_get_pad_name(NULL,&src_pad_name,&src_pad_num,&sink_pad_name,&sink_pad_num);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);

	assert_eq(src_pad_name, NULL);
	assert_eq(src_pad_num, 0);
	assert_eq(sink_pad_name, NULL);
	assert_eq(sink_pad_num, 0);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_set_params_p1
 * @since_tizen		3.0
 * @description		Sets list of parameters for
 *			media streamer node.
 */
int utc_media_streamer_node_set_params_p1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h http_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_HTTP, &http_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(http_src, NULL);
	APPEND_NODE(http_src);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, "true");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_URI, "/home");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_USER_AGENT, "bob");
	ret = media_streamer_node_set_params(http_src, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);

	media_streamer_node_h udp_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_RTSP, &udp_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_src, NULL);
	APPEND_NODE(udp_src);

	params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_PORT, "5000");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_IP_ADDRESS, "127.0.0.1");
	ret = media_streamer_node_set_params(udp_src, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);

	media_streamer_node_h udp_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_RTSP, &udp_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_sink, NULL);
	APPEND_NODE(udp_sink);

	params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_PORT, "5004");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_HOST, "localhost");
	ret = media_streamer_node_set_params(udp_sink, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_set_params_p2
 * @since_tizen		3.0
 * @description		Sets list of parameters for
 *			media streamer node.
 */
int utc_media_streamer_node_set_params_p2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h rtp_node= NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_RTP, NULL, NULL, &rtp_node);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(rtp_node, NULL);
	APPEND_NODE(rtp_node);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, "5005");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_AUDIO_IN_PORT, "5006");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, "6005");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_AUDIO_OUT_PORT, "6006");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_HOST, "localhost");
	ret = media_streamer_node_set_params(rtp_node, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);

	return 0;
}

//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_set_params_p3
 * @since_tizen		3.0
 * @description		Sets list of parameters for
 *			media streamer node.
 */
int utc_media_streamer_node_set_params_p3(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_CLOCK_SYNCHRONIZED, "true");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_ROTATE, "1");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_FLIP, "2");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_DISPLAY_GEOMETRY_METHOD, "1");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_USE_TBM, "false");

	ret = media_streamer_node_set_params(video_sink, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);

	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)      //Starts MOBILE
//& purpose: A purpose of a first positive TC.
/**
 * @testcase		utc_media_streamer_node_set_params_p4
 * @since_tizen		3.0
 * @description		Sets list of parameters for
 *			media streamer node.
 */
int utc_media_streamer_node_set_params_p4(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_capture = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CAMERA, &video_capture);
	if (!g_system_info && ret == MEDIA_STREAMER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, MEDIA_STREAMER_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_capture, NULL);
	APPEND_NODE(video_capture);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_CAMERA_ID, CAMERA_ID);
	ret = media_streamer_node_set_params(video_capture, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);

	return 0;
}
#endif   //MOBILE  //End MOBILE

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_set_params_n1
 * @since_tizen		3.0
 * @description		Sets list of parameters for
 *			media streamer node.
 */
int utc_media_streamer_node_set_params_n1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h udp_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &udp_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_src, NULL);
	APPEND_NODE(udp_src);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_PORT, "5000");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_IP_ADDRESS, "127.0.0.1");
	ret = media_streamer_node_set_params(udp_src, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	bundle_free(params);
	params = NULL;

	media_streamer_node_h udp_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &udp_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_sink, NULL);
	APPEND_NODE(udp_sink);

	params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_PORT, "5004");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_HOST, "localhost");
	ret = media_streamer_node_set_params(udp_sink, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	bundle_free(params);
	params = NULL;

	media_streamer_node_h rtp_node= NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_PAY, vfmt_encoded, NULL, &rtp_node);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(rtp_node, NULL);
	APPEND_NODE(rtp_node);

	params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, "5005");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_AUDIO_IN_PORT, "5006");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, "6005");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_AUDIO_OUT_PORT, "6006");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_HOST, "localhost");
	ret = media_streamer_node_set_params(rtp_node, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	bundle_free(params);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_set_params_n2
 * @since_tizen		3.0
 * @description		Sets list of parameters for
 *			media streamer node.
 */
int utc_media_streamer_node_set_params_n2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_HTTP, &src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(src, NULL);
	APPEND_NODE(src);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_CAMERA_ID, CAMERA_ID);
	ret = media_streamer_node_set_params(src, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	bundle_free(params);

	return 0;
}

//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_set_params_n3
 * @since_tizen		3.0
 * @description		Sets list of parameters for
 *			media streamer node.
 */
int utc_media_streamer_node_set_params_n3(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_CUSTOM, &sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(sink, NULL);
	APPEND_NODE(sink);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_ROTATE, "0");
	ret = media_streamer_node_set_params(sink, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	bundle_add_str(params, MEDIA_STREAMER_PARAM_ROTATE, "1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	bundle_add_str(params, MEDIA_STREAMER_PARAM_FLIP, "2");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	bundle_add_str(params, MEDIA_STREAMER_PARAM_DISPLAY_GEOMETRY_METHOD, "1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	bundle_free(params);

	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)      //Starts MOBILE
//& purpose: A purpose of a first negative TC.
/**
 * @testcase		utc_media_streamer_node_set_params_n4
 * @since_tizen		3.0
 * @description		Sets list of parameters for
 *			media streamer node.
 */
int utc_media_streamer_node_set_params_n4(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h http_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CAMERA, &http_src);
	if (!g_system_info && ret == MEDIA_STREAMER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, MEDIA_STREAMER_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(http_src, NULL);
	APPEND_NODE(http_src);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, "true");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_URI, "/home");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_USER_AGENT, "bob");
	ret = media_streamer_node_set_params(http_src, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_PARAMETER);
	bundle_free(params);

	return 0;
}
#endif   //MOBILE  //End MOBILE

/**
 * @testcase		utc_media_streamer_node_get_params_p1
 * @since_tizen		3.0
 * @description		Gets list of parameters of
 *			media streamer node.
 */
int utc_media_streamer_node_get_params_p1(void)
{

	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *string_ret = NULL;

	media_streamer_node_h udp_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_RTSP, &udp_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_src, NULL);
	APPEND_NODE(udp_src);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_PORT, "5000");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_IP_ADDRESS, "127.0.0.1");
	ret = media_streamer_node_set_params(udp_src, params);
	bundle_free(params);
	params = NULL;

	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_params(udp_src, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_get_str (params, MEDIA_STREAMER_PARAM_PORT, &string_ret);
	assert(!strcmp(string_ret, "5000"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_IP_ADDRESS, &string_ret);
	assert(!strcmp(string_ret, "127.0.0.1"));
	bundle_free(params);
	params = NULL;

	media_streamer_node_h udp_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_RTSP, &udp_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_sink, NULL);
	APPEND_NODE(udp_sink);

	params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_PORT, "5004");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_HOST, "localhost");
	ret = media_streamer_node_set_params(udp_sink, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);
	params = NULL;

	ret = media_streamer_node_get_params(udp_sink, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_get_str (params, MEDIA_STREAMER_PARAM_PORT, &string_ret);
	assert(!strcmp(string_ret, "5004"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_HOST, &string_ret);
	assert(!strcmp(string_ret, "localhost"));
	bundle_free(params);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_params_p2
 * @since_tizen		3.0
 * @description		Gets list of parameters of
 *			media streamer node.
 */
int utc_media_streamer_node_get_params_p2(void)
{

	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *string_ret = NULL;

	media_streamer_node_h rtp_node= NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_RTP, NULL, NULL, &rtp_node);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(rtp_node, NULL);
	APPEND_NODE(rtp_node);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, "5005");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_AUDIO_IN_PORT, "5006");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, "6005");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_AUDIO_OUT_PORT, "6006");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_HOST, "localhost");
	ret = media_streamer_node_set_params(rtp_node, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);
	params = NULL;

	ret = media_streamer_node_get_params(rtp_node, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_get_str (params, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, &string_ret);
	assert(!strcmp(string_ret, "5005"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_AUDIO_IN_PORT, &string_ret);
	assert(!strcmp(string_ret, "5006"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, &string_ret);
	assert(!strcmp(string_ret, "6005"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_AUDIO_OUT_PORT, &string_ret);
	assert(!strcmp(string_ret, "6006"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_HOST, &string_ret);
	assert(!strcmp(string_ret, "localhost"));
	bundle_free(params);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_params_p3
 * @since_tizen		3.0
 * @description		Gets list of parameters of
 *			media streamer node.
 */
int utc_media_streamer_node_get_params_p3(void)
{

	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *string_ret = NULL;

	media_streamer_node_h http_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_HTTP, &http_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(http_src, NULL);
	APPEND_NODE(http_src);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, "true");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_URI, "/home");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_USER_AGENT, "bob");
	ret = media_streamer_node_set_params(http_src, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);
	params = NULL;

	ret = media_streamer_node_get_params(http_src, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_get_str (params, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, &string_ret);
	assert(!strcmp(string_ret, "true"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_URI, &string_ret);
	assert(!strcmp(string_ret, "/home"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_USER_AGENT, &string_ret);
	assert(!strcmp(string_ret, "bob"));
	bundle_free(params);
	params = NULL;

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_params_p4
 * @since_tizen		3.0
 * @description		Gets list of parameters of
 *			media streamer node.
 */
int utc_media_streamer_node_get_params_p4(void)
{

	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *string_ret = NULL;

	media_streamer_node_h video_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_CLOCK_SYNCHRONIZED, "true");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_ROTATE, "1");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_FLIP, "2");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_DISPLAY_GEOMETRY_METHOD, "1");
	bundle_add_str(params, MEDIA_STREAMER_PARAM_USE_TBM, "false");

	ret = media_streamer_node_set_params(video_sink, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);
	params = NULL;

	ret = media_streamer_node_get_params(video_sink, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_get_str (params, MEDIA_STREAMER_PARAM_CLOCK_SYNCHRONIZED, &string_ret);
	assert(!strcmp(string_ret, "true"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_ROTATE, &string_ret);
	assert(!strcmp(string_ret, "1"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_FLIP, &string_ret);
	assert(!strcmp(string_ret, "2"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_DISPLAY_GEOMETRY_METHOD, &string_ret);
	assert(!strcmp(string_ret, "1"));
	bundle_get_str (params, MEDIA_STREAMER_PARAM_USE_TBM, &string_ret);
	assert(!strcmp(string_ret, "false"));

	bundle_free(params);

	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)      //Starts MOBILE
/**
 * @testcase		utc_media_streamer_node_get_params_p5
 * @since_tizen		3.0
 * @description		Gets list of parameters of
 *			media streamer node.
 */
int utc_media_streamer_node_get_params_p5(void)
{

	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *string_ret = NULL;

	media_streamer_node_h video_capture = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CAMERA, &video_capture);
	if (!g_system_info && ret == MEDIA_STREAMER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, MEDIA_STREAMER_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_capture, NULL);
	APPEND_NODE(video_capture);

	bundle *params = bundle_create();
	bundle_add_str(params, MEDIA_STREAMER_PARAM_CAMERA_ID, CAMERA_ID);
	ret = media_streamer_node_set_params(video_capture, params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_free(params);
	params = NULL;
	ret = media_streamer_node_get_params(video_capture, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_get_str (params, MEDIA_STREAMER_PARAM_CAMERA_ID, &string_ret);
	bundle_free(params);

	return 0;
}
#endif   //MOBILE  //End MOBILE

/**
 * @testcase		utc_media_streamer_node_get_params_n1
 * @since_tizen		3.0
 * @description		Gets list of parameters of
 *			media streamer node.
 */
int utc_media_streamer_node_get_params_n1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *string_ret = NULL;
	int bundle_ret = BUNDLE_ERROR_NONE;
	bundle *params = NULL;

	media_streamer_node_h video_test = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_test);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_test, NULL);
	APPEND_NODE(video_test);

	ret = media_streamer_node_get_params(video_test, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_PORT, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_IP_ADDRESS, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_free(params);
	params = NULL;

	media_streamer_node_h video_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_get_params(video_sink, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_PORT, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_HOST, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_free(params);
	params = NULL;

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_params_n2
 * @since_tizen		3.0
 * @description		Gets list of parameters of
 *			media streamer node.
 */
int utc_media_streamer_node_get_params_n2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *string_ret = NULL;
	int bundle_ret = BUNDLE_ERROR_NONE;
	bundle *params = NULL;

	media_streamer_node_h http_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_HTTP, &http_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(http_src, NULL);
	APPEND_NODE(http_src);

	ret = media_streamer_node_get_params(http_src, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_CAMERA_ID, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_free(params);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_params_n3
 * @since_tizen		3.0
 * @description		Gets list of parameters of
 *			media streamer node.
 */
int utc_media_streamer_node_get_params_n3(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *string_ret = NULL;
	int bundle_ret = BUNDLE_ERROR_NONE;
	bundle *params = NULL;

	media_streamer_node_h audio_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_AUDIO, &audio_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(audio_sink, NULL);
	APPEND_NODE(audio_sink);

	ret = media_streamer_node_get_params(audio_sink, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_AUDIO_IN_PORT, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_AUDIO_OUT_PORT, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_HOST, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_free(params);
	params = NULL;

	media_streamer_node_h audio_test= NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_AUDIO_TEST, &audio_test);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(audio_test, NULL);
	APPEND_NODE(audio_test);

	ret = media_streamer_node_get_params(audio_test, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_CLOCK_SYNCHRONIZED, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_ROTATE, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_FLIP, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_DISPLAY_GEOMETRY_METHOD, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_USE_TBM, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_free(params);

	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)      //Starts MOBILE
/**
 * @testcase		utc_media_streamer_node_get_params_n4
 * @since_tizen		3.0
 * @description		Gets list of parameters of
 *			media streamer node.
 */
int utc_media_streamer_node_get_params_n4(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *string_ret = NULL;
	int bundle_ret = BUNDLE_ERROR_NONE;
	bundle *params = NULL;

	media_streamer_node_h video_capture = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CAMERA, &video_capture);
	if (!g_system_info && ret == MEDIA_STREAMER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, MEDIA_STREAMER_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_capture, NULL);
	APPEND_NODE(video_capture);

	ret = media_streamer_node_get_params(video_capture, &params);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_URI, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_ret = bundle_get_str (params, MEDIA_STREAMER_PARAM_USER_AGENT, &string_ret);
	assert_eq(bundle_ret, BUNDLE_ERROR_KEY_NOT_AVAILABLE);
	bundle_free(params);

	return 0;
}
#endif   //MOBILE  //End MOBILE

/**
 * @testcase		utc_media_streamer_node_set_param_p1
 * @since_tizen		3.0
 * @description		Sets a single parameter for
 *			media streamer node.
 */
int utc_media_streamer_node_set_param_p1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h http_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_HTTP, &http_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(http_src, NULL);
	APPEND_NODE(http_src);

	ret = media_streamer_node_set_param(http_src, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, "true");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(http_src, MEDIA_STREAMER_PARAM_URI, "/home");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(http_src, MEDIA_STREAMER_PARAM_USER_AGENT, "bob");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h udp_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_RTSP, &udp_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_src, NULL);
	APPEND_NODE(udp_src);

	ret = media_streamer_node_set_param(udp_src, MEDIA_STREAMER_PARAM_PORT, "5000");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(udp_src, MEDIA_STREAMER_PARAM_IP_ADDRESS, "127.0.0.1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	media_streamer_node_h udp_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_RTSP, &udp_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_sink, NULL);
	APPEND_NODE(udp_sink);

	ret = media_streamer_node_set_param(udp_sink, MEDIA_STREAMER_PARAM_PORT, "5004");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(udp_sink, MEDIA_STREAMER_PARAM_HOST, "localhost");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_set_param_p2
 * @since_tizen		3.0
 * @description		Sets a single parameter for
 *			media streamer node.
 */
int utc_media_streamer_node_set_param_p2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h rtp_bin= NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_RTP, NULL, NULL, &rtp_bin);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(rtp_bin, NULL);
	APPEND_NODE(rtp_bin);

	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, "5005");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_AUDIO_IN_PORT, "5006");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, "6005");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_AUDIO_OUT_PORT, "6006");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_HOST, "localhost");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_set_param_p3
 * @since_tizen		3.0
 * @description		Sets a single parameter for
 *			media streamer node.
 */
int utc_media_streamer_node_set_param_p3(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_CLOCK_SYNCHRONIZED, "true");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_ROTATE, "0");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_FLIP, "1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_DISPLAY_GEOMETRY_METHOD, "1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_USE_TBM, "false");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)      //Starts MOBILE
/**
 * @testcase		utc_media_streamer_node_set_param_p4
 * @since_tizen		3.0
 * @description		Sets a single parameter for
 *			media streamer node.
 */
int utc_media_streamer_node_set_param_p4(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_capture = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CAMERA, &video_capture);
	if (!g_system_info && ret == MEDIA_STREAMER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, MEDIA_STREAMER_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_capture, NULL);
	APPEND_NODE(video_capture);

	ret = media_streamer_node_set_param(video_capture, MEDIA_STREAMER_PARAM_CAMERA_ID, CAMERA_ID);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	return 0;
}
#endif   //MOBILE  //End MOBILE

/**
 * @testcase		utc_media_streamer_node_set_param_n1
 * @since_tizen		3.0
 * @description		Sets a single parameter for
 *			media streamer node.
 */
int utc_media_streamer_node_set_param_n1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h udp_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &udp_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_src, NULL);
	APPEND_NODE(udp_src);

	ret = media_streamer_node_set_param(udp_src, MEDIA_STREAMER_PARAM_PORT, "5000");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(udp_src, MEDIA_STREAMER_PARAM_IP_ADDRESS, "127.0.0.1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);

	media_streamer_node_h udp_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &udp_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_sink, NULL);
	APPEND_NODE(udp_sink);

	ret = media_streamer_node_set_param(udp_sink, MEDIA_STREAMER_PARAM_PORT, "5004");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(udp_sink, MEDIA_STREAMER_PARAM_HOST, "localhost");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);

	media_streamer_node_h rtp_bin= NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_PAY, vfmt_encoded, NULL, &rtp_bin);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(rtp_bin, NULL);
	APPEND_NODE(rtp_bin);

	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, "5005");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_AUDIO_IN_PORT, "5006");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, "6005");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_AUDIO_OUT_PORT, "6006");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_set_param_n2
 * @since_tizen		3.0
 * @description		Sets a single parameter for
 *			media streamer node.
 */
int utc_media_streamer_node_set_param_n2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h video_sink= NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_CONVERTER, NULL, NULL, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_CLOCK_SYNCHRONIZED, "true");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_VISIBLE, "false");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_ROTATE, "1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_FLIP, "1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_DISPLAY_GEOMETRY_METHOD, "1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_USE_TBM, "false");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_set_param_n3
 * @since_tizen		3.0
 * @description		Sets a single parameter for
 *			media streamer node.
 */
int utc_media_streamer_node_set_param_n3(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_HTTP, &src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(src, NULL);
	APPEND_NODE(src);

	ret = media_streamer_node_set_param(src, MEDIA_STREAMER_PARAM_CAMERA_ID, CAMERA_ID);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(src, MEDIA_STREAMER_PARAM_CAPTURE_WIDTH, "640");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(src, MEDIA_STREAMER_PARAM_CAPTURE_HEIGHT, "480");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);

	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)      //Starts MOBILE
/**
 * @testcase		utc_media_streamer_node_set_param_n4
 * @since_tizen		3.0
 * @description		Sets a single parameter for
 *			media streamer node.
 */
int utc_media_streamer_node_set_param_n4(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h http_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CAMERA, &http_src);
	if (!g_system_info && ret == MEDIA_STREAMER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, MEDIA_STREAMER_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(http_src, NULL);
	APPEND_NODE(http_src);

	ret = media_streamer_node_set_param(http_src, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, "true");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(http_src, MEDIA_STREAMER_PARAM_URI, "/home");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	ret = media_streamer_node_set_param(http_src, MEDIA_STREAMER_PARAM_USER_AGENT, "bob");
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);


	return 0;
}
#endif   //MOBILE  //End MOBILE

/**
 * @testcase		utc_media_streamer_node_get_param_p1
 * @since_tizen		3.0
 * @description		Gets a parameter value of
 *			media streamer node.
 */
int utc_media_streamer_node_get_param_p1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *param_value = NULL;

	media_streamer_node_h http_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_HTTP, &http_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(http_src, NULL);
	APPEND_NODE(http_src);

	ret = media_streamer_node_set_param(http_src, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, "true");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(http_src, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "true"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(http_src, MEDIA_STREAMER_PARAM_URI, "/home");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(http_src, MEDIA_STREAMER_PARAM_URI, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "/home"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(http_src, MEDIA_STREAMER_PARAM_USER_AGENT, "bob");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(http_src, MEDIA_STREAMER_PARAM_USER_AGENT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "bob"));
	free(param_value);
	param_value = NULL;

	media_streamer_node_h udp_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_RTSP, &udp_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_src, NULL);
	APPEND_NODE(udp_src);

	ret = media_streamer_node_set_param(udp_src, MEDIA_STREAMER_PARAM_PORT, "5000");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(udp_src, MEDIA_STREAMER_PARAM_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "5000"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(udp_src, MEDIA_STREAMER_PARAM_IP_ADDRESS, "127.0.0.1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(udp_src, MEDIA_STREAMER_PARAM_IP_ADDRESS, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "127.0.0.1"));
	free(param_value);
	param_value = NULL;

	media_streamer_node_h udp_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_RTSP, &udp_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(udp_sink, NULL);
	APPEND_NODE(udp_sink);

	ret = media_streamer_node_set_param(udp_sink, MEDIA_STREAMER_PARAM_PORT, "5004");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(udp_sink, MEDIA_STREAMER_PARAM_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "5004"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(udp_sink, MEDIA_STREAMER_PARAM_HOST, "localhost");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(udp_sink, MEDIA_STREAMER_PARAM_HOST, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "localhost"));
	free(param_value);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_param_p2
 * @since_tizen		3.0
 * @description		Gets a parameter value of
 *			media streamer node.
 */
int utc_media_streamer_node_get_param_p2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *param_value = NULL;

	media_streamer_node_h rtp_bin= NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_RTP, NULL, NULL, &rtp_bin);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(rtp_bin, NULL);
	APPEND_NODE(rtp_bin);

	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, "5005");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(rtp_bin, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "5005"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_AUDIO_IN_PORT, "5006");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(rtp_bin, MEDIA_STREAMER_PARAM_AUDIO_IN_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "5006"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, "6005");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(rtp_bin, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "6005"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_AUDIO_OUT_PORT, "6006");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(rtp_bin, MEDIA_STREAMER_PARAM_AUDIO_OUT_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "6006"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(rtp_bin, MEDIA_STREAMER_PARAM_HOST, "localhost");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(rtp_bin, MEDIA_STREAMER_PARAM_HOST, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "localhost"));
	free(param_value);
	param_value = NULL;

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_param_p3
 * @since_tizen		3.0
 * @description		Gets a parameter value of
 *			media streamer node.
 */
int utc_media_streamer_node_get_param_p3(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *param_value = NULL;

	media_streamer_node_h video_sink= NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_CLOCK_SYNCHRONIZED, "true");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(video_sink, MEDIA_STREAMER_PARAM_CLOCK_SYNCHRONIZED, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "true"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_ROTATE, "0");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(video_sink, MEDIA_STREAMER_PARAM_ROTATE, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "0"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_FLIP, "1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(video_sink, MEDIA_STREAMER_PARAM_FLIP, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "1"));
	free(param_value);
	param_value = NULL;

	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_DISPLAY_GEOMETRY_METHOD, "1");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(video_sink, MEDIA_STREAMER_PARAM_DISPLAY_GEOMETRY_METHOD, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "1"));
	free(param_value);

	ret = media_streamer_node_set_param(video_sink, MEDIA_STREAMER_PARAM_USE_TBM, "false");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(video_sink, MEDIA_STREAMER_PARAM_USE_TBM, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, "false"));
	free(param_value);
	param_value = NULL;

	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)      //Starts MOBILE
/**
 * @testcase		utc_media_streamer_node_get_param_p4
 * @since_tizen		3.0
 * @description		Gets a parameter value of
 *			media streamer node.
 */
int utc_media_streamer_node_get_param_p4(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *param_value = NULL;

	media_streamer_node_h video_capture = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CAMERA, &video_capture);
	if (!g_system_info && ret == MEDIA_STREAMER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, MEDIA_STREAMER_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_capture, NULL);
	APPEND_NODE(video_capture);

	ret = media_streamer_node_set_param(video_capture, MEDIA_STREAMER_PARAM_CAMERA_ID, CAMERA_ID);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(video_capture, MEDIA_STREAMER_PARAM_CAMERA_ID, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	PRINT_UTC_LOG("param_value:%s", param_value);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, CAMERA_ID));
	free(param_value);

	return 0;
}
#endif   //MOBILE  //End MOBILE

/**
 * @testcase		utc_media_streamer_node_get_param_p5
 * @since_tizen		3.0
 * @description		Gets a parameter value of
 *			media streamer node.
 */
int utc_media_streamer_node_get_param_p5(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *param_value = NULL;

	media_streamer_node_h adaptive_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_ADAPTIVE, &adaptive_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(adaptive_src, NULL);
	APPEND_NODE(adaptive_src);

	ret = media_streamer_node_set_param(adaptive_src, MEDIA_STREAMER_PARAM_URI, file_path);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_get_param(adaptive_src, MEDIA_STREAMER_PARAM_URI, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(param_value, NULL);
	assert(!strcmp(param_value, file_path));
	free(param_value);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_param_n1
 * @since_tizen		3.0
 * @description		Gets a parameter value of
 *			media streamer node.
 */
int utc_media_streamer_node_get_param_n1(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *param_value = NULL;

	media_streamer_node_h video_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_VIDEO_TEST, &video_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_src, NULL);
	APPEND_NODE(video_src);

	ret = media_streamer_node_get_param(video_src, MEDIA_STREAMER_PARAM_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_src, MEDIA_STREAMER_PARAM_IP_ADDRESS, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);

	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_sink, NULL);
	APPEND_NODE(video_sink);

	ret = media_streamer_node_get_param(video_sink, MEDIA_STREAMER_PARAM_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_sink, MEDIA_STREAMER_PARAM_HOST, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_param_n2
 * @since_tizen		3.0
 * @description		Gets a parameter value of
 *			media streamer node.
 */
int utc_media_streamer_node_get_param_n2(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *param_value = NULL;

	media_streamer_node_h http_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_HTTP, &http_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(http_src, NULL);
	APPEND_NODE(http_src);

	ret = media_streamer_node_get_param(http_src, MEDIA_STREAMER_PARAM_CAMERA_ID, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);

	return 0;
}

/**
 * @testcase		utc_media_streamer_node_get_param_n3
 * @since_tizen		3.0
 * @description		Gets a parameter value of
 *			media streamer node.
 */
int utc_media_streamer_node_get_param_n3(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *param_value = NULL;


	media_streamer_node_h video_pay = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_PAY, vfmt_encoded, NULL, &video_pay);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_pay, NULL);
	APPEND_NODE(video_pay);

	ret = media_streamer_node_get_param(video_pay, MEDIA_STREAMER_PARAM_VIDEO_IN_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_pay, MEDIA_STREAMER_PARAM_AUDIO_IN_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_pay, MEDIA_STREAMER_PARAM_VIDEO_OUT_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_pay, MEDIA_STREAMER_PARAM_AUDIO_OUT_PORT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_pay, MEDIA_STREAMER_PARAM_HOST, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);

	media_streamer_node_h video_converter = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_CONVERTER, NULL, NULL, &video_converter);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_converter, NULL);
	APPEND_NODE(video_converter);

	ret = media_streamer_node_get_param(video_converter, MEDIA_STREAMER_PARAM_CLOCK_SYNCHRONIZED, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_converter, MEDIA_STREAMER_PARAM_ROTATE, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_converter, MEDIA_STREAMER_PARAM_FLIP, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_converter, MEDIA_STREAMER_PARAM_DISPLAY_GEOMETRY_METHOD, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_converter, MEDIA_STREAMER_PARAM_USE_TBM, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);

	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)      //Starts MOBILE
/**
 * @testcase		utc_media_streamer_node_get_param_n4
 * @since_tizen		3.0
 * @description		Gets a parameter value of
 *			media streamer node.
 */
int utc_media_streamer_node_get_param_n4(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	char *param_value = NULL;

	media_streamer_node_h video_capture = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_CAMERA, &video_capture);
	if (!g_system_info && ret == MEDIA_STREAMER_ERROR_NOT_SUPPORTED) {
		assert_eq(ret, MEDIA_STREAMER_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	assert_neq(video_capture, NULL);
	APPEND_NODE(video_capture);

	ret = media_streamer_node_get_param(video_capture, MEDIA_STREAMER_PARAM_IS_LIVE_STREAM, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_capture, MEDIA_STREAMER_PARAM_URI, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);
	ret = media_streamer_node_get_param(video_capture, MEDIA_STREAMER_PARAM_USER_AGENT, &param_value);
	assert_eq(ret, MEDIA_STREAMER_ERROR_INVALID_OPERATION);
	assert_eq(param_value, NULL);

	return 0;
}
#endif   //MOBILE  //End

/**
 * @testcase		utc_media_streamer_play_p3
 * @since_tizen		3.0
 * @description		Adaptive auto playing of
 *			media streamer client.
 */
int utc_media_streamer_play_p3(void)
{
	int ret = MEDIA_STREAMER_ERROR_NONE;
	media_streamer_node_h adaptive_src = NULL;

	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_ADAPTIVE, &adaptive_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(adaptive_src, MEDIA_STREAMER_PARAM_URI, file_path_playlist);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, adaptive_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(adaptive_src);

	/*********************** videosink *********************************** */
	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(video_sink);

	/*********************** audiosink *********************************** */
	media_streamer_node_h audio_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_AUDIO, &audio_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, audio_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(audio_sink);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);
	return 0;
}

/**
 * @testcase		utc_media_streamer_play_p4
 * @since_tizen		3.0
 * @description		Adaptive manual playing of
 *			media streamer client.
 */
int utc_media_streamer_play_p4(void)
{

	int ret = MEDIA_STREAMER_ERROR_NONE;


	media_streamer_node_h adaptive_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_ADAPTIVE, &adaptive_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(adaptive_src, MEDIA_STREAMER_PARAM_URI, file_path_playlist);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, adaptive_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(adaptive_src);

	media_streamer_node_h ts_demux = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_DEMUXER, tsfmt, NULL, &ts_demux);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, ts_demux);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(ts_demux);

	media_streamer_node_h video_dec = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_DECODER, vfmt_aenc, vfmt_raw, &video_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, video_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(video_dec);

	media_streamer_node_h audio_dec = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_DECODER, afmt_aenc, afmt_araw, &audio_dec);
	if (ret != MEDIA_STREAMER_ERROR_NONE)
		ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_DECODER, afmt_aenc, afmt_raw, &audio_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, audio_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(audio_dec);

	/*********************** videosink *********************************** */
	media_streamer_node_h video_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_OVERLAY, &video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, video_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(video_sink);

	/*********************** audiosink *********************************** */
	media_streamer_node_h audio_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_AUDIO, &audio_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, audio_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(audio_sink);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	return 0;
}

/**
 * @testcase		utc_media_streamer_play_p5
 * @since_tizen		3.0
 * @description		Adaptive server of
 *			media streamer server.
 */
int utc_media_streamer_play_p5(void)
{

	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h file_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &file_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(file_src, MEDIA_STREAMER_PARAM_URI, file_path);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, file_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(file_src);

	/*********************** videosink *********************************** */
	media_streamer_node_h adaptive_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_ADAPTIVE, &adaptive_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(adaptive_sink, MEDIA_STREAMER_PARAM_SEGMENT_LOCATION, DEFAULT_SEGMENT_PATH);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(adaptive_sink, MEDIA_STREAMER_PARAM_PLAYLIST_LOCATION, DEFAULT_PLAYLIST_PATH);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, adaptive_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(adaptive_sink);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	return 0;
}

/**
 * @testcase		utc_media_streamer_play_p6
 * @since_tizen		3.0
 * @description		Adaptive manual server of
 *			media streamer server.
 */
int utc_media_streamer_play_p6(void)
{

	int ret = MEDIA_STREAMER_ERROR_NONE;

	media_streamer_node_h file_src = NULL;
	ret = media_streamer_node_create_src(MEDIA_STREAMER_NODE_SRC_TYPE_FILE, &file_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(file_src, MEDIA_STREAMER_PARAM_URI, file_path);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, file_src);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(file_src);

	media_streamer_node_h qt_demux = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_DEMUXER, qtfmt, NULL, &qt_demux);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, qt_demux);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(qt_demux);

	media_streamer_node_h video_dec = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_DECODER, vfmt_aenc, vfmt_raw, &video_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, video_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(video_dec);

	media_streamer_node_h audio_dec = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_DECODER, afmt_aenc, afmt_araw, &audio_dec);
	if (ret != MEDIA_STREAMER_ERROR_NONE)
		ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_DECODER, afmt_aenc, afmt_raw, &audio_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, audio_dec);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(audio_dec);

	media_streamer_node_h video_enc = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_VIDEO_ENCODER, vfmt_raw, vfmt_aencm, &video_enc);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, video_enc);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(video_enc);

	media_streamer_node_h audio_enc = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_ENCODER, afmt_araw, afmt_aenc, &audio_enc);
	if (ret != MEDIA_STREAMER_ERROR_NONE)
		ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_AUDIO_ENCODER, afmt_raw, afmt_aenc, &audio_enc);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, audio_enc);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(audio_enc);

	media_streamer_node_h ts_mux = NULL;
	ret = media_streamer_node_create(MEDIA_STREAMER_NODE_TYPE_MUXER, NULL, tsfmt, &ts_mux);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, ts_mux);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(ts_mux);

	media_streamer_node_h adaptive_sink = NULL;
	ret = media_streamer_node_create_sink(MEDIA_STREAMER_NODE_SINK_TYPE_ADAPTIVE, &adaptive_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(adaptive_sink, MEDIA_STREAMER_PARAM_SEGMENT_LOCATION, DEFAULT_SEGMENT_PATH);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_set_param(adaptive_sink, MEDIA_STREAMER_PARAM_PLAYLIST_LOCATION, DEFAULT_PLAYLIST_PATH);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_add(streamer, adaptive_sink);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	APPEND_NODE(adaptive_sink);

	ret = media_streamer_node_link(file_src, "src", qt_demux, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_link(video_dec, "src", video_enc, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_link(audio_dec, "src", audio_enc, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_link(video_enc, "src", ts_mux, "sink_%d");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_link(audio_enc, "src", ts_mux, "sink_%d");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	ret = media_streamer_node_link(ts_mux, "src", adaptive_sink, "sink");
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);

	ret = media_streamer_prepare(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	ret = media_streamer_play(streamer);
	assert_eq(ret, MEDIA_STREAMER_ERROR_NONE);
	wait_for_async(PLAY_TIME);

	return 0;
}
