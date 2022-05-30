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
#include "utc-sensor-common.h"
#include <glib.h>
#include <string.h>
#include <system_info.h>

//& set: SensorBasic

#define TEST_STRING "TEST_TEST_TEST"
#define INTERVAL 20
#define WRONG_HANDLE -1

#define ARRAY_SIZE(list) (sizeof(list) / sizeof((list)[0]))

static GMainLoop* g_mainloop = NULL;
static bool g_called = false;

sensor_type_e types[] = {
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
	SENSOR_HRM_BATCH,                        /**< Heart Rate Monitor Batch sensor */
	SENSOR_HRM_LED_GREEN_BATCH               /**< HRM (LED Green) Batch sensor */
};

sensor_type_e manual_types[] = {
	SENSOR_PROXIMITY,                        /**< Proximity sensor */
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
};

const char *uri_types[] = {
	"http://tizen.org/sensor/general/accelerometer",                         /**< Accelerometer */
	"http://tizen.org/sensor/general/gravity",                               /**< Gravity sensor */
	"http://tizen.org/sensor/general/linear_acceleration",                   /**< Linear acceleration sensor */
	"http://tizen.org/sensor/general/magnetic",                              /**< Magnetic sensor */
	"http://tizen.org/sensor/general/rotation_vector",                       /**< Rotation Vector sensor */
	"http://tizen.org/sensor/general/orientation",                           /**< Orientation sensor */
	"http://tizen.org/sensor/general/gyroscope",                             /**< Gyroscope sensor */
	"http://tizen.org/sensor/general/light",                                 /**< Light sensor */
	"http://tizen.org/sensor/general/pressure",                              /**< Pressure sensor */
	"http://tizen.org/sensor/general/ultraviolet",                           /**< Ultraviolet sensor */
	"http://tizen.org/sensor/general/temperature",                           /**< Temperature sensor */
	"http://tizen.org/sensor/general/humidity",                              /**< Humidity sensor */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor",                 /**< Heart Rate Monitor sensor */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor.led_green",       /**< HRM (LED Green) sensor */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor.led_ir",          /**< HRM (LED IR) sensor */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor.led_red",         /**< HRM (LED RED) sensor */
	"http://tizen.org/sensor/general/gyroscope.uncalibrated",                /**< Uncalibrated Gyroscope sensor (Since Tizen 2.4) */
	"http://tizen.org/sensor/general/geomagnetic.uncalibrated",              /**< Uncalibrated Geomagnetic sensor (Since Tizen 2.4) */
	"http://tizen.org/sensor/general/gyroscope_rotation_vector",             /**< Gyroscope-based rotation vector sensor (Since Tizen 2.4) */
	"http://tizen.org/sensor/general/geomagnetic_rotation_vector",           /**< Geomagnetic-based rotation vector sensor (Since Tizen 2.4) */
	"http://tizen.org/sensor/general/gyroscope_orientation",                 /**< Orientation sensor based on gyroscope rotation vector Since 6.5 */
	"http://tizen.org/sensor/general/geomagnetic_orientation",               /**< Orientation sensor based on geomagnetic rotation vector Since 6.5 */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor.batch",           /**< Heart Rate Monitor Batch sensor */
	"http://tizen.org/sensor/healthinfo/heart_rate_monitor.led_green.batch", /**< HRM (LED Green) Batch sensor */
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
	"http://tizen.org/feature/sensor.heart_rate_monitor.batch",
	"http://tizen.org/feature/sensor.heart_rate_monitor.led_green.batch",
};

static char* manual_sensor_features[] = {
	"http://tizen.org/feature/sensor.proximity",
	"http://tizen.org/feature/sensor.pedometer",
	"http://tizen.org/feature/sensor.sleep_monitor",
	"http://tizen.org/feature/sensor.sleep_monitor",
	"http://tizen.org/feature/sensor.stress_monitor",
};

static bool sensor_supported[30];
static bool manual_sensor_supported[10];
static bool supported=false;

static gboolean timeout_func(gpointer data)
{
	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);

	return FALSE;
}

static void wait_callback(sensor_type_e type)
{
	int CB_TIMEOUT = 2000;
	if (type == SENSOR_HRM_BATCH || type == SENSOR_HRM_LED_GREEN_BATCH) {
		CB_TIMEOUT = 30000;
	}

	int nSensorTimeoutId = g_timeout_add(CB_TIMEOUT, timeout_func, g_mainloop);
	g_main_loop_run(g_mainloop);
	g_source_remove(nSensorTimeoutId);
}

static void test_accuracy_changed(sensor_h sensor, unsigned long long timestamp, sensor_data_accuracy_e accuracy, void* user_data)
{
	fprintf(stderr, "test_accuracy_cb was called.\n");

	char* ud = (char*) user_data;
	if(strcmp(ud, TEST_STRING) == 0) {
		g_called = true;
	}

	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);
}

static void test_callback(sensor_h sensor, sensor_event_s *event, void* user_data)
{
	fprintf(stderr, "test_callback was called\n");

	char* ud = (char*) user_data;
	if(strcmp(ud, TEST_STRING) == 0) {
		g_called = true;
	}

	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);
}

static void test_events_callback(sensor_h sensor, sensor_event_s events[], int events_count, void *user_data)
{
	fprintf(stderr, "test_callback was called\n");

	char* ud = (char*) user_data;
	if(strcmp(ud, TEST_STRING) == 0) {
		g_called = true;
	}

	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);
}

/**
 * @function		utc_system_sensor_basic_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_sensor_basic_startup(void)
{
	g_mainloop = g_main_loop_new(NULL, FALSE);

	int sensor_cnt = sizeof(types)/sizeof(sensor_type_e);
	int i;

	for( i=0;i<sensor_cnt;i++){
		system_info_get_platform_bool(sensor_features[i], &sensor_supported[i]);
		if(sensor_supported[i]) supported=true;
	}
}

/**
 * @function		utc_system_sensor_basic_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_sensor_basic_cleanup(void)
{
	g_main_loop_unref(g_mainloop);
}

/**
 * @testcase		utc_system_sensor_get_default_sensor_p
 * @since_tizen		2.3
 * @description		Gets a specific sensor handle.
 */
int utc_system_sensor_get_default_sensor_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);

		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}
	return 0;
}

/**
 * @testcase		utc_system_sensor_get_default_sensor_n
 * @since_tizen		2.3
 * @description		Gets a specific sensor handle with invalid parameter.
 */
int utc_system_sensor_get_default_sensor_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_get_default_sensor(-1, NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_default_sensor_by_uri_p
 * @since_tizen		4.0
 * @description		Gets a specific sensor handle.
 */
int utc_system_sensor_get_default_sensor_by_uri_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	int count;

	count = ARRAY_SIZE(uri_types);

	for (i = 0; i < count; ++i) {
		sensor_h sensor;
		error = sensor_get_default_sensor_by_uri(uri_types[i], &sensor);

		if (!sensor_supported[i])
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		else
			assert_eq(error, SENSOR_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_system_sensor_get_default_sensor_by_uri_n
 * @since_tizen		4.0
 * @description		Gets a specific sensor handle with invalid parameter.
 */
int utc_system_sensor_get_default_sensor_by_uri_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_get_default_sensor_by_uri(uri_types[0], NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_sensor_list_p
 * @since_tizen		2.3
 * @description		Gets a sensor list.
 */
int utc_system_sensor_get_sensor_list_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	sensor_h *list;
	int count;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		error = sensor_get_sensor_list(types[i], &list, &count);

		if(!sensor_supported[i]){
			assert_eq(error, SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			assert_eq(error, SENSOR_ERROR_NONE);
		}

		fprintf(stderr, "sensor[%d] passed", i);
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_sensor_list_n
 * @since_tizen		2.3
 * @description		Gets a sensor list with invalid parameter.
 */
int utc_system_sensor_get_sensor_list_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_get_sensor_list(-1, NULL, NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_sensor_list_by_uri_p
 * @since_tizen		4.0
 * @description		Gets a sensor list.
 */
int utc_system_sensor_get_sensor_list_by_uri_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	sensor_h *list;
	int count;
	int sensor_count;

	count = ARRAY_SIZE(uri_types);

	for (i = 0; i < count; ++i) {
		error = sensor_get_sensor_list_by_uri(uri_types[i], &list, &count);

		if (!sensor_supported[i])
			assert_eq(error, SENSOR_ERROR_NOT_SUPPORTED);
		else
			assert_eq(error, SENSOR_ERROR_NONE);

		fprintf(stderr, "sensor[%d] passed\n", i);
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_sensor_list_by_uri_n
 * @since_tizen		4.0
 * @description		Gets a sensor list with invalid parameter.
 */
int utc_system_sensor_get_sensor_list_by_uri_n(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_h *list = NULL;
	int count;

	error = sensor_get_sensor_list_by_uri(uri_types[0], NULL, &count);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	error = sensor_get_sensor_list_by_uri(uri_types[0], &list, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_is_wake_up_p
 * @since_tizen		3.0
 * @description		Checks whether a given sensor supports wake-up.
 */
int utc_system_sensor_is_wake_up_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	int type_count;
	bool wakeup;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_listener_h listener;
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);

		if (!sensor_supported[i]) {
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		} else {
			error = sensor_is_wake_up(sensor, &wakeup);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_is_wake_up_n
 * @since_tizen		3.0
 * @description		Checks whether a given sensor supports wake-up with invalid parameter.
 */
int utc_system_sensor_is_wake_up_n(void)
{
	int error = SENSOR_ERROR_NONE;
	bool wakeup;

	error = sensor_is_wake_up(NULL, &wakeup);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_create_listener_p
 * @since_tizen		2.3
 * @description		Creates a sensor listener.
 */
int utc_system_sensor_create_listener_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_listener_h listener;
	sensor_h sensor;
	int type_count;
	int i;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {

		error = sensor_get_default_sensor(types[i], &sensor);

		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

		}

		fprintf(stderr, "sensor[%d] passed", i);
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_create_listener_n
 * @since_tizen		2.3
 * @description		Creates a sensor listener with invalid parameter.
 */
int utc_system_sensor_create_listener_n(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_h sensor;

	sensor_get_default_sensor(SENSOR_ACCELEROMETER, &sensor);

	error = sensor_create_listener(sensor, NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_destroy_listener_p
 * @since_tizen		2.3
 * @description		Destroys the sensor handle and releases all its resources.
 */
int utc_system_sensor_destroy_listener_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_listener_h listener;
	sensor_h sensor;
	int type_count;
	int i;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {

		error = sensor_get_default_sensor(types[i], &sensor);

		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			assert_eq(error,SENSOR_ERROR_NONE);

			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_destroy_listener_n
 * @since_tizen		2.3
 * @description		Destroys the sensor handle and releases all its resources with invalid parameter.
 */
int utc_system_sensor_destroy_listener_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_destroy_listener(NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_start_p
 * @since_tizen		2.3
 * @description		Starts the sensor server for the given listener.
 */
int utc_system_sensor_listener_start_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_listener_h listener;
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);

		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{

			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_start_n
 * @since_tizen		2.3
 * @description		Starts the sensor server for the given listener with invalid parameter.
 */
int utc_system_sensor_listener_start_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_start(NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_stop_p
 * @since_tizen		2.3
 * @description		Stops the sensor server for the given listener.
 */
int utc_system_sensor_listener_stop_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_listener_h listener;
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{

			sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_stop_n
 * @since_tizen		2.3
 * @description		Stops the sensor server for the given listener with invalid parameter.
 */
int utc_system_sensor_listener_stop_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_stop(NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_event_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when a sensor event occurs.
 */
int utc_system_sensor_listener_set_event_cb_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);
	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;
		g_called = false;

		error = sensor_get_default_sensor(types[i], &sensor);

		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_event_cb(listener, INTERVAL, test_callback, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			sensor_listener_set_option(listener, SENSOR_OPTION_ALWAYS_ON);

			wait_callback(types[i]);

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_event_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			if (!g_called) {
				FPRINTF("[Line : %d][%s] sensor_listener_set_events_cb failed to invoke callback\n", __LINE__, sensor_type_e_to_str(types[i]));
			}
			assert(g_called);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_event_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when a sensor event occurs with invalid parameter.
 */
int utc_system_sensor_listener_set_event_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_set_event_cb(NULL, INTERVAL, test_callback, TEST_STRING);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	sensor_listener_h listener;
	sensor_h sensor;
	int backup;

	if (!sensor_supported[SENSOR_ACCELEROMETER])
		return 0;

	sensor_get_default_sensor(SENSOR_ACCELEROMETER, &sensor);

	sensor_create_listener(sensor, &listener);

	backup = *(int *)listener;
	*(int *)listener = WRONG_HANDLE;

	error = sensor_listener_set_event_cb(listener, INTERVAL, test_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_OPERATION_FAILED);

	*(int *)listener = backup;
	sensor_destroy_listener(listener);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_unset_event_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the sensor callback function.
 */
int utc_system_sensor_listener_unset_event_cb_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;
		g_called = false;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_event_cb(listener, INTERVAL, test_callback, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_event_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_unset_event_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the sensor callback function with invalid parameter.
 */
int utc_system_sensor_listener_unset_event_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_unset_event_cb(NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_events_cb_p
 * @since_tizen		5.5
 * @description		Registers a callback function to be invoked when a sensor events occurs.
 */
int utc_system_sensor_listener_set_events_cb_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);
	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;
		g_called = false;

		error = sensor_get_default_sensor(types[i], &sensor);

		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_events_cb(listener, test_events_callback, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			sensor_listener_set_option(listener, SENSOR_OPTION_ALWAYS_ON);

			wait_callback(types[i]);

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_events_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			if (!g_called) {
				FPRINTF("[Line : %d][%s] sensor_listener_set_events_cb failed to invoke callback\n", __LINE__, sensor_type_e_to_str(types[i]));
			}
			assert(g_called);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_events_cb_n
 * @since_tizen		5.5
 * @description		Registers a callback function to be invoked when a sensor event occurs with invalid parameter.
 */
int utc_system_sensor_listener_set_events_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_set_events_cb(NULL, test_events_callback, TEST_STRING);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	sensor_listener_h listener;
	sensor_h sensor;
	int backup;

	if (!sensor_supported[SENSOR_ACCELEROMETER])
		return 0;

	sensor_get_default_sensor(SENSOR_ACCELEROMETER, &sensor);

	sensor_create_listener(sensor, &listener);
	backup = *(int *)listener;
	*(int *)listener = WRONG_HANDLE;

	error = sensor_listener_set_events_cb(listener, test_events_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_OPERATION_FAILED);

	*(int *)listener = backup;
	sensor_destroy_listener(listener);

	return 0;
}


/**
 * @testcase		utc_system_sensor_listener_unset_events_cb_p
 * @since_tizen		5.5
 * @description		Unregisters the sensor callback function.
 */
int utc_system_sensor_listener_unset_events_cb_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;
		g_called = false;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_events_cb(listener, test_events_callback, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_events_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_unset_events_cb_n
 * @since_tizen		5.5
 * @description		Unregisters the sensor callback function with invalid parameter.
 */
int utc_system_sensor_listener_unset_events_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_unset_events_cb(NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_accuracy_cb_p
 * @since_tizen		2.3
 * @description		Registers an accuracy callback function to be invoked when the accuracy of a sensor has changed.
 */
int utc_system_sensor_listener_set_accuracy_cb_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;
		g_called = false;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{

			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_event_cb(listener, INTERVAL, test_callback, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_accuracy_cb(listener, test_accuracy_changed, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_accuracy_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_event_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_accuracy_cb_n
 * @since_tizen		2.3
 * @description		Registers an accuracy callback function to be invoked when the accuracy of a sensor has changed with invalid parameter.
 */
int utc_system_sensor_listener_set_accuracy_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_set_accuracy_cb(NULL, test_accuracy_changed, TEST_STRING);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	sensor_listener_h listener;
	sensor_h sensor;
	int backup;

	if (!sensor_supported[SENSOR_ACCELEROMETER])
		return 0;

	sensor_get_default_sensor(SENSOR_ACCELEROMETER, &sensor);

	sensor_create_listener(sensor, &listener);
	backup = *(int *)listener;
	*(int *)listener = WRONG_HANDLE;

	error = sensor_listener_set_accuracy_cb(listener, test_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_OPERATION_FAILED);

	*(int *)listener = backup;
	sensor_destroy_listener(listener);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_unset_accuracy_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the sensor accuracy changed callback function.
 */
int utc_system_sensor_listener_unset_accuracy_cb_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;
		g_called = false;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_event_cb(listener, INTERVAL, test_callback, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_accuracy_cb(listener, test_accuracy_changed, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_accuracy_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_event_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_unset_accuracy_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the sensor accuracy changed callback function with invalid parameter.
 */
int utc_system_sensor_listener_unset_accuracy_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_unset_accuracy_cb(NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}
/**
 * @testcase		utc_system_sensor_listener_read_data_p
 * @since_tizen		2.3
 * @description		Gets sensor data.
 */
int utc_system_sensor_listener_read_data_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;
		sensor_event_s event;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_event_cb(listener, INTERVAL, test_callback, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			sensor_listener_set_option(listener, SENSOR_OPTION_ALWAYS_ON);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			wait_callback(types[i]);

			error = sensor_listener_read_data(listener, &event);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_event_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_read_data_n
 * @since_tizen		2.3
 * @description		Gets sensor data with invalid parameter.
 */
int utc_system_sensor_listener_read_data_n(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_event_s event;

	error = sensor_listener_read_data(NULL, &event);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_interval_p
 * @since_tizen		2.3
 * @description		Changes the interval at sensor measurements.
 */
int utc_system_sensor_listener_set_interval_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;
		g_called = false;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			sensor_create_listener(sensor, &listener);

			error = sensor_listener_set_event_cb(listener, INTERVAL, test_callback, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_interval(listener, INTERVAL*2);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_event_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_interval_n
 * @since_tizen		2.3
 * @description		Changes the interval at sensor measurements with invalid parameter.
 */
int utc_system_sensor_listener_set_interval_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_set_interval(NULL, INTERVAL*2);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_max_batch_latency_p
 * @since_tizen		2.3
 * @description		Changes the max batch latency at sensor measurements.
 */
int utc_system_sensor_listener_set_max_batch_latency_p(void)
{
	int i = 0;
	int type_count;
	int max_batch_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;
		g_called = false;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			sensor_create_listener(sensor, &listener);

			error = sensor_listener_set_event_cb(listener, INTERVAL, test_callback, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_get_max_batch_count(sensor, &max_batch_count);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_max_batch_latency(listener, INTERVAL*20);

			if (max_batch_count == 0) {
				assert_eq(error, SENSOR_ERROR_NOT_SUPPORTED);
			} else {
				assert_eq(error, SENSOR_ERROR_NONE);
			}

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_event_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_max_batch_latency_n
 * @since_tizen		2.3
 * @description		Changes the max batch latency at sensor measurements with invalid parameter.
 */
int utc_system_sensor_listener_set_max_batch_latency_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_set_max_batch_latency(NULL, INTERVAL*20);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_attribute_int_p
 * @since_tizen		3.0
 * @description		Changes the attribute value for a given sensor.
 */
int utc_system_sensor_listener_set_attribute_int_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if (!sensor_supported[i]) {
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		} else {
			sensor_create_listener(sensor, &listener);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_attribute_int(listener, SENSOR_ATTRIBUTE_PAUSE_POLICY, 0);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_attribute_int_n
 * @since_tizen		3.0
 * @description		Changes the attribute value for a given sensor with invalid parameter.
 */
int utc_system_sensor_listener_set_attribute_int_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_set_attribute_int(NULL, SENSOR_ATTRIBUTE_PAUSE_POLICY, 0);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_read_data_list_p
 * @since_tizen		5.5
 * @description		Gets sensor data list.
 */
int utc_system_sensor_listener_read_data_list_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			sensor_event_s *events = NULL;
			int count = 0;
			error = sensor_create_listener(sensor, &listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_event_cb(listener, INTERVAL, test_callback, TEST_STRING);
			assert_eq(error, SENSOR_ERROR_NONE);

			sensor_listener_set_option(listener, SENSOR_OPTION_ALWAYS_ON);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			wait_callback(types[i]);

			error = sensor_listener_read_data_list(listener, &events, &count);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_unset_event_cb(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			free(events);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_read_data_list_n
 * @since_tizen		5.5
 * @description		Gets sensor data list.
 */
int utc_system_sensor_listener_read_data_list_n(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_event_s *events = NULL;
	int count = 0;

	error = sensor_listener_read_data_list(NULL, &events, &count);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_flush_p
 * @since_tizen		5.5
 * @description		flushes stored data of a sensor.
 */
int utc_system_sensor_listener_flush_p(void)
{
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		int error = SENSOR_ERROR_NONE;
		sensor_listener_h listener;
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if (!sensor_supported[i]) {
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		} else {
			sensor_create_listener(sensor, &listener);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_flush(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_destroy_listener(listener);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_flush_p
 * @since_tizen		5.5
 * @description		flushes stored data of a sensor.
 */
int utc_system_sensor_listener_flush_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_flush(NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_uri_p
 * @since_tizen		4.0
 * @description		Gets the uri of the sensor.
 */
int utc_system_sensor_get_uri_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	char *uri;
	sensor_h sensor;
	int count;

	count = ARRAY_SIZE(types);

	for (i = 0; i < count; ++i) {
		error = sensor_get_default_sensor(types[i], &sensor);

		if (!sensor_supported[i]) {
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		} else {
			error = sensor_get_uri(sensor, &uri);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_uri_n
 * @since_tizen		4.0
 * @description		Gets the uri of the sensor with invalid parameter.
 */
int utc_system_sensor_get_uri_n(void)
{
	int error = SENSOR_ERROR_NONE;
	char *uri;

	error = sensor_get_uri(NULL, &uri);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_name_p
 * @since_tizen		2.3
 * @description		Gets the name of the sensor.
 */
int utc_system_sensor_get_name_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	char *name;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_get_name(sensor, &name);
			assert_eq(error, SENSOR_ERROR_NONE);

			assert(name);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_name_n
 * @since_tizen		2.3
 * @description		Gets the name of the sensor with invalid parameter.
 */
int utc_system_sensor_get_name_n(void)
{
	int error = SENSOR_ERROR_NONE;
	char *name;

	error = sensor_get_name(NULL, &name);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_vendor_p
 * @since_tizen		2.3
 * @description		Gets the vendor of the sensor.
 */
int utc_system_sensor_get_vendor_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	char *vendor;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);

		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{

			error = sensor_get_vendor(sensor, &vendor);
			assert_eq(error, SENSOR_ERROR_NONE);

			assert(vendor);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_vendor_n
 * @since_tizen		2.3
 * @description		Gets the vendor of the sensor with invalid parameter.
 */
int utc_system_sensor_get_vendor_n(void)
{
	int error = SENSOR_ERROR_NONE;
	char *vendor;

	error = sensor_get_vendor(NULL, &vendor);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_type_p
 * @since_tizen		2.3
 * @description		Gets the type of the sensor.
 */
int utc_system_sensor_get_type_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	int type;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_get_type(sensor, &type);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_type_n
 * @since_tizen		2.3
 * @description		Gets the type of the sensor with invalid parameter.
 */
int utc_system_sensor_get_type_n(void)
{
	int error = SENSOR_ERROR_NONE;
	int type;

	error = sensor_get_type(NULL, &type);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_min_range_p
 * @since_tizen		2.3
 * @description		Gets the minimum range of the sensor.
 */
int utc_system_sensor_get_min_range_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	float min_range;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_get_min_range(sensor, &min_range);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_min_range_n
 * @since_tizen		2.3
 * @description		Gets the minimum range of the sensor with invalid parameter.
 */
int utc_system_sensor_get_min_range_n(void)
{
	int error = SENSOR_ERROR_NONE;
	float min_range;

	error = sensor_get_min_range(NULL, &min_range);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_max_range_p
 * @since_tizen		2.3
 * @description		Gets the maximum range of the sensor.
 */
int utc_system_sensor_get_max_range_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	float max_range;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_get_max_range(sensor, &max_range);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_max_range_n
 * @since_tizen		2.3
 * @description		Gets the maximum range of the sensor with invalid parameter.
 */
int utc_system_sensor_get_max_range_n(void)
{
	int error = SENSOR_ERROR_NONE;
	float max_range;

	error = sensor_get_max_range(NULL, &max_range);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_resolution_p
 * @since_tizen		2.3
 * @description		Gets the resolution of the sensor.
 */
int utc_system_sensor_get_resolution_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	float resolution;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_get_resolution(sensor, &resolution);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_resolution_n
 * @since_tizen		2.3
 * @description		Gets the resolution of the sensor with invalid parameter.
 */
int utc_system_sensor_get_resolution_n(void)
{
	int error = SENSOR_ERROR_NONE;
	float resolution;

	error = sensor_get_resolution(NULL, &resolution);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_min_interval_p
 * @since_tizen		2.3
 * @description		Gets the minimun interval of the sensor.
 */
int utc_system_sensor_get_min_interval_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	int min_interval;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_get_min_interval(sensor, &min_interval);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_min_interval_n
 * @since_tizen		2.3
 * @description		Gets the minimun interval of the sensor with invalid parameter.
 */
int utc_system_sensor_get_min_interval_n(void)
{
	int error = SENSOR_ERROR_NONE;
	int min_interval;

	error = sensor_get_min_interval(NULL, &min_interval);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_fifo_count_p
 * @since_tizen		2.3
 * @description		Gets the fifo count of the sensor.
 */
int utc_system_sensor_get_fifo_count_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	int fifo_count;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_get_fifo_count(sensor, &fifo_count);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_fifo_count_n
 * @since_tizen		2.3
 * @description		Gets the fifo count of the sensor with invalid parameter.
 */
int utc_system_sensor_get_fifo_count_n(void)
{
	int error = SENSOR_ERROR_NONE;
	int fifo_count;

	error = sensor_get_fifo_count(NULL, &fifo_count);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_max_batch_count_p
 * @since_tizen		2.3
 * @description		Gets the maximum batch count of the sensor.
 */
int utc_system_sensor_get_max_batch_count_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	int max_batch_count;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			error = sensor_get_max_batch_count(sensor, &max_batch_count);
			assert_eq(error, SENSOR_ERROR_NONE);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_get_max_batch_count_n
 * @since_tizen		2.3
 * @description		Gets the maximum batch count of the sensor with invalid parameter.
 */
int utc_system_sensor_get_max_batch_count_n(void)
{
	int error = SENSOR_ERROR_NONE;
	int max_batch_count;

	error = sensor_get_max_batch_count(NULL, &max_batch_count);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_option_p
 * @since_tizen		2.3
 * @description		Changes the option of the sensor.
 */
int utc_system_sensor_listener_set_option_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		sensor_listener_h listener;
		sensor_h sensor;

		error = sensor_get_default_sensor(types[i], &sensor);
		if(!sensor_supported[i]){
			assert_eq(error,SENSOR_ERROR_NOT_SUPPORTED);
		}
		else{
			sensor_create_listener(sensor, &listener);

			error = sensor_listener_start(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_set_option(listener, SENSOR_OPTION_ALWAYS_ON);
			assert_eq(error, SENSOR_ERROR_NONE);

			error = sensor_listener_stop(listener);
			assert_eq(error, SENSOR_ERROR_NONE);

			sensor_destroy_listener(listener);
		}
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_listener_set_option_n
 * @since_tizen		2.3
 * @description		Changes the option of the sensor with invalid parameter.
 */
int utc_system_sensor_listener_set_option_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_set_option(NULL, SENSOR_OPTION_ALWAYS_ON);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_is_supported_p
 * @since_tizen		2.3
 * @description		Checks whether a given sensor type is available on a device.
 */
int utc_system_sensor_is_supported_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	bool support = false;
	int type_count;

	type_count = sizeof(types) / sizeof(sensor_type_e);

	for (i = 0; i < type_count; i++) {
		error = sensor_is_supported(types[i], &support);
		assert_eq(error, SENSOR_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_is_supported_n
 * @since_tizen		2.3
 * @description		Checks whether a given sensor type is available on a device with invalid parameter.
 */
int utc_system_sensor_is_supported_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_is_supported(-1, NULL);

	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_is_supported_by_uri_p
 * @since_tizen		4.0
 * @description		Checks whether a given sensor URI is available on a device.
 */
int utc_system_sensor_is_supported_by_uri_p(void)
{
	int error = SENSOR_ERROR_NONE;
	int i = 0;
	bool support = false;
	int count;

	count = ARRAY_SIZE(uri_types);

	for (i = 0; i < count; ++i) {
		error = sensor_is_supported_by_uri(uri_types[i], &support);
		assert_eq(error, SENSOR_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_system_sensor_is_supported_by_uri_n
 * @since_tizen		4.0
 * @description		Checks whether a given sensor URI is available on a device with invalid parameter.
 */
int utc_system_sensor_is_supported_by_uri_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_is_supported(-1, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}
