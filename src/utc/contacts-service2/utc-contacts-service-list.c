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

#define API_NAME_CONTACTS_LIST_CREATE "contacts_list_create"
#define API_NAME_CONTACTS_LIST_DESTROY "contacts_list_destroy"
#define API_NAME_CONTACTS_LIST_FIRST "contacts_list_first"
#define API_NAME_CONTACTS_LIST_GET_COUNT "contacts_list_get_count"
#define API_NAME_CONTACTS_LIST_GET_CURRENT_RECORD_P "contacts_list_get_current_record_p"
#define API_NAME_CONTACTS_LIST_LAST "contacts_list_last"
#define API_NAME_CONTACTS_LIST_NEXT "contacts_list_next"
#define API_NAME_CONTACTS_LIST_PREV "contacts_list_prev"
#define API_NAME_CONTACTS_LIST_ADD "contacts_list_add"
#define API_NAME_CONTACTS_LIST_REMOVE "contacts_list_remove"

static int _startup_err;

/**
 * @function		utc_contacts_service2_list_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_list_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_list_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_list_cleanup(void)
{
	contacts_disconnect();
}


/**
 * @testcase		utc_contacts_service2_list_create_p
 * @since_tizen		2.3
 * @description		Test creating a contacts list.
 */
int utc_contacts_service2_list_create_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_list_h list = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_list_create(&list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_create(&list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_create_n
 * @since_tizen		2.3
 * @description		Test fail creating a contacts list with invalid parameters.
 */
int utc_contacts_service2_list_create_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_list_create(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_destroy_p
 * @since_tizen		2.3
 * @description		Test destroying a contacts list and releases its all resources.
 */
int utc_contacts_service2_list_destroy_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_list_h list = NULL;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_list_destroy(list, true);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_create(&list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_destroy_n
 * @since_tizen		2.3
 * @description		Test fail destroying a contacts list with invalid parameters.
 */
int utc_contacts_service2_list_destroy_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_list_destroy(NULL, true);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}



/**
 * @testcase		utc_contacts_service2_list_first_p
 * @since_tizen		2.3
 * @description		Test moving a contacts list to the first position.
 */
int utc_contacts_service2_list_first_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;
	const char *view_uri = _contacts_contact._uri;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_list_first(list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_create(&list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_first(list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_first_n
 * @since_tizen		2.3
 * @description		Test fail moving a contacts list to the first position with invalid parameters.
 */
int utc_contacts_service2_list_first_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_list_first(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_get_count_p
 * @since_tizen		2.3
 * @description		Test retrieving the number of contact entities from a contacts list.
 */
int utc_contacts_service2_list_get_count_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	int count = 0;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;
	const char *view_uri = _contacts_contact._uri;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_list_get_count(list, &count);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_create(&list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_count(list, &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_get_count_n
 * @since_tizen		2.3
 * @description		Test fail retrieving the number of contact entities with invalid paramter.
 */
int utc_contacts_service2_list_get_count_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	int count = 0;

	ret = contacts_list_get_count(NULL, &count);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_get_current_record_p_p
 * @since_tizen		2.3
 * @description		Test retrieving a record from the contacts list.
 */
int utc_contacts_service2_list_get_current_record_p_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_p = NULL;
	const char *view_uri = _contacts_contact._uri;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_list_get_current_record_p(list, &record_p);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_create(&list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_current_record_p(list, &record_p))) break;
		if (NULL == record_p) {
			ret = -1;
			break;
		}
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_get_current_record_p_n
 * @since_tizen		2.3
 * @description		Test fail retrieving a record from the contacts list with invalid parameters.
 */
int utc_contacts_service2_list_get_current_record_p_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_record_h record = NULL;

	ret = contacts_list_get_current_record_p(NULL, &record);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_last_p
 * @since_tizen		2.3
 * @description		Test moving a contacts list to the last position.
 */
int utc_contacts_service2_list_last_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;
	const char *view_uri = _contacts_contact._uri;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_list_last(list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_create(&list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_last(list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_last_n
 * @since_tizen		2.3
 * @description		Test fail moving a contacts list to the last position with invalid parameters.
 */
int utc_contacts_service2_list_last_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_list_last(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_next_p
 * @since_tizen		2.3
 * @description		Test moving a contacts list to the next position.
 */
int utc_contacts_service2_list_next_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;
	const char *view_uri = _contacts_contact._uri;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_list_next(list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_create(&list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_next(list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_next_n
 * @since_tizen		2.3
 * @description		Test fail moving a contacts list to the next position with invalid parameters.
 */
int utc_contacts_service2_list_next_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_list_next(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_prev_p
 * @since_tizen		2.3
 * @description		Test moving a contacts list to the previous position.
 */
int utc_contacts_service2_list_prev_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;
	const char *view_uri = _contacts_contact._uri;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_list_prev(list);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_create(&list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_next(list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_prev(list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_prev_n
 * @since_tizen		2.3
 * @description		Test fail moving a contacts list to the previous position with invalid parameters.
 */
int utc_contacts_service2_list_prev_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_list_prev(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_add_p
 * @since_tizen		2.3
 * @description		Test adding a record to a contacts list.
 */
int utc_contacts_service2_list_add_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;
	const char *view_uri = _contacts_contact._uri;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_list_add(list, record);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_create(&list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_current_record_p(list, &record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;

}

/**
 * @testcase		utc_contacts_service2_list_add_n
 * @since_tizen		2.3
 * @description		Test fail adding a record to a contacts list with invalid parameters.
 */
int utc_contacts_service2_list_add_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;

	ret = contacts_list_add(list, record);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_remove_p
 * @since_tizen		2.3
 * @description		Test removing a record from the contacts list.
 */
int utc_contacts_service2_list_remove_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;
	const char *view_uri = _contacts_contact._uri;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_list_remove(list, record);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_create(&list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_add(list, record))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_current_record_p(list, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_remove(list, record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_list_remove_n
 * @since_tizen		2.3
 * @description		Test fail removing a record from the contacts list with invalid parameters.
 */
int utc_contacts_service2_list_remove_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_record_h record = NULL;

	ret = contacts_list_remove(NULL, record);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;


}
