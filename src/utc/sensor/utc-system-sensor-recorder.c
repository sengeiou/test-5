//
// Copyright (c) 2016 Samsung Electronics Co., Ltd.
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
#include <sensor.h>
#include <glib.h>
#include <string.h>
#include <system_info.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define TIME_1_HOUR_SEC 3600
#define TIME_1_DAY_SEC (TIME_1_HOUR_SEC * 24)
#define TIME_1_MONTH_SEC (TIME_1_DAY_SEC * 30)

#define SKIP_IF_NOT_SUPPORTED(error) \
if (!g_is_supported) { \
	PRINT_UTC_LOG("Sensor recorder is not supported."); \
	return 0; \
}

static sensor_type_e sensor_types[] = {
	SENSOR_ACCELEROMETER,                    /**< Accelerometer */
	SENSOR_GRAVITY,                          /**< Gravity sensor */
	SENSOR_LINEAR_ACCELERATION,              /**< Linear acceleration sensor */
	SENSOR_MAGNETIC,                         /**< Magnetic sensor */
	SENSOR_ROTATION_VECTOR,                  /**< Rotation Vector sensor */
	SENSOR_ORIENTATION,                      /**< Orientation sensor */
	SENSOR_GYROSCOPE,                        /**< Gyroscope sensor */
	SENSOR_LIGHT,                            /**< Light sensor */
	SENSOR_PRESSURE,                         /**< Pressure sensor */
	SENSOR_ULTRAVIOLET,                      /**< Ultraviolet sensor */
	SENSOR_TEMPERATURE,                      /**< Temperature sensor */
	SENSOR_HUMIDITY,                         /**< Humidity sensor */
	SENSOR_HRM,                              /**< Heart Rate Monitor sensor */
	SENSOR_HRM_LED_GREEN,                    /**< HRM (LED Green) sensor */
	SENSOR_HRM_LED_IR,                       /**< HRM (LED IR) sensor */
	SENSOR_HRM_LED_RED,                      /**< HRM (LED RED) sensor */
	SENSOR_GYROSCOPE_UNCALIBRATED,           /**< Uncalibrated Gyroscope sensor (Since Tizen 2.4) */
	SENSOR_GEOMAGNETIC_UNCALIBRATED,         /**< Uncalibrated Geomagnetic sensor (Since Tizen 2.4) */
	SENSOR_GYROSCOPE_ROTATION_VECTOR,        /**< Gyroscope-based rotation vector sensor (Since Tizen 2.4) */
	SENSOR_GEOMAGNETIC_ROTATION_VECTOR,      /**< Geomagnetic-based rotation vector sensor (Since Tizen 2.4) */
	SENSOR_GYROSCOPE_ORIENTATION,            /**< Orientation sensor based on gyroscope rotation vector Since 6.5 */
	SENSOR_GEOMAGNETIC_ORIENTATION,          /**< Orientation sensor based on geomagnetic rotation vector Since 6.5 */
	SENSOR_HUMAN_PEDOMETER,                  /**< Pedometer
	                                              @if MOBILE (Since 3.0) @elseif WEARABLE (Since 2.3.2) @endif
	                                              @n Privilege : http://tizen.org/privilege/healthinfo */
	SENSOR_HUMAN_SLEEP_MONITOR,              /**< Sleep monitor (Since 3.0)
	                                              @if MOBILE (Since 3.0) @elseif WEARABLE (Since 2.3.2) @endif
	                                              @n Privilege : http://tizen.org/privilege/healthinfo */
	SENSOR_HUMAN_SLEEP_DETECTOR,             /**< Sleep detector (Since 3.0)
	                                              @if MOBILE (Since 3.0) @elseif WEARABLE (Since 2.3.2) @endif
	                                              @n Privilege : http://tizen.org/privilege/healthinfo */
	SENSOR_HUMAN_STRESS_MONITOR,             /**< Stress monitor (Since 3.0)
	                                              @if MOBILE (Since 3.0) @elseif WEARABLE (Since 2.3.2) @endif
	                                              @n Privilege : http://tizen.org/privilege/healthinfo */
	SENSOR_HRM_BATCH,                        /**< Heart Rate Monitor Batch sensor */
	SENSOR_HRM_LED_GREEN_BATCH,              /**< HRM (LED Green) Batch sensor */
};

static char* sensor_features[] = {
	"http://tizen.org/feature/sensor.accelerometer",
	"http://tizen.org/feature/sensor.gravity",
	"http://tizen.org/feature/sensor.linear_acceleration",
	"http://tizen.org/feature/sensor.magnetometer",
	"http://tizen.org/feature/sensor.rotation_vector",
	"http://tizen.org/feature/sensor.tiltmeter",
	"http://tizen.org/feature/sensor.gyroscope",
	"http://tizen.org/feature/sensor.photometer",
	"http://tizen.org/feature/sensor.barometer",
	"http://tizen.org/feature/sensor.ultraviolet",
	"http://tizen.org/feature/sensor.temperature",
	"http://tizen.org/feature/sensor.humidity",
	"http://tizen.org/feature/sensor.heart_rate_monitor",
	"http://tizen.org/feature/sensor.heart_rate_monitor.led_green",
	"http://tizen.org/feature/sensor.heart_rate_monitor.led_ir",
	"http://tizen.org/feature/sensor.heart_rate_monitor.led_red",
	"http://tizen.org/feature/sensor.gyroscope.uncalibrated",
	"http://tizen.org/feature/sensor.magnetometer.uncalibrated",
	"http://tizen.org/feature/sensor.gyroscope_rotation_vector",
	"http://tizen.org/feature/sensor.geomagnetic_rotation_vector",
	"http://tizen.org/feature/sensor.gyroscope_orientation",
	"http://tizen.org/feature/sensor.geomagnetic_orientation",
	"http://tizen.org/feature/sensor.pedometer",
	"http://tizen.org/feature/sensor.sleep_monitor",
	"http://tizen.org/feature/sensor.sleep_monitor",
	"http://tizen.org/feature/sensor.stress_monitor",
	"http://tizen.org/feature/sensor.heart_rate_monitor.batch",
	"http://tizen.org/feature/sensor.heart_rate_monitor.led_green.batch",
};

static GMainLoop* g_mainloop = NULL;
static bool g_called = false;
static bool g_is_supported = false;

static int g_read_time_error_p = SENSOR_ERROR_NONE;
static int g_read_time_error_n = SENSOR_ERROR_NONE;
static int g_read_int_error_p = SENSOR_ERROR_NONE;
static int g_read_int_error_n = SENSOR_ERROR_NONE;
static int g_read_double_error_p = SENSOR_ERROR_NONE;
static int g_read_double_error_n = SENSOR_ERROR_NONE;

static bool sensor_supported[30];
static bool sensor_recorder_supported[30];
static int sensor_count;

static bool recorder_async_cb(sensor_type_e type, sensor_recorder_data_h data, int remains, sensor_error_e error, void *user_data)
{
	if (error == SENSOR_ERROR_NONE || error == SENSOR_ERROR_NO_DATA)
		g_called = true;

	if (remains == 0) {
		if (g_main_loop_is_running(g_mainloop))
			g_main_loop_quit(g_mainloop);
	}

	return true;
}

static bool recorder_sync_cb(sensor_type_e type, sensor_recorder_data_h data, int remains, sensor_error_e error, void *user_data)
{
	if (error != SENSOR_ERROR_NONE)
		return true;

	g_called = true;

	return true;
}

static bool recorder_read_sync_cb(sensor_type_e type, sensor_recorder_data_h data, int remains, sensor_error_e error, void *user_data)
{
	time_t start, end;
	int val_int;
	double val_double;

	if (error != SENSOR_ERROR_NONE)
		return true;

	g_called = true;

	g_read_time_error_p |= sensor_recorder_data_get_time(data, &start, &end);

	if (type == SENSOR_HUMAN_PEDOMETER) {
		g_read_int_error_p |= sensor_recorder_data_get_int(data, SENSOR_RECORDER_DATA_STEPS, &val_int);
		g_read_int_error_p |= sensor_recorder_data_get_int(data, SENSOR_RECORDER_DATA_WALK_STEPS, &val_int);
		g_read_int_error_p |= sensor_recorder_data_get_int(data, SENSOR_RECORDER_DATA_RUN_STEPS, &val_int);

		g_read_double_error_p |= sensor_recorder_data_get_double(data, SENSOR_RECORDER_DATA_DISTANCE, &val_double);
		g_read_double_error_p |= sensor_recorder_data_get_double(data, SENSOR_RECORDER_DATA_CALORIE, &val_double);
	}

	if (type == SENSOR_HRM) {
		g_read_int_error_p |= sensor_recorder_data_get_int(data, SENSOR_RECORDER_DATA_HEART_RATE, &val_int);
	}

	if (type == SENSOR_HUMAN_SLEEP_MONITOR || type == SENSOR_HUMAN_SLEEP_DETECTOR) {
		g_read_int_error_p |= sensor_recorder_data_get_int(data, SENSOR_RECORDER_DATA_SLEEP_STATE, &val_int);
	}

	g_read_time_error_n |= sensor_recorder_data_get_time(NULL, &start, &end);
	g_read_time_error_n |= sensor_recorder_data_get_time(data, NULL, &end);
	g_read_time_error_n |= sensor_recorder_data_get_time(data, &start, NULL);
	g_read_int_error_n |= sensor_recorder_data_get_int(NULL, SENSOR_RECORDER_DATA_STEPS, &val_int);
	g_read_int_error_n |= sensor_recorder_data_get_int(data, -1, &val_int);
	g_read_int_error_n |= sensor_recorder_data_get_int(data, SENSOR_RECORDER_DATA_STEPS, NULL);
	g_read_double_error_n |= sensor_recorder_data_get_double(NULL, SENSOR_RECORDER_DATA_STEPS, &val_double);
	g_read_double_error_n |= sensor_recorder_data_get_double(data, -1, &val_double);
	g_read_double_error_n |= sensor_recorder_data_get_double(data, SENSOR_RECORDER_DATA_STEPS, NULL);

	return true;
}

void utc_system_sensor_recorder_startup(void)
{
	int i;
	int error = SENSOR_ERROR_NONE;
	bool supported;
	sensor_recorder_option_h option;

	sensor_count = ARRAY_SIZE(sensor_types);

	for (i = 0; i < sensor_count; ++i) {
		system_info_get_platform_bool(sensor_features[i], &sensor_supported[i]);

		sensor_recorder_is_supported(sensor_types[i], &sensor_recorder_supported[i]);
		g_is_supported |= sensor_recorder_supported[i];
	}

	g_mainloop = g_main_loop_new(NULL, FALSE);
}

void utc_system_sensor_recorder_cleanup(void)
{
	if (!g_mainloop)
		return;

	g_main_loop_quit(g_mainloop);
	g_main_loop_unref(g_mainloop);
	g_mainloop = NULL;
}

int utc_system_sensor_recorder_is_supported_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int supported = false;
	int i;

	for (i = 0; i < sensor_count; ++i) {
		error = sensor_recorder_is_supported(sensor_types[i], &supported);
		assert_eq(error, SENSOR_ERROR_NONE);

		if (!sensor_supported[i])
			assert_eq(supported, false);
	}

	return 0;
}

int utc_system_sensor_recorder_is_supported_n(void)
{
	int error = SENSOR_ERROR_NONE;
	bool supported = false;

	error = sensor_recorder_is_supported(SENSOR_HUMAN_PEDOMETER, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	error = sensor_recorder_is_supported(-3, &supported);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_system_sensor_recorder_start_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;

	for (i = 0; i < sensor_count; ++i) {
		if (!sensor_recorder_supported[i])
			continue;

		error = sensor_recorder_start(sensor_types[i], NULL);
		assert_eq(error, SENSOR_ERROR_NONE);

		error = sensor_recorder_stop(sensor_types[i]);
		assert_eq(error, SENSOR_ERROR_NONE);
	}

	return 0;
}

int utc_system_sensor_recorder_start_n(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;

	error = sensor_recorder_start(-1, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	for (i = 0; i < sensor_count; ++i) {
		if (sensor_recorder_supported[i])
			continue;

		error = sensor_recorder_start(sensor_types[i], NULL);
		assert_eq(error, SENSOR_ERROR_NOT_SUPPORTED);

		error = sensor_recorder_stop(sensor_types[i]);
		assert_eq(error, SENSOR_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_system_sensor_recorder_stop_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;

	for (i = 0; i < sensor_count; ++i) {
		if (!sensor_recorder_supported[i])
			continue;

		error = sensor_recorder_start(sensor_types[i], NULL);
		assert_eq(error, SENSOR_ERROR_NONE);

		error = sensor_recorder_stop(sensor_types[i]);
		assert_eq(error, SENSOR_ERROR_NONE);
	}

	return 0;
}

int utc_system_sensor_recorder_stop_n(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;

	error = sensor_recorder_stop(-1);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	for (i = 0; i < sensor_count; ++i) {
		if (sensor_recorder_supported[i])
			continue;

		error = sensor_recorder_start(sensor_types[i], NULL);
		assert_eq(error, SENSOR_ERROR_NOT_SUPPORTED);

		error = sensor_recorder_stop(sensor_types[i]);
		assert_eq(error, SENSOR_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_system_sensor_recorder_create_option_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_recorder_option_h option;

	error = sensor_recorder_create_option(&option);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_recorder_destroy_option(option);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

int utc_system_sensor_recorder_create_option_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_recorder_create_option(NULL);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_system_sensor_recorder_destroy_option_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_recorder_option_h option;

	error = sensor_recorder_create_option(&option);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_recorder_destroy_option(option);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

int utc_system_sensor_recorder_destroy_option_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_recorder_destroy_option(NULL);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_system_sensor_recorder_option_set_int_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_recorder_option_h option;

	error = sensor_recorder_create_option(&option);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_recorder_option_set_int(option, SENSOR_RECORDER_OPTION_INTERVAL, SENSOR_RECORDER_INTERVAL_10_MINUTES);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_recorder_destroy_option(option);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

int utc_system_sensor_recorder_option_set_int_n(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_recorder_option_h option;

	error = sensor_recorder_create_option(&option);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_recorder_option_set_int(NULL, SENSOR_RECORDER_OPTION_INTERVAL, SENSOR_RECORDER_INTERVAL_10_MINUTES);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	error = sensor_recorder_option_set_int(option, -1, SENSOR_RECORDER_INTERVAL_10_MINUTES);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_system_sensor_recorder_create_query_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_recorder_query_h query;

	error = sensor_recorder_create_query(&query);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_recorder_destroy_query(query);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

int utc_system_sensor_recorder_create_query_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_recorder_create_query(NULL);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_system_sensor_recorder_destroy_query_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_recorder_query_h query;

	error = sensor_recorder_create_query(&query);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_recorder_destroy_query(query);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

int utc_system_sensor_recorder_destroy_query_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_recorder_destroy_query(NULL);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_system_sensor_recorder_query_set_int_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_recorder_query_h query;

	error = sensor_recorder_create_query(&query);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_10_MINUTES);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_recorder_destroy_query(query);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

int utc_system_sensor_recorder_query_set_int_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_recorder_query_set_int(NULL, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_10_MINUTES);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_system_sensor_recorder_query_set_time_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_recorder_query_h query;
	time_t now;
	time_t start, end;
	time_t anchor;

	error = sensor_recorder_create_query(&query);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_NONE);

	now = time(NULL);

	/* start time : 1 months ago */
	start = now - TIME_1_MONTH_SEC;
	/* end time : now */
	end = now;
	/* anchor time : 7 AM */
	anchor = 7 * TIME_1_HOUR_SEC;

	error = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	error = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	error = sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);

	error = sensor_recorder_destroy_query(query);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

int utc_system_sensor_recorder_query_set_time_n(void)
{
	int error = SENSOR_ERROR_NONE;
	time_t now;

	now = time(NULL);

	error = sensor_recorder_query_set_time(NULL, SENSOR_RECORDER_QUERY_START_TIME, now);

	SKIP_IF_NOT_SUPPORTED(error);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

int utc_system_sensor_recorder_read_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;

	sensor_recorder_create_query(&query);

	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);

	for (i = 0; i < sensor_count; ++i) {
		if (!sensor_recorder_supported[i])
			continue;

		g_called = false;

		error = sensor_recorder_read(sensor_types[i], query, recorder_async_cb, NULL);
		assert_eq(error, SENSOR_ERROR_NONE);

		g_main_loop_run(g_mainloop);

		assert(g_called);
	}

	sensor_recorder_destroy_query(query);

	return 0;
}

int utc_system_sensor_recorder_read_n(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_recorder_query_h query;

	sensor_recorder_create_query(&query);

	error = sensor_recorder_read(-1, query, recorder_async_cb, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	error = sensor_recorder_read(SENSOR_HUMAN_PEDOMETER, NULL, recorder_async_cb, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	error = sensor_recorder_read(SENSOR_HUMAN_PEDOMETER, query, NULL, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	sensor_recorder_destroy_query(query);

	return 0;
}

int utc_system_sensor_recorder_read_sync_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;

	sensor_recorder_create_query(&query);

	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);

	for (i = 0; i < sensor_count; ++i) {
		if (!sensor_recorder_supported[i])
			continue;

		g_called = false;

		error = sensor_recorder_read_sync(sensor_types[i], query, recorder_sync_cb, NULL);
		if (error == SENSOR_ERROR_NO_DATA)
			continue;

		assert_eq(error, SENSOR_ERROR_NONE);
		assert(g_called);
	}

	sensor_recorder_destroy_query(query);

	return 0;
}

int utc_system_sensor_recorder_read_sync_n(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_recorder_query_h query;

	sensor_recorder_create_query(&query);

	error = sensor_recorder_read_sync(-1, query, recorder_async_cb, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	error = sensor_recorder_read_sync(SENSOR_HUMAN_PEDOMETER, NULL, recorder_async_cb, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	error = sensor_recorder_read_sync(SENSOR_HUMAN_PEDOMETER, query, NULL, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	sensor_recorder_destroy_query(query);

	return 0;
}

int utc_system_sensor_recorder_data_get_time_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;

	sensor_recorder_create_query(&query);

	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);

	for (i = 0; i < sensor_count; ++i) {
		if (!sensor_recorder_supported[i])
			continue;

		g_called = false;
		g_read_time_error_p = SENSOR_ERROR_NONE;

		error = sensor_recorder_read_sync(sensor_types[i], query, recorder_read_sync_cb, NULL);
		if (error == SENSOR_ERROR_NO_DATA)
			continue;

		assert_eq(error, SENSOR_ERROR_NONE);
		assert(g_called);
		assert_eq(g_read_time_error_p, SENSOR_ERROR_NONE);
	}

	sensor_recorder_destroy_query(query);

	return 0;
}

int utc_system_sensor_recorder_data_get_time_n(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;

	sensor_recorder_create_query(&query);

	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);

	for (i = 0; i < sensor_count; ++i) {
		if (!sensor_recorder_supported[i])
			continue;

		g_called = false;
		g_read_time_error_n = SENSOR_ERROR_INVALID_PARAMETER;

		error = sensor_recorder_read_sync(sensor_types[i], query, recorder_read_sync_cb, NULL);
		if (error == SENSOR_ERROR_NO_DATA)
			continue;

		assert_eq(error, SENSOR_ERROR_NONE);
		assert(g_called);
		assert_eq(g_read_time_error_n, SENSOR_ERROR_INVALID_PARAMETER);
	}

	sensor_recorder_destroy_query(query);

	return 0;
}

int utc_system_sensor_recorder_data_get_int_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;

	sensor_recorder_create_query(&query);

	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);

	for (i = 0; i < sensor_count; ++i) {
		if (!sensor_recorder_supported[i])
			continue;

		g_called = false;
		g_read_int_error_p = SENSOR_ERROR_NONE;

		error = sensor_recorder_read_sync(sensor_types[i], query, recorder_read_sync_cb, NULL);
		if (error == SENSOR_ERROR_NO_DATA)
			continue;

		assert_eq(error, SENSOR_ERROR_NONE);
		assert(g_called);
		assert_eq(g_read_int_error_p, SENSOR_ERROR_NONE);
	}

	sensor_recorder_destroy_query(query);

	return 0;
}

int utc_system_sensor_recorder_data_get_int_n(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;

	sensor_recorder_create_query(&query);

	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);

	for (i = 0; i < sensor_count; ++i) {
		if (!sensor_recorder_supported[i])
			continue;

		g_called = false;
		g_read_int_error_n = SENSOR_ERROR_INVALID_PARAMETER;

		error = sensor_recorder_read_sync(sensor_types[i], query, recorder_read_sync_cb, NULL);
		if (error == SENSOR_ERROR_NO_DATA)
			continue;

		assert_eq(error, SENSOR_ERROR_NONE);
		assert(g_called);
		assert_eq(g_read_int_error_n, SENSOR_ERROR_INVALID_PARAMETER);
	}

	sensor_recorder_destroy_query(query);

	return 0;
}

int utc_system_sensor_recorder_data_get_double_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;

	sensor_recorder_create_query(&query);

	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);

	for (i = 0; i < sensor_count; ++i) {
		if (!sensor_recorder_supported[i])
			continue;

		g_called = false;
		g_read_double_error_p = SENSOR_ERROR_NONE;

		error = sensor_recorder_read_sync(sensor_types[i], query, recorder_read_sync_cb, NULL);
		if (error == SENSOR_ERROR_NO_DATA)
			continue;

		assert_eq(error, SENSOR_ERROR_NONE);
		assert(g_called);
		assert_eq(g_read_double_error_p, SENSOR_ERROR_NONE);
	}

	sensor_recorder_destroy_query(query);

	return 0;
}

int utc_system_sensor_recorder_data_get_double_n(void)
{
	int error = SENSOR_ERROR_NONE;
	int i;
	time_t now;
	time_t start, end;
	time_t anchor;
	sensor_recorder_query_h query;

	sensor_recorder_create_query(&query);

	now = time(NULL);
	start = now - TIME_1_MONTH_SEC;
	end = now;
	anchor = 7 * TIME_1_HOUR_SEC;

	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, start);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, end);
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, anchor);
	sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, SENSOR_RECORDER_INTERVAL_1_DAY);

	for (i = 0; i < sensor_count; ++i) {
		if (!sensor_recorder_supported[i])
			continue;

		g_called = false;
		g_read_double_error_n = SENSOR_ERROR_INVALID_PARAMETER;

		error = sensor_recorder_read_sync(sensor_types[i], query, recorder_read_sync_cb, NULL);
		if (error == SENSOR_ERROR_NO_DATA)
			continue;

		assert_eq(error, SENSOR_ERROR_NONE);
		assert(g_called);
		assert_eq(g_read_double_error_n, SENSOR_ERROR_INVALID_PARAMETER);
	}

	sensor_recorder_destroy_query(query);

	return 0;
}
