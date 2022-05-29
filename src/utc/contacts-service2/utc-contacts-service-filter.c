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

#define API_NAME_CONTACTS_FILTER_CREATE "contacts_filter_create"
#define API_NAME_CONTACTS_FILTER_DESTROY "contacts_filter_destroy"
#define API_NAME_CONTACTS_FILTER_ADD_BOOL "contacts_filter_add_bool"
#define API_NAME_CONTACTS_FILTER_ADD_DOUBLE "contacts_filter_add_double"
#define API_NAME_CONTACTS_FILTER_ADD_FILTER "contacts_filter_add_filter"
#define API_NAME_CONTACTS_FILTER_ADD_INT "contacts_filter_add_int"
#define API_NAME_CONTACTS_FILTER_ADD_LLI "contacts_filter_add_lli"
#define API_NAME_CONTACTS_FILTER_ADD_OPERATOR "contacts_filter_add_operator"
#define API_NAME_CONTACTS_FILTER_ADD_STR "contacts_filter_add_str"

extern ctsvc_tc_filter_plugin_s _tc_filter_address_book;
extern ctsvc_tc_filter_plugin_s _tc_filter_group;
extern ctsvc_tc_filter_plugin_s _tc_filter_person;
extern ctsvc_tc_filter_plugin_s _tc_filter_contact;
extern ctsvc_tc_filter_plugin_s _tc_filter_my_profile;
extern ctsvc_tc_filter_plugin_s _tc_filter_phone_log;
extern ctsvc_tc_filter_plugin_s _tc_filter_speeddial;
extern ctsvc_tc_filter_plugin_s _tc_filter_updated_info;
extern ctsvc_tc_filter_plugin_s _tc_filter_address;
extern ctsvc_tc_filter_plugin_s _tc_filter_activity;
extern ctsvc_tc_filter_plugin_s _tc_filter_activity_photo;
extern ctsvc_tc_filter_plugin_s _tc_filter_company;
extern ctsvc_tc_filter_plugin_s _tc_filter_email;
extern ctsvc_tc_filter_plugin_s _tc_filter_event;
extern ctsvc_tc_filter_plugin_s _tc_filter_extension;
extern ctsvc_tc_filter_plugin_s _tc_filter_group_relation;
extern ctsvc_tc_filter_plugin_s _tc_filter_messenger;
extern ctsvc_tc_filter_plugin_s _tc_filter_name;
extern ctsvc_tc_filter_plugin_s _tc_filter_nickname;
extern ctsvc_tc_filter_plugin_s _tc_filter_note;
extern ctsvc_tc_filter_plugin_s _tc_filter_number;
extern ctsvc_tc_filter_plugin_s _tc_filter_profile;
extern ctsvc_tc_filter_plugin_s _tc_filter_relationship;
extern ctsvc_tc_filter_plugin_s _tc_filter_url;
extern ctsvc_tc_filter_plugin_s _tc_filter_image;
extern ctsvc_tc_filter_plugin_s _tc_filter_sip;

static ctsvc_tc_filter_plugin_s* _ctsvc_tc_get_filter_plugin(ctsvc_view_e view)
{
	switch (view) {
		case VIEW_ADDRESSBOOK:
			return &_tc_filter_address_book;
		case VIEW_GROUP:
			return &_tc_filter_group;
		case VIEW_PERSON:
			return &_tc_filter_person;
		case VIEW_CONTACT:
			return &_tc_filter_contact;
		case VIEW_MY_PROFILE:
			return &_tc_filter_my_profile;
		case VIEW_NAME:
			return &_tc_filter_name;
		case VIEW_NUMBER:
			return &_tc_filter_number;
		case VIEW_EMAIL:
			return &_tc_filter_email;
		case VIEW_ADDRESS:
			return &_tc_filter_address;
		case VIEW_NOTE:
			return &_tc_filter_note;
		case VIEW_URL:
			return &_tc_filter_url;
		case VIEW_EVENT:
			return &_tc_filter_event;
		case VIEW_GROUP_RELATION:
			return &_tc_filter_group_relation;
		case VIEW_RELATIONSHIP:
			return &_tc_filter_relationship;
		case VIEW_IMAGE:
			return &_tc_filter_image;
		case VIEW_COMPANY:
			return &_tc_filter_company;
		case VIEW_NICKNAME:
			return &_tc_filter_nickname;
		case VIEW_MESSENGER:
			return &_tc_filter_messenger;
		case VIEW_EXTENSION:
			return &_tc_filter_extension;
		case VIEW_PROFILE:
			return &_tc_filter_profile;
		case VIEW_ACTIVITY_PHOTO:
			return &_tc_filter_activity_photo;
		case VIEW_ACTIVITY:
			return &_tc_filter_activity;
		case VIEW_SPEEDDIAL:
			return &_tc_filter_speeddial;
		case VIEW_PHONE_LOG:
			return &_tc_filter_phone_log;
		case VIEW_SIP:
			return &_tc_filter_sip;
		case VIEW_SDN: // can't create
		case VIEW_SIMPLE_CONTACT: // can't create
		case VIEW_CONTACT_UPDATED_INFO: // can't create
		case VIEW_MY_PROFILE_UPDATED_INFO: // can't create
		case VIEW_GROUP_UPDATED_INFO: // can't create
		case VIEW_GROUP_MEMBER_UPDATED_INFO: // can't create
		case VIEW_GROUPREL_UPDATED_INFO: // can't create
		case VIEW_PHONE_LOG_STAT: // can't create
		default :
			return NULL;
	}
	return NULL;
}


static int _startup_err;

/**
 * @function		utc_contacts_service2_filter_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_filter_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_filter_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_filter_cleanup(void)
{
	contacts_disconnect();
}


/**
 * @testcase		utc_contacts_service2_filter_create_p
 * @since_tizen		2.3
 * @description		Test creating a filter.
 */
int utc_contacts_service2_filter_create_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret = 0;
	contacts_filter_h filter = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_filter_create(ctsvc_tc_util_get_view_uri(0), &filter);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_filter_create(ctsvc_tc_util_get_view_uri(i), &filter);
		assert_eq(CONTACTS_ERROR_NONE, ret);
		ret = contacts_filter_destroy(filter);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_create_n
 * @since_tizen		2.3
 * @description		Test fail creating a filter with invalid parameters.
 */
int utc_contacts_service2_filter_create_n(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret = 0;
	contacts_filter_h filter = NULL;

	ret = contacts_filter_create(NULL, &filter);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_filter_create(ctsvc_tc_util_get_view_uri(i), NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_destroy_p
 * @since_tizen		2.3
 * @description		Test destroying a filter.
 */
int utc_contacts_service2_filter_destroy_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret = 0;
	contacts_filter_h filter = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_filter_create(ctsvc_tc_util_get_view_uri(0), &filter);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_filter_create(ctsvc_tc_util_get_view_uri(i), &filter);
		assert_eq(CONTACTS_ERROR_NONE, ret);
		ret = contacts_filter_destroy(filter);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_destroy_n
 * @since_tizen		2.3
 * @description		Test fail destroying a filter with invalid parameters.
 */
int utc_contacts_service2_filter_destroy_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_filter_destroy(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_operator_p
 * @since_tizen		2.3
 * @description		Test adding an operator between conditions.
 */
int utc_contacts_service2_filter_add_operator_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_filter_h filter = NULL;

	const char *test_view_uri = _contacts_contact._uri;
	unsigned int test_property_id = _contacts_contact.id;
	int test_match_value = 1;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_filter_add_operator(filter, CONTACTS_FILTER_OPERATOR_AND);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = contacts_filter_create(test_view_uri, &filter);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_filter_add_int(filter, test_property_id, CONTACTS_MATCH_EQUAL, test_match_value);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_filter_add_operator(filter, CONTACTS_FILTER_OPERATOR_AND);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_filter_destroy(filter);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_operator_n
 * @since_tizen		2.3
 * @description		Test fail adding an operator between conditions with invalid parameters.
 */
int utc_contacts_service2_filter_add_operator_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_filter_add_operator(NULL, CONTACTS_FILTER_OPERATOR_AND);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = contacts_filter_add_operator(NULL, CONTACTS_FILTER_OPERATOR_AND);
	assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	ret = contacts_filter_add_operator(NULL, CONTACTS_FILTER_OPERATOR_OR);
	assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_filter_add_filter_p
 * @since_tizen		2.3
 * @description		Test adding a filter to a given filter.
 */
int utc_contacts_service2_filter_add_filter_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_filter_h filter = NULL;
	contacts_filter_h filter2 = NULL;

	const char *test_view_uri = _contacts_contact._uri;
	unsigned int test_property_id = _contacts_contact.id;
	int test_match_value = 1;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_filter_add_filter(filter, filter2);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = contacts_filter_create(test_view_uri, &filter);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_filter_create(test_view_uri, &filter2);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_filter_add_int(filter, test_property_id, CONTACTS_MATCH_EQUAL, test_match_value);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_filter_add_int(filter2, test_property_id, CONTACTS_MATCH_EQUAL, test_match_value);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_filter_add_operator(filter, CONTACTS_FILTER_OPERATOR_AND);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_filter_add_filter(filter, filter2);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_filter_destroy(filter);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_filter_destroy(filter2);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;

}

/**
 * @testcase		utc_contacts_service2_filter_add_filter_n
 * @since_tizen		2.3
 * @description		Test fail adding a filter to a given filter with invalid parameters.
 */
int utc_contacts_service2_filter_add_filter_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	ret = contacts_filter_add_filter(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_bool_n
 * @since_tizen		2.3
 * @description		Test fail adding a condition for a boolean type property with invalid parameters.
 */
int utc_contacts_service2_filter_add_bool_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	bool value = false;

	ret = contacts_filter_add_bool(NULL, INVALID_PROPERTY_ID, value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_int_n
 * @since_tizen		2.3
 * @description		Test fail adding a condition for an integer type property with invalid parameters.
 */
int utc_contacts_service2_filter_add_int_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int value = 0;

	ret = contacts_filter_add_int(NULL, INVALID_PROPERTY_ID, CONTACTS_MATCH_EQUAL, value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_double_n
 * @since_tizen		2.3
 * @description		Test fail adding a condition for a double type property with invalid parameters.
 */
int utc_contacts_service2_filter_add_double_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	double value = 0.0;

	ret = contacts_filter_add_double(NULL, INVALID_PROPERTY_ID, CONTACTS_MATCH_EQUAL, value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_lli_n
 * @since_tizen		2.3
 * @description		Test fail adding a condition for a long long integer type property with invalid parameters.
 */
int utc_contacts_service2_filter_add_lli_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	long long int value = 0;

	ret = contacts_filter_add_lli(NULL, INVALID_PROPERTY_ID, CONTACTS_MATCH_EQUAL, value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_filter_add_str_n
 * @since_tizen		2.3
 * @description		Test fail adding a condition for a string type property with invalid parameters.
 */
int utc_contacts_service2_filter_add_str_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	char *value = NULL;

	ret = contacts_filter_add_str(NULL, INVALID_PROPERTY_ID, CONTACTS_MATCH_FULLSTRING, value);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_bool_p
 * @since_tizen		2.3
 * @description		Test adding a condition for a boolean type property.
 */
int utc_contacts_service2_filter_add_bool_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_filter_add_bool(NULL, INVALID_PROPERTY_ID, false);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_filter_plugin_s *tc_filter_plugin = _ctsvc_tc_get_filter_plugin(i);
		if (tc_filter_plugin && tc_filter_plugin->add_bool) {
			ret = tc_filter_plugin->add_bool();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_int_p
 * @since_tizen		2.3
 * @description		Test adding a condition for an integer type property.
 */
int utc_contacts_service2_filter_add_int_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_filter_add_int(NULL, INVALID_PROPERTY_ID, CONTACTS_MATCH_EQUAL, 0);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_filter_plugin_s *tc_filter_plugin = _ctsvc_tc_get_filter_plugin(i);
		if (tc_filter_plugin && tc_filter_plugin->add_int) {
			ret = tc_filter_plugin->add_int();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_doulble_p
 * @since_tizen		2.3
 * @description		Test adding a condition for a double type property.
 */
double utc_contacts_service2_filter_add_double_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	double ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_filter_add_double(NULL, INVALID_PROPERTY_ID, CONTACTS_MATCH_EQUAL, 0.0);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_filter_plugin_s *tc_filter_plugin = _ctsvc_tc_get_filter_plugin(i);
		if (tc_filter_plugin && tc_filter_plugin->add_double) {
			ret = tc_filter_plugin->add_double();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_lli_p
 * @since_tizen		2.3
 * @description		Test adding a condition for a long long integer type property.
 */
int utc_contacts_service2_filter_add_lli_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_filter_add_lli(NULL, INVALID_PROPERTY_ID, CONTACTS_MATCH_EQUAL, 0);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_filter_plugin_s *tc_filter_plugin = _ctsvc_tc_get_filter_plugin(i);
		if (tc_filter_plugin && tc_filter_plugin->add_lli) {
			ret = tc_filter_plugin->add_lli();
			assert_eq(0, ret);
		}
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_filter_add_str_p
 * @since_tizen		2.3
 * @description		Test adding a condition for a string type property.
 */
int utc_contacts_service2_filter_add_str_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_filter_add_str(NULL, INVALID_PROPERTY_ID, CONTACTS_MATCH_FULLSTRING, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ctsvc_tc_filter_plugin_s *tc_filter_plugin = _ctsvc_tc_get_filter_plugin(i);
		if (tc_filter_plugin && tc_filter_plugin->add_str) {
			ret = tc_filter_plugin->add_str();
			assert_eq(0, ret);
		}
	}
	return 0;
}
