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

#include "ITs-location-manager-common.h"

/** @addtogroup itc-location-manager
*  @ingroup itc
*  @{
*/

//& set: LocationManager

int g_nPolygonCoordsResponseCount = 0;

/**
* @function 		ITs_location_bounds_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_location_bounds_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Location_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsWpsFeatureSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_WPS_FEATURE, API_NAMESPACE);
	g_bIsGpsFeatureSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_GPS_FEATURE, API_NAMESPACE);
	g_bIsLocationFeatureSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_FEATURE, API_NAMESPACE);

	g_bIsLocationManagerSupported = g_bIsLocationFeatureSupported && ( g_bIsWpsFeatureSupported || g_bIsGpsFeatureSupported);
	g_nPolygonCoordsResponseCount = 0;
}

/**
* @function 		ITs_location_bounds_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_location_bounds_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Location_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		LocationPolygonCoordinatesCB
* @description	 	to check polygon coordinates
* @parameter		location_coords_s, void *user_data
* @return 			bool
*/
bool LocationPolygonCoordinatesCB(location_coords_s coords, void *user_data)
{
	FPRINTF("[Line : %d][%s]location_bounds_foreach_rect_coords(latitude : %lf, longitude: %lf)\\n", __LINE__, API_NAMESPACE, coords.latitude, coords.longitude);
	g_nPolygonCoordsResponseCount++;
	if(user_data == NULL)
	{
		FPRINTF("[Line : %d][%s] User data received in callback is NULL \\n", __LINE__, API_NAMESPACE);
		g_nPolygonCoordsResponseCount--;
	}
	return TRUE;
}

/**
* @function 		LocationBoundsPolygonStateChangedCB
* @description	 	invoke when coordinate state change on location boundry
* @parameter		location_boundary_state_e, void *user_data
* @return 			void
*/
void LocationBoundsPolygonStateChangedCB(location_boundary_state_e state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside the callback LocationBoundsPolygonStateChangedCB\\n", __LINE__, API_NAMESPACE);
}

/** @addtogroup itc-location-bounds-testcases
*  @brief 		Integration testcases for module location-bounds
*  @ingroup 	itc-location-bounds
*  @{
*/

//& purpose: To check creates/destroy a rect type of new location bounds
//& type: auto
/**
* @testcase 			ITc_location_bounds_create_destory_rect_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check creates/destroy a rect type of new location bounds
* @scenario				creates/destroy a rect type of new location bounds and verify output\n
* 						check the generate location bound for null\n
* 						destroy a rect type of new location bounds and verify output
* @apicovered			location_bounds_create_rect, location_bounds_create_rect
* @passcase				When location_bounds_create_rect and location_bounds_destroy are successful
* @failcase				If target API fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_bounds_create_destory_rect_p(void)
{
	START_TEST;

	location_bounds_h hRectBounds = NULL;
	location_coords_s left_top;
	left_top.latitude = 30;
	left_top.longitude = 30;
	location_coords_s right_bottom;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	location_bound_error_e nRet = location_bounds_create_rect(left_top, right_bottom, &hRectBounds);// Target API
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_bounds_create_rect() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	CHECK_HANDLE(hRectBounds, "location_bounds_create_rect");
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_create_rect", LocationBoundsGetError(nRet));

	nRet = location_bounds_destroy(hRectBounds);// Target API
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_destroy", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check the top left and right bottom of rect type location bounds
//& type: auto
/**
* @testcase 			ITc_location_bounds_get_rect_coords_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check the top left and right bottom of rect type location bounds
* @scenario				creates/destroy a rect type of new location bounds and verify output\n
* 						check the generate location bound for null\n
* 						Get location bounds coords\n
* 						destroy a rect type of new location bounds and verify output
* @apicovered			location_bounds_get_rect_coords, location_bounds_create_rect, location_bounds_create_rect
* @passcase				When location_bounds_get_rect_coords, location_bounds_create_rect and location_bounds_destroy are successful
* @failcase				If target API or supporting APIs fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_bounds_get_rect_coords_p(void)
{
	START_TEST;

	location_bounds_h hRectBounds = NULL;

	location_coords_s sLeftTop;
	sLeftTop.latitude = 30;
	sLeftTop.longitude = 30;

	location_coords_s sRightBottom;
	sRightBottom.latitude = 10;
	sRightBottom.longitude = 50;

	location_coords_s sFindLeftTop = {0};
	location_coords_s sFindRightBottom = {0};

	location_bound_error_e nRet = location_bounds_create_rect(sLeftTop, sRightBottom, &hRectBounds);
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_bounds_create_rect() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_create_rect", LocationBoundsGetError(nRet));
	if ( hRectBounds == NULL )
	{
		FPRINTF("[Line : %d][%s] location_bounds_create_rect failed on precondition, returned location rect bound handle is null\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = location_bounds_get_rect_coords(hRectBounds, &sFindLeftTop, &sFindRightBottom);// Target API
	PRINT_RESULT_CLEANUP(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_get_rect_coords", LocationBoundsGetError(nRet), location_bounds_destroy(hRectBounds));

	if ( (sFindLeftTop.latitude != sLeftTop.latitude) || (sFindLeftTop.longitude != sLeftTop.longitude) )
	{
		FPRINTF("[Line : %d][%s] location_bounds_get_rect_coords failed, mismatch in top left value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( (sFindRightBottom.latitude != sRightBottom.latitude) || (sFindRightBottom.longitude != sRightBottom.longitude) )
	{
		FPRINTF("[Line : %d][%s] location_bounds_get_rect_coords failed, mismatch in bottom right value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = location_bounds_destroy(hRectBounds);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_destroy", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check creates/destroy a circle type of new location bounds
//& type: auto
/**
* @testcase 			ITc_location_bounds_create_destory_circle_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check creates/destroy a circle type of new location bounds
* @scenario				creates a circle type of new location bounds and verify output\n
* 						check the generate location bound for null\n
* 						destroy a circle type of new location bounds and verify output
* @apicovered			location_bounds_create_circle
* @passcase				When location_bounds_create_circle and location_bounds_destroy are successful
* @failcase				If target API fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_bounds_create_destory_circle_p(void)
{
	START_TEST;

	location_bounds_h hCircleBounds = NULL;
	location_coords_s center;
	center.latitude = 37.336723;
	center.longitude = -121.889555;
	double dRadius = 30;

	location_bound_error_e nRet = location_bounds_create_circle(center, dRadius, &hCircleBounds);// Target API
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_bounds_create_circle() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_create_circle", LocationBoundsGetError(nRet));
	CHECK_HANDLE(hCircleBounds, "location_bounds_create_circle");

	nRet = location_bounds_destroy(hCircleBounds);// Target API
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_destroy", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check the center position and radius of circle bounds
//& type: auto
/**
* @testcase 			ITc_location_bounds_get_circle_coords_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check the center position and radius of circle bounds
* @scenario				creates/destroy a rect type of new location bounds and verify output\n
* 						check the generate location bound for null\n  
* 						Get circle center location bounds and redius\n
* 						destroy a rect type of new location bounds and verify output
* @apicovered			location_bounds_get_circle_coords, location_bounds_destroy
* @passcase				When location_bounds_get_circle_coords and supporting APIs are successful
* @failcase				If target API or supporting APIs fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_bounds_get_circle_coords_p(void)
{
	START_TEST;

	location_bounds_h hCircleBounds = NULL;
	location_coords_s sCenter;
	sCenter.latitude = 37.336723;
	sCenter.longitude = -121.889555;

	double dRadius = 30;
	double dFindRadius = 0;

	location_coords_s sFindCenter = {0};

	location_bound_error_e nRet = location_bounds_create_circle(sCenter,dRadius, &hCircleBounds);
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_bounds_create_circle() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_create_circle", LocationBoundsGetError(nRet));
	CHECK_HANDLE(hCircleBounds, "location_bounds_create_circle");

	nRet = location_bounds_get_circle_coords(hCircleBounds, &sFindCenter, &dFindRadius);// Target API
	PRINT_RESULT_CLEANUP(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_get_circle_coords", LocationBoundsGetError(nRet), location_bounds_destroy(hCircleBounds));

	if ( (sCenter.latitude != sFindCenter.latitude) || (sCenter.longitude != sFindCenter.longitude) )
	{
		FPRINTF("[Line : %d][%s] location_bounds_get_circle_coords failed, mismatch in centre coord\\n", __LINE__, API_NAMESPACE);
		location_bounds_destroy(hCircleBounds);
		return 1;
	}

	if ( dRadius != dFindRadius )
	{
		FPRINTF("[Line : %d][%s] location_bounds_get_circle_coords failed, mismatch in radius\\n", __LINE__, API_NAMESPACE);
		location_bounds_destroy(hCircleBounds);
		return 1;
	}

	nRet = location_bounds_destroy(hCircleBounds);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_destroy", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check creates/destroy a polygon type of new location bounds
//& type: auto
/**
* @testcase 			ITc_location_bounds_create_destory_polygon_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check creates/destroy a polygon type of new location bounds
* @scenario				creates a polygon type of new location bounds and verify output\n
* 						check the generate location bound for null\n
* 						destroy a polygon type of new location bounds and verify output
* @apicovered			location_bounds_create_polygon, location_bounds_destroy
* @passcase				When location_bounds_create_polygon and location_bounds_destroy are successful
* @failcase				If target API fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_bounds_create_destory_polygon_p(void)
{
	START_TEST;

	location_bounds_h hPolyLocationBound = NULL;
	int nPolySize = 3;
	location_coords_s location_coord_list[nPolySize];

	location_coord_list[0].latitude = 10;
	location_coord_list[0].longitude = 10;
	location_coord_list[1].latitude = 20;
	location_coord_list[1].longitude = 20;
	location_coord_list[2].latitude = 30;
	location_coord_list[2].longitude = 30;

	location_bound_error_e nRet = location_bounds_create_polygon(location_coord_list, nPolySize, &hPolyLocationBound);// Target API
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_bounds_create_polygon() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_create_polygon", LocationBoundsGetError(nRet));
	CHECK_HANDLE(hPolyLocationBound, "location_bounds_create_polygon");

	nRet = location_bounds_destroy(hPolyLocationBound);// Target API
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_destroy", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check register/unregister callback function to be invoked when boundary area is entered or exited
//& type: auto
/**
* @testcase 			ITc_location_bounds_set_unset_state_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check register/unregister callback function to be invoked when boundary area is entered or exited
* @scenario				creates a polygon type of new location bounds and verify output\n
* 						check the generate location bound for null\n
* 						register callback function to be invoked when boundary area is entered or exited\n  
* 						unregister callback function\n
* 						destroy a polygon type of new location bounds and verify output
* @apicovered			location_bounds_create_polygon, location_bounds_destroy, location_bounds_set_state_changed_cb, location_bounds_unset_state_changed_cb
* @passcase				When location_bounds_set_state_changed_cb, location_bounds_unset_state_changed_cb and supporting APIs are successful
* @failcase				If target API and supporting APIs fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_bounds_set_unset_state_changed_cb_p(void)
{
	START_TEST;

	location_bounds_h hPolyLocationBound = NULL;
	int nPolySize = 3;
	location_coords_s location_coord_list[nPolySize];

	location_coord_list[0].latitude = 10;
	location_coord_list[0].longitude = 10;
	location_coord_list[1].latitude = 20;
	location_coord_list[1].longitude = 20;
	location_coord_list[2].latitude = 30;
	location_coord_list[2].longitude = 30;

	location_bound_error_e nRet = location_bounds_create_polygon(location_coord_list, nPolySize, &hPolyLocationBound);
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_bounds_create_polygon() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_create_polygon", LocationBoundsGetError(nRet));
	CHECK_HANDLE(hPolyLocationBound, "location_bounds_create_polygon");

	nRet = location_bounds_set_state_changed_cb(hPolyLocationBound, LocationBoundsPolygonStateChangedCB, NULL);// Target API
	PRINT_RESULT_CLEANUP(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_set_state_changed_cb", LocationBoundsGetError(nRet), location_bounds_destroy(hPolyLocationBound));

	nRet = location_bounds_unset_state_changed_cb(hPolyLocationBound);// Target API
	PRINT_RESULT_CLEANUP(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_unset_state_changed_cb", LocationBoundsGetError(nRet), location_bounds_destroy(hPolyLocationBound));

	nRet = location_bounds_destroy(hPolyLocationBound);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_destroy", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check coordinates of polygon
//& type: auto
/**
* @testcase 			ITc_location_bounds_foreach_polygon_coords_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check coordinates of polygon
* @scenario				creates a polygon type of new location bounds and verify output\n
* 						check the generate location bound for null\n
* 						check coordinates of polygon\n
* 						destroy a polygon type of new location bounds and verify output
* @apicovered			location_bounds_foreach_polygon_coords, location_bounds_create_polygon, location_bounds_destroy
* @passcase				When location_bounds_foreach_polygon_coords and supporting APIs are successful
* @failcase				If target API or supporting APIs fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_bounds_foreach_polygon_coords_p(void)
{
	START_TEST;

	location_bounds_h hPolyLocationBound = NULL;
	int nPolySize = 3;
	location_coords_s location_coord_list[nPolySize];
	location_coord_list[0].latitude = 10;
	location_coord_list[0].longitude = 10;
	location_coord_list[1].latitude = 20;
	location_coord_list[1].longitude = 20;
	location_coord_list[2].latitude = 30;
	location_coord_list[2].longitude = 30;

	location_bound_error_e nRet = location_bounds_create_polygon(location_coord_list, nPolySize, &hPolyLocationBound);
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_bounds_create_polygon() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_create_polygon", LocationBoundsGetError(nRet));
	CHECK_HANDLE(hPolyLocationBound, "location_bounds_create_polygon");

	nRet = location_bounds_foreach_polygon_coords(hPolyLocationBound, LocationPolygonCoordinatesCB, &location_coord_list);// Target API
	PRINT_RESULT_CLEANUP(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_foreach_polygon_coords", LocationBoundsGetError(nRet), location_bounds_destroy(hPolyLocationBound));
	if ( g_nPolygonCoordsResponseCount != nPolySize )
	{
		FPRINTF("[Line : %d][%s] location_bounds_foreach_polygon_coords failed, mismatch in polygon coordinate\\n", __LINE__, API_NAMESPACE);
		location_bounds_destroy(hPolyLocationBound);
		return 1;
	}

	g_nPolygonCoordsResponseCount = 0;
	nRet = location_bounds_destroy(hPolyLocationBound);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_destroy", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check the bounds contains the specified coordinates
//& type: auto
/**
* @testcase 			ITc_location_bounds_contains_coordinates_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check the bounds contains the specified coordinates
* @scenario				creates a polygon type of new location bounds and verify output\n
* 						check the generate location bound for null\n
* 						check coordinates inside polygon boundary\n
* 						destroy a polygon type of new location bounds and verify output
* @apicovered			location_bounds_contains_coordinates, location_bounds_create_polygon, location_bounds_destroy
* @passcase				When location_bounds_contains_coordinates and supporting APIs are successful
* @failcase				If target API or supporting APIs fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_bounds_contains_coordinates_p(void)
{
	START_TEST;

	location_bounds_h hPolyLocationBound = NULL;
	bool bIsContained = false;
	int nPolySize = 3;
	location_coords_s location_coord_list[nPolySize];
	location_coord_list[0].latitude = 10;
	location_coord_list[0].longitude = 10;
	location_coord_list[1].latitude = 20;
	location_coord_list[1].longitude = 20;
	location_coord_list[2].latitude = 30;
	location_coord_list[2].longitude = 10;

	//Checking coordinates in location boundary
	location_coords_s testLocationCoordinates;
	testLocationCoordinates.latitude = 20;
	testLocationCoordinates.longitude = 12;
	location_bound_error_e nRet = location_bounds_create_polygon(location_coord_list, nPolySize, &hPolyLocationBound);
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_bounds_create_polygon() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_create_polygon", LocationBoundsGetError(nRet));
	CHECK_HANDLE(hPolyLocationBound, "location_bounds_create_polygon");

	bIsContained = location_bounds_contains_coordinates(hPolyLocationBound, testLocationCoordinates);// Target API
	if ( bIsContained == false )
	{
		FPRINTF("[Line : %d][%s] location_bounds_contains_coordinates failed, error returned = %s\\n", __LINE__, API_NAMESPACE, LocationBoundsGetError(nRet));
		location_bounds_destroy(hPolyLocationBound);
		return 1;
	}

	bIsContained = false;
	nRet = location_bounds_destroy(hPolyLocationBound);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_destroy", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check the type of location bounds
//& type: auto
/**
* @testcase 			ITc_location_bounds_get_type_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto 
* @description			To check the type of location bounds
* @scenario				creates a polygon type of new location bounds and verify output\n
* 						check the generate location bound for null\n
* 						check the type of location bounds\n
* 						destroy a polygon type of new location bounds and verify output
* @apicovered			location_bounds_get_type, location_bounds_create_circle, location_bounds_destroy
* @passcase				When location_bounds_get_type and supporting APIs are successful
* @failcase				If target API or supporting APIs fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_bounds_get_type_p(void)
{
	START_TEST;

	location_bounds_h hCircleBounds = NULL;
	location_bounds_type_e eFindBoundsType = -1;
	location_coords_s sCenter;
	sCenter.latitude = 37.336723;
	sCenter.longitude = -121.889555;

	double dRadius = 30;

	location_bound_error_e nRet = location_bounds_create_circle(sCenter,dRadius, &hCircleBounds);
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_bounds_create_circle() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_create_circle", LocationBoundsGetError(nRet));
	CHECK_HANDLE(hCircleBounds, "location_bounds_create_circle");

	nRet = location_bounds_get_type(hCircleBounds, &eFindBoundsType);// Target API
	PRINT_RESULT_CLEANUP(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_get_type", LocationBoundsGetError(nRet), location_bounds_destroy(hCircleBounds));
	if ( eFindBoundsType != LOCATION_BOUNDS_CIRCLE )
	{
		FPRINTF("[Line : %d][%s] location_bounds_get_type failed, mismatch in location bounds type\\n", __LINE__, API_NAMESPACE);
		location_bounds_destroy(hCircleBounds);
		return 1;
	}

	nRet = location_bounds_destroy(hCircleBounds);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_destroy", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check whether the edges of the bounds contain the specified coordinates within tolerance.
//& type: auto
/**
* @testcase 			ITc_location_bounds_contains_coordinates_on_edge_p
* @since_tizen			6.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Checks whether the edges of the bounds contain the specified coordinates within tolerance.
* @scenario				creates a polygon type of new location bounds and verify output\n
*						check the generate location bound for null\n
*						check coordinates on polygon boundary within tolerance\n
*						destroy a polygon type of new location bounds and verify output
* @apicovered			location_bounds_contains_coordinates, location_bounds_create_polygon, location_bounds_destroy
* @passcase				When location_bounds_contains_coordinates_on_edge and supporting APIs are successful
* @failcase				If target API or supporting APIs fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_bounds_contains_coordinates_on_edge_p(void)
{
	START_TEST;

	location_bounds_h hPolyLocationBound = NULL;
	bool bIsContained = false;
	int nPolySize = 4;
	location_coords_s location_coord_list[nPolySize];
	location_coord_list[0].latitude = 28.581394;
	location_coord_list[0].longitude = 77.362621;
	location_coord_list[1].latitude = 28.580652;
	location_coord_list[1].longitude = 77.363302;
	location_coord_list[2].latitude = 28.580976;
	location_coord_list[2].longitude = 77.363771;
	location_coord_list[3].latitude = 28.581717;
	location_coord_list[3].longitude = 77.363032;

	location_coords_s testLocationCoordinates;
	testLocationCoordinates.latitude = 28.580723;
	testLocationCoordinates.longitude = 77.363666;
	location_bound_error_e nRet = location_bounds_create_polygon(location_coord_list, nPolySize, &hPolyLocationBound);
	if ( false == g_bIsLocationFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_bounds_create_polygon() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_create_polygon", LocationBoundsGetError(nRet));
	CHECK_HANDLE(hPolyLocationBound, "location_bounds_create_polygon");

	double dTolerance = 40;
	bIsContained = location_bounds_contains_coordinates_on_edge(hPolyLocationBound, testLocationCoordinates, dTolerance);
	if ( bIsContained == false )
	{
		FPRINTF("[Line : %d][%s] location_bounds_contains_coordinates_on_edge failed, bIsContained returned = false\\n", __LINE__, API_NAMESPACE);
		location_bounds_destroy(hPolyLocationBound);
		return 1;
	}

	bIsContained = false;
	nRet = location_bounds_destroy(hPolyLocationBound);
	PRINT_RESULT_NORETURN(LOCATION_BOUNDS_ERROR_NONE, nRet, "location_bounds_destroy", LocationBoundsGetError(nRet));

	return 0;
}
/** @} */
/** @} */
