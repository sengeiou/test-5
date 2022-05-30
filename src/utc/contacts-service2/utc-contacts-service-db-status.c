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

#define API_NAME_CONTACTS_DB_ADD_STATUS_CHANGED_CB "contacts_db_add_status_changed_cb"
#define API_NAME_CONTACTS_DB_REMOVE_STATUS_CHANGED_CB "contacts_db_get_status"
#define API_NAME_CONTACTS_DB_GET_STATUS "contacts_db_remove_status_changed_cb"

static int _startup_err;

/**
 * @function		utc_contacts_service2_db_status_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_db_status_startup(void)
{
	_startup_err = 0;
	_startup_err = contacts_connect();
}

/**
 * @function		utc_contacts_service2_db_status_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_contacts_service2_db_status_cleanup(void)
{
	contacts_disconnect();
}

/**
 * @testcase		utc_contacts_service2_db_get_status_p
 * @since_tizen		2.3
 * @description		Test getting the current status of server.
 */
int utc_contacts_service2_db_get_status_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;
	contacts_db_status_e status;

	ret = contacts_db_get_status(&status);
	assert_eq(CONTACTS_ERROR_NONE, ret);

	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_get_status_n
 * @since_tizen		2.3
 * @description		Test fail getting the current status of server with invalid parameter.
 */
int utc_contacts_service2_db_get_status_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	ret = contacts_db_get_status(NULL);
	assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}

static void _status_changed_cb(contacts_db_status_e status, void* user_data)
{

}

/**
 * @testcase		utc_contacts_service2_db_add_status_changed_cb_p
 * @since_tizen		2.3
 * @description		Test registering a callback function to be invoked when status changes.
 */
int utc_contacts_service2_db_add_status_changed_cb_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_add_status_changed_cb(_status_changed_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_remove_status_changed_cb(_status_changed_cb, NULL))) break;
		return 0;
	} while (0);
	contacts_db_remove_status_changed_cb(_status_changed_cb, NULL);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_add_status_changed_cb_n
 * @since_tizen		2.3
 * @description		Test fail registering a status-changed callback with invalid parameters.
 */
int utc_contacts_service2_db_add_status_changed_cb_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	ret = contacts_db_add_status_changed_cb(NULL, NULL);
	assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}


/**
 * @testcase		utc_contacts_service2_db_remove_status_changed_cb_p
 * @since_tizen		2.3
 * @description		Test unregistering a callback function to be invoked when status changes.
 */
int utc_contacts_service2_db_remove_status_changed_cb_p(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_add_status_changed_cb(_status_changed_cb, NULL))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_remove_status_changed_cb(_status_changed_cb, NULL))) break;
		return 0;
	} while (0);
	contacts_db_remove_status_changed_cb(_status_changed_cb, NULL);
	assert_eq(CONTACTS_ERROR_NONE, ret);
	return 0;
}

/**
 * @testcase		utc_contacts_service2_db_remove_status_changed_cb_n
 * @since_tizen		2.3
 * @description		Test fail unregistering a status-changed callback with invalid parameters.
 */
int utc_contacts_service2_db_remove_status_changed_cb_n(void)
{
	assert_eq(_startup_err, 0);

	int ret = 0;

	ret = contacts_db_remove_status_changed_cb(NULL, NULL);
	assert_eq(CONTACTS_ERROR_INVALID_PARAMETER, ret);

	return 0;
}
