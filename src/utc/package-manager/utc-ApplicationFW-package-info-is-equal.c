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

//& set: PackageInfoIsEqual

/**
 * @testcase		utc_package_manager_package_info_is_equal_p
 * @since_tizen		2.3
 * @description		Positive test case of package_info_is_equal()
 */
int utc_package_manager_package_info_is_equal_p(void)
{
	int ret;
	const char *lpkgid = "org.tizen.helloworld2";
	const char *rpkgid = "org.tizen.helloworld2";
	bool info;
	package_info_h lpackage_info = NULL;
	package_info_h rpackage_info = NULL;

	package_manager_get_package_info(lpkgid, &lpackage_info);
	package_manager_get_package_info(rpkgid, &rpackage_info);

	ret = package_info_is_equal(lpackage_info, rpackage_info, &info);
	package_info_destroy(lpackage_info);
	package_info_destroy(rpackage_info);
	assert_eq_with_exit(info, true);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_info_is_equal_n
 * @since_tizen		2.3
 * @description		Negative test case of package_info_is_equal()
 */
int utc_package_manager_package_info_is_equal_n(void)
{
	int ret;
	const char *lpkgid = "org.tizen.helloworld2";
	const char *rpkgid = NULL;
	bool info;
	package_info_h lpackage_info = NULL;
	package_info_h rpackage_info = NULL;

	package_manager_get_package_info(lpkgid, &lpackage_info);
	package_manager_get_package_info(rpkgid, &rpackage_info);

	ret = package_info_is_equal(lpackage_info, rpackage_info, &info);
	package_info_destroy(lpackage_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
