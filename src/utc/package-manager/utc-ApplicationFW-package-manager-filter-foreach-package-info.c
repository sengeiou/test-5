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

static package_manager_filter_h g_filter = NULL;

/**
 * @function		utc_package_manager_filter_foreach_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_package_manager_filter_foreach_cleanup(void)
{
	package_manager_filter_destroy(g_filter);
}

static bool filter_cb(package_info_h package_info, void *user_data)
{
	normal_exit(0);
	return true;
}

/**
 * @testcase		utc_package_manager_package_manager_filter_foreach_package_info_p
 * @since_tizen		2.3
 * @description		Test add property into filter and invoke callback function with each package info retrieved.
 */
int utc_package_manager_package_manager_filter_foreach_package_info_p(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	package_manager_filter_h filter = NULL;

	ret = package_manager_filter_create(&filter);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_add_bool(filter, PACKAGE_MANAGER_PKGINFO_PROP_PRELOAD, false);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_foreach_package_info(filter, filter_cb, NULL);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_manager_filter_foreach_package_info_n
 * @since_tizen		2.3
 * @description		Test failed to get package info because there are no filter added and no callback function has passed.
 */
int utc_package_manager_package_manager_filter_foreach_package_info_n(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;

	ret = package_manager_filter_create(&g_filter);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_foreach_package_info(g_filter, NULL, NULL);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
