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

void utc_notification_ex_image_startup(void)
{
}

void utc_notification_ex_image_cleanup(void)
{
}

/**
 * @testcase utc_noti_ex_item_image_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_image_create()
 */
int utc_noti_ex_item_image_create_p(void)
{
	int ret;
	noti_ex_item_h handle;

	//ret = noti_ex_item_image_create(&handle, "image_id", "image_path");
	ret = noti_ex_item_image_create(&handle, NULL, "image_path");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_image_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_image_create()
 */
int utc_noti_ex_item_image_create_n(void)
{
	int ret;

	ret = noti_ex_item_image_create(NULL, NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_image_get_image_path_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_image_get_image_path()
 */
int utc_noti_ex_item_image_get_image_path_p(void)
{
	int ret;
	char *image_path = NULL;
	noti_ex_item_h handle;

	ret = noti_ex_item_image_create(&handle, "image_id", "image_path");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_image_get_image_path(handle, &image_path);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_neq_with_exit(image_path, NULL);

	ret = noti_ex_item_destroy(handle);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_image_get_image_path_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_image_get_image_path()
 */
int utc_noti_ex_item_image_get_image_path_n(void)
{
	int ret;

	ret = noti_ex_item_image_get_image_path(NULL, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}
