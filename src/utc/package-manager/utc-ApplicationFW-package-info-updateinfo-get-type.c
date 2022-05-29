//
// Copyright (c) 2017 Samsung Electronics Co., Ltd.
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
#include <package_info.h>
#include <package_manager.h>

//& set: PackageInfoCreate

/**
 * @testcase		utc_ApplicationFW_package_info_updateinfo_get_type_p
 * @since_tizen		4.0
 * @description		Positive test case of package_info_updateinfo_get_type()
 */
int utc_ApplicationFW_package_info_updateinfo_get_type_p(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	package_updateinfo_h package_info = NULL;
	const char *pkgid = "org.tizen.helloworld2";
	package_updateinfo_type_e type;

	ret = package_info_updateinfo_create(pkgid, &package_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	ret = package_info_updateinfo_get_type(package_info, &type);
	package_info_updateinfo_destroy(package_info);
	package_info = NULL;

	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_ApplicationFW_package_info_updateinfo_get_type_n1
 * @since_tizen		4.0
 * @description		Negative test case of package_info_updateinfo_get_type()
 */
int utc_ApplicationFW_package_info_updateinfo_get_type_n1(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	package_updateinfo_h package_info = NULL;
	const char *pkgid = "org.tizen.helloworld2";

	ret = package_info_updateinfo_create(pkgid, &package_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	ret = package_info_updateinfo_get_type(package_info, NULL);
	package_info_updateinfo_destroy(package_info);
	package_info = NULL;
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_ApplicationFW_package_info_updateinfo_get_type_n2
 * @since_tizen		4.0
 * @description		Negative test case of package_info_updateinfo_get_type()
 */
int utc_ApplicationFW_package_info_updateinfo_get_type_n2(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	package_updateinfo_type_e type;

	ret = package_info_updateinfo_get_type(NULL, &type);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
