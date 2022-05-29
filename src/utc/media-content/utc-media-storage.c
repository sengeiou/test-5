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
static media_storage_h g_storage_dst;
static filter_h g_filter;
static char *g_media_id = NULL;
static char *g_storage_id = NULL;

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool media_item_cb(media_info_h media, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	if (g_media_id) {
		free(g_media_id);
		g_media_id = NULL;
	}

	if (g_storage_id) {
		free(g_storage_id);
		g_storage_id = NULL;
	}

	ret = media_info_get_media_id(media, &g_media_id);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_media_id == NULL))
		return false;

	ret = media_info_get_storage_id(media, &g_storage_id);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_storage_id == NULL))
		return false;

	return true;
}

static bool _media_storage_cb(media_storage_h storage, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_path = NULL;
	media_content_storage_e storage_type;

	ret = media_storage_clone(&g_storage, storage);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_storage == NULL))
		goto MEDIA_STORAGE_CB_FAIL;

	ret = media_storage_get_id(storage, &g_storage_id);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_storage_id == NULL))
		goto MEDIA_STORAGE_CB_FAIL;

	ret = media_storage_get_path(storage, &storage_path);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (storage_path == NULL))
		goto MEDIA_STORAGE_CB_FAIL;

	ret = media_storage_get_type(storage, &storage_type);
	if ((ret != MEDIA_CONTENT_ERROR_NONE))
		goto MEDIA_STORAGE_CB_FAIL;

	if (storage_path) {
		free(storage_path);
		storage_path = NULL;
	}

	return true;
 MEDIA_STORAGE_CB_FAIL:
	if (g_storage) {
		media_storage_destroy(g_storage);
		g_storage = NULL;
	}
	if (g_storage_id) {
		free(g_storage_id);
		g_storage_id = NULL;
	}
	if (storage_path) {
		free(storage_path);
		storage_path = NULL;
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
	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	g_filter = NULL;
	g_storage = NULL;
	g_storage_dst = NULL;

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
	}

	char *condition = "MEDIA_TYPE=3 AND MEDIA_STORAGE_TYPE=0";	//Music

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
	}

	if (g_filter != NULL)
		media_filter_destroy(g_filter);

	media_filter_create(&g_filter);
	if (g_filter == NULL) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "filter is NULL");
		startup_ret = ret;
		return;
	}

	ret = media_storage_foreach_storage_from_db(g_filter, _media_storage_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_storage_foreach_storage_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
	}
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
	if (g_media_id != NULL) {
		free(g_media_id);
		g_media_id = NULL;
	}
	if (g_storage_id != NULL) {
		free(g_storage_id);
		g_storage_id = NULL;
	}
	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_storage_get_storage_info_from_db(g_storage_id, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_storage_get_storage_info_from_db(g_storage_id, &g_storage);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_storage_get_storage_count_from_db(g_filter, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int storage_count = 0;

	ret = media_storage_get_storage_count_from_db(g_filter, &storage_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_storage_foreach_storage_from_db(NULL, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	/* actual test */
	ret = media_filter_create(&filter);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_storage_foreach_storage_from_db(filter, _media_storage_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_storage_get_media_count_from_db(NULL, g_filter, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int storage_count = 0;

	ret = media_storage_get_media_count_from_db(g_storage_id, g_filter, &storage_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_storage_foreach_media_from_db(NULL, NULL, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	/* actual test */
	ret = media_filter_create(&filter);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_storage_foreach_media_from_db(g_storage_id, filter, media_item_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_storage_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	/* precondition */
	ret = media_storage_clone(&g_storage_dst, g_storage);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	/* actual test */
	ret = media_storage_destroy(g_storage_dst);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_storage_clone(&g_storage_dst, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_storage_clone(&g_storage_dst, g_storage);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	if (g_storage_dst) {
		ret = media_storage_destroy(g_storage_dst);
	}
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_id = NULL;

	ret = media_storage_get_id(NULL, &storage_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	if (storage_id) {
		free(storage_id);
		storage_id = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_id = NULL;

	ret = media_storage_get_id(g_storage, &storage_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (storage_id) {
		free(storage_id);
		storage_id = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_path = NULL;

	ret = media_storage_get_path(NULL, &storage_path);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	if (storage_path) {
		free(storage_path);
		storage_path = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_path = NULL;

	ret = media_storage_get_path(g_storage, &storage_path);

	if (storage_path) {
		free(storage_path);
		storage_path = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_storage_e storage_type;

	ret = media_storage_get_type(NULL, &storage_type);

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_storage_e storage_type;

	ret = media_storage_get_type(g_storage, &storage_type);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	return 0;
}
