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

//& set: MediaAudio

static media_storage_h g_storage;
static char *g_storage_id = NULL;
static char *g_val_str = NULL;
static int g_val_int = 0;
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool __media_item_cb(media_info_h media, void *user_data)
{
	return false;
}

static bool __media_storage_cb(media_storage_h storage, void *user_data)
{
	if (media_storage_clone(&g_storage, storage) != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_storage_clone failed.\\n", __LINE__);
		return false;
	}

	if (media_storage_get_id(g_storage, &g_storage_id) != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_storage_get_id failed.\\n", __LINE__);
		return false;
	}

	return false;
}

/**
 * @function		utc_media_storage_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_storage_startup(void)
{
	startup_ret = media_content_connect();
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_storage_foreach_storage_from_db(NULL, __media_storage_cb, NULL);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE)
		FPRINTF("[Line : %d] media_storage_foreach_storage_from_db failed.\\n", __LINE__);
}

/**
 * @function		utc_media_storage_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_storage_cleanup(void)
{
	if (g_storage) {
		media_storage_destroy(g_storage);
		g_storage = NULL;
	}

	FREE_MEMORY(g_storage_id);
	FREE_MEMORY(g_val_str);

	media_content_disconnect();
}

/**
 * @testcase		utc_media_storage_get_storage_info_from_db_n
 * @since_tizen		2.4
 * @description		Negative test case of media_storage_get_storage_info_from_db()
 */
int utc_media_storage_get_storage_info_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_get_storage_info_from_db(g_storage_id, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_storage_info_from_db_p
 * @since_tizen		2.4
 * @description		Positive test case of media_storage_get_storage_info_from_db()
 */
int utc_media_storage_get_storage_info_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_destroy(g_storage), MEDIA_CONTENT_ERROR_NONE);
	g_storage = NULL;

	assert_eq(media_storage_get_storage_info_from_db(g_storage_id, &g_storage), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_storage_count_from_db_n
 * @since_tizen		2.4
 * @description		Negative test case of media_storage_get_storage_count_from_db()
 */
int utc_media_storage_get_storage_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_get_storage_count_from_db(NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_storage_count_from_db_p
 * @since_tizen		2.4
 * @description		Positive test case of media_storage_get_storage_count_from_db()
 */
int utc_media_storage_get_storage_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_get_storage_count_from_db(NULL, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_storage_foreach_storage_from_db_n
 * @since_tizen		2.4
 * @description		Negative test case of media_storage_foreach_storage_from_db()
 */
int utc_media_storage_foreach_storage_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_foreach_storage_from_db(NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_storage_foreach_storage_from_db_p
 * @since_tizen		2.4
 * @description		Positive test case of media_storage_foreach_storage_from_db()
 */
int utc_media_storage_foreach_storage_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_foreach_storage_from_db(NULL, __media_storage_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_media_count_from_db_n
 * @since_tizen		2.4
 * @description		Negative test case of media_storage_get_media_count_from_db()
 */
int utc_media_storage_get_media_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_get_media_count_from_db(NULL, NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_media_count_from_db_p
 * @since_tizen		2.4
 * @description		Positive test case of media_storage_get_media_count_from_db()
 */
int utc_media_storage_get_media_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_get_media_count_from_db(g_storage_id, NULL, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_storage_foreach_media_from_db_n
 * @since_tizen		2.4
 * @description		Negative test case of media_storage_foreach_media_from_db()
 */
int utc_media_storage_foreach_media_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_foreach_media_from_db(NULL, NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_storage_foreach_media_from_db_p
 * @since_tizen		2.4
 * @description		Positive test case of media_storage_foreach_media_from_db()
 */
int utc_media_storage_foreach_media_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_foreach_media_from_db(g_storage_id, NULL, __media_item_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_storage_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of media_storage_destroy()
 */
int utc_media_storage_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_storage_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of media_storage_destroy()
 */
int utc_media_storage_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_destroy(g_storage), MEDIA_CONTENT_ERROR_NONE);
	g_storage = NULL;

	return 0;
}

/**
 * @testcase		utc_media_storage_clone_n
 * @since_tizen		2.4
 * @description		Negative test case of media_storage_clone()
 */
int utc_media_storage_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	media_storage_h cloned = NULL;

	assert_eq(media_storage_clone(&cloned, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_storage_clone(NULL, g_storage), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_storage_clone_p
 * @since_tizen		2.4
 * @description		Positive test case of media_storage_clone()
 */
int utc_media_storage_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	media_storage_h cloned = NULL;

	assert_eq(media_storage_clone(&cloned, g_storage), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_destroy(cloned), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_id_n
 * @since_tizen		2.4
 * @description		Negative test case of media_storage_get_id()
 */
int utc_media_storage_get_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_get_id(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_storage_get_id(g_storage, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_id_p
 * @since_tizen		2.4
 * @description		Positive test case of media_storage_get_id()
 */
int utc_media_storage_get_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_get_id(g_storage, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_path_n
 * @since_tizen		2.4
 * @description		Negative test case of media_storage_get_path()
 */
int utc_media_storage_get_path_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_get_path(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_storage_get_path(g_storage, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_path_p
 * @since_tizen		2.4
 * @description		Positive test case of media_storage_get_path()
 */
int utc_media_storage_get_path_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_storage_get_path(g_storage, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_type_n
 * @since_tizen		2.4
 * @description		Negative test case of media_storage_get_type()
 */
int utc_media_storage_get_type_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	media_content_storage_e storage_type;

	assert_eq(media_storage_get_type(NULL, &storage_type), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_storage_get_type(g_storage, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_storage_get_type_p
 * @since_tizen		2.4
 * @description		Positive test case of media_storage_get_type()
 */
int utc_media_storage_get_type_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	media_content_storage_e storage_type = MEDIA_CONTENT_STORAGE_INTERNAL;

	assert_eq(media_storage_get_type(g_storage, &storage_type), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
