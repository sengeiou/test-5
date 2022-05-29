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
#include <maps_coordinates.h>
#include <maps_service.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_coordinates_h __pCoordinates = NULL;
static maps_coordinates_list_h __pCoordinatesList = NULL;
static bool __isCalled = false;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_coordinates_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_coordinates_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();

	ret = 0;
	__pCoordinates = NULL;
	__isCalled = true;

	maps_coordinates_create(15.665354, 74.311523, &__pCoordinates);
	maps_coordinates_list_create(&__pCoordinatesList);
}

/**
 * @function		utc_maps_coordinates_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_coordinates_cleanup(void)
{
	maps_coordinates_destroy(__pCoordinates);
	maps_coordinates_list_destroy(__pCoordinatesList);
}

/**
 * @testcase		utc_maps_coordinates_create_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_coordinates_create()
 */
int utc_maps_coordinates_create_p(void)
{
	maps_coordinates_h coordinates = NULL;

	ret = maps_coordinates_create(55.665354, 114.311523, &coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(coordinates);

	ret = maps_coordinates_destroy(coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_create_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_coordinates_create()
 */
int utc_maps_coordinates_create_n(void)
{
	ret = maps_coordinates_create(90.01, 74.311523, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_destroy_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_coordinates_destroy()
 */
int utc_maps_coordinates_destroy_p(void)
{
	/* tested in utc_maps_coordinates_create_p */
	return 0;
}

/**
 * @testcase		utc_maps_coordinates_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_coordinates_destroy()
 */
int utc_maps_coordinates_destroy_n(void)
{
	ret = maps_coordinates_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_clone_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_coordinates_clone()
 */
int utc_maps_coordinates_clone_p(void)
{
	maps_coordinates_h clone = NULL;

	ret = maps_coordinates_clone(__pCoordinates, &clone);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(clone);

	ret = maps_coordinates_destroy(clone);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_coordinates_clone()
 */
int utc_maps_coordinates_clone_n(void)
{
	maps_coordinates_h clone = NULL;

	ret = maps_coordinates_clone(NULL, &clone);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_clone(__pCoordinates, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_get_latitude_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_coordinates_get_latitude()
 */
int utc_maps_coordinates_get_latitude_p(void)
{
	double lat = .0;

	ret = maps_coordinates_set_latitude(__pCoordinates, 16.5555);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_get_latitude(__pCoordinates, &lat);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	if (is_maps_supported)
		assert_eq(lat, 16.5555);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_get_latitude_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_coordinates_get_latitude()
 */
int utc_maps_coordinates_get_latitude_n(void)
{
	double lat = .0;

	ret = maps_coordinates_get_latitude(NULL, &lat);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_get_latitude(__pCoordinates, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_get_longitude_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_coordinates_get_longitude()
 */
int utc_maps_coordinates_get_longitude_p(void)
{
	double lon = .0;

	ret = maps_coordinates_set_longitude(__pCoordinates, 16.5555);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_get_longitude(__pCoordinates, &lon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert_eq(lon, 16.5555);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_get_longitude_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_coordinates_get_longitude()
 */
int utc_maps_coordinates_get_longitude_n(void)
{
	double lon = .0;
	ret = maps_coordinates_get_longitude(NULL, &lon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_get_longitude(__pCoordinates, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_set_latitude_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_coordinates_set_latitude()
 */
int utc_maps_coordinates_set_latitude_p(void)
{
	/* tested in utc_maps_coordinates_get_latitude_p */
	return 0;
}

/**
 * @testcase		utc_maps_coordinates_set_latitude_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_coordinates_set_latitude()
 */
int utc_maps_coordinates_set_latitude_n(void)
{
	ret = maps_coordinates_set_latitude(NULL, 16.5555);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_set_latitude(__pCoordinates, 90.1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_set_longitude_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_coordinates_set_longitude()
 */
int utc_maps_coordinates_set_longitude_p(void)
{
	/* tested in utc_maps_coordinates_get_longitude_p */
	return 0;
}

/**
 * @testcase		utc_maps_coordinates_set_longitude_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_coordinates_set_longitude()
 */
int utc_maps_coordinates_set_longitude_n(void)
{
	ret = maps_coordinates_set_longitude(NULL, 16.5555);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_set_longitude(__pCoordinates, 180.1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}


/**
 * @testcase		utc_maps_coordinates_get_latitude_longitude_p
 * @since_tizen		3.0
 * @description		Positive test case of maps_coordinates_get_latitude_longitude()
 */
int utc_maps_coordinates_get_latitude_longitude_p(void)
{
	double lat = .0;
	double lon = .0;

	ret = maps_coordinates_set_latitude_longitude(__pCoordinates, 16.5555, 16.5555);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_get_latitude_longitude(__pCoordinates, &lat, &lon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported) {
		assert_eq(lat, 16.5555);
		assert_eq(lon, 16.5555);
	}
	return 0;
}

/**
 * @testcase		utc_maps_coordinates_get_latitude_longitude_n
 * @since_tizen		3.0
 * @description		Negative test case of maps_coordinates_get_latitude_longitude()
 */
int utc_maps_coordinates_get_latitude_longitude_n(void)
{
	double lat = .0;
	double lon = .0;

	ret = maps_coordinates_get_latitude_longitude(NULL, &lat, &lon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_get_latitude_longitude(__pCoordinates, NULL, &lon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_get_latitude_longitude(__pCoordinates, &lat, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_set_latitude_longitude_p
 * @since_tizen		3.0
 * @description		Positive test case of maps_coordinates_set_latitude_longitude()
 */
int utc_maps_coordinates_set_latitude_longitude_p(void)
{
	/* tested in utc_maps_coordinates_get_latitude_longitude_p */
	return 0;
}

/**
 * @testcase		utc_maps_coordinates_set_latitude_longitude_n
 * @since_tizen		3.0
 * @description		Negative test case of maps_coordinates_set_latitude_longitude()
 */
int utc_maps_coordinates_set_latitude_longitude_n(void)
{
	ret = maps_coordinates_set_latitude_longitude(NULL, 16.5555, 16.5555);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_set_latitude_longitude(__pCoordinates, 90.1, 16.5555);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_set_latitude_longitude(__pCoordinates, 16.5555, 180.1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_create_p
 * @since_tizen		3.0
 * @description		Positive test case of maps_coordinates_list_create()
 */
int utc_maps_coordinates_list_create_p(void)
{
	maps_coordinates_list_h coordinates_list = NULL;

	ret = maps_coordinates_list_create(&coordinates_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert(coordinates_list);

	ret = maps_coordinates_list_destroy(coordinates_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_create_n
 * @since_tizen		3.0
 * @description		Negative test case of maps_coordinates_list_create()
 */
int utc_maps_coordinates_list_create_n(void)
{
	ret = maps_coordinates_list_create(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_destroy_p
 * @since_tizen		3.0
 * @description		Positive test case of maps_coordinates_list_destroy()
 */
int utc_maps_coordinates_list_destroy_p(void)
{
	/* tested in utc_maps_coordinates_list_create_p */
	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_destroy_n
 * @since_tizen		3.0
 * @description		Negative test case of maps_coordinates_list_destroy()
 */
int utc_maps_coordinates_list_destroy_n(void)
{
	ret = maps_coordinates_list_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_append_p
 * @since_tizen		3.0
 * @description		Positive test case of maps_coordinates_list_append()
 */
int utc_maps_coordinates_list_append_p(void)
{
	ret = maps_coordinates_list_append(__pCoordinatesList, __pCoordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_remove(__pCoordinatesList, __pCoordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_append_n
 * @since_tizen		3.0
 * @description		Negative test case of maps_coordinates_list_append()
 */
int utc_maps_coordinates_list_append_n(void)
{
	ret = maps_coordinates_list_append(NULL, __pCoordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(__pCoordinatesList, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_remove_p
 * @since_tizen		3.0
 * @description		Positive test case of maps_coordinates_list_remove()
 */
int utc_maps_coordinates_list_remove_p(void)
{
	/* tested in utc_maps_coordinates_list_append_p */
	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_remove_n
 * @since_tizen		3.0
 * @description		Positive test case of maps_coordinates_list_remove()
 */
int utc_maps_coordinates_list_remove_n(void)
{
	ret = maps_coordinates_list_remove(NULL, __pCoordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_remove(__pCoordinatesList, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_get_length_p
 * @since_tizen		3.0
 * @description		Positive test case of maps_coordinates_list_get_length()
 */
int utc_maps_coordinates_list_get_length_p(void)
{
	int len = 0;

	ret = maps_coordinates_list_get_length(__pCoordinatesList, &len);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_get_length_n
 * @since_tizen		3.0
 * @description		Negative test case of maps_coordinates_list_get_length()
 */
int utc_maps_coordinates_list_get_length_n(void)
{
	int len = 0;
	ret = maps_coordinates_list_get_length(NULL, &len);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_get_length(__pCoordinatesList, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

static bool __maps_coordinates_list_cb(int index, maps_coordinates_h coord, void *user_data)
{
	__isCalled = true;
	assert(coord);

	return true;
}

/**
 * @testcase		utc_maps_coordinates_list_foreach_p
 * @since_tizen		3.0
 * @description		Positive test case of maps_coordinates_list_foreach()
 */
int utc_maps_coordinates_list_foreach_p(void)
{
	ret = maps_coordinates_list_append(__pCoordinatesList, __pCoordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_foreach(__pCoordinatesList, __maps_coordinates_list_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	if (is_maps_supported)
		assert_eq(__isCalled, true);

	ret = maps_coordinates_list_remove(__pCoordinatesList, __pCoordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_coordinates_list_foreach_n
 * @since_tizen		3.0
 * @description		Negative test case of maps_coordinates_list_foreach()
 */
int utc_maps_coordinates_list_foreach_n(void)
{
	ret = maps_coordinates_list_foreach(NULL, __maps_coordinates_list_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_foreach(__pCoordinatesList, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
