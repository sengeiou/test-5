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

/**
 * @testcase		utc_package_manager_package_manager_filter_add_string_p
 * @since_tizen		6.5
 * @description		Test add string filter into package info filter.
 */
int utc_package_manager_package_manager_filter_add_string_p(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	package_manager_filter_h filter = NULL;

	ret = package_manager_filter_create(&filter);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_add_string(filter, PACKAGE_MANAGER_PKGINFO_PROP_RES_TYPE, "ai_model");
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_destroy(filter);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_manager_filter_add_string_n1
 * @since_tizen		6.5
 * @description		Test failed to add string filter into package info filter which is uninitialized.
 */
int utc_package_manager_package_manager_filter_add_string_n1(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	package_manager_filter_h filter = NULL;

	ret = package_manager_filter_add_string(filter, PACKAGE_MANAGER_PKGINFO_PROP_RES_TYPE, "ai_model");
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_manager_filter_add_string_n2
 * @since_tizen		6.5
 * @description		Test failed to add string filter into package info filter by passing NULL to property.
 */
int utc_package_manager_package_manager_filter_add_string_n2(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	int r;
	package_manager_filter_h filter = NULL;

	ret = package_manager_filter_create(&filter);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_add_string(filter, NULL, true);
	r = package_manager_filter_destroy(filter);
	assert_eq_with_exit(r, PACKAGE_MANAGER_ERROR_NONE);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_package_manager_package_manager_filter_add_string_n3
 * @since_tizen		6.5
 * @description		Test failed to add string filter into package info filter by passing NULL to value.
 */
int utc_package_manager_package_manager_filter_add_string_n3(void)
{
	int ret = PACKAGE_MANAGER_ERROR_NONE;
	int r;
	package_manager_filter_h filter = NULL;

	ret = package_manager_filter_create(&filter);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	ret = package_manager_filter_add_string(filter, PACKAGE_MANAGER_PKGINFO_PROP_RES_TYPE, NULL);
	r = package_manager_filter_destroy(filter);
	assert_eq_with_exit(r, PACKAGE_MANAGER_ERROR_NONE);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
