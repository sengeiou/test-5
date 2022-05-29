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
#include "utc-contacts-service-record-contact.h"
#include "utc-contacts-service-record-person.h"
#include "utc-contacts-service-db-address-book.h"
#include "utc-contacts-service-db-group.h"
#include "utc-contacts-service-db-contact.h"
#include "utc-contacts-service-db-person.h"

static int _ctsvc_tc_db_add_changed_cb_person(void);
static int _ctsvc_tc_db_remove_changed_cb_person(void);
static int _ctsvc_tc_db_get_record_person(int account_id);
static int _ctsvc_tc_db_get_records_with_query_person(int account_id);
static int _ctsvc_tc_db_get_all_records_person(int account_id);
static int _ctsvc_tc_db_get_count_person(int account_id);
static int _ctsvc_tc_db_get_count_with_query_person(int account_id);
static int _ctsvc_tc_db_update_record_person(int account_id);
static int _ctsvc_tc_db_update_records_person(int account_id);
static int _ctsvc_tc_db_delete_record_person(int account_id);
static int _ctsvc_tc_db_delete_records_person(int account_id);
static int _ctsvc_tc_db_search_records_person(int account_id);
static int _ctsvc_tc_db_search_records_with_query_person(int account_id);
static int _ctsvc_tc_db_search_records_with_range_person(int account_id);
static int _ctsvc_tc_db_search_records_for_snippet_person(int account_id);
static int _ctsvc_tc_db_search_records_with_query_for_snippet_person(int account_id);
static int _ctsvc_tc_db_search_records_with_range_for_snippet_person(int account_id);
static int _ctsvc_tc_db_get_count_for_search_records_person(int account_id);
static int _ctsvc_tc_db_get_count_for_search_records_with_query_person(int account_id);
static int _ctsvc_tc_db_get_count_for_search_records_with_range_person(int account_id);


ctsvc_tc_db_plugin_s _tc_db_person = {
	.db_add_changed_cb = _ctsvc_tc_db_add_changed_cb_person,
	.db_remove_changed_cb = _ctsvc_tc_db_remove_changed_cb_person,
	.db_get_record = _ctsvc_tc_db_get_record_person,
	.db_get_records_with_query = _ctsvc_tc_db_get_records_with_query_person,
	.db_get_all_records = _ctsvc_tc_db_get_all_records_person,
	.db_get_changes_by_version = NULL,
	.db_get_count = _ctsvc_tc_db_get_count_person,
	.db_get_count_with_query = _ctsvc_tc_db_get_count_with_query_person,
	.db_insert_record = NULL,
	.db_insert_records = NULL,
	.db_update_record = _ctsvc_tc_db_update_record_person,
	.db_update_records = _ctsvc_tc_db_update_records_person,
	.db_delete_record = _ctsvc_tc_db_delete_record_person,
	.db_delete_records = _ctsvc_tc_db_delete_records_person,
	.db_replace_record = NULL,
	.db_replace_records = NULL,
	.db_search_records = _ctsvc_tc_db_search_records_person,
	.db_search_records_with_query = _ctsvc_tc_db_search_records_with_query_person,
	.db_search_records_with_range = _ctsvc_tc_db_search_records_with_range_person,
	.db_search_records_for_snippet = _ctsvc_tc_db_search_records_for_snippet_person,
	.db_search_records_with_query_for_snippet = _ctsvc_tc_db_search_records_with_query_for_snippet_person,
	.db_search_records_with_range_for_snippet = _ctsvc_tc_db_search_records_with_range_for_snippet_person,
	.db_get_count_for_search_records = _ctsvc_tc_db_get_count_for_search_records_person,
	.db_get_count_for_search_records_with_query = _ctsvc_tc_db_get_count_for_search_records_with_query_person,
	.db_get_count_for_search_records_with_range = _ctsvc_tc_db_get_count_for_search_records_with_range_person,
};

static int _ctsvc_tc_db_add_changed_cb_person(void)
{
	int ret = 0;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_add_changed_cb(_contacts_person._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_remove_changed_cb(_contacts_person._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		return 0;
	} while (0);
	return ret;
}

static int _ctsvc_tc_db_remove_changed_cb_person(void)
{
	int ret = 0;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_add_changed_cb(_contacts_person._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_remove_changed_cb(_contacts_person._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		return 0;
	} while (0);
	return ret;
}

static int _ctsvc_tc_db_get_record_person(int account_id)
{
	int ret = 0;
	int id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, id, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_person._uri, id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_get_records_with_query_person(int account_id)
{
	int ret = 0;
	int id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;
	contacts_record_h record_p = NULL;
	contacts_query_h query = NULL;
	contacts_filter_h filter = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_query_create(_contacts_person._uri, &query))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_create(_contacts_person._uri, &filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_add_int(filter, _contacts_person.id, CONTACTS_MATCH_EQUAL, id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_set_filter(query, filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_records_with_query(query, OFFSET_DEFAULT, LIMIT_DEFAULT, &list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_current_record_p(list, &record_p))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		list = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_destroy(query))) break;
		query = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	contacts_filter_destroy(filter);
	contacts_query_destroy(query);
	contacts_db_delete_record(_contacts_person._uri, id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_get_all_records_person(int account_id)
{
	int ret = 0;
	int id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_all_records(_contacts_person._uri, OFFSET_DEFAULT, LIMIT_DEFAULT, &list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_current_record_p(list, &record_p))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		list = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	contacts_db_delete_record(_contacts_person._uri, id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;

}


static int _ctsvc_tc_db_get_count_person(int account_id)
{
	int ret = 0;
	int id = 0;
	int address_book_id = 0;
	int group_id = 0;
	int count = 0;
	contacts_record_h record = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_count(_contacts_person._uri, &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_person._uri, id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}


static int _ctsvc_tc_db_get_count_with_query_person(int account_id)
{
	int ret = 0;
	int id = 0;
	int address_book_id = 0;
	int group_id = 0;
	int count = 0;
	contacts_record_h record = NULL;
	contacts_query_h query = NULL;
	contacts_filter_h filter = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_query_create(_contacts_person._uri, &query))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_create(_contacts_person._uri, &filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_add_int(filter, _contacts_person.id, CONTACTS_MATCH_EQUAL, id))) break;
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

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_filter_destroy(filter);
	contacts_query_destroy(query);

	contacts_db_delete_record(_contacts_person._uri, id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_update_record_person(int account_id)
{
	int ret = 0;
	int id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, id, &record))) break;
		if (0 != (ret = ctsvc_tc_record_update_person(record, PROPERTY_TYPE_UPDATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_update_record(record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, id, &record))) break;
		if (0 != (ret = ctsvc_tc_record_compare_person(record, PROPERTY_TYPE_UPDATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_person._uri, id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_update_records_person(int account_id)
{
	int ret = 0;
	int ids[2]= {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		contacts_list_create(&list);
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, ids[0], &record))) break;
		if (0 != (ret = ctsvc_tc_record_update_person(record, PROPERTY_TYPE_UPDATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, ids[1], &record))) break;
		if (0 != (ret = ctsvc_tc_record_update_person(record, PROPERTY_TYPE_UPDATE2))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_update_records(list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		list = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, ids[0], &record))) break;
		if (0 != (ret = ctsvc_tc_record_compare_person(record, PROPERTY_TYPE_UPDATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, ids[1], &record))) break;
		if (0 != (ret = ctsvc_tc_record_compare_person(record, PROPERTY_TYPE_UPDATE2))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		ids_count = 0;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_delete_record_person(int account_id)
{
	int ret = 0;
	int id = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, id, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_person._uri, id))) break;
		if (CONTACTS_ERROR_NO_DATA != (ret = contacts_db_get_record(_contacts_person._uri, id, &record))) {
			ret = -1;
			break;
		}

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_person._uri, id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_delete_records_person(int account_id)
{
	int ret = 0;
	int ids[2] = {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, ids[0], &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_record(_contacts_person._uri, ids[1], &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		if (CONTACTS_ERROR_NO_DATA != (ret = contacts_db_get_record(_contacts_person._uri, ids[0], &record))) {
			ret = -1;
			break;
		}
		if (CONTACTS_ERROR_NO_DATA != (ret = contacts_db_get_record(_contacts_person._uri, ids[1], &record))) {
			ret = -1;
			break;
		}
		ids_count = 0;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_search_records_person(int account_id)
{
	int ret = 0;
	int ids[2]= {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_search_records(_contacts_person._uri, "010", OFFSET_DEFAULT, LIMIT_DEFAULT, &list))) break;
		contacts_list_first(list);
		do
		{
			if (0 != (ret = contacts_list_get_current_record_p(list, &record_p)))break;
			if (0 != (ret = ctsvc_tc_record_compare_person(record_p, PROPERTY_TYPE_CREATE1)))break;
		} while (CONTACTS_ERROR_NONE == contacts_list_next(list));
		if (CONTACTS_ERROR_NONE != ret) break;
		contacts_list_destroy(list, true);

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_list_destroy(list, true);
	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_search_records_with_query_person(int account_id)
{
	int ret = 0;
	int ids[2]= {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_query_h query = NULL;
	contacts_filter_h filter = NULL;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		if (CONTACTS_ERROR_NONE != (ret = contacts_query_create(_contacts_person._uri, &query))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_create(_contacts_person._uri, &filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_add_int(filter, _contacts_person.id, CONTACTS_MATCH_EQUAL, ids[1]))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_set_filter(query, filter))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_search_records_with_query(query, "010", OFFSET_DEFAULT, LIMIT_DEFAULT, &list))) break;

		contacts_filter_destroy(filter);
		filter = NULL;
		contacts_query_destroy(query);
		query = NULL;

		contacts_list_first(list);
		do
		{
			if (0 != (ret = contacts_list_get_current_record_p(list, &record_p)))break;
			if (0 != (ret = ctsvc_tc_record_compare_person(record_p, PROPERTY_TYPE_CREATE1)))break;
		} while (CONTACTS_ERROR_NONE == contacts_list_next(list));

		if (CONTACTS_ERROR_NONE != ret) break;

		contacts_list_destroy(list, true);
		list = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_filter_destroy(filter);
	contacts_query_destroy(query);
	contacts_list_destroy(list, true);
	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_search_records_with_range_person(int account_id)
{
	int ret = 0;
	int ids[2]= {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_search_records_with_range(_contacts_person._uri,
				"010", OFFSET_DEFAULT, LIMIT_DEFAULT, CONTACTS_SEARCH_RANGE_NAME | CONTACTS_SEARCH_RANGE_NUMBER, &list))) break;
		contacts_list_first(list);
		do
		{
			if (0 != (ret = contacts_list_get_current_record_p(list, &record_p)))break;
			if (0 != (ret = ctsvc_tc_record_compare_person(record_p, PROPERTY_TYPE_CREATE1)))break;
		} while (CONTACTS_ERROR_NONE == contacts_list_next(list));
		if (CONTACTS_ERROR_NONE != ret) break;
		contacts_list_destroy(list, true);

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_list_destroy(list, true);
	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_search_records_for_snippet_person(int account_id)
{
	int ret = 0;
	int ids[2]= {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_search_records_for_snippet(_contacts_person._uri,
						"010", OFFSET_DEFAULT, LIMIT_DEFAULT, NULL, NULL, -1, &list))) break;
		contacts_list_first(list);
		do
		{
			if (0 != (ret = contacts_list_get_current_record_p(list, &record_p)))break;
			if (0 != (ret = ctsvc_tc_record_compare_person(record_p, PROPERTY_TYPE_CREATE1)))break;
		} while (CONTACTS_ERROR_NONE == contacts_list_next(list));
		if (CONTACTS_ERROR_NONE != ret) break;
		contacts_list_destroy(list, true);

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_list_destroy(list, true);
	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_search_records_with_query_for_snippet_person(int account_id)
{
	int ret = 0;
	int ids[2]= {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_query_h query = NULL;
	contacts_filter_h filter = NULL;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		if (CONTACTS_ERROR_NONE != (ret = contacts_query_create(_contacts_person._uri, &query))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_create(_contacts_person._uri, &filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_add_int(filter, _contacts_person.id, CONTACTS_MATCH_EQUAL, ids[1]))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_set_filter(query, filter))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_search_records_with_query_for_snippet(query,
						"010", OFFSET_DEFAULT, LIMIT_DEFAULT, NULL, NULL, -1, &list))) break;

		contacts_filter_destroy(filter);
		filter = NULL;
		contacts_query_destroy(query);
		query = NULL;

		contacts_list_first(list);
		do
		{
			if (0 != (ret = contacts_list_get_current_record_p(list, &record_p)))break;
			if (0 != (ret = ctsvc_tc_record_compare_person(record_p, PROPERTY_TYPE_CREATE1)))break;
		} while (CONTACTS_ERROR_NONE == contacts_list_next(list));

		if (CONTACTS_ERROR_NONE != ret) break;

		contacts_list_destroy(list, true);
		list = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_filter_destroy(filter);
	contacts_query_destroy(query);
	contacts_list_destroy(list, true);
	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_search_records_with_range_for_snippet_person(int account_id)
{
	int ret = 0;
	int ids[2]= {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_search_records_with_range_for_snippet(_contacts_person._uri,
				"010", OFFSET_DEFAULT, LIMIT_DEFAULT, CONTACTS_SEARCH_RANGE_NAME | CONTACTS_SEARCH_RANGE_NUMBER,
				NULL, NULL, -1, &list))) break;
		contacts_list_first(list);
		do
		{
			if (0 != (ret = contacts_list_get_current_record_p(list, &record_p)))break;
			if (0 != (ret = ctsvc_tc_record_compare_person(record_p, PROPERTY_TYPE_CREATE1)))break;
		} while (CONTACTS_ERROR_NONE == contacts_list_next(list));
		if (CONTACTS_ERROR_NONE != ret) break;
		contacts_list_destroy(list, true);

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_list_destroy(list, true);
	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

int ctsvc_tc_db_insert_record_person(int address_book_id, int group_id, ctsvc_property_type_e type, int *p_id)
{
	if (address_book_id < 0)
		return -1;

	int id = 0;
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_create_contact(address_book_id, group_id, type, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_insert_record(record, &id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (contacts_db_get_record(_contacts_contact._uri, id, &record))) break;
		if (CONTACTS_ERROR_NONE != (contacts_record_get_int(record, _contacts_contact.person_id, p_id))) break;
		if (CONTACTS_ERROR_NONE != (contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}


static int _ctsvc_tc_db_get_count_for_search_records_person(int account_id)
{
	int ret = 0;
	int ids[2]= {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	int count = 0;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_count_for_search_records(_contacts_person._uri, "010", &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_get_count_for_search_records_with_query_person(int account_id)
{
	int ret = 0;
	int ids[2]= {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	contacts_query_h query = NULL;
	contacts_filter_h filter = NULL;
	int count = 0;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		if (CONTACTS_ERROR_NONE != (ret = contacts_query_create(_contacts_person._uri, &query))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_create(_contacts_person._uri, &filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_add_int(filter, _contacts_person.id, CONTACTS_MATCH_EQUAL, ids[1]))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_set_filter(query, filter))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_count_for_search_records_with_query(query, "010", &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}

		contacts_filter_destroy(filter);
		filter = NULL;
		contacts_query_destroy(query);
		query = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_filter_destroy(filter);
	contacts_query_destroy(query);
	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_get_count_for_search_records_with_range_person(int account_id)
{
	int ret = 0;
	int ids[2]= {0};
	int ids_count = 0;
	int address_book_id = 0;
	int group_id = 0;
	int count = 0;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[0])))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_person(address_book_id, group_id, PROPERTY_TYPE_CREATE1, &(ids[1])))) break;
		ids_count = 2;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_count_for_search_records_with_range(_contacts_person._uri, "010", CONTACTS_SEARCH_RANGE_NAME | CONTACTS_SEARCH_RANGE_NUMBER, &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_records(_contacts_person._uri, ids, ids_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_db_delete_records(_contacts_person._uri, ids, ids_count);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

