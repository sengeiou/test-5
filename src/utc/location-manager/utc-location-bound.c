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

#include <locations.h>
#include <glib.h>
#include "assert.h"
#include <string.h>
#include <unistd.h>
#include <system_info.h>
#include "utc-location-manager-common.h"

//& set: LocationBounds
static bool touch_foreach_bounds = false;
static location_manager_h manager = NULL;


static bool __location_bounds_cb(location_bounds_h bounds, void *user_data)
{
	if (bounds == NULL) {
		printf("bounds ==NULL\n");
	} else {
		location_bounds_type_e type;
		ret = location_bounds_get_type(bounds, &type);
		if (ret != LOCATIONS_ERROR_NONE )
		{
			return false;
		}
		touch_foreach_bounds = true;
	}
	return true;
}

static bool __polygon_coords_cb(location_coords_s coords, void *user_data)
{
	printf("polygon_coords_cb(latitude : %lf, longitude: %lf) \n", coords.latitude, coords.longitude);
	return true;
}

static void __bounds_state_cb(location_boundary_state_e state, void *user_data)
{
	FPRINTF("[%d: %s] __bounds_state_cb\\n", __LINE__, "BBB");
}

/**
 * @function		utc_location_manager_bound_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_location_manager_bound_startup(void)
{
	system_info_get_platform_bool(LOCATION_FEATURE, &is_location_supported);
	system_info_get_platform_bool(GPS_FEATURE, &is_gps_supported);
	system_info_get_platform_bool(WPS_FEATURE, &is_wps_supported);

	if (manager == NULL) {
		location_manager_create(LOCATIONS_METHOD_HYBRID, &manager);
	}
}

/**
 * @function		utc_location_manager_bound_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_location_manager_bound_cleanup(void)
{
	if (manager) {
		location_manager_destroy(manager);
		manager = NULL;
	}
}


/**
 * @testcase		utc_location_manager_add_boundary_p
 * @since_tizen		2.3
 * @description		Adds a bounds for a given location manager
 */
int utc_location_manager_add_boundary_p(void)
{
	location_bounds_h bounds_circle = NULL;
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;

	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	CHECK(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, bounds_circle);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_manager_remove_boundary(manager, bounds_circle);
	CHECK(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_circle);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_add_boundary_p2
 * @since_tizen		2.3
 * @description		Adds a bounds for a given location manager
 */
int utc_location_manager_add_boundary_p2(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, bounds_rect);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_manager_remove_boundary(manager, bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_rect);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_add_boundary_p3
 * @since_tizen		2.3
 * @description		Adds a bounds for a given location manager
 */
int utc_location_manager_add_boundary_p3(void)
{
	location_bounds_h bounds_poly = NULL;

	int poly_size = 3;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 30;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, bounds_poly);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_manager_remove_boundary(manager, bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_add_boundary_n
 * @since_tizen		2.3
 * @description		Adds a bounds for a given location manager with invalid parameters
 */
int utc_location_manager_add_boundary_n(void)
{
	location_bounds_h bounds_circle = NULL;
	ret = location_manager_add_boundary(NULL, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_add_boundary(NULL, bounds_circle);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_foreach_boundary_p
 * @since_tizen		2.3
 * @description		Retrieves all location bounds by invoking a specific callback for each location bounds
 */
int utc_location_manager_foreach_boundary_p(void)
{
	location_bounds_h bounds_circle = NULL;
	location_bounds_h bounds_rect = NULL;
	location_bounds_h bounds_poly = NULL;
	touch_foreach_bounds = false;

	//Add the circle bounds
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;
	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	CHECK(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, bounds_circle);
	CHECK_ERROR_NONE(is_location_supported, ret);

	//Add the rect bounds
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;
	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, bounds_rect);
	CHECK(is_location_supported, ret);

	//Add the polygon bounds
	int poly_size = 3;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 30;
	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_manager_foreach_boundary(manager, __location_bounds_cb, NULL);
	if (is_location_supported) {
		assert_eq(ret, LOCATION_BOUNDS_ERROR_NONE);
		assert_eq(touch_foreach_bounds, true);
	} else {
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	ret = location_manager_remove_boundary(manager, bounds_circle);
	CHECK(is_location_supported, ret);
	ret = location_bounds_destroy(bounds_circle);
	CHECK(is_location_supported, ret);

	ret = location_manager_remove_boundary(manager, bounds_rect);
	CHECK(is_location_supported, ret);
	ret = location_bounds_destroy(bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_manager_remove_boundary(manager, bounds_poly);
	CHECK(is_location_supported, ret);
	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_foreach_boundary_n
 * @since_tizen		2.3
 * @description		Retrieves all location bounds by invoking a specific callback for each location bounds with invalid parameters
 */
int utc_location_manager_foreach_boundary_n(void)
{
	ret = location_manager_foreach_boundary(NULL, __location_bounds_cb, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_foreach_boundary(manager, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_remove_boundary_p
 * @since_tizen		2.3
 * @description		Deletes a bounds for a given location manager
 */
int utc_location_manager_remove_boundary_p(void)
{
	location_bounds_h bounds_circle = NULL;
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;

	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	CHECK(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, bounds_circle);
	CHECK(is_location_supported, ret);

	ret = location_manager_remove_boundary(manager, bounds_circle);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_circle);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_remove_boundary_p2
 * @since_tizen		2.3
 * @description		Deletes a bounds for a given location manager
 */
int utc_location_manager_remove_boundary_p2(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_manager_remove_boundary(manager, bounds_rect);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_rect);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_remove_boundary_p3
 * @since_tizen		2.3
 * @description		Deletes a bounds for a given location manager
 */
int utc_location_manager_remove_boundary_p3(void)
{
	location_bounds_h bounds_poly = NULL;
	int poly_size = 3;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 30;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_manager_remove_boundary(manager, bounds_poly);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_manager_remove_boundary_n
 * @since_tizen		2.3
 * @description		Deletes a bounds for a given location manager with invalid parameters
 */
int utc_location_manager_remove_boundary_n(void)
{
	location_bounds_h bounds_rect = NULL;
	ret = location_manager_remove_boundary(NULL, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_remove_boundary(NULL, bounds_rect);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_manager_remove_boundary(manager, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_foreach_polygon_coords_p
 * @since_tizen		2.3
 * @description		Get the coordinates of a polygon
 */
int utc_location_bounds_foreach_polygon_coords_p(void)
{
	location_bounds_h bounds_poly = NULL;
	int poly_size = 3;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 30;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_manager_add_boundary(manager, bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_bounds_foreach_polygon_coords(bounds_poly, __polygon_coords_cb, NULL);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_manager_remove_boundary(manager, bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_foreach_polygon_coords_n
 * @since_tizen		2.3
 * @description		Get the coordinates of a polygon with invalid parameters
 */
int utc_location_bounds_foreach_polygon_coords_n(void)
{
	ret = location_bounds_foreach_polygon_coords(NULL, __polygon_coords_cb, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_foreach_polygon_coords_n2
 * @since_tizen		2.3
 * @description		Get the coordinates of a polygon with invalid parameters
 */
int utc_location_bounds_foreach_polygon_coords_n2(void)
{
	location_bounds_h bounds_poly = NULL;
	int poly_size = 3;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 30;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_bounds_foreach_polygon_coords(bounds_poly, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_get_circle_coords_p
 * @since_tizen		2.3
 * @description		Gets the center position and radius of circle bounds
 */
int utc_location_bounds_get_circle_coords_p(void)
{
	location_bounds_h bounds_circle = NULL;
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;

	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	CHECK(is_location_supported, ret);

	ret = location_bounds_get_circle_coords(bounds_circle, &center, &radius);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_circle);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_get_circle_coords_n
 * @since_tizen		2.3
 * @description		Gets the center position and radius of circle bounds with invalid parameters
 */
int utc_location_bounds_get_circle_coords_n(void)
{
	location_bounds_h bounds_circle = NULL;
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;

	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	CHECK(is_location_supported, ret);

	ret = location_bounds_get_circle_coords(NULL, &center, &radius);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_get_circle_coords(bounds_circle, NULL, &radius);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_get_circle_coords(bounds_circle, &center, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_circle);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_get_rect_coords_p
 * @since_tizen		2.3
 * @description		Get the rect coordinations
 */
int utc_location_bounds_get_rect_coords_p(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_bounds_get_rect_coords(bounds_rect, &left_top, &right_bottom);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_rect);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_get_rect_coords_n
 * @since_tizen		2.3
 * @description		Get the rect coordinations with invalid parameters
 */
int utc_location_bounds_get_rect_coords_n(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_bounds_get_rect_coords(NULL, &left_top, &right_bottom);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_get_rect_coords(bounds_rect, NULL, &right_bottom);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_get_rect_coords(bounds_rect, &left_top, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_rect);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_get_type_p
 * @since_tizen		2.3
 * @description		Gets the type of location bounds
 */
int utc_location_bounds_get_type_p(void)
{
	location_bounds_h bounds_rect = NULL;
	location_bounds_type_e type;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	if (is_location_supported) {
		ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
		assert_eq(ret, LOCATIONS_ERROR_NONE);

		ret = location_bounds_get_type(bounds_rect, &type);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
		assert_eq(type, LOCATION_BOUNDS_RECT);

		ret = location_bounds_destroy(bounds_rect);
		assert_eq(ret, LOCATIONS_ERROR_NONE);
	} else {
		ret = location_bounds_get_type(bounds_rect, &type);
		assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_location_bounds_get_type_n
 * @since_tizen		2.3
 * @description		Gets the type of location bounds with invalid parameters
 */
int utc_location_bounds_get_type_n(void)
{
	location_bounds_h bounds_rect = NULL;
	location_bounds_type_e type;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_bounds_get_type(NULL, &type);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_get_type(bounds_rect, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_rect);
	CHECK(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_contains_coordinates_p
 * @since_tizen		2.3
 * @description		Checks whether the bounds contains the specified coordinates
 */
int utc_location_bounds_contains_coordinates_p(void)
{
	location_bounds_h bounds_poly = NULL;
	int poly_size = 3;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 10;
	location_coords_s test_coords;
	test_coords.latitude = 20;
	test_coords.longitude = 12;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	location_bounds_contains_coordinates(bounds_poly, test_coords);
	ret = get_last_result();
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_contains_coordinates_n
 * @since_tizen		2.3
 * @description		Checks whether the bounds contains the specified coordinates with invalid parameters
 */
int utc_location_bounds_contains_coordinates_n(void)
{
	location_coords_s test_coords;
	test_coords.latitude = 12;
	test_coords.longitude = 12;

	location_bounds_contains_coordinates(NULL, test_coords);
	ret = get_last_result();
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_contains_coordinates_n2
 * @since_tizen		2.3
 * @description		Checks whether the bounds contains the specified coordinates with invalid parameters
 */
int utc_location_bounds_contains_coordinates_n2(void)
{
	location_bounds_h bounds_poly = NULL;
	int poly_size = 3;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 10;
	location_coords_s coord_test;
	coord_test.latitude = -91;
	coord_test.longitude = 181;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	location_bounds_contains_coordinates(bounds_poly, coord_test);
	ret = get_last_result();
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_contains_coordinates_on_edge_p
 * @since_tizen		6.0
 * @description		Checks whether the edges of the bounds contain the specified coordinates within tolerance
 */
int utc_location_bounds_contains_coordinates_on_edge_p(void)
{
	location_bounds_h bounds_poly = NULL;
	int poly_size = 4;
	double tolerance = 40;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 28.581394;
	coord_list[0].longitude = 77.362621;
	coord_list[1].latitude = 28.580652;
	coord_list[1].longitude = 77.363302;
	coord_list[2].latitude = 28.580976;
	coord_list[2].longitude = 77.363771;
	coord_list[3].latitude = 28.581717;
	coord_list[3].longitude = 77.363032;
	location_coords_s test_coords;
	test_coords.latitude = 28.580723;
	test_coords.longitude = 77.363666;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	location_bounds_contains_coordinates_on_edge(bounds_poly, test_coords, tolerance);
	ret = get_last_result();
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_contains_coordinates_on_edge_n
 * @since_tizen		6.0
 * @description		Checks whether the edges of the bounds contain the specified coordinates within tolerance with invalid parameters
 */
int utc_location_bounds_contains_coordinates_on_edge_n(void)
{
	double tolerance = 40;
	location_coords_s test_coords;
	test_coords.latitude = 28.580723;
	test_coords.longitude = 77.363666;

	location_bounds_contains_coordinates_on_edge(NULL, test_coords, tolerance);
	ret = get_last_result();
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_contains_coordinates_on_edge_n2
 * @since_tizen		6.0
 * @description		Checks whether the edges of the bounds contain the specified coordinates within tolerance with invalid parameters
 */
int utc_location_bounds_contains_coordinates_on_edge_n2(void)
{
	location_bounds_h bounds_poly = NULL;
	int poly_size = 4;
	double tolerance = 40;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 28.581394;
	coord_list[0].longitude = 77.362621;
	coord_list[1].latitude = 28.580652;
	coord_list[1].longitude = 77.363302;
	coord_list[2].latitude = 28.580976;
	coord_list[2].longitude = 77.363771;
	coord_list[3].latitude = 28.581717;
	coord_list[3].longitude = 77.363032;
	location_coords_s coord_test;
	coord_test.latitude = -91;
	coord_test.longitude = 181;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	location_bounds_contains_coordinates_on_edge(bounds_poly, coord_test, tolerance);
	ret = get_last_result();
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_contains_coordinates_on_edge_n3
 * @since_tizen		6.0
 * @description		Checks whether the edges of the bounds contain the specified coordinates within tolerance with invalid parameters
 */
int utc_location_bounds_contains_coordinates_on_edge_n3(void)
{
	location_bounds_h bounds_poly = NULL;
	int poly_size = 4;
	double tolerance = -40;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 28.581394;
	coord_list[0].longitude = 77.362621;
	coord_list[1].latitude = 28.580652;
	coord_list[1].longitude = 77.363302;
	coord_list[2].latitude = 28.580976;
	coord_list[2].longitude = 77.363771;
	coord_list[3].latitude = 28.581717;
	coord_list[3].longitude = 77.363032;
	location_coords_s coord_test;
	coord_test.latitude = 28.580723;
	coord_test.longitude = 77.363666;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	location_bounds_contains_coordinates_on_edge(bounds_poly, coord_test, tolerance);
	ret = get_last_result();
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_create_rect_p
 * @since_tizen		2.3
 * @description		Creates a rect type of new location bounds
 */
int utc_location_bounds_create_rect_p(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_rect);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_create_rect_n
 * @since_tizen		2.3
 * @description		Creates a rect type of new location bounds with invalid parameters
 */
int utc_location_bounds_create_rect_n(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = -200;
	left_top.longitude = -200;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_create_rect_n2
 * @since_tizen		2.3
 * @description		Creates a rect type of new location bounds with invalid parameters
 */
int utc_location_bounds_create_rect_n2(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	left_top.latitude = 30;
	left_top.longitude = 30;
	location_coords_s right_bottom;
	right_bottom.latitude = -200;
	right_bottom.longitude = -200;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_create_rect_n3
 * @since_tizen		2.3
 * @description		Creates a rect type of new location bounds with invalid parameters
 */
int utc_location_bounds_create_rect_n3(void)
{
	location_coords_s left_top;
	left_top.latitude = 30;
	left_top.longitude = 30;
	location_coords_s right_bottom;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_create_circle_p
 * @since_tizen		2.3
 * @description		Creates a circle type of new location bounds
 */
int utc_location_bounds_create_circle_p(void)
{
	location_bounds_h bounds_circle = NULL;
	location_coords_s center;
	center.latitude = 37.336723;
	center.longitude = -121.889555;
	double radius = 30;

	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_circle);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_create_circle_n
 * @since_tizen		2.3
 * @description		Creates a circle type of new location bounds with invalid parameters
 */
int utc_location_bounds_create_circle_n(void)
{
	location_bounds_h bounds_circle = NULL;
	location_coords_s center;
	center.latitude = -200;
	center.longitude = -200;
	double radius = 30;

	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_create_circle_n2
 * @since_tizen		2.3
 * @description		Creates a circle type of new location bounds with invalid parameters
 */
int utc_location_bounds_create_circle_n2(void)
{
	location_bounds_h bounds_circle = NULL;
	location_coords_s center;
	center.latitude = 37.336723;
	center.longitude = -121.889555;
	double radius = -1;

	ret = location_bounds_create_circle(center, radius, &bounds_circle);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_create_circle_n3
 * @since_tizen		2.3
 * @description		Creates a circle type of new location bounds with invalid parameters
 */
int utc_location_bounds_create_circle_n3(void)
{
	location_coords_s center;
	center.latitude = 37.336723;
	center.longitude = -121.889555;
	double radius = 30;

	ret = location_bounds_create_circle(center, radius, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_create_polygon_p
 * @since_tizen		2.3
 * @description		Creates a polygon type of new location bounds
 */
int utc_location_bounds_create_polygon_p(void)
{
	location_bounds_h bounds_poly = NULL;
	int poly_size = 3;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 30;

	ret = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_bounds_set_state_changed_cb(bounds_poly, __bounds_state_cb, NULL);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_unset_state_changed_cb(bounds_poly);
	CHECK(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_poly);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_set_state_changed_cb_p2
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the boundary area is entered or exited
 */
int utc_location_bounds_set_state_changed_cb_p2(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_bounds_set_state_changed_cb(bounds_rect, __bounds_state_cb, NULL);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_unset_state_changed_cb(bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_rect);
	CHECK(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_set_state_changed_cb_n
 * @since_tizen		2.3
 * @description		Registers a callback function to be invoked when the boundary area is entered or exited with invalid parameters
 */
int utc_location_bounds_set_state_changed_cb_n(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_bounds_set_state_changed_cb(bounds_rect, NULL, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_set_state_changed_cb(NULL, __bounds_state_cb, NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_rect);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_unset_state_changed_cb_p
 * @since_tizen		2.3
 * @description		Unregisters the callback function
 */
int utc_location_bounds_unset_state_changed_cb_p(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_bounds_set_state_changed_cb(bounds_rect, __bounds_state_cb, NULL);
	CHECK(is_location_supported, ret);

	ret = location_bounds_unset_state_changed_cb(bounds_rect);
	CHECK_ERROR_NONE(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_rect);
	CHECK(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_unset_state_changed_cb_n
 * @since_tizen		2.3
 * @description		Unregisters the callback function with invalid parameters
 */
int utc_location_bounds_unset_state_changed_cb_n(void)
{
	ret = location_bounds_unset_state_changed_cb(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}

/**
 * @testcase		utc_location_bounds_destroy_p
 * @since_tizen		2.3
 * @description		Releases the location bounds handle
 */
int utc_location_bounds_destroy_p(void)
{
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	ret = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	CHECK(is_location_supported, ret);

	ret = location_bounds_destroy(bounds_rect);
	CHECK_ERROR_NONE(is_location_supported, ret);

	return 0;
}

/**
 * @testcase		utc_location_bounds_destroy_n
 * @since_tizen		2.3
 * @description		Releases the location bounds handle with invalid parameters
 */
int utc_location_bounds_destroy_n(void)
{
	ret = location_bounds_destroy(NULL);
	CHECK_INVALID_PARAMETER(is_location_supported, ret);
	return 0;
}
