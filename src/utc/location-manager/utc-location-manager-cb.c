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

#include <locations.h>
#include <glib.h>
#include "assert.h"
#include <string.h>
#include <unistd.h>
#include <system_info.h>
#include "utc-location-manager-common.h"

//& set: LocationManagercb
static GMainLoop *g_mainloop = NULL;
static location_manager_h manager = NULL;

static bool __position_updated = false;
static bool __velocity_updated = false;
static bool __location_changed = false;
static bool __setting_changed = false;
static bool __zone_changed = false;

static void wait_for_service()
{
	g_mainloop = g_main_loop_new(NULL, 0);
	g_main_loop_run(g_mainloop);
}

static void wait_for_callback(bool *status)
{
	int timeout = 0;
	for (timeout = 0; timeout < 20; timeout++) {
		if (*status) {
			break;
		} else {
			sleep(1);
		}
	}
}

static void __service_state_changed_cb(location_service_state_e state, void *user_data)
{
	switch (state) {
		case LOCATIONS_SERVICE_ENABLED:
			service_enabled = true;
			break;
		case LOCATIONS_SERVICE_DISABLED:
			service_enabled = false;
			break;
	}

	if (g_mainloop) {
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}
}


/**
 * @function		utc_location_manager_cb_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_location_manager_cb_startup(void)
{
	service_enabled = false;
	__position_updated = false;
	__velocity_updated = false;
	__location_changed = false;
	__setting_changed = false;
	__zone_changed = false;

	system_info_get_platform_bool(LOCATION_FEATURE, &is_location_supported);
	system_info_get_platform_bool(GPS_FEATURE, &is_gps_supported);
	system_info_get_platform_bool(WPS_FEATURE, &is_wps_supported);

	if (manager == NULL) {
		location_manager_create(LOCATIONS_METHOD_HYBRID, &manager);
	}
}

/**
 * @function		utc_location_manager_cb_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_location_manager_cb_cleanup(void)
{
	if (manager) {
		location_manager_destroy(manager);
		manager = NULL;
	}

	if (g_mainloop) {
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}
}

static void __position_updated_cb(double latitude, double longitude, double altitude, time_t timestamp, void *user_data)
{
	__position_updated = true;
	if (g_mainloop) {
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}
}

static void __zone_changed_cb(location_boundary_state_e state, double latitude, double longitude, double altitude, time_t timestamp, void *user_data)
{
	__zone_changed = true;
	if (g_mainloop) {
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}
}

static void __velocity_updated_cb(double speed, double direction, double climb, time_t timestamp, void *user_data)
{
	__velocity_updated = true;
	if (g_mainloop) {
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}
}

static void __location_changed_cb(double latitude, double longitude, double altitude, double speed, double direction, double horizontal_accuracy, time_t timestamp, void *user_data)
{
	__location_changed = true;
	if (g_mainloop) {
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}
}

static void __setting_changed_cb(location_method_e method, bool enable, void *user_data)
{
	__setting_changed = true;
}

/**
 * @testcase		utc_location_manager_start_p
 * @since_tizen		2.3
 * @description		Starts the location service
 */
int utc_location_manager_start_p(void)
{
	ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
	CHECK(is_location_supported, ret);

	ret = location_manager_start(manager);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		assert(!service_enabled);

		ret = location_manager_unset_service_state_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_start_n
 * @since_tizen		2.3
 * @description		Starts the location service with invalid parameter
 */
int utc_location_manager_start_n(void)
{
	ret = location_manager_start(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_set_position_updated_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked at defined interval with updated position information
 */
int utc_location_manager_set_position_updated_cb_p(void)
{
	__position_updated = false;
	ret = location_manager_set_position_updated_cb(manager, __position_updated_cb, 1, NULL);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		wait_for_service();

		wait_for_callback(&__position_updated);
		assert(__position_updated);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_position_updated_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_set_position_updated_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked at defined interval with updated position information with invalid parameters
 */
int utc_location_manager_set_position_updated_cb_n(void)
{
	ret = location_manager_set_position_updated_cb(manager, NULL, 1, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_position_updated_cb(NULL, __position_updated_cb, 1, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_position_updated_cb(manager, __position_updated_cb, 0, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_position_updated_cb(manager, __position_updated_cb, 121, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_unset_position_updated_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the callback function
 */
int utc_location_manager_unset_position_updated_cb_p(void)
{
	ret = location_manager_set_position_updated_cb(manager, __position_updated_cb, 1, NULL);
	CHECK(is_location_supported, ret);

	ret = location_manager_unset_position_updated_cb(manager);
	CHECK_ERROR_NONE(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_unset_position_updated_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the callback function with invalid parameter
 */
int utc_location_manager_unset_position_updated_cb_n(void)
{
	ret = location_manager_unset_position_updated_cb(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_set_velocity_updated_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked at defined interval with updated velocity information
 */
int utc_location_manager_set_velocity_updated_cb_p(void)
{
	__velocity_updated = false;
	ret = location_manager_set_velocity_updated_cb(manager, __velocity_updated_cb, 1, NULL);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		wait_for_service();

		wait_for_callback(&__velocity_updated);
		assert(__velocity_updated);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_velocity_updated_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_set_velocity_updated_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked at defined interval with updated velocity information with invalid parameters
 */
int utc_location_manager_set_velocity_updated_cb_n(void)
{
	ret = location_manager_set_velocity_updated_cb(manager, NULL, 1, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_velocity_updated_cb(NULL, __velocity_updated_cb, 1, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_unset_velocity_updated_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the callback function
 */
int utc_location_manager_unset_velocity_updated_cb_p(void)
{
	ret = location_manager_set_velocity_updated_cb(manager, __velocity_updated_cb, 1, NULL);
	CHECK(is_location_supported, ret);

	ret = location_manager_unset_velocity_updated_cb(manager);
	CHECK_ERROR_NONE(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_unset_velocity_updated_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the callback function with invalid parameter
 */
int utc_location_manager_unset_velocity_updated_cb_n(void)
{
	ret = location_manager_unset_velocity_updated_cb(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_set_service_state_changed_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the location service state is changed
 */
int utc_location_manager_set_service_state_changed_cb_p(void)
{
	ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		assert(!service_enabled);

		ret = location_manager_unset_service_state_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_set_service_state_changed_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the location service state is changed with invalid parameters
 */
int utc_location_manager_set_service_state_changed_cb_n(void)
{
	ret = location_manager_set_service_state_changed_cb(manager, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_service_state_changed_cb(NULL, __service_state_changed_cb, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_unset_service_state_changed_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the callback function
 */
int utc_location_manager_unset_service_state_changed_cb_p(void)
{
	ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
	CHECK(is_location_supported, ret);

	ret = location_manager_unset_service_state_changed_cb(manager);
	CHECK_ERROR_NONE(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_unset_service_state_changed_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the callback function with invalid parameter
 */
int utc_location_manager_unset_service_state_changed_cb_n(void)
{
	ret = location_manager_unset_service_state_changed_cb(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_set_zone_changed_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the previously set boundary area is entered or left
 */
int utc_location_manager_set_zone_changed_cb_p(void)
{
	__zone_changed = false;
	ret = location_manager_set_zone_changed_cb(manager, __zone_changed_cb, NULL);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		location_coords_s center;
		location_bounds_h bounds_circle = NULL;
		center.latitude = 37.258;
		center.longitude = 127.056;
		double radius = 30;
		ret = location_bounds_create_circle(center, radius, &bounds_circle);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		ret = location_manager_add_boundary(manager, bounds_circle);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		wait_for_service();

		wait_for_callback(&__zone_changed);
		assert(__zone_changed);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_zone_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_set_zone_changed_cb_p2
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the previously set boundary area is entered or left
 */
int utc_location_manager_set_zone_changed_cb_p2(void)
{
	__zone_changed = false;
	ret = location_manager_set_zone_changed_cb(manager, __zone_changed_cb, NULL);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		location_coords_s center;
		location_bounds_h bounds_circle = NULL;
		center.latitude = 37.253670;
		center.longitude = 127.054963;
		double radius = 30;
		ret = location_bounds_create_circle(center, radius, &bounds_circle);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		ret = location_manager_add_boundary(manager, bounds_circle);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		wait_for_service();

		wait_for_callback(&__zone_changed);
		assert(__zone_changed);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_zone_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_set_zone_changed_cb_p3
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the previously set boundary area is entered or left
 */
int utc_location_manager_set_zone_changed_cb_p3(void)
{
	__zone_changed = false;
	ret = location_manager_set_zone_changed_cb(manager, __zone_changed_cb, NULL);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		int poly_size = 3;
		location_bounds_h bounds_poly = NULL;
		location_coords_s coord_list[poly_size];
		coord_list[0].latitude = 10;
		coord_list[0].longitude = 10;
		coord_list[1].latitude = 20;
		coord_list[1].longitude = 20;
		coord_list[2].latitude = 30;
		coord_list[2].longitude = 30;

		ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_add_boundary(manager, bounds_poly);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		wait_for_service();

		wait_for_callback(&__zone_changed);
		assert(__zone_changed);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_zone_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_set_zone_changed_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the previously set boundary area is entered or left
 */
int utc_location_manager_set_zone_changed_cb_n(void)
{
	ret = location_manager_set_zone_changed_cb(manager, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_zone_changed_cb(NULL, __zone_changed_cb, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_unset_zone_changed_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the callback function
 */
int utc_location_manager_unset_zone_changed_cb_p(void)
{
	ret = location_manager_set_zone_changed_cb(manager, __zone_changed_cb, NULL);
	CHECK(is_location_supported, ret);

	ret = location_manager_unset_zone_changed_cb(manager);
	CHECK_ERROR_NONE(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_unset_zone_changed_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the callback function with invalid parameter
 */
int utc_location_manager_unset_zone_changed_cb_n(void)
{
	ret = location_manager_unset_zone_changed_cb(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_set_setting_changed_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the location setting is changed
 */
int utc_location_manager_set_setting_changed_cb_p(void)
{
	ret = location_manager_set_setting_changed_cb(LOCATIONS_METHOD_HYBRID, __setting_changed_cb, NULL);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_manager_unset_setting_changed_cb(LOCATIONS_METHOD_HYBRID);
	CHECK(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_set_setting_changed_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the location setting is changed with invalid parameters
 */
int utc_location_manager_set_setting_changed_cb_n(void)
{
	ret = location_manager_set_setting_changed_cb(LOCATIONS_METHOD_NONE, __setting_changed_cb, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_setting_changed_cb(LOCATIONS_METHOD_GPS, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_unset_setting_changed_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the callback function
 */
int utc_location_manager_unset_setting_changed_cb_p(void)
{
	ret = location_manager_set_setting_changed_cb(LOCATIONS_METHOD_GPS, __setting_changed_cb, NULL);
	CHECK(is_location_supported, ret);

	ret = location_manager_unset_setting_changed_cb(LOCATIONS_METHOD_GPS);
	CHECK_ERROR_NONE(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_unset_setting_changed_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the callback function with invalid parameter
 */
int utc_location_manager_unset_setting_changed_cb_n(void)
{
	ret = location_manager_unset_setting_changed_cb(LOCATIONS_METHOD_NONE);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_stop_p
 * @since_tizen		2.3
 * @description		Stops the location service
 */
int utc_location_manager_stop_p(void)
{
	if (is_location_supported) {
		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		assert(!service_enabled);

		ret = location_manager_unset_service_state_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_stop_n
 * @since_tizen		2.3
 * @description		Stops the location service with invalid parameter
 */
int utc_location_manager_stop_n(void)
{
	ret = location_manager_stop(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_set_distance_based_location_changed_cb_p
 * @since_tizen		2.4
 * @description		Registers a callback function to be invoked at minimum interval or minimum distance with updated position information
 */
int utc_location_manager_set_distance_based_location_changed_cb_p(void)
{
	__location_changed = false;
	ret = location_manager_set_distance_based_location_changed_cb(manager, __location_changed_cb, 5, 10.2, NULL);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		wait_for_service();

		wait_for_callback(&__location_changed);
		assert(__location_changed);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_distance_based_location_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_set_distance_based_location_changed_cb_n
 * @since_tizen		2.4
 * @description		Registers a callback function to be invoked at minimum interval or minimum distance with updated position information
 */
int utc_location_manager_set_distance_based_location_changed_cb_n(void)
{
	ret = location_manager_set_distance_based_location_changed_cb(manager, NULL, 1, 10, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_distance_based_location_changed_cb(manager, __location_changed_cb, 0, 10, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_distance_based_location_changed_cb(manager, __location_changed_cb, 121, 10, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_distance_based_location_changed_cb(manager, __location_changed_cb, 1, 0, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_distance_based_location_changed_cb(manager, __location_changed_cb, 1, 121, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_unset_distance_based_location_changed_cb_p
 * @since_tizen		2.4
 * @description		Unregisters the callback function
 */
int utc_location_manager_unset_distance_based_location_changed_cb_p(void)
{
	ret = location_manager_set_distance_based_location_changed_cb(manager, __location_changed_cb, 1, 10.2, NULL);
	CHECK(is_location_supported, ret);

	ret = location_manager_unset_distance_based_location_changed_cb(manager);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_unset_distance_based_location_changed_cb_n
 * @since_tizen		2.4
 * @description		Unregisters the callback function with invalid parameter
 */
int utc_location_manager_unset_distance_based_location_changed_cb_n(void)
{
	ret = location_manager_unset_distance_based_location_changed_cb(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_set_location_changed_cb_p
 * @since_tizen		2.4
 * @description		Registers a callback function to be invoked at defined interval with updated location information
 */
int utc_location_manager_set_location_changed_cb_p(void)
{
	__location_changed = false;
	ret = location_manager_set_location_changed_cb(manager, __location_changed_cb, 1, NULL);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		wait_for_service();

		wait_for_callback(&__location_changed);
		assert(__location_changed);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_location_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_set_location_changed_cb_p2
 * @since_tizen		3.0
 * @description		Registers a callback function to be invoked at defined interval with updated location information
 */
int utc_location_manager_set_location_changed_cb_p2(void)
{
	location_manager_h manager2 = NULL;
	__location_changed = false;

	if (is_location_supported) {
		location_manager_create(LOCATIONS_METHOD_PASSIVE, &manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_set_location_changed_cb(manager2, __location_changed_cb, 1, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		wait_for_service();

		wait_for_callback(&__location_changed);
		assert(__location_changed);

		ret = location_manager_stop(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_location_changed_cb(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_destroy(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		manager2 = NULL;
	} else {
		ret = location_manager_set_location_changed_cb(manager, __location_changed_cb, 1, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_set_location_changed_cb_n
 * @since_tizen		2.4
 * @description		Registers a callback function to be invoked at defined interval with invalid parameters
 */
int utc_location_manager_set_location_changed_cb_n(void)
{
	ret = location_manager_set_location_changed_cb(manager, NULL, 1, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_location_changed_cb(manager, __location_changed_cb, 0, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_set_location_changed_cb(manager, __location_changed_cb, 121, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_unset_location_changed_cb_p
 * @since_tizen		2.4
 * @description		Unregisters the callback function
 */
int utc_location_manager_unset_location_changed_cb_p(void)
{
	ret = location_manager_set_location_changed_cb(manager, __location_changed_cb, 1, NULL);
	CHECK(is_location_supported, ret);

	ret = location_manager_unset_location_changed_cb(manager);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_unset_location_changed_cb_n
 * @since_tizen		2.4
 * @description		Unregisters the callback function with invalid parameter
 */
int utc_location_manager_unset_location_changed_cb_n(void)
{
	ret = location_manager_unset_location_changed_cb(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}
