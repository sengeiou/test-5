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
#include <limits.h>

//& set: MediaAudio

static audio_meta_h g_audio;
static char *g_val_str = NULL;
static int g_val_int = 0;
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

/**
 * @function		utc_media_audio_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_audio_startup(void)
{
	char *root_path = NULL;
	char audio_path[PATH_MAX + 1] = { 0, };
	media_info_h media = NULL;

	if (storage_get_root_directory(0, &root_path) == STORAGE_ERROR_NONE) {
		snprintf(audio_path, PATH_MAX, "%s/res/sound.mp3", root_path);
		FREE_MEMORY(root_path);
	}

	startup_ret = media_content_connect();
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_info_get_media_from_db_by_path(audio_path, &media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(audio_path, &media);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}
	}

	startup_ret = media_info_get_audio(media, &g_audio);
	media_info_destroy(media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_info_get_audio failed.\\n", __LINE__);
		return;
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
	media_content_disconnect();

	if (g_audio) {
		audio_meta_destroy(g_audio);
		g_audio = NULL;
	}

	FREE_MEMORY(g_val_str);
}

/**
 * @testcase		utc_media_audio_meta_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of media_audio_meta_destroy()
 */
int utc_media_audio_meta_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(audio_meta_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_destroy(g_audio), MEDIA_CONTENT_ERROR_NONE);
	g_audio = NULL;

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

	audio_meta_h cloned = NULL;

	assert_eq(audio_meta_clone(&cloned, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_clone(NULL, g_audio), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	audio_meta_h cloned = NULL;

	assert_eq(audio_meta_clone(&cloned, g_audio), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(audio_meta_destroy(cloned), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_media_id(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_media_id(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_media_id(g_audio, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_album(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_album(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_album(g_audio, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_artist(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_artist(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_artist(g_audio, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_album_artist(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_album_artist(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_album_artist(g_audio, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_genre(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_genre(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_genre(g_audio, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_composer(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_composer(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_composer(g_audio, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_year(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_year(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_year(g_audio, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_recorded_date(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_recorded_date(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_recorded_date(g_audio, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_copyright(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_copyright(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_copyright(g_audio, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_track_num(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_track_num(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_track_num(g_audio, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_bit_rate(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_bit_rate(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_bit_rate(g_audio, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_sample_rate(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_sample_rate(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_sample_rate(g_audio, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_channel(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_channel(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_channel(g_audio, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_duration(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_duration(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_duration(g_audio, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(audio_meta_get_bitpersample(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(audio_meta_get_bitpersample(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(audio_meta_get_bitpersample(g_audio, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
