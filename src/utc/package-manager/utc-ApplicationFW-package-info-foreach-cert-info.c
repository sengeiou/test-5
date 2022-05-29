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

//& set: PackageInfoForeachCertInfo

static bool info_cb(package_info_h handle, package_cert_type_e cert_type, const char *cert_value, void *user_data)
{
	normal_exit(0);
	return false;
}

/**
 * @testcase		utc_package_manager_package_info_foreach_cert_info_p
 * @since_tizen		2.3
 * @description		Positive test case of package_info_foreach_cert_info()
 */
int utc_package_manager_package_info_foreach_cert_info_p(void)
{
	int ret;
	const char *pkgid = "org.tizen.helloworld2";
	package_info_h package_info = NULL;

	package_manager_get_package_info(pkgid, &package_info);

	ret = package_info_foreach_cert_info(package_info, info_cb, NULL);
	package_info_destroy(package_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_info_foreach_cert_info_n
 * @since_tizen		2.3
 * @description		Negative test case of package_info_foreach_cert_info()
 */
int utc_package_manager_package_info_foreach_cert_info_n(void)
{
	int ret;
	package_info_h package_info = NULL;

	ret = package_info_foreach_cert_info(package_info, info_cb, NULL);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
