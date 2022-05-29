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
static bool __location_batch = false;
static bool __get_batch = false;
static int interval = 1;
static int batch_period = 5;


static void wait_for_service()
{
	g_mainloop = g_main_loop_new(NULL, 0);
	g_main_loop_run(g_mainloop);
}

static void wait_for_callback()
{
	g_mainloop = g_main_loop_new(NULL, 0);
	g_main_loop_run(g_mainloop);
}

static void __location_batch_cb(int num_of_location, void *user_data)
{
	__location_batch = true;
	if (g_mainloop) {
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}
}

static bool __get_batch_cb(double latitude, double longitude, double altitude, double speed, double direction, double horizontal, double vertical, time_t timestamp, void *user_data)
{
	__get_batch = true;
	return true;
}

void utc_location_manager_batch_startup(void)
{
	system_info_get_platform_bool(WPS_FEATURE, &is_wps_supported);
	system_info_get_platform_bool(BATCH_FEATURE, &is_batch_supported);

	if(manager == NULL) {
		location_manager_create(LOCATIONS_METHOD_GPS, &manager);
	}
}

void utc_location_manager_batch_cleanup(void)
{
	if(manager) {
		location_manager_destroy(manager);
		manager = NULL;
	}

	if (g_mainloop) {
		g_main_loop_quit(g_mainloop);
		g_mainloop = NULL;
	}
}


int utc_location_manager_start_batch_p(void)
{
	__location_batch = false;

	if(is_batch_supported) {
		ret = location_manager_set_location_batch_cb(manager, __location_batch_cb, interval, batch_period, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start_batch(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(__location_batch);

		ret = location_manager_stop_batch(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_location_batch_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_start_batch(manager);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_location_manager_start_batch_n(void)
{
	ret = location_manager_start_batch(NULL);
	CHECK_INVALID_PARAMETER(is_batch_supported, ret);

	if(is_wps_supported) {
		if(manager) {
			location_manager_destroy(manager);
			manager = NULL;
		}

		location_manager_h manager2 = NULL;
		ret = location_manager_create(LOCATIONS_METHOD_WPS, &manager2);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start_batch(manager2);
		if (is_batch_supported) {
			assert_eq(ret, LOCATIONS_ERROR_INCORRECT_METHOD);
		} else {
			assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
		}

		if (manager2) {
			ret = location_manager_destroy(manager2);
			assert_eq(ret, LOCATIONS_ERROR_NONE);
			manager2 = NULL;
		}
	}

	return 0;
}

int utc_location_manager_stop_batch_p(void)
{
	__get_batch = false;
	__location_batch = false;

	if(is_batch_supported) {
		ret = location_manager_set_location_batch_cb(manager, __location_batch_cb, interval, batch_period, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start_batch(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(__location_batch);

		ret = location_manager_stop_batch(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_location_batch_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_stop_batch(manager);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_location_manager_stop_batch_n(void)
{
	ret = location_manager_stop_batch(NULL);
	CHECK_INVALID_PARAMETER(is_batch_supported, ret);
	return 0;
}

int utc_location_manager_foreach_location_batch_p(void)
{
	__get_batch = false;
	__location_batch = false;

	if(is_batch_supported) {
		ret = location_manager_set_location_batch_cb(manager, __location_batch_cb, interval, batch_period, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_start_batch(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_service();
		assert(__location_batch);

		ret = location_manager_foreach_location_batch(manager, __get_batch_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		wait_for_callback();
		assert(__get_batch);

		ret = location_manager_stop_batch(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_location_batch_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_foreach_location_batch(manager, __get_batch_cb, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_location_manager_foreach_location_batch_n(void)
{
	ret = location_manager_foreach_location_batch(manager, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_batch_supported, ret);

	ret = location_manager_foreach_location_batch(NULL, __get_batch_cb, NULL);
	CHECK_INVALID_PARAMETER(is_batch_supported, ret);

	return 0;
}

int utc_location_manager_foreach_location_batch_n2(void)
{
	ret = location_manager_foreach_location_batch(manager, __get_batch_cb, NULL);
	if(is_batch_supported) {
		assert_eq(ret, LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_location_manager_set_location_batch_cb_p(void)
{
	ret = location_manager_set_location_batch_cb(manager, __location_batch_cb, interval, batch_period, NULL);
	if(is_batch_supported) {
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_location_batch_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_location_manager_set_location_batch_cb_n(void)
{
	ret = location_manager_set_location_batch_cb(NULL, __location_batch_cb, interval, batch_period, NULL);
	CHECK_INVALID_PARAMETER(is_batch_supported, ret);

	ret = location_manager_set_location_batch_cb(manager, NULL, interval, batch_period, NULL);
	CHECK_INVALID_PARAMETER(is_batch_supported, ret);

	ret = location_manager_set_location_batch_cb(manager, __location_batch_cb, 0, batch_period, NULL);
	CHECK_INVALID_PARAMETER(is_batch_supported, ret);

	ret = location_manager_set_location_batch_cb(manager, __location_batch_cb, interval, 60001, NULL);
	CHECK_INVALID_PARAMETER(is_batch_supported, ret);

	ret = location_manager_set_location_batch_cb(manager, __location_batch_cb, 5, 3, NULL);
	CHECK_INVALID_PARAMETER(is_batch_supported, ret);

	return 0;
}

int utc_location_manager_unset_location_batch_cb_p(void)
{
	if(is_batch_supported) {
		ret = location_manager_set_location_batch_cb(manager, __location_batch_cb, interval, batch_period, NULL);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_manager_unset_location_batch_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_manager_unset_location_batch_cb(manager);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_location_manager_unset_location_batch_cb_n(void)
{
	ret = location_manager_unset_location_batch_cb(NULL);
	CHECK_INVALID_PARAMETER(is_batch_supported, ret);
	return 0;
}


