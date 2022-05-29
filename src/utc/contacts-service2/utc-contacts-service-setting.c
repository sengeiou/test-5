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
#include "utc-contacts-service-db-address-book.h"
#include "utc-contacts-service-db-group.h"
#include "utc-contacts-service-record-contact.h"

// _display_name
#define CTSVC_NAME_PREFIX_C1_FIRST "PREFIX_C FIRST_"
#define CTSVC_NAME_PREFIX_C2_FIRST "PREFIX_C2 FIRST_"

#define API_NAME_CONTACTS_SETTING_ADD_NAME_DISPLAY_ORDER_CHANGED_CB "contacts_setting_add_name_display_order_changed_cb"
#define API_NAME_CONTACTS_SETTING_ADD_NAME_SORTING_ORDER_CHANGED_CB "contacts_setting_add_name_sorting_order_changed_cb"
#define API_NAME_CONTACTS_SETTING_REMOVE_NAME_DISPLAY_ORDER_CHANGED_CB "contacts_setting_remove_name_display_order_changed_cb"
#define API_NAME_CONTACTS_SETTING_REMOVE_NAME_SORTING_ORDER_CHANGED_CB "contacts_setting_remove_name_sorting_order_changed_cb"
#define API_NAME_CONTACTS_SETTING_GET_NAME_DISPLAY_ORDER "contacts_setting_get_name_display_order"
#define API_NAME_CONTACTS_SETTING_SET_NAME_DISPLAY_ORDER "contacts_setting_set_name_display_order"
#define API_NAME_CONTACTS_SETTING_GET_NAME_SORTING_ORDER "contacts_setting_get_name_sorting_order"
#define API_NAME_CONTACTS_SETTING_SET_NAME_SORTING_ORDER "contacts_setting_set_name_sorting_order"

static int _startup_err;

/**
 * @function		utc_contacts_service2_setting_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_setting_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_setting_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_setting_cleanup(void)
{
	contacts_disconnect();
}


/**
 * @testcase		utc_contacts_service2_setting_add_name_display_order_changed_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function for notifying name_display_order changed.
 */
int utc_contacts_service2_setting_add_name_display_order_changed_cb_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_setting_add_name_display_order_changed_cb(ctsvc_tc_util_setting_name_display_order_chagned_cb, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_add_name_display_order_changed_cb(ctsvc_tc_util_setting_name_display_order_chagned_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_remove_name_display_order_changed_cb(ctsvc_tc_util_setting_name_display_order_chagned_cb, NULL))) break;
		return 0;
	} while (0);
	contacts_setting_remove_name_display_order_changed_cb(ctsvc_tc_util_setting_name_display_order_chagned_cb, NULL);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}


/**
 * @testcase		utc_contacts_service2_setting_add_name_display_order_changed_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function for notifying name_display_order changed with invalid parameters.
 */
int utc_contacts_service2_setting_add_name_display_order_changed_cb_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_setting_add_name_display_order_changed_cb(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_setting_remove_name_display_order_changed_cb_p
 * @since_tizen		2.3
 * @description		Unregisters a callback function for notifying name_display_order changed.
 */
int utc_contacts_service2_setting_remove_name_display_order_changed_cb_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_setting_remove_name_display_order_changed_cb(ctsvc_tc_util_setting_name_display_order_chagned_cb, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_add_name_display_order_changed_cb(ctsvc_tc_util_setting_name_display_order_chagned_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_remove_name_display_order_changed_cb(ctsvc_tc_util_setting_name_display_order_chagned_cb, NULL))) break;
		return 0;
	} while (0);
	contacts_setting_remove_name_display_order_changed_cb(ctsvc_tc_util_setting_name_display_order_chagned_cb, NULL);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}


/**
 * @testcase		utc_contacts_service2_setting_remove_name_display_order_changed_cb_n
 * @since_tizen		2.3
 * @description		Unregisters a callback function for notifying name_display_order changed with invalid parameters.
 */
int utc_contacts_service2_setting_remove_name_display_order_changed_cb_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_setting_remove_name_display_order_changed_cb(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_setting_add_name_sorting_order_changed_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function for notifying name_sorting_order changed.
 */
int utc_contacts_service2_setting_add_name_sorting_order_changed_cb_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_setting_add_name_sorting_order_changed_cb(ctsvc_tc_util_setting_name_sorting_order_chagned_cb, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_add_name_sorting_order_changed_cb(ctsvc_tc_util_setting_name_sorting_order_chagned_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_remove_name_sorting_order_changed_cb(ctsvc_tc_util_setting_name_sorting_order_chagned_cb, NULL))) break;
		return 0;
	} while (0);
	contacts_setting_remove_name_sorting_order_changed_cb(ctsvc_tc_util_setting_name_sorting_order_chagned_cb, NULL);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}


/**
 * @testcase		utc_contacts_service2_setting_add_name_sorting_order_changed_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function for notifying name_sorting_order changed with invalid parameters.
 */
int utc_contacts_service2_setting_add_name_sorting_order_changed_cb_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_setting_add_name_sorting_order_changed_cb(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_setting_remove_name_sorting_order_changed_cb_p
 * @since_tizen		2.3
 * @description		Unregisters a callback function for notifying name_sorting_order changed.
 */
int utc_contacts_service2_setting_remove_name_sorting_order_changed_cb_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_setting_remove_name_sorting_order_changed_cb(ctsvc_tc_util_setting_name_sorting_order_chagned_cb, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_add_name_sorting_order_changed_cb(ctsvc_tc_util_setting_name_sorting_order_chagned_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_remove_name_sorting_order_changed_cb(ctsvc_tc_util_setting_name_sorting_order_chagned_cb, NULL))) break;
		return 0;
	} while (0);
	contacts_setting_remove_name_sorting_order_changed_cb(ctsvc_tc_util_setting_name_sorting_order_chagned_cb, NULL);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}


/**
 * @testcase		utc_contacts_service2_setting_remove_name_sorting_order_changed_cb_n
 * @since_tizen		2.3
 * @description		Unregisters a callback function for notifying name_sorting_order changed with invalid parameters.
 */
int utc_contacts_service2_setting_remove_name_sorting_order_changed_cb_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_setting_remove_name_sorting_order_changed_cb(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_setting_get_name_display_order_p
 * @since_tizen		2.3
 * @description		Gets the contacts name display order.
 */
int utc_contacts_service2_setting_get_name_display_order_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	contacts_name_display_order_e order_set = CONTACTS_NAME_DISPLAY_ORDER_FIRSTLAST;
	contacts_name_display_order_e order_get;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_setting_get_name_display_order(&order_get);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_set_name_display_order(order_set))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_get_name_display_order(&order_get))) break;
		assert_eq(order_set, order_get);
		return 0;
	} while (0);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_setting_get_name_display_order_n
 * @since_tizen		2.3
 * @description		Gets the contacts name display order with invalid parameters.
 */
int utc_contacts_service2_setting_get_name_display_order_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_setting_get_name_display_order(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_setting_set_name_display_order_p
 * @since_tizen		2.3
 * @description		Sets the contacts name display order.
 */
int utc_contacts_service2_setting_set_name_display_order_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	contacts_name_display_order_e order_set = CONTACTS_NAME_DISPLAY_ORDER_FIRSTLAST;
	contacts_name_display_order_e order_get;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_setting_set_name_display_order(order_set);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_set_name_display_order(order_set))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_get_name_display_order(&order_get))) break;
		assert_eq(order_set, order_get);
	} while (0);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	/* start result check */
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_list_h list = NULL;

	contacts_db_get_all_records(_contacts_contact._uri, OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
	contacts_list_first(list);
	do {
		int record_id = 0;
		contacts_record_h p_record = NULL;
		contacts_list_get_current_record_p(list, &p_record);
		if (p_record) {
			contacts_record_get_int(p_record, _contacts_contact.id, &record_id);
			contacts_db_delete_record(_contacts_contact._uri, record_id);
		}
	} while (CONTACTS_ERROR_NONE == contacts_list_next(list));
	contacts_list_destroy(list, true);
	list = NULL;

	ctsvc_tc_util_account_insert(&account_id);
	ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id);
	ctsvc_tc_db_insert_record_group(address_book_id, &group_id);

	contacts_record_h record2 = NULL;
	ctsvc_tc_record_create_contact(address_book_id, group_id, PROPERTY_TYPE_CREATE2, &record2);
	int id2 = 0;
	contacts_db_insert_record(record2, &id2);
	contacts_record_destroy(record2, true);

	contacts_record_h record = NULL;
	ctsvc_tc_record_create_contact(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &record);
	int id = 0;
	contacts_db_insert_record(record, &id);
	contacts_record_destroy(record, true);

	contacts_db_get_all_records(_contacts_contact._uri, OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
	contacts_list_first(list);
	do {
		int ad_id = 0;
		contacts_record_h p_record = NULL;
		contacts_list_get_current_record_p(list, &p_record);
		contacts_record_get_int(p_record, _contacts_contact.address_book_id, &ad_id);
		if (ad_id == address_book_id) {
			char *display_name = NULL;
			contacts_record_get_str_p(p_record, _contacts_contact.display_name, &display_name);
			if (display_name) {
				int check = 0;
				check = strncmp(display_name, CTSVC_NAME_PREFIX_C2_FIRST, strlen(CTSVC_NAME_PREFIX_C2_FIRST));
				if (0 != check) {
					check = strncmp(display_name, CTSVC_NAME_PREFIX_C1_FIRST, strlen(CTSVC_NAME_PREFIX_C1_FIRST));
				}
				if (0 != check) {
					ret = -1;
					break;
				}
			}
		}
	} while (CONTACTS_ERROR_NONE == contacts_list_next(list));
	contacts_list_destroy(list, true);
	list = NULL;

	contacts_db_delete_record(_contacts_contact._uri, id);
	contacts_db_delete_record(_contacts_contact._uri, id2);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_setting_set_name_display_order_n
 * @since_tizen		2.3
 * @description		Sets the contacts name display order with invalid parameters.
 */
int utc_contacts_service2_setting_set_name_display_order_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_setting_set_name_display_order(INVALID_ENUM);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_setting_get_name_sorting_order_p
 * @since_tizen		2.3
 * @description		Gets the contacts name sorting order.
 */
int utc_contacts_service2_setting_get_name_sorting_order_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	contacts_name_sorting_order_e order_set = CONTACTS_NAME_SORTING_ORDER_FIRSTLAST;
	contacts_name_sorting_order_e order_get;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_setting_get_name_sorting_order(&order_get);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_set_name_sorting_order(order_set))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_get_name_sorting_order(&order_get))) break;
		assert_eq(order_set, order_get);
		return 0;
	} while (0);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_setting_get_name_sorting_order_n
 * @since_tizen		2.3
 * @description		Gets the contacts name sorting order with invalid parameters.
 */
int utc_contacts_service2_setting_get_name_sorting_order_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_setting_get_name_sorting_order(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_setting_set_name_sorting_order_p
 * @since_tizen		2.3
 * @description		Sets the contacts name sorting order.
 */
int utc_contacts_service2_setting_set_name_sorting_order_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;
	contacts_name_sorting_order_e order_set = CONTACTS_NAME_SORTING_ORDER_FIRSTLAST;
	contacts_name_sorting_order_e order_get;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_setting_set_name_sorting_order(order_set);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_set_name_sorting_order(order_set))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_setting_get_name_sorting_order(&order_get))) break;
		assert_eq(order_set, order_get);
	} while (0);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	/* start result check */
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	char *last_str = NULL;
	contacts_list_h list = NULL;

	ctsvc_tc_util_account_insert(&account_id);
	ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id);
	ctsvc_tc_db_insert_record_group(address_book_id, &group_id);

	contacts_record_h record2 = NULL;
	ctsvc_tc_record_create_contact(address_book_id, group_id, PROPERTY_TYPE_CREATE2, &record2);
	int id2 = 0;
	contacts_db_insert_record(record2, &id2);
	contacts_record_destroy(record2, true);

	contacts_record_h record = NULL;
	ctsvc_tc_record_create_contact(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &record);
	int id = 0;
	contacts_db_insert_record(record, &id);
	contacts_record_destroy(record, true);

	contacts_db_get_all_records(_contacts_person._uri, OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
	contacts_list_first(list);
	do {
		contacts_record_h p_record = NULL;
		contacts_list_get_current_record_p(list, &p_record);

		int display_contact_id = 0;
		contacts_record_get_int(p_record, _contacts_person.display_contact_id, &display_contact_id);
		if ((display_contact_id == id) || (display_contact_id == id2)) {
			char *display_name = NULL;
			contacts_record_get_str_p(p_record, _contacts_person.display_name, &display_name);
			if (NULL == last_str) {
				last_str = display_name;
			}
			else {
				int check = 0;
				check = strcmp(last_str, display_name);
				/* plus : when last_str > display_name
				 *  0   : display_name = last_str
				 * minus: when last_str < display_name
				 */
				if (0 < check) {
					ret = -1;
					break;
				}
			}
		}
	} while (CONTACTS_ERROR_NONE == contacts_list_next(list));
	contacts_list_destroy(list, true);
	list = NULL;
	contacts_db_delete_record(_contacts_contact._uri, id);
	contacts_db_delete_record(_contacts_contact._uri, id2);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_setting_set_name_sorting_order_n
 * @since_tizen		2.3
 * @description		Sets the contacts name sorting order with invalid parameters.
 */
int utc_contacts_service2_setting_set_name_sorting_order_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_setting_set_name_sorting_order(INVALID_ENUM);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}
