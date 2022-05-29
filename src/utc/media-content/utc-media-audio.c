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
#include <media_content.h>
#include <tct_common.h>
#include <storage.h>
#include <glib.h>

//& set: MediaAudio

static audio_meta_h g_audio;
static audio_meta_h g_audio_dst;
static filter_h g_filter;
static char *g_media_id = NULL;
static char *dir_path = NULL;
static GMainLoop *g_loop = NULL;

static media_content_error_e cb_result = MEDIA_CONTENT_ERROR_NONE;
static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool __storage_device_supported_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
	if (type == STORAGE_TYPE_INTERNAL) {
		dir_path = strdup(path);
		return false;
	}
	return true;
}

static void _scan_folder_cb(media_content_error_e error, void *user_data)
{
	cb_result = error;
	g_main_loop_quit(g_loop);
}

static gboolean _startup_scan_start(gpointer data)
{
	if (media_content_scan_folder(dir_path, TRUE, _scan_folder_cb, NULL) != MEDIA_CONTENT_ERROR_NONE)
		return false;

	return false;
}

static bool media_item_cb(media_info_h media, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_media_id(media, &g_media_id);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_media_id == NULL))
		return false;

	ret = media_info_get_audio(media, &g_audio);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_audio == NULL))
		return false;

	return true;
}

/**
 * @function		utc_media_audio_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_audio_startup(void)
{
	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;
	GSource *source = NULL;
	GMainContext *context = NULL;
	int media_count = 0;

	g_filter = NULL;
	g_audio = NULL;
	g_audio_dst = NULL;

	if (storage_foreach_device_supported(__storage_device_supported_cb, NULL) != STORAGE_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
	}

	char *condition = "MEDIA_STORAGE_TYPE=0 AND MEDIA_PATH like '%/res/sound.mp3'";	//Music

	media_filter_create(&g_filter);
	media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT);
	if (g_filter == NULL) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "filter is NULL");
		startup_ret = ret;
		return;
	}

	ret = media_info_get_media_count_from_db(g_filter, &media_count);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_foreach_media_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
	}

	if (media_count == 0) {
		g_loop = g_main_loop_new(NULL, FALSE);
		context = g_main_loop_get_context(g_loop);
		source = g_idle_source_new();
		g_source_set_callback(source, _startup_scan_start, NULL, NULL);
		g_source_attach(source, context);

		g_main_loop_run(g_loop);
		g_main_loop_unref(g_loop);

		g_loop = NULL;
		if (cb_result != MEDIA_CONTENT_ERROR_NONE) {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
			startup_ret = cb_result;
			return;
		}
	}

	media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);

	ret = media_info_foreach_media_from_db(g_filter, media_item_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_foreach_media_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
	}
}

/**
 * @function		utc_media_audio_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_audio_cleanup(void)
{
	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}

	if (g_audio) {
		audio_meta_destroy(g_audio);
		g_audio = NULL;
	}
	if (g_audio_dst) {
		audio_meta_destroy(g_audio_dst);
		g_audio_dst = NULL;
	}

	if (g_media_id) {
		free(g_media_id);
		g_media_id = NULL;
	}
	if (dir_path) {
		free(dir_path);
		dir_path = NULL;
	}

	media_content_disconnect();
}

/**
 * @testcase		utc_media_audio_meta_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_destroy()
 */
int utc_media_audio_meta_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = audio_meta_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_destroy()
 */
int utc_media_audio_meta_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	/* precondition */
	ret = audio_meta_clone(&g_audio_dst, g_audio);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	/* actual test */
	ret = audio_meta_destroy(g_audio_dst);
	g_audio_dst = NULL;
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_clone()
 */
int utc_media_audio_meta_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = audio_meta_clone(&g_audio_dst, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_clone()
 */
int utc_media_audio_meta_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = audio_meta_clone(&g_audio_dst, g_audio);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	if (g_audio_dst) {
		ret = audio_meta_destroy(g_audio_dst);
		g_audio_dst = NULL;
	}
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_media_id_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_media_id()
 */
int utc_media_audio_meta_get_media_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = audio_meta_get_media_id(NULL, &media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	if (media_id) {
		free(media_id);
		media_id = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_media_id_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_media_id()
 */
int utc_media_audio_meta_get_media_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = audio_meta_get_media_id(g_audio, &media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (media_id) {
		free(media_id);
		media_id = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_album_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_album()
 */
int utc_media_audio_meta_get_album_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album = NULL;

	ret = audio_meta_get_album(NULL, &album);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	if (album) {
		free(album);
		album = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_album_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_album()
 */
int utc_media_audio_meta_get_album_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album = NULL;

	ret = audio_meta_get_album(g_audio, &album);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (album) {
		free(album);
		album = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_artist_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_artist()
 */
int utc_media_audio_meta_get_artist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *artist = NULL;

	ret = audio_meta_get_artist(NULL, &artist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	if (artist) {
		free(artist);
		artist = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_artist_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_artist()
 */
int utc_media_audio_meta_get_artist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *artist = NULL;

	ret = audio_meta_get_artist(g_audio, &artist);

	if (artist) {
		free(artist);
		artist = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_album_artist_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_album_artist()
 */
int utc_media_audio_meta_get_album_artist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album_artist = NULL;

	ret = audio_meta_get_album_artist(NULL, &album_artist);

	if (album_artist) {
		free(album_artist);
		album_artist = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_album_artist_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_album_artist()
 */
int utc_media_audio_meta_get_album_artist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album_artist = NULL;

	ret = audio_meta_get_album_artist(g_audio, &album_artist);

	if (album_artist) {
		free(album_artist);
		album_artist = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_genre_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_genre()
 */
int utc_media_audio_meta_get_genre_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *genre = NULL;

	ret = audio_meta_get_genre(NULL, &genre);

	if (genre) {
		free(genre);
		genre = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_genre_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_genre()
 */
int utc_media_audio_meta_get_genre_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *genre = NULL;

	ret = audio_meta_get_genre(g_audio, &genre);

	if (genre) {
		free(genre);
		genre = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_composer_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_composer()
 */
int utc_media_audio_meta_get_composer_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *composer = NULL;

	ret = audio_meta_get_composer(NULL, &composer);

	if (composer) {
		free(composer);
		composer = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_composer_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_composer()
 */
int utc_media_audio_meta_get_composer_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *composer = NULL;

	ret = audio_meta_get_composer(g_audio, &composer);

	if (composer) {
		free(composer);
		composer = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_year_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_year()
 */
int utc_media_audio_meta_get_year_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *year = NULL;

	ret = audio_meta_get_year(NULL, &year);

	if (year) {
		free(year);
		year = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_year_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_year()
 */
int utc_media_audio_meta_get_year_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *year = NULL;

	ret = audio_meta_get_year(g_audio, &year);

	if (year) {
		free(year);
		year = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_recorded_date_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_recorded_date()
 */
int utc_media_audio_meta_get_recorded_date_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *recorded_date = NULL;

	ret = audio_meta_get_recorded_date(NULL, &recorded_date);

	if (recorded_date) {
		free(recorded_date);
		recorded_date = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_recorded_date_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_recorded_date()
 */
int utc_media_audio_meta_get_recorded_date_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *recorded_date = NULL;

	ret = audio_meta_get_recorded_date(g_audio, &recorded_date);

	if (recorded_date) {
		free(recorded_date);
		recorded_date = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_copyright_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_copyright()
 */
int utc_media_audio_meta_get_copyright_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *copyright = NULL;

	ret = audio_meta_get_copyright(NULL, &copyright);

	if (copyright) {
		free(copyright);
		copyright = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_copyright_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_copyright()
 */
int utc_media_audio_meta_get_copyright_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *copyright = NULL;

	ret = audio_meta_get_copyright(g_audio, &copyright);

	if (copyright) {
		free(copyright);
		copyright = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_track_num_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_track_num()
 */
int utc_media_audio_meta_get_track_num_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *tracknum = NULL;

	ret = audio_meta_get_track_num(NULL, &tracknum);

	if (tracknum) {
		free(tracknum);
		tracknum = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_track_num_p
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_track_num()
 */
int utc_media_audio_meta_get_track_num_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *tracknum = NULL;

	ret = audio_meta_get_track_num(g_audio, &tracknum);

	if (tracknum) {
		free(tracknum);
		tracknum = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_bit_rate_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_bit_rate()
 */
int utc_media_audio_meta_get_bit_rate_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int bit_rate = 0;

	ret = audio_meta_get_bit_rate(NULL, &bit_rate);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_bit_rate_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_bit_rate()
 */
int utc_media_audio_meta_get_bit_rate_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int bit_rate = 0;

	ret = audio_meta_get_bit_rate(g_audio, &bit_rate);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_sample_rate_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_sample_rate()
 */
int utc_media_audio_meta_get_sample_rate_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int sample_rate = 0;

	ret = audio_meta_get_sample_rate(NULL, &sample_rate);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_sample_rate_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_sample_rate()
 */
int utc_media_audio_meta_get_sample_rate_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int sample_rate = 0;

	ret = audio_meta_get_sample_rate(g_audio, &sample_rate);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_channel_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_channel()
 */
int utc_media_audio_meta_get_channel_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int channel = 0;

	ret = audio_meta_get_channel(NULL, &channel);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_channel_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_channel()
 */
int utc_media_audio_meta_get_channel_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int channel = 0;

	ret = audio_meta_get_channel(g_audio, &channel);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_duration_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_duration()
 */
int utc_media_audio_meta_get_duration_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int duration = 0;

	ret = audio_meta_get_duration(NULL, &duration);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_duration_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_duration()
 */
int utc_media_audio_meta_get_duration_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int duration = 0;

	ret = audio_meta_get_duration(g_audio, &duration);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_bitpersample_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_get_bitpersample()
 */
int utc_media_audio_meta_get_bitpersample_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int bitpersample = 0;

	ret = audio_meta_get_bitpersample(NULL, &bitpersample);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_audio_meta_get_bitpersample_p
 * @since_tizen		2.3
 * @description		Positive test case of media_audio_meta_get_bitpersample()
 */
int utc_media_audio_meta_get_bitpersample_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int bitpersample = 0;

	ret = audio_meta_get_bitpersample(g_audio, &bitpersample);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
