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

//& set: LocationGpsStatus
static GMainLoop *g_mainloop = NULL;
static location_manager_h manager = NULL;
static bool satellite_enabled = false;
static bool __get_satellites = false;
static int interval = 1;

static void wait_for_service()
{
	g_mainloop = g_main_loop_new(NULL, 0);
	g_main_loop_run(g_mainloop);

}

static void wait_for_satellite()
{
	int timeout = 0;
	for (timeout = 0; timeout < 20; timeout++) {
		if (__get_satellites) {
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

	if (service_enabled && satellite_enabled) {
		if (g_mainloop) {
			g_main_loop_quit(g_mainloop);
			g_mainloop = NULL;
		}
	}
}

static void __satellite_updated_cb(int num_of_active, int num_of_inview, time_t timestamp, void *user_data)
{
	satellite_enabled = true;
	if (service_enabled && satellite_enabled) {
		if (g_mainloop) {
			g_main_loop_quit(g_mainloop);
			g_mainloop = NULL;
		}
	}
}

static bool __get_satellites_cb(unsigned int azimuth, unsigned int elevation, unsigned int prn, int snr, bool is_in_use, void *user_data)
{
	__get_satellites = true;
	return true;
}

/**
 * @function		utc_location_gps_status_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_location_gps_status_startup(void)
{
	service_enabled = false;
	satellite_enabled = false;
	__get_satellites = false;

	system_info_get_platform_bool(GPS_FEATURE, &is_gps_supported);
	system_info_get_platform_bool(GPS_SATELLITE_FEATURE, &is_gps_satellite_supported);

	if (is_gps_supported) {
		if (manager == NULL) {
			location_manager_create(LOCATIONS_METHOD_GPS, &manager);
		}
		location_manager_set_service_state_changed_cb(manager, __service_state_changed_cb, NULL);
	}
}

/**
 * @function		utc_location_gps_status_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_location_gps_status_cleanup(void)
{
	if (is_gps_supported) {
		location_manager_unset_service_state_changed_cb(manager);

		if (manager) {
			location_manager_destroy(manager);
			manager = NULL;
		}
	}

	if (g_mainloop) {
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}
}

/**
 * @testcase		utc_location_gps_status_get_nmea_p
 * @since_tizen		2.3
 * @description		Gets the GPS NMEA data
 */
int utc_location_gps_status_get_nmea_p(void)
{
	char *nmea = NULL;

	if (is_gps_satellite_supported) {
		ret = gps_status_set_satellite_updated_cb(manager, __satellite_updated_cb, interval, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled && satellite_enabled);

		ret = gps_status_get_nmea(manager, &nmea);
		if (nmea) {
			free(nmea);
		}
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = gps_status_unset_satellite_updated_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = gps_status_get_nmea(manager, &nmea);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_gps_status_get_nmea_n
 * @since_tizen		2.3
 * @description		Gets the GPS NMEA data with invalid parameters
 */
int utc_location_gps_status_get_nmea_n(void)
{
	char *nmea = NULL;
	ret = gps_status_get_nmea(manager, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_get_nmea(NULL, &nmea);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_gps_status_get_nmea_n2
 * @since_tizen		2.3
 * @description		Gets the GPS NMEA data with invalid parameters
 */
int utc_location_gps_status_get_nmea_n2(void)
{
	char *nmea = NULL;
	ret = gps_status_get_nmea(manager, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_get_nmea(NULL, &nmea);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_gps_status_set_satellite_updated_cb_p
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked at defined interval with updated satellite information
 */
int utc_location_gps_status_set_satellite_updated_cb_p(void)
{
	ret = gps_status_set_satellite_updated_cb(manager, __satellite_updated_cb, interval, NULL);
	if (is_gps_satellite_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled && satellite_enabled);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_service_state_changed_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_gps_status_set_satellite_updated_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked at defined interval with updated satellite information with invalid parameters
 */
int utc_location_gps_status_set_satellite_updated_cb_n(void)
{
	ret = gps_status_set_satellite_updated_cb(manager, NULL, interval, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_set_satellite_updated_cb(NULL, __satellite_updated_cb, interval, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_set_satellite_updated_cb(manager, __satellite_updated_cb, 121, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_gps_status_unset_satellite_updated_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the callback function
 */
int utc_location_gps_status_unset_satellite_updated_cb_p(void)
{
	ret = gps_status_set_satellite_updated_cb(manager, __satellite_updated_cb, interval, NULL);
	CHECK(is_gps_satellite_supported, ret);

	ret = gps_status_unset_satellite_updated_cb(manager);
	CHECK_ERROR_NONE(is_gps_satellite_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_gps_status_unset_satellite_updated_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the callback function with invalid parameter
 */
int utc_location_gps_status_unset_satellite_updated_cb_n(void)
{
	ret = gps_status_unset_satellite_updated_cb(NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_gps_status_get_satellite_p
 * @since_tizen		2.3
 * @description		Gets the information of satellites
 */
int utc_location_gps_status_get_satellite_p(void)
{
	int num_of_active = 0, num_of_inview = 0;
	time_t timestamp;

	if (is_gps_satellite_supported) {
		ret = gps_status_set_satellite_updated_cb(manager, __satellite_updated_cb, interval, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled && satellite_enabled);

		ret = gps_status_get_satellite(manager, &num_of_active, &num_of_inview, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = gps_status_unset_satellite_updated_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = gps_status_get_satellite(manager, &num_of_active, &num_of_inview, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_gps_status_get_satellite_n
 * @since_tizen		2.3
 * @description		Gets the information of satellites with invalid parameters
 */
int utc_location_gps_status_get_satellite_n(void)
{
	int num_of_active = 0, num_of_inview = 0;
	time_t timestamp;

	ret = gps_status_get_satellite(manager, NULL, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_get_satellite(NULL, &num_of_active, &num_of_inview, &timestamp);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_get_satellite(manager, NULL, &num_of_inview, &timestamp);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_get_satellite(manager, &num_of_active, NULL, &timestamp);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_get_satellite(manager, &num_of_active, &num_of_inview, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_gps_status_foreach_satellites_in_view_p
 * @since_tizen		2.3
 * @description		Invokes the callback function for each satellite
 */
int utc_location_gps_status_foreach_satellites_in_view_p(void)
{
	if (is_gps_satellite_supported) {
		ret = gps_status_set_satellite_updated_cb(manager, __satellite_updated_cb, interval, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled && satellite_enabled);

		ret = gps_status_foreach_satellites_in_view(manager, __get_satellites_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_satellite();
		assert(__get_satellites);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = gps_status_unset_satellite_updated_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = gps_status_foreach_satellites_in_view(manager, __get_satellites_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_gps_status_foreach_satellites_in_view_n
 * @since_tizen		2.3
 * @description		Invokes the callback function for each satellite with invalid parameters
 */
int utc_location_gps_status_foreach_satellites_in_view_n(void)
{
	ret = gps_status_foreach_satellites_in_view(manager, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_foreach_satellites_in_view(NULL, __get_satellites_cb, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_gps_status_foreach_last_satellites_in_view_p
 * @since_tizen		2.3
 * @description		Invokes the callback function for each last satellite which is recorded
 */
int utc_location_gps_status_foreach_last_satellites_in_view_p(void)
{
	if (is_gps_satellite_supported) {
		ret = gps_status_set_satellite_updated_cb(manager, __satellite_updated_cb, interval, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled && satellite_enabled);

		ret = gps_status_foreach_last_satellites_in_view(manager, __get_satellites_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_satellite();
		assert(__get_satellites);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = gps_status_unset_satellite_updated_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = gps_status_foreach_last_satellites_in_view(manager, __get_satellites_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_gps_status_foreach_last_satellites_in_view_n
 * @since_tizen		2.3
 * @description		Invokes the callback function for each last satellite which is recorded with invalid parameters
 */
int utc_location_gps_status_foreach_last_satellites_in_view_n(void)
{
	ret = gps_status_foreach_last_satellites_in_view(manager, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_foreach_last_satellites_in_view(NULL, __get_satellites_cb, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_gps_status_get_last_satellite_p
 * @since_tizen		2.3
 * @description		Gets the last information of satellites
 */
int utc_location_gps_status_get_last_satellite_p(void)
{
	int num_of_inview = 0, num_of_active = 0;
	time_t timestamp;

	if (is_gps_satellite_supported) {
		ret = gps_status_set_satellite_updated_cb(manager, __satellite_updated_cb, interval, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(service_enabled && satellite_enabled);

		ret = gps_status_get_last_satellite(manager, &num_of_active, &num_of_inview, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_stop(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = gps_status_unset_satellite_updated_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = gps_status_get_last_satellite(manager, &num_of_active, &num_of_inview, &timestamp);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_gps_status_get_last_satellite_n
 * @since_tizen		2.3
 * @description		Gets the last information of satellites with invalid parameters
 */
int utc_location_gps_status_get_last_satellite_n(void)
{
	int num_of_inview = 0, num_of_active = 0;
	time_t timestamp;

	ret = gps_status_get_last_satellite(NULL, &num_of_active, &num_of_inview, &timestamp);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_get_last_satellite(manager, NULL, &num_of_inview, &timestamp);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_get_last_satellite(manager, &num_of_active, NULL, &timestamp);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	ret = gps_status_get_last_satellite(manager, &num_of_active, &num_of_inview, NULL);
	CHECK_INVALID_PARAMETER(is_gps_satellite_supported, ret);

	return 0;
}
