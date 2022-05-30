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
#include "utc-contacts-service-record-contact.h"
#include "utc-contacts-service-record-my-profile.h"
#include "utc-contacts-service-db-address-book.h"
#include "utc-contacts-service-db-group.h"
#include "utc-contacts-service-db-person.h"
#include "utc-contacts-service-tc-utils.h"

#define API_NAME_CONTACTS_VCARD_GET_ENTITY_COUNT "contacts_vcard_get_entity_count"
#define API_NAME_CONTACTS_VCARD_MAKE_FROM_CONTACT "contacts_vcard_make_from_contact"
#define API_NAME_CONTACTS_VCARD_MAKE_FROM_MY_PROFILE "contacts_vcard_make_from_my_profile"
#define API_NAME_CONTACTS_VCARD_MAKE_FROM_PERSON "contacts_vcard_make_from_person"
#define API_NAME_CONTACTS_VCARD_PARSE_TO_CONTACTS "contacts_vcard_parse_to_contacts"
#define API_NAME_CONTACTS_VCARD_PARSE_TO_CONTACT_FOREACH "contacts_vcard_parse_to_contact_foreach"

static int _startup_err;

/**
 * @function		utc_contacts_service2_vcard_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_vcard_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_vcard_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_vcard_cleanup(void)
{
	contacts_disconnect();
}

/**
 * @testcase		utc_contacts_service2_vcard_get_entity_count_p
 * @since_tizen		2.3
 * @description		Retrieves the count of contact entities from a vCard file.
 */
int utc_contacts_service2_vcard_get_entity_count_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int count = 0;
	char *file_path = NULL;
	do {
		file_path = CTSVC_VCARD_PATH;
		if (CONTACTS_ERROR_NONE != (ret = contacts_vcard_get_entity_count(file_path, &count))) break;
		free(file_path);
		file_path = NULL;
		return 0;
	} while (0);
	free(file_path);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_get_entity_count_n
 * @since_tizen		2.3
 * @description		Retrieves the count of contact entities from a vCard file with invalid parameters.
 */
int utc_contacts_service2_vcard_get_entity_count_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	ret = contacts_vcard_get_entity_count(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_make_from_contact_p
 * @since_tizen		2.3
 * @description		Retrieves the vCard stream from a contact.
 */
int utc_contacts_service2_vcard_make_from_contact_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	char *vcard_stream = NULL;
	contacts_record_h record = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_vcard_make_from_contact(record, &vcard_stream);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_record_create_contact(LOCAL_DB_ID, LOCAL_DB_ID, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_vcard_make_from_contact(record, &vcard_stream))) break;
		if (NULL == vcard_stream) {
			ret = -1;
			break;
		}
		free(vcard_stream);
		vcard_stream = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	free(vcard_stream);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_make_from_contact_n
 * @since_tizen		2.3
 * @description		Retrieves the vCard stream from a contact with invalid parameters.
 */
int utc_contacts_service2_vcard_make_from_contact_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	ret = contacts_vcard_make_from_contact(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_vcard_make_from_my_profile_p
 * @since_tizen		2.3
 * @description		Retrieves the vCard stream from my_profile.
 */
int utc_contacts_service2_vcard_make_from_my_profile_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	char *vcard_stream = NULL;
	contacts_record_h record = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_vcard_make_from_my_profile(record, &vcard_stream);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_record_create_my_profile(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_vcard_make_from_my_profile(record, &vcard_stream))) break;
		if (NULL == vcard_stream) {
			ret = -1;
			break;
		}
		free(vcard_stream);
		vcard_stream = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	free(vcard_stream);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_make_from_my_profile_n
 * @since_tizen		2.3
 * @description		Retrieves the vCard stream from my_profile with invalid parameters.
 */
int utc_contacts_service2_vcard_make_from_my_profile_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	ret = contacts_vcard_make_from_my_profile(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_make_from_person_p
 * @since_tizen		2.3
 * @description		Retrieves the vCard stream from a person.
 */
int utc_contacts_service2_vcard_make_from_person_p(void)
{
	int ret = 0;
	int person_id = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	char *vcard_stream = NULL;
	contacts_record_h record = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_vcard_make_from_person(record, &vcard_stream);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &person_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, person_id, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_vcard_make_from_person(record, &vcard_stream))) break;
		if (NULL == vcard_stream) {
			ret = -1;
			break;
		}
		free(vcard_stream);
		vcard_stream = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	free(vcard_stream);
	contacts_db_delete_record(_contacts_person._uri, person_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_make_from_person_n
 * @since_tizen		2.3
 * @description		Retrieves the vCard stream from a person with invalid parameters.
 */
int utc_contacts_service2_vcard_make_from_person_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	ret = contacts_vcard_make_from_person(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_vcard_parse_to_contacts_p
 * @since_tizen		2.3
 * @description		Retrieves all contacts with a contacts list from a vCard stream.
 */
int utc_contacts_service2_vcard_parse_to_contacts_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	char *vcard_stream = NULL;
	contacts_record_h record = NULL;
	contacts_list_h list = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_vcard_parse_to_contacts(vcard_stream, &list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_record_create_contact(LOCAL_DB_ID, LOCAL_DB_ID, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_vcard_make_from_contact(record, &vcard_stream))) break;
		if (NULL == vcard_stream) {
			ret = -1;
			break;
		}
		if (CONTACTS_ERROR_NONE != (ret = contacts_vcard_parse_to_contacts(vcard_stream, &list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		list = NULL;
		free(vcard_stream);
		vcard_stream = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	free(vcard_stream);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	return ret;
}

/**
 * @testcase		utc_contacts_service2_vcard_parse_to_contacts_n
 * @since_tizen		2.3
 * @description		Retrieves all contacts with a contacts list from a vCard stream with invalid parameters.
 */
int utc_contacts_service2_vcard_parse_to_contacts_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_vcard_parse_to_contacts(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

static bool vcard_foreach_cb(contacts_record_h record, void *user_data)
{
	return true;
}

/**
 * @testcase		utc_contacts_service2_vcard_parse_to_contact_foreach_p
 * @since_tizen		2.3
 * @description		Retrieves all contacts with a record handle (_contacts_contact) from a vCard file.
 */
int utc_contacts_service2_vcard_parse_to_contact_foreach_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	char *file_path = NULL;
	do {
		file_path = CTSVC_VCARD_PATH;
		if (CONTACTS_ERROR_NONE != (ret = contacts_vcard_parse_to_contact_foreach(file_path, vcard_foreach_cb, NULL))) break;
		free(file_path);
		file_path = NULL;
		return 0;
	} while (0);
	free(file_path);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_parse_to_contact_foreach_n
 * @since_tizen		2.3
 * @description		Retrieves all contacts with a record handle (_contacts_contact) from a vCard file with invalid parameters.
 */
int utc_contacts_service2_vcard_parse_to_contact_foreach_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_vcard_parse_to_contact_foreach(NULL, NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_get_limit_size_of_photo_p
 * @since_tizen		3.0
 * @description		Gets the limit size of width and hight of photos to append in vCard files.
 */
int utc_contacts_service2_vcard_get_limit_size_of_photo_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	unsigned int limit_size;
	ret = contacts_vcard_get_limit_size_of_photo(&limit_size);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_get_limit_size_of_photo_n
 * @since_tizen		3.0
 * @description		Gets the limit size of width and hight of photos to append in vCard files with invalid parameters.
 */
int utc_contacts_service2_vcard_get_limit_size_of_photo_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_vcard_get_limit_size_of_photo(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_set_limit_size_of_photo_p
 * @since_tizen		3.0
 * @description		Sets the limit size of width and hight of photos to append in vCard files..
 */
int utc_contacts_service2_vcard_set_limit_size_of_photo_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	unsigned int setting_size = 96;
	unsigned int getting_size;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_vcard_set_limit_size_of_photo(setting_size);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_vcard_set_limit_size_of_photo(setting_size))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_vcard_get_limit_size_of_photo(&getting_size))) break;
		if (setting_size != getting_size)
			break;

		return 0;
	} while (0);

	assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_vcard_set_limit_size_of_photo_n
 * @since_tizen		3.0
 * @description		Sets the limit size of width and hight of photos to append in vCard files. with invalid parameter.
 */
int utc_contacts_service2_vcard_set_limit_size_of_photo_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_vcard_set_limit_size_of_photo(0);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}



