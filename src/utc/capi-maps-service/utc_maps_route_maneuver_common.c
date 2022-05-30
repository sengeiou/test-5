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
#include <maps_route_maneuver.h>
#include "utc_maps_utils.h"

static int ret = 0;
static maps_route_maneuver_h __pManeuver = NULL;
static bool is_maps_supported = false;

/**
 * @function		utc_maps_route_maneuver_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_route_maneuver_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();
}

/**
 * @function		utc_maps_route_maneuver_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_maps_route_maneuver_cleanup(void)
{
}

/**
 * @testcase		utc_maps_route_maneuver_destroy_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_maneuver_destroy()
 */
int utc_maps_route_maneuver_destroy_n(void)
{
	ret = maps_route_maneuver_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_maneuver_clone_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_maneuver_clone()
 */
int utc_maps_route_maneuver_clone_n(void)
{
	maps_route_maneuver_h clone = NULL;

	ret = maps_route_maneuver_clone(NULL, &clone);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_clone(__pManeuver, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_maneuver_get_direction_id_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_maneuver_get_direction_id()
 */
int utc_maps_route_maneuver_get_direction_id_n(void)
{
	maps_route_direction_e test = MAPS_ROUTE_DIRECTION_SOUTH;

	ret = maps_route_maneuver_get_direction_id(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_get_direction_id(__pManeuver, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_get_direction_id(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_maneuver_get_turn_type_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_maneuver_get_turn_type()
 */
int utc_maps_route_maneuver_get_turn_type_n(void)
{
	maps_route_turn_type_e test = MAPS_ROUTE_TURN_TYPE_NONE;

	ret = maps_route_maneuver_get_turn_type(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_get_turn_type(__pManeuver, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_get_turn_type(NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_maneuver_get_position_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_maneuver_get_position()
 */
int utc_maps_route_maneuver_get_position_n(void)
{
	maps_coordinates_h position = NULL;

	ret = maps_route_maneuver_get_position(__pManeuver, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_get_position(NULL, &position);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_maneuver_get_road_name_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_maneuver_get_road_name()
 */
int utc_maps_route_maneuver_get_road_name_n(void)
{
	char *test = NULL;

	ret = maps_route_maneuver_get_road_name(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_get_road_name(__pManeuver, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_maneuver_get_instruction_text_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_maneuver_get_instruction_text()
 */
int utc_maps_route_maneuver_get_instruction_text_n(void)
{
	char *test = NULL;

	ret = maps_route_maneuver_get_instruction_text(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_get_instruction_text(__pManeuver, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_maneuver_get_locale_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_maneuver_get_locale()
 */
int utc_maps_route_maneuver_get_locale_n(void)
{
	char *test = NULL;

	ret = maps_route_maneuver_get_locale(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_get_locale(__pManeuver, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_maneuver_get_time_to_next_instruction_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_maneuver_get_time_to_next_instruction()
 */
int utc_maps_route_maneuver_get_time_to_next_instruction_n(void)
{
	int test = 0;

	ret = maps_route_maneuver_get_time_to_next_instruction(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_get_time_to_next_instruction(__pManeuver, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_route_maneuver_get_distance_to_next_instruction_n
 * @since_tizen		@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_route_maneuver_get_distance_to_next_instruction()
 */
int utc_maps_route_maneuver_get_distance_to_next_instruction_n(void)
{
	double test = .0;

	ret = maps_route_maneuver_get_distance_to_next_instruction(NULL, &test);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_route_maneuver_get_distance_to_next_instruction(__pManeuver, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}
