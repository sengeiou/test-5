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
#include <time.h>

#include "utc-calendar-debug.h"
#include "utc-calendar-util.h"
#include "utc-calendar-helper-event.h"

static int g_startup_err = CALENDAR_ERROR_NONE;

/**
 * @testcase		utc_calendar_db_insert_record_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_record_p_event(void)
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

	// check
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_record_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_record_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	ret = calendar_db_insert_record(NULL, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_record_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_record_p_event(void)
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

	// get
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_record_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_record_n_event(void)
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

	// case 1
	ret = calendar_db_get_record(NULL, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_get_record(_calendar_event._uri, record_id, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	record_id = -1;
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_record_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_record_p_event(void)
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

	// get to update
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// update
	ret = utc_calendar_helper_event_set_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_db_update_record(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	// get to check
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_record_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_record_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_update_record(NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_record_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_record_p_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int record_id = 0;
	ret = calendar_db_insert_record(event, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);

	// delete
	ret = calendar_db_delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	calendar_record_h get_event = NULL;
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &get_event);
	assert_eq(ret, CALENDAR_ERROR_DB_RECORD_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_record_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_record_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	int record_id = 1;
	ret = calendar_db_delete_record(NULL, record_id);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	record_id = -1;
	ret = calendar_db_delete_record(_calendar_event._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_all_records_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_all_records_p_event(void)
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

	// get all
	int offset = 0, limit = 0;
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_all_records(_calendar_event._uri, offset, limit, &get_list);
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

	ret = utc_calendar_helper_event_check_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_list_destroy(get_list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_all_records_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_all_records_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	int offset = 0, limit = 0;
	ret = calendar_db_get_all_records(_calendar_event._uri, offset, limit, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_all_records(NULL, offset, limit, &get_list);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_records_with_query_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_records_with_query_p_event(void)
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

	ret = calendar_filter_add_int(filter, _calendar_event.id, CALENDAR_MATCH_EQUAL, record_id);
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

	ret = utc_calendar_helper_event_check_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_list_destroy(get_list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_records_with_query_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_records_with_query_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	calendar_query_h query = NULL;
	int offset = 0, limit = 0;
	ret = calendar_db_get_records_with_query(query, offset, limit, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_records_with_query(NULL, offset, limit, &get_list);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_p_event(void)
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

	// get count
	int get_count = 0;
	ret = calendar_db_get_count(_calendar_event._uri, &get_count);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ASSERT_IF(UTC_CALENDAR_INSERT_COUNT != get_count,
			"expected(%d): get(%d)", UTC_CALENDAR_INSERT_COUNT, get_count);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	ret = calendar_db_get_count(_calendar_event._uri, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	int get_count = 0;
	ret = calendar_db_get_count(NULL, &get_count);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_with_query_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_with_query_p_event(void)
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

	// query
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_event._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_event._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_event.id, CALENDAR_MATCH_EQUAL, record_id);
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

	ASSERT_IF(UTC_CALENDAR_INSERT_COUNT != get_count,
			"expected(%d): get(%d)", UTC_CALENDAR_INSERT_COUNT, get_count);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_with_query_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_with_query_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_event._uri, &query);
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
 * @testcase		utc_calendar_db_insert_records_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_records_p_event(void)
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

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_records(list, &ids, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	int record_id = ids[0];
	free(ids);
	calendar_list_destroy(list, true);

	// check
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_records_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_records_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_records(NULL, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_records_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_records_p_event(void)
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

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_records(list, &ids, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	int record_id = ids[0];
	free(ids);
	calendar_list_destroy(list, true);

	// get to udpate
	int offset = 0, limit = 0;
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_all_records(_calendar_event._uri, offset, limit, &get_list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

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

	ret = utc_calendar_helper_event_set_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// update
	ret = calendar_db_update_records(get_list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(get_list, false);

	// check
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_records_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_records_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_update_records(NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_records_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_records_p_event(void)
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

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_records(list, &ids, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(list, true);

	// delete
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	if (CALENDAR_ERROR_NONE != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	int record_id = ids[0];
	free(ids);

	// check
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_DB_RECORD_NOT_FOUND);

	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_records_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_records_n_event(void)
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

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_records(list, &ids, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(list, true);

	// case 1
	ret = calendar_db_delete_records(NULL, ids, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_delete_records(_calendar_event._uri, NULL, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	count = -1;
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_calendar_db_get_current_version_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_current_version_p_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int version = 0;
	ret = calendar_db_get_current_version(&version);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_current_version_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_current_version_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_get_current_version(NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

static void __changed_cb_event(const char* view_uri, void* user_data)
{
}

/**
 * @testcase		utc_calendar_db_add_changed_cb_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_add_changed_cb_p_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_add_changed_cb(_calendar_event._uri, __changed_cb_event, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_add_changed_cb_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_add_changed_cb_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	ret = calendar_db_add_changed_cb(_calendar_event._uri, NULL, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_add_changed_cb(NULL, __changed_cb_event, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_remove_changed_cb_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_remove_changed_cb_p_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_remove_changed_cb(_calendar_event._uri, __changed_cb_event, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_remove_changed_cb_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_remove_changed_cb_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	ret = calendar_db_remove_changed_cb(_calendar_event._uri, NULL, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_remove_changed_cb(NULL, __changed_cb_event, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_by_version_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_by_version_p_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int event_id = 0;
	int last_version = 1;
	calendar_list_h list = NULL;
	int current_version = 0;
	ret = calendar_db_get_changes_by_version(_calendar_event._uri, event_id,
			last_version, &list, &current_version);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_list_destroy(list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_by_version_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_by_version_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int event_id = 0;
	int last_version = 1;
	calendar_list_h list = NULL;
	int current_version = 0;

	// case 1
	ret = calendar_db_get_changes_by_version(NULL, event_id,
			last_version, &list, &current_version);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_get_changes_by_version(_calendar_event._uri, event_id,
			last_version, NULL, &current_version);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	ret = calendar_db_get_changes_by_version(_calendar_event._uri, event_id,
			last_version, &list, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_vcalendars_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_vcalendars_p_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"PRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n"
		"BEGIN:VEVENT\r\n"
		"UID:19970610T172345Z-AF23B2@example.com\r\n"
		"DTSTAMP:19970610T172345Z\r\n"
		"SUMMARY:"UTC_STR_NEW_SUMMARY"\r\n"
		"DTSTART:"UTC_CALTIME_NEW_START_STRING"\r\n"
		"DTEND:"UTC_CALTIME_NEW_END_STRING"\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_vcalendars(stream, &ids, &count);
	free(ids);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	int offset = 0, limit = 0;
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_all_records(_calendar_event._uri, offset, limit, &get_list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_first(get_list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h get_event = NULL;
	ret = calendar_list_get_current_record_p(get_list, &get_event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	char *summary = NULL;
	ret = calendar_record_get_str_p(get_event, _calendar_event.summary, &summary);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	if (NULL == summary || 0 != strcmp(summary, UTC_STR_NEW_SUMMARY)) {
		calendar_list_destroy(get_list, true);
		assert_eq(-1, CALENDAR_ERROR_NONE);
	}
	calendar_list_destroy(get_list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_vcalendars_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_vcalendars_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_vcalendars(NULL, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_vcalendars_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_vcalendars_p_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"PRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n"
		"BEGIN:VEVENT\r\n"
		"UID:19970610T172345Z-AF23B2@example.com\r\n"
		"DTSTAMP:19970610T172345Z\r\n"
		"SUMMARY:"UTC_STR_NEW_SUMMARY"\r\n"
		"DTSTART:"UTC_CALTIME_NEW_START_STRING"\r\n"
		"DTEND:"UTC_CALTIME_NEW_END_STRING"\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_vcalendars(stream, &ids, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	const char *stream_mod = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"PRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n"
		"BEGIN:VEVENT\r\n"
		"UID:19970610T172345Z-AF23B2@example.com\r\n"
		"DTSTAMP:19970610T172345Z\r\n"
		"SUMMARY:"UTC_STR_MOD_SUMMARY"\r\n"
		"DTSTART:"UTC_CALTIME_MOD_START_STRING"\r\n"
		"DTEND:"UTC_CALTIME_MOD_END_STRING"\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";

	ret = calendar_db_replace_vcalendars(stream_mod, ids, count);
	free(ids);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	int offset = 0, limit = 0;
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_all_records(_calendar_event._uri, offset, limit, &get_list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_first(get_list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h get_event = NULL;
	ret = calendar_list_get_current_record_p(get_list, &get_event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	char *summary = NULL;
	ret = calendar_record_get_str_p(get_event, _calendar_event.summary, &summary);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	if (NULL == summary || 0 != strcmp(summary, UTC_STR_MOD_SUMMARY)) {
		calendar_list_destroy(get_list, true);
		assert_eq(-1, CALENDAR_ERROR_NONE);
	}
	calendar_list_destroy(get_list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_vcalendars_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_vcalendars_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"PRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n"
		"BEGIN:VEVENT\r\n"
		"UID:19970610T172345Z-AF23B2@example.com\r\n"
		"DTSTAMP:19970610T172345Z\r\n"
		"SUMMARY:"UTC_STR_NEW_SUMMARY"\r\n"
		"DTSTART:"UTC_CALTIME_NEW_START_STRING"\r\n"
		"DTEND:"UTC_CALTIME_NEW_END_STRING"\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_vcalendars(stream, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_db_replace_vcalendars(NULL, ids, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_replace_vcalendars(stream, NULL, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	count = -1;
	ret = calendar_db_replace_vcalendars(stream, ids, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	free(ids);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_record_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_record_p_event(void)
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

	// get to update
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// replace
	ret = calendar_db_replace_record(event, record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get to check
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_record_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_record_n_event(void)
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

	// case 1
	ret = calendar_db_replace_record(NULL, record_id);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	record_id = -1;
	ret = calendar_db_replace_record(event, record_id);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_records_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_records_p_event(void)
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

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_records(list, &ids, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	int record_id = ids[0];
	calendar_list_destroy(list, true);

	// get to udpate
	int offset = 0, limit = 0;
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_all_records(_calendar_event._uri, offset, limit, &get_list);
	if (CALENDAR_ERROR_NONE != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_first(get_list);
	if (CALENDAR_ERROR_NONE != ret) {
		free(ids);
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_get_current_record_p(get_list, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		free(ids);
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		free(ids);
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// replace
	ret = calendar_db_replace_records(get_list, ids, count);
	if (CALENDAR_ERROR_NONE != ret) {
		free(ids);
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_db_get_record(_calendar_event._uri, record_id, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(event, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_records_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_records_n_event(void)
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

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int *ids = NULL;
	int count = 0;
	ret = calendar_db_insert_records(list, &ids, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_db_replace_records(NULL, ids, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_replace_records(list, NULL, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	count = -1;
	ret = calendar_db_replace_records(list, ids, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	free(ids);
	calendar_list_destroy(list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_last_change_version_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_last_change_version_p_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int version = 0;
	ret = calendar_db_get_last_change_version(&version);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_last_change_version_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_last_change_version_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_get_last_change_version(NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_exception_by_version_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_exception_by_version_p_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int original_event_id = 1;
	int version = 1;
	calendar_list_h list = NULL;
	ret = calendar_db_get_changes_exception_by_version(_calendar_event._uri, original_event_id, version, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_list_destroy(list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_exception_by_version_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_exception_by_version_n_event(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int record_id = 1;
	int version = 1;
	calendar_list_h list = NULL;

	// case 1
	ret = calendar_db_get_changes_exception_by_version(NULL, record_id, version, &list);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_get_changes_exception_by_version(_calendar_event._uri, record_id, version, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_clean_after_sync_p_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_clean_after_sync_p_event(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_clean_after_sync_n_event
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_clean_after_sync_n_event(void)
{
	return 0;
}

static int _add_record(time_t tm, char *summary, int alarm_sec, int *out_id)
{
	calendar_record_h event = NULL;
	calendar_record_h alarm = NULL;
	calendar_time_s st = {0};
	calendar_time_s et = {0};
	calendar_time_s at = {0};

	int ret;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	st.type = CALENDAR_TIME_UTIME;
	st.time.utime = tm;
	calendar_record_set_caltime(event, _calendar_event.start_time, st);
	et.type = CALENDAR_TIME_UTIME;
	et.time.utime = tm + 3600;
	calendar_record_set_caltime(event, _calendar_event.end_time, et);
	calendar_record_set_str(event, _calendar_event.summary, summary);

	/* alarm */
	ret = calendar_record_create(_calendar_alarm._uri, &alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_set_int(alarm, _calendar_alarm.tick_unit, CALENDAR_ALARM_TIME_UNIT_SPECIFIC);
	at.type = CALENDAR_TIME_UTIME;
	at.time.utime = tm + alarm_sec;
	calendar_record_set_caltime(alarm, _calendar_alarm.alarm_time, at);
	calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);

	int id = 0;
	calendar_db_insert_record(event, &id);
	DBG("id(%d)", id);
	*out_id = id;
	return 0;
}

UTC_HIDDEN int utc_calendar_db_link_record_p_event(void)
{
	calendar_connect();

	int base_id = 0;
	int linked1_id = 0;
	int linked2_id = 0;
	int new_id = 0;
	time_t tm = time(NULL);

	// case 1
	_add_record(tm, "base", 5, &base_id);

	_add_record(tm, "base", 7, &linked1_id);
	calendar_db_link_record(base_id, linked1_id);

	_add_record(tm, "base", 9, &linked2_id);
	calendar_db_link_record(base_id, linked2_id);

	sleep(1);

	_add_record(tm, "base", 11, &base_id);
	calendar_db_link_record(new_id, base_id);

	// case 2
	_add_record(tm, "base", 5, &base_id);

	_add_record(tm, "base", 7, &linked1_id);
	calendar_db_link_record(base_id, linked1_id);

	_add_record(tm, "base", 9, &linked2_id);
	calendar_db_link_record(base_id, linked2_id);

	sleep(1);

	_add_record(tm, "base", 11, &base_id);
	calendar_db_link_record(base_id, new_id);

	calendar_disconnect();
	return 0;
}

UTC_HIDDEN int utc_calendar_db_link_record_n_event(void)
{
	calendar_connect();

	int ret = 0;

	int record_id = 0;
	time_t tm = time(NULL);

	_add_record(tm, "base", 5, &record_id);

	// case 1
	ret = calendar_db_link_record(-1, record_id);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_link_record(record_id, -1);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_disconnect();
	return 0;
}

UTC_HIDDEN int utc_calendar_db_unlink_record_p_event(void)
{
	calendar_connect();

	time_t tm = time(NULL);

	int base_id = 0;
	_add_record(tm, "base", 5, &base_id);

	int linked1_id = 0;
	_add_record(tm, "base", 7, &linked1_id);
	calendar_db_link_record(base_id, linked1_id);

	int linked2_id = 0;
	_add_record(tm, "base", 9, &linked2_id);
	calendar_db_link_record(base_id, linked2_id);

	calendar_db_unlink_record(linked1_id);

	calendar_disconnect();
	return 0;
}

UTC_HIDDEN int utc_calendar_db_unlink_record_n_event(void)
{
	calendar_connect();

	int ret = 0;

	ret = calendar_db_unlink_record(-1);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_disconnect();
	return 0;
}

