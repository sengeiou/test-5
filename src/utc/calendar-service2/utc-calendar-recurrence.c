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
#include <stdio.h>
#include <string.h>
#include <calendar.h>
#include <time.h>

#include "utc-calendar-debug.h"
#include "utc-calendar-util.h"
#include "utc-calendar-db.h"

static int g_startup_err = CALENDAR_ERROR_NONE;

/**
 * @function		utc_calendar_recurrence_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_recurrence_startup(void)
{
	g_startup_err = calendar_connect();
	if (g_startup_err != CALENDAR_ERROR_NONE) {
		if (CALENDAR_ERROR_NOT_SUPPORTED == g_startup_err
				&& false == _is_feature_supported()) {
			g_startup_err = CALENDAR_ERROR_NONE;
		} else {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "calendar_connect failed (code: %d)\n", g_startup_err);
		}
	}
	_clean_db();
}

/**
 * @function		utc_calendar_recurrence_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_recurrence_cleanup(void)
{
	_clean_db();
	calendar_disconnect();
}

time_t __get_utime(int y, int m, int d, int h, int n, int s)
{
	struct tm st = {0};
	st.tm_year = y - 1900;
	st.tm_mon = m - 1;
	st.tm_mday = d;
	st.tm_hour = h;
	st.tm_min = n;
	st.tm_sec = s;
	return mktime(&st);
}

void _create_event(calendar_record_h *out_event)
{
	calendar_record_h event = NULL;
	int ret;
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret){
		fprintf(stderr, "Calendar record create error at %s:%d\n", __FILE__, __LINE__);
		return;
	}
	const char *set_tzid = "Asia/Seoul";

	calendar_record_set_str(event, _calendar_event.start_tzid, set_tzid);
	calendar_time_s st = {0};
	st.type = CALENDAR_TIME_UTIME;
	int set_start_year = 2012;
	int set_start_month = 9;
	int set_start_mday = 3;

	calendar_record_set_str(event, _calendar_event.end_tzid, set_tzid);
	calendar_time_s et = {0};
	et.type = CALENDAR_TIME_UTIME;
	int set_end_year = 2012;
	int set_end_month = 9;
	int set_end_mday = 3;

	st.time.utime = __get_utime(set_start_year, set_start_month, set_start_mday, 10, 0, 0);
	et.time.utime = __get_utime(set_end_year, set_end_month, set_end_mday, 11, 0, 0);

	calendar_record_set_caltime(event, _calendar_event.start_time, st);
	calendar_record_set_caltime(event, _calendar_event.end_time, et);

	const char *set_summary_origin = "test_origin";
	calendar_record_set_str(event, _calendar_event.summary, set_summary_origin);
	const char *set_description = "description";
	calendar_record_set_str(event, _calendar_event.description, set_description);
	const char *set_location = "location";
	calendar_record_set_str(event, _calendar_event.location, set_location);
	const char *set_categories = "categories";
	calendar_record_set_str(event, _calendar_event.categories, set_categories);
	int set_event_status = CALENDAR_EVENT_STATUS_CONFIRMED;
	calendar_record_set_int(event, _calendar_event.event_status, set_event_status);

	int set_priority = CALENDAR_EVENT_PRIORITY_NORMAL;
	calendar_record_set_int(event, _calendar_event.priority, set_priority);
	int set_busy_status = CALENDAR_EVENT_BUSY_STATUS_BUSY;
	calendar_record_set_int(event, _calendar_event.busy_status, set_busy_status);
	int set_sensitivity = CALENDAR_SENSITIVITY_PRIVATE;
	calendar_record_set_int(event, _calendar_event.sensitivity, set_sensitivity);
	const char *set_uid = "uid";
	calendar_record_set_str(event, _calendar_event.uid, set_uid);
	const char *set_organizer_name = "organizer_name";
	calendar_record_set_str(event, _calendar_event.organizer_name, set_organizer_name);
	const char *set_organizer_email = "organizer_email";
	calendar_record_set_str(event, _calendar_event.organizer_email, set_organizer_email);
	int set_meeting_status = CALENDAR_MEETING_STATUS_MEETING;
	calendar_record_set_int(event, _calendar_event.meeting_status, set_meeting_status);
	double set_latitude = 36.7;
	calendar_record_set_double(event, _calendar_event.latitude, set_latitude);
	double set_longitude = 139.3;
	calendar_record_set_double(event, _calendar_event.longitude, set_longitude);
	int set_calendar_system_type = CALENDAR_SYSTEM_GREGORIAN;
	calendar_record_set_int(event, _calendar_event.calendar_system_type, set_calendar_system_type);
	const char *set_sync_data1 = "sync_data1";
	calendar_record_set_str(event, _calendar_event.sync_data1, set_sync_data1);
	const char *set_sync_data2 = "sync_data2";
	calendar_record_set_str(event, _calendar_event.sync_data2, set_sync_data2);
	const char *set_sync_data3 = "sync_data3";
	calendar_record_set_str(event, _calendar_event.sync_data3, set_sync_data3);
	const char *set_sync_data4 = "sync_data4";
	calendar_record_set_str(event, _calendar_event.sync_data4, set_sync_data4);

	// recurrence
	int set_freq = CALENDAR_RECURRENCE_MONTHLY;
	calendar_record_set_int(event, _calendar_event.freq, set_freq);
	int set_wkst = CALENDAR_MONDAY;
	calendar_record_set_int(event, _calendar_event.wkst, set_wkst);
	int set_interval = 1;
	calendar_record_set_int(event, _calendar_event.interval, set_interval);
	const char *set_bymonthday = "3,4,5";
	calendar_record_set_str(event, _calendar_event.bymonthday, set_bymonthday);

	int set_range_type = CALENDAR_RANGE_COUNT;
	calendar_record_set_int(event, _calendar_event.range_type, set_range_type);
	int set_count = 8;
	calendar_record_set_int(event, _calendar_event.count, set_count);

	// alarm
	calendar_record_h alarm = NULL;
	ret = calendar_record_create(_calendar_alarm._uri, &alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		fprintf(stderr, "Calendar record create error at %s:%d\n", __FILE__, __LINE__);
		calendar_record_destroy(event, true);
		return;
	}
	int set_alarm_tick = 5;
	calendar_record_set_int(alarm, _calendar_alarm.tick, set_alarm_tick);
	int set_alarm_unit = CALENDAR_ALARM_TIME_UNIT_MINUTE;
	calendar_record_set_int(alarm, _calendar_alarm.tick_unit, set_alarm_unit);
	const char *set_alarm_description = "alarm_description";
	calendar_record_set_str(alarm, _calendar_alarm.description, set_alarm_description);
	const char *set_alarm_summary = "alarm_summary";
	calendar_record_set_str(alarm, _calendar_alarm.summary, set_alarm_summary);
	int set_alarm_action = 1;
	calendar_record_set_int(alarm, _calendar_alarm.action, set_alarm_action);
	const char *set_alarm_attach = "alarm_attach";
	calendar_record_set_str(alarm, _calendar_alarm.attach, set_alarm_attach);

	calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);

	// attendee
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		fprintf(stderr, "Calendar record create error at %s:%d\n", __FILE__, __LINE__);
		calendar_record_destroy(event, true);
		calendar_record_destroy(alarm, true);
		return;
	}
	const char *set_attendee_number = "010-1234-1234";
	calendar_record_set_str(attendee, _calendar_attendee.number, set_attendee_number);
	int set_attendee_cutype = CALENDAR_ATTENDEE_CUTYPE_GROUP;
	calendar_record_set_int(attendee, _calendar_attendee.cutype, set_attendee_cutype);
	int set_attendee_person_id = 4;
	calendar_record_set_int(attendee, _calendar_attendee.person_id, set_attendee_person_id);
	const char *set_attendee_uid = "attendee_uid";
	calendar_record_set_str(attendee, _calendar_attendee.uid, set_attendee_uid);
	const char *set_attendee_group = "company";
	calendar_record_set_str(attendee, _calendar_attendee.group, set_attendee_group);
	const char *set_attendee_email = "abc@company.com";
	calendar_record_set_str(attendee, _calendar_attendee.email, set_attendee_email);
	int set_attendee_role = CALENDAR_ATTENDEE_ROLE_CHAIR;
	calendar_record_set_int(attendee, _calendar_attendee.role, set_attendee_role);
	int set_attendee_status = CALENDAR_ATTENDEE_STATUS_TENTATIVE;
	calendar_record_set_int(attendee, _calendar_attendee.status, set_attendee_status);
	int set_attendee_rsvp = 2;
	calendar_record_set_int(attendee, _calendar_attendee.rsvp, set_attendee_rsvp);
	const char *set_attendee_delegatee_uri = "Lee";
	calendar_record_set_str(attendee, _calendar_attendee.delegatee_uri, set_attendee_delegatee_uri);
	const char *set_attendee_delegator_uri = "Kim";
	calendar_record_set_str(attendee, _calendar_attendee.delegator_uri, set_attendee_delegator_uri);
	const char *set_attendee_name = "Mr.";
	calendar_record_set_str(attendee, _calendar_attendee.name, set_attendee_name);
	const char *set_attendee_member = "member";
	calendar_record_set_str(attendee, _calendar_attendee.member, set_attendee_member);

	calendar_record_add_child_record(event, _calendar_event.calendar_attendee, attendee);

	if (out_event)
		*out_event = event;
}

static int _del_instance(int event_id)
{
	int ret = 0;

	calendar_record_h get_event = NULL;
	ret = calendar_db_get_record(_calendar_event._uri, event_id, &get_event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	const char *set_exdate = "20121104T010000Z";
	ret = calendar_record_set_str(get_event, _calendar_event.exdate, set_exdate);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_db_update_record(get_event);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_destroy(get_event, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
};

static int _mod_instance(int event_id)
{
	int ret = 0;

	calendar_record_h get_event = NULL;
	ret = calendar_db_get_record(_calendar_event._uri, event_id, &get_event);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	calendar_record_h clone = NULL;
	ret = calendar_record_clone(get_event, &clone);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(clone, _calendar_event.summary, "test_mod");
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(clone, _calendar_event.original_event_id, event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(clone, _calendar_event.recurrence_id, "20121005T010000Z");
	assert_eq(ret, CALENDAR_ERROR_NONE);

	int clone_id = 0;
	ret = calendar_db_insert_record(clone, &clone_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_record_destroy(clone, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_destroy(get_event, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}

/**
 * @testcase		utc_calendar_recurrence_p
 * @since_tizen		3.0
 * @description		Test for exception in recurrence event.
 */

int utc_calendar_recurrence_p(void)
{
	int ret = 0;
	int event_id = 0;
	calendar_record_h event = NULL;

	if (false == _is_feature_supported()) {
		ret = calendar_connect();
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	_create_event(&event);
	ret = calendar_db_insert_record(event, &event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_destroy(event, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _del_instance(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _mod_instance(event_id);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	calendar_db_delete_record(_calendar_event._uri, event_id);

	return ret;
}

