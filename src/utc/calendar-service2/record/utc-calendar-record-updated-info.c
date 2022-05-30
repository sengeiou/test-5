/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
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
#include "utc-calendar-helper-updated-info.h"

/**
 * @testcase		utc_calendar_record_create_p_updated_info
 * @since_tizen		3.0
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_p_updated_info(void)
{
	int ret = 0;

	calendar_record_h updated_info = NULL;
	ret = calendar_record_create(_calendar_updated_info._uri, &updated_info);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == updated_info)
		assert_eq(-1, CALENDAR_ERROR_NONE);

	calendar_record_destroy(updated_info, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_create_n_updated_info
 * @since_tizen		3.0
 * @description
 */
UTC_HIDDEN int utc_calendar_record_create_n_updated_info(void)
{
	int ret = 0;

	// case 1
	calendar_record_h updated_info = NULL;
	ret = calendar_record_create(NULL, &updated_info);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_record_create(_calendar_updated_info._uri, NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_p_updated_info
 * @since_tizen		3.0
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_p_updated_info(void)
{
	int ret = 0;

	calendar_record_h updated_info = NULL;
	ret = calendar_record_create(_calendar_updated_info._uri, &updated_info);
	assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_record_destroy(updated_info, true);
    assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_record_destroy_n_updated_info
 * @since_tizen		3.0
 * @description
 */
UTC_HIDDEN int utc_calendar_record_destroy_n_updated_info(void)
{
	int ret = 0;

    ret = calendar_record_destroy(NULL, true);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_p_updated_info
 * @since_tizen		3.0
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_p_updated_info(void)
{
	int ret = 0;

	calendar_record_h updated_info = NULL;
	ret = calendar_record_create(_calendar_updated_info._uri, &updated_info);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// clone
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(updated_info, &clone);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(updated_info, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(updated_info, true);

	calendar_record_destroy(clone, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_clone_n_updated_info
 * @since_tizen		3.0
 * @description
 */
UTC_HIDDEN int utc_calendar_record_clone_n_updated_info(void)
{
	int ret = 0;

	calendar_record_h updated_info = NULL;
	ret = calendar_record_create(_calendar_updated_info._uri, &updated_info);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// case 1
	ret = calendar_record_clone(updated_info, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER!= ret) {
		calendar_record_destroy(updated_info, true);
	}
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(updated_info, true);

	// case 2
	calendar_record_h clone = NULL;
	ret = calendar_record_clone(NULL, &clone);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_p_updated_info
 * @since_tizen		3.0
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_p_updated_info(void)
{
	int ret = 0;

	calendar_record_h updated_info = NULL;
	ret = calendar_record_create(_calendar_updated_info._uri, &updated_info);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get and check
	ret = utc_calendar_helper_updated_info_get_int(updated_info);
	if (CALENDAR_ERROR_NONE!= ret) {
		calendar_record_destroy(updated_info, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_record_destroy(updated_info, true);
	return 0;
}

/**
 * @testcase		utc_calendar_record_get_int_n_updated_info
 * @since_tizen		3.0
 * @description
 */
UTC_HIDDEN int utc_calendar_record_get_int_n_updated_info(void)
{
	int ret = 0;

	// case 1
	int i = 0;
	ret = calendar_record_get_int(NULL, _calendar_updated_info.calendar_book_id, &i);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_record_h updated_info = NULL;
	ret = calendar_record_create(_calendar_updated_info._uri, &updated_info);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_int(updated_info, _calendar_updated_info.calendar_book_id, NULL);
	if (CALENDAR_ERROR_INVALID_PARAMETER != ret) {
		calendar_record_destroy(updated_info, true);
	}
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	calendar_record_destroy(updated_info, true);
	return 0;
}

