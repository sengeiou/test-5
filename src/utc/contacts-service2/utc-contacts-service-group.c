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
#include "utc-contacts-service-tc-utils.h"

#define API_NAME_CONTACTS_GROUP_ADD_CONTACT "contacts_group_add_contact"
#define API_NAME_CONTACTS_GROUP_REMOVE_CONTACT "contacts_group_remove_contact"
#define API_NAME_CONTACTS_GROUP_SET_GROUP_ORDER "contacts_group_set_group_order"

static int _startup_err;

/**
 * @function		utc_contacts_service2_group_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_group_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_group_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_group_cleanup(void)
{
	contacts_disconnect();
}


/**
 * @testcase		utc_contacts_service2_group_add_contact_p
 * @since_tizen		2.3
 * @description		Test adding a contact and a group relationship to the contacts database.
 */
int utc_contacts_service2_group_add_contact_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int contact_id = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_group_add_contact(group_id, contact_id);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, 0, &contact_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_group_add_contact(group_id, contact_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_contact._uri, contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_db_delete_record(_contacts_contact._uri, contact_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_group_add_contact_n
 * @since_tizen		2.3
 * @description		Test fail adding a contact and a group relationship to the contacts database with invalid parameters.
 */
int utc_contacts_service2_group_add_contact_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	ret = contacts_group_add_contact(INVALID_DB_ID, INVALID_DB_ID);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_group_remove_contact_p
 * @since_tizen		2.3
 * @description		Test removing a contact and a group relationship from the contacts database.
 */
int utc_contacts_service2_group_remove_contact_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int contact_id = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_group_remove_contact(group_id, contact_id);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_group_remove_contact(group_id, contact_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_contact._uri, contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_db_delete_record(_contacts_contact._uri, contact_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_group_remove_contact_n
 * @since_tizen		2.3
 * @description		Test fail removing a contact and a group relationship from the contacts database with invalid parameters.
 */
int utc_contacts_service2_group_remove_contact_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	ret = contacts_group_remove_contact(INVALID_DB_ID, INVALID_DB_ID);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_group_set_group_order_p
 * @since_tizen		2.3
 * @description		Test setting a group between the previous group and the next group.
 */
int utc_contacts_service2_group_set_group_order_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	int group_id2 = 0;
	int group_id3 = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_group_set_group_order(group_id, group_id2, group_id3);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id2))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id3))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_group_set_group_order(group_id, group_id2, group_id3))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id2))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id3))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_group._uri, group_id2);
	contacts_db_delete_record(_contacts_group._uri, group_id3);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_group_set_group_order_n
 * @since_tizen		2.3
 * @description		Test fail setting a group between the previous group and the next group with invalid parameters.
 */
int utc_contacts_service2_group_set_group_order_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_group_set_group_order(INVALID_DB_ID, INVALID_DB_ID, INVALID_DB_ID);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}
