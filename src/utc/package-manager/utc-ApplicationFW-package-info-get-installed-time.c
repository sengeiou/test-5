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

/**
 * @testcase		utc_package_manager_package_info_get_installed_time_p
 * @since_tizen		4.0
 * @description		Positive test case of package_info_get_installed_time()
 */
int utc_package_manager_package_info_get_installed_time_p(void)
{
	int ret;
	const char *pkgid = "org.tizen.helloworld2";
	package_info_h package_info = NULL;
	int installed_time = NULL;

	package_manager_get_package_info(pkgid, &package_info);

	ret = package_info_get_installed_time(package_info, &installed_time);
	package_info_destroy(package_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_info_get_installed_time_n
 * @since_tizen		4.0
 * @description		Negative test case of package_info_get_installed_time()
 */
int utc_package_manager_package_info_get_installed_time_n(void)
{
	int ret;
	package_info_h package_info = NULL;
	int installed_time;

	ret = package_info_get_installed_time(package_info, &installed_time);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
