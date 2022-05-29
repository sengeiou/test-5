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

#include <stdlib.h>
#include <string.h>

#include <app_common.h>
#include <package_manager.h>
#include <package_archive_info.h>

#include "assert_common.h"

//& set: PackageArchiveInfoGetDescription

/**
 * @testcase		utc_ApplicationFW_package_archive_info_get_description_p
 * @since_tizen		4.0
 * @description		Positive test case of package_archive_info_get_description()
 */
int utc_ApplicationFW_package_archive_info_get_description_p(void)
{
	int ret;
	const char file_name[] = "org.example.sampletpk.tpk";
	char *res_path;
	char path[128];
	package_archive_info_h archive_info;
	char *description;

	res_path = app_get_shared_resource_path();
	assert_neq_with_exit(res_path, NULL);

	snprintf(path, sizeof(path), "%s/%s", res_path, file_name);
	free(res_path);

	ret = package_archive_info_create(path, &archive_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	ret = package_archive_info_get_description(archive_info, &description);
	package_archive_info_destroy(archive_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);
	assert_eq_with_exit(strcmp("This is test description.", description), 0);

	free(description);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_ApplicationFW_package_archive_info_get_description_n
 * @since_tizen		4.0
 * @description		Negative test case of package_archive_info_get_description()
 */
int utc_ApplicationFW_package_archive_info_get_description_n(void)
{
	int ret;
	const char file_name[] = "org.example.sampletpk.tpk";
	char *res_path;
	char path[128];
	package_archive_info_h archive_info;
	char *description;

	ret = package_archive_info_get_description(NULL, &description);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);

	res_path = app_get_shared_resource_path();
	assert_neq_with_exit(res_path, NULL);

	snprintf(path, sizeof(path), "%s/%s", res_path, file_name);
	free(res_path);

	ret = package_archive_info_create(path, &archive_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_NONE);

	ret = package_archive_info_get_description(archive_info, NULL);
	package_archive_info_destroy(archive_info);
	assert_eq_with_exit(ret, PACKAGE_MANAGER_ERROR_INVALID_PARAMETER);

	normal_exit(0);

	return 0;
}
