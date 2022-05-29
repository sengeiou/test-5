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

void utc_notification_ex_group_startup(void)
{
}

void utc_notification_ex_group_cleanup(void)
{
}

/**
 * @testcase utc_noti_ex_item_group_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_group_create()
 */
int utc_noti_ex_item_group_create_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;

	ret = noti_ex_item_group_create(&item_handle, "group_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_itNONEem_group_create()
 */
int utc_noti_ex_item_group_create_n(void)
{
	int ret;

	ret = noti_ex_item_group_create(NULL, "group_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_set_direction_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_group_set_direction()
 */
int utc_noti_ex_item_group_set_direction_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	bool vertical;

	ret = noti_ex_item_group_create(&item_handle, "group_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_set_direction(item_handle, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_is_vertical(item_handle, &vertical);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(vertical, true);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_set_direction_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_group_set_direction()
 */
int utc_noti_ex_item_group_set_direction_n(void)
{
	int ret;

	ret = noti_ex_item_group_set_direction(NULL, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_is_vertical_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_group_is_vertical()
 */
int utc_noti_ex_item_group_is_vertical_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	bool vertical;

	ret = noti_ex_item_group_create(&item_handle, "group_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_set_direction(item_handle, true);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_is_vertical(item_handle, &vertical);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(vertical, true);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_is_vertical_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_group_is_vertical()
 */
int utc_noti_ex_item_group_is_vertical_n(void)
{
	int ret;
	bool vertical;

	ret = noti_ex_item_group_is_vertical(NULL, &vertical);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_get_app_label_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_group_get_app_label()
 */
int utc_noti_ex_item_group_get_app_label_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	char *label = NULL;

	ret = noti_ex_item_group_create(&item_handle, "group_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_get_app_label(item_handle, &label);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_neq_with_exit(label, NULL);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_get_app_label_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_group_get_app_label()
 */
int utc_noti_ex_item_group_get_app_label_n(void)
{
	int ret;
	char *label = NULL;

	ret = noti_ex_item_group_get_app_label(NULL, &label);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_add_child_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_group_add_child()
 */
int utc_noti_ex_item_group_add_child_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	noti_ex_item_h child_item = NULL;

	ret = noti_ex_item_group_create(&item_handle, "group_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_button_create(&child_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_add_child(item_handle, child_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_add_child_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_group_add_child()
 */
int utc_noti_ex_item_group_add_child_n(void)
{
	int ret;
	noti_ex_item_h child_item = NULL;

	ret = noti_ex_item_button_create(&child_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_add_child(NULL, child_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	noti_ex_item_destroy(child_item);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_remove_child_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_group_remove_child()
 */
int utc_noti_ex_item_group_remove_child_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	noti_ex_item_h child_item = NULL;

	ret = noti_ex_item_group_create(&item_handle, "group_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_button_create(&child_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_add_child(item_handle, child_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_remove_child(item_handle, "button_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	noti_ex_item_destroy(item_handle);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_remove_child_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_group_remove_child()
 */
int utc_noti_ex_item_group_remove_child_n(void)
{
	int ret;

	ret = noti_ex_item_group_remove_child(NULL, "button_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}

int _noti_ex_item_group_foreach_child_cb(noti_ex_item_h handle, void *user_data)
{
	int ret;
	char *id = NULL;

	ret = noti_ex_item_get_id(handle, &id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);
	assert_eq_with_exit(strcmp(id, "button_id"), 0);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_foreach_child_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_item_group_foreach_child()
 */
int utc_noti_ex_item_group_foreach_child_p(void)
{
	int ret;
	noti_ex_item_h item_handle = NULL;
	noti_ex_item_h child_item = NULL;

	ret = noti_ex_item_group_create(&item_handle, "group_id");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_button_create(&child_item, "button_id", "button_title");
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_add_child(item_handle, child_item);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_item_group_foreach_child(item_handle, _noti_ex_item_group_foreach_child_cb, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_item_group_foreach_child_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_item_group_foreach_child()
 */
int utc_noti_ex_item_group_foreach_child_n(void)
{
	int ret;

	ret = noti_ex_item_group_foreach_child(NULL, _noti_ex_item_group_foreach_child_cb, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}