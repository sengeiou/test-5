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

void utc_notification_ex_checkbox_startup(void)
{
}

void utc_notification_ex_checkbox_cleanup(void)
{
}

/**
 * @testcase utc_noti_ex_item_checkbox_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_checkbox_create()
 */
int utc_noti_ex_item_checkbox_create_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;

	ret = noti_ex_item_checkbox_create(&item_handle, "checkbox_id", "checkbox_title", false);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_checkbox_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_checkbox_create()
 */
int utc_noti_ex_item_checkbox_create_n(void)
{
	int ret;

	ret = noti_ex_item_checkbox_create(NULL, "checkbox_id", "checkbox_title", false);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_checkbox_get_title_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_checkbox_get_title()
 */
int utc_noti_ex_item_checkbox_get_title_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	char *title = NULL;

	ret = noti_ex_item_checkbox_create(&item_handle, "checkbox_id", "checkbox_title", false);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_checkbox_get_title(item_handle, &title);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(title, "checkbox_title"), 0);

	noti_ex_item_destroy(item_handle);
	free(title);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_checkbox_get_title_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_checkbox_get_title()
 */
int utc_noti_ex_item_checkbox_get_title_n(void)
{
	int ret;
	char *title = NULL;

	ret = noti_ex_item_checkbox_get_title(NULL, &title);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_checkbox_get_check_state_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_checkbox_get_check_state()
 */
int utc_noti_ex_item_checkbox_get_check_state_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	bool checked;

	ret = noti_ex_item_checkbox_create(&item_handle, "checkbox_id", "checkbox_title", false);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_checkbox_get_check_state(item_handle, &checked);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(checked, false);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_checkbox_get_check_state_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_checkbox_get_check_state()
 */
int utc_noti_ex_item_checkbox_get_check_state_n(void)
{
	int ret;
	bool checked;

	ret = noti_ex_item_checkbox_get_check_state(NULL, &checked);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_checkbox_set_check_state_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_checkbox_set_check_state()
 */
int utc_noti_ex_item_checkbox_set_check_state_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;

	ret = noti_ex_item_checkbox_create(&item_handle, "checkbox_id", "checkbox_title", false);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_checkbox_set_check_state(item_handle, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_checkbox_set_check_state_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_checkbox_set_check_state()
 */
int utc_noti_ex_item_checkbox_set_check_state_n(void)
{
	int ret;

	ret = noti_ex_item_checkbox_get_check_state(NULL, false);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_checkbox_set_multi_language_title_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_checkbox_set_multi_language_title()
 */
int utc_noti_ex_item_checkbox_set_multi_language_title_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	char *title = NULL;
	noti_ex_multi_lang_h multi;

	ret = noti_ex_item_checkbox_create(&item_handle, "checkbox_id", "checkbox_title", false);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_multi_lang_create(&multi, "TEST_ID",
		"test string(%s) integer(%d) float(%f)", "test", 777, 0.77);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_checkbox_set_multi_language_title(item_handle, multi);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_checkbox_get_title(item_handle, &title);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(title, "test string(test) integer(777) float(0.77)"), 0);
	free(title);

	noti_ex_multi_lang_destroy(multi);
	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_checkbox_set_multi_language_title_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_checkbox_set_multi_language_title()
 */
int utc_noti_ex_item_checkbox_set_multi_language_title_n(void)
{
	int ret;

	ret = noti_ex_item_checkbox_set_multi_language_title(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}
