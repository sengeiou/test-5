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
#include <string.h>
#include <calendar.h>

#include "utc-calendar-debug.h"
#include "utc-calendar-util.h"
#include "utc-calendar-helper-event.h"
#include "utc-calendar-helper-alarm.h"
#include "utc-calendar-helper-attendee.h"
#include "utc-calendar-helper-exception.h"
#include "utc-calendar-helper-extended.h"

/**
 * @testcase		utc_calendar_record_create_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == event)
		assert_eq(-1, CALENDAR_ERROR_NONE);

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_create_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_n_event(void)
{
	int ret = 0;

	// case 1
	calendar_record_h event = NULL;
	ret = calendar_record_create(NULL, &event);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_create(_calendar_event._uri, NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_record_destroy(event, true);
    assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_n_event(void)
{
	int ret = 0;

    ret = calendar_record_destroy(NULL, true);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_p_event(void)
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

	// clone
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(event, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	// check
	ret = utc_calendar_helper_event_check_new(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(clone, true);
	}
	calendar_record_destroy(clone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_n_event(void)
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

	// case 1
	ret = calendar_record_clone(event, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(event, true);

	// case 2
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(NULL, &clone);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_uri_p_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	char *uri = NULL;
	ret = calendar_record_get_uri_p(event, &uri);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == uri || 0 != strcmp(uri, _calendar_event._uri)) {
		calendar_record_destroy(event, true);
		assert_eq(-1, CALENDAR_ERROR_NONE);
	}
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_uri_p_n_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_uri_p(event, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(event, true);

	// case 2
	char *uri = NULL;
	ret = calendar_record_get_uri_p(NULL, &uri);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new_str(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_event_check_new_str(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_n_event(void)
{
	int ret = 0;

	// case 1
	char *str = NULL;
	ret = calendar_record_get_str(NULL, _calendar_event.summary, &str);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_str(event, _calendar_event.summary, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new_str(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_event_check_new_str_p(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_n_event(void)
{
	int ret = 0;

	// case 1
	char *str = NULL;
	ret = calendar_record_get_str_p(NULL, _calendar_event.summary, &str);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_str_p(event, _calendar_event.summary, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new_int(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_event_check_new_int(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_n_event(void)
{
	int ret = 0;

	// case 1
	int i = 0;
	ret = calendar_record_get_int(NULL, _calendar_event.calendar_book_id, &i);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_int(event, _calendar_event.calendar_book_id, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_double_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new_double(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_event_check_new_double(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_double_n_event(void)
{
	int ret = 0;

	// case 1
	double d = 0.0;
	ret = calendar_record_get_double(NULL, _calendar_event.latitude, &d);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_double(event, _calendar_event.latitude, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_lli_p_event(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_lli_n_event(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_caltime_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new_caltime(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_event_check_new_caltime(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_caltime_n_event(void)
{
	int ret = 0;

	// case 1
	calendar_time_s ct = {0};
	ret = calendar_record_get_caltime(NULL, _calendar_event.until_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(event, _calendar_event.until_time, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_str_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_event_set_new_str(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_event_check_new_str_p(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_str_n_event(void)
{
	int ret = 0;
	ret = calendar_record_set_str(NULL, _calendar_event.summary, UTC_STR_NEW_SUMMARY);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_int_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_event_set_new_int(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_event_check_new_int(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_int_n_event(void)
{
	int ret = 0;
	ret = calendar_record_set_int(NULL, _calendar_event.calendar_book_id, UTC_INT_NEW_EVENT_CALENDAR_BOOK_ID);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_double_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_event_set_new_double(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_event_check_new_double(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_double_n_event(void)
{
	int ret = 0;
	ret = calendar_record_set_double(NULL, _calendar_event.latitude, UTC_DOUBLE_NEW_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_lli_p_event(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_lli_n_event(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_caltime_p_event(void)
{
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new_caltime(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_event_check_new_caltime(event);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_caltime_n_event(void)
{
	int ret = 0;

	calendar_time_s ct = {0};
	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_NEW_END_UTIME;
	ret = calendar_record_set_caltime(NULL, _calendar_event.until_time, ct);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_add_child_record_p_event(void)
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

	// check
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.calendar_alarm, 0, &alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_alarm_check_new(alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
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

	// check
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.calendar_attendee, 0, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_attendee_check_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// exception
	calendar_record_h exception = NULL;
	ret = calendar_record_create(_calendar_event._uri, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_exception_set_new(exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.exception, 0, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_exception_check_new(exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
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

	// check
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.extended, 0, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_check_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_add_child_record_n_event(void)
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
	// case 1
	ret = calendar_record_add_child_record(NULL, _calendar_event.calendar_alarm, alarm);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(alarm, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(alarm, true);
	// case 2
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_alarm, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// attendee
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_add_child_record(NULL, _calendar_event.calendar_attendee, attendee);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(attendee, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(attendee, true);
	// case 2
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_attendee, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// exception
	calendar_record_h exception = NULL;
	ret = calendar_record_create(_calendar_event._uri, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_add_child_record(NULL, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(exception, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(exception, true);
	// case 2
	ret = calendar_record_add_child_record(event, _calendar_event.exception, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_add_child_record(NULL, _calendar_event.extended, extended);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(extended, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(extended, true);
	// case 2
	ret = calendar_record_add_child_record(event, _calendar_event.extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_remove_child_record_p_event(void)
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
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(alarm, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// remove
	ret = calendar_record_remove_child_record(event, _calendar_event.calendar_alarm, alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// remove
	ret = calendar_record_remove_child_record(event, _calendar_event.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// exception
	calendar_record_h exception = NULL;
	ret = calendar_record_create(_calendar_event._uri, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// remove
	ret = calendar_record_remove_child_record(event, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// remove
	ret = calendar_record_remove_child_record(event, _calendar_event.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_remove_child_record_n_event(void)
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
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(alarm, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_remove_child_record(NULL, _calendar_event.calendar_alarm, alarm);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	// case 2
	ret = calendar_record_remove_child_record(event, _calendar_event.calendar_alarm, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_remove_child_record(NULL, _calendar_event.calendar_attendee, attendee);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	// case 2
	ret = calendar_record_remove_child_record(event, _calendar_event.calendar_attendee, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// exception
	calendar_record_h exception = NULL;
	ret = calendar_record_create(_calendar_event._uri, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_remove_child_record(NULL, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	// case 2
	ret = calendar_record_remove_child_record(event, _calendar_event.exception, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_remove_child_record(NULL, _calendar_event.extended, extended);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	// case 2
	ret = calendar_record_remove_child_record(event, _calendar_event.extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_count_p_event(void)
{
	int ret = 0;
	unsigned int count = 0;

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

	// get count
	ret = calendar_record_get_child_record_count(event, _calendar_event.calendar_alarm, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	if (1 != count) {
		calendar_record_destroy(event, true);
	}
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

	// get count
	ret = calendar_record_get_child_record_count(event, _calendar_event.calendar_attendee, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	if (1 != count) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// exception
	calendar_record_h exception = NULL;
	ret = calendar_record_create(_calendar_event._uri, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_exception_set_new(exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get count
	ret = calendar_record_get_child_record_count(event, _calendar_event.exception, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	if (1 != count) {
		calendar_record_destroy(event, true);
	}
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

	// get count
	ret = calendar_record_get_child_record_count(event, _calendar_event.extended, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	if (1 != count) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_count_n_event(void)
{
	int ret = 0;
	unsigned int count = 0;

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

	// case 1
	ret = calendar_record_get_child_record_count(NULL, _calendar_event.calendar_alarm, &count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_get_child_record_count(event, _calendar_event.calendar_alarm, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

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

	// case 1
	ret = calendar_record_get_child_record_count(NULL, _calendar_event.calendar_attendee, &count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_get_child_record_count(event, _calendar_event.calendar_attendee, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// exception
	calendar_record_h exception = NULL;
	ret = calendar_record_create(_calendar_event._uri, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_exception_set_new(exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_child_record_count(NULL, _calendar_event.exception, &count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_get_child_record_count(event, _calendar_event.exception, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

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

	// case 1
	ret = calendar_record_get_child_record_count(NULL, _calendar_event.extended, &count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_get_child_record_count(event, _calendar_event.extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_at_p_p_event(void)
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

	// check
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.calendar_alarm, 0, &alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_alarm_check_new(alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
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

	// check
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.calendar_attendee, 0, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_attendee_check_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// exception
	calendar_record_h exception = NULL;
	ret = calendar_record_create(_calendar_event._uri, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_exception_set_new(exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.exception, 0, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_exception_check_new(exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
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

	// check
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.extended, 0, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_check_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_at_p_n_event(void)
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

	ret = calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(alarm, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_get_child_record_at_p(NULL, _calendar_event.calendar_alarm, 0, &alarm);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	// case 2
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.calendar_alarm, 0, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_get_child_record_at_p(NULL, _calendar_event.calendar_attendee, 0, &attendee);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	// case 2
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.calendar_attendee, 0, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// exception
	calendar_record_h exception = NULL;
	ret = calendar_record_create(_calendar_event._uri, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_add_child_record(event, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_child_record_at_p(NULL, _calendar_event.exception, 0, &exception);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.exception, 0, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_add_child_record(event, _calendar_event.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_child_record_at_p(NULL, _calendar_event.extended, 0, &extended);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_get_child_record_at_p(event, _calendar_event.extended, 0, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_child_record_list_p_event(void)
{
	int ret = 0;
	calendar_list_h clone = NULL;

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

	ret = calendar_record_clone_child_record_list(event, _calendar_event.calendar_alarm, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_list_first(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_get_current_record_p(clone, &alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_alarm_check_new(alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(clone, true);
	clone = NULL;

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

	ret = calendar_record_clone_child_record_list(event, _calendar_event.calendar_attendee, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_list_first(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_get_current_record_p(clone, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_attendee_check_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(clone, true);
	clone = NULL;

	// exception
	calendar_record_h exception = NULL;
	ret = calendar_record_create(_calendar_event._uri, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_exception_set_new(exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_clone_child_record_list(event, _calendar_event.exception, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_list_first(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_get_current_record_p(clone, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_exception_check_new(exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(clone, true);
	clone = NULL;

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

	ret = calendar_record_clone_child_record_list(event, _calendar_event.extended, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_list_first(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_get_current_record_p(clone, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_check_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(clone, true);
	clone = NULL;

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_child_record_list_n_event(void)
{
	int ret = 0;
	calendar_list_h clone = NULL;

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
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(alarm, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_clone_child_record_list(NULL, _calendar_event.calendar_alarm, &clone);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_clone_child_record_list(event, _calendar_event.calendar_alarm, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_list_destroy(clone, true);
	clone = NULL;

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_clone_child_record_list(NULL, _calendar_event.calendar_attendee, &clone);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_clone_child_record_list(event, _calendar_event.calendar_attendee, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_list_destroy(clone, true);
	clone = NULL;

	// exception
	calendar_record_h exception = NULL;
	ret = calendar_record_create(_calendar_event._uri, &exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.exception, exception);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(exception, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_clone_child_record_list(NULL, _calendar_event.exception, &clone);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_clone_child_record_list(event, _calendar_event.exception, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_list_destroy(clone, true);
	clone = NULL;

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_clone_child_record_list(NULL, _calendar_event.extended, &clone);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_clone_child_record_list(event, _calendar_event.extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_list_destroy(clone, true);
	clone = NULL;

	calendar_record_destroy(event, true);
	return 0;
}
