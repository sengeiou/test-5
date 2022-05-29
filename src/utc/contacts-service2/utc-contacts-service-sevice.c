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

#define API_NAME_CONTACTS_CONNECT "contacts_connect"
#define API_NAME_CONTACTS_CONNECT_ON_THREAD "contacts_connect_on_thread"
#define API_NAME_CONTACTS_CONNECT_WITH_FLAGS "contacts_connect_with_flags"
#define API_NAME_CONTACTS_DISCONNECT "contacts_disconnect"
#define API_NAME_CONTACTS_DISCONNECT_ON_THREAD "contacts_disconnect_on_thread"

static int _startup_err;

/**
 * @function		utc_contacts_service2_service_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_service_startup(void)
{
	_startup_err = 0;
}

/**
 * @function		utc_contacts_service2_service_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_service_cleanup(void)
{
}


/**
 * @testcase		utc_contacts_service2_connect_p
 * @since_tizen		2.3
 * @description		Connects to the contacts service.
 */
int utc_contacts_service2_connect_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_connect();
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_connect())) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_disconnect())) break;
		return 0;
	} while (0);
	contacts_disconnect();
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_connect_on_flags_p
 * @since_tizen		2.3
 * @description		Connects to the contacts service with flags.
 */
int utc_contacts_service2_connect_on_flags_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_connect_with_flags(CONTACTS_CONNECT_FLAG_RETRY);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_connect_with_flags(CONTACTS_CONNECT_FLAG_RETRY))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_disconnect())) break;
		return 0;
	} while (0);
	contacts_disconnect();
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_connect_on_flags_n
 * @since_tizen		2.3
 * @description		Connects to the contacts service with invalid flags.
 */
int utc_contacts_service2_connect_on_flags_n(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_connect_with_flags(INVALID_CONNECT_FLAG);
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = contacts_connect_with_flags(INVALID_CONNECT_FLAG);
	assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_disconnect_p
 * @since_tizen		2.3
 * @description		Disconnects from the contacts service.
 */
int utc_contacts_service2_disconnect_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_disconnect();
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_connect())) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_disconnect())) break;
		return 0;
	} while (0);
	contacts_disconnect();
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}


/**
 * @testcase		utc_contacts_service2_connect_on_thread_p
 * @since_tizen		2.3
 * @description		Connects from the contacts service on thread.
 */
int utc_contacts_service2_connect_on_thread_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_connect_on_thread();
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_connect_on_thread())) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_disconnect_on_thread())) break;
		return 0;
	} while (0);
	contacts_disconnect_on_thread();
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_disconnect_on_thread_p
 * @since_tizen		2.3
 * @description		Disconnects from the contacts service on thread.
 */
int utc_contacts_service2_disconnect_on_thread_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		ret = contacts_disconnect_on_thread();
		assert_eq(ret, CONTACTS_ERROR_NOT_SUPPORTED);
		return 0;
	}

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_connect_on_thread())) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_disconnect_on_thread())) break;
		return 0;
	} while (0);
	contacts_disconnect_on_thread();
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}
