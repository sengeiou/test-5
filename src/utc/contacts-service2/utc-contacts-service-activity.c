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
#include "utc-contacts-service-db-contact.h"
#include "utc-contacts-service-db-activity.h"
#include "utc-contacts-service-db-group.h"
#include "utc-contacts-service-db-address-book.h"
#include "utc-contacts-service-tc-utils.h"

#define API_NAME_CONTACTS_ACTIVITY_DELETE_BY_CONTACT_ID "contacts_activity_delete_by_contact_id"
#define API_NAME_CONTACTS_ACTIVITY_DELETE_BY_ACCOUNT_ID "contacts_activity_delete_by_account_id"

static int _startup_err;

/**
 * @function		utc_contacts_service2_activity_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_activity_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_activity_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_activity_cleanup(void)
{
	contacts_disconnect();
}

/**
 * @testcase		utc_contacts_service2_activity_delete_by_contact_id_p
 * @since_tizen		2.3
 * @description		Test deleting an activity record from the contacts database by contact ID.
 */
int utc_contacts_service2_activity_delete_by_contact_id_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	int contact_id = 0;
	int activity_id = 0;
	contacts_record_h record = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_activity_delete_by_contact_id(contact_id);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_activity(contact_id, &activity_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_activity._uri, activity_id, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_activity_delete_by_contact_id(contact_id))) break;
		if (CONTACTS_ERROR_NO_DATA != (ret = contacts_db_get_record(_contacts_activity._uri, activity_id, &record))) {
			ret = -1;
			break;
		}

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_contact._uri, contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_activity._uri, activity_id);
	contacts_db_delete_record(_contacts_contact._uri, contact_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	assert_eq(0, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_activity_delete_by_contact_id_n
 * @since_tizen		2.3
 * @description		Test fail deleting an activity record from the contacts database with invalid parameter.
 */
int utc_contacts_service2_activity_delete_by_contact_id_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_activity_delete_by_contact_id(INVALID_PROPERTY_ID);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_activity_delete_by_account_id_p
 * @since_tizen		2.3
 * @description		Test deleting an activity record from the contacts database by account ID.
 */
int utc_contacts_service2_activity_delete_by_account_id_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	int contact_id = 0;
	int activity_id = 0;
	contacts_record_h record = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_activity_delete_by_account_id(account_id);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (0 != (ret = ctsvc_tc_util_account_insert(&account_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_activity(contact_id, &activity_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_activity._uri, activity_id, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_activity_delete_by_account_id(account_id))) break;
		if (CONTACTS_ERROR_NO_DATA != (ret = contacts_db_get_record(_contacts_activity._uri, activity_id, &record))) {
			ret = -1;
			break;
		}

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_contact._uri, contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_activity._uri, activity_id);
	contacts_db_delete_record(_contacts_contact._uri, contact_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	assert_eq(0, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_activity_delete_by_account_id_n
 * @since_tizen		2.3
 * @description		Test fail deleting an activity record from the contacts database with invalid parameters.
 */
int utc_contacts_service2_activity_delete_by_account_id_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_activity_delete_by_account_id(INVALID_PROPERTY_ID);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}
