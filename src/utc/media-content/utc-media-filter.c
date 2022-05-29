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

#define SET_TEST_CONDITION "MEDIA_TYPE=3"
//& set: MediaFilter

static filter_h g_filter = NULL;

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

/**
 * @function		utc_media_filter_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_filter_startup(void)
{
	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_create(&g_filter);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_filter_create failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

}

/**
 * @function		utc_media_filter_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_filter_cleanup(void)
{
	media_filter_destroy(g_filter);
	g_filter = NULL;
}

/**
 * @testcase		utc_media_filter_set_offset_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_set_offset()
 */
int utc_media_filter_set_offset_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_offset(NULL, 0, 3);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_offset_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_set_offset()
 */
int utc_media_filter_set_offset_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_offset(g_filter, 0, 3);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_condition_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_set_condition()
 */
int utc_media_filter_set_condition_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_condition(NULL, SET_TEST_CONDITION, MEDIA_CONTENT_COLLATE_NOCASE);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_condition_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_set_condition()
 */
int utc_media_filter_set_condition_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_condition(g_filter, SET_TEST_CONDITION, MEDIA_CONTENT_COLLATE_NOCASE);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_order_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_set_order()
 */
int utc_media_filter_set_order_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_order(NULL, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_order_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_set_order()
 */
int utc_media_filter_set_order_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_storage_n
 * @since_tizen		2.4
 * @description		Negative test case of media_filter_set_storage()
 */
int utc_media_filter_set_storage_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	const char *storage_id = "media";

	ret = media_filter_set_storage(NULL, storage_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_storage_p
 * @since_tizen		2.4
 * @description		Positive test case of media_filter_set_storage()
 */
int utc_media_filter_set_storage_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	const char *storage_id = "media";

	ret = media_filter_set_storage(g_filter, storage_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_offset_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_get_offset()
 */
int utc_media_filter_get_offset_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int offset = 0;
	int count = 0;

	ret = media_filter_get_offset(NULL, &offset, &count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_offset_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_get_offset()
 */
int utc_media_filter_get_offset_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int offset = 0;
	int count = 0;

	ret = media_filter_get_offset(g_filter, &offset, &count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_condition_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_get_condition()
 */
int utc_media_filter_get_condition_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *condition = NULL;
	media_content_collation_e collate_type = -1;

	ret = media_filter_get_condition(NULL, &condition, &collate_type);

	if (condition) {
		free(condition);
		condition = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_condition_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_get_condition()
 */
int utc_media_filter_get_condition_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *condition = NULL;
	media_content_collation_e collate_type = -1;

	ret = media_filter_set_condition(g_filter, SET_TEST_CONDITION, MEDIA_CONTENT_COLLATE_NOCASE);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_filter_get_condition(g_filter, &condition, &collate_type);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (condition != NULL) {
		if (strcmp(condition, SET_TEST_CONDITION))
			ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

		free(condition);
		condition = NULL;
	} else {
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (collate_type != MEDIA_CONTENT_COLLATE_NOCASE)
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_order_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_get_order()
 */
int utc_media_filter_get_order_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_order_e order;
	char *order_keyword = NULL;
	media_content_collation_e collate_type = -1;

	ret = media_filter_get_order(NULL, &order, &order_keyword, &collate_type);

	if (order_keyword) {
		free(order_keyword);
		order_keyword = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_order_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_get_order()
 */
int utc_media_filter_get_order_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_order_e order = 0;
	char *order_keyword = NULL;
	media_content_collation_e collate_type = -1;

	ret = media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_filter_get_order(g_filter, &order, &order_keyword, &collate_type);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (order_keyword != NULL) {
		if (strcmp(order_keyword, MEDIA_TITLE))
			ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

		free(order_keyword);
		order_keyword = NULL;
	} else {
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (order != MEDIA_CONTENT_ORDER_ASC)
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (collate_type != MEDIA_CONTENT_COLLATE_DEFAULT)
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_storage_n
 * @since_tizen		2.4
 * @description		Negative test case of media_filter_get_storage()
 */
int utc_media_filter_get_storage_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_id = NULL;

	ret = media_filter_get_storage(NULL, &storage_id);

	if (storage_id) {
		free(storage_id);
		storage_id = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_storage_p
 * @since_tizen		2.4
 * @description		Positive test case of media_filter_get_storage()
 */
int utc_media_filter_get_storage_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_id = NULL;

	ret = media_filter_set_storage(g_filter, "media");
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_filter_get_storage(g_filter, &storage_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (storage_id != NULL) {
		if (strcmp(storage_id, "media"))
			ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

		free(storage_id);
		storage_id = NULL;
	} else {
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
