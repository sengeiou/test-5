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

//& set: MediaTag

static media_tag_h g_tag = NULL;
static int g_tag_id = 0;
static char *g_media_id = NULL;
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

/**
 * @function		utc_media_tag_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_tag_startup(void)
{
	char video_path[PATH_MAX + 1] = { 0, };
	char *root_path = NULL;
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

	startup_ret = media_info_get_media_id(media, &g_media_id);
	media_info_destroy(media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_info_get_media_id failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_tag_insert_to_db("TEST", &g_tag);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_tag_insert_to_db failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_tag_get_tag_id(g_tag, &g_tag_id);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_tag_get_tag_id failed.\\n", __LINE__);
		return;
	}
}

/**
 * @function		utc_media_tag_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_tag_cleanup(void)
{
	if (g_tag) {
		media_tag_delete_from_db(g_tag_id);
		media_tag_destroy(g_tag);
		g_tag = NULL;

	}

	FREE_MEMORY(g_media_id);

	media_content_disconnect();
}

static bool tag_cb(media_tag_h tag, void *user_data)
{
	return true;
}

static bool media_cb(media_info_h media, void *user_data)
{
	return true;
}

/**
 * @testcase		utc_media_tag_insert_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_insert_to_db()
 */
int utc_media_tag_insert_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_insert_to_db(NULL, &g_tag), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_tag_insert_to_db("TEST", NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_insert_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_insert_to_db()
 */
int utc_media_tag_insert_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_delete_from_db(g_tag_id), MEDIA_CONTENT_ERROR_NONE);
	assert_eq(media_tag_destroy(g_tag), MEDIA_CONTENT_ERROR_NONE);
	g_tag = NULL;

	assert_eq(media_tag_insert_to_db("TEST", &g_tag), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_get_tag_id(g_tag, &g_tag_id), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_tag_delete_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_delete_from_db()
 */
int utc_media_tag_delete_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_delete_from_db(-1), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_delete_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_delete_from_db()
 */
int utc_media_tag_delete_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_delete_from_db(g_tag_id), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_tag_get_tag_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_get_tag_count_from_db()
 */
int utc_media_tag_get_tag_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_get_tag_count_from_db(NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_get_tag_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_get_tag_count_from_db()
 */
int utc_media_tag_get_tag_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int tag_count = 0;

	assert_eq(media_tag_get_tag_count_from_db(NULL, &tag_count), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_tag_foreach_tag_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_foreach_tag_from_db()
 */
int utc_media_tag_foreach_tag_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_foreach_tag_from_db(NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_foreach_tag_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_foreach_tag_from_db()
 */
int utc_media_tag_foreach_tag_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	const char *condition = "TAG_NAME=\"TEST\"";
	filter_h filter = NULL;

	assert_eq(media_filter_create(&filter), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_filter_set_order(filter, MEDIA_CONTENT_ORDER_DESC, TAG_NAME, MEDIA_CONTENT_COLLATE_RTRIM), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_foreach_tag_from_db(filter, tag_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	if (filter)
		media_filter_destroy(filter);

	return 0;
}

/**
 * @testcase		utc_media_tag_get_media_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_get_media_count_from_db()
 */
int utc_media_tag_get_media_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int count = 0;

	assert_eq(media_tag_get_media_count_from_db(g_tag_id, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_tag_get_media_count_from_db(-1, NULL, &count), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_get_media_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_get_media_count_from_db()
 */
int utc_media_tag_get_media_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int count = 0;

	assert_eq(media_tag_get_media_count_from_db(g_tag_id, NULL, &count), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_tag_foreach_media_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_foreach_media_from_db()
 */
int utc_media_tag_foreach_media_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_foreach_media_from_db(g_tag_id, NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_tag_foreach_media_from_db(-1, NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_foreach_media_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_foreach_media_from_db()
 */
int utc_media_tag_foreach_media_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_foreach_media_from_db(g_tag_id, NULL, media_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_tag_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_clone()
 */
int utc_media_tag_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_tag_h cloned = NULL;

	assert_eq(media_tag_clone(&cloned, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_tag_clone(NULL, g_tag), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_clone()
 */
int utc_media_tag_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_tag_h cloned = NULL;

	assert_eq(media_tag_clone(&cloned, g_tag), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_destroy(cloned), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_tag_update_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_update_to_db()
 */
int utc_media_tag_update_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_update_to_db(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_update_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_update_to_db()
 */
int utc_media_tag_update_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_add_media(g_tag, g_media_id), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_update_to_db(g_tag), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_remove_media(g_tag, g_media_id), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_update_to_db(g_tag), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_tag_add_media_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_add_media()
 */
int utc_media_tag_add_media_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_add_media(NULL, g_media_id), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_tag_add_media(g_tag, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_add_media_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_add_media()
 */
int utc_media_tag_add_media_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_add_media(g_tag, g_media_id), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_tag_remove_media_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_remove_media()
 */
int utc_media_tag_remove_media_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_remove_media(NULL, g_media_id), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_tag_remove_media(g_tag, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_remove_media_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_remove_media()
 */
int utc_media_tag_remove_media_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_remove_media(g_tag, g_media_id), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_tag_set_name_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_set_name()
 */
int utc_media_tag_set_name_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_set_name(NULL, "myTag"), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_tag_set_name(g_tag, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_set_name_p
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_set_name()
 */
int utc_media_tag_set_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_set_name(g_tag, "myTag"), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_update_to_db(g_tag), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_tag_get_tag_id_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_get_tag_id()
 */
int utc_media_tag_get_tag_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int tag_id = 0;

	assert_eq(media_tag_get_tag_id(NULL, &tag_id), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_tag_get_tag_id(g_tag, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_get_tag_id_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_get_tag_id()
 */
int utc_media_tag_get_tag_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int tag_id = 0;

	assert_eq(media_tag_get_tag_id(g_tag, &tag_id), MEDIA_CONTENT_ERROR_NONE);
	assert_eq(tag_id, g_tag_id);

	return 0;
}

/**
 * @testcase		utc_media_tag_get_name_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_get_name()
 */
int utc_media_tag_get_name_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	char *name = NULL;

	assert_eq(media_tag_get_name(NULL, &name), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_tag_get_name(g_tag, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_get_name_p
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_get_name()
 */
int utc_media_tag_get_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	char *name = NULL;

	assert_eq(media_tag_get_name(g_tag, &name), MEDIA_CONTENT_ERROR_NONE);
	FREE_MEMORY(name);

	return 0;
}

/**
 * @testcase		utc_media_tag_get_tag_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_get_tag_from_db()
 */
int utc_media_tag_get_tag_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_tag_h tag = NULL;

	assert_eq(media_tag_get_tag_from_db(-1, &tag), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_tag_get_tag_from_db(g_tag_id, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_get_tag_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_get_tag_from_db()
 */
int utc_media_tag_get_tag_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_tag_h tag = NULL;

	assert_eq(media_tag_get_tag_from_db(g_tag_id, &tag), MEDIA_CONTENT_ERROR_NONE);

	if (tag)
		media_tag_destroy(tag);

	return 0;
}

/**
 * @testcase		utc_media_tag_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_destroy()
 */
int utc_media_tag_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_tag_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of media_tag_destroy()
 */
int utc_media_tag_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_tag_destroy(g_tag), MEDIA_CONTENT_ERROR_NONE);
	g_tag = NULL;

	assert_eq(media_tag_delete_from_db(g_tag_id), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
