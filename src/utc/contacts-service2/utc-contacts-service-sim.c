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
#include <telephony.h>

#include "assert.h"
#include "utc-contacts-service-tc-utils.h"

static int _startup_err;
static bool _cb_invoked = false;


/**
 * @function		utc_contacts_service2_sim_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_sim_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_sim_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_sim_cleanup(void)
{
	contacts_disconnect();
}

#ifdef MOBILE
/**
 * @testcase		utc_contacts_service2_sim_get_initialization_status_p
 * @since_tizen		2.3
 * @description		Checks whether first SIM initialization is completed.
 */
int utc_contacts_service2_sim_get_initialization_status_p(void)
{
	assert_eq(_startup_err, 0);
	bool complete = false;
	int ret = 0;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_sim_get_initialization_status(&complete))) break;
		return 0;
	} while (0);

	if (false == ctsvc_tc_util_is_sim_support() || false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_sim_get_initialization_status_n
 * @since_tizen		2.3
 * @description		Checks whether first SIM initialization is completed with invalid parameters.
 */
int utc_contacts_service2_sim_get_initialization_status_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_sim_get_initialization_status(NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_sim_import_all_contacts_p
 * @since_tizen		2.3
 * @description		Imports all contacts from first SIM to Contacts Database.
 */

int utc_contacts_service2_sim_import_all_contacts_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_sim_import_all_contacts())) break;
		return 0;
	} while (0);

	if (false == ctsvc_tc_util_is_sim_support() || false == ctsvc_tc_util_is_contact_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	}
	else {
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}
#endif

/**
 * @testcase		utc_contacts_service2_sim_get_initialization_status_by_sim_slot_no_p
 * @since_tizen		3.0
 * @description		Checks whether SIM of the given SIM slot number is initialized
 */
int utc_contacts_service2_sim_get_initialization_status_by_sim_slot_no_p(void)
{
	assert_eq(_startup_err, 0);
	bool complete = false;
	int ret = 0;
	int cnt = 0;
	telephony_handle_list_s handle_list;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_sim_get_initialization_status_by_sim_slot_no(0, &complete);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		ret = telephony_init(&handle_list);
		if (TELEPHONY_ERROR_NONE != ret)
			break;

		for (cnt = 0; cnt < handle_list.count; cnt++) {
			ret = contacts_sim_get_initialization_status_by_sim_slot_no(cnt, &complete);
			if (CONTACTS_ERROR_NONE != ret)
				break;
		}

		telephony_deinit(&handle_list);

		if (CONTACTS_ERROR_NONE != ret)
			break;

		return 0;
	} while (0);

	if (!ctsvc_tc_util_is_sim_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	}
	else {
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}
	return 0;
}

/**
 * @testcase		utc_contacts_service2_sim_get_initialization_status_by_sim_slot_no_n
 * @since_tizen		3.0
 * @description		Checks whether SIM of the given SIM slot number is initialized with invalid parameters.
 */
int utc_contacts_service2_sim_get_initialization_status_by_sim_slot_no_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_sim_get_initialization_status_by_sim_slot_no(-1, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

static bool _import_progress_cb(int total, int imported_cnt, void *user_data)
{
	_cb_invoked = true;
	return true;
}

/**
 * @testcase		utc_contacts_service2_sim_import_all_contacts_by_sim_slot_no_p
 * @since_tizen		3.0
 * @description		Imports all contacts from SIM of the given SIM slot number to Contacts Database.
 */
int utc_contacts_service2_sim_import_all_contacts_by_sim_slot_no_p(void)
{
	assert_eq(_startup_err, 0);
	bool is_failed = false;
	int ret = 0;
	int cnt = 0;
	telephony_handle_list_s handle_list;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_sim_import_all_contacts_by_sim_slot_no(cnt, _import_progress_cb, NULL);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		ret = telephony_init(&handle_list);
		if (TELEPHONY_ERROR_NONE != ret)
			break;

		for (cnt = 0; cnt < handle_list.count; cnt++) {
			_cb_invoked= false;
			ret = contacts_sim_import_all_contacts_by_sim_slot_no(cnt, _import_progress_cb, NULL);
			if ((CONTACTS_ERROR_NONE != ret && CONTACTS_ERROR_NO_DATA != ret)
#ifdef MOBILE
					||(CONTACTS_ERROR_NO_DATA == ret && 0 == cnt) /* first SIM should be inserted and has SIM contacts*/
#endif
					||(CONTACTS_ERROR_NONE == ret && false == _cb_invoked)) {
				is_failed = true;
				break;
			}
		}
		telephony_deinit(&handle_list);

		if (is_failed)
			break;

		return 0;
	} while (0);

	if (!ctsvc_tc_util_is_sim_support()) {
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	}
	else {
		assert_eq(CONTACTS_ERROR_NONE, ret);
	}

	return 0;
}

/**
 * @testcase		utc_contacts_service2_sim_import_all_contacts_by_sim_slot_no_n
 * @since_tizen		3.0
 * @description		Imports all contacts from SIM of the given SIM slot number to Contacts Database with invalid parameters.
 */
int utc_contacts_service2_sim_import_all_contacts_by_sim_slot_no_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_sim_import_all_contacts_by_sim_slot_no(-1, NULL, NULL);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

