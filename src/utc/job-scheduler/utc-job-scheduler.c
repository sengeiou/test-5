/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
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
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <job_scheduler.h>
#include <system_info.h>
#include <dlog.h>

#include "assert.h"
#include "tct_app_common.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "NativeTCT"

#define JOB_ID "TestJob"

static job_info_h job_info;
static job_service_h job_service;

/**
 * @function    utc_job_info_create_p_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_create_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_create_p
 * @since_tizen 4.0
 * @description Creates the job info handle.
 * @scenario    Check whether the result is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_create_p(void)
{
	int ret;

	ret = job_info_create(&job_info);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_create_n
 * @since_tizen 4.0
 * @description Creates the job info handle.
 * @scenario    Calls the job_info_create() with invalid parameter.
 *              Checks whether the result is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_create_n(void)
{
	int ret;

	ret = job_info_create(NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_destroy_p_startup
 * @description Creates the job info handle for Test.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_destroy_p_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_destroy_p_cleanup
 * @description Sets the job info handle to NULL.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_destroy_p_cleanup(void)
{
	job_info = NULL;
}

/**
 * @function    utc_job_info_destroy_p
 * @since_tizen 4.0
 * @description Destroys the created job info handle.
 * @scenario    Destroys the created job info handle.
 *              Checks whether the result is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_destroy_p(void)
{
	int ret;

	ret = job_info_destroy(job_info);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_destroy_n
 * @since_tizen 4.0
 * @description Destroys the created job info handle.
 * @scenario    Calls the job_info_destroy() with invalid parameter.
 *              Checks whether the result is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_destroy_n(void)
{
	int ret;

	ret = job_info_destroy(NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_set_periodic_p_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_periodic_p_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_set_periodic_p_cleanup
 * @description Destroys the create job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_periodic_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_set_periodic_p
 * @since_tizen 4.0
 * @description Sets the periodic interval to the job handle.
 * @scenario    Sets the periodic interval(30 minutes) to the job handle.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_set_periodic_p(void)
{
	int ret;

	ret = job_info_set_periodic(job_info, 30);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_set_periodic_n
 * @since_tizen 4.0
 * @description Sets the periodic interval to the job handle.
 * @scenario    Calls the job_info_set_periodic() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_set_periodic_n(void)
{
	int ret;

	ret = job_info_set_periodic(NULL, 30);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_set_persistent_p_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_persistent_p_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_set_persistent_p_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_persistent_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_set_persistent_p
 * @since_tizen 4.0
 * @description Sets the job to be automatically scheduled after
 *              the device reboots.
 * @scenario    Calls the job_info_set_persistent() with "true" flag.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the persistent parameter is true, the job will be scheduled
 *              automatically after the device reboots.
 */
int utc_job_info_set_persistent_p(void)
{
	int ret;

	ret = job_info_set_persistent(job_info, true);
	assert_eq(ret, JOB_ERROR_NONE);

	ret = job_info_set_persistent(job_info, false);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_set_persistent_n
 * @since_tizen 4.0
 * @description Sets the job to be automatically scheduled after
 *              the device reboots.
 * @scenario    Calls the job_info_set_persistent() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_set_persistent_n(void)
{
	int ret;

	ret = job_info_set_persistent(NULL, true);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_set_once_p_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_once_p_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_set_once_p_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_once_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_set_once_p
 * @since_tizen 4.0
 * @description Sets the job not to be repeated.
 * @scenario    Calls the job_info_set_once().
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the once parameter is "true", the job will not be repeated.
 */
int utc_job_info_set_once_p(void)
{
	int ret;

	ret = job_info_set_once(job_info, true);
	assert_eq(ret, JOB_ERROR_NONE);

	ret = job_info_set_once(job_info, false);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_set_once_n
 * @since_tizen 4.0
 * @description Sets the job not to be repeated.
 * @scenario    Calls the job_info_set_once() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_set_once_n(void)
{
	int ret;

	ret = job_info_set_once(NULL, true);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_set_requirement_timeout_p_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requirement_timeout_p_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_set_requirement_timeout_p_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requirement_timeout_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_set_requirement_timeout_p
 * @since_tizen 4.0
 * @description Sets the timeout interval of the requirements.
 * @scenario    Sets the timeout interval(500ms) of the requirements to
 *              the job info handle.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the requirements are not ready within the interval when
 *              triggering the events, the job will not be launched.
 */
int utc_job_info_set_requirement_timeout_p(void)
{
	int ret;

	ret = job_info_set_requirement_timeout(job_info, 500);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_set_requirement_timeout_n
 * @since_tizen 4.0
 * @description Sets the timeout interval of the requirements.
 * @scenario    Calls the job_info_set_requirement_timeout() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_set_requirement_timeout_n(void)
{
	int ret;

	ret = job_info_set_requirement_timeout(NULL, 500);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_set_requires_battery_not_low_p_startup
 * @description Initializes the job scheduler and creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_battery_not_low_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_set_requires_battery_not_low_p_cleanup
 * @description Destroys the create job info handle and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_battery_not_low_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_info_set_requires_battery_not_low_p
 * @since_tizen 4.0
 * @description Sets that the battery level must not be low to run the job.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_set_requires_battery_not_low().
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the function returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_set_requires_battery_not_low_p(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool("http://tizen.org/feature/battery",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_set_requires_battery_not_low(job_info, true);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_set_requires_battery_not_low_n1
 * @since_tizen 4.0
 * @description Sets that the battery level must not be low to run the job.
 * @scenario    Calls the job_info_set_requires_battery_not_low() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_set_requires_battery_not_low_n1(void)
{
	int ret;

	ret = job_info_set_requires_battery_not_low(NULL, true);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_set_requires_battery_not_low_n2_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_battery_not_low_n2_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_set_requires_battery_not_low_n2_cleanup
 * @description Destorys the create job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_battery_not_low_n2_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_set_requires_battery_not_low_n2
 * @since_tizen 4.0
 * @description Sets that the battery level must not be low to run the job.
 * @scenario    Calls the job_info_set_requires_battery_not_low() without calling job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_info_set_requires_battery_not_low_n2(void)
{
	int ret;

	ret = job_info_set_requires_battery_not_low(job_info, true);
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_info_set_requires_charging_p_startup
 * @description Initializes the job scheudler and creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_charging_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_set_requires_charging_p_cleanup
 * @description Destroys the created job info handle and finalizes the job shceudler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_charging_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_info_set_requires_charging_p
 * @since_tizen 4.0
 * @description Sets that the battery must be charging to run the job.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_set_requires_charging().
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the function returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_set_requires_charging_p(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool("http://tizen.org/feature/battery",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_set_requires_charging(job_info, true);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_set_requires_charging_n1
 * @since_tizen 4.0
 * @description Sets that the battery must be charging to run the job.
 * @scenario    Calls the job_info_set_requires_charging() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_set_requires_charging_n1(void)
{
	int ret;

	ret = job_info_set_requires_charging(NULL, true);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_set_requires_charging_n2_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_charging_n2_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_set_requires_charging_n2_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_charging_n2_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_set_requires_charging_n2
 * @since_tizen 4.0
 * @description Sets that the battery must be charging to run the job.
 * @scenario    Calls the job_info_set_requires_charging() without calling job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_info_set_requires_charging_n2(void)
{
	int ret;

	ret = job_info_set_requires_charging(job_info, true);
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_info_set_requires_wifi_connection_p_startup
 * @description Initializes the job scheduler and creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_wifi_connection_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_set_requires_wifi_connection_p_cleanup
 * @description Destroys the created job info handle and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_wifi_connection_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_info_set_requires_wifi_connection_p
 * @since_tizen 4.0
 * @privilege   %http://tizen.org/privilege/network.get
 * @description Sets that the WiFi must be connected to run the job.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_set_requires_wifi_connection().
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the function returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_set_requires_wifi_connection_p(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool(
			"http://tizen.org/feature/network.wifi",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_set_requires_wifi_connection(job_info, true);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_set_requires_wifi_connection_n1
 * @since_tizen 4.0
 * @privilege   %http://tizen.org/privilege/network.get
 * @description Sets that the WiFi must be connected to run the job.
 * @scenario    Calls the job_info_set_requires_wifi_connection() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_set_requires_wifi_connection_n1(void)
{
	int ret;

	ret = job_info_set_requires_wifi_connection(NULL, true);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_set_requires_wifi_connection_n2_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_wifi_connection_n2_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_set_requires_wifi_connection_n2_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_set_requires_wifi_connection_n2_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_set_requires_wifi_connection_n2
 * @since_tizen 4.0
 * @privilege   %http://tizen.org/privilege/network.get
 * @description Sets that the WiFi must be connected to run the job.
 * @scenario    Calls the job_info_set_requires_wifi_connection() without calling the job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_info_set_requires_wifi_connection_n2(void)
{
	int ret;

	ret = job_info_set_requires_wifi_connection(job_info, true);
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p_startup
 * @description Initializes the job scheduler and creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 * @see         utc_job_info_add_trigger_event_p1()
 * @see         utc_job_info_add_trigger_event_p2()
 * @see         utc_job_info_add_trigger_event_p3()
 * @see         utc_job_info_add_trigger_event_p4()
 * @see         utc_job_info_add_trigger_event_p5()
 * @see         utc_job_info_add_trigger_event_p6()
 * @see         utc_job_info_add_trigger_event_p7()
 * @see         utc_job_info_add_trigger_event_p8()
 * @see         utc_job_info_add_trigger_event_p9()
 * @see         utc_job_info_add_trigger_event_p10()
 * @see         utc_job_info_add_trigger_event_p11()
 * @see         utc_job_info_add_trigger_event_p12()
 * @see         utc_job_info_add_trigger_event_p13()
 * @see         utc_job_info_add_trigger_event_p14()
 * @see         utc_job_info_add_trigger_event_p15()
 * @see         utc_job_info_add_trigger_event_p16()
 * @see         utc_job_info_add_trigger_event_p17()
 * @see         utc_job_info_add_trigger_event_p18()
 * @see         utc_job_info_add_trigger_event_p19()
 * @see         utc_job_info_add_trigger_event_p20()
 * @see         utc_job_info_add_trigger_event_p21()
 */
void utc_job_info_add_trigger_event_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_add_trigger_event_p_cleanup
 * @description Destroys the created job info handle and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 * @see         utc_job_info_add_trigger_event_p1()
 * @see         utc_job_info_add_trigger_event_p2()
 * @see         utc_job_info_add_trigger_event_p3()
 * @see         utc_job_info_add_trigger_event_p4()
 * @see         utc_job_info_add_trigger_event_p5()
 * @see         utc_job_info_add_trigger_event_p6()
 * @see         utc_job_info_add_trigger_event_p7()
 * @see         utc_job_info_add_trigger_event_p8()
 * @see         utc_job_info_add_trigger_event_p9()
 * @see         utc_job_info_add_trigger_event_p10()
 * @see         utc_job_info_add_trigger_event_p11()
 * @see         utc_job_info_add_trigger_event_p12()
 * @see         utc_job_info_add_trigger_event_p13()
 * @see         utc_job_info_add_trigger_event_p14()
 * @see         utc_job_info_add_trigger_event_p15()
 * @see         utc_job_info_add_trigger_event_p16()
 * @see         utc_job_info_add_trigger_event_p17()
 * @see         utc_job_info_add_trigger_event_p18()
 * @see         utc_job_info_add_trigger_event_p19()
 * @see         utc_job_info_add_trigger_event_p20()
 * @see         utc_job_info_add_trigger_event_p21()
 */
void utc_job_info_add_trigger_event_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_info_add_trigger_event_p1
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_BATTERY_LEVEL_EMPTY.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p1(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool("http://tizen.org/feature/battery",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_BATTERY_LEVEL_EMPTY);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p2
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_BATTERY_LEVEL_CRITICAL.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p2(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool("http://tizen.org/feature/battery",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_BATTERY_LEVEL_CRITICAL);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p3
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_BATTERY_LEVEL_LOW.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p3(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool("http://tizen.org/feature/battery",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_BATTERY_LEVEL_LOW);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p4
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_BATTERY_LEVEL_HIGH.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p4(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool("http://tizen.org/feature/battery",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_BATTERY_LEVEL_HIGH);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p5
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_CHARGER_STATE_CONNECTED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p5(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool("http://tizen.org/feature/battery",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_CHARGER_STATE_CONNECTED);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p6
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_CHARGER_STATE_DISCONNECTED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p6(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool("http://tizen.org/feature/battery",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_CHARGER_STATE_DISCONNECTED);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p7
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_DISPLAY_STATE_ON.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_add_trigger_event_p7(void)
{
	int ret;

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_DISPLAY_STATE_ON);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p7
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_DISPLAY_STATE_OFF.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_add_trigger_event_p8(void)
{
	int ret;

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_DISPLAY_STATE_OFF);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p9
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_DISPLAY_STATE_DIM.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_add_trigger_event_p9(void)
{
	int ret;

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_DISPLAY_STATE_DIM);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p10
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_EARJACK_STATE_CONNECTED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_add_trigger_event_p10(void)
{
	int ret;

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_EARJACK_STATE_CONNECTED);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p11
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_EARJACK_STATE_DISCONNECTED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_add_trigger_event_p11(void)
{
	int ret;

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_EARJACK_STATE_DISCONNECTED);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p12
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_GPS_STATE_DISABLED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p12(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool(
			"http://tizen.org/feature/location.gps",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_GPS_STATE_DISABLED);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p13
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_GPS_STATE_SEARCHING.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p13(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool(
			"http://tizen.org/feature/location.gps",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_GPS_STATE_SEARCHING);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p14
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_GPS_STATE_CONNECTED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p14(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool(
			"http://tizen.org/feature/location.gps",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_GPS_STATE_CONNECTED);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p15
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_POWERSAVE_MODE_ENABLED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_add_trigger_event_p15(void)
{
	int ret;

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_POWERSAVE_MODE_ENABLED);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p16
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_POWERSAVE_MODE_DISABLED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_add_trigger_event_p16(void)
{
	int ret;

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_POWERSAVE_MODE_DISABLED);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p17
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_USB_STATE_CONNECTED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p17(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool(
			"http://tizen.org/feature/usb.host",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_USB_STATE_CONNECTED);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p18
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_USB_STATE_DISCONNECTED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p18(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool(
			"http://tizen.org/feature/usb.host",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_USB_STATE_DISCONNECTED);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p19
 * @since_tizen 4.0
 * @remakrs     To add this event, the application must have http://tizen.org/privilege/network.get privilege.
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_WIFI_STATE_DISABLED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p19(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool(
			"http://tizen.org/feature/network.wifi",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_WIFI_STATE_DISABLED);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p20
 * @since_tizen 4.0
 * @remakrs     To add this event, the application must have http://tizen.org/privilege/network.get privilege.
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_WIFI_STATE_DISCONNECTED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p20(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool(
			"http://tizen.org/feature/network.wifi",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_WIFI_STATE_DISCONNECTED);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_p21
 * @since_tizen 4.0
 * @remakrs     To add this event, the application must have http://tizen.org/privilege/network.get privilege.
 * @description Adds the trigger event to the job info handle.
 * @scenario    Checks whether the feature is supported or NOT.
 *              Calls the job_info_add_trigger_event() with JOB_TRIGGER_EVENT_WIFI_STATE_CONNECTED.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 *              If the feature is not supported, the funtions returns JOB_ERROR_NOT_SUPPORTED.
 */
int utc_job_info_add_trigger_event_p21(void)
{
	int ret;
	bool feature = false;

	ret = system_info_get_platform_bool(
			"http://tizen.org/feature/network.wifi",
			&feature);
	assert_eq(ret, SYSTEM_INFO_ERROR_NONE);

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_WIFI_STATE_CONNECTED);
	if (feature)
		assert_eq(ret, JOB_ERROR_NONE);
	else
		assert_eq(ret, JOB_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_n1
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_add_trigger_event_n1(void)
{
	int ret;

	ret = job_info_add_trigger_event(NULL,
			JOB_TRIGGER_EVENT_WIFI_STATE_CONNECTED);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_n2_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_add_trigger_event_n2_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_add_trigger_event_n2_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_add_trigger_event_n2_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_add_trigger_event_n2
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event() without calling the job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_info_add_trigger_event_n2(void)
{
	int ret;

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_DISPLAY_STATE_ON);
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_n3_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_add_trigger_event_n3_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_add_trigger_event_n3_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_add_trigger_event_n3_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_add_trigger_event_n3
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_add_trigger_event_n3(void)
{
	int ret;

	ret = job_info_add_trigger_event(job_info, 100);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_add_trigger_event_n4_startup
 * @description Creates the job info handle and sets the periodic interval to the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_add_trigger_event_n4_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");

	ret = job_info_set_periodic(job_info, 30);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to set priodic interval");
	}
}

/**
 * @function    utc_job_info_add_trigger_event_n4_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_add_trigger_event_n4_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_add_trigger_event_n4
 * @since_tizen 4.0
 * @description Adds the trigger event to the job info handle.
 * @scenario    Calls the job_info_add_trigger_event().
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 *              If the job info handle has periodic interval that is not 0,
 *              the funtion returns JOB_ERROR_INVALID_PARAMETER.
 */
int utc_job_info_add_trigger_event_n4(void)
{
	int ret;

	ret = job_info_add_trigger_event(job_info,
			JOB_TRIGGER_EVENT_DISPLAY_STATE_ON);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_remove_trigger_event_p_startup
 * @description Initializes the job scheduler and creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_remove_trigger_event_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialized job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_remove_trigger_event_p_cleanup
 * @description Destroys the created job info handle and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_remove_trigger_event_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_info_remove_trigger_event_p
 * @since_tizen 4.0
 * @description Removes the trigger event from the job info handle.
 * @scenario    Calls the job_info_remove_trigger_event() with all trigger events.
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_info_remove_trigger_event_p(void)
{
	int ret;
	int start = JOB_TRIGGER_EVENT_BATTERY_LEVEL_EMPTY;
	int end = JOB_TRIGGER_EVENT_WIFI_STATE_CONNECTED;
	int event;

	for (event = start; event <= end; ++event) {
		ret = job_info_remove_trigger_event(job_info, event);
		if (ret != JOB_ERROR_NONE) {
			dlog_print(DLOG_ERROR, LOG_TAG,
					"Failed to remove trigger event(%d)",
					event);
			assert(true);
		}
	}

	return 0;
}

/**
 * @function    utc_job_info_remove_trigger_event_n1
 * @since_tizen 4.0
 * @description Removes the trigger event from the job info handle.
 * @scenario    Calls the job_info_remove_trigger_event() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_remove_trigger_event_n1(void)
{
	int ret;

	ret = job_info_remove_trigger_event(NULL,
			JOB_TRIGGER_EVENT_BATTERY_LEVEL_EMPTY);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_remove_trigger_event_n2_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_remove_trigger_event_n2_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_remove_trigger_event_n2_cleanup
 * @description Destroys the create job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_remove_trigger_event_n2_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_remove_trigger_event_n2
 * @since_tizen 4.0
 * @description Removes the trigger event from the job info handle.
 * @scenario    Calls the job_info_remove_trigger_event() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_remove_trigger_event_n2(void)
{
	int ret;

	ret = job_info_remove_trigger_event(job_info, 200);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_remove_trigger_event_n3_startup
 * @description Creates the job info handle and then sets the periodic interval to the created job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_remove_trigger_event_n3_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");

	ret = job_info_set_periodic(job_info, 30);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to set periodic interval");
	}
}

/**
 * @function    utc_job_info_remove_trigger_event_n3_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_remove_trigger_event_n3_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_remove_trigger_event_n3
 * @since_tizen 4.0
 * @description Removes the trigger event from the job info handle.
 * @scenario    Calls the job_info_remove_trigger_event() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 *              If the job info handle has the periodic interval, the funtion returns JOB_ERROR_INVALID_PARAMETER.
 */
int utc_job_info_remove_trigger_event_n3(void)
{
	int ret;

	ret = job_info_remove_trigger_event(job_info,
			JOB_TRIGGER_EVENT_BATTERY_LEVEL_EMPTY);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_get_job_id_p_startup
 * @description Initializes the job scheduler and creates the job info handle.
 *              And then, schedules the created the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_get_job_id_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
		return;
	}

	ret = job_info_set_periodic(job_info, 30);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to set periodic internal");
		return;
	}

	job_info_set_requires_battery_not_low(job_info, true);

	ret = job_scheduler_schedule(job_info, JOB_ID);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to schedule job");
}

/**
 * @function    utc_job_info_get_job_id_p_cleanup
 * @description Cancels the scheduled job, destroys the created job info handle
 *              and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_get_job_id_p_cleanup(void)
{
	job_scheduler_cancel(JOB_ID);

	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_info_get_job_id_p
 * @since_tizen 4.0
 * @description Gets the ID of the job.
 * @scenario    Calls the job_info_get_job_id().
 *              Checks whether the return values are the expected results or NOT.
 *              The ret should be JOB_ERROR_NONE and the job_is should be JOB_ID("TestJob").
 */
int utc_job_info_get_job_id_p(void)
{
	int ret;
	char *job_id = NULL;

	ret = job_info_get_job_id(job_info, &job_id);
	assert_eq(ret, JOB_ERROR_NONE);

	ret = strcmp(job_id, JOB_ID);
	assert_eq(ret, 0);

	free(job_id);

	return 0;
}

/**
 * @function    utc_job_info_get_job_id_n1
 * @since_tizen 4.0
 * @description Gets the ID of the job.
 * @scenario    Calls the job_info_get_job_id() with invalid parameter.
 *              Checks whether return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_get_job_id_n1(void)
{
	int ret;
	char *job_id = NULL;

	ret = job_info_get_job_id(NULL, &job_id);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_get_job_id_n2_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_get_job_id_n2_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_get_job_id_n2_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_get_job_id_n2_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_get_job_id_n2
 * @since_tizen 4.0
 * @description Gets the ID of the job.
 * @scenario    Calls the job_info_get_job_id() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_get_job_id_n2(void)
{
	int ret;

	ret = job_info_get_job_id(job_info, NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_get_job_id_n3_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_get_job_id_n3_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_get_job_id_n3_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_get_job_id_n3_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_get_job_id_n3
 * @since_tizen 4.0
 * @description Gets the ID of the job.
 * @scenario    Calls the job_info_get_job_id() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 *              The job_info should be scheduled.
 */
int utc_job_info_get_job_id_n3(void)
{
	int ret;
	char *job_id = NULL;

	ret = job_info_get_job_id(job_info, &job_id);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_clone_p_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_clone_p_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_clone_p_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_clone_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_clone_p
 * @since_tizen 4.0
 * @description Clones the given job_info handle.
 * @scenario    Calls the job_info_clone().
 *              Checks whether the return values are the expected results or NOT.
 */
int utc_job_info_clone_p(void)
{
	int ret;
	job_info_h clone = NULL;

	ret = job_info_clone(job_info, &clone);
	assert_eq(ret, JOB_ERROR_NONE);
	assert_neq(clone, NULL);

	job_info_destroy(clone);

	return 0;
}

/**
 * @function    utc_job_info_clone_n1
 * @since_tizen 4.0
 * @description Clones the given job_info handle.
 * @scenario    Calls the job_info_clone() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_clone_n1(void)
{
	int ret;
	job_info_h clone = NULL;

	ret = job_info_clone(NULL, &clone);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_clone_n2_startup
 * @description Creates the job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_clone_n2_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_info_clone_n2_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_info_clone_n2_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_info_clone_n2
 * @since_tizen 4.0
 * @description Clones the given job_info handle.
 * @scenario    Calls the job_info_clone() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_clone_n2(void)
{
	int ret;

	ret = job_info_clone(job_info, NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_info_clone_n3
 * @since_tizen 4.0
 * @description Clones the given job_info handle.
 * @scenario    Calls the job_info_clone() with invalid parameters.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_info_clone_n3(void)
{
	int ret;

	ret = job_info_clone(NULL, NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_init_p_cleanup
 * @description Finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_init_p_cleanup(void)
{
	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_init_p
 * @since_tizen 4.0
 * @description Initializes the job scheduler.
 * @scenario    Calls the job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NONE or not.
 */
int utc_job_scheduler_init_p(void)
{
	int ret;

	ret = job_scheduler_init();
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_scheduler_finish_p_startup
 * @description Initializes the job scheduler for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_finish_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialized job shceulder");
	}
}

/**
 * @function    utc_job_scheduler_finish_p
 * @since_tizen 4.0
 * @description Finalizes the job scheduler.
 * @scenario    Calls the job_scheduler_finish().
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_scheduler_finish_p(void)
{
	int ret;

	ret = job_scheduler_finish();
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_scheduler_finish_n
 * @since_tizen 4.0
 * @description Finalizes the job scheduler.
 * @scenario    Calls the job_scheduler_finish() without calling the job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_scheduler_finish_n(void)
{
	int ret;

	ret = job_scheduler_finish();
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_scheduler_schedule_p_startup
 * @description Initializes the job scheduler and Creates the job info handle.
 *              And then, Sets the periodic interval to the job info handle with the requirement for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_schedule_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialized job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
		return;
	}

	ret = job_info_set_periodic(job_info, 30);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to set periodic internal");
		return;
	}

	job_info_set_requires_battery_not_low(job_info, true);
}

/**
 * @function    utc_job_scheduler_schedule_p_cleanup
 * @description Cancels the scheduled job, destroys the created job info handle
 *              and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_schedule_p_cleanup(void)
{
	job_scheduler_cancel(JOB_ID);

	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_schedule_p
 * @since_tizen 4.0
 * @privilege   %http://tizen.org/privilege/appmanager.launch
 * @description Schedules the job.
 * @scenario    Calls the job_scheduler_schedule().
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_scheduler_schedule_p(void)
{
	int ret;

	ret = job_scheduler_schedule(job_info, JOB_ID);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_scheduler_schedule_n1
 * @since_tizen 4.0
 * @privilege   %http://tizen.org/privilege/appmanager.launch
 * @description Schedules the job.
 * @scenario    Calls the job_scheduler_schedule() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_schedule_n1(void)
{
	int ret;

	ret = job_scheduler_schedule(NULL, JOB_ID);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_schedule_n2_startup
 * @description Initializes the job scheduler and creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_schedule_n2_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret !=JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_scheduler_schedule_n2_cleanup
 * @description Destroys the created job info handle and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_schedule_n2_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_schedule_n2
 * @since_tizen 4.0
 * @privilege   %http://tizen.org/privilege/appmanager.launch
 * @description Schedules the job.
 * @scenario    Calls the job_scheduler_schedule() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_schedule_n2(void)
{
	int ret;

	ret = job_scheduler_schedule(job_info, NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_schedule_n3_startup
 * @description Creates the job info handle for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_schedule_n3_startup(void)
{
	int ret;

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
}

/**
 * @function    utc_job_scheduler_schedule_n3_cleanup
 * @description Destroys the created job info handle.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_schedule_n3_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}
}

/**
 * @function    utc_job_scheduler_schedule_n3
 * @since_tizen 4.0
 * @privilege   %http://tizen.org/privilege/appmanager.launch
 * @description Schedules the job.
 * @scenario    Calls the job_scheduler_schedule() without calling the job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_scheduler_schedule_n3(void)
{
	int ret;

	ret = job_scheduler_schedule(job_info, JOB_ID);
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_scheduler_schedule_n4_startup
 * @description Initializes the job scheduler and Creates the job info handle.
 *              And, sets the periodic interval to the job info handle with the requirement.
 *              And then, schedules the job for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_schedule_n4_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialized job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
		return;
	}

	ret = job_info_set_periodic(job_info, 30);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to set periodic internal");
		return;
	}

	job_info_set_requires_battery_not_low(job_info, true);

	ret = job_scheduler_schedule(job_info, JOB_ID);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to schedule job");
}

/**
 * @function    utc_job_scheduler_schedule_n4_cleanup
 * @description Cancels the scheduled job, destroys the created job info handle
 *              and finilzies the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_schedule_n4_cleanup(void)
{
	job_scheduler_cancel(JOB_ID);

	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_schedule_n4
 * @since_tizen 4.0
 * @privilege   %http://tizen.org/privilege/appmanager.launch
 * @description Schedules the job.
 * @scenario    Calls the job_scheduler_scheduler() with the scheduled job info handle.
 *              Checks whether the return value is JOB_ERROR_ALREADY_EXIST or NOT.
 */
int utc_job_scheduler_schedule_n4(void)
{
	int ret;

	ret = job_scheduler_schedule(job_info, JOB_ID);
	assert_eq(ret, JOB_ERROR_ALREADY_EXIST);

	return 0;
}

/**
 * @function    utc_job_scheduler_cancel_p_startup
 * @description Initializes the job scheduler and Creates the job info handle.
 *              And, sets the periodic interval to the job info handle with the requirement.
 *              And then, Schedules the job for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_cancel_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
		return;
	}

	ret = job_info_set_periodic(job_info, 30);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to set periodic internal");
		return;
	}

	job_info_set_requires_battery_not_low(job_info, true);

	ret = job_scheduler_schedule(job_info, JOB_ID);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to schedule job");
}

/**
 * @function    utc_job_scheduler_cancel_p_cleanup
 * @description Destroys the created job info handle and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_cancel_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_cancel_p
 * @since_tizen 4.0
 * @description Cancels the scheduled job.
 * @scenario    Calls the job_scheduler_cancel().
 *              Checks whether the return value JOB_ERORR_NONE or NOT.
 */
int utc_job_scheduler_cancel_p(void)
{
	int ret;

	ret = job_scheduler_cancel(JOB_ID);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_scheduler_cancel_n1
 * @since_tizen 4.0
 * @description Cancels the scheduled job.
 * @scenario    Calls the job_scheduler_cancel() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_cancel_n1(void)
{
	int ret;

	ret = job_scheduler_cancel(NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_cancel_n2
 * @since_tizen 4.0
 * @description Cancels the scheduled job.
 * @scenario    Calls the job_scheduler_cancel() wihout calling the job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_scheduler_cancel_n2(void)
{
	int ret;

	ret = job_scheduler_cancel(JOB_ID);
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_scheduler_cancel_n3_startup
 * @description Initializes the job scheduler for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_cancel_n3_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
	}
}

/**
 * @function    utc_job_scheduler_cancel_n3_cleanup
 * @description Finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_cancel_n3_cleanup(void)
{
	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_cancel_n3
 * @since_tizen 4.0
 * @description Cancels the scheduled job.
 * @scenario    Calls the job_scheduler_cancel() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_NO_SUCH_JOB or NOT.
 *              If the job_id is not scheduled, the function returns JOB_ERROR_NO_SUCH_JOB.
 */
int utc_job_scheduler_cancel_n3(void)
{
	int ret;

	ret = job_scheduler_cancel(JOB_ID);
	assert_eq(ret, JOB_ERROR_NO_SUCH_JOB);

	return 0;
}

/**
 * @function    utc_job_scheduler_cancel_all_p_startup
 * @description Initializes the job scheduler and Creates the job info handle.
 *              And, sets the periodic interval to the job info handle with the requirement.
 *              And then, schedules the job for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_cancel_all_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
		return;
	}

	ret = job_info_set_periodic(job_info, 30);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to set periodic internal");
		return;
	}

	job_info_set_requires_battery_not_low(job_info, true);

	ret = job_scheduler_schedule(job_info, JOB_ID);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to schedule job");
}

/**
 * @function    utc_job_scheduler_cancel_all_p_cleanup
 * @description Destroys the created job info handle and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_cancel_all_p_cleanup(void)
{
	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_cancel_all_p
 * @since_tizen 4.0
 * @description Cancels all scheduled jobs.
 * @scenario    Calls the job_scheduler_cancel_all().
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_scheduler_cancel_all_p(void)
{
	int ret;

	ret = job_scheduler_cancel_all();
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_scheduler_cancel_all_n
 * @since_tizen 4.0
 * @description Cancels all scheduled jobs.
 * @scenario    Calls the job_scheduler_cancel_all() without calling the job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_scheduler_cancel_all_n(void)
{
	int ret;

	ret = job_scheduler_cancel_all();
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_scheduler_notify_job_finished_p_startup
 * @description Initializes the job scheduler and Creates the job info handle.
 *              And, sets the periodic interval to the job info handle with the requirement.
 *              And then, schedules the job for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_notify_job_finished_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
		return;
	}

	ret = job_info_set_periodic(job_info, 30);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to set periodic internal");
		return;
	}

	job_info_set_requires_battery_not_low(job_info, true);

	ret = job_scheduler_schedule(job_info, JOB_ID);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to schedule job");
}

/**
 * @function    utc_job_scheduler_notify_job_finished_p_cleanup
 * @description Cancels the scheduled job, destroys the created job info handle
 *              and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_notify_job_finished_p_cleanup(void)
{
	job_scheduler_cancel(JOB_ID);

	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_notify_job_finished_p
 * @since_tizen 4.0
 * @description Notifies that the job is finished.
 * @scenario    Calls the job_scheduler_notify_job_finished().
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_scheduler_notify_job_finished_p(void)
{
	int ret;

	ret = job_scheduler_notify_job_finished(JOB_ID);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_scheduler_notify_job_finished_n1
 * @since_tizen 4.0
 * @description Notifies that the job is finished.
 * @scenario    Calls the job_scheduler_notify_job_finished() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_notify_job_finished_n1(void)
{
	int ret;

	ret = job_scheduler_notify_job_finished(NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_notify_job_finished_n2
 * @since_tizen 4.0
 * @description Notifies that the job is finished.
 * @scenario    Calls the job_scheduler_notify_job_finished() without calling job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_scheduler_notify_job_finished_n2(void)
{
	int ret;

	ret = job_scheduler_notify_job_finished(JOB_ID);
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_scheduler_notify_job_finished_n3_startup
 * @description Initializes the job scheduler for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_notify_job_finished_n3_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
	}
}

/**
 * @function    utc_job_scheduler_notify_job_finished_n3_cleanup
 * @description Finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_notify_job_finished_n3_cleanup(void)
{
	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_notify_job_finished_n3
 * @since_tizen 4.0
 * @description Notifies that the job is finished.
 * @scenario    Calls the job_scheduler_notify_job_finished() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_NO_SUCH_JOB or NOT.
 *              If the job_id is not scheduled, the funtion returns JOB_ERROR_NO_SUCH_JOB.
 */
int utc_job_scheduler_notify_job_finished_n3(void)
{
	int ret;

	ret = job_scheduler_notify_job_finished(JOB_ID);
	assert_eq(ret, JOB_ERROR_NO_SUCH_JOB);

	return 0;
}

/**
 * @function    utc_job_scheduler_foreach_job_p_startup
 * @description Initializes the job scheduler and Creates the job info handle.
 *              And, sets the periodic interval to the job info handle with the requirement.
 *              And then, schedules the job for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_foreach_job_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_info_create(&job_info);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create job info");
		return;
	}

	ret = job_info_set_periodic(job_info, 30);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to set periodic internal");
		return;
	}

	job_info_set_requires_battery_not_low(job_info, true);

	ret = job_scheduler_schedule(job_info, JOB_ID);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to schedule job");
}

/**
 * @function    utc_job_scheduler_foreach_job_p_cleanup
 * @description Cancels the scheduled job, destroys the created job info handle
 *              and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_foreach_job_p_cleanup(void)
{
	job_scheduler_cancel(JOB_ID);

	if (job_info) {
		job_info_destroy(job_info);
		job_info = NULL;
	}

	job_scheduler_finish();
}

static bool __foreach_job_cb(job_info_h job_info, void *user_data)
{
	int ret;
	char *job_id = NULL;
	bool *exist = (bool *)user_data;

	ret = job_info_get_job_id(job_info, &job_id);
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get job id");
		return false;
	}

	if (strcmp(job_id, JOB_ID) == 0) {
		dlog_print(DLOG_INFO, LOG_TAG, "%s exists", job_id);
		*exist = true;
	}

	free(job_id);

	return true;
}

/**
 * @function    utc_job_scheduler_foreach_job_p
 * @since_tizen 4.0
 * @description Retrieves all scheduled jobs.
 * @scenario    Calls the job_scheduler_foreach_job().
 *              Checks whether the return values are the expected results or NOT.
 *              The return value should be JOB_ERROR_NONE and the exist should be true.
 */
int utc_job_scheduler_foreach_job_p(void)
{
	int ret;
	bool exist = false;

	ret = job_scheduler_foreach_job(__foreach_job_cb, &exist);
	assert_eq(ret, JOB_ERROR_NONE);
	assert_eq(exist, true);

	return 0;
}

/**
 * @function    utc_job_scheduler_foreach_job_n1
 * @since_tizen 4.0
 * @description Retrieves all scheduled jobs.
 * @scenario    Calls the job_scheduler_foreach_job() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_foreach_job_n1(void)
{
	int ret;

	ret = job_scheduler_foreach_job(NULL, NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_foreach_job_n2
 * @since_tizen 4.0
 * @description Retrieves all scheduled jobs.
 * @scenario    Calls the job_scheduler_foreach_job() without calling the job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_scheduler_foreach_job_n2(void)
{
	int ret;

	ret = job_scheduler_foreach_job(__foreach_job_cb, NULL);
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_scheduler_foreach_job_n3_startup
 * @description Initializes the job scheduler for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_foreach_job_n3_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
	}
}

/**
 * @function    utc_job_scheduler_foreach_job_n3_cleanup
 * @description Finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_foreach_job_n3_cleanup(void)
{
	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_foreach_job_n3
 * @since_tizen 4.0
 * @description Retrieves all scheduled jobs.
 * @scenario    Calls the job_scheduler_foreach_job().
 *              Checks whether the return value is JOB_ERROR_NO_SUCH_JOB or NOT.
 *              If the scheduled job doesn't exist, the funtion returns JOB_ERROR_NO_SUCH_JOB.
 */
int utc_job_scheduler_foreach_job_n3(void)
{
	int ret;

	ret = job_scheduler_foreach_job(__foreach_job_cb, NULL);
	assert_eq(ret, JOB_ERROR_NO_SUCH_JOB);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_add_p_startup
 * @description Initializes the job scheduler for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_service_add_p_startup(void)
{
	int ret;

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
	}
}

/**
 * @function    utc_job_scheduler_service_add_p_cleanup
 * @description Revmoves the added job service handle and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_service_add_p_cleanup(void)
{
	if (job_service) {
		job_scheduler_service_remove(job_service);
		job_service = NULL;
	}

	job_scheduler_finish();
}

static void __job_service_start_cb(job_info_h job_info, void *user_data)
{
	/* Nothing */
}

static void __job_service_stop_cb(job_info_h job_info, void *user_data)
{
	/* Nothing */
}

/**
 * @function    utc_job_scheduler_service_add_p
 * @since_tizen 4.0
 * @description Adds job service handler for receiving the information of the scheduled job.
 * @scenario    Calls the job_scheduler_service_add().
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_scheduler_service_add_p(void)
{
	int ret;
	job_service_callback_s callbacks = {
		.start = __job_service_start_cb,
		.stop = __job_service_stop_cb
	};

	ret = job_scheduler_service_add(JOB_ID, &callbacks, NULL, &job_service);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_add_n1
 * @since_tizen 4.0
 * @description Adds job service handler for receiving the information of the scheduled job.
 * @scenario    Calls the job_scheduler_service_add() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_service_add_n1(void)
{
	int ret;

	ret = job_scheduler_service_add(JOB_ID, NULL, NULL, &job_service);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_add_n2
 * @since_tizen 4.0
 * @description Adds job service handler for receiving the information of the scheduled job.
 * @scenario    Calls the job_scheduler_service_add() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_service_add_n2(void)
{
	int ret;
	job_service_callback_s callbacks = {
		.start = __job_service_start_cb,
		.stop = __job_service_stop_cb
	};

	ret = job_scheduler_service_add(NULL, &callbacks, NULL, &job_service);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_add_n3
 * @since_tizen 4.0
 * @description Adds job service handler for receiving the information of the scheduled job.
 * @scenario    Calls the job_scheduler_service_add() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_service_add_n3(void)
{
	int ret;
	job_service_callback_s callbacks = {
		.start = NULL,
		.stop = __job_service_stop_cb
	};

	ret = job_scheduler_service_add(JOB_ID, &callbacks, NULL, &job_service);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_add_n4
 * @since_tizen 4.0
 * @description Adds job service handler for receiving the information of the scheduled job.
 * @scenario    Calls the job_scheduler_service_add() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_service_add_n4(void)
{
	int ret;
	job_service_callback_s callbacks = {
		.start = __job_service_start_cb,
		.stop = NULL
	};

	ret = job_scheduler_service_add(JOB_ID, &callbacks, NULL, &job_service);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_add_n5
 * @since_tizen 4.0
 * @description Adds job service handler for receiving the information of the scheduled job.
 * @scenario    Calls the job_scheduler_service_add() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_service_add_n5(void)
{
	int ret;
	job_service_callback_s callbacks = {
		.start = NULL,
		.stop = NULL
	};

	ret = job_scheduler_service_add(JOB_ID, &callbacks, NULL, &job_service);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_add_n6
 * @since_tizen 4.0
 * @description Adds job service handler for receiving the information of the scheduled job.
 * @scenario    Calls the job_scheduler_service_add() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_service_add_n6(void)
{
	int ret;
	job_service_callback_s callbacks = {
		.start = __job_service_start_cb,
		.stop = __job_service_stop_cb
	};

	ret = job_scheduler_service_add(JOB_ID, &callbacks, NULL, NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_add_n7
 * @since_tizen 4.0
 * @description Adds job service handler for receiving the information of the scheduled job.
 * @scenario    Calls the job_scheduler_service_add() without calling the job_scheduler_init().
 *              Checks whether the return value is JOB_ERROR_NOT_INITIALIZED or NOT.
 */
int utc_job_scheduler_service_add_n7(void)
{
	int ret;
	job_service_callback_s callbacks = {
		.start = __job_service_start_cb,
		.stop = __job_service_stop_cb
	};

	ret = job_scheduler_service_add(JOB_ID, &callbacks, NULL, &job_service);
	assert_eq(ret, JOB_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_remove_p_startup
 * @description Initializes the job scheduler and adds the job service handler for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_service_remove_p_startup(void)
{
	int ret;
	job_service_callback_s callbacks = {
		.start = __job_service_start_cb,
		.stop = __job_service_stop_cb
	};

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_scheduler_service_add(JOB_ID, &callbacks, NULL, &job_service);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to add job service");
}

/**
 * @function    utc_job_scheduler_service_remove_p_cleanup
 * @description Sets NULL to the job_service and finalizes the job scheduler.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_service_remove_p_cleanup(void)
{
	job_service = NULL;
	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_service_remove_p
 * @since_tizen 4.0
 * @description Removes registered job service handler.
 * @scenario    Calls the job_scheduler_service_remove().
 *              Checks whether the return value is JOB_ERROR_NONE or NOT.
 */
int utc_job_scheduler_service_remove_p(void)
{
	int ret;

	ret = job_scheduler_service_remove(job_service);
	assert_eq(ret, JOB_ERROR_NONE);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_remove_n1
 * @since_tizen 4.0
 * @description Removes registered job service handler.
 * @scenario    Calls the job_scheduler_service_remove() with invalid parameter.
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_service_remove_n1(void)
{
	int ret;

	ret = job_scheduler_service_remove(NULL);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @function    utc_job_scheduler_service_remove_n2_startup
 * @description Initializes the job scheduler, adds the job service handler
 *              and finalizes the job scheduler for TEST.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_service_remove_n2_startup(void)
{
	int ret;
	job_service_callback_s callbacks = {
		.start = __job_service_start_cb,
		.stop = __job_service_stop_cb
	};

	ret = job_scheduler_init();
	if (ret != JOB_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to initialize job scheduler");
		return;
	}

	ret = job_scheduler_service_add(JOB_ID, &callbacks, NULL, &job_service);
	if (ret != JOB_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to add job service");

	job_scheduler_finish();
}

/**
 * @function    utc_job_scheduler_service_remove_n2_cleanup
 * @description Sets NULL to the job_service.
 * @parameter   N/A
 * @return      N/A
 */
void utc_job_scheduler_service_remove_n2_cleanup(void)
{
	job_service = NULL;
}

/**
 * @function    utc_job_scheduler_service_remove_n2
 * @since_tizen 4.0
 * @description Removes registered job service handler.
 * @scenario    Calls the job_scheduler_service_remove() after calling the job_scheduler_finish().
 *              Checks whether the return value is JOB_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_job_scheduler_service_remove_n2(void)
{
	int ret;

	ret = job_scheduler_service_remove(job_service);
	assert_eq(ret, JOB_ERROR_INVALID_PARAMETER);

	return 0;
}
