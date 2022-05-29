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

#include <app.h>
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

#define IMAGE_FILENAME "location_01_ic.png"
#define NEW_IMAGE_FILENAME "location_02_ic.png"

static Evas_Object *win = NULL;
static int ret = 0;
static char image_path[4096] = {0, };
static bool is_maps_supported = false;
static maps_view_object_h overlay = NULL;

static bool dummy_maps_coordinates_cb(int index, maps_coordinates_h coordinates, void *user_data)
{
	return true;
}

/**
 * @function		utc_map_view_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_maps_view_object_startup(void)
{
	is_maps_supported = _is_maps_feature_supported();

	elm_init(0, NULL);
	elm_config_accel_preference_set("opengl");

	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	elm_win_autodel_set(win, TRUE);

	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(image_path, 4096, "%s%s", res_path, IMAGE_FILENAME);
		free(res_path);
	}
}

/**
 * @function		utc_map_view_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_maps_view_object_cleanup(void)
{
	elm_shutdown();
	win = NULL;
}

/**
 * @testcase		utc_maps_view_object_create_marker_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_create_marker()
 */
int utc_maps_view_object_create_marker_p(void)
{
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord1 = NULL, coord2 = NULL, coord3 = NULL;
	maps_view_object_type_e type = MAPS_VIEW_OBJECT_POLYLINE;

	bool visible = false;
	char *file_path = NULL;
	char new_image_path[4096] = {0, };
	int width = 0, height = 0;
	maps_view_marker_type_e marker_type;
	int z_order = 0;

	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(new_image_path, 4096, "%s%s", res_path, NEW_IMAGE_FILENAME);
		free(res_path);
	}

	ret = maps_coordinates_create(0.0, 0.0, &coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 10.0, &coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord1, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_get_type(marker, &type);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_set_visible(marker, false);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_get_visible(marker, &visible);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_set_coordinates(marker, coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_get_coordinates(marker, &coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_resize(marker, 10, 10);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_set_image_file(marker, new_image_path);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_get_image_file(marker, &file_path);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	free(file_path);
	file_path = NULL;

	ret = maps_view_object_marker_get_size(marker, &width, &height);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_get_type(marker, &marker_type);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_set_z_order(marker, 0);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_get_z_order(marker, &z_order);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_create_marker_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_create_marker()
 */
int utc_maps_view_object_create_marker_n(void)
{
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(NULL, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, NULL, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN - 1, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_destroy_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_destroy()
 */
int utc_maps_view_object_destroy_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_destroy_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_destroy()
 */
int utc_maps_view_object_destroy_n(void)
{
	ret = maps_view_object_destroy(NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_get_type_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_get_type()
 */
int utc_maps_view_object_get_type_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_get_type_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_get_type()
 */
int utc_maps_view_object_get_type_n(void)
{
	maps_view_object_type_e type = MAPS_VIEW_OBJECT_POLYLINE;
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_get_type(NULL, &type);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_get_type(marker, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_set_visible_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_set_visible()
 */
int utc_maps_view_object_set_visible_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_set_visible_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_set_visible()
 */
int utc_maps_view_object_set_visible_n(void)
{
	ret = maps_view_object_set_visible(NULL, false);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_get_visible_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_get_visible()
 */
int utc_maps_view_object_get_visible_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_get_visible_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_get_visible()
 */
int utc_maps_view_object_get_visible_n(void)
{
	bool visible = false;
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_get_visible(NULL, &visible);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_get_visible(marker, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_marker_set_coordinates_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_marker_set_coordinates()
 */
int utc_maps_view_object_marker_set_coordinates_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_marker_set_coordinates_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_marker_set_coordinates()
 */
int utc_maps_view_object_marker_set_coordinates_n(void)
{
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_marker_set_coordinates(NULL, coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_set_coordinates(marker, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_marker_resize_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_marker_resize()
 */
int utc_maps_view_object_marker_resize_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_marker_resize_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_marker_resize()
 */
int utc_maps_view_object_marker_resize_n(void)
{
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_marker_resize(NULL, 10, 10);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_resize(marker, -1, 10);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_resize(marker, 10, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_marker_set_image_file_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_marker_set_image_file()
 */
int utc_maps_view_object_marker_set_image_file_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_marker_set_image_file_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_marker_set_image_file()
 */
int utc_maps_view_object_marker_set_image_file_n(void)
{
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	char new_image_path[4096] = {0, };
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(image_path, 4096, "%s%s", res_path, NEW_IMAGE_FILENAME);
		free(res_path);
	}

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_marker_set_image_file(NULL, new_image_path);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_set_image_file(marker, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_marker_get_image_file_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_marker_get_image_file()
 */
int utc_maps_view_object_marker_get_image_file_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_marker_get_image_file_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_marker_get_image_file()
 */
int utc_maps_view_object_marker_get_image_file_n(void)
{
	char *file_path = NULL;
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_marker_get_image_file(NULL, &file_path);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	free(file_path);
	file_path = NULL;

	ret = maps_view_object_marker_get_image_file(marker, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_marker_get_coordinates_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_marker_get_coordinates()
 */
int utc_maps_view_object_marker_get_coordinates_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_marker_get_coordinates_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_marker_get_coordinates()
 */
int utc_maps_view_object_marker_get_coordinates_n(void)
{
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_marker_get_coordinates(NULL, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_get_coordinates(marker, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_marker_get_size_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_marker_get_size()
 */
int utc_maps_view_object_marker_get_size_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_marker_get_size_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_marker_get_size()
 */
int utc_maps_view_object_marker_get_size_n(void)
{
	int width = 0, height = 0;
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_marker_get_size(NULL, &width, &height);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_get_size(marker, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_marker_get_type_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_marker_get_type()
 */
int utc_maps_view_object_marker_get_type_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_marker_get_type_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_marker_get_type()
 */
int utc_maps_view_object_marker_get_type_n(void)
{
	maps_view_marker_type_e type;
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_marker_get_type(NULL, &type);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_get_type(marker, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_marker_set_z_order_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_marker_set_z_order()
 */
int utc_maps_view_object_marker_set_z_order_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_marker_set_z_order_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_marker_set_z_order()
 */
int utc_maps_view_object_marker_set_z_order_n(void)
{
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_marker_set_z_order(NULL, 0);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_set_z_order(marker, -101);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase        utc_maps_view_object_marker_get_z_order_p
 * @since_tizen     @if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description     Positive test case of maps_view_object_marker_get_z_order()
 */
int utc_maps_view_object_marker_get_z_order_p(void)
{
	/* tested in utc_maps_view_object_create_marker_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_marker_get_z_order_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_marker_get_z_order()
 */
int utc_maps_view_object_marker_get_z_order_n(void)
{
	int z_order = 0;
	maps_view_object_h marker = NULL;
	maps_coordinates_h coord = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_marker(coord, image_path, MAPS_VIEW_MARKER_PIN, &marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_marker_get_z_order(NULL, &z_order);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_marker_get_z_order(marker, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(marker);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_create_polyline_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_create_polyline()
 */
int utc_maps_view_object_create_polyline_p(void)
{
	maps_coordinates_h coord1 = NULL, coord2 = NULL, coord3 = NULL, coord4 = NULL;
	maps_coordinates_list_h coord_list1 = NULL, coord_list2 = NULL;
	maps_view_object_h polyline = NULL;
	unsigned char r, g, b, a;
	int width = 0;

	ret = maps_coordinates_create(0.0, 0.0, &coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 10.0, &coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list1, coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list1, coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(5.0, 5.0, &coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(15.0, 15.0, &coord4);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list2, coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list2, coord4);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polyline(coord_list1, '1', '1', '1', '1', 1, &polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_set_polyline(polyline, coord_list2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_foreach_point(polyline, dummy_maps_coordinates_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_set_color(polyline, '2', '2', '2', '2');
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_get_color(polyline, &r, &g, &b, &a);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_set_width(polyline, 2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_get_width(polyline, &width);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_destroy(polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_create_polyline_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_create_polyline()
 */
int utc_maps_view_object_create_polyline_n(void)
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


	ret = maps_view_object_create_polyline(NULL, '1', '1', '1', '1', 1, &polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polyline(coord_list, '1', '1', '1', '1', 0, &polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polyline(coord_list, '1', '1', '1', '1', 1, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_coordinates_list_destroy(coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_set_polyline_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_polyline_set_polyline()
 */
int utc_maps_view_object_polyline_set_polyline_p(void)
{
	/* tested in utc_maps_view_object_create_polyline_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_set_polyline_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_polyline_set_polyline()
 */
int utc_maps_view_object_polyline_set_polyline_n(void)
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


	ret = maps_view_object_polyline_set_polyline(NULL, coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_set_polyline(polyline, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_coordinates_list_destroy(coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_foreach_point_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_polyline_foreach_point()
 */
int utc_maps_view_object_polyline_foreach_point_p(void)
{
	/* tested in utc_maps_view_object_create_polyline_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_foreach_point_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_polyline_foreach_point()
 */
int utc_maps_view_object_polyline_foreach_point_n(void)
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


	ret = maps_view_object_polyline_foreach_point(NULL, dummy_maps_coordinates_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_foreach_point(polyline, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_set_color_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_polyline_set_color()
 */
int utc_maps_view_object_polyline_set_color_p(void)
{
	/* tested in utc_maps_view_object_create_polyline_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_set_color_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_polyline_set_color()
 */
int utc_maps_view_object_polyline_set_color_n(void)
{
	ret = maps_view_object_polyline_set_color(NULL, '2', '2', '2', '2');
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_get_color_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_polyline_get_color()
 */
int utc_maps_view_object_polyline_get_color_p(void)
{
	/* tested in utc_maps_view_object_create_polyline_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_get_color_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_polyline_get_color()
 */
int utc_maps_view_object_polyline_get_color_n(void)
{
	maps_coordinates_h coord1 = NULL, coord2 = NULL;
	maps_coordinates_list_h coord_list = NULL;
	maps_view_object_h polyline = NULL;
	unsigned char r, g, b, a;

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


	ret = maps_view_object_polyline_get_color(NULL, &r, &g, &b, &a);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_get_color(polyline, NULL, NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_set_width_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_polyline_set_width()
 */
int utc_maps_view_object_polyline_set_width_p(void)
{
	/* tested in utc_maps_view_object_create_polyline_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_set_width_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_polyline_set_width()
 */
int utc_maps_view_object_polyline_set_width_n(void)
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


	ret = maps_view_object_polyline_set_width(NULL, 2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_set_width(polyline, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_get_width_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_polyline_get_width()
 */
int utc_maps_view_object_polyline_get_width_p(void)
{
	/* tested in utc_maps_view_object_create_polyline_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_polyline_get_width_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_polyline_get_width()
 */
int utc_maps_view_object_polyline_get_width_n(void)
{
	maps_coordinates_h coord1 = NULL, coord2 = NULL;
	maps_coordinates_list_h coord_list = NULL;
	maps_view_object_h polyline = NULL;
	int width = 0;

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


	ret = maps_view_object_polyline_get_width(NULL, &width);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polyline_get_width(polyline, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(polyline);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_create_polygon_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_create_polygon()
 */
int utc_maps_view_object_create_polygon_p(void)
{
	maps_coordinates_h coord1 = NULL, coord2 = NULL, coord3 = NULL, coord4 = NULL, coord5 = NULL, coord6 = NULL;
	maps_coordinates_list_h coord_list1 = NULL, coord_list2 = NULL;
	maps_view_object_h polygon = NULL;
	unsigned char r, g, b, a;

	ret = maps_coordinates_create(0.0, 0.0, &coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 10.0, &coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 0.0, &coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list1, coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list1, coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list1, coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(0.0, 1.0, &coord4);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 11.0, &coord5);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 1.0, &coord6);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list2, coord4);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list2, coord5);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list2, coord6);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polygon(coord_list1, '1', '1', '1', '1', &polygon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polygon_set_polygon(polygon, coord_list2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polygon_foreach_point(polygon, dummy_maps_coordinates_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polygon_set_fill_color(polygon, '2', '2', '2', '2');
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polygon_get_fill_color(polygon, &r, &g, &b, &a);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_destroy(polygon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_create_polygon_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_create_polygon()
 */
int utc_maps_view_object_create_polygon_n(void)
{
	maps_coordinates_h coord1 = NULL, coord2 = NULL, coord3 = NULL;
	maps_coordinates_list_h coord_list = NULL;
	maps_view_object_h polygon = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 10.0, &coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 0.0, &coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_create_polygon(NULL, '1', '1', '1', '1', &polygon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polygon(coord_list, '1', '1', '1', '1', NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_coordinates_list_destroy(coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_polygon_set_polygon_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_polygon_set_polygon()
 */
int utc_maps_view_object_polygon_set_polygon_p(void)
{
	/* tested in utc_maps_view_object_create_polygon_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_polygon_set_polygon_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_polygon_set_polygon()
 */
int utc_maps_view_object_polygon_set_polygon_n(void)
{
	maps_coordinates_h coord1 = NULL, coord2 = NULL, coord3 = NULL;
	maps_coordinates_list_h coord_list = NULL;
	maps_view_object_h polygon = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 10.0, &coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 0.0, &coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polygon(coord_list, '1', '1', '1', '1', &polygon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_polygon_set_polygon(NULL, coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polygon_set_polygon(polygon, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(polygon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_polygon_foreach_point_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_polygon_foreach_point()
 */
int utc_maps_view_object_polygon_foreach_point_p(void)
{
	/* tested in utc_maps_view_object_create_polygon_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_polygon_foreach_point_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_polygon_foreach_point()
 */
int utc_maps_view_object_polygon_foreach_point_n(void)
{
	maps_coordinates_h coord1 = NULL, coord2 = NULL, coord3 = NULL;
	maps_coordinates_list_h coord_list = NULL;
	maps_view_object_h polygon = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 10.0, &coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 0.0, &coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polygon(coord_list, '1', '1', '1', '1', &polygon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_polygon_foreach_point(NULL, dummy_maps_coordinates_cb, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polygon_foreach_point(polygon, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_destroy(polygon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_polygon_set_fill_color_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_polygon_set_fill_color()
 */
int utc_maps_view_object_polygon_set_fill_color_p(void)
{
	/* tested in utc_maps_view_object_create_polygon_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_polygon_set_fill_color_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_polygon_set_fill_color()
 */
int utc_maps_view_object_polygon_set_fill_color_n(void)
{
	ret = maps_view_object_polygon_set_fill_color(NULL, '1', '1', '1', '1');
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_polygon_get_fill_color_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_polygon_get_fill_color()
 */
int utc_maps_view_object_polygon_get_fill_color_p(void)
{
	/* tested in utc_maps_view_object_create_polygon_p */
	return 0;
}

/**
 * @testcase		utc_maps_view_object_polygon_get_fill_color_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_polygon_get_fill_color()
 */
int utc_maps_view_object_polygon_get_fill_color_n(void)
{
	maps_coordinates_h coord1 = NULL, coord2 = NULL, coord3 = NULL;
	maps_coordinates_list_h coord_list = NULL;
	maps_view_object_h polygon = NULL;
	unsigned char r, g, b, a;

	ret = maps_coordinates_create(0.0, 0.0, &coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 10.0, &coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_create(10.0, 0.0, &coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_create(&coord_list);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_list_append(coord_list, coord3);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_polygon(coord_list, '1', '1', '1', '1', &polygon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);


	ret = maps_view_object_polygon_get_fill_color(NULL, &r, &g, &b, &a);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_polygon_get_fill_color(polygon, NULL, NULL, NULL, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_destroy(polygon);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @function		utc_map_view_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_maps_view_object_overlay_startup(void)
{
	utc_maps_view_object_startup();

	maps_coordinates_h coordinate = NULL;
	Evas_Object *object = elm_button_add(win);
	maps_view_overlay_type_e type = MAPS_VIEW_OVERLAY_NORMAL;

	maps_coordinates_create(0.0, 0.0, &coordinate);
	maps_view_object_create_overlay(coordinate, object, type, &overlay);
}

/**
 * @function		utc_map_view_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void utc_maps_view_object_overlay_cleanup(void)
{
	maps_view_object_destroy(overlay);
	utc_maps_view_object_cleanup();
}

/**
 * @testcase		utc_maps_view_object_create_overlay_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_create_overlay()
 */
int utc_maps_view_object_create_overlay_p(void)
{
	maps_coordinates_h coordinate = NULL;
	Evas_Object *object = elm_button_add(win);
	maps_view_overlay_type_e type = MAPS_VIEW_OVERLAY_NORMAL;
	maps_view_object_h overlay2 = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coordinate);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_overlay(coordinate, object, type, &overlay2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_set_visible(overlay2, true);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_set_visible(overlay2, false);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_destroy(overlay2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_create_overlay_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_create_overlay()
 */
int utc_maps_view_object_create_overlay_n(void)
{
	maps_coordinates_h coordinate = NULL;
	Evas_Object *object = NULL;
	maps_view_overlay_type_e type = MAPS_VIEW_OVERLAY_NORMAL;
	maps_view_object_h overlay2 = NULL;

	ret = maps_coordinates_create(0.0, 0.0, &coordinate);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_overlay(NULL, object, type, &overlay2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_overlay(coordinate, NULL, type, &overlay2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_overlay(coordinate, object, type - 1, &overlay2);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_create_overlay(coordinate, object, type, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(coordinate);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_get_object_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_overlay_get_object()
 */
int utc_maps_view_object_overlay_get_object_p(void)
{
	Evas_Object *object = NULL;

	ret = maps_view_object_overlay_get_object(overlay, &object);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_get_object_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_overlay_get_object()
 */
int utc_maps_view_object_overlay_get_object_n(void)
{
	Evas_Object *object = NULL;

	ret = maps_view_object_overlay_get_object(NULL, &object);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_overlay_get_object(overlay, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_set_coordinates_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_overlay_set_coordinates()
 */
int utc_maps_view_object_overlay_set_coordinates_p(void)
{
	maps_coordinates_h coordinates = NULL;
	ret = maps_coordinates_create(1.0, 1.0, &coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_overlay_set_coordinates(overlay, coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_set_coordinates_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_overlay_set_coordinates()
 */
int utc_maps_view_object_overlay_set_coordinates_n(void)
{
	maps_coordinates_h coordinates = NULL;

	ret = maps_coordinates_create(1.0, 1.0, &coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_overlay_set_coordinates(NULL, coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_overlay_set_coordinates(overlay, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_get_coordinates_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_overlay_get_coordinates()
 */
int utc_maps_view_object_overlay_get_coordinates_p(void)
{
	maps_coordinates_h coordinates = NULL;

	ret = maps_view_object_overlay_get_coordinates(overlay, &coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_coordinates_destroy(coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);
	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_get_coordinates_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_overlay_get_coordinates()
 */
int utc_maps_view_object_overlay_get_coordinates_n(void)
{
	maps_coordinates_h coordinates = NULL;

	ret = maps_view_object_overlay_get_coordinates(NULL, &coordinates);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_overlay_get_coordinates(overlay, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_set_min_zoom_level_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_overlay_set_min_zoom_level()
 */
int utc_maps_view_object_overlay_set_min_zoom_level_p(void)
{
	ret = maps_view_object_overlay_set_min_zoom_level(overlay, 1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_set_min_zoom_level_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_overlay_set_min_zoom_level()
 */
int utc_maps_view_object_overlay_set_min_zoom_level_n(void)
{
	ret = maps_view_object_overlay_set_min_zoom_level(NULL, 1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_overlay_set_min_zoom_level(overlay, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_get_min_zoom_level_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_overlay_get_min_zoom_level()
 */
int utc_maps_view_object_overlay_get_min_zoom_level_p(void)
{
	int zoom_level = 0;

	ret = maps_view_object_overlay_get_min_zoom_level(overlay, &zoom_level);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_get_min_zoom_level_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_overlay_get_min_zoom_level()
 */
int utc_maps_view_object_overlay_get_min_zoom_level_n(void)
{
	int zoom_level = 0;

	ret = maps_view_object_overlay_get_min_zoom_level(NULL, &zoom_level);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_overlay_get_min_zoom_level(overlay, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_set_max_zoom_level_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_overlay_set_max_zoom_level()
 */
int utc_maps_view_object_overlay_set_max_zoom_level_p(void)
{
	ret = maps_view_object_overlay_set_max_zoom_level(overlay, 20);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_set_max_zoom_level_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_overlay_set_max_zoom_level()
 */
int utc_maps_view_object_overlay_set_max_zoom_level_n(void)
{
	ret = maps_view_object_overlay_set_max_zoom_level(NULL, 5);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_overlay_set_max_zoom_level(overlay, -1);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_get_max_zoom_level_p
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Positive test case of maps_view_object_overlay_get_max_zoom_level()
 */
int utc_maps_view_object_overlay_get_max_zoom_level_p(void)
{
	int zoom_level = 0;

	ret = maps_view_object_overlay_get_max_zoom_level(overlay, &zoom_level);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_NONE, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_maps_view_object_overlay_get_max_zoom_level_n
 * @since_tizen		@if MOBILE 3.0 @elseif WEARABLE 2.3.2 @endif
 * @description		Negative test case of maps_view_object_overlay_get_max_zoom_level()
 */
int utc_maps_view_object_overlay_get_max_zoom_level_n(void)
{
	int zoom_level = 0;

	ret = maps_view_object_overlay_get_max_zoom_level(NULL, &zoom_level);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	ret = maps_view_object_overlay_get_max_zoom_level(overlay, NULL);
	ASSERT_IF_VAL_REF2(ret, is_maps_supported, MAPS_ERROR_INVALID_PARAMETER, MAPS_ERROR_NOT_SUPPORTED);

	return 0;
}

