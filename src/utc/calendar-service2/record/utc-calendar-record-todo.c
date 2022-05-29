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
#include "utc-calendar-helper-todo.h"
#include "utc-calendar-helper-attendee.h"
#include "utc-calendar-helper-extended.h"

/**
 * @testcase		utc_calendar_record_create_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == todo)
		assert_eq(-1, CALENDAR_ERROR_NONE);

	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_create_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_n_todo(void)
{
	int ret = 0;

	// case 1
	calendar_record_h todo = NULL;
	ret = calendar_record_create(NULL, &todo);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_create(_calendar_todo._uri, NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_record_destroy(todo, true);
    assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_n_todo(void)
{
	int ret = 0;

    ret = calendar_record_destroy(NULL, true);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_p_todo(void)
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

	// clone
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(todo, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);

	// check
	ret = utc_calendar_helper_todo_check_new(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(clone, true);
	}
	calendar_record_destroy(clone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_n_todo(void)
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

	// case 1
	ret = calendar_record_clone(todo, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(todo, true);

	// case 2
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(NULL, &clone);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_uri_p_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	char *uri = NULL;
	ret = calendar_record_get_uri_p(todo, &uri);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == uri || 0 != strcmp(uri, _calendar_todo._uri)) {
		calendar_record_destroy(todo, true);
		assert_eq(-1, CALENDAR_ERROR_NONE);
	}
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_uri_p_n_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_uri_p(todo, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(todo, true);

	// case 2
	char *uri = NULL;
	ret = calendar_record_get_uri_p(NULL, &uri);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_todo_set_new_str(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_str(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_n_todo(void)
{
	int ret = 0;

	// case 1
	char *str = NULL;
	ret = calendar_record_get_str(NULL, _calendar_todo.summary, &str);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_str(todo, _calendar_todo.summary, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_todo_set_new_str(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_str_p(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_n_todo(void)
{
	int ret = 0;

	// case 1
	char *str = NULL;
	ret = calendar_record_get_str_p(NULL, _calendar_todo.summary, &str);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_str_p(todo, _calendar_todo.summary, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_todo_set_new_int(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_int(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_n_todo(void)
{
	int ret = 0;

	// case 1
	int i = 0;
	ret = calendar_record_get_int(NULL, _calendar_todo.calendar_book_id, &i);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_int(todo, _calendar_todo.calendar_book_id, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_double_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_todo_set_new_double(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_double(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_double_n_todo(void)
{
	int ret = 0;

	// case 1
	double d = 0.0;
	ret = calendar_record_get_double(NULL, _calendar_todo.latitude, &d);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_double(todo, _calendar_todo.latitude, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_lli_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_todo_set_new_lli(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_lli(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_lli_n_todo(void)
{
	int ret = 0;

	// case 1
	long long int lli = 0;
	ret = calendar_record_get_lli(NULL, _calendar_todo.completed_time, &lli);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_double(todo, _calendar_todo.completed_time, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_caltime_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_todo_set_new_caltime(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_caltime(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_caltime_n_todo(void)
{
	int ret = 0;

	// case 1
	calendar_time_s ct = {0};
	ret = calendar_record_get_caltime(NULL, _calendar_todo.until_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(todo, _calendar_todo.until_time, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_str_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_todo_set_new_str(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_str_p(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_str_n_todo(void)
{
	int ret = 0;
	ret = calendar_record_set_str(NULL, _calendar_todo.summary, UTC_STR_MOD_SUMMARY);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_int_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_todo_set_new_int(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_int(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_int_n_todo(void)
{
	int ret = 0;
	ret = calendar_record_set_int(NULL, _calendar_todo.calendar_book_id, UTC_INT_NEW_TODO_CALENDAR_BOOK_ID);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_double_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_todo_set_new_double(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_double(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_double_n_todo(void)
{
	int ret = 0;
	ret = calendar_record_set_double(NULL, _calendar_todo.latitude, UTC_DOUBLE_NEW_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_lli_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_todo_set_new_lli(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_lli(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_lli_n_todo(void)
{
	int ret = 0;
	ret = calendar_record_set_lli(NULL, _calendar_todo.completed_time, 0);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_caltime_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_todo_set_new_caltime(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_todo_check_new_caltime(todo);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_caltime_n_todo(void)
{
	int ret = 0;
	calendar_time_s ct = {0};
	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_NEW_END_UTIME;
	ret = calendar_record_set_caltime(NULL, _calendar_todo.until_time, ct);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_add_child_record_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_set_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_record_get_child_record_at_p(todo, _calendar_todo.calendar_attendee, 0, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_attendee_check_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_extended_set_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_record_get_child_record_at_p(todo, _calendar_todo.extended, 0, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_check_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_add_child_record_n_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attendee
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_add_child_record(NULL, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(attendee, true);
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(attendee, true);
	// case 2
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_attendee, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_add_child_record(NULL, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(extended, true);
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(extended, true);
	// case 2
	ret = calendar_record_add_child_record(todo, _calendar_todo.extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_remove_child_record_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// remove
	ret = calendar_record_remove_child_record(todo, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// remove
	ret = calendar_record_remove_child_record(todo, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_remove_child_record_n_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_remove_child_record(NULL, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	// case 2
	ret = calendar_record_remove_child_record(todo, _calendar_todo.calendar_attendee, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_remove_child_record(NULL, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	// case 2
	ret = calendar_record_remove_child_record(todo, _calendar_todo.extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_count_p_todo(void)
{
	int ret = 0;
	unsigned int count = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_set_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get count
	ret = calendar_record_get_child_record_count(todo, _calendar_todo.calendar_attendee, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	if (1 != count) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_extended_set_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get count
	ret = calendar_record_get_child_record_count(todo, _calendar_todo.extended, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	if (1 != count) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_count_n_todo(void)
{
	int ret = 0;
	unsigned int count = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_set_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_child_record_count(NULL, _calendar_todo.calendar_attendee, &count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_get_child_record_count(todo, _calendar_todo.calendar_attendee, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_extended_set_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_child_record_count(NULL, _calendar_todo.extended, &count);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_get_child_record_count(todo, _calendar_todo.extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_at_p_p_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_set_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_record_get_child_record_at_p(todo, _calendar_todo.calendar_attendee, 0, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_attendee_check_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_extended_set_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_record_get_child_record_at_p(todo, _calendar_todo.extended, 0, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_check_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_at_p_n_todo(void)
{
	int ret = 0;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	// case 1
	ret = calendar_record_get_child_record_at_p(NULL, _calendar_todo.calendar_attendee, 0, &attendee);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	// case 2
	ret = calendar_record_get_child_record_at_p(todo, _calendar_todo.calendar_attendee, 0, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_add_child_record(todo, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_child_record_at_p(NULL, _calendar_todo.extended, 0, &extended);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_get_child_record_at_p(todo, _calendar_todo.extended, 0, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_p_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_child_record_list_p_todo(void)
{
	int ret = 0;
	calendar_list_h clone = NULL;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_set_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_clone_child_record_list(todo, _calendar_todo.calendar_attendee, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_list_first(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_get_current_record_p(clone, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_attendee_check_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(clone, true);
	clone = NULL;

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_extended_set_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_clone_child_record_list(todo, _calendar_todo.extended, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	ret = calendar_list_first(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_get_current_record_p(clone, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_list_destroy(clone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_check_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(clone, true);
	clone = NULL;

	calendar_record_destroy(todo, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_n_todo
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_child_record_list_n_todo(void)
{
	int ret = 0;
	calendar_list_h clone = NULL;

	calendar_record_h todo = NULL;
	ret = calendar_record_create(_calendar_todo._uri, &todo);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// attende
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(attendee, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_clone_child_record_list(NULL, _calendar_todo.calendar_attendee, &clone);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_clone_child_record_list(todo, _calendar_todo.calendar_attendee, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_list_destroy(clone, true);
	clone = NULL;

	// extended
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(todo, _calendar_todo.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(todo, true);
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_clone_child_record_list(NULL, _calendar_todo.extended, &clone);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_clone_child_record_list(todo, _calendar_todo.extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(todo, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_list_destroy(clone, true);
	clone = NULL;

	calendar_record_destroy(todo, true);
	return 0;
}
