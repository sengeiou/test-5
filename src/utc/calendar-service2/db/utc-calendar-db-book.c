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
#include "utc-calendar-helper-book.h"

static int g_startup_err = CALENDAR_ERROR_NONE;

/**
 * @testcase		utc_calendar_db_insert_record_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_record_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// check
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_check_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(book, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_record_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_record_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	ret = calendar_db_insert_record(NULL, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_record_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_record_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// get
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_check_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(book, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_record_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_record_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// case 1
	ret = calendar_db_get_record(NULL, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_get_record(_calendar_book._uri, record_id, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	record_id = -1;
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_record_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_record_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// get to update
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// update
	ret = utc_calendar_helper_book_set_mod(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_db_update_record(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(book, true);

	// get to check
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_check_mod(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(book, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_record_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_record_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_update_record(NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_record_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_record_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h book = NULL;
	ret = calendar_record_create(_calendar_book._uri, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int record_id = 0;
	ret = calendar_db_insert_record(book, &record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(book, true);

	// delete
	ret = calendar_db_delete_record(_calendar_book._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	calendar_record_h get_book = NULL;
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &get_book);
	assert_eq(ret, CALENDAR_ERROR_DB_RECORD_NOT_FOUND);
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_record_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_record_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	int record_id = 1;
	ret = calendar_db_delete_record(NULL, record_id);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	record_id = -1;
	ret = calendar_db_delete_record(_calendar_book._uri, record_id);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_all_records_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_all_records_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// get all
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_book._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_book._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_book.id, CALENDAR_MATCH_EQUAL, record_id);
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

	ret = calendar_list_get_current_record_p(get_list, &book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_check_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_list_destroy(get_list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_all_records_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_all_records_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	int offset = 0, limit = 0;
	ret = calendar_db_get_all_records(_calendar_book._uri, offset, limit, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_list_h get_list = NULL;
	ret = calendar_db_get_all_records(NULL, offset, limit, &get_list);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_records_with_query_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_records_with_query_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// make query
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_book._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_book._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_book.id, CALENDAR_MATCH_EQUAL, record_id);
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

	ret = calendar_list_get_current_record_p(get_list, &book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_check_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_list_destroy(get_list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_records_with_query_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_records_with_query_n_book(void)
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
 * @testcase		utc_calendar_db_get_count_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// get count
	int get_count = 0;
	ret = calendar_db_get_count(_calendar_book._uri, &get_count);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ASSERT_IF(4 != get_count,
			"expected(%d): get(%d)", 4, get_count);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	ret = calendar_db_get_count(_calendar_book._uri, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	int get_count = 0;
	ret = calendar_db_get_count(NULL, &get_count);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_count_with_query_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_with_query_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// query
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_book._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_book._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_book.id, CALENDAR_MATCH_EQUAL, record_id);
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
 * @testcase		utc_calendar_db_get_count_with_query_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_count_with_query_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_book._uri, &query);
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
 * @testcase		utc_calendar_db_insert_records_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_records_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h book = NULL;
	ret = calendar_record_create(_calendar_book._uri, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_set_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
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
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_check_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(book, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_records_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_records_n_book(void)
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
 * @testcase		utc_calendar_db_update_records_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_records_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h book = NULL;
	ret = calendar_record_create(_calendar_book._uri, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_set_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
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

	// get
	calendar_query_h query = NULL;
	ret = calendar_query_create(_calendar_book._uri, &query);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_filter_h filter = NULL;
	ret = calendar_filter_create(_calendar_book._uri, &filter);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_query_destroy(query);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_filter_add_int(filter, _calendar_book.id, CALENDAR_MATCH_EQUAL, record_id);
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

	// get list
	ret = calendar_list_first(get_list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_get_current_record_p(get_list, &book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_set_mod(book);
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
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_check_mod(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(book, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_update_records_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_update_records_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_update_records(NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_records_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_records_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h book = NULL;
	ret = calendar_record_create(_calendar_book._uri, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_set_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
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
	ret = calendar_db_delete_records(_calendar_book._uri, ids, count);
	if (CALENDAR_ERROR_NONE != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	int record_id = ids[0];
	free(ids);

	// check
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_DB_RECORD_NOT_FOUND);

	return 0;
}

/**
 * @testcase		utc_calendar_db_delete_records_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_delete_records_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h book = NULL;
	ret = calendar_record_create(_calendar_book._uri, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_set_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
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
	ret = calendar_db_delete_records(_calendar_book._uri, NULL, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 3
	count = -1;
	ret = calendar_db_delete_records(_calendar_book._uri, ids, count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		free(ids);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_calendar_db_get_current_version_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_current_version_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int version = 0;
	ret = calendar_db_get_current_version(&version);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_current_version_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_current_version_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_get_current_version(NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

static void __changed_cb_book(const char* view_uri, void* user_data)
{
}

/**
 * @testcase		utc_calendar_db_add_changed_cb_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_add_changed_cb_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_add_changed_cb(_calendar_book._uri, __changed_cb_book, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_add_changed_cb_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_add_changed_cb_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	ret = calendar_db_add_changed_cb(_calendar_book._uri, NULL, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_add_changed_cb(NULL, __changed_cb_book, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_remove_changed_cb_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_remove_changed_cb_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_remove_changed_cb(_calendar_book._uri, __changed_cb_book, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_remove_changed_cb_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_remove_changed_cb_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// case 1
	ret = calendar_db_remove_changed_cb(_calendar_book._uri, NULL, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_db_remove_changed_cb(NULL, __changed_cb_book, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_by_version_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_by_version_p_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_by_version_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_by_version_n_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_vcalendars_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_vcalendars_p_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_insert_vcalendars_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_insert_vcalendars_n_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_vcalendars_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_vcalendars_p_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_vcalendars_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_vcalendars_n_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_record_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_record_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// get to update
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_set_mod(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// replace
	ret = calendar_db_replace_record(book, record_id);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get to check
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_check_mod(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(book, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_record_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_record_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
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

	// case 1
	ret = calendar_db_replace_record(NULL, record_id);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	record_id = -1;
	ret = calendar_db_replace_record(book, record_id);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_record_destroy(book, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_records_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_records_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h book = NULL;
	ret = calendar_record_create(_calendar_book._uri, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_set_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
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
	ret = calendar_db_get_all_records(_calendar_book._uri, offset, limit, &get_list);
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
	ret = calendar_list_get_current_record_p(get_list, &book);
	if (CALENDAR_ERROR_NONE != ret) {
		free(ids);
		calendar_list_destroy(get_list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_set_mod(book);
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
	ret = calendar_db_get_record(_calendar_book._uri, record_id, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_check_mod(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(book, true);
	return 0;
}

/**
 * @testcase		utc_calendar_db_replace_records_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_replace_records_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	calendar_record_h book = NULL;
	ret = calendar_record_create(_calendar_book._uri, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_book_set_new(book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// list
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, book);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(book, true);
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
 * @testcase		utc_calendar_db_get_last_change_version_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_last_change_version_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int version = 0;
	ret = calendar_db_get_last_change_version(&version);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_last_change_version_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_last_change_version_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	ret = calendar_db_get_last_change_version(NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_exception_by_version_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_exception_by_version_p_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_get_changes_exception_by_version_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_get_changes_exception_by_version_n_book(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_db_clean_after_sync_p_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_clean_after_sync_p_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	// create book
	calendar_record_h book = NULL;
	ret = calendar_record_create(_calendar_book._uri, &book);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int book_id = 0;
	calendar_db_insert_record(book, &book_id);
	calendar_record_destroy(book, true);

	int db_version = 1;
	ret = calendar_db_clean_after_sync(book_id, db_version);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// delete book
	calendar_db_delete_record(_calendar_book._uri, book_id);
	return 0;
}

/**
 * @testcase		utc_calendar_db_clean_after_sync_n_book
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_db_clean_after_sync_n_book(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	int book_id = -1;
	int db_version = 1;
	ret = calendar_db_clean_after_sync(book_id, db_version);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}
