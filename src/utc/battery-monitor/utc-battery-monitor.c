/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License")
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <time.h>
#include <dlog.h>
#include <system_info.h>
#include "battery_monitor.h"

#include "assert.h"
#include "tct_app_common.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "NativeTCT"

#define BATTERY_FEATURE				"http://tizen.org/feature/battery"

#define TEST_APP_ID "org.tizen.w-home"

static battery_usage_data_h data_handle;
static bool is_battery_supported = false;
static double power_usage = -1;
time_t s_t, e_t;
const int tmin = 604800; /* Time interval for 7 days in seconds */

static void get_custom_time_values(void)
{
	time_t ret_time;
	long int crr_time = 0;
	time(&ret_time);
	if (ret_time == -1) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Precondition Fails: Time failed");
		return;
	}
	crr_time = ret_time;
	s_t = 0; e_t = 0;
	s_t = (crr_time - tmin/2); e_t = (crr_time - 1);

	return;
}

/**
 * @function		utc_battery_monitor_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_battery_monitor_startup(void)
{
	system_info_get_platform_bool(BATTERY_FEATURE, &is_battery_supported);
	get_custom_time_values();
	data_handle = NULL;
	power_usage = -1;

	return;
}

/**
 * @function		utc_battery_monitor_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_battery_monitor_cleanup(void)
{
	int error_code = 0;

	if (data_handle != NULL) {
		error_code = battery_monitor_battery_usage_data_destroy(data_handle);
		if (error_code != BATTERY_MONITOR_ERROR_NONE)
			dlog_print(DLOG_ERROR, LOG_TAG, "Failed to delete handle cleanup");

		data_handle = NULL;
	}

	return;
}

/**
 * @testcase		utc_battery_monitor_battery_usage_data_destroy_p
 * @since_tizen		5.5
 * @description		Positive test case of battery_monitor_battery_usage_data_destroy()
 */
int utc_battery_monitor_battery_usage_data_destroy_p(void)
{
	int error_code = 0;

	if (data_handle != NULL) {
		error_code = battery_monitor_battery_usage_data_destroy(data_handle);
		if (!is_battery_supported)
			assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
		else
			assert_eq(error_code, BATTERY_MONITOR_ERROR_NONE);
	} else {
		error_code = BATTERY_MONITOR_ERROR_NONE;
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NONE);
	}

	data_handle = NULL;

	return 0;
}

/**
 * @testcase		utc_battery_monitor_battery_usage_data_destroy_n
 * @since_tizen		5.5
 * @description		Negative test case of battery_monitor_battery_usage_data_destroy()
 */
int utc_battery_monitor_battery_usage_data_destroy_n(void)
{
	int error_code = 0;

	error_code = battery_monitor_battery_usage_data_destroy(NULL);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_battery_monitor_usage_data_get_power_usage_per_resource_n
 * @since_tizen		5.5
 * @description		Negative test case of battery_monitor_usage_data_get_power_usage_per_resource()
 */
int utc_battery_monitor_usage_data_get_power_usage_per_resource_n(void)
{
	int error_code = 0;

	error_code = battery_monitor_get_power_usage_by_app_for_all_resources(TEST_APP_ID, s_t, e_t, &data_handle);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else if (error_code == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NONE);

	error_code = battery_monitor_usage_data_get_power_usage_per_resource(NULL, BATTERY_MONITOR_RESOURCE_ID_CPU, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_usage_data_get_power_usage_per_resource(data_handle, BATTERY_MONITOR_RESOURCE_ID_CPU, NULL);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_usage_data_get_power_usage_per_resource(data_handle, BATTERY_MONITOR_RESOURCE_ID_MAX, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_battery_monitor_usage_data_get_power_usage_per_resource_p
 * @since_tizen		5.5
 * @description		Positive test case of battery_monitor_usage_data_get_power_usage_per_resource()
 */
int utc_battery_monitor_usage_data_get_power_usage_per_resource_p(void)
{
	int error_code = 0;

	error_code = battery_monitor_get_power_usage_by_app_for_all_resources(TEST_APP_ID, s_t, e_t, &data_handle);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else if (error_code == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
		return 0;
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NONE);

	error_code = battery_monitor_usage_data_get_power_usage_per_resource(data_handle, BATTERY_MONITOR_RESOURCE_ID_CPU, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_battery_monitor_get_power_usage_by_app_for_all_resources_p
 * @since_tizen		5.5
 * @description		Positive test case of battery_monitor_get_power_usage_by_app_for_all_resources()
 */
int utc_battery_monitor_get_power_usage_by_app_for_all_resources_p(void)
{
	int error_code = 0;

	error_code = battery_monitor_get_power_usage_by_app_for_all_resources(TEST_APP_ID, s_t, e_t, &data_handle);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else if (error_code == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_battery_monitor_get_power_usage_by_app_for_all_resources_n
 * @since_tizen		5.5
 * @description		Negative test case of battery_monitor_get_power_usage_by_app_for_all_resources()
 */
int utc_battery_monitor_get_power_usage_by_app_for_all_resources_n(void)
{
	int error_code = 0;

	error_code = battery_monitor_get_power_usage_by_app_for_all_resources(TEST_APP_ID, s_t, e_t, NULL);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app_for_all_resources(NULL, s_t, e_t, &data_handle);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app_for_all_resources(TEST_APP_ID, -1, -1, &data_handle);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app_for_all_resources(TEST_APP_ID, s_t, -1, &data_handle);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	/* Interchange time */
	error_code = battery_monitor_get_power_usage_by_app_for_all_resources(TEST_APP_ID, e_t, s_t, &data_handle);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_battery_monitor_get_power_usage_by_app_per_resource_p
 * @since_tizen		5.5
 * @description		Positive test case of battery_monitor_get_power_usage_by_app_per_resource()
 */
int utc_battery_monitor_get_power_usage_by_app_per_resource_p(void)
{
	int error_code = 0;

	error_code = battery_monitor_get_power_usage_by_app_per_resource(TEST_APP_ID, BATTERY_MONITOR_RESOURCE_ID_CPU, s_t, e_t, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else if (error_code == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_battery_monitor_get_power_usage_by_app_per_resource_n
 * @since_tizen		5.5
 * @description		Negative test case of battery_monitor_get_power_usage_by_app_per_resource()
 */
int utc_battery_monitor_get_power_usage_by_app_per_resource_n(void)
{
	int error_code = 0;

	error_code = battery_monitor_get_power_usage_by_app_per_resource(TEST_APP_ID, BATTERY_MONITOR_RESOURCE_ID_CPU, s_t, e_t, NULL);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app_per_resource(NULL, BATTERY_MONITOR_RESOURCE_ID_CPU, s_t, e_t, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app_per_resource(TEST_APP_ID, BATTERY_MONITOR_RESOURCE_ID_CPU, e_t, s_t, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app_per_resource(TEST_APP_ID, BATTERY_MONITOR_RESOURCE_ID_CPU, -1, -1, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app_per_resource(TEST_APP_ID, BATTERY_MONITOR_RESOURCE_ID_CPU, s_t, -1, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app_per_resource(TEST_APP_ID, BATTERY_MONITOR_RESOURCE_ID_MAX, s_t, e_t, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_battery_monitor_get_power_usage_by_app_p
 * @since_tizen		5.5
 * @description		Positive test case of battery_monitor_get_power_usage_by_app()
 */
int utc_battery_monitor_get_power_usage_by_app_p(void)
{
	int error_code = 0;

	error_code = battery_monitor_get_power_usage_by_app(TEST_APP_ID, s_t, e_t, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else if (error_code == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_battery_monitor_get_power_usage_by_app_n
 * @since_tizen		5.5
 * @description		Negative test case of battery_monitor_get_power_usage_by_app()
 */
int utc_battery_monitor_get_power_usage_by_app_n(void)
{
	int error_code = 0;

	error_code = battery_monitor_get_power_usage_by_app(TEST_APP_ID, s_t, e_t, NULL);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app(NULL, s_t, e_t, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app(TEST_APP_ID, e_t, s_t, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app(TEST_APP_ID, -1, -1, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_app(TEST_APP_ID, s_t, -1, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_battery_monitor_get_power_usage_by_resource_p
 * @since_tizen		5.5
 * @description		Positive test case of battery_monitor_get_power_usage_by_resource()
 */
int utc_battery_monitor_get_power_usage_by_resource_p(void)
{
	int error_code = 0;
	int resource_id = BATTERY_MONITOR_RESOURCE_ID_CPU;

	error_code = battery_monitor_get_power_usage_by_resource(resource_id, s_t, e_t, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else if (error_code == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_battery_monitor_get_power_usage_by_resource_n
 * @since_tizen		5.5
 * @description		Negative test case of battery_monitor_get_power_usage_by_resource()
 */
int utc_battery_monitor_get_power_usage_by_resource_n(void)
{
	int error_code = 0;
	int resource_id = BATTERY_MONITOR_RESOURCE_ID_CPU;

	error_code = battery_monitor_get_power_usage_by_resource(resource_id, s_t, e_t, NULL);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_resource(resource_id, e_t, s_t, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_resource(resource_id, s_t, -1, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_resource(resource_id, -1, -1, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	error_code = battery_monitor_get_power_usage_by_resource(BATTERY_MONITOR_RESOURCE_ID_MAX, s_t, e_t, &power_usage);
	if (!is_battery_supported)
		assert_eq(error_code, BATTERY_MONITOR_ERROR_NOT_SUPPORTED);
	else
		assert_eq(error_code, BATTERY_MONITOR_ERROR_INVALID_PARAMETER);

	return 0;
}
