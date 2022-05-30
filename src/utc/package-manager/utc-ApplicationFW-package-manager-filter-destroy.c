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
 * @testcase		utc_package_manager_package_manager_filter_destroy_p
 * @since_tizen		2.3
 * @description		Test destroy package manager filter.
 */
int utc_package_manager_package_manager_filter_destroy_p(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	package_manager_filter_h filter = NULL;

	ret = package_manager_filter_create(&filter);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_destroy(filter);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_manager_filter_destroy_n
 * @since_tizen		2.3
 * @description		Test failed to destroy package manager filter by passing NULL as argument.
 */
int utc_package_manager_package_manager_filter_destroy_n(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;

	ret = package_manager_filter_destroy(NULL);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
