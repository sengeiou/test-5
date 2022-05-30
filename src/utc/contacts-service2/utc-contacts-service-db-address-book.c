/*
 * Copyright (c) 2014 - 2015 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <contacts.h>
#include "utc-contacts-service-tc-utils.h"
#include "utc-contacts-service-record-address-book.h"
#include "utc-contacts-service-db-address-book.h"

#define PARENT_ADDRESS_BOOK_NAME "address_book_parent"

static int _ctsvc_tc_db_add_changed_cb_address_book(void);
static int _ctsvc_tc_db_remove_changed_cb_address_book(void);
static int _ctsvc_tc_db_get_record_address_book(int account_id);
static int _ctsvc_tc_db_get_records_with_query_address_book(int account_id);
static int _ctsvc_tc_db_get_all_records_address_book(int account_id);
static int _ctsvc_tc_db_get_count_address_book(int account_id);
static int _ctsvc_tc_db_get_count_with_query_address_book(int account_id);
static int _ctsvc_tc_db_insert_record_address_book(int account_id);
static int _ctsvc_tc_db_update_record_address_book(int account_id);
static int _ctsvc_tc_db_delete_record_address_book(int account_id);


ctsvc_tc_db_plugin_s _tc_db_address_book = {
	.db_add_changed_cb = _ctsvc_tc_db_add_changed_cb_address_book,
	.db_remove_changed_cb = _ctsvc_tc_db_remove_changed_cb_address_book,
	.db_get_record = _ctsvc_tc_db_get_record_address_book,
	.db_get_records_with_query = _ctsvc_tc_db_get_records_with_query_address_book,
	.db_get_all_records = _ctsvc_tc_db_get_all_records_address_book,
	.db_get_changes_by_version = NULL,
	.db_get_count = _ctsvc_tc_db_get_count_address_book,
	.db_get_count_with_query = _ctsvc_tc_db_get_count_with_query_address_book,
	.db_insert_record = _ctsvc_tc_db_insert_record_address_book,
	.db_insert_records = NULL,
	.db_update_record = _ctsvc_tc_db_update_record_address_book,
	.db_update_records = NULL,
	.db_delete_record = _ctsvc_tc_db_delete_record_address_book,
	.db_delete_records = NULL,
	.db_replace_record = NULL,
	.db_replace_records = NULL,
	.db_search_records = NULL,
	.db_search_records_with_query = NULL,
	.db_search_records_with_range = NULL,
	.db_search_records_for_snippet = NULL,
	.db_search_records_with_query_for_snippet = NULL,
	.db_search_records_with_range_for_snippet = NULL,
	.db_get_count_for_search_records = NULL,
	.db_get_count_for_search_records_with_query = NULL,
	.db_get_count_for_search_records_with_range = NULL,
};

static int _ctsvc_tc_db_add_changed_cb_address_book(void)
{
	int ret = 0;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_add_changed_cb(_contacts_address_book._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_remove_changed_cb(_contacts_address_book._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		return 0;
	} while (0);
	return ret;
}

static int _ctsvc_tc_db_remove_changed_cb_address_book(void)
{
	int ret = 0;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_add_changed_cb(_contacts_address_book._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_remove_changed_cb(_contacts_address_book._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		return 0;
	} while (0);
	return ret;
}

static int _ctsvc_tc_db_get_record_address_book(int account_id)
{
	int ret = 0;
	int id = 0;
	contacts_record_h record = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_record_create_address_book(account_id, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_insert_record(record, &id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_address_book._uri, id, &record))) break;
		if (0 != (ret = ctsvc_tc_record_compare_address_book(record, PROPERTY_TYPE_CREATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_address_book._uri, id);

	return ret;
}

static int _ctsvc_tc_db_get_records_with_query_address_book(int account_id)
{
	int ret = 0;
	int id = 0;
	contacts_record_h record = NULL;
	contacts_record_h record_p = NULL;
	contacts_query_h query = NULL;
	contacts_filter_h filter = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_record_create_address_book(account_id, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_insert_record(record, &id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_query_create(_contacts_address_book._uri, &query))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_create(_contacts_address_book._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_filter_set_address_book(filter, PROPERTY_TYPE_CREATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_set_filter(query, filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_records_with_query(query, OFFSET_DEFAULT, LIMIT_DEFAULT, &list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_current_record_p(list, &record_p))) break;
		if (0 != (ret = ctsvc_tc_record_compare_address_book(record_p, PROPERTY_TYPE_CREATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		list = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_destroy(query))) break;
		query = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	contacts_filter_destroy(filter);
	contacts_query_destroy(query);
	contacts_db_delete_record(_contacts_address_book._uri, id);

	return ret;
}

static int _ctsvc_tc_db_get_all_records_address_book(int account_id)
{
	int ret = 0;
	int id = 0;
	contacts_record_h record = NULL;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_record_create_address_book(account_id, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_insert_record(record, &id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_all_records(_contacts_address_book._uri, OFFSET_DEFAULT, LIMIT_DEFAULT, &list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_current_record_p(list, &record_p))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		list = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	contacts_db_delete_record(_contacts_address_book._uri, id);

	return ret;
}


static int _ctsvc_tc_db_get_count_address_book(int account_id)
{
	int ret = 0;
	int id = 0;
	int count = 0;
	contacts_record_h record = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_record_create_address_book(account_id, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_insert_record(record, &id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_count(_contacts_address_book._uri, &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_address_book._uri, id);

	return ret;
}


static int _ctsvc_tc_db_get_count_with_query_address_book(int account_id)
{
	int ret = 0;
	int id = 0;
	int count = 0;
	contacts_record_h record = NULL;
	contacts_query_h query = NULL;
	contacts_filter_h filter = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_record_create_address_book(account_id, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_insert_record(record, &id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_query_create(_contacts_address_book._uri, &query))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_create(_contacts_address_book._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_filter_set_address_book(filter, PROPERTY_TYPE_CREATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_set_filter(query, filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_count_with_query(query, &count))) break;

		if (count < 1) {
			ret = -1;
			break;
		}

		// free memory
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_destroy(query))) break;
		query = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, id))) break;

		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_filter_destroy(filter);
	contacts_query_destroy(query);

	contacts_db_delete_record(_contacts_address_book._uri, id);

	return ret;
}

static int _ctsvc_tc_db_insert_record_address_book(int account_id)
{
	int ret = 0;
	int id = 0;
	contacts_record_h record = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_record_create_address_book(account_id, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_insert_record(record, &id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_address_book._uri, id, &record))) break;
		if (0 != (ret = ctsvc_tc_record_compare_address_book(record, PROPERTY_TYPE_CREATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, id))) break;
		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_address_book._uri, id);

	return ret;
}

static int _ctsvc_tc_db_update_record_address_book(int account_id)
{
	int ret = 0;
	int id = 0;
	contacts_record_h record = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_record_create_address_book(account_id, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_insert_record(record, &id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_address_book._uri, id, &record))) break;
		if (0 != (ret = ctsvc_tc_record_update_address_book(record, PROPERTY_TYPE_UPDATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_update_record(record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_address_book._uri, id, &record))) break;
		if (0 != (ret = ctsvc_tc_record_compare_address_book(record, PROPERTY_TYPE_UPDATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, id))) break;
		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_address_book._uri, id);

	return ret;
}

static int _ctsvc_tc_db_delete_record_address_book(int account_id)
{
	int ret = 0;
	int id = 0;
	contacts_record_h record = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_record_create_address_book(account_id, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_insert_record(record, &id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_address_book._uri, id, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, id))) break;
		if (CONTACTS_ERROR_NO_DATA != (ret = contacts_db_get_record(_contacts_address_book._uri, id, &record))) {
			ret = -1;
			break;
		}
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_address_book._uri, id);

	return ret;
}

int ctsvc_tc_db_insert_record_address_book(int account_id, int *p_id)
{
	if (account_id <= 0)
		return -1;

	int ret = 0;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_address_book(account_id, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = contacts_record_set_str(record, _contacts_address_book.name, PARENT_ADDRESS_BOOK_NAME))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_insert_record(record, p_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}