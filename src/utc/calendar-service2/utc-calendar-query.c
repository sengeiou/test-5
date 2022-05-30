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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <calendar.h>

#include "utc-calendar-debug.h"
#include "utc-calendar-util.h"
#include "utc-calendar-helper-timezone.h"
#include "utc-calendar-helper-event.h"
#include "utc-calendar-helper-todo.h"
#include "utc-calendar-helper-book.h"
#include "utc-calendar-helper-alarm.h"
#include "utc-calendar-helper-attendee.h"
#include "utc-calendar-helper-extended.h"

static int g_startup_err = CALENDAR_ERROR_NONE;

/**
 * @function		utc_calendar_query_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_query_startup(void)
{
    g_startup_err = calendar_connect();
    if (g_startup_err != CALENDAR_ERROR_NONE) {
		if (CALENDAR_ERROR_NOT_SUPPORTED == g_startup_err
				&& false == _is_feature_supported()) {
			g_startup_err = CALENDAR_ERROR_NONE;
		} else {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "calendar_connect failed (code: %d)\n", g_startup_err);
		}
    }
}

/**
 * @function		utc_calendar_query_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_query_cleanup(void)
{
    calendar_disconnect();
}

/**
 * @testcase		utc_calendar_query_create_p
 * @since_tizen		2.3
 * @description		Test creating a query handle.
 */
int utc_calendar_query_create_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_create(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_event._uri, &query);
    assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == query)
		assert_eq(-1, CALENDAR_ERROR_NONE);

    calendar_query_destroy(query);
	return 0;
}

/**
 * @testcase		utc_calendar_query_create_n
 * @since_tizen		2.3
 * @description		Test fail creating a query handle with invalid parameters.
 */
int utc_calendar_query_create_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_create(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_query_h query = NULL;
	// case 1
	ret = calendar_query_create(NULL, &query);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_query_create(_calendar_event._uri, NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_query_destroy_p
 * @since_tizen		2.3
 * @description		Test destroying a query handle.
 */
int utc_calendar_query_destroy_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_destroy(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_event._uri, &query);
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_query_destroy(query);
    assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_query_destroy_n
 * @since_tizen		2.3
 * @description		Test fail destroying a query handle with invalid parameter.
 */
int utc_calendar_query_destroy_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_destroy(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_query_destroy(NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

static int _set_projection(const char *view_uri, unsigned int projection[], int projection_count)
{
	int ret = 0;

	calendar_query_h query = NULL;
	ret = calendar_query_create(view_uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_query_set_projection(query, projection, projection_count);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int offset = 0, limit = 0;
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_records_with_query(query, offset, limit, &get_list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_list_destroy(get_list, true);
	calendar_query_destroy(query);

	return ret;
}
static int _delete_record(const char *view_uri, int id)
{
	return calendar_db_delete_record(view_uri, id);
}

static int _insert_book(int *out_id)
{
	int ret = 0;
	calendar_record_h book = NULL;
	ret = calendar_record_create(_calendar_book._uri, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_set_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int record_id = 0;
	ret = calendar_db_insert_record(book, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(book, true);

	*out_id = record_id;
	return ret;
}
static int _set_projection_p_book(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_book(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_book.id,
		_calendar_book.uid,
		_calendar_book.name,
		_calendar_book.description,
		_calendar_book.color,
		_calendar_book.location,
		_calendar_book.visibility,
		_calendar_book.sync_event,
		_calendar_book.account_id,
		_calendar_book.store_type,
		_calendar_book.sync_data1,
		_calendar_book.sync_data2,
		_calendar_book.sync_data3,
		_calendar_book.sync_data4,
		_calendar_book.mode,
	};
	ret = _set_projection(_calendar_book._uri, projection,
			sizeof(projection) / sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_book._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}
static int _insert_event_utime(int *out_id)
{
	int ret = 0;
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int record_id = 0;
	ret = calendar_db_insert_record(event, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	*out_id = record_id;
	return ret;
}
static int _insert_event_localtime(int *out_id)
{
	int ret = 0;
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new_local(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int record_id = 0;
	ret = calendar_db_insert_record(event, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	*out_id = record_id;
	return ret;
}
static int _set_projection_p_event(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_event_utime(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_event.id,
		_calendar_event.calendar_book_id,
		_calendar_event.summary,
		_calendar_event.description,
		_calendar_event.location,
		_calendar_event.categories,
		_calendar_event.exdate,
		_calendar_event.event_status,
		_calendar_event.priority,
		_calendar_event.timezone,
		_calendar_event.person_id,
		_calendar_event.busy_status,
		_calendar_event.sensitivity,
		_calendar_event.uid,
		_calendar_event.organizer_name,
		_calendar_event.organizer_email,
		_calendar_event.meeting_status,
		_calendar_event.original_event_id,
		_calendar_event.latitude,
		_calendar_event.longitude,
		_calendar_event.email_id,
		_calendar_event.created_time,
		_calendar_event.last_modified_time,
		_calendar_event.is_deleted,
		_calendar_event.freq,
		_calendar_event.range_type,
		_calendar_event.until_time,
		_calendar_event.count,
		_calendar_event.interval,
		_calendar_event.bysecond,
		_calendar_event.byminute,
		_calendar_event.byhour,
		_calendar_event.byday,
		_calendar_event.bymonthday,
		_calendar_event.byyearday,
		_calendar_event.byweekno,
		_calendar_event.bymonth,
		_calendar_event.bysetpos,
		_calendar_event.wkst,
		_calendar_event.recurrence_id,
		_calendar_event.rdate,
		_calendar_event.has_attendee,
		_calendar_event.has_alarm,
		_calendar_event.calendar_system_type,
		_calendar_event.sync_data1,
		_calendar_event.sync_data2,
		_calendar_event.sync_data3,
		_calendar_event.sync_data4,
		_calendar_event.start_time,
		_calendar_event.start_tzid,
		_calendar_event.end_time,
		_calendar_event.end_tzid,
		_calendar_event.is_allday,
	};
	ret = _set_projection(_calendar_event._uri, projection,
			sizeof(projection) / sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}
static int _insert_todo(int *out_id)
{
	int ret = 0;
	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_todo_set_new(todo);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int record_id = 0;
	ret = calendar_db_insert_record(todo, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);

	*out_id = record_id;
	return ret;
}
static int _set_projection_p_todo(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_todo(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_todo.id,
		_calendar_todo.calendar_book_id,
		_calendar_todo.summary,
		_calendar_todo.description,
		_calendar_todo.location,
		_calendar_todo.categories,
		_calendar_todo.todo_status,
		_calendar_todo.priority,
		_calendar_todo.sensitivity,
		_calendar_todo.uid,
		_calendar_todo.latitude,
		_calendar_todo.longitude,
		_calendar_todo.created_time,
		_calendar_todo.last_modified_time,
		_calendar_todo.completed_time,
		_calendar_todo.progress,
		_calendar_todo.is_deleted,
		_calendar_todo.freq,
		_calendar_todo.range_type,
		_calendar_todo.until_time,
		_calendar_todo.count,
		_calendar_todo.interval,
		_calendar_todo.bysecond,
		_calendar_todo.byminute,
		_calendar_todo.byhour,
		_calendar_todo.byday,
		_calendar_todo.bymonthday,
		_calendar_todo.byyearday,
		_calendar_todo.byweekno,
		_calendar_todo.bymonth,
		_calendar_todo.bysetpos,
		_calendar_todo.wkst,
		_calendar_todo.has_alarm,
		_calendar_todo.sync_data1,
		_calendar_todo.sync_data2,
		_calendar_todo.sync_data3,
		_calendar_todo.sync_data4,
		_calendar_todo.start_time,
		_calendar_todo.start_tzid,
		_calendar_todo.due_time,
		_calendar_todo.due_tzid,
		_calendar_todo.organizer_name,
		_calendar_todo.organizer_email,
		_calendar_todo.has_attendee,
		_calendar_todo.is_allday,
	};
	ret = _set_projection(_calendar_todo._uri, projection,
			sizeof(projection) / sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_todo._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}
static int _insert_timezone(int *out_id)
{
	int ret = 0;
	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_timezone_set_new(timezone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int record_id = 0;
	ret = calendar_db_insert_record(timezone, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(timezone, true);

	*out_id = record_id;
	return ret;
}
static int _set_projection_p_timezone(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_timezone(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_timezone.id,
		_calendar_timezone.calendar_book_id,
		_calendar_timezone.tz_offset_from_gmt,
		_calendar_timezone.standard_name,
		_calendar_timezone.standard_start_month,
		_calendar_timezone.standard_start_position_of_week,
		_calendar_timezone.standard_start_day,
		_calendar_timezone.standard_start_hour,
		_calendar_timezone.standard_bias,
		_calendar_timezone.day_light_name,
		_calendar_timezone.day_light_start_month,
		_calendar_timezone.day_light_start_position_of_week,
		_calendar_timezone.day_light_start_day,
		_calendar_timezone.day_light_start_hour,
		_calendar_timezone.day_light_bias,
	};
	ret = _set_projection(_calendar_timezone._uri, projection,
			sizeof(projection) / sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_timezone._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}
static int _insert_event_alarm(int *out_id)
{
	int ret = 0;
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// alarm
	calendar_record_h alarm = NULL;
	ret = calendar_record_create(_calendar_alarm._uri, &alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_alarm_set_new(alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(alarm, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(alarm, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int record_id = 0;
	ret = calendar_db_insert_record(event, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	*out_id = record_id;
	return ret;
}
static int _set_projection_p_alarm(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_event_alarm(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_alarm.parent_id,
		_calendar_alarm.tick,
		_calendar_alarm.tick_unit,
		_calendar_alarm.description,
		_calendar_alarm.summary,
		_calendar_alarm.action,
		_calendar_alarm.attach,
		_calendar_alarm.alarm_time,
	};
	ret = _set_projection(_calendar_alarm._uri, projection,
			sizeof(projection)/sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}

static int _insert_event_attendee(int *out_id)
{
	int ret = 0;
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_set_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int record_id = 0;
	ret = calendar_db_insert_record(event, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	*out_id = record_id;
	return ret;
}
static int _set_projection_p_attendee(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_event_attendee(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_attendee.parent_id,
		_calendar_attendee.number,
		_calendar_attendee.cutype,
		_calendar_attendee.person_id,
		_calendar_attendee.uid,
		_calendar_attendee.group,
		_calendar_attendee.email,
		_calendar_attendee.role,
		_calendar_attendee.status,
		_calendar_attendee.rsvp,
		_calendar_attendee.delegatee_uri,
		_calendar_attendee.delegator_uri,
		_calendar_attendee.name,
		_calendar_attendee.member,
	};
	ret = _set_projection(_calendar_attendee._uri, projection,
			sizeof(projection)/sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}

static int _insert_event_extended(int *out_id)
{
	int ret = 0;
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_extended_set_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int record_id = 0;
	ret = calendar_db_insert_record(event, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	*out_id = record_id;
	return ret;
}
static int _set_projection_p_extended(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_event_extended(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_extended_property.id,
		_calendar_extended_property.record_id,
		_calendar_extended_property.record_type,
		_calendar_extended_property.key,
		_calendar_extended_property.value,
	};
	ret = _set_projection(_calendar_extended_property._uri, projection,
			sizeof(projection)/sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}

static int _set_projection_p_event_calendar_book(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_event_utime(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_event_calendar_book.event_id,
		_calendar_event_calendar_book.calendar_book_id,
		_calendar_event_calendar_book.summary,
		_calendar_event_calendar_book.description,
		_calendar_event_calendar_book.location,
		_calendar_event_calendar_book.categories,
		_calendar_event_calendar_book.exdate,
		_calendar_event_calendar_book.event_status,
		_calendar_event_calendar_book.priority,
		_calendar_event_calendar_book.timezone,
		_calendar_event_calendar_book.person_id,
		_calendar_event_calendar_book.busy_status,
		_calendar_event_calendar_book.sensitivity,
		_calendar_event_calendar_book.uid,
		_calendar_event_calendar_book.organizer_name,
		_calendar_event_calendar_book.organizer_email,
		_calendar_event_calendar_book.meeting_status,
		_calendar_event_calendar_book.original_event_id,
		_calendar_event_calendar_book.latitude,
		_calendar_event_calendar_book.longitude,
		_calendar_event_calendar_book.email_id,
		_calendar_event_calendar_book.created_time,
		_calendar_event_calendar_book.last_modified_time,
		_calendar_event_calendar_book.freq,
		_calendar_event_calendar_book.range_type,
		_calendar_event_calendar_book.until_time,
		_calendar_event_calendar_book.count,
		_calendar_event_calendar_book.interval,
		_calendar_event_calendar_book.bysecond,
		_calendar_event_calendar_book.byminute,
		_calendar_event_calendar_book.byhour,
		_calendar_event_calendar_book.byday,
		_calendar_event_calendar_book.bymonthday,
		_calendar_event_calendar_book.byyearday,
		_calendar_event_calendar_book.byweekno,
		_calendar_event_calendar_book.bymonth,
		_calendar_event_calendar_book.bysetpos,
		_calendar_event_calendar_book.wkst,
		_calendar_event_calendar_book.recurrence_id,
		_calendar_event_calendar_book.rdate,
		_calendar_event_calendar_book.has_attendee,
		_calendar_event_calendar_book.has_alarm,
		_calendar_event_calendar_book.calendar_system_type,
		_calendar_event_calendar_book.sync_data1,
		_calendar_event_calendar_book.sync_data2,
		_calendar_event_calendar_book.sync_data3,
		_calendar_event_calendar_book.sync_data4,
		_calendar_event_calendar_book.start_time,
		_calendar_event_calendar_book.start_tzid,
		_calendar_event_calendar_book.end_time,
		_calendar_event_calendar_book.end_tzid,
		_calendar_event_calendar_book.is_allday,
	};
	ret = _set_projection(_calendar_event_calendar_book._uri, projection,
			sizeof(projection) / sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}
static int _set_projection_p_todo_calendar_book(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_todo(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_todo_calendar_book.todo_id,
		_calendar_todo_calendar_book.calendar_book_id,
		_calendar_todo_calendar_book.summary,
		_calendar_todo_calendar_book.description,
		_calendar_todo_calendar_book.location,
		_calendar_todo_calendar_book.categories,
		_calendar_todo_calendar_book.todo_status,
		_calendar_todo_calendar_book.priority,
		_calendar_todo_calendar_book.sensitivity,
		_calendar_todo_calendar_book.uid,
		_calendar_todo_calendar_book.latitude,
		_calendar_todo_calendar_book.longitude,
		_calendar_todo_calendar_book.created_time,
		_calendar_todo_calendar_book.last_modified_time,
		_calendar_todo_calendar_book.completed_time,
		_calendar_todo_calendar_book.progress,
		_calendar_todo_calendar_book.freq,
		_calendar_todo_calendar_book.range_type,
		_calendar_todo_calendar_book.until_time,
		_calendar_todo_calendar_book.count,
		_calendar_todo_calendar_book.interval,
		_calendar_todo_calendar_book.bysecond,
		_calendar_todo_calendar_book.byminute,
		_calendar_todo_calendar_book.byhour,
		_calendar_todo_calendar_book.byday,
		_calendar_todo_calendar_book.bymonthday,
		_calendar_todo_calendar_book.byyearday,
		_calendar_todo_calendar_book.byweekno,
		_calendar_todo_calendar_book.bymonth,
		_calendar_todo_calendar_book.bysetpos,
		_calendar_todo_calendar_book.wkst,
		_calendar_todo_calendar_book.has_alarm,
		_calendar_todo_calendar_book.sync_data1,
		_calendar_todo_calendar_book.sync_data2,
		_calendar_todo_calendar_book.sync_data3,
		_calendar_todo_calendar_book.sync_data4,
		_calendar_todo_calendar_book.start_time,
		_calendar_todo_calendar_book.start_tzid,
		_calendar_todo_calendar_book.due_time,
		_calendar_todo_calendar_book.due_tzid,
		_calendar_todo_calendar_book.organizer_name,
		_calendar_todo_calendar_book.organizer_email,
		_calendar_todo_calendar_book.has_attendee,
		_calendar_todo_calendar_book.is_allday,
	};
	ret = _set_projection(_calendar_todo_calendar_book._uri, projection,
			sizeof(projection) / sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_todo._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}
static int _set_projection_p_instance_utime_calendar_book(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_event_utime(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_instance_utime_calendar_book.event_id,
		_calendar_instance_utime_calendar_book.start_time,
		_calendar_instance_utime_calendar_book.end_time,
		_calendar_instance_utime_calendar_book.summary,
		_calendar_instance_utime_calendar_book.location,
		_calendar_instance_utime_calendar_book.calendar_book_id,
		_calendar_instance_utime_calendar_book.description,
		_calendar_instance_utime_calendar_book.busy_status,
		_calendar_instance_utime_calendar_book.event_status,
		_calendar_instance_utime_calendar_book.priority,
		_calendar_instance_utime_calendar_book.sensitivity,
		_calendar_instance_utime_calendar_book.has_rrule,
		_calendar_instance_utime_calendar_book.latitude,
		_calendar_instance_utime_calendar_book.longitude,
		_calendar_instance_utime_calendar_book.has_alarm,
		_calendar_instance_utime_calendar_book.original_event_id,
		_calendar_instance_utime_calendar_book.last_modified_time,
		_calendar_instance_utime_calendar_book.sync_data1,
	};
	ret = _set_projection(_calendar_instance_utime_calendar_book._uri, projection,
			sizeof(projection) / sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}

static int _set_projection_p_instance_localtime_calendar_book(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_event_localtime(&record_id);

	unsigned int projection[] = {
		_calendar_instance_localtime_calendar_book.event_id,
		_calendar_instance_localtime_calendar_book.start_time,
		_calendar_instance_localtime_calendar_book.end_time,
		_calendar_instance_localtime_calendar_book.summary,
		_calendar_instance_localtime_calendar_book.location,
		_calendar_instance_localtime_calendar_book.calendar_book_id,
		_calendar_instance_localtime_calendar_book.description,
		_calendar_instance_localtime_calendar_book.busy_status,
		_calendar_instance_localtime_calendar_book.event_status,
		_calendar_instance_localtime_calendar_book.priority,
		_calendar_instance_localtime_calendar_book.sensitivity,
		_calendar_instance_localtime_calendar_book.has_rrule,
		_calendar_instance_localtime_calendar_book.latitude,
		_calendar_instance_localtime_calendar_book.longitude,
		_calendar_instance_localtime_calendar_book.has_alarm,
		_calendar_instance_localtime_calendar_book.original_event_id,
		_calendar_instance_localtime_calendar_book.last_modified_time,
		_calendar_instance_localtime_calendar_book.sync_data1,
		_calendar_instance_localtime_calendar_book.is_allday,

	};
	ret = _set_projection(_calendar_instance_localtime_calendar_book._uri, projection,
			sizeof(projection)/sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}

static int _set_projection_p_instance_utime_calendar_book_extended(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_event_utime(&record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	unsigned int projection[] = {
		_calendar_instance_utime_calendar_book_extended.event_id,
		_calendar_instance_utime_calendar_book_extended.start_time,
		_calendar_instance_utime_calendar_book_extended.end_time,
		_calendar_instance_utime_calendar_book_extended.summary,
		_calendar_instance_utime_calendar_book_extended.location,
		_calendar_instance_utime_calendar_book_extended.calendar_book_id,
		_calendar_instance_utime_calendar_book_extended.description,
		_calendar_instance_utime_calendar_book_extended.busy_status,
		_calendar_instance_utime_calendar_book_extended.event_status,
		_calendar_instance_utime_calendar_book_extended.priority,
		_calendar_instance_utime_calendar_book_extended.sensitivity,
		_calendar_instance_utime_calendar_book_extended.has_rrule,
		_calendar_instance_utime_calendar_book_extended.latitude,
		_calendar_instance_utime_calendar_book_extended.longitude,
		_calendar_instance_utime_calendar_book_extended.has_alarm,
		_calendar_instance_utime_calendar_book_extended.original_event_id,
		_calendar_instance_utime_calendar_book_extended.last_modified_time,
		_calendar_instance_utime_calendar_book_extended.sync_data1,
	};
	ret = _set_projection(_calendar_instance_utime_calendar_book_extended._uri, projection,
			sizeof(projection) / sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}

static int _set_projection_p_instance_localtime_calendar_book_extended(void)
{
	int ret = 0;
	int record_id = 0;

	ret = _insert_event_localtime(&record_id);

	unsigned int projection[] = {
		_calendar_instance_localtime_calendar_book_extended.event_id,
		_calendar_instance_localtime_calendar_book_extended.start_time,
		_calendar_instance_localtime_calendar_book_extended.end_time,
		_calendar_instance_localtime_calendar_book_extended.summary,
		_calendar_instance_localtime_calendar_book_extended.location,
		_calendar_instance_localtime_calendar_book_extended.calendar_book_id,
		_calendar_instance_localtime_calendar_book_extended.description,
		_calendar_instance_localtime_calendar_book_extended.busy_status,
		_calendar_instance_localtime_calendar_book_extended.event_status,
		_calendar_instance_localtime_calendar_book_extended.priority,
		_calendar_instance_localtime_calendar_book_extended.sensitivity,
		_calendar_instance_localtime_calendar_book_extended.has_rrule,
		_calendar_instance_localtime_calendar_book_extended.latitude,
		_calendar_instance_localtime_calendar_book_extended.longitude,
		_calendar_instance_localtime_calendar_book_extended.has_alarm,
		_calendar_instance_localtime_calendar_book_extended.original_event_id,
		_calendar_instance_localtime_calendar_book_extended.last_modified_time,
		_calendar_instance_localtime_calendar_book_extended.sync_data1,
		_calendar_instance_localtime_calendar_book_extended.is_allday,

	};
	ret = _set_projection(_calendar_instance_localtime_calendar_book_extended._uri, projection,
			sizeof(projection)/sizeof(projection[0]));
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}

/**
 * @testcase		utc_calendar_query_set_projection_p
 * @since_tizen		2.3
 * @description		Test adding property IDs for projection.
 */
int utc_calendar_query_set_projection_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_set_projection(NULL, NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _set_projection_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_event_calendar_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_todo_calendar_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_instance_utime_calendar_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_instance_localtime_calendar_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_instance_utime_calendar_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _set_projection_p_instance_localtime_calendar_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_query_set_projection_n
 * @since_tizen		2.3
 * @description		Test fail adding property IDs for projection with invalid parameters.
 */
int utc_calendar_query_set_projection_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_set_projection(NULL, NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    calendar_query_h query = NULL;
    unsigned int projection[] = {
        _calendar_event.summary,
        _calendar_event.categories,
    };

	// case 1
    ret = calendar_query_set_projection(NULL, projection, sizeof(projection)/sizeof(int));
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
    ret = calendar_query_set_projection(query, NULL, sizeof(projection)/sizeof(int));
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
    ret = calendar_query_set_projection(query, projection, -1);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_query_set_distinct_p
 * @since_tizen		2.3
 * @description		Test setting the "distinct" option for projection.
 */
int utc_calendar_query_set_distinct_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_set_distinct(NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    calendar_query_h query = NULL;
    ret = calendar_query_create(_calendar_event._uri, &query);
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_query_set_distinct(query, true);
    assert_eq(ret, CALENDAR_ERROR_NONE);

    calendar_query_destroy(query);
	return 0;
}

/**
 * @testcase		utc_calendar_query_set_distinct_n
 * @since_tizen		2.3
 * @description		Test fail setting the "distinct" option for projection with invalid parameters.
 */
int utc_calendar_query_set_distinct_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_set_distinct(NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_query_set_distinct(NULL, true);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_query_set_filter_p
 * @since_tizen		2.3
 * @description		Test setting the filter for a query.
 */
int utc_calendar_query_set_filter_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_set_filter(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    calendar_query_h query = NULL;
    ret = calendar_query_create(_calendar_event._uri, &query);
    assert_eq(ret, CALENDAR_ERROR_NONE);

    calendar_filter_h filter = NULL;
    ret = calendar_filter_create(_calendar_event._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_filter_add_int(filter, _calendar_event.id, CALENDAR_MATCH_EQUAL, 3);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
		calendar_filter_destroy(filter);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_query_set_filter(query, filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
		calendar_filter_destroy(filter);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

    calendar_query_destroy(query);
    calendar_filter_destroy(filter);
	return 0;
}

/**
 * @testcase		utc_calendar_query_set_filter_n
 * @since_tizen		2.3
 * @description		Test fail setting the filter for a query with invalid parameters.
 */
int utc_calendar_query_set_filter_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_set_filter(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	calendar_filter_h filter = NULL;
    ret = calendar_query_set_filter(NULL, filter);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_query_h query = NULL;
    ret = calendar_query_set_filter(query, NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_query_set_sort_p
 * @since_tizen		2.3
 * @description		Test setting the sort mode for a query.
 */
int utc_calendar_query_set_sort_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_set_sort(NULL, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_query_h query = NULL;
    ret = calendar_query_create(_calendar_event._uri, &query);
    assert_eq(ret, CALENDAR_ERROR_NONE);

    calendar_filter_h filter = NULL;
    ret = calendar_filter_create(_calendar_event._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_filter_add_int(filter, _calendar_event.id, CALENDAR_MATCH_EQUAL, 3);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
		calendar_filter_destroy(filter);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_query_set_filter(query, filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
		calendar_filter_destroy(filter);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_query_set_sort(query, _calendar_event.start_time, true);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
		calendar_filter_destroy(filter);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

    calendar_filter_destroy(filter);
    calendar_query_destroy(query);
	return 0;
}

/**
 * @testcase		utc_calendar_query_set_sort_n
 * @since_tizen		2.3
 * @description		Test fail setting the sort mode for a query with invalid parameters.
 */
int utc_calendar_query_set_sort_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_query_set_sort(NULL, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_query_set_sort(NULL, _calendar_event.start_time, true);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}
