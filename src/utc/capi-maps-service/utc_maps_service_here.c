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
#include <maps_error.h>
#include <maps_service.h>
#include <unistd.h>
#include <glib.h>
#include "utc_maps_utils.h"


static int ret = 0;
static maps_service_h __pMaps = NULL;
static bool service_available = false;
static GMainLoop *mainloop = NULL;
static maps_preference_h __preference = NULL;
static char *__place_uri = NULL;
static char maps_provider_key[CONFIG_VALUE_LEN_MAX] = {0,};
static const int INVALID_REQUEST_ID = -1;
static bool is_internet_supported = false;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_service_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_service_startup(void)
{
	if (__pMaps) return;

	is_internet_supported = _is_internet_feature_supported();
	is_maps_supported = _is_maps_feature_supported();

	GetValueFromConfigFile("HERE_MAPS_PROVIDER_KEY", maps_provider_key, API_NAMESPACE);

	maps_service_create(__utc_get_maps_provider_name_here(), &__pMaps);
	maps_service_set_provider_key(__pMaps, maps_provider_key);

	maps_preference_create(&__preference);
	maps_preference_set_max_results(__preference, 10);
	maps_service_set_preference(__pMaps, __preference);
}

/**
 * @function		utc_maps_service_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_service_cleanup(void)
{
	maps_preference_destroy(__preference);
	maps_service_destroy(__pMaps);

	__preference = NULL;
	__pMaps = NULL;

	ret = 0;
	mainloop = NULL;
}

static gboolean timeout_func(gpointer data)
{
	g_main_loop_quit((GMainLoop *) data);
	g_main_loop_unref((GMainLoop *) data);
	return FALSE;
}

static void wait_for_service(void)
{
	int timeout_id = 0;
	mainloop = g_main_loop_new(NULL, FALSE);

	timeout_id = g_timeout_add(30000, timeout_func, mainloop);
	g_main_loop_run(mainloop);
	g_source_remove(timeout_id);
}

static void quit_for_service(void)
{
	if (mainloop) {
		g_main_loop_quit(mainloop);
		g_main_loop_unref(mainloop);
		mainloop = NULL;
	}
}

static bool __utc_maps_service_provider_info_cb(char *maps_provider, void *user_data)
{
	free(maps_provider);
	service_available = true;
	return true;
}

/**
 * @testcase		utc_maps_service_foreach_provider_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_foreach_provider()
 */
int utc_maps_service_foreach_provider_p(void)
{
	ret = maps_service_foreach_provider(__utc_maps_service_provider_info_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(service_available);
	service_available = false;

	return 0;
}

/**
 * @testcase		utc_maps_service_foreach_provider_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_foreach_provider()
 */
int utc_maps_service_foreach_provider_n(void)
{
	ret = maps_service_foreach_provider(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_create_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_create()
 */
int utc_maps_service_create_p(void)
{
	maps_service_h service = NULL;

	ret = maps_service_create(__utc_get_maps_provider_name_here(), &service);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(service);

	ret = maps_service_destroy(service);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_create_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_create()
 */
int utc_maps_service_create_n(void)
{
	maps_service_h maps = NULL;

	ret = maps_service_create(__utc_get_maps_provider_name_here(), NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_create(NULL, &maps);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_create(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_create("test", &maps);
	assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_destroy_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_destroy()
 */
int utc_maps_service_destroy_p(void)
{
	/* tested in utc_maps_service_create_p */
	return 0;
}

/**
 * @testcase		utc_maps_service_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_destroy()
 */
int utc_maps_service_destroy_n(void)
{
	ret = maps_service_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_set_provider_key_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_set_provider_key()
 */
int utc_maps_service_set_provider_key_p(void)
{
	ret = maps_service_set_provider_key(__pMaps, maps_provider_key);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_set_provider_key_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_set_provider_key()
 */
int utc_maps_service_set_provider_key_n(void)
{
	ret = maps_service_set_provider_key(__pMaps, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_set_provider_key(NULL, maps_provider_key);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_set_provider_key(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	return 0;
}

/**
 * @testcase		utc_maps_service_get_provider_key_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_get_provider_key()
 */
int utc_maps_service_get_provider_key_p(void)
{
	char *maps_key = NULL;

	ret = maps_service_get_provider_key(__pMaps, &maps_key);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(maps_key);
	return 0;
}

/**
 * @testcase		utc_maps_service_get_provider_key_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_get_provider_key()
 */
int utc_maps_service_get_provider_key_n(void)
{
	char *maps_key = NULL;

	ret = maps_service_get_provider_key(NULL, &maps_key);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_get_provider_key(__pMaps, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_set_preference_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_set_preference()
 */
int utc_maps_service_set_preference_p(void)
{
	maps_preference_h preference;

	ret = maps_preference_create(&preference);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_set_max_results(preference, 10);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_set_preference(__pMaps, preference);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_preference_destroy(preference);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_set_preference_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_set_preference()
 */
int utc_maps_service_set_preference_n(void)
{
	ret = maps_service_set_preference(__pMaps, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_set_preference(NULL, __preference);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_set_preference(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_get_preference_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_get_preference()
 */
int utc_maps_service_get_preference_p(void)
{
	maps_preference_h preference = NULL;

	ret = maps_service_get_preference(__pMaps, &preference);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_get_preference_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_get_preference()
 */
int utc_maps_service_get_preference_n(void)
{
	maps_preference_h pref = NULL;

	ret = maps_service_get_preference(__pMaps, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_get_preference(NULL, &pref);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_get_preference(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_provider_is_service_supported_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_provider_is_service_supported()
 */
int utc_maps_service_provider_is_service_supported_p(void)
{
	bool test = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_GEOCODE, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_GEOCODE_INSIDE_AREA, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_GEOCODE_BY_STRUCTURED_ADDRESS, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_REVERSE_GEOCODE, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE_BY_AREA, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE_BY_ADDRESS, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_ROUTE, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_ROUTE_WAYPOINTS, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_CANCEL_REQUEST, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_MULTI_REVERSE_GEOCODE, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE_LIST, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_GET_PLACE_DETAILS, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_VIEW, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_VIEW_SNAPSHOT, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_provider_is_service_supported_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_provider_is_service_supported()
 */
int utc_maps_service_provider_is_service_supported_n(void)
{
	bool test = false;

	ret = maps_service_provider_is_service_supported(__pMaps, 100, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(NULL, MAPS_SERVICE_GEOCODE, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_GEOCODE, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, -1, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_provider_is_data_supported_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_provider_is_data_supported()
 */
int utc_maps_service_provider_is_data_supported_p(void)
{
	bool test = false;

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_ADDRESS, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_RATING, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_CATEGORIES, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_ATTRIBUTES, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_CONTACTS, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_EDITORIALS, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_REVIEWS, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_IMAGE, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_SUPPLIER, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_RELATED, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_ROUTE_PATH, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_ROUTE_SEGMENTS_PATH, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_ROUTE_SEGMENTS_MANEUVERS, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_TRAFFIC, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_PUBLIC_TRANSIT, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_BUILDING, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_VIEW_SCALEBAR, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_provider_is_data_supported_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_provider_is_data_supported()
 */
int utc_maps_service_provider_is_data_supported_n(void)
{
	bool test = false;

	ret = maps_service_provider_is_data_supported(__pMaps, 100, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(NULL, MAPS_PLACE_ADDRESS, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, -1, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_data_supported(__pMaps, MAPS_PLACE_ADDRESS, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_location_foreach_cb(maps_error_e result, int request_id, int index, int total, maps_coordinates_h coord, void *user_data)
{
	maps_coordinates_destroy(coord);

	if (result == MAPS_ERROR_NONE) {
		if (index + 1 < total) return true;
		service_available = true;
	}

	quit_for_service();
	return false;
}

/**
 * @testcase		utc_maps_service_geocode_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_geocode()
 */
int utc_maps_service_geocode_p(void)
{
	int request_id = INVALID_REQUEST_ID;
	bool is_geocode_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_GEOCODE, &is_geocode_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode(__pMaps, "Berlin", __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_internet_supported && is_maps_supported && is_geocode_supported) {
		wait_for_service();
		assert(service_available);
		service_available = false;
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_geocode_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_geocode()
 */
int utc_maps_service_geocode_n(void)
{
	int request_id = INVALID_REQUEST_ID;
	bool is_geocode_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_GEOCODE, &is_geocode_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode(NULL, "Bangalore, India", __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode(__pMaps, NULL, __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode(__pMaps, "Bangalore, India", __preference, NULL, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode(__pMaps, "Bangalore, India", __preference, __utc_maps_location_foreach_cb, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode(NULL, NULL, NULL, NULL, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_geocode_inside_area_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_geocode_inside_area()
 */
int utc_maps_service_geocode_inside_area_p(void)
{
	maps_area_h boundary = NULL;
	maps_coordinates_h top_left = NULL;
	maps_coordinates_h bottom_right = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_geocode_inside_area_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_GEOCODE_INSIDE_AREA, &is_geocode_inside_area_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		maps_coordinates_create(15.665354, 74.311523, &top_left);
		maps_coordinates_create(10.617418, 79.145508, &bottom_right);
		assert(top_left);
		assert(bottom_right);

		ret = maps_area_create_rectangle(top_left, bottom_right, &boundary);
		ret = maps_coordinates_destroy(top_left);
		assert_eq(ret, MAPS_ERROR_NONE);
		ret = maps_coordinates_destroy(bottom_right);

		assert_eq(ret, MAPS_ERROR_NONE);
		assert(boundary);

		ret = maps_service_geocode_inside_area(__pMaps, "Bengaluru", boundary, __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
		if (is_internet_supported && is_geocode_inside_area_supported) {
			assert_eq(ret, MAPS_ERROR_NONE);

			wait_for_service();
			assert(service_available);
			service_available = false;

			ret = maps_area_destroy(boundary);
			assert_eq(ret, MAPS_ERROR_NONE);
		} else {
			ret = maps_area_destroy(boundary);

			assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
		}
	} else {
		ret = maps_service_geocode_inside_area(__pMaps, "Bengaluru", boundary, __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_geocode_inside_area_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_geocode_inside_area()
 */
int utc_maps_service_geocode_inside_area_n(void)
{
	maps_area_h boundary = NULL;
	maps_coordinates_h top_left = NULL;
	maps_coordinates_h bottom_right = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_geocode_inside_area_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_GEOCODE_INSIDE_AREA, &is_geocode_inside_area_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		maps_coordinates_create(15.665354, 74.311523, &top_left);
		maps_coordinates_create(10.617418, 79.145508, &bottom_right);
		assert(top_left);
		assert(bottom_right);

		ret = maps_area_create_rectangle(top_left, bottom_right, &boundary);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(boundary);
	}
	ret = maps_service_geocode_inside_area(NULL, "Berlin", boundary, __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode_inside_area(__pMaps, NULL, boundary, __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_inside_area_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode_inside_area(__pMaps, "Berlin", NULL, __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_inside_area_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode_inside_area(__pMaps, "Berlin", boundary, __preference, NULL, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_inside_area_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode_inside_area(__pMaps, "Berlin", boundary, __preference, __utc_maps_location_foreach_cb, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_inside_area_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode_inside_area(NULL, NULL, NULL, NULL, NULL, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(top_left);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(bottom_right);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_area_destroy(boundary);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_geocode_by_structured_address_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_geocode_by_structured_address()
 */
int utc_maps_service_geocode_by_structured_address_p(void)
{
	maps_address_h address = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_geocode_by_structured_address_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_GEOCODE_BY_STRUCTURED_ADDRESS, &is_geocode_by_structured_address_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_address_create(&address);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(address);

		ret = maps_address_set_city(address, "Berlin");
		assert_eq(ret, MAPS_ERROR_NONE);
		/* ret= maps_address_set_street(address, "Rosa-Luxemburg"); */
		/* assert_eq(ret, MAPS_ERROR_NONE); */
		/* ret = maps_address_set_building_number(address, "13"); */
		/* assert_eq(ret, MAPS_ERROR_NONE); */

		ret = maps_service_geocode_by_structured_address(__pMaps, address, __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
		if (is_internet_supported && is_geocode_by_structured_address_supported) {
			assert_eq(ret, MAPS_ERROR_NONE);

			wait_for_service();
			assert(service_available);
			service_available = false;

			ret = maps_address_destroy(address);
			assert_eq(ret, MAPS_ERROR_NONE);
		} else {
			maps_address_destroy(address);
			assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
		}
	} else {
		ret = maps_service_geocode_by_structured_address(__pMaps, address, __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_geocode_by_structured_address_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_geocode_by_structured_address()
 */
int utc_maps_service_geocode_by_structured_address_n(void)
{
	maps_address_h address = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_geocode_by_structured_address_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_GEOCODE_BY_STRUCTURED_ADDRESS, &is_geocode_by_structured_address_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_address_create(&address);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(address);
	}
	ret = maps_address_set_city(address, "Seoul");
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode_by_structured_address(NULL, address, __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode_by_structured_address(__pMaps, NULL, __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_by_structured_address_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode_by_structured_address(__pMaps, address, __preference, NULL, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_by_structured_address_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode_by_structured_address(__pMaps, address, __preference, __utc_maps_location_foreach_cb, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_geocode_by_structured_address_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode_by_structured_address(NULL, NULL, NULL, NULL, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_address_destroy(address);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static void __utc_maps_address_foreach_cb(maps_error_e result, int request_id, int index, int total, maps_address_h address, void *user_data)
{
	maps_address_destroy(address);

	if (result == MAPS_ERROR_NONE) {
		if (index + 1 < total) return;
		service_available = true;
	}

	quit_for_service();
}

/**
 * @testcase		utc_maps_service_reverse_geocode_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_reverse_geocode()
 */
int utc_maps_service_reverse_geocode_p(void)
{
	int request_id = INVALID_REQUEST_ID;
	bool is_reverse_geocode_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_REVERSE_GEOCODE, &is_reverse_geocode_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_reverse_geocode(__pMaps, 12.944594, 77.554303, __preference, __utc_maps_address_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_reverse_geocode_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_internet_supported && is_maps_supported && is_reverse_geocode_supported) {
		wait_for_service();
		assert(service_available);
		service_available = false;
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_reverse_geocode_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_reverse_geocode()
 */
int utc_maps_service_reverse_geocode_n(void)
{
	int request_id = INVALID_REQUEST_ID;
	bool is_reverse_geocode_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_REVERSE_GEOCODE, &is_reverse_geocode_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_reverse_geocode(NULL, 12.944594, 77.554303, __preference, __utc_maps_address_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_reverse_geocode(__pMaps,  12.944594, 77.554303, __preference, __utc_maps_address_foreach_cb, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_reverse_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_reverse_geocode(__pMaps,  -91.00, 77.554303, __preference, __utc_maps_address_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_reverse_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_reverse_geocode(__pMaps,  12.944594, 181.4546, __preference, __utc_maps_address_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_reverse_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_reverse_geocode(__pMaps,  12.944594, 77.554303, __preference, NULL, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_reverse_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_reverse_geocode(NULL,  12.944594, 77.554303, NULL, NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_cancel_request_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_cancel_request()
 */
int utc_maps_service_cancel_request_p(void)
{
	int request_id = INVALID_REQUEST_ID;
	bool is_cancel_request_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_CANCEL_REQUEST, &is_cancel_request_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_geocode(__pMaps, "Bangalore, India", __preference, __utc_maps_location_foreach_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_cancel_request_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_internet_supported && is_maps_supported && is_cancel_request_supported) {
		ret = maps_service_cancel_request(__pMaps, request_id);
		assert_eq(ret, MAPS_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_cancel_request_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_cancel_request()
 */
int utc_maps_service_cancel_request_n(void)
{
	int request_id = INVALID_REQUEST_ID;
	bool is_cancel_request_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_CANCEL_REQUEST, &is_cancel_request_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_cancel_request(NULL, request_id);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_cancel_request(__pMaps, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported && is_cancel_request_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_cancel_request(NULL, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_route_service_found_cb(maps_error_e result, int request_id, int index, int total, maps_route_h route, void *user_data)
{
	maps_route_destroy(route);

	if (result == MAPS_ERROR_NONE) {
		if (index + 1 < total) return true;
		service_available = true;
	}

	quit_for_service();
	return false;
}

/**
 * @testcase		utc_maps_service_search_route_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_search_route()
 */
int utc_maps_service_search_route_p(void)
{
	maps_coordinates_h origin = NULL;
	maps_coordinates_h dest = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_route_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_ROUTE, &is_search_route_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		maps_coordinates_create(37.564263, 126.974676, &origin);
		maps_coordinates_create(37.557120, 126.992410, &dest);
		assert(origin);
		assert(dest);

		ret = maps_service_search_route(__pMaps, origin, dest, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
		if (is_internet_supported && is_search_route_supported) {
			assert_eq(ret, MAPS_ERROR_NONE);

			wait_for_service();
			assert(service_available);
			service_available = false;

			ret = maps_coordinates_destroy(origin);
			assert_eq(ret, MAPS_ERROR_NONE);
			ret = maps_coordinates_destroy(dest);
			assert_eq(ret, MAPS_ERROR_NONE);
		} else {
			assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
		}
	} else {
		ret = maps_service_search_route(__pMaps, origin, dest, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_search_route_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_search_route()
 */
int utc_maps_service_search_route_n(void)
{
	maps_coordinates_h origin = NULL;
	maps_coordinates_h dest = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_route_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_ROUTE, &is_search_route_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_coordinates_create(37.564263, 126.974676, &origin);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(origin);

		ret = maps_coordinates_create(37.557120, 126.992410, &dest);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(dest);
	}
	ret = maps_service_search_route(NULL, origin, dest, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_search_route(__pMaps, NULL, dest, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_search_route_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_search_route(__pMaps, origin, NULL, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_search_route_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_search_route(__pMaps, origin, dest, __preference,  NULL, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_search_route_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_search_route(__pMaps, origin, dest, __preference, __utc_maps_route_service_found_cb, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_search_route_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_search_route(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(origin);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(dest);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_search_route_waypoints_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_search_route_waypoints()
 */
int utc_maps_service_search_route_waypoints_p(void)
{
	maps_coordinates_h *waypoints = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_route_waypoint_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_ROUTE_WAYPOINTS, &is_search_route_waypoint_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		waypoints = (maps_coordinates_h *)g_malloc(sizeof(maps_coordinates_h)*3);
		maps_coordinates_create(37.564263, 126.974676, &waypoints[0]);
		maps_coordinates_create(37.557120, 126.992410, &waypoints[1]);
		maps_coordinates_create(37.550120, 126.982410, &waypoints[2]);
		assert(waypoints[0]);
		assert(waypoints[1]);
		assert(waypoints[2]);

		ret = maps_service_search_route_waypoints(__pMaps, waypoints, 3, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
		if (is_internet_supported && is_search_route_waypoint_supported) {
			assert_eq(ret, MAPS_ERROR_NONE);

			wait_for_service();
			assert(service_available);
			service_available = false;

			ret = maps_coordinates_destroy(waypoints[0]);
			assert_eq(ret, MAPS_ERROR_NONE);
			ret = maps_coordinates_destroy(waypoints[1]);
			assert_eq(ret, MAPS_ERROR_NONE);
			ret = maps_coordinates_destroy(waypoints[2]);
			assert_eq(ret, MAPS_ERROR_NONE);
		} else {
			assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
		}
		g_free(waypoints);
	} else {
		ret = maps_service_search_route_waypoints(__pMaps, waypoints, 3, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_search_route_waypoints_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_search_route_waypoints()
 */
int utc_maps_service_search_route_waypoints_n(void)
{
	maps_coordinates_h *waypoints = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_route_waypoint_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_ROUTE_WAYPOINTS, &is_search_route_waypoint_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		waypoints = (maps_coordinates_h *)g_malloc(sizeof(maps_coordinates_h)*3);
		maps_coordinates_create(37.564263, 126.974676, &waypoints[0]);
		maps_coordinates_create(37.557120, 126.992410, &waypoints[1]);
		maps_coordinates_create(37.550120, 126.982410, &waypoints[2]);
		assert(waypoints[0]);
		assert(waypoints[1]);
		assert(waypoints[2]);

		ret = maps_service_search_route_waypoints(NULL, waypoints, 3, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_route_waypoints(__pMaps, NULL, 3, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_route_waypoint_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_route_waypoints(__pMaps, waypoints, 3, __preference, NULL, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_route_waypoint_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_route_waypoints(__pMaps, waypoints, 3, __preference, __utc_maps_route_service_found_cb, NULL, NULL);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_route_waypoint_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_route_waypoints(__pMaps, waypoints, -1, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_route_waypoint_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_route_waypoints(NULL, NULL, 0, NULL, NULL, NULL, NULL);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		assert(!service_available);
		service_available = false;

		ret = maps_coordinates_destroy(waypoints[0]);
		assert_eq(ret, MAPS_ERROR_NONE);
		ret = maps_coordinates_destroy(waypoints[1]);
		assert_eq(ret, MAPS_ERROR_NONE);
		ret = maps_coordinates_destroy(waypoints[2]);
		assert_eq(ret, MAPS_ERROR_NONE);

		g_free(waypoints);
	} else {
		ret = maps_service_search_route_waypoints(NULL, waypoints, 3, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_route_waypoints(__pMaps, NULL, 3, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_route_waypoints(__pMaps, waypoints, 3, __preference, NULL, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_route_waypoints(__pMaps, waypoints, 3, __preference, __utc_maps_route_service_found_cb, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_route_waypoints(__pMaps, waypoints, -1, __preference, __utc_maps_route_service_found_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_route_waypoints(NULL, NULL, 0, NULL, NULL, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

static bool __utc_maps_service_search_place_cb(maps_error_e result, int request_id , int index, int total, maps_place_h place, void *user_data)
{
	maps_place_destroy(place);

	if (result == MAPS_ERROR_NONE) {
		if (index + 1 < total) return true;
		service_available = true;
	}

	quit_for_service();
	return false;
}

/**
 * @testcase		utc_maps_service_search_place_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_search_place()
 */
int utc_maps_service_search_place_p(void)
{
	maps_place_filter_h places_fil = NULL;
	maps_coordinates_h coords = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_place_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE, &is_search_place_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_place_filter_create(&places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(places_fil);

		ret = maps_place_filter_set_keyword(places_fil, "restaurant");
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_place_filter_set_place_name(places_fil, "Berlin");
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_create(52.5167, 13.383, &coords);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(coords);

		ret = maps_service_search_place(__pMaps, coords, 100, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		if (is_internet_supported && is_search_place_supported) {
			assert_eq(ret, MAPS_ERROR_NONE);

			wait_for_service();
			assert(service_available);
			service_available = false;

			ret = maps_coordinates_destroy(coords);
			assert_eq(ret, MAPS_ERROR_NONE);

			ret = maps_place_filter_destroy(places_fil);
			assert_eq(ret, MAPS_ERROR_NONE);
		} else {
			assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
		}
	} else {
		ret = maps_service_search_place(__pMaps, coords, 100, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_search_place_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_search_place()
 */
int utc_maps_service_search_place_n(void)
{
	maps_place_filter_h places_fil = NULL;
	int request_id = INVALID_REQUEST_ID;
	maps_coordinates_h coords = NULL;
	bool is_search_place_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE, &is_search_place_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_place_filter_create(&places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(places_fil);

		ret = maps_place_filter_set_keyword(places_fil, "restaurant");
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_place_filter_set_place_name(places_fil, "Berlin");
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_create(52.5167, 13.383, &coords);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(coords);

		ret = maps_service_search_place(NULL, coords, 100, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(__pMaps, NULL, 100, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(__pMaps, coords, 100, NULL, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(__pMaps, coords, 0,  places_fil, __preference, NULL, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(__pMaps, coords, 0,  places_fil, __preference, __utc_maps_service_search_place_cb, NULL, NULL);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(NULL, NULL, 0,  NULL, NULL, NULL, NULL, NULL);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(__pMaps, coords, -1, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		assert(!service_available);
		service_available = false;

		ret = maps_coordinates_destroy(coords);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_place_filter_destroy(places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_service_search_place(NULL, coords, 100, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(__pMaps, NULL, 100, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(__pMaps, coords, 100, NULL, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(__pMaps, coords, 0,  places_fil, __preference, NULL, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(__pMaps, coords, 0,  places_fil, __preference, __utc_maps_service_search_place_cb, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(NULL, NULL, 0,  NULL, NULL, NULL, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place(__pMaps, coords, -1, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_search_place_by_area_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_search_place_by_area()
 */
int utc_maps_service_search_place_by_area_p(void)
{
	maps_place_filter_h places_fil = NULL;
	maps_area_h area = NULL;
	maps_coordinates_h top_left = NULL;
	maps_coordinates_h bottom_right = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_place_by_area_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE_BY_AREA, &is_search_place_by_area_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_place_filter_create(&places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(places_fil);

		ret = maps_place_filter_set_keyword(places_fil, "restaurant");
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_place_filter_set_place_name(places_fil, "Berlin");
		assert_eq(ret, MAPS_ERROR_NONE);

		maps_coordinates_create(52.51605, 12.37691, &top_left);
		maps_coordinates_create(54.12351, 14.22351, &bottom_right);
		assert(top_left);
		assert(bottom_right);

		ret = maps_area_create_rectangle(top_left, bottom_right, &area);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(area);

		ret = maps_service_search_place_by_area(__pMaps, area,  places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		if (is_internet_supported && is_search_place_by_area_supported) {
			assert_eq(ret, MAPS_ERROR_NONE);

			wait_for_service();
			assert(service_available);
			service_available = false;

			ret = maps_coordinates_destroy(top_left);
			assert_eq(ret, MAPS_ERROR_NONE);

			ret = maps_coordinates_destroy(bottom_right);
			assert_eq(ret, MAPS_ERROR_NONE);

			ret = maps_area_destroy(area);
			assert_eq(ret, MAPS_ERROR_NONE);

			ret = maps_place_filter_destroy(places_fil);
			assert_eq(ret, MAPS_ERROR_NONE);
		} else
			assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	} else {
		ret = maps_service_search_place_by_area(__pMaps, area,  places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_search_place_by_area_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_search_place_by_area()
 */
int utc_maps_service_search_place_by_area_n(void)
{
	maps_place_filter_h places_fil = NULL;
	maps_area_h area = NULL;
	maps_coordinates_h top_left = NULL;
	maps_coordinates_h bottom_right = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_place_by_area_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE_BY_AREA, &is_search_place_by_area_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_place_filter_create(&places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(places_fil);

		ret = maps_place_filter_set_keyword(places_fil, "restaurant");
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_place_filter_set_place_name(places_fil, "Berlin");
		assert_eq(ret, MAPS_ERROR_NONE);

		maps_coordinates_create(15.665354, 74.311523, &top_left);
		maps_coordinates_create(10.617418, 79.145508, &bottom_right);
		assert(top_left);
		assert(bottom_right);

		ret = maps_area_create_rectangle(top_left, bottom_right, &area);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(area);

		ret = maps_service_search_place_by_area(NULL, area,  places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_area(__pMaps, NULL,  places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_by_area_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_area(__pMaps, area, NULL, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_by_area_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_area(__pMaps, area, places_fil, __preference, NULL, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_by_area_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_area(__pMaps, area, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, NULL);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_by_area_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_area(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		assert(!service_available);
		service_available = false;

		ret = maps_coordinates_destroy(top_left);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_destroy(bottom_right);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_area_destroy(area);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_place_filter_destroy(places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_service_search_place_by_area(NULL, area,  places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_area(__pMaps, NULL,  places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_area(__pMaps, area, NULL, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_area(__pMaps, area, places_fil, __preference, NULL, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_area(__pMaps, area, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_area(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_search_place_by_address_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_search_place_by_address()
 */
int utc_maps_service_search_place_by_address_p(void)
{
	maps_place_filter_h places_fil = NULL;
	maps_area_h area = NULL;
	maps_coordinates_h top_left = NULL;
	maps_coordinates_h bottom_right = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_place_by_address_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE_BY_ADDRESS, &is_search_place_by_address_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_place_filter_create(&places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(places_fil);

		maps_coordinates_create(15.665354, 74.311523, &top_left);
		maps_coordinates_create(10.617418, 79.145508, &bottom_right);
		assert(top_left);
		assert(bottom_right);

		ret = maps_area_create_rectangle(top_left, bottom_right, &area);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(area);

		ret = maps_service_search_place_by_address(__pMaps, "Bengaluru", area, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		if (is_internet_supported && is_search_place_by_address_supported) {
			assert_eq(ret, MAPS_ERROR_NONE);

			wait_for_service();
			assert(service_available);
			service_available = false;

			ret = maps_place_filter_destroy(places_fil);
			assert_eq(ret, MAPS_ERROR_NONE);
		} else
			assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	} else {
		ret = maps_service_search_place_by_address(__pMaps, "Bengaluru", area, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_search_place_by_address_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_search_place_by_address()
 */
int utc_maps_service_search_place_by_address_n(void)
{
	maps_place_filter_h places_fil = NULL;
	maps_area_h area = NULL;
	maps_coordinates_h top_left = NULL;
	maps_coordinates_h bottom_right = NULL;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_place_by_address_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE_BY_ADDRESS, &is_search_place_by_address_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_place_filter_create(&places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(places_fil);

		ret = maps_place_filter_set_keyword(places_fil, "restaurant");
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_place_filter_set_place_name(places_fil, "Berlin");
		assert_eq(ret, MAPS_ERROR_NONE);

		maps_coordinates_create(15.665354, 74.311523, &top_left);
		maps_coordinates_create(10.617418, 79.145508, &bottom_right);
		assert(top_left);
		assert(bottom_right);

		ret = maps_area_create_rectangle(top_left, bottom_right, &area);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(area);

		ret = maps_service_search_place_by_address(NULL, "Berlin", area, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(__pMaps, NULL, area, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_by_address_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(__pMaps, "Berlin", NULL, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_by_address_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(__pMaps, "Berlin", area, NULL, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_by_address_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(__pMaps, "Berlin", area, places_fil, __preference, NULL, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_by_address_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(__pMaps, "Berlin", area,  places_fil, __preference, __utc_maps_service_search_place_cb, NULL, NULL);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_by_address_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(NULL, NULL, NULL,  NULL, NULL, NULL, NULL, NULL);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		assert(!service_available);
		service_available = false;

		ret = maps_place_filter_destroy(places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_service_search_place_by_address(NULL, "Berlin", area, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(__pMaps, NULL, area, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(__pMaps, "Berlin", NULL, places_fil, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(__pMaps, "Berlin", area, NULL, __preference, __utc_maps_service_search_place_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(__pMaps, "Berlin", area, places_fil, __preference, NULL, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(__pMaps, "Berlin", area,  places_fil, __preference, __utc_maps_service_search_place_cb, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_by_address(NULL, NULL, NULL,  NULL, NULL, NULL, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

static bool __utc_maps_service_multi_reverse_geocode_cb(maps_error_e result, int request_id, int total, maps_address_list_h address_list, void *user_data)
{
	maps_address_list_destroy(address_list);

	if (result == MAPS_ERROR_NONE)
		service_available = true;

	quit_for_service();
	return false;
}

/**
 * @testcase		utc_maps_service_multi_reverse_geocode_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_multi_reverse_geocode()
 */
int utc_maps_service_multi_reverse_geocode_p(void)
{
	int request_id = INVALID_REQUEST_ID;
	maps_coordinates_list_h coordinates_list = NULL;
	maps_coordinates_h *coord = NULL;
	bool is_multi_reverse_geocode_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_MULTI_REVERSE_GEOCODE, &is_multi_reverse_geocode_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_coordinates_list_create(&coordinates_list);
		assert_eq(ret, MAPS_ERROR_NONE);

		coord = (maps_coordinates_h *)g_malloc(sizeof(maps_coordinates_h)*3);
		maps_coordinates_create(52.5309, 13.3845, &coord[0]);
		maps_coordinates_create(50.1618996, 8.5334997, &coord[1]);
		maps_coordinates_create(40.72962607104243, -73.98685008095087, &coord[2]);
		assert(coord[0]);
		assert(coord[1]);
		assert(coord[2]);

		ret = maps_coordinates_list_append(coordinates_list, coord[0]);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_list_append(coordinates_list, coord[1]);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_list_append(coordinates_list, coord[2]);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_service_multi_reverse_geocode(__pMaps, coordinates_list, __preference, __utc_maps_service_multi_reverse_geocode_cb, NULL, &request_id);
		if (is_internet_supported && is_multi_reverse_geocode_supported) {
			assert_eq(ret, MAPS_ERROR_NONE);

			wait_for_service();
			assert(service_available);
			service_available = false;

			ret = maps_coordinates_list_destroy(coordinates_list);
			assert_eq(ret, MAPS_ERROR_NONE);
		} else
			assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
		g_free(coord);
	} else {
		ret = maps_service_multi_reverse_geocode(__pMaps, coordinates_list, __preference, __utc_maps_service_multi_reverse_geocode_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_multi_reverse_geocode_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_multi_reverse_geocode()
 */
int utc_maps_service_multi_reverse_geocode_n(void)
{
	int request_id = INVALID_REQUEST_ID;
	maps_coordinates_list_h coordinates_list = NULL;
	maps_coordinates_h *coord = NULL;
	bool is_multi_reverse_geocode_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_MULTI_REVERSE_GEOCODE, &is_multi_reverse_geocode_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_coordinates_list_create(&coordinates_list);
		assert_eq(ret, MAPS_ERROR_NONE);

		coord = (maps_coordinates_h *)g_malloc(sizeof(maps_coordinates_h)*3);
		maps_coordinates_create(52.5309, 13.3845, &coord[0]);
		maps_coordinates_create(50.1618996, 8.5334997, &coord[1]);
		maps_coordinates_create(40.72962607104243, -73.98685008095087, &coord[2]);
		assert(coord[0]);
		assert(coord[1]);
		assert(coord[2]);

		ret = maps_coordinates_list_append(coordinates_list, coord[0]);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_list_append(coordinates_list, coord[1]);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_list_append(coordinates_list, coord[2]);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_service_multi_reverse_geocode(NULL, coordinates_list, __preference, __utc_maps_service_multi_reverse_geocode_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_multi_reverse_geocode(__pMaps, NULL, __preference, __utc_maps_service_multi_reverse_geocode_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_multi_reverse_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_multi_reverse_geocode(__pMaps, coordinates_list, __preference, NULL, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_multi_reverse_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_multi_reverse_geocode(__pMaps, coordinates_list, __preference, __utc_maps_service_multi_reverse_geocode_cb, NULL, NULL);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_multi_reverse_geocode_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		assert(!service_available);
		service_available = false;

		ret = maps_coordinates_list_destroy(coordinates_list);
		assert_eq(ret, MAPS_ERROR_NONE);

		g_free(coord);
	} else {
		ret = maps_service_multi_reverse_geocode(NULL, coordinates_list, __preference, __utc_maps_service_multi_reverse_geocode_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_multi_reverse_geocode(__pMaps, NULL, __preference, __utc_maps_service_multi_reverse_geocode_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_multi_reverse_geocode(__pMaps, coordinates_list, __preference, NULL, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_multi_reverse_geocode(__pMaps, coordinates_list, __preference, __utc_maps_service_multi_reverse_geocode_cb, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

static bool __utc_maps_place_cb(int index, maps_place_h place, void *user_data)
{
	if (index == 0) {
		maps_place_get_uri(place, &__place_uri);
	}

	return true;
}

static void __utc_maps_service_search_place_list_cb(maps_error_e result, int request_id, int total, maps_place_list_h place_list, void *user_data)
{
	if (result == MAPS_ERROR_NONE) {
		maps_place_list_foreach(place_list, __utc_maps_place_cb, NULL);
		service_available = true;
	}
	maps_place_list_destroy(place_list);

	quit_for_service();
}

/**
 * @testcase		utc_maps_service_search_place_list_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_search_place_list()
 */
int utc_maps_service_search_place_list_p(void)
{
	if (__place_uri != NULL) {
		free(__place_uri);
		__place_uri = NULL;
	}

	maps_place_filter_h places_fil = NULL;
	maps_coordinates_h coords = NULL;
	maps_area_h boundary = NULL;
	int distance = 504295;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_place_list_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE_LIST, &is_search_place_list_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_place_filter_create(&places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(places_fil);

		ret = maps_place_filter_set_keyword(places_fil, "restaurant");
		assert_eq(ret, MAPS_ERROR_NONE);
		ret = maps_place_filter_set_place_name(places_fil, "Berlin");
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_create(52.5167, 13.383, &coords);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(coords);

		ret = maps_area_create_circle(coords, distance, &boundary);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(boundary);

		ret = maps_service_search_place_list(__pMaps, boundary, places_fil, __preference, __utc_maps_service_search_place_list_cb, NULL, &request_id);
		if (is_internet_supported && is_search_place_list_supported) {
			assert_eq(ret, MAPS_ERROR_NONE);

			wait_for_service();
			assert(service_available);
			service_available = false;

			ret = maps_area_destroy(boundary);
			assert_eq(ret, MAPS_ERROR_NONE);

			ret = maps_coordinates_destroy(coords);
			assert_eq(ret, MAPS_ERROR_NONE);

			ret = maps_place_filter_destroy(places_fil);
			assert_eq(ret, MAPS_ERROR_NONE);
		} else
			assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	} else {
		ret = maps_service_search_place_list(__pMaps, boundary, places_fil, __preference, __utc_maps_service_search_place_list_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_maps_service_search_place_list_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_search_place_list()
 */
int utc_maps_service_search_place_list_n(void)
{
	int request_id = INVALID_REQUEST_ID;
	maps_place_filter_h places_fil = NULL;
	maps_coordinates_h coords = NULL;
	maps_area_h boundary = NULL;
	bool is_search_place_list_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE_LIST, &is_search_place_list_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_place_filter_create(&places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(places_fil);

		ret = maps_coordinates_create(52.5167, 13.383, &coords);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(coords);

		ret = maps_area_create_circle(coords, 5234, &boundary);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(boundary);

		ret = maps_service_search_place_list(NULL, boundary, places_fil, __preference, __utc_maps_service_search_place_list_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_list(__pMaps, NULL, places_fil, __preference, __utc_maps_service_search_place_list_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_list_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_list(__pMaps, boundary, NULL, __preference, __utc_maps_service_search_place_list_cb, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_list_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_list(__pMaps, boundary, places_fil, __preference, NULL, NULL, &request_id);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_list_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_list(__pMaps, boundary, places_fil, __preference, __utc_maps_service_search_place_list_cb, NULL, NULL);
		ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_search_place_list_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_area_destroy(boundary);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_destroy(coords);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_place_filter_destroy(places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_service_search_place_list(NULL, boundary, places_fil, __preference, __utc_maps_service_search_place_list_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_list(__pMaps, NULL, places_fil, __preference, __utc_maps_service_search_place_list_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_list(__pMaps, boundary, NULL, __preference, __utc_maps_service_search_place_list_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_list(__pMaps, boundary, places_fil, __preference, NULL, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_service_search_place_list(__pMaps, boundary, places_fil, __preference, __utc_maps_service_search_place_list_cb, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

static void __utc_maps_service_get_place_details_cb(maps_error_e result, int request_id, maps_place_h place, void *user_data)
{
	maps_place_destroy(place);

	if (result == MAPS_ERROR_NONE)
		service_available = true;

	quit_for_service();
}

/**
 * @testcase		utc_maps_service_get_place_details_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_get_place_details()
 */
int utc_maps_service_get_place_details_p(void)
{
	if (__place_uri != NULL) {
		free(__place_uri);
		__place_uri = NULL;
	}

	maps_place_filter_h places_fil = NULL;
	maps_coordinates_h coords = NULL;
	maps_area_h boundary = NULL;
	int distance = 504295;
	int request_id = INVALID_REQUEST_ID;
	bool is_search_place_list_supported = false;
	bool is_search_get_place_details_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_PLACE_LIST, &is_search_place_list_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_GET_PLACE_DETAILS, &is_search_get_place_details_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported) {
		ret = maps_place_filter_create(&places_fil);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(places_fil);

		ret = maps_place_filter_set_keyword(places_fil, "restaurant");
		assert_eq(ret, MAPS_ERROR_NONE);
		ret = maps_place_filter_set_place_name(places_fil, "Berlin");
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_create(52.5167, 13.383, &coords);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(coords);

		ret = maps_area_create_circle(coords, distance, &boundary);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(boundary);

		ret = maps_service_search_place_list(__pMaps, boundary, places_fil, __preference, __utc_maps_service_search_place_list_cb, NULL, &request_id);
		if (is_internet_supported && is_search_place_list_supported) {
			assert_eq(ret, MAPS_ERROR_NONE);

			if (!service_available)
				wait_for_service();
			assert(service_available);
			service_available = false;

			ret = maps_service_get_place_details(__pMaps, __place_uri, __utc_maps_service_get_place_details_cb, NULL, &request_id);
			if (is_internet_supported && is_search_get_place_details_supported) {
				assert_eq(ret, MAPS_ERROR_NONE);

				if (!service_available)
					wait_for_service();
				assert(service_available);
				service_available = false;

				ret = maps_area_destroy(boundary);
				assert_eq(ret, MAPS_ERROR_NONE);

				ret = maps_coordinates_destroy(coords);
				assert_eq(ret, MAPS_ERROR_NONE);

				ret = maps_place_filter_destroy(places_fil);
				assert_eq(ret, MAPS_ERROR_NONE);
			} else
				assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
		} else
			assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	} else {
		ret = maps_service_get_place_details(__pMaps, __place_uri, __utc_maps_service_get_place_details_cb, NULL, &request_id);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_service_get_place_details_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_get_place_details()
 */
int utc_maps_service_get_place_details_n(void)
{
	int request_id = INVALID_REQUEST_ID;
	bool is_search_get_place_details_supported = false;

	ret = maps_service_provider_is_service_supported(__pMaps, MAPS_SERVICE_SEARCH_GET_PLACE_DETAILS, &is_search_get_place_details_supported);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_get_place_details(NULL, __place_uri, __utc_maps_service_get_place_details_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_get_place_details(__pMaps, NULL, __utc_maps_service_get_place_details_cb, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_search_get_place_details_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_get_place_details(__pMaps, __place_uri, NULL, NULL, &request_id);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_search_get_place_details_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_get_place_details(__pMaps, __place_uri, __utc_maps_service_get_place_details_cb, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_internet_supported && is_maps_supported && is_search_get_place_details_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static void __utc_maps_service_request_user_consent_cb(bool consented, const char *maps_provider, void *user_data)
{}

/**
 * @testcase		utc_maps_service_request_user_consent_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_service_request_user_consent()
 */
int utc_maps_service_request_user_consent_p(void)
{
	ret = maps_service_request_user_consent(__utc_get_maps_provider_name_here(), __utc_maps_service_request_user_consent_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_service_request_user_consent_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_service_request_user_consent()
 */
int utc_maps_service_request_user_consent_n(void)
{
	ret = maps_service_request_user_consent(NULL, __utc_maps_service_request_user_consent_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_request_user_consent(__utc_get_maps_provider_name_here(), NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_service_request_user_consent("XXXXXX", __utc_maps_service_request_user_consent_cb, NULL);
	assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
