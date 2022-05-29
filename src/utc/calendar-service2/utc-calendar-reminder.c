/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib-object.h>
#include <glib-2.0/glib.h>
#include <calendar.h>

#include "utc-calendar-debug.h"
#include "utc-calendar-util.h"

static int g_startup_err = CALENDAR_ERROR_NONE;
static GMainLoop *g_mainloop;
static bool g_checked = false;

/**
 * @function		utc_calendar_reminder_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_reminder_startup(void)
{
	g_startup_err = calendar_connect();
    if(g_startup_err != CALENDAR_ERROR_NONE) {
		if (CALENDAR_ERROR_NOT_SUPPORTED == g_startup_err
				&& false == _is_feature_supported()) {
			g_startup_err = CALENDAR_ERROR_NONE;
		} else {
			fprintf(stderr, "Startup error at %s:%d", __FILE__, __LINE__);
			fprintf(stderr, "calendar_connect failed (code: %d)", g_startup_err);
		}
    }
	_clean_db();
}

/**
 * @function		utc_calendar_reminder_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_reminder_cleanup(void)
{
	_clean_db();
	calendar_disconnect();
}

static gboolean _timeout_cb(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

static void _reminder_cb(const char *param, void *user_data)
{
	time_t now_t = 0;
	struct tm now_s = {0};

	now_t = time(NULL);
	tzset();
	localtime_r(&now_t, &now_s);
	DBG("Alarm alerted (%04d/%02d/%02d %02d:%02d:%02d)",
			now_s.tm_year + 1900, now_s.tm_mon + 1, now_s.tm_mday, now_s.tm_hour,
			now_s.tm_min, now_s.tm_sec);

	g_checked = true;
	if (g_mainloop)
		g_main_loop_quit(g_mainloop);
}

static int _delete_event(int event_id)
{
	return calendar_db_delete_record(_calendar_event._uri, event_id);
}

static int _delete_todo(int todo_id)
{
	return calendar_db_delete_record(_calendar_todo._uri, todo_id);
}

static int _add_reminder_utime_in_event(int64_t utime, int unit, int recurrence, int *out_id)
{
	int ret = 0;
	int event_id = 0;

	struct tm now_s = {0};
	time_t now_t = (time_t)utime;
	tzset();
	localtime_r(&now_t, &now_s);
	DBG("Alarm set (%04d/%02d/%02d %02d:%02d:%02d) and alarm (%d)secs before",
			now_s.tm_year + 1900, now_s.tm_mon + 1, now_s.tm_mday, now_s.tm_hour,
			now_s.tm_min, now_s.tm_sec, unit);

	calendar_time_s start_time = {0};
	start_time.type = CALENDAR_TIME_UTIME;
	start_time.time.utime = utime;

	calendar_time_s end_time = {0};
	end_time.type = CALENDAR_TIME_UTIME;
	end_time.time.utime = start_time.time.utime + 3600;

	calendar_record_h alarm = NULL;
	ret = calendar_record_create(_calendar_alarm._uri, &alarm);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(alarm, _calendar_alarm.tick_unit, unit);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	switch (unit) {
	case CALENDAR_ALARM_TIME_UNIT_SPECIFIC:
		ret = calendar_record_set_caltime(alarm, _calendar_alarm.alarm_time, start_time);
		break;
	default:
		ret = calendar_record_set_int(alarm, _calendar_alarm.tick, 1);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(alarm, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	if (CALENDAR_ALARM_TIME_UNIT_SPECIFIC != unit) {
		ret = calendar_record_set_caltime(event, _calendar_event.start_time, start_time);
		assert_eq(ret, CALENDAR_ERROR_NONE);
		ret = calendar_record_set_caltime(event, _calendar_event.end_time, end_time);
		assert_eq(ret, CALENDAR_ERROR_NONE);
	}
	if (CALENDAR_RECURRENCE_NONE != recurrence) {
		ret = calendar_record_set_int(event, _calendar_event.freq, recurrence);
		assert_eq(ret, CALENDAR_ERROR_NONE);
		ret = calendar_record_set_int(event, _calendar_event.range_type, CALENDAR_RANGE_COUNT);
		assert_eq(ret, CALENDAR_ERROR_NONE);
		ret = calendar_record_set_int(event, _calendar_event.count, 3);
		assert_eq(ret, CALENDAR_ERROR_NONE);
	}
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_record(event, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	*out_id = event_id;

	int time_id = 0;
	g_checked = false;
	g_mainloop = g_main_loop_new(NULL, false);
	ret = calendar_reminder_add_cb(_reminder_cb, NULL);
	time_id = g_timeout_add(10000, _timeout_cb, g_mainloop);
	g_main_loop_run(g_mainloop);

	ret = calendar_reminder_remove_cb(_reminder_cb, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	if (false == g_checked) {
		DBG("fail");
		return -1;
	}

	g_source_remove(time_id);

	return 0;
}

static int _add_reminder_localtime_in_event(struct tm *local, int unit, int recurrence,  int *out_id)
{
	int ret = 0;
	int event_id = 0;

	DBG("Alarm set : (%04d/%02d/%02d %02d:%02d:%02d) - (%d)secs",
			local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour,
			local->tm_min, local->tm_sec, unit);

	calendar_time_s start_time = {0};
	start_time.type = CALENDAR_TIME_LOCALTIME;
	start_time.time.date.year = local->tm_year + 1900;
	start_time.time.date.month = local->tm_mon + 1;
	start_time.time.date.mday = local->tm_mday;
	start_time.time.date.hour = local->tm_hour;
	start_time.time.date.minute = local->tm_min;
	start_time.time.date.second = local->tm_sec;

	calendar_time_s end_time = {0};
	end_time.type = CALENDAR_TIME_LOCALTIME;
	end_time.time.date.year = local->tm_year + 1900;
	end_time.time.date.month = local->tm_mon + 1;
	end_time.time.date.mday = local->tm_mday;
	end_time.time.date.hour = local->tm_hour;
	end_time.time.date.minute = local->tm_min;
	end_time.time.date.second = local->tm_sec;

	calendar_record_h alarm = NULL;
	ret = calendar_record_create(_calendar_alarm._uri, &alarm);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(alarm, _calendar_alarm.tick_unit, unit);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	switch (unit) {
	case CALENDAR_ALARM_TIME_UNIT_SPECIFIC:
		ret = calendar_record_set_caltime(alarm, _calendar_alarm.alarm_time, start_time);
		break;
	default:
		ret = calendar_record_set_int(alarm, _calendar_alarm.tick, 1);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(alarm, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	if (CALENDAR_ALARM_TIME_UNIT_SPECIFIC != unit) {
		ret = calendar_record_set_caltime(event, _calendar_event.start_time, start_time);
		assert_eq(ret, CALENDAR_ERROR_NONE);
		ret = calendar_record_set_caltime(event, _calendar_event.end_time, end_time);
		assert_eq(ret, CALENDAR_ERROR_NONE);
	}
	if (CALENDAR_RECURRENCE_NONE != recurrence) {
		ret = calendar_record_set_int(event, _calendar_event.freq, recurrence);
		assert_eq(ret, CALENDAR_ERROR_NONE);
		ret = calendar_record_set_int(event, _calendar_event.range_type, CALENDAR_RANGE_COUNT);
		assert_eq(ret, CALENDAR_ERROR_NONE);
		ret = calendar_record_set_int(event, _calendar_event.count, 3);
		assert_eq(ret, CALENDAR_ERROR_NONE);
	}
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_record(event, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	*out_id = event_id;

	int time_id = 0;
	g_checked = false;
	g_mainloop = g_main_loop_new(NULL, false);
	ret = calendar_reminder_add_cb(_reminder_cb, NULL);
	time_id = g_timeout_add(10000, _timeout_cb, g_mainloop);
	g_main_loop_run(g_mainloop);

	ret = calendar_reminder_remove_cb(_reminder_cb, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	if (false == g_checked) {
		DBG("fail");
		return -1;
	}

	g_source_remove(time_id);

	return 0;
}

static int _add_reminder_utime_in_todo(int64_t utime, int unit, int recurrence, int *out_id)
{
	int ret = 0;
	int todo_id = 0;

	struct tm now_s = {0};
	time_t now_t = (time_t)utime;
	tzset();
	localtime_r(&now_t, &now_s);
	DBG("Alarm set (%04d/%02d/%02d %02d:%02d:%02d) and alarm (%d)secs before",
			now_s.tm_year + 1900, now_s.tm_mon + 1, now_s.tm_mday, now_s.tm_hour,
			now_s.tm_min, now_s.tm_sec, unit);

	calendar_time_s due_time = {0};
	due_time.type = CALENDAR_TIME_UTIME;
	due_time.time.utime = utime;

	calendar_record_h alarm = NULL;
	ret = calendar_record_create(_calendar_alarm._uri, &alarm);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(alarm, _calendar_alarm.tick_unit, unit);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	switch (unit) {
	case CALENDAR_ALARM_TIME_UNIT_SPECIFIC:
		ret = calendar_record_set_caltime(alarm, _calendar_alarm.alarm_time, due_time);
		break;
	default:
		ret = calendar_record_set_int(alarm, _calendar_alarm.tick, 1);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(alarm, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	if (CALENDAR_ALARM_TIME_UNIT_SPECIFIC != unit) {
		ret = calendar_record_set_caltime(todo, _calendar_todo.due_time, due_time);
		assert_eq(ret, CALENDAR_ERROR_NONE);
	}
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_alarm, alarm);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_record(todo, &todo_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	*out_id = todo_id;

	int time_id = 0;
	g_checked = false;
	g_mainloop = g_main_loop_new(NULL, false);
	ret = calendar_reminder_add_cb(_reminder_cb, NULL);
	time_id = g_timeout_add(10000, _timeout_cb, g_mainloop);
	g_main_loop_run(g_mainloop);

	ret = calendar_reminder_remove_cb(_reminder_cb, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);

	if (false == g_checked) {
		DBG("fail");
		return -1;
	}

	g_source_remove(time_id);

	return 0;
}

static int _add_reminder_localtime_in_todo(struct tm *local, int unit, int recurrence,  int *out_id)
{
	int ret = 0;
	int todo_id = 0;

	DBG("Alarm set : (%04d/%02d/%02d %02d:%02d:%02d) - (%d)secs",
			local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour,
			local->tm_min, local->tm_sec, unit);

	calendar_time_s due_time = {0};
	due_time.type = CALENDAR_TIME_LOCALTIME;
	due_time.time.date.year = local->tm_year + 1900;
	due_time.time.date.month = local->tm_mon + 1;
	due_time.time.date.mday = local->tm_mday;
	due_time.time.date.hour = local->tm_hour;
	due_time.time.date.minute = local->tm_min;
	due_time.time.date.second = local->tm_sec;

	calendar_record_h alarm = NULL;
	ret = calendar_record_create(_calendar_alarm._uri, &alarm);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(alarm, _calendar_alarm.tick_unit, unit);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	switch (unit) {
	case CALENDAR_ALARM_TIME_UNIT_SPECIFIC:
		ret = calendar_record_set_caltime(alarm, _calendar_alarm.alarm_time, due_time);
		break;
	default:
		ret = calendar_record_set_int(alarm, _calendar_alarm.tick, 1);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(alarm, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	if (CALENDAR_ALARM_TIME_UNIT_SPECIFIC != unit) {
		ret = calendar_record_set_caltime(todo, _calendar_todo.due_time, due_time);
		assert_eq(ret, CALENDAR_ERROR_NONE);
	}
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_alarm, alarm);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_record(todo, &todo_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	*out_id = todo_id;

	int time_id = 0;
	g_checked = false;
	g_mainloop = g_main_loop_new(NULL, false);
	ret = calendar_reminder_add_cb(_reminder_cb, NULL);
	time_id = g_timeout_add(10000, _timeout_cb, g_mainloop);
	g_main_loop_run(g_mainloop);

	ret = calendar_reminder_remove_cb(_reminder_cb, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);

	if (false == g_checked) {
		DBG("fail");
		return -1;
	}

	g_source_remove(time_id);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an once alarm alerts.
 */
int utc_calendar_reminder_add_cb_utime_once_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	now_t = time(NULL);
	now_t += 5;
	now_t += 60;					/* add 1 min */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_NONE, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60);				/* add 1 hour */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_HOUR,
			CALENDAR_RECURRENCE_NONE, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24);		/* add 1 day */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_DAY,
			CALENDAR_RECURRENCE_NONE, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24 * 7);	/* add 1 week */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_WEEK,
			CALENDAR_RECURRENCE_NONE, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_utime_daily_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an daily event alarm alerts.
 */
int utc_calendar_reminder_add_cb_utime_daily_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	DBG("add 1 min, daily");
	now_t = time(NULL);
	now_t += 5;
	now_t += 60;					/* add 1 min */
	now_t -= (60 * 60 * 24);		/* 1 day before */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_DAILY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 hour, daily");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60);				/* add 1 hour */
	now_t -= (60 * 60 * 24);		/* 1 day before */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_HOUR,
			CALENDAR_RECURRENCE_DAILY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 day, daily");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24);		/* add 1 day */
	now_t -= (60 * 60 * 24);		/* 1 day before */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_DAY,
			CALENDAR_RECURRENCE_DAILY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 week, daily");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24 * 7);	/* add 1 week */
	now_t -= (60 * 60 * 24);		/* 1 day before */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_WEEK,
			CALENDAR_RECURRENCE_DAILY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_utime_weekly_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an weekly event alarm alerts.
 */
int utc_calendar_reminder_add_cb_utime_weekly_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	DBG("add 1 min, weekly");
	now_t = time(NULL);
	now_t += 5;
	now_t += 60;					/* add 1 min */
	now_t -= (60 * 60 * 24 * 7);	/* 1 week before */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_WEEKLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 hour, weekly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60);				/* add 1 hour */
	now_t -= (60 * 60 * 24 * 7);	/* 1 week before */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_HOUR,
			CALENDAR_RECURRENCE_WEEKLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 day, weekly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24);		/* add 1 day */
	now_t -= (60 * 60 * 24 * 7);	/* 1 week before */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_DAY,
			CALENDAR_RECURRENCE_WEEKLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 week, weekly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24 * 7);	/* add 1 week */
	now_t -= (60 * 60 * 24 * 7);	/* 1 week before */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_WEEK,
			CALENDAR_RECURRENCE_WEEKLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_utime_monthly_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an monthly event alarm alerts.
 */
int utc_calendar_reminder_add_cb_utime_monthly_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;
	struct tm now_s = {0};

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	DBG("add 1 min, monthly");
	now_t = time(NULL);
	now_t += 5;
	now_t += 60;					/* add 1 min */
	tzset();
	localtime_r(&now_t, &now_s);
	if (now_s.tm_mday < 2 || 28 < now_s.tm_mday)			/* if mday goes over 28, alarm needs more params */
		return 0;
	if (0 == now_s.tm_mon) { /* Jan */
		now_s.tm_year--;
		now_s.tm_mon = 11;
	} else {
		now_s.tm_mon--;
	}
	now_t = (int64_t)mktime(&now_s);
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_MONTHLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 hour, monthly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60);				/* add 1 hour */
	tzset();
	localtime_r(&now_t, &now_s);
	if (now_s.tm_mday < 2 || 28 < now_s.tm_mday)			/* if mday goes over 28, alarm needs more params */
		return 0;
	if (0 == now_s.tm_mon) { /* Jan */
		now_s.tm_year--;
		now_s.tm_mon = 11;
	} else {
		now_s.tm_mon--;
	}
	now_t = (int64_t)mktime(&now_s);
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_HOUR,
			CALENDAR_RECURRENCE_MONTHLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 day, monthly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24);		/* add 1 day */
	tzset();
	localtime_r(&now_t, &now_s);
	if (now_s.tm_mday < 2 || 28 < now_s.tm_mday)			/* if mday goes over 28, alarm needs more params */
		return 0;
	if (0 == now_s.tm_mon) { /* Jan */
		now_s.tm_year--;
		now_s.tm_mon = 11;
	} else {
		now_s.tm_mon--;
	}
	now_t = (int64_t)mktime(&now_s);
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_DAY,
			CALENDAR_RECURRENCE_MONTHLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 week, monthly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24 * 7);	/* add 1 week */
	tzset();
	localtime_r(&now_t, &now_s);
	if (now_s.tm_mday < 2 || 28 < now_s.tm_mday)			/* if mday goes over 28, alarm needs more params */
		return 0;
	if (0 == now_s.tm_mon) { /* Jan */
		now_s.tm_year--;
		now_s.tm_mon = 11;
	} else {
		now_s.tm_mon--;
	}
	now_t = (int64_t)mktime(&now_s);
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_WEEK,
			CALENDAR_RECURRENCE_MONTHLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_utime_yearly_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an yearly event alarm alerts.
 */
int utc_calendar_reminder_add_cb_utime_yearly_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;
	struct tm now_s = {0};

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	DBG("add 1 min, yearly");
	now_t = time(NULL);
	now_t += 5;
	now_t += 60;					/* add 1 min */
	tzset();
	localtime_r(&now_t, &now_s);
	now_s.tm_year--;
	now_t = (int64_t)mktime(&now_s);
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_YEARLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 hour, yearly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60);				/* add 1 hour */
	tzset();
	localtime_r(&now_t, &now_s);
	now_s.tm_year--;
	now_t = (int64_t)mktime(&now_s);
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_HOUR,
			CALENDAR_RECURRENCE_YEARLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 day, yearly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24);		/* add 1 day */
	tzset();
	localtime_r(&now_t, &now_s);
	now_s.tm_year--;
	now_t = (int64_t)mktime(&now_s);
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_DAY,
			CALENDAR_RECURRENCE_YEARLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 week, yearly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24 * 7);	/* add 1 week */
	tzset();
	localtime_r(&now_t, &now_s);
	now_s.tm_year--;
	now_t = (int64_t)mktime(&now_s);
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_WEEK,
			CALENDAR_RECURRENCE_YEARLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_utime_specific_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an specific event alarm alerts.
 */
int utc_calendar_reminder_add_cb_utime_specific_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	now_t = time(NULL);
	now_t += 5;						/* add 5 secs */
	ret = _add_reminder_utime_in_event((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_SPECIFIC,
			CALENDAR_RECURRENCE_NONE, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_localtime_once_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an once event alarm alerts.
 */
int utc_calendar_reminder_add_cb_localtime_once_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;
	struct tm now_s = {0};

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	DBG("add 1 hour, once");
	now_t = time(NULL);
	now_t += 5;
	now_t += 60;				/* add 1 hour */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_NONE, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 hour, once");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60);				/* add 1 hour */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_HOUR,
			CALENDAR_RECURRENCE_NONE, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 day, once");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24);		/* add 1 day */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_DAY,
			CALENDAR_RECURRENCE_NONE, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 week, once");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24 * 7);	/* add 1 week */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_WEEK,
			CALENDAR_RECURRENCE_NONE, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_localtime_daily_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an daily event alarm alerts.
 */
int utc_calendar_reminder_add_cb_localtime_daily_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;
	struct tm now_s = {0};

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	DBG("add 1 min, daily");
	now_t = time(NULL);
	now_t += 5;
	now_t += 60;					/* add 1 min */
	now_t -= (60 * 60 * 24);		/* 1 day before */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_DAILY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 hour, daily");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60);				/* add 1 hour */
	now_t -= (60 * 60 * 24);		/* 1 day before */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_HOUR,
			CALENDAR_RECURRENCE_DAILY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 day, daily");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24);		/* add 1 day */
	now_t -= (60 * 60 * 24);		/* 1 day before */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_DAY,
			CALENDAR_RECURRENCE_DAILY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 week, daily");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24 * 7);	/* add 1 week */
	now_t -= (60 * 60 * 24);		/* 1 day before */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_WEEK,
			CALENDAR_RECURRENCE_DAILY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_localtime_weekly_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an weekly event alarm alerts.
 */
int utc_calendar_reminder_add_cb_localtime_weekly_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;
	struct tm now_s = {0};

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	/* localtime weekly */
	DBG("add 1 min, weekly");
	now_t = time(NULL);
	now_t += 5;
	now_t += 60;					/* add 1 min */
	now_t -= (60 * 60 * 24 * 7);	/* 1 week before */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_WEEKLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 hour, weekly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60);				/* add 1 hour */
	now_t -= (60 * 60 * 24 * 7);	/* 1 week before */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_HOUR,
			CALENDAR_RECURRENCE_WEEKLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 day, weekly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24);		/* add 1 day */
	now_t -= (60 * 60 * 24 * 7);	/* 1 week before */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_DAY,
			CALENDAR_RECURRENCE_WEEKLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 week, weekly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24 * 7);	/* add 1 week */
	now_t -= (60 * 60 * 24 * 7);	/* 1 week before */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_WEEK,
			CALENDAR_RECURRENCE_WEEKLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_localtime_monthly_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an monthly event alarm alerts.
 */
int utc_calendar_reminder_add_cb_localtime_monthly_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;
	struct tm now_s = {0};

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	DBG("add 1 min, monthly");
	now_t = time(NULL);
	now_t += 5;
	now_t += 60;					/* add 1 min */
	tzset();
	localtime_r(&now_t, &now_s);
	if (now_s.tm_mday < 2 || 28 < now_s.tm_mday)			/* if mday goes over 28, alarm needs more params */
		return 0;
	if (0 == now_s.tm_mon) { /* Jan */
		now_s.tm_year--;
		now_s.tm_mon = 11;
	} else {
		now_s.tm_mon--;
	}
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_MONTHLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 hour, monthly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60);				/* add 1 hour */
	tzset();
	localtime_r(&now_t, &now_s);
	if (now_s.tm_mday < 2 || 28 < now_s.tm_mday)			/* if mday goes over 28, alarm needs more params */
		return 0;
	if (0 == now_s.tm_mon) { /* Jan */
		now_s.tm_year--;
		now_s.tm_mon = 11;
	} else {
		now_s.tm_mon--;
	}
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_HOUR,
			CALENDAR_RECURRENCE_MONTHLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 day, monthly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24);		/* add 1 day */
	tzset();
	localtime_r(&now_t, &now_s);
	if (now_s.tm_mday < 2 || 28 < now_s.tm_mday)			/* if mday goes over 28, alarm needs more params */
		return 0;
	if (0 == now_s.tm_mon) { /* Jan */
		now_s.tm_year--;
		now_s.tm_mon = 11;
	} else {
		now_s.tm_mon--;
	}
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_DAY,
			CALENDAR_RECURRENCE_MONTHLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 week, monthly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24 * 7);	/* add 1 week */
	tzset();
	localtime_r(&now_t, &now_s);
	if (now_s.tm_mday < 2 || 28 < now_s.tm_mday)			/* if mday goes over 28, alarm needs more params */
		return 0;
	if (0 == now_s.tm_mon) { /* Jan */
		now_s.tm_year--;
		now_s.tm_mon = 11;
	} else {
		now_s.tm_mon--;
	}
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_WEEK,
			CALENDAR_RECURRENCE_MONTHLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_localtime_yearly_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an yearly event alarm alerts.
 */
int utc_calendar_reminder_add_cb_localtime_yearly_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;
	struct tm now_s = {0};

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	DBG("add 1 min, yearly");
	now_t = time(NULL);
	now_t += 5;
	now_t += 60;					/* add 1 min */
	tzset();
	localtime_r(&now_t, &now_s);
	now_s.tm_year--;
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_YEARLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 hour, yearly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60);				/* add 1 hour */
	tzset();
	localtime_r(&now_t, &now_s);
	now_s.tm_year--;
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_HOUR,
			CALENDAR_RECURRENCE_YEARLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 day, yearly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24);		/* add 1 day */
	tzset();
	localtime_r(&now_t, &now_s);
	now_s.tm_year--;
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_DAY,
			CALENDAR_RECURRENCE_YEARLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	DBG("add 1 week, yearly");
	now_t = time(NULL);
	now_t += 5;
	now_t += (60 * 60 * 24 * 7);	/* add 1 week */
	tzset();
	localtime_r(&now_t, &now_s);
	now_s.tm_year--;
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_WEEK,
			CALENDAR_RECURRENCE_YEARLY, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_localtime_specific_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an specific event alarm alerts.
 */
int utc_calendar_reminder_add_cb_localtime_specific_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int event_id = 0;
	time_t now_t = 0;
	struct tm now_s = {0};

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	now_t = time(NULL);
	now_t += 5;						/* add 5 secs */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_event(&now_s, CALENDAR_ALARM_TIME_UNIT_SPECIFIC,
			CALENDAR_RECURRENCE_NONE, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_event(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_todo_utime_once_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an todo alarm alerts.
 */
int utc_calendar_reminder_add_cb_todo_utime_once_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int todo_id = 0;
	time_t now_t = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	now_t = time(NULL);
	now_t += 5;
	now_t += 60;					/* add 1 min */
	ret = _add_reminder_utime_in_todo((int64_t)now_t, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_NONE, &todo_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_todo(todo_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_todo_localtime_once_p
 * @since_tizen		3.0
 * @description		Test adding a callback to get a notification when an once todo alarm alerts.
 */
int utc_calendar_reminder_add_cb_todo_localtime_once_p(void)
{
	DBG("[%s]", __func__);

	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	int todo_id = 0;
	time_t now_t = 0;
	struct tm now_s = {0};

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	now_t = time(NULL);
	now_t += 5;
	now_t += 60;				/* add 1 hour */
	tzset();
	localtime_r(&now_t, &now_s);
	ret = _add_reminder_localtime_in_todo(&now_s, CALENDAR_ALARM_TIME_UNIT_MINUTE,
			CALENDAR_RECURRENCE_NONE, &todo_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _delete_todo(todo_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_reminder_add_cb_n
 * @since_tizen		2.3
 * @description		Test fail adding a callback to get an alarm notification with invalid parameters.
 */
int utc_calendar_reminder_add_cb_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_add_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = calendar_reminder_add_cb(NULL, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return CALENDAR_ERROR_NONE;
}

/**
 * @testcase		utc_calendar_reminder_remove_cb_p
 * @since_tizen		2.3
 * @description		Test removing a callback to get a notification when an alarm alerts.
 */
int utc_calendar_reminder_remove_cb_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_remove_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = calendar_reminder_add_cb(_reminder_cb, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_reminder_remove_cb(_reminder_cb, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_reminder_remove_cb_n
 * @since_tizen		2.3
 * @description		Test fail removing a callback to get an alarm notification with invalid parameters.
 */
int utc_calendar_reminder_remove_cb_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_reminder_remove_cb(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = calendar_reminder_remove_cb(NULL, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}
