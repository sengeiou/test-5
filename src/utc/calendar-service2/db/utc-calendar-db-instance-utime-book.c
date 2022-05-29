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
#include "utc-calendar-helper-event.h"
#include "utc-calendar-helper-instance-utime-book.h"

static int g_startup_err = CALENDAR_ERROR_NONE;

/**
 * @testcase		utc_calendar_db_insert_record_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_record_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_record_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_record_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_record_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_record_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_record_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_record_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_record_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_record_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_record_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_record_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_record_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_record_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_record_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_record_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_all_records_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_all_records_p_instance_utime_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// get_all
	int offset = 0, limit = 0;
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_all_records(_calendar_instance_utime_calendar_book._uri, offset, limit, &get_list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_list_first(get_list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_get_current_record_p(get_list, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_instance_utime_book_check_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_list_destroy(get_list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_all_records_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_all_records_n_instance_utime_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	int offset = 0, limit = 0;
	ret = calendar_db_get_all_records(_calendar_instance_utime_calendar_book._uri, offset, limit, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_all_records(NULL, offset, limit, &get_list);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_records_with_query_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_records_with_query_p_instance_utime_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// insert
	int record_id = 0;
	ret = calendar_db_insert_record(event, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	// make query
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_instance_utime_calendar_book._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_instance_utime_calendar_book._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_instance_utime_calendar_book.event_id, CALENDAR_MATCH_EQUAL, record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_query_set_filter(query, filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get records
	int offset = 0, limit = 0;
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_records_with_query(query, offset, limit, &get_list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_filter_destroy(filter);
	calendar_query_destroy(query);

	// check
	ret = calendar_list_first(get_list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h instance_utime_book = NULL;
	ret = calendar_list_get_current_record_p(get_list, &instance_utime_book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_instance_utime_book_check_new(instance_utime_book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(instance_utime_book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_list_destroy(get_list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_records_with_query_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_records_with_query_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_p_instance_utime_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// insert
	int record_id = 0;
	ret = calendar_db_insert_record(event, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	// get count
	int get_count = 0;
	ret = calendar_db_get_count(_calendar_instance_utime_calendar_book._uri, &get_count);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ASSERT_IF(UTC_INT_NEW_COUNT != get_count,
			"expected(%d): get(%d)", UTC_CALENDAR_INSERT_COUNT, get_count);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_n_instance_utime_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	ret = calendar_db_get_count(_calendar_instance_utime_calendar_book._uri, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	int get_count = 0;
	ret = calendar_db_get_count(NULL, &get_count);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_with_query_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_with_query_p_instance_utime_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// insert
	int record_id = 0;
	ret = calendar_db_insert_record(event, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	// query
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_instance_utime_calendar_book._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_instance_utime_calendar_book._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_instance_utime_calendar_book.event_id, CALENDAR_MATCH_EQUAL, record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_query_set_filter(query, filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get count
	int get_count = 0;
	ret = calendar_db_get_count_with_query(query, &get_count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_filter_destroy(filter);
	calendar_query_destroy(query);

	ASSERT_IF(UTC_INT_NEW_COUNT != get_count,
			"expected(%d): get(%d)", UTC_CALENDAR_INSERT_COUNT, get_count);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_with_query_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_with_query_n_instance_utime_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_instance_utime_calendar_book._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_db_get_count_with_query(query, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_query_destroy(query);

	// case 2
	int get_count = 0;
	ret = calendar_db_get_count_with_query(NULL, &get_count);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_records_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_records_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_records_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_records_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_records_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_records_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_records_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_records_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_records_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_records_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_records_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_records_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_current_version_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_current_version_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_current_version_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_current_version_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_add_changed_cb_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_add_changed_cb_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_add_changed_cb_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_add_changed_cb_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_remove_changed_cb_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_remove_changed_cb_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_remove_changed_cb_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_remove_changed_cb_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_by_version_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_by_version_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_by_version_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_by_version_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_vcalendars_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_vcalendars_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_vcalendars_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_vcalendars_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_vcalendars_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_vcalendars_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_vcalendars_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_vcalendars_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_record_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_record_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_record_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_record_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_records_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_records_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_records_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_records_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_last_change_version_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_last_change_version_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_last_change_version_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_last_change_version_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_exception_by_version_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_exception_by_version_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_exception_by_version_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_exception_by_version_n_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_clean_after_sync_p_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_clean_after_sync_p_instance_utime_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_clean_after_sync_n_instance_utime_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_clean_after_sync_n_instance_utime_book(void)
{
	return 0;
}
