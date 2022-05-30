//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include "assert.h"
#include <app.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <libintl.h>

#include <notification-ex/api/notification_ex.h>

#include "utc-notification.h"

void utc_notification_ex_text_startup(void)
{
}

void utc_notification_ex_text_cleanup(void)
{
}

/**
 * @testcase utc_noti_ex_item_text_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_text_create()
 */
int utc_noti_ex_item_text_create_p(void)
{
	int ret;
	noti_ex_item_h handle;

	ret = noti_ex_item_text_create(&handle, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_text_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_text_create()
 */
int utc_noti_ex_item_text_create_n(void)
{
	int ret;

	ret = noti_ex_item_text_create(NULL, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_text_set_contents_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_text_set_contents()
 */
int utc_noti_ex_item_text_set_contents_p(void)
{
	int ret;
	noti_ex_item_h handle;

	ret = noti_ex_item_text_create(&handle, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_text_set_contents(handle, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_text_set_contents_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_text_set_contents()
 */
int utc_noti_ex_item_text_set_contents_n(void)
{
	int ret;

	ret = noti_ex_item_text_set_contents(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_text_get_contents_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_text_get_contents()
 */
int utc_noti_ex_item_text_get_contents_p(void)
{
	int ret;
	noti_ex_item_h handle;
	char *contents = NULL;

	ret = noti_ex_item_text_create(&handle, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_text_set_contents(handle, "test");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_text_get_contents(handle, &contents);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_neq_with_exit(contents, NULL);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_text_get_contents_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_text_get_contents()
 */
int utc_noti_ex_item_text_get_contents_n(void)
{
	int ret;

	ret = noti_ex_item_text_get_contents(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_text_get_hyperlink_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_text_get_hyperlink()
 */
int utc_noti_ex_item_text_get_hyperlink_p(void)
{
	int ret;
	noti_ex_item_h handle;
	char *link = NULL;

	ret = noti_ex_item_text_create(&handle, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_text_get_hyperlink(handle, &link);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_neq_with_exit(link, NULL);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_text_get_hyperlink_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_text_get_hyperlink()
 */
int utc_noti_ex_item_text_get_hyperlink_n(void)
{
	int ret;

	ret = noti_ex_item_text_get_hyperlink(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_entry_set_multi_language_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_entry_set_multi_language()
 */
int utc_noti_ex_item_text_set_multi_language_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	char *text = NULL;
	noti_ex_multi_lang_h multi;

	ret = noti_ex_item_text_create(&item_handle, "text_id", "text", "hyperlink");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_multi_lang_create(&multi, "TEST_ID",
		"test string(%s) integer(%d) float(%f)", "test", 777, 0.77);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_text_set_multi_language(item_handle, multi);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_text_get_contents(item_handle, &text);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(text, "test string(test) integer(777) float(0.77)"), 0);
	free(text);

	noti_ex_multi_lang_destroy(multi);
	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_text_set_multi_language_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_text_set_multi_language()
 */
int utc_noti_ex_item_text_set_multi_language_n(void)
{
	int ret;

	ret = noti_ex_item_text_set_multi_language(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}
