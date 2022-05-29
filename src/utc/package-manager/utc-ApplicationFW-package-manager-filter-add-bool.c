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
 * @function		utc_package_manager_filter_add_bool_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_package_manager_filter_add_bool_cleanup(void)
{
	package_manager_filter_destroy(g_filter);
}

/**
 * @testcase		utc_package_manager_package_manager_filter_add_bool_p
 * @since_tizen		2.3
 * @description		Test add boolean filter into package info filter.
 */
int utc_package_manager_package_manager_filter_add_bool_p(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	package_manager_filter_h filter = NULL;

	ret = package_manager_filter_create(&filter);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_add_bool(filter, PACKAGE_MANAGER_PKGINFO_PROP_PRELOAD, true);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_destroy(filter);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_manager_filter_add_bool_n1
 * @since_tizen		2.3
 * @description		Test failed to add boolean filter into package info filter which is uninitialized.
 */
int utc_package_manager_package_manager_filter_add_bool_n1(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	package_manager_filter_h filter = NULL;

	ret = package_manager_filter_add_bool(filter, PACKAGE_MANAGER_PKGINFO_PROP_PRELOAD, true);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_manager_filter_add_bool_n2
 * @since_tizen		2.3
 * @description		Test failed to add boolean filter into package info filter by passing NULL to property.
 */
int utc_package_manager_package_manager_filter_add_bool_n2(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;

	ret = package_manager_filter_create(&g_filter);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_add_bool(g_filter, NULL, true);
	assert_eq_with_exit(ret,PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
