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

#define API_NAME_CONTACTS_QUERY_CREATE "contacts_query_create"
#define API_NAME_CONTACTS_QUERY_DESTROY "contacts_query_destroy"
#define API_NAME_CONTACTS_QUERY_SET_DISTINCT "contacts_query_set_distinct"
#define API_NAME_CONTACTS_QUERY_SET_FILTER "contacts_query_set_filter"
#define API_NAME_CONTACTS_QUERY_SET_PROJECTION "contacts_query_set_projection"
#define API_NAME_CONTACTS_QUERY_SET_SORT "contacts_query_set_sort"

static int _startup_err;

/**
 * @function		utc_contacts_service2_query_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_query_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_query_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_query_cleanup(void)
{
	contacts_disconnect();
}


/**
 * @testcase		utc_contacts_service2_query_create_p
 * @since_tizen		2.3
 * @description		Creates a query.
 */
int utc_contacts_service2_query_create_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret = 0;
	contacts_query_h query = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(0), &query);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), &query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
		ret = contacts_query_destroy(query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_query_create_n
 * @since_tizen		2.3
 * @description		Creates a query with invalid parameter.
 */
int utc_contacts_service2_query_create_n(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret = 0;
	contacts_query_h query = NULL;

	ret = contacts_query_create(NULL, &query);
	if (false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
		return 0;
	} else {
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), NULL);
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_query_destroy_p
 * @since_tizen		2.3
 * @description		Destroys a query.
 */
int utc_contacts_service2_query_destroy_p(void)
{
	assert_eq(_startup_err, 0);
	int i;
	int ret = 0;
	contacts_query_h query = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_query_destroy(query);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), &query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
		ret = contacts_query_destroy(query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_query_destroy_n
 * @since_tizen		2.3
 * @description		Destroys a query with invalid parameter.
 */
int utc_contacts_service2_query_destroy_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_query_destroy(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_query_set_distinct_p
 * @since_tizen		2.3
 * @description		Sets the "distinct" option for projection.
 */
int utc_contacts_service2_query_set_distinct_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret = 0;
	contacts_query_h query = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_query_set_distinct(query, true);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), &query);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_query_set_distinct(query, true);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_query_destroy(query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_query_set_distinct_n
 * @since_tizen		2.3
 * @description		Sets the "distinct" option for projection with invalid parameter.
 */
int utc_contacts_service2_query_set_distinct_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	ret = contacts_query_set_distinct(NULL, true);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_query_set_filter_p
 * @since_tizen		2.3
 * @description		Sets a filter for query.
 */
int utc_contacts_service2_query_set_filter_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret = 0;
	contacts_query_h query = NULL;
	contacts_filter_h filter = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_query_set_filter(query, filter);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), &query);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_filter_create(ctsvc_tc_util_get_view_uri(i), &filter);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_query_set_filter(query, filter);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_query_destroy(query);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_filter_destroy(filter);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}


/**
 * @testcase		utc_contacts_service2_query_set_filter_n
 * @since_tizen		2.3
 * @description		Sets a filter for query with invalid parameters.
 */
int utc_contacts_service2_query_set_filter_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	ret = contacts_query_set_filter(NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);


	return 0;
}

/**
 * @testcase		utc_contacts_service2_query_set_projection_p
 * @since_tizen		2.3
 * @description		Adds property IDs for projection.
 */
int utc_contacts_service2_query_set_projection_p(void)
{
	assert_eq(_startup_err, 0);

	int i;
	int ret = 0;
	unsigned int projection_list[] = {};
	int projection_count = sizeof(projection_list)/sizeof(int);
	contacts_query_h query = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_query_set_projection(query, projection_list, projection_count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i=0;i<VIEW_MAX;i++) {
		ret = contacts_query_create(ctsvc_tc_util_get_view_uri(i), &query);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_query_set_projection(query, projection_list, projection_count);
		assert_eq(CONTACTS_ERROR_NONE, ret);

		ret = contacts_query_destroy(query);
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	/* check */
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	int contact_id = 0;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	unsigned int projection[] = {_contacts_contact.address_book_id,};
	int get_id = 0;

	ctsvc_tc_util_account_insert(&account_id);
	ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id);
	ctsvc_tc_db_insert_record_group(address_book_id, &group_id);
	ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id);

	contacts_query_create(_contacts_contact._uri, &query);
	ret = contacts_query_set_projection(query, projection,sizeof(projection)/sizeof(int));
	if (CONTACTS_ERROR_NONE != ret) {
		contacts_query_destroy(query);
		query = NULL;
		contacts_db_delete_record(_contacts_contact._uri, contact_id);
		contacts_db_delete_record(_contacts_group._uri, group_id);
		contacts_db_delete_record(_contacts_address_book._uri, address_book_id);
		return 1;
	}

	contacts_db_get_records_with_query(query, OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
	contacts_list_first(list);
	do
	{
		contacts_list_get_current_record_p(list, &record_p);
		if (record_p) {
			ret = contacts_record_get_int(record_p, _contacts_contact.address_book_id, &get_id);
			if (CONTACTS_ERROR_NONE != ret) {
				ret = -1;
				break;
			}
			get_id = 0;
			/* check non projection id */
			ret = contacts_record_get_int(record_p, _contacts_contact.person_id, &get_id);
			if (CONTACTS_ERROR_INVALID_PARAMETER != ret) {
				get_id = -1;
				break;
			}
		}
	} while (CONTACTS_ERROR_NONE == contacts_list_next(list));

	contacts_list_destroy(list, true);
	list = NULL;
	contacts_query_destroy(query);
	query = NULL;
	contacts_db_delete_record(_contacts_contact._uri, contact_id);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);
	assert_neq(-1, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_query_set_projection_n
 * @since_tizen		2.3
 * @description		Adds property IDs for projection with invalid parameters.
 */
int utc_contacts_service2_query_set_projection_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	ret = contacts_query_set_projection(NULL, NULL, INVALID_COUNT);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_query_set_sort_p
 * @since_tizen		2.3
 * @description		Sets a sort mode for query.
 */
int utc_contacts_service2_query_set_sort_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_query_h query = NULL;
	const char *test_view_uri = _contacts_contact._uri;
	unsigned int test_property_id = _contacts_contact.id;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_query_set_sort(query, test_property_id, true);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = contacts_query_create(test_view_uri, &query);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_query_set_sort(query, test_property_id, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	ret = contacts_query_destroy(query);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	/* check */
	int account_id = 0;
	int address_book_id = 0;
	int group_id = 0;
	int contact_id = 0;
	int contact_id2 = 0;
	contacts_record_h record_p = NULL;
	contacts_list_h list = NULL;
	int prev_id = 0;
	int get_id = 0;

	ctsvc_tc_util_account_insert(&account_id);
	ctsvc_tc_db_insert_record_address_book(account_id, &address_book_id);
	ctsvc_tc_db_insert_record_group(address_book_id, &group_id);
	ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id);
	ctsvc_tc_db_insert_record_contact(address_book_id, group_id, &contact_id2);

	contacts_query_create(_contacts_contact._uri, &query);
	ret = contacts_query_set_sort(query, test_property_id, true);
	if (CONTACTS_ERROR_NONE != ret) {
		contacts_query_destroy(query);
		query = NULL;
		contacts_db_delete_record(_contacts_contact._uri, contact_id);
		contacts_db_delete_record(_contacts_contact._uri, contact_id2);
		contacts_db_delete_record(_contacts_group._uri, group_id);
		contacts_db_delete_record(_contacts_address_book._uri, address_book_id);
		return 1;
	}

	contacts_db_get_records_with_query(query, OFFSET_DEFAULT, LIMIT_DEFAULT, &list);
	contacts_list_first(list);
	do
	{
		contacts_list_get_current_record_p(list, &record_p);
		if (record_p) {
			contacts_record_get_int(record_p, test_property_id, &get_id);
			if (get_id < prev_id) {
				ret = -1;
				break;
			}
			prev_id = get_id;
			get_id = 0;
		}

	} while (CONTACTS_ERROR_NONE == contacts_list_next(list));

	contacts_list_destroy(list, true);
	list = NULL;
	contacts_query_destroy(query);
	query = NULL;
	contacts_db_delete_record(_contacts_contact._uri, contact_id);
	contacts_db_delete_record(_contacts_contact._uri, contact_id2);
	contacts_db_delete_record(_contacts_group._uri, group_id);
	contacts_db_delete_record(_contacts_address_book._uri, address_book_id);
	assert_neq(-1, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_query_set_sort_n
 * @since_tizen		2.3
 * @description		Sets a sort mode for query with invalid parameters.
 */
int utc_contacts_service2_query_set_sort_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	ret = contacts_query_set_sort(NULL, INVALID_PROPERTY_ID, true);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}
