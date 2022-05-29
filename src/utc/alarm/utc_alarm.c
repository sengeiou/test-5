//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#include <time.h>
#include <glib-object.h>
#include <string.h>
#include <app_alarm.h>
#include <app.h>
#include <glib.h>
#include <system_info.h>
#include <dlog.h>

#include "assert.h"
#include "assert_common.h"
#include "tct_app_common.h"
#include "tct_common.h"

#define API_NAMESPACE			"CAPI-APPFW-ALARM-UTC"
#define TIZEN_FEATURE_SCREEN	"http://tizen.org/feature/screen"

static guint timeout_id = 0;
static int tid;
static char *package = NULL;

/**
 * @function		utc_alarm_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_alarm_startup(void)
{

#if !(GLIB_CHECK_VERSION(2, 36, 0))
	g_type_init();
#endif
	package = NULL;

	TCT_UTCCheckInstalledApp(4, "org.tizen.testservice",
			"org.tizen.service-with-bg-category",
			"org.tizen.helloworld",
			"org.tizen.globalapp");
}

/**
 * @function		utc_alarm_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_alarm_cleanup(void)
{
	if (package != NULL) {
		free(package);
	}
}

static gboolean timeout(gpointer data)
{
	app_control_h app_control = (app_control_h)data;

	alarm_cancel_all();
	normal_exit(1);

	return FALSE;
}

static bool foreach_alarm_cb(int alarm, void *user_data)
{
	if (timeout_id > 0) {
		g_source_remove(timeout_id);
		timeout_id = 0;
	}

	alarm_cancel_all();
	normal_exit(0);

	return true;
}

static gboolean __alarm_check(gpointer data)
{
	app_control_h app_control = (app_control_h)data;
	int ret;
	bool is_running = false;
	const char *app_id = "org.tizen.helloworld";

	ret = app_manager_is_running(app_id, &is_running);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);

	if (is_running) {
		ret = app_control_add_extra_data(app_control, "ALARM_UTC", "TERM");
		assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

		ret = app_control_send_launch_request(app_control, NULL, NULL);
		assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

		normal_exit(0);
	} else {
		normal_exit(1);
	}

	app_control_destroy(app_control);
	alarm_cancel_all();
	return true;
}

/**
 * @testcase		utc_alarm_schedule_after_delay_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_after_delay() and then checks the return value.
 *			Removes the registerted alarms.
 */
int utc_alarm_schedule_after_delay_p(void)
{
	app_control_h app_control;
	int tid;
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &tid);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_after_delay_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_after_delay() with the NULL parameter
 *			and then checks the return value.
 */
int utc_alarm_schedule_after_delay_n1(void)
{
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.helloworld";
	int delay = 1;
	int period = 1;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, NULL);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_after_delay_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_after_delay() with the app_control
 *			that is not permitted and then checks the return value.
 */
int utc_alarm_schedule_after_delay_n2(void)
{
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.testservice";
	int delay = 1;
	int period = 1;
	int tid;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &tid);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NOT_PERMITTED_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_after_delay_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_after_delay() with the app_control
 *			that is not permitted and then checks the return value.
 */
int utc_alarm_schedule_after_delay_n3(void)
{
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	int tid;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_VIEW);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &tid);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NOT_PERMITTED_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_after_delay_n4
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_after_delay() with the NULL parameter
 *			and then checks the return value.
 */
int utc_alarm_schedule_after_delay_n4(void)
{
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	int tid;

	ret = alarm_schedule_after_delay(NULL, delay, period, &tid);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}


/**
 * @testcase		utc_alarm_schedule_at_date_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets an alarm to be triggered at a specific time.
 * @scenario		Calls the alarm_schedule_at_date().
 *			Removes the registered alarms and then checks the return value.
 */
int utc_alarm_schedule_at_date_p(void)
{
	app_control_h app_control;
	int tid;
	int ret = ALARM_ERROR_NONE;
	struct tm date;
	time_t now;
	const char *app_id = "org.tizen.helloworld";

	time(&now);
	now += 30;
	tzset();
	localtime_r(&now, &date);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_at_date(app_control, &date, 0, &tid);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_at_date_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered at a specific time.
 * @scenario		Calls the alarm_schedule_at_date() with the invalid parameter
 *			that alarm_id is NULL and then checks the return value.
 */
int utc_alarm_schedule_at_date_n(void)
{
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.helloworld";
	struct tm date;
	time_t now;

	time(&now);
	now += 30;
	tzset();
	localtime_r(&now, &date);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_at_date(app_control, &date, 0, NULL);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_once_after_delay_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_once_after_delay().
 *			Removes the registered alarms and then checks the return value.
 */
int utc_alarm_schedule_once_after_delay_p(void)
{
	app_control_h app_control;
	int tid;
	int ret = ALARM_ERROR_NONE;
	int delay = 5;
	const char *app_id = "org.tizen.helloworld";
	bool is_screen = false;

	/* For IOT headless */
	system_info_get_platform_bool(TIZEN_FEATURE_SCREEN, &is_screen);
	dlog_print(DLOG_INFO, "NativeTCT", "%d", is_screen);
	if (!is_screen) {
		normal_exit(0);
		return 0;
	}

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_after_delay(app_control, delay, &tid);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	g_timeout_add_seconds(10, __alarm_check, app_control);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_once_after_delay_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_once_after_delay() with the invalid parameter
 *			that alarm_id is NULL and then checks the return value.
 */
int utc_alarm_schedule_once_after_delay_n1(void)
{
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.helloworld";
	int delay = 1;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_after_delay(app_control, delay, NULL);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_once_after_delay_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_once_after_delay() with the invalid parameter
 *			that app_control is not permitted and then checks the return value.
 */
int utc_alarm_schedule_once_after_delay_n2(void)
{
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.testservice";
	int delay = 1;
	int tid;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_after_delay(app_control, delay, &tid);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NOT_PERMITTED_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_once_after_delay_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_once_after_delay() with the invalid parameter
 *			that alarm_id is NULL and then checks the return value.
 */
int utc_alarm_schedule_once_after_delay_n3(void)
{
	int ret = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.testservice";
	int delay = 1;
	int tid;

	ret = alarm_schedule_once_after_delay(NULL, delay, &tid);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_cancel_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Cancels the alarm with the specific alarm ID.
 * @scenario		Sets an alarm and cancels the alarm.
 *			Calls the alarm_cancel() with the specific alarm ID.
 */
int utc_alarm_cancel_p(void)
{
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	int ret1 = ALARM_ERROR_NONE;
	int ret2 = ALARM_ERROR_NONE;
	int tid;
	int delay = 1;
	int period = 5;
	bool is_running = false;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret1 = alarm_schedule_after_delay(app_control, delay, period, &tid);
	ret2 = alarm_cancel(tid);

	sleep(10);

	ret = app_manager_is_running(app_id, &is_running);
	assert_eq_with_exit(ret, APP_MANAGER_ERROR_NONE);
	assert_eq_with_exit(is_running, false);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret1, ALARM_ERROR_NONE);
	assert_eq_with_exit(ret2, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_cancel_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Cancels the alarm with the specific alarm ID.
 * @scenario		Calls the alarm_cancel() with the invalid parameter
 *			and then checks the return value.
 */
int utc_alarm_cancel_n(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_cancel(0);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_cancel_all_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Cancels all schedule alarms that are registered
 *			by the application that calls this API.
 * @scenario		Calls the alarm_cancel_all() and then checks the return value.
 */
int utc_alarm_cancel_all_p(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}


/**
 * @testcase		utc_alarm_foreach_registered_alarm_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Retrieves the IDs of all registered alarms
 *			by invoking a callback once for each scheduled alarm.
 * @scenario		Calls the alarm_foreach_registered_alarm() with the foreach callback.
 *			The foreach callback will call the ui_app_exit().
 */
int utc_alarm_foreach_registered_alarm_p(void)
{
	int ret = ALARM_ERROR_NONE;
	app_control_h app_control;
	int delay = 1;
	int period = 5;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	alarm_schedule_after_delay(app_control, delay, period, &tid);
	app_control_destroy(app_control);

	ret = alarm_foreach_registered_alarm(foreach_alarm_cb, NULL);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	timeout_id = g_timeout_add(5000, timeout, NULL);

	return 0;
}


/**
 * @testcase		utc_alarm_foreach_registered_alarm_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Retrieves the IDs of all registered alarms
 *			by invoking a callback once for each scheduled alarm.
 * @scenario		Calls the alarm_foreach_registered_alarm() with the invalid parameter
 *			that the callback is NULL and then checks the return value.
 */
int utc_alarm_foreach_registered_alarm_n(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_foreach_registered_alarm(NULL, NULL);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}


/**
 * @testcase		utc_alarm_get_scheduled_date_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the scheduled time from the given alarm ID in C standard time struct.
 * @scenario		Sets an alarm and gets the schedule.
 *			Calls the alarm_schedule_after_delay() and calls
 *			the alarm_get_scheduled_date() and then checks the return value.
 */
int utc_alarm_get_scheduled_date_p(void)
{
	struct tm date;
	struct tm get_date;
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	int tid;
	time_t now;
	const char *app_id = "org.tizen.helloworld";

	time(&now);
	now += 20;
	tzset();
	localtime_r(&now, &date);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_at_date(app_control, &date, &tid);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_get_scheduled_date(tid, &get_date);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	assert_eq_with_exit(date.tm_sec, get_date.tm_sec);

	app_control_destroy(app_control);
	alarm_cancel_all();

	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_scheduled_date_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the scheduled time from the given alarm ID in C standard time struct.
 * @scenario		Calls the alarm_get_scheduled_date() with the invalid parameter
 *			that alarm_id is -1 and then checks the return value.
 * */
int utc_alarm_get_scheduled_date_n(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_get_scheduled_date(-1, NULL);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}


/**
 * @testcase		utc_alarm_get_scheduled_period_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the period of time between the recurrent alarms.
 * @scenario		Sets an alarm and gets the period.
 *			Calls the alarm_schedule_after_delay() and calls the
 *			alarm_get_schedule_period() and then checks the return value.
 */
int utc_alarm_get_scheduled_period_p(void)
{
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	int period1 = 1;
	int period2 = 0;
	int delay = 1;
	int tid;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	alarm_schedule_after_delay(app_control, delay, period1, &tid);

	ret = alarm_get_scheduled_period(tid, &period2);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	assert_with_exit(period2 >= 600);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_scheduled_period_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the period of time between the recurrent alarms.
 * @scenario		Calls the alarm_get_schedule_period() with the invalid parameter
 *			that alarm_id is 0 and then checks the return value.
 */
int utc_alarm_get_scheduled_period_n1(void)
{
	int ret = ALARM_ERROR_NONE;
	int period = 0;

	ret = alarm_get_scheduled_period(0, &period);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_scheduled_period_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the period of time between the recurrent alarms.
 * @scenario		Calls the alarm_get_schedule_period() with the invalid parameter
 *			that alarm_id is 0 and then checks the return value.
 */
int utc_alarm_get_scheduled_period_n2(void)
{
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	int period1 = 1;
	int period2 = 0;
	int delay = 1;
	int tid;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	alarm_schedule_after_delay(app_control, delay, period1, &tid);

	ret = alarm_get_scheduled_period(tid, NULL);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}


/**
 * @testcase		utc_alarm_schedule_once_at_date_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets an alarm to be triggered at a specific time.
 * @scenario		Sets an alarm.
 *			Calls the alarm_schedule_once_at_date() and then
 *			checks the return value.
 */
int utc_alarm_schedule_once_at_date_p(void)
{
	struct tm date;
	time_t now;
	app_control_h app_control;
	int tid;
	const char *app_id = "org.tizen.helloworld";
	int ret = ALARM_ERROR_NONE;
	bool is_screen = true;

	/* For IOT headless */
	system_info_get_platform_bool(TIZEN_FEATURE_SCREEN, &is_screen);
	if (!is_screen) {
		normal_exit(0);
		return 0;
	}

	time(&now);
	now += 5;
	tzset();
	localtime_r(&now, &date);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_at_date(app_control, &date, &tid);

	g_timeout_add_seconds(10, __alarm_check, app_control);

	return 0;
}


/**
 * @testcase		utc_alarm_schedule_once_at_date_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered at a specific time.
 * @scenario		Calls the alarm_schedule_once_at_date() with the invalid parameter
 *			and then checks the return value.
 */
int utc_alarm_schedule_once_at_date_n1(void)
{
	struct tm date;
	time_t now;
	int ret = ALARM_ERROR_NONE;
	app_control_h app_control;
	const char *app_id = "org.tizen.helloworld";

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_mon = 1;
	date.tm_mday = 30;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_at_date(app_control, &date, &tid);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_DATE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_once_at_date_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered at a specific time.
 * @scenario		Calls the alarm_schedule_once_at_date() with the invalid parameter
 *			that date is NULL and then checks the return value.
 */
int utc_alarm_schedule_once_at_date_n2(void)
{
	int ret = ALARM_ERROR_NONE;
	app_control_h app_control;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_at_date(app_control, NULL, &tid);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_once_at_date_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered at a specific time.
 * @scenario		Calls the alarm_schedule_once_at_date() with the invalid parameter
 *			that date is invalid and then checks the return value.
 */
int utc_alarm_schedule_once_at_date_n3(void)
{
	app_control_h app_control;
	int ret = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.testservice";
	int tid;

	struct tm date;
	time_t now;

	time(&now);
	now += 20;
	tzset();
	localtime_r(&now, &date);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_at_date(app_control, &date, &tid);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NOT_PERMITTED_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_with_recurrence_week_flag_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Sets an alarm to be triggered periodically, starting at a specific time.
 * @scenario		Sets an alarm with ALARM_WEEK_FLAG_MONDAY flag.
 *			Calls the alarm_schedule_with_recurrence_week_flag()
 *			with ALARM_WEEK_FLAG_MONDAY flag and then checks the return value.
 */
int utc_alarm_schedule_with_recurrence_week_flag_p(void)
{
	struct tm date;
	time_t now;
	app_control_h app_control;
	int tid;
	const char *app_id = "org.tizen.helloworld";
	int ret = ALARM_ERROR_NONE;
	bool is_screen = true;

	/* For IOT headless */
	system_info_get_platform_bool(TIZEN_FEATURE_SCREEN, &is_screen);
	if (!is_screen) {
		normal_exit(0);
		return 0;
	}

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_sec += 5;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_with_recurrence_week_flag(app_control, &date,
			ALARM_WEEK_FLAG_MONDAY | ALARM_WEEK_FLAG_TUESDAY |
			ALARM_WEEK_FLAG_WEDNESDAY | ALARM_WEEK_FLAG_THURSDAY |
			ALARM_WEEK_FLAG_FRIDAY | ALARM_WEEK_FLAG_SATURDAY |
			ALARM_WEEK_FLAG_SUNDAY, &tid);

	g_timeout_add_seconds(10, __alarm_check, app_control);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_with_recurrence_week_flag_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered periodically, starting at a specific time.
 * @scenario		Calls the alarm_schdule_with_recurrence_week_flag() with the invalid parameter
 *			that app_control is NULL and then checks the return value.
 */
int utc_alarm_schedule_with_recurrence_week_flag_n1(void)
{
	struct tm date;
	time_t now;
	int tid;

	int ret = ALARM_ERROR_NONE;

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_sec += 3;

	ret = alarm_schedule_with_recurrence_week_flag(NULL, &date, ALARM_WEEK_FLAG_MONDAY, &tid);

	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_with_recurrence_week_flag_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered periodically, starting at a specific time.
 * @scenario		Calls the alarm_schedule_with_recurrence_week_flag() with the invalid parameter
 *			that date is invalid and then checks the return value.
 */
int utc_alarm_schedule_with_recurrence_week_flag_n2(void)
{
	struct tm date;
	time_t now;
	app_control_h app_control;
	int tid;
	const char *app_id = "org.tizen.helloworld";

	int ret = ALARM_ERROR_NONE;

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_mon = 1;
	date.tm_mday = 30;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_with_recurrence_week_flag(app_control, &date, ALARM_WEEK_FLAG_MONDAY, &tid);

	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_DATE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_with_recurrence_week_flag_n3
 * @since_tizen		2.3
 * @type		Negative
 * @description		Sets an alarm to be triggered periodically, starting at a specific time.
 * @scenario		Calls the alarm_schedule_with_recurrence_week_flag() with the invalid parameter
 *			that app_control is not permitted and then checks the return value.
 */
int utc_alarm_schedule_with_recurrence_week_flag_n3(void)
{
	struct tm date;
	time_t now;
	app_control_h app_control;
	int tid;
	const char *app_id = "org.tizen.testservice";

	int ret = ALARM_ERROR_NONE;

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_sec += 3;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_with_recurrence_week_flag(app_control, &date, ALARM_WEEK_FLAG_MONDAY, &tid);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NOT_PERMITTED_APP);
	normal_exit(0);

	return 0;
}
/**
 * @testcase		utc_alarm_get_scheduled_recurrence_week_flag_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the recurrence days of the week.
 * @scenario		Sets an alarm with ALARM_WEEK_FLAG_MONDAY flag and gets the
 *			recurrence week flag.
 *			Calls the alarm_schedule_with_recurrence_week_flag() and calls
 *			the alarm_get_scheduled_recurrence_week_flag(), and then
 *			checks the return value.
 */
int utc_alarm_get_scheduled_recurrence_week_flag_p(void)
{
	struct tm date;
	time_t now;
	app_control_h app_control;
	int tid;
	int week_flag = 0;
	const char *app_id = "org.tizen.helloworld";
	int ret = ALARM_ERROR_NONE;

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_sec += 3;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_with_recurrence_week_flag(app_control, &date, ALARM_WEEK_FLAG_MONDAY, &tid);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	ret = alarm_get_scheduled_recurrence_week_flag(tid, &week_flag);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	ret = app_control_destroy(app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_cancel_all();
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	assert_eq_with_exit(week_flag, ALARM_WEEK_FLAG_MONDAY);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_scheduled_recurrence_week_flag_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the recurrence days of the week.
 * @scenario		Calls the alarm_get_scheduled_week_flag() with the invalid parameters
 *			that alarm_id is 0 and week_flag is NULL, and then checks the return value.
 */
int utc_alarm_get_scheduled_recurrence_week_flag_n(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_get_scheduled_recurrence_week_flag(0, NULL);

	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_current_time_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the current system time using C standard time struct.
 * @scenario		Gets the current system time.
 *			Calls the alarm_get_current_time() and then checks the return value.
 */
int utc_alarm_get_current_time_p(void)
{
	struct tm date;
	int ret = ALARM_ERROR_NONE;
	time_t now;
	time_t result;

	ret = alarm_get_current_time(&date);

	time(&now);
	result = mktime(&date);

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	assert_eq_with_exit((int)(now - result), 0);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_current_time_n
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the current system time using C standard time struct.
 * @scenario		Calls the alarm_get_current_time() with the invalid parameter
 *			that date is NULL, and then checks the return value.
 */
int utc_alarm_get_current_time_n(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_get_current_time(NULL);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_app_control_p
 * @since_tizen		2.3
 * @type		Positive
 * @description		Gets the app_control to be invoked when the the alarm is triggered.
 * @scenario		Sets an alarm and gets the app_control by alarm_id.
 *			Calls the alarm_schedule_after_delay() and Calls the alarm_get_app_control(),
 *			and then checks the return value.
 */
int utc_alarm_get_app_control_p(void)
{
	app_control_h app_control;
	app_control_h app_control_return;

	int ret = ALARM_ERROR_NONE;
	int ret1 = ALARM_ERROR_NONE;
	int ret2 = APP_CONTROL_ERROR_NONE;
	int tid;
	int period = 0;
	int delay = 3;
	char *package;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &tid);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	ret1 = alarm_get_app_control(tid, &app_control_return);
	ret2 = app_control_get_app_id(app_control_return, &package);

	app_control_destroy(app_control);
	app_control_destroy(app_control_return);
	alarm_cancel_all();

	assert_eq_with_exit(ret1, ALARM_ERROR_NONE);
	assert_eq_with_exit(ret2, APP_CONTROL_ERROR_NONE);
	assert_with_exit(!strcmp(package, app_id));

	free(package);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_app_control_n1
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the app_control to be invoked when the the alarm is triggered.
 * @scenario		Calls the alarm_get_app_control() with the invalid parameter
 *			that app_control is NULL, and then checks the return value.
 */
int utc_alarm_get_app_control_n1(void)
{
	app_control_h app_control;

	int ret = ALARM_ERROR_NONE;
	int tid;
	int period = 0;
	int delay = 3;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &tid);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	ret = alarm_get_app_control(tid, NULL);
	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);

	ret = app_control_destroy(app_control);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	alarm_cancel_all();
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_app_control_n2
 * @since_tizen		2.3
 * @type		Negative
 * @description		Gets the app_control to be invoked when the the alarm is triggered.
 * @scenario		Calls the alarm_get_app_control() with the invalid paramters
 *			that alarm_id is 0 and app_control is NULL, and then checks return value.
 */
int utc_alarm_get_app_control_n2(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_get_app_control(0, NULL);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_set_global_p
 * @since_tizen		3.0
 * @type		Positive
 * @description	Set global flag to set/unset alarm globally
 * @scenario		Sets an alarm and gets global flag
 *				Calls the alarm_schedule_after_delay() and calls
 *				the alarm_set_global() and then checks the return value.
 */
int utc_alarm_set_global_p(void)
{
	app_control_h app_control;
	int tid;
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	const char *app_id = "org.tizen.globalapp";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &tid);

	if (ret == ALARM_ERROR_NONE) {
		ret = alarm_set_global(tid, true);
	}

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_set_global_n1
 * @since_tizen		3.0
 * @type		Negative
 * @description	Set global flag to set/unset alarm globally
 * @scenario		Sets an alarm and gets global flag
 *				Calls the alarm_schedule_after_delay() with non global application
 *				and calls the alarm_set_global() and then checks the return value.
 */
int utc_alarm_set_global_n1(void)
{
	app_control_h app_control;
	int tid;
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	const char *app_id = "org.tizen.helloworld";
	char pszValue1[CONFIG_VALUE_LEN_MAX] = {0,};
	char pszValue2[CONFIG_VALUE_LEN_MAX] = {0,};

	/*
	 * If capi-appfw-alarm utc runs with admin user,
	 * all application is installed as globalapp and this testcase is meaningless.
	 */
	GetValueForTCTSetting("DEVICE_EXECUTION_MODE_30", pszValue1,
			API_NAMESPACE);
	GetValueForTCTSetting("DEVICE_ADMIN_USER_30", pszValue2,
			API_NAMESPACE);
	if (pszValue1 && pszValue2 && !strcmp(pszValue1, pszValue2)) {
		normal_exit(0);
		return 0;
	}

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &tid);

	if (ret == ALARM_ERROR_NONE) {
		ret = alarm_set_global(tid, true);
	}

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NOT_PERMITTED_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_set_global_n2
 * @since_tizen		3.0
 * @type		Negative
 * @description	Set global flag to set/unset alarm globally
 * @scenario		Calls the alarm_set_global() with invalid parameter.
 */
int utc_alarm_set_global_n2(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_set_global(0, true);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_global_p
 * @since_tizen		3.0
 * @type		Positive
 * @description	Get the alarm will launch global appliation or not
 * @scenario		Sets an alarm and gets global flag
 *				Calls the alarm_schedule_after_delay() and calls
 *				the alarm_get_global() and then checks the return value.
 */
int utc_alarm_get_global_p(void)
{
	app_control_h app_control;
	int tid;
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	bool global;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &tid);

	if (ret == ALARM_ERROR_NONE)
		ret = alarm_get_global(tid, &global);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	assert_eq_with_exit(global, false);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_global_n
 * @since_tizen		3.0
 * @type		Negative
 * @description	Get the alarm will launch global appliation or not
 * @scenario		Calls the alarm_get_global() with invalid parameter.
 */
int utc_alarm_get_global_n(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_get_global(0, NULL);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

static gboolean _noti_check(gpointer data)
{
	notification_h noti;

	noti = notification_load_by_tag("alarm-utc");
	alarm_cancel_all();
	assert_neq_with_exit(noti, NULL);

	notification_delete(noti);
	notification_free(noti);
	normal_exit(0);

	return FALSE;
}

/**
 * @testcase		utc_alarm_schedule_noti_once_at_date_p
 * @since_tizen	3.0
 * @type			Positive
 * @description	Sets an alarm to be triggered at a specific time.
 * @scenario		Sets an notification alarm.
 *				Calls the alarm_schedule_noti_once_at_date() and then
 *				checks the return value.
 */
int utc_alarm_schedule_noti_once_at_date_p(void)
{
	struct tm date;
	time_t now;
	notification_h noti;
	int tid;

	int ret = ALARM_ERROR_NONE;

	time(&now);
	now += 5;
	tzset();
	localtime_r(&now, &date);

	noti = notification_create(NOTIFICATION_TYPE_NOTI);

	ret = notification_set_text(noti, NOTIFICATION_TEXT_TYPE_TITLE,
			"test", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_set_display_applist(noti,
			NOTIFICATION_DISPLAY_APP_INDICATOR |
			NOTIFICATION_DISPLAY_APP_NOTIFICATION_TRAY |
			NOTIFICATION_DISPLAY_APP_TICKER);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_set_tag(noti, "alarm-utc");
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = alarm_schedule_noti_once_at_date(noti, &date, &tid);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	notification_free(noti);

	g_timeout_add_seconds(10, _noti_check, &noti);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_once_at_date_n1
 * @since_tizen	3.0
 * @type			Negative
 * @description	Sets an alarm to be triggered at a specific time.
 * @scenario		Sets an notification alarm.
 *				Calls the alarm_schedule_noti_once_at_date() with invalid parameter
 *				and then checks the return value.
 */
int utc_alarm_schedule_noti_once_at_date_n1(void)
{
	struct tm date;
	time_t now;
	notification_h noti;

	int ret = ALARM_ERROR_NONE;

	time(&now);
	now += 20;
	tzset();
	localtime_r(&now, &date);

	noti = notification_create(NOTIFICATION_TYPE_NOTI);

	ret = notification_set_text(noti, NOTIFICATION_TEXT_TYPE_TITLE,
			"test", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = alarm_schedule_noti_once_at_date(noti, &date, NULL);

	notification_free(noti);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_once_at_date_n2
 * @since_tizen	3.0
 * @type			Negative
 * @description	Sets an alarm to be triggered at a specific time.
 * @scenario		Sets an notification alarm.
 *				Calls the alarm_schedule_noti_once_at_date() with invalid parameter
 *				and then checks the return value.
 */
int utc_alarm_schedule_noti_once_at_date_n2(void)
{
	int tid;
	struct tm date;
	time_t now;

	int ret = ALARM_ERROR_NONE;

	time(&now);
	now += 20;
	tzset();
	localtime_r(&now, &date);

	ret = alarm_schedule_noti_once_at_date(NULL, &date, &tid);

	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_after_delay_p
 * @since_tizen	3.0
 * @type			Positive
 * @description	Sets an notification alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_noti_after_delay() and then checks the return value.
 *				Removes the registerted alarms.
 */
int utc_alarm_schedule_noti_after_delay_p(void)
{
	int tid;
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	notification_h noti;

	noti = notification_create(NOTIFICATION_TYPE_NOTI);

	ret = notification_set_text(noti, NOTIFICATION_TEXT_TYPE_TITLE,
			"test", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = alarm_schedule_noti_after_delay(noti, delay, period, &tid);

	notification_free(noti);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_after_delay_n1
 * @since_tizen	3.0
 * @type			Negative
 * @description	Sets an notification alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_noti_after_delay() with invalid parameter
 *				and then checks the return value.
 */
int utc_alarm_schedule_noti_after_delay_n1(void)
{
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	notification_h noti;

	noti = notification_create(NOTIFICATION_TYPE_NOTI);

	ret = notification_set_text(noti, NOTIFICATION_TEXT_TYPE_TITLE,
			"test", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = alarm_schedule_noti_after_delay(noti, delay, period, NULL);

	notification_free(noti);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_after_delay_n2
 * @since_tizen	3.0
 * @type			Negative
 * @description	Sets an notification alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_noti_after_delay() with invalid parameter
 *				and then checks the return value.
 */
int utc_alarm_schedule_noti_after_delay_n2(void)
{
	int tid;
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;

	ret = alarm_schedule_noti_after_delay(NULL, delay, period, &tid);

	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_once_after_delay_p
 * @since_tizen	3.0
 * @type			Positive
 * @description	Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_noti_once_after_delay().
 *				Removes the registered notification alarm and then checks the return value.
 */
int utc_alarm_schedule_noti_once_after_delay_p(void)
{
	int tid;
	int ret = ALARM_ERROR_NONE;
	int delay = 5;
	notification_h noti;

	noti = notification_create(NOTIFICATION_TYPE_NOTI);

	ret = notification_set_text(noti, NOTIFICATION_TEXT_TYPE_TITLE,
			"test", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_set_display_applist(noti,
			NOTIFICATION_DISPLAY_APP_INDICATOR |
			NOTIFICATION_DISPLAY_APP_NOTIFICATION_TRAY |
			NOTIFICATION_DISPLAY_APP_TICKER);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_set_tag(noti, "alarm-utc");
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = alarm_schedule_noti_once_after_delay(noti, delay, &tid);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	notification_free(noti);

	g_timeout_add_seconds(10, _noti_check, &noti);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_once_after_delay_n1
 * @since_tizen	3.0
 * @type			Negative
 * @description	Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_noti_once_after_delay() with invalid parameter
 *				and then checks the return value.
 */
int utc_alarm_schedule_noti_once_after_delay_n1(void)
{
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	notification_h noti;

	noti = notification_create(NOTIFICATION_TYPE_NOTI);

	ret = notification_set_text(noti, NOTIFICATION_TEXT_TYPE_TITLE,
			"test", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = alarm_schedule_noti_once_after_delay(noti, delay, NULL);

	notification_free(noti);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_once_after_delay_n2
 * @since_tizen	3.0
 * @type			Negative
 * @description	Sets an alarm to be triggered after a specific time.
 * @scenario		Calls the alarm_schedule_noti_once_after_delay() with invalid parameter
 *				and then checks the return value.
 */
int utc_alarm_schedule_noti_once_after_delay_n2(void)
{
	int tid;
	int ret = ALARM_ERROR_NONE;
	int delay = 1;

	ret = alarm_schedule_noti_once_after_delay(NULL, delay, &tid);

	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_with_recurrence_week_flag_p
 * @since_tizen	3.0
 * @type			Positive
 * @description	Sets a notification alarm to be triggered periodically, starting at a specific time.
 * @scenario		Sets alarm with ALARM_WEEK_FLAG_MONDAY flag.
 *				Calls the alarm_schedule_noti_with_recurrence_week_flag()
 *				with ALARM_WEEK_FLAG_MONDAY flag and then checks the return value.
 */
int utc_alarm_schedule_noti_with_recurrence_week_flag_p(void)
{
	struct tm date;
	time_t now;
	int tid;
	int ret = ALARM_ERROR_NONE;
	notification_h noti;

	time(&now);
	now += 5;
	tzset();
	localtime_r(&now, &date);

	noti = notification_create(NOTIFICATION_TYPE_NOTI);

	ret = notification_set_text(noti, NOTIFICATION_TEXT_TYPE_TITLE,
			"test", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_set_display_applist(noti,
			NOTIFICATION_DISPLAY_APP_INDICATOR |
			NOTIFICATION_DISPLAY_APP_NOTIFICATION_TRAY |
			NOTIFICATION_DISPLAY_APP_TICKER);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = notification_set_tag(noti, "alarm-utc");
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = alarm_schedule_noti_with_recurrence_week_flag(noti, &date,
			ALARM_WEEK_FLAG_SUNDAY |
			ALARM_WEEK_FLAG_MONDAY |
			ALARM_WEEK_FLAG_TUESDAY |
			ALARM_WEEK_FLAG_WEDNESDAY |
			ALARM_WEEK_FLAG_THURSDAY |
			ALARM_WEEK_FLAG_FRIDAY |
			ALARM_WEEK_FLAG_SATURDAY
			, &tid);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	notification_free(noti);

	g_timeout_add_seconds(10, _noti_check, &noti);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_with_recurrence_week_flag_n1
 * @since_tizen	3.0
 * @type			Negative
 * @description	Sets a notification alarm to be triggered periodically, starting at a specific time.
 * @scenario		Calls the alarm_schedule_with_recurrence_week_flag() with the invalid parameter
 *				and then checks the return value.
 */
int utc_alarm_schedule_noti_with_recurrence_week_flag_n1(void)
{
	struct tm date;
	time_t now;
	int ret = ALARM_ERROR_NONE;
	notification_h noti;

	noti = notification_create(NOTIFICATION_TYPE_NOTI);

	ret = notification_set_text(noti, NOTIFICATION_TEXT_TYPE_TITLE,
			"test", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_sec += 3;

	ret = alarm_schedule_noti_with_recurrence_week_flag(noti, &date, ALARM_WEEK_FLAG_MONDAY, NULL);

	notification_free(noti);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_schedule_noti_with_recurrence_week_flag_n2
 * @since_tizen	3.0
 * @type			Negative
 * @description	Sets a notification alarm to be triggered periodically, starting at a specific time.
 * @scenario		Calls the alarm_schedule_with_recurrence_week_flag() with the invalid parameter
 *				and then checks the return value.
 */
int utc_alarm_schedule_noti_with_recurrence_week_flag_n2(void)
{
	struct tm date;
	time_t now;
	int ret = ALARM_ERROR_NONE;
	int tid;

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_sec += 3;

	ret = alarm_schedule_noti_with_recurrence_week_flag(NULL, &date, ALARM_WEEK_FLAG_MONDAY, &tid);

	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_notification_p
 * @since_tizen	3.0
 * @type			Positive
 * @description	Gets the notification to be invoked when the the alarm is triggered.
 * @scenario		Sets an alarm and gets the notification by alarm_id.
 *				Calls the alarm_schedule_noti_after_delay() and Calls the alarm_get_notification(),
 *				and then checks the return value.
 */
int utc_alarm_get_notification_p(void)
{
	notification_h noti;
	notification_h noti_return;
	char *text;

	int ret = ALARM_ERROR_NONE;
	int tid;
	int period = 0;
	int delay = 30;

	noti = notification_create(NOTIFICATION_TYPE_NOTI);

	ret = notification_set_text(noti, NOTIFICATION_TEXT_TYPE_TITLE,
			"test", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	assert_eq_with_exit(ret, NOTIFICATION_ERROR_NONE);

	ret = alarm_schedule_noti_after_delay(noti, delay, period, &tid);
	assert_eq_with_exit(ret, ALARM_ERROR_NONE);

	ret = alarm_get_notification(tid, &noti_return);

	alarm_cancel_all();

	ret = notification_get_text(noti_return,
			NOTIFICATION_TEXT_TYPE_TITLE, &text);
	assert_with_exit(!strcmp(text, "test"));

	notification_free(noti);
	notification_free(noti_return);

	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_alarm_get_notification_n
 * @since_tizen	3.0
 * @type			Negative
 * @description	Gets the notification to be invoked when the the alarm is triggered.
 * @scenario		Calls the alarm
 * @scenario		Calls the alarm_get_notification() with the invalid parameter
 *				that notification is NULL, and then checks the return value.
 */
int utc_alarm_get_notification_n(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_get_notification(0, NULL);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_delay_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_delay() and then checks the return value.
 *                  Removes the registerted alarms.
 */
int utc_alarm_update_delay_p(void)
{
	app_control_h app_control;
	int alarm_id;
	int ret = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_after_delay(app_control, 100, &alarm_id);
	if (ret == ALARM_ERROR_NONE)
		ret = alarm_update_delay(alarm_id, 10);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_delay_n1
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_delay() with invalid parameter
 *                  and then checks the return value.
 */
int utc_alarm_update_delay_n1(void)
{
	app_control_h app_control;
	int alarm_id;
	int ret = ALARM_ERROR_NONE;
	int ret2 = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_after_delay(app_control, 100, &alarm_id);
	if (ret == ALARM_ERROR_NONE) {
		ret2 = alarm_update_delay(alarm_id, -1);
	}

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	assert_eq_with_exit(ret2, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_delay_n2
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_delay() with invalid parameter
 *                  and then checks the return value.
 */
int utc_alarm_update_delay_n2(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_update_delay(0, 10);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_delay_n3
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_delay() for alarm whose app control launches service application
 *                  and then checks the return value.
 */
int utc_alarm_update_delay_n3(void)
{
	app_control_h app_control;
	int alarm_id;
	int ret = ALARM_ERROR_NONE;
	int ret2 = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.service-with-bg-category";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, 10, 100, &alarm_id);
	if (ret == ALARM_ERROR_NONE) {
		ret2 = alarm_update_delay(alarm_id, 100);
	}

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	assert_eq_with_exit(ret2, ALARM_ERROR_NOT_PERMITTED_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_date_p
 * @since_tizen     4.0
 * @type            Positive
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_date() and then checks the return value.
 *                  Removes the registerted alarms.
 */
int utc_alarm_update_date_p(void)
{
	struct tm date;
	struct tm date2;
	time_t now;
	app_control_h app_control;
	int alarm_id;
	const char *app_id = "org.tizen.helloworld";

	int ret = ALARM_ERROR_NONE;

	time(&now);
	now += 20;
	tzset();
	localtime_r(&now, &date);
	now += 20;
	localtime_r(&now, &date2);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_at_date(app_control, &date, &alarm_id);
	if (ret == ALARM_ERROR_NONE)
		ret = alarm_update_date(alarm_id, &date2);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_date_n1
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_date() with invalid parameter
 *                  and then checks the return value.
 */
int utc_alarm_update_date_n1(void)
{
	struct tm date;
	time_t now;
	app_control_h app_control;
	int alarm_id;
	const char *app_id = "org.tizen.helloworld";

	int ret = ALARM_ERROR_NONE;
	int ret2 = ALARM_ERROR_NONE;

	time(&now);
	now += 20;
	tzset();
	localtime_r(&now, &date);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_once_at_date(app_control, &date, &alarm_id);
	if (ret == ALARM_ERROR_NONE)
		ret2 = alarm_update_date(alarm_id, NULL);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	assert_eq_with_exit(ret2, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_date_n2
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_date() with invalid parameter
 *                  and then checks the return value.
 */
int utc_alarm_update_date_n2(void)
{
	struct tm date;
	time_t now;
	int ret = ALARM_ERROR_NONE;

	time(&now);
	now += 20;
	tzset();
	localtime_r(&now, &date);

	ret = alarm_update_date(0, &date);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_date_n3
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_date() for alarm whose app control launches service application
 *                  and then checks the return value.
 */
int utc_alarm_update_date_n3(void)
{
	struct tm date;
	time_t now;
	app_control_h app_control;
	int alarm_id;
	int ret = ALARM_ERROR_NONE;
	int ret2 = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.service-with-bg-category";
	time(&now);
	now += 20;
	tzset();
	localtime_r(&now, &date);

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, 10, 100, &alarm_id);
	if (ret == ALARM_ERROR_NONE) {
		ret2 = alarm_update_date(alarm_id, &date);
	}

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	assert_eq_with_exit(ret2, ALARM_ERROR_NOT_PERMITTED_APP);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_period_p1
 * @since_tizen     4.0
 * @type            Positive
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_period() and then checks the return value.
 *                  Removes the registerted alarms.
 */
int utc_alarm_update_period_p1(void)
{
	app_control_h app_control;
	int alarm_id;
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &alarm_id);
	if (ret == ALARM_ERROR_NONE)
		ret = alarm_update_period(alarm_id, 100);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

int utc_alarm_update_period_p2(void)
{
	app_control_h app_control;
	int alarm_id;
	int ret = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &alarm_id);
	if (ret == ALARM_ERROR_NONE)
		ret = alarm_update_period(alarm_id, 0);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_period_p3
 * @since_tizen     4.0
 * @type            Positive
 * @description     Sets an alarm to be triggered with serviceapp after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_period() and then checks the return value.
 */
int utc_alarm_update_period_p3(void)
{
	app_control_h app_control;
	int alarm_id;
	int ret = ALARM_ERROR_NONE;
	int ret2 = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	const char *app_id = "org.tizen.service-with-bg-category";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &alarm_id);
	if (ret == ALARM_ERROR_NONE)
		ret = alarm_update_period(alarm_id, 100);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_period_n1
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_period() with invalid parameter
 *                  and then checks the return value.
 */
int utc_alarm_update_period_n1(void)
{
	app_control_h app_control;
	int alarm_id;
	int ret = ALARM_ERROR_NONE;
	int ret2 = ALARM_ERROR_NONE;
	int delay = 1;
	int period = 1;
	const char *app_id = "org.tizen.helloworld";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, delay, period, &alarm_id);
	if (ret == ALARM_ERROR_NONE)
		ret2 = alarm_update_period(alarm_id, -1);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	assert_eq_with_exit(ret2, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_period_n2
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_period() with invalid parameter
 *                  and then checks the return value.
 */
int utc_alarm_update_period_n2(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_update_period(0, 10);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_week_flag_p1
 * @since_tizen     4.0
 * @type            Positive
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_week_flag() and then checks the return value.
 *                  Removes the registerted alarms.
 */
int utc_alarm_update_week_flag_p1(void)
{
	struct tm date;
	time_t now;
	app_control_h app_control;
	int alarm_id;
	const char *app_id = "org.tizen.helloworld";
	int ret = ALARM_ERROR_NONE;

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_sec += 3;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_with_recurrence_week_flag(app_control, &date, ALARM_WEEK_FLAG_MONDAY, &alarm_id);
	if (ret == ALARM_ERROR_NONE)
		ret = alarm_update_week_flag(alarm_id, ALARM_WEEK_FLAG_TUESDAY);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_week_flag_p2
 * @since_tizen     4.0
 * @type            Positive
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_week_flag() and then checks the return value.
 *                  Removes the registerted alarms.
 */
int utc_alarm_update_week_flag_p2(void)
{
	struct tm date;
	time_t now;
	app_control_h app_control;
	int alarm_id;
	const char *app_id = "org.tizen.helloworld";
	int ret = ALARM_ERROR_NONE;

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_sec += 3;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_with_recurrence_week_flag(app_control, &date, ALARM_WEEK_FLAG_MONDAY, &alarm_id);
	if (ret == ALARM_ERROR_NONE)
		ret = alarm_update_week_flag(alarm_id, 0);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	normal_exit(0);

	return 0;
}
/**
 * @testcase        utc_alarm_update_week_flag_n1
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_week_flag() with invalid parameter
 *                  and then checks the return value.
 */
int utc_alarm_update_week_flag_n1(void)
{
	struct tm date;
	time_t now;
	app_control_h app_control;
	int alarm_id;
	const char *app_id = "org.tizen.helloworld";
	int ret = ALARM_ERROR_NONE;
	int ret2 = ALARM_ERROR_NONE;

	time(&now);
	tzset();
	localtime_r(&now, &date);
	date.tm_sec += 3;

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_with_recurrence_week_flag(app_control, &date, ALARM_WEEK_FLAG_MONDAY, &alarm_id);
	if (ret == ALARM_ERROR_NONE)
		ret2 = alarm_update_week_flag(alarm_id, -1);

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	assert_eq_with_exit(ret2, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_week_flag_n2
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_week_flag() with invalid parameter
 *                  and then checks the return value.
 */
int utc_alarm_update_week_flag_n2(void)
{
	int ret = ALARM_ERROR_NONE;

	ret = alarm_update_week_flag(0, ALARM_WEEK_FLAG_MONDAY);

	assert_eq_with_exit(ret, ALARM_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase        utc_alarm_update_week_flag_n3
 * @since_tizen     4.0
 * @type            Negative
 * @description     Sets an alarm to be triggered after a specific time and update alarm delay.
 * @scenario        Calls the alarm_update_week_flag() for alarm whose app control launches service application
 *                  and then checks the return value.
 */
int utc_alarm_update_week_flag_n3(void)
{
	app_control_h app_control;
	int alarm_id;
	int ret = ALARM_ERROR_NONE;
	int ret2 = ALARM_ERROR_NONE;
	const char *app_id = "org.tizen.service-with-bg-category";

	ret = app_control_create(&app_control);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(app_control, app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = alarm_schedule_after_delay(app_control, 10, 100, &alarm_id);
	if (ret == ALARM_ERROR_NONE) {
		ret2 = alarm_update_week_flag(alarm_id, ALARM_WEEK_FLAG_MONDAY);
	}

	app_control_destroy(app_control);
	alarm_cancel_all();

	assert_eq_with_exit(ret, ALARM_ERROR_NONE);
	assert_eq_with_exit(ret2, ALARM_ERROR_NOT_PERMITTED_APP);
	normal_exit(0);

	return 0;
}
