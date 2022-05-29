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

static int ret = 0;
static maps_view_event_data_h event = NULL;
static bool is_maps_supported = false;

/**
 * @function		utc_map_view_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_maps_view_event_data_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();
}

/**
 * @function		utc_map_view_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_maps_view_event_data_cleanup(void)
{
}

/*
 * @testcase        utc_maps_view_event_data_destroy_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_destroy()
 */
int utc_maps_view_event_data_destroy_n(void)
{
	ret = maps_view_event_data_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_clone_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_clone()
 */
int utc_maps_view_event_data_clone_n(void)
{
	maps_view_event_data_h cloned = NULL;

	ret = maps_view_event_data_clone(NULL, &cloned);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_clone(event, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_type_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_type()
 */
int utc_maps_view_event_data_get_type_n(void)
{
	maps_view_event_type_e event_type;

	ret = maps_view_event_data_get_type(NULL, &event_type);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_type(event, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_gesture_type_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_gesture_type()
 */
int utc_maps_view_event_data_get_gesture_type_n(void)
{
	maps_view_gesture_e gesture_type;

	ret = maps_view_event_data_get_gesture_type(NULL, &gesture_type);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_gesture_type(event, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_action_type_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_action_type()
 */
int utc_maps_view_event_data_get_action_type_n(void)
{
	maps_view_action_e action_type;

	ret = maps_view_event_data_get_action_type(NULL, &action_type);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_action_type(event, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_center_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_center()
 */
int utc_maps_view_event_data_get_center_n(void)
{
	maps_coordinates_h center = NULL;

	ret = maps_view_event_data_get_center(NULL, &center);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_center(event, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_delta_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_delta()
 */
int utc_maps_view_event_data_get_delta_n(void)
{
	int delta_x = 0, delta_y = 0;

	ret = maps_view_event_data_get_delta(NULL, &delta_x, &delta_y);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_delta(event, NULL, &delta_y);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_delta(event, &delta_x, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_position_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_position()
 */
int utc_maps_view_event_data_get_position_n(void)
{
	int x = 0, y = 0;

	ret = maps_view_event_data_get_position(NULL, &x, &y);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_position(event, NULL, &y);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_position(event, &x, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_fingers_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_fingers()
 */
int utc_maps_view_event_data_get_fingers_n(void)
{
	int fingers = 0;

	ret = maps_view_event_data_get_fingers(NULL, &fingers);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_fingers(event, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_zoom_factor_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_zoom_factor()
 */
int utc_maps_view_event_data_get_zoom_factor_n(void)
{
	double zoom_factor = 0.0;

	ret = maps_view_event_data_get_zoom_factor(NULL, &zoom_factor);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_zoom_factor(event, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_rotation_angle_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_rotation_angle()
 */
int utc_maps_view_event_data_get_rotation_angle_n(void)
{
	double rotation_angle = 0.0;

	ret = maps_view_event_data_get_rotation_angle(NULL, &rotation_angle);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_rotation_angle(event, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_object_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_object()
 */
int utc_maps_view_event_data_get_object_n(void)
{
	maps_view_object_h object = NULL;

	ret = maps_view_event_data_get_object(NULL, &object);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_object(event, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/*
 * @testcase        utc_maps_view_event_data_get_coordinates_n
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Negative test case of maps_view_event_data_get_coordinates()
 */
int utc_maps_view_event_data_get_coordinates_n(void)
{
	maps_coordinates_h coordinates = NULL;

	ret = maps_view_event_data_get_coordinates(NULL, &coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_event_data_get_coordinates(event, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

