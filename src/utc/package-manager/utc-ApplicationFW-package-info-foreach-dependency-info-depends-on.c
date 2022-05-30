//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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

#include <package_manager.h>

#include "assert_common.h"

//& set: PackageInfoForeachDependencyInfo

static bool dependency_cb(const char* from, const char *to, const char *type, const char *required_version, void *user_data)
{
	normal_exit(0);
	return true;
}

/**
 * @testcase		utc_package_manager_package_info_foreach_dependency_info_depends_on_p
 * @since_tizen		5.5
 * @description		Positive test case of package_info_foreach_dependency_info_depends_on()
 */
int utc_package_manager_package_info_foreach_dependency_info_depends_on_p(void)
{
	int ret;
	const char *pkgid = "org.tizen.helloworld2";
	package_info_h package_info = NULL;

	ret = package_manager_get_package_info(pkgid, &package_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	ret = package_info_foreach_dependency_info_depends_on(package_info, dependency_cb, NULL);
	package_info_destroy(package_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_info_foreach_dependency_info_depends_on_n
 * @since_tizen		5.5
 * @description		Negative test case of package_info_foreach_dependency_info_depends_on()
 */
int utc_package_manager_package_info_foreach_dependency_info_depends_on_n(void)
{
	int ret;
	package_info_h package_info = NULL;

	ret = package_info_foreach_dependency_info_depends_on(package_info, dependency_cb, NULL);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
