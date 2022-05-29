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
#include "utc-contacts-service-record-group-relation.h"
#include "utc-contacts-service-db-address-book.h"
#include "utc-contacts-service-db-group.h"
#include "utc-contacts-service-db-contact.h"
#include "utc-contacts-service-db-group-relation.h"

static int _ctsvc_tc_db_add_changed_cb_group_relation(void);
static int _ctsvc_tc_db_remove_changed_cb_group_relation(void);
static int _ctsvc_tc_db_get_records_with_query_group_relation(int account_id);
static int _ctsvc_tc_db_get_all_records_group_relation(int account_id);
static int _ctsvc_tc_db_get_count_group_relation(int account_id);
static int _ctsvc_tc_db_get_count_with_query_group_relation(int account_id);


ctsvc_tc_db_plugin_s _tc_db_group_relation = {
	.db_add_changed_cb = _ctsvc_tc_db_add_changed_cb_group_relation,
	.db_remove_changed_cb = _ctsvc_tc_db_remove_changed_cb_group_relation,
	.db_get_record = NULL,
	.db_get_records_with_query = _ctsvc_tc_db_get_records_with_query_group_relation,
	.db_get_all_records = _ctsvc_tc_db_get_all_records_group_relation,
	.db_get_changes_by_version = NULL,
	.db_get_count = _ctsvc_tc_db_get_count_group_relation,
	.db_get_count_with_query = _ctsvc_tc_db_get_count_with_query_group_relation,
	.db_insert_record = NULL,
	.db_insert_records = NULL,
	.db_update_record = NULL,
	.db_update_records = NULL,
	.db_delete_record = NULL,
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

static int _ctsvc_tc_db_add_changed_cb_group_relation(void)
{
	int ret = 0;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_add_changed_cb(_contacts_group_relation._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_remove_changed_cb(_contacts_group_relation._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		return 0;
	} while (0);
	return ret;
}

static int _ctsvc_tc_db_remove_changed_cb_group_relation(void)
{
	int ret = 0;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_add_changed_cb(_contacts_group_relation._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_remove_changed_cb(_contacts_group_relation._uri, ctsvc_tc_util_db_changed_cb, NULL))) break;
		return 0;
	} while (0);
	return ret;
}

static int _ctsvc_tc_db_get_records_with_query_group_relation(int account_id)
{
	int ret = 0;
	int address_book_id = 0;
	int group_id = 0;
	int contact_id = 0;
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
		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_query_create(_contacts_group_relation._uri, &query))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_create(_contacts_group_relation._uri, &filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_add_int(filter, _contacts_group_relation.contact_id, CONTACTS_MATCH_EQUAL, contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_set_filter(query, filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_records_with_query(query, OFFSET_DEFAULT, LIMIT_DEFAULT, &list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_current_record_p(list, &record_p))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		list = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_query_destroy(query))) break;
		query = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_contact._uri, contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	contacts_filter_destroy(filter);
	contacts_query_destroy(query);
	contacts_db_delete_record(_contacts_contact._uri, contact_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}

static int _ctsvc_tc_db_get_all_records_group_relation(int account_id)
{
	int ret = 0;
	int address_book_id = 0;
	int group_id = 0;
	int contact_id = 0;
	contacts_record_h record = NULL;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_all_records(_contacts_group_relation._uri, OFFSET_DEFAULT, LIMIT_DEFAULT, &list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_current_record_p(list, &record_p))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		list = NULL;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_contact._uri, contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	contacts_db_delete_record(_contacts_contact._uri, contact_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;

}


static int _ctsvc_tc_db_get_count_group_relation(int account_id)
{
	int ret = 0;
	int address_book_id = 0;
	int group_id = 0;
	int contact_id = 0;
	int count = 0;
	contacts_record_h record = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_count(_contacts_group_relation._uri, &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_contact._uri, contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_record_destroy(record, true);
	contacts_db_delete_record(_contacts_contact._uri, contact_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}


static int _ctsvc_tc_db_get_count_with_query_group_relation(int account_id)
{
	int ret = 0;
	int address_book_id = 0;
	int group_id = 0;
	int contact_id = 0;
	int count = 0;
	contacts_record_h record = NULL;
	contacts_query_h query = NULL;
	contacts_filter_h filter = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_query_create(_contacts_group_relation._uri, &query))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_create(_contacts_group_relation._uri, &filter))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_add_int(filter, _contacts_group_relation.contact_id, CONTACTS_MATCH_EQUAL, contact_id))) break;
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

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_contact._uri, contact_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_filter_destroy(filter);
	contacts_query_destroy(query);

	contacts_db_delete_record(_contacts_contact._uri, contact_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;
}
