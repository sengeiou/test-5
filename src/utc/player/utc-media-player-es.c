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
#include <media/player.h>
#include <media/media_packet.h>
#include <media/media_format.h>
#include <glib.h>
#include <storage.h>
#include <pthread.h>
#include "tct_common.h"
#ifndef TIZENIOT
#include <Elementary.h>
#endif

#define API_NAMESPACE			"[PLAYER]"

//& set: PlayerMediaEs
#define ES_FEEDING_PATH "es_buff://pull_mode"
#define ES_DEFAULT_VIDEO_PTS_OFFSET 20000000
#define ES_NUMBER_OF_FEED 100
#define ES_BUFFER_MAX_SIZE (3*1024*1024)
#define RETRY_COUNT_DEFAULT 5

static char* media = "test.h264";
static char* media_path = NULL;

static player_h player;
static bool _is_broken = false;
static bool _is_pass = false;
FILE *file_src = NULL;
media_format_h video_fmt = NULL;
media_format_h audio_fmt = NULL;
media_packet_h video_pkt = NULL;
unsigned char sps[100];
unsigned char pps[100];
unsigned char tmp_buf[1000000];
static int sps_len, pps_len;
pthread_t feeding_thread_id;
int g_ret;
#ifndef TIZENIOT
static Evas_Object *g_win = NULL;
#endif
static GMainLoop *g_mainloop = NULL;

static gboolean timeout_func(gpointer data)
{
    PRINT_UTC_LOG("[Line : %d][%s] waited 10 seconds\\n", __LINE__, API_NAMESPACE);
    g_main_loop_quit((GMainLoop *) data);
    return FALSE;
}

static void wait_for_async()
{
	int timeout_id;
	g_mainloop = g_main_loop_new(NULL, FALSE);

	timeout_id = g_timeout_add(5000, timeout_func, g_mainloop);
	g_main_loop_run(g_mainloop);
	g_source_remove(timeout_id);
	g_main_loop_unref(g_mainloop);
	g_mainloop = NULL;
}

static void seek_completed_cb(void *user_data)
{
}

static void seek_start_cb(void *user_data)
{
    PRINT_UTC_LOG("[Line : %d][%s] seek start callback\\n", __LINE__, API_NAMESPACE);
    int ret = player_set_play_position(player, 2, TRUE, seek_completed_cb, NULL);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] fail to set position\\n", __LINE__, API_NAMESPACE);
    }
}

static void _player_prepared_cb(void *user_data)
{
    PRINT_UTC_LOG("[Line : %d][%s] prepare callback\\n", __LINE__, API_NAMESPACE);
    int ret = player_start(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] fail to start\\n", __LINE__, API_NAMESPACE);
    }

}

#ifndef TIZENIOT
static void win_del(void *data, Evas_Object *obj, void *event)
{
    elm_exit();
}

static void create_window()
{
    int w = 0;
    int h = 0;

    g_win = elm_win_util_standard_add("player_tc", "player_tc");
    if (g_win) {
        elm_win_borderless_set(g_win, EINA_TRUE);
        evas_object_smart_callback_add(g_win, "delete,request",win_del, NULL);
        elm_win_screen_size_get(g_win, NULL, NULL, &w, &h);
        evas_object_resize(g_win, w, h);
        elm_win_autodel_set(g_win, EINA_TRUE);
    }
}

static void destroy_window()
{
    if (g_win) {
        evas_object_del(g_win);
        g_win = NULL;
    }
}
#endif

unsigned int bytestream2nalunit(FILE *fd, unsigned char* nal)
{
    int nal_length = 0;
    size_t result;
    int read_size = 1;
    unsigned char buffer[1000000];
    unsigned char val, zero_count, i;
    int nal_unit_type = 0;
    int init;

    zero_count = 0;
    if (!fd || feof(fd))
        return -1;

    result = fread(buffer, 1, read_size, fd);

    if(result != read_size)
        return -1;

    val = buffer[0];
    while (!val)
    {
        zero_count++;
        result = fread(buffer, 1, read_size, fd);

        if(result != read_size)
        {
            break;
        }
        val = buffer[0];
    }
    nal[nal_length++] = 0;
    nal[nal_length++] = 0;
    nal[nal_length++] = 0;
    nal[nal_length++] = 1;
    zero_count = 0;
    init = 1;
    while(1)
    {
        if (feof(fd))
            return nal_length;

        result = fread(buffer, 1, read_size, fd);
        if(result != read_size)
        {
            break;
        }
        val = buffer[0];

        if(init) {
            nal_unit_type = val & 0xf;
            init = 0;
        }
        if (!val)
        {
            zero_count++;
        }
        else
        {
            if ((zero_count == 2 || zero_count == 3 || zero_count == 4) && (val == 1))
            {
                break;
            }
            else
            {
                for (i = 0; i<zero_count; i++)
                {
                    nal[nal_length++] = 0;
                }
                nal[nal_length++] = val;
                zero_count = 0;
            }
        }
    }

    fseek(fd, -(zero_count + 1), SEEK_CUR);

    if (nal_unit_type == 0x7)
    {
        sps_len = nal_length;
        memcpy(sps, nal, nal_length);
        return 0;
    }
    else if (nal_unit_type == 0x8)
    {
        pps_len = nal_length;
        memcpy(pps, nal, nal_length);
        return 0;
    }
    else if (nal_unit_type == 0x5)
    {
        memcpy(tmp_buf, nal, nal_length);
        memcpy(nal, sps, sps_len);
        memcpy(nal + sps_len, pps, pps_len);
        memcpy(nal + sps_len + pps_len, tmp_buf, nal_length);
        nal_length += sps_len + pps_len;
    }

    return nal_length;
}

static void feed_video_data()
{
    int read = 0;
    static guint64 pts = 0L;
    void *buf_data_ptr = NULL;

    if (media_packet_create_alloc(video_fmt, NULL, NULL, &video_pkt) != MEDIA_PACKET_ERROR_NONE) {
		    PRINT_UTC_LOG("[Line : %d][%s] fail to alloc media_packet\\n", __LINE__, API_NAMESPACE);
        return;
    }

    if (media_packet_get_buffer_data_ptr(video_pkt, &buf_data_ptr) != MEDIA_PACKET_ERROR_NONE) {
        PRINT_UTC_LOG("[Line : %d][%s] media_packet_get_buffer_data_ptr failed\\n", __LINE__, API_NAMESPACE);
        goto FREE_PACKET;
    }

    if (media_packet_set_pts(video_pkt, (uint64_t)(pts/1000000)) != MEDIA_PACKET_ERROR_NONE) {
        PRINT_UTC_LOG("[Line : %d][%s] media_packet_set_pts failed\\n", __LINE__, API_NAMESPACE);
        goto FREE_PACKET;
    }
    /* NOTE: In case of H.264 video, stream format for feeding is NAL unit.
    * And, SPS(0x67) and PPS(0x68) should be located before IDR.(0x65).
    */
    read = bytestream2nalunit(file_src, buf_data_ptr);
    if (read <= 0) {
        PRINT_UTC_LOG("[Line : %d][%s] input file read failed\\n", __LINE__, API_NAMESPACE);
        goto FREE_PACKET;
    }

    if (media_packet_set_buffer_size(video_pkt, (uint64_t)read) != MEDIA_PACKET_ERROR_NONE) {
        PRINT_UTC_LOG("[Line : %d][%s] media_packet_set_buffer_size failed\\n", __LINE__, API_NAMESPACE);
        goto FREE_PACKET;
    }

    /* push media packet */
    g_ret = player_push_media_stream(player, video_pkt);
    pts += ES_DEFAULT_VIDEO_PTS_OFFSET;

    goto FREE_PACKET;

FREE_PACKET:
    /* destroy media packet after use */
    media_packet_destroy(video_pkt);
    video_pkt = NULL;
    return;
}

static void feed_video_data_thread_func()
{
    gboolean exit = FALSE;
    int frame_count = 0;

    while (!exit)
    {
        if (frame_count < ES_NUMBER_OF_FEED) {
            feed_video_data();
            frame_count++;
        } else {
            exit = TRUE;
        }
    }
    pthread_exit(0);
}

static void player_media_stream_buffer_status_callback (player_media_stream_buffer_status_e status, void *user_data)
{
    _is_pass = true;
}

static void player_media_stream_seek_callback(unsigned long long offset, void *user_data)
{
    if(offset>500)
        _is_pass = true;
}

static bool _player_supported_media_format_cb(media_format_mimetype_e format, void *user_data)
{
	PRINT_UTC_LOG("[Line : %d][%s] supported format 0x%X\n", __LINE__, API_NAMESPACE, format);
	_is_pass = true;
	return true;
}

/**
 * @function		utc_media_player_es_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_es_startup(void)
{
#ifndef TIZENIOT
	elm_init(0, NULL);
#endif
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		unsigned int size_of_path = strlen(pszValue) + strlen(media) + 11;
		media_path = (char*)malloc(size_of_path);
		snprintf(media_path, size_of_path, "%s/res/res/%s", pszValue, media);
	}
	else
	{
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

    file_src = fopen(media_path, "r");

    _is_broken = false;
    _is_pass = false;

    int ret = player_create(&player);
    if (PLAYER_ERROR_NONE != ret) {
        _is_broken = true;
        return;
    }

    ret = player_set_uri(player, ES_FEEDING_PATH);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player didn't set uri\\n", __LINE__, API_NAMESPACE);
        _is_broken = true;
    }

    /* get media format format */
    ret = media_format_create(&video_fmt);
    if (ret != MEDIA_FORMAT_ERROR_NONE) {
        PRINT_UTC_LOG("[Line : %d][%s] media_format_create(v) is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = media_format_create(&audio_fmt);
    if (ret != MEDIA_FORMAT_ERROR_NONE) {
        PRINT_UTC_LOG("[Line : %d][%s] media_format_create(a) is failed\\n", __LINE__, API_NAMESPACE);
    }

    /* set format */
    media_format_set_video_mime(video_fmt, MEDIA_FORMAT_H264_SP);
    media_format_set_video_width(video_fmt, 640);
    media_format_set_video_height(video_fmt, 480);

    media_format_set_audio_mime(audio_fmt, MEDIA_FORMAT_AAC);
    media_format_set_audio_channel(audio_fmt, 2);
    media_format_set_audio_samplerate(audio_fmt, 48000);
}

/**
 * @function		utc_media_player_es_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_es_cleanup(void)
{
    player_state_e state;
    int ret = 0;

    if (video_fmt)
        media_format_unref(video_fmt);
    if (audio_fmt)
        media_format_unref(audio_fmt);

	if (file_src) {
		fclose(file_src);
		file_src = NULL;
	}

    if(player){
        ret = player_get_state (player, &state);
        if (PLAYER_ERROR_NONE != ret) {
          PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
        }
        if (state != PLAYER_STATE_IDLE)
          player_unprepare(player);

        player_destroy(player);
        player = NULL;
    }
    if(media_path)
      free(media_path);
#ifndef TIZENIOT
	destroy_window();
	elm_shutdown();
#endif
}

/**
 * @testcase		utc_media_player_set_media_stream_info_p
 * @since_tizen		2.4
 * @description		Positive test case to set media stream info
 */
int utc_media_player_set_media_stream_info_p(void)
{
    assert(!_is_broken);
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_info(player, PLAYER_STREAM_TYPE_VIDEO, video_fmt);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_info is failed\\n", __LINE__, API_NAMESPACE);
    }
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_media_stream_info_n
 * @since_tizen		2.4
 * @description 		Negative test case to set media stream info
 */
int utc_media_player_set_media_stream_info_n(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
#ifndef TIZENIOT
	create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_info(player, PLAYER_STREAM_TYPE_VIDEO, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_OPERATION);

    return 0;
}

/**
 * @testcase		utc_media_player_push_media_stream_p
 * @since_tizen		2.4
 * @description		Positive test case to push media stream
 */
int utc_media_player_push_media_stream_p(void)
{
    assert(!_is_broken);
    int ret = 0;
    player_state_e state;

    ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    ret = player_set_media_stream_buffer_status_cb(player, PLAYER_STREAM_TYPE_VIDEO, player_media_stream_buffer_status_callback, NULL);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_status_cb is failed\\n", __LINE__, API_NAMESPACE);
    }

    ret = player_set_media_stream_buffer_max_size(player, PLAYER_STREAM_TYPE_VIDEO, ES_BUFFER_MAX_SIZE);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_status_cb is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_set_media_stream_seek_cb(player, PLAYER_STREAM_TYPE_VIDEO, player_media_stream_seek_callback, NULL);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_status_cb is failed\\n", __LINE__, API_NAMESPACE);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_info(player, PLAYER_STREAM_TYPE_VIDEO, video_fmt);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_info is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_prepare_async(player, _player_prepared_cb, (void*)player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }
    if(pthread_create(&feeding_thread_id, NULL, (void*)feed_video_data_thread_func, NULL)<0) {
        PRINT_UTC_LOG("[Line : %d][%s] pthread_create is failed\\n", __LINE__, API_NAMESPACE);
        return 0;
    }

    usleep(500 * 1000);
    pthread_join(feeding_thread_id, NULL);
    assert_eq(g_ret, PLAYER_ERROR_NONE);
    usleep(1000);

    player_stop(player);
    player_unprepare(player);
    feeding_thread_id = 0;

    return 0;
}

/**
 * @testcase		utc_media_player_push_media_stream_n
 * @since_tizen		2.4
 * @description		Negative test case to push media stream
 */
int utc_media_player_push_media_stream_n(void)
{
    int ret = 0;
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_info(player, PLAYER_STREAM_TYPE_AUDIO, audio_fmt);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_info is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_prepare_async(player, _player_prepared_cb, (void*)player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_push_media_stream(player, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    player_stop(player);
    player_unprepare(player);

    return 0;
}

/**
 * @testcase		utc_player_set_media_stream_buffer_max_size_p
 * @since_tizen		2.4
 * @description		Positive test case to set media stream buffer maximum size
 */
int utc_player_set_media_stream_buffer_max_size_p(void)
{
    assert(!_is_broken);
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_buffer_max_size(player, PLAYER_STREAM_TYPE_VIDEO, 10);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_player_set_media_stream_buffer_max_size_n
 * @since_tizen		2.4
 * @description		Negative test case to set media stream buffer maximum size
 */
int utc_player_set_media_stream_buffer_max_size_n(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_buffer_max_size(NULL, PLAYER_STREAM_TYPE_VIDEO, 10);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_player_get_media_stream_buffer_max_size_p
 * @since_tizen		2.4
 * @description		Positive test case to get media stream buffer maximum size
 */
int utc_player_get_media_stream_buffer_max_size_p(void)
{
    assert(!_is_broken);
    player_state_e state;
    unsigned long long max_size;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_buffer_max_size(player, PLAYER_STREAM_TYPE_VIDEO, 10);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_max_size is failed\\n", __LINE__, API_NAMESPACE);
    }
	ret = player_get_media_stream_buffer_max_size(player, PLAYER_STREAM_TYPE_VIDEO, &max_size);
    assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_player_get_media_stream_buffer_max_size_n
 * @since_tizen		2.4
 * @description		Negative test case to get media stream buffer maximum size
 */
int utc_player_get_media_stream_buffer_max_size_n(void)
{
    player_state_e state;
    unsigned long long max_size;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_buffer_max_size(player, PLAYER_STREAM_TYPE_VIDEO, 10);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_max_size is failed\\n", __LINE__, API_NAMESPACE);
    }
	ret = player_get_media_stream_buffer_max_size(NULL, PLAYER_STREAM_TYPE_VIDEO, &max_size);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_player_set_media_stream_buffer_min_threshold_p
 * @since_tizen		2.4
 * @description		Positive test case to set media stream buffer minimum threshold
 */
int utc_player_set_media_stream_buffer_min_threshold_p(void)
{
    assert(!_is_broken);
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_buffer_min_threshold(player, PLAYER_STREAM_TYPE_VIDEO, 10);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;

}

/**
 * @testcase		utc_player_set_media_stream_buffer_min_threshold_n
 * @since_tizen		2.4
 * @description		Negative test case to set media stream buffer minimum threshold
 */
int utc_player_set_media_stream_buffer_min_threshold_n(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_buffer_min_threshold(NULL, PLAYER_STREAM_TYPE_VIDEO, 10);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;

}

/**
 * @testcase		utc_player_get_media_stream_buffer_min_threshold_p
 * @since_tizen		2.4
 * @description		Positive test case to get media stream buffer minimum threshold
 */
int utc_player_get_media_stream_buffer_min_threshold_p(void)
{
    assert(!_is_broken);
    player_state_e state;
    unsigned int percent;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_buffer_min_threshold(player, PLAYER_STREAM_TYPE_VIDEO, 10);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_min_threshold is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_get_media_stream_buffer_min_threshold(player, PLAYER_STREAM_TYPE_VIDEO, &percent);
    assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;

}

/**
 * @testcase		utc_player_get_media_stream_buffer_min_threshold_n
 * @since_tizen		2.4
 * @description		Negative test case to get media stream buffer minimum threshold
 */
int utc_player_get_media_stream_buffer_min_threshold_n(void)
{
	player_state_e state;
	unsigned int percent;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_buffer_min_threshold(player, PLAYER_STREAM_TYPE_VIDEO, 10);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_min_threshold is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_get_media_stream_buffer_min_threshold(NULL, PLAYER_STREAM_TYPE_VIDEO, &percent);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;

}

/**
 * @testcase		utc_player_set_media_stream_buffer_status_cb_p
 * @since_tizen		2.4
 * @description		Positive test case to set media stream buffer status callback
 */
int utc_player_set_media_stream_buffer_status_cb_p(void)
{
    assert(!_is_broken);
    int ret = 0;
    player_state_e state;

    ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    ret = player_set_media_stream_buffer_status_cb(player, PLAYER_STREAM_TYPE_VIDEO, player_media_stream_buffer_status_callback, NULL);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_status_cb is failed\\n", __LINE__, API_NAMESPACE);
    }

    ret = player_set_media_stream_buffer_max_size(player, PLAYER_STREAM_TYPE_VIDEO, ES_BUFFER_MAX_SIZE);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_status_cb is failed\\n", __LINE__, API_NAMESPACE);
    }

    ret = player_set_media_stream_buffer_min_threshold(player, PLAYER_STREAM_TYPE_VIDEO, 5);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_min_threshold is failed\\n", __LINE__, API_NAMESPACE);
    }

#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_info(player, PLAYER_STREAM_TYPE_VIDEO, video_fmt);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_info is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_prepare_async(player, _player_prepared_cb, (void*)player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }
    if(pthread_create(&feeding_thread_id, NULL, (void*)feed_video_data_thread_func, NULL)<0) {
        PRINT_UTC_LOG("[Line : %d][%s] pthread_create is failed\\n", __LINE__, API_NAMESPACE);
        return 0;
    }

    usleep(500 * 1000);
    pthread_join(feeding_thread_id, NULL);
    assert_eq(g_ret, PLAYER_ERROR_NONE);
    usleep(1000);

    player_stop(player);
    player_unprepare(player);
    feeding_thread_id = 0;

    assert(_is_pass);
    _is_pass = false;

    return 0;
}

/**
 * @testcase		utc_player_set_media_stream_buffer_status_cb_n
 * @since_tizen		2.4
 * @description		Negative test case to set media stream buffer status callback
 */
int utc_player_set_media_stream_buffer_status_cb_n(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
    ret = player_set_media_stream_buffer_status_cb(NULL, PLAYER_STREAM_TYPE_VIDEO, player_media_stream_buffer_status_callback, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_player_unset_media_stream_buffer_status_cb_p
 * @since_tizen		2.4
 * @description		Positive test case to unset media stream buffer status callback
 */
int utc_player_unset_media_stream_buffer_status_cb_p(void)
{
    assert(!_is_broken);
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
    ret = player_unset_media_stream_buffer_status_cb(player, PLAYER_STREAM_TYPE_VIDEO);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_player_unset_media_stream_buffer_status_cb_p2
 * @since_tizen		2.4
 * @description		Positive test case to unset media stream buffer status callback
 */
int utc_player_unset_media_stream_buffer_status_cb_p2(void)
{
    assert(!_is_broken);
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
    ret = player_unset_media_stream_buffer_status_cb(player, PLAYER_STREAM_TYPE_AUDIO);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_player_unset_media_stream_buffer_status_cb_n
 * @since_tizen		2.4
 * @description		Negative test case to unset media stream buffer status callback
 */
int utc_player_unset_media_stream_buffer_status_cb_n(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
    ret = player_unset_media_stream_buffer_status_cb(NULL, PLAYER_STREAM_TYPE_VIDEO);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_player_set_media_stream_seek_cb_p
 * @since_tizen		2.4
 * @description		Positive test case to set media stream seek callback
 */
int utc_player_set_media_stream_seek_cb_p(void)
{
    assert(!_is_broken);
    int ret = 0;
    int repeat = 0;
    player_state_e state;

    ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    ret = player_set_media_stream_seek_cb(player, PLAYER_STREAM_TYPE_VIDEO, player_media_stream_seek_callback, NULL);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_seek_cb is failed\\n", __LINE__, API_NAMESPACE);
    }
#ifndef TIZENIOT
    create_window();
    ret = player_set_display(player, PLAYER_DISPLAY_TYPE_OVERLAY, g_win);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display is failed\\n", __LINE__, API_NAMESPACE);
    }
#endif
    ret = player_set_media_stream_info(player, PLAYER_STREAM_TYPE_VIDEO, video_fmt);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_info is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_set_media_stream_buffer_max_size(player, PLAYER_STREAM_TYPE_VIDEO, ES_BUFFER_MAX_SIZE);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_media_stream_buffer_max_size is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_prepare_async(player, seek_start_cb, (void*)player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
    }

    if(pthread_create(&feeding_thread_id, NULL, (void*)feed_video_data_thread_func, NULL)<0) {
        PRINT_UTC_LOG("[Line : %d][%s] pthread_create is failed\\n", __LINE__, API_NAMESPACE);
        return 0;
    }

    for (repeat = 0; repeat < RETRY_COUNT_DEFAULT; repeat++) {
        wait_for_async();
    }

    pthread_join(feeding_thread_id, NULL);
    assert_eq(g_ret, PLAYER_ERROR_NONE);
    usleep(1000);

    player_unprepare(player);
    feeding_thread_id = 0;

    assert(_is_pass);
    _is_pass = false;

    return 0;
}

/**
 * @testcase		utc_player_set_media_stream_seek_cb_n
 * @since_tizen		2.4
 * @description		Negative test case to set media stream seek callback
 */
int utc_player_set_media_stream_seek_cb_n(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
    ret = player_set_media_stream_seek_cb(player, 5, player_media_stream_seek_callback, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_player_unset_media_stream_seek_cb_p
 * @since_tizen		2.4
 * @description		Positive test case to unset media stream seek callback
 */
int utc_player_unset_media_stream_seek_cb_p(void)
{
    assert(!_is_broken);

    int ret = player_unset_media_stream_seek_cb(player, PLAYER_STREAM_TYPE_VIDEO);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_player_unset_media_stream_seek_cb_p2
 * @since_tizen		2.4
 * @description		Positive test case to unset media stream seek callback
 */
int utc_player_unset_media_stream_seek_cb_p2(void)
{
    assert(!_is_broken);

    int ret = player_unset_media_stream_seek_cb(player, PLAYER_STREAM_TYPE_AUDIO);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_player_unset_media_stream_seek_cb_n
 * @since_tizen		2.4
 * @description		Negative test case to unset media stream seek callback
 */
int utc_player_unset_media_stream_seek_cb_n(void)
{
    int ret = player_unset_media_stream_seek_cb(NULL, PLAYER_STREAM_TYPE_VIDEO);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_player_foreach_media_stream_supported_format_p
 * @since_tizen     5.5
 * @description     Positive test case to retrieve the supported format
 *                  about external media stream playback
 */
int utc_player_foreach_media_stream_supported_format_p(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;
	int repeat = 0;

	ret = player_foreach_media_stream_supported_format(player, _player_supported_media_format_cb, player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	for (repeat = 0 ; repeat < RETRY_COUNT_DEFAULT ; repeat++) {
		wait_for_async();
		if (_is_pass)
			break;
	}

	assert(_is_pass);
	_is_pass = false;

	return 0;
}

/**
 * @testcase        utc_player_foreach_media_stream_supported_format_n
 * @since_tizen     5.5
 * @description     Negative test case to retrieve the supported format
 *                  about external media stream playback
 */
int utc_player_foreach_media_stream_supported_format_n(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;

	ret = player_foreach_media_stream_supported_format(player, NULL, player);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
	return 0;
}
