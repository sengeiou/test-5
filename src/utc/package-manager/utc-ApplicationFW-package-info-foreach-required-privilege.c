//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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

//& set: PackageInfoForeachRequiredPrivilege

static bool privilege_cb(const char *privilege_name, void *user_data)
{
	normal_exit(0);
	return true;
}

static bool allowed_package_cb(const char *allowed_package, allowed_package_required_privilege_h privilege_handle, void *user_data)
{
	package_info_foreach_required_privilege(privilege_handle, privilege_cb, NULL);
	normal_exit(0);
	return true;
}

/**
 * @testcase		utc_package_manager_package_info_foreach_required_privilege_p
 * @since_tizen		6.5
 * @description		Positive test case of package_info_foreach_required_privilege()
 */
int utc_package_manager_package_info_foreach_required_privilege_p(void)
{
	int ret;
	const char *pkgid = "org.tizen.hellorpk";
	package_info_h package_info = NULL;

	package_manager_get_package_info(pkgid, &package_info);

	ret = package_info_foreach_res_allowed_package(package_info, allowed_package_cb, NULL);
	package_info_destroy(package_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_info_foreach_required_privilege_n
 * @since_tizen		6.5
 * @description		Negative test case of package_info_foreach_required_privilege()
 */
int utc_package_manager_package_info_foreach_required_privilege_n(void)
{
	int ret;
	package_info_h package_info = NULL;

	ret = package_info_foreach_required_privilege(package_info, privilege_cb, NULL);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
