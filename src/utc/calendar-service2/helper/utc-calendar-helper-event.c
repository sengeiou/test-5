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
 * @testcase		utc_calendar_helper_event_set_new_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_new_str(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_str(record, _calendar_event.summary, UTC_STR_NEW_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.description, UTC_STR_NEW_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.location, UTC_STR_NEW_LOCATION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.categories, UTC_STR_NEW_CATEGORIES);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.exdate,  UTC_STR_NEW_EXDATE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.uid, UTC_STR_NEW_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.organizer_name, UTC_STR_NEW_ORGANIZER_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.organizer_email, UTC_STR_NEW_ORGANIZER_EMAIL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.bysecond, UTC_STR_NEW_BYSECOND);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.byminute, UTC_STR_NEW_BYMINUTE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.byhour, UTC_STR_NEW_BYHOUR);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.byday, UTC_STR_NEW_BYDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.bymonthday, UTC_STR_NEW_BYMONTHDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.byyearday, UTC_STR_NEW_BYYEARDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.byweekno, UTC_STR_NEW_BYWEEKNO);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.bymonth, UTC_STR_NEW_BYMONTH);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.bysetpos, UTC_STR_NEW_BYSETPOS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.recurrence_id, UTC_STR_NEW_RECURRENCE_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.rdate, UTC_STR_NEW_RDATE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.sync_data1, UTC_STR_NEW_SYNC_DATA1);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.sync_data2, UTC_STR_NEW_SYNC_DATA2);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.sync_data3, UTC_STR_NEW_SYNC_DATA3);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.sync_data4, UTC_STR_NEW_SYNC_DATA4);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.start_tzid, UTC_STR_NEW_START_TZID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.end_tzid, UTC_STR_NEW_END_TZID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_set_new_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_new_int(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_int(record, _calendar_event.calendar_book_id, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.event_status, CALENDAR_EVENT_STATUS_TENTATIVE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.priority, CALENDAR_EVENT_PRIORITY_LOW);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.timezone, UTC_INT_NEW_TIMEZONE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.person_id, UTC_INT_NEW_PERSON_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.busy_status, CALENDAR_EVENT_BUSY_STATUS_FREE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.sensitivity, CALENDAR_SENSITIVITY_PUBLIC);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.meeting_status, CALENDAR_MEETING_STATUS_MEETING);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.original_event_id, UTC_INT_NEW_ORIGINAL_EVENT_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.email_id, UTC_INT_NEW_EMAIL_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.freq, CALENDAR_RECURRENCE_DAILY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.range_type, CALENDAR_RANGE_COUNT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.count, UTC_INT_NEW_COUNT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.interval, UTC_INT_NEW_INTERVAL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.wkst, CALENDAR_SUNDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.calendar_system_type, CALENDAR_SYSTEM_GREGORIAN);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_set_new_double
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_new_double(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_double(record, _calendar_event.latitude, UTC_DOUBLE_NEW_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_double(record, _calendar_event.longitude, UTC_DOUBLE_NEW_LONGITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_set_new_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_new_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};
	ret = calendar_record_set_caltime(record, _calendar_event.until_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
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
 * @testcase		utc_calendar_helper_event_set_new_caltime_local
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_new_caltime_local(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};
	ret = calendar_record_set_caltime(record, _calendar_event.until_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ct.type = CALENDAR_TIME_LOCALTIME;
	ct.time.date.year = UTC_CALTIME_NEW_START_YEAR;
	ct.time.date.month = UTC_CALTIME_NEW_START_MONTH;
	ct.time.date.mday = UTC_CALTIME_NEW_START_MDAY;
	ct.time.date.hour = UTC_CALTIME_NEW_START_HOUR;
	ct.time.date.minute = UTC_CALTIME_NEW_START_MINUTE;
	ct.time.date.second = UTC_CALTIME_NEW_START_SECOND;

	ret = calendar_record_set_caltime(record, _calendar_event.start_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ct.type = CALENDAR_TIME_LOCALTIME;
	ct.time.date.year = UTC_CALTIME_NEW_END_YEAR;
	ct.time.date.month = UTC_CALTIME_NEW_END_MONTH;
	ct.time.date.mday = UTC_CALTIME_NEW_END_MDAY;
	ct.time.date.hour = UTC_CALTIME_NEW_END_HOUR;
	ct.time.date.minute = UTC_CALTIME_NEW_END_MINUTE;
	ct.time.date.second = UTC_CALTIME_NEW_END_SECOND;
	ret = calendar_record_set_caltime(record, _calendar_event.end_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_event_set_new
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_new(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_event_set_new_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_set_new_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_set_new_double(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_set_new_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_event_set_new_local
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_new_local(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_event_set_new_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_set_new_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_set_new_double(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_set_new_caltime_local(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_calendar_helper_event_set_mod_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_mod_str(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_str(record, _calendar_event.summary, UTC_STR_MOD_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.description, UTC_STR_MOD_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.location, UTC_STR_MOD_LOCATION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.categories, UTC_STR_MOD_CATEGORIES);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.uid, UTC_STR_MOD_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.organizer_name, UTC_STR_MOD_ORGANIZER_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.organizer_email, UTC_STR_MOD_ORGANIZER_EMAIL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.bysecond, UTC_STR_MOD_BYSECOND);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.byminute, UTC_STR_MOD_BYMINUTE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.byhour, UTC_STR_MOD_BYHOUR);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.byday, UTC_STR_MOD_BYDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.bymonthday, UTC_STR_MOD_BYMONTHDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.byyearday, UTC_STR_MOD_BYYEARDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.byweekno, UTC_STR_MOD_BYWEEKNO);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.bymonth, UTC_STR_MOD_BYMONTH);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.bysetpos, UTC_STR_MOD_BYSETPOS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.recurrence_id, UTC_STR_MOD_RECURRENCE_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.rdate, UTC_STR_MOD_RDATE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.sync_data1, UTC_STR_MOD_SYNC_DATA1);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.sync_data2, UTC_STR_MOD_SYNC_DATA2);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.sync_data3, UTC_STR_MOD_SYNC_DATA3);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.sync_data4, UTC_STR_MOD_SYNC_DATA4);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.start_tzid, UTC_STR_MOD_START_TZID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_event.end_tzid, UTC_STR_MOD_END_TZID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_set_mod_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_mod_int(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_int(record, _calendar_event.calendar_book_id, UTC_INT_NEW_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.event_status, CALENDAR_EVENT_STATUS_TENTATIVE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.priority, CALENDAR_EVENT_PRIORITY_LOW);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.timezone, UTC_INT_MOD_TIMEZONE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.person_id, UTC_INT_MOD_PERSON_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.busy_status, CALENDAR_EVENT_BUSY_STATUS_FREE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.sensitivity, CALENDAR_SENSITIVITY_PUBLIC);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.meeting_status, CALENDAR_MEETING_STATUS_MEETING);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.original_event_id, UTC_INT_MOD_ORIGINAL_EVENT_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.email_id, UTC_INT_MOD_EMAIL_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.freq, CALENDAR_RECURRENCE_DAILY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.range_type, CALENDAR_RANGE_COUNT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.count, UTC_INT_MOD_COUNT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.interval, UTC_INT_MOD_INTERVAL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.wkst, CALENDAR_SUNDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_event.calendar_system_type, CALENDAR_SYSTEM_GREGORIAN);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_set_mod_double
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_mod_double(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_double(record, _calendar_event.latitude, UTC_DOUBLE_MOD_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_double(record, _calendar_event.longitude, UTC_DOUBLE_MOD_LONGITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_set_mod_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_mod_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};
	ret = calendar_record_set_caltime(record, _calendar_event.until_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
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
 * @testcase		utc_calendar_helper_event_set_mod
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_set_mod(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_event_set_mod_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_set_mod_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_set_mod_double(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_set_mod_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_event_check_new_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_new_str(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str(record, _calendar_event.summary, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SUMMARY);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.description, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_DESCRIPTION);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.location, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_LOCATION);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.categories, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_CATEGORIES);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.exdate, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str,  UTC_STR_NEW_EXDATE);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.uid, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_UID);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.organizer_name, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ORGANIZER_NAME);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.organizer_email, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ORGANIZER_EMAIL);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.bysecond, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYSECOND);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.byminute, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYMINUTE);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.byhour, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYHOUR);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.byday, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYDAY);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.bymonthday, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYMONTHDAY);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.byyearday, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYYEARDAY);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.byweekno, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYWEEKNO);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.bymonth, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYMONTH);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.bysetpos, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYSETPOS);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.recurrence_id, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_RECURRENCE_ID);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.rdate, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_RDATE);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.sync_data1, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA1);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.sync_data2, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA2);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.sync_data3, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA3);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.sync_data4, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA4);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.start_tzid, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_START_TZID);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_event.end_tzid, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_END_TZID);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_check_new_str_p
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_new_str_p(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str_p(record, _calendar_event.summary, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.description, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.location, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_LOCATION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.categories, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_CATEGORIES);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.exdate, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str,  UTC_STR_NEW_EXDATE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.uid, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.organizer_name, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ORGANIZER_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.organizer_email, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ORGANIZER_EMAIL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.bysecond, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYSECOND);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.byminute, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYMINUTE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.byhour, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYHOUR);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.byday, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.bymonthday, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYMONTHDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.byyearday, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYYEARDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.byweekno, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYWEEKNO);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.bymonth, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYMONTH);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.bysetpos, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_BYSETPOS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.recurrence_id, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_RECURRENCE_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.rdate, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_RDATE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.sync_data1, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA1);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.sync_data2, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA2);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.sync_data3, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA3);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.sync_data4, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA4);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.start_tzid, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_START_TZID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.end_tzid, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_END_TZID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_event_check_new_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_new_int(calendar_record_h record)
{
	int ret = 0;
	int i = 0;
	ret = calendar_record_get_int(record, _calendar_event.calendar_book_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, DEFAULT_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.event_status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_EVENT_STATUS_TENTATIVE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.priority, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_EVENT_PRIORITY_LOW);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.timezone, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_TIMEZONE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.person_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_PERSON_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.busy_status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_EVENT_BUSY_STATUS_FREE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.sensitivity, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_SENSITIVITY_PUBLIC);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.meeting_status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_MEETING_STATUS_MEETING);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.original_event_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_ORIGINAL_EVENT_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.email_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_EMAIL_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.freq, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_RECURRENCE_DAILY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.range_type, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_RANGE_COUNT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.count, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_COUNT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.interval, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_INTERVAL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.wkst, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_SUNDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.calendar_system_type, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_SYSTEM_GREGORIAN);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.is_deleted, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.has_attendee, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.has_alarm, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.is_allday, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_check_new_double
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_new_double(calendar_record_h record)
{
	int ret = 0;
	double d = 0;
	ret = calendar_record_get_double(record, _calendar_event.latitude, &d);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_double(&d, UTC_DOUBLE_NEW_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_double(record, _calendar_event.longitude, &d);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_double(&d, UTC_DOUBLE_NEW_LONGITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_check_new_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_new_caltime(calendar_record_h record)
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
 * @testcase		utc_calendar_helper_event_check_new_caltime_local
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_new_caltime_local(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};
	ret = calendar_record_get_caltime(record, _calendar_event.until_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(record, _calendar_event.start_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_time_s t = {0};
	t.type = CALENDAR_TIME_UTIME;
	t.time.date.year = UTC_CALTIME_NEW_START_YEAR;
	t.time.date.month = UTC_CALTIME_NEW_START_MONTH;
	t.time.date.mday = UTC_CALTIME_NEW_START_MDAY;
	t.time.date.hour = UTC_CALTIME_NEW_START_HOUR;
	t.time.date.minute = UTC_CALTIME_NEW_START_MINUTE;
	t.time.date.second = UTC_CALTIME_NEW_START_SECOND;
	ret = _check_caltime(&ct, t);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(record, _calendar_event.end_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	t.type = CALENDAR_TIME_UTIME;
	t.time.date.year = UTC_CALTIME_NEW_END_YEAR;
	t.time.date.month = UTC_CALTIME_NEW_END_MONTH;
	t.time.date.mday = UTC_CALTIME_NEW_END_MDAY;
	t.time.date.hour = UTC_CALTIME_NEW_END_HOUR;
	t.time.date.minute = UTC_CALTIME_NEW_END_MINUTE;
	t.time.date.second = UTC_CALTIME_NEW_END_SECOND;
	ret = _check_caltime(&ct, t);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}


/**
 * @testcase		utc_calendar_helper_event_check_new
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_new(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_event_check_new_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_check_new_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_check_new_double(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_check_new_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_event_check_mod_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_mod_str(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str_p(record, _calendar_event.summary, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.description, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.location, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_LOCATION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.categories, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_CATEGORIES);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	//	ret = calendar_record_get_str_p(record, _calendar_event.exdate, &str);
	//	assert_eq(ret, CALENDAR_ERROR_NONE);
	//	ret = _check_str(str,  UTC_STR_MOD_EXDATE);
	//	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.uid, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.organizer_name, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ORGANIZER_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.organizer_email, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ORGANIZER_EMAIL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.bysecond, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_BYSECOND);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.byminute, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_BYMINUTE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.byhour, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_BYHOUR);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.byday, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_BYDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.bymonthday, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_BYMONTHDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.byyearday, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_BYYEARDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.byweekno, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_BYWEEKNO);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.bymonth, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_BYMONTH);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.bysetpos, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_BYSETPOS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.recurrence_id, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_RECURRENCE_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.rdate, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_RDATE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.sync_data1, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_SYNC_DATA1);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.sync_data2, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_SYNC_DATA2);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.sync_data3, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_SYNC_DATA3);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.sync_data4, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_SYNC_DATA4);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.start_tzid, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_START_TZID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_event.end_tzid, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_END_TZID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_check_mod_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_mod_int(calendar_record_h record)
{
	int ret = 0;
	int i = 0;
	ret = calendar_record_get_int(record, _calendar_event.calendar_book_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.event_status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_EVENT_STATUS_TENTATIVE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.priority, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_EVENT_PRIORITY_LOW);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.timezone, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_TIMEZONE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.person_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_PERSON_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.busy_status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_EVENT_BUSY_STATUS_FREE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.sensitivity, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_SENSITIVITY_PUBLIC);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.meeting_status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_MEETING_STATUS_MEETING);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.original_event_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_ORIGINAL_EVENT_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.email_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_EMAIL_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.freq, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_RECURRENCE_DAILY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.range_type, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_RANGE_COUNT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.count, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_COUNT);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.interval, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_INTERVAL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.wkst, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_SUNDAY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_event.calendar_system_type, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, CALENDAR_SYSTEM_GREGORIAN);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_check_mod_double
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_mod_double(calendar_record_h record)
{
	int ret = 0;
	double d = 0;
	ret = calendar_record_get_double(record, _calendar_event.latitude, &d);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_double(&d, UTC_DOUBLE_MOD_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_double(record, _calendar_event.longitude, &d);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_double(&d, UTC_DOUBLE_MOD_LONGITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_event_check_mod_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_mod_caltime(calendar_record_h record)
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
 * @testcase		utc_calendar_helper_event_check_mod
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_event_check_mod(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_event_check_mod_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_check_mod_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_check_mod_double(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_event_check_mod_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
