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

//& set: PackageSizeInfoGetExternalDataSize

void get_ext_data_size_cb_p(const char *package_id, const package_size_info_h size_info, void *user_data)
{
	long long ext_data_size = 0;
	int ret;

	ret = package_size_info_get_external_data_size(size_info, &ext_data_size);
	normal_exit(ret);
}

void get_ext_data_size_cb_n(const char *package_id, const package_size_info_h size_info, void *user_data)
{
	long long ext_data_size = 0;
	int ret;

	ret = package_size_info_get_external_data_size(NULL, &ext_data_size);
	normal_exit((ret == PACKAGE_MANAGER_ERROR_INVALID_PARAMETER) ? 0 : 1);
}

/**
 * @testcase		utc_ApplicationFW_package_size_info_get_external_data_size_p
 * @since_tizen		2.3
 * @description		Test retrieve package info and invoke callback function
 *					to get external data size.
 */
int utc_ApplicationFW_package_size_info_get_external_data_size_p(void)
{
	int ret;
	const char *pkgid = "org.tizen.helloworld2";

	ret = package_manager_get_package_size_info(pkgid, get_ext_data_size_cb_p, NULL);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_ApplicationFW_package_size_info_get_external_data_size_n
 * @since_tizen		2.3
 * @description		Test failed to get external data size in callback function
 *					because function passing NULL as size info handle.
 */
int utc_ApplicationFW_package_size_info_get_external_data_size_n(void)
{
	int ret;
	const char *pkgid = "org.tizen.helloworld2";

	ret = package_manager_get_package_size_info(pkgid, get_ext_data_size_cb_n, NULL);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	return 0;
}
