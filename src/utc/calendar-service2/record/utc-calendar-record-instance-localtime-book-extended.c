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
#include "utc-calendar-helper-instance-localtime-book-extended.h"

/**
 * @testcase		utc_calendar_record_create_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == instance_localtime_book_extended)
		assert_eq(-1, CALENDAR_ERROR_NONE);

	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_create_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_n_instance_localtime_book_extended(void)
{
	int ret = 0;

	// case 1
	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(NULL, &instance_localtime_book_extended);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_record_destroy(instance_localtime_book_extended, true);
    assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_n_instance_localtime_book_extended(void)
{
	int ret = 0;

    ret = calendar_record_destroy(NULL, true);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_instance_localtime_book_extended_set_new(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// clone
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(instance_localtime_book_extended, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(instance_localtime_book_extended, true);

	// check
	ret = utc_calendar_helper_instance_localtime_book_extended_check_new(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(clone, true);
	}
	calendar_record_destroy(clone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_n_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_instance_localtime_book_extended_set_new(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_clone(instance_localtime_book_extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(instance_localtime_book_extended, true);

	// case 2
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(NULL, &clone);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_uri_p_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	char *uri = NULL;
	ret = calendar_record_get_uri_p(instance_localtime_book_extended, &uri);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == uri || 0 != strcmp(uri, _calendar_instance_localtime_calendar_book_extended._uri)) {
		calendar_record_destroy(instance_localtime_book_extended, true);
		assert_eq(-1, CALENDAR_ERROR_NONE);
	}
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_uri_p_n_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_uri_p(instance_localtime_book_extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(instance_localtime_book_extended, true);

	// case 2
	char *uri = NULL;
	ret = calendar_record_get_uri_p(NULL, &uri);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_instance_localtime_book_extended_set_new_str(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_instance_localtime_book_extended_check_new_str(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_n_instance_localtime_book_extended(void)
{
	int ret = 0;

	// case 1
	char *str = NULL;
	ret = calendar_record_get_str(NULL, _calendar_instance_localtime_calendar_book_extended.summary, &str);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_str(instance_localtime_book_extended, _calendar_instance_localtime_calendar_book_extended.summary, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_instance_localtime_book_extended_set_new_str(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_instance_localtime_book_extended_check_new_str_p(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_n_instance_localtime_book_extended(void)
{
	int ret = 0;

	// case 1
	char *str = NULL;
	ret = calendar_record_get_str_p(NULL, _calendar_instance_localtime_calendar_book_extended.summary, &str);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_str_p(instance_localtime_book_extended, _calendar_instance_localtime_calendar_book_extended.summary, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_instance_localtime_book_extended_set_new_int(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_instance_localtime_book_extended_check_new_int(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_n_instance_localtime_book_extended(void)
{
	int ret = 0;

	// case 1
	int i = 0;
	ret = calendar_record_get_int(NULL, _calendar_instance_localtime_calendar_book_extended.calendar_book_id, &i);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_int(instance_localtime_book_extended, _calendar_instance_localtime_calendar_book_extended.calendar_book_id, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_double_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_instance_localtime_book_extended_set_new_double(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_instance_localtime_book_extended_check_new_double(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_double_n_instance_localtime_book_extended(void)
{
	int ret = 0;

	// case 1
	double d = 0.0;
	ret = calendar_record_get_double(NULL, _calendar_instance_localtime_calendar_book_extended.latitude, &d);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_double(instance_localtime_book_extended, _calendar_instance_localtime_calendar_book_extended.latitude, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_lli_p_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_lli_n_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_caltime_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_instance_localtime_book_extended_set_new_caltime(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_instance_localtime_book_extended_check_new_caltime(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_caltime_n_instance_localtime_book_extended(void)
{
	int ret = 0;

	// case 1
	calendar_time_s ct = {0};
	ret = calendar_record_get_caltime(NULL, _calendar_instance_localtime_calendar_book_extended.start_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(instance_localtime_book_extended, _calendar_instance_localtime_calendar_book_extended.start_time, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_str_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_instance_localtime_book_extended_set_new_str(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_instance_localtime_book_extended_check_new_str_p(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_str_n_instance_localtime_book_extended(void)
{
	int ret = 0;
	ret = calendar_record_set_str(NULL, _calendar_instance_localtime_calendar_book_extended.summary, UTC_STR_NEW_SUMMARY);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_int_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_instance_localtime_book_extended_set_new_int(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_instance_localtime_book_extended_check_new_int(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_int_n_instance_localtime_book_extended(void)
{
	int ret = 0;
	ret = calendar_record_set_int(NULL, _calendar_instance_localtime_calendar_book_extended.calendar_book_id, UTC_INT_NEW_EVENT_CALENDAR_BOOK_ID);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_double_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_instance_localtime_book_extended_set_new_double(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_instance_localtime_book_extended_check_new_double(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_double_n_instance_localtime_book_extended(void)
{
	int ret = 0;
	ret = calendar_record_set_double(NULL, _calendar_instance_localtime_calendar_book_extended.latitude, UTC_DOUBLE_NEW_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_lli_p_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_lli_n_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_caltime_p_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_record_h instance_localtime_book_extended = NULL;
	ret = calendar_record_create(_calendar_instance_localtime_calendar_book_extended._uri, &instance_localtime_book_extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_instance_localtime_book_extended_set_new_caltime(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_instance_localtime_book_extended_check_new_caltime(instance_localtime_book_extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(instance_localtime_book_extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(instance_localtime_book_extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_caltime_n_instance_localtime_book_extended(void)
{
	int ret = 0;

	calendar_time_s ct = {0};
	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_NEW_END_UTIME;
	ret = calendar_record_set_caltime(NULL, _calendar_instance_localtime_calendar_book_extended.start_time, ct);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_add_child_record_p_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_add_child_record_n_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_remove_child_record_p_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_remove_child_record_n_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_count_p_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_count_n_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_at_p_p_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_at_p_n_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_p_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_child_record_list_p_instance_localtime_book_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_n_instance_localtime_book_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_child_record_list_n_instance_localtime_book_extended(void)
{
	return 0;
}
