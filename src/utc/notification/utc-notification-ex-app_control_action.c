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

void utc_notification_ex_app_control_action_startup(void)
{
}

void utc_notification_ex_app_control_action_cleanup(void)
{
}

/**
 * @testcase utc_noti_ex_action_app_control_create_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_action_app_control_create()
 */
int utc_noti_ex_action_app_control_create_p(void)
{
	int ret;
	app_control_h app_control = NULL;
	noti_ex_action_h appcontrol_action = NULL;

	app_control_create(&app_control);
	app_control_set_app_id(app_control, "temp_appid");

	ret = noti_ex_action_app_control_create(&appcontrol_action, app_control, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	app_control_destroy(app_control);
	noti_ex_action_destroy(appcontrol_action);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_app_control_create_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_action_app_control_create()
 */
int utc_noti_ex_action_app_control_create_n(void)
{
	int ret;
	app_control_h app_control = NULL;

	app_control_create(&app_control);
	app_control_set_app_id(app_control, "temp_appid");

	ret = noti_ex_action_app_control_create(NULL, app_control, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	app_control_destroy(app_control);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_app_control_set_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_action_app_control_set()
 */
int utc_noti_ex_action_app_control_set_p(void)
{
	int ret;
	app_control_h app_control = NULL;
	app_control_h new_app_control = NULL;
	noti_ex_action_h appcontrol_action = NULL;

	app_control_create(&app_control);
	app_control_set_app_id(app_control, "temp_appid");

	ret = noti_ex_action_app_control_create(&appcontrol_action, app_control, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	app_control_create(&new_app_control);
	app_control_set_app_id(new_app_control, "new_appid");

	ret = noti_ex_action_app_control_set(appcontrol_action, new_app_control);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	app_control_destroy(app_control);
	app_control_destroy(new_app_control);
	noti_ex_action_destroy(appcontrol_action);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_app_control_set_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_action_app_control_set()
 */
int utc_noti_ex_action_app_control_set_n(void)
{
	int ret;
	app_control_h app_control = NULL;

	app_control_create(&app_control);
	app_control_set_app_id(app_control, "temp_appid");

	ret = noti_ex_action_app_control_set(NULL, app_control);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	app_control_destroy(app_control);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_app_control_get_p
 * @since_tizen 5.5
 * @description Positive test case of noti_ex_action_app_control_get()
 */
int utc_noti_ex_action_app_control_get_p(void)
{
	int ret;
	app_control_h app_control = NULL;
	app_control_h new_app_control = NULL;
	noti_ex_action_h appcontrol_action = NULL;

	app_control_create(&app_control);
	app_control_set_app_id(app_control, "temp_appid");

	ret = noti_ex_action_app_control_create(&appcontrol_action, app_control, NULL);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	ret = noti_ex_action_app_control_get(appcontrol_action, &new_app_control);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_NONE);

	app_control_destroy(app_control);
	noti_ex_action_destroy(appcontrol_action);
	normal_exit(0);
}

/**
 * @testcase utc_noti_ex_action_app_control_get_n
 * @since_tizen 5.5
 * @description Negative test case of noti_ex_action_app_control_get()
 */
int utc_noti_ex_action_app_control_get_n(void)
{
	int ret;
	app_control_h app_control = NULL;

	ret = noti_ex_action_app_control_get(NULL, &app_control);
	assert_eq_with_exit(ret, NOTI_EX_ERROR_INVALID_PARAMETER);

	normal_exit(0);
}
