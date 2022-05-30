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
#include <app_manager.h>
#include <app_control.h>

#include <notification-ex/api/notification_ex.h>
#include "utc-notification.h"

static void reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
}

void utc_notification_ex_event_info_startup(void)
{
}

void utc_notification_ex_event_info_cleanup(void)
{
}

/**
 * @testcase utc_noti_ex_event_info_clone_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_event_info_clone()
 */
int utc_noti_ex_event_info_clone_n(void)
{
	int ret;
	noti_ex_event_info_h cloned_info = NULL;

	ret = noti_ex_event_info_clone(NULL, &cloned_info);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_event_info_destroy_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_event_info_destroy()
 */
int utc_noti_ex_event_info_destroy_n(void)
{
	int ret;

	ret = noti_ex_event_info_destroy(NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_event_info_get_event_type_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_event_info_get_event_type()
 */
int utc_noti_ex_event_info_get_event_type_n(void)
{
	int ret;
	noti_ex_event_info_type_e event_type;

	ret = noti_ex_event_info_get_event_type(NULL, &event_type);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_event_info_get_owner_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_event_info_get_owner()
 */
int utc_noti_ex_event_info_get_owner_n(void)
{
	int ret;
	char *owner = NULL;

	ret = noti_ex_event_info_get_owner(NULL, &owner);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_event_info_get_channel_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_event_info_get_channel()
 */
int utc_noti_ex_event_info_get_channel_n(void)
{
	int ret;
	char *channel = NULL;

	ret = noti_ex_event_info_get_channel(NULL, &channel);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_event_info_get_item_id_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_event_info_get_item_id()
 */
int utc_noti_ex_event_info_get_item_id_n(void)
{
	int ret;
	char *item_id = NULL;

	ret = noti_ex_event_info_get_item_id(NULL, &item_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_event_info_get_request_id_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_event_info_get_request_id()
 */
int utc_noti_ex_event_info_get_request_id_n(void)
{
	int ret;
	int req_id;

	ret = noti_ex_event_info_get_request_id(NULL, &req_id);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);
	normal_exit(0);
}
