//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include <device/temperature.h>

//& set: DeviceTemperature
#define THERMAL_AP_FEATURE              "http://tizen.org/feature/thermistor.ap"
#define THERMAL_CP_FEATURE              "http://tizen.org/feature/thermistor.cp"
#define THERMAL_BATTERY_FEATURE        "http://tizen.org/feature/thermistor.battery"

static bool ap_supported;
static bool cp_supported;
static bool battery_supported;


/**
 * @testcase		utc_system_device_temperature_startup
 * @since_tizen		5.5
 * @description		Called before each test
 */
void utc_system_device_thermal_startup(void)
{
	int ret;

	ret = system_info_get_platform_bool(THERMAL_AP_FEATURE, &ap_supported);
	ret = system_info_get_platform_bool(THERMAL_CP_FEATURE, &cp_supported);
	ret = system_info_get_platform_bool(THERMAL_BATTERY_FEATURE, &battery_supported);

	return;
}

/**
 * @testcase		utc_system_device_temperature_cleanup
 * @since_tizen		5.5
 * @description		Called before each test
 */
void utc_system_device_thermal_cleanup(void)
{

	return;
}

/**
 * @testcase		utc_system_device_thermal_get_temperature_p
 * @since_tizen		5.5
 * @description		Positive test case of utc_system_device_thermal_get_temperature.
 */
int utc_system_device_thermal_get_temperature_p(void)
{
	int value;
	int error;

	if(!ap_supported && !cp_supported && !battery_supported)
		return 0;

	if (ap_supported) {
		error = device_thermal_get_temperature(DEVICE_THERMAL_AP, &value);
		assert_eq(error, DEVICE_ERROR_NONE);
	}

	if (cp_supported) {
		error = device_thermal_get_temperature(DEVICE_THERMAL_CP, &value);
		assert_eq(error, DEVICE_ERROR_NONE);
	}

	if (battery_supported) {
		error = device_thermal_get_temperature(DEVICE_THERMAL_BATTERY, &value);
		assert_eq(error, DEVICE_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_system_device_thermal_get_temperature_n
 * @since_tizen		5.5
 * @description		Negative test case of utc_system_device_thermal_get_temperature.
 */
int utc_system_device_thermal_get_temperature_n(void)
{
	int value;
	int error;

	if(!ap_supported && !cp_supported && !battery_supported)
		return 0;

	error = device_thermal_get_temperature(1000, &value);
	assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}
