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


/** @addtogroup itc-maps-service
*  @ingroup itc
*  @{
*/

maps_coordinates_h g_HandleAreaMapCoordinate = NULL;
maps_area_h g_HandleMapArea = NULL;
//& set: MapsService


/**
 * @function 		ITs_maps_service_area_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_area_startup(void)
{
	struct stat stBuff;  

	g_bFeatureSupported = true;
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	double dLatitude = 44.4;
	double dLongitude = 22.2;
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dLatitude, dLongitude, &g_HandleAreaMapCoordinate);
	if ( false == bMapsFeatureSupported)
	{
		g_bFeatureSupported = false;
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_coordinates_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_HandleAreaMapCoordinate = NULL;
	}
	return;
}


/**
 * @function 		ITs_maps_service_area_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_area_cleanup(void)
{
	if((g_HandleAreaMapCoordinate != NULL)&& (g_bFeatureSupported == true))
	{
		maps_coordinates_destroy(g_HandleAreaMapCoordinate);
	}
	return;
}

/** @addtogroup itc-maps-service-testcases
*  @brief 		Integration testcases for module maps-service
*  @ingroup 	itc-maps-service
*  @{
*/


//& type: auto
//& purpose:  scenario to creates and destroy instance of rectangular type of new Geographical Area
/**
* @testcase 			ITc_maps_area_create_destroy_rectangle_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to creates and destroy instance of rectangular type of new Geographical Area
* @scenario				creates instance of rectangular type of new Geographical Area \n
* 						destroy instance of rectangular type of new Geographical Area\n
* @apicovered			maps_area_create_rectangle, maps_area_destroy
* @passcase				if maps_area_create_rectangle and maps_area_destroy passes
* @failcase				if maps_area_create_rectangle or maps_area_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_area_create_destroy_rectangle_p(void)
{
	START_TEST(g_HandleAreaMapCoordinate, "maps_area");
	
	double dLatitude = 11.1;
	double dLongitude = 55.5;
	maps_coordinates_h LocalHandleMapCoordinate = NULL;
	
	int nRet = maps_coordinates_create(dLatitude, dLongitude, &LocalHandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(LocalHandleMapCoordinate, "maps_coordinates_create");
	
	nRet = maps_area_create_rectangle(g_HandleAreaMapCoordinate, LocalHandleMapCoordinate, &g_HandleMapArea);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_area_create_rectangle", MapServiceGetError(nRet), maps_coordinates_destroy(LocalHandleMapCoordinate));
	if(g_HandleMapArea == NULL)
	{
		FPRINTF("[Line : %d][%s] maps_area_create_rectangle failed, error = Handle returned is NULL \\n", __LINE__, API_NAMESPACE);
		maps_coordinates_destroy(LocalHandleMapCoordinate);
		return 1;
	}
	
	nRet = maps_area_destroy(g_HandleMapArea);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_area_destroy", MapServiceGetError(nRet), maps_coordinates_destroy(LocalHandleMapCoordinate));
	
	nRet = maps_coordinates_destroy(LocalHandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to creates and destroy instance of circle type of new Geographical Area
/**
* @testcase 			ITc_maps_area_create_destroy_circle_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to creates and destroy instance of circle type of new Geographical Area
* @scenario				creates instance of circle type of new Geographical Area \n
* 						destroy instance of circle type of new Geographical Area\n
* @apicovered			maps_area_create_circle, maps_area_destroy
* @passcase				if maps_area_create_circle and maps_area_destroy passes
* @failcase				if maps_area_create_circle or maps_area_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_area_create_destroy_circle_p(void)
{
	START_TEST(g_HandleAreaMapCoordinate, "maps_area");
	
	double dRadius = 200;
	int nRet = maps_area_create_circle(g_HandleAreaMapCoordinate, dRadius, &g_HandleMapArea);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_area_create_circle", MapServiceGetError(nRet));
	CHECK_HANDLE(g_HandleMapArea,"maps_area_create_circle");
	
	nRet = maps_area_destroy(g_HandleMapArea);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_area_destroy", MapServiceGetError(nRet));
	return 0;
}


//& type: auto
//& purpose:  scenario to clone Geographical Area handle
/**
* @testcase 			ITc_maps_area_clone_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to clone Geographical Area handle
* @scenario				clone Geographical Area handle\n
* 						destroy cloned Geographical Area handle\n
* @apicovered			maps_coordinates_clone, maps_area_destroy
* @passcase				if maps_coordinates_clone and maps_area_destroy passes
* @failcase				if maps_coordinates_clone or maps_area_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_area_clone_p(void)
{
	START_TEST(g_HandleAreaMapCoordinate, "maps_coordinate");
	
	maps_area_h LocalHandleArea = NULL;
	double dRadius = 200;
	int nRet = maps_area_create_circle(g_HandleAreaMapCoordinate, dRadius, &g_HandleMapArea);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_area_create_circle", MapServiceGetError(nRet));
	CHECK_HANDLE(g_HandleMapArea,"maps_area_create_circle");
	
	nRet = maps_area_clone(g_HandleMapArea, &LocalHandleArea);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_clone", MapServiceGetError(nRet), maps_area_destroy(g_HandleMapArea));
	if(LocalHandleArea == NULL)
	{
		FPRINTF("[Line : %d][%s] maps_area_clone failed, error = Handle returned is NULL \\n", __LINE__, API_NAMESPACE);
		maps_area_destroy(g_HandleMapArea);
		return 1;
	}
	
	nRet = maps_area_destroy(LocalHandleArea);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_area_destroy", MapServiceGetError(nRet), maps_area_destroy(g_HandleMapArea));
	
	nRet = maps_area_destroy(g_HandleMapArea);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_area_destroy", MapServiceGetError(nRet));
	return 0;
}


/** @} */
/** @} */
