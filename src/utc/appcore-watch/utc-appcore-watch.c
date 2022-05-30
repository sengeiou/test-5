//
// Copyright (c) 2015 Samsung Electronics Co., Ltd.
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
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <watch_app.h>
#include <watch_app_efl.h>
#include <Evas.h>
#define TIMEZONE_BUFFER_MAX 1024
#include <unistd.h>
#include <system_info.h>

#define WATCH_APP_FEATURE "http://tizen.org/feature/watchapplication"

bool is_supported = true;

static void handler(int sig)
{
    watch_app_exit();
}

/**
 * @function            utc_appcore_watch_startup
 * @description         Called before each test
 * @parameter           NA
 * @return                      NA
 */
void utc_appcore_watch_startup(void)
{
	system_info_get_platform_bool(WATCH_APP_FEATURE, &is_supported);
	alarm(4);
}

/**
 * @function            utc_appcore_watch_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return                      NA
 */
void utc_appcore_watch_cleanup(void)
{
    alarm(0);
}

static bool _app_create(int width, int height, void *user_data)
{
	return true;
}

static void _app_terminate(void *user_data)
{
}

static void _app_control(app_control_h app_control, void *user_data)
{
}

static void _app_pause(void *user_data)
{
}

static void _app_resume(void *user_data)
{
}

static void _app_time_tick(void *user_data)
{
}

static void _app_ambient_tick(void *user_data)
{
}

static void _app_ambient_changed(void *user_data)
{
}

/**
 * @testcase            utc_appcore_watch_watch_app_main_n1
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Runs the main loop of the watch app.
 * @scenario            Calls watch_app_main() function.
 */
int utc_appcore_watch_watch_app_main_n1(void)
{
	int ret;
	char *argv[] = {"test", "argv"};
	watch_app_lifecycle_callback_s ops;

	ops.create = (watch_app_create_cb)_app_create;

	ret = watch_app_main(0, argv, &ops, NULL);

	if (is_supported == false) {
		assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_main_n2
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Runs the main loop of the watch app.
 * @scenario            Calls watch_app_main() function.
 */
int utc_appcore_watch_watch_app_main_n2(void)
{
	int ret;
	int argc = 2;
	watch_app_lifecycle_callback_s ops;

	ops.create = (watch_app_create_cb)_app_create;

	ret = watch_app_main(argc, NULL, &ops, NULL);

        if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_main_n3
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Runs the main loop of the watch app.
 * @scenario            Calls watch_app_main() function.
 */
int utc_appcore_watch_watch_app_main_n3(void)
{
	int ret;
	int argc = 2;
	char *argv[] = {"test", "argv"};
	watch_app_lifecycle_callback_s ops;

	ret = watch_app_main(argc, argv, NULL, NULL);

        if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
		return 0;
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	ops.create = NULL;
	ret = watch_app_main(argc, argv, &ops, NULL);
	assert_eq(ret, APP_ERROR_INVALID_PARAMETER);

	return 0;
}

static void event_callback(void *event, void *data)
{
}


/**
 * @testcase            utc_appcore_watch_watch_app_add_event_handler_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Add watch app event handler.
 * @scenario            Calls watch_app_add_event_handler function.
 */
int utc_appcore_watch_watch_app_add_event_handler_p(void)
{
	int ret;
	app_event_handler_h handler;

	ret = watch_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, (app_event_cb)event_callback, NULL);

        if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_app_remove_event_handler(handler);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_add_event_handler_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Add watch app event handler.
 * @scenario            Calls watch_app_add_event_handler function.
 */
int utc_appcore_watch_watch_app_add_event_handler_n(void)
{
	int ret;
	app_event_handler_h handler;

	ret = watch_app_add_event_handler(NULL, APP_EVENT_LOW_MEMORY, (app_event_cb)event_callback, NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
		return 0;
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	ret = watch_app_add_event_handler(&handler, -1, (app_event_cb)event_callback, NULL);
	assert_eq(ret, APP_ERROR_INVALID_PARAMETER);

	ret = watch_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, NULL, NULL);
	assert_eq(ret, APP_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_remove_event_handler_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Remove watch app event handler.
 * @scenario            Calls watch_app_add_event_handler function.
 */
int utc_appcore_watch_watch_app_remove_event_handler_p(void)
{
	int ret;
	app_event_handler_h handler;

	ret = watch_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, (app_event_cb)event_callback, NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_app_remove_event_handler(handler);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_remove_event_handler_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Remove watch app event handler.
 * @scenario            Calls watch_app_add_event_handler function.
 */
int utc_appcore_watch_watch_app_remove_event_handler_n(void)
{
	int ret;

	ret = watch_app_remove_event_handler(NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_current_time_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets current time.
 * @scenario            Calls watch_time_get_current_time function.
 */
int utc_appcore_watch_watch_time_get_current_time_p(void)
{
	int ret;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_current_time_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets current time.
 * @scenario            Calls watch_time_get_current_time function.
 */
int utc_appcore_watch_watch_time_get_current_time_n(void)
{
	int ret;

	ret = watch_time_get_current_time(NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_delete_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Delete watch time handle and release its resources.
 * @scenario            Calls watch_time_delete function.
 */
int utc_appcore_watch_watch_time_delete_p(void)
{
	int ret;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_delete(watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}


	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_delete_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Delete watch time handle and release its resources.
 * @scenario            Calls watch_time_delete function.
 */
int utc_appcore_watch_watch_time_delete_n(void)
{
	int ret;

	ret = watch_time_delete(NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_year_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets year information.
 * @scenario            Calls watch_time_get_year function.
 */
int utc_appcore_watch_watch_time_get_year_p(void)
{
	int ret, year;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_year(watch_time, &year);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_year_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets year information.
 * @scenario            Calls watch_time_get_year function.
 */
int utc_appcore_watch_watch_time_get_year_n(void)
{
	int ret, year;

	ret = watch_time_get_year(NULL, &year);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/**
 * @testcase            utc_appcore_watch_watch_time_get_month_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets month information.
 * @scenario            Calls watch_time_get_month function
 */
int utc_appcore_watch_watch_time_get_month_p(void)
{
	int ret, month;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_month(watch_time, &month);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_month_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets month information.
 * @scenario            Calls watch_time_get_month function
 */
int utc_appcore_watch_watch_time_get_month_n(void)
{
	int ret, month;

	ret = watch_time_get_month(NULL, &month);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_day_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets day information.
 * @scenario            Calls watch_time_get_day.
 */
int utc_appcore_watch_watch_time_get_day_p(void)
{
	int ret, day;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_day(watch_time, &day);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_day_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets day information.
 * @scenario            Calls watch_time_get_day.
 */
int utc_appcore_watch_watch_time_get_day_n(void)
{
	int ret, day;

	ret = watch_time_get_day(NULL, &day);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_day_of_week_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets day of week information
 * @scenario            Calls watch_time_get_day_of_week.
 */
int utc_appcore_watch_watch_time_get_day_of_week_p(void)
{
	int ret, day_of_week;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_day_of_week(watch_time, &day_of_week);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_day_of_week_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets day of week information
 * @scenario            Calls watch_time_get_day_of_week.
 */
int utc_appcore_watch_watch_time_get_day_of_week_n(void)
{
	int ret, day_of_week;

	ret = watch_time_get_day_of_week(NULL, &day_of_week);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_hour_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets hour information
 * @scenario            Calls watch_time_get_hour function
 */
int utc_appcore_watch_watch_time_get_hour_p(void)
{
	int ret, hour;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_hour(watch_time, &hour);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_hour_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets hour information
 * @scenario            Calls watch_time_get_hour function
 */
int utc_appcore_watch_watch_time_get_hour_n(void)
{
	int ret, hour;

	ret = watch_time_get_hour(NULL, &hour);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_hour24_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets hour information 24-hour presentation.
 * @scenario            Calls watch_time_get_hour24 function.
 */
int utc_appcore_watch_watch_time_get_hour24_p(void)
{
	int ret, hour24;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_hour24(watch_time, &hour24);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_hour24_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets hour information 24-hour presentation.
 * @scenario            Calls watch_time_get_hour24 function.
 */
int utc_appcore_watch_watch_time_get_hour24_n(void)
{
	int ret, hour24;

	ret = watch_time_get_hour24(NULL, &hour24);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_minute_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets minute information.
 * @scenario            Calls watch_time_get_minute function.
 */
int utc_appcore_watch_watch_time_get_minute_p(void)
{
	int ret, minute;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_minute(watch_time, &minute);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}


	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_minute_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets minute information.
 * @scenario            Calls watch_time_get_minute function.
 */
int utc_appcore_watch_watch_time_get_minute_n(void)
{
	int ret, minute;

	ret = watch_time_get_minute(NULL, &minute);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_second_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets second information.
 * @scenario            Calls watch_time_get_second function.
 */
int utc_appcore_watch_watch_time_get_second_p(void)
{
	int ret, second;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_second(watch_time, &second);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_second_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets second information.
 * @scenario            Calls watch_time_get_second function.
 */
int utc_appcore_watch_watch_time_get_second_n(void)
{
	int ret, second;

	ret = watch_time_get_second(NULL, &second);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_millisecond_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets millisecond information.
 * @scenario            Calls watch_time_get_millisecond function.
 */
int utc_appcore_watch_watch_time_get_millisecond_p(void)
{
	int ret, millisecond;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_millisecond(watch_time, &millisecond);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_millisecond_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets millisecond information.
 * @scenario            Calls watch_time_get_millisecond function.
 */
int utc_appcore_watch_watch_time_get_millisecond_n(void)
{
	int ret, millisecond;

	ret = watch_time_get_millisecond(NULL, &millisecond);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_utc_time_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets utc time information.
 * @scenario            Calls watch_time_get_utc_time function.
 */
int utc_appcore_watch_watch_time_get_utc_time_p(void)
{
	int ret1, ret2;
	struct tm *utc_time = calloc(1, sizeof(struct tm));
	watch_time_h watch_time = {0,};

	ret1 = watch_time_get_current_time(&watch_time);

	ret2 = watch_time_get_utc_time(watch_time, utc_time);

	free(utc_time);

	if (is_supported == false) {
                assert_eq(ret1, APP_ERROR_NOT_SUPPORTED);
		assert_eq(ret2, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret1, APP_ERROR_NONE);
		assert_eq(ret2, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_utc_time_n1
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets utc time information.
 * @scenario            Calls watch_time_get_utc_time function.
 */
int utc_appcore_watch_watch_time_get_utc_time_n1(void)
{
	int ret;
	struct tm *utc_time = calloc(1, sizeof(struct tm));

	ret = watch_time_get_utc_time(NULL, utc_time);

	free(utc_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_utc_time_n2
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets utc time information.
 * @scenario            Calls watch_time_get_utc_time function.
 */
int utc_appcore_watch_watch_time_get_utc_time_n2(void)
{
	int ret;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_utc_time(watch_time, NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_utc_timestamp_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets utc timestamp..
 * @scenario            Calls watch_time_get_utc_timestamp function.
 */
int utc_appcore_watch_watch_time_get_utc_timestamp_p(void)
{
	int ret1, ret2;
	time_t *time_stamp = calloc(1, sizeof(time_t));
	watch_time_h watch_time = {0,};

	ret1 = watch_time_get_current_time(&watch_time);

	ret2 = watch_time_get_utc_timestamp(watch_time, time_stamp);

	free(time_stamp);

	if (is_supported == false) {
                assert_eq(ret1, APP_ERROR_NOT_SUPPORTED);
		assert_eq(ret2, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret1, APP_ERROR_NONE);
		assert_eq(ret2, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_utc_timestamp_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets utc timestamp..
 * @scenario            Calls watch_time_get_utc_timestamp function.
 */
int utc_appcore_watch_watch_time_get_utc_timestamp_n(void)
{
	int ret;
	time_t *time_stamp = calloc(1, sizeof(time_t));

	ret = watch_time_get_utc_timestamp(NULL, time_stamp);

	free(time_stamp);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_time_zone_p
 * @since_tizen         2.3.1
 * @type                Positive
 * @description         Gets time zone.
 * @scenario            Calls watch_time_get_time_zone function.
 */
int utc_appcore_watch_watch_time_get_time_zone_p(void)
{
	int ret;
	char timezone[TIMEZONE_BUFFER_MAX] = {0,};
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_time_zone(watch_time, &timezone);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_time_zone_n1
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets time zone.
 * @scenario            Calls watch_time_get_time_zone function.
 */
int utc_appcore_watch_watch_time_get_time_zone_n1(void)
{
	int ret;
	char timezone[TIMEZONE_BUFFER_MAX] = {0,};

	ret = watch_time_get_time_zone(NULL, &timezone);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_time_zone_n2
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets time zone.
 * @scenario            Calls watch_time_get_time_zone function.
 */
int utc_appcore_watch_watch_time_get_time_zone_n2(void)
{
	int ret;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_time_zone(watch_time, NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_dst_status_p
 * @since_tizen         4.0
 * @type                Positive
 * @description         Gets dst status.
 * @scenario            Calls watch_time_get_dst_status function.
 */
int utc_appcore_watch_watch_time_get_dst_status_p(void)
{
	int ret;
	bool dst;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_dst_status(watch_time, &dst);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_dst_status_n1
 * @since_tizen         4.0
 * @type                Negative
 * @description         Gets dst status.
 * @scenario            Calls watch_time_get_dst_status with invalid parameter
 */
int utc_appcore_watch_watch_time_get_dst_status_n1(void)
{
	int ret;
	bool dst;

	ret = watch_time_get_dst_status(NULL, &dst);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_time_get_dst_status_n2
 * @since_tizen         4.0
 * @type                Negative
 * @description         Gets dst status.
 * @scenario            Calls watch_time_get_dst_status with invalid parameter
 */
int utc_appcore_watch_watch_time_get_dst_status_n2(void)
{
	int ret;
	bool dst;
	watch_time_h watch_time = {0,};

	ret = watch_time_get_current_time(&watch_time);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_time_get_dst_status(watch_time, NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_get_elm_win_n
 * @since_tizen         2.3.1
 * @type                Negative
 * @description         Gets elm win.
 * @scenario            Calls watch_app_get_elm_win function.
 */
int utc_appcore_watch_watch_app_get_elm_win_n(void)
{
	int ret;

	ret = watch_app_get_elm_win(NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_set_ambient_tick_type_p
 * @since_tizen         2.3.2
 * @type                Positive
 * @description         Sets ambient tick type.
 * @scenario            Calls watch_app_set_ambient_tick_type function.
 */
int utc_appcore_watch_watch_app_set_ambient_tick_type_p(void)
{
	int ret;
	watch_app_ambient_tick_type_e type;

	ret = watch_app_set_ambient_tick_type(WATCH_APP_AMBIENT_TICK_EVERY_FIVE_MINUTES);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_app_get_ambient_tick_type(&type);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
		assert_eq(type, WATCH_APP_AMBIENT_TICK_EVERY_FIVE_MINUTES);
	}

	watch_app_set_ambient_tick_type(WATCH_APP_AMBIENT_TICK_EVERY_MINUTE);
	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_set_ambient_tick_type_n
 * @since_tizen         2.3.2
 * @type                Negative
 * @description         Sets ambient tick type.
 * @scenario            Calls watch_app_set_ambient_tick_type function.
 */
int utc_appcore_watch_watch_app_set_ambient_tick_type_n(void)
{
	int ret;

	ret = watch_app_set_ambient_tick_type(-1);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_get_ambient_tick_type_p
 * @since_tizen         2.3.2
 * @type                Positive
 * @description         Gets ambient tick type.
 * @scenario            Calls watch_app_get_ambient_tick_type function.
 */
int utc_appcore_watch_watch_app_get_ambient_tick_type_p(void)
{
	int ret;
	watch_app_ambient_tick_type_e type;

	ret = watch_app_set_ambient_tick_type(WATCH_APP_AMBIENT_TICK_EVERY_DAY);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_app_get_ambient_tick_type(&type);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
		assert_eq(type, WATCH_APP_AMBIENT_TICK_EVERY_DAY);
	}

	watch_app_set_ambient_tick_type(WATCH_APP_AMBIENT_TICK_EVERY_MINUTE);
	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_get_ambient_tick_type_n
 * @since_tizen         2.3.2
 * @type                Negative
 * @description         Gets ambient tick type.
 * @scenario            Calls watch_app_get_ambient_tick_type function.
 */
int utc_appcore_watch_watch_app_get_ambient_tick_type_n(void)
{
	int ret;

	ret = watch_app_get_ambient_tick_type(NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_set_time_tick_frequency_p
 * @since_tizen         3.0
 * @type                Positive
 * @description         Sets time tick type.
 * @scenario            Calls watch_app_set_time_tick_frequency function.
 */
int utc_appcore_watch_watch_app_set_time_tick_frequency_p(void)
{
	int ret;
	watch_app_time_tick_resolution_e type = WATCH_APP_TIME_TICKS_PER_SECOND;

	ret = watch_app_set_time_tick_frequency(1, type);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	return 0;
}


/**
 * @testcase            utc_appcore_watch_watch_app_set_time_tick_frequency_n
 * @since_tizen         3.0
 * @type                Negative
 * @description         Sets time tick type.
 * @scenario            Calls watch_app_set_time_tick_frequency function with invalid parameter.
 */
int utc_appcore_watch_watch_app_set_time_tick_frequency_n(void)
{
	int ret;

	ret = watch_app_set_time_tick_frequency(1, -1);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/**
 * @testcase            utc_appcore_watch_watch_app_get_time_tick_frequency_p
 * @since_tizen         3.0
 * @type                Positive
 * @description         Gets time tick type.
 * @scenario            Calls watch_app_get_time_tick_frequency function.
 */
int utc_appcore_watch_watch_app_get_time_tick_frequency_p(void)
{
	int ret;
	watch_app_time_tick_resolution_e type = WATCH_APP_TIME_TICKS_PER_MINUTE;
	watch_app_time_tick_resolution_e get_type;
	int tick;

	ret = watch_app_set_time_tick_frequency(60, type);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
	}

	ret = watch_app_get_time_tick_frequency(&tick, &get_type);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_NONE);
		assert_eq(tick, 60);
		assert_eq(get_type, WATCH_APP_TIME_TICKS_PER_MINUTE);
	}

	return 0;
}

/**
 * @testcase            utc_appcore_watch_watch_app_get_time_tick_frequency_n
 * @since_tizen         3.0
 * @type                Negative
 * @description         Gets time tick type.
 * @scenario            Calls watch_app_get_time_tick_frequency function with invalid parameter.
 */
int utc_appcore_watch_watch_app_get_time_tick_frequency_n(void)
{
	int ret;

	ret = watch_app_get_time_tick_frequency(NULL, NULL);

	if (is_supported == false) {
                assert_eq(ret, APP_ERROR_NOT_SUPPORTED);
        } else {
		assert_eq(ret, APP_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
