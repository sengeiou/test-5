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
#include <unistd.h>
#include <maps_route.h>
#include <maps_error.h>
#include <maps_service.h>
#include <maps_coordinates.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_route_h __pRoute = NULL;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_route_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_route_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();
}

/**
 * @function		utc_maps_route_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_route_cleanup(void)
{
}

/**
 * @testcase		utc_maps_route_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_destroy()
 */
int utc_maps_route_destroy_n(void)
{
	ret = maps_route_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_clone()
 */
int utc_maps_route_clone_n(void)
{
	maps_route_h clone = NULL;

	ret = maps_route_clone(__pRoute, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_clone(NULL, &clone);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_clone(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);
	return 0;
}

/**
 * @testcase		utc_maps_route_get_route_id_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_get_route_id()
 */
int utc_maps_route_get_route_id_n(void)
{
	char *test = NULL;

	ret = maps_route_get_route_id(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_route_id(__pRoute, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_route_id(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_get_origin_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_get_origin()
 */
int utc_maps_route_get_origin_n(void)
{
	maps_coordinates_h origin = NULL;

	ret = maps_route_get_origin(NULL, &origin);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_origin(__pRoute, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_origin(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_get_destination_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_get_destination()
 */
int utc_maps_route_get_destination_n(void)
{
	maps_coordinates_h destination = NULL;

	ret = maps_route_get_destination(NULL, &destination);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_destination(__pRoute, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_destination(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_get_bounding_box_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_get_bounding_box()
 */
int utc_maps_route_get_bounding_box_n(void)
{
	maps_area_h area = NULL;

	ret = maps_route_get_bounding_box(__pRoute, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_bounding_box(NULL, &area);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_bounding_box(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_get_total_distance_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_get_total_distance()
 */
int utc_maps_route_get_total_distance_n(void)
{
	double test = .0;

	ret = maps_route_get_total_distance(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_total_distance(__pRoute, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_total_distance(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_get_transport_mode_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_get_transport_mode()
 */
int utc_maps_route_get_transport_mode_n(void)
{
	maps_route_transport_mode_e test = MAPS_ROUTE_TRANSPORT_MODE_TRUCK;

	ret = maps_route_get_transport_mode(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_transport_mode(__pRoute, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_transport_mode(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_get_total_duration_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_get_total_duration()
 */
int utc_maps_route_get_total_duration_n(void)
{
	long test = 0l;

	ret = maps_route_get_total_duration(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_total_duration(__pRoute, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_total_duration(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_get_distance_unit_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_get_distance_unit()
 */
int utc_maps_route_get_distance_unit_n(void)
{
	maps_distance_unit_e test = MAPS_DISTANCE_UNIT_M;

	ret = maps_route_get_distance_unit(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_get_distance_unit(__pRoute, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __route_foreach_property_cb(int index, int total, char *key, void *value, void *user_data)
{
	free(key);
	free(value);
	return true;
}

/**
 * @testcase		utc_maps_route_foreach_property_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_foreach_property()
 */
int utc_maps_route_foreach_property_n(void)
{
	void *user_data = NULL;

	ret = maps_route_foreach_property(__pRoute, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_foreach_property(NULL, __route_foreach_property_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_foreach_property(NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_route_path_cb(int index, int total, maps_coordinates_h coordinates, void *user_data)
{
	ret = maps_coordinates_destroy(coordinates);
	assert_eq(ret, MAPS_ERROR_NONE);
	return true;
}

/**
 * @testcase		utc_maps_route_foreach_path_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_foreach_path()
 */
int utc_maps_route_foreach_path_n(void)
{
	void *user_data = NULL;

	ret = maps_route_foreach_path(__pRoute, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_foreach_path(NULL, __utc_maps_route_path_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_foreach_path(NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_route_segment_cb(int index, int total, maps_route_segment_h segment, void *user_data)
{
	ret = maps_route_segment_destroy(segment);
	assert_eq(ret, MAPS_ERROR_NONE);
	return true;
}

/**
 * @testcase		utc_maps_route_foreach_segment_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_foreach_segment()
 */
int utc_maps_route_foreach_segment_n(void)
{
	void *user_data = NULL;

	ret = maps_route_foreach_segment(__pRoute, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_foreach_segment(NULL, __utc_maps_route_segment_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_foreach_segment(NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
