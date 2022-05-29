/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
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

#include <string.h>
#include "assert.h"
#include <maps_view.h>
#include <maps_service.h>
#include <maps_error.h>
#include <unistd.h>
#include <glib.h>
#include <Evas.h>
#include <Elementary.h>
#include "utc_maps_utils.h"
#include <dlog.h>

static int ret = 0;
static maps_service_h __pMaps = NULL;
static char maps_provider_key[CONFIG_VALUE_LEN_MAX] = {0,};
static maps_view_h maps_view_handle = NULL;
static Evas_Object *win = NULL;
static bool is_internet_supported = false;
static bool is_maps_supported = false;
static bool is_maps_view_supported = false;

static void dummy_utc_maps_view_on_event_cb(maps_view_event_type_e type, maps_view_event_data_h event_data, void *user_data) { }

static bool dummy_maps_view_object_cb(int index, int total, maps_view_object_h object, void *user_data)
{
	return true;
}

/**
 * @function		utc_maps_view_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_maps_view_startup(void)
{
    if (__pMaps) return;

	is_internet_supported = _is_internet_feature_supported();
	is_maps_supported = _is_maps_feature_supported();

	elm_init(0, NULL);
	elm_config_accel_preference_set("opengl");

	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	elm_win_autodel_set(win, TRUE);

	GetValueFromConfigFile("HERE_MAPS_PROVIDER_KEY", maps_provider_key, API_NAMESPACE);
	maps_service_create(__utc_get_maps_provider_name_here(), &__pMaps);
	maps_service_set_provider_key(__pMaps, maps_provider_key);

	maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_VIEW, &is_maps_view_supported);
    if (is_maps_view_supported)
    	maps_view_create(__pMaps, win, &maps_view_handle);
}

/**
 * @function		utc_maps_view_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_maps_view_cleanup(void)
{
	maps_view_destroy(maps_view_handle);
	maps_service_destroy(__pMaps);

	evas_object_del(win);

	maps_view_handle = NULL;
	__pMaps = NULL;
	win = NULL;
}

/**
 * @testcase		utc_maps_view_create_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_create()
 */
int utc_maps_view_create_p(void)
{
	ret = maps_view_destroy(maps_view_handle);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

	maps_view_handle = NULL;

	ret = maps_view_create(__pMaps, win, &maps_view_handle);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported && is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_create_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_create()
 */
int utc_maps_view_create_n(void)
{
	ret = maps_view_create(NULL, win, &maps_view_handle);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_create(__pMaps, NULL, &maps_view_handle);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported && is_maps_view_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_create(__pMaps, win, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported && is_maps_view_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_get_center_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_center()
 */
int utc_maps_view_get_center_p(void)
{
	maps_coordinates_h coord = NULL;

	ret = maps_view_get_center(maps_view_handle, &coord);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	ret = maps_view_set_center(maps_view_handle, coord);
	if (is_internet_supported && is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	ret = maps_coordinates_destroy(coord);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_center_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_center()
*/
int utc_maps_view_get_center_n(void)
{
	maps_coordinates_h coord = NULL;

	ret = maps_view_get_center(NULL, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_center(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_set_center_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_center()
 */
int utc_maps_view_set_center_p(void)
{
	/* tested in utc_maps_view_get_center_p */
	return 0;
}

/**
* @testcase        utc_maps_view_set_center_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_center()
*/
int utc_maps_view_set_center_n(void)
{
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_center(NULL, coord);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_center(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_get_zoom_level_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_zoom_level()
 */
int utc_maps_view_get_zoom_level_p(void)
{
	int level = 0;

	ret = maps_view_get_zoom_level(maps_view_handle, &level);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_zoom_level_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_zoom_level()
*/
int utc_maps_view_get_zoom_level_n(void)
{
	int level = 0;

	ret = maps_view_get_zoom_level(NULL, &level);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_zoom_level(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_set_zoom_level_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_zoom_level()
 */
int utc_maps_view_set_zoom_level_p(void)
{
	ret = maps_view_set_zoom_level(maps_view_handle, 3);
	if (is_internet_supported && is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_zoom_level_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_zoom_level()
*/
int utc_maps_view_set_zoom_level_n(void)
{
	ret = maps_view_set_zoom_level(NULL, 3);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_min_zoom_level_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_min_zoom_level()
 */
int utc_maps_view_get_min_zoom_level_p(void)
{
	int level = 0;

	ret = maps_view_get_min_zoom_level(maps_view_handle, &level);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_min_zoom_level_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_min_zoom_level()
*/
int utc_maps_view_get_min_zoom_level_n(void)
{
	int level = 0;

	ret = maps_view_get_min_zoom_level(NULL, &level);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_min_zoom_level(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_max_zoom_level_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_max_zoom_level()
 */
int utc_maps_view_get_max_zoom_level_p(void)
{
	int level = 0;

	ret = maps_view_get_max_zoom_level(maps_view_handle, &level);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_max_zoom_level_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_max_zoom_level()
*/
int utc_maps_view_get_max_zoom_level_n(void)
{
	int level = 0;

	ret = maps_view_get_max_zoom_level(NULL, &level);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_max_zoom_level(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_set_orientation_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_orientation()
 */
int utc_maps_view_set_orientation_p(void)
{
	ret = maps_view_set_orientation(maps_view_handle, 0.0);
	if (is_internet_supported && is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_orientation_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_orientation()
*/
int utc_maps_view_set_orientation_n(void)
{
	ret = maps_view_set_orientation(NULL, 0.0);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_orientation_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_orientation()
 */
int utc_maps_view_get_orientation_p(void)
{
	double orientation = 0.0;

	ret = maps_view_get_orientation(maps_view_handle, &orientation);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_orientation_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_orientation()
*/
int utc_maps_view_get_orientation_n(void)
{
	double orientation = 0.0;

	ret = maps_view_get_orientation(NULL, &orientation);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_orientation(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_screen_to_geolocation_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_screen_to_geolocation()
 */
int utc_maps_view_screen_to_geolocation_p(void)
{
	maps_coordinates_h coord = NULL;

	ret = maps_view_screen_to_geolocation(maps_view_handle, 0, 0, &coord);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	maps_coordinates_destroy(coord);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_screen_to_geolocation_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_screen_to_geolocation()
*/
int utc_maps_view_screen_to_geolocation_n(void)
{
	maps_coordinates_h coord = NULL;

	ret = maps_view_screen_to_geolocation(NULL, 0, 0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_screen_to_geolocation(maps_view_handle, 0, 0, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_geolocation_to_screen_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_geolocation_to_screen()
 */
int utc_maps_view_geolocation_to_screen_p(void)
{
	int x = 0, y = 0;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_geolocation_to_screen(maps_view_handle, coord, &x, &y);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	ret = maps_coordinates_destroy(coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
* @testcase        utc_maps_view_geolocation_to_screen_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_geolocation_to_screen()
*/
int utc_maps_view_geolocation_to_screen_n(void)
{
	int x = 0, y = 0;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_geolocation_to_screen(NULL, coord, &x, &y);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_geolocation_to_screen(maps_view_handle, NULL, &x, &y);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_geolocation_to_screen(maps_view_handle, coord, NULL, &y);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_geolocation_to_screen(maps_view_handle, coord, &x, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_set_type_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_type()
 */
int utc_maps_view_set_type_p(void)
{
	ret = maps_view_set_type(maps_view_handle, MAPS_VIEW_TYPE_NORMAL);
	if (is_internet_supported && is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_type_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_type()
*/
int utc_maps_view_set_type_n(void)
{
	ret = maps_view_set_type(NULL, MAPS_VIEW_TYPE_NORMAL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_type(maps_view_handle, -1000);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_type_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_type()
 */
int utc_maps_view_get_type_p(void)
{
	maps_view_type_e type;

	ret = maps_view_get_type(maps_view_handle, &type);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_type_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_type()
*/
int utc_maps_view_get_type_n(void)
{
	maps_view_type_e type;

	ret = maps_view_get_type(NULL, &type);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_type(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_set_buildings_enabled_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_buildings_enabled()
 */
int utc_maps_view_set_buildings_enabled_p(void)
{
	bool is_building_supported = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_BUILDING, &is_building_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_buildings_enabled(maps_view_handle, false);
	if (is_internet_supported && is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_building_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_buildings_enabled_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_buildings_enabled()
*/
int utc_maps_view_set_buildings_enabled_n(void)
{
	ret = maps_view_set_buildings_enabled(NULL, false);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_buildings_enabled_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_buildings_enabled()
 */
int utc_maps_view_get_buildings_enabled_p(void)
{
	bool is_building_supported = false;
	bool enabled = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_BUILDING, &is_building_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_buildings_enabled(maps_view_handle, &enabled);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_building_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_buildings_enabled_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_buildings_enabled()
*/
int utc_maps_view_get_buildings_enabled_n(void)
{
	bool enabled = false;
	bool is_building_supported = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_BUILDING, &is_building_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_buildings_enabled(NULL, &enabled);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_buildings_enabled(maps_view_handle, NULL);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_building_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/*
 * @testcase        utc_maps_view_set_traffic_enabled_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_traffic_enabled()
 */
int utc_maps_view_set_traffic_enabled_p(void)
{
	bool is_traffic_supported = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_TRAFFIC, &is_traffic_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_traffic_enabled(maps_view_handle, false);
	if (is_internet_supported && is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_traffic_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_traffic_enabled_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_traffic_enabled()
*/
int utc_maps_view_set_traffic_enabled_n(void)
{
	ret = maps_view_set_traffic_enabled(NULL, false);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_traffic_enabled_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_traffic_enabled()
 */
int utc_maps_view_get_traffic_enabled_p(void)
{
	bool is_traffic_supported = false;
	bool enabled = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_TRAFFIC, &is_traffic_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_traffic_enabled(maps_view_handle, &enabled);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_traffic_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_traffic_enabled_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_traffic_enabled()
*/
int utc_maps_view_get_traffic_enabled_n(void)
{
	bool enabled = false;
	bool is_traffic_supported = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_TRAFFIC, &is_traffic_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_traffic_enabled(NULL, &enabled);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_traffic_enabled(maps_view_handle, NULL);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_traffic_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/*
 * @testcase        utc_maps_view_set_public_transit_enabled_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_public_transit_enabled()
 */
int utc_maps_view_set_public_transit_enabled_p(void)
{
	bool is_public_transit_supported = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_PUBLIC_TRANSIT, &is_public_transit_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_public_transit_enabled(maps_view_handle, false);
	if (is_internet_supported && is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_public_transit_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_public_transit_enabled_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_public_transit_enabled()
*/
int utc_maps_view_set_public_transit_enabled_n(void)
{
	ret = maps_view_set_public_transit_enabled(NULL, false);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_public_transit_enabled_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_public_transit_enabled()
 */
int utc_maps_view_get_public_transit_enabled_p(void)
{
	bool is_public_transit_supported = false;
	bool enabled = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_PUBLIC_TRANSIT, &is_public_transit_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_public_transit_enabled(maps_view_handle, &enabled);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_public_transit_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_public_transit_enabled_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_public_transit_enabled()
*/
int utc_maps_view_get_public_transit_enabled_n(void)
{
	bool enabled = false;
	bool is_public_transit_supported = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_PUBLIC_TRANSIT, &is_public_transit_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_public_transit_enabled(NULL, &enabled);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_public_transit_enabled(maps_view_handle, NULL);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_public_transit_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/*
 * @testcase        utc_maps_view_set_language_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_language()
 */
int utc_maps_view_set_language_p(void)
{
	ret = maps_view_set_language(maps_view_handle, "eng");
	if (is_internet_supported && is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_language_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_language()
*/
int utc_maps_view_set_language_n(void)
{
	ret = maps_view_set_language(NULL, "eng");
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_language(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_language_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_language()
 */
int utc_maps_view_get_language_p(void)
{
	char *language = NULL;

	dlog_print(DLOG_ERROR, "Maps", "[%s:%d] %p %p %s", __FUNCTION__, __LINE__, maps_view_handle, language, language);
	ret = maps_view_get_language(maps_view_handle, &language);
	dlog_print(DLOG_ERROR, "Maps", "[%s:%d] %p maps_view_get_language result = %s", __FUNCTION__, __LINE__, maps_view_handle, language);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	free(language);

	return 0;
}

/**
* @testcase        utc_maps_view_get_language_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_language()
*/
int utc_maps_view_get_language_n(void)
{
	char *language = NULL;

	ret = maps_view_get_language(NULL, &language);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_language(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_viewport_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_viewport()
 */
int utc_maps_view_get_viewport_p(void)
{
	Evas_Object *viewport = NULL;

	ret = maps_view_get_viewport(maps_view_handle, &viewport);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_viewport_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_viewport()
*/
int utc_maps_view_get_viewport_n(void)
{
	Evas_Object *viewport = NULL;

	ret = maps_view_get_viewport(NULL, &viewport);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_viewport(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_set_screen_location_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_screen_location()
 */
int utc_maps_view_set_screen_location_p(void)
{
	ret = maps_view_set_screen_location(maps_view_handle, 10, 10, 10, 10);
	if (is_internet_supported && is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_screen_location_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_screen_location()
*/
int utc_maps_view_set_screen_location_n(void)
{
	ret = maps_view_set_screen_location(NULL, 10, 10, 10, 10);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_screen_location_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_screen_location()
 */
int utc_maps_view_get_screen_location_p(void)
{
	int x = 0, y = 0, width = 0, height = 0;

	ret = maps_view_get_screen_location(maps_view_handle, &x, &y, &width, &height);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_screen_location_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_screen_location()
*/
int utc_maps_view_get_screen_location_n(void)
{
	int x = 0, y = 0, width = 0, height = 0;

	ret = maps_view_get_screen_location(NULL, &x, &y, &width, &height);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_screen_location(maps_view_handle, NULL, NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_move_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_move()
 */
int utc_maps_view_move_p(void)
{
	ret = maps_view_move(maps_view_handle, 10, 10);
	if (is_internet_supported && is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_move_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_move()
*/
int utc_maps_view_move_n(void)
{
	ret = maps_view_move(NULL, 10, 10);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_resize_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_resize()
 */
int utc_maps_view_resize_p(void)
{
	ret = maps_view_resize(maps_view_handle, 10, 10);
	if (is_internet_supported && is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_resize_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_resize()
*/
int utc_maps_view_resize_n(void)
{
	ret = maps_view_resize(NULL, 10, 10);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_resize(maps_view_handle, -1, 10);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_resize(maps_view_handle, 10, -1);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_set_visibility_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_visibility()
 */
int utc_maps_view_set_visibility_p(void)
{
	ret = maps_view_set_visibility(maps_view_handle, false);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	ret = maps_view_set_visibility(maps_view_handle, true);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_visibility_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_visibility()
*/
int utc_maps_view_set_visibility_n(void)
{
	ret = maps_view_set_visibility(NULL, false);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_visibility_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_visibility()
 */
int utc_maps_view_get_visibility_p(void)
{
	bool visible = false;

	ret = maps_view_get_visibility(maps_view_handle, &visible);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_visibility_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_visibility()
*/
int utc_maps_view_get_visibility_n(void)
{
	bool visible = false;

	ret = maps_view_get_visibility(NULL, &visible);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_visibility(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_set_event_cb_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_event_cb()
 */
int utc_maps_view_set_event_cb_p(void)
{
	ret = maps_view_set_event_cb(maps_view_handle, MAPS_VIEW_EVENT_GESTURE, dummy_utc_maps_view_on_event_cb, NULL);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_event_cb_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_event_cb()
*/
int utc_maps_view_set_event_cb_n(void)
{
	ret = maps_view_set_event_cb(NULL, MAPS_VIEW_EVENT_GESTURE, dummy_utc_maps_view_on_event_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_event_cb(maps_view_handle, MAPS_VIEW_EVENT_GESTURE - 1, dummy_utc_maps_view_on_event_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_event_cb(maps_view_handle, MAPS_VIEW_EVENT_GESTURE, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_unset_event_cb_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_unset_event_cb()
 */
int utc_maps_view_unset_event_cb_p(void)
{
	ret = maps_view_unset_event_cb(maps_view_handle, MAPS_VIEW_EVENT_GESTURE);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_unset_event_cb_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_unset_event_cb()
*/
int utc_maps_view_unset_event_cb_n(void)
{
	ret = maps_view_unset_event_cb(NULL, MAPS_VIEW_EVENT_GESTURE);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_unset_event_cb(maps_view_handle, MAPS_VIEW_EVENT_GESTURE - 1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_set_gesture_enabled_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_gesture_enabled()
 */
int utc_maps_view_set_gesture_enabled_p(void)
{
	ret = maps_view_set_gesture_enabled(maps_view_handle, MAPS_VIEW_GESTURE_NONE, false);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_gesture_enabled_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_gesture_enabled()
*/
int utc_maps_view_set_gesture_enabled_n(void)
{
	ret = maps_view_set_gesture_enabled(NULL, MAPS_VIEW_GESTURE_NONE, false);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_gesture_enabled(maps_view_handle, MAPS_VIEW_GESTURE_NONE - 1, false);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_gesture_enabled_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_gesture_enabled()
 */
int utc_maps_view_get_gesture_enabled_p(void)
{
	bool enabled = false;

	ret = maps_view_get_gesture_enabled(maps_view_handle, MAPS_VIEW_GESTURE_NONE, &enabled);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_gesture_enabled_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_gesture_enabled()
*/
int utc_maps_view_get_gesture_enabled_n(void)
{
	bool enabled = false;

	ret = maps_view_get_gesture_enabled(NULL, MAPS_VIEW_GESTURE_NONE, &enabled);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_gesture_enabled(maps_view_handle, MAPS_VIEW_GESTURE_NONE - 1, &enabled);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_gesture_enabled(maps_view_handle, MAPS_VIEW_GESTURE_NONE, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_set_scalebar_enabled_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_scalebar_enabled()
 */
int utc_maps_view_set_scalebar_enabled_p(void)
{
	bool is_scalebar_supported = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_SCALEBAR, &is_scalebar_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_scalebar_enabled(maps_view_handle, false);
	if (is_internet_supported && is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_scalebar_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_set_scalebar_enabled_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_set_scalebar_enabled()
*/
int utc_maps_view_set_scalebar_enabled_n(void)
{
	bool is_scalebar_supported = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_SCALEBAR, &is_scalebar_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_scalebar_enabled(NULL, false);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_get_scalebar_enabled_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_get_scalebar_enabled()
 */
int utc_maps_view_get_scalebar_enabled_p(void)
{
	bool enabled = false;
	bool is_scalebar_supported = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_SCALEBAR, &is_scalebar_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_scalebar_enabled(maps_view_handle, &enabled);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_scalebar_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
* @testcase        utc_maps_view_get_scalebar_enabled_n
* @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
* @description     Negative test case of maps_view_get_scalebar_enabled()
*/
int utc_maps_view_get_scalebar_enabled_n(void)
{
	bool is_scalebar_supported = false;
	bool enabled = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_SCALEBAR, &is_scalebar_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_scalebar_enabled(NULL, &enabled);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_get_scalebar_enabled(maps_view_handle, NULL);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_scalebar_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/*
 * @testcase        utc_maps_view_add_object_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_add_object()
 */
int utc_maps_view_add_object_p(void)
{
	Evas_Object *eo = elm_button_add(win);
	assert(eo);

	maps_coordinates_h coord1 = NULL, coord2 = NULL;
	maps_coordinates_list_h coord_list = NULL;
	maps_view_object_h polyline = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 10.0, &coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polyline(coord_list, '1', '1', '1', '1', 1, &polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_add_object(maps_view_handle, polyline);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	ret = maps_view_foreach_object(maps_view_handle, dummy_maps_view_object_cb, NULL);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	ret = maps_view_remove_object(maps_view_handle, polyline);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	maps_coordinates_h coord = NULL;
	maps_view_object_h overlay = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_overlay(coord, eo, MAPS_VIEW_OVERLAY_BUBBLE, &overlay);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_add_object(maps_view_handle, overlay);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	ret = maps_view_remove_object(maps_view_handle, overlay);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/*
 * @testcase        utc_maps_view_add_object_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_add_object()
 */
int utc_maps_view_add_object_n(void)
{
	maps_coordinates_h coord1 = NULL, coord2 = NULL;
	maps_coordinates_list_h coord_list = NULL;
	maps_view_object_h polyline = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 10.0, &coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polyline(coord_list, '1', '1', '1', '1', 1, &polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_add_object(NULL, polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_add_object(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_destroy(polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_remove_object_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_remove_object()
 */
int utc_maps_view_remove_object_p(void)
{
	/* tested in utc_maps_view_add_object_p */
	return 0;
}

/*
 * @testcase        utc_maps_view_remove_object_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_remove_object()
 */
int utc_maps_view_remove_object_n(void)
{
	maps_coordinates_h coord1 = NULL, coord2 = NULL;
	maps_coordinates_list_h coord_list = NULL;
	maps_view_object_h polyline = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 10.0, &coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polyline(coord_list, '1', '1', '1', '1', 1, &polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_remove_object(NULL, polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_remove_object(maps_view_handle, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_destroy(polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_remove_all_objects_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_remove_all_objects()
 */
int utc_maps_view_remove_all_objects_p(void)
{
	ret = maps_view_remove_all_objects(maps_view_handle);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/*
 * @testcase        utc_maps_view_remove_all_objects_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_remove_all_objects()
 */
int utc_maps_view_remove_all_objects_n(void)
{
	ret = maps_view_remove_all_objects(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_foreach_object_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_foreach_object()
 */
int utc_maps_view_foreach_object_p(void)
{
	/* tested in utc_maps_view_add_object_p */
	return 0;
}

/*
 * @testcase        utc_maps_view_foreach_object_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_foreach_object()
 */
int utc_maps_view_foreach_object_n(void)
{
	ret = maps_view_foreach_object(NULL, dummy_maps_view_object_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_foreach_object(maps_view_handle, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_set_min_zoom_level_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_min_zoom_level()
 */
int utc_maps_view_set_min_zoom_level_p(void)
{
	ret = maps_view_set_min_zoom_level(maps_view_handle, 1);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/*
 * @testcase        utc_maps_view_set_min_zoom_level_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_set_min_zoom_level()
 */
int utc_maps_view_set_min_zoom_level_n(void)
{
	ret = maps_view_set_min_zoom_level(NULL, 1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_min_zoom_level(maps_view_handle, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_set_max_zoom_level_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_set_max_zoom_level()
 */
int utc_maps_view_set_max_zoom_level_p(void)
{
	ret = maps_view_set_max_zoom_level(maps_view_handle, 3);
	if (is_maps_supported == true) {
		ASSERT_IF_VAL_REF2(ret, is_maps_view_supported, MAPS_ERROR_NONE, MAPS_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/*
 * @testcase        utc_maps_view_set_max_zoom_level_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_set_max_zoom_level()
 */
int utc_maps_view_set_max_zoom_level_n(void)
{
	ret = maps_view_set_max_zoom_level(NULL, 3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_set_max_zoom_level(maps_view_handle, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_capture_snapshot_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_capture_snapshot()
 */
int utc_maps_view_capture_snapshot_p(void)
{
	bool is_snapshot_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_VIEW_SNAPSHOT, &is_snapshot_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_capture_snapshot(maps_view_handle, MAPS_VIEW_SNAPSHOT_BMP, 90, "/tmp/maps_tmp_image.bmp");
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_snapshot_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	ret = maps_view_capture_snapshot(maps_view_handle, MAPS_VIEW_SNAPSHOT_JPEG, 90, "/tmp/maps_tmp_image.jpg");
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_snapshot_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/*
 * @testcase        utcmaps_view_capture_snapshot_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_capture_snapshot()
 */
int utc_maps_view_capture_snapshot_n(void)
{
	char *path = "/tmp/maps_tmp_image.bmp";
	bool is_snapshot_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_VIEW_SNAPSHOT, &is_snapshot_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_capture_snapshot(NULL, MAPS_VIEW_SNAPSHOT_BMP, 50, path);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_capture_snapshot(maps_view_handle, MAPS_VIEW_SNAPSHOT_BMP - 1, 50, path);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_snapshot_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	ret = maps_view_capture_snapshot(maps_view_handle, MAPS_VIEW_SNAPSHOT_BMP, -1, path);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_snapshot_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	ret = maps_view_capture_snapshot(maps_view_handle, MAPS_VIEW_SNAPSHOT_BMP, 50, NULL);
	if (is_maps_supported == true) {
		if (is_maps_view_supported == true) {
			ASSERT_IF_VAL_REF2(ret, is_snapshot_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
		} else {
			assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);
		}
	} else {
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_maps_view_destroy_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_destroy()
 */
int utc_maps_view_destroy_p(void)
{
	/* tested in utc_maps_view_create_p */

	return 0;
}

/**
 * @testcase		utc_maps_view_destroy_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_destroy()
 */
int utc_maps_view_destroy_n(void)
{
	ret = maps_view_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
