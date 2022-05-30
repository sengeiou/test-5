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
#include <device/callback.h>
#include <stdbool.h>

//& set: DeviceCallback

static bool is_supported(int i)
{
	bool is_supported;
	int ret;

	switch (i) {
	case DEVICE_CALLBACK_DISPLAY_STATE:
		ret = system_info_get_platform_bool("http://tizen.org/feature/display", &is_supported);
		if (ret < 0 || !is_supported)
			return false;

		ret = system_info_get_platform_bool("http://tizen.org/feature/display.state", &is_supported);
		if (ret < 0 || !is_supported)
			return false;

		return true;
	case DEVICE_CALLBACK_BATTERY_CAPACITY:
	case DEVICE_CALLBACK_BATTERY_LEVEL:
	case DEVICE_CALLBACK_BATTERY_CHARGING:
		ret = system_info_get_platform_bool("http://tizen.org/feature/battery", &is_supported);
		if (ret < 0)
			return false;
		else
			return is_supported;
	case DEVICE_CALLBACK_FLASH_BRIGHTNESS:
		ret = system_info_get_platform_bool("http://tizen.org/feature/camera.back.flash", &is_supported);
		if (ret < 0)
			return false;
		else
			return is_supported;
	default:
		return false;
	}
}

static void changed_cb(device_callback_e type, void *value, void *user_data)
{

}

/**
 * @testcase		utc_system_device_add_callback_p
 * @since_tizen		2.3
 * @description		Positive test case of device_add_callback.
 */
int utc_system_device_add_callback_p(void)
{
	int i, error;

	for (i = 0; i < DEVICE_CALLBACK_MAX; ++i) {
		if (!is_supported(i))
			continue;
		error = device_add_callback(i, changed_cb, NULL);
		device_remove_callback(i, changed_cb);
		assert_eq(error, DEVICE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_add_callback_n_1
 * @since_tizen		2.3
 * @description		Negative test case of device_add_callback. Invalid callback type.
 */
int utc_system_device_add_callback_n_1(void)
{
	int error;

	error = device_add_callback(-1, changed_cb, NULL);
	assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_add_callback_n_2
 * @since_tizen		2.3
 * @description		Negative test case of device_add_callback. Callback function is null.
 */
int utc_system_device_add_callback_n_2(void)
{
	int i, error;

	for (i = 0; i < DEVICE_CALLBACK_MAX; ++i) {
		if (!is_supported(i))
			continue;
		error = device_add_callback(i, NULL, NULL);
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_remove_callback_p
 * @since_tizen		2.3
 * @description		Positive test case of device_remove_callback.
 */
int utc_system_device_remove_callback_p(void)
{
	int i, error;

	for (i = 0; i < DEVICE_CALLBACK_MAX; ++i) {
		if (!is_supported(i))
			continue;
		device_add_callback(i, changed_cb, NULL);
		error = device_remove_callback(i, changed_cb);
		assert_eq(error, DEVICE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_remove_callback_n_1
 * @since_tizen		2.3
 * @description		Negative test case of device_remove_callback. Invalid callback type.
 */
int utc_system_device_remove_callback_n_1(void)
{
	int i, error;

	for (i = 0; i < DEVICE_CALLBACK_MAX; ++i) {
		if (!is_supported(i))
			continue;
		device_add_callback(i, changed_cb, NULL);
		error = device_remove_callback(-1, changed_cb);
		device_remove_callback(i, changed_cb);
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_remove_callback_n_2
 * @since_tizen		2.3
 * @description		Negative test case of device_remove_callback. Callback function is null.
 */
int utc_system_device_remove_callback_n_2(void)
{
	int i, error;

	for (i = 0; i < DEVICE_CALLBACK_MAX; ++i) {
		if (!is_supported(i))
			continue;
		device_add_callback(i, changed_cb, NULL);
		error = device_remove_callback(i, NULL);
		device_remove_callback(i, changed_cb);
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
