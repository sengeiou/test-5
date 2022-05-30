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
#include <stdio.h>
#include <string.h>
#include <calendar.h>
#include <storage.h>

#include "utc-calendar-debug.h"
#include "utc-calendar-util.h"
#include "utc-calendar-helper-event.h"
#include "utc-calendar-helper-alarm.h"
#include "utc-calendar-helper-attendee.h"
#include "utc-calendar-helper-extended.h"

#include "tct_common.h"

#define API_NAMESPACE			"[CALENDAR-SERVICE2]"

#define UTC_VCALENDAR_STREAM_MAX 10
#define UTC_VCALENDAR_TZID "Australia/Adelaide"

typedef struct stream {
	char *key[UTC_VCALENDAR_STREAM_MAX];
	char *value[UTC_VCALENDAR_STREAM_MAX];
} stream_s;

static int g_startup_err = CALENDAR_ERROR_NONE;

static char *ics_file = "cal-tc.ics";
static char *ics_path = NULL;


/**
 * @function		utc_calendar_vcalendar_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_vcalendar_startup(void)
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
	_clean_db();

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		int ics_path_len = strlen(pszValue) + strlen(ics_file) + 6;
		ics_path = (char*)malloc(ics_path_len);
		CHECK_HANDLE(ics_path,"malloc:failure:utc_calendar_vcalendar_startup");
		snprintf(ics_path, ics_path_len, "%s/res/%s", pszValue, ics_file);
	}
	else
	{
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}
}

/**
 * @function		utc_calendar_vcalendar_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_calendar_vcalendar_cleanup(void)
{
	_clean_db();
	calendar_disconnect();

	if(ics_path)
		free(ics_path);
}

static int _check_stream(const char *stream, stream_s *r)
{
	int ret = 0;
	char *p = NULL;
	int i;
	for (i = 0; i < UTC_VCALENDAR_STREAM_MAX; i++) {
		if (NULL == r->key[i])
			break;
		p = strstr(stream, r->key[i]);
		if (p) {
			ret = strncmp(p +strlen(r->key[i]) +1, r->value[i], strlen(r->value[i]));
			assert_eq(ret, 0);
		}
	}
	return 0;
}

static int _make_stream_01(char **stream)
{
	int ret = 0;

	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	/* event */
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = utc_calendar_helper_event_set_new(event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	/* alarm */
	calendar_record_h alarm = NULL;
	ret = calendar_record_create(_calendar_alarm._uri, &alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_alarm_set_new(alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(alarm, true);
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(alarm, true);
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	/* end alarm */

	/* attendee */
	calendar_record_h attendee = NULL;
	ret = calendar_record_create(_calendar_attendee._uri, &attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_set_new(attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(attendee, true);
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_attendee, attendee);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(attendee, true);
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	/* end attendee */

	/* extended */
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_extended_set_new(extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(extended, true);
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.extended, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(extended, true);
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	/* end extended */

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_vcalendar_make_from_records(list, stream);
	calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}

static int _make_stream_02(char **stream)
{
	int ret = 0;

	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	/* extended for ver1 */
	calendar_record_h extended = NULL;
	ret = calendar_record_create(_calendar_extended_property._uri, &extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	char *extended_key = "VERSION:";
	ret = calendar_record_set_str(extended, _calendar_extended_property.key, extended_key);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(extended, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	char *extended_value = "1.0";
	ret = calendar_record_set_str(extended, _calendar_extended_property.value, extended_value);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(extended, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	/* end extended */
	ret = calendar_list_add(list, extended);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(extended, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	/* event */
	calendar_record_h event = NULL;
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(event, _calendar_event.freq, CALENDAR_RECURRENCE_YEARLY);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(event, _calendar_event.bymonth, UTC_STR_NEW_BYMONTH);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(event, _calendar_event.byday, UTC_STR_NEW_BYDAY);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(event, _calendar_event.range_type, CALENDAR_RANGE_COUNT);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	ret = calendar_record_set_int(event, _calendar_event.count, UTC_INT_NEW_COUNT);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	/* alarm */
	calendar_record_h alarm = NULL;
	ret = calendar_record_create(_calendar_alarm._uri, &alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_alarm_set_new(alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(alarm, true);
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_add_child_record(event, _calendar_event.calendar_alarm, alarm);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(alarm, true);
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	/* end alarm */

	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	/* event */
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(event, _calendar_event.start_tzid, UTC_VCALENDAR_TZID);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	ret = calendar_record_set_int(event, _calendar_event.freq, CALENDAR_RECURRENCE_MONTHLY);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(event, _calendar_event.byday, UTC_STR_NEW_BYDAY);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(event, _calendar_event.range_type, CALENDAR_RANGE_COUNT);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	ret = calendar_record_set_int(event, _calendar_event.count, UTC_INT_NEW_COUNT);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	/* event */
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(event, _calendar_event.start_tzid, UTC_VCALENDAR_TZID);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(event, _calendar_event.freq, CALENDAR_RECURRENCE_MONTHLY);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(event, _calendar_event.range_type, CALENDAR_RANGE_COUNT);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	ret = calendar_record_set_int(event, _calendar_event.count, UTC_INT_NEW_COUNT);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	/* event */
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(event, _calendar_event.freq, CALENDAR_RECURRENCE_WEEKLY);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(event, _calendar_event.range_type, CALENDAR_RANGE_COUNT);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	ret = calendar_record_set_int(event, _calendar_event.count, UTC_INT_NEW_COUNT);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);

	/* event */
	ret = calendar_record_create(_calendar_event._uri, &event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(event, _calendar_event.freq, CALENDAR_RECURRENCE_WEEKLY);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(event, _calendar_event.byday, UTC_STR_NEW_BYDAY);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(event, _calendar_event.range_type, CALENDAR_RANGE_COUNT);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	ret = calendar_record_set_int(event, _calendar_event.count, UTC_INT_NEW_COUNT);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	ret = calendar_list_add(list, event);
	if (CALENDAR_ERROR_NONE != ret) {
		calendar_record_destroy(event, true);
		calendar_list_destroy(list, true);
	}
	assert_eq(ret, CALENDAR_ERROR_NONE);


	ret = calendar_vcalendar_make_from_records(list, stream);
	calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return ret;
}

/**
 * @testcase		utc_calendar_vcalendar_make_from_records_p
 * @since_tizen		2.3
 * @description		Test retrieving a vcalendar stream from a calendar list.
 */
int utc_calendar_vcalendar_make_from_records_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;
	char *stream = NULL;

	if (false == _is_feature_supported()) {
		ret = calendar_vcalendar_make_from_records(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	/* 1st make */
	ret = _make_stream_01(&stream);
	assert_eq(ret, 0);
	/* check */
	stream_s r1 = {{"VERSION", "DTSTART", "DTEND", "ORGANIZER", "DESCRIPTION", "CATEGORIES", "TRIGGER"}, {
			"2.0",
			"TZID=Asia/Seoul:20150105T090000",
			"TZID=Asia/Seoul:20150105T100000",
			"CN=new_organizer_name:MAILTO:new_organizer_email",
			"new_description",
			"new_categories",
			"-PT5M"
		}};
	ret = _check_stream(stream, &r1);
	assert_eq(ret, 0);
	free(stream);
	stream = NULL;

	/* 2nd make */
	ret = _make_stream_02(&stream);
	assert_eq(ret, 0);
	/* check */
	stream_s r2 = {{"VERSION", "RRULE:Y", "RRULE:M"}, {
		"1.0",
		"1 1 2 MP1 1+ MO TU #5",
		"1 1+ MO TU #5",
		}};
	ret = _check_stream(stream, &r2);
	assert_eq(ret, 0);
	free(stream);
	stream = NULL;
	return 0;
}

/**
 * @testcase		utc_calendar_vcalendar_make_from_records_n
 * @since_tizen		2.3
 * @description		Test fail retrieving a vcalendar stream from a calendar list with invalid parameters.
 */
int utc_calendar_vcalendar_make_from_records_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_vcalendar_make_from_records(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	calendar_list_h list = NULL;
	ret = calendar_list_create(&list);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = calendar_vcalendar_make_from_records(list, NULL);
	calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	char *stream = NULL;
	ret = calendar_vcalendar_make_from_records(NULL, &stream);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	return 0;
}

static int _parse_ver10_alarm_fields(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART:20140721T000000Z\r\n"
		"DTEND:20140721T010000Z\r\n"
		"AALARM;TYPE=WAVE;VALUE=CONTENT-ID:19960903T060000;PT15M;4;\r\n"
		"DALARM:19960415T235000;PT5M;2;Your Taxes Are Due !!!\r\n"
		"MALARM:;TYPE=WAVE;VALUE=URL:19960415T235959; ; ; file:///mmedia/taps.wav\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;

}
static int _parse_ver10_extention_fields(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"TZ:+09\r\n"
		"BEGIN:VEVENT\r\n"
		"SUMMARY;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:Hydro-Qu=C3=A9bec\r\n"
		"DESCRIPTION;ENCODING=BASE64:ZGVzY3JpcHRpb24=\r\n"
		"DTSTART:20140721T000000Z\r\n"
		"DTEND:20140721T010000Z\r\n"
		"PRIORITY:1\r\n"
		"CATEGORIES:APPOINTMENT\r\n"
		"DCREATED:20140720T082814Z\r\n"
		"X-CALENDARGROUP:1\r\n"
		"X-ALLDAY:SET\r\n"
		"X-LUNAR:UNSET\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;

}
static int _parse_ver20_timezone_fields(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VTIMEZONE\r\n"
		"TZID:US-Eastern\r\n"
		"BEGIN:STANDARD\r\n"
		"DTSTART:19981025T020000\r\n"
		"RDATE:19981025T020000\r\n"
		"TZOFFSETFROM:-0400\r\n"
		"TZOFFSETTO:-0500\r\n"
		"TZNAME:EST\r\n"
		"END:STANDARD\r\n"
		"BEGIN:DAYLIGHT\r\n"
		"DTSTART:19990404T020000\r\n"
		"RDATE:19990404T020000\r\n"
		"TZOFFSETFROM:-0500\r\n"
		"TZOFFSETTO:-0400\r\n"
		"TZNAME:EDT\r\n"
		"END:DAYLIGHT\r\n"
		"END:VTIMEZONE\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_timezone._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver20_event_fields(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=Asia/Seoul:20150105T000000\r\n"
		"DTEND;TZID=Asia/Seoul:20150105T010000\r\n"
		"SUMMARY:"UTC_STR_NEW_SUMMARY"\r\n"
		"ORGANIZER;ROLE=CHAIR:MAILTO:mrbig@host.com\r\n"
		"CLASS:PUBLIC\r\n"
		"CREATED:19980309T130000Z\r\n"
		"LOCATION:LDB Lobby\r\n"
		"CATEGORIES:MEETING,PROJECT\r\n"
		"RIORITY:5\r\n"
		"CREATED:20150104T082814Z\r\n"
		"LAST-MODIFIED:20150104T082814Z\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver20_vfreebusy_fields(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"PRODID:-//RDU Software//NONSGML HandCal//EN\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VFREEBUSY\r\n"
		"ORGANIZER:MAILTO:jane_doe@host1.com\r\n"
		"ATTENDEE:MAILTO:john_public@host2.com\r\n"
		"DTSTART:19971015T050000Z\r\n"
		"DTEND:19971016T050000Z\r\n"
		"DTSTAMP:19970901T083000Z\r\n"
		"END:VFREEBUSY\r\n"
		"BEGIN:VJOURNAL\r\n"
		"DTSTAMP:19970324T120000Z\r\n"
		"UID:uid5@host1.com\r\n"
		"ORGANIZER:MAILTO:jsmith@host.com\r\n"
		"STATUS:DRAFT\r\n"
		"CLASS:PUBLIC\r\n"
		"CATEGORY:Project Report, XYZ, Weekly Meeting\r\n"
		"END:VJOURNAL\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19980312T083000\r\n"
		"DTEND;TZID=US-Eastern:19980312T093000\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver20_attendee_fields(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=Asia/Seoul:20150105T000000\r\n"
		"DTEND;TZID=Asia/Seoul:20150105T010000\r\n"
		"ATTENDEE;RSVP=TRUE;ROLE=REQ-PARTICIPANT;CUTYPE=GROUP;PARTSTAT=DELEGAT\r\n"
		" ED;DELEGATED-FROM=\"MAILTO:immud@host3.com\";DELEGATED-TO=\"MAILTO:h\r\n"
		" cabot@host2.com\";CN=The Big Cheese;MEMBER=\"MAILTO:ietf-calsch@imc.\r\n"
		" org\":MAILTO:employee-A@host.com\r\n"
		"ATTENDEE;CUTYPE=INDIVIDUAL;ROLE=OPT-PARTICIPANT;PARTSTAT=NEEDS-ACTION\r\n"
		" :MAILTO:employee-A@host.com\r\n"
		"ATTENDEE;CUTYPE=RESOURCE;ROLE=NON-PARTICIPANT;PARTSTAT=ACCEPTED:MAILT\r\n"
		" O:employee-A@host.com\r\n"
		"ATTENDEE;CUTYPE=ROOM;ROLE=CHAIR:MAILTO;PARTSTAT=DECLINED:employee-A@h\r\n"
		" ost.com\r\n"
		"ATTENDEE;CUTYPE=UNKNOWN;PARTSTAT=COMPLETED:MAILTO:employee-A@host.com\r\n"
		"ATTENDEE;CUTYPE=UNKNOWN;PARTSTAT=IN-PROCESS:MAILTO:employee-A@host.com\r\n"
		"ATTENDEE;CUTYPE=UNKNOWN;PARTSTAT=TENTATIVE:MAILTO:employee-A@host.com\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver20_alarm_fields(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=Asia/Seoul:20150105T000000\r\n"
		"DTEND;TZID=Asia/Seoul:20150105T010000\r\n"
		"BEGIN:VALARM\r\n"
		"ACTION:AUDIO\r\n"
		"TRIGGER:19980403T120000\r\n"
		"ATTACH;FMTTYPE=audio/basic:http://host.com/pub/audio-\r\n"
		" files/ssbanner.aud\r\n"
		"REPEAT:4\r\n"
		"DURATION:PT1H\r\n"
		"SUMMARY:alarm\r\n"
		"DESCRIPTION:description\r\n"
		"END:VALARM\r\n"
		"BEGIN:VALARM\r\n"
		"TRIGGE;RELATED=END:-PT30S\r\n"
		"END:VALARM\r\n"
		"BEGIN:VALARM\r\n"
		"TRIGGER;RELATED=START:-PT30M\r\n"
		"END:VALARM\r\n"
		"BEGIN:VALARM\r\n"
		"TRIGGER:-PT1H\r\n"
		"END:VALARM\r\n"
		"END:VEVENT\r\n"
		"BEGIN:VALARM\r\n"
		"TRIGGER:-PT7D\r\n"
		"END:VALARM\r\n"
		"BEGIN:VALARM\r\n"
		"TRIGGER:-PT1W\r\n"
		"END:VALARM\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver20_todo_fields(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VTODO\r\n"
		"DTSTAMP:19980130T134500Z\r\n"
		"SEQUENCE:2\r\n"
		"CATEGORIES:APPOINTMENT\r\n"
		"DUE:19980415T235959\r\n"
		"STATUS:COMPLETED\r\n"
		"SUMMARY:Submit Income Taxes\r\n"
		"END:VTODO\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_todo._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver20_exception_words(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=Asia/Seoul:20150105T000000\r\n"
		"DTEND;TZID=Asia/Seoul:20150105T010000\r\n"
		"DESCRIPTION:semi-colon\\; slash\\/ colon\\: comma\\, line-feed\\n \\N\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver20_lunar(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=Asia/Seoul:20150105T000000\r\n"
		"DTEND;TZID=Asia/Seoul:20150105T010000\r\n"
		"X-LUNAR:SET\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 * (1998 9:00 AM EST)February 13;March 13;November 13
 * (1999 9:00 AM EDT)August 13
 * (2000 9:00 AM EDT)October 13
 */
static int _parse_ver20_exdate(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970902T090000\r\n"
		"DTEND;TZID=US-Eastern:19970902T100000\r\n"
		"EXDATE:19970902T090000Z\r\n"
		"RRULE:FREQ=MONTHLY;BYDAY=FR;BYMONTHDAY=13\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return ret;
}
static int _parse_ver20_recurrence_id(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970902T090000\r\n"
		"DTEND;TZID=US-Eastern:19970902T100000\r\n"
		"RRULE:FREQ=MONTHLY;BYDAY=FR;BYMONTHDAY=13\r\n"
		"RECURRENCE-ID;VALUE=DATE:19970401\r\n"
		"RECURRENCE-ID;RANGE=THISANDFUTURE:19970120T120000Z\r\n"
		"RECURRENCE-ID;RANGE=THISANDPRIOR:19970401T133000Z\r\n"
		"RECURRENCE-ID;TZID=Asia/Seoul:20170106T090000\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return ret;
}

static int _parse_ver10_once(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART:19960401T033000Z\r\n"
		"DTEND:19960401T043000Z\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver10_daily(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART:19960401T033000Z\r\n"
		"DTEND:19960401T043000Z\r\n"
		"RRULE:D1 #10\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver10_weekly(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART:19960401T033000Z\r\n"
		"DTEND:19960401T043000Z\r\n"
		"RRULE:W2 TU TH\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;

}
static int _parse_ver10_monthly_bymonthly(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART:19960401T033000Z\r\n"
		"DTEND:19960401T043000Z\r\n"
		"RRULE:MD1 2- #5\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;

}
static int _parse_ver10_monthly_byday(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART:19960401T033000Z\r\n"
		"DTEND:19960401T043000Z\r\n"
		"RRULE:MP2 1+ 1- FR #3\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;

}
static int _parse_ver10_yearly_bymonth(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART:19960401T033000Z\r\n"
		"DTEND:19960401T043000Z\r\n"
		"RRULE:YM1 6 7 #8\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;

}
static int _parse_ver10_yearly_byyearday(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART:19960401T033000Z\r\n"
		"DTEND:19960401T043000Z\r\n"
		"RRULE:YD1 1 100 #5 D1 #5\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver10_yearly_byweekno(void)
{
	return 0;
}
static int _parse_ver10_yearly_bymonthly(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART:19960401T033000Z\r\n"
		"DTEND:19960401T043000Z\r\n"
		"RRULE:YM1 6 9 10 #10 MP1 1+ 2+ 3+ 4+ 1- SA SU #1\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
static int _parse_ver10_yearly_byday(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:1.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART:19960401T033000Z\r\n"
		"DTEND:19960401T043000Z\r\n"
		"RRULE:YM1 6 #10 W1 TU TH #4\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;


}
static int _parse_ver20_once(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=Asia/Seoul:20150105T000000\r\n"
		"DTEND;TZID=Asia/Seoul:20150105T010000\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 *  (1997 9:00 AM EDT)September 2-11
 */
static int _parse_ver20_daily(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970902T090000\r\n"
		"DTEND;TZID=US-Eastern:19970902T100000\r\n"
		"RRULE:FREQ=DAILY;COUNT=10\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 * (1997 9:00 AM EDT)September 2,9,16,23,30;October 7,14,21
 * (1997 9:00 AM EST)October 28;November 4
 */
static int _parse_ver20_weekly(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970902T090000\r\n"
		"DTEND;TZID=US-Eastern:19970902T100000\r\n"
		"RRULE:FREQ=WEEKLY;COUNT=10\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 * (1997 9:00 AM EDT)September 28
 * (1997 9:00 AM EST)October 29;November 28;December 29
 * (1998 9:00 AM EST)January 29;February 26
 */
static int _parse_ver20_monthly_bymonthly(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970928T090000\r\n"
		"DTEND;TZID=US-Eastern:19970928T100000\r\n"
		"RRULE:FREQ=MONTHLY;BYMONTHDAY=-3\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 * (1997 9:00 AM EDT)September 2,9,16,23,30
 * (1997 9:00 AM EST)November 4,11,18,25
 * (1998 9:00 AM EST)January 6,13,20,27;March 3,10,17,24,31
 */
static int _parse_ver20_monthly_byday_TU(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970902T090000\r\n"
		"DTEND;TZID=US-Eastern:19970902T100000\r\n"
		"RRULE:FREQ=MONTHLY;INTERVAL=2;BYDAY=TU\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 * (1997 9:00 AM EDT)September 5;October 3
 * (1997 9:00 AM EST)November 7;Dec 5
 * (1998 9:00 AM EST)January 2;February 6;March 6;April 3
 * (1998 9:00 AM EDT)May 1;June 5
 */
static int _parse_ver20_monthly_byday_1FR(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970905T090000\r\n"
		"DTEND;TZID=US-Eastern:19970905T100000\r\n"
		"RRULE:FREQ=MONTHLY;COUNT=10;BYDAY=1FR\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 * (1997 9:00 AM EDT)September 29
 * (1997 9:00 AM EST)October 30;November 27;December 30
 * (1998 9:00 AM EST)January 29;February 26;March 30
 */
static int _parse_ver20_monthly_byday_bysetpos(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970929T090000\r\n"
		"DTEND;TZID=US-Eastern:19970929T100000\r\n"
		"RRULE:FREQ=MONTHLY;BYDAY=MO,TU,WE,TH,FR;BYSETPOS=-2\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 * (1997 9:00 AM EDT)June 10;July 10
 * (1998 9:00 AM EDT)June 10;July 10
 * (1999 9:00 AM EDT)June 10;July 10
 * (2000 9:00 AM EDT)June 10;July 10
 * (2001 9:00 AM EDT)June 10;July 10
 */
static int _parse_ver20_yearly_bymonth(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970610T090000\r\n"
		"DTEND;TZID=US-Eastern:19970610T100000\r\n"
		"RRULE:FREQ=YEARLY;COUNT=10;BYMONTH=6,7\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 * (1997 9:00 AM EST)January 1
 * (1997 9:00 AM EDT)April 10;July 19
 * (2000 9:00 AM EST)January 1
 * (2000 9:00 AM EDT)April 9;July 18
 * (2003 9:00 AM EST)January 1
 * (2003 9:00 AM EDT)April 10;July 19
 * (2006 9:00 AM EST)January 1
 */
static int _parse_ver20_yearly_byyearday(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970101T090000\r\n"
		"DTEND;TZID=US-Eastern:19970101T100000\r\n"
		"RRULE:FREQ=YEARLY;INTERVAL=3;COUNT=10;BYYEARDAY=1,100,200\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	free(ids);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return ret;
}
/*
 * (1997 9:00 AM EDT)May 12
 * (1998 9:00 AM EDT)May 11
 * (1999 9:00 AM EDT)May 17
 */
static int _parse_ver20_yearly_byweekno(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970512T090000\r\n"
		"DTEND;TZID=US-Eastern:19970512T100000\r\n"
		"RRULE:FREQ=YEARLY;BYWEEKNO=20;BYDAY=MO\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 * (1996 9:00 AM EST)November 5
 * (2000 9:00 AM EST)November 7
 * (2004 9:00 AM EST)November 2
 */
static int _parse_ver20_yearly_bymonthly(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19961105T090000\r\n"
		"DTEND;TZID=US-Eastern:19961105T100000\r\n"
		"RRULE:FREQ=YEARLY;INTERVAL=4;BYMONTH=11;BYDAY=TU;BYMONTHDAY=2,3,4,5,6,7,8;COUNT=10\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}
/*
 * (1997 9:00 AM EDT)May 19
 * (1998 9:00 AM EDT)May 18
 * (1999 9:00 AM EDT)May 17
 */
static int _parse_ver20_yearly_byday(void)
{
	DBG("[%s]", __func__);

	int ret = 0;
	int *ids = NULL;
	int count = 0;
	calendar_list_h list = NULL;

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"BEGIN:VEVENT\r\n"
		"DTSTART;TZID=US-Eastern:19970519T090000\r\n"
		"DTEND;TZID=US-Eastern:19970519T100000\r\n"
		"RRULE:FREQ=YEARLY;BYDAY=20MO\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";
	ret = calendar_vcalendar_parse_to_calendar(stream, &list);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_insert_records(list, &ids, &count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_db_delete_records(_calendar_event._uri, ids, count);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_list_destroy(list, true);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	free(ids);
	return ret;
}

/**
 * @testcase		utc_calendar_vcalendar_parse_to_calendar_p
 * @since_tizen		2.3
 * @description		Test retrieving all calendars from a vcalendar stream.
 */
int utc_calendar_vcalendar_parse_to_calendar_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_vcalendar_parse_to_calendar(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _parse_ver10_alarm_fields();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver10_extention_fields();
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _parse_ver20_timezone_fields();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_event_fields();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_vfreebusy_fields();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_attendee_fields();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_alarm_fields();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_todo_fields();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_exception_words();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_lunar();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_exdate();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_recurrence_id();
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _parse_ver10_once();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver10_daily();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver10_weekly();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver10_monthly_bymonthly();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver10_monthly_byday();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver10_yearly_bymonth();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver10_yearly_byyearday();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver10_yearly_byweekno();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver10_yearly_bymonthly();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver10_yearly_byday();
	assert_eq(ret, CALENDAR_ERROR_NONE);

	ret = _parse_ver20_once();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_daily();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_weekly();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_monthly_bymonthly();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_monthly_byday_TU();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_monthly_byday_1FR();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_monthly_byday_bysetpos();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_yearly_bymonth();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_yearly_byyearday();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_yearly_byweekno();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_yearly_bymonthly();
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _parse_ver20_yearly_byday();
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

int utc_calendar_vcalendar_parse_to_calendar_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_vcalendar_parse_to_calendar(NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	const char *stream = "BEGIN:VCALENDAR\r\n"
		"VERSION:2.0\r\n"
		"PRODID:-//hacksw/handcal//NONSGML v1.0//EN\r\n"
		"BEGIN:VEVENT\r\n"
		"UID:19970610T172345Z-AF23B2@example.com\r\n"
		"DTSTAMP:19970610T172345Z\r\n"
		"SUMMARY:"UTC_STR_NEW_SUMMARY"\r\n"
		"DTSTART:"UTC_CALTIME_NEW_START_STRING"\r\n"
		"DTEND:"UTC_CALTIME_NEW_END_STRING"\r\n"
		"END:VEVENT\r\n"
		"END:VCALENDAR\r\n";

	// case 1
	ret = calendar_vcalendar_parse_to_calendar(stream, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	calendar_list_h list = NULL;
	ret = calendar_vcalendar_parse_to_calendar(NULL, &list);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool __utc_calendar_service2_vcalendar_cb(calendar_record_h record, void *user_data)
{
	return true;
}

/**
 * @testcase		utc_calendar_vcalendar_parse_to_calendar_foreach_p
 * @since_tizen		2.3
 * @description		Test retrieving all events or to-dos.
 */
int utc_calendar_vcalendar_parse_to_calendar_foreach_p(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);

	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_vcalendar_parse_to_calendar_foreach(NULL, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = calendar_vcalendar_parse_to_calendar_foreach(ics_path, __utc_calendar_service2_vcalendar_cb, NULL);
	assert_eq(ret, CALENDAR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_calendar_vcalendar_parse_to_calendar_foreach_n
 * @since_tizen		2.3
 * @description		Test fail retrieving all events or to-dos with invalid parameters.
 */
int utc_calendar_vcalendar_parse_to_calendar_foreach_n(void)
{
	assert_eq(g_startup_err, CALENDAR_ERROR_NONE);
	int ret = 0;

	if (false == _is_feature_supported()) {
		ret = calendar_vcalendar_parse_to_calendar_foreach(NULL, NULL, NULL);
		assert_eq(ret, CALENDAR_ERROR_NOT_SUPPORTED);
		return 0;
	}

	// case 1
	ret = calendar_vcalendar_parse_to_calendar_foreach(ics_path, NULL, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);

	// case 2
	ret = calendar_vcalendar_parse_to_calendar_foreach(NULL, __utc_calendar_service2_vcalendar_cb, NULL);
	assert_eq(ret, CALENDAR_ERROR_INVALID_PARAMETER);
	return 0;
}
