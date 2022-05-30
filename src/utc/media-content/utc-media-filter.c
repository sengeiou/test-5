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

#define API_NAMESPACE "[MEDIA-CONTENT]"

//& set: MediaFilter

static filter_h g_filter = NULL;

/**
 * @function		utc_media_filter_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_filter_startup(void)
{
	if (media_filter_create(&g_filter) != MEDIA_CONTENT_ERROR_NONE)
		FPRINTF("[Line : %d] media_filter_create failed.\\n", __LINE__);
}

/**
 * @function		utc_media_filter_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_filter_cleanup(void)
{
	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}
}

/**
 * @testcase		utc_media_filter_create_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_create()
 */
int utc_media_filter_create_n(void)
{
	assert_eq(media_filter_create(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_create_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_create()
 */
int utc_media_filter_create_p(void)
{
	assert_eq(media_filter_destroy(g_filter), MEDIA_CONTENT_ERROR_NONE);
	g_filter = NULL;

	assert_eq(media_filter_create(&g_filter), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_destroy()
 */
int utc_media_filter_destroy_n(void)
{
	assert_eq(media_filter_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_destroy()
 */
int utc_media_filter_destroy_p(void)
{
	assert_eq(media_filter_destroy(g_filter), MEDIA_CONTENT_ERROR_NONE);
	g_filter = NULL;

	return 0;
}

/**
 * @testcase		utc_media_filter_set_offset_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_set_offset()
 */
int utc_media_filter_set_offset_n(void)
{
	assert_eq(media_filter_set_offset(NULL, 0, 3), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_offset_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_set_offset()
 */
int utc_media_filter_set_offset_p(void)
{
	assert_eq(media_filter_set_offset(g_filter, 0, 3), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_condition_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_set_condition()
 */
int utc_media_filter_set_condition_n(void)
{
	assert_eq(media_filter_set_condition(NULL, "MEDIA_TYPE=3", MEDIA_CONTENT_COLLATE_NOCASE), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_condition_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_set_condition()
 */
int utc_media_filter_set_condition_p(void)
{
	assert_eq(media_filter_set_condition(g_filter, "MEDIA_TYPE=3", MEDIA_CONTENT_COLLATE_NOCASE), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_order_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_set_order()
 */
int utc_media_filter_set_order_n(void)
{
	assert_eq(media_filter_set_order(NULL, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_order_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_set_order()
 */
int utc_media_filter_set_order_p(void)
{
	assert_eq(media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_DEFAULT), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_storage_n
 * @since_tizen		2.4
 * @description		Negative test case of media_filter_set_storage()
 */
int utc_media_filter_set_storage_n(void)
{
	assert_eq(media_filter_set_storage(NULL, "media"), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_set_storage_p
 * @since_tizen		2.4
 * @description		Positive test case of media_filter_set_storage()
 */
int utc_media_filter_set_storage_p(void)
{
	assert_eq(media_filter_set_storage(g_filter, "media"), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_offset_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_get_offset()
 */
int utc_media_filter_get_offset_n(void)
{
	int offset = 0;
	int count = 0;

	assert_eq(media_filter_get_offset(NULL, &offset, &count), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_offset_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_get_offset()
 */
int utc_media_filter_get_offset_p(void)
{
	int offset = 0;
	int count = 0;

	assert_eq(media_filter_get_offset(g_filter, &offset, &count), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_condition_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_get_condition()
 */
int utc_media_filter_get_condition_n(void)
{
	char *condition = NULL;
	media_content_collation_e collate_type = MEDIA_CONTENT_COLLATE_DEFAULT;

	assert_eq(media_filter_get_condition(NULL, &condition, &collate_type), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_condition_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_get_condition()
 */
int utc_media_filter_get_condition_p(void)
{
	char *condition = NULL;
	media_content_collation_e collate_type = MEDIA_CONTENT_COLLATE_DEFAULT;

	assert_eq(media_filter_set_condition(g_filter, "MEDIA_TYPE=3", MEDIA_CONTENT_COLLATE_NOCASE), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_filter_get_condition(g_filter, &condition, &collate_type), MEDIA_CONTENT_ERROR_NONE);
	CHECK_VALUE_STRING(condition, "media_filter_get_condition");
	assert_eq(collate_type, MEDIA_CONTENT_COLLATE_NOCASE);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_order_n
 * @since_tizen		2.3
 * @description		Negative test case of media_filter_get_order()
 */
int utc_media_filter_get_order_n(void)
{
	media_content_order_e order = MEDIA_CONTENT_ORDER_ASC;
	char *keyword = NULL;
	media_content_collation_e collate = MEDIA_CONTENT_COLLATE_DEFAULT;

	assert_eq(media_filter_get_order(NULL, &order, &keyword, &collate), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_order_p
 * @since_tizen		2.3
 * @description		Positive test case of media_filter_get_order()
 */
int utc_media_filter_get_order_p(void)
{
	media_content_order_e order = MEDIA_CONTENT_ORDER_ASC;
	char *keyword = NULL;
	media_content_collation_e collate = MEDIA_CONTENT_COLLATE_DEFAULT;

	assert_eq(media_filter_set_order(g_filter, MEDIA_CONTENT_ORDER_DESC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_RTRIM), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_filter_get_order(g_filter, &order, &keyword, &collate), MEDIA_CONTENT_ERROR_NONE);
	CHECK_VALUE_STRING(keyword, "media_filter_get_order");
	assert_eq(order, MEDIA_CONTENT_ORDER_DESC);
	assert_eq(collate, MEDIA_CONTENT_COLLATE_RTRIM);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_storage_n
 * @since_tizen		2.4
 * @description		Negative test case of media_filter_get_storage()
 */
int utc_media_filter_get_storage_n(void)
{
	char *storage_id = NULL;

	assert_eq(media_filter_get_storage(NULL, &storage_id), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_filter_get_storage_p
 * @since_tizen		2.4
 * @description		Positive test case of media_filter_get_storage()
 */
int utc_media_filter_get_storage_p(void)
{
	char *storage_id = NULL;

	assert_eq(media_filter_set_storage(g_filter, "media"), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_filter_get_storage(g_filter, &storage_id), MEDIA_CONTENT_ERROR_NONE);
	CHECK_VALUE_STRING(storage_id, "media_filter_get_storage");

	return 0;
}
