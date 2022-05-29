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
#include <device/battery.h>

//& set: DeviceBattery
#define BATTERY_FEATURE                      "http://tizen.org/feature/battery"

static bool is_supported;

/**
 * @testcase		utc_system_device_battery_startup
 * @since_tizen		4.0
 * @description		Called before each test
 */
void utc_system_device_battery_startup(void)
{
	int ret;

	ret = system_info_get_platform_bool(BATTERY_FEATURE, &is_supported);
	return;
}

/**
 * @testcase		utc_system_device_battery_cleanup
 * @since_tizen		4.0
 * @description		Called before each test
 */
void utc_system_device_battery_cleanup(void)
{

	return;
}

/**
 * @testcase		utc_system_device_battery_get_percent_p
 * @since_tizen		2.3
 * @description		Positive test case of device_battery_get_percent.
 */
int utc_system_device_battery_get_percent_p(void)
{
	int percent, error;

	if(!is_supported)
		return 0;

	error = device_battery_get_percent(&percent);
	assert_eq(error, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_percent_n
 * @since_tizen		2.3
 * @description		Negative test case of device_battery_get_percent.
 */
int utc_system_device_battery_get_percent_n(void)
{
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_get_percent(NULL);
	assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_is_charging_p
 * @since_tizen		2.3
 * @description		Positive test case of system_device_battery_is_charging.
 */
int utc_system_device_battery_is_charging_p(void)
{
	bool charging;
	int error;
	device_battery_status_e status;

	if(!is_supported)
		return 0;

	error = device_battery_is_charging(&charging);

	/* If there is no battery on the target during the auto tests,
	 * status is "Not Charging", and apis can be operated improperly.
	 * Thus battery apis need to be handled as no error state in the case. */
	if (device_battery_get_status(&status) == DEVICE_ERROR_NONE &&
		status == DEVICE_BATTERY_STATUS_NOT_CHARGING)
		error = DEVICE_ERROR_NONE;

	assert_eq(error, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_is_charging_n
 * @since_tizen		2.3
 * @description		Negative test case of system_device_battery_is_charging.
 */
int utc_system_device_battery_is_charging_n(void)
{
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_is_charging(NULL);
	assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_level_status_p
 * @since_tizen		2.3
 * @description		Positive test case of device_battery_get_level_status.
 */
int utc_system_device_battery_get_level_status_p(void)
{
	device_battery_level_e status;
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_get_level_status(&status);
	assert_eq(error, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_level_status_n
 * @since_tizen		2.3
 * @description		Negative test case of device_battery_get_level_status.
 */
int utc_system_device_battery_get_level_status_n(void)
{
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_get_level_status(NULL);
	assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_health_p
 * @since_tizen		3.0
 * @description		Positive test case of device_battery_get_health.
 */
int utc_system_device_battery_get_health_p(void)
{
	device_battery_health_e health;
	int error;
	device_battery_status_e status;

	if(!is_supported)
		return 0;

	error = device_battery_get_health(&health);

	/* If there is no battery on the target during the auto tests,
	 * status is "Not Charging", and apis can be operated improperly.
	 * Thus battery apis need to be handled as no error state in the case. */
	if (device_battery_get_status(&status) == DEVICE_ERROR_NONE &&
		status == DEVICE_BATTERY_STATUS_NOT_CHARGING)
		error = DEVICE_ERROR_NONE;

	assert_eq(error, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_health_n
 * @since_tizen		3.0
 * @description		Negative test case of device_battery_get_health.
 */
int utc_system_device_battery_get_health_n(void)
{
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_get_health(NULL);
	assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_power_source_p
 * @since_tizen		3.0
 * @description		Positive test case of device_battery_get_power_source.
 */
int utc_system_device_battery_get_power_source_p(void)
{
	device_battery_power_source_e power;
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_get_power_source(&power);
	assert_eq(error, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_power_source_n
 * @since_tizen		3.0
 * @description		Negative test case of device_battery_get_power_source.
 */
int utc_system_device_battery_get_power_source_n(void)
{
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_get_power_source(NULL);
	assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_status_p
 * @since_tizen		3.0
 * @description		Positive test case of device_battery_get_status.
 */
int utc_system_device_battery_get_status_p(void)
{
	device_battery_status_e status;
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_get_status(&status);
	assert_eq(error, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_status_n
 * @since_tizen		3.0
 * @description		Negative test case of device_battery_get_status.
 */
int utc_system_device_battery_get_status_n(void)
{
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_get_status(NULL);
	assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_property_p
 * @since_tizen		3.0
 * @description		Positive test case of device_battery_get_property.
 */
int utc_system_device_battery_get_property_p(void)
{
	int value;
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_get_property(DEVICE_BATTERY_PROPERTY_CAPACITY, &value);
	assert_eq(error, DEVICE_ERROR_NONE);

	error = device_battery_get_property(DEVICE_BATTERY_PROPERTY_CURRENT_NOW, &value);
	assert_eq(error, DEVICE_ERROR_NONE);

	error = device_battery_get_property(DEVICE_BATTERY_PROPERTY_CURRENT_AVERAGE, &value);
	assert_eq(error, DEVICE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_device_battery_get_property_n
 * @since_tizen		3.0
 * @description		Negative test case of device_battery_get_property.
 */
int utc_system_device_battery_get_property_n(void)
{
	int error;

	if(!is_supported)
		return 0;

	error = device_battery_get_property(DEVICE_BATTERY_PROPERTY_CAPACITY, NULL);
	assert_eq(error, DEVICE_ERROR_INVALID_PARAMETER);

	return 0;
}

