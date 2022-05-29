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

void utc_notification_ex_input_selector_startup(void)
{
}

void utc_notification_ex_input_selector_cleanup(void)
{
}

/**
 * @testcase utc_noti_ex_item_input_selector_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_input_selector_create()
 */
int utc_noti_ex_item_input_selector_create_p(void)
{
	int ret;
	noti_ex_item_h handle;

	ret = noti_ex_item_input_selector_create(&handle, "input_selector_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_input_selector_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_input_selector_create()
 */
int utc_noti_ex_item_input_selector_create_n(void)
{
	int ret;

	ret = noti_ex_item_input_selector_create(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc _noti_ex_item_input_selector_set_contents_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_input_selector_set_contents()
 */
int utc_noti_ex_item_input_selector_set_contents_p(void)
{
	int ret;
	noti_ex_item_h handle;
	const char *contents[] = {"contest_1", "content_2"};

	ret = noti_ex_item_input_selector_create(&handle, "input_selector_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_input_selector_set_contents(handle, contents, 2);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_input_selector_set_contents_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_input_selector_set_contents()
 */
int utc_noti_ex_item_input_selector_set_contents_n(void)
{
	int ret;

	ret = noti_ex_item_input_selector_set_contents(NULL, NULL, 0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_input_selector_get_contents_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_input_selector_get_contents()
 */
int utc_noti_ex_item_input_selector_get_contents_p(void)
{
	int ret;
	int count = 0;
	noti_ex_item_h handle;
	const char *contents[] = {"content_1", "content_2"};
	char **contents_ = NULL;

	ret = noti_ex_item_input_selector_create(&handle, "input_selector_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_input_selector_set_contents(handle, contents, 2);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_input_selector_get_contents(handle, &contents_, &count);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(count, 2);
	assert_neq_with_exit(contents_, NULL);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_input_selector_get_contents_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_input_selector_get_contents()
 */
int utc_noti_ex_item_input_selector_get_contents_n(void)
{
	int ret;

	ret = noti_ex_item_input_selector_get_contents(NULL, NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_input_selector_set_multi_language_contents_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_input_selector_set_multi_language_contents()
 */
int utc_noti_ex_item_input_selector_set_multi_language_contents_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	char *text = NULL;
	noti_ex_multi_lang_h multi;
	noti_ex_multi_lang_h *contents;
	char **out_contents = NULL;
	char buf[256];
	int count;

	contents = (noti_ex_multi_lang_h *)calloc(3, sizeof(noti_ex_multi_lang_h));
	ret = noti_ex_item_input_selector_create(&item_handle, "input_selector_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	for (int i = 0; i < 3; i++) {
		noti_ex_multi_lang_create(&contents[i], "TEST_ID",
			"test string(%s) integer(%d) float(%f)", "test", i, 0.77);
	}

	ret = noti_ex_item_input_selector_set_multi_language_contents(item_handle, contents, 3);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_input_selector_get_contents(item_handle, &out_contents, &count);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(count, 3);

	for (int i = 0; i < count; i++) {
		snprintf(buf, sizeof(buf), "test string(test) integer(%d) float(0.77)", i);
		assert_eq_with_exit(strcmp(out_contents[i], buf), 0);
	}

	for (int i = 0; i < count; i++) {
		noti_ex_multi_lang_destroy(contents[i]);
		free(out_contents[i]);
	}
	free(out_contents);
	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_input_selector_set_multi_language_contents_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_input_selector_set_multi_language_contents()
 */
int utc_noti_ex_item_input_selector_set_multi_language_contents_n(void)
{
	int ret;

	ret = noti_ex_item_input_selector_set_multi_language_contents(NULL, NULL, 0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}
