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

//& set: PackageManagerGetPackageInfo

/**
 * @testcase		utc_ApplicationFW_package_manager_get_package_info_p
 * @since_tizen		2.3
 * @description		Test gets package info with given package id.
 */
int utc_ApplicationFW_package_manager_get_package_info_p(void)
{
	int ret;
	package_info_h package_info = NULL;
	const char *pkgid = "org.tizen.helloworld2";

	ret = package_manager_get_package_info(pkgid, &package_info);
	package_info_destroy(package_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_ApplicationFW_package_manager_get_package_info_n1
 * @since_tizen		2.3
 * @description		Test failed to get package info by passing NULL as package id.
 */
int utc_ApplicationFW_package_manager_get_package_info_n1(void)
{
	int ret;
	package_info_h package_info = NULL;
	const char *pkgid = NULL;

	ret = package_manager_get_package_info(pkgid, &package_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_ApplicationFW_package_manager_get_package_info_n2
 * @since_tizen		2.3
 * @description		Test failed to get package info by passing package id which doesn't exist.
 */
int utc_ApplicationFW_package_manager_get_package_info_n2(void)
{
	int ret;
	package_info_h package_info = NULL;
	const char *pkgid = "org.tizen.fake_app_id";

	ret = package_manager_get_package_info(pkgid, &package_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NO_SUCH_PACKAGE);
	normal_exit(0);

	return 0;
}
