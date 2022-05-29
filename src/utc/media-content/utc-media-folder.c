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

#define TEST_SET_CONDITION "MEDIA_TYPE=0"
#define TEST_SET_CONDITION_WITH_STORAGE_TYPE "MEDIA_TYPE=0 and MEDIA_STORAGE_TYPE=0"
#define TEST_SET_NAME "new_test"
#define TEST_DEFAULT_NAME "test"

//& set: MediaFolder

static media_folder_h g_folder = NULL;
static media_folder_h g_test_folder = NULL;
static filter_h g_filter = NULL;

static char *g_folder_path = NULL;
static char *g_test_folder_path = NULL;
static char *g_default_folder_path = NULL;
static char *g_set_folder_path = NULL;

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool __storage_device_supported_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
	char temp[500];
	if (type == STORAGE_TYPE_INTERNAL) {
		memset(temp, 0x00, sizeof(temp));
		snprintf(temp, sizeof(temp), "%s/%s", path, "res");
		g_default_folder_path = strdup(temp);

		memset(temp, 0x00, sizeof(temp));
		snprintf(temp, sizeof(temp), "%s/res/%s", path, TEST_SET_NAME);
		g_set_folder_path = strdup(temp);

		memset(temp, 0x00, sizeof(temp));
		snprintf(temp, sizeof(temp), "%s/%s", path, "res/test");
		g_test_folder_path = strdup(temp);

		return false;
	}
	return true;
}

static bool capi_folder_list_cb(media_folder_h folder, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	if (folder != NULL) {
		media_folder_get_path(folder, &g_folder_path);

		if (strcmp(g_folder_path, g_test_folder_path) == 0) {
			ret = media_folder_clone(&g_test_folder, folder);
			if (ret != MEDIA_CONTENT_ERROR_NONE) {
				fprintf(stderr, "CB error at %s:%d\n", __FILE__, __LINE__);
				fprintf(stderr, "g_test_folder cloning failed (code: %d)\n", ret);
			}

		} else if (strcmp(g_folder_path, g_default_folder_path) == 0) {
			ret = media_folder_clone(&g_folder, folder);
			if (ret != MEDIA_CONTENT_ERROR_NONE) {
				fprintf(stderr, "CB error at %s:%d\n", __FILE__, __LINE__);
				fprintf(stderr, "g_folder cloning failed (code: %d)\n", ret);
			}

		}
	}

	if (g_folder_path) {
		free(g_folder_path);
		g_folder_path = NULL;
	}

	return true;
}

/**
 * @function		utc_media_folder_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_folder_startup(void)
{
	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;
	g_filter = NULL;
	if (storage_foreach_device_supported(__storage_device_supported_cb, NULL) != STORAGE_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	media_filter_create(&g_filter);
	media_filter_set_condition(g_filter, "FOLDER_STORAGE_TYPE=0", MEDIA_CONTENT_COLLATE_DEFAULT);

	if (!g_filter) {
		startup_ret = ret;
		return;
	}
	ret = media_folder_foreach_folder_from_db(g_filter, capi_folder_list_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = ret;
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

	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}
	if (g_folder) {
		media_folder_destroy(g_folder);
		g_folder = NULL;
	}
	if (g_test_folder) {
		media_folder_destroy(g_test_folder);
		g_test_folder = NULL;
	}
	if (g_folder_path) {
		free(g_folder_path);
		g_folder_path = NULL;
	}
	if (g_test_folder_path) {
		free(g_test_folder_path);
		g_test_folder_path = NULL;
	}
	if (g_default_folder_path) {
		free(g_default_folder_path);
		g_default_folder_path = NULL;
	}
	if (g_set_folder_path) {
		free(g_set_folder_path);
		g_set_folder_path = NULL;
	}
}

/**
 * @testcase		utc_media_folder_foreach_folder_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_foreach_folder_from_db()
 */
int utc_media_folder_foreach_folder_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_foreach_folder_from_db(NULL, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter;

	/* precondition */
	if (g_folder) {
		media_folder_destroy(g_folder);
		g_folder = NULL;
	}

	/* actual test */
	ret = media_filter_create(&filter);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_folder_foreach_folder_from_db(filter, capi_folder_list_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int cnt;

	ret = media_folder_get_media_count_from_db(NULL, NULL, &cnt);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int cnt;

	filter_h filter;

	ret = media_filter_create(&filter);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_filter_set_condition(filter, TEST_SET_CONDITION, MEDIA_CONTENT_COLLATE_DEFAULT);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	char *folder_id = NULL;
	ret = media_folder_get_folder_id(g_folder, &folder_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_folder_get_media_count_from_db(folder_id, filter, &cnt);

	if (folder_id) {
		free(folder_id);
		folder_id = NULL;
	}

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

static bool sub_media_cb(media_info_h media, void *user_data)
{
	return true;
}

/**
 * @testcase		utc_media_folder_foreach_media_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_folder_foreach_media_from_db()
 */
int utc_media_folder_foreach_media_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	filter_h filter;

	ret = media_filter_create(&filter);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_filter_set_condition(filter, TEST_SET_CONDITION, MEDIA_CONTENT_COLLATE_DEFAULT);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_folder_foreach_media_from_db(NULL, filter, sub_media_cb, NULL);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	filter_h filter;
	ret = media_filter_create(&filter);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_filter_set_condition(filter, TEST_SET_CONDITION, MEDIA_CONTENT_COLLATE_DEFAULT);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	char *folder_id = NULL;
	ret = media_folder_get_folder_id(g_folder, &folder_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_folder_foreach_media_from_db(folder_id, filter, sub_media_cb, NULL);

	if (folder_id) {
		free(folder_id);
		folder_id = NULL;
	}

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_folder_h dst_folder = NULL;

	ret = media_folder_clone(&dst_folder, NULL);

	if (dst_folder) {
		media_folder_destroy(dst_folder);
		dst_folder = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_folder_h dst_folder = NULL;

	ret = media_folder_clone(&dst_folder, g_folder);

	if (dst_folder) {
		media_folder_destroy(dst_folder);
		dst_folder = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *path = NULL;

	ret = media_folder_get_path(NULL, &path);

	if (path) {
		free(path);
		path = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *path = NULL;

	ret = media_folder_get_path(g_folder, &path);

	if (path) {
		free(path);
		path = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_folder_get_name(NULL, &name);

	if (name) {
		free(name);
		name = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_folder_get_name(g_folder, &name);

	if (name) {
		free(name);
		name = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_storage_e type;

	ret = media_folder_get_storage_type(NULL, &type);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_storage_e type;

	ret = media_folder_get_storage_type(g_folder, &type);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_id = NULL;

	ret = media_folder_get_storage_id(NULL, &storage_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_id = NULL;

	ret = media_folder_get_storage_id(g_folder, &storage_id);

	if (storage_id) {
		free(storage_id);
		storage_id = NULL;
	}
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_get_folder_id(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *folder_id = NULL;

	ret = media_folder_get_folder_id(g_folder, &folder_id);

	if (folder_id) {
		free(folder_id);
		folder_id = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_get_folder_from_db(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *folder_id = NULL;
	media_folder_h folder_info = NULL;

	ret = media_folder_get_folder_id(g_folder, &folder_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_folder_get_folder_from_db(folder_id, &folder_info);

	if (folder_id) {
		free(folder_id);
		folder_id = NULL;
	}
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (folder_info) {
		ret = media_folder_destroy(folder_info);
		folder_info = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_get_folder_count_from_db(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int cnt = 0;

	filter_h filter;
	ret = media_filter_create(&filter);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_filter_set_condition(filter, TEST_SET_CONDITION, MEDIA_CONTENT_COLLATE_DEFAULT);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_folder_get_folder_count_from_db(filter, &cnt);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_folder_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	if (g_folder) {
		ret = media_folder_destroy(g_folder);
		g_folder = NULL;
		assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	} else
		return -1;

	return 0;
}
