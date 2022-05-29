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
#include "utc-calendar-helper-timezone.h"

/**
 * @testcase		utc_calendar_record_create_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_p_timezone(void)
{
	int ret = 0;

	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == timezone)
		assert_eq(-1, CALENDAR_ERROR_NONE);

	calendar_record_destroy(timezone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_create_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_n_timezone(void)
{
	int ret = 0;

	// case 1
	calendar_record_h timezone = NULL;
	ret = calendar_record_create(NULL, &timezone);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_create(_calendar_timezone._uri, NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_p_timezone(void)
{
	int ret = 0;

	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_record_destroy(timezone, true);
    assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_n_timezone(void)
{
	int ret = 0;

    ret = calendar_record_destroy(NULL, true);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_p_timezone(void)
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

	// clone
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(timezone, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(timezone, true);

	// check
	ret = utc_calendar_helper_timezone_check_new(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(clone, true);
	}
	calendar_record_destroy(clone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_n_timezone(void)
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

	// case 1
	ret = calendar_record_clone(timezone, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(timezone, true);

	// case 2
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(NULL, &clone);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_uri_p_p_timezone(void)
{
	int ret = 0;

	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	char *uri = NULL;
	ret = calendar_record_get_uri_p(timezone, &uri);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == uri || 0 != strcmp(uri, _calendar_timezone._uri)) {
		calendar_record_destroy(timezone, true);
		assert_eq(-1, CALENDAR_ERROR_NONE);
	}
	calendar_record_destroy(timezone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_uri_p_n_timezone(void)
{
	int ret = 0;

	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_uri_p(timezone, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(timezone, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(timezone, true);

	// case 2
	char *uri = NULL;
	ret = calendar_record_get_uri_p(NULL, &uri);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_timezone(void)
{
	int ret = 0;

	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_timezone_set_new_str(timezone);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_timezone_check_new_str(timezone);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(timezone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_n_timezone(void)
{
	int ret = 0;

	// case 1
	char *str = NULL;
	ret = calendar_record_get_str(NULL, _calendar_timezone.standard_name, &str);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_str(timezone, _calendar_timezone.standard_name, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(timezone, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(timezone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_p_timezone(void)
{
	int ret = 0;

	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_timezone_set_new_str(timezone);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_timezone_check_new_str_p(timezone);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(timezone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_n_timezone(void)
{
	int ret = 0;

	// case 1
	char *str = NULL;
	ret = calendar_record_get_str_p(NULL, _calendar_timezone.standard_name, &str);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_str_p(timezone, _calendar_timezone.standard_name, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(timezone, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(timezone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_p_timezone(void)
{
	int ret = 0;

	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_timezone_set_new_int(timezone);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_timezone_check_new_int(timezone);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(timezone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_n_timezone(void)
{
	int ret = 0;

	// case 1
	int i = 0;
	ret = calendar_record_get_int(NULL, _calendar_timezone.calendar_book_id, &i);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_int(timezone, _calendar_timezone.calendar_book_id, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(timezone, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(timezone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_double_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_double_n_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_lli_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_lli_n_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_caltime_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_caltime_n_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_str_p_timezone(void)
{
	int ret = 0;

	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_timezone_set_new_str(timezone);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_timezone_check_new_str_p(timezone);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(timezone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_str_n_timezone(void)
{
	int ret = 0;
	ret = calendar_record_set_str(NULL, _calendar_timezone.standard_name, UTC_STR_NEW_TIMEZONE_STANDARD_NAME);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_int_p_timezone(void)
{
	int ret = 0;

	calendar_record_h timezone = NULL;
	ret = calendar_record_create(_calendar_timezone._uri, &timezone);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_timezone_set_new_int(timezone);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_timezone_check_new_int(timezone);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(timezone, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(timezone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_int_n_timezone(void)
{
	int ret = 0;

	ret = calendar_record_get_int(NULL, _calendar_timezone.calendar_book_id, 0);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_double_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_double_n_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_lli_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_lli_n_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_caltime_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_caltime_n_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_add_child_record_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_add_child_record_n_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_remove_child_record_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_remove_child_record_n_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_count_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_count_n_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_at_p_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_at_p_n_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_p_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_child_record_list_p_timezone(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_n_timezone
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_child_record_list_n_timezone(void)
{
	return 0;
}
