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

//& set: MediaTag

static media_tag_h g_tag = NULL;
static media_tag_h g_tag_dst = NULL;
static filter_h g_filter;
static int g_tag_id;
static char *g_media_id = NULL;
static char *tag_name = "tag_test_12";
static media_content_error_e cb_name_cmp_result = MEDIA_CONTENT_ERROR_NONE;

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool media_item_cb(media_info_h media, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_media_id(media, &g_media_id);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_media_id == NULL)) {
		fprintf(stderr, "CB error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_info_get_media_id failed (code: %d)\n", ret);
		return false;
	}

	return true;
}

/**
 * @function		utc_media_tag_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_tag_startup(void)
{
	g_filter = NULL;
	g_tag = NULL;
	g_tag_dst = NULL;

	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	char *condition = "MEDIA_TYPE=1 AND MEDIA_STORAGE_TYPE=0";	//Video

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
		fprintf(stderr, "media_info_foreach_media_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}
	// test if the same data already has been inserted
	ret = media_tag_insert_to_db(tag_name, &g_tag);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_tag_insert_to_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_tag_get_tag_id(g_tag, &g_tag_id);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_tag_get_tag_id failed (code: %d)\n", ret);
		startup_ret = ret;
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
	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}
	if (g_media_id) {
		free(g_media_id);
		g_media_id = NULL;
	}
	media_content_disconnect();
}

static bool tag_cb(media_tag_h tag, void *user_data)
{
	char *name = NULL;

	if (tag != NULL) {
		media_tag_get_name(tag, &name);

		if (name != NULL && strcmp(name, tag_name) == 0) {
			fprintf(stderr, " tag name : %s \n", name);
			free(name);
		}
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_insert_to_db(NULL, &g_tag);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_delete_from_db(g_tag_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	/* precondition */
	if (g_tag) {
		ret = media_tag_destroy(g_tag);
		g_tag = NULL;
		assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	}

	/* actual test */
	ret = media_tag_insert_to_db(tag_name, &g_tag);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_tag_get_tag_id(g_tag, &g_tag_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_delete_from_db(-1);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_delete_from_db(g_tag_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_get_tag_count_from_db(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int tag_count = 0;

	ret = media_tag_get_tag_count_from_db(NULL, &tag_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_foreach_tag_from_db(NULL, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	cb_name_cmp_result = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter1;

	char *g_condition = "TAG_NAME like \"%%tag%%\"";

	ret = media_filter_create(&filter1);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_filter_set_condition(filter1, g_condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_filter_set_order(filter1, MEDIA_CONTENT_ORDER_DESC, TAG_NAME, MEDIA_CONTENT_COLLATE_DEFAULT);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_tag_foreach_tag_from_db(filter1, tag_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (filter1) {
		media_filter_destroy(filter1);
		filter1 = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_get_media_count_from_db(g_tag_id, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;

	ret = media_tag_get_media_count_from_db(g_tag_id, NULL, &media_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_foreach_media_from_db(g_tag_id, NULL, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_foreach_media_from_db(g_tag_id, NULL, media_item_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_clone(&g_tag_dst, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_clone(&g_tag_dst, g_tag);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (g_tag_dst) {
		media_tag_destroy(g_tag_dst);
		g_tag_dst = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_update_to_db(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_update_to_db(g_tag);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_add_media(NULL, g_media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_add_media(g_tag, g_media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_tag_update_to_db(g_tag);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_remove_media(NULL, g_media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_remove_media(g_tag, g_media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_tag_update_to_db(g_tag);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_set_name(NULL, "myTag");
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool _set_name_cb(media_tag_h tag, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;
	int tag_id = 0;

	ret = media_tag_get_tag_id(tag, &tag_id);

	if (tag_id == g_tag_id) {
		ret = media_tag_get_name(tag, &name);

		if (strcmp(name, "myTag") != 0)
			ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	if (name) {
		free(name);
		name = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return true;
}

/**
 * @testcase		utc_media_tag_set_name_p
 * @since_tizen		2.3
 * @description		Negative test case of media_tag_set_name()
 */
int utc_media_tag_set_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_set_name(g_tag, "myTag");

	ret = media_tag_update_to_db(g_tag);

	ret = media_tag_foreach_tag_from_db(g_filter, _set_name_cb, NULL);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int tag_id = 0;

	ret = media_tag_get_tag_id(NULL, &tag_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int tag_id = 0;

	ret = media_tag_get_tag_id(g_tag, &tag_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_tag_get_name(NULL, &name);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_tag_get_name(g_tag, &name);

	if (name) {
		free(name);
		name = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_tag_h tag;

	ret = media_tag_get_tag_from_db(0, &tag);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_tag_h tag = NULL;

	ret = media_tag_get_tag_from_db(g_tag_id, &tag);

	if (tag) {
		media_tag_destroy(tag);
		tag = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_tag_destroy(g_tag);
	g_tag = NULL;

	media_tag_delete_from_db(g_tag_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
