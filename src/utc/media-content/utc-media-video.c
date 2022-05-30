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
#include <limits.h>
#include <storage.h>

//& set: MediaVideo

static video_meta_h g_video;
static char *g_val_str = NULL;
static int g_val_int = 0;
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

/**
 * @function		utc_media_video_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_video_startup(void)
{
	char *root_path = NULL;
	char video_path[PATH_MAX + 1] = { 0, };
	media_info_h media = NULL;

	if (storage_get_root_directory(0, &root_path) == STORAGE_ERROR_NONE) {
		snprintf(video_path, PATH_MAX, "%s/res/movie.mp4", root_path);
		FREE_MEMORY(root_path);
	}

	startup_ret = media_content_connect();
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_info_get_media_from_db_by_path(video_path, &media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(video_path, &media);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}
	}

	startup_ret = media_info_get_video(media, &g_video);
	media_info_destroy(media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_info_get_video failed.\\n", __LINE__);
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
	if (g_video) {
		video_meta_destroy(g_video);
		g_video = NULL;
	}

	FREE_MEMORY(g_val_str);

	media_content_disconnect();
}

/**
 * @testcase		utc_video_meta_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_destroy()
 */
int utc_video_meta_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_destroy()
 */
int utc_video_meta_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_destroy(g_video), MEDIA_CONTENT_ERROR_NONE);
	g_video = NULL;

	return 0;
}

/**
 * @testcase		utc_video_meta_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_clone()
 */
int utc_video_meta_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	video_meta_h video = NULL;

	assert_eq(video_meta_clone(&video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_clone(NULL, g_video), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_clone()
 */
int utc_video_meta_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	video_meta_h video = NULL;

	assert_eq(video_meta_clone(&video, g_video), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_destroy(video), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_media_id_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_media_id()
 */
int utc_video_meta_get_media_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_media_id(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_media_id(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_media_id_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_media_id()
 */
int utc_video_meta_get_media_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_media_id(g_video, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_album_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_album()
 */
int utc_video_meta_get_album_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_album(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_album(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_album_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_album()
 */
int utc_video_meta_get_album_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_album(g_video, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_artist_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_artist()
 */
int utc_video_meta_get_artist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_artist(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_artist(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_artist_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_artist()
 */
int utc_video_meta_get_artist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_artist(g_video, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_album_artist_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_album_artist()
 */
int utc_video_meta_get_album_artist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_album_artist(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_album_artist(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_album_artist_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_album_artist()
 */
int utc_video_meta_get_album_artist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_album_artist(g_video, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_genre_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_genre()
 */
int utc_video_meta_get_genre_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_genre(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_genre(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_genre_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_genre()
 */
int utc_video_meta_get_genre_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_genre(g_video, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_composer_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_composer()
 */
int utc_video_meta_get_composer_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_composer(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_composer(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_composer_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_composer()
 */
int utc_video_meta_get_composer_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_composer(g_video, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_year_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_year()
 */
int utc_video_meta_get_year_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_year(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_year(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_year_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_year()
 */
int utc_video_meta_get_year_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_year(g_video, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_recorded_date_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_recorded_date()
 */
int utc_video_meta_get_recorded_date_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_recorded_date(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_recorded_date(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_recorded_date_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_recorded_date()
 */
int utc_video_meta_get_recorded_date_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_recorded_date(g_video, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_copyright_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_copyright()
 */
int utc_video_meta_get_copyright_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_copyright(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_copyright(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_copyright_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_copyright()
 */
int utc_video_meta_get_copyright_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_copyright(g_video, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_track_num_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_track_num()
 */
int utc_video_meta_get_track_num_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_track_num(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_track_num(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_track_num_p
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_track_num()
 */
int utc_video_meta_get_track_num_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_track_num(g_video, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_bit_rate_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_bit_rate()
 */
int utc_video_meta_get_bit_rate_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_bit_rate(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_bit_rate(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_bit_rate_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_bit_rate()
 */
int utc_video_meta_get_bit_rate_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_bit_rate(g_video, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_duration_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_duration()
 */
int utc_video_meta_get_duration_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_duration(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_duration(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_duration_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_duration()
 */
int utc_video_meta_get_duration_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_duration(g_video, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_width_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_width()
 */
int utc_video_meta_get_width_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_width(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_width(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_width_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_width()
 */
int utc_video_meta_get_width_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_width(g_video, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_height_n
 * @since_tizen		2.3
 * @description		Negative test case of video_meta_get_height()
 */
int utc_video_meta_get_height_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_height(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_height(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_height_p
 * @since_tizen		2.3
 * @description		Positive test case of video_meta_get_height()
 */
int utc_video_meta_get_height_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_height(g_video, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_rotation_n
 * @since_tizen		4.0
 * @description		Negative test case of video_meta_get_rotation()
 */
int utc_video_meta_get_rotation_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_rotation(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(video_meta_get_rotation(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_video_meta_get_rotation_p
 * @since_tizen		4.0
 * @description		Positive test case of video_meta_get_rotation()
 */
int utc_video_meta_get_rotation_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_get_rotation(g_video, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
