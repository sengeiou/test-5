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

/**
 * @testcase		utc_calendar_connect_p
 * @since_tizen		2.3
 * @description		Test connecting to the calendar service.
 */
int utc_calendar_connect_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_connect();
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// nomal case
    ret = calendar_connect();
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_disconnect();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_connect();
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_disconnect();
    assert_eq(ret, CALENDAR_ERROR_NONE);

	// nest case
    ret = calendar_connect();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_connect();
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_disconnect();
    assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_disconnect();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_calendar_disconnect_p
 * @since_tizen		2.3
 * @description		Test disconnecting from the calendar service.
 */
int utc_calendar_disconnect_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_disconnect();
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_connect();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_disconnect();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_calendar_connect_on_thread_p
 * @since_tizen		2.3
 * @description		Test connecting to the calendar service on a thread.
 */
int utc_calendar_connect_on_thread_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_connect_on_thread();
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// normal case
    ret = calendar_connect_on_thread();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_disconnect_on_thread();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_connect_on_thread();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_disconnect_on_thread();
    assert_eq(ret, CALENDAR_ERROR_NONE);

	// nest case
    ret = calendar_connect_on_thread();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_connect_on_thread();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_disconnect_on_thread();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_disconnect_on_thread();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_calendar_disconnect_on_thread_p
 * @since_tizen		2.3
 * @description		Test disconnecting from the calendar service on a thread.
 */
int utc_calendar_disconnect_on_thread_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_disconnect_on_thread();
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_connect_on_thread();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_disconnect_on_thread();
    assert_eq(ret, CALENDAR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_calendar_connect_with_flags_p
 * @since_tizen		2.3
 * @description		Test connecting to the calendar service with flag.
 */
int utc_calendar_connect_with_flags_p(void)
{
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_connect_with_flags(0);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

    ret = calendar_connect_with_flags(CALENDAR_CONNECT_FLAG_RETRY);
    assert_eq(ret, CALENDAR_ERROR_NONE);

    ret = calendar_disconnect();

    return 0;
}
