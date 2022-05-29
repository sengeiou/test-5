//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#include "assert_common.h"
#include <package_manager.h>

//& set: PackageCertInfo

/**
 * @testcase		utc_ApplicationFW_package_manager_compare_package_cert_info_p
 * @since_tizen		2.3
 * @description		Tests comparing certificate informations between
 * 					two package and confirm return value is indicating "matched".
 */
int utc_ApplicationFW_package_manager_compare_package_cert_info_p(void)
{
	int ret;
	const char *lhs_app_id = "org.tizen.helloworld2";
	const char *rhs_app_id = "org.tizen.helloworld3";
	package_manager_compare_result_type_e compare_result = -1;

	ret = package_manager_compare_package_cert_info(lhs_app_id, rhs_app_id, &compare_result);
	assert_eq_with_exit(compare_result, PACKAGE_MANAGER_COMPARE_MATCH);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_ApplicationFW_package_manager_compare_package_cert_info_n
 * @since_tizen		2.3
 * @description		Test failed to compare cert info by passing NULL
 * 					as second package id argument
 */
int utc_ApplicationFW_package_manager_compare_package_cert_info_n(void)
{
	int ret;
	const char *lhs_app_id = "org.tizen.helloworld2";
	const char *rhs_app_id = NULL;
	package_manager_compare_result_type_e compare_result = -1;

	ret = package_manager_compare_package_cert_info(lhs_app_id, rhs_app_id, &compare_result);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
