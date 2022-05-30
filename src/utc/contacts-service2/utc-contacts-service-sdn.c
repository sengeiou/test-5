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

static int _startup_err;

/**
 * @function		utc_contacts_service2_sdn_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_sdn_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
	if (_startup_err == CONTACTS_ERROR_NOT_SUPPORTED
		&& false == ctsvc_tc_util_is_contact_support())
		_startup_err = CONTACTS_ERROR_NONE;
}

/**
 * @function		utc_contacts_service2_sdn_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_sdn_cleanup(void)
{
	contacts_disconnect();
}

extern ctsvc_tc_db_plugin_s _tc_db_sdn;

/**
 * @testcase		utc_contacts_service2_sdn_db_p
 * @since_tizen		2.3
 * @description		Each DB test for SDN view.
 */
int utc_contacts_service2_sdn_db_p(void)
{
	assert_eq(_startup_err, 0);
	int ret = 0;

	if (false == ctsvc_tc_util_is_contact_support()) {
		/* This test case for the specific view(sdn) is not needed if contact feature is not supported
		because contacts service db API is tested in utc-contacts-service-db.c */
		return 0;
	}

	do {
		if (0 != (ret = _tc_db_sdn.db_add_changed_cb())) break;
		if (0 != (ret = _tc_db_sdn.db_remove_changed_cb())) break;
		if (0 != (ret = _tc_db_sdn.db_get_record(0))) break;
		if (0 != (ret = _tc_db_sdn.db_get_records_with_query(0))) break;
		if (0 != (ret = _tc_db_sdn.db_get_all_records(0))) break;
		if (0 != (ret = _tc_db_sdn.db_get_count(0))) break;
		if (0 != (ret = _tc_db_sdn.db_get_count_with_query(0))) break;
		return 0;
	} while (0);
	assert_eq(0, ret);
	return 0;
}
