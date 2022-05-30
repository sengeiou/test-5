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
#include <maps_error.h>
#include <maps_route_segment.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_route_segment_h __pSegment = NULL;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_route_segment_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_route_segment_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();
}

/**
 * @function		utc_maps_route_segment_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_route_segment_cleanup(void)
{
}

/**
 * @testcase		utc_maps_route_segment_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_segment_destroy()
 */
int utc_maps_route_segment_destroy_n(void)
{
	ret = maps_route_segment_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_segment_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_segment_clone()
 */
int utc_maps_route_segment_clone_n(void)
{
	maps_route_segment_h clone = NULL;

	ret = maps_route_segment_clone(__pSegment, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_clone(NULL, &clone);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_segment_get_origin_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_segment_get_origin()
 */
int utc_maps_route_segment_get_origin_n(void)
{
	maps_coordinates_h origin = NULL;

	ret = maps_route_segment_get_origin(NULL, &origin);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_get_origin(__pSegment, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_get_origin(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_segment_get_destination_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_segment_get_destination()
 */
int utc_maps_route_segment_get_destination_n(void)
{
	maps_coordinates_h destination = NULL;

	ret = maps_route_segment_get_destination(NULL, &destination);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_get_destination(__pSegment, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_get_destination(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_segment_get_bounding_box_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_segment_get_bounding_box()
 */
int utc_maps_route_segment_get_bounding_box_n(void)
{
	maps_area_h area = NULL;

	ret = maps_route_segment_get_bounding_box(__pSegment, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_get_bounding_box(NULL, &area);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_segment_get_distance_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_segment_get_distance()
 */
int utc_maps_route_segment_get_distance_n(void)
{
	double test = .0;

	ret = maps_route_segment_get_distance(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_get_distance(__pSegment, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_get_distance(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_segment_get_duration_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_segment_get_duration()
 */
int utc_maps_route_segment_get_duration_n(void)
{
	long test = 0;

	ret = maps_route_segment_get_duration(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_get_duration(__pSegment, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_get_duration(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/* Make all callbacks static */
/* Check index, total, data ptr */
static bool __utc_maps_route_segment_path_cb(int index, int total, maps_coordinates_h coordinates, void *user_data)
{
	ret = maps_coordinates_destroy(coordinates);
	assert_eq(ret, MAPS_ERROR_NONE);
	return true;
}

/**
 * @testcase		utc_maps_route_segment_foreach_path_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_segment_foreach_path()
 */
int utc_maps_route_segment_foreach_path_n(void)
{
	void *user_data = NULL;

	ret = maps_route_segment_foreach_path(__pSegment, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_foreach_path(NULL, __utc_maps_route_segment_path_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_foreach_path(NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __utc_maps_route_segment_maneuver_cb(int index, int total, maps_route_maneuver_h maneuver, void *user_data)
{
	ret = maps_route_maneuver_destroy(maneuver);
	assert_eq(ret, MAPS_ERROR_NONE);
	return true;
}

/**
 * @testcase		utc_maps_route_segment_foreach_maneuver_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_segment_foreach_maneuver()
 */
int utc_maps_route_segment_foreach_maneuver_n(void)
{
	void *user_data = NULL;

	ret = maps_route_segment_foreach_maneuver(__pSegment, NULL, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_foreach_maneuver(NULL, __utc_maps_route_segment_maneuver_cb, user_data);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_segment_foreach_maneuver(NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
