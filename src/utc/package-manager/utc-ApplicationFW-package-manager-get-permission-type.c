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

//& set: PackageManagerGetPermissionType

/**
 * @testcase		utc_ApplicationFW_package_manager_get_permission_type_p
 * @since_tizen		2.3
 * @description		Test retrieve permission type of given package id.
 */
int utc_ApplicationFW_package_manager_get_permission_type_p(void)
{
	int ret;
	package_manager_permission_type_e permission = -1;
	const char *pkgid = "org.tizen.helloworld2";

	ret = package_manager_get_permission_type(pkgid, &permission);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_ApplicationFW_package_manager_get_permission_type_n
 * @since_tizen		2.3
 * @description		Test failed to get permission type by passing NULL as parameter.
 */
int utc_ApplicationFW_package_manager_get_permission_type_n(void)
{
	int ret;
	package_manager_permission_type_e permission = -1;
	const char *pkgid = NULL;

	ret = package_manager_get_permission_type(pkgid, &permission);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NO_SUCH_PACKAGE);
	normal_exit(0);

	return 0;
}
