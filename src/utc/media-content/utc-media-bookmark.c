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

//& set: MediaBookmark

static media_bookmark_h g_bookmark = NULL;
static char *g_media_id = NULL;
static int g_bookmark_id = 0;
static char g_image_path[PATH_MAX + 1];
static char g_video_path[PATH_MAX + 1];
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool bookmark_cb(media_bookmark_h bookmark, void *user_data)
{
	if (media_bookmark_clone(&g_bookmark, bookmark) != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_bookmark_clone failed.\\n", __LINE__);
		return false;
	}

	if (media_bookmark_get_bookmark_id(bookmark, &g_bookmark_id) != MEDIA_CONTENT_ERROR_NONE)
		FPRINTF("[Line : %d] media_bookmark_get_bookmark_id failed.\\n", __LINE__);

	return false;
}

static bool sub_bookmark_cb(media_bookmark_h bookmark, void *user_data)
{
	return false;
}

/**
 * @function		utc_media_bookmark_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_bookmark_startup(void)
{
	char *root_path = NULL;
	media_info_h media = NULL;

	if (storage_get_root_directory(0, &root_path) == STORAGE_ERROR_NONE) {
		snprintf(g_image_path, PATH_MAX, "%s/res/image.jpg", root_path);
		snprintf(g_video_path, PATH_MAX, "%s/res/movie.mp4", root_path);
		FREE_MEMORY(root_path);
	}

	startup_ret = media_content_connect();
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_info_get_media_from_db_by_path(g_video_path, &media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(g_video_path, &media);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}
	}

	startup_ret = media_info_get_media_id(media, &g_media_id);
	media_info_destroy(media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_info_get_media_id failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_bookmark_insert_to_db(g_media_id, 0, g_image_path);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_bookmark_insert_to_db failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_info_foreach_bookmark_from_db(g_media_id, NULL, bookmark_cb, NULL);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_info_foreach_bookmark_from_db failed.\\n", __LINE__);
		return;
	}
}

/**
 * @function		utc_media_bookmark_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_bookmark_cleanup(void)
{
	media_bookmark_delete_from_db(g_bookmark_id);

	FREE_MEMORY(g_media_id);
	memset(&g_image_path, 0, PATH_MAX + 1);
	memset(&g_video_path, 0, PATH_MAX + 1);

	if (g_bookmark) {
		media_bookmark_destroy(g_bookmark);
		g_bookmark = NULL;
	}

	media_content_disconnect();
}

/**
 * @testcase		utc_media_bookmark_delete_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_bookmark_delete_from_db()
 */
int utc_media_bookmark_delete_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_delete_from_db(-1), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_delete_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_bookmark_delete_from_db()
 */
int utc_media_bookmark_delete_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_delete_from_db(g_bookmark_id), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_insert_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_bookmark_insert_to_db()
 */
int utc_media_bookmark_insert_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_insert_to_db(NULL, 0, g_image_path), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_insert_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_bookmark_insert_to_db()
 */
int utc_media_bookmark_insert_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	time_t stTime = { 0 };
	time(&stTime);

	assert_eq(media_bookmark_delete_from_db(g_bookmark_id), MEDIA_CONTENT_ERROR_NONE);

	if (g_bookmark) {
		media_bookmark_destroy(g_bookmark);
		g_bookmark = NULL;
	}

	assert_eq(media_bookmark_insert_to_db(g_media_id, stTime, g_image_path), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_foreach_bookmark_from_db(g_media_id, NULL, bookmark_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_get_bookmark_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_bookmark_get_bookmark_count_from_db()
 */
int utc_media_bookmark_get_bookmark_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_get_bookmark_count_from_db(NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_get_bookmark_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_bookmark_get_bookmark_count_from_db()
 */
int utc_media_bookmark_get_bookmark_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int value = 0;

	assert_eq(media_bookmark_get_bookmark_count_from_db(NULL, &value), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_foreach_bookmark_from_db_n
 * @since_tizen		4.0
 * @description		Negative test case of media_bookmark_foreach_bookmark_from_db()
 */
int utc_media_bookmark_foreach_bookmark_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_foreach_bookmark_from_db(NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_foreach_bookmark_from_db_p
 * @since_tizen		4.0
 * @description		Positive test case of media_bookmark_foreach_bookmark_from_db()
 */
int utc_media_bookmark_foreach_bookmark_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_foreach_bookmark_from_db(NULL, sub_bookmark_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of media_bookmark_clone()
 */
int utc_media_bookmark_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_bookmark_h bookmark = NULL;

	assert_eq(media_bookmark_clone(&bookmark, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_bookmark_clone(NULL, g_bookmark), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of media_bookmark_clone()
 */
int utc_media_bookmark_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_bookmark_h bookmark = NULL;

	assert_eq(media_bookmark_clone(&bookmark, g_bookmark), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_destroy(bookmark), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of media_bookmark_destroy()
 */
int utc_media_bookmark_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of media_bookmark_destroy()
 */
int utc_media_bookmark_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_destroy(g_bookmark), MEDIA_CONTENT_ERROR_NONE);
	g_bookmark = NULL;

	return 0;
}

/**
 * @testcase		utc_media_bookmark_get_bookmark_id_n
 * @since_tizen		2.3
 * @description		Negative test case of media_bookmark_get_bookmark_id()
 */
int utc_media_bookmark_get_bookmark_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int bookmark_id = 0;

	assert_eq(media_bookmark_get_bookmark_id(g_bookmark, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_bookmark_get_bookmark_id(NULL, &bookmark_id), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_get_bookmark_id_p
 * @since_tizen		2.3
 * @description		Positive test case of media_bookmark_get_bookmark_id()
 */
int utc_media_bookmark_get_bookmark_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int bookmark_id = 0;

	assert_eq(media_bookmark_get_bookmark_id(g_bookmark, &bookmark_id), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_get_marked_time_n
 * @since_tizen		2.3
 * @description		Negative test case of media_bookmark_get_marked_time()
 */
int utc_media_bookmark_get_marked_time_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	time_t bookmark_time = 0;

	assert_eq(media_bookmark_get_marked_time(g_bookmark, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_bookmark_get_marked_time(NULL, &bookmark_time), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_get_marked_time_p
 * @since_tizen		2.3
 * @description		Positive test case of media_bookmark_get_marked_time()
 */
int utc_media_bookmark_get_marked_time_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	time_t bookmark_time = 0;

	assert_eq(media_bookmark_get_marked_time(g_bookmark, &bookmark_time), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_get_thumbnail_path_n
 * @since_tizen		2.3
 * @description		Negative test case of media_bookmark_get_thumbnail_path()
 */
int utc_media_bookmark_get_thumbnail_path_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	char *path = NULL;

	assert_eq(media_bookmark_get_thumbnail_path(g_bookmark, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_bookmark_get_thumbnail_path(NULL, &path), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_get_thumbnail_path_p
 * @since_tizen		2.3
 * @description		Positive test case of media_bookmark_get_thumbnail_path()
 */
int utc_media_bookmark_get_thumbnail_path_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	char *path = NULL;

	assert_eq(media_bookmark_get_thumbnail_path(g_bookmark, &path), MEDIA_CONTENT_ERROR_NONE);
	FREE_MEMORY(path);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_get_name_n
 * @since_tizen		4.0
 * @description		Negative test case of media_bookmark_get_name()
 */
int utc_media_bookmark_get_name_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_get_name(NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_get_name_p
 * @since_tizen		2.3
 * @description		Positive test case of media_bookmark_get_name()
 */
int utc_media_bookmark_get_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	char *name = NULL;

	assert_eq(media_bookmark_set_name(g_bookmark, "test_name"), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_get_name(g_bookmark, &name), MEDIA_CONTENT_ERROR_NONE);
	FREE_MEMORY(name);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_set_name_n
 * @since_tizen		4.0
 * @description		Negative test case of media_bookmark_set_name()
 */
int utc_media_bookmark_set_name_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_set_name(NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_set_name_p
 * @since_tizen		4.0
 * @description		Positive test case of media_bookmark_set_name()
 */
int utc_media_bookmark_set_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_set_name(g_bookmark, "test_name"), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_update_to_db_n
 * @since_tizen		4.0
 * @description		Negative test case of media_bookmark_update_to_db()
 */
int utc_media_bookmark_update_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_update_to_db(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_update_to_db_p
 * @since_tizen		4.0
 * @description		Positive test case of media_bookmark_update_to_db()
 */
int utc_media_bookmark_update_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_bookmark_update_to_db(g_bookmark), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
