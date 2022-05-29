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

#define TEST_SET_GROUP_NAME "artist"
//& set: MediaGroup

static media_album_h g_album = NULL;
static media_album_h g_album_dst = NULL;
static filter_h g_filter = NULL;
static int g_album_id = 0;
static char *g_album_name = NULL;
static char *g_artist_name = NULL;
static char *g_genre_name = NULL;
static char *g_composer_name = NULL;
static char *g_year_name = NULL;

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool media_item_cb(media_info_h media, void *user_data)
{
	return true;
}

static bool album_cb(media_album_h album, void *user_data)
{
	if (album != NULL) {
		media_album_get_album_id(album, &g_album_id);
		media_album_get_name(album, &g_album_name);
	}

	return false;
}

static bool group_cb(const char *name, void *user_data)
{
	return false;
}

/**
 * @function		utc_media_group_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_group_startup(void)
{
	/* start of TC */
	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	char *condition = "MEDIA_ALBUM='Test album'";	//Music

	media_filter_create(&g_filter);
	media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	if (g_filter == NULL) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "g_filter is NULL");
		startup_ret = ret;
		return;
	}

	ret = media_album_foreach_album_from_db(g_filter, album_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_album_foreach_album_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_album_get_album_from_db(g_album_id, &g_album);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_album_get_album_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

}

/**
 * @function		utc_media_group_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_group_cleanup(void)
{
	/* end of TC */

	if (g_album_name) {
		free(g_album_name);
		g_album_name = NULL;
	}

	if (g_artist_name) {
		free(g_artist_name);
		g_artist_name = NULL;
	}

	if (g_genre_name) {
		free(g_genre_name);
		g_genre_name = NULL;
	}

	if (g_composer_name) {
		free(g_composer_name);
		g_composer_name = NULL;
	}

	if (g_year_name) {
		free(g_year_name);
		g_year_name = NULL;
	}

	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}

	if (g_album) {
		media_album_destroy(g_album);
		g_album = NULL;
	}

	media_content_disconnect();

}

/**
 * @testcase		utc_media_album_get_album_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_get_album_count_from_db()
 */
int utc_media_album_get_album_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_album_count_from_db(g_filter, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_get_album_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_album_get_album_count_from_db()
 */
int utc_media_album_get_album_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int album_count = 0;

	ret = media_album_get_album_count_from_db(g_filter, &album_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_album_foreach_album_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_foreach_album_from_db()
 */
int utc_media_album_foreach_album_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_foreach_album_from_db(g_filter, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_foreach_album_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_album_foreach_album_from_db()
 */
int utc_media_album_foreach_album_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_foreach_album_from_db(g_filter, album_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_album_get_media_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_get_media_count_from_db()
 */
int utc_media_album_get_media_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;

	ret = media_album_get_media_count_from_db(0, g_filter, &media_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_get_media_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_album_get_media_count_from_db()
 */
int utc_media_album_get_media_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;

	ret = media_album_get_media_count_from_db(g_album_id, g_filter, &media_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_album_foreach_media_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_foreach_media_from_db()
 */
int utc_media_album_foreach_media_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_foreach_media_from_db(0, g_filter, media_item_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_foreach_media_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_album_foreach_media_from_db()
 */
int utc_media_album_foreach_media_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_foreach_media_from_db(g_album_id, g_filter, media_item_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_album_get_album_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_get_album_from_db()
 */
int utc_media_album_get_album_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_album_from_db(-1, &g_album);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_get_album_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_album_get_album_from_db()
 */
int utc_media_album_get_album_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	/* precondition */
	ret = media_album_destroy(g_album);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	/* actual test */
	ret = media_album_get_album_from_db(g_album_id, &g_album);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_album_get_album_id_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_get_album_id()
 */
int utc_media_album_get_album_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_album_id(g_album, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_get_album_id_p
 * @since_tizen		2.3
 * @description		Positive test case of media_album_get_album_id()
 */
int utc_media_album_get_album_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int album_id = 0;

	ret = media_album_get_album_id(g_album, &album_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_album_get_name_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_get_name()
 */
int utc_media_album_get_name_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_name(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_get_name_p
 * @since_tizen		2.3
 * @description		Negative test case of media_album_get_name()
 */
int utc_media_album_get_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album_name = NULL;

	ret = media_album_get_name(g_album, &album_name);

	if (album_name) {
		free(album_name);
		album_name = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_album_get_artist_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_get_artist()
 */
int utc_media_album_get_artist_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_artist(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_get_artist_p
 * @since_tizen		2.3
 * @description		Positive test case of media_album_get_artist()
 */
int utc_media_album_get_artist_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *artist_name = NULL;

	ret = media_album_get_artist(g_album, &artist_name);

	if (artist_name) {
		free(artist_name);
		artist_name = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_album_get_album_art_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_get_album_art()
 */
int utc_media_album_get_album_art_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_get_album_art(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_get_album_art_p
 * @since_tizen		2.3
 * @description		Positive test case of media_album_get_album_art()
 */
int utc_media_album_get_album_art_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *album_art = NULL;

	ret = media_album_get_album_art(g_album, &album_art);

	if (album_art) {
		free(album_art);
		album_art = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_album_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_clone()
 */
int utc_media_album_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_clone(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of media_album_clone()
 */
int utc_media_album_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_clone(&g_album_dst, g_album);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_album_destroy(g_album_dst);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_album_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of media_album_destroy()
 */
int utc_media_album_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_album_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_album_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of media_album_destroy()
 */
int utc_media_album_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	/* precondition */
	ret = media_album_clone(&g_album_dst, g_album);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	/* actual test */
	ret = media_album_destroy(g_album_dst);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_group_get_group_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_group_get_group_count_from_db()
 */
int utc_media_group_get_group_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_group_get_group_count_from_db(g_filter, MEDIA_CONTENT_GROUP_DISPLAY_NAME, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_group_get_group_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_group_get_group_count_from_db()
 */
int utc_media_group_get_group_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int group_count = 0;
	int idx = 0;

	for (idx = 0; idx < MEDIA_CONTENT_GROUP_MAX; idx++) {
		ret = media_group_get_group_count_from_db(g_filter, idx, &group_count);
		assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_media_group_get_media_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_group_get_media_count_from_db()
 */
int utc_media_group_get_media_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_group_get_media_count_from_db(NULL, MEDIA_CONTENT_GROUP_DISPLAY_NAME, g_filter, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_group_get_media_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_group_get_media_count_from_db()
 */
int utc_media_group_get_media_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;

	ret = media_group_get_media_count_from_db(NULL, MEDIA_CONTENT_GROUP_DISPLAY_NAME, g_filter, &media_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_group_foreach_group_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_group_foreach_group_from_db()
 */
int utc_media_group_foreach_group_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_group_foreach_group_from_db(g_filter, MEDIA_CONTENT_GROUP_DISPLAY_NAME, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_group_foreach_group_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_group_foreach_group_from_db()
 */
int utc_media_group_foreach_group_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int idx = 0;

	for (idx = 0; idx < MEDIA_CONTENT_GROUP_MAX; idx++) {
		ret = media_group_foreach_group_from_db(NULL, MEDIA_CONTENT_GROUP_DISPLAY_NAME, group_cb, TEST_SET_GROUP_NAME);
		assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_media_group_foreach_media_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_group_foreach_media_from_db()
 */
int utc_media_group_foreach_media_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_group_foreach_media_from_db(NULL, MEDIA_CONTENT_GROUP_DISPLAY_NAME, g_filter, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_group_foreach_media_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_group_foreach_media_from_db()
 */
int utc_media_group_foreach_media_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_group_foreach_media_from_db(NULL, MEDIA_CONTENT_GROUP_DISPLAY_NAME, g_filter, media_item_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
