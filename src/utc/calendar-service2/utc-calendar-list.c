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
#include <stdio.h>
#include <calendar.h>

#include "utc-calendar-debug.h"
#include "utc-calendar-util.h"
#include "utc-calendar-helper-event.h"

static int g_startup_err = CALENDAR_ERROR_NONE;

/**
 * @function		utc_calendar_list_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_list_startup(void)
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
 * @function		utc_calendar_list_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_list_cleanup(void)
{
    calendar_disconnect();
}

/**
 * @testcase		utc_calendar_list_create_p
 * @since_tizen		2.3
 * @description		Test creating a calendar list handle.
 */
int utc_calendar_list_create_p(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_create(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_list_h list = NULL;
    ret = calendar_list_create(&list);
    assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	if (NULL == list)
		assert_eq(-1, CALENDAR_ERROR_NONE);

    calendar_list_destroy(list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_list_create_n
 * @since_tizen		2.3
 * @description		Test fail creating a calendar list handle with invalid parameters.
 */
int utc_calendar_list_create_n(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_create(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_list_create(NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_list_destroy_p
 * @since_tizen		2.3
 * @description		Test destroying a calendar list handle and releases all its resources.
 */
int utc_calendar_list_destroy_p(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_destroy(NULL, true);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_list_h list = NULL;
    ret = calendar_list_create(&list);
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_list_destroy(list, true);
    assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_list_destroy_n
 * @since_tizen		2.3
 * @description		Test fail destroying a calendar list handle and releases all its resources with invalid parameters.
 */
int utc_calendar_list_destroy_n(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_destroy(NULL, true);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_list_destroy(NULL, true);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_list_get_count_p
 * @since_tizen		2.3
 * @description		Test retrieving the number of calendar entities in a calendar list.
 */
int utc_calendar_list_get_count_p(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_get_count(NULL, true);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

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

	// get count
	int count = 0;
	ret = calendar_list_get_count(list, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(list, true);

	if (1 != count) {
		assert_eq(-1, CALENDAR_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_calendar_list_get_count_n
 * @since_tizen		2.3
 * @description		Test fail retrieving the number of calendar entities in a calendar list with invalid parameters.
 */
int utc_calendar_list_get_count_n(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_get_count(NULL, true);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	int count = 0;
    ret = calendar_list_get_count(NULL, &count);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_list_h list = NULL;
    ret = calendar_list_get_count(list, NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_list_add_p
 * @since_tizen		2.3
 * @description		Test adding a record to the calendar list.
 */
int utc_calendar_list_add_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_add(NULL, true);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_record_h event = NULL;
	calendar_record_create(_calendar_event._uri, &event);
    	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// list add
	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// get count
	int count = 0;
	ret = calendar_list_get_count(list, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(list, true);

	if (1 != count) {
		assert_eq(-1, CALENDAR_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_calendar_list_add_n
 * @since_tizen		2.3
 * @description		Test fail adding a record to the calendar list with invalid parameters.
 */
int utc_calendar_list_add_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_add(NULL, true);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	calendar_record_h record = NULL;
	ret = calendar_list_add(NULL, record);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_list_h list = NULL;
	ret = calendar_list_add(list, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_list_remove_p
 * @since_tizen		2.3
 * @description		Test removing a record from the calendar list.
 */
int utc_calendar_list_remove_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_remove(NULL, true);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

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

	ret = calendar_list_remove(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
	int count = 0;
	ret = calendar_list_get_count(list, &count);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(list, true);

	if (0 != count) {
		assert_eq(-1, CALENDAR_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_calendar_list_remove_n
 * @since_tizen		2.3
 * @description		Test fail removing a record from the calendar list with invalid parameters.
 */
int utc_calendar_list_remove_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_remove(NULL, true);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	calendar_record_h record = NULL;
	ret = calendar_list_remove(NULL, record);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_list_h list = NULL;
	ret = calendar_list_remove(list, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_list_get_current_record_p_p
 * @since_tizen		2.3
 * @description		Test retrieving a record from the calendar list.
 */
int utc_calendar_list_get_current_record_p_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_get_current_record_p(NULL, NULL);
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

	// get
	ret = calendar_list_first(list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_get_current_record_p(list, &event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_list_get_current_record_p_n
 * @since_tizen		2.3
 * @description		Test fail retrieving a record from the calendar list with invalid parameters.
 */
int utc_calendar_list_get_current_record_p_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_get_current_record_p(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	calendar_record_h event = NULL;
	ret = calendar_list_get_current_record_p(NULL, &event);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_list_h list = NULL;
	ret = calendar_list_get_current_record_p(list, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_list_prev_p
 * @since_tizen		2.3
 * @description		Test moving a calendar list to the previous position.
 */
int utc_calendar_list_prev_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_prev(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h event = NULL;
	// add new
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// add mod
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check: set last and prev
	ret = calendar_list_last(list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// prev
	ret = calendar_list_prev(list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_get_current_record_p(list, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_list_prev_n
 * @since_tizen		2.3
 * @description		Test fail moving a calendar list to the previous position with invalid parameters.
 */
int utc_calendar_list_prev_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_prev(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = calendar_list_prev(NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_list_next_p
 * @since_tizen		2.3
 * @description		Test moving a calendar list to the next position.
 */
int utc_calendar_list_next_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_next(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h event = NULL;
	// add new
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// add mod
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// check: set first and next
	ret = calendar_list_first(list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	// next
	ret = calendar_list_next(list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_get_current_record_p(list, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(list, true);
	return 0;
}

/**
 * @test:case		utc_calendar_list_next_n
 * @since_tizen		2.3
 * @description		Test fail moving a calendar list to the next position with invalid parameters.
 */
int utc_calendar_list_next_n(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_next(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_list_next(NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_list_first_p
 * @since_tizen		2.3
 * @description		Test moving a calendar list to the first position.
 */
int utc_calendar_list_first_p(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_first(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
    assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h event = NULL;
	// add new
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	// add mod
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
    ret = calendar_list_first(list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_get_current_record_p(list, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_list_first_n
 * @since_tizen		2.3
 * @description		Test fail moving a calendar list to the first position with invalid parameters.
 */
int utc_calendar_list_first_n(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_first(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_list_first(NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_calendar_list_last_p
 * @since_tizen		2.3
 * @description		Test moving a calendar list to the last position.
 */
int utc_calendar_list_last_p(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_last(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
    assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h event = NULL;
	// add new
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	// add mod
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
		calendar_record_destroy(event, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	// check
    ret = calendar_list_last(list);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_list_get_current_record_p(list, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_check_mod(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
    assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_list_destroy(list, true);
	return 0;
}

/**
 * @testcase		utc_calendar_list_last_n
 * @since_tizen		2.3
 * @description		Test fail moving a calendar list to the last position with invalid parameters.
 */
int utc_calendar_list_last_n(void)
{
    assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_list_last(NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_list_last(NULL);
    assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}
