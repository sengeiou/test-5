//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-capi-maps-service-common.h"

#include <app.h>
#include <string.h>
#include "assert.h"
#include <maps_view.h>
#include <maps_service.h>
#include <maps_error.h>
#include <unistd.h>
#include <glib.h>
#include <Evas.h>

static bool gCheckCb = false;

static bool MapsViewObjectCoordinateCB(int index, maps_coordinates_h coordinates, void *user_data)
{
	FPRINTF("\nEntered Callback MapsViewObjectCoordinateCB \n");
	gCheckCb = true;
	return true;
}


/** @addtogroup itc-maps-service
*  @ingroup itc
*  @{
*/


/**
 * @function 		ITs_maps_view_object_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 

void ITs_maps_view_object_startup(void)
{
	struct stat stBuff;   
	
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	return;
}

/**
 * @function		ITs_maps_view_object_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void ITs_maps_view_object_cleanup(void)
{
	return;
}


/** @addtogroup itc-maps-service-testcases
*  @brief 		Integration testcases for module maps-service
*  @ingroup 	itc-maps-service
*  @{
*/

//& type: auto
//& purpose:  scenario to create and destroy a new maps view
/**
* @testcase 			ITc_maps_view_object_create_marker_destroy_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Creates a Marker visual object.
* @scenario				This function creates a hMarker on a given geographical coordinates.\n
* 						The hMarker is specified with a given image file and a type.
* @apicovered			maps_view_object_create_marker, maps_view_object_destroy
* @passcase				if maps_view_object_create_marker and maps_view_object_destroy passes
* @failcase				if maps_view_object_create_marker or maps_view_object_destroy fails
* @precondition			map_coordinates_create
* @postcondition		NA
*/
int ITc_maps_view_object_create_marker_destroy_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hMarker = NULL;
	double dX = 0.0, dY = 0.0;
	int  nRet, nLoopCount = 0;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	maps_view_marker_type_e eMapViewMarkerType[] = {MAPS_VIEW_MARKER_PIN, MAPS_VIEW_MARKER_STICKER};
	int nMapViewMarkerArraySize = sizeof(eMapViewMarkerType) / sizeof(eMapViewMarkerType[0]);
	
	gCheckBool = GetResourceDataPath();
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	for(nLoopCount = 0; nLoopCount < nMapViewMarkerArraySize; nLoopCount++)
	{
		nRet = maps_coordinates_create(dX, dY, &hCoord);
		if ( false == bMapsFeatureSupported)
		{
			if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
				return 1;
			}
			else
			{
				FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
				return 0;
			}
		}
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
		CHECK_HANDLE(hCoord, "maps_coordinates_create");

		nRet = maps_view_object_create_marker(hCoord, gszImagePath, eMapViewMarkerType[nLoopCount], &hMarker);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
		CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord));

		nRet = maps_view_object_destroy(hMarker);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	}	
	return 0;
}

//& type: auto
//& purpose:  scenario to create Polyline object
/**
* @testcase 			ITc_maps_view_object_create_polyline_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Creates a Polyline visual object.
* @scenario				This function creates a hPolyline visual object, specified\n
* 						with a list of geographical coordinates, line width and color.
* @apicovered			maps_view_object_create_polyline
* @passcase				if maps_view_object_create_polyline passes
* @failcase				if maps_view_object_create_polyline fails
* @precondition			maps_coordinates_list_create
* @postcondition		NA
*/
int ITc_maps_view_object_create_polyline_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL;
	maps_coordinates_list_h hCoord_list = NULL;
	maps_view_object_h hPolyline = NULL;
	
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	int nWidth = 1;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord1, "maps_coordinates_create");

	nRet = maps_coordinates_create(dX2, dY2, &hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord2, "maps_coordinates_create", maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list, "maps_coordinates_create", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_view_object_create_polyline(hCoord_list, cRed, cGreen, cBlue, cAlpha, nWidth, &hPolyline);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_polyline", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));	
	CHECK_HANDLE_CLEANUP(hPolyline, "maps_view_object_create_polyline", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_view_object_destroy(hPolyline);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));	

	return 0;
}

//& type: auto
//& purpose:  scenario to create Polygon object
/**
* @testcase 			ITc_maps_view_object_create_polygon_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Create a hPolygon visual object.
* @scenario				This function creates a Polygon visual object, specified\n
* 						with a list of geographical coordinates and fill color.
* @apicovered			maps_view_object_create_polygon
* @passcase				if maps_view_object_create_polygon passes
* @failcase				if maps_view_object_create_polygon fails
* @precondition			maps_coordinates_list_create
* @postcondition		NA
*/
int ITc_maps_view_object_create_polygon_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL, hCoord3 = NULL;
	maps_coordinates_list_h hCoord_list = NULL;
	maps_view_object_h hPolygon = NULL;
	
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord1, "maps_coordinates_create");

	nRet = maps_coordinates_create(dX2, dY2, &hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord2, "maps_coordinates_create", maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_create(dX2, dY1, &hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord3, "maps_coordinates_create", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list, "maps_coordinates_list_create", maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_view_object_create_polygon(hCoord_list, cRed, cGreen, cBlue, cAlpha, &hPolygon);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_polygon", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hPolygon, "maps_view_object_create_polygon", maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_view_object_destroy(hPolygon);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to create and Gets the object type.
/**
* @testcase 			ITc_maps_view_object_get_type_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the object type.
* @scenario				This function gets the object type.
* @apicovered			maps_view_object_get_type
* @passcase				if maps_view_object_get_type passes
* @failcase				if maps_view_object_get_type fails
* @precondition			object is created using maps_view_object_create_marker(),\n
*						maps_view_object_create_polyline() or maps_view_object_create_polygon().
* @postcondition		NA
*/
int ITc_maps_view_object_get_type_p(void)
{
	START_TEST_OBJECT;
	maps_view_object_h hMarker = NULL;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_type_e hType = -1;
	double dX = 0.0, dY = 0.0;
	
	gCheckBool = GetResourceDataPath();
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");
	
	nRet = maps_view_object_create_marker(hCoord, gszImagePath, MAPS_VIEW_MARKER_PIN, &hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord));
	
	nRet = maps_view_object_get_type(hMarker, &hType);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_get_type", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));
	if(hType == -1)
	{
		FPRINTF("[Line : %d][%s] maps_view_object_get_type FAILS \\n", __LINE__, API_NAMESPACE);
		
		nRet = maps_view_object_destroy(hMarker);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
		return 1;
	}
	
	nRet = maps_view_object_destroy(hMarker);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the object.
/**
* @testcase 			ITc_maps_view_object_set_get_visible_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			This function changes the visibility of the given object on the View.
* @scenario				Sets and gets the object visibility.
* @apicovered			maps_view_object_set_visible, maps_view_object_get_visible
* @passcase				if maps_view_object_set_visible and maps_view_object_get_visible passes
* @failcase				if maps_view_object_set_visible or maps_view_object_get_visible fails
* @precondition			object is created using maps_view_object_create_marker(),\n
*						maps_view_object_create_polyline() or maps_view_object_create_polygon().
* @postcondition		NA
*/
int ITc_maps_view_object_set_get_visible_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hMarker = NULL;
	double dX = 0.0, dY = 0.0;
	bool setVisible = false, getVisible = true;
	
	gCheckBool = GetResourceDataPath();
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");

	nRet = maps_view_object_create_marker(hCoord, gszImagePath, MAPS_VIEW_MARKER_PIN, &hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord));
	
	nRet = maps_view_object_set_visible(hMarker, setVisible);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_set_visible", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));

	nRet = maps_view_object_get_visible(hMarker, &getVisible);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_get_visible", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));
	if(setVisible != getVisible)
	{
		FPRINTF("maps_view_object_get_visible and maps_view_object_set_visible FAILS \n");
		
		nRet = maps_view_object_destroy(hMarker);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));	
	
		return 1;
	}

	nRet = maps_view_object_destroy(hMarker);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to Retrieves all points, added to the hPolyline.
/**
* @testcase 			ITc_maps_view_object_polyline_foreach_point_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Retrieves all points, added to the hPolyline.
* @scenario				This function retrieves all points, added to the hPolyline.
* @apicovered			maps_view_object_polyline_foreach_point
* @passcase				if maps_view_object_polyline_foreach_point passes
* @failcase				if maps_view_object_polyline_foreach_point fails
* @precondition			hPolyline is created using maps_view_object_create_polyline().
* @postcondition		This function invokes maps_view_object_polyline_point_cb() repeatedly to\n
* 						retrieve each point.
*/
int ITc_maps_view_object_polyline_foreach_point_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL;
	maps_coordinates_list_h hCoord_list = NULL;
	maps_view_object_h hPolyline = NULL;
	
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	int nWidth = 1;
	gCheckCb = false;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord1, "maps_coordinates_create");

	nRet = maps_coordinates_create(dX2, dY2, &hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord2, "maps_coordinates_create", maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list, "maps_coordinates_list_create", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_view_object_create_polyline(hCoord_list, cRed, cGreen, cBlue, cAlpha, nWidth, &hPolyline);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_polyline", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));	
	CHECK_HANDLE_CLEANUP(hPolyline, "maps_view_object_create_polyline", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_view_object_polyline_foreach_point(hPolyline, MapsViewObjectCoordinateCB, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_polyline_foreach_point", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));		
	if(gCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked \\n", __LINE__, API_NAMESPACE);
		
		nRet = maps_view_object_destroy(hPolyline);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));	
		
		return 1;
	}
	
	nRet = maps_view_object_destroy(hPolyline);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));	
	
	return 0;
}


//& type: auto
//& purpose:  scenario to Sets points to the hPolyline.
/**
* @testcase 			ITc_maps_view_object_polyline_set_polyline_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets points to the Polyline.
* @scenario				This function sets point list to the hPolyline.
* @apicovered			maps_view_object_polyline_set_polyline
* @passcase				if maps_view_object_polyline_set_polyline passes
* @failcase				if maps_view_object_polyline_set_polyline fails
* @precondition			hPolyline is created using maps_view_object_create_polyline(),\n
*						points are created using maps_coordinates_list_create().
* @postcondition		Previous points will be destroyed automatically.
*/
int ITc_maps_view_object_polyline_set_polyline_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL, hCoord3 = NULL, hCoord4 = NULL;
	maps_coordinates_list_h hCoord_list1 = NULL, hCoord_list2 = NULL;
	maps_view_object_h hPolyline = NULL;
	
	double dX1 = 0.0, dX2 = 10.0, dX3 = 5.0, dX4 = 15.0, dY1 = 0.0, dY2 = 10.0, dY3 = 5.0, dY4 = 15.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	int nWidth = 1;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord1, "maps_coordinates_create");

	nRet = maps_coordinates_create(dX2, dY2, &hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord2, "maps_coordinates_create", maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list1, "maps_coordinates_list_create", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list1, hCoord1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list1, hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_create(dX3, dY3, &hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord3, "maps_coordinates_create", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_create(dX4, dY4, &hCoord4);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord4, "maps_coordinates_create", maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list2, "maps_coordinates_list_create", maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_append(hCoord_list2, hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list2, hCoord4);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_view_object_create_polyline(hCoord_list1, cRed, cGreen, cBlue, cAlpha, nWidth, &hPolyline);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_polyline", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));	
	CHECK_HANDLE_CLEANUP(hPolyline, "maps_view_object_create_polyline", maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
		
	nRet = maps_view_object_polyline_set_polyline(hPolyline, hCoord_list2);	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_polyline_set_polyline", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));	
		
	nRet = maps_view_object_destroy(hPolyline);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));	

	return 0;
}

//& type: auto
//& purpose:  scenario to Set and Get the hPolyline color.
/**
* @testcase 			ITc_maps_view_object_polyline_set_get_color_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and Gets the Polyline color.
* @scenario				This function sets and gets the Polyline color on canvas.
* @apicovered			maps_view_object_polyline_set_color, maps_view_object_polyline_get_color
* @passcase				if maps_view_object_polyline_set_color and maps_view_object_polyline_get_color passes
* @failcase				if maps_view_object_polyline_set_color or maps_view_object_polyline_get_color fails
* @precondition			hPolyline is created using maps_view_object_create_polyline().\n
*						color components may be previously set using maps_view_object_polyline_set_color().
* @postcondition		NA
*/
int ITc_maps_view_object_polyline_set_get_color_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL;
	maps_coordinates_list_h hCoord_list = NULL;
	maps_view_object_h hPolyline = NULL;
	
	unsigned char cSetRed = '2', cSetGreen = '2', cSetBlue = '2', cSetAlpha = '2';
	unsigned char cGetRed, cGetGreen, cGetBlue, cGetAlpha;
	
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	int nWidth = 1;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord1, "maps_coordinates_create");

	nRet = maps_coordinates_create(dX2, dY2, &hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord2, "maps_coordinates_create", maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list, "maps_coordinates_list_create", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_view_object_create_polyline(hCoord_list, cRed, cGreen, cBlue, cAlpha, nWidth, &hPolyline);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_polyline", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));	
	CHECK_HANDLE_CLEANUP(hPolyline, "maps_view_object_create_polyline", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_view_object_polyline_set_color(hPolyline, cSetRed, cSetGreen, cSetBlue, cSetAlpha);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_polyline_set_color", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));

	nRet = maps_view_object_polyline_get_color(hPolyline, &cGetRed, &cGetGreen, &cGetBlue, &cGetAlpha);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_polyline_get_color", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));	
	if(cGetRed != cSetRed || cGetGreen != cSetGreen || cGetBlue != cSetBlue || cGetAlpha != cSetAlpha)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		nRet = maps_view_object_destroy(hPolyline);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));	

		return 1;
	}
	
	nRet = maps_view_object_destroy(hPolyline);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));	

	return 0;
}

//& type: auto
//& purpose:  scenario to Set and Get the hPolyline width.
/**
* @testcase 			ITc_maps_view_object_polyline_set_get_width_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and Gets the Polyline width on canvas
* @scenario				This function sets and gets the Polyline width on canvas.
* @apicovered			maps_view_object_polyline_set_width, maps_view_object_polyline_get_width
* @passcase				if maps_view_object_polyline_set_width and maps_view_object_polyline_get_width passes
* @failcase				if maps_view_object_polyline_set_width or maps_view_object_polyline_get_width fails
* @precondition			hPolyline is created using maps_view_object_create_polyline().\n
*						width may be previously set using maps_view_object_polyline_set_width().
* @postcondition		NA
*/
int ITc_maps_view_object_polyline_set_get_width_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL;
	maps_coordinates_list_h hCoord_list = NULL;
	maps_view_object_h hPolyline = NULL;
	
	int nSetWidth = 2, nGetWidth;
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	int nWidth = 1;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord1, "maps_coordinates_create");

	nRet = maps_coordinates_create(dX2, dY2, &hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord2, "maps_coordinates_create", maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list, "maps_coordinates_list_create", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_view_object_create_polyline(hCoord_list, cRed, cGreen, cBlue, cAlpha, nWidth, &hPolyline);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_polyline", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));	
	CHECK_HANDLE_CLEANUP(hPolyline, "maps_view_object_create_polyline", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_view_object_polyline_set_width(hPolyline, nSetWidth);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_polyline_set_width", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));
	
	nRet = maps_view_object_polyline_get_width(hPolyline, &nGetWidth);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_polyline_get_width", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));
	if(nGetWidth != nSetWidth)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		nRet = maps_view_object_destroy(hPolyline);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));	

		return 1;
	}
	
	nRet = maps_view_object_destroy(hPolyline);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));	

	return 0;
}

//& type: auto
//& purpose:  scenario to Sets points to the hPolygon.
/**
* @testcase 			ITc_maps_view_object_polygon_set_polygon_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets points to the Polygon.
* @scenario				This function sets point list to the Polygon.
* @apicovered			maps_view_object_polygon_set_polygon
* @passcase				if maps_view_object_polygon_set_polygon passes
* @failcase				if maps_view_object_polygon_set_polygon fails
* @precondition			hPolygon is created using maps_view_object_create_polygon().points are created using maps_coordinates_list_create().
* @postcondition		NA
*/
int ITc_maps_view_object_polygon_set_polygon_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL, hCoord3 = NULL, hCoord4 = NULL, hCoord5 = NULL, hCoord6 = NULL;
	maps_coordinates_list_h hCoord_list1 = NULL, hCoord_list2 = NULL;
	maps_view_object_h hPolygon = NULL;
	
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0, dY3 = 1.0, dY4 = 11.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord1, "maps_coordinates_create");

	nRet = maps_coordinates_create(dX2, dY2, &hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord2, "maps_coordinates_create", maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_create(dX2, dY1, &hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord3, "maps_coordinates_create", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_create(dX1, dY3, &hCoord4);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord4, "maps_coordinates_create", maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_create(dX2, dY4, &hCoord5);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord5, "maps_coordinates_create", maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_create(dX2, dY3, &hCoord6);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord6, "maps_coordinates_create", maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list1, "maps_coordinates_list_create", maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list1, hCoord1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list1, hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list1, hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list2, "maps_coordinates_list_create", maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_append(hCoord_list2, hCoord4);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_append(hCoord_list2, hCoord5);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_append(hCoord_list2, hCoord6);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_view_object_create_polygon(hCoord_list1, cRed, cGreen, cBlue, cAlpha, &hPolygon);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_polygon", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hPolygon, "maps_view_object_create_polygon", maps_coordinates_destroy(hCoord6); maps_coordinates_destroy(hCoord5); maps_coordinates_destroy(hCoord4); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_view_object_polygon_set_polygon(hPolygon, hCoord_list2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_polygon_set_polygon", MapServiceGetError(nRet), maps_view_object_destroy(hPolygon));
	
	nRet = maps_view_object_destroy(hPolygon);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to Retrieves all points, added to the hPolygon.
/**
* @testcase 			ITc_maps_view_object_polygon_foreach_point_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Retrieves all points, added to the Polygon.
* @scenario				This function retrieves all points, added to the hPolygon.
* @apicovered			maps_view_object_polygon_foreach_point
* @passcase				if maps_view_object_polygon_foreach_point passes
* @failcase				if maps_view_object_polygon_foreach_point fails
* @precondition			hPolygon is created using maps_view_object_create_polygon().
* @postcondition		This function invokes maps_view_object_polygon_point_cb() repeatedly to \n
* 						retrieve each point.
*/
int ITc_maps_view_object_polygon_foreach_point_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL, hCoord3 = NULL;
	maps_coordinates_list_h hCoord_list = NULL;
	maps_view_object_h hPolygon = NULL;
	
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	gCheckCb = false;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord1, "maps_coordinates_create");

	nRet = maps_coordinates_create(dX2, dY2, &hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord2, "maps_coordinates_create", maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_create(dX2, dY1, &hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord3, "maps_coordinates_create", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list, "maps_coordinates_list_create", maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_view_object_create_polygon(hCoord_list, cRed, cGreen, cBlue, cAlpha, &hPolygon);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_polygon", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hPolygon, "maps_view_object_create_polygon", maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_view_object_polygon_foreach_point(hPolygon, MapsViewObjectCoordinateCB, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_polygon_foreach_point", MapServiceGetError(nRet), maps_view_object_destroy(hPolygon));
	if(gCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked \\n", __LINE__, API_NAMESPACE);
		
		nRet = maps_view_object_destroy(hPolygon);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
		
		return 1;
	}
	
	nRet = maps_view_object_destroy(hPolygon);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get hPolygon fill color.
/**
* @testcase 			ITc_maps_view_object_polygon_set_get_fill_color_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and Gets Polygon fill color.
* @scenario				This function sets and gets the hPolygon fill color on canvas.
* @apicovered			maps_view_object_polygon_set_fill_color, maps_view_object_polygon_get_fill_color
* @passcase				if maps_view_object_polygon_set_fill_color and maps_view_object_polygon_get_fill_color passes
* @failcase				if maps_view_object_polygon_set_fill_color or maps_view_object_polygon_get_fill_color fails
* @precondition			hPolygon is created using maps_view_object_create_polygon().\n
* 						fill color components may be previously set using maps_view_object_polygon_set_fill_color().
* @postcondition		NA
*/
int ITc_maps_view_object_polygon_set_get_fill_color_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL, hCoord3 = NULL;
	maps_coordinates_list_h hCoord_list = NULL;
	maps_view_object_h hPolygon = NULL;
	unsigned char cSetRed = '2', cSetGreen = '2', cSetBlue = '2', cSetAlpha = '2';
	unsigned char cGetRed, cGetGreen, cGetBlue, cGetAlpha;
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord1, "maps_coordinates_create");

	nRet = maps_coordinates_create(dX2, dY2, &hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord2, "maps_coordinates_create", maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_create(dX2, dY1, &hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord3, "maps_coordinates_create", maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_coordinates_list_create(&hCoord_list);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord_list, "maps_coordinates_list_create", maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord1);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_coordinates_list_append(hCoord_list, hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));

	nRet = maps_view_object_create_polygon(hCoord_list, cRed, cGreen, cBlue, cAlpha, &hPolygon);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_polygon", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hPolygon, "maps_view_object_create_polygon", maps_coordinates_destroy(hCoord3); maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	
	nRet = maps_view_object_polygon_set_fill_color(hPolygon, cSetRed, cSetGreen, cSetBlue, cSetAlpha);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_polygon_set_fill_color", MapServiceGetError(nRet), maps_view_object_destroy(hPolygon));
	
	nRet = maps_view_object_polygon_get_fill_color(hPolygon, &cGetRed, &cGetGreen, &cGetBlue, &cGetAlpha);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_polygon_get_fill_color", MapServiceGetError(nRet), maps_view_object_destroy(hPolygon));
	if(cGetRed != cSetRed || cGetGreen != cSetGreen || cGetBlue != cSetBlue || cGetAlpha != cSetAlpha)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		
		nRet = maps_view_object_destroy(hPolygon);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));	

		return 1;
	}
		
	nRet = maps_view_object_destroy(hPolygon);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to sets and get the hMarker coordinates.
/**
* @testcase 			ITc_maps_view_object_marker_set_get_coordinates_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and gets the Marker coordinates.
* @scenario				This function sets and gets the hMarker geographical coordinates.
* @apicovered			maps_view_object_marker_set_coordinates, maps_view_object_marker_get_coordinates
* @passcase				if maps_view_object_marker_set_coordinates and maps_view_object_marker_get_coordinates passes
* @failcase				if maps_view_object_marker_set_coordinates or maps_view_object_marker_get_coordinates fails
* @precondition			hMarker is created using maps_view_object_create_marker().\n
* 						coordinates may be set previously using maps_view_object_marker_set_coordinates().
* @postcondition		NA
*/
int ITc_maps_view_object_marker_set_get_coordinates_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL, hCoord3 = NULL;
	maps_view_object_h hMarker = NULL;
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
		
	gCheckBool = GetResourceDataPath();
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord1, "maps_coordinates_create");
	
	nRet = maps_coordinates_create(dX2, dY2, &hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hCoord2, "maps_coordinates_create", maps_coordinates_destroy(hCoord1));

	nRet = maps_view_object_create_marker(hCoord1, gszImagePath, MAPS_VIEW_MARKER_PIN, &hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord2); maps_coordinates_destroy(hCoord1));
	CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord1));
		
	nRet = maps_view_object_marker_set_coordinates(hMarker, hCoord2);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_marker_set_coordinates", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));	

	nRet = maps_view_object_marker_get_coordinates(hMarker, &hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_marker_get_coordinates", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));	
	CHECK_HANDLE_CLEANUP(hCoord3, "maps_view_object_marker_get_coordinates", maps_view_object_destroy(hMarker));
	
	nRet = maps_view_object_destroy(hMarker);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to Set the Marker screen size.
/**
* @testcase 			ITc_maps_view_object_marker_resize_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Set the Marker screen size.
* @scenario				This function sets the Marker screen size.
* @apicovered			maps_view_object_marker_resize
* @passcase				if maps_view_object_marker_resize passes
* @failcase				if maps_view_object_marker_resize fails
* @precondition			hMarker is created using maps_view_object_create_marker().
* @postcondition		NA
*/
int ITc_maps_view_object_marker_resize_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hMarker = NULL;
	double dX = 0.0, dY = 0.0;
	int nWidth = 10, nHeight = 10;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);

	gCheckBool = GetResourceDataPath();
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");

	nRet = maps_view_object_create_marker(hCoord, gszImagePath, MAPS_VIEW_MARKER_PIN, &hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord));
	
	nRet = maps_view_object_marker_resize(hMarker, nWidth, nHeight);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_marker_resize", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));	

	nRet = maps_view_object_destroy(hMarker);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to Set and get the Marker image file path.
/**
* @testcase 			ITc_maps_view_object_marker_set_get_image_file_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and gets the Marker image file path.
* @scenario				This function sets and gets the hMarker image file path.
* @apicovered			maps_view_object_marker_set_image_file, maps_view_object_marker_get_image_file
* @passcase				if maps_view_object_marker_set_image_file and maps_view_object_marker_get_image_file passes
* @failcase				if maps_view_object_marker_set_image_file or maps_view_object_marker_get_image_file fails
* @precondition			hMarker is created using maps_view_object_create_marker().\n
*						file_path may be set previously using maps_view_object_marker_set_image_file().
* @postcondition		NA
*/
int ITc_maps_view_object_marker_set_get_image_file_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hMarker = NULL;
	double dX = 0.0, dY = 0.0;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	gCheckBool = GetResourceDataPath();
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	char *pzFilePath = NULL;
	char szNewFilePath[BUFF_LEN] = {0, };
	char *pszResPath = app_get_resource_path();
	if (pszResPath) {
		snprintf(szNewFilePath, BUFF_LEN, "%s%s", pszResPath, NEW_IMAGE_FILENAME);
		FREE_MEMORY_TC(pszResPath);
	}
	else
	{
		FPRINTF("\nIMAGE PATH is NULL \n");
		return 1;
	}
	
	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");

	nRet = maps_view_object_create_marker(hCoord, gszImagePath, MAPS_VIEW_MARKER_PIN, &hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord));
		
	nRet = maps_view_object_marker_set_image_file(hMarker, szNewFilePath);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_marker_set_image_file", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));

	nRet = maps_view_object_marker_get_image_file(hMarker, &pzFilePath);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_marker_get_image_file", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));
	CHECK_HANDLE_CLEANUP(pzFilePath, "maps_view_object_marker_get_image_file", maps_view_object_destroy(hMarker));
	if(0 != strcmp(szNewFilePath,pzFilePath))
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = maps_view_object_destroy(hMarker);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to get the Marker screen size.
/**
* @testcase 			ITc_maps_view_object_marker_get_size_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the hMarker screen size.
* @scenario				This function gets the Marker size on the screen.
* @apicovered			maps_view_object_marker_get_size
* @passcase				if maps_view_object_marker_get_size passes
* @failcase				if maps_view_object_marker_get_size fails
* @precondition			hMarker is created using maps_view_object_create_marker().\n
*						width and height may be set previously using maps_view_object_marker_resize().
* @postcondition		NA
*/
int ITc_maps_view_object_marker_get_size_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hMarker = NULL;
	double dX = 0.0, dY = 0.0;
	int nWidth = 10, nHeight = 10;
	int nGetWidth, nGetHeight;
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	gCheckBool = GetResourceDataPath();
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");

	nRet = maps_view_object_create_marker(hCoord, gszImagePath, MAPS_VIEW_MARKER_PIN, &hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord));
	
	nRet = maps_view_object_marker_resize(hMarker, nWidth, nHeight);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_marker_resize", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));	
	
	nRet = maps_view_object_marker_get_size(hMarker, &nGetWidth, &nGetHeight);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_marker_get_size", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));	
	if(nGetWidth != nWidth || nGetHeight != nHeight)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		
		nRet = maps_view_object_destroy(hMarker);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
		return 1;
	}
	
	nRet = maps_view_object_destroy(hMarker);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to get the Marker type.
/**
* @testcase 			ITc_maps_view_object_marker_get_type_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the Marker type.
* @scenario				This function gets the Marker type.
* @apicovered			maps_view_object_marker_get_type
* @passcase				if maps_view_object_marker_get_type passes
* @failcase				if maps_view_object_marker_get_type fails
* @precondition			hMarker is created using maps_view_object_create_marker().
* @postcondition		NA
*/
int ITc_maps_view_object_marker_get_type_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hMarker = NULL;
	double dX = 0.0, dY = 0.0;
	
	maps_view_marker_type_e marker_type = -1;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	gCheckBool = GetResourceDataPath();
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");

	nRet = maps_view_object_create_marker(hCoord, gszImagePath, MAPS_VIEW_MARKER_PIN, &hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord));
	
	nRet = maps_view_object_marker_get_type(hMarker, &marker_type);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_marker_get_type", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));
	if(marker_type == -1)
	{
		FPRINTF("[Line : %d][%s] maps_view_object_marker_get_type FAILS \\n", __LINE__, API_NAMESPACE);
		
		nRet = maps_view_object_destroy(hMarker);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
		return 1;
	}
		
	nRet = maps_view_object_destroy(hMarker);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the Marker z-order.
/**
* @testcase 			ITc_maps_view_object_marker_set_get_z_order_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and gets the Marker z-order.
* @scenario				This function sets and gets the z-order.
* @apicovered			maps_view_object_marker_set_z_order, maps_view_object_marker_get_z_order
* @passcase				if maps_view_object_marker_set_z_order  and maps_view_object_marker_get_z_order passes
* @failcase				if maps_view_object_marker_set_z_order or maps_view_object_marker_get_z_order fails
* @precondition			hMarker is created using maps_view_object_create_marker().
* @postcondition		NA
*/
int ITc_maps_view_object_marker_set_get_z_order_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hMarker = NULL;
	double dX = 0.0, dY = 0.0;
	int nSetZOrder = 0, nGetZOrder = -1;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	gCheckBool = GetResourceDataPath();
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");

	nRet = maps_view_object_create_marker(hCoord, gszImagePath, MAPS_VIEW_MARKER_PIN, &hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord));

	nRet = maps_view_object_marker_set_z_order(hMarker, nSetZOrder);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_marker_set_z_order", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));
	
	nRet = maps_view_object_marker_get_z_order(hMarker, &nGetZOrder);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_marker_get_z_order", MapServiceGetError(nRet), maps_view_object_destroy(hMarker));
	if(nGetZOrder != nSetZOrder)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		
		nRet = maps_view_object_destroy(hMarker);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
		return 1;
	}
	
	nRet = maps_view_object_destroy(hMarker);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  Creates a overlay object.
/**
* @testcase 			ITc_maps_view_object_create_overlay_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Creates a overlay object.
* @scenario				Creates a overlay object.
* @apicovered			maps_coordinates_create, maps_view_object_create_overlay
* @passcase				if maps_view_object_create_overlay and its precondition API passes
* @failcase				if maps_view_object_create_overlay or its precondition API fails
* @precondition			NA().
* @postcondition		NA
*/
int ITc_maps_view_object_create_overlay_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hOverlay = NULL;
	double dX = 0.0, dY = 0.0;
	int nLoopCount;
	elm_init(0, NULL);
	elm_config_accel_preference_set("opengl");
	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	
	Evas_Object * win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	elm_win_autodel_set(win, TRUE);
	
	Evas_Object *object = elm_button_add(win);
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	
	maps_view_overlay_type_e eMapViewOverlayType[] = {  MAPS_VIEW_OVERLAY_NORMAL,	/**< Indicates the normal type */
													MAPS_VIEW_OVERLAY_BUBBLE,	/**< Indicates the bubble type */
														MAPS_VIEW_OVERLAY_BOX};		/**< Indicates the box type */

	int nMapViewOverlayArraySize = sizeof(eMapViewOverlayType) / sizeof(eMapViewOverlayType[0]);
	
	
	
	for(nLoopCount = 0; nLoopCount < nMapViewOverlayArraySize; nLoopCount++)
	{
		int nRet = maps_coordinates_create(0.0,0.0, &hCoord);
		if ( false == bMapsFeatureSupported)
		{
			if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
				return 1;
			}
			else
			{
				FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
				return 0;
			}
		}
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
		CHECK_HANDLE(hCoord, "maps_coordinates_create");
		
		nRet = maps_view_object_create_overlay(hCoord, object, eMapViewOverlayType[nLoopCount], &hOverlay);

		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_overlay", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
		CHECK_HANDLE_CLEANUP(hOverlay, "maps_view_object_create_overlay", maps_coordinates_destroy(hCoord));
			
		nRet = maps_view_object_destroy(hOverlay);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	}
	elm_shutdown();
	win = NULL;
	
	return 0;
}

//& type: auto
//& purpose:  Gets the Evas object.
/**
* @testcase 			ITc_maps_view_object_overlay_get_object_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Gets the Evas object.
* @scenario				Creates a overlay object.
*  						Gets the Evas object.
* @apicovered			maps_coordinates_create, maps_view_object_create_overlay, maps_view_object_overlay_get_object
* @passcase				if maps_view_object_overlay_get_object and its precondition API passes
* @failcase				if maps_view_object_overlay_get_object or its precondition API fails
* @precondition			NA.
* @postcondition		NA
*/
int ITc_maps_view_object_overlay_get_object_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hOverlay = NULL;
	Evas_Object *win = NULL;
	
	Evas_Object *getObject = NULL;
	maps_view_overlay_type_e eOverlayType = MAPS_VIEW_OVERLAY_NORMAL;
	double dX = 0.0, dY = 0.0;
	
	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	elm_win_autodel_set(win, TRUE);
	Evas_Object *object = elm_button_add(win);
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");
	
	nRet = maps_view_object_create_overlay(hCoord, object, eOverlayType, &hOverlay);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_overlay", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hOverlay, "maps_view_object_create_overlay", maps_coordinates_destroy(hCoord));
		
	nRet = maps_view_object_overlay_get_object(hOverlay, &getObject);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_overlay_get_object", MapServiceGetError(nRet), maps_view_object_destroy(hOverlay);maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(getObject, "maps_view_object_overlay_get_object", maps_view_object_destroy(hOverlay);maps_coordinates_destroy(hCoord));
	
	nRet = maps_view_object_destroy(hOverlay);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  Sets and gets the overlay coordinates.
/**
* @testcase 			ITc_maps_view_object_overlay_set_get_coordinates_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and gets the overlay coordinates.
* @scenario				Creates a overlay object.
*  						Sets and gets the overlay coordinates.
* @apicovered			maps_coordinates_create, maps_view_object_create_overlay, maps_view_object_overlay_set_coordinates, maps_view_object_overlay_get_coordinates
* @passcase				if maps_view_object_overlay_set_coordinates and maps_view_object_overlay_get_coordinates and its precondition API passes
* @failcase				if maps_view_object_overlay_set_coordinates or maps_view_object_overlay_get_coordinates or its precondition API fails
* @precondition			NA.
* @postcondition		NA
*/
int ITc_maps_view_object_overlay_set_get_coordinates_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_coordinates_h hGetCoord = NULL;
	maps_view_object_h hOverlay = NULL;
	Evas_Object *win = NULL;
	maps_view_overlay_type_e eOverlayType = MAPS_VIEW_OVERLAY_NORMAL;
	double dX = 0.0, dY = 0.0;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	elm_win_autodel_set(win, TRUE);
	Evas_Object *object = elm_button_add(win);
	
	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");
	
	nRet = maps_view_object_create_overlay(hCoord, object, eOverlayType, &hOverlay);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_overlay", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hOverlay, "maps_view_object_create_overlay", maps_coordinates_destroy(hCoord));
		
	nRet = maps_view_object_overlay_set_coordinates(hOverlay, hCoord);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_overlay_set_coordinates", MapServiceGetError(nRet), maps_view_object_destroy(hOverlay);maps_coordinates_destroy(hCoord));
	
	nRet = maps_view_object_overlay_get_coordinates(hOverlay, &hGetCoord);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_overlay_get_coordinates", MapServiceGetError(nRet), maps_view_object_destroy(hOverlay);maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hGetCoord, "maps_view_object_overlay_get_coordinates", maps_view_object_destroy(hOverlay);maps_coordinates_destroy(hCoord));
	
	nRet = maps_view_object_destroy(hOverlay);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));
	
	nRet = maps_coordinates_destroy(hGetCoord);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  Sets and gets the minimal zoom level for overlay.
/**
* @testcase 			ITc_maps_view_object_overlay_set_get_min_zoom_level_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and gets the minimal zoom level for overlay.
* @scenario				Creates a overlay object.
*  						Sets and gets the minimal zoom level for overlay.
* @apicovered			maps_coordinates_create, maps_view_object_create_overlay, maps_view_object_overlay_set_min_zoom_level, maps_view_object_overlay_get_min_zoom_level
* @passcase				if maps_view_object_overlay_set_min_zoom_level and maps_view_object_overlay_get_min_zoom_level and its precondition API passes
* @failcase				if maps_view_object_overlay_set_min_zoom_level or maps_view_object_overlay_get_min_zoom_level or its precondition API fails
* @precondition			NA.
* @postcondition		NA
*/
int ITc_maps_view_object_overlay_set_get_min_zoom_level_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hOverlay = NULL;
	Evas_Object *win = NULL;
	maps_view_overlay_type_e eOverlayType = MAPS_VIEW_OVERLAY_NORMAL;
	double dX = 0.0, dY = 0.0;
	int nSetZoomLevel = 2;
	int nGetZoomLevel;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);

	elm_init(0, NULL);
	elm_config_accel_preference_set("opengl");

	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	elm_win_autodel_set(win, TRUE);
	Evas_Object *object = elm_button_add(win);

	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");
	
	nRet = maps_view_object_create_overlay(hCoord, object, eOverlayType, &hOverlay);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_overlay", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hOverlay, "maps_view_object_create_overlay", maps_coordinates_destroy(hCoord));
		
	nRet = maps_view_object_overlay_set_min_zoom_level(hOverlay, nSetZoomLevel);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_overlay_set_min_zoom_level", MapServiceGetError(nRet), maps_view_object_destroy(hOverlay);maps_coordinates_destroy(hCoord));
	
	nRet = maps_view_object_overlay_get_min_zoom_level(hOverlay, &nGetZoomLevel);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_overlay_get_min_zoom_level", MapServiceGetError(nRet), maps_view_object_destroy(hOverlay);maps_coordinates_destroy(hCoord));
	if(nSetZoomLevel != nGetZoomLevel)
	{
		FPRINTF("[Line : %d][%s] Mismatch in set and get zoom level \\n", __LINE__, API_NAMESPACE);
		maps_view_object_destroy(hOverlay);
		return 1;
	}
	
	nRet = maps_view_object_destroy(hOverlay);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  Sets and gets the maximum zoom level for overlay.
/**
* @testcase 			ITc_maps_view_object_overlay_set_get_max_zoom_level_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and gets the maximum zoom level for overlay.
* @scenario				Creates a overlay object.
*  						Sets and gets the maximum zoom level for overlay.
* @apicovered			maps_coordinates_create, maps_view_object_create_overlay, maps_view_object_overlay_set_max_zoom_level, maps_view_object_overlay_get_max_zoom_level
* @passcase				if maps_view_object_overlay_set_max_zoom_level and maps_view_object_overlay_get_max_zoom_level and its precondition API passes
* @failcase				if maps_view_object_overlay_set_max_zoom_level or maps_view_object_overlay_get_max_zoom_level or its precondition API fails
* @precondition			NA.
* @postcondition		NA
*/
int ITc_maps_view_object_overlay_set_get_max_zoom_level_p(void)
{
	START_TEST_OBJECT;
	maps_coordinates_h hCoord = NULL;
	maps_view_object_h hOverlay = NULL;
	Evas_Object *win = NULL;
	maps_view_overlay_type_e eOverlayType = MAPS_VIEW_OVERLAY_NORMAL;
	double dX = 0.0, dY = 0.0;
	int nSetZoomLevel = 2;
	int nGetZoomLevel;
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	win = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	elm_win_autodel_set(win, TRUE);
	Evas_Object *object = elm_button_add(win);
	
	int nRet = maps_coordinates_create(dX, dY, &hCoord);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hCoord, "maps_coordinates_create");

	nRet = maps_view_object_create_overlay(hCoord, object, eOverlayType, &hOverlay);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_overlay", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord));
	CHECK_HANDLE_CLEANUP(hOverlay, "maps_view_object_create_overlay", maps_coordinates_destroy(hCoord));
		
	nRet = maps_view_object_overlay_set_max_zoom_level(hOverlay, nSetZoomLevel);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_overlay_set_max_zoom_level", MapServiceGetError(nRet), maps_view_object_destroy(hOverlay);maps_coordinates_destroy(hCoord));

	nRet = maps_view_object_overlay_get_max_zoom_level(hOverlay, &nGetZoomLevel);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_overlay_get_max_zoom_level", MapServiceGetError(nRet), maps_view_object_destroy(hOverlay);maps_coordinates_destroy(hCoord));
	if(nSetZoomLevel != nGetZoomLevel)
	{
		FPRINTF("[Line : %d][%s] Mismatch in set and get zoom level \\n", __LINE__, API_NAMESPACE);
		maps_view_object_destroy(hOverlay);
		return 1;
	}

	nRet = maps_view_object_destroy(hOverlay);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_object_destroy", MapServiceGetError(nRet));

	return 0;
}
/** @} */
/** @} */
