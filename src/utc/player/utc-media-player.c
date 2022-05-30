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
#include <media/sound_manager.h>
#include <glib.h>
#include <Elementary.h>
#include <storage.h>
#include "tct_common.h"

#define API_NAMESPACE    "[PLAYER]"

//& set: PlayerMedia


static char* audio = "sample.mp3";
static char* media = "test.mp4";
static char* subtitle = "subtitles_test_file.srt";
static char* audio_path = NULL;
static char* media_path = NULL;
static char* subtitle_path = NULL;
static int *band_levels = NULL;
static char* code = NULL;
static player_h player;
static bool _is_broken = false;
static bool _is_pass = false;
static sound_stream_info_h g_stream_info_h = NULL;

typedef struct{
    char *album;
    char *artist;
    char *author;
    char *genre;
    char *title;
    char *year;
    char *audio_codec;
    char *video_codec;
    int audio_sample_rate;
    int audio_channel;
    int audio_bit_rate;
    void *album_art;
    int album_art_size;
    int audio_tracks_count;
}t_streamInfo;
static t_streamInfo stream_info = {0};

static GMainLoop *g_mainloop = NULL;

static gboolean timeout_func(gpointer data)
{
    PRINT_UTC_LOG("[Line : %d][%s] waited 5 seconds\\n", __LINE__, API_NAMESPACE);
    g_main_loop_quit((GMainLoop *) data);
    return FALSE;
}

static void wait_for_async(bool custom)
{
    GMainContext *context = g_main_context_new();
    GSource *source = g_timeout_source_new(5000);

    /* attach source to context */
    g_source_attach (source, context);

    if (custom) {
        g_mainloop = g_main_loop_new(context, FALSE);

        /* set the callback for this source */
        g_source_set_callback (source, timeout_func, g_mainloop, NULL);

        g_main_loop_run(g_mainloop);

    } else {
        int timeout_id;

        g_mainloop = g_main_loop_new(NULL, FALSE);
        timeout_id = g_timeout_add(5000, timeout_func, g_mainloop);

        g_main_loop_run(g_mainloop);
        g_source_remove(timeout_id);
    }

    /* after attaching with the GSource, destroy() is needed */
    g_source_destroy(source);

    /* unref the last reference we got for GSource */
    g_source_unref(source);

    /* main loop should be destroyed before unref the context */
    g_main_loop_unref(g_mainloop);
    g_main_context_unref(context);

    g_mainloop = NULL;
}

static bool _check_sound_stream_feature(void)
{
#define _FEATURE_NAME_SOUND_STREAM "http://tizen.org/feature/multimedia.player.stream_info"
    bool supported = FALSE;

    system_info_get_platform_bool(_FEATURE_NAME_SOUND_STREAM, &supported);

    if (supported)
        return true;

    PRINT_UTC_LOG("[Line : %d][%s] sound_stream is not supportable.\\n", __LINE__, API_NAMESPACE);
    return false;
}

void focus_cb(sound_stream_info_h stream_info, sound_stream_focus_mask_e focus_mask, sound_stream_focus_state_e focus_state,
             sound_stream_focus_change_reason_e reason, int sound_behavior, const char *extra_info, void *user_data)
{
	PRINT_UTC_LOG("[Line : %d][%s]FOCUS callback is called, reason(%d), extra_info(%s), userdata(%p)",
		__LINE__, API_NAMESPACE, reason, extra_info, user_data);
	return;
}

static void set_sound_stream_info()
{
	if (g_stream_info_h) {
		PRINT_UTC_LOG("[Line : %d][%s]stream information is already set, please destory handle and try again\\n", __LINE__, API_NAMESPACE);
		return;
	}
	if (sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, focus_cb, player, &g_stream_info_h)) {
		PRINT_UTC_LOG("[Line : %d][%s]failed to create stream_information()\\n", __LINE__, API_NAMESPACE);
		return;
	}
	return;
}

static bool _check_audio_offload_feature(void)
{
#define _FEATURE_NAME_AUDIO_OFFLOAD "http://tizen.org/feature/multimedia.player.audio_offload"
    bool supported = FALSE;

    system_info_get_platform_bool(_FEATURE_NAME_AUDIO_OFFLOAD, &supported);

    if (supported)
        return true;

    PRINT_UTC_LOG("[Line : %d][%s] audio offload is not supportable.\\n", __LINE__, API_NAMESPACE);
    return false;
}

static bool _audio_offload_format_cb(media_format_mimetype_e format, void *user_data)
{
	PRINT_UTC_LOG("[Line : %d][%s] supported format 0x%X\n", __LINE__, API_NAMESPACE, format);
	_is_pass = true;
	return true;
}

/**
 * @function		utc_media_player_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_startup(void)
{
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		unsigned int size_of_path = strlen(pszValue) + strlen(audio) + 11;
		audio_path = (char*)malloc(size_of_path);
		snprintf(audio_path, size_of_path, "%s/res/res/%s", pszValue, audio);

		size_of_path = strlen(pszValue) + strlen(media) + 11;
		media_path = (char*)malloc(size_of_path);
		snprintf(media_path, size_of_path, "%s/res/res/%s", pszValue, media);

		size_of_path = strlen(pszValue) + strlen(subtitle) + 11;
		subtitle_path = (char*)malloc(size_of_path);
		snprintf(subtitle_path, size_of_path, "%s/res/res/%s", pszValue, subtitle);
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

    _is_broken = false;	/* If the tc meet timeout, cleanup is not called.*/
    _is_pass = false;

    int ret = player_create(&player);
    if (PLAYER_ERROR_NONE != ret) {
        _is_broken = true;
        return;
    }

    ret = player_set_uri(player, media_path);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player didn't set uri\\n", __LINE__, API_NAMESPACE);
        _is_broken = true;
    }

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);
        _is_broken = true;
    }

}

/**
 * @function		utc_media_player_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_cleanup(void)
{
    player_state_e state;
    int ret = 0;

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
    if(audio_path)
      free(audio_path);
    if(media_path)
      free(media_path);
    if(subtitle_path)
      free(subtitle_path);
    audio_path = media_path = subtitle_path = NULL;
    if (g_stream_info_h) {
      sound_manager_destroy_stream_information(g_stream_info_h);
      g_stream_info_h = NULL;
    }
    if(band_levels) {
      free(band_levels);
      band_levels = NULL;
    }
    if (code) {
      free(code);
      code = NULL;
    }
    if(stream_info.album)
      free(stream_info.album);
    if(stream_info.artist)
      free(stream_info.artist);
    if(stream_info.author)
      free(stream_info.author);
    if(stream_info.genre)
      free(stream_info.genre);
    if(stream_info.title)
      free(stream_info.title);
    if(stream_info.year)
      free(stream_info.year);
    if(stream_info.audio_codec)
      free(stream_info.audio_codec);
    if(stream_info.video_codec)
      free(stream_info.video_codec);

    stream_info.album = stream_info.artist = stream_info.author = stream_info.genre = stream_info.title = stream_info.year
      = stream_info.audio_codec = stream_info.video_codec = NULL;
}

/**
 * @testcase		utc_media_player_get_duration_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get duration
 */
int utc_media_player_get_duration_p(void)
{
    assert(!_is_broken);
    int duration;

    int ret = player_get_duration(player, &duration);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_get_duration_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get duration
 */
int utc_media_player_get_duration_n(void)
{
    int ret = player_get_duration(player, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_duration_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to get duration
 */
int utc_media_player_get_duration_n2(void)
{
    int duration;
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
      PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE)
      player_unprepare(player);

    ret = player_get_duration(player, &duration);
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase        utc_media_player_get_duration_nsec_p
 * @since_tizen     5.0
 * @description     Positive test case to get duration in nanoseconds
 */
int utc_media_player_get_duration_nsec_p(void)
{
	assert(!_is_broken);
	int64_t duration = 0;

	int ret = player_get_duration_nsec(player, &duration);
	assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_media_player_get_duration_nsec_n
 * @since_tizen     5.0
 * @description     Negative test case to get duration in nanoseconds
 */
int utc_media_player_get_duration_nsec_n(void)
{
	int ret = player_get_duration_nsec(player, NULL);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

static void player_seek_completed_cb_func(void *user_data) {

}

/**
 * @testcase		utc_media_player_set_play_position_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set play position
 */
int utc_media_player_set_play_position_p(void)
{
    assert(!_is_broken);
    int position = 10;

    int ret = player_set_play_position(player, position, TRUE, player_seek_completed_cb_func, NULL);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_play_position_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set play position
 */
int utc_media_player_set_play_position_n(void)
{
    int position = -100;

    int ret = player_set_play_position(player, position, TRUE, player_seek_completed_cb_func, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_play_position_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to set play position
 */
int utc_media_player_set_play_position_n2(void)
{
    int position = 10;
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
      PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE)
      player_unprepare(player);

    ret = player_set_play_position(player, position, TRUE, player_seek_completed_cb_func, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase        utc_media_player_set_play_position_nsec_p
 * @since_tizen     5.0
 * @description     Positive test case to set play position in nanoseconds
 */
int utc_media_player_set_play_position_nsec_p(void)
{
	assert(!_is_broken);
	int64_t position = 1000*1000*1000; /* 1sec */

	int ret = player_set_play_position_nsec(player, position, TRUE, player_seek_completed_cb_func, NULL);
	assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_media_player_set_play_position_nsec_n
 * @since_tizen     5.0
 * @description     Negative test case to set play position in nanoseconds
 */
int utc_media_player_set_play_position_nsec_n(void)
{
	int64_t position = -100;

	int ret = player_set_play_position_nsec(player, position, TRUE, player_seek_completed_cb_func, NULL);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_player_get_play_position_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get play position
 */
int utc_media_player_get_play_position_p(void)
{
    assert(!_is_broken);
    int position = 10;

    int ret = player_set_play_position(player, position, TRUE, player_seek_completed_cb_func, NULL);
    assert_eq(ret, PLAYER_ERROR_NONE);
    wait_for_async(FALSE);

    int millisecond;
    int ret2 = player_get_play_position(player, &millisecond);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert(millisecond);

    return 0;
}

/**
 * @testcase		utc_media_player_get_play_position_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get play position
 */
int utc_media_player_get_play_position_n(void)
{
    int position;

    int ret = player_get_play_position(NULL, &position);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_play_position_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to get play position
 */
int utc_media_player_get_play_position_n2(void)
{
    int position;
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
      PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE)
      player_unprepare(player);

    ret = player_get_play_position(player, &position);
    assert_eq(position, 0);

    return 0;
}

/**
 * @testcase        utc_media_player_get_play_position_nsec_p
 * @since_tizen     5.0
 * @description     Positive test case to get play position in nanoseconds
 */
int utc_media_player_get_play_position_nsec_p(void)
{
	assert(!_is_broken);
	int position = 1000;
	int64_t nanoseconds = 0;

	int ret = player_set_play_position(player, position, TRUE, player_seek_completed_cb_func, NULL);
	assert_eq(ret, PLAYER_ERROR_NONE);
	wait_for_async(FALSE);

	int ret2 = player_get_play_position_nsec(player, &nanoseconds);
	assert_eq(ret2, PLAYER_ERROR_NONE);
	assert(nanoseconds);

	return 0;
}

/**
 * @testcase        utc_media_player_get_play_position_nsec_n
 * @since_tizen     5.0
 * @description     Negative test case to get play position in nanoseconds
 */
int utc_media_player_get_play_position_nsec_n(void)
{
	int ret = player_get_play_position_nsec(player, NULL);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_player_get_state_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get state
 */
int utc_media_player_get_state_p(void)
{
    assert(!_is_broken);
    player_state_e cur_state;

    int ret = player_get_state(player, &cur_state);
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(cur_state, PLAYER_STATE_READY);

    return 0;
}

/**
 * @testcase		utc_media_player_get_state_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get state
 */
int utc_media_player_get_state_n(void)
{
    int ret = player_get_state(player, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_playback_rate_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set playback rate
 */
int utc_media_player_set_playback_rate_p(void)
{
    float rate = 1.0f;

    int ret = player_set_playback_rate(player, rate);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_playback_rate_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set playback rate
 */
int utc_media_player_set_playback_rate_n(void)
{
    float rate = 10.0f;

    int ret = player_set_playback_rate(player, rate);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_playback_rate_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to set playback rate
 */
int utc_media_player_set_playback_rate_n2(void)
{
    float rate = 1.0f;
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
      PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE)
      player_unprepare(player);

    ret = player_set_playback_rate(player, rate);
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_looping_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set looping
 */
int utc_media_player_set_looping_p(void)
{
    assert(!_is_broken);
    bool is = false;
    bool looping;

    int ret = player_is_looping(player, &is);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_is_looping is failed\\n", __LINE__, API_NAMESPACE);
    }
    if(!is)
      looping = true;
    else
      looping = false;
    ret = player_set_looping(player, looping);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_is_looping(player, &is);
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(is, looping);

    return 0;
}

/**
 * @testcase		utc_media_player_set_looping_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set looping
 */
int utc_media_player_set_looping_n(void)
{
    bool looping = true;

    int ret = player_set_looping(NULL, looping);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_is_looping_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get whether looping is on or not
 */
int utc_media_player_is_looping_p(void)
{
    assert(!_is_broken);
    bool is = false;

    int ret = player_set_looping(player, true);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_is_looping(player, &is);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert(is);

    return 0;
}

/**
 * @testcase		utc_media_player_is_looping_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get whether looping is on or not
 */
int utc_media_player_is_looping_n(void)
{
    bool looping;

    int ret = player_is_looping(NULL, &looping);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_mute_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set mute
 */
int utc_media_player_set_mute_p(void)
{
    assert(!_is_broken);

    bool is = false;
    bool mute = false;

    int ret = player_is_muted(player, &is);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_is_muted is failed\\n", __LINE__, API_NAMESPACE);
    }
    if(!is)
      mute = true;
    else
      mute = false;
    ret = player_set_mute(player, mute);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_is_muted(player, &is);
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(is, mute);

    return 0;
}

/**
 * @testcase		utc_media_player_set_mute_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set mute
 */
int utc_media_player_set_mute_n(void)
{
    bool muted = false;

    int ret = player_set_mute(NULL, muted);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_is_muted_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get whether mute is on or not
 */
int utc_media_player_is_muted_p(void)
{
    assert(!_is_broken);
    bool muted = false;
    bool is = true;

    int ret = player_set_mute(player, muted);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_is_muted(player, &is);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert(!is);

    return 0;
}

/**
 * @testcase		utc_media_player_is_muted_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get whether mute is on or not
 */
int utc_media_player_is_muted_n(void)
{
    bool muted;

    int ret = player_is_muted(NULL, &muted);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_memory_buffer_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set memory buffer
 */
int utc_media_player_set_memory_buffer_p(void)
{
    assert(!_is_broken);

    GMappedFile *file;
    gsize file_size;
    guint8* g_media_mem = NULL;

    file = g_mapped_file_new (media_path, FALSE,NULL);
    file_size = g_mapped_file_get_length (file);
    g_media_mem = (guint8 *) g_mapped_file_get_contents (file);

    int ret = player_unprepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_set_memory_buffer(player, (void*)g_media_mem, file_size);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    g_mapped_file_unref(file);

    return 0;
}

/**
 * @testcase		utc_media_player_set_memory_buffer_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set memory buffer
 */
int utc_media_player_set_memory_buffer_n(void)
{
    int ret = player_set_memory_buffer(player, NULL, 0);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_volume_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set volume
 */
int utc_media_player_set_volume_p(void)
{
    assert(!_is_broken);
    float left = 0.5f, right  = 0.5f;

    int ret = player_set_volume(player, left, right);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_volume_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set volume
 */
int utc_media_player_set_volume_n(void)
{
    float left = 2.0f, right  = -3.0f;

    int ret = player_set_volume(player, left, right);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_volume_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get volume
 */
int utc_media_player_get_volume_p(void)
{
    assert(!_is_broken);
    float left = 0.7f, right  = 0.7f;
    float l = .0f, r = .0f;

    int ret = player_set_volume(player, left, right);
    assert_eq(ret, PLAYER_ERROR_NONE);
    int ret2 = player_get_volume(player, &l, &r);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    if (l != left || r > right) {
        assert(false);
    }

    return 0;
}

/**
 * @testcase		utc_media_player_get_volume_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get volume
 */
int utc_media_player_get_volume_n(void)
{
    float left;

    int ret = player_get_volume(player, &left, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_sound_stream_info_p
 * @since_tizen		3.0
 * @description		Positive test case to set audio policy info
 */
int utc_media_player_set_sound_stream_info_p(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    assert_eq(ret, PLAYER_ERROR_NONE);
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    ret = player_get_state (player, &state);
    assert_eq(ret, PLAYER_ERROR_NONE);

    if (state == PLAYER_STATE_IDLE){
        set_sound_stream_info();
        ret = player_set_sound_stream_info(player, g_stream_info_h);
        if (!_check_sound_stream_feature()) {
            assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
            return 0;
        }

        assert_eq(ret, PLAYER_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_media_player_set_sound_stream_info_n
 * @since_tizen		3.0
 * @description		Negative test case to set audio policy info
 */
int utc_media_player_set_sound_stream_info_n(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    assert_eq(ret, PLAYER_ERROR_NONE);
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    ret = player_get_state (player, &state);
    assert_eq(ret, PLAYER_ERROR_NONE);

    if (state == PLAYER_STATE_IDLE){
        ret = player_set_sound_stream_info(NULL, NULL);
        if (!_check_sound_stream_feature()) {
            assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
            return 0;
        }
        assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
    }
    return 0;
}

/**
 * @testcase		utc_media_player_set_subtitle_path_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set subtitle path
 */
int utc_media_player_set_subtitle_path_p(void)
{
    int ret;
    assert(!_is_broken);

    ret = player_unprepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_subtitle_path(player, subtitle_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_subtitle_path_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set subtitle path
 */
int utc_media_player_set_subtitle_path_n(void)
{
    int ret = player_set_subtitle_path(NULL, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_bands_count_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get band count of audio equalizer
 */
int utc_media_player_audio_effect_get_equalizer_bands_count_p(void)
{
    assert(!_is_broken);
    int count = 0;

    int ret2 = player_audio_effect_get_equalizer_bands_count(player, &count);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_bands_count_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get band count of audio equalizer
 */
int utc_media_player_audio_effect_get_equalizer_bands_count_n(void)
{
    int count;

    int ret = player_audio_effect_get_equalizer_bands_count(NULL, &count);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_bands_count_n2
 * @since_tizen		5.5
 * @description		Negative test case to get band count of audio equalizer
 */
int utc_media_player_audio_effect_get_equalizer_bands_count_n2(void)
{
    assert(!_is_broken);
 	int ret = PLAYER_ERROR_NONE;
	player_state_e state = PLAYER_STATE_NONE;
    bool available = 0;

	ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (state != PLAYER_STATE_IDLE){
		player_unprepare(player);
	}

	ret = player_set_audio_codec_type(player, PLAYER_CODEC_TYPE_HW); /* H/W is optional */
	if (ret == PLAYER_ERROR_NONE) {
		int ret2 = player_audio_effect_equalizer_is_available(player, &available);
		assert_eq(ret2, PLAYER_ERROR_NONE);

		if (!available) {
			int count;
			ret2 = player_audio_effect_get_equalizer_bands_count(player, &count);
			assert_eq(ret2, PLAYER_ERROR_NOT_AVAILABLE);
		}
	}

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_set_equalizer_band_level_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set band level of audio equalizer
 */
int utc_media_player_audio_effect_set_equalizer_band_level_p(void)
{
    assert(!_is_broken);
    int count, min, max, level;

    int ret2 = player_audio_effect_get_equalizer_bands_count(player, &count);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    int ret3 = player_audio_effect_get_equalizer_level_range(player, &min, &max);
    assert_eq(ret3, PLAYER_ERROR_NONE);

    int ret4 = player_audio_effect_set_equalizer_band_level(player, count/2, min);
    assert_eq(ret4, PLAYER_ERROR_NONE);

    int ret5 = player_audio_effect_get_equalizer_band_level(player, count/2, &level);
    assert_eq(ret5, PLAYER_ERROR_NONE);

    assert_eq(level, min);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_set_equalizer_band_level_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set band level of audio equalizer
 */
int utc_media_player_audio_effect_set_equalizer_band_level_n(void)
{
    int count = 0;
    int min = 0;

    int ret = player_audio_effect_set_equalizer_band_level(NULL, count, min);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_band_level_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get band level of audio equalizer
 */
int utc_media_player_audio_effect_get_equalizer_band_level_p(void)
{
    assert(!_is_broken);
    int count, min, max, level;

    int ret2 = player_audio_effect_get_equalizer_bands_count(player, &count);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    int ret3 = player_audio_effect_get_equalizer_level_range(player, &min, &max);
    assert_eq(ret3, PLAYER_ERROR_NONE);

    int ret4 = player_audio_effect_set_equalizer_band_level(player, count/2, min);
    assert_eq(ret4, PLAYER_ERROR_NONE);

    int ret5 = player_audio_effect_get_equalizer_band_level(player, count/2, &level);
    assert_eq(ret5, PLAYER_ERROR_NONE);

    assert_eq(level, min);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_band_level_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get band level of audio equaalizer
 */
int utc_media_player_audio_effect_get_equalizer_band_level_n(void)
{
    int level;

    int ret = player_audio_effect_get_equalizer_band_level(NULL, 2, &level);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_level_range_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get level range of audio equalizer
 */
int utc_media_player_audio_effect_get_equalizer_level_range_p(void)
{
    assert(!_is_broken);
    int min, max;

    int ret2 = player_audio_effect_get_equalizer_level_range(player, &min, &max);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_level_range_n
 * @since_tizen		2.3.1
 * @description		Negative test case for getting level range of audio eqaulizer
 */
int utc_media_player_audio_effect_get_equalizer_level_range_n(void)
{
    int min, max;

    int ret = player_audio_effect_get_equalizer_level_range(NULL, &min, &max);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_set_equalizer_all_bands_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set all bands of audio equalizer
 */
int utc_media_player_audio_effect_set_equalizer_all_bands_p(void)
{
    assert(!_is_broken);
    int i;
    int count, min, max, level;

    int ret2 = player_audio_effect_get_equalizer_bands_count(player, &count);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    int ret3 = player_audio_effect_get_equalizer_level_range(player, &min, &max);
    assert_eq(ret3, PLAYER_ERROR_NONE);

    band_levels = (int*)malloc(sizeof(int) * count);
    assert(band_levels);
    for(i = 0; i < count; i++)
        band_levels[i] = min;

    int ret4 = player_audio_effect_set_equalizer_all_bands(player, band_levels, count);
    assert_eq(ret4, PLAYER_ERROR_NONE);

    for(i = 0; i < count; i++){
        int ret5 = player_audio_effect_get_equalizer_band_level(player, i, &level);
        assert_eq(ret5, PLAYER_ERROR_NONE);
        assert_eq(level, min);
    }

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_set_equalizer_all_bands_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set all bands of audio equalizer
 */
int utc_media_player_audio_effect_set_equalizer_all_bands_n(void)
{
    int ret;

    ret = player_audio_effect_set_equalizer_all_bands(player, NULL, 0);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_equalizer_clear_p
 * @since_tizen		2.3.1
 * @description		Positive test case for clearing audio equalizer
 */
int utc_media_player_audio_effect_equalizer_clear_p(void)
{
    int ret2 = player_audio_effect_equalizer_clear(player);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_equalizer_clear_n
 * @since_tizen		2.3.1
 * @description		Negative test case for clearing audio equalizer
 */
int utc_media_player_audio_effect_equalizer_clear_n(void)
{
    int ret2 = player_audio_effect_equalizer_clear(NULL);
    assert_eq(ret2, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_equalizer_is_available_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get whether audio equalizer is available or not
 */
int utc_media_player_audio_effect_equalizer_is_available_p(void)
{
    bool available = 0;

    int ret2 = player_audio_effect_equalizer_is_available(player, &available);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_equalizer_is_available_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get whether audio equalizer is available or not
 */
int utc_media_player_audio_effect_equalizer_is_available_n(void)
{
    bool available = 0;

    int ret2 = player_audio_effect_equalizer_is_available(NULL, &available);
    assert_eq(ret2, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_content_info_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get content info
 */
int utc_media_player_get_content_info_p(void)
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
    ret = player_set_uri(player, audio_path);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_uri is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_prepare is failed\\n", __LINE__, API_NAMESPACE);
    }

    int ret2 = player_get_content_info(player, PLAYER_CONTENT_INFO_ALBUM, &stream_info.album);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    int ret3 = player_get_content_info(player, PLAYER_CONTENT_INFO_ARTIST, &stream_info.artist);
    assert_eq(ret3, PLAYER_ERROR_NONE);

    int ret4 = player_get_content_info(player, PLAYER_CONTENT_INFO_AUTHOR, &stream_info.author);
    assert_eq(ret4, PLAYER_ERROR_NONE);

    int ret5 = player_get_content_info(player, PLAYER_CONTENT_INFO_GENRE, &stream_info.genre);
    assert_eq(ret5, PLAYER_ERROR_NONE);

    int ret6 = player_get_content_info(player, PLAYER_CONTENT_INFO_TITLE, &stream_info.title);
    assert_eq(ret6, PLAYER_ERROR_NONE);

    int ret7 = player_get_content_info(player, PLAYER_CONTENT_INFO_YEAR, &stream_info.year);
    assert_eq(ret7, PLAYER_ERROR_NONE);

    if((strcmp(stream_info.album, "album")==0)
      && strcmp(stream_info.artist, "singer")==0
      && strcmp(stream_info.title, "title")==0)
      _is_pass = true;

    assert(_is_pass);
    _is_pass = false;

    return 0;
}

/**
 * @testcase		utc_media_player_get_content_info_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get content info
 */
int utc_media_player_get_content_info_n(void)
{
    int ret = player_get_content_info(NULL, PLAYER_CONTENT_INFO_ALBUM, &stream_info.album);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_content_info_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to get content info
 */
int utc_media_player_get_content_info_n2(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }
    ret = player_set_uri(player, audio_path);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_uri is failed\\n", __LINE__, API_NAMESPACE);
    }
    ret = player_get_content_info(player, PLAYER_CONTENT_INFO_ALBUM, &stream_info.album);
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_get_codec_info_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get codec info
 */
int utc_media_player_get_codec_info_p(void)
{
    assert(!_is_broken);
    int ret = player_start(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_get_codec_info(player, &stream_info.audio_codec, &stream_info.video_codec);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    if ((strncmp(stream_info.audio_codec, "MPEG-4 AAC", strlen("MPEG-4 AAC")) == 0)
        && (strncmp(stream_info.video_codec, "MPEG-4 Video", strlen("MPEG-4 Video")) == 0
            || strncmp(stream_info.video_codec, "MPEG-4 video", strlen("PEG-4 video"))== 0))
      _is_pass = true;

    assert(_is_pass);
    _is_pass = false;

    int ret3 = player_stop(player);
    assert_eq(ret3, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_get_codec_info_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get codec info
 */
int utc_media_player_get_codec_info_n(void)
{
    int ret = player_get_codec_info(NULL, &stream_info.audio_codec, &stream_info.video_codec);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_codec_info_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to get codec info
 */
int utc_media_player_get_codec_info_n2(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
      PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE)
      player_unprepare(player);

    ret = player_get_codec_info(player, &stream_info.audio_codec, &stream_info.video_codec);
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_get_audio_stream_info_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get audio stream info
 */
int utc_media_player_get_audio_stream_info_p(void)
{
    assert(!_is_broken);

    int ret = player_start(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_get_audio_stream_info(player, &stream_info.audio_sample_rate, &stream_info.audio_channel,
        &stream_info.audio_bit_rate);
    assert_eq(ret2, PLAYER_ERROR_NONE);
	assert_eq(stream_info.audio_sample_rate, 48000);
    assert_eq(stream_info.audio_channel, 2);

    int ret3 = player_stop(player);
    assert_eq(ret3, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_get_audio_stream_info_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get audio stream info
 */
int utc_media_player_get_audio_stream_info_n(void)
{
    int ret = player_get_audio_stream_info(NULL, &stream_info.audio_sample_rate, &stream_info.audio_channel,
        &stream_info.audio_bit_rate);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_audio_stream_info_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to get audio stream info
 */
int utc_media_player_get_audio_stream_info_n2(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
      PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE)
      player_unprepare(player);

    ret = player_get_audio_stream_info(player, &stream_info.audio_sample_rate, &stream_info.audio_channel,
        &stream_info.audio_bit_rate);
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_get_album_art_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get album art
 */
int utc_media_player_get_album_art_p(void)
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
    ret = player_set_uri(player, audio_path);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_uri is failed\\n", __LINE__, API_NAMESPACE);
    }

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_prepare is failed\\n", __LINE__, API_NAMESPACE);
    }

    ret = player_get_album_art(player, &stream_info.album_art, &stream_info.album_art_size);
    assert_eq(ret, PLAYER_ERROR_NONE);

    if(stream_info.album_art_size == 2667)
      _is_pass = true;

    assert(_is_pass);
    _is_pass = false;

    return 0;
}

/**
 * @testcase		utc_media_player_get_album_art_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get album art
 */
int utc_media_player_get_album_art_n(void)
{
    player_h local_player = NULL;

    int ret = player_get_album_art(local_player, &stream_info.album_art, &stream_info.album_art_size);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_album_art_n2
 * @since_tizen		2.3.1
 * @description		Negative test case to get album art
 */
int utc_media_player_get_album_art_n2(void)
{
    player_state_e state;

    int ret = player_get_state (player, &state);
    if (PLAYER_ERROR_NONE != ret) {
      PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);
    }
    if (state != PLAYER_STATE_IDLE)
      player_unprepare(player);

    ret = player_get_album_art(player, &stream_info.album_art, &stream_info.album_art_size);
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_band_frequency_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get band frequency of audio equalizer
 */
int utc_media_player_audio_effect_get_equalizer_band_frequency_p(void)
{
    assert(!_is_broken);
    int frequency = 10;

    int ret = player_audio_effect_get_equalizer_band_frequency(player, 0, &frequency);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_band_frequency_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get band frequency of audio equalizer
 */
int utc_media_player_audio_effect_get_equalizer_band_frequency_n(void)
{
    int frequency = 10;

    int ret = player_audio_effect_get_equalizer_band_frequency(NULL, 0, &frequency);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_band_frequency_range_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get band frequency range of audio equalizer
 */
int utc_media_player_audio_effect_get_equalizer_band_frequency_range_p(void)
{
    assert(!_is_broken);
    int frequency = 10;

    int ret = player_audio_effect_get_equalizer_band_frequency_range(player, 0, &frequency);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_effect_get_equalizer_band_frequency_range_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get band frequency range of audio equalizer
 */
int utc_media_player_audio_effect_get_equalizer_band_frequency_range_n(void)
{
    int frequency = 10;

    int ret = player_audio_effect_get_equalizer_band_frequency_range(NULL, 0, &frequency);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_get_audio_latency_mode_p
 * @since_tizen		2.3.1
 * @description		Positive test case to get audio latency mode
 */
int utc_media_player_get_audio_latency_mode_p(void)
{
    assert(!_is_broken);
    audio_latency_mode_e latency_mode;

    int ret = player_set_audio_latency_mode(player, AUDIO_LATENCY_MODE_MID);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_get_audio_latency_mode(player, &latency_mode);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(latency_mode, AUDIO_LATENCY_MODE_MID);

    return 0;
}

/**
 * @testcase		utc_media_player_get_audio_latency_mode_n
 * @since_tizen		2.3.1
 * @description		Negative test case to get audio latency mode
 */
int utc_media_player_get_audio_latency_mode_n(void)
{
    audio_latency_mode_e *latency_mode = NULL;

    int ret = player_get_audio_latency_mode(NULL, latency_mode);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

static void player_prepared_cb_func(void *user_data) {
    _is_pass = true;
}

/**
 * @testcase		utc_media_player_prepare_async_p
 * @since_tizen		2.3.1
 * @description		Positive test case to prepare player asynchronously
 */
int utc_media_player_prepare_async_p(void)
{
#define PREPARE_MAX_TIMEOUT 5
    int ret;
    int repeat = 0;

    assert(!_is_broken);

    ret = player_unprepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, media_path);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare_async(player, player_prepared_cb_func, NULL);
    assert_eq(ret, PLAYER_ERROR_NONE);

    for (repeat = 0; repeat < PREPARE_MAX_TIMEOUT; repeat++) {
        wait_for_async(FALSE);
        if (_is_pass)
            break;
    }
    assert(_is_pass);
    _is_pass = false;

    return 0;
}

/**
 * @testcase		utc_media_player_prepare_async_n
 * @since_tizen		2.3.1
 * @description		Negative test case to prepare player asynchronously
 */
int utc_media_player_prepare_async_n(void)
{
    int ret = player_prepare_async(NULL, player_prepared_cb_func, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_audio_latency_mode_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set audio latency mode
 */
int utc_media_player_set_audio_latency_mode_p(void)
{
    assert(!_is_broken);
    audio_latency_mode_e latency_mode = AUDIO_LATENCY_MODE_LOW;
    audio_latency_mode_e get_latency_mode;

    int ret = player_set_audio_latency_mode(player, latency_mode);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_get_audio_latency_mode(player, &get_latency_mode);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(get_latency_mode, latency_mode);

    return 0;
}

/**
 * @testcase		utc_media_player_set_audio_latency_mode_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set audio latency mode
 */
int utc_media_player_set_audio_latency_mode_n(void)
{
    int ret = player_set_audio_latency_mode(NULL, AUDIO_LATENCY_MODE_MID);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_streaming_user_agent_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set streaming user agent
 */
int utc_media_player_set_streaming_user_agent_p(void)
{
    assert(!_is_broken);
    const char *user_agent = "123456789";

    int ret = player_unprepare(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_set_streaming_user_agent(player, user_agent, strlen(user_agent)+1);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    int ret3 = player_prepare(player);
    assert_eq(ret3, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_streaming_user_agent_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set streaming user agent
 */
int utc_media_player_set_streaming_user_agent_n(void)
{
    const char *user_agent = "123456789";

    int ret = player_set_streaming_user_agent(NULL, user_agent, strlen(user_agent)+1);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_subtitle_position_offset_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set subtitle position offset
 */
int utc_media_player_set_subtitle_position_offset_p(void)
{
  assert(!_is_broken);

  int ret = player_set_subtitle_path(player, subtitle_path);
  assert_eq(ret, PLAYER_ERROR_NONE);

  ret = player_start(player);
  assert_eq(ret, PLAYER_ERROR_NONE);

  ret = player_set_subtitle_position_offset(player, 5);
  assert_eq(ret, PLAYER_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_media_player_set_subtitle_position_offset_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set subtitle position offset
 */
int utc_media_player_set_subtitle_position_offset_n(void)
{
  int ret = player_set_subtitle_position_offset(player, 5);
  assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

  return 0;
}

/**
 * @testcase		utc_player_get_current_track_p
 * @since_tizen		2.4
 * @description		Positive test case to get current track
 */
int utc_player_get_current_track_p(void)
{
  int cur_index = 0;

  int ret = player_get_current_track (player, PLAYER_STREAM_TYPE_AUDIO, &cur_index);
  assert_eq(ret, PLAYER_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_player_get_current_track_n
 * @since_tizen		2.4
 * @description		Negative test case to get current track
 */
int utc_player_get_current_track_n(void)
{
  int cur_index = 0;

  int ret = player_get_current_track (player, 5, &cur_index);
  assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_player_get_current_track_n2
 * @since_tizen		2.4
 * @description		Negative test case to get current track
 */
int utc_player_get_current_track_n2(void)
{
  int cur_index = 0;

  int ret = player_unprepare(player);
  assert_eq(ret, PLAYER_ERROR_NONE);

  ret = player_get_current_track (player, PLAYER_STREAM_TYPE_AUDIO, &cur_index);
  assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

  return 0;
}

/**
 * @testcase		utc_player_get_track_language_code_p
 * @since_tizen		2.4
 * @description		Positive test case to get track language code
 */
int utc_player_get_track_language_code_p(void)
{
  int ret = player_get_track_language_code(player, PLAYER_STREAM_TYPE_AUDIO, 0, &code);
  assert_eq(ret, PLAYER_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_player_get_track_language_code_n
 * @since_tizen		2.4
 * @description		Negative test case to get track language code
 */
int utc_player_get_track_language_code_n(void)
{
  int ret = player_get_track_language_code(player, PLAYER_STREAM_TYPE_TEXT, 0, &code);
  assert_eq(ret, PLAYER_ERROR_INVALID_OPERATION);

  return 0;
}

/**
 * @testcase		utc_player_get_track_language_code_n2
 * @since_tizen		2.4
 * @description		Negative test case to get track language code
 */
int utc_player_get_track_language_code_n2(void)
{
  int ret = player_unprepare(player);
  assert_eq(ret, PLAYER_ERROR_NONE);

  ret = player_get_track_language_code(player, PLAYER_STREAM_TYPE_AUDIO, 0, &code);
  assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

  return 0;
}

/**
 * @testcase		utc_player_get_track_count_p
 * @since_tizen		2.4
 * @description		Positive test case to get track count
 */
int utc_player_get_track_count_p(void)
{
  int count = 0;

  int ret = player_get_track_count (player, PLAYER_STREAM_TYPE_TEXT, &count);
  assert_eq(ret, PLAYER_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_player_get_track_count_n
 * @since_tizen		2.4
 * @description		Negative test case to get track count
 */
int utc_player_get_track_count_n(void)
{
  int count = 0;

  int ret = player_unprepare(player);
  assert_eq(ret, PLAYER_ERROR_NONE);

  ret = player_get_track_count (player, PLAYER_STREAM_TYPE_TEXT, &count);
  assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

  return 0;
}

/**
 * @testcase		utc_player_get_track_count_n2
 * @since_tizen		2.4
 * @description		Negative test case to get track count
 */
int utc_player_get_track_count_n2(void)
{
  int count = 0;

  int ret = player_get_track_count (player, 10, &count);
  assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_player_select_track_p
 * @since_tizen		2.4
 * @description		Positive test case for selecting track
 */
int utc_player_select_track_p(void)
{
  int ret = player_select_track (player, PLAYER_STREAM_TYPE_TEXT, 0);
  assert_eq(ret, PLAYER_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_player_select_track_n
 * @since_tizen		2.4
 * @description		Negative test case for selecting track
 */
int utc_player_select_track_n(void)
{
  int ret = player_unprepare(player);
  assert_eq(ret, PLAYER_ERROR_NONE);

  ret = player_select_track (player, PLAYER_STREAM_TYPE_TEXT, 0);
  assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

  return 0;
}

/**
 * @testcase		utc_player_select_track_n2
 * @since_tizen		2.4
 * @description		Negative test case for selecting track
 */
int utc_player_select_track_n2(void)
{
  int ret = player_select_track (player, 5, 0);
  assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_media_player_set_replaygain_enabled_p
 * @since_tizen		5.0
 * @description		Positive test case to set replaygain enabled
 */
int utc_media_player_set_replaygain_enabled_p(void)
{
    assert(!_is_broken);

    bool is = false;
    bool enabled = false;

    int ret = player_is_replaygain_enabled(player, &is);
    if (ret != PLAYER_ERROR_NONE) {
        PRINT_UTC_LOG("[Line : %d][%s] player_is_replaygain_enabled is failed\\n", __LINE__, API_NAMESPACE);
    }
    if(!is)
      enabled = true;
    else
      enabled = false;
    ret = player_set_replaygain_enabled(player, enabled);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_is_replaygain_enabled(player, &is);
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(is, enabled);

    return 0;
}

/**
 * @testcase		utc_media_player_set_replaygain_enabled_n
 * @since_tizen		5.0
 * @description		Negative test case to set replaygain enabled
 */
int utc_media_player_set_replaygain_enabled_n(void)
{
    bool enabled = false;

    int ret = player_set_replaygain_enabled(NULL, enabled);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_is_replaygain_enabled_p
 * @since_tizen		5.0
 * @description		Positive test case to get whether replaygain enabled or not
 */
int utc_media_player_is_replaygain_enabled_p(void)
{
    assert(!_is_broken);
    bool enabled = false;
    bool is = true;

    int ret = player_set_replaygain_enabled(player, enabled);
    assert_eq(ret, PLAYER_ERROR_NONE);

    int ret2 = player_is_replaygain_enabled(player, &is);
    assert_eq(ret2, PLAYER_ERROR_NONE);
    assert_eq(is, enabled);

    return 0;
}

/**
 * @testcase		utc_media_player_is_replaygain_enabled_n
 * @since_tizen		5.0
 * @description		Negative test case to get whether replaygain enabled or not
 */
int utc_media_player_is_replaygain_enabled_n(void)
{
    bool enabled;

    int ret = player_is_replaygain_enabled(NULL, &enabled);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_pitch_set_get_enabled_p
 * @since_tizen		5.5
 * @description		Positive test case to enable the audio pitch control fucntion
 */
int utc_media_player_audio_pitch_set_get_enabled_p(void)
{
    assert(!_is_broken);

	int ret = PLAYER_ERROR_NONE;
    bool is = false;
    bool enabled = false;
	player_state_e state = PLAYER_STATE_NONE;

    ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    ret = player_audio_pitch_is_enabled(player, &is);
    assert_eq(ret, PLAYER_ERROR_NONE);

    if(is)
      enabled = false;
    else
      enabled = true;

    ret = player_audio_pitch_set_enabled(player, enabled);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_audio_pitch_is_enabled(player, &is);
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(is, enabled);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_pitch_set_enabled_n
 * @since_tizen		5.5
 * @description		Negative test case to audio pitch set enabled
 */
int utc_media_player_audio_pitch_set_enabled_n(void)
{
	int ret = PLAYER_ERROR_NONE;
    bool enabled = false;
	player_state_e state = PLAYER_STATE_NONE;

    ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

    ret = player_audio_pitch_set_enabled(NULL, enabled);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_pitch_set_enabled_n2
 * @since_tizen		5.5
 * @description		Negative test case to audio pitch set enabled
 */
int utc_media_player_audio_pitch_set_enabled_n2(void)
{
	int ret = PLAYER_ERROR_NONE;
	player_state_e state = PLAYER_STATE_NONE;

    ret = player_get_state(player, &state);
    assert_eq(ret, PLAYER_ERROR_NONE);

    if (state == PLAYER_STATE_IDLE){
		ret = player_prepare(player);
		assert_eq(ret, PLAYER_ERROR_NONE);
	}

	ret = player_audio_pitch_set_enabled(player, true);
	assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_pitch_is_enabled_n
 * @since_tizen		5.5
 * @description		Negative test case to get whether the audio pitch is enabled or not
 */
int utc_media_player_audio_pitch_is_enabled_n(void)
{
    bool enabled;

    int ret = player_audio_pitch_is_enabled(NULL, &enabled);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_pitch_set_value_p
 * @since_tizen		5.5
 * @description		Positive test case to set audio pitch value
 */
int utc_media_player_audio_pitch_set_value_p(void)
{
	int ret = PLAYER_ERROR_NONE;
	player_state_e state = PLAYER_STATE_NONE;

	ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (state != PLAYER_STATE_IDLE){
		player_unprepare(player);
	}

	ret = player_set_uri(player, audio_path);
	if (PLAYER_ERROR_NONE != ret) {
		PRINT_UTC_LOG("[Line : %d][%s] player_set_uri is failed\\n", __LINE__, API_NAMESPACE);
	}

	ret = player_audio_pitch_set_enabled(player, true);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_audio_pitch_set_value(player, 0.9);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_prepare(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_audio_pitch_set_value(player, 1.5);
	assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_player_audio_pitch_set_value_n
 * @since_tizen		5.5
 * @description		Negative test case to set the audio pitch value
 */
int utc_media_player_audio_pitch_set_value_n(void)
{
    float pitch = 3.3f;

    int ret = player_audio_pitch_set_value(player, pitch);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_pitch_get_value_p
 * @since_tizen		5.5
 * @description		Positive test case to get the audio pitch value
 */
int utc_media_player_audio_pitch_get_value_p(void)
{
	int ret = PLAYER_ERROR_NONE;
	player_state_e state = PLAYER_STATE_NONE;
	float value = 0;

    ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

    if (state != PLAYER_STATE_IDLE){
        player_unprepare(player);
    }

	ret = player_audio_pitch_set_enabled(player, true);
	assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_audio_pitch_set_value(player, 0.9f);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_audio_pitch_get_value(player, &value);
    assert_eq(ret, PLAYER_ERROR_NONE);
    assert_eq(value, 0.9f);

    return 0;
}

/**
 * @testcase		utc_media_player_audio_pitch_get_value_n
 * @since_tizen		5.5
 * @description		Negative test case to get the audio pitch value
 */
int utc_media_player_audio_pitch_get_value_n(void)
{
    float pitch = 0;

    int ret = player_audio_pitch_get_value(NULL, &pitch);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase        utc_media_player_audio_offload_foreach_supported_format_p
 * @since_tizen     5.5
 * @description     Positive test case to retrieve audio offload format info
 */
int utc_media_player_audio_offload_foreach_supported_format_p(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;

	ret = player_audio_offload_foreach_supported_format(player, _audio_offload_format_cb, player);
	if (!_check_audio_offload_feature()) {
		assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}
	assert_eq(ret, PLAYER_ERROR_NONE);

	wait_for_async(FALSE);
	assert(_is_pass);
	_is_pass = false;

	return 0;
}

/**
 * @testcase        utc_media_player_audio_offload_foreach_supported_format_n
 * @since_tizen     5.5
 * @description     Negative test case to retrieve audio offload format info
 */
int utc_media_player_audio_offload_foreach_supported_format_n(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;

	ret = player_audio_offload_foreach_supported_format(player, NULL, player);
	if (!_check_audio_offload_feature()) {
		assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_media_player_audio_offload_set_get_enabled_p
 * @since_tizen     5.5
 * @description     Positive test case to enable the audio offload
 */
int utc_media_player_audio_offload_set_get_enabled_p(void)
{
	assert(!_is_broken);

	int ret = PLAYER_ERROR_NONE;
	bool is_enabled = false;
	bool enabled = true;
	player_state_e state = PLAYER_STATE_NONE;

	ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (state != PLAYER_STATE_IDLE){
		player_unprepare(player);
	}

	ret = player_audio_offload_set_enabled(player, enabled);
	if (!_check_audio_offload_feature()) {
		assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_audio_offload_is_enabled(player, &is_enabled);
	assert_eq(ret, PLAYER_ERROR_NONE);
	assert_eq(is_enabled, enabled);

	return 0;
}

/**
 * @testcase        utc_media_player_audio_offload_set_enabled_n
 * @since_tizen     5.5
 * @description     Negative test case to enable the audio offload
 */
int utc_media_player_audio_offload_set_enabled_n(void)
{
	int ret = PLAYER_ERROR_NONE;
	bool enabled = false;
	player_state_e state = PLAYER_STATE_NONE;

	ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (state != PLAYER_STATE_IDLE){
		player_unprepare(player);
	}

	ret = player_audio_offload_set_enabled(NULL, enabled);
	if (!_check_audio_offload_feature()) {
		assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_media_player_audio_offload_set_enabled_n2
 * @since_tizen     5.5
 * @description     Negative test case to audio pitch set enabled
 */
int utc_media_player_audio_offload_set_enabled_n2(void)
{
	int ret = PLAYER_ERROR_NONE;
	player_state_e state = PLAYER_STATE_NONE;

	ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (state == PLAYER_STATE_IDLE){
		ret = player_prepare(player);
		assert_eq(ret, PLAYER_ERROR_NONE);
	}

	ret = player_audio_offload_set_enabled(player, true);
	if (!_check_audio_offload_feature()) {
		assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	assert_eq(ret, PLAYER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase        utc_media_player_audio_offload_is_enabled_n
 * @since_tizen     5.5
 * @description     Negative test case to get whether the audio offload is enabled or not
 */
int utc_media_player_audio_offload_is_enabled_n(void)
{
	bool enabled;

	int ret = player_audio_offload_is_enabled(NULL, &enabled);
	if (!_check_audio_offload_feature()) {
		assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_media_player_audio_offload_is_activated_p
 * @since_tizen     5.5
 * @description     Positive test case to get whether the audio offload is activated or not
 */
int utc_media_player_audio_offload_is_activated_p(void)
{
	assert(!_is_broken);

	int ret = PLAYER_ERROR_NONE;
	bool is_activated = true;
	player_state_e state = PLAYER_STATE_NONE;

	ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (state != PLAYER_STATE_IDLE){
		ret = player_audio_offload_is_activated(player, &is_activated);
		if (!_check_audio_offload_feature()) {
			assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
			return 0;
		}
		assert_eq(ret, PLAYER_ERROR_NONE);
		assert_eq(is_activated, false);
		player_unprepare(player);
	}

	ret = player_set_uri(player, audio_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_audio_offload_set_enabled(player, true);
	if (!_check_audio_offload_feature()) {
		assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_prepare(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_audio_offload_is_activated(player, &is_activated);
	assert_eq(ret, PLAYER_ERROR_NONE);
	assert_eq(is_activated, true);

	return 0;
}

/**
 * @testcase        utc_media_player_audio_offload_is_activated_n
 * @since_tizen     5.5
 * @description     Negative test case to get whether the audio offload is activated or not
 */
int utc_media_player_audio_offload_is_activated_n(void)
{
	assert(!_is_broken);

	int ret = PLAYER_ERROR_NONE;
	bool is_activated = true;
	player_state_e state = PLAYER_STATE_NONE;

	ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (state != PLAYER_STATE_IDLE){
		player_unprepare(player);
	}

	ret = player_audio_offload_is_activated(player, &is_activated);
	if (!_check_audio_offload_feature()) {
		assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	assert_eq(ret, PLAYER_ERROR_INVALID_STATE);
	return 0;
}

/**
 * @testcase        utc_media_player_audio_offload_is_activated_n2
 * @since_tizen     5.5
 * @description     Negative test case to get whether the audio offload is activated or not
 */
int utc_media_player_audio_offload_is_activated_n2(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;

	ret = player_audio_offload_is_activated(player, NULL);
	if (!_check_audio_offload_feature()) {
		assert_eq(ret, PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE);
		return 0;
	}

	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase        utc_media_player_set_audio_codec_type_p
 * @since_tizen     5.5
 * @description     Positive test case to set the audio codec type
 */
int utc_media_player_set_audio_codec_type_p(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;
	player_state_e state = PLAYER_STATE_NONE;

	ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (state != PLAYER_STATE_IDLE){
		player_unprepare(player);
	}

	ret = player_set_audio_codec_type(player, PLAYER_CODEC_TYPE_HW); /* H/W is optional */
	if (ret != PLAYER_ERROR_NONE && ret != PLAYER_ERROR_NOT_SUPPORTED_AUDIO_CODEC)
		return 1;

	ret = player_set_audio_codec_type(player, PLAYER_CODEC_TYPE_SW);
	assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;
}

/**
 * @testcase        utc_media_player_set_audio_codec_type_n
 * @since_tizen     5.5
 * @description     Negative test case to set the audio codec type
 */
int utc_media_player_set_audio_codec_type_n(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;
	player_state_e state = PLAYER_STATE_NONE;

	ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (state != PLAYER_STATE_IDLE){
		ret = player_set_audio_codec_type(player, PLAYER_CODEC_TYPE_SW);
		assert_eq(ret, PLAYER_ERROR_INVALID_STATE);
		player_unprepare(player);
	}

	ret = player_set_audio_codec_type(NULL, PLAYER_CODEC_TYPE_SW);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase        utc_media_player_get_audio_codec_type_p
 * @since_tizen     5.5
 * @description     Positive test case to get the audio codec type
 */
int utc_media_player_get_audio_codec_type_p(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;
	player_state_e state = PLAYER_STATE_NONE;
	player_codec_type_e type;

	ret = player_get_audio_codec_type(player, &type);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (type != PLAYER_CODEC_TYPE_HW && type != PLAYER_CODEC_TYPE_SW)
		return 1;

	ret = player_get_state(player, &state);
	assert_eq(ret, PLAYER_ERROR_NONE);

	if (state != PLAYER_STATE_IDLE)
		player_unprepare(player);

	ret = player_set_audio_codec_type(player, PLAYER_CODEC_TYPE_SW);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_get_audio_codec_type(player, &type);
	assert_eq(ret, PLAYER_ERROR_NONE);
	assert_eq(type, PLAYER_CODEC_TYPE_SW);

	return 0;
}

/**
 * @testcase        utc_media_player_get_audio_codec_type_n
 * @since_tizen     5.5
 * @description     Negative test case to get the audio codec type
 */
int utc_media_player_get_audio_codec_type_n(void)
{
	assert(!_is_broken);
	int ret = PLAYER_ERROR_NONE;
	player_state_e state = PLAYER_STATE_NONE;
	player_codec_type_e type;

	ret = player_get_audio_codec_type(player, NULL);
	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}
