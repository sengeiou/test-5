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

//& set: LocationManager
static GMainLoop *g_mainloop = NULL;
static location_manager_h manager = NULL;
static bool __location_updated = false;


static void wait_for_service()
{
	g_mainloop = g_main_loop_new(NULL, 0);
	g_main_loop_run(g_mainloop);
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

static void __location_updated_cb(location_error_e error, double latitude, double longitude, double altitude, time_t timestamp, double speed, double direction, double climb, void *user_data)
{
	__location_updated = true;
	printf("location_updated_cb \n");
	if (g_mainloop) {
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}
}

static int cleanup_default_handle()
{
	int ret = LOCATIONS_ERROR_NONE;
	if (manager) {
		ret = location_manager_destroy(manager);
		manager = NULL;
	}
	return ret;
}

/**
 * @function		utc_location_manager_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_location_manager_startup(void)
{
	system_info_get_platform_bool(LOCATION_FEATURE, &is_location_supported);
	system_info_get_platform_bool(GPS_FEATURE, &is_gps_supported);
	system_info_get_platform_bool(WPS_FEATURE, &is_wps_supported);
	system_info_get_platform_bool(FUSED_FEATURE, &is_fused_supported);

	if (manager == NULL) {
		location_manager_create(LOCATIONS_METHOD_HYBRID, &manager);
	}
}

/**
 * @function		utc_location_manager_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_location_manager_cleanup(void)
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

/**
 * @testcase		utc_location_manager_create_p
 * @since_tizen		2.3
 * @description		Creates a new location manager handle for GPS
 */
int utc_location_manager_create_p(void)
{
	location_manager_h manager2 = NULL;

	ret = cleanup_default_handle();
	assert_eq(ret, LOCATIONS_ERROR_NONE);

	ret = location_manager_create(LOCATIONS_METHOD_GPS, &manager2);
	if (is_gps_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_destroy(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		manager2 = NULL;
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_create_p2
 * @since_tizen		2.3
 * @description		Creates a new location manager handle for WPS
 */
int utc_location_manager_create_p2(void)
{
	location_manager_h manager2 = NULL;

	ret = cleanup_default_handle();
	assert_eq(ret, LOCATIONS_ERROR_NONE);

	ret = location_manager_create(LOCATIONS_METHOD_WPS, &manager2);
	if (is_wps_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_destroy(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		manager2 = NULL;
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_create_p3
 * @since_tizen		3.0
 * @description		Creates a new location manager handle for Passive
 */
int utc_location_manager_create_p3(void)
{
	location_manager_h manager2 = NULL;

	ret = cleanup_default_handle();
	assert_eq(ret, LOCATIONS_ERROR_NONE);

	ret = location_manager_create(LOCATIONS_METHOD_PASSIVE, &manager2);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_destroy(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		manager2 = NULL;
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_create_p4
 * @since_tizen		3.0
 * @description		Create handles to test  multi handle
 */
int utc_location_manager_create_p4(void)
{
	location_manager_h manager2 = NULL;
	location_manager_h manager3 = NULL;

	ret = location_manager_create(LOCATIONS_METHOD_HYBRID, &manager2);

	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		if (is_gps_supported) {
			ret = location_manager_create(LOCATIONS_METHOD_GPS, &manager3);
			assert_eq(ret, LOCATIONS_ERROR_NONE);

			ret = location_manager_destroy(manager3);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
		} else if (is_wps_supported) {
			ret = location_manager_create(LOCATIONS_METHOD_WPS, &manager3);
			assert_eq(ret, LOCATIONS_ERROR_NONE);

			ret = location_manager_destroy(manager3);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
		}

		ret = location_manager_destroy(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		manager2 = NULL;
		manager3 = NULL;
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_create_p5
 * @since_tizen		4.0
 * @description		Creates a new location manager handle for Fused
 */
int utc_location_manager_create_p5(void)
{
	location_manager_h manager2 = NULL;

	ret = cleanup_default_handle();
	assert_eq(ret, LOCATIONS_ERROR_NONE);

	ret = location_manager_create(LOCATIONS_METHOD_FUSED, &manager2);
	if (is_fused_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_destroy(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		manager2 = NULL;
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_create_n
 * @since_tizen		2.3
 * @description		Creates a new location manager handle with invalid parameter
 */
int utc_location_manager_create_n(void)
{
	if (manager) {
		ret = location_manager_destroy(manager);
		assert(ret == LOCATIONS_ERROR_NONE || ret == LOCATIONS_ERROR_NOT_SUPPORTED);
		manager = NULL;
	}

	ret = location_manager_create(LOCATIONS_METHOD_HYBRID, NULL);
	CHECK_INVALID_PARAMETER(is_gps_supported || is_wps_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_create_n2
 * @since_tizen		2.3
 * @description		Creates a new location manager handle with invalid parameter
 */
int utc_location_manager_create_n2(void)
{
	if (manager) {
		ret = location_manager_destroy(manager);
		assert(ret == LOCATIONS_ERROR_NONE || ret == LOCATIONS_ERROR_NOT_SUPPORTED);
		manager = NULL;
	}

	ret = location_manager_create(LOCATIONS_METHOD_NONE, NULL);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_get_method_p
 * @since_tizen		2.3
 * @description		Gets the given location manager's method
 */
int utc_location_manager_get_method_p(void)
{
	location_method_e method;

	ret = location_manager_get_method(manager, &method);
	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		assert_eq(method, LOCATIONS_METHOD_HYBRID);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_get_method_p2
 * @since_tizen		2.3
 * @description		Gets the given location manager's method
 */
int utc_location_manager_get_method_p2(void)
{
	location_method_e method;
	location_manager_h manager2 = NULL;

	if (is_location_supported) {
		if (is_gps_supported) {
			ret = cleanup_default_handle();
			assert_eq(ret, LOCATIONS_ERROR_NONE);

			ret = location_manager_create(LOCATIONS_METHOD_GPS, &manager2);
			assert_eq(ret, LOCATIONS_ERROR_NONE);

			ret = location_manager_get_method(manager2, &method);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			assert_eq(method, LOCATIONS_METHOD_GPS);

			if (manager2) {
				ret = location_manager_destroy(manager2);
				assert_eq(ret, LOCATIONS_ERROR_NONE);
				manager2 = NULL;
			}
		}
	} else {
		ret = location_manager_get_method(manager2, &method);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_get_method_p3
 * @since_tizen		2.3
 * @description		Gets the given location manager's method
 */
int utc_location_manager_get_method_p3(void)
{
	location_method_e method;
	location_manager_h manager2 = NULL;

	if (is_location_supported) {
		if (is_wps_supported) {
			ret = cleanup_default_handle();
			assert_eq(ret, LOCATIONS_ERROR_NONE);

			ret = location_manager_create(LOCATIONS_METHOD_WPS, &manager2);
			assert_eq(ret, LOCATIONS_ERROR_NONE);

			ret = location_manager_get_method(manager2, &method);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			assert_eq(method, LOCATIONS_METHOD_WPS);

			if (manager2) {
				ret = location_manager_destroy(manager2);
				assert_eq(ret, LOCATIONS_ERROR_NONE);
				manager2 = NULL;
			}
		}
	} else {
		ret = location_manager_get_method(manager2, &method);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_get_method_p4
 * @since_tizen		3.0
 * @description		Gets the given location manager's method
 */
int utc_location_manager_get_method_p4(void)
{
	location_method_e method;
	location_manager_h manager2 = NULL;

	if (is_location_supported) {
		ret = cleanup_default_handle();
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_create(LOCATIONS_METHOD_PASSIVE, &manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_get_method(manager2, &method);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		assert_eq(method, LOCATIONS_METHOD_PASSIVE);

		if (manager2) {
			ret = location_manager_destroy(manager2);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			manager2 = NULL;
		}
	} else {
		ret = location_manager_get_method(manager2, &method);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_get_method_p5
 * @since_tizen		4.0
 * @description		Gets the given location manager's method
 */
int utc_location_manager_get_method_p5(void)
{
	location_method_e method;
	location_manager_h manager2 = NULL;

	ret = cleanup_default_handle();
	assert_eq(ret, LOCATIONS_ERROR_NONE);

	ret = location_manager_create(LOCATIONS_METHOD_FUSED, &manager2);
	if (is_fused_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_get_method(manager2, &method);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		assert_eq(method, LOCATIONS_METHOD_FUSED);

		if (manager2) {
			ret = location_manager_destroy(manager2);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			manager2 = NULL;
		}
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}


/**
 * @testcase		utc_location_manager_get_method_n
 * @since_tizen		2.3
 * @description		Gets the given location manager's method with invalid parameters
 */
int utc_location_manager_get_method_n(void)
{
	location_method_e method;
	ret = location_manager_get_method(NULL, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_method(manager, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_method(NULL, &method);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_get_position_p
 * @since_tizen		2.3
 * @description		Gets the current position information
 */
int utc_location_manager_get_position_p(void)
{
	double altitude = 0.0;
	double latitude = 0.0;
	double longitude = 0.0;
	time_t timestamp = 0.0;
	service_enabled = false;

	if (is_location_supported) {
		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_get_position(manager, &altitude, &latitude, &longitude, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_service_state_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_get_position(manager, &altitude, &latitude, &longitude, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_get_position_p2
 * @since_tizen		4.0
 * @description		Gets the current position information
 */
int utc_location_manager_get_position_p2(void)
{
	location_manager_h manager2 = NULL;
	double latitude = 0.0;
	double longitude = 0.0;
	double altitude = 0.0;
	time_t timestamp = 0.0;
	service_enabled = false;

	ret = cleanup_default_handle();
	assert_eq(ret, LOCATIONS_ERROR_NONE);

	ret = location_manager_create(LOCATIONS_METHOD_FUSED, &manager2);
	if (is_fused_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_set_service_state_changed_cb(manager2, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_get_position(manager2, &altitude, &latitude, &longitude, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_service_state_changed_cb(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_destroy(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		manager2 = NULL;
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_get_position_n
 * @since_tizen		2.3
 * @description		Gets the current position information with invalid parameters
 */
int utc_location_manager_get_position_n(void)
{
	double altitude = 0.0;
	double latitude = 0.0;
	double longitude = 0.0;
	time_t timestamp;

	ret = location_manager_get_position(NULL, &altitude, &latitude, &longitude, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_position(manager, NULL, &latitude, &longitude, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_position(manager, &altitude, NULL, &longitude, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_position(manager, &altitude, &latitude, NULL, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_position(manager, &altitude, &latitude, &longitude, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_get_velocity_p
 * @since_tizen		2.3
 * @description		Gets the current velocity information
 */
int utc_location_manager_get_velocity_p(void)
{
	double climb = 0.0;
	double direction = 0.0;
	double speed = 0.0;
	time_t timestamp;
	service_enabled = false;

	if (is_location_supported) {
		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_get_velocity(manager, &climb, &direction, &speed, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_service_state_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_get_velocity(manager, &climb, &direction, &speed, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_get_velocity_n
 * @since_tizen		2.3
 * @description		Gets the current velocity information with invalid parameters
 */
int utc_location_manager_get_velocity_n(void)
{
	double climb = 0.0;
	double direction = 0.0;
	double speed = 0.0;
	time_t timestamp;

	ret = location_manager_get_velocity(NULL, &climb, &direction, &speed, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_velocity(manager, NULL, &direction, &speed, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_velocity(manager, &climb, NULL, &speed, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_velocity(manager, &climb, &direction, NULL, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_velocity(manager, &climb, &direction, &speed, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_get_accuracy_p
 * @since_tizen		2.3
 * @description		Gets the current accuracy information
 */
int utc_location_manager_get_accuracy_p(void)
{
	location_accuracy_level_e level;
	double horizontal = 0.0;
	double vertical = 0.0;
	service_enabled = false;

	if (is_location_supported) {
		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_get_accuracy(manager, &level, &horizontal, &vertical);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_service_state_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_get_accuracy(manager, &level, &horizontal, &vertical);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_get_accuracy_n
 * @since_tizen		2.3
 * @description		Gets the current accuracy information with invalid parameters
 */
int utc_location_manager_get_accuracy_n(void)
{
	location_accuracy_level_e level;
	double horizontal = 0.0;
	double vertical = 0.0;

	ret = location_manager_get_accuracy(NULL, &level, &horizontal, &vertical);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_accuracy(manager, NULL, &horizontal, &vertical);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_accuracy(manager, &level, NULL, &vertical);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_accuracy(manager, &level, &horizontal, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_get_velocity_accuracy_p
 * @since_tizen		6.0
 * @description		Gets the current velocity accuracy information
 */
int utc_location_manager_get_velocity_accuracy_p(void)
{
	double velocity_accuracy = 0.0;
	service_enabled = false;

	if (is_location_supported) {
		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_get_velocity_accuracy(manager, &velocity_accuracy);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_service_state_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_get_velocity_accuracy(manager, &velocity_accuracy);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_get_velocity_accuracy_n
 * @since_tizen		6.0
 * @description		Gets the current velocity accuracy information with invalid parameters
 */
int utc_location_manager_get_velocity_accuracy_n(void)
{
	double velocity_accuracy = 0.0;

	ret = location_manager_get_velocity_accuracy(NULL, &velocity_accuracy);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_velocity_accuracy(manager, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_get_last_accuracy_p
 * @since_tizen		2.3
 * @description		Gets the last accuracy information which is recorded
 */
int utc_location_manager_get_last_accuracy_p(void)
{
	double horizontal = 0.0, vertical = 0.0;
	location_accuracy_level_e level;

	ret = location_manager_get_last_accuracy(manager, &level, &horizontal, &vertical);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_get_last_accuracy_n
 * @since_tizen		2.3
 * @description		Gets the last accuracy information which is recorded with invalid parameters
 */
int utc_location_manager_get_last_accuracy_n(void)
{
	double horizontal = 0.0, vertical = 0.0;
	location_accuracy_level_e level;

	ret = location_manager_get_last_accuracy(NULL, &level, &horizontal, &vertical);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_accuracy(manager, NULL, &horizontal, &vertical);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_accuracy(manager, &level, NULL, &vertical);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_accuracy(manager, &level, &horizontal, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_get_accessibility_state_p
 * @since_tizen		2.3
 * @description		Gets the current application's location accessibility status
 */
int utc_location_manager_get_accessibility_state_p(void)
{
	location_accessibility_state_e state;

	ret = location_manager_get_accessibility_state(&state);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_get_accessibility_state_n
 * @since_tizen		2.3
 * @description		Gets the current application's location accessibility status with invalid parameter
 */
int utc_location_manager_get_accessibility_state_n(void)
{
	ret = location_manager_get_accessibility_state(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_get_last_location_p
 * @since_tizen		2.3
 * @description		Gets the last location information
 */
int utc_location_manager_get_last_location_p(void)
{
	double altitude, latitude, longitude, climb, direction, speed, horizontal, vertical;
	location_accuracy_level_e level;
	time_t timestamp;

	ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_get_last_location_n
 * @since_tizen		2.3
 * @description		Gets the last location information with invalid parameters
 */
int utc_location_manager_get_last_location_n(void)
{
	double altitude, latitude, longitude, climb, direction, speed, horizontal, vertical;
	location_accuracy_level_e level;
	time_t timestamp;

	ret = location_manager_get_last_location(NULL, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_location(manager, NULL, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_location(manager, &altitude, NULL, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_location(manager, &altitude, &latitude, NULL, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude, NULL, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude, &climb, NULL, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude, &climb, &direction, NULL, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, NULL, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, NULL, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, NULL, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_get_location_p
 * @since_tizen		2.3
 * @description		Gets the current position information
 */
int utc_location_manager_get_location_p(void)
{
	double altitude, latitude, longitude, climb, direction, speed, horizontal, vertical;
	location_accuracy_level_e level;
	time_t timestamp;
	service_enabled = false;

	if (is_location_supported) {
		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_get_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_service_state_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_get_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_get_location_n
 * @since_tizen		2.3
 * @description		Gets the current position information with invalid parameters
 */
int utc_location_manager_get_location_n(void)
{
	double altitude, latitude, longitude, climb, direction, speed, horizontal, vertical;
	location_accuracy_level_e level;
	time_t timestamp;

	ret = location_manager_get_location(NULL, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_location(manager, NULL, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_location(manager, &altitude, NULL, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_location(manager, &altitude, &latitude, NULL, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_location(manager, &altitude, &latitude, &longitude, NULL, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_location(manager, &altitude, &latitude, &longitude, &climb, NULL, &speed, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_location(manager, &altitude, &latitude, &longitude, &climb, &direction, NULL, &level, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, NULL, &horizontal, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, NULL, &vertical, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, NULL, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_location(manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_get_last_position_p
 * @since_tizen		2.3
 * @description		Gets the last position information which is recorded
 */
int utc_location_manager_get_last_position_p(void)
{
	double altitude = 0.0;
	double latitude = 0.0;
	double longitude = 0.0;
	time_t timestamp;

	ret = location_manager_get_last_position(manager, &altitude, &latitude, &longitude, &timestamp);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_get_last_position_n
 * @since_tizen		2.3
 * @description		Gets the last position information which is recorded with invalid parameters
 */
int utc_location_manager_get_last_position_n(void)
{
	double altitude = 0.0;
	double latitude = 0.0;
	double longitude = 0.0;
	time_t timestamp;

	ret = location_manager_get_last_position(NULL, &altitude, &latitude, &longitude, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_position(manager, NULL, &latitude, &longitude, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_position(manager, &altitude, NULL, &longitude, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_position(manager, &altitude, &latitude, NULL, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_position(manager, &altitude, &latitude, &longitude, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_get_last_velocity_p
 * @since_tizen		2.3
 * @description		Gets the last velocity information which is recorded
 */
int utc_location_manager_get_last_velocity_p(void)
{
	double climb = 0.0;
	double direction = 0.0;
	double speed = 0.0;
	time_t timestamp;

	ret = location_manager_get_last_velocity(manager, &climb, &direction, &speed, &timestamp);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_get_last_velocity_n
 * @since_tizen		2.3
 * @description		Gets the last velocity information which is recorded with invalid parameters
 */
int utc_location_manager_get_last_velocity_n(void)
{
	double climb = 0.0;
	double direction = 0.0;
	double speed = 0.0;
	time_t timestamp;

	ret = location_manager_get_last_velocity(NULL, &climb, &direction, &speed, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_velocity(manager, NULL, &direction, &speed, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_velocity(manager, &climb, NULL, &speed, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_velocity(manager, &climb, &direction, NULL, &timestamp);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_last_velocity(manager, &climb, &direction, &speed, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_is_supported_method_p
 * @since_tizen		2.3
 * @description		Checks whether the given location method is available
 */
int utc_location_manager_is_supported_method_p(void)
{
	bool ret_bool = false;
	ret_bool = location_manager_is_supported_method(LOCATIONS_METHOD_HYBRID);
	ret = get_last_result();

	if (is_location_supported) {
		assert(ret_bool);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret_bool, false);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_is_supported_method_p2
 * @since_tizen		2.3
 * @description		Checks whether the given location method is available
 */
int utc_location_manager_is_supported_method_p2(void)
{
	bool ret_bool = false;
	ret_bool = location_manager_is_supported_method(LOCATIONS_METHOD_GPS);
	ret = get_last_result();

	if (is_location_supported) {
		if (is_gps_supported) {
			assert_eq(ret_bool, true);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
		} else {
			assert_eq(ret_bool, false);
			assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
		}
	} else {
		assert_eq(ret_bool, false);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_is_supported_method_p3
 * @since_tizen		2.3
 * @description		Checks whether the given location method is available
 */
int utc_location_manager_is_supported_method_p3(void)
{
	bool ret_bool = false;
	ret_bool = location_manager_is_supported_method(LOCATIONS_METHOD_WPS);
	ret = get_last_result();

	if (is_location_supported) {
		if (is_wps_supported) {
			assert_eq(ret_bool, true);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
		} else {
			assert_eq(ret_bool, false);
			assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
		}
	} else {
		assert_eq(ret_bool, false);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_is_supported_method_p4
 * @since_tizen		2.3
 * @description		Checks whether the given location method is available
 */
int utc_location_manager_is_supported_method_p4(void)
{
	bool ret_bool = false;
	ret_bool = location_manager_is_supported_method(LOCATIONS_METHOD_PASSIVE);
	ret = get_last_result();

	if (is_location_supported) {
		assert(ret_bool);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret_bool, false);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_is_supported_method_n
 * @since_tizen		2.3
 * @description		Checks whether the given location method is available
 */
int utc_location_manager_is_supported_method_n(void)
{
	bool ret_bool = false;
	ret_bool = location_manager_is_supported_method(LOCATIONS_METHOD_NONE);
	ret = get_last_result();

	if (is_location_supported) {
		assert_eq(ret_bool, false);
		assert_eq(ret, LOCATIONS_ERROR_INCORRECT_METHOD);
	} else {
		assert_eq(ret_bool, false);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_destroy_p
 * @since_tizen		2.3
 * @description		Releases the location manager handle
 */
int utc_location_manager_destroy_p(void)
{
	ret = location_manager_destroy(manager);
	CHECK_ERROR_NONE(is_location_supported, ret);
	manager = NULL;
	return 0;
}

/**
 * @testcase		utc_location_manager_destroy_n
 * @since_tizen		2.3
 * @description		Releases the location manager handle with invalid parameter
 */
int utc_location_manager_destroy_n(void)
{
	ret = location_manager_destroy(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_get_distance_p
 * @since_tizen		2.3
 * @description		Gets the distance in meters between two locations
 */
int utc_location_manager_get_distance_p(void)
{
	double start_latitude = 30.0;
	double start_longitude = 30.0;
	double end_latitude = 50.0;
	double end_longitude = 50.0;
	double distance = 0.0;

	ret = location_manager_get_distance(start_latitude, start_longitude, end_latitude, end_longitude, &distance);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_get_distance_n
 * @since_tizen		2.3
 * @description		Gets the distance in meters between two locations with invalid parameters
 */
int utc_location_manager_get_distance_n(void)
{
	double start_latitude = 30.0;
	double start_longitude = 30.0;
	double end_latitude = 50.0;
	double end_longitude = 50.0;
	double distance = 0.0;

	ret = location_manager_get_distance(200, start_longitude, end_latitude, end_longitude, &distance);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_distance(start_latitude, 200, end_latitude, end_longitude, &distance);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_distance(start_latitude, start_longitude, 200, end_longitude, &distance);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_distance(start_latitude, start_longitude, end_latitude, 200, &distance);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_get_distance(start_latitude, start_longitude, end_latitude, end_longitude, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_is_enabled_method_p
 * @since_tizen		2.3
 * @description		Checks whether the given location method is enabled or not on setting
 */
int utc_location_manager_is_enabled_method_p(void)
{
	bool enabled = false;

	ret = location_manager_is_enabled_method(LOCATIONS_METHOD_HYBRID, &enabled);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_is_enabled_method_p2
 * @since_tizen		2.3
 * @description		Checks whether the given location method is enabled or not on setting
 */
int utc_location_manager_is_enabled_method_p2(void)
{
	bool enabled = false;

	ret = location_manager_is_enabled_method(LOCATIONS_METHOD_GPS, &enabled);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_is_enabled_method_p3
 * @since_tizen		2.3
 * @description		Checks whether the given location method is enabled or not on setting
 */
int utc_location_manager_is_enabled_method_p3(void)
{
	bool enabled = false;

	ret = location_manager_is_enabled_method(LOCATIONS_METHOD_WPS, &enabled);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_is_enabled_method_n
 * @since_tizen		2.3
 * @description		Checks the method is available or not with invalid parameter
 */
int utc_location_manager_is_enabled_method_n(void)
{
	bool enabled = false;
	ret = location_manager_is_enabled_method(LOCATIONS_METHOD_NONE, &enabled);
	CHECK_INCORRECT_METHOD(is_location_supported, ret);

	ret = location_manager_is_enabled_method(LOCATIONS_METHOD_GPS, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_request_single_location_p
 * @since_tizen		2.3
 * @description		Request to update current location once
 */
int utc_location_manager_request_single_location_p(void)
{
	__location_updated = false;
	ret = location_manager_request_single_location(manager, 30, __location_updated_cb, NULL);

	if (is_location_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		wait_for_service();
		assert(__location_updated);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_location_manager_request_single_location_p2
 * @since_tizen		2.3
 * @description		Request to update current location once
 */
int utc_location_manager_request_single_location_p2(void)
{
	location_manager_h manager2 = NULL;
	__location_updated = false;

	if (is_location_supported) {
		ret = cleanup_default_handle();
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		if (is_gps_supported) {
			ret = location_manager_create(LOCATIONS_METHOD_GPS, &manager2);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			ret = location_manager_request_single_location(manager2, 30, __location_updated_cb, NULL);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			wait_for_service();
			assert(__location_updated);
		} else if (is_wps_supported) {
			ret = location_manager_create(LOCATIONS_METHOD_WPS, &manager2);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			ret = location_manager_request_single_location(manager2, 30, __location_updated_cb, NULL);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			wait_for_service();
			assert(__location_updated);
		}

		if (manager2) {
			ret = location_manager_destroy(manager2);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			manager2 = NULL;
		}
	} else {
		ret = location_manager_request_single_location(manager2, 30, __location_updated_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_request_single_location_n
 * @since_tizen		2.3
 * @description		Request to update current location once with invalid parameters
 */
int utc_location_manager_request_single_location_n(void)
{
	ret = location_manager_request_single_location(NULL, 2, __location_updated_cb, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_request_single_location(manager, 2, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_request_single_location(manager, 0, __location_updated_cb, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_request_single_location_n2
 * @since_tizen		3.0
 * @description		Request to update current location once with invalid parameters
 */
int utc_location_manager_request_single_location_n2(void)
{
	location_manager_h manager2 = NULL;

	if (is_location_supported) {
		ret = cleanup_default_handle();
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_create(LOCATIONS_METHOD_PASSIVE, &manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		ret = location_manager_request_single_location(manager2, 30, __location_updated_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_INCORRECT_METHOD);

		if (manager2) {
			ret = location_manager_destroy(manager2);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			manager2 = NULL;
		}
	} else {
		ret = location_manager_request_single_location(manager2, 30, __location_updated_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_request_single_location_n3
 * @since_tizen		4.0
 * @description		Request to update current location once with invalid parameters
 */
int utc_location_manager_request_single_location_n3(void)
{
	location_manager_h manager2 = NULL;
	ret = cleanup_default_handle();
	assert_eq(ret, LOCATIONS_ERROR_NONE);

	ret = location_manager_create(LOCATIONS_METHOD_FUSED, &manager2);
	if (is_fused_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		ret = location_manager_request_single_location(manager2, 30, __location_updated_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_INCORRECT_METHOD);

		if (manager2) {
			ret = location_manager_destroy(manager2);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			manager2 = NULL;
		}
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_is_enabled_mock_location_p
 * @since_tizen		3.0
 * @description		Checks whether the mock location is enabled or not
 */
int utc_location_manager_is_enabled_mock_location_p(void)
{
	bool enabled = false;
	ret = location_manager_is_enabled_mock_location(&enabled);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_is_enabled_mock_location_n
 * @since_tizen		3.0
 * @description		Checks whether the mock location is enabled or not
 */
int utc_location_manager_is_enabled_mock_location_n(void)
{
	ret = location_manager_is_enabled_mock_location(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_enable_mock_location_p
 * @since_tizen		3.0
 * @description		Enable mock location
 */
int utc_location_manager_enable_mock_location_p(void)
{
	ret = location_manager_enable_mock_location(true);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_manager_enable_mock_location(false);
	CHECK_ERROR_NONE(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_manager_set_mock_location_p
 * @since_tizen		3.0
 * @description		Set mock location
 */
int utc_location_manager_set_mock_location_p(void)
{
	double latitude = 10.0;
	double longitude = 20.0;
	double altitude = 30.0;
	double speed = 4.0;
	double direction = 50.1;
	double accuracy = 6.0;
	time_t timestamp = 0.0;
	service_enabled = false;

	if (is_location_supported) {
		ret = location_manager_enable_mock_location(true);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_set_mock_location(manager, latitude, longitude, altitude, speed, direction, accuracy);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_get_position(manager, &altitude, &latitude, &longitude, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_clear_mock_location(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_service_state_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_enable_mock_location(false);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_set_mock_location(manager, latitude, longitude, altitude, speed, direction, accuracy);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_set_mock_location_n
 * @since_tizen		3.0
 * @description		Set mock location
 */
int utc_location_manager_set_mock_location_n(void)
{
	double latitude = 10.0;
	double longitude = 20.0;
	double altitude = 30.0;
	double speed = 4.0;
	double direction = 50.1;
	double accuracy = 6.0;

	ret = location_manager_set_mock_location(NULL, latitude, longitude, altitude, speed, direction, accuracy);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	latitude = 190.0;
	ret = location_manager_set_mock_location(manager, latitude, longitude, altitude, speed, direction, accuracy);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	if (is_location_supported) {
		ret = location_manager_enable_mock_location(false);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		latitude = 10.0;
		ret = location_manager_set_mock_location(manager, latitude, longitude, altitude, speed, direction, accuracy);
		assert_eq(ret, LOCATIONS_ERROR_SETTING_OFF);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_clear_mock_location_p
 * @since_tizen		3.0
 * @description		Clear mock location
 */
int utc_location_manager_clear_mock_location_p(void)
{
	double latitude = 10.0;
	double longitude = 20.0;
	double altitude = 30.0;
	double speed = 4.0;
	double direction = 50.1;
	double accuracy = 6.0;
	time_t timestamp = 0.0;
	service_enabled = false;

	if (is_location_supported) {
		ret = location_manager_enable_mock_location(true);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_set_mock_location(manager, latitude, longitude, altitude, speed, direction, accuracy);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled);

		ret = location_manager_get_position(manager, &altitude, &latitude, &longitude, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_clear_mock_location(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_enable_mock_location(false);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_clear_mock_location(manager);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_clear_mock_location_n
 * @since_tizen		3.0
 * @description		Clear mock location
 */
int utc_location_manager_clear_mock_location_n(void)
{
	ret = location_manager_clear_mock_location(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	if (is_location_supported) {
		ret = location_manager_enable_mock_location(false);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_clear_mock_location(manager);
		assert_eq(ret, LOCATIONS_ERROR_SETTING_OFF);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_set_fused_mode_p
 * @since_tizen		4.0
 * @description		Set fused mode
 */
int utc_location_manager_set_fused_mode_p(void)
{
	location_manager_h manager2 = NULL;

	ret = cleanup_default_handle();
	assert_eq(ret, LOCATIONS_ERROR_NONE);

	ret = location_manager_create(LOCATIONS_METHOD_FUSED, &manager2);
	if (is_fused_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_set_fused_mode(manager2, LOCATIONS_FUSED_HIGH_ACCURACY);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_destroy(manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		manager2 = NULL;
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_manager_set_fused_mode_n
 * @since_tizen		4.0
 * @description		Set fused mode with invalid parameter
 */
int utc_location_manager_set_fused_mode_n(void)
{
	ret = location_manager_set_fused_mode(NULL, LOCATIONS_FUSED_HIGH_ACCURACY);
	CHECK_INVALID_PARAMETER(is_fused_supported, ret);

	ret = location_manager_set_fused_mode(manager, LOCATIONS_FUSED_HIGH_ACCURACY - 1);
	CHECK_INVALID_PARAMETER(is_fused_supported, ret);

	ret = location_manager_set_fused_mode(manager, LOCATIONS_FUSED_BALANCED_POWER + 1);
	CHECK_INVALID_PARAMETER(is_fused_supported, ret);

	ret = location_manager_set_fused_mode(manager, LOCATIONS_FUSED_HIGH_ACCURACY);
	CHECK_INCORRECT_METHOD(is_fused_supported, ret);

	return 0;
}

