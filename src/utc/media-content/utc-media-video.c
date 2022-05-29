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

//& set: MediaVideo

static video_meta_h g_video;
static video_meta_h g_video_dst;
static filter_h g_filter;
static char *g_media_id = NULL;

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool media_item_cb(media_info_h media, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_media_id(media, &g_media_id);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_media_id == NULL)) {
		fprintf(stderr, "CB error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_info_get_media_id failed (code: %d)\n", ret);
		return false;
	}

	ret = media_info_get_video(media, &g_video);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_video == NULL)) {
		fprintf(stderr, "CB error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_info_get_video failed (code: %d)\n", ret);
		return false;
	}

	return true;
}

/**
 * @function		utc_media_video_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_video_startup(void)
{
	/* start of TC */
	g_filter = NULL;
	g_video = NULL;

	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	char *condition = "MEDIA_TYPE=1 AND MEDIA_STORAGE_TYPE=0";	//Video

	media_filter_create(&g_filter);
	media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT);
	if (g_filter == NULL) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "filter is NULL");
		startup_ret = ret;
		return;
	}

	ret = media_info_foreach_media_from_db(g_filter, media_item_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_foreach_media_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}
}

/**
 * @function		utc_media_video_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_video_cleanup(void)
{
	/* end of TC */
	if (g_media_id != NULL) {
		free(g_media_id);
		g_media_id = NULL;
	}

	if (g_video != NULL) {
		video_meta_destroy(g_video);
		g_video = NULL;
	}

	if (g_video_dst != NULL) {
		video_meta_destroy(g_video_dst);
		g_video_dst = NULL;
	}

	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}

	media_content_disconnect();
}

/**
 * @testcase		utc_video_meta_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_destroy()
 */
int utc_video_meta_destroy_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = video_meta_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_destroy()
 */
int utc_video_meta_destroy_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = video_meta_clone(&g_video_dst, g_video);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = video_meta_destroy(g_video_dst);
	g_video_dst = NULL;
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_clone()
 */
int utc_video_meta_clone_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = video_meta_clone(&g_video_dst, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_clone()
 */
int utc_video_meta_clone_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = video_meta_clone(&g_video_dst, g_video);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_media_id_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_media_id()
 */
int utc_video_meta_get_media_id_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = video_meta_get_media_id(NULL, &media_id);

	if (media_id) {
		free(media_id);
		media_id = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_media_id_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_media_id()
 */
int utc_video_meta_get_media_id_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = video_meta_get_media_id(g_video, &media_id);

	if (media_id) {
		free(media_id);
		media_id = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_album_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_album()
 */
int utc_video_meta_get_album_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album = NULL;

	ret = video_meta_get_album(NULL, &album);

	if (album) {
		free(album);
		album = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_album_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_album()
 */
int utc_video_meta_get_album_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album = NULL;

	ret = video_meta_get_album(g_video, &album);

	if (album) {
		free(album);
		album = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_artist_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_artist()
 */
int utc_video_meta_get_artist_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *artist = NULL;

	ret = video_meta_get_artist(NULL, &artist);

	if (artist) {
		free(artist);
		artist = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_artist_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_artist()
 */
int utc_video_meta_get_artist_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *artist = NULL;

	ret = video_meta_get_artist(g_video, &artist);

	if (artist) {
		free(artist);
		artist = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_album_artist_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_album_artist()
 */
int utc_video_meta_get_album_artist_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album_artist = NULL;

	ret = video_meta_get_album_artist(NULL, &album_artist);

	if (album_artist) {
		free(album_artist);
		album_artist = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_album_artist_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_album_artist()
 */
int utc_video_meta_get_album_artist_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album_artist = NULL;

	ret = video_meta_get_album_artist(g_video, &album_artist);

	if (album_artist) {
		free(album_artist);
		album_artist = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_genre_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_genre()
 */
int utc_video_meta_get_genre_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *genre = NULL;

	ret = video_meta_get_genre(NULL, &genre);

	if (genre) {
		free(genre);
		genre = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_genre_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_genre()
 */
int utc_video_meta_get_genre_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *genre = NULL;

	ret = video_meta_get_genre(g_video, &genre);

	if (genre) {
		free(genre);
		genre = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_composer_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_composer()
 */
int utc_video_meta_get_composer_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *composer = NULL;

	ret = video_meta_get_composer(NULL, &composer);

	if (composer) {
		free(composer);
		composer = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_composer_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_composer()
 */
int utc_video_meta_get_composer_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *composer = NULL;

	ret = video_meta_get_composer(g_video, &composer);

	if (composer) {
		free(composer);
		composer = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_year_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_year()
 */
int utc_video_meta_get_year_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *year = NULL;

	ret = video_meta_get_year(NULL, &year);

	if (year) {
		free(year);
		year = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_year_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_year()
 */
int utc_video_meta_get_year_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *year = NULL;

	ret = video_meta_get_year(g_video, &year);

	if (year) {
		free(year);
		year = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_recorded_date_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_recorded_date()
 */
int utc_video_meta_get_recorded_date_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *recorded_date = NULL;

	ret = video_meta_get_recorded_date(NULL, &recorded_date);

	if (recorded_date) {
		free(recorded_date);
		recorded_date = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_recorded_date_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_recorded_date()
 */
int utc_video_meta_get_recorded_date_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *recorded_date = NULL;

	ret = video_meta_get_recorded_date(g_video, &recorded_date);

	if (recorded_date) {
		free(recorded_date);
		recorded_date = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_copyright_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_copyright()
 */
int utc_video_meta_get_copyright_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *copyright = NULL;

	ret = video_meta_get_copyright(NULL, &copyright);

	if (copyright) {
		free(copyright);
		copyright = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_copyright_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_copyright()
 */
int utc_video_meta_get_copyright_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *copyright = NULL;

	ret = video_meta_get_copyright(g_video, &copyright);

	if (copyright) {
		free(copyright);
		copyright = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_track_num_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_track_num()
 */
int utc_video_meta_get_track_num_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *track_num = NULL;

	ret = video_meta_get_track_num(NULL, &track_num);

	if (track_num) {
		free(track_num);
		track_num = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_track_num_p
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_track_num()
 */
int utc_video_meta_get_track_num_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *track_num = NULL;

	ret = video_meta_get_track_num(g_video, &track_num);

	if (track_num) {
		free(track_num);
		track_num = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_bit_rate_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_bit_rate()
 */
int utc_video_meta_get_bit_rate_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int bit_rate = 0;

	ret = video_meta_get_bit_rate(NULL, &bit_rate);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_bit_rate_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_bit_rate()
 */
int utc_video_meta_get_bit_rate_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int bit_rate = 0;

	ret = video_meta_get_bit_rate(g_video, &bit_rate);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_duration_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_duration()
 */
int utc_video_meta_get_duration_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int duration = 0;

	ret = video_meta_get_duration(NULL, &duration);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_duration_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_duration()
 */
int utc_video_meta_get_duration_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int duration = 0;

	ret = video_meta_get_duration(g_video, &duration);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_width_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_width()
 */
int utc_video_meta_get_width_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int width = 0;

	ret = video_meta_get_width(NULL, &width);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_width_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_width()
 */
int utc_video_meta_get_width_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int width = 0;

	ret = video_meta_get_width(g_video, &width);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_height_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_height()
 */
int utc_video_meta_get_height_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int height = 0;

	ret = video_meta_get_height(NULL, &height);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_height_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_height()
 */
int utc_video_meta_get_height_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int height = 0;

	ret = video_meta_get_height(g_video, &height);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_rotation_n
 * @since_tizen		4.0
 * @description		Negative test case of video_meta_get_rotation()
 */
int utc_video_meta_get_rotation_n(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int val = 0;

	ret = video_meta_get_rotation(NULL, &val);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_rotation_p
 * @since_tizen		4.0
 * @description		Positive test case of video_meta_get_rotation()
 */
int utc_video_meta_get_rotation_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int val = 0;

	ret = video_meta_get_rotation(g_video, &val);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	assert_eq(val, 90);

	return 0;
}
