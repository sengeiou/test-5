//
// Copyright (c) 2017 Samsung Electronics Co., Ltd.
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

#define TEST_STRING "TEST_TEST_TEST"
#define TEST_STRING_TERM "TERM"
#define INTERVAL 200
#define CB_TIMEOUT 2000

#define TEST_SENSOR_URI "http://samsung.com/sensor/general/test_sensor/test_sensor"
#define ARRAY_SIZE(list) (sizeof(list) / sizeof((list)[0]))

static GMainLoop* g_mainloop = NULL;
static bool g_called = false;

static gboolean timeout_func(gpointer data)
{
	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);

	return FALSE;
}

static void wait_callback(void)
{
	int nSensorTimeoutId = g_timeout_add(CB_TIMEOUT, timeout_func, g_mainloop);
	g_main_loop_run(g_mainloop);
	g_source_remove(nSensorTimeoutId);
}

static void test_callback(sensor_h sensor, sensor_event_s *event, void* user_data)
{
	fprintf(stderr, "test_callback was called\n");

	char *ud = (char *)user_data;
	if (strcmp(ud, TEST_STRING_TERM) == 0) {
		g_called = true;
		return;
	}

	if (strcmp(ud, TEST_STRING) == 0)
		g_called = true;

	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);
}

static void test_sensor_added_callback(const char *uri, void *user_data)
{
	fprintf(stderr, "test_callback was called\n");

	char *ud = (char *)user_data;
	if (strcmp(ud, TEST_STRING) == 0)
		g_called = true;

	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);
}

static void test_sensor_removed_callback(const char *uri, void *user_data)
{
	fprintf(stderr, "test_callback was called\n");

	char *ud = (char *)user_data;
	if (strcmp(ud, TEST_STRING) == 0)
		g_called = true;

	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);
}

static void test_start_callback(sensor_provider_h provider, void *user_data)
{
	fprintf(stderr, "test_callback was called\n");

	char *ud = (char *)user_data;
	if (strcmp(ud, TEST_STRING) == 0)
		g_called = true;

	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);
}

static void test_stop_callback(sensor_provider_h provider, void *user_data)
{
	fprintf(stderr, "test_callback was called\n");

	char *ud = (char *)user_data;
	if (strcmp(ud, TEST_STRING) == 0)
		g_called = true;

	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);
}

static void test_interval_changed_callback(sensor_provider_h provider,
		unsigned int interval_ms, void *user_data)
{
	fprintf(stderr, "test_callback was called\n");

	char *ud = (char *)user_data;
	if (strcmp(ud, TEST_STRING) == 0)
		g_called = true;

	if (g_main_loop_is_running(g_mainloop))
		g_main_loop_quit(g_mainloop);
}

/**
 * @function		utc_system_sensor_provider_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_sensor_provider_startup(void)
{
	g_mainloop = g_main_loop_new(NULL, FALSE);
}

/**
 * @function		utc_system_sensor_provider_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_sensor_provider_cleanup(void)
{
	g_main_loop_unref(g_mainloop);
}

/**
 * @testcase		utc_system_sensor_create_provider_p
 * @since_tizen		4.0
 * @description		Creates a sensor provider.
 */
int utc_system_sensor_create_provider_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_create_provider_n
 * @since_tizen		4.0
 * @description		Creates a sensor provider with invalid parameter.
 */
int utc_system_sensor_create_provider_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_create_provider(TEST_SENSOR_URI, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_destroy_provider_p
 * @since_tizen		4.0
 * @description		Destroys the sensor handle and releases all its resources.
 */
int utc_system_sensor_destroy_provider_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_destroy_provider_n
 * @since_tizen		4.0
 * @description		Destroys the sensor handle and releases all its resources with invalid parameter.
 */
int utc_system_sensor_destroy_provider_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_destroy_provider(NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_add_provider_p
 * @since_tizen		4.0
 * @description		Adds the sensor provider handle and releases all its resources.
 */
int utc_system_sensor_add_provider_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_remove_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_add_provider_n
 * @since_tizen		4.0
 * @description		Adds the sensor provider with invalid parameter.
 */
int utc_system_sensor_add_provider_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_add_provider(NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_remove_provider_p
 * @since_tizen		4.0
 * @description		Removes the sensor provider handle and releases all its resources.
 */
int utc_system_sensor_remove_provider_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_remove_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_remove_provider_n
 * @since_tizen		4.0
 * @description		Add the sensor provider with invalid parameter.
 */
int utc_system_sensor_remove_provider_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_remove_provider(NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_add_sensor_added_cb_p
 * @since_tizen		4.0
 * @description		Registers a callback function to be invoked when a new sensor is added.
 */
int utc_system_sensor_add_sensor_added_cb_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;
	g_called = false;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_sensor_added_cb(test_sensor_added_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	wait_callback();
	assert_eq(g_called, true);

	error = sensor_remove_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_remove_sensor_added_cb(test_sensor_added_callback);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_add_sensor_added_cb_n
 * @since_tizen		4.0
 * @description		Registers a callback function with invalid parameter.
 */
int utc_system_sensor_add_sensor_added_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_add_sensor_added_cb(NULL, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_remove_sensor_added_cb_p
 * @since_tizen		4.0
 * @description		Deregisters a callback function to be invoked when a new sensor is added.
 */
int utc_system_sensor_remove_sensor_added_cb_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;
	g_called = false;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_sensor_added_cb(test_sensor_added_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_remove_sensor_added_cb(test_sensor_added_callback);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_remove_sensor_added_cb_n
 * @since_tizen		4.0
 * @description		Deregisters a callback function with invalid parameter.
 */
int utc_system_sensor_remove_sensor_added_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_remove_sensor_added_cb(NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_add_sensor_removed_cb_p
 * @since_tizen		4.0
 * @description		Registers a callback function to be invoked when a new sensor is removed.
 */
int utc_system_sensor_add_sensor_removed_cb_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;
	g_called = false;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_sensor_removed_cb(test_sensor_removed_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_remove_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	wait_callback();
	assert_eq(g_called, true);

	error = sensor_remove_sensor_removed_cb(test_sensor_removed_callback);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_add_sensor_removed_cb_n
 * @since_tizen		4.0
 * @description		Registers a callback function with invalid parameter.
 */
int utc_system_sensor_add_sensor_removed_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_add_sensor_removed_cb(NULL, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_remove_sensor_removed_cb_p
 * @since_tizen		4.0
 * @description		Deregisters a callback function to be invoked when a new sensor is removed.
 */
int utc_system_sensor_remove_sensor_removed_cb_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;
	g_called = false;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_sensor_removed_cb(test_sensor_removed_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_remove_sensor_removed_cb(test_sensor_removed_callback);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_remove_sensor_removed_cb_n
 * @since_tizen		4.0
 * @description		Deregisters a callback function with invalid parameter.
 */
int utc_system_sensor_remove_sensor_removed_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_remove_sensor_removed_cb(NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_name_p
 * @since_tizen		4.0
 * @description		Sets the name of the sensor
 */
int utc_system_sensor_provider_set_name_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_provider_set_name(provider, "mysensor");
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_name_n
 * @since_tizen		4.0
 * @description		Sets the name of the sensor with invalid parameter
 */
int utc_system_sensor_provider_set_name_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_provider_set_name(NULL, NULL);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_vendor_p
 * @since_tizen		4.0
 * @description		Sets the vendor of the sensor
 */
int utc_system_sensor_provider_set_vendor_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_provider_set_vendor(provider, "Tizen");
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_vendor_n
 * @since_tizen		4.0
 * @description		Sets the vendor of the sensor with invalid parameter
 */
int utc_system_sensor_provider_set_vendor_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_provider_set_vendor(NULL, "Tizen");
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_range_p
 * @since_tizen		4.0
 * @description		Sets the value range of the sensor
 */
int utc_system_sensor_provider_set_range_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_provider_set_range(provider, 0.0, 1.0);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_range_n
 * @since_tizen		4.0
 * @description		Sets the value range of the sensor with invalid parameter
 */
int utc_system_sensor_provider_set_range_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_provider_set_range(NULL, 0, 0);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_resolution_p
 * @since_tizen		4.0
 * @description		Sets the resolution of the sensor
 */
int utc_system_sensor_provider_set_resolution_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_provider_h provider;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_provider_set_resolution(provider, 0.1);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_resolution_n
 * @since_tizen		4.0
 * @description		Sets the resolution of the sensor with invalid parameter
 */
int utc_system_sensor_provider_set_resolution_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_provider_set_resolution(NULL, 0);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

static int start_mysensor(sensor_listener_h *listener, const char *msg)
{
	sensor_h sensor;
	int error = SENSOR_ERROR_NONE;

	error = sensor_get_default_sensor_by_uri(TEST_SENSOR_URI, &sensor);
	if (error < 0) return error;
	error = sensor_create_listener(sensor, listener);
	if (error < 0) return error;
	error = sensor_listener_set_event_cb(*listener, INTERVAL, test_callback, (void *)msg);
	if (error < 0) return error;
	error = sensor_listener_start(*listener);
	if (error < 0) return error;
	error = sensor_listener_set_interval(*listener, INTERVAL);
	if (error < 0) return error;

	return SENSOR_ERROR_NONE;
}

static int stop_mysensor(sensor_listener_h listener)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_listener_stop(listener);
	if (error < 0) return error;
	error = sensor_listener_unset_event_cb(listener);
	if (error < 0) return error;
	error = sensor_destroy_listener(listener);
	if (error < 0) return error;

	return SENSOR_ERROR_NONE;
}

static gboolean test_start_sensor(gpointer gdata)
{
	sensor_listener_h *listener = (sensor_listener_h *)(gdata);
	start_mysensor(listener, TEST_STRING_TERM);
	return FALSE;
}

static gboolean test_stop_sensor(gpointer gdata)
{
	sensor_listener_h *listener = (sensor_listener_h *)(gdata);
	stop_mysensor(*listener);
	return FALSE;
}

/**
 * @testcase		utc_system_sensor_provider_set_start_cb_p
 * @since_tizen		4.0
 * @description		Registers a callback function to be invoked when a sensor is started
 */
int utc_system_sensor_provider_set_start_cb_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_listener_h listener;
	sensor_provider_h provider;
	g_called = false;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_provider_set_start_cb(provider, test_start_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_NONE);

	g_timeout_add(100, test_start_sensor, &listener);

	wait_callback();
	assert_eq(g_called, true);

	stop_mysensor(listener);

	error = sensor_remove_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_start_cb_n
 * @since_tizen		4.0
 * @description		Registers a callback function to be invoked when a sensor is started with invalid parameter
 */
int utc_system_sensor_provider_set_start_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_provider_set_start_cb(NULL, test_start_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_stop_cb_p
 * @since_tizen		4.0
 * @description		Registers a callback function to be invoked when a sensor is stopped
 */
int utc_system_sensor_provider_set_stop_cb_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_listener_h listener;
	sensor_provider_h provider;
	g_called = false;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_provider_set_stop_cb(provider, test_stop_callback, (void *)TEST_STRING);
	assert_eq(error, SENSOR_ERROR_NONE);

	g_timeout_add(100, test_start_sensor, &listener);
	g_timeout_add(300, test_stop_sensor, &listener);

	wait_callback();
	assert_eq(g_called, true);

	error = sensor_remove_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_stop_cb_n
 * @since_tizen		4.0
 * @description		Registers a callback function to be invoked when a sensor is stopped with invalid parameter
 */
int utc_system_sensor_provider_set_stop_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_provider_set_stop_cb(NULL, test_stop_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_interval_changed_cb_p
 * @since_tizen		4.0
 * @description		Registers a callback function to be invoked when interval is set to sensor
 */
int utc_system_sensor_provider_set_interval_changed_cb_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_listener_h listener;
	sensor_provider_h provider;
	g_called = false;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_provider_set_interval_changed_cb(provider, test_interval_changed_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_NONE);

	g_timeout_add(100, test_start_sensor, &listener);

	wait_callback();
	assert_eq(g_called, true);

	stop_mysensor(listener);

	error = sensor_remove_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_set_interval_changed_cb_n
 * @since_tizen		4.0
 * @description		Registers a callback function to be invoked when interval is set to sensor with invalid parameter
 */
int utc_system_sensor_provider_set_interval_changed_cb_n(void)
{
	int error = SENSOR_ERROR_NONE;

	error = sensor_provider_set_interval_changed_cb(NULL, test_interval_changed_callback, TEST_STRING);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

static gboolean test_publish(gpointer gdata)
{
	fprintf(stderr, "test_callback was called\n");

	if (g_called) return FALSE;

	sensor_provider_h provider = (sensor_provider_h)(gdata);

	sensor_event_s data;
	data.accuracy = 3;
	data.timestamp = 9999;
	data.value_count = 3;
	data.values[0] = 1;
	data.values[1] = 2;
	data.values[2] = 3;

	sensor_provider_publish(provider, data);
	return TRUE;
}

/**
 * @testcase		utc_system_sensor_provider_publish_p
 * @since_tizen		4.0
 * @description		Publishes a sensor event to it's listeners
 */
int utc_system_sensor_provider_publish_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_listener_h listener;
	sensor_provider_h provider;
	g_called = false;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	g_timeout_add(100, test_publish, provider);

	start_mysensor(&listener, TEST_STRING);

	wait_callback();
	assert_eq(g_called, true);

	stop_mysensor(listener);

	error = sensor_remove_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_publish_n
 * @since_tizen		4.0
 * @description		Publishes a sensor event to it's listeners with invalid parameter
 */
int utc_system_sensor_provider_publish_n(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_event_s event;

	error = sensor_provider_publish(NULL, event);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

static gboolean test_publish_events(gpointer gdata)
{
	fprintf(stderr, "test_callback was called\n");

	if (g_called) return FALSE;

	sensor_provider_h provider = (sensor_provider_h)(gdata);
	const int NUMBER_OF_EVENT = 100;
	sensor_event_s data[NUMBER_OF_EVENT];

	for (int i = 0 ; i < NUMBER_OF_EVENT; i++) {
		data[i].accuracy = 3;
		data[i].timestamp = 1000 + i;
		data[i].value_count = 3;
		data[i].values[0] = i;
		data[i].values[1] = i;
		data[i].values[2] = i;
	}

	sensor_provider_publish_events(provider, data, NUMBER_OF_EVENT);
	return TRUE;
}

/**
 * @testcase		utc_system_sensor_provider_publish_events_p
 * @since_tizen		5.5
 * @description		Publishes sensor events to it's listeners
 */
int utc_system_sensor_provider_publish_events_p(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_listener_h listener;
	sensor_provider_h provider;
	g_called = false;

	error = sensor_create_provider(TEST_SENSOR_URI, &provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_add_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	g_timeout_add(100, test_publish_events, provider);

	start_mysensor(&listener, TEST_STRING);

	wait_callback();
	assert_eq(g_called, true);

	stop_mysensor(listener);

	error = sensor_remove_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	error = sensor_destroy_provider(provider);
	assert_eq(error, SENSOR_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_system_sensor_provider_publish_events_n
 * @since_tizen		5.5
 * @description		Publishes sensor events to it's listeners with invalid parameter
 */
int utc_system_sensor_provider_publish_events_n(void)
{
	int error = SENSOR_ERROR_NONE;
	sensor_event_s event[10];

	error = sensor_provider_publish_events(NULL, event, 10);
	assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

	return 0;
}

