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
#include <device/display.h>

//& set: DeviceDisplay
static bool g_DisplayFeature = false;
static bool g_DisplayStateFeature = false;

#define DISPLAY_STATE_FEATURE        "http://tizen.org/feature/display.state"
#define DISPLAY_FEATURE        "http://tizen.org/feature/display"
#define ARRAY_SIZE(name) (sizeof(name)/sizeof(name[0]))

#if (defined(MOBILE) || defined(TIZENIOT)) //Starts MOBILE or TIZENIOT
	display_state_e display_states[] = { DISPLAY_STATE_NORMAL,DISPLAY_STATE_SCREEN_DIM,DISPLAY_STATE_SCREEN_OFF};
#endif   // End MOBILE or TIZENIOT
#if defined(TV) || defined(WEARABLE)
	display_state_e display_states[] = { DISPLAY_STATE_NORMAL,DISPLAY_STATE_SCREEN_OFF};
#endif

static int cnt;

/* Do not regard DEVICE_ERROR_NOT_SUPPORTED as an error for brightness operation.
 *
 * It is likely to return DEVICE_ERROR_NOT_SUPPORTED even though the display feature is true.
 * This is mainly in case of headed tizeniot profile, which supports plugin-display.
 * If a display is attached, it works properly, returning DEVICE_ERROR_NONE. On the other hand,
 * if a display is detached, it returns DEVICE_ERROR_NOT_SUPPORTED and it won't work. This is
 * intended behaviour, not an error case. */
static int assert_except_not_supported(int error, int val)
{
	if (error == DEVICE_ERROR_NOT_SUPPORTED)
		return 0;

	assert_eq(error, val);

	return 0;
}

/**
 * @function		utc_system_device_display_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_device_display_startup(void)
{
	int ret;

	ret = system_info_get_platform_bool(DISPLAY_STATE_FEATURE, &g_DisplayStateFeature);
	ret = system_info_get_platform_bool(DISPLAY_FEATURE, &g_DisplayFeature);
	device_display_get_numbers(&cnt);
}

/**
 * @function		utc_system_device_display_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_device_display_cleanup(void)
{

}

/**
 * @testcase		utc_system_device_display_get_numbers_p
 * @since_tizen		2.3
 * @description		Positive test case of device_display_get_numbers.
 */
int utc_system_device_display_get_numbers_p(void)
{
	int number, error;

	error = device_display_get_numbers(&number);
	if (g_DisplayFeature == false)
		assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_display_get_numbers_n
 * @since_tizen		2.3
 * @description		Negative test case of device_display_get_numbers.
 */
int utc_system_device_display_get_numbers_n(void)
{
	int error;

	error = device_display_get_numbers(NULL);
	if (g_DisplayFeature == false)
		assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_display_get_max_brightness_p
 * @since_tizen		2.3
 * @description		Positive test case of device_display_get_max_brightness.
 */
int utc_system_device_display_get_max_brightness_p(void)
{
	int value, error, i, ret;

	for (i = 0; i < cnt; i++) {
		error = device_display_get_max_brightness(i, &value);
		if (g_DisplayFeature == false)
			assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);

		ret = assert_except_not_supported(error, DEVICE_ERROR_NONE);
		if (ret != 0)
			return ret;
	}

	return 0;
}

/**
 * @testcase		utc_system_device_display_get_max_brightness_n_1
 * @since_tizen		2.3
 * @description		Negative test case of device_display_get_max_brightness. Invalid display index.
 */
int utc_system_device_display_get_max_brightness_n_1(void)
{
	int value, error;

	error = device_display_get_max_brightness(cnt+1, &value);
	if (g_DisplayFeature == false)
		assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_display_get_max_brightness_n_2
 * @since_tizen		2.3
 * @description		Negative test case of device_display_get_max_brightness. Brightness parameter is null.
 */
int utc_system_device_display_get_max_brightness_n_2(void)
{
	int error, i;

	for (i = 0; i < cnt; i++) {
		error = device_display_get_max_brightness(i, NULL);
		if (g_DisplayFeature == false)
			assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
		else
			assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_display_get_brightness_p
 * @since_tizen		2.3
 * @description		Positive test case of device_display_get_brightness.
 */
int utc_system_device_display_get_brightness_p(void)
{
	int value, error, i, ret;

	for (i = 0; i < cnt; i++) {
		error = device_display_get_brightness(i, &value);
		if (g_DisplayFeature == false)
			assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);

		ret = assert_except_not_supported(error, DEVICE_ERROR_NONE);
		if (ret != 0)
			return ret;
	}

	return 0;
}

/**
 * @testcase		utc_system_device_display_get_brightness_n_1
 * @since_tizen		2.3
 * @description		Negative test case of device_display_get_brightness. Invalid display index.
 */
int utc_system_device_display_get_brightness_n_1(void)
{
	int value, error;

	error = device_display_get_brightness(cnt+1, &value);
	if (g_DisplayFeature == false)
		assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_display_get_brightness_n_2
 * @since_tizen		2.3
 * @description		Negative test case of device_display_get_brightness. Brightness parameter is null.
 */
int utc_system_device_display_get_brightness_n_2(void)
{
	int error, i;

	for (i = 0; i < cnt; i++) {
		error = device_display_get_brightness(i, NULL);
		if (g_DisplayFeature == false)
			assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
		else
			assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_display_set_brightness_p
 * @since_tizen		2.3
 * @description		Positive test case of device_display_set_brightness.
 */
int utc_system_device_display_set_brightness_p(void)
{
	int max, error, i, ret;

	for (i = 0; i < cnt; i++) {
		error = device_display_get_max_brightness(i, &max);
		if (g_DisplayFeature == false)
			assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);

		ret = assert_except_not_supported(error, DEVICE_ERROR_NONE);
		if (ret != 0)
			return ret;

		error = device_display_set_brightness(i, max);
		if (g_DisplayFeature == false)
			assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);

		ret = assert_except_not_supported(error, DEVICE_ERROR_NONE);
		if (ret != 0)
			return ret;
	}

	return 0;
}

/**
 * @testcase		utc_system_device_display_set_brightness_n_1
 * @since_tizen		2.3
 * @description		Negative test case of device_display_set_brightness. Invalid display index.
 */
int utc_system_device_display_set_brightness_n_1(void)
{
	int error;

	error = device_display_set_brightness(-1, 0);
	if (g_DisplayFeature == false)
		assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_display_set_brightness_n_2
 * @since_tizen		2.3
 * @description		Negative test case of device_display_set_brightness. Invalid brightness.
 */
int utc_system_device_display_set_brightness_n_2(void)
{
	int error, i;

	for (i = 0; i < cnt; i++) {
		error = device_display_set_brightness(i, -1);
		if (g_DisplayFeature == false)
			assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
		else
			assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_display_set_brightness_n_3
 * @since_tizen		2.3
 * @description		Negative test case of device_display_set_brightness. Invalid brightness.
 */
int utc_system_device_display_set_brightness_n_3(void)
{
	int max, error, i;

	for (i = 0; i < cnt; i++) {
		error = device_display_get_max_brightness(i, &max);
		if (g_DisplayFeature == false)
			assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
		else
			assert_eq(error, DEVICE_ERROR_NONE);

		error = device_display_set_brightness(i, max+1);
		if (g_DisplayFeature == false)
			assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
		else
			assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_display_get_state_p
 * @since_tizen		2.3
 * @description		Positive test case of device_display_get_state.
 */
int utc_system_device_display_get_state_p(void)
{
	display_state_e state;
	int error;

	error = device_display_get_state(&state);
	if (g_DisplayFeature == false)
		assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_display_get_state_n
 * @since_tizen		2.3
 * @description		Negative test case of device_display_get_state.
 */
int utc_system_device_display_get_state_n(void)
{
	int error;

	error = device_display_get_state(NULL);
	if (g_DisplayFeature == false)
		assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_display_change_state_p
 * @since_tizen		2.3
 * @description		Positive test case of device_display_change_state()
 */
int utc_system_device_display_change_state_p(void)
{
	int error, i;

	for (i = 0; i < ARRAY_SIZE(display_states); i++) {
		error = device_display_change_state(display_states[i]);
		if (g_DisplayFeature == true && g_DisplayStateFeature == true)
			assert_eq(error, DEVICE_ERROR_NONE);
		else
			assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_display_change_state_n
 * @since_tizen		2.3
 * @description		Negative test case of device_display_change_state()
 */
int utc_system_device_display_change_state_n(void)
{
	int error;

	error = device_display_change_state(-1);
	if (g_DisplayFeature == true && g_DisplayStateFeature == true)
		assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);
	else
		assert_eq(error, DEVICE_ERROR_NOT_SUPPORTED);

	return 0;
}
