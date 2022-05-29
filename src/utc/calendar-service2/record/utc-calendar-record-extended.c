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
#include "utc-calendar-helper-extended.h"

/**
 * @testcase		utc_calendar_record_create_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_p_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == extended)
		assert_eq(-1, CALENDAR_ERROR_NONE);

	calendar_record_destroy(extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_create_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_n_extended(void)
{
	int ret = 0;

	// case 1
	calendar_record_h extended = NULL;
	ret = calendar_record_create(NULL, &extended);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_create(_calendar_extended_property._uri, NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_p_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_record_destroy(extended, true);
    assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_n_extended(void)
{
	int ret = 0;

    ret = calendar_record_destroy(NULL, true);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_p_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_set_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// clone
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(extended, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(extended, true);

	// check
	ret = utc_calendar_helper_extended_check_new(clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(clone, true);
	}
	calendar_record_destroy(clone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_n_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_set_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_clone(extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(extended, true);

	// case 2
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(NULL, &clone);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_uri_p_p_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	char *uri = NULL;
	ret = calendar_record_get_uri_p(extended, &uri);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == uri || 0 != strcmp(uri, _calendar_extended_property._uri)) {
		calendar_record_destroy(extended, true);
		assert_eq(-1, CALENDAR_ERROR_NONE);
	}
	calendar_record_destroy(extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_uri_p_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_uri_p_n_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_get_uri_p(extended, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(extended, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(extended, true);

	// case 2
	char *uri = NULL;
	ret = calendar_record_get_uri_p(NULL, &uri);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_set_new_str(extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_extended_check_new_str(extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_n_extended(void)
{
	int ret = 0;

	// case 1
	char *str = NULL;
	ret = calendar_record_get_str(NULL, _calendar_extended_property.key, &str);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_str(extended, _calendar_extended_property.key, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(extended, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_p_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_set_new_str(extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_extended_check_new_str_p(extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_str_p_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_str_p_n_extended(void)
{
	int ret = 0;

	// case 1
	char *str = NULL;
	ret = calendar_record_get_str_p(NULL, _calendar_extended_property.key, &str);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_str_p(extended, _calendar_extended_property.key, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(extended, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_p_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_extended_set_new_int(extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_extended_check_new_int(extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_n_extended(void)
{
	int ret = 0;

	// case 1
	int i = 0;
	ret = calendar_record_get_int(NULL, _calendar_extended_property.record_type, &i);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_int(extended, _calendar_extended_property.record_type, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(extended, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_double_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_double_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_double_n_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_lli_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_lli_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_lli_n_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_caltime_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_caltime_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_caltime_n_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_str_p_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_extended_set_new_str(extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_extended_check_new_str_p(extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_str_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_str_n_extended(void)
{
	int ret = 0;
	ret = calendar_record_set_str(NULL, _calendar_extended_property.key, UTC_STR_NEW_EXTENDED_KEY);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_int_p_extended(void)
{
	int ret = 0;

	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// set
	ret = utc_calendar_helper_extended_set_new_int(extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_extended_check_new_int(extended);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(extended, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(extended, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_int_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_int_n_extended(void)
{
	int ret = 0;

	ret = calendar_record_get_int(NULL, _calendar_extended_property.record_type, 0);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_double_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_double_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_double_n_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_lli_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_lli_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_lli_n_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_caltime_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_set_caltime_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_set_caltime_n_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_add_child_record_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_add_child_record_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_add_child_record_n_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_remove_child_record_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_remove_child_record_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_remove_child_record_n_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_count_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_count_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_count_n_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_at_p_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_child_record_at_p_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_child_record_at_p_n_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_p_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_child_record_list_p_extended(void)
{
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_child_record_list_n_extended
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_child_record_list_n_extended(void)
{
	return 0;
}
