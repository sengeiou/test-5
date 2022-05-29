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
 * @testcase		utc_calendar_helper_instance_utime_book_extended_set_new_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_set_new_str(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.summary, UTC_STR_NEW_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.location, UTC_STR_NEW_LOCATION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.description, UTC_STR_NEW_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.sync_data1, UTC_STR_NEW_SYNC_DATA1);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.organizer_name, UTC_STR_NEW_ORGANIZER_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.categories, UTC_STR_NEW_CATEGORIES);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.sync_data2, UTC_STR_NEW_SYNC_DATA2);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.sync_data3, UTC_STR_NEW_SYNC_DATA3);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.sync_data4, UTC_STR_NEW_SYNC_DATA4);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_set_new_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_set_new_int(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.calendar_book_id, UTC_INT_NEW_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.busy_status, UTC_INT_NEW_BUSY_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.event_status, UTC_INT_NEW_EVENT_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.priority, UTC_INT_NEW_PRIORITY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.sensitivity, UTC_INT_NEW_SENSITIVITY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.original_event_id, UTC_INT_NEW_ORIGINAL_EVENT_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_set_new_double
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_set_new_double(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_double(record, _calendar_instance_utime_calendar_book_extended.latitude, UTC_DOUBLE_NEW_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_double(record, _calendar_instance_utime_calendar_book_extended.longitude, UTC_DOUBLE_NEW_LONGITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_set_new_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_set_new_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};
	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_NEW_START_UTIME;
	ret = calendar_record_set_caltime(record, _calendar_instance_utime_calendar_book_extended.start_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_NEW_END_UTIME;
	ret = calendar_record_set_caltime(record, _calendar_instance_utime_calendar_book_extended.end_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_set_new
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_set_new(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_instance_utime_book_extended_set_new_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_set_new_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_set_new_double(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_set_new_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_set_mod_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_set_mod_str(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.summary, UTC_STR_MOD_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.location, UTC_STR_MOD_LOCATION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.description, UTC_STR_MOD_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.sync_data1, UTC_STR_MOD_SYNC_DATA1);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.organizer_name, UTC_STR_MOD_ORGANIZER_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.categories, UTC_STR_MOD_CATEGORIES);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.sync_data2, UTC_STR_MOD_SYNC_DATA2);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.sync_data3, UTC_STR_MOD_SYNC_DATA3);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_instance_utime_calendar_book_extended.sync_data4, UTC_STR_MOD_SYNC_DATA4);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_set_mod_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_set_mod_int(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.calendar_book_id, UTC_INT_MOD_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.busy_status, UTC_INT_MOD_BUSY_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.event_status, UTC_INT_MOD_EVENT_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.priority, UTC_INT_MOD_PRIORITY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.sensitivity, UTC_INT_MOD_SENSITIVITY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_instance_utime_calendar_book_extended.original_event_id, UTC_INT_MOD_ORIGINAL_EVENT_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_set_mod_double
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_set_mod_double(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_double(record, _calendar_instance_utime_calendar_book_extended.latitude, UTC_DOUBLE_MOD_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_double(record, _calendar_instance_utime_calendar_book_extended.longitude, UTC_DOUBLE_MOD_LONGITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_set_mod_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_set_mod_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s ct = {0};
	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_MOD_START_UTIME;
	ret = calendar_record_set_caltime(record, _calendar_instance_utime_calendar_book_extended.start_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ct.type = CALENDAR_TIME_UTIME;
	ct.time.utime = UTC_CALTIME_MOD_END_UTIME;
	ret = calendar_record_set_caltime(record, _calendar_instance_utime_calendar_book_extended.end_time, ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_set_mod
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_set_mod(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_instance_utime_book_extended_set_mod_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_set_mod_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_set_mod_double(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_set_mod_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_new_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_new_str(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str(record, _calendar_instance_utime_calendar_book_extended.summary, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SUMMARY);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_instance_utime_calendar_book_extended.location, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_LOCATION);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_instance_utime_calendar_book_extended.description, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_DESCRIPTION);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_instance_utime_calendar_book_extended.sync_data1, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA1);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_instance_utime_calendar_book_extended.organizer_name, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ORGANIZER_NAME);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_instance_utime_calendar_book_extended.categories, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_CATEGORIES);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_instance_utime_calendar_book_extended.sync_data2, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA2);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_instance_utime_calendar_book_extended.sync_data3, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA3);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_instance_utime_calendar_book_extended.sync_data4, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA4);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;


	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_new_str_p
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_new_str_p(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.summary, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.location, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_LOCATION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.description, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.sync_data1, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA1);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.organizer_name, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ORGANIZER_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.categories, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_CATEGORIES);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.sync_data2, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA2);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.sync_data3, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA3);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.sync_data4, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_SYNC_DATA4);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_new_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_new_int(calendar_record_h record)
{
	int ret = 0;
	int i = 0;
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.calendar_book_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.busy_status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_BUSY_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.event_status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_EVENT_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.priority, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_PRIORITY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.sensitivity, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_SENSITIVITY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.original_event_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_ORIGINAL_EVENT_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.event_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.has_rrule, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.has_alarm, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.has_attendee, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_new_double
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_new_double(calendar_record_h record)
{
	int ret = 0;
	double d = 0;
	ret = calendar_record_get_double(record, _calendar_instance_utime_calendar_book_extended.latitude, &d);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_double(&d, UTC_DOUBLE_NEW_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_double(record, _calendar_instance_utime_calendar_book_extended.longitude, &d);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_double(&d, UTC_DOUBLE_NEW_LONGITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_new_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_new_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s t = {0};
	calendar_time_s ct = {0};

	ret = calendar_record_get_caltime(record, _calendar_instance_utime_calendar_book_extended.start_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	t.type = CALENDAR_TIME_UTIME;
	t.time.utime = UTC_CALTIME_NEW_START_UTIME;
	ret = _check_caltime(&ct, t);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(record, _calendar_instance_utime_calendar_book_extended.end_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	t.type = CALENDAR_TIME_UTIME;
	t.time.utime = UTC_CALTIME_NEW_END_UTIME;
	ret = _check_caltime(&ct, t);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_new_lli
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_new_lli(calendar_record_h record)
{
	int ret = 0;
	long long int lli = 0;
	ret = calendar_record_get_lli(record, _calendar_instance_utime_calendar_book_extended.last_modified_time, &lli);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_new
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_new(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_instance_utime_book_extended_check_new_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_check_new_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_check_new_double(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_check_new_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_check_new_lli(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_mod_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_mod_str(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.summary, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_SUMMARY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.location, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_LOCATION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.description, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_DESCRIPTION);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.sync_data1, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_SYNC_DATA1);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.organizer_name, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ORGANIZER_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.categories, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_CATEGORIES);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.sync_data2, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_SYNC_DATA2);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.sync_data3, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_SYNC_DATA3);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_instance_utime_calendar_book_extended.sync_data4, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_SYNC_DATA4);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_mod_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_mod_int(calendar_record_h record)
{
	int ret = 0;
	int i = 0;
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.calendar_book_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_EVENT_CALENDAR_BOOK_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.busy_status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_BUSY_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.event_status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_EVENT_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.priority, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_PRIORITY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.sensitivity, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_SENSITIVITY);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_instance_utime_calendar_book_extended.original_event_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_ORIGINAL_EVENT_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_mod_double
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_mod_double(calendar_record_h record)
{
	int ret = 0;
	double d = 0;
	ret = calendar_record_get_double(record, _calendar_instance_utime_calendar_book_extended.latitude, &d);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_double(&d, UTC_DOUBLE_MOD_LATITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_double(record, _calendar_instance_utime_calendar_book_extended.longitude, &d);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_double(&d, UTC_DOUBLE_MOD_LONGITUDE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_mod_caltime
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_mod_caltime(calendar_record_h record)
{
	int ret = 0;
	calendar_time_s t = {0};
	calendar_time_s ct = {0};

	ret = calendar_record_get_caltime(record, _calendar_instance_utime_calendar_book_extended.start_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	t.type = CALENDAR_TIME_UTIME;
	t.time.utime = UTC_CALTIME_MOD_START_UTIME;
	ret = _check_caltime(&ct, t);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_get_caltime(record, _calendar_instance_utime_calendar_book_extended.end_time, &ct);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	t.type = CALENDAR_TIME_UTIME;
	t.time.utime = UTC_CALTIME_MOD_END_UTIME;
	ret = _check_caltime(&ct, t);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_instance_utime_book_extended_check_mod
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_instance_utime_book_extended_check_mod(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_instance_utime_book_extended_check_mod_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_check_mod_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_check_mod_double(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_instance_utime_book_extended_check_mod_caltime(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
