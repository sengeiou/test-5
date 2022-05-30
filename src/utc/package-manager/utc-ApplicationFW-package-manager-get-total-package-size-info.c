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
#include "assert_common.h"
#include <package_manager.h>

//& set: PackageManagerGetTotalPackageSizeInfo

static void size_cb(const package_size_info_h size_info, void *user_data)
{
	normal_exit(0);
}

/**
 * @testcase		utc_ApplicationFW_package_manager_get_total_package_size_info_p
 * @since_tizen		2.3
 * @description		Test retrieve package size info and execute callback with size info retrieved.
 */
int utc_ApplicationFW_package_manager_get_total_package_size_info_p(void)
{
	int ret;

	ret = package_manager_get_total_package_size_info(size_cb, NULL);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_ApplicationFW_package_manager_get_total_package_size_info_n
 * @since_tizen		2.3
 * @description		Test failed to retrieve size info with given package id by passing NULL as callback argument.
 */
int utc_ApplicationFW_package_manager_get_total_package_size_info_n(void)
{
	int ret;

	ret = package_manager_get_total_package_size_info(NULL, NULL);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
