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

static int g_startup_err = CALENDAR_ERROR_NONE;

/**
 * @function		utc_calendar_filter_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_filter_startup(void)
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
 * @function		utc_calendar_filter_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_filter_cleanup(void)
{
    calendar_disconnect();
}

/**
 * @testcase		utc_calendar_filter_create_p
 * @since_tizen		2.3
 * @description		Test creating a filter handle.
 */
int utc_calendar_filter_create_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_create(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == filter)
		assert_eq(-1, CALENDAR_ERROR_NONE);

	calendar_filter_destroy(filter);
	return 0;
}

/**
 * @testcase		utc_calendar_filter_create_n
 * @since_tizen		2.3
 * @description		Test fail creating a filter handle with invalid parameters.
 */
int utc_calendar_filter_create_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_create(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_filter_h filter = NULL;
	// case 1
	ret = calendar_filter_create(NULL, &filter);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_filter_create(_calendar_event._uri, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_filter_destroy_p
 * @since_tizen		2.3
 * @description		Test destroying a filter handle.
 */
int utc_calendar_filter_destroy_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_destroy(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_destroy(filter);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_filter_destroy_n
 * @since_tizen		2.3
 * @description		Test fail destroying a filter handle with invalid parameters.
 */
int utc_calendar_filter_destroy_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_destroy(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = calendar_filter_destroy(NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_str_p
 * @since_tizen		2.3
 * @description		Test adding a condition for the string type property.
 */
int utc_calendar_filter_add_str_p(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_str(NULL, 0, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

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

	// make query
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_event._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_str(filter, _calendar_event.summary,
			CALENDAR_MATCH_EXACTLY, "summary");
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_str(filter, _calendar_event.summary,
			CALENDAR_MATCH_FULLSTRING, "summary");
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_str(filter, _calendar_event.summary,
			CALENDAR_MATCH_CONTAINS, "summary");
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_str(filter, _calendar_event.summary,
			CALENDAR_MATCH_STARTSWITH, "summary");
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_str(filter, _calendar_event.summary,
			CALENDAR_MATCH_ENDSWITH, "summary");
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_str(filter, _calendar_event.summary,
			CALENDAR_MATCH_EXISTS, "summary");
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
	calendar_list_destroy(get_list, true);

	/* delete */
	calendar_db_delete_record(_calendar_event._uri, record_id);

	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_str_n
 * @since_tizen		2.3
 * @description		Test fail adding a condition for the string type property with invalid parameters.
 */
int utc_calendar_filter_add_str_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_str(NULL, 0, 0, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	ret = calendar_filter_add_str(NULL, _calendar_event.summary, CALENDAR_MATCH_CONTAINS, UTC_STR_NEW_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_filter_h filter = NULL;
	unsigned int property_id = -1;
	ret = calendar_filter_add_str(filter, property_id, CALENDAR_MATCH_CONTAINS, UTC_STR_NEW_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	int match_flag = 100;
	ret = calendar_filter_add_str(filter, _calendar_event.summary, match_flag, UTC_STR_NEW_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 4
	ret = calendar_filter_add_str(filter, _calendar_event.summary, CALENDAR_MATCH_CONTAINS, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_int_p
 * @since_tizen		2.3
 * @description		Test adding a condition for the integer type property.
 */
int utc_calendar_filter_add_int_p(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_int(NULL, 0, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

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

	// make query
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_event._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_event.calendar_book_id,
			CALENDAR_MATCH_EQUAL, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_event.calendar_book_id,
			CALENDAR_MATCH_GREATER_THAN, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_event.calendar_book_id,
			CALENDAR_MATCH_GREATER_THAN_OR_EQUAL, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_event.calendar_book_id,
			CALENDAR_MATCH_LESS_THAN, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_event.calendar_book_id,
			CALENDAR_MATCH_LESS_THAN_OR_EQUAL, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_event.calendar_book_id,
			CALENDAR_MATCH_NOT_EQUAL, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_event.calendar_book_id,
			CALENDAR_MATCH_NONE, DEFAULT_EVENT_CALENDAR_BOOK_ID);
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
	calendar_list_destroy(get_list, true);

	/* delete */
	calendar_db_delete_record(_calendar_event._uri, record_id);

	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_int_n
 * @since_tizen		2.3
 * @description		Test fail adding a condition for the integer type property with invalid parameters.
 */
int utc_calendar_filter_add_int_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_int(NULL, 0, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	ret = calendar_filter_add_int(NULL, _calendar_event.calendar_book_id, CALENDAR_MATCH_GREATER_THAN, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_filter_h filter = NULL;
	unsigned int property_id = -1;
	ret = calendar_filter_add_int(filter, property_id, CALENDAR_MATCH_GREATER_THAN, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	int match_flag = 100;
	ret = calendar_filter_add_int(filter, _calendar_event.calendar_book_id, match_flag, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_double_p
 * @since_tizen		2.3
 * @description		Test adding a condition for the double type property.
 */
int utc_calendar_filter_add_double_p(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_double(NULL, 0, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

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

	// make query
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_event._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_double(filter, _calendar_event.latitude,
			CALENDAR_MATCH_EQUAL, 0.1);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_double(filter, _calendar_event.latitude,
			CALENDAR_MATCH_GREATER_THAN, 0.1);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_double(filter, _calendar_event.latitude,
			CALENDAR_MATCH_GREATER_THAN_OR_EQUAL, 0.1);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_double(filter, _calendar_event.latitude,
			CALENDAR_MATCH_LESS_THAN, 0.1);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_double(filter, _calendar_event.latitude,
			CALENDAR_MATCH_LESS_THAN_OR_EQUAL, 0.1);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_double(filter, _calendar_event.latitude,
			CALENDAR_MATCH_NOT_EQUAL, 0.1);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_double(filter, _calendar_event.latitude,
			CALENDAR_MATCH_NONE, 0.1);
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
	calendar_list_destroy(get_list, true);

	/* delete */
	calendar_db_delete_record(_calendar_event._uri, record_id);

	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_double_n
 * @since_tizen		2.3
 * @description		Test fail adding a condition for the double type property with invalid parameters.
 */
int utc_calendar_filter_add_double_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_double(NULL, 0, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	ret = calendar_filter_add_double(NULL, _calendar_event.latitude, CALENDAR_MATCH_CONTAINS, UTC_DOUBLE_NEW_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_filter_h filter = NULL;
	unsigned int property_id = -1;
	ret = calendar_filter_add_double(filter, property_id, CALENDAR_MATCH_CONTAINS, UTC_DOUBLE_NEW_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	int match_flag = 100;
	ret = calendar_filter_add_double(filter, _calendar_event.latitude, match_flag, UTC_DOUBLE_NEW_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_lli_p
 * @since_tizen		2.3
 * @description		Test adding a condition for the long long int type property.
 */
int utc_calendar_filter_add_lli_p(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_lli(NULL, 0, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

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

	// make query
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_event._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_lli(filter, _calendar_event.created_time,
			CALENDAR_MATCH_EQUAL, 0);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_lli(filter, _calendar_event.created_time,
			CALENDAR_MATCH_GREATER_THAN, 0);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_lli(filter, _calendar_event.created_time,
			CALENDAR_MATCH_GREATER_THAN_OR_EQUAL, 0);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_lli(filter, _calendar_event.created_time,
			CALENDAR_MATCH_LESS_THAN, 0);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_lli(filter, _calendar_event.created_time,
			CALENDAR_MATCH_LESS_THAN_OR_EQUAL, 0);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_lli(filter, _calendar_event.created_time,
			CALENDAR_MATCH_NOT_EQUAL, 0);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_lli(filter, _calendar_event.created_time,
			CALENDAR_MATCH_NONE, 0);
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
	calendar_list_destroy(get_list, true);

	/* delete */
	calendar_db_delete_record(_calendar_event._uri, record_id);

	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_lli_n
 * @since_tizen		2.3
 * @description		Test fail adding a condition for the long long int type property with invalid parameters.
 */
int utc_calendar_filter_add_lli_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_lli(NULL, 0, 0, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	ret = calendar_filter_add_lli(NULL, _calendar_event.created_time, CALENDAR_MATCH_GREATER_THAN, 0);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_filter_h filter = NULL;
	unsigned int property_id = -1;
	ret = calendar_filter_add_lli(filter, property_id, CALENDAR_MATCH_GREATER_THAN, 0);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	int match_flag = 100;
	ret = calendar_filter_add_lli(filter, _calendar_event.created_time, match_flag, 0);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_caltime_p
 * @since_tizen		2.3
 * @description		Test adding a condition for the calendar_time_s type property.
 */
int utc_calendar_filter_add_caltime_p(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		calendar_time_s t;
		ret = calendar_filter_add_caltime(NULL, 0, 0, t);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

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

	// make query
    calendar_time_s st = {0};

	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_event._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_caltime(filter, _calendar_event.start_time,
			CALENDAR_MATCH_EQUAL, st);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_caltime(filter, _calendar_event.start_time,
			CALENDAR_MATCH_GREATER_THAN, st);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_caltime(filter, _calendar_event.start_time,
			CALENDAR_MATCH_GREATER_THAN_OR_EQUAL, st);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_caltime(filter, _calendar_event.start_time,
			CALENDAR_MATCH_LESS_THAN, st);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_caltime(filter, _calendar_event.start_time,
			CALENDAR_MATCH_LESS_THAN_OR_EQUAL, st);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_caltime(filter, _calendar_event.start_time,
			CALENDAR_MATCH_NOT_EQUAL, st);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_OR);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_caltime(filter, _calendar_event.start_time,
			CALENDAR_MATCH_NONE, st);
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
	calendar_list_destroy(get_list, true);

	/* delete */
	calendar_db_delete_record(_calendar_event._uri, record_id);

	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_caltime_n
 * @since_tizen		2.3
 * @description		Test fail adding a condition for the calendar_time_s type property with invalid parameters.
 */
int utc_calendar_filter_add_caltime_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		calendar_time_s t;
		ret = calendar_filter_add_caltime(NULL, 0, 0, t);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	calendar_time_s st = {0};
	ret = calendar_filter_add_caltime(NULL, _calendar_event.start_time, CALENDAR_MATCH_GREATER_THAN, st);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_filter_h filter = NULL;
	unsigned int property_id = -1;
	ret = calendar_filter_add_caltime(filter, property_id, CALENDAR_MATCH_GREATER_THAN, st);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	int match_flag = 100;
	ret = calendar_filter_add_caltime(filter, _calendar_event.start_time, match_flag, st);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_filter_p
 * @since_tizen		2.3
 * @description		Test adding a child filter to a parent filter.
 */
int utc_calendar_filter_add_filter_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_filter(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter2 = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter2);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_filter(filter, filter2);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
		calendar_filter_destroy(filter2);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_destroy(filter);
	calendar_filter_destroy(filter2);
	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_filter_n
 * @since_tizen		2.3
 * @description		Test fail adding a child filter to a parent filter with invalid parameters.
 */
int utc_calendar_filter_add_filter_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_filter(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_filter_h filter = NULL;
	// case 1
	ret = calendar_filter_add_filter(NULL, filter);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_filter_add_filter(filter, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_operator_p
 * @since_tizen		2.3
 * @description		Test adding an operator between conditions.
 */
int utc_calendar_filter_add_operator_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_operator(NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_event.id, CALENDAR_MATCH_GREATER_THAN, 0);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_operator(filter, CALENDAR_FILTER_OPERATOR_AND);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_filter_destroy(filter);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_destroy(filter);
	return 0;
}

/**
 * @testcase		utc_calendar_filter_add_operator_n
 * @since_tizen		2.3
 * @description		Test adding an operator between conditions with invalid parameters.
 */
int utc_calendar_filter_add_operator_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_filter_add_operator(NULL, 0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	ret = calendar_filter_add_operator(NULL, CALENDAR_FILTER_OPERATOR_AND);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_filter_h filter = NULL;
	int operator_flag = 100;
	ret = calendar_filter_add_operator(filter, operator_flag);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	return 0;
}
