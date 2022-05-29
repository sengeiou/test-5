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

void utc_notification_ex_progress_startup(void)
{
}

void utc_notification_ex_progress_cleanup(void)
{
}

/**
 * @testcase utc_noti_ex_item_progress_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_progress_create()
 */
int utc_noti_ex_item_progress_create_p(void)
{
	int ret;
	noti_ex_item_h handle;

	ret = noti_ex_item_progress_create(&handle, "progress_id", 0.0, 0.0, 100.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_progress_create()
 */
int utc_noti_ex_item_progress_create_n(void)
{
	int ret;

	ret = noti_ex_item_progress_create(NULL, "progress_id", 0.0, 0.0, 100.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_set_current_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_progress_set_current()
 */
int utc_noti_ex_item_progress_set_current_p(void)
{
	int ret;
	noti_ex_item_h handle;

	ret = noti_ex_item_progress_create(&handle, "progress_id", 0.0, 0.0, 100.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_progress_set_current(handle, 50.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_set_current_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_progress_set_current()
 */
int utc_noti_ex_item_progress_set_current_n(void)
{
	int ret;

	ret = noti_ex_item_progress_set_current(NULL, 50.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_get_current_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_progress_get_current()
 */
int utc_noti_ex_item_progress_get_current_p(void)
{
	int ret;
	noti_ex_item_h handle;
	float current = 0.0;

	ret = noti_ex_item_progress_create(&handle, "progress_id", 0.0, 0.0, 100.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_progress_set_current(handle, 50.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_progress_get_current(handle, &current);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(current, 50.0);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_get_current_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_progress_get_current()
 */
int utc_noti_ex_item_progress_get_current_n(void)
{
	int ret;

	ret = noti_ex_item_progress_get_current(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_get_min_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_progress_get_min()
 */
int utc_noti_ex_item_progress_get_min_p(void)
{
	int ret;
	noti_ex_item_h handle;
	float min;

	ret = noti_ex_item_progress_create(&handle, "progress_id", 0.0, 0.0, 100.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_progress_get_min(handle, &min);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(min, 0);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_get_min_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_progress_get_min()
 */
int utc_noti_ex_item_progress_get_min_n(void)
{
	int ret;

	ret = noti_ex_item_progress_get_min(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_get_max_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_progress_get_max()
 */
int utc_noti_ex_item_progress_get_max_p(void)
{
	int ret;
	noti_ex_item_h handle;
	float max;

	ret = noti_ex_item_progress_create(&handle, "progress_id", 0.0, 0.0, 100.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_progress_get_max(handle, &max);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(max, 100.0);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_get_max_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_progress_get_max()
 */
int utc_noti_ex_item_progress_get_max_n(void)
{
	int ret;

	ret = noti_ex_item_progress_get_max(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_set_type_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_progress_set_type()
 */
int utc_noti_ex_item_progress_set_type_p(void)
{
	int ret;
	noti_ex_item_h handle;

	ret = noti_ex_item_progress_create(&handle, "progress_id", 0.0, 0.0, 100.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_progress_set_type(handle, NOTI_EX_ITEM_PROGRESS_TYPE_PERCENT);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_set_type_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_progress_set_type()
 */
int utc_noti_ex_item_progress_set_type_n(void)
{
	int ret;
	ret = noti_ex_item_progress_set_type(NULL, 0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_get_type_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_progress_get_type()
 */
int utc_noti_ex_item_progress_get_type_p(void)
{
	int ret;
	noti_ex_item_h handle;
	int type;

	ret = noti_ex_item_progress_create(&handle, "progress_id", 0.0, 0.0, 100.0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_progress_set_type(handle, NOTI_EX_ITEM_PROGRESS_TYPE_PERCENT);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	ret = noti_ex_item_progress_get_type(handle, &type);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_progress_get_type_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_progress_get_type()
 */
int utc_noti_ex_item_progress_get_type_n(void)
{
	int ret;
	ret = noti_ex_item_progress_get_type(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}
