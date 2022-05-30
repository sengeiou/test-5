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

//& set: MediaFolder

static media_folder_h g_folder = NULL;
static char *g_folder_id = NULL;
static char *g_val_str = NULL;
static int g_val_int = 0;
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool __media_cb(media_info_h media, void *user_data)
{
	return false;
}

static bool __folder_list_cb(media_folder_h folder, void *user_data)
{
	if (g_folder_id)
		return false;

	if (media_folder_clone(&g_folder, folder) != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_folder_clone failed.\\n", __LINE__);
		return false;
	}

	if (media_folder_get_folder_id(g_folder, &g_folder_id) != MEDIA_CONTENT_ERROR_NONE)
		FPRINTF("[Line : %d] media_folder_clone failed.\\n", __LINE__);

	return false;
}

/**
 * @function		utc_media_folder_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_folder_startup(void)
{
	filter_h filter = NULL;

	startup_ret = media_content_connect();
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_filter_create(&filter);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_filter_create failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_filter_set_condition(filter, "MEDIA_STORAGE_TYPE=0", MEDIA_CONTENT_COLLATE_DEFAULT);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_filter_set_condition failed.\\n", __LINE__);
		media_filter_destroy(filter);
		return;
	}

	startup_ret = media_folder_foreach_folder_from_db(filter, __folder_list_cb, NULL);
	media_filter_destroy(filter);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_folder_foreach_folder_from_db failed.\\n", __LINE__);
		return;
	}
}

/**
 * @function		utc_media_folder_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_folder_cleanup(void)
{
	media_content_disconnect();

	if (g_folder) {
		media_folder_destroy(g_folder);
		g_folder = NULL;
	}

	FREE_MEMORY(g_folder_id);
}

/**
 * @testcase		utc_media_folder_foreach_folder_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_foreach_folder_from_db()
 */
int utc_media_folder_foreach_folder_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_foreach_folder_from_db(NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_foreach_folder_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_folder_foreach_folder_from_db()
 */
int utc_media_folder_foreach_folder_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_foreach_folder_from_db(NULL, __folder_list_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_media_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_get_media_count_from_db()
 */
int utc_media_folder_get_media_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_media_count_from_db(NULL, NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_folder_get_media_count_from_db(g_folder_id, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_media_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_folder_get_media_count_from_db()
 */
int utc_media_folder_get_media_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_media_count_from_db(g_folder_id, NULL, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_foreach_media_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_foreach_media_from_db()
 */
int utc_media_folder_foreach_media_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_foreach_media_from_db(NULL, NULL, __media_cb, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_folder_foreach_media_from_db(g_folder_id, NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_foreach_media_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_folder_foreach_media_from_db()
 */
int utc_media_folder_foreach_media_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_foreach_media_from_db(g_folder_id, NULL, __media_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_clone()
 */
int utc_media_folder_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	media_folder_h cloned = NULL;

	assert_eq(media_folder_clone(&cloned, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_folder_clone(NULL, g_folder), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of media_folder_clone()
 */
int utc_media_folder_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	media_folder_h cloned = NULL;

	assert_eq(media_folder_clone(&cloned, g_folder), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_destroy(cloned), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_path_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_get_path()
 */
int utc_media_folder_get_path_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_path(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_folder_get_path(g_folder, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_path_p
 * @since_tizen		2.3
 * @description		Positive test case of media_folder_get_path()
 */
int utc_media_folder_get_path_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_path(g_folder, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_name_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_get_name()
 */
int utc_media_folder_get_name_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_name(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_folder_get_name(g_folder, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_name_p
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_get_name()
 */
int utc_media_folder_get_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_name(g_folder, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_storage_type_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_get_storage_type()
 */
int utc_media_folder_get_storage_type_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	media_content_storage_e type = MEDIA_CONTENT_STORAGE_INTERNAL;

	assert_eq(media_folder_get_storage_type(NULL, &type), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_folder_get_storage_type(g_folder, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_storage_type_p
 * @since_tizen		2.3
 * @description		Positive test case of media_folder_get_storage_type()
 */
int utc_media_folder_get_storage_type_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	media_content_storage_e type = MEDIA_CONTENT_STORAGE_INTERNAL;

	assert_eq(media_folder_get_storage_type(g_folder, &type), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_storage_id_n
 * @since_tizen		2.4
 * @description		Negative test case of media_folder_get_storage_id()
 */
int utc_media_folder_get_storage_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_storage_id(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_folder_get_storage_id(g_folder, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_storage_id_p
 * @since_tizen		2.4
 * @description		Positive test case of media_folder_get_storage_id()
 */
int utc_media_folder_get_storage_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_storage_id(g_folder, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_folder_id_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_get_folder_id()
 */
int utc_media_folder_get_folder_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_folder_id(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_folder_get_folder_id(g_folder, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_folder_id_p
 * @since_tizen		2.3
 * @description		Positive test case of media_folder_get_folder_id()
 */
int utc_media_folder_get_folder_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_folder_id(g_folder, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_folder_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_get_folder_from_db()
 */
int utc_media_folder_get_folder_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_folder_from_db(g_folder_id, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_folder_get_folder_from_db(NULL, &g_folder), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_folder_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_folder_get_folder_from_db()
 */
int utc_media_folder_get_folder_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_destroy(g_folder), MEDIA_CONTENT_ERROR_NONE);
	g_folder = NULL;

	assert_eq(media_folder_get_folder_from_db(g_folder_id, &g_folder), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_folder_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_get_folder_count_from_db()
 */
int utc_media_folder_get_folder_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_folder_count_from_db(NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_get_folder_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_folder_get_folder_count_from_db()
 */
int utc_media_folder_get_folder_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_get_folder_count_from_db(NULL, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_folder_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_destroy()
 */
int utc_media_folder_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_folder_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of media_folder_destroy()
 */
int utc_media_folder_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_folder_destroy(g_folder), MEDIA_CONTENT_ERROR_NONE);
	g_folder = NULL;

	return 0;
}
