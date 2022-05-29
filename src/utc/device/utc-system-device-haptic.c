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
#include <device/haptic.h>


//& set: DeviceHaptic
#define HAPTIC_FEATURE		"http://tizen.org/feature/feedback.vibration"

static bool is_supported;
static haptic_device_h haptic_h;

/**
 * @function		utc_system_haptic_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_haptic_startup(void)
{
	int cnt, ret;

	ret = system_info_get_platform_bool(HAPTIC_FEATURE, &is_supported);
	if (!is_supported)
		return;

	ret = device_haptic_get_count(&cnt);
	if (ret < 0) {
		printf("Failed to get count\n");
		return;
	}

	if (cnt == 0) {
		printf("Do not support haptic device\n");
		return;
	}

	ret = device_haptic_open(0, &haptic_h);
	if (ret < 0) {
		printf("Failed to open haptic device\n");
		return;
	}
}

/**
 * @function		utc_system_haptic_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_haptic_cleanup(void)
{
	if (!haptic_h)
		return;

	device_haptic_close(haptic_h);
}


/**
 * @testcase		utc_system_device_haptic_get_count_p
 * @since_tizen		2.3
 * @description		Positive test case of haptic_get_count()
 */
int utc_system_device_haptic_get_count_p(void)
{
	int val, ret;

	if (!is_supported)
		return 0;

	ret = device_haptic_get_count(&val);
	assert_eq(ret, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_get_count_n
 * @since_tizen		2.3
 * @description		Negative test case of haptic_get_count()
 */
int utc_system_device_haptic_get_count_n(void)
{
	int ret;

	if (!is_supported)
		return 0;

	ret = device_haptic_get_count(NULL);
	assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_open_p
 * @since_tizen		2.3
 * @description		Positive test case of device_haptic_open()
 */
int utc_system_device_haptic_open_p(void)
{
	haptic_device_h handle;
	int ret;

	if (!is_supported)
		return 0;

	ret = device_haptic_open(0, &handle);
	assert_eq(ret, DEVICE_ERROR_NONE);
	device_haptic_close(handle);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_open_n_1
 * @since_tizen		2.3
 * @description		Negative test case of device_haptic_open()
 */
int utc_system_device_haptic_open_n_1(void)
{
	haptic_device_h handle;
	int ret;

	if (!is_supported)
		return 0;

	ret = device_haptic_open(-1, &handle);
	assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_open_n_2
 * @since_tizen		2.3
 * @description		Negative test case of device_haptic_open()
 */
int utc_system_device_haptic_open_n_2(void)
{
	int ret;

	if (!is_supported)
		return 0;

	ret = device_haptic_open(0, NULL);
	assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_close_p
 * @since_tizen		2.3
 * @description		Positive test case of device_haptic_close()
 */
int utc_system_device_haptic_close_p(void)
{
	haptic_device_h handle;
	haptic_effect_h eh;
	int ret;

	if (!is_supported)
		return 0 ;

	device_haptic_open(0, &handle);
	ret = device_haptic_vibrate(handle, 1000, 100, &eh);
	ret = device_haptic_close(handle);
	assert_eq(ret, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_close_n
 * @since_tizen		2.3
 * @description		Negative test case of device_haptic_close()
 */
int utc_system_device_haptic_close_n(void)
{
	int ret;

	if (!is_supported)
		return 0;

	ret = device_haptic_close(NULL);
	assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_vibrate_p
 * @since_tizen		2.3
 * @description		Positive test case of device_haptic_vibrate()
 */
int utc_system_device_haptic_vibrate_p(void)
{
	haptic_effect_h eh;
	int ret;

	if (!is_supported)
		return 0;

	ret = device_haptic_vibrate(haptic_h, 1000, 100, &eh);
	device_haptic_stop(haptic_h, eh);
	assert_eq(ret, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_vibrate_n_1
 * @since_tizen		2.3
 * @description		Negative test case of device_haptic_vibrate()
 */
int utc_system_device_haptic_vibrate_n_1(void)
{
	int ret;

	if (!is_supported)
		return 0;

	ret = device_haptic_vibrate(NULL, 1000, 100, NULL);
	assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_vibrate_n_2
 * @since_tizen		2.3
 * @description		Negative test case of device_haptic_vibrate()
 */
int utc_system_device_haptic_vibrate_n_2(void)
{
	int ret;

	if (!is_supported)
		return 0;

	ret = device_haptic_vibrate(haptic_h, -1, 100, NULL);
	assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_vibrate_n_3
 * @since_tizen		2.3
 * @description		Negative test case of device_haptic_vibrate()
 */
int utc_system_device_haptic_vibrate_n_3(void)
{
	int ret;

	if (!is_supported)
		return 0;

	ret = device_haptic_vibrate(haptic_h, 1000, -1, NULL);
	assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_stop_p
 * @since_tizen		2.3
 * @description		Positive test case of device_haptic_stop()
 */
int utc_system_device_haptic_stop_p(void)
{
	haptic_effect_h eh;
	int ret;

	if (!is_supported)
		return 0;

	device_haptic_vibrate(haptic_h, 1000, 100, &eh);
	ret = device_haptic_stop(haptic_h, eh);
	assert_eq(ret, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_haptic_stop_n
 * @since_tizen		2.3
 * @description		Negative test case of device_haptic_stop()
 */
int utc_system_device_haptic_stop_n(void)
{
	haptic_effect_h eh = NULL;
	int ret;

	if (!is_supported)
		return 0;

	device_haptic_vibrate(haptic_h, 1000, 100, &eh);
	ret = device_haptic_stop(NULL, eh);
	assert_eq(ret, DEVICE_ERROR_INVALID_PARAMETER);
	device_haptic_stop(haptic_h, eh);

	return 0;
}
