//
// Copyright (c) 2014 - 2018 Samsung Electronics Co., Ltd.
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
#include "assert.h"

#include <privacy_privilege_manager.h>

static const char *location_privilege = "http://tizen.org/privilege/location";

/**
 * @testcase		utc_ppm_check_permission_n1
 * @since_tizen		4.0
 * @description		Check permission for a given privilege
 *					- check status of privilege when the privilege parameter is NULL
 */
int utc_ppm_check_permission_n1(void)
{
	int ret;
	ppm_check_result_e result = PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ALLOW;
	ret = ppm_check_permission(NULL, &result);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);
	assert_eq(result, PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ALLOW);

	return 0;
}

/**
 * @testcase		utc_ppm_check_permission_n2
 * @since_tizen		4.0
 * @description		Check permission for a given privilege
 *					- check status of privilege when the privilege parameter is
 *					  an empty string
 */
int utc_ppm_check_permission_n2(void)
{
	int ret;
	ppm_check_result_e result = PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ALLOW;

	ret = ppm_check_permission("", &result);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);
	assert_eq(result, PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ALLOW);

	return 0;
}

/**
 * @testcase		utc_ppm_check_permission_n3
 * @since_tizen		4.0
 * @description		Check permission for a given privilege
 *					- check status of privilege when the result parameter is NULL
 */
int utc_ppm_check_permission_n3(void)
{
	int ret;

	ret = ppm_check_permission(location_privilege, NULL);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_ppm_check_permissions_n1
 * @since_tizen		5.0
 * @description		Check permission for a given privileges
 *					- check status of privileges when the privileges parameter is NULL
 */
int utc_ppm_check_permissions_n1(void)
{
	int ret;
	ppm_check_result_e result = PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ALLOW;
	ret = ppm_check_permissions(NULL, 0, &result);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);
	assert_eq(result, PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ALLOW);

	return 0;
}

/**
 * @testcase		utc_ppm_check_permissions_n2
 * @since_tizen		5.0
 * @description		Check permission for a given privileges
 *					- check status of privileges when the privileges parameter is
 *					  an empty string
 */
int utc_ppm_check_permissions_n2(void)
{
	int ret;
	ppm_check_result_e result = PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ALLOW;
	const char* empty_privilege = "";
	ret = ppm_check_permissions(&empty_privilege, 1, &result);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);
	assert_eq(result, PRIVACY_PRIVILEGE_MANAGER_CHECK_RESULT_ALLOW);

	return 0;
}

/**
 * @testcase		utc_ppm_check_permissions_n3
 * @since_tizen		5.0
 * @description		Check permission for a given privileges
 *					- check status of privileges when the result parameter is NULL
 */
int utc_ppm_check_permissions_n3(void)
{
	int ret;

	ret = ppm_check_permissions(&location_privilege, 1, NULL);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

void ppm_request_response_test_cb(ppm_call_cause_e cause,
								  ppm_request_result_e result,
								  const char *privilege,
								  void *user_data)
{
}

/**
 * @testcase		utc_ppm_request_permission_n1
 * @since_tizen		4.0
 * @description		Request user permission
 *					- request permission when the privilege parameter is NULL
 */
int utc_ppm_request_permission_n1(void)
{
	int ret;

	ret = ppm_request_permission(NULL, ppm_request_response_test_cb, NULL);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_ppm_request_permission_n2
 * @since_tizen		4.0
 * @description		Request user permission
 *					- request permission when the privilege parameter is an empty
 *					  string
 */
int utc_ppm_request_permission_n2(void)
{
	int ret;

	ret = ppm_request_permission("", ppm_request_response_test_cb, NULL);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_ppm_request_permission_n3
 * @since_tizen		4.0
 * @description		Request user permission
 *					- request permission when the callback parameter is NULL
 */
int utc_ppm_request_permission_n3(void)
{
	int ret;

	ret = ppm_request_permission(location_privilege, NULL, NULL);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

void ppm_request_multiple_response_test_cb(ppm_call_cause_e cause,
								  ppm_request_result_e *results,
								  const char **privileges,
								  size_t privileges_count,
								  void *user_data)
{
}

/**
 * @testcase		utc_ppm_request_permissions_n1
 * @since_tizen		5.0
 * @description		Request user permissions
 *					- request permissions when the privilege parameter is NULL
 */
int utc_ppm_request_permissions_n1(void)
{
	int ret;

	ret = ppm_request_permissions(NULL, 0, ppm_request_multiple_response_test_cb, NULL);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_ppm_request_permissions_n2
 * @since_tizen		5.0
 * @description		Request user permissions
 *					- request permissions when the privilege parameter is an empty
 *					  string
 */
int utc_ppm_request_permissions_n2(void)
{
	int ret;
	const char* empty_privilege = "";
	ret = ppm_request_permissions(&empty_privilege, 1, ppm_request_response_test_cb, NULL);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_ppm_request_permissions_n3
 * @since_tizen		5.0
 * @description		Request user permissions
 *					- request permissions when the callback parameter is NULL
 */
int utc_ppm_request_permissions_n3(void)
{
	int ret;

	ret = ppm_request_permissions(&location_privilege, 1, NULL, NULL);

	assert_eq(ret, PRIVACY_PRIVILEGE_MANAGER_ERROR_INVALID_PARAMETER);

	return 0;
}
