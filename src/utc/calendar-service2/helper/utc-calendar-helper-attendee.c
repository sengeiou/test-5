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
 * @testcase		utc_calendar_helper_attendee_set_new_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_set_new_str(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_str(record, _calendar_attendee.number, UTC_STR_NEW_ATTENDEE_NUMBER);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.uid, UTC_STR_NEW_ATTENDEE_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.group, UTC_STR_NEW_ATTENDEE_GROUP);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.email, UTC_STR_NEW_ATTENDEE_EMAIL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.delegatee_uri, UTC_STR_NEW_ATTENDEE_DELEGATEE_URI);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.delegator_uri, UTC_STR_NEW_ATTENDEE_DELEGATOR_URI);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.name, UTC_STR_NEW_ATTENDEE_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.member, UTC_STR_NEW_ATTENDEE_MEMBER);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_attendee_set_new_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_set_new_int(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_int(record, _calendar_attendee.cutype, UTC_INT_NEW_ATTENDEE_CUTYPE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_attendee.person_id, UTC_INT_NEW_ATTENDEE_PERSON_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_attendee.role, UTC_INT_NEW_ATTENDEE_ROLE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_attendee.status, UTC_INT_NEW_ATTENDEE_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_attendee.rsvp, UTC_INT_NEW_ATTENDEE_RSVP);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_attendee_set_new
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_set_new(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_attendee_set_new_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_set_new_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_attendee_set_mod_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_set_mod_str(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_str(record, _calendar_attendee.number, UTC_STR_MOD_ATTENDEE_NUMBER);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.uid, UTC_STR_MOD_ATTENDEE_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.group, UTC_STR_MOD_ATTENDEE_GROUP);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.email, UTC_STR_MOD_ATTENDEE_EMAIL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.delegatee_uri, UTC_STR_MOD_ATTENDEE_DELEGATEE_URI);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.delegator_uri, UTC_STR_MOD_ATTENDEE_DELEGATOR_URI);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.name, UTC_STR_MOD_ATTENDEE_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_str(record, _calendar_attendee.member, UTC_STR_MOD_ATTENDEE_MEMBER);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_attendee_set_mod_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_set_mod_int(calendar_record_h record)
{
	int ret = 0;
	ret = calendar_record_set_int(record, _calendar_attendee.cutype, UTC_INT_MOD_ATTENDEE_CUTYPE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_attendee.person_id, UTC_INT_MOD_ATTENDEE_PERSON_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_attendee.role, UTC_INT_MOD_ATTENDEE_ROLE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_attendee.status, UTC_INT_MOD_ATTENDEE_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_set_int(record, _calendar_attendee.rsvp, UTC_INT_MOD_ATTENDEE_RSVP);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_attendee_set_mod
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_set_mod(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_attendee_set_mod_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_set_mod_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_attendee_check_new_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_check_new_str(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str(record, _calendar_attendee.number, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_NUMBER);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_attendee.uid, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_UID);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_attendee.group, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_GROUP);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_attendee.email, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_EMAIL);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_attendee.delegatee_uri, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_DELEGATEE_URI);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_attendee.delegator_uri, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_DELEGATOR_URI);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_attendee.name, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_NAME);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	ret = calendar_record_get_str(record, _calendar_attendee.member, &str);
	if (CALENDAR_ERROR_NONE != ret)
		free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_MEMBER);
	free(str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	str = NULL;

	return 0;
}
/**
 * @testcase		utc_calendar_helper_attendee_check_new_str_p
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_check_new_str_p(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str_p(record, _calendar_attendee.number, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_NUMBER);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.uid, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.group, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_GROUP);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.email, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_EMAIL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.delegatee_uri, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_DELEGATEE_URI);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.delegator_uri, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_DELEGATOR_URI);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.name, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.member, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_NEW_ATTENDEE_MEMBER);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_attendee_check_new_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_check_new_int(calendar_record_h record)
{
	int ret = 0;
	int i = 0;
	ret = calendar_record_get_int(record, _calendar_attendee.cutype, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_ATTENDEE_CUTYPE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_attendee.person_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_ATTENDEE_PERSON_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_attendee.role, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_ATTENDEE_ROLE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_attendee.status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_ATTENDEE_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_attendee.rsvp, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_NEW_ATTENDEE_RSVP);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_attendee.parent_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_attendee_check_new
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_check_new(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_attendee_check_new_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_check_new_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_attendee_check_mod_str
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_check_mod_str(calendar_record_h record)
{
	int ret = 0;
	char *str = NULL;
	ret = calendar_record_get_str_p(record, _calendar_attendee.number, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ATTENDEE_NUMBER);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.uid, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ATTENDEE_UID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.group, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ATTENDEE_GROUP);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.email, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ATTENDEE_EMAIL);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.delegatee_uri, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ATTENDEE_DELEGATEE_URI);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.delegator_uri, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ATTENDEE_DELEGATOR_URI);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.name, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ATTENDEE_NAME);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_str_p(record, _calendar_attendee.member, &str);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_str(str, UTC_STR_MOD_ATTENDEE_MEMBER);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
/**
 * @testcase		utc_calendar_helper_attendee_check_mod_int
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_check_mod_int(calendar_record_h record)
{
	int ret = 0;
	int i = 0;
	ret = calendar_record_get_int(record, _calendar_attendee.cutype, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_ATTENDEE_CUTYPE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_attendee.person_id, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_ATTENDEE_PERSON_ID);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_attendee.role, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_ATTENDEE_ROLE);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_attendee.status, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_ATTENDEE_STATUS);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = calendar_record_get_int(record, _calendar_attendee.rsvp, &i);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = _check_int(&i, UTC_INT_MOD_ATTENDEE_RSVP);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_calendar_helper_attendee_check_mod
 * @since_tizen		2.3
 * @description
 */
UTC_HIDDEN int utc_calendar_helper_attendee_check_mod(calendar_record_h record)
{
	int ret = 0;
	ret = utc_calendar_helper_attendee_check_mod_str(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	ret = utc_calendar_helper_attendee_check_mod_int(record);
	assert_eq(ret, CALENDAR_ERROR_NONE);
	return 0;
}
