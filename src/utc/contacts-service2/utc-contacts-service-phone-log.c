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

#define API_NAME_CONTACTS_PHONE_LOG_RESET_STATISTICS "contacts_phone_log_reset_statistics"

static int _startup_err;

/**
 * @function		utc_contacts_service2_phone_log_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_phone_log_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_phone_log_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_phone_log_cleanup(void)
{
	contacts_disconnect();
}

/**
 * @testcase		utc_contacts_service2_phone_log_reset_statistics_p
 * @since_tizen		2.3
 * @description		Test reseting the phone log's count.
 */
int utc_contacts_service2_phone_log_reset_statistics_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_phone_log_reset_statistics();
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_phone_log_reset_statistics_by_sim_p
 * @since_tizen		3.0
 * @description		Test reseting the phone log's count by sim slot no.
 */
int utc_contacts_service2_phone_log_reset_statistics_by_sim_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_phone_log_reset_statistics_by_sim(0);
	if (false == ctsvc_tc_util_is_sim_support() || false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_phone_log_reset_statistics_by_sim_n
 * @since_tizen		3.0
 * @description		Test fail reseting the phone log's count by sim slot no.
 */
int utc_contacts_service2_phone_log_reset_statistics_by_sim_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	ret = contacts_phone_log_reset_statistics_by_sim(-1);
	if (false == ctsvc_tc_util_is_contact_support())
		assert_eq(CONTACTS_ERROR_NOT_SUPPORTED, ret);
	else
		assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}
