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
#include <stdio.h>
#include <calendar.h>

#include "utc-calendar-debug.h"
#include "utc-calendar-util.h"
#include "utc-calendar-record.h"
#include "utc-calendar-record-alarm.h"
#include "utc-calendar-record-attendee.h"
#include "utc-calendar-record-book.h"
#include "utc-calendar-record-event-book-attendee.h"
#include "utc-calendar-record-event-book.h"
#include "utc-calendar-record-event.h"
#include "utc-calendar-record-extended.h"
#include "utc-calendar-record-instance-localtime-book-extended.h"
#include "utc-calendar-record-instance-localtime-book.h"
#include "utc-calendar-record-instance-utime-book-extended.h"
#include "utc-calendar-record-instance-utime-book.h"
#include "utc-calendar-record-timezone.h"
#include "utc-calendar-record-todo-book.h"
#include "utc-calendar-record-todo.h"
#include "utc-calendar-record-updated-info.h"

static int g_startup_err = CALENDAR_ERROR_NONE;

/**
 * @function		utc_calendar_record_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_record_startup(void)
{
    g_startup_err = calendar_connect();
    if(g_startup_err != CALENDAR_ERROR_NONE) {
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
 * @function		utc_calendar_record_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_record_cleanup(void)
{
    calendar_disconnect();
}

/**
 * @testcase		utc_calendar_record_create_p
 * @since_tizen		2.3
 * @description		Test creating a record handle.
 */
int utc_calendar_record_create_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_create(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_create_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_p_updated_info();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_create_n
 * @since_tizen		2.3
 * @description		Test fail creating a record handle with invalid parameters.
 */
int utc_calendar_record_create_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_create(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_create_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_create_n_updated_info();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_p
 * @since_tizen		2.3
 * @description		Test destroying a record handle and releases all its resources.
 */
int utc_calendar_record_destroy_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_destroy(NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_destroy_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_p_updated_info();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_n
 * @since_tizen		2.3
 * @description		Test fail destroying a record handle and releases all its resources with invalid parameters.
 */
int utc_calendar_record_destroy_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_destroy(NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_destroy_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_destroy_n_updated_info();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_p
 * @since_tizen		2.3
 * @description		Test making a clone of a record handle.
 */
int utc_calendar_record_clone_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_destroy(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_clone_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_p_updated_info();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_n
 * @since_tizen		2.3
 * @description		Test fail making a clone of a record handle with invalid parameters.
 */
int utc_calendar_record_clone_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_destroy(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_clone_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_n_updated_info();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_p
 * @since_tizen		2.3
 * @description		Test getting a URI string from a record.
 */
int utc_calendar_record_get_uri_p_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_uri_p(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_uri_p_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_n
 * @since_tizen		2.3
 * @description		Test fail getting a URI string from a record with invalid parameters.
 */
int utc_calendar_record_get_uri_p_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_uri_p(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_uri_p_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_uri_p_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p
 * @since_tizen		2.3
 * @description		Test getting a string from a record.
 */
int utc_calendar_record_get_str_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_str(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_str_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_n
 * @since_tizen		2.3
 * @description		Test fail getting a string from a record with invalid parameters.
 */
int utc_calendar_record_get_str_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_str(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_str_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_p
 * @since_tizen		2.3
 * @description		Test getting a string pointer from a record.
 */
int utc_calendar_record_get_str_p_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_str_p(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_str_p_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_n
 * @since_tizen		2.3
 * @description		Test fail getting a string pointer from a record with invalid parameters.
 */
int utc_calendar_record_get_str_p_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_str_p(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_str_p_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_str_p_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_p
 * @since_tizen		2.3
 * @description		Test getting an integer value from a record.
 */
int utc_calendar_record_get_int_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_int(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_int_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_p_updated_info();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_n
 * @since_tizen		2.3
 * @description		Test fail getting an integer value from a record with invalid parameters.
 */
int utc_calendar_record_get_int_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_int(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_int_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_int_n_updated_info();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_p
 * @since_tizen		2.3
 * @description		Test getting a double value from a record.
 */
int utc_calendar_record_get_double_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_double(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_double_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_n
 * @since_tizen		2.3
 * @description		Test fail getting a double value from a record with invalid parameters.
 */
int utc_calendar_record_get_double_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_double(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_double_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_double_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_p
 * @since_tizen		2.3
 * @description		Test getting a long long integer value from a record.
 */
int utc_calendar_record_get_lli_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_lli(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_lli_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_n
 * @since_tizen		2.3
 * @description		Test fail getting a long long integer value from a record.
 */
int utc_calendar_record_get_lli_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_lli(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_lli_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_lli_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_p
 * @since_tizen		2.3
 * @description		Test getting a calendar_caltime_s value from a record.
 */
int utc_calendar_record_get_caltime_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_caltime(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_caltime_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_n
 * @since_tizen		2.3
 * @description		Test fail getting a calendar_caltime_s value from a record with invalid parameters.
 */
int utc_calendar_record_get_caltime_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_caltime(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_caltime_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_caltime_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_p
 * @since_tizen		2.3
 * @description		Test setting a string to a record.
 */
int utc_calendar_record_set_str_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_set_str(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_set_str_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_n
 * @since_tizen		2.3
 * @description		Test fail setting a string to a record with invalid parameters.
 */
int utc_calendar_record_set_str_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_set_str(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_set_str_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_str_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_p
 * @since_tizen		2.3
 * @description		Test setting an integer value to a record.
 */
int utc_calendar_record_set_int_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_set_int(NULL, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_set_int_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_n
 * @since_tizen		2.3
 * @description		Test fail setting an integer value to a record with invalid parameters.
 */
int utc_calendar_record_set_int_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_set_int(NULL, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_set_int_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_int_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_p
 * @since_tizen		2.3
 * @description		Test setting a double value to a record.
 */
int utc_calendar_record_set_double_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_set_double(NULL, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_set_double_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_n
 * @since_tizen		2.3
 * @description		Test fail setting a double value to a record with invalid parameters.
 */
int utc_calendar_record_set_double_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_set_double(NULL, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_set_double_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_double_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_p
 * @since_tizen		2.3
 * @description		Test setting a long long integer value to a record.
 */
int utc_calendar_record_set_lli_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_set_lli(NULL, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_set_lli_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_n
 * @since_tizen		2.3
 * @description		Test fail setting a long long integer value to a record with invalid parameters.
 */
int utc_calendar_record_set_lli_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_set_lli(NULL, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_set_lli_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_lli_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_p
 * @since_tizen		2.3
 * @description		Test setting a calendar_time_s value to a record.
 */
int utc_calendar_record_set_caltime_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		calendar_time_s t;
		ret = calendar_record_set_caltime(NULL, 0, t);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_set_caltime_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_n
 * @since_tizen		2.3
 * @description		Test fail setting a calendar_time_s value to a record with invalid parameters.
 */
int utc_calendar_record_set_caltime_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		calendar_time_s t;
		ret = calendar_record_set_caltime(NULL, 0, t);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_set_caltime_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_set_caltime_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_p
 * @since_tizen		2.3
 * @description		Test adding a child record to the parent record.
 */
int utc_calendar_record_add_child_record_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_add_child_record(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_add_child_record_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_n
 * @since_tizen		2.3
 * @description		Test fail adding a child record to the parent record with invalid parameters.
 */
int utc_calendar_record_add_child_record_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_add_child_record(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_add_child_record_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_add_child_record_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_p
 * @since_tizen		2.3
 * @description		Test removing a child record from the parent record.
 */
int utc_calendar_record_remove_child_record_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_remove_child_record(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_remove_child_record_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_n
 * @since_tizen		2.3
 * @description		Test fail removing a child record from the parent record with invalid parameters.
 */
int utc_calendar_record_remove_child_record_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_remove_child_record(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_remove_child_record_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_remove_child_record_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_p
 * @since_tizen		2.3
 * @description		Test getting the number of child records in a record.
 */
int utc_calendar_record_get_child_record_count_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_child_record_count(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_child_record_count_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_n
 * @since_tizen		2.3
 * @description		Test fail getting the number of child records in a record with invalid parameters.
 */
int utc_calendar_record_get_child_record_count_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_child_record_count(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_child_record_count_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_count_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_p
 * @since_tizen		2.3
 * @description		Test getting a child record handle pointer from the parent record.
 */
int utc_calendar_record_get_child_record_at_p_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_child_record_at_p(NULL, 0, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_child_record_at_p_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_n
 * @since_tizen		2.3
 * @description		Test fail getting a child record handle pointer from the parent record with invalid parameters.
 */
int utc_calendar_record_get_child_record_at_p_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_get_child_record_at_p(NULL, 0, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_get_child_record_at_p_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_get_child_record_at_p_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_p
 * @since_tizen		2.3
 * @description		Test making a clone of a given record's child record list.
 */
int utc_calendar_record_clone_child_record_list_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_clone_child_record_list(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_clone_child_record_list_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_n
 * @since_tizen		2.3
 * @description		Test fail making a clone of a given record's child record list with invalid parameters.
 */
int utc_calendar_record_clone_child_record_list_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_record_clone_child_record_list(NULL, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_record_clone_child_record_list_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_event_book_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_record_clone_child_record_list_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
