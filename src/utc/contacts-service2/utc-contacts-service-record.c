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

#define API_NAME_CONTACTS_RECORD_CLONE "contacts_record_clone"
#define API_NAME_CONTACTS_RECORD_CREATE "contacts_record_create"
#define API_NAME_CONTACTS_RECORD_DESTROY "contacts_record_destroy"
#define API_NAME_CONTACTS_RECORD_GET_URI_P "contacts_record_get_uri_p"
#define API_NAME_CONTACTS_RECORD_ADD_CHILD_RECORD "contacts_record_add_child_record"
#define API_NAME_CONTACTS_RECORD_CLONE_CHILD_RECORD_LIST "contacts_record_clone_child_record_list"
#define API_NAME_CONTACTS_RECORD_REMOVE_CHILD_RECORD "contacts_record_remove_child_record"
#define API_NAME_CONTACTS_RECORD_GET_CHILD_RECORD_AT_P "contacts_record_get_child_record_at_p"
#define API_NAME_CONTACTS_RECORD_GET_CHILD_RECORD_COUNT "contacts_record_get_child_record_count"
#define API_NAME_CONTACTS_RECORD_GET_BOOL "contacts_record_get_bool"
#define API_NAME_CONTACTS_RECORD_GET_DOUBLE "contacts_record_get_double"
#define API_NAME_CONTACTS_RECORD_GET_INT "contacts_record_get_int"
#define API_NAME_CONTACTS_RECORD_GET_LLI "contacts_record_get_lli"
#define API_NAME_CONTACTS_RECORD_GET_STR "contacts_record_get_str"
#define API_NAME_CONTACTS_RECORD_GET_STR_P "contacts_record_get_str_p"
#define API_NAME_CONTACTS_RECORD_SET_BOOL "contacts_record_set_bool"
#define API_NAME_CONTACTS_RECORD_SET_DOUBLE "contacts_record_set_double"
#define API_NAME_CONTACTS_RECORD_SET_INT "contacts_record_set_int"
#define API_NAME_CONTACTS_RECORD_SET_LLI "contacts_record_set_lli"
#define API_NAME_CONTACTS_RECORD_SET_STR "contacts_record_set_str"

extern ctsvc_tc_record_plugin_s _tc_record_address_book;
extern ctsvc_tc_record_plugin_s _tc_record_group;
extern ctsvc_tc_record_plugin_s _tc_record_person;
extern ctsvc_tc_record_plugin_s _tc_record_contact;
extern ctsvc_tc_record_plugin_s _tc_record_simple_contact;
extern ctsvc_tc_record_plugin_s _tc_record_my_profile;
extern ctsvc_tc_record_plugin_s _tc_record_phone_log;
extern ctsvc_tc_record_plugin_s _tc_record_result;
extern ctsvc_tc_record_plugin_s _tc_record_speeddial;
extern ctsvc_tc_record_plugin_s _tc_record_updated_info;
extern ctsvc_tc_record_plugin_s _tc_record_address;
extern ctsvc_tc_record_plugin_s _tc_record_activity;
extern ctsvc_tc_record_plugin_s _tc_record_activity_photo;
extern ctsvc_tc_record_plugin_s _tc_record_company;
extern ctsvc_tc_record_plugin_s _tc_record_email;
extern ctsvc_tc_record_plugin_s _tc_record_event;
extern ctsvc_tc_record_plugin_s _tc_record_extension;
extern ctsvc_tc_record_plugin_s _tc_record_group_relation;
extern ctsvc_tc_record_plugin_s _tc_record_messenger;
extern ctsvc_tc_record_plugin_s _tc_record_name;
extern ctsvc_tc_record_plugin_s _tc_record_nickname;
extern ctsvc_tc_record_plugin_s _tc_record_note;
extern ctsvc_tc_record_plugin_s _tc_record_number;
extern ctsvc_tc_record_plugin_s _tc_record_profile;
extern ctsvc_tc_record_plugin_s _tc_record_relationship;
extern ctsvc_tc_record_plugin_s _tc_record_url;
extern ctsvc_tc_record_plugin_s _tc_record_image;
extern ctsvc_tc_record_plugin_s _tc_record_contact_updated_info;
extern ctsvc_tc_record_plugin_s _tc_record_my_profile_updated_info;
extern ctsvc_tc_record_plugin_s _tc_record_group_updated_info;
extern ctsvc_tc_record_plugin_s _tc_record_group_member_updated_info;
extern ctsvc_tc_record_plugin_s _tc_record_grouprel_updated_info;
extern ctsvc_tc_record_plugin_s _tc_record_phone_log_stat;
extern ctsvc_tc_record_plugin_s _tc_record_sdn;

static ctsvc_tc_record_plugin_s* _ctsvc_tc_get_record_plugin(ctsvc_view_e view)
{
	switch (view) {
		case VIEW_ADDRESSBOOK:
			return &_tc_record_address_book;
		case VIEW_GROUP:
			return &_tc_record_group;
		case VIEW_PERSON:
			return &_tc_record_person;
		case VIEW_SIMPLE_CONTACT:
			return &_tc_record_simple_contact;
		case VIEW_CONTACT:
			return &_tc_record_contact;
		case VIEW_MY_PROFILE:
			return &_tc_record_my_profile;
		case VIEW_NAME:
			return &_tc_record_name;
		case VIEW_NUMBER:
			return &_tc_record_number;
		case VIEW_EMAIL:
			return &_tc_record_email;
		case VIEW_ADDRESS:
			return &_tc_record_address;
		case VIEW_NOTE:
			return &_tc_record_note;
		case VIEW_URL:
			return &_tc_record_url;
		case VIEW_EVENT:
			return &_tc_record_event;
		case VIEW_GROUP_RELATION:
			return &_tc_record_group_relation;
		case VIEW_RELATIONSHIP:
			return &_tc_record_relationship;
		case VIEW_IMAGE:
			return &_tc_record_image;
		case VIEW_COMPANY:
			return &_tc_record_company;
		case VIEW_NICKNAME:
			return &_tc_record_nickname;
		case VIEW_MESSENGER:
			return &_tc_record_messenger;
		case VIEW_EXTENSION:
			return &_tc_record_extension;
		case VIEW_SDN:
			return &_tc_record_sdn;
		case VIEW_PROFILE:
			return &_tc_record_profile;
		case VIEW_ACTIVITY_PHOTO:
			return &_tc_record_activity_photo;
		case VIEW_ACTIVITY:
			return &_tc_record_activity;
		case VIEW_SPEEDDIAL:
			return &_tc_record_speeddial;
		case VIEW_PHONE_LOG:
			return &_tc_record_phone_log;
		case VIEW_CONTACT_UPDATED_INFO: // readonly
			return &_tc_record_contact_updated_info;
		case VIEW_MY_PROFILE_UPDATED_INFO: // readonly
			return &_tc_record_my_profile_updated_info;
		case VIEW_GROUP_UPDATED_INFO: // readonly
			return &_tc_record_group_updated_info;
		case VIEW_GROUP_MEMBER_UPDATED_INFO: // readonly
			return &_tc_record_group_member_updated_info;
		case VIEW_GROUPREL_UPDATED_INFO: // readonly
			return &_tc_record_grouprel_updated_info;
		case VIEW_PHONE_LOG_STAT: // readonly
			return &_tc_record_phone_log_stat;
			return NULL;
		default :
			return NULL;
	}
	return NULL;
}

static int _startup_err = 0;

/**
 * @function		utc_contacts_service2_record_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_record_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_record_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_record_cleanup(void)
{
	contacts_disconnect();
}


/**
 * @function		utc_contacts_service2_record_free_properties
 * @description		Frees properties of all views
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_record_free_properties()
{
	int i;
	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_record_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_record_plugin && tc_record_plugin->free_properties) {
			tc_record_plugin->free_properties();
		}
	}
}

/**
 * @testcase		utc_contacts_service2_record_clone_p
 * @since_tizen		2.3
 * @description		Makes a clone of a record.
 */
int utc_contacts_service2_record_clone_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		contacts_record_h record_clone = NULL;
		ret = contacts_record_clone(record, &record_clone);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->clone) {
			ret = tc_db_plugin->clone();
			assert_eq(0, ret);
		}
	}
	return 0;
}
/**
 * @testcase		utc_contacts_service2_record_create_p
 * @since_tizen		2.3
 * @description		Creates a record.
 */
int utc_contacts_service2_record_create_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		ret = contacts_record_create(ctsvc_tc_util_get_view_uri(0), &record);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->create) {
			ret = tc_db_plugin->create();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_destroy_p
 * @since_tizen		2.3
 * @description		Destroys a record and releases its all resources.
 */
int utc_contacts_service2_record_destroy_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		ret = contacts_record_destroy(record, true);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->destroy) {
			ret = tc_db_plugin->destroy();
			assert_eq(0, ret);
		}
	}
	return 0;
}


/**
 * @testcase		utc_contacts_service2_record_get_uri_p_p
 * @since_tizen		2.3
 * @description		Gets URI string from a record.
 */
int utc_contacts_service2_record_get_uri_p_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		const char *uri = NULL;
		ret = contacts_record_get_uri_p(record, &uri);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->get_uri_p) {
			ret = tc_db_plugin->get_uri_p();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_add_child_record_p
 * @since_tizen		2.3
 * @description		Adds a child record to the parent record.
 */
int utc_contacts_service2_record_add_child_record_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		ret = contacts_record_add_child_record(record, INVALID_PROPERTY_ID, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->add_child_record) {
			ret = tc_db_plugin->add_child_record();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_clone_child_record_list_p
 * @since_tizen		2.3
 * @description		Clones a child record list of the given parent record.
 */
int utc_contacts_service2_record_clone_child_record_list_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		ret = contacts_record_clone_child_record_list(record, INVALID_PROPERTY_ID, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->clone_child_record_list) {
			ret = tc_db_plugin->clone_child_record_list();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_remove_child_record_p
 * @since_tizen		2.3
 * @description		Removes a child record from the parent record.
 */
int utc_contacts_service2_record_remove_child_record_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		ret = contacts_record_remove_child_record(record, INVALID_PROPERTY_ID, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->remove_child_record) {
			ret = tc_db_plugin->remove_child_record();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_child_record_at_p_p
 * @since_tizen		2.3
 * @description		Gets a child record handle pointer from the parent record.
 */
int utc_contacts_service2_record_get_child_record_at_p_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		ret = contacts_record_get_child_record_at_p(record, INVALID_PROPERTY_ID, 0, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->get_child_record_at_p) {
			ret = tc_db_plugin->get_child_record_at_p();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_child_record_count_p
 * @since_tizen		2.3
 * @description		Gets the number of child records of a parent record.
 */
int utc_contacts_service2_record_get_child_record_count_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		int count = 0;
		ret = contacts_record_get_child_record_count(record, INVALID_PROPERTY_ID, &count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->get_child_record_count) {
			ret = tc_db_plugin->get_child_record_count();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_bool_p
 * @since_tizen		2.3
 * @description		Gets a record's boolean value.
 */
int utc_contacts_service2_record_get_bool_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		bool value;
		ret = contacts_record_get_bool(record, INVALID_PROPERTY_ID, &value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->get_bool) {
			ret = tc_db_plugin->get_bool();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_double_p
 * @since_tizen		2.3
 * @description		Gets a record's double value.
 */
int utc_contacts_service2_record_get_double_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		double value;
		ret = contacts_record_get_double(record, INVALID_PROPERTY_ID, &value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->get_double) {
			ret = tc_db_plugin->get_double();
			assert_eq(0, ret);
		}
	}
	return 0;

}

/**
 * @testcase		utc_contacts_service2_record_get_int_p
 * @since_tizen		2.3
 * @description		Gets a record's integer value.
 */
int utc_contacts_service2_record_get_int_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		int value;
		ret = contacts_record_get_int(record, INVALID_PROPERTY_ID, &value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->get_int) {
			ret = tc_db_plugin->get_int();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_lli_p
 * @since_tizen		2.3
 * @description		Gets a record's long long integer value.
 */
int utc_contacts_service2_record_get_lli_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		long long int value;
		ret = contacts_record_get_lli(record, INVALID_PROPERTY_ID, &value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->get_lli) {
			ret = tc_db_plugin->get_lli();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_str_p
 * @since_tizen		2.3
 * @description		Gets a record's string value.
 */
int utc_contacts_service2_record_get_str_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		char *value;
		ret = contacts_record_get_str(record, INVALID_PROPERTY_ID, &value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->get_str) {
			ret = tc_db_plugin->get_str();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_str_p_p
 * @since_tizen		2.3
 * @description		Gets a string pointer from the record handle.
 */
int utc_contacts_service2_record_get_str_p_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		char *value;
		ret = contacts_record_get_str_p(record, INVALID_PROPERTY_ID, &value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->get_str_p) {
			ret = tc_db_plugin->get_str_p();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_set_bool_p
 * @since_tizen		2.3
 * @description		Sets a boolean value to a record.
 */
int utc_contacts_service2_record_set_bool_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		bool value = false;
		ret = contacts_record_set_bool(record, INVALID_PROPERTY_ID, value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->set_bool) {
			ret = tc_db_plugin->set_bool();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_set_double_p
 * @since_tizen		2.3
 * @description		Sets a double value to a record.
 */
int utc_contacts_service2_record_set_double_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		double value = 0.0;
		ret = contacts_record_set_double(record, INVALID_PROPERTY_ID, value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->set_double) {
			ret = tc_db_plugin->set_double();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_set_int_p
 * @since_tizen		2.3
 * @description		Sets an integer value to a record.
 */
int utc_contacts_service2_record_set_int_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		int value = 0;
		ret = contacts_record_set_int(record, INVALID_PROPERTY_ID, value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->set_int) {
			ret = tc_db_plugin->set_int();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_set_lli_p
 * @since_tizen		2.3
 * @description		Sets a long long integer value to a record.
 */
int utc_contacts_service2_record_set_lli_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		long long int value = 0;
		ret = contacts_record_set_lli(record, INVALID_PROPERTY_ID, value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->set_lli) {
			ret = tc_db_plugin->set_lli();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_set_str_p
 * @since_tizen		2.3
 * @description		Sets a string value to a record.
 */
int utc_contacts_service2_record_set_str_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		contacts_record_h record = NULL;
		char *value = NULL;
		ret = contacts_record_set_str(record, INVALID_PROPERTY_ID, value);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_record_plugin_s *tc_db_plugin = _ctsvc_tc_get_record_plugin(i);
		if (tc_db_plugin && tc_db_plugin->set_str) {
			ret = tc_db_plugin->set_str();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_clone_n
 * @since_tizen		2.3
 * @description		Makes a clone of a record with invalid parameters.
 */
int utc_contacts_service2_record_clone_n(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret = 0;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	ret = contacts_record_clone(NULL, &record_clone);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}


	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_record_create(ctsvc_tc_util_get_view_uri(i), &record);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_record_clone(record, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

		ret = contacts_record_destroy(record, true);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_create_n
 * @since_tizen		2.3
 * @description		Creates a record with invalid parameters.
 */
int utc_contacts_service2_record_create_n(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret = 0;
	contacts_record_h record = NULL;

	ret = contacts_record_create(NULL, &record);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_record_create(ctsvc_tc_util_get_view_uri(i), NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_destroy_n
 * @since_tizen		2.3
 * @description		Destroys a record with invalid parameters.
 */
int utc_contacts_service2_record_destroy_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	ret = contacts_record_destroy(NULL, true);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_uri_p_n
 * @since_tizen		2.3
 * @description		Gets URI string from a record with invalid parameters.
 */
int utc_contacts_service2_record_get_uri_p_n(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;

	ret = contacts_record_get_uri_p(NULL, &uri);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_record_create(ctsvc_tc_util_get_view_uri(i), &record);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_record_get_uri_p(record, NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

		ret = contacts_record_destroy(record, true);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_add_child_record_n
 * @since_tizen		2.3
 * @description		Adds a child record to the parent record with invalid parameters.
 */
int utc_contacts_service2_record_add_child_record_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	ret = contacts_record_add_child_record(NULL, INVALID_PROPERTY_ID, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_clone_child_record_list_n
 * @since_tizen		2.3
 * @description		Clones a child record list of the given parent record with invalid parameters.
 */
int utc_contacts_service2_record_clone_child_record_list_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	ret = contacts_record_clone_child_record_list(NULL, INVALID_PROPERTY_ID, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_remove_child_record_n
 * @since_tizen		2.3
 * @description		Removes a child record from the parent record with invalid parameters.
 */
int utc_contacts_service2_record_remove_child_record_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	ret = contacts_record_remove_child_record(NULL, INVALID_PROPERTY_ID, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_child_record_at_p_n
 * @since_tizen		2.3
 * @description		Gets a child record handle pointer from the parent record with invalid parameters.
 */
int utc_contacts_service2_record_get_child_record_at_p_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int index = 0;

	ret = contacts_record_get_child_record_at_p(NULL, INVALID_PROPERTY_ID, index, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_child_record_count_n
 * @since_tizen		2.3
 * @description		Gets the number of child records of a parent record with invalid parameters.
 */
int utc_contacts_service2_record_get_child_record_count_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int count = 0;

	ret = contacts_record_get_child_record_count(NULL, INVALID_PROPERTY_ID, &count);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_bool_n
 * @since_tizen		2.3
 * @description		Gets a record's boolean value with invalid parameters.
 */
int utc_contacts_service2_record_get_bool_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	bool value;
	ret = contacts_record_get_bool(NULL, INVALID_PROPERTY_ID, &value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_double_n
 * @since_tizen		2.3
 * @description		Gets a record's double value with invalid parameters.
 */
int utc_contacts_service2_record_get_double_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	double value;
	ret = contacts_record_get_double(NULL, INVALID_PROPERTY_ID, &value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_int_n
 * @since_tizen		2.3
 * @description		Gets a record's integer value with invalid parameters.
 */
int utc_contacts_service2_record_get_int_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int value;
	ret = contacts_record_get_int(NULL, INVALID_PROPERTY_ID, &value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_lli_n
 * @since_tizen		2.3
 * @description		Gets a record's long long integer value with invalid parameters.
 */
int utc_contacts_service2_record_get_lli_n(void)
{
	int ret = 0;
	long long int value;
	ret = contacts_record_get_lli(NULL, INVALID_PROPERTY_ID, &value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_str_n
 * @since_tizen		2.3
 * @description		Gets a record's string value with invalid parameters.
 */
int utc_contacts_service2_record_get_str_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	char *value;
	ret = contacts_record_get_str(NULL, INVALID_PROPERTY_ID, &value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_get_str_p_n
 * @since_tizen		2.3
 * @description		Gets a string pointer from the record handle with invalid parameters.
 */
int utc_contacts_service2_record_get_str_p_n(void)
{
	int ret = 0;
	char *value;
	ret = contacts_record_get_str_p(NULL, INVALID_PROPERTY_ID, &value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_set_bool_n
 * @since_tizen		2.3
 * @description		Sets a boolean value to a record with invalid parameters.
 */
int utc_contacts_service2_record_set_bool_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	bool value = false;
	ret = contacts_record_set_bool(NULL, INVALID_PROPERTY_ID, value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_set_double_n
 * @since_tizen		2.3
 * @description		Sets a double value to a record with invalid parameters.
 */
int utc_contacts_service2_record_set_double_n(void)
{
	int ret = 0;
	double value = 0.0;
	ret = contacts_record_set_double(NULL, INVALID_PROPERTY_ID, value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_set_int_n
 * @since_tizen		2.3
 * @description		Sets an integer value to a record with invalid parameters.
 */
int utc_contacts_service2_record_set_int_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int value = 0;
	ret = contacts_record_set_int(NULL, INVALID_PROPERTY_ID, value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_set_lli_n
 * @since_tizen		2.3
 * @description		Sets a long long integer value to a record with invalid parameters.
 */
int utc_contacts_service2_record_set_lli_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	long long int value = 0;
	ret = contacts_record_set_lli(NULL, INVALID_PROPERTY_ID, value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_record_set_str_n
 * @since_tizen		2.3
 * @description		Sets a string value to a record with invalid parameters.
 */
int utc_contacts_service2_record_set_str_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	char *value = NULL;
	ret = contacts_record_set_str(NULL, INVALID_PROPERTY_ID, value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	return 0;
}
