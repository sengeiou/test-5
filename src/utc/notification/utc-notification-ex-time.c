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
#include <time.h>

#include <notification-ex/api/notification_ex.h>

#include "utc-notification.h"

void utc_notification_ex_time_startup(void)
{
}

void utc_notification_ex_time_cleanup(void)
{
}

/**
 * @testcase utc_noti_ex_item_time_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_time_create()
 */
int utc_noti_ex_item_time_create_p(void)
{
	int ret;
	noti_ex_item_h handle;
	time_t cur;

	time(&cur);
	ret = noti_ex_item_time_create(&handle, "time_id", cur);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_time_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_time_create()
 */
int utc_noti_ex_item_time_create_n(void)
{
	int ret;

	ret = noti_ex_item_time_create(NULL, "time_id", 0);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_time_get_time_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_time_get_time()
 */
int utc_noti_ex_item_time_get_time_p(void)
{
	int ret;
	noti_ex_item_h handle;
	time_t cur;
	time_t time_;

	time(&cur);
	ret = noti_ex_item_time_create(&handle, "time_id", cur);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_time_get_time(handle, &time_);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_neq_with_exit(time_, 0);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_time_get_time_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_time_get_time()
 */
int utc_noti_ex_item_time_get_time_n(void)
{
	int ret;

	ret = noti_ex_item_time_get_time(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}
