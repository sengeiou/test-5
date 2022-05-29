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
 * @testcase		utc_calendar_helper_exception_set_new_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_set_new_str(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_str(record, _calendar_event.uid, UTC_STR_NEW_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_exception_set_new_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_set_new_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};

	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_NEW_START_UTIME;
	ret = calendar_record_set_caltime(record, _calendar_event.start_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_NEW_END_UTIME;
	ret = calendar_record_set_caltime(record, _calendar_event.end_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_exception_set_new
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_set_new(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_exception_set_new_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_exception_set_new_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_exception_set_mod_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_set_mod_str(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_str(record, _calendar_event.uid, UTC_STR_MOD_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_exception_set_mod_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_set_mod_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};

	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_MOD_START_UTIME;
	ret = calendar_record_set_caltime(record, _calendar_event.start_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_MOD_END_UTIME;
	ret = calendar_record_set_caltime(record, _calendar_event.end_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_exception_set_mod
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_set_mod(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_exception_set_mod_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_exception_set_mod_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_exception_check_new_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_check_new_str(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str(record, _calendar_event.uid, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_UID);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;
	return 0;
}
/**
 * @testcase		utc_calendar_helper_exception_check_new_str_p
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_check_new_str_p(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str_p(record, _calendar_event.uid, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_exception_check_new_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_check_new_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};
	ret = calendar_record_get_caltime(record, _calendar_event.until_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(record, _calendar_event.start_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_time_s t = {0};
	t.type = CALENDAR_TIME_UTIME;
	t.time.utime = UTC_CALTIME_NEW_START_UTIME;
	ret = _check_caltime(&ct, t);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(record, _calendar_event.end_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	t.type = CALENDAR_TIME_UTIME;
	t.time.utime = UTC_CALTIME_NEW_END_UTIME;
	ret = _check_caltime(&ct, t);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_exception_check_new
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_check_new(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_exception_check_new_str_p(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_exception_check_new_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_exception_check_mod_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_check_mod_str(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str_p(record, _calendar_event.uid, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_exception_check_mod_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_check_mod_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};
	ret = calendar_record_get_caltime(record, _calendar_event.until_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(record, _calendar_event.start_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_time_s t = {0};
	t.type = CALENDAR_TIME_UTIME;
	t.time.utime = UTC_CALTIME_MOD_START_UTIME;
	ret = _check_caltime(&ct, t);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(record, _calendar_event.end_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	t.type = CALENDAR_TIME_UTIME;
	t.time.utime = UTC_CALTIME_MOD_END_UTIME;
	ret = _check_caltime(&ct, t);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_exception_check_mod
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_exception_check_mod(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_exception_check_mod_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_exception_check_mod_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
