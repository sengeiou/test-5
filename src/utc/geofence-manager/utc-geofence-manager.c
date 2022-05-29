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
#include <stdio.h>
#include <string.h>
#include "geofence_manager.h"
#include <system_info.h>
#include <unistd.h>
#include "glib.h"

int ret;
static bool bFenceListRetrieval = false;
static bool bPlaceListRetrieval = false;
static bool bEventSuccess = false;
static bool bStateInOut = false;
static bool bStateProximity = false;

static bool bEventPlaceAdded = false;
static bool bEventPlaceRemoved = false;
static bool bEventPlaceUpdated = false;

static bool bEventFenceAdded = false;
static bool bEventFenceRemoved = false;
static bool bEventFenceStarted = false;
static bool bEventFenceStopped = false;

static bool is_geofence_supported = false;
static bool supported;
static char* geofence_feature = "http://tizen.org/feature/location.geofence";

geofence_manager_h pGeofenceManager;
geofence_h pGeofenceParams;
geofence_status_h pStatus;
static GMainLoop *mainloop = NULL;

static gboolean timeout_func(gpointer data)
{
	g_main_loop_quit(mainloop);
	g_main_loop_unref(mainloop);
	mainloop = NULL;
	return FALSE;
}

static int wait_for_callback()
{
	int timeout_id = 0;
	mainloop = g_main_loop_new(NULL, FALSE);
	timeout_id = g_timeout_add(5000, timeout_func, NULL);
	g_main_loop_run(mainloop);
	g_source_remove(timeout_id);
	return 0;
}

static int wait_for_placecallback()
{
	int timeout_id = 0;
	mainloop = g_main_loop_new(NULL, FALSE);
	timeout_id = g_timeout_add(5000, timeout_func, NULL);
	g_main_loop_run(mainloop);
	g_source_remove(timeout_id);
	return 0;
}

static int wait_for_eventcallback()
{
	int timeout_id = 0;
	mainloop = g_main_loop_new(NULL, FALSE);
	timeout_id = g_timeout_add(5000, timeout_func, NULL);
	g_main_loop_run(mainloop);
	g_source_remove(timeout_id);
	return 0;
}

void geofence_state_changed_cb_p(int geofence_id, geofence_state_e state, void *user_data)
{
	if(state == GEOFENCE_STATE_IN || state == GEOFENCE_STATE_OUT || state == GEOFENCE_STATE_UNCERTAIN)
	{
		bStateInOut = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	bStateInOut = false;
}

void geofence_proximity_state_changed_cb_p(int geofence_id, geofence_proximity_state_e state, geofence_proximity_provider_e provider, void *user_data)
{
	if(state == GEOFENCE_PROXIMITY_STATE_UNCERTAIN || state == GEOFENCE_PROXIMITY_STATE_FAR || state == GEOFENCE_PROXIMITY_STATE_NEAR || state == GEOFENCE_PROXIMITY_STATE_IMMEDIATE)
	{
		bStateProximity = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	bStateProximity = false;
}

//geofence_event_cb

void __geofence_event_cb_p(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(error == GEOFENCE_MANAGER_ERROR_NONE)
	{
		bEventSuccess = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	{
		bEventSuccess = false;
	}
}

void __geofence_event_padded(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(error == GEOFENCE_MANAGER_ERROR_NONE && manage == GEOFENCE_MANAGE_PLACE_ADDED)
	{
		bEventPlaceAdded = true;
		bEventSuccess = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;

		}
	}
	else
	{
		bEventSuccess = false;
		bEventPlaceAdded = false;
	}
}

void __geofence_event_premoved(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(error == GEOFENCE_MANAGER_ERROR_NONE && manage == GEOFENCE_MANAGE_PLACE_REMOVED)
	{
		bEventPlaceRemoved = true;
		bEventSuccess = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	{
		bEventSuccess = false;
		bEventPlaceRemoved = false;
	}
}

void __geofence_event_idnot_premoved(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(error == GEOFENCE_MANAGER_ERROR_INVALID_ID && manage == GEOFENCE_MANAGE_PLACE_REMOVED)
	{
		bEventSuccess = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	{
		bEventSuccess = false;
		bEventPlaceRemoved = false;
	}
}

void __geofence_event_notauthorized_premoved(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if( place_id < 3)
	{
		if(error == GEOFENCE_MANAGER_ERROR_PLACE_ACCESS_DENIED && manage == GEOFENCE_MANAGE_PLACE_REMOVED)
		{
			bEventSuccess = true;
			if(mainloop)
			{
				g_main_loop_quit(mainloop);
				g_main_loop_unref(mainloop);
				mainloop = NULL;
			}
		}
	}
	else
	{
		bEventSuccess = false;
		bEventPlaceRemoved = false;
	}
}

void __geofence_event_pupdated(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(error == GEOFENCE_MANAGER_ERROR_NONE && manage == GEOFENCE_MANAGE_PLACE_UPDATED)
	{
		bEventPlaceUpdated = true;
		bEventSuccess = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	{
		bEventSuccess = false;
		bEventPlaceUpdated = false;
	}
}

void __geofence_event_fadded(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(error == GEOFENCE_MANAGER_ERROR_NONE && manage == GEOFENCE_MANAGE_FENCE_ADDED)
	{
		bEventFenceAdded = true;
		bEventSuccess = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	{
		bEventSuccess = false;
		bEventFenceAdded = false;
	}
}

void __geofence_event_fremoved(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(error == GEOFENCE_MANAGER_ERROR_NONE && manage == GEOFENCE_MANAGE_FENCE_REMOVED)
	{
		bEventFenceRemoved = true;
		bEventSuccess = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	{
		bEventSuccess = false;
		bEventFenceRemoved = false;
	}
}

void __geofence_event_idnot_fremoved(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(error == GEOFENCE_MANAGER_ERROR_INVALID_ID && manage == GEOFENCE_MANAGE_FENCE_REMOVED)
	{
		bEventSuccess = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	{
		bEventSuccess = false;
		bEventFenceRemoved = false;
	}
}

void __geofence_event_fstarted(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(manage == GEOFENCE_MANAGE_FENCE_STARTED)
	{
		bEventFenceStarted = true;
		if(error == GEOFENCE_MANAGER_ERROR_NONE)
		{
			bEventSuccess = true;
			if(mainloop)
			{
				g_main_loop_quit(mainloop);
				g_main_loop_unref(mainloop);
				mainloop = NULL;
			}
		}
	}
	else
	{
		bEventSuccess = false;
		bEventFenceStarted = false;
	}
}

void __geofence_event_idnot_fstarted(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(error == GEOFENCE_MANAGER_ERROR_INVALID_ID && manage == GEOFENCE_MANAGE_FENCE_STARTED)
	{
		bEventSuccess = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	{
		bEventSuccess = false;
		bEventFenceStarted = false;
	}
}

void __geofence_event_fstopped(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	if(error == GEOFENCE_MANAGER_ERROR_NONE && manage == GEOFENCE_MANAGE_FENCE_STOPPED)
	{
		bEventFenceStopped = true;
		bEventSuccess = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	else
	{
		bEventSuccess = false;
		bEventFenceStopped = false;
	}
}

bool __geofence_manager_fence_cb(int geofence_id, geofence_h params, int index, int total_fence_count, void *user_data)
{
	if(index == total_fence_count)
	{
		bFenceListRetrieval = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	return true;
}

bool __geofence_manager_place_cb(int place_id, const char *place_name, int place_index, int place_cnt, void *user_data)
{
	if(place_index == place_cnt)
	{
		bPlaceListRetrieval = true;
		if(mainloop)
		{
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
			mainloop = NULL;
		}
	}
	return true;
}

/**
 * @function		utc_geofence_manager_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_geofence_manager_startup(void)
{
	system_info_get_platform_bool(geofence_feature,&is_geofence_supported);
}

/**
 * @function		utc_geofence_manager_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_geofence_manager_cleanup(void)
{
}

//is_support
/**
 * @testcase		utc_geofence_manager_is_supported_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_is_supported()
 */
int utc_geofence_manager_is_supported_p(void)
{
    ret = geofence_manager_is_supported(&supported);

    if(is_geofence_supported)
    {
        assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
    }
    else
    {
        assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_geofence_manager_is_supported_n
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_is_supported()
 */
int utc_geofence_manager_is_supported_n(void)
{
    ret = geofence_manager_is_supported(NULL);

    if(is_geofence_supported)
    {
        assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
    }
    else
    {
        assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
    }

    return 0;
}


//1 create
/**
 * @testcase		utc_geofence_manager_create_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_create()
 */
int utc_geofence_manager_create_p(void)
{
	ret = geofence_manager_create(&pGeofenceManager);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_create_n
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_create()
 */
int utc_geofence_manager_create_n(void)
{
	ret = geofence_manager_create(NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//2 destroy

/**
 * @testcase		utc_geofence_manager_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_destroy()
 */
int utc_geofence_manager_destroy_p(void)
{
	if(is_geofence_supported)
	{
		/* tested in utc_geofence_manager_create_p */
	}
	else
	{
		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_destroy()
 */
int utc_geofence_manager_destroy_n(void)
{
	ret = geofence_manager_destroy(NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 3 set_geofence_state_changed_cb
/**
 * @testcase		utc_geofence_manager_set_geofence_event_cb_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_set_geofence_event_cb()
 */
int utc_geofence_manager_set_geofence_event_cb_p(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_set_geofence_event_cb_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_set_geofence_event_cb()
 */
int utc_geofence_manager_set_geofence_event_cb_n1(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_set_geofence_event_cb_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_set_geofence_event_cb()
 */
int utc_geofence_manager_set_geofence_event_cb_n2(void)
{
	ret = geofence_manager_set_geofence_event_cb(NULL, __geofence_event_cb_p, (void*)NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 4 geofence_manager_unset_geofence_event

/**
 * @testcase		utc_geofence_manager_unset_geofence_event_cb_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_unset_geofence_event_cb()
 */
int utc_geofence_manager_unset_geofence_event_cb_p(void)
{
	if(is_geofence_supported)
	{
		/* tested in utc_geofence_manager_set_geofence_event_cb_p */
	}
	else
	{
		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_unset_geofence_event_cb_n
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_unset_geofence_event_cb()
 */
int utc_geofence_manager_unset_geofence_event_cb_n(void)
{
	ret = geofence_manager_unset_geofence_event_cb(NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 5 create_geopoint

/**
 * @testcase		utc_geofence_create_geopoint_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_create_geopoint()
 */
int utc_geofence_create_geopoint_p(void)
{
	int place_id = 1;
	const char* address = "geopoint";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;

	ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_geopoint_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_geopoint()
 */
int utc_geofence_create_geopoint_n1(void)
{
	int place_id = -1;
	const char* address = "geopoint";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;

	ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_geopoint_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_geopoint()
 */
int utc_geofence_create_geopoint_n2(void)
{
	int place_id = 1;
	const char* address = "geopoint";
	double lat = 91, lon = 77.5667;
	int radius = 100;

	ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_geopoint_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_geopoint()
 */
int utc_geofence_create_geopoint_n3(void)
{
	int place_id = 1;
	const char* address = "geopoint";
	double lat = 12.9667, lon = 181;
	int radius = 100;

	ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_geopoint_n4
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_geopoint()
 */
int utc_geofence_create_geopoint_n4(void)
{
	int place_id = 1;
	double lat = 12.9667, lon = 77.5667;
	int radius = 0;
	const char* address = "geopoint";

	ret = geofence_create_geopoint(place_id, lat, lon, radius, address, NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_geopoint_n5
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_geopoint()
 */
int utc_geofence_create_geopoint_n5(void)
{
	int place_id = 1;
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;

	ret = geofence_create_geopoint(place_id, lat, lon, radius, NULL, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_geopoint_n6
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_geopoint()
 */
int utc_geofence_create_geopoint_n6(void)
{
	int place_id = 1;
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	const char* address = "geopoint";

	ret = geofence_create_geopoint(place_id, lat, lon, radius, address, NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 6 create_bluetooth

/**
 * @testcase		utc_geofence_create_bluetooth_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_create_bluetooth()
 */
int utc_geofence_create_bluetooth_p(void)
{
	int place_id = 1;
	const char* ssid = "BT";
	const char* bssid = "88:30:8A:6C:28:16";

	ret = geofence_create_bluetooth(place_id, bssid, ssid, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_bluetooth_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_bluetooth()
 */
int utc_geofence_create_bluetooth_n1(void)
{
	const char* bssid = "88:30:8A:6C:28:16";
	const char* ssid = "BT";

	ret = geofence_create_bluetooth(-1, bssid, ssid, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_bluetooth_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_bluetooth()
 */
int utc_geofence_create_bluetooth_n2(void)
{
	int place_id = 1;
	const char* ssid = "BT";

	ret = geofence_create_bluetooth(place_id, NULL, ssid, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_bluetooth_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_bluetooth()
 */
int utc_geofence_create_bluetooth_n3(void)
{
	int place_id = 1;
	const char* bssid = "88:30:8A:6C:28:16";

	ret = geofence_create_bluetooth(place_id, bssid, NULL, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_bluetooth_n4
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_bluetooth()
 */
int utc_geofence_create_bluetooth_n4(void)
{
	int place_id = 1;
	const char* bssid = "88:30:8A:6C:28:16";
	const char* ssid = "BT";

	ret = geofence_create_bluetooth(place_id, bssid, ssid, NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 7 create_wifi

/**
 * @testcase		utc_geofence_create_wifi_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_create_wifi()
 */
int utc_geofence_create_wifi_p(void)
{
	int place_id = 1;
	const char* ssid = "WIFI";
	const char* bssid = "88:30:8A:6C:28:16";

	ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_wifi_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_wifi()
 */
int utc_geofence_create_wifi_n1(void)
{
	const char* ssid = "WIFI";
	const char* bssid = "88:30:8A:6C:28:16";

	ret = geofence_create_wifi(-1, bssid, ssid, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_wifi_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_wifi()
 */
int utc_geofence_create_wifi_n2(void)
{
	int place_id = 1;
	const char* ssid = "WIFI";

	ret = geofence_create_wifi(place_id, NULL, ssid, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_geofence_create_wifi_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_wifi()
 */
int utc_geofence_create_wifi_n3(void)
{
	int place_id = 1;
	const char* bssid = "88:30:8A:6C:28:16";

	ret = geofence_create_wifi(place_id, bssid, NULL, &pGeofenceParams);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_create_wifi_n4
 * @since_tizen		2.4
 * @description		Negative test case of geofence_create_wifi()
 */
int utc_geofence_create_wifi_n4(void)
{
	int place_id = 1;
	const char* bssid = "88:30:8A:6C:28:16";
	const char* ssid = "WIFI";

	ret = geofence_create_wifi(place_id, bssid, ssid, NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//  8 destroy

/**
 * @testcase		utc_geofence_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_destroy()
 */
int utc_geofence_destroy_p(void)
{
	if(is_geofence_supported)
	{
		/* tested in utc_geofence_create_wifi_p */
	}
	else
	{
		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of geofence_destroy()
 */
int utc_geofence_destroy_n(void)
{
	ret = geofence_destroy(NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 9 Add Place
/**
 * @testcase		utc_geofence_manager_add_place_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_add_place()
 */
int utc_geofence_manager_add_place_p(void)
{
	const char* place_name = "SRIB";
	int place_id = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_padded, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_place(pGeofenceManager, place_name, &place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventPlaceAdded);
		bEventPlaceAdded = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_place(pGeofenceManager, place_name, &place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_add_place_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_add_place()
 */
int utc_geofence_manager_add_place_n1(void)
{
	int place_id = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_place(pGeofenceManager, NULL, &place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_place(pGeofenceManager, NULL, &place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_add_place_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_add_place()
 */
int utc_geofence_manager_add_place_n2(void)
{
	const char* place_name = "SRIB";
	int place_id = -1;

	ret = geofence_manager_add_place(NULL, place_name, &place_id);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_add_place_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_add_place()
 */
int utc_geofence_manager_add_place_n3(void)
{
	const char* place_name = "SRIB";

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_place(pGeofenceManager, place_name, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_place(pGeofenceManager, place_name, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 10 add fence

/**
 * @testcase		utc_geofence_manager_add_fence_p1
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_add_fence()
 */
int utc_geofence_manager_add_fence_p1(void)
{
	const char* address = "geopoint";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fadded, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceAdded);
		bEventFenceAdded = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_add_fence_p2
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_add_fence()
 */
int utc_geofence_manager_add_fence_p2(void)
{
	const char* ssid = "BT-Fence";
	const char* bssid = "88:30:8A:6C:28:16";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_bluetooth(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fadded, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceAdded);
		bEventFenceAdded = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_add_fence_p3
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_add_fence()
 */
int utc_geofence_manager_add_fence_p3(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fadded, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceAdded);
		bEventFenceAdded = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_add_fence_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_add_fence()
 */
int utc_geofence_manager_add_fence_n1(void)
{
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, NULL, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_fence(pGeofenceManager, NULL, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_add_fence_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_add_fence()
 */
int utc_geofence_manager_add_fence_n2(void)
{
	const char* address = "GPS-Fence";
	int place_id = 1;
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(NULL, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_fence(NULL, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_add_fence_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_add_fence()
 */
int utc_geofence_manager_add_fence_n3(void)
{
	const char* ssid = "BT-Fence";
	const char* bssid = "88:30:8A:6C:28:16";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_create_bluetooth(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(NULL, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_fence(NULL, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_add_fence_n4
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_add_fence()
 */
int utc_geofence_manager_add_fence_n4(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:16";
	int place_id =1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(NULL, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_fence(NULL, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_add_fence_n5
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_add_fence()
 */
int utc_geofence_manager_add_fence_n5(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:16";
	int place_id =1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//11  update place

/**
 * @testcase		utc_geofence_manager_update_place_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_update_place()
 */
int utc_geofence_manager_update_place_p(void)
{
	const char* place_name = "place1";
	int place_id = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_place(pGeofenceManager, place_name, &place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_pupdated, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		place_name = "place2";
		ret = geofence_manager_update_place(pGeofenceManager, place_id, place_name);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventPlaceUpdated);
		bEventPlaceUpdated = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_update_place(pGeofenceManager, place_id, place_name);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_update_place_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_update_place()
 */
int utc_geofence_manager_update_place_n1(void)
{
	const char* place_name = "place1";
	int place_id = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_place(pGeofenceManager, place_name, &place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		place_name = "place2";
		ret = geofence_manager_update_place(NULL, place_id, place_name);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_update_place(NULL, place_id, place_name);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_update_place_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_update_place()
 */
int utc_geofence_manager_update_place_n2(void)
{
	const char* place_name = "place3";

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_update_place(pGeofenceManager, -1, place_name);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_update_place(pGeofenceManager, -1, place_name);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_update_place_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_update_place()
 */
int utc_geofence_manager_update_place_n3(void)
{
	const char* place_name = "place1";
	int place_id = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_place(pGeofenceManager, place_name, &place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_update_place(pGeofenceManager, place_id, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_update_place(pGeofenceManager, place_id, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_update_place_n4
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_update_place()
 */
int utc_geofence_manager_update_place_n4(void)
{
	const char* place_name = "place1";
	int place_id = 1000;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_pupdated, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		place_name = "place2";
		ret = geofence_manager_update_place(pGeofenceManager, place_id, place_name);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert_eq(bEventSuccess,bEventPlaceUpdated);
		bEventPlaceUpdated = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_update_place(pGeofenceManager, place_id, place_name);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 12 foreach_fence_list

/**
 * @testcase		utc_geofence_manager_foreach_geofence_list_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_foreach_geofence_list()
 */
int utc_geofence_manager_foreach_geofence_list_p(void)
{
	int place_id = 1;
	const char* address = "geopoint";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_foreach_geofence_list(pGeofenceManager, __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_callback();
		assert(bFenceListRetrieval);
		bFenceListRetrieval = false;

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_foreach_geofence_list(pGeofenceManager, __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_foreach_geofence_list_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_foreach_geofence_list()
 */
int utc_geofence_manager_foreach_geofence_list_n1(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_foreach_geofence_list(NULL, __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = geofence_manager_foreach_geofence_list(NULL, __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_foreach_geofence_list_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_foreach_geofence_list()
 */
int utc_geofence_manager_foreach_geofence_list_n2(void)
{
	int place_id = 1;
	const char* address = "geopoint";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_foreach_geofence_list(pGeofenceManager, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_foreach_geofence_list(pGeofenceManager, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//13 geofence_manager_foreach_place_geofence_list

/**
 * @testcase		utc_geofence_manager_foreach_place_geofence_list_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_foreach_place_geofence_list()
 */
int utc_geofence_manager_foreach_place_geofence_list_p(void)
{
	int place_id = 1;
	const char* address = "geopoint";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_foreach_place_geofence_list(pGeofenceManager, place_id, __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_callback();
		assert(bFenceListRetrieval);
		bFenceListRetrieval = false;

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_foreach_place_geofence_list(pGeofenceManager, place_id, __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_foreach_place_geofence_list_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_foreach_place_geofence_list()
 */
int utc_geofence_manager_foreach_place_geofence_list_n1(void)
{
	int place_id = 1;
	if(is_geofence_supported)
	{
		ret = geofence_manager_foreach_place_geofence_list(NULL, place_id,  __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = geofence_manager_foreach_place_geofence_list(NULL, place_id,  __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_foreach_place_geofence_list_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_foreach_place_geofence_list()
 */
int utc_geofence_manager_foreach_place_geofence_list_n2(void)
{
	int place_id = 1;
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_foreach_place_geofence_list(pGeofenceManager, place_id, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_foreach_place_geofence_list(pGeofenceManager, place_id, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_foreach_place_geofence_list_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_foreach_place_geofence_list()
 */
int utc_geofence_manager_foreach_place_geofence_list_n3(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_foreach_place_geofence_list(pGeofenceManager, -1, __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_foreach_place_geofence_list(pGeofenceManager, -1, __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_foreach_place_geofence_list_n4
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_foreach_place_geofence_list()
 */
int utc_geofence_manager_foreach_place_geofence_list_n4(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_foreach_place_geofence_list(pGeofenceManager, 1000, __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_DATABASE);

		wait_for_callback();
		assert_eq(bFenceListRetrieval,false);
		bFenceListRetrieval = false;

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_foreach_place_geofence_list(pGeofenceManager, 1000, __geofence_manager_fence_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


//14 geofence_manager_foreach_place_list

/**
 * @testcase		utc_geofence_manager_foreach_place_list_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_foreach_place_list()
 */
int utc_geofence_manager_foreach_place_list_p(void)
{
	const char *place_name = "place1";
	int place_id = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_place(pGeofenceManager, place_name, &place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_foreach_place_list(pGeofenceManager, __geofence_manager_place_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_placecallback();
		assert(bPlaceListRetrieval);
		bPlaceListRetrieval = false;

		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_foreach_place_list(pGeofenceManager, __geofence_manager_place_cb, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_foreach_place_list_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_foreach_place_list()
 */
int utc_geofence_manager_foreach_place_list_n1(void)
{
	ret = geofence_manager_foreach_place_list(NULL, __geofence_manager_place_cb, (void*)NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_foreach_place_list_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_foreach_place_list()
 */
int utc_geofence_manager_foreach_place_list_n2(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_foreach_place_list(pGeofenceManager, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_foreach_place_list(pGeofenceManager, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 15 remove Place
/**
 * @testcase		utc_geofence_manager_remove_place_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_remove_place()
 */
int utc_geofence_manager_remove_place_p(void)
{
	const char* place_name = "SRIB";
	int place_id = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_place(pGeofenceManager, place_name, &place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_premoved, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventPlaceRemoved);
		bEventPlaceRemoved = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_remove_place_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_remove_place()
 */
int utc_geofence_manager_remove_place_n1(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_remove_place(NULL, 1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = geofence_manager_remove_place(NULL, 1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_remove_place_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_remove_place()
 */
int utc_geofence_manager_remove_place_n2(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_place(pGeofenceManager, -1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_remove_place(pGeofenceManager, -1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_remove_place_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_remove_place()
 */
int utc_geofence_manager_remove_place_n3(void)
{
	int place_id = 1000;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_idnot_premoved, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert_eq(bEventSuccess, true);
		bEventPlaceRemoved = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_remove_place_n4
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_remove_place()
 */
int utc_geofence_manager_remove_place_n4(void)
{
	int place_id = 1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_notauthorized_premoved, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert_eq(bEventSuccess, true);
		bEventPlaceRemoved = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 16 remove fence

/**
 * @testcase		utc_geofence_manager_remove_fence_p1
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_remove_fence()
 */
int utc_geofence_manager_remove_fence_p1(void)
{
	const char* address = "Gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fremoved, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceRemoved);
		bEventFenceRemoved = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_remove_fence_p2
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_remove_fence()
 */
int utc_geofence_manager_remove_fence_p2(void)
{
	const char* ssid = "BT-fence";
	const char* bssid = "88:30:8A:6C:28:16";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_bluetooth(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fremoved, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceRemoved);
		bEventFenceRemoved = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_remove_fence_p3
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_remove_fence()
 */
int utc_geofence_manager_remove_fence_p3(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:16";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fremoved, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceRemoved);
		bEventFenceRemoved = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_remove_fence_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_remove_fence()
 */
int utc_geofence_manager_remove_fence_n1(void)
{
	int fenceId = 1;

	ret = geofence_manager_remove_fence(NULL, fenceId);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_remove_fence_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_remove_fence()
 */
int utc_geofence_manager_remove_fence_n2(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, -1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_remove_fence(pGeofenceManager, -1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_remove_fence_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_remove_fence()
 */
int utc_geofence_manager_remove_fence_n3(void)
{
	int fenceId = 1000;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_idnot_fremoved, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert_eq(bEventSuccess,true);
		bEventFenceRemoved = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//17 geofence_manager_set_geofence_state_changed_cb

/**
 * @testcase		utc_geofence_manager_set_geofence_state_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_set_geofence_state_changed_cb()
 */
int utc_geofence_manager_set_geofence_state_changed_cb_p(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_state_changed_cb(pGeofenceManager, geofence_state_changed_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_set_geofence_state_changed_cb(pGeofenceManager, geofence_state_changed_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_set_geofence_state_changed_cb_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_set_geofence_state_changed_cb()
 */
int utc_geofence_manager_set_geofence_state_changed_cb_n1(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_state_changed_cb(pGeofenceManager, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_set_geofence_state_changed_cb(pGeofenceManager, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_set_geofence_state_changed_cb_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_set_geofence_state_changed_cb()
 */
int utc_geofence_manager_set_geofence_state_changed_cb_n2(void)
{
	ret = geofence_manager_set_geofence_state_changed_cb(NULL, geofence_state_changed_cb_p, (void*)NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 14 unset_geofence_state_changed_cb

/**
 * @testcase		utc_geofence_manager_unset_geofence_state_changed_cb_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_unset_geofence_state_changed_cb()
 */
int utc_geofence_manager_unset_geofence_state_changed_cb_p(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_state_changed_cb(pGeofenceManager, geofence_state_changed_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_unset_geofence_state_changed_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_unset_geofence_state_changed_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_unset_geofence_state_changed_cb_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_unset_geofence_state_changed_cb()
 */
int utc_geofence_manager_unset_geofence_state_changed_cb_n1(void)
{
	ret = geofence_manager_unset_geofence_state_changed_cb(NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_set_geofence_proximity_state_changed_cb_p
 * @since_tizen		3.0
 * @description		Positive test case of geofence_manager_set_geofence_proximity_state_changed_cb()
 */
int utc_geofence_manager_set_geofence_proximity_state_changed_cb_p(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_proximity_state_changed_cb(pGeofenceManager, geofence_proximity_state_changed_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_set_geofence_proximity_state_changed_cb(pGeofenceManager, geofence_proximity_state_changed_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_set_geofence_proximity_state_changed_cb_n1
 * @since_tizen		3.0
 * @description		Negative test case of geofence_manager_set_geofence_proximity_state_changed_cb()
 */
int utc_geofence_manager_set_geofence_proximity_state_changed_cb_n1(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_proximity_state_changed_cb(pGeofenceManager, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_set_geofence_proximity_state_changed_cb(pGeofenceManager, NULL, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_set_geofence_proximity_state_changed_cb_n2
 * @since_tizen		3.0
 * @description		Negative test case of geofence_manager_set_geofence_proximity_state_changed_cb()
 */
int utc_geofence_manager_set_geofence_proximity_state_changed_cb_n2(void)
{
	ret = geofence_manager_set_geofence_proximity_state_changed_cb(NULL, geofence_proximity_state_changed_cb_p, (void*)NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_unset_geofence_proximity_state_changed_cb_p
 * @since_tizen		3.0
 * @description		Positive test case of geofence_manager_unset_geofence_proximity_state_changed_cb()
 */
int utc_geofence_manager_unset_geofence_proximity_state_changed_cb_p(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_proximity_state_changed_cb(pGeofenceManager, geofence_proximity_state_changed_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_unset_geofence_proximity_state_changed_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_unset_geofence_proximity_state_changed_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_unset_geofence_proximity_state_changed_cb_n1
 * @since_tizen		3.0
 * @description		Negative test case of geofence_manager_unset_geofence_proximity_state_changed_cb()
 */
int utc_geofence_manager_unset_geofence_proximity_state_changed_cb_n1(void)
{
	ret = geofence_manager_unset_geofence_proximity_state_changed_cb(NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 18 start

/**
 * @testcase		utc_geofence_manager_start_p1
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_start()
 */
int utc_geofence_manager_start_p1(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstarted, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceStarted);
		bEventFenceStarted = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_stop(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_start_p2
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_start()
 */
int utc_geofence_manager_start_p2(void)
{
	const char* ssid = "bt-fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_bluetooth(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstarted, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_state_changed_cb(pGeofenceManager, geofence_state_changed_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceStarted);

		if(bEventSuccess)
		{
			wait_for_callback();
			assert(bStateInOut);

			bStateInOut = false;
			bEventFenceStarted = false;
		}

		ret = geofence_manager_unset_geofence_state_changed_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		if(bEventSuccess)
		{
			ret = geofence_manager_stop(pGeofenceManager, fenceId);
			assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

			bEventSuccess = false;
		}

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_start_p3
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_start()
 */
int utc_geofence_manager_start_p3(void)
{
	const char* ssid = "wifi-fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstarted, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
#ifdef TIZEN_DEVICE
		ret = geofence_manager_set_geofence_state_changed_cb(pGeofenceManager, geofence_state_changed_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_proximity_state_changed_cb(pGeofenceManager, geofence_proximity_state_changed_cb_p, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
#endif
		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceStarted);
#ifdef TIZEN_DEVICE
		wait_for_callback();
		assert(bStateInOut);
		wait_for_callback();
		assert(bStateProximity);
		bStateInOut = false;
		bStateProximity = false;
#endif
		bEventFenceStarted = false;
		bEventSuccess = false;
#ifdef TIZEN_DEVICE
		ret = geofence_manager_unset_geofence_proximity_state_changed_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_unset_geofence_state_changed_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
#endif
		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_stop(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_start_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_start()
 */
int utc_geofence_manager_start_n1(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(NULL, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_start(NULL, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_start_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_start()
 */
int utc_geofence_manager_start_n2(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, -1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_start(pGeofenceManager, -1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_start_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_start()
 */
int utc_geofence_manager_start_n3(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_idnot_fstarted, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, 1000);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert_eq(bEventSuccess, true);
		bEventFenceStarted = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_start(pGeofenceManager, 1000);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_start_n4
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_start()
 */
int utc_geofence_manager_start_n4(void)
{
	const char* ssid = "wifi-fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstarted, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceStarted);
		bEventFenceStarted = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_ALREADY_STARTED);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_stop(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 16 stop

/**
 * @testcase		utc_geofence_manager_stop_p1
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_stop()
 */
int utc_geofence_manager_stop_p1(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstarted, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		//Wait for started callback
		wait_for_eventcallback();
		assert(bEventFenceStarted);
		bEventFenceStarted = false;
		bEventSuccess = false;

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstopped, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_stop(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		//Wait for stopped callback
		wait_for_eventcallback();
		assert(bEventFenceStopped);
		bEventFenceStopped = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_stop(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_stop_p2
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_stop()
 */
int utc_geofence_manager_stop_p2(void)
{
	const char* ssid = "bt-fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_bluetooth(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstarted, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		//Wait for started callback
		wait_for_eventcallback();
		assert(bEventFenceStarted);
		bEventFenceStarted = false;

		if(bEventSuccess)
		{
			ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstopped, NULL);
			assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

			ret = geofence_manager_stop(pGeofenceManager, fenceId);
			assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

			//Wait for stopped callback
			wait_for_eventcallback();
			assert(bEventFenceStopped);
			bEventFenceStopped = false;
			bEventSuccess = false;
		}

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_stop(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_stop_p3
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_stop()
 */
int utc_geofence_manager_stop_p3(void)
{
	const char* ssid = "wifi-fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstarted, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		//Wait for started callback
		wait_for_eventcallback();
		assert(bEventFenceStarted);
		bEventFenceStarted = false;
		bEventSuccess = false;

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstopped, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_stop(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		//Wait for stopped callback
		wait_for_eventcallback();
		assert(bEventFenceStopped);
		bEventFenceStopped = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_stop(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_stop_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_stop()
 */
int utc_geofence_manager_stop_n1(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_stop(NULL, 1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = geofence_manager_stop(NULL, 1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_stop_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_stop()
 */
int utc_geofence_manager_stop_n2(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_stop(pGeofenceManager, -1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_stop(pGeofenceManager, -1);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//17 geofence_status_create

/**
 * @testcase		utc_geofence_status_create_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_status_create()
 */
int utc_geofence_status_create_p(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_create(fenceId, &pStatus);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_destroy(pStatus);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_status_create(fenceId, &pStatus);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_status_create_n
 * @since_tizen		2.4
 * @description		Negative test case of geofence_status_create()
 */
int utc_geofence_status_create_n(void)
{

	ret = geofence_status_create(-1, &pStatus);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//18 geofence_status_destroy

/**
 * @testcase		utc_geofence_status_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_status_destroy()
 */
int utc_geofence_status_destroy_p(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int fenceId = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_create(fenceId, &pStatus);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_destroy(pStatus);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_status_destroy(pStatus);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_status_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of geofence_status_destroy()
 */
int utc_geofence_status_destroy_n(void)
{
	ret = geofence_status_destroy(NULL);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//19 geofence_status_get_state

/**
 * @testcase		utc_geofence_status_get_state_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_status_get_state()
 */
int utc_geofence_status_get_state_p(void)
{

	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int fenceId = -1;
	geofence_state_e pState;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_create(fenceId, &pStatus);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_get_state(pStatus, &pState);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstarted, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceStarted);
		bEventFenceStarted = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_get_state(pStatus, &pState);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_destroy(pStatus);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_status_get_state(pStatus, &pState);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_status_get_state_n
 * @since_tizen		2.4
 * @description		Negative test case of geofence_status_get_state()
 */
int utc_geofence_status_get_state_n(void)
{

	geofence_state_e pState;
	ret = geofence_status_get_state(NULL, &pState);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//20 geofence_status_get_duration

/**
 * @testcase		utc_geofence_status_get_duration_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_status_get_duration()
 */
int utc_geofence_status_get_duration_p(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int fenceId = -1;
	int seconds = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_fence(pGeofenceManager, pGeofenceParams, &fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_create(fenceId, &pStatus);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_get_duration(pStatus, &seconds);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_set_geofence_event_cb(pGeofenceManager, __geofence_event_fstarted, (void*)NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_start(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		wait_for_eventcallback();
		assert(bEventFenceStarted);
		bEventFenceStarted = false;
		bEventSuccess = false;

		ret = geofence_manager_unset_geofence_event_cb(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_get_duration(pStatus, &seconds);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_status_destroy(pStatus);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_remove_fence(pGeofenceManager, fenceId);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_status_get_duration(pStatus, &seconds);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_status_get_duration_n
 * @since_tizen		2.4
 * @description		Negative test case of geofence_status_get_duration()
 */
int utc_geofence_status_get_duration_n(void)
{
	int seconds = -1;

	ret = geofence_status_get_duration(NULL, &seconds);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 21 geofence_manager_get_place_name

/**
 * @testcase		utc_geofence_manager_get_place_name_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_manager_get_place_name()
 */
int utc_geofence_manager_get_place_name_p(void)
{
	const char* place_name = "SISO";
	int place_id = -1;
	char* placeName = NULL;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_add_place(pGeofenceManager, place_name, &place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_get_place_name(pGeofenceManager, place_id, &placeName);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = strcmp(place_name, placeName);
		assert_eq(ret, 0);

		ret = geofence_manager_remove_place(pGeofenceManager, place_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		free(placeName);
	}
	else
	{
		ret = geofence_manager_get_place_name(pGeofenceManager, place_id, &placeName);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_get_place_name_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_get_place_name()
 */
int utc_geofence_manager_get_place_name_n1(void)
{
	char* placeName = NULL;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_get_place_name(NULL, 1, &placeName);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_get_place_name(NULL, 1, &placeName);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_get_place_name_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_get_place_name()
 */
int utc_geofence_manager_get_place_name_n2(void)
{
	char* placeName = NULL;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_get_place_name(pGeofenceManager, -1, &placeName);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_get_place_name(pGeofenceManager, -1, &placeName);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_manager_get_place_name_n3
 * @since_tizen		2.4
 * @description		Negative test case of geofence_manager_get_place_name()
 */
int utc_geofence_manager_get_place_name_n3(void)
{
	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_get_place_name(pGeofenceManager, 1, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_manager_get_place_name(pGeofenceManager, 1, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 22 geofence_get_address

/**
 * @testcase		utc_geofence_get_address_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_get_address()
 */
int utc_geofence_get_address_p(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;
	char* getaddress = NULL;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_address(pGeofenceParams, &getaddress);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = strcmp(address, getaddress);
		assert_eq(ret, 0);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		free(getaddress);
	}
	else
	{
		ret = geofence_get_address(pGeofenceParams, &getaddress);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_address_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_address()
 */
int utc_geofence_get_address_n1(void)
{
	char* getaddress = NULL;

	ret = geofence_get_address(NULL, &getaddress);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_address_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_address()
 */
int utc_geofence_get_address_n2(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_address(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_address(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 23 geofence_get_latitute

/**
 * @testcase		utc_geofence_get_latitude_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_get_latitude()
 */
int utc_geofence_get_latitude_p(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;
	double getlatitude = -0.0;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_latitude(pGeofenceParams, &getlatitude);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
		if(lat == getlatitude)
			ret = 0;
		else
			ret = 1;
		assert_eq(ret, 0);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_latitude(pGeofenceParams, &getlatitude);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_latitude_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_latitude()
 */
int utc_geofence_get_latitude_n1(void)
{
	double getlatitude = -0.0;

	ret = geofence_get_latitude(NULL, &getlatitude);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_latitude_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_latitude()
 */
int utc_geofence_get_latitude_n2(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_latitude(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_latitude(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 24 geofence_get_longitude

/**
 * @testcase		utc_geofence_get_longitude_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_get_longitude()
 */
int utc_geofence_get_longitude_p(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;
	double getlongitute = -0.0;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_longitude(pGeofenceParams, &getlongitute);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
		if(lon == getlongitute)
			ret = 0;
		else
			ret = 1;
		assert_eq(ret, 0);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_longitude(pGeofenceParams, &getlongitute);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_longitude_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_longitude()
 */
int utc_geofence_get_longitude_n1(void)
{
	double getlongitute = -0.0;

	ret = geofence_get_longitude(NULL, &getlongitute);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_longitude_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_longitude()
 */
int utc_geofence_get_longitude_n2(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_longitude(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_longitude(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 25 geofence_get_radius

/**
 * @testcase		utc_geofence_get_radius_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_get_radius()
 */
int utc_geofence_get_radius_p(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;
	int getradius = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_radius(pGeofenceParams, &getradius);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
		if(radius == getradius)
			ret = 0;
		else
			ret = 1;
		assert_eq(ret, 0);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_radius(pGeofenceParams, &getradius);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_radius_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_radius()
 */
int utc_geofence_get_radius_n1(void)
{
	int getradius = -1;

	ret = geofence_get_radius(NULL, &getradius);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_radius_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_radius()
 */
int utc_geofence_get_radius_n2(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_radius(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_radius(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 26 geofence_get_bssid

/**
 * @testcase		utc_geofence_get_bssid_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_get_bssid()
 */
int utc_geofence_get_bssid_p(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	char* getbssid = NULL;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_bssid(pGeofenceParams, &getbssid);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = strcmp(bssid, getbssid);
		assert_eq(ret, 0);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		free(getbssid);
	}
	else
	{
		ret = geofence_get_bssid(pGeofenceParams, &getbssid);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_bssid_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_bssid()
 */
int utc_geofence_get_bssid_n1(void)
{
	char* getbssid = NULL;

	ret = geofence_get_bssid(NULL, &getbssid);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_bssid_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_bssid()
 */
int utc_geofence_get_bssid_n2(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_bssid(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_bssid(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

//27 geofence_get_ssid

/**
 * @testcase		utc_geofence_get_ssid_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_get_ssid()
 */
int utc_geofence_get_ssid_p(void)
{
	const char *ssid = "Wifi-Fence";
	const char *bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	char *getssid = NULL;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_ssid(pGeofenceParams, &getssid);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = strcmp(ssid, getssid);
		assert_eq(ret, 0);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		free(getssid);
	}
	else
	{
		ret = geofence_get_ssid(pGeofenceParams, &getssid);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_ssid_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_ssid()
 */
int utc_geofence_get_ssid_n1(void)
{
	char* getssid = NULL;

	ret = geofence_get_ssid(NULL, &getssid);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_ssid_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_ssid()
 */
int utc_geofence_get_ssid_n2(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_ssid(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_ssid(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 28 geofence_get_place_id

/**
 * @testcase		utc_geofence_get_place_id_p
 * @since_tizen		2.4
 * @description		Positive test case of geofence_get_place_id()
 */
int utc_geofence_get_place_id_p(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	int getplace_id = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_place_id(pGeofenceParams, &getplace_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
		if(place_id == getplace_id)
			ret = 0;
		else
			ret = 1;
		assert_eq(ret, 0);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_place_id(pGeofenceParams, &getplace_id);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_place_id_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_place_id()
 */
int utc_geofence_get_place_id_n1(void)
{
	int getplace_id = -1;
	ret = geofence_get_place_id(NULL, &getplace_id);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;

}

/**
 * @testcase		utc_geofence_get_place_id_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_place_id()
 */
int utc_geofence_get_place_id_n2(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_place_id(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_place_id(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

// 29 geofence_get_type

/**
 * @testcase		utc_geofence_get_type_p1
 * @since_tizen		2.4
 * @description		Positive test case of geofence_get_type()
 */
int utc_geofence_get_type_p1(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;
	geofence_type_e type = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_type(pGeofenceParams, &type);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		if(type == GEOFENCE_TYPE_GEOPOINT)
			ret = 0;
		else
			ret = 1;
		assert_eq(ret, 0);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_type(pGeofenceParams, &type);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_geofence_get_type_p2
 * @since_tizen		2.4
 * @description		Positive test case of geofence_get_type()
 */
int utc_geofence_get_type_p2(void)
{
	const char* ssid = "Wifi-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	geofence_type_e type = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_wifi(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_type(pGeofenceParams, &type);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		if(type == GEOFENCE_TYPE_WIFI)
			ret = 0;
		else
			ret = 1;
		assert_eq(ret, 0);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_type(pGeofenceParams, &type);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_type_p3
 * @since_tizen		2.4
 * @description		Positive test case of geofence_get_type()
 */
int utc_geofence_get_type_p3(void)
{
	const char* ssid = "BT-Fence";
	const char* bssid = "88:30:8A:6C:28:15";
	int place_id = 1;
	geofence_type_e type = -1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_bluetooth(place_id, bssid, ssid, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_type(pGeofenceParams, &type);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		if(type == GEOFENCE_TYPE_BT)
			ret = 0;
		else
			ret = 1;
		assert_eq(ret, 0);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_type(pGeofenceParams, &type);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_type_n1
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_type()
 */
int utc_geofence_get_type_n1(void)
{
	geofence_type_e type = -1;

	ret = geofence_get_type(NULL, &type);
	if(is_geofence_supported)
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_geofence_get_type_n2
 * @since_tizen		2.4
 * @description		Negative test case of geofence_get_type()
 */
int utc_geofence_get_type_n2(void)
{
	const char* address = "gps-fence";
	double lat = 12.9667, lon = 77.5667;
	int radius = 100;
	int place_id = 1;

	if(is_geofence_supported)
	{
		ret = geofence_manager_create(&pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_create_geopoint(place_id, lat, lon, radius, address, &pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_get_type(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER);

		ret = geofence_destroy(pGeofenceParams);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);

		ret = geofence_manager_destroy(pGeofenceManager);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NONE);
	}
	else
	{
		ret = geofence_get_type(pGeofenceParams, NULL);
		assert_eq(ret, GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED);
	}

	return 0;
}
