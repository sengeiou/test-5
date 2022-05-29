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
 * @testcase		utc_calendar_helper_alarm_set_new_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_set_new_str(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_str(record, _calendar_alarm.summary, UTC_STR_NEW_ALARM_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_alarm.description, UTC_STR_NEW_ALARM_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_alarm.attach, UTC_STR_NEW_ALARM_ATTACH);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_alarm_set_new_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_set_new_int(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_int(record, _calendar_alarm.tick, UTC_INT_NEW_ALARM_TICK);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_alarm.tick_unit, UTC_INT_NEW_ALARM_TICK_UNIT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_alarm.action, UTC_INT_NEW_ALARM_ACTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_alarm_set_new
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_set_new(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_alarm_set_new_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_alarm_set_new_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_alarm_set_mod_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_set_mod_str(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_str(record, _calendar_alarm.summary, UTC_STR_MOD_ALARM_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_alarm.description, UTC_STR_MOD_ALARM_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_alarm.attach, UTC_STR_MOD_ALARM_ATTACH);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_alarm_set_mod_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_set_mod_int(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_int(record, _calendar_alarm.tick, UTC_INT_MOD_ALARM_TICK);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_alarm.tick_unit, UTC_INT_MOD_ALARM_TICK_UNIT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_alarm.action, UTC_INT_MOD_ALARM_ACTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_alarm_set_mod
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_set_mod(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_alarm_set_mod_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_alarm_set_mod_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_alarm_check_new_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_check_new_str(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str(record, _calendar_alarm.summary, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ALARM_SUMMARY);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_alarm.description, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ALARM_DESCRIPTION);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_alarm.attach, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ALARM_ATTACH);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	return 0;
}
/**
 * @testcase		utc_calendar_helper_alarm_check_new_str_p
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_check_new_str_p(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str_p(record, _calendar_alarm.summary, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ALARM_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_alarm.description, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ALARM_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_alarm.attach, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ALARM_ATTACH);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_alarm_check_new_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_check_new_int(calendar_record_h record)
{
	int ret = 0;
	int i = 0;
	ret = calendar_record_get_int(record, _calendar_alarm.tick, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_ALARM_TICK);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_alarm.tick_unit, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_ALARM_TICK_UNIT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_alarm.parent_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_alarm.action, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_ALARM_ACTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_alarm_check_new_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_check_new_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};
	ret = calendar_record_get_caltime(record, _calendar_alarm.alarm_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_alarm_check_new
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_check_new(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_alarm_check_new_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_alarm_check_new_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_alarm_check_new_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_alarm_check_mod_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_check_mod_str(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str_p(record, _calendar_alarm.summary, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ALARM_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_alarm.description, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ALARM_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_alarm.attach, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ALARM_ATTACH);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_alarm_check_mod_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_check_mod_int(calendar_record_h record)
{
	int ret = 0;
	int i = 0;
	ret = calendar_record_get_int(record, _calendar_alarm.tick, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_ALARM_TICK);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_alarm.tick_unit, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_ALARM_TICK_UNIT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_alarm.action, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_ALARM_ACTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_alarm_check_mod
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_alarm_check_mod(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_alarm_check_mod_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_alarm_check_mod_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
