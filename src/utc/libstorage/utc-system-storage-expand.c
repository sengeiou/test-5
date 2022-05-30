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
#include "assert.h"
#include <storage.h>

#define STORAGE_FEATURE "http://tizen.org/feature/storage.external"

//& set: StorageExpand

static int internal_storage_id = -1;
static int external_storage_id = -1;
static int extended_id = -1;
static bool is_supported;

static bool get_internal_storage(int storage_id, storage_type_e type,
		storage_state_e state, const char *path, void *user_data)
{
	if (type == STORAGE_TYPE_INTERNAL && internal_storage_id < 0)
		internal_storage_id = storage_id;
#ifndef TV
	else if (type == STORAGE_TYPE_EXTERNAL && external_storage_id < 0)
		external_storage_id = storage_id;
	else if (type == STORAGE_TYPE_EXTENDED_INTERNAL && extended_id < 0)
		extended_id = storage_id;
#endif

	return true;
}

/**
 * @function		utc_storage_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_storage_startup(void)
{
	int ret;

	ret = system_info_get_platform_bool(STORAGE_FEATURE, &is_supported);
	if (ret < 0)
		is_supported = false;

	/* find internal storage */
	storage_foreach_device_supported(get_internal_storage, NULL);
}

static bool get_storage_device(int storage, storage_type_e type, storage_state_e state,
			const char *path, void *user_data)
{
	return true;
}

/**
 * @testcase		utc_storage_foreach_device_supported_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_foreach_device_supported
 */
int utc_storage_foreach_device_supported_p(void)
{
	int err;

	err = storage_foreach_device_supported(get_storage_device, NULL);
	assert_eq(err, STORAGE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_storage_foreach_device_supported_n
 * @since_tizen		2.3
 * @description		Negative test case of storage_foreach_device_supported
 */
int utc_storage_foreach_device_supported_n(void)
{
	int err;

	err = storage_foreach_device_supported(NULL, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_root_directory_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_get_root_directory.
 */
int utc_storage_get_root_directory_p(void)
{
	char *path = NULL;
	int err;

	if (external_storage_id >= 0) {
		err = storage_get_root_directory(external_storage_id, &path);
		if (path) {
			free(path);
			path = NULL;
		}
		assert_eq(err, STORAGE_ERROR_NONE);
	}
	if (extended_id >= 0) {
		err = storage_get_root_directory(extended_id, &path);
		if (path) {
			free(path);
			path = NULL;
		}
		assert_eq(err, STORAGE_ERROR_NONE);
	}
	err = storage_get_root_directory(internal_storage_id, &path);
	if (path) {
		free(path);
		path = NULL;
	}
	assert_eq(err, STORAGE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_storage_get_root_directory_n_1
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_root_directory. Invalid storage_id.
 */
int utc_storage_get_root_directory_n_1(void)
{
	char *path;
	int err;

	err = storage_get_root_directory(-1, &path);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_root_directory_n_2
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_root_directory. Path is null.
 */
int utc_storage_get_root_directory_n_2(void)
{
	int err;

	err = storage_get_root_directory(internal_storage_id, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_directory_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_get_directory.
 */
int utc_storage_get_directory_p(void)
{
	char *path = NULL;
	int i, err;

	for (i = 0; i < STORAGE_DIRECTORY_MAX; ++i) {
		if (i != STORAGE_DIRECTORY_SYSTEM_RINGTONES && external_storage_id >= 0) {
			err = storage_get_directory(external_storage_id, i, &path);
			if (path) {
				free(path);
				path = NULL;
			}
			assert_eq(err, STORAGE_ERROR_NONE);
		}
		err = storage_get_directory(internal_storage_id, i, &path);
		if (path) {
			free(path);
			path = NULL;
		}
		assert_eq(err, STORAGE_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_storage_get_directory_n_1
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_directory. Invalid storage id.
 */
int utc_storage_get_directory_n_1(void)
{
	char *path;
	int err;

	err = storage_get_directory(-1, STORAGE_DIRECTORY_IMAGES, &path);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_directory_n_2
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_directory. Invalid storage directory type.
 */
int utc_storage_get_directory_n_2(void)
{
	char *path;
	int err;

	err = storage_get_directory(internal_storage_id, -1, &path);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_directory_n_3
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_directory. Path is null.
 */
int utc_storage_get_directory_n_3(void)
{
	int err;

	err = storage_get_directory(internal_storage_id, STORAGE_DIRECTORY_IMAGES, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_type_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_get_type.
 */
int utc_storage_get_type_p(void)
{
	storage_type_e type;
	int err;

	if (external_storage_id >= 0) {
		err = storage_get_type(external_storage_id, &type);
		assert_eq(err, STORAGE_ERROR_NONE);
		assert_eq(type, STORAGE_TYPE_EXTERNAL);
	}
	if (extended_id >= 0) {
		err = storage_get_type(extended_id, &type);
		assert_eq(err, STORAGE_ERROR_NONE);
		assert_eq(type, STORAGE_TYPE_EXTENDED_INTERNAL);
	}
	err = storage_get_type(internal_storage_id, &type);
	assert_eq(err, STORAGE_ERROR_NONE);
	assert_eq(type, STORAGE_TYPE_INTERNAL);
	return 0;
}

/**
 * @testcase		utc_storage_get_type_n_1
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_type. Invalid storage id.
 */
int utc_storage_get_type_n_1(void)
{
	storage_type_e type;
	int err;

	err = storage_get_type(-1, &type);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_type_n_2
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_type. Storage type is null.
 */
int utc_storage_get_type_n_2(void)
{
	int err;

	err = storage_get_type(internal_storage_id, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_state_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_get_state.
 */
int utc_storage_get_state_p(void)
{
	storage_state_e state;
	int err;

	if (external_storage_id >= 0) {
		err = storage_get_state(external_storage_id, &state);
		assert_eq(err, STORAGE_ERROR_NONE);
		assert(STORAGE_STATE_UNMOUNTABLE <= state && state <= STORAGE_STATE_MOUNTED_READ_ONLY);
	}
	err = storage_get_state(internal_storage_id, &state);
	assert_eq(err, STORAGE_ERROR_NONE);
	assert_eq(state, STORAGE_STATE_MOUNTED);
	return 0;
}

/**
 * @testcase		utc_storage_get_state_n_1
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_state. Invalid storage id.
 */
int utc_storage_get_state_n_1(void)
{
	storage_state_e state;
	int err;

	err = storage_get_state(-1, &state);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_state_n_2
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_state. Storage state is null.
 */
int utc_storage_get_state_n_2(void)
{
	int err;

	err = storage_get_state(internal_storage_id, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_total_space_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_get_total_space.
 */
int utc_storage_get_total_space_p(void)
{
	unsigned long long size;
	int err;

	if (external_storage_id >= 0) {
		err = storage_get_total_space(external_storage_id, &size);
		assert_eq(err, STORAGE_ERROR_NONE);
	}
	err = storage_get_total_space(internal_storage_id, &size);
	assert_eq(err, STORAGE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_storage_get_total_space_n_1
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_total_space. Invalid storage_id.
 */
int utc_storage_get_total_space_n_1(void)
{
	unsigned long long size;
	int err;

	err = storage_get_total_space(-1, &size);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_total_space_n_2
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_total_space. Storage size is null.
 */
int utc_storage_get_total_space_n_2(void)
{
	int err;
	err = storage_get_total_space(internal_storage_id, NULL);

	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_available_space_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_get_available_space.
 */
int utc_storage_get_available_space_p(void)
{
	unsigned long long size;
	int err;

	if (external_storage_id >= 0) {
		err = storage_get_available_space(external_storage_id, &size);
		assert_eq(err, STORAGE_ERROR_NONE);
	}
	err = storage_get_available_space(internal_storage_id, &size);
	assert_eq(err, STORAGE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_storage_get_available_space_n_1
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_available_space. Invalid storage_id.
 */
int utc_storage_get_available_space_n_1(void)
{
	unsigned long long size;
	int err;

	err = storage_get_available_space(-1, &size);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_available_space_n_2
 * @since_tizen		2.3
 * @description		Negative test case of storage_get_available_space. Storage size parameter is null.
 */
int utc_storage_get_available_space_n_2(void)
{
	int err;

	err = storage_get_available_space(internal_storage_id, NULL);
	assert_eq(err,STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

static void dts_storage_state_changed_cb(int storage, storage_state_e state, void *user_data)
{
}

/**
 * @testcase		utc_storage_set_state_changed_cb_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_set_state_changed_cb.
 */
int utc_storage_set_state_changed_cb_p(void)
{
	int err;

	if (external_storage_id >= 0) {
		err = storage_set_state_changed_cb(external_storage_id, dts_storage_state_changed_cb, NULL);
		assert_eq(err, STORAGE_ERROR_NONE);
	}
	err = storage_set_state_changed_cb(internal_storage_id, dts_storage_state_changed_cb, NULL);
	assert_eq(err, STORAGE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_storage_set_state_changed_cb_n_1
 * @since_tizen		2.3
 * @description		Negative test case of storage_set_state_changed_cb. Invalid storage_id.
 */
int utc_storage_set_state_changed_cb_n_1(void)
{
	int err;

	err = storage_set_state_changed_cb(-1, dts_storage_state_changed_cb, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_set_state_changed_cb_n_2
 * @since_tizen		2.3
 * @description		Negative test case of storage_set_state_changed_cb. Callback function is null.
 */
int utc_storage_set_state_changed_cb_n_2(void)
{
	int err;

	err = storage_set_state_changed_cb(internal_storage_id, NULL, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_unset_state_changed_cb_p
 * @since_tizen		2.3
 * @description		Positive test case of storage_unset_state_changed_cb.
 */
int utc_storage_unset_state_changed_cb_p(void)
{
	int err;

	if (external_storage_id >= 0) {
		storage_set_state_changed_cb(external_storage_id, dts_storage_state_changed_cb, NULL);
		err = storage_unset_state_changed_cb(external_storage_id, dts_storage_state_changed_cb);
		assert_eq(err, STORAGE_ERROR_NONE);
	}
	storage_set_state_changed_cb(internal_storage_id, dts_storage_state_changed_cb, NULL);
	err = storage_unset_state_changed_cb(internal_storage_id, dts_storage_state_changed_cb);
	assert_eq(err, STORAGE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_storage_unset_state_changed_cb_n_1
 * @since_tizen		2.3
 * @description		Negative test case of storage_unset_state_changed_cb. Invalid storage_id.
 */
int utc_storage_unset_state_changed_cb_n_1(void)
{
	int err;

	err = storage_unset_state_changed_cb(-1, dts_storage_state_changed_cb);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_unset_state_changed_cb_n_2
 * @since_tizen		2.3
 * @description		Negative test case of storage_unset_state_changed_cb. Callback function is null.
 */
int utc_storage_unset_state_changed_cb_n_2(void)
{
	int err;

	err = storage_unset_state_changed_cb(internal_storage_id, NULL);
    assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

static void test_storage_changed_cb(int storage_id, storage_dev_e dev, storage_state_e state, const char *fstype, const char *fsuuid, const char *mountpath, bool primary, int flags, void *user_data)
{
}

/**
 * @testcase		utc_storage_set_changed_cb_p
 * @since_tizen		3.0
 * @description		Positive test case of storage_set_changed_cb.
 */
int utc_storage_set_changed_cb_p(void)
{
	int err;

	if (!is_supported)
		return 0;

	err= storage_set_changed_cb(STORAGE_TYPE_EXTERNAL, test_storage_changed_cb, NULL);
	assert_eq(err, STORAGE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_storage_set_changed_cb_n_1
 * @since_tizen		3.0
 * @description		Negative test case of storage_set_changed_cb.
 */
int utc_storage_set_changed_cb_n_1(void)
{
	int err;

	err= storage_set_changed_cb(STORAGE_TYPE_INTERNAL, test_storage_changed_cb, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_set_changed_cb_n_2
 * @since_tizen		3.0
 * @description		Negative test case of storage_set_changed_cb.
 */
int utc_storage_set_changed_cb_n_2(void)
{
	int err;

	if (!is_supported)
		return 0;

	err= storage_set_changed_cb(STORAGE_TYPE_EXTERNAL, NULL, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_set_changed_cb_n_3
 * @since_tizen		3.0
 * @description		Negative test case of storage_set_changed_cb.
 */
int utc_storage_set_changed_cb_n_3(void)
{
	int err;

	err= storage_set_changed_cb(-1, NULL, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_unset_changed_cb_p
 * @since_tizen		3.0
 * @description		Negative test case of storage_unset_changed_cb.
 */
int utc_storage_unset_changed_cb_p(void)
{
	int err;

	if (!is_supported)
		return 0;

	err= storage_set_changed_cb(STORAGE_TYPE_EXTERNAL, test_storage_changed_cb, NULL);
	err= storage_unset_changed_cb(STORAGE_TYPE_EXTERNAL, test_storage_changed_cb);
	assert_eq(err, STORAGE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_storage_unset_changed_cb_n_1
 * @since_tizen		3.0
 * @description		Negative test case of storage_unset_changed_cb.
 */
int utc_storage_unset_changed_cb_n_1(void)
{
	int err;

	err= storage_unset_changed_cb(STORAGE_TYPE_INTERNAL, test_storage_changed_cb);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_unset_changed_cb_n_2
 * @since_tizen		3.0
 * @description		Negative test case of storage_unset_changed_cb.
 */
int utc_storage_unset_changed_cb_n_2(void)
{
	int err;

	if (!is_supported)
		return 0;

	err= storage_unset_changed_cb(STORAGE_TYPE_EXTERNAL, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_unset_changed_cb_n_3
 * @since_tizen		3.0
 * @description		Negative test case of storage_unset_changed_cb.
 */
int utc_storage_unset_changed_cb_n_3(void)
{
	int err;

	err= storage_unset_changed_cb(-1, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_type_dev_p
 * @since_tizen		5.0
 * @description		Positive test case of storage_get_type_dev.
 */
int utc_storage_get_type_dev_p(void)
{
	int err;
	storage_type_e type;
	storage_dev_e dev;

	if (external_storage_id < 0)
		return 0;

	err = storage_get_type_dev(external_storage_id, &type, &dev);
	assert_eq(err, STORAGE_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_storage_get_type_dev_n_1
 * @since_tizen		5.0
 * @description		Negative test case of storage_get_type_dev.
 */
int utc_storage_get_type_dev_n_1(void)
{
	int err;
	storage_type_e type;

	if (external_storage_id < 0)
		return 0;

	err = storage_get_type_dev(external_storage_id, &type, NULL);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_type_dev_n_2
 * @since_tizen		5.0
 * @description		Negative test case of storage_get_type_dev.
 */
int utc_storage_get_type_dev_n_2(void)
{
	int err;
	storage_type_e type;
	storage_dev_e dev;

	err = storage_get_type_dev(internal_storage_id, &type, &dev);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_storage_get_type_dev_n_3
 * @since_tizen		5.0
 * @description		Negative test case of storage_get_type_dev.
 */
int utc_storage_get_type_dev_n_3(void)
{
	int err;
	storage_type_e type;
	storage_dev_e dev;

	err = storage_get_type_dev(-1, &type, &dev);
	assert_eq(err, STORAGE_ERROR_INVALID_PARAMETER);
	return 0;
}
