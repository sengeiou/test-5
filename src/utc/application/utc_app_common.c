/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>
#include <dlog.h>
#include <app_common.h>

#include "assert.h"
#include "assert_common.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "NativeTCT"

void utc_application_app_watchdog_timer_enable_p_cleanup(void)
{
	app_watchdog_timer_disable();
}

/**
 * @testcase            utc_application_app_watchdog_timer_enable_p
 * @since_tizen         5.5
 * @type                Positive
 * @description         Sends the enable request to activate the watchdog timer
 * @scenario            Enables the watchdog timer.
 *                      Calls the app_watchdog_timer_enable() and then checks the return value.
 *                      After the app_watchdog_timer_enable() is called, the system detects a timeout error.
 */
int utc_application_app_watchdog_timer_enable_p(void)
{
	int ret;

	ret = app_watchdog_timer_enable();
	assert_eq_with_exit(ret, APP_ERROR_NONE);

	normal_exit(0);

	return 0;
}

void utc_application_app_watchdog_timer_disable_p_startup(void)
{
	int ret;

	ret = app_watchdog_timer_enable();
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to enable watchdog timer");
		normal_exit(1);
	}
}

/**
 * @testcase            utc_application_app_watchdog_timer_disable_p
 * @since_tizen         5.5
 * @type                Positive
 * @description         Sends the disable request to deactivate the watchdog timer
 * @scenario            Disables the watchdog timer.
 *                      Calls the app_watchdog_timer_disable() and then checks the return value.
 *                      After the app_watchdog_timer_disable() is called, the system doesn't detect a timeout error.
 */
int utc_application_app_watchdog_timer_disable_p(void)
{
	int ret;

	ret = app_watchdog_timer_disable();
	assert_eq_with_exit(ret, APP_ERROR_NONE);

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_watchdog_timer_disable_n
 * @since_tizen         5.5
 * @type                Negative
 * @description         Sends the disable request to deactivate the watchdog timer
 * @scenario            Disables the watchdog timer.
 *                      Calls the app_watchdog_timer_disable() and then checks the return value.
 *                      The return value is AP_ERROR_INVALID_CONTEXT.
 */
int utc_application_app_watchdog_timer_disable_n(void)
{
	int ret;

	ret = app_watchdog_timer_disable();
	assert_eq_with_exit(ret, APP_ERROR_INVALID_CONTEXT);

	normal_exit(0);

	return 0;
}


void utc_application_app_watchdog_timer_kick_p_startup(void)
{
	int ret;

	ret = app_watchdog_timer_enable();
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to enable watchdog timer");
		normal_exit(1);
	}
}

void utc_application_app_watchdog_timer_kick_p_cleanup(void)
{
	int ret;

	ret = app_watchdog_timer_disable();
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to disable watchdog timer");
	}
}

/**
 * @testcase            utc_application_app_watchdog_timer_kick_p
 * @since_tizen         5.5
 * @type                Positive
 * @description         Sends the kick request to reset the watchdog timer
 * @scenario            kicks the watchdog timer.
 *                      Calls the app_watchdog_timer_kick() and then checks the return value.
 *                      Before the function is called, the watchdog timer has to be enabled.
 */
int utc_application_app_watchdog_timer_kick_p(void)
{
	int ret;

	ret = app_watchdog_timer_kick();
	assert_eq_with_exit(ret, APP_ERROR_NONE);

	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_watchdog_timer_kick_n
 * @since_tizen         5.5
 * @type                Negative
 * @description         Sends the kick request to reset the watchdog timer
 * @scenario            kicks the watchdog timer.
 *                      Calls the app_watchdog_timer_kick() and then checks the return value.
 */
int utc_application_app_watchdog_timer_kick_n(void)
{
	int ret;

	ret = app_watchdog_timer_kick();
	assert_eq_with_exit(ret, APP_ERROR_INVALID_CONTEXT);

	normal_exit(0);

	return 0;
}
