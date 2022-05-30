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
#include <maps_area.h>
#include <maps_service.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_area_h __pArea = NULL;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_area_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_area_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();

	ret = 0;
	__pArea = NULL;
}

/**
 * @function		utc_maps_area_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_area_cleanup(void)
{
}

/**
 * @testcase		utc_maps_area_create_rectangle_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_area_create_rectangle()
 */
int utc_maps_area_create_rectangle_p(void)
{
	maps_coordinates_h top_left = NULL;
	maps_coordinates_h bottom_right = NULL;

	if (is_maps_supported) {
		ret = maps_coordinates_create(15.665354, 74.311523, &top_left);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(top_left);

		ret = maps_coordinates_create(10.617418, 79.145508, &bottom_right);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(bottom_right);

		ret = maps_area_create_rectangle(top_left, bottom_right, &__pArea);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(__pArea);

		ret = maps_coordinates_destroy(top_left);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_destroy(bottom_right);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_area_destroy(__pArea);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_area_create_rectangle(top_left, bottom_right, &__pArea);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_area_destroy(__pArea);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_area_create_rectangle_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_area_create_rectangle()
 */
int utc_maps_area_create_rectangle_n(void)
{
	maps_coordinates_h top_left = NULL;
	maps_coordinates_h bottom_right = NULL;

	if (is_maps_supported) {
		ret = maps_coordinates_create(15.665354, 74.311523, &top_left);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(top_left);

		ret = maps_coordinates_create(10.617418, 79.145508, &bottom_right);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(bottom_right);

		ret = maps_area_create_rectangle(top_left, bottom_right, NULL);
		assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);

		ret = maps_area_create_rectangle(NULL, bottom_right, &__pArea);
		assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);

		ret = maps_area_create_rectangle(top_left, NULL, &__pArea);
		assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);

		ret = maps_area_create_rectangle(NULL, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);

		ret = maps_coordinates_destroy(top_left);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_coordinates_destroy(bottom_right);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_area_create_rectangle(top_left, bottom_right, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_area_create_rectangle(NULL, bottom_right, &__pArea);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_area_create_rectangle(top_left, NULL, &__pArea);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_area_create_rectangle(NULL, NULL, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_area_create_circle_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_area_create_circle()
 */
int utc_maps_area_create_circle_p(void)
{
	maps_coordinates_h center = NULL;

	if (is_maps_supported) {
		ret = maps_coordinates_create(15.665354, 74.311523, &center);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(center);

		ret = maps_area_create_circle(center, 100, &__pArea);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(__pArea);

		ret = maps_coordinates_destroy(center);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_area_destroy(__pArea);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_area_create_circle(center, 100, &__pArea);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_area_destroy(__pArea);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_area_create_circle_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_area_create_circle()
 */
int utc_maps_area_create_circle_n(void)
{
	maps_coordinates_h center = NULL;

	if (is_maps_supported) {
		ret = maps_coordinates_create(15.665354, 74.311523, &center);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(center);

		ret = maps_area_create_circle(center, 100, NULL);
		assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);

		ret = maps_area_create_circle(NULL, 100, &__pArea);
		assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);

		ret = maps_area_create_circle(center, -1, &__pArea);
		assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);

		ret = maps_coordinates_destroy(center);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_area_create_circle(center, 100, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_area_create_circle(NULL, 100, &__pArea);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_area_create_circle(center, -1, &__pArea);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_area_destroy_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_area_destroy()
 */
int utc_maps_area_destroy_p(void)
{
	/* tested in utc_maps_area_create_rectangle_p */
	return 0;
}


/**
 * @testcase		utc_maps_area_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_area_destroy()
 */
int utc_maps_area_destroy_n(void)
{
	ret = maps_area_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_area_clone_p
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_area_clone()
 */
int utc_maps_area_clone_p(void)
{
	maps_coordinates_h center = NULL;
	maps_area_h clone = NULL;

	if (is_maps_supported) {
		ret = maps_coordinates_create(15.665354, 74.311523, &center);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(center);

		ret = maps_area_create_circle(center, 100, &__pArea);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(__pArea);

		ret = maps_area_clone(__pArea, &clone);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(clone);

		ret = maps_coordinates_destroy(center);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_area_destroy(clone);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_area_destroy(__pArea);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_area_clone(__pArea, &clone);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}

/**
 * @testcase		utc_maps_area_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_area_clone()
 */
int utc_maps_area_clone_n(void)
{
	maps_coordinates_h center = NULL;
	maps_area_h clone = NULL;

	if (is_maps_supported) {
		ret = maps_coordinates_create(15.665354, 74.311523, &center);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(center);

		ret = maps_area_create_circle(center, 100, &__pArea);
		assert_eq(ret, MAPS_ERROR_NONE);
		assert(__pArea);

		ret = maps_area_clone(__pArea, NULL);
		assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);

		ret = maps_area_clone(NULL, &clone);
		assert_eq(ret, MAPS_ERROR_INVALID_PARAMETER);

		ret = maps_coordinates_destroy(center);
		assert_eq(ret, MAPS_ERROR_NONE);

		ret = maps_area_destroy(__pArea);
		assert_eq(ret, MAPS_ERROR_NONE);
	} else {
		ret = maps_area_clone(__pArea, NULL);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);

		ret = maps_area_clone(NULL, &clone);
		assert_eq(ret, MAPS_ERROR_NOT_SUPPORTED);
	}
	return 0;
}
