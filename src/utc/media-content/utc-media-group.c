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

//& set: MediaGroup

static media_album_h g_album = NULL;
static media_album_h g_album_dst = NULL;
static filter_h g_filter = NULL;
static int g_album_id = 0;

static int g_val_int = 0;
static char *g_val_str = NULL;
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool media_item_cb(media_info_h media, void *user_data)
{
	return false;
}

static bool album_cb(media_album_h album, void *user_data)
{
	if (album != NULL && g_album == NULL) {
		media_album_clone(&g_album, album);
		media_album_get_album_id(g_album, &g_album_id);
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
	const char *condition = "MEDIA_ALBUM='Test album'";

	startup_ret = media_content_connect();
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_filter_create(&g_filter);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_filter_create failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_filter_set_condition failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_album_foreach_album_from_db(g_filter, album_cb, NULL);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_album_foreach_album_from_db failed.\\n", __LINE__);
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
	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}

	if (g_album) {
		media_album_destroy(g_album);
		g_album = NULL;
	}

	if (g_album_dst) {
		media_album_destroy(g_album_dst);
		g_album_dst = NULL;
	}

	FREE_MEMORY(g_val_str);

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

	assert_eq(media_album_get_album_count_from_db(g_filter, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_get_album_count_from_db(g_filter, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_album_foreach_album_from_db(g_filter, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_foreach_album_from_db(g_filter, album_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_album_get_media_count_from_db(0, NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_album_get_media_count_from_db(g_album_id, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_get_media_count_from_db(g_album_id, g_filter, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_album_foreach_media_from_db(0, g_filter, media_item_cb, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_foreach_media_from_db(g_album_id, g_filter, media_item_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_album_get_album_from_db(-1, &g_album_dst), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_album_get_album_from_db(g_album_id, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_get_album_from_db(g_album_id, &g_album_dst), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_album_get_album_id(g_album, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_album_get_album_id(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_get_album_id(g_album, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_album_get_name(g_album, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_album_get_name(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_get_name(g_album, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_album_get_artist(g_album, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_album_get_artist(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_get_artist(g_album, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_album_get_album_art(g_album, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_album_get_album_art(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_get_album_art(g_album, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_album_clone(&g_album_dst, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_album_clone(NULL, g_album), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_clone(&g_album_dst, g_album), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_album_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_album_destroy(g_album), MEDIA_CONTENT_ERROR_NONE);
	g_album = NULL;

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

	assert_eq(media_group_get_group_count_from_db(g_filter, MEDIA_CONTENT_GROUP_DISPLAY_NAME, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int idx = 0;

	for (idx = 0; idx < MEDIA_CONTENT_GROUP_MAX; idx++) {
		assert_eq(media_group_get_group_count_from_db(g_filter, idx, &g_val_int), MEDIA_CONTENT_ERROR_NONE);
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

	assert_eq(media_group_get_media_count_from_db(NULL, MEDIA_CONTENT_GROUP_DISPLAY_NAME, g_filter, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_group_get_media_count_from_db(NULL, MEDIA_CONTENT_GROUP_DISPLAY_NAME, g_filter, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_group_foreach_group_from_db(NULL, MEDIA_CONTENT_GROUP_DISPLAY_NAME, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int idx = 0;

	for (idx = 0; idx < MEDIA_CONTENT_GROUP_MAX; idx++) {
		assert_eq(media_group_foreach_group_from_db(NULL, idx, group_cb, NULL), MEDIA_CONTENT_ERROR_NONE);
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

	assert_eq(media_group_foreach_media_from_db(NULL, MEDIA_CONTENT_GROUP_DISPLAY_NAME, NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_group_foreach_media_from_db(NULL, MEDIA_CONTENT_GROUP_DISPLAY_NAME, g_filter, media_item_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
