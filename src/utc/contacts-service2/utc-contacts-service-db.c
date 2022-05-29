//
// Copyright (c) 2015 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <stdarg.h>
#include <stdlib.h>
#include <contacts.h>

#include "assert.h"

#include "utc-contacts-service-tc-utils.h"

#define API_NAME_CONTACTS_DB_GET_RECORD "contacts_db_get_records"
#define API_NAME_CONTACTS_DB_GET_ALL_RECORDS "contacts_db_get_all_records"
#define API_NAME_CONTACTS_DB_GET_RECORDS_WITH_QUERY "contacts_db_get_records_with_query"
#define API_NAME_CONTACTS_DB_GET_CHANGES_BY_VERSION "contacts_db_get_changes_by_version"
#define API_NAME_CONTACTS_DB_GET_COUNT "contacts_db_get_count"
#define API_NAME_CONTACTS_DB_GET_COUNT_WITH_QUERY "contacts_db_get_count_with_query"
#define API_NAME_CONTACTS_DB_GET_CURRENT_VERSION "contacts_db_get_current_version"
#define API_NAME_CONTACTS_DB_GET_LAST_CHANGE_VERSION "contacts_db_get_last_change_version"
#define API_NAME_CONTACTS_DB_INSERT_RECORD "contacts_db_insert_record"
#define API_NAME_CONTACTS_DB_INSERT_RECORDS "contacts_db_insert_records"
#define API_NAME_CONTACTS_DB_UPDATE_RECORD "contacts_db_update_record"
#define API_NAME_CONTACTS_DB_UPDATE_RECORDS "contacts_db_update_records"
#define API_NAME_CONTACTS_DB_REPLACE_RECORD "contacts_db_replace_record"
#define API_NAME_CONTACTS_DB_REPLACE_RECORDS "contacts_db_replace_records"
#define API_NAME_CONTACTS_DB_DELETE_RECORD "contacts_db_delete_record"
#define API_NAME_CONTACTS_DB_DELETE_RECORDS "contacts_db_delete_records"
#define API_NAME_CONTACTS_DB_SEARCH_RECORDS "contacts_db_search_records"
#define API_NAME_CONTACTS_DB_SEARCH_RECORDS_WITH_QUERY "contacts_db_search_records_with_query"
#define API_NAME_CONTACTS_DB_SEARCH_RECORDS_WITH_RANGE "contacts_db_search_records_with_range"
#define API_NAME_CONTACTS_DB_GET_COUNT_FOR_SEARCH_RECORDS "contacts_db_get_count_for_search_records"
#define API_NAME_CONTACTS_DB_GET_COUNT_FOR_SEARCH_RECORDS_WITH_QUERY "contacts_db_get_count_for_search_records_with_query"
#define API_NAME_CONTACTS_DB_GET_COUNT_FOR_SEARCH_RECORDS_WITH_RANGE "contacts_db_get_count_for_search_records_with_range"
#define API_NAME_CONTACTS_DB_ADD_CHANGED_CB "contacts_db_add_changed_cb"
#define API_NAME_CONTACTS_DB_REMOVE_CHANGED_CB "contacts_db_remove_changed_cb"

extern ctsvc_tc_db_plugin_s _tc_db_address_book;
extern ctsvc_tc_db_plugin_s _tc_db_group;
extern ctsvc_tc_db_plugin_s _tc_db_person;
extern ctsvc_tc_db_plugin_s _tc_db_contact;
extern ctsvc_tc_db_plugin_s _tc_db_simple_contact;
extern ctsvc_tc_db_plugin_s _tc_db_my_profile;
extern ctsvc_tc_db_plugin_s _tc_db_phone_log;
extern ctsvc_tc_db_plugin_s _tc_db_result;
extern ctsvc_tc_db_plugin_s _tc_db_speeddial;
extern ctsvc_tc_db_plugin_s _tc_db_updated_info;
extern ctsvc_tc_db_plugin_s _tc_db_address;
extern ctsvc_tc_db_plugin_s _tc_db_activity;
extern ctsvc_tc_db_plugin_s _tc_db_activity_photo;
extern ctsvc_tc_db_plugin_s _tc_db_company;
extern ctsvc_tc_db_plugin_s _tc_db_email;
extern ctsvc_tc_db_plugin_s _tc_db_event;
extern ctsvc_tc_db_plugin_s _tc_db_extension;
extern ctsvc_tc_db_plugin_s _tc_db_group_relation;
extern ctsvc_tc_db_plugin_s _tc_db_messenger;
extern ctsvc_tc_db_plugin_s _tc_db_name;
extern ctsvc_tc_db_plugin_s _tc_db_nickname;
extern ctsvc_tc_db_plugin_s _tc_db_note;
extern ctsvc_tc_db_plugin_s _tc_db_number;
extern ctsvc_tc_db_plugin_s _tc_db_profile;
extern ctsvc_tc_db_plugin_s _tc_db_relationship;
extern ctsvc_tc_db_plugin_s _tc_db_url;
extern ctsvc_tc_db_plugin_s _tc_db_image;
extern ctsvc_tc_db_plugin_s _tc_db_contact_updated_info;
extern ctsvc_tc_db_plugin_s _tc_db_my_profile_updated_info;
extern ctsvc_tc_db_plugin_s _tc_db_group_updated_info;
extern ctsvc_tc_db_plugin_s _tc_db_group_member_updated_info;
extern ctsvc_tc_db_plugin_s _tc_db_grouprel_updated_info;
extern ctsvc_tc_db_plugin_s _tc_db_phone_log_stat;
extern ctsvc_tc_db_plugin_s _tc_db_sip;

static ctsvc_tc_db_plugin_s* _ctsvc_tc_get_db_plugin(ctsvc_view_e view)
{
	switch (view) {
		case VIEW_ADDRESSBOOK:
			return &_tc_db_address_book;
		case VIEW_GROUP:
			return &_tc_db_group;
		case VIEW_PERSON:
			return &_tc_db_person;
		case VIEW_SIMPLE_CONTACT:
			return &_tc_db_simple_contact;
		case VIEW_CONTACT:
			return &_tc_db_contact;
		case VIEW_MY_PROFILE:
			return &_tc_db_my_profile;
		case VIEW_NAME:
			return &_tc_db_name;
		case VIEW_NUMBER:
			return &_tc_db_number;
		case VIEW_EMAIL:
			return &_tc_db_email;
		case VIEW_ADDRESS:
			return &_tc_db_address;
		case VIEW_NOTE:
			return &_tc_db_note;
		case VIEW_URL:
			return &_tc_db_url;
		case VIEW_EVENT:
			return &_tc_db_event;
		case VIEW_GROUP_RELATION:
			return &_tc_db_group_relation;
		case VIEW_RELATIONSHIP:
			return &_tc_db_relationship;
		case VIEW_IMAGE:
			return &_tc_db_image;
		case VIEW_COMPANY:
			return &_tc_db_company;
		case VIEW_NICKNAME:
			return &_tc_db_nickname;
		case VIEW_MESSENGER:
			return &_tc_db_messenger;
		case VIEW_EXTENSION:
			return &_tc_db_extension;
		case VIEW_PROFILE:
			return &_tc_db_profile;
		case VIEW_ACTIVITY_PHOTO:
			return &_tc_db_activity_photo;
		case VIEW_ACTIVITY:
			return &_tc_db_activity;
		case VIEW_SPEEDDIAL:
			return &_tc_db_speeddial;
		case VIEW_PHONE_LOG:
			return &_tc_db_phone_log;
		case VIEW_CONTACT_UPDATED_INFO:
			return &_tc_db_contact_updated_info;
		case VIEW_MY_PROFILE_UPDATED_INFO:
			return &_tc_db_my_profile_updated_info;
		case VIEW_GROUP_UPDATED_INFO:
			return &_tc_db_group_updated_info;
		case VIEW_GROUP_MEMBER_UPDATED_INFO:
			return &_tc_db_group_member_updated_info;
		case VIEW_GROUPREL_UPDATED_INFO:
			return &_tc_db_grouprel_updated_info;
		case VIEW_PHONE_LOG_STAT:
			return &_tc_db_phone_log_stat;
		case VIEW_SIP:
			return &_tc_db_sip;
		default :
			return NULL;
	}
	return NULL;
}


static int _startup_err = 0;

/**
 * @function		utc_contacts_service2_db_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_db_startup(void)
{
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}
/**
 * @function		utc_contacts_service2_db_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_db_cleanup(void)
{
	contacts_disconnect();
}

/**
 * @testcase		utc_contacts_service2_db_get_record_p
 * @since_tizen		2.3
 * @description		Test getting a record from the contacts database.
 */
int utc_contacts_service2_db_get_record_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		ret = contacts_db_get_record(ctsvc_tc_util_get_view_uri(0), 1, &record);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_get_record) {
			ret = tc_db_plugin->db_get_record(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_get_record_n
 * @since_tizen		2.3
 * @description		Test fail getting a record from the contacts database with invalid parameters.
 */
int utc_contacts_service2_db_get_record_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	contacts_record_h record = NULL;

	ret = contacts_db_get_record(NULL, INVALID_DB_ID, &record);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_get_record(ctsvc_tc_util_get_view_uri(i), INVALID_DB_ID, &record);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

		ret = contacts_db_get_record(ctsvc_tc_util_get_view_uri(i), INVALID_DB_ID, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_all_records_p
 * @since_tizen		2.3
 * @description		Test retrieving all records and returns the results list.
 */
int utc_contacts_service2_db_get_all_records_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_list_h list = NULL;
		ret = contacts_db_get_all_records(ctsvc_tc_util_get_view_uri(0), OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_get_all_records) {
			ret = tc_db_plugin->db_get_all_records(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_all_records_n
 * @since_tizen		2.3
 * @description		Test fail retrieving all records and returns the results list with invalid parameters.
 */
int utc_contacts_service2_db_get_all_records_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	contacts_list_h list = NULL;

	ret = contacts_db_get_all_records(NULL, OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_get_all_records(ctsvc_tc_util_get_view_uri(i), OFFSET_DEFAULT, LIMIT_DEFAULT, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}



/**
 * @testcase		utc_contacts_service2_db_get_records_with_query_p
 * @since_tizen		2.3
 * @description		Test retrieving multiple records using a query.
 */
int utc_contacts_service2_db_get_records_with_query_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_list_h list = NULL;
		ret = contacts_db_get_records_with_query(NULL, OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_get_records_with_query) {
			ret = tc_db_plugin->db_get_records_with_query(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_records_with_query_n
 * @since_tizen		2.3
 * @description		Test fail retrieving multiple records using a query with invalid parameters.
 */
int utc_contacts_service2_db_get_records_with_query_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	contacts_query_h query = NULL;
	contacts_list_h list = NULL;

	ret = contacts_db_get_records_with_query(NULL, OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}


	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), &query);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_db_get_records_with_query(query, OFFSET_DEFAULT, LIMIT_DEFAULT, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

		ret = contacts_query_destroy(query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_get_changes_by_version_p
 * @since_tizen		2.3
 * @description		Test finding records based on a given keyword.
 */
int utc_contacts_service2_db_get_changes_by_version_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		int version = 0;
		ret = contacts_db_get_changes_by_version(ctsvc_tc_util_get_view_uri(0), OFFSET_DEFAULT, LIMIT_DEFAULT, NULL, &version);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_get_changes_by_version) {
			ret = tc_db_plugin->db_get_changes_by_version(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_changes_by_version_n
 * @since_tizen		2.3
 * @description		Test fail finding records based on a given keyword with invalid parameters.
 */
int utc_contacts_service2_db_get_changes_by_version_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int version = 0;
	contacts_list_h list = NULL;

	ret = contacts_db_get_changes_by_version(NULL, OFFSET_DEFAULT, LIMIT_DEFAULT, &list, &version);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_get_changes_by_version(ctsvc_tc_util_get_view_uri(i), OFFSET_DEFAULT, LIMIT_DEFAULT, NULL, &version);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

		ret = contacts_db_get_changes_by_version(ctsvc_tc_util_get_view_uri(i), OFFSET_DEFAULT, LIMIT_DEFAULT, &list, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_get_count_p
 * @since_tizen		2.3
 * @description		Test getting the number of records in a specific view.
 */
int utc_contacts_service2_db_get_count_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		int count = 0;
		ret = contacts_db_get_count(ctsvc_tc_util_get_view_uri(0), &count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_get_count) {
			ret = tc_db_plugin->db_get_count(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_count_n
 * @since_tizen		2.3
 * @description		Test fail getting the number of records in a specific view with invalid parameters.
 */
int utc_contacts_service2_db_get_count_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int count = 0;

	ret = contacts_db_get_count(NULL, &count);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_get_count(ctsvc_tc_util_get_view_uri(i), NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}



/**
 * @testcase		utc_contacts_service2_db_get_count_with_query_p
 * @since_tizen		2.3
 * @description		Test getting the number of records matching a query.
 */
int utc_contacts_service2_db_get_count_with_query_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		int count = 0;
		ret = contacts_db_get_count_with_query(NULL, &count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_get_count_with_query) {
			ret = tc_db_plugin->db_get_count_with_query(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_count_with_query_n
 * @since_tizen		2.3
 * @description		Test fail getting the number of records matching a query with invalid parameters.
 */
int utc_contacts_service2_db_get_count_with_query_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int count;
	contacts_query_h query = NULL;

	ret = contacts_db_get_count_with_query(NULL, &count);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), &query);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_db_get_count_with_query(query, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

		ret = contacts_query_destroy(query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_get_current_version_p
 * @since_tizen		2.3
 * @description		Test getting the current contacts database version.
 */
int utc_contacts_service2_db_get_current_version_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	int version = 0;

	ret = contacts_db_get_current_version(&version);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_current_version_n
 * @since_tizen		2.3
 * @description		Test fail getting the current contacts database version with invalid parameters.
 */
int utc_contacts_service2_db_get_current_version_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	ret = contacts_db_get_current_version(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_get_last_change_version_p
 * @since_tizen		2.3
 * @description		Test getting the last successful changed contacts database version on the current connection.
 */
int utc_contacts_service2_db_get_last_change_version_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	int version = 0;

	ret = contacts_db_get_last_change_version(&version);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_last_change_version_n
 * @since_tizen		2.3
 * @description		Test fail getting the last successful changed contacts database version on the current connection with invalid parameters.
 */
int utc_contacts_service2_db_get_last_change_version_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	ret = contacts_db_get_last_change_version(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_insert_record_p
 * @since_tizen		2.3
 * @description		Test inserting a record to the contacts database.
 */
int utc_contacts_service2_db_insert_record_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		int id;
		ret = contacts_db_insert_record(NULL, &id);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_insert_record) {
			ret = tc_db_plugin->db_insert_record(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_insert_record_n
 * @since_tizen		2.3
 * @description		Test fail inserting a record to the contacts database with invalid parameters.
 */
int utc_contacts_service2_db_insert_record_n(void)
{
	assert_eq(_startup_err, 0);

	int ret;
	int id;

	ret = contacts_db_insert_record(NULL, &id);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_insert_records_p
 * @since_tizen		2.3
 * @description		Test inserting multiple records to the contacts database.
 */
int utc_contacts_service2_db_insert_records_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		int *ids = NULL;
		int ids_count = 0;
		ret = contacts_db_insert_records(NULL, &ids, &ids_count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_insert_records) {
			ret = tc_db_plugin->db_insert_records(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_insert_records_n
 * @since_tizen		2.3
 * @description		Test fail inserting multiple records to the contacts database with invalid parameters.
 */
int utc_contacts_service2_db_insert_records_n(void)
{
	assert_eq(_startup_err, 0);

	int ret;
	int *ids = NULL;
	int ids_count = 0;

	ret = contacts_db_insert_records(NULL, &ids, &ids_count);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_update_record_p
 * @since_tizen		2.3
 * @description		Test updating a record in the contacts database.
 */
int utc_contacts_service2_db_update_record_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_db_update_record(NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_update_record) {
			ret = tc_db_plugin->db_update_record(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_update_record_n
 * @since_tizen		2.3
 * @description		Test fail updating a record in the contacts database with invalid parameters.
 */
int utc_contacts_service2_db_update_record_n(void)
{
	assert_eq(_startup_err, 0);

	int ret;

	ret = contacts_db_update_record(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_update_records_p
 * @since_tizen		2.3
 * @description		Test updating multiple records in the contacts database.
 */
int utc_contacts_service2_db_update_records_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_db_update_records(NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_update_records) {
			ret = tc_db_plugin->db_update_records(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_update_records_n
 * @since_tizen		2.3
 * @description		Test fail updating multiple records in the contacts database with invalid parameters.
 */
int utc_contacts_service2_db_update_records_n(void)
{
	assert_eq(_startup_err, 0);

	int ret;

	ret = contacts_db_update_records(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}



/**
 * @testcase		utc_contacts_service2_db_replace_record_p
 * @since_tizen		2.3
 * @description		Test replacing an id-identified record with the given record.
 */
int utc_contacts_service2_db_replace_record_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_db_replace_record(NULL, 0);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_replace_record) {
			ret = tc_db_plugin->db_replace_record(account_id);
			assert_eq(0, ret);
		}
	}

	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_replace_record_n
 * @since_tizen		2.3
 * @description		Test fail replacing an id-identified record with invalid parameters.
 */
int utc_contacts_service2_db_replace_record_n(void)
{
	assert_eq(_startup_err, 0);

	int ret;

	ret = contacts_db_replace_record(NULL, 0);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_replace_records_p
 * @since_tizen		2.3
 * @description		Test replacing database records identified by given ids with a given record list.
 */
int utc_contacts_service2_db_replace_records_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		int ids[2] = {0};
		int ids_count = sizeof(ids)/sizeof(int);
		ret = contacts_db_replace_records(NULL, ids, ids_count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_replace_records) {
			ret = tc_db_plugin->db_replace_records(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_replace_records_n
 * @since_tizen		2.3
 * @description		Test fail replacing database records identified by given ids with invalid parameterst.
 */
int utc_contacts_service2_db_replace_records_n(void)
{
	assert_eq(_startup_err, 0);

	int ret;
	int ids[2] = {0};
	int ids_count = sizeof(ids)/sizeof(int);
	contacts_list_h list = NULL;

	ret = contacts_db_replace_records(NULL, ids, ids_count);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	ret = contacts_list_create(&list);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_db_replace_records(list, NULL, ids_count);
	assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	ret = contacts_db_replace_records(list, ids, 0);
	assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	ret = contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_delete_record_p
 * @since_tizen		2.3
 * @description		Test deleting a record from the contacts database.
 */
int utc_contacts_service2_db_delete_record_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_db_delete_record(NULL, INVALID_DB_ID);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_delete_record) {
			ret = tc_db_plugin->db_delete_record(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_delete_record_n
 * @since_tizen		2.3
 * @description		Test fail deleting a record from the contacts database with invalid parameters.
 */
int utc_contacts_service2_db_delete_record_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;

	ret = contacts_db_delete_record(NULL, INVALID_DB_ID);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_delete_record(ctsvc_tc_util_get_view_uri(i), INVALID_DB_ID);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}




/**
 * @testcase		utc_contacts_service2_db_delete_records_p
 * @since_tizen		2.3
 * @description		Test deleting multiple records in the contacts database.
 */
int utc_contacts_service2_db_delete_records_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		int ids[2] = {0};
		int ids_count = sizeof(ids)/sizeof(int);
		ret = contacts_db_delete_records(NULL, ids, ids_count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_delete_records) {
			ret = tc_db_plugin->db_delete_records(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_delete_records_n
 * @since_tizen		2.3
 * @description		Test fail deleting multiple records in the contacts database with invalid parameters.
 */
int utc_contacts_service2_db_delete_records_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int ids[2] = {0};
	int ids_count = sizeof(ids)/sizeof(int);

	ret = contacts_db_delete_records(NULL, ids, ids_count);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_delete_records(ctsvc_tc_util_get_view_uri(i), ids, 0);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_search_records_p
 * @since_tizen		2.3
 * @description		Test finding records based on a given keyword.
 */
int utc_contacts_service2_db_search_records_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_list_h list = NULL;
		ret = contacts_db_search_records(NULL, "", OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_search_records) {
			ret = tc_db_plugin->db_search_records(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_search_records_n
 * @since_tizen		2.3
 * @description		Test fail finding records with invalid parameters.
 */
int utc_contacts_service2_db_search_records_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	contacts_list_h list = NULL;

	ret = contacts_db_search_records(NULL, "", OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_search_records(ctsvc_tc_util_get_view_uri(i), "", OFFSET_DEFAULT, LIMIT_DEFAULT, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_search_records_with_query_p
 * @since_tizen		2.3
 * @description		Test finding records based on given query and keyword.
 */
int utc_contacts_service2_db_search_records_with_query_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_list_h list = NULL;
		ret = contacts_db_search_records_with_query(NULL, "", OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_search_records_with_query) {
			ret = tc_db_plugin->db_search_records_with_query(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_search_records_with_query_n
 * @since_tizen		2.3
 * @description		Test fail finding records based on given query and keyword with invalid parameters.
 */
int utc_contacts_service2_db_search_records_with_query_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	contacts_list_h list = NULL;
	contacts_query_h query = NULL;

	ret = contacts_db_search_records_with_query(NULL, "", OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), &query);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_db_search_records_with_query(query, "", OFFSET_DEFAULT, LIMIT_DEFAULT, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

		ret = contacts_query_destroy(query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}




/**
 * @testcase		utc_contacts_service2_db_search_records_with_range_p
 * @since_tizen		2.3
 * @description		Test finding records based on a keyword and range.
 */
int utc_contacts_service2_db_search_records_with_range_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_list_h list = NULL;
		ret = contacts_db_search_records_with_range(NULL, "", OFFSET_DEFAULT, LIMIT_DEFAULT, CONTACTS_SEARCH_RANGE_DATA, &list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_search_records_with_range) {
			ret = tc_db_plugin->db_search_records_with_range(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_search_records_with_range_n
 * @since_tizen		2.3
 * @description		Test fail finding records based on a keyword and range with invalid parameters.
 */
int utc_contacts_service2_db_search_records_with_range_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	contacts_list_h list = NULL;

	ret = contacts_db_search_records_with_range(NULL, "", OFFSET_DEFAULT, LIMIT_DEFAULT, CONTACTS_SEARCH_RANGE_DATA, &list);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_search_records_with_range(ctsvc_tc_util_get_view_uri(i), "", OFFSET_DEFAULT, LIMIT_DEFAULT, 0, &list);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
		ret = contacts_db_search_records_with_range(ctsvc_tc_util_get_view_uri(i), "", OFFSET_DEFAULT, LIMIT_DEFAULT, CONTACTS_SEARCH_RANGE_DATA, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_get_count_for_search_records_p
 * @since_tizen		2.3
 * @description		Test finding records based on a given keyword.
 */
int utc_contacts_service2_db_get_count_for_search_records_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		int count = 0;
		ret = contacts_db_get_count_for_search_records(NULL, "", &count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_get_count_for_search_records) {
			ret = tc_db_plugin->db_get_count_for_search_records(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_count_for_search_records_n
 * @since_tizen		2.3
 * @description		Test fail finding records with invalid parameters.
 */
int utc_contacts_service2_db_get_count_for_search_records_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int count = 0;

	ret = contacts_db_get_count_for_search_records(NULL, "", &count);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_get_count_for_search_records(ctsvc_tc_util_get_view_uri(i), "", NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_get_count_for_search_records_with_query_p
 * @since_tizen		2.3
 * @description		Test finding records based on given query and keyword.
 */
int utc_contacts_service2_db_get_count_for_search_records_with_query_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		int count = 0;
		ret = contacts_db_get_count_for_search_records_with_query(NULL, "", &count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_get_count_for_search_records_with_query) {
			ret = tc_db_plugin->db_get_count_for_search_records_with_query(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_count_for_search_records_with_query_n
 * @since_tizen		2.3
 * @description		Test fail finding records based on given query and keyword with invalid parameters.
 */
int utc_contacts_service2_db_get_count_for_search_records_with_query_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int count = 0;
	contacts_query_h query = NULL;

	ret = contacts_db_get_count_for_search_records_with_query(NULL, "", &count);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), &query);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_db_get_count_for_search_records_with_query(query, "", NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

		ret = contacts_query_destroy(query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}




/**
 * @testcase		utc_contacts_service2_db_get_count_for_search_records_with_range_p
 * @since_tizen		2.3
 * @description		Test finding records based on a keyword and range.
 */
int utc_contacts_service2_db_get_count_for_search_records_with_range_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		int count = 0;
		ret = contacts_db_get_count_for_search_records_with_range(NULL, "", CONTACTS_SEARCH_RANGE_DATA, &count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_get_count_for_search_records_with_range) {
			ret = tc_db_plugin->db_get_count_for_search_records_with_range(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_count_for_search_records_with_range_n
 * @since_tizen		2.3
 * @description		Test fail finding records based on a keyword and range with invalid parameters.
 */
int utc_contacts_service2_db_get_count_for_search_records_with_range_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int count = 0;

	ret = contacts_db_get_count_for_search_records_with_range(NULL, "", CONTACTS_SEARCH_RANGE_DATA, &count);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_get_count_for_search_records_with_range(ctsvc_tc_util_get_view_uri(i), "", 0, &count);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
		ret = contacts_db_get_count_for_search_records_with_range(ctsvc_tc_util_get_view_uri(i), "", CONTACTS_SEARCH_RANGE_DATA, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}



/**
 * @testcase		utc_contacts_service2_db_search_records_for_snippet_p
 * @since_tizen		3.0
 * @description		Test finding records based on a given keyword.
 */
int utc_contacts_service2_db_search_records_for_snippet_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_list_h list = NULL;
		ret = contacts_db_search_records_for_snippet(NULL, "", OFFSET_DEFAULT, LIMIT_DEFAULT,
				NULL, NULL, -1, &list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_search_records_for_snippet) {
			ret = tc_db_plugin->db_search_records_for_snippet(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_search_records_for_snippet_n
 * @since_tizen		3.0
 * @description		Test fail finding records with invalid parameters.
 */
int utc_contacts_service2_db_search_records_for_snippet_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	contacts_list_h list = NULL;

	ret = contacts_db_search_records_for_snippet(NULL, "", OFFSET_DEFAULT, LIMIT_DEFAULT,
			NULL, NULL, -1, &list);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_search_records_for_snippet(ctsvc_tc_util_get_view_uri(i), "",
				OFFSET_DEFAULT, LIMIT_DEFAULT, NULL, NULL, -1, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_search_records_with_query_for_snippet_p
 * @since_tizen		3.0
 * @description		Test finding records based on given query and keyword.
 */
int utc_contacts_service2_db_search_records_with_query_for_snippet_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_list_h list = NULL;
		ret = contacts_db_search_records_with_query_for_snippet(NULL, "", OFFSET_DEFAULT,
				LIMIT_DEFAULT, NULL, NULL, -1, &list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_search_records_with_query_for_snippet) {
			ret = tc_db_plugin->db_search_records_with_query_for_snippet(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_search_records_with_query_for_snippet_n
 * @since_tizen		3.0
 * @description		Test fail finding records based on given query and keyword with invalid parameters.
 */
int utc_contacts_service2_db_search_records_with_query_for_snippet_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	contacts_list_h list = NULL;
	contacts_query_h query = NULL;

	ret = contacts_db_search_records_with_query_for_snippet(NULL, "", OFFSET_DEFAULT,
			LIMIT_DEFAULT, NULL, NULL, -1, &list);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), &query);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_db_search_records_with_query_for_snippet(query, "",
				OFFSET_DEFAULT, LIMIT_DEFAULT, NULL, NULL, -1, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

		ret = contacts_query_destroy(query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_search_records_with_range_for_snippet_p
 * @since_tizen		3.0
 * @description		Test finding records based on a keyword and range.
 */
int utc_contacts_service2_db_search_records_with_range_for_snippet_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	int account_id =0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_list_h list = NULL;
		ret = contacts_db_search_records_with_range_for_snippet(NULL, "", OFFSET_DEFAULT,
				LIMIT_DEFAULT, CONTACTS_SEARCH_RANGE_DATA, NULL, NULL, -1, &list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ctsvc_tc_util_account_insert(&account_id);
	assert_eq(0, ret);
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_search_records_with_range_for_snippet) {
			ret = tc_db_plugin->db_search_records_with_range_for_snippet(account_id);
			assert_eq(0, ret);
		}
	}
	assert_eq(0, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_search_records_with_range_for_snippet_n
 * @since_tizen		3.0
 * @description		Test fail finding records based on a keyword and range with invalid parameters.
 */
int utc_contacts_service2_db_search_records_with_range_for_snippet_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;
	contacts_list_h list = NULL;

	ret = contacts_db_search_records_with_range_for_snippet(NULL, "", OFFSET_DEFAULT,
			LIMIT_DEFAULT, CONTACTS_SEARCH_RANGE_DATA, NULL, NULL, -1, &list);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_search_records_with_range_for_snippet(ctsvc_tc_util_get_view_uri(i),
				"", OFFSET_DEFAULT, LIMIT_DEFAULT, 0, NULL, NULL, -1, &list);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
		ret = contacts_db_search_records_with_range_for_snippet(ctsvc_tc_util_get_view_uri(i),
				"", OFFSET_DEFAULT, LIMIT_DEFAULT, CONTACTS_SEARCH_RANGE_DATA,
				NULL, NULL, -1, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_add_changed_cb_p
 * @since_tizen		2.3
 * @description		Test registering a callback function to be invoked when a record changes.
 */
int utc_contacts_service2_db_add_changed_cb_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_list_h list = NULL;
		ret = contacts_db_add_changed_cb(ctsvc_tc_util_get_view_uri(0), ctsvc_tc_util_db_changed_cb, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_add_changed_cb) {
			ret = tc_db_plugin->db_add_changed_cb();
			assert_eq(0, ret);
		}
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_add_changed_cb_n
 * @since_tizen		2.3
 * @description		Test fail registering a record-change callback with invalid parameters.
 */
int utc_contacts_service2_db_add_changed_cb_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;

	ret = contacts_db_add_changed_cb(NULL, ctsvc_tc_util_db_changed_cb, NULL);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_add_changed_cb(ctsvc_tc_util_get_view_uri(i), NULL, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_remove_changed_cb_p
 * @since_tizen		2.3
 * @description		Test unregistering a callback function to be invoked when a record changes.
 */
int utc_contacts_service2_db_remove_changed_cb_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_list_h list = NULL;
		ret = contacts_db_remove_changed_cb(ctsvc_tc_util_get_view_uri(0), ctsvc_tc_util_db_changed_cb, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_db_plugin_s *tc_db_plugin = _ctsvc_tc_get_db_plugin(i);
		if (tc_db_plugin && tc_db_plugin->db_remove_changed_cb) {
			ret = tc_db_plugin->db_remove_changed_cb();
			assert_eq(0, ret);
		}
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_remove_changed_cb_n
 * @since_tizen		2.3
 * @description		Test fail unregistering a record-change callback with invalid parameters.
 */
int utc_contacts_service2_db_remove_changed_cb_n(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret;

	ret = contacts_db_remove_changed_cb(NULL, ctsvc_tc_util_db_changed_cb, NULL);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_db_remove_changed_cb(ctsvc_tc_util_get_view_uri(i), NULL, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}
