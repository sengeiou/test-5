/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All rights reserved.
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
 *
 */

#include <system_info.h>
#include <glib.h>
#include <dlog.h>
#include <user-awareness.h>

#include "utc-ua-common.h"

static int g_nCallbackRet = UA_ERROR_NONE;

static bool __ua_monitor_foreach_sensor_cb(ua_sensor_type_e sensor, void *user_data)
{
	g_nCallbackRet = UA_ERROR_NONE;
	return TRUE;
}

static void __ua_monitor_sensor_status_changed_cb(ua_monitor_h handle,
	ua_sensor_h sensor_handle, ua_sensor_type_e sensor_type,
	ua_sensor_report_e status, void *user_data)
{
}

static void __ua_monitor_scan_completed_cb(ua_active_scan_type_e result,
	ua_monitor_h handle, ua_device_h device_handle, void *user_data)
{
}

static void __ua_monitor_sensor_presence_detected_cb(int result,
	ua_monitor_h monitor, ua_sensor_type_e sensor, ua_service_h service_handle,
	ua_device_h device_handle, ua_sensor_h sensor_handle, void *user_data)
{
}

static void __ua_monitor_sensor_absence_detected_cb(int result,
	ua_monitor_h monitor, ua_service_h service_handle, ua_sensor_type_e sensor,
	ua_sensor_h sensor_handle, void *user_data)
{
}

int utc_ua_monitor_create_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_create(NULL);
		CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_create_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_create(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_destroy_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_destroy(NULL);
		CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_destroy_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_destroy(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_add_sensor_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_add_sensor(NULL, UA_SENSOR_WIFI);
		CHECK_RETURN("ua_monitor_add_sensor", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret = ua_monitor_add_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_add_sensor", ret, UA_ERROR_NONE);

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_add_sensor_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_add_sensor(NULL, UA_SENSOR_WIFI);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_add_sensor", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_add_sensor", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_remove_sensor_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_remove_sensor(NULL, UA_SENSOR_WIFI);
		CHECK_RETURN("ua_monitor_remove_sensor", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret = ua_monitor_add_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_add_sensor", ret, UA_ERROR_NONE);

	ret = ua_monitor_remove_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_remove_sensor", ret, UA_ERROR_NONE);

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_remove_sensor_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_remove_sensor(NULL, UA_SENSOR_WIFI);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_remove_sensor", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_remove_sensor", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_foreach_sensor_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_foreach_sensor(NULL, NULL, NULL);
		CHECK_RETURN("ua_monitor_foreach_sensor", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret = ua_monitor_add_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_add_sensor", ret, UA_ERROR_NONE);

	g_nCallbackRet = UA_ERROR_INVALID_PARAMETER;
	ret = ua_monitor_foreach_sensor(ua_mon_h, __ua_monitor_foreach_sensor_cb, NULL);
	CHECK_RETURN("ua_monitor_foreach_sensor", ret, UA_ERROR_NONE);

	ret = ua_monitor_remove_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_remove_sensor", ret, UA_ERROR_NONE);

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_foreach_sensor_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_foreach_sensor(NULL, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_foreach_sensor", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_foreach_sensor", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_is_sensor_available_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;
	bool available = false;

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_is_sensor_available(UA_SENSOR_WIFI, NULL);
		CHECK_RETURN("ua_monitor_foreach_sensor", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret = ua_monitor_is_sensor_available(UA_SENSOR_WIFI, &available);
	CHECK_RETURN("ua_monitor_is_sensor_available", ret, UA_ERROR_NONE);

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_is_sensor_available_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_is_sensor_available(UA_SENSOR_WIFI, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_is_sensor_available", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_is_sensor_available", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_set_sensor_status_changed_cb_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_set_sensor_status_changed_cb(NULL, NULL, NULL);
		CHECK_RETURN("ua_monitor_set_sensor_status_changed_cb", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret = ua_monitor_set_sensor_status_changed_cb(ua_mon_h, __ua_monitor_sensor_status_changed_cb, NULL);
	CHECK_RETURN("ua_monitor_set_sensor_status_changed_cb", ret, UA_ERROR_NONE);

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_set_sensor_status_changed_cb_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_set_sensor_status_changed_cb(NULL, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_set_sensor_status_changed_cb", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_set_sensor_status_changed_cb", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_unset_sensor_status_changed_cb_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_unset_sensor_status_changed_cb(NULL);
		CHECK_RETURN("ua_monitor_unset_sensor_status_changed_cb", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret = ua_monitor_unset_sensor_status_changed_cb(ua_mon_h);
	CHECK_RETURN("ua_monitor_unset_sensor_status_changed_cb", ret, UA_ERROR_NONE);

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_unset_sensor_status_changed_cb_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_unset_sensor_status_changed_cb(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_unset_sensor_status_changed_cb", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_unset_sensor_status_changed_cb", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_start_scan_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_start_scan(NULL, 0, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_start_scan", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_start_scan", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_stop_scan_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_stop_scan(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_stop_scan", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_stop_scan", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_start_presence_detection_p(void)
{
	int ret = UA_ERROR_NONE;
	int ret1 = UA_ERROR_NONE;
	int ret2 = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_start_presence_detection(NULL, NULL, 0, NULL, NULL);
		CHECK_RETURN("ua_monitor_start_presence_detection", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	PRINT_RETURN("UA_ERROR_ALREADY_REGISTERED", UA_ERROR_ALREADY_REGISTERED);

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret1 = ua_get_default_service(&service_h);
	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_create(service_str, &service_h);
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

		ret2 = ua_service_add(service_h);
		CHECK2_RETURN("ua_service_add", ret2, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);
	} else {
		CHECK_RETURN("ua_get_default_service", ret1, UA_ERROR_NONE);
	}

	ret = ua_monitor_add_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_add_sensor", ret, UA_ERROR_NONE);

	ret = ua_monitor_start_presence_detection(ua_mon_h, service_h,
		UA_DETECT_MODE_ALL_SENSORS, __ua_monitor_sensor_presence_detected_cb, NULL);
	CHECK_RETURN("ua_monitor_start_presence_detection", ret, UA_ERROR_NONE);

	ret = ua_monitor_stop_presence_detection(ua_mon_h);
	CHECK_RETURN("ua_monitor_stop_presence_detection", ret, UA_ERROR_NONE);

	ret = ua_monitor_remove_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_remove_sensor", ret, UA_ERROR_NONE);

	if (UA_ERROR_NONE == ret2) {
		ret = ua_service_remove(service_h);
		CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);
	}

	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_destroy(service_h);
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);
	}

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_start_presence_detection_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_start_presence_detection(NULL, NULL, 0, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_start_presence_detection", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_start_presence_detection", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_stop_presence_detection_p(void)
{
	int ret = UA_ERROR_NONE;
	int ret1 = UA_ERROR_NONE;
	int ret2 = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_stop_presence_detection(NULL);
		CHECK_RETURN("ua_monitor_stop_presence_detection", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret = ua_service_create(service_str, &service_h);
	CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

	ret1 = ua_get_default_service(&service_h);
	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_create(service_str, &service_h);
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

		ret2 = ua_service_add(service_h);
		CHECK2_RETURN("ua_service_add", ret2, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);
	} else {
		CHECK_RETURN("ua_get_default_service", ret1, UA_ERROR_NONE);
	}

	ret = ua_monitor_add_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_add_sensor", ret, UA_ERROR_NONE);

	ret = ua_monitor_start_presence_detection(ua_mon_h, service_h,
		UA_DETECT_MODE_ALL_SENSORS, __ua_monitor_sensor_presence_detected_cb, NULL);
	CHECK_RETURN("ua_monitor_start_presence_detection", ret, UA_ERROR_NONE);

	ret = ua_monitor_stop_presence_detection(ua_mon_h);
	CHECK_RETURN("ua_monitor_stop_presence_detection", ret, UA_ERROR_NONE);

	ret = ua_monitor_remove_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_remove_sensor", ret, UA_ERROR_NONE);

	if (UA_ERROR_NONE == ret2) {
		ret = ua_service_remove(service_h);
		CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);
	}

	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_destroy(service_h);
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);
	}

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_stop_presence_detection_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_stop_presence_detection(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_stop_presence_detection", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_stop_presence_detection", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_start_absence_detection_p(void)
{
	int ret = UA_ERROR_NONE;
	int ret1 = UA_ERROR_NONE;
	int ret2 = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_start_absence_detection(NULL, NULL, 0, NULL, NULL);
		CHECK_RETURN("ua_monitor_start_absence_detection", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret1 = ua_get_default_service(&service_h);
	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_create(service_str, &service_h);
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

		ret2 = ua_service_add(service_h);
		CHECK2_RETURN("ua_service_add", ret2, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);
	} else {
		CHECK_RETURN("ua_get_default_service", ret1, UA_ERROR_NONE);
	}

	ret = ua_monitor_add_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_add_sensor", ret, UA_ERROR_NONE);

	ret = ua_monitor_start_absence_detection(ua_mon_h, service_h,
		UA_DETECT_MODE_ALL_SENSORS, __ua_monitor_sensor_absence_detected_cb, NULL);
	CHECK_RETURN("ua_monitor_start_absence_detection", ret, UA_ERROR_NONE);

	ret = ua_monitor_stop_absence_detection(ua_mon_h);
	CHECK_RETURN("ua_monitor_stop_absence_detection", ret, UA_ERROR_NONE);

	ret = ua_monitor_remove_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_remove_sensor", ret, UA_ERROR_NONE);

	if (UA_ERROR_NONE == ret2) {
		ret = ua_service_remove(service_h);
		CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);
	}

	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_destroy(service_h);
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);
	}

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_start_absence_detection_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_start_absence_detection(NULL, NULL, 0, NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_start_absence_detection", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_start_absence_detection", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_stop_absence_detection_p(void)
{
	int ret = UA_ERROR_NONE;
	int ret1 = UA_ERROR_NONE;
	int ret2 = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;
	ua_service_h service_h = NULL;
	char service_str[] = {"ua.service.default"};

	if (!ua_is_feature_supported()) {
		ret = ua_monitor_stop_absence_detection(NULL);
		CHECK_RETURN("ua_monitor_stop_absence_detection", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret1 = ua_get_default_service(&service_h);
	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_create(service_str, &service_h);
		CHECK_RETURN("ua_service_create", ret, UA_ERROR_NONE);

		ret2 = ua_service_add(service_h);
		CHECK2_RETURN("ua_service_add", ret2, UA_ERROR_NONE, UA_ERROR_ALREADY_REGISTERED);
	} else {
		CHECK_RETURN("ua_get_default_service", ret1, UA_ERROR_NONE);
	}

	ret = ua_monitor_add_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_add_sensor", ret, UA_ERROR_NONE);

	ret = ua_monitor_start_absence_detection(ua_mon_h, service_h,
		UA_DETECT_MODE_ALL_SENSORS, __ua_monitor_sensor_absence_detected_cb, NULL);
	CHECK_RETURN("ua_monitor_start_absence_detection", ret, UA_ERROR_NONE);

	ret = ua_monitor_stop_absence_detection(ua_mon_h);
	CHECK_RETURN("ua_monitor_stop_absence_detection", ret, UA_ERROR_NONE);

	ret = ua_monitor_remove_sensor(ua_mon_h, UA_SENSOR_WIFI);
	CHECK_RETURN("ua_monitor_remove_sensor", ret, UA_ERROR_NONE);

	if (UA_ERROR_NONE == ret2) {
		ret = ua_service_remove(service_h);
		CHECK2_RETURN("ua_service_remove", ret, UA_ERROR_NONE, UA_ERROR_NOT_REGISTERED);
	}

	if (UA_ERROR_NONE != ret1) {
		ret = ua_service_destroy(service_h);
		CHECK_RETURN("ua_service_destroy", ret, UA_ERROR_NONE);
	}

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_stop_absence_detection_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_stop_absence_detection(NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_monitor_stop_absence_detection", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_stop_absence_detection", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
