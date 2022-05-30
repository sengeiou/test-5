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
#include <device/power.h>

//& set: DevicePower

#define DISPLAY_FEATURE        "http://tizen.org/feature/display"
#define DISPLAY_STATE_FEATURE  "http://tizen.org/feature/display.state"
#define ARRAY_SIZE(name) (sizeof(name)/sizeof(name[0]))

power_lock_e locks[] = {
	POWER_LOCK_CPU,
};

static bool bIsDisplayFeatureSupported;
static bool bIsDisplayStateFeatureSupported;

/**
 * @function		utc_system_device_power_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_device_power_startup(void)
{
	int ret;

	ret = system_info_get_platform_bool(DISPLAY_FEATURE, &bIsDisplayFeatureSupported);
	ret = system_info_get_platform_bool(DISPLAY_STATE_FEATURE, &bIsDisplayStateFeatureSupported);
}

/**
 * @function		utc_system_device_power_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_device_power_cleanup(void)
{

}

/**
 * @testcase		utc_system_device_power_request_lock_p_1
 * @since_tizen		2.3
 * @description		Positive test case of device_power_request_lock.
 */
int utc_system_device_power_request_lock_p_1(void)
{
	int error, i;

	for (i = 0; i < ARRAY_SIZE(locks); i++) {
		error = device_power_request_lock(locks[i], 0);
		if ((bIsDisplayFeatureSupported == false) ||
			(bIsDisplayStateFeatureSupported == false))	{
			if ((locks[i] == POWER_LOCK_DISPLAY) ||
				(locks[i] == POWER_LOCK_DISPLAY_DIM)) {
				assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
				return 0;
			} else if (locks[i] == POWER_LOCK_CPU) {
				assert_eq(error, DEVICE_ERROR_NONE);
				return 0;
			}
		}
		assert_eq(error, DEVICE_ERROR_NONE);
		device_power_release_lock(locks[i]);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_power_request_lock_p_2
 * @since_tizen		2.3
 * @description		Positive test case of device_power_request_lock.
 */
int utc_system_device_power_request_lock_p_2(void)
{
	int error, i;

	for (i = 0; i < ARRAY_SIZE(locks); i++) {
		error = device_power_request_lock(locks[i], 10);
		if ((bIsDisplayFeatureSupported == false) ||
			(bIsDisplayStateFeatureSupported == false))	{
			if ((locks[i] == POWER_LOCK_DISPLAY) ||
				(locks[i] == POWER_LOCK_DISPLAY_DIM)) {
				assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
				return 0;
			} else if (locks[i] == POWER_LOCK_CPU) {
				assert_eq(error, DEVICE_ERROR_NONE);
				return 0;
			}
		}
		assert_eq(error, DEVICE_ERROR_NONE);
		device_power_release_lock(locks[i]);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_power_request_lock_n_1
 * @since_tizen		2.3
 * @description		Negative test case of device_power_request_lock. Invalid power lock.
 */
int utc_system_device_power_request_lock_n_1(void)
{
	int error;

	error = device_power_request_lock(-1, 0);
	assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_system_device_power_request_lock_n_2
 * @since_tizen		2.3
 * @description		Negative test case of device_power_request_lock. Invalid timeout
 */
int utc_system_device_power_request_lock_n_2(void)
{
	int error, i;

	for (i = 0; i < ARRAY_SIZE(locks); i++) {
		error = device_power_request_lock(locks[i], -1);
		if ((bIsDisplayFeatureSupported == false) ||
			(bIsDisplayStateFeatureSupported == false)) {
			if ((locks[i] == POWER_LOCK_DISPLAY) ||
				(locks[i] == POWER_LOCK_DISPLAY_DIM)) {
				assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
				return 0;
			} else if (locks[i] == POWER_LOCK_CPU) {
				assert_eq(error, DEVICE_ERROR_NONE);
				return 0;
			}
		}
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_power_release_lock_p
 * @since_tizen		2.3
 * @description		Positive test case of device_power_release_lock.
 */
int utc_system_device_power_release_lock_p(void)
{
	int error, i;

	for (i = 0; i < ARRAY_SIZE(locks); i++) {
		device_power_request_lock(locks[i], 0);
		error = device_power_release_lock(locks[i]);
		if ((bIsDisplayFeatureSupported == false) ||
			(bIsDisplayStateFeatureSupported == false)) {
			if ((locks[i] == POWER_LOCK_DISPLAY) ||
				(locks[i] == POWER_LOCK_DISPLAY_DIM)) {
				assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
				return 0;
			} else if (locks[i] == POWER_LOCK_CPU) {
				assert_eq(error, DEVICE_ERROR_NONE);
				return 0;
			}
		}
		assert_eq(error, DEVICE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_power_release_lock_n
 * @since_tizen		2.3
 * @description		Negative test case of device_power_release_lock.
 */
int utc_system_device_power_release_lock_n(void)
{
	int error, i;

	for (i = 0; i < ARRAY_SIZE(locks); i++) {
		device_power_request_lock(locks[i], 0);
		error = device_power_release_lock(-1);

		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
		device_power_release_lock(locks[i]);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_power_wakeup_p
 * @since_tizen		2.3
 * @description		Positive test case of device_power_wakeup.
 */
int utc_system_device_power_wakeup_p(void)
{
	int error, ret;
	bool is_supported = false;

	ret = system_info_get_platform_bool(DISPLAY_STATE_FEATURE, &is_supported);
	error = device_power_wakeup(false);
	if (is_supported == false)
	{
		assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(error, DEVICE_ERROR_NONE);

	return 0;
}
