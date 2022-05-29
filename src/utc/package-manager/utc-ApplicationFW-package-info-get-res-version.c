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

//& set: PackageInfoGetResVersion

/**
 * @testcase		utc_package_manager_package_info_get_res_version_p
 * @since_tizen		6.5
 * @description		Positive test case of package_info_get_res_version()
 */
int utc_package_manager_package_info_get_res_version_p(void)
{
	int ret;
	const char *pkgid = "org.tizen.hellorpk";
	package_info_h package_info = NULL;
	char *info = NULL;

	package_manager_get_package_info(pkgid, &package_info);

	ret = package_info_get_res_version(package_info, &info);
	package_info_destroy(package_info);
	free(info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_info_get_res_version_n
 * @since_tizen		6.5
 * @description		Negative test case of package_info_get_res_version()
 */
int utc_package_manager_package_info_get_res_version_n(void)
{
	int ret;
	package_info_h package_info = NULL;
	char *info = NULL;

	ret = package_info_get_res_version(package_info, &info);
	free(info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
