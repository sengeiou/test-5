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
#include "utc-calendar-db.h"

static int g_startup_err = CALENDAR_ERROR_NONE;

/**
 * @function		utc_calendar_db_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_db_startup(void)
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
	_clean_db();
}

/**
 * @function		utc_calendar_db_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_db_cleanup(void)
{
	_clean_db();
	calendar_disconnect();
}

/**
 * @testcase		utc_calendar_db_insert_record_p
 * @since_tizen		2.3
 * @description		Test inserting a record into the calendar database.
 */
int utc_calendar_db_insert_record_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_insert_record(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_insert_record_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_record_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_record_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_record_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_record_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_record_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_record_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_record_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_record_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_record_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_record_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_record_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_record_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_record_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_record_n
 * @since_tizen		2.3
 * @description		Test fail inserting an invalid record into the calendar database with invalid parameters.
 */
int utc_calendar_db_insert_record_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_insert_record(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_insert_record_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_record_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_record_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_record_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_record_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_record_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_record_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_record_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_record_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_record_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_record_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_record_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_record_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_record_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_record_p
 * @since_tizen		2.3
 * @description		Test getting a record from the calendar database.
 */
int utc_calendar_db_get_record_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_record(NULL, 1, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_get_record_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_record_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_record_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_record_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_record_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_record_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_record_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_record_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_record_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_record_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_record_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_record_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_record_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_record_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_record_n
 * @since_tizen		2.3
 * @description		Test fail getting a record from the calendar database with invalid parameters.
 */
int utc_calendar_db_get_record_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_record(NULL, 1, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_record_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_record_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_record_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_record_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_record_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_record_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_record_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_record_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_record_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_record_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_record_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_record_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_record_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_record_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_record_p
 * @since_tizen		2.3
 * @description		Test updating a record in the calendar database.
 */
int utc_calendar_db_update_record_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_update_record(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_update_record_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_record_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_record_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_record_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_record_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_record_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_record_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_record_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_record_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_record_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_record_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_record_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_record_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_record_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_record_n
 * @since_tizen		2.3
 * @description		Test fail updating an invalid record in the calendar database.
 */
int utc_calendar_db_update_record_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_update_record(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_update_record_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_record_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_record_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_record_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_record_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_record_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_record_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_record_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_record_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_record_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_record_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_record_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_record_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_record_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_record_p
 * @since_tizen		2.3
 * @description		Test deleting a record from the calendar database with related child records.
 */
int utc_calendar_db_delete_record_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_delete_record(NULL, 1);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_delete_record_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_record_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_record_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_record_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_record_n
 * @since_tizen		2.3
 * @description		Test fail deleting a record from the calendar database with related child records with invalid parameters.
 */
int utc_calendar_db_delete_record_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_delete_record(NULL, 1);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_delete_record_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_record_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_record_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_record_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_record_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_all_records_p
 * @since_tizen		2.3
 * @description		Test retrieving all records as a list.
 */
int utc_calendar_db_get_all_records_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_all_records(NULL, 0, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_get_all_records_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_all_records_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_all_records_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_all_records_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_all_records_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_all_records_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_all_records_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_all_records_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_all_records_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_all_records_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_all_records_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_all_records_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_all_records_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_all_records_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_all_records_n
 * @since_tizen		2.3
 * @description		Test fail retrieving records as a list with invalid parameters.
 */
int utc_calendar_db_get_all_records_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_all_records(NULL, 0, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_all_records_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_all_records_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_all_records_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_all_records_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_all_records_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_all_records_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_all_records_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_all_records_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_all_records_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_all_records_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_all_records_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_all_records_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_all_records_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_all_records_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_records_with_query_p
 * @since_tizen		2.3
 * @description		Test retrieving records using a query handle.
 */
int utc_calendar_db_get_records_with_query_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_records_with_query(NULL, 0, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_records_with_query_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_records_with_query_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_records_with_query_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_records_with_query_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_records_with_query_n
 * @since_tizen		2.3
 * @description		Test fail retrieving records using a query handle with invalid parameters.
 */
int utc_calendar_db_get_records_with_query_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_records_with_query(NULL, 0, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_records_with_query_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_records_with_query_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_records_with_query_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_records_with_query_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_records_with_query_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_records_with_query_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_records_with_query_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_records_with_query_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_records_with_query_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_records_with_query_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_records_with_query_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_records_with_query_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_records_with_query_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_records_with_query_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_p
 * @since_tizen		2.3
 * @description		Test getting the record count of a specific view.
 */
int utc_calendar_db_get_count_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_count(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_get_count_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_count_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_count_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_count_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_n
 * @since_tizen		2.3
 * @description		Test fail getting the record count with invalid parameters.
 */
int utc_calendar_db_get_count_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_count(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_count_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_count_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_count_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_count_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_with_query_p
 * @since_tizen		2.3
 * @description		Test getting the record count with a query handle.
 */
int utc_calendar_db_get_count_with_query_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_count_with_query(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_event_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_todo_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_count_with_query_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_get_count_with_query_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_with_query_n
 * @since_tizen		2.3
 * @description		Test fail getting the record count with a query handle with invalid parameters.
 */
int utc_calendar_db_get_count_with_query_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_count_with_query(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_count_with_query_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_with_query_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_with_query_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_with_query_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_with_query_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_with_query_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_with_query_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_count_with_query_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_count_with_query_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_count_with_query_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_with_query_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_with_query_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_with_query_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_count_with_query_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_records_p
 * @since_tizen		2.3
 * @description		Test inserting multiple records into the calendar database as a batch operation.
 */
int utc_calendar_db_insert_records_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_insert_records(NULL, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_insert_records_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_records_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_records_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_records_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_records_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_records_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_records_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_records_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_records_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_records_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_records_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_records_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_records_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_records_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_records_n
 * @since_tizen		2.3
 * @description		Test fail inserting multiple records into the calendar database as a batch operation with invalid parameters.
 */
int utc_calendar_db_insert_records_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_insert_records(NULL, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_insert_records_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_records_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_records_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_records_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_records_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_records_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_records_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_records_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_records_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_records_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_records_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_records_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_records_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_records_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_records_p
 * @since_tizen		2.3
 * @description		Test updating multiple records into the calendar database as a batch operation.
 */
int utc_calendar_db_update_records_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_update_records(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_update_records_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_records_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_records_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_records_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_records_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_records_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_records_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_records_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_records_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_records_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_records_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_records_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_records_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_update_records_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_records_n
 * @since_tizen		2.3
 * @description		Test fail updating multiple records into the calendar database as a batch operation with invalid parameters.
 */
int utc_calendar_db_update_records_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_update_records(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_update_records_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_records_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_records_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_records_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_records_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_records_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_records_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_records_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_records_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_update_records_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_records_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_records_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_records_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_update_records_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_records_p
 * @since_tizen		2.3
 * @description		Test deleting multiple records with related child records from the calendar database as a batch operation.
 */
int utc_calendar_db_delete_records_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_delete_records(NULL, NULL, 1);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_delete_records_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_records_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_records_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_records_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_records_n
 * @since_tizen		2.3
 * @description		Test fail deleting multiple records with related child records from the calendar database as a batch operation with invalid parameters.
 */
int utc_calendar_db_delete_records_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_delete_records(NULL, NULL, 1);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_delete_records_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_records_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_records_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_delete_records_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_delete_records_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_current_version_p
 * @since_tizen		2.3
 * @description		Test updating multiple records into the calendar database as a batch operation.
 */
int utc_calendar_db_get_current_version_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_current_version(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_current_version_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_current_version_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_current_version_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_current_version_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_current_version_n
 * @since_tizen		2.3
 * @description		Test fail updating multiple records into the calendar database as a batch operation with invalid parameters.
 */
int utc_calendar_db_get_current_version_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_current_version(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_current_version_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_current_version_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_current_version_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_current_version_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_current_version_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_add_changed_cb_p
 * @since_tizen		2.3
 * @description		Test registering a callback function to be invoked when a record changes.
 */
int utc_calendar_db_add_changed_cb_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_add_changed_cb(NULL, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_add_changed_cb_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_add_changed_cb_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_add_changed_cb_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_add_changed_cb_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_add_changed_cb_n
 * @since_tizen		2.3
 * @description		Test fail registering a callback function with invalid parameters.
 */
int utc_calendar_db_add_changed_cb_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_add_changed_cb(NULL, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_add_changed_cb_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_add_changed_cb_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_add_changed_cb_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_add_changed_cb_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_add_changed_cb_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_remove_changed_cb_p
 * @since_tizen		2.3
 * @description		Test unregistering a callback function.
 */
int utc_calendar_db_remove_changed_cb_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_remove_changed_cb(NULL, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_remove_changed_cb_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_remove_changed_cb_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_remove_changed_cb_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_remove_changed_cb_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_remove_changed_cb_n
 * @since_tizen		2.3
 * @description		Test fail unregistering a callback function with invalid parameters.
 */
int utc_calendar_db_remove_changed_cb_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_remove_changed_cb(NULL, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_remove_changed_cb_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_remove_changed_cb_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_remove_changed_cb_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_remove_changed_cb_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_remove_changed_cb_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_by_version_p
 * @since_tizen		2.3
 * @description		Test retrieving records with the given calendar database version.
 */
int utc_calendar_db_get_changes_by_version_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_changes_by_version(NULL, 0, 0, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_changes_by_version_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_by_version_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_by_version_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_by_version_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_by_version_n
 * @since_tizen		2.3
 * @description		Test fail retrieving records with invalid parameters.
 */
int utc_calendar_db_get_changes_by_version_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_changes_by_version(NULL, 0, 0, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_changes_by_version_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_by_version_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_by_version_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_by_version_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_by_version_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_vcalendars_p
 * @since_tizen		2.3
 * @description		Test inserting a vcalendar stream into the calendar database.
 */
int utc_calendar_db_insert_vcalendars_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_insert_vcalendars(NULL, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_vcalendars_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_vcalendars_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_vcalendars_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_insert_vcalendars_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_vcalendars_n
 * @since_tizen		2.3
 * @description		Test fail inserting a vcalendar stream into the calendar database with invalid parameters.
 */
int utc_calendar_db_insert_vcalendars_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_insert_vcalendars(NULL, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_insert_vcalendars_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_vcalendars_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_vcalendars_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_vcalendars_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_vcalendars_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_vcalendars_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_vcalendars_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_vcalendars_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_vcalendars_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_insert_vcalendars_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_vcalendars_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_vcalendars_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_vcalendars_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_insert_vcalendars_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_vcalendars_p
 * @since_tizen		2.3
 * @description		Test replacing a vcalendar stream in the calendar database.
 */
int utc_calendar_db_replace_vcalendars_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_replace_vcalendars(NULL, NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_vcalendars_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_vcalendars_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_vcalendars_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_vcalendars_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_vcalendars_n
 * @since_tizen		2.3
 * @description		Test fail replacing a vcalendar stream in the calendar database with invalid parameters.
 */
int utc_calendar_db_replace_vcalendars_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_replace_vcalendars(NULL, NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_replace_vcalendars_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_vcalendars_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_vcalendars_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_vcalendars_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_vcalendars_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_vcalendars_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_vcalendars_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_vcalendars_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_vcalendars_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_vcalendars_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_vcalendars_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_vcalendars_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_vcalendars_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_vcalendars_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_record_p
 * @since_tizen		2.3
 * @description		Test replacing a record in the calendar database.
 */
int utc_calendar_db_replace_record_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_replace_record(NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_replace_record_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_record_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_record_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_record_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_record_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_record_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_record_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_record_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_record_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_record_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_record_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_record_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_record_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_record_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_record_n
 * @since_tizen		2.3
 * @description		Test fail replacing a record in the calendar database with invalid parameters.
 */
int utc_calendar_db_replace_record_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_replace_record(NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_replace_record_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_record_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_record_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_record_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_record_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_record_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_record_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_record_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_record_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_record_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_record_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_record_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_record_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_record_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_records_p
 * @since_tizen		2.3
 * @description		Test replacing multiple records in the calendar database as a batch operation.
 */
int utc_calendar_db_replace_records_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_replace_records(NULL, NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_clean_db();
	ret = utc_calendar_db_replace_records_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_records_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_records_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_records_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_records_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_records_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_records_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_records_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_records_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_records_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_records_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_records_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_records_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	_clean_db();
	ret = utc_calendar_db_replace_records_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_records_n
 * @since_tizen		2.3
 * @description		Test fail replacing multiple records in the calendar database as a batch operation with invalid parameters
 */
int utc_calendar_db_replace_records_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_replace_records(NULL, NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_replace_records_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_records_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_records_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_records_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_records_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_records_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_records_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_records_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_records_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_replace_records_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_records_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_records_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_records_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_replace_records_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_last_change_version_p
 * @since_tizen		2.3
 * @description		Test getting the last successful change version of the database on the current connection.
 */
int utc_calendar_db_get_last_change_version_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_last_change_version(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_last_change_version_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_last_change_version_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_last_change_version_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_last_change_version_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_last_change_version_n
 * @since_tizen		2.3
 * @description		Test fail getting the last successful change version of the database on the current connection with invalid parameters.
 */
int utc_calendar_db_get_last_change_version_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_last_change_version(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_last_change_version_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_last_change_version_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_last_change_version_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_last_change_version_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_last_change_version_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_exception_by_version_p
 * @since_tizen		2.3
 * @description		Test retrieving changed exception records since the given calendar database version.
 *                  Exceptions are the modified or deleted instances in a recurring event.
 */
int utc_calendar_db_get_changes_exception_by_version_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_changes_exception_by_version(NULL, 0, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_changes_exception_by_version_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_exception_by_version_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_exception_by_version_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_exception_by_version_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_exception_by_version_n
 * @since_tizen		2.3
 * @description		Test fail retrieving changed exception records with invalid parameters.
 */
int utc_calendar_db_get_changes_exception_by_version_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_get_changes_exception_by_version(NULL, 0, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_get_changes_exception_by_version_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_exception_by_version_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_exception_by_version_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_get_changes_exception_by_version_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_get_changes_exception_by_version_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_clean_after_sync_p
 * @since_tizen		2.3
 * @description		Test cleaning the data after sync.
 */
int utc_calendar_db_clean_after_sync_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_clean_after_sync(0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_clean_after_sync_p_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_p_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_p_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_p_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_p_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_p_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_p_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_clean_after_sync_p_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_clean_after_sync_p_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_clean_after_sync_p_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_p_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_p_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_p_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_p_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_clean_after_sync_n
 * @since_tizen		2.3
 * @description		Test fail cleaning the data with invalid parameters after sync.
 */
int utc_calendar_db_clean_after_sync_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_clean_after_sync(0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_clean_after_sync_n_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_n_event();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_n_todo();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_n_timezone();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_n_alarm();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_n_attendee();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_n_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_clean_after_sync_n_event_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_clean_after_sync_n_todo_book();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	//ret = utc_calendar_db_clean_after_sync_n_event_book_attendee();
	//assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_n_instance_utime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_n_instance_utime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_n_instance_localtime_book();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_db_clean_after_sync_n_instance_localtime_book_extended();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_link_record_p
 * @since_tizen		4.0
 * @description		Test
 */
int utc_calendar_db_link_record_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_clean_after_sync(0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_link_record_p_event();
	if (false == _is_feature_supported()) {
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, CALENDAR_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_calendar_db_link_record_n
 * @since_tizen		4.0
 * @description		Test
 */
int utc_calendar_db_link_record_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_clean_after_sync(0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_link_record_n_event();
	if (false == _is_feature_supported()) {
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, CALENDAR_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_calendar_db_unlink_record_p
 * @since_tizen		4.0
 * @description		Test
 */
int utc_calendar_db_unlink_record_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_clean_after_sync(0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_unlink_record_p_event();
	if (false == _is_feature_supported()) {
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, CALENDAR_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_calendar_db_unlink_record_n
 * @since_tizen		4.0
 * @description		Test
 */
int utc_calendar_db_unlink_record_n(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_db_clean_after_sync(0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = utc_calendar_db_unlink_record_n_event();
	if (false == _is_feature_supported()) {
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, CALENDAR_ERROR_NONE);
	}
	return 0;
}

