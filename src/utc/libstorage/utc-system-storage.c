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
#include <storage.h>
#include "assert.h"

#define STORAGE_FEATURE "http://tizen.org/feature/storage.external"

/**
 * @testcase		utc_system_storage_get_internal_memory_size_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_get_internal_memory_size()
 */
int utc_system_storage_get_internal_memory_size_p(void)
{
	struct statvfs s;
	int ret = storage_get_internal_memory_size(&s);
	assert_eq(ret, 0);
	return 0;
}

/**
 * @testcase		utc_system_storage_get_internal_memory_size_n
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_internal_memory_size()
 */
int utc_system_storage_get_internal_memory_size_n(void)
{
	int ret = storage_get_internal_memory_size(NULL);
	assert_lt(ret, 0);
	return 0;
}

//#ifndef TIZENIOT
/**
 * @testcase		utc_system_storage_get_external_memory_size_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_get_external_memory_size()
 */
int utc_system_storage_get_external_memory_size_p(void)
{
	struct statvfs s;
	int ret;
	bool is_supported;

	ret = system_info_get_platform_bool(STORAGE_FEATURE, &is_supported);
	if (ret < 0)
		is_supported = false;

	if (!is_supported)
		return 0;

	ret = storage_get_external_memory_size(&s);
	assert_eq(ret, 0);

	return 0;
}

/**
 * @testcase		utc_system_storage_get_external_memory_size_n
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_external_memory_size()
 */
int utc_system_storage_get_external_memory_size_n(void)
{
	int ret;
	bool is_supported;

	ret = system_info_get_platform_bool(STORAGE_FEATURE, &is_supported);
	if (ret < 0)
		is_supported = false;

	if (!is_supported)
		return 0;

	ret = storage_get_external_memory_size(NULL);
	assert_lt(ret, 0);

	return 0;
}
//#endif //TIZENIOT
