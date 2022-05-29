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
#include "utc-contacts-service-db-address-book.h"
#include "utc-contacts-service-db-group.h"
#include "utc-contacts-service-db-group-updated-info.h"

static int _ctsvc_tc_db_get_chages_by_version_group_updated_info(int account_id);

ctsvc_tc_db_plugin_s _tc_db_group_updated_info = {
	.db_add_changed_cb = NULL,
	.db_remove_changed_cb = NULL,
	.db_get_record = NULL,
	.db_get_records_with_query = NULL,
	.db_get_all_records = NULL,
	.db_get_changes_by_version = _ctsvc_tc_db_get_chages_by_version_group_updated_info,
	.db_get_count = NULL,
	.db_get_count_with_query = NULL,
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

static int _ctsvc_tc_db_get_chages_by_version_group_updated_info(int account_id)
{
	int ret = 0;
	int address_book_id = 0;
	int group_id = 0;
	int version = 0;
	int version_new = 0;

	contacts_list_h list = NULL;
	contacts_record_h record_p = NULL;
	if (account_id <= 0)
		return -1;

	do {
		if (0 != (ret = contacts_db_get_current_version(&version))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id))) break;
		if (0 != (ret = ctsvc_tc_db_insert_record_group(address_book_id, &group_id))) break;

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_changes_by_version(_contacts_group_updated_info._uri, address_book_id, version, &list, &version_new))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_current_record_p(list, &record_p))) break;
		contacts_list_destroy(list, true);
		list = NULL;

		if (version == version_new) { // not change
			return -1;
			break;
		}

		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_group._uri, group_id))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_delete_record(_contacts_address_book._uri, address_book_id))) break;

		return 0;
	} while (0);

	contacts_list_destroy(list, true);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);

	return ret;

}
