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

maps_coordinates_h g_HandleMapCoordinate = NULL;
maps_coordinates_list_h g_HandleMapCoordinateList = NULL;
bool g_bCbCalledCoordinateList = false;
//& set: MapsService

/**
* @function 		MapsCoordinatesListCallback
* @description	 	callback function 
* @parameter		int index, maps_coordinates_h coord, void *user_data
* @return 			false
*/
bool MapsCoordinatesListCallback(int index, maps_coordinates_h coord, void *user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback MapsCoordinatesListCallback is called \\n", __LINE__, API_NAMESPACE);
#endif
	if (coord == NULL)
	{
		FPRINTF("[Line : %d][%s]Coordinate Handle is NULL \\n", __LINE__, API_NAMESPACE);
		return true;
	}
	g_bCbCalledCoordinateList = true;
	return false;	
}

/**
 * @function 		ITs_maps_service_coordinates_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_coordinates_startup(void)
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
	int nRet = maps_coordinates_create(dLatitude, dLongitude, &g_HandleMapCoordinate);
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
		g_HandleMapCoordinate = NULL;
		return;
	}
	
	nRet = maps_coordinates_list_create(&g_HandleMapCoordinateList);
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_list_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_HandleMapCoordinateList = NULL;
		return;
	}
	
	return;
}


/**
 * @function 		ITs_maps_service_coordinates_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_coordinates_cleanup(void)
{
	if((g_HandleMapCoordinate != NULL)&& (g_bFeatureSupported == true))
	{
		maps_coordinates_destroy(g_HandleMapCoordinate);
	}
	if(g_HandleMapCoordinateList != NULL)
	{
		maps_coordinates_list_destroy(g_HandleMapCoordinateList);
	}
	return;
}

/** @addtogroup itc-maps-service-testcases
*  @brief 		Integration testcases for module maps-service
*  @ingroup 	itc-maps-service
*  @{
*/

//& type: auto
//& purpose:  scenario to creates and destroy instance of Geographical Coordinates
/**
* @testcase 			ITc_maps_coordinates_create_destroy_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to creates and destroy instance of Geographical Coordinates
* @scenario				creates instance of Geographical Coordinates \n
* 						destroy instance of Geographical Coordinates\n
* @apicovered			maps_coordinates_create, maps_coordinates_destroy
* @passcase				if maps_coordinates_create and maps_coordinates_destroy passes
* @failcase				if maps_coordinates_create or maps_coordinates_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_coordinates_create_destroy_p(void)
{
	START_TEST(g_HandleMapCoordinate, "maps_coordinate");
	maps_coordinates_destroy(g_HandleMapCoordinate);
	g_HandleMapCoordinate = NULL;
	
	double dLatitude = 44.4;
	double dLongitude = 22.2;
	maps_coordinates_h LocalHandleMapCoordinate = NULL;
	int nRet = maps_coordinates_create(dLatitude, dLongitude, &LocalHandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(LocalHandleMapCoordinate, "maps_coordinates_create");
	
	nRet = maps_coordinates_destroy(LocalHandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	return 0;
}


//& type: auto
//& purpose:  scenario to clone coordinates handle
/**
* @testcase 			ITc_maps_coordinates_clone_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to clone coordinates handle
* @scenario				clone coordinates handle\n
* 						destroy cloned coordinates handle\n
* @apicovered			maps_coordinates_clone, maps_coordinates_destroy
* @passcase				if maps_coordinates_clone and maps_coordinates_destroy passes
* @failcase				if maps_coordinates_clone or maps_coordinates_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_coordinates_clone_p(void)
{
	START_TEST(g_HandleMapCoordinate, "maps_coordinate");
	
	maps_coordinates_h LocalHandleMapCoordinate = NULL;
	int nRet = maps_coordinates_clone(g_HandleMapCoordinate, &LocalHandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_clone", MapServiceGetError(nRet));
	CHECK_HANDLE(LocalHandleMapCoordinate, "maps_coordinates_clone");
	
	nRet = maps_coordinates_destroy(LocalHandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get latitude
/**
* @testcase 			ITc_maps_coordinates_set_get_latitude_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get latitude
* @scenario				set latitude\n
* 						get latitude\n
* 						compare the set and get latitude\n
* @apicovered			maps_coordinates_set_latitude, maps_coordinates_get_latitude
* @passcase				if maps_coordinates_set_latitude and maps_coordinates_get_latitude passes  and set get values are same
* @failcase				if maps_coordinates_set_latitude or maps_coordinates_get_latitude fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_coordinates_set_get_latitude_p(void)
{
	START_TEST(g_HandleMapCoordinate, "maps_coordinate");
	
	double dSetLatitude = 44.4;
	double dGetLatitude = 0;
	int nRet = maps_coordinates_set_latitude(g_HandleMapCoordinate, dSetLatitude);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_set_latitude", MapServiceGetError(nRet));
	
	nRet = maps_coordinates_get_latitude(g_HandleMapCoordinate, &dGetLatitude);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_get_latitude", MapServiceGetError(nRet));

	if(dSetLatitude != dGetLatitude)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %lf, get = %lf\\n", __LINE__, API_NAMESPACE, dSetLatitude, dGetLatitude);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get longitude
/**
* @testcase 			ITc_maps_coordinates_set_get_longitude_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get longitude
* @scenario				set longitude\n
* 						get longitude\n
* 						compare the set and get longitude\n
* @apicovered			maps_coordinates_set_longitude, maps_coordinates_get_longitude
* @passcase				if maps_coordinates_set_longitude and maps_coordinates_get_longitude passes  and set get values are same
* @failcase				if maps_coordinates_set_longitude or maps_coordinates_get_longitude fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_coordinates_set_get_longitude_p(void)
{
	START_TEST(g_HandleMapCoordinate, "maps_coordinate");
	
	double dSetLongitude = 22.2;
	double dGetLongitude = 0;
	int nRet = maps_coordinates_set_longitude(g_HandleMapCoordinate, dSetLongitude);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_set_longitude", MapServiceGetError(nRet));
	
	nRet = maps_coordinates_get_longitude(g_HandleMapCoordinate, &dGetLongitude);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_get_longitude", MapServiceGetError(nRet));

	if(dSetLongitude != dGetLongitude)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %lf, get = %lf\\n", __LINE__, API_NAMESPACE, dSetLongitude, dGetLongitude);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get latitude and longitude
/**
* @testcase 			ITc_maps_coordinates_set_get_latitude_longitude_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to set and get latitude and longitude
* @scenario				set latitude and longitude\n
* 						get latitude and longitude\n
* 						compare the set and get latitude and longitude\n
* @apicovered			maps_coordinates_set_latitude_longitude, maps_coordinates_get_latitude_longitude
* @passcase				if maps_coordinates_set_latitude_longitude and maps_coordinates_get_latitude_longitude passes  and set get values are same
* @failcase				if maps_coordinates_set_latitude_longitude or maps_coordinates_get_latitude_longitude fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_coordinates_set_get_latitude_longitude_p(void)
{
	START_TEST(g_HandleMapCoordinate, "maps_coordinate");
	
	double dSetLatitude = 44.4;
	double dSetLongitude = 22.2;
	double dGetLatitude = 0;
	double dGetLongitude = 0;
	
	int nRet = maps_coordinates_set_latitude_longitude(g_HandleMapCoordinate, dSetLatitude, dSetLongitude );
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_set_latitude_longitude", MapServiceGetError(nRet));
		
	nRet = maps_coordinates_get_latitude_longitude(g_HandleMapCoordinate, &dGetLatitude, &dGetLongitude);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_get_latitude_longitude", MapServiceGetError(nRet));
	if(dSetLatitude != dGetLatitude)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %lf, get = %lf\\n", __LINE__, API_NAMESPACE, dSetLatitude, dGetLatitude);
		return 1;
	}
	if(dSetLongitude != dGetLongitude)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %lf, get = %lf\\n", __LINE__, API_NAMESPACE, dSetLongitude, dGetLongitude);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose:  scenario to create and destroy list
/**
* @testcase 			ITc_maps_coordinates_list_create_destroy_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to create and destroy list
* @scenario				create list\n
* 						destroy list\n
* 						create the list and destroy the list\n
* @apicovered			maps_coordinates_list_create, maps_coordinates_list_destroy
* @passcase				if maps_coordinates_list_create and maps_coordinates_list_destroy passes  
* @failcase				if maps_coordinates_list_create or maps_coordinates_list_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_coordinates_list_create_destroy_p(void)
{
	START_TEST(g_HandleMapCoordinateList, "maps_coordinate_list");
	
	maps_coordinates_list_h LocalHandleMapCoordinateList = NULL;
	
	int nRet = maps_coordinates_list_create(&LocalHandleMapCoordinateList);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_create", MapServiceGetError(nRet));
	if (LocalHandleMapCoordinateList == NULL)
	{
		FPRINTF("[Line : %d][%s]LocalHandleMapCoordinateList is empty \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = maps_coordinates_list_destroy(LocalHandleMapCoordinateList);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to append and remove list
/**
* @testcase 			ITc_maps_coordinates_list_append_remove_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to append and remove list
* @scenario				append and remove list\n
* @apicovered			maps_coordinates_list_append and maps_coordinates_list_remove
* @passcase				if maps_coordinates_list_append and maps_coordinates_list_remove passes  
* @failcase				if maps_coordinates_list_append and maps_coordinates_list_remove fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_coordinates_list_append_remove_p(void)
{
	START_TEST(g_HandleMapCoordinateList, "maps_coordinate_list");
	START_TEST(g_HandleMapCoordinate, "maps_coordinate");

	int nRet = maps_coordinates_list_append(g_HandleMapCoordinateList, g_HandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet));
	
	nRet = maps_coordinates_list_remove(g_HandleMapCoordinateList, g_HandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_remove", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to get length of list
/**
* @testcase 			ITc_maps_coordinates_list_get_length_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get length of list
* @scenario				get length of list\n
* @apicovered			maps_coordinates_list_get_length
* @passcase				if maps_coordinates_list_get_length passes  
* @failcase				if maps_coordinates_list_get_length fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_coordinates_list_get_length_p(void)
{
	START_TEST(g_HandleMapCoordinateList, "maps_coordinate_list");
	START_TEST(g_HandleMapCoordinate, "maps_coordinate");

	int dGetLength = 0;
	
	int nRet = maps_coordinates_list_append(g_HandleMapCoordinateList, g_HandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet));
	
	nRet = maps_coordinates_list_get_length(g_HandleMapCoordinateList, &dGetLength);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_get_length", MapServiceGetError(nRet));
	
	if(dGetLength != 1)
	{
		FPRINTF("[Line : %d][%s] dGetLength is mismatch, failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = maps_coordinates_list_remove(g_HandleMapCoordinateList, g_HandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_remove", MapServiceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to check list cord
/**
* @testcase 			ITc_maps_coordinates_list_foreach_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to check list cord
* @scenario				check list cord\n
* @apicovered			maps_coordinates_list_foreach
* @passcase				if maps_coordinates_list_foreach passes  
* @failcase				if maps_coordinates_list_foreach fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_coordinates_list_foreach_p(void)
{
	START_TEST(g_HandleMapCoordinateList, "maps_coordinate_list");
	START_TEST(g_HandleMapCoordinate, "maps_coordinate");

	g_bCbCalledCoordinateList = false;
	
	int nRet = maps_coordinates_list_append(g_HandleMapCoordinateList, g_HandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet));
		
	nRet = maps_coordinates_list_foreach(g_HandleMapCoordinateList, MapsCoordinatesListCallback, NULL);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_foreach", MapServiceGetError(nRet));
	if(!g_bCbCalledCoordinateList)
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_list_foreach failed, error = Callback function not invoked \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = maps_coordinates_list_remove(g_HandleMapCoordinateList, g_HandleMapCoordinate);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_remove", MapServiceGetError(nRet));
	
	return 0;
}
/** @} */
/** @} */
