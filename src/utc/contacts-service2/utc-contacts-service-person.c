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
#include "utc-contacts-service-db-address-book.h"
#include "utc-contacts-service-db-group.h"
#include "utc-contacts-service-db-contact.h"
#include "utc-contacts-service-db-person.h"
#include "utc-contacts-service-record-person.h"
#include "utc-contacts-service-tc-utils.h"

#define API_NAME_CONTACTS_PERSON_GET_DEFAULT_PROPERTY "contacts_person_get_default_property"
#define API_NAME_CONTACTS_PERSON_SET_DEFAULT_PROPERTY "contacts_person_set_default_property"
#define API_NAME_CONTACTS_PERSON_LINK_PERSON "contacts_person_link_person"
#define API_NAME_CONTACTS_PERSON_UNLINK_CONTACT "contacts_person_unlink_contact"
#define API_NAME_CONTACTS_PERSON_RESET_USAGE "contacts_person_reset_usage"
#define API_NAME_CONTACTS_PERSON_SET_FAVORITE_ORDER "contacts_person_set_favorite_order"

static int _startup_err;

/**
 * @function		utc_contacts_service2_person_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_person_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_person_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_person_cleanup(void)
{
	contacts_disconnect();
}


/**
 * @testcase		utc_contacts_service2_person_get_default_property_p
 * @since_tizen		2.3
 * @description		Test getting a default property for a record.
 */
int utc_contacts_service2_person_get_default_property_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int id = 0;
	int person_id = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_person_get_default_property(CONTACTS_PERSON_PROPERTY_NAME_CONTACT, person_id, &id);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &person_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_person_get_default_property(CONTACTS_PERSON_PROPERTY_NAME_CONTACT, person_id, &id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_person._uri, person_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

/**
 * @testcase		utc_contacts_service2_person_get_default_property_n
 * @since_tizen		2.3
 * @description		Test fail getting a default property for a record with invalid parameters.
 */
int utc_contacts_service2_person_get_default_property_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_person_get_default_property(INVALID_ENUM, INVALID_DB_ID, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_person_set_default_property_p
 * @since_tizen		2.3
 * @description		Test setting a record's default property.
 */
int utc_contacts_service2_person_set_default_property_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int id = 0;
	int person_id = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_person_set_default_property(CONTACTS_PERSON_PROPERTY_NAME_CONTACT, person_id, id);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &person_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_person_get_default_property(CONTACTS_PERSON_PROPERTY_NAME_CONTACT, person_id, &id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_person_set_default_property(CONTACTS_PERSON_PROPERTY_NAME_CONTACT, person_id, id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, person_id, &record))) break;
		if (0 != (ret = ctsvc_tc_record_compare_person(record, PROPERTY_TYPE_CREATE1)))break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_person._uri, person_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

/**
 * @testcase		utc_contacts_service2_person_set_default_property_n
 * @since_tizen		2.3
 * @description		Test fail setting a record's default property with invalid parameters.
 */
int utc_contacts_service2_person_set_default_property_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_person_set_default_property(INVALID_ENUM, INVALID_DB_ID, INVALID_DB_ID);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_person_link_person_p
 * @since_tizen		2.3
 * @description		Test linking a person to another person.
 */
int utc_contacts_service2_person_link_person_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int person_id = 0;
	int person_id2 = 0;
	int contact_id = 0;
	int contact_id2 = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_person_link_person(person_id, person_id2);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_contact._uri, contact_id, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_int(record, _contacts_contact.person_id, &person_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id2))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_contact._uri, contact_id2, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_int(record, _contacts_contact.person_id, &person_id2))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_person_link_person(person_id, person_id2))) break;
		person_id2 = 0;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_contact._uri, contact_id2, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_int(record, _contacts_contact.person_id, &person_id2))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		if (person_id2 != person_id)
		{
			ret = -1;
			break;
		}

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_person._uri, person_id);
	contacts_db_delete_record(_contacts_person._uri, person_id2);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_person_link_person_n
 * @since_tizen		2.3
 * @description		Test fail linking a person to another person with invalid parameters.
 */
int utc_contacts_service2_person_link_person_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_person_link_person(INVALID_DB_ID, INVALID_DB_ID);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_person_unlink_contact_p
 * @since_tizen		2.3
 * @description		Test unlinking a contact from a person.
 */
int utc_contacts_service2_person_unlink_contact_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int person_id = 0;
	int person_id2 = 0;
	int person_id3 = 0;
	int contact_id = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_person_unlink_contact(person_id, contact_id, &person_id2);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &person_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_contact._uri, contact_id, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_int(record, _contacts_contact.person_id, &person_id2))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_person_link_person(person_id, person_id2))) break;
		person_id2 = 0;
		if (CONTACTS_ERROR_NONE != (ret = contacts_person_unlink_contact(person_id, contact_id, &person_id2))) break;
		if (person_id2 == person_id)
		{
			ret = -1;
			break;
		}

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_contact._uri, contact_id, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_int(record, _contacts_contact.person_id, &person_id3))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		if (person_id3 != person_id2)
		{
			ret = -2;
			break;
		}

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_id2))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_person._uri, person_id);
	contacts_db_delete_record(_contacts_person._uri, person_id2);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_person_unlink_contact_n
 * @since_tizen		2.3
 * @description		Test fail unlinking a contact from a person with invalid parameters.
 */
int utc_contacts_service2_person_unlink_contact_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_person_unlink_contact(INVALID_DB_ID, INVALID_DB_ID, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_person_reset_usage_p
 * @since_tizen		2.3
 * @description		Test reseting a person's usage count.
 */
int utc_contacts_service2_person_reset_usage_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int person_id = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_person_reset_usage(person_id, CONTACTS_USAGE_STAT_TYPE_OUTGOING_CALL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &person_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_person_reset_usage(person_id, CONTACTS_USAGE_STAT_TYPE_OUTGOING_CALL))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_db_delete_record(_contacts_person._uri, person_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;

}

/**
 * @testcase		utc_contacts_service2_person_reset_usage_n
 * @since_tizen		2.3
 * @description		Test fail reseting a person's usage count with invalid parameters.
 */
int utc_contacts_service2_person_reset_usage_n(void)
{
	assert_eq(_startup_err, 0);

	int ret;
	ret = contacts_person_reset_usage(INVALID_DB_ID, INVALID_ENUM);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_person_set_favorite_order_p
 * @since_tizen		2.3
 * @description		Test setting the order of a (favorite) contact.
 */
int utc_contacts_service2_person_set_favorite_order_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int person_id = 0;
	int person_id2 = 0;
	int person_id3 = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_person_set_favorite_order(person_id, person_id2, person_id3);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &person_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &person_id2))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &person_id3))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_person_set_favorite_order(person_id, person_id2, person_id3))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_id2))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_id3))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_person._uri, person_id);
	contacts_db_delete_record(_contacts_person._uri, person_id2);
	contacts_db_delete_record(_contacts_person._uri, person_id3);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;

}

/**
 * @testcase		utc_contacts_service2_person_set_favorite_order_n
 * @since_tizen		2.3
 * @description		Test fail setting the order of a (favorite) contact with invalid parameters.
 */
int utc_contacts_service2_person_set_favorite_order_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_person_set_favorite_order(INVALID_DB_ID, INVALID_DB_ID, INVALID_DB_ID);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_person_get_aggregation_suggestions_p
 * @since_tizen		3.0
 * @description		Test getting aggregation suggestions.
 */
int utc_contacts_service2_person_get_aggregation_suggestions_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int person_ids[PROPERTY_TYPE_CREATE5+1] = {0};
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	ctsvc_property_type_e type = 0;
	contacts_list_h list = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_person_get_aggregation_suggestions(person_ids[PROPERTY_TYPE_CREATE1], 0, &list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		for (type = PROPERTY_TYPE_CREATE1; type <= PROPERTY_TYPE_CREATE5; type++) {
			if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, type, &person_ids[type])))
				break;
		}
		if (0 != ret)
			break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_person_get_aggregation_suggestions(person_ids[PROPERTY_TYPE_CREATE1], 0, &list))) break;

		/* start result check */
		int count = 0;
		contacts_record_h record = NULL;

		contacts_list_get_count(list, &count);

		/* one has similar name & same number, the other has similar name & same email id */
		if (2 != count) {
			ret = -1;
			break;
		}

		contacts_list_first(list);
		while (CONTACTS_ERROR_NONE == contacts_list_get_current_record_p(list, &record)) {
			int person_id = 0;

			contacts_record_get_int(record, _contacts_person.id, &person_id);

			if (person_ids[PROPERTY_TYPE_CREATE3] != person_id &&
				person_ids[PROPERTY_TYPE_CREATE4] != person_id 	) {
				ret = -1;
				break;
			}

			contacts_list_next(list);
		}
		if (CONTACTS_ERROR_NONE != ret)
			break;
		/* end result check */

		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		for (type = PROPERTY_TYPE_CREATE1; type <= PROPERTY_TYPE_CREATE5; type++)
			if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, person_ids[type]))) break;

		if (CONTACTS_ERROR_NONE != ret)
			break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_list_destroy(list, true);
	for (type = PROPERTY_TYPE_CREATE1; type <= PROPERTY_TYPE_CREATE5; type++)
		contacts_db_delete_record(_contacts_person._uri, person_ids[type]);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;

}

/**
 * @testcase		utc_contacts_service2_person_get_aggregation_suggestions_n
 * @since_tizen		3.0
 * @description		Test fail getting aggregation suggestions with invalid parameters.
 */
int utc_contacts_service2_person_get_aggregation_suggestions_n(void)
{
	assert_eq(_startup_err, 0);

	int ret;
	ret = contacts_person_get_aggregation_suggestions(INVALID_PROPERTY_ID, 0, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

