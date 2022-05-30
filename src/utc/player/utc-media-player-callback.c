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
#include <glib.h>
#include <storage.h>
#include <string.h>
#include "tct_common.h"
#include "net_connection.h"

#define API_NAMESPACE			"[PLAYER]"

#define UTC_EXPORT_PCM_SAMPLERATE  44100
#define UTC_EXPORT_PCM_STEREO      2
#define UTC_EXPORT_PCM_MONO        1

extern bool get_value_from_config(char* key, char* value);
extern bool check_network_supportable(void);
extern bool check_connection_statistics(connection_h connection, long long *size);
extern bool check_online_status(char *media_path);

//& set: MediaPlayerCallback

static player_h player = NULL;
static connection_h connection = NULL;

static bool _is_broken = false;
static bool _is_pass = false;

static char* media = "test.mp4";
static char* subtitle = "subtitles_test_file.srt";
static char* media_path = NULL;
static char* subtitle_path = NULL;
static char media_download_path[CONFIG_VALUE_LEN_MAX] = {0,};

#define INVALID_PATH "http://aaa.bbb.ccc/fake.mp4"

static GMainLoop *g_mainloop = NULL;
static gboolean timeout_func(gpointer data)
{
    PRINT_UTC_LOG("[Line : %d][%s] waited 5 seconds\\n", __LINE__, API_NAMESPACE);
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

static int _player_prepare_with_connection_check(char *media_path)
{
	int ret = PLAYER_ERROR_NONE;
	long long before = 0, after = 0;

	if (!check_online_status(media_path)) {
		PRINT_UTC_LOG("[Line : %d][%s][Reference] network is disconnected\\n", __LINE__, API_NAMESPACE);
	}

	if (connection_create(&connection) != CONNECTION_ERROR_NONE) {
		PRINT_UTC_LOG("[Line : %d][%s] Failed to create connection handle\\n", __LINE__, API_NAMESPACE);
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] Success to create connection handle %p\\n", __LINE__, API_NAMESPACE, connection);
	}

	if (connection && !check_connection_statistics(connection, &before)) {
		PRINT_UTC_LOG("[Line : %d][%s] Failed to get connection statistics\\n", __LINE__, API_NAMESPACE);
	}

	ret = player_prepare(player);

	if (connection) {
		if (!check_connection_statistics(connection, &after)) {
			PRINT_UTC_LOG("[Line : %d][%s] Failed to get connection statistics\\n", __LINE__, API_NAMESPACE);
		} else {
			PRINT_UTC_LOG("[Line : %d][%s][Reference] total received data [%lld]\\n", __LINE__, API_NAMESPACE, (after-before));
		}
	}

	if (ret != PLAYER_ERROR_NONE) {
		PRINT_UTC_LOG("[Line : %d][%s] Failed to player_prepare 0x%X\\n", __LINE__, API_NAMESPACE, ret);
	}

	if (connection && (connection_destroy(connection) != CONNECTION_ERROR_NONE)) {
		PRINT_UTC_LOG("[Line : %d][%s] Failed to destroy connection handle\\n", __LINE__, API_NAMESPACE);
	}

	return ret;
}

/**
 * @function		utc_media_player_callback_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_callback_startup(void)
{
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	unsigned int size_of_path = 0;
	if (true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE)) {
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		size_of_path = strlen(pszValue) + strlen(media) + 11;
		media_path = (char*)malloc(size_of_path);

		if (media_path) {
			snprintf(media_path, size_of_path, "%s/res/res/%s", pszValue, media);
		} else {
			PRINT_UTC_LOG("[Line : %d][%s] failed to alloc mem for test content path.\\n", __LINE__, API_NAMESPACE);
			goto ERROR;
		}

		size_of_path = strlen(pszValue) + strlen(subtitle) + 11;
		subtitle_path = (char*)malloc(size_of_path);
		if (subtitle_path) {
			snprintf(subtitle_path, size_of_path, "%s/res/res/%s", pszValue, subtitle);
		} else {
			PRINT_UTC_LOG("[Line : %d][%s] failed to alloc mem for test subtitle path.\n", __LINE__, API_NAMESPACE);
			goto ERROR;
		}
	} else {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
		goto ERROR;
	}

	if (true != get_value_from_config("PLAYER_HTTP_STREAMING_URL", media_download_path)) {
		PRINT_UTC_LOG("[Line : %d][%s] Failed to get value from config\\n", __LINE__, API_NAMESPACE);
		goto ERROR;
	}

	_is_broken = false;
	_is_pass = false;

	int ret = player_create(&player);
	if (PLAYER_ERROR_NONE != ret) {
		goto ERROR;
	}

	ret = player_set_uri(player, media_path);
	if (PLAYER_ERROR_NONE != ret) {
		PRINT_UTC_LOG("[Line : %d][%s] player didn't set uri\\n", __LINE__, API_NAMESPACE);
		goto ERROR;
	}
	return;

ERROR:
	_is_broken = true;

	if (media_path) free(media_path);
	if (subtitle_path) free(subtitle_path);

	media_path = subtitle_path = NULL;
	return;

}

/**
 * @function		utc_media_player_callback_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_player_callback_cleanup(void)
{
	player_state_e state = PLAYER_STATE_IDLE;
	int ret = PLAYER_ERROR_NONE;

	if (player) {
		ret = player_get_state(player, &state);
		if (PLAYER_ERROR_NONE != ret)
			PRINT_UTC_LOG("[Line : %d][%s] player_get_state is failed\\n", __LINE__, API_NAMESPACE);

		if (state != PLAYER_STATE_IDLE)
			player_unprepare(player);

		player_destroy(player);
		player = NULL;
	}

	if (media_path) free(media_path);
	if (subtitle_path) free(subtitle_path);

	media_path = subtitle_path = NULL;
}

static void player_complete_cb(void *data)
{
}

static void player_buffer_cb(int percent, void *data)
{
	if (percent >= 5)
		_is_pass = TRUE;
}

static void player_error_callback(int error_code, void *data)
{
	if (error_code != PLAYER_ERROR_NONE)
		_is_pass = TRUE;
}

static void player_interrupt_cb(player_interrupted_code_e code, void *data)
{
}

static  void player_subtitle_update_cb(unsigned long duration, char *text, void *user_data)
{
	if (duration > 10)
		_is_pass = TRUE;
}

static void player_audio_decoded_cb(media_packet_h pkt, void *user_data)
{
	media_format_h aformat = NULL;
	int mime, channel, rate;
	uint64_t channel_mask;
	static uint64_t mask = 0;

	if (!pkt) {
		PRINT_UTC_LOG("[Line : %d][%s] invalid pkt\n", __LINE__, API_NAMESPACE);
		return;
	}

	media_packet_get_format(pkt, &aformat);
	media_format_get_audio_info(aformat, (media_format_mimetype_e *)&mime, &channel, &rate, NULL, NULL);
	media_format_get_audio_channel_mask(aformat, &channel_mask);

	if (mask == 0) {
		mask = channel_mask;
	}

	if ((mime == MEDIA_FORMAT_PCM_S16LE) &&
		(rate == UTC_EXPORT_PCM_SAMPLERATE) &&
		(channel == UTC_EXPORT_PCM_MONO) && (mask != channel_mask)) { // opt : PLAYER_AUDIO_EXTRACT_DEINTERLEAVE
		_is_pass = true;
	}

	media_packet_destroy(pkt);
}

static void player_media_packet_decoded_cb(media_packet_h pkt, void *user_data)
{
    media_packet_destroy(pkt);
}

/**
 * @testcase		utc_media_player_set_buffering_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set buffering callback
 */
int utc_media_player_set_buffering_cb_p(void)
{
	assert(!_is_broken);

	int repeat = 0;
	bool _is_network_supportable = check_network_supportable();

	int ret = player_set_uri(player, media_download_path);
	if ((ret == PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE) &&
		(!_is_network_supportable)) {
		PRINT_UTC_LOG("[Line : %d][%s] network is not supportable.\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_set_buffering_cb(player, player_buffer_cb, NULL);
	if ((ret == PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE) &&
		(!_is_network_supportable)) {
		PRINT_UTC_LOG("[Line : %d][%s] network is not supportable.\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = _player_prepare_with_connection_check(media_download_path);
	assert_eq(ret, PLAYER_ERROR_NONE);

	for (repeat = 0 ; repeat < 11 ; repeat++) {
		wait_for_async();
		if (_is_pass)
			break;
	}
	assert(_is_pass);
	_is_pass = false;

	return 0;
}

/**
 * @testcase		utc_media_player_set_buffering_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set buffering callback
 */
int utc_media_player_set_buffering_cb_n(void)
{
    int ret = player_set_buffering_cb(NULL, player_buffer_cb, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_buffering_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case to unset buffering callback
 */
int utc_media_player_unset_buffering_cb_p(void)
{
    assert(!_is_broken);

    int ret2 = player_unset_buffering_cb(player);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_buffering_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case to unset buffering callback
 */
int utc_media_player_unset_buffering_cb_n(void)
{
    int ret = player_unset_buffering_cb(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_completed_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set completed callback
 */
int utc_media_player_set_completed_cb_p(void)
{
    assert(!_is_broken);
    int ret = player_set_completed_cb(player, player_complete_cb, NULL);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);

    ret = player_start(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't started\\n", __LINE__, API_NAMESPACE);

    ret = player_stop(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't stopped\\n", __LINE__, API_NAMESPACE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_completed_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set completed callback
 */
int utc_media_player_set_completed_cb_n(void)
{
    int ret = player_set_completed_cb(NULL, player_complete_cb, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_completed_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case to unset completed callback
 */
int utc_media_player_unset_completed_cb_p(void)
{
    assert(!_is_broken);

    int ret2 = player_unset_completed_cb(player);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_completed_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case to unset completed callback
 */
int utc_media_player_unset_completed_cb_n(void)
{
    int ret = player_unset_completed_cb(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_error_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set error callback
 */
int utc_media_player_set_error_cb_p(void)
{
    assert(!_is_broken);
    int repeat = 0;
    int ret = player_set_error_cb(player, player_error_callback, NULL);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_set_uri(player, INVALID_PATH);
    if (PLAYER_ERROR_NONE != ret) {
        PRINT_UTC_LOG("[Line : %d][%s] player_set_uri is failed\\n", __LINE__, API_NAMESPACE);
    }
    player_prepare_async(player, player_complete_cb, NULL);

    for(repeat=0; repeat<5; repeat++) {
        wait_for_async();
        if(_is_pass)
            break;
    }
    assert(_is_pass);
    _is_pass = false;

    return 0;
}

/**
 * @testcase		utc_media_player_set_error_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set error callback
 */
int utc_media_player_set_error_cb_n(void)
{
    int ret = player_set_error_cb(NULL, player_error_callback, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_error_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case to unset error callback
 */
int utc_media_player_unset_error_cb_p(void)
{
    assert(!_is_broken);

    int ret2 = player_unset_error_cb(player);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_error_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case to unset error callback
 */
int utc_media_player_unset_error_cb_n(void)
{
    int ret = player_unset_error_cb(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_interrupted_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set interrupted callback
 */
int utc_media_player_set_interrupted_cb_p(void)
{
    assert(!_is_broken);
    int ret = player_set_interrupted_cb(player, player_interrupt_cb, NULL);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);

    ret = player_start(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't started\\n", __LINE__, API_NAMESPACE);

    ret = player_stop(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't stopped\\n", __LINE__, API_NAMESPACE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_interrupted_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set interrupted callback
 */
int utc_media_player_set_interrupted_cb_n(void)
{
    void* user_data = NULL;

    int ret = player_set_interrupted_cb(player, NULL, user_data);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_interrupted_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case to unset interrupted callback
 */
int utc_media_player_unset_interrupted_cb_p(void)
{
    assert(!_is_broken);

    int ret2 = player_unset_interrupted_cb(player);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_interrupted_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case to unset interrupted callback
 */
int utc_media_player_unset_interrupted_cb_n(void)
{
    int ret = player_unset_interrupted_cb(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_subtitle_updated_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case to set subtitle updated callback
 */
int utc_media_player_set_subtitle_updated_cb_p(void)
{
    assert(!_is_broken);

    int repeat = 0;
    int ret = player_set_subtitle_path(player, subtitle_path);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] subtitle path isn't set\\n", __LINE__, API_NAMESPACE);

    ret = player_set_subtitle_updated_cb(player, player_subtitle_update_cb, NULL);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);

    ret = player_start(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't started\\n", __LINE__, API_NAMESPACE);

    for(repeat=0; repeat<5; repeat++) {
        wait_for_async();
        if(_is_pass)
            break;
    }
    assert(_is_pass);
    _is_pass = false;

    ret = player_stop(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't stopped\\n", __LINE__, API_NAMESPACE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_subtitle_updated_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case to set subtitle updated callback
 */
int utc_media_player_set_subtitle_updated_cb_n(void)
{
    int ret = player_set_subtitle_updated_cb(player, NULL, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_subtitle_updated_cb_p
 * @since_tizen		2.3.1
 * @description		Positive test case to unset subtitle updated callback
 */
int utc_media_player_unset_subtitle_updated_cb_p(void)
{
    assert(!_is_broken);

    int ret2 = player_unset_subtitle_updated_cb(player);
    assert_eq(ret2, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_subtitle_updated_cb_n
 * @since_tizen		2.3.1
 * @description		Negative test case to unset subtitle updated callback
 */
int utc_media_player_unset_subtitle_updated_cb_n(void)
{
    int ret = player_unset_subtitle_updated_cb(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_media_packet_audio_frame_decoded_cb_p
 * @since_tizen		5.5
 * @description		Positive test case to set media packet audio frame decoded callback
 */
int utc_media_player_set_media_packet_audio_frame_decoded_cb_p(void)
{
	int ret = PLAYER_ERROR_NONE;
	media_format_h aformat = NULL;
	int repeat = 0;

	media_format_create(&aformat);
	media_format_set_audio_mime(aformat, MEDIA_FORMAT_PCM_S16LE);
	media_format_set_audio_channel(aformat, UTC_EXPORT_PCM_STEREO);
	media_format_set_audio_samplerate(aformat, UTC_EXPORT_PCM_SAMPLERATE);

	ret = player_set_media_packet_audio_frame_decoded_cb(player, aformat, PLAYER_AUDIO_EXTRACT_DEINTERLEAVE, player_audio_decoded_cb, NULL);
	media_format_unref(aformat);
	aformat = NULL;

	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_prepare(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_start(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	for(repeat = 0; repeat < 5; repeat++) {
		wait_for_async();
		if(_is_pass)
			break;
	}
	assert(_is_pass);
	_is_pass = false;

	ret = player_stop(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_player_set_media_packet_audio_frame_decoded_cb_n
 * @since_tizen		5.5
 * @description		Negative test case to set media packet audio frame decoded callback
 */
int utc_media_player_set_media_packet_audio_frame_decoded_cb_n(void)
{
	int ret = PLAYER_ERROR_NONE;
	media_format_h aformat = NULL;

	media_format_create(&aformat);
	media_format_set_audio_mime(aformat, MEDIA_FORMAT_PCMU); /* not support format */
	media_format_set_audio_channel(aformat, UTC_EXPORT_PCM_STEREO);
	media_format_set_audio_samplerate(aformat, UTC_EXPORT_PCM_SAMPLERATE);

	ret = player_set_media_packet_audio_frame_decoded_cb(player, aformat, PLAYER_AUDIO_EXTRACT_DEINTERLEAVE, player_audio_decoded_cb, NULL);
	media_format_unref(aformat);
	aformat = NULL;

	assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_player_set_media_packet_audio_frame_decoded_cb_n2
 * @since_tizen		5.5
 * @description		Negative test case to set media packet audio frame decoded callback
 */
int utc_media_player_set_media_packet_audio_frame_decoded_cb_n2(void)
{
	int ret = PLAYER_ERROR_NONE;

	ret = player_prepare(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_set_media_packet_audio_frame_decoded_cb(player, NULL, PLAYER_AUDIO_EXTRACT_DEFAULT, player_audio_decoded_cb, NULL);
	assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

	return 0;
}

/**
 * @testcase		utc_media_player_set_media_packet_audio_frame_decoded_cb_n3
 * @since_tizen		5.5
 * @description		Negative test case to set media packet audio frame decoded callback
 */
int utc_media_player_set_media_packet_audio_frame_decoded_cb_n3(void)
{
	int ret = PLAYER_ERROR_NONE;

	ret = player_set_audio_codec_type(player, PLAYER_CODEC_TYPE_HW); /* H/W is optional */
	if (ret == PLAYER_ERROR_NONE) {
		int ret2 = player_set_media_packet_audio_frame_decoded_cb(player, NULL, PLAYER_AUDIO_EXTRACT_DEFAULT, player_audio_decoded_cb, NULL);
		if (ret2 != PLAYER_ERROR_NONE && ret2 != PLAYER_ERROR_NOT_AVAILABLE)
			return 1;
	}

	return 0;
}

/**
 * @testcase		utc_media_player_unset_media_packet_audio_frame_decoded_cb_p
 * @since_tizen		5.5
 * @description		Positive test case to unset media packet audio frame decoded callback
 */
int utc_media_player_unset_media_packet_audio_frame_decoded_cb_p(void)
{
	int ret = player_unset_media_packet_audio_frame_decoded_cb(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_player_unset_media_packet_audio_frame_decoded_cb_n
 * @since_tizen		5.5
 * @description		Negative test case to unset media packet audio frame decoded callback
 */
int utc_media_player_unset_media_packet_audio_frame_decoded_cb_n(void)
{
	int ret = PLAYER_ERROR_NONE;

	ret = player_set_media_packet_audio_frame_decoded_cb(player, NULL, PLAYER_AUDIO_EXTRACT_DEFAULT, player_audio_decoded_cb, NULL);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_prepare(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_start(player);
	assert_eq(ret, PLAYER_ERROR_NONE);

	ret = player_unset_media_packet_audio_frame_decoded_cb(player);
	assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

	return 0;
}

/**
 * @testcase		utc_media_player_set_media_packet_video_frame_decoded_cb_p
 * @since_tizen		2.4
 * @description		Positive test case to set media packet video frame decoded callback
 */
int utc_media_player_set_media_packet_video_frame_decoded_cb_p(void)
{
    int ret = player_set_display(player, PLAYER_DISPLAY_TYPE_NONE, NULL);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display failed\\n", __LINE__, API_NAMESPACE);

    ret = player_set_media_packet_video_frame_decoded_cb(player, player_media_packet_decoded_cb, NULL);
    assert_eq(ret, PLAYER_ERROR_NONE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);

    ret = player_start(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't started\\n", __LINE__, API_NAMESPACE);

    ret = player_stop(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't stopped\\n", __LINE__, API_NAMESPACE);

    return 0;
}

/**
 * @testcase		utc_media_player_set_media_packet_video_frame_decoded_cb_n
 * @since_tizen		2.4
 * @description		Negative test case to set media packet video frame decoded callback
 */
int utc_media_player_set_media_packet_video_frame_decoded_cb_n(void)
{
    int ret = player_set_media_packet_video_frame_decoded_cb(NULL, player_media_packet_decoded_cb, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_media_player_set_media_packet_video_frame_decoded_cb_n2
 * @since_tizen		2.4
 * @description		Negative test case to set media packet video frame decoded callback
 */
int utc_media_player_set_media_packet_video_frame_decoded_cb_n2(void)
{
    int ret = player_set_display(player, PLAYER_DISPLAY_TYPE_NONE, NULL);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player_set_display failed\\n", __LINE__, API_NAMESPACE);

    ret = player_prepare(player);
    if (PLAYER_ERROR_NONE != ret)
        PRINT_UTC_LOG("[Line : %d][%s] player isn't prepared\\n", __LINE__, API_NAMESPACE);

    ret = player_set_media_packet_video_frame_decoded_cb(player, player_media_packet_decoded_cb, NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_STATE);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_media_packet_video_frame_decoded_cb_p
 * @since_tizen		2.4
 * @description		Positive test case to unset media packet video frame decoded callback
 */
int utc_media_player_unset_media_packet_video_frame_decoded_cb_p(void)
{
    int ret = player_unset_media_packet_video_frame_decoded_cb(player);
    assert_eq(ret, PLAYER_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_media_player_unset_media_packet_video_frame_decoded_cb_n
 * @since_tizen		2.4
 * @description		Negative test case to unset media packet video frame decoded callback
 */
int utc_media_player_unset_media_packet_video_frame_decoded_cb_n(void)
{
    int ret = player_unset_media_packet_video_frame_decoded_cb(NULL);
    assert_eq(ret, PLAYER_ERROR_INVALID_PARAMETER);

    return 0;
}
