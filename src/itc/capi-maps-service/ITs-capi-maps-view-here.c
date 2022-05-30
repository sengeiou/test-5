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
static Evas_Object *g_pEvasWin  = NULL;
static maps_service_h g_HandleMapService = NULL; 
static char gszStrValue[CONFIG_VALUE_LEN_MAX] = {0,};
static maps_view_h g_HandleMapView = NULL;
static Evas_Image *g_hImage = NULL;

static bool gCheckCB = false;
static bool g_CheckInitErr = false;

static bool MapsViewCoordinateCB(int index, int total, maps_view_object_h object, void *user_data)
{
	FPRINTF("\nEntered Callback MapsViewCoordinateCB \n");
	gCheckCB = true;
	return true;
}

static void MapsViewEventCb(maps_view_event_type_e type, maps_view_event_data_h event_data, void *user_data) 
{ 
}

/**
 * @function 		ITs_maps_view_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_view_startup(void)
{
	g_CheckInitErr = true;
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	elm_init(0,NULL);
	elm_config_accel_preference_set("opengl");

	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	
	g_pEvasWin  = elm_win_add(NULL, "sample", ELM_WIN_BASIC);
	if(g_pEvasWin == NULL)
	{
		FPRINTF("[Line : %d][%s] elm_win_add fail in startup  \\n", __LINE__, API_NAMESPACE);
		g_CheckInitErr = false;
		return;
	}
	elm_win_autodel_set(g_pEvasWin , TRUE);
	g_hImage = evas_object_image_filled_add(evas_object_evas_get(g_pEvasWin ));
	if(g_hImage == NULL)
	{
		FPRINTF("[Line : %d][%s] evas_object_image_filled_add fail in startup  \\n", __LINE__, API_NAMESPACE);
		g_CheckInitErr = false;
		return;
	}
	
	memset(g_szMapsProvider, '\0', sizeof(char)*BUFFER);
	strncpy(g_szMapsProvider, "HERE", sizeof(g_szMapsProvider)-1);
	FPRINTF("[Line : %d][%s] Provider list from maps_service_foreach_provider is = %s\\n", __LINE__, API_NAMESPACE, g_szMapsProvider);
	int nRet = maps_service_create(g_szMapsProvider, &g_HandleMapService);
	if ( false == bMapsFeatureSupported)
	{
		g_bFeatureSupported = false;
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_service_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_HandleMapService = NULL;
		g_CheckInitErr = false;
		return;
	}
	if ( true == GetValueFromConfigFile("HERE_MAPS_PROVIDER_KEY", gszStrValue, API_NAMESPACE))
    {
	#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, gszStrValue);
	#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		g_CheckInitErr = false;
		return;
	}
	nRet = maps_service_set_provider_key(g_HandleMapService, gszStrValue);
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_service_set_provider_key fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		maps_service_destroy(g_HandleMapService);
		g_HandleMapService = NULL;
		g_CheckInitErr = false;
		return;
	}
	nRet = maps_view_create(g_HandleMapService, g_pEvasWin, &g_HandleMapView);
	
	if ( nRet != MAPS_ERROR_NONE || g_HandleMapView == NULL)
	{
		FPRINTF("[Line : %d][%s] maps_service_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_HandleMapService = NULL;
		g_CheckInitErr = false;
		return;
	}

	return;
}

/**
 * @function 		ITs_maps_view_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_view_cleanup(void)
{
	if(g_HandleMapView != NULL)
    {
		maps_view_destroy(g_HandleMapView);
	}
	if(g_HandleMapService != NULL)
	{
		maps_service_destroy(g_HandleMapService);
	}
	elm_shutdown();

	g_HandleMapView = NULL;
	g_HandleMapService = NULL;
	g_hImage = NULL;
	g_pEvasWin  = NULL;
	
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
* @testcase 			ITc_maps_view_create_destroy_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to create and destroy a new maps view
* @scenario				creates a new map view\n
* 						destroy the map view\n
* @apicovered			maps_view_create, maps_view_destroy
* @passcase				if maps_view_create and maps_view_destroy passes
* @failcase				if maps_view_create or maps_view_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_view_create_destroy_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	maps_service_h HandleMapService = NULL; 
	maps_view_h HandleMapView = NULL;
	Evas_Image *Image = NULL;
	
	Image = evas_object_image_filled_add(evas_object_evas_get(g_pEvasWin ));
	if(Image == NULL)
	{
		FPRINTF("[Line : %d][%s] Evas_Image null\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nRet = maps_service_create(g_szMapsProvider, &HandleMapService);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_create", MapServiceGetError(nRet));
	CHECK_HANDLE(HandleMapService, "maps_service_create");

	nRet = maps_service_set_provider_key(HandleMapService, gszStrValue);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_set_provider_key", MapServiceGetError(nRet), maps_service_destroy(HandleMapService));
	
	nRet = maps_view_create(HandleMapService, Image, &HandleMapView);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_create", MapServiceGetError(nRet), maps_service_destroy(HandleMapService));
	CHECK_HANDLE_CLEANUP(HandleMapView, "maps_view_create", maps_service_destroy(HandleMapService));
	
	nRet = maps_view_destroy(HandleMapView);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_destroy", MapServiceGetError(nRet), maps_service_destroy(HandleMapService));
	
	maps_service_destroy(HandleMapService);
	
	return 0;
}
//& type: auto
//& purpose:  scenario to set and get center
/**
* @testcase 			ITc_maps_view_set_get_center_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to set and get center
* @scenario				call maps_view_get_center and maps_view_set_center
* @apicovered			maps_view_get_center, maps_view_set_center
* @passcase				if maps_view_get_center and maps_view_set_center passes
* @failcase				if maps_view_get_center and maps_view_set_center fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_view_set_get_center_p(void)   
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	maps_coordinates_h Setcoord = NULL;
	maps_coordinates_h Getcoord = NULL;
	
	double Setlatitude = 30.0;
	double Setlongitude = 40.0;
	double Getlatitude = 0.0;
	double Getlongitude = 0.0;

	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(Setlatitude, Setlongitude, &Setcoord);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
    CHECK_HANDLE(Setcoord, "maps_coordinates_create");
	
	nRet = maps_view_set_center(g_HandleMapView, Setcoord);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_set_center API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_set_center API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_set_center", MapServiceGetError(nRet), maps_coordinates_destroy(Setcoord));
	
	nRet = maps_view_get_center(g_HandleMapView, &Getcoord);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_get_center", MapServiceGetError(nRet), maps_coordinates_destroy(Setcoord));
	CHECK_HANDLE(Getcoord, "maps_view_get_center");
	
    nRet = maps_coordinates_get_latitude_longitude(Getcoord,&Getlatitude,&Getlongitude);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_get_latitude_longitude", MapServiceGetError(nRet), maps_coordinates_destroy(Setcoord));
	
	if(Setlatitude != Getlatitude || Setlongitude != Getlongitude)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		maps_coordinates_destroy(Setcoord);
		return 1;
	}
	nRet = maps_coordinates_destroy(Setcoord);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to set and get zoom level
/**
* @testcase 			ITc_maps_view_set_get_zoom_level_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to set and get zoom level
* @scenario				call maps_view_set_zoom_level and maps_view_get_zoom_level
* @apicovered			maps_view_set_zoom_level, maps_view_get_zoom_level
* @passcase				if maps_view_set_zoom_level and maps_view_get_zoom_level passes
* @failcase				if maps_view_set_zoom_level and maps_view_get_zoom_level fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_view_set_get_zoom_level_p(void)   
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	int Setlevel = 3;
	int Getlevel = 0;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_view_set_zoom_level(g_HandleMapView, Setlevel);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_set_zoom_level API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_set_zoom_level API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_zoom_level", MapServiceGetError(nRet));
	
	nRet = maps_view_get_zoom_level(g_HandleMapView, &Getlevel);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_zoom_level", MapServiceGetError(nRet));

	if(Setlevel != Getlevel)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}
//& type: auto
//& purpose:  scenario to set and get the minimal zoom level of the map
/**
* @testcase 			ITc_maps_view_set_get_min_zoom_level_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets the minimal zoom level of the map.
*						Gets the minimal zoom level of the map.
* @scenario				maps_view_set_min_zoom_level, call maps_view_get_min_zoom_level
* @apicovered			maps_view_set_min_zoom_level, maps_view_get_min_zoom_level
* @passcase				if maps_view_set_min_zoom_level and maps_view_get_min_zoom_level passes
* @failcase				if maps_view_set_min_zoom_level or maps_view_get_min_zoom_level fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_view_set_get_min_zoom_level_p(void)   
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	int nSetZoomLevel = 1;
	int nGetZoomLevel;
	
	int nRet = maps_view_set_min_zoom_level(g_HandleMapView, nSetZoomLevel);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_min_zoom_level", MapServiceGetError(nRet));
	
	nRet = maps_view_get_min_zoom_level(g_HandleMapView, &nGetZoomLevel);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_min_zoom_level", MapServiceGetError(nRet));
	
	if(nSetZoomLevel != nGetZoomLevel)
	{
		FPRINTF("[Line : %d][%s] Mismatch in set and get zoom level \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
	
}

//& type: auto
//& purpose:  scenario to set and get the maximal zoom level of the map
/**
* @testcase 			ITc_maps_view_set_get_max_zoom_level_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets the maximal zoom level of the map.
*						Gets the maximal zoom level of the map.
* @scenario				call maps_view_set_max_zoom_level and maps_view_get_max_zoom_level
* @apicovered			maps_view_set_max_zoom_level, maps_view_get_max_zoom_level
* @passcase				if maps_view_set_max_zoom_level and maps_view_get_max_zoom_level pass
* @failcase				if maps_view_set_max_zoom_level or maps_view_get_max_zoom_level fail
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_view_set_get_max_zoom_level_p(void)   
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	int nSetZoomLevel = 7;
	int nGetZoomLevel;

	int nRet = maps_view_set_max_zoom_level(g_HandleMapView, nSetZoomLevel);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_max_zoom_level", MapServiceGetError(nRet));

	nRet = maps_view_get_max_zoom_level(g_HandleMapView, &nGetZoomLevel);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_max_zoom_level", MapServiceGetError(nRet));
	
	if(nSetZoomLevel != nGetZoomLevel)
	{
		FPRINTF("[Line : %d][%s] Mismatch in set and get zoom level \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}
//& type: auto
//& purpose:  scenario to set and get the orientation on the View
/**
* @testcase 			ITc_maps_view_set_get_orientation_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and Gets the orientation on the View
* @scenario				call maps_view_set_orientation and maps_view_get_orientation
* @apicovered			maps_view_set_orientation, maps_view_get_orientation
* @passcase				if maps_view_set_orientation, maps_view_get_orientation passes
* @failcase				if maps_view_set_orientation, maps_view_get_orientation fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_view_set_get_orientation_p(void)   
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	double SetOrientation = 30.0;
	double GetOrientation = 0.0;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_view_set_orientation(g_HandleMapView, SetOrientation);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_set_orientation API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_set_orientation API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_orientation", MapServiceGetError(nRet));

	nRet = maps_view_get_orientation(g_HandleMapView, &GetOrientation);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_orientation", MapServiceGetError(nRet));
	
    if(SetOrientation != GetOrientation)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}
//& type: auto
//& purpose:  scenario to converts screen coordinates to the geographical coordinates accordingly to the current map zoom and orientation.
/**
* @testcase 			ITc_maps_view_screen_to_geolocation_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Converts screen coordinates to the geographical coordinates
* @scenario				call maps_view_screen_to_geolocation
* @apicovered			maps_view_screen_to_geolocation
* @passcase				if maps_view_screen_to_geolocation passes
* @failcase				if maps_view_screen_to_geolocation fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_view_screen_to_geolocation_p(void)   
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	maps_coordinates_h GeoCord = NULL;
	int x = 3;
	int y = 4;
	
	int nRet = maps_view_screen_to_geolocation(g_HandleMapView, x, y, &GeoCord);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_screen_to_geolocation", MapServiceGetError(nRet));
	CHECK_HANDLE(GeoCord, "maps_view_screen_to_geolocation");

	nRet = maps_coordinates_destroy(GeoCord);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to convert geographical coordinates to the screen coordinates
/**
* @testcase 			ITc_maps_view_geolocation_to_screen_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Converts geographical coordinates to the screen coordinates.
* @scenario				call maps_view_geolocation_to_screen
* @apicovered			maps_view_geolocation_to_screen
* @passcase				if maps_view_geolocation_to_screen passes
* @failcase				if maps_view_geolocation_to_screen fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_view_geolocation_to_screen_p(void)   
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	maps_coordinates_h coord = NULL;
	double latitude = 0.0;
	double longitude = 0.0;
	int screen_x = 0, screen_y = 0;

	int nRet = maps_coordinates_create(latitude, longitude, &coord);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
    CHECK_HANDLE(coord, "maps_coordinates_create");
	
	nRet = maps_view_geolocation_to_screen(g_HandleMapView, coord, &screen_x, &screen_y);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_geolocation_to_screen", MapServiceGetError(nRet), maps_coordinates_destroy(coord));

	nRet = maps_coordinates_destroy(coord);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to set and get View type
/**
* @testcase 			ITc_maps_view_set_get_type_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets and Gets View type
* @scenario				call maps_view_set_type and maps_view_get_type
* @apicovered			maps_view_set_type and maps_view_get_type
* @passcase				if maps_view_set_type and maps_view_get_type passes
* @failcase				if maps_view_set_type or maps_view_get_type fails
* @precondition			a view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_set_get_type_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	maps_view_type_e Gettype;
	int nRet, nLoopCount = 0;
	maps_view_type_e eMapViewTypes[] = {MAPS_VIEW_TYPE_NORMAL, MAPS_VIEW_TYPE_SATELLITE, MAPS_VIEW_TYPE_TERRAIN, MAPS_VIEW_TYPE_HYBRID};
	
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nMapViewTypeArraySize = sizeof(eMapViewTypes) / sizeof(eMapViewTypes[0]);
	
	for(nLoopCount = 0; nLoopCount < nMapViewTypeArraySize; nLoopCount++)
	{
		nRet = maps_view_set_type(g_HandleMapView, eMapViewTypes[nLoopCount]);
		if ( false == bInternetFeatureSupported)
		{
			if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] maps_view_set_type API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
				return 1;
			}
			else
			{
				FPRINTF("[Line : %d][%s] maps_view_set_type API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
				return 0;
			}
		}
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_type", MapServiceGetError(nRet));

		nRet = maps_view_get_type(g_HandleMapView, &Gettype);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_type", MapServiceGetError(nRet));
		
		if(Gettype != eMapViewTypes[nLoopCount])
		{
			FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to enable or disable 3D buildings
/**
* @testcase 			ITc_maps_view_set_get_buildings_enabled_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Enables or disables 3D buildings
* @scenario				call maps_view_set_buildings_enabled, maps_view_get_buildings_enabled
* @apicovered			maps_view_set_buildings_enabled, maps_view_get_buildings_enabled
* @passcase				if maps_view_set_buildings_enabled, maps_view_get_buildings_enabled passes
* @failcase				if maps_view_set_buildings_enabled, maps_view_get_buildings_enabled fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_view_set_get_buildings_enabled_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	bool supported = false;
	bool SetEnabled = false;
	bool GetEnabled;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);

	int nRet = maps_service_provider_is_data_supported(g_HandleMapService, MAPS_VIEW_BUILDING, &supported);
	
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_set_buildings_enabled API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_set_buildings_enabled API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_provider_is_data_supported", MapServiceGetError(nRet));
	
	if(supported == true)
	{
		nRet = maps_view_set_buildings_enabled(g_HandleMapView, SetEnabled);
		
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_buildings_enabled", MapServiceGetError(nRet));
		
		nRet = maps_view_get_buildings_enabled(g_HandleMapView, &GetEnabled);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_buildings_enabled", MapServiceGetError(nRet));
		if(GetEnabled != SetEnabled)
		{
			FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] ITc_maps_view_set_get_buildings_enabled_p API not supported", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
	}

	return 0;
}

//& type: auto
//& purpose:  scenario to set and get View language.
/**
* @testcase 			ITc_maps_view_set_get_language_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			This function sets and gets the language to the given View.
* @scenario				Sets the language to the given View. Gets the language to the given View
* @apicovered			maps_view_set_language, maps_view_get_language
* @passcase				if maps_view_set_language and maps_view_get_language passes
* @failcase				if maps_view_set_language or maps_view_get_language fails
* @precondition			view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_set_get_language_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	char *setLanguage = "eng";
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_view_set_language(g_HandleMapView, setLanguage);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_set_language API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_set_language API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_language", MapServiceGetError(nRet));
	
	char *getLanguage = NULL;

	nRet = maps_view_get_language(g_HandleMapView, &getLanguage);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_language", MapServiceGetError(nRet));
	if(0 != strcmp(getLanguage,setLanguage))
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY_TC(getLanguage);
		return 1;
	}
		
	FREE_MEMORY_TC(getLanguage);

	return 0;
}

//& type: auto
//& purpose:  scenario to Enables or disables scalebar and Gets whether the scalebar is enabled or not.
/**
* @testcase 			ITc_maps_view_set_get_scalebar_enabled_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Enables or disables scalebar and Gets whether the scalebar is enabled or not
* @scenario				Enables or disables scalebar. Gets whether the scalebar is enabled or not
* @apicovered			maps_view_set_scalebar_enabled, maps_view_get_scalebar_enabled
* @passcase				if maps_view_set_scalebar_enabled and maps_view_get_scalebar_enabled passes
* @failcase				if maps_view_set_scalebar_enabled or maps_view_get_scalebar_enabled fails
* @precondition			view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_set_get_scalebar_enabled_p(void)   
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	bool setEnabled = false;
	bool getEnabled = true;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_view_set_scalebar_enabled(g_HandleMapView, setEnabled);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_set_scalebar_enabled API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_set_scalebar_enabled API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_scalebar_enabled", MapServiceGetError(nRet));
    
	nRet = maps_view_get_scalebar_enabled(g_HandleMapView, &getEnabled);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_scalebar_enabled", MapServiceGetError(nRet));
	if(setEnabled != getEnabled)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose:  scenario to set and get View language.
/**
* @testcase 			ITc_maps_view_set_get_traffic_enabled_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			This function turns the traffic layer on or off. Gets whether map is drawing traffic data.
* @scenario				turns the traffic layer on or off. Gets whether map is drawing traffic data.
* @apicovered			maps_view_set_traffic_enabled, maps_view_get_traffic_enabled
* @passcase				if maps_view_set_traffic_enabled and maps_view_get_traffic_enabled passes
* @failcase				if maps_view_set_traffic_enabled or maps_view_get_traffic_enabled fails
* @precondition			view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_set_get_traffic_enabled_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	bool setEnabled = false;
	bool getEnabled = true;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_view_set_traffic_enabled(g_HandleMapView, setEnabled);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_set_traffic_enabled API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_set_traffic_enabled API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_traffic_enabled", MapServiceGetError(nRet));
	
	nRet = maps_view_get_traffic_enabled(g_HandleMapView, &getEnabled);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_traffic_enabled", MapServiceGetError(nRet));
	if(setEnabled != getEnabled)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose:  scenario to get the View port.
/**
* @testcase 			ITc_maps_view_get_viewport_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			This function gets the View port as a pointer on Evas_Image.
* @scenario				Gets the View port.
* @apicovered			maps_view_get_viewport
* @passcase				if maps_view_get_viewport passes
* @failcase				if maps_view_get_viewport fails
* @precondition			view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_get_viewport_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	Evas_Image *viewport = NULL;

	int nRet = maps_view_get_viewport(g_HandleMapView, &viewport);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_viewport", MapServiceGetError(nRet));
	CHECK_HANDLE(viewport, "maps_view_get_viewport");
	
	return 0;
}
//& type: auto
//& purpose:  scenario to Sets geometry of View port.
/**
* @testcase 			ITc_maps_view_set_get_screen_location_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			maps_view_set_screen_location set the position and (rectangular) size of the given view. \n
*						maps_view_get_screen_location retrieves the position and (rectangular) size of the given View.
* @scenario				set the position and (rectangular) size of the given view \n
*						retrieves the position and (rectangular) size of the given View.
* @apicovered			maps_view_set_screen_location, maps_view_get_screen_location
* @passcase				if maps_view_set_screen_location and maps_view_get_screen_location passes
* @failcase				if maps_view_set_screen_location or maps_view_get_screen_location fails
* @precondition			view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_set_get_screen_location_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	int nSetX = 10, nSetY = 10, nSetWidth = 10, nSetHeight = 10;
	int nGetX, nGetY, nGetWidth, nGetHeight;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_view_set_screen_location(g_HandleMapView, nSetX, nSetY, nSetWidth, nSetHeight);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_set_screen_location API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_set_screen_location API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_screen_location", MapServiceGetError(nRet));
	
    nRet = maps_view_get_screen_location(g_HandleMapView, &nGetX, &nGetY, &nGetWidth, &nGetHeight);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_screen_location", MapServiceGetError(nRet));
	if(nSetX != nGetX || nSetY != nGetY || nSetWidth != nGetWidth || nSetHeight != nGetHeight)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}
//& type: auto
//& purpose:  scenario to Shows or hides the View. Gets the View visibility.
/**
* @testcase 			ITc_maps_view_set_get_visibility_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			maps_view_set_visibility Shows or hides the View. \n 
*						maps_view_get_visibility retrieves whether or not the given View is visible.
* @scenario				call maps_view_screen_to_geolocation
* @apicovered			maps_view_set_visibility, maps_view_get_visibility
* @passcase				if maps_view_set_visibility and maps_view_get_visibility passes
* @failcase				if maps_view_set_visibility or maps_view_get_visibility fails
* @precondition			view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_set_get_visibility_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	bool setVisibility = false;
	bool getVisibility;
	
	int nRet = maps_view_set_visibility(g_HandleMapView, setVisibility);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_visibility", MapServiceGetError(nRet));
    
	nRet = maps_view_get_visibility(g_HandleMapView, &getVisibility);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_visibility", MapServiceGetError(nRet));
	if(setVisibility != getVisibility)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}
//& type: auto
//& purpose:  scenario to Enables or disables the map gesture and then check whether the map gesture is enabled or not.
/**
* @testcase 			ITc_maps_view_set_get_gesture_enabled_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			maps_view_set_gesture_enabled Enables or disables the map gesture \n
*						maps_view_get_gesture_enabled check whether the map gesture is enabled or not.
* @scenario				call maps_view_screen_to_geolocation
* @apicovered			maps_view_set_gesture_enabled, maps_view_get_gesture_enabled
* @passcase				if maps_view_set_gesture_enabled and maps_view_get_gesture_enabled passes
* @failcase				if maps_view_set_gesture_enabled or maps_view_get_gesture_enabled fails
* @precondition			view is created using maps_view_create(). \n 
*						enabled status set as default or modified using maps_view_set_gesture_enabled().
* @postcondition		NA
*/
int ITc_maps_view_set_get_gesture_enabled_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	bool setEnabled = false;
	bool getEnabled;
	int nRet, nLoopCount = 0;
	maps_view_gesture_e eMapViewGestureType[] = {MAPS_VIEW_GESTURE_NONE, MAPS_VIEW_GESTURE_SCROLL, MAPS_VIEW_GESTURE_ZOOM, MAPS_VIEW_GESTURE_TAP, MAPS_VIEW_GESTURE_DOUBLE_TAP, MAPS_VIEW_GESTURE_2_FINGER_TAP, MAPS_VIEW_GESTURE_ROTATE, MAPS_VIEW_GESTURE_LONG_PRESS};
	int nMapViewGestureArraySize = sizeof(eMapViewGestureType) / sizeof(eMapViewGestureType[0]);
	
	for(nLoopCount = 0; nLoopCount < nMapViewGestureArraySize; nLoopCount++)
	{
		nRet = maps_view_set_gesture_enabled(g_HandleMapView, eMapViewGestureType[nLoopCount], setEnabled);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_gesture_enabled", MapServiceGetError(nRet));
		
		nRet = maps_view_get_gesture_enabled(g_HandleMapView, eMapViewGestureType[nLoopCount], &getEnabled);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_gesture_enabled", MapServiceGetError(nRet));
		if(setEnabled != getEnabled)
		{
			FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}	
	return 0;
}

//& type: auto
//& purpose:  scenario to Adds a visual object on the map. Then Removes a visual object from the map.
/**
* @testcase 			ITc_maps_view_add_remove_object_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			maps_view_add_object adds a visual object on the map. maps_view_remove_object removes a visual object from the map.
* @scenario				Create a visual object. Adds a visual object on the map. Then Removes a visual object from the map.
* @apicovered			maps_view_add_object, maps_view_remove_object
* @passcase				if maps_view_add_object and maps_view_remove_object passes
* @failcase				if maps_view_add_object or maps_view_remove_object fails
* @precondition			view is created using maps_view_create(). \n
*						object is added using maps_view_add_object().
* @postcondition		NA
*/
int ITc_maps_view_add_remove_object_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL;
	maps_coordinates_list_h hCoord_list = NULL;
	maps_view_object_h hPolyline = NULL;
	
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	int nWidth = 1;
	
	int nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
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
	
	nRet = maps_view_add_object(g_HandleMapView, hPolyline);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_add_object", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));
	
	nRet = maps_view_remove_object(g_HandleMapView, hPolyline);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_remove_object", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to Adds a visual object on the map. Then Removes all visual objects from the map.
/**
* @testcase 			ITc_maps_view_remove_all_objects_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			Removes all visual objects from the map.
* @scenario				Create a visual object. Add visual objects on the map. Then Removes all visual objects from the map.
* @apicovered			maps_view_remove_all_objects
* @passcase				if maps_view_remove_all_objects passes
* @failcase				if maps_view_remove_all_objects fails
* @precondition			view is created using maps_view_create(). \n
*						object is added using maps_view_add_object().
* @postcondition		NA
*/
int ITc_maps_view_remove_all_objects_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL;
	maps_coordinates_list_h hCoord_list = NULL;
	maps_view_object_h hPolyline = NULL;
	maps_view_object_h hMarker = NULL;
	maps_coordinates_h hCoord3 = NULL;
	
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	int nRet, nWidth = 1;
	
	gCheckBool = GetResourceDataPath();
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
				
	nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
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
	
	nRet = maps_view_add_object(g_HandleMapView, hPolyline);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_add_object", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));
	
	nRet = maps_coordinates_create(dX1, dY1, &hCoord3);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE_CLEANUP(hCoord3, "maps_coordinates_create", maps_view_object_destroy(hPolyline));

	nRet = maps_view_object_create_marker(hCoord3, gszImagePath, MAPS_VIEW_MARKER_PIN, &hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3));
	CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord3); maps_view_object_destroy(hPolyline));

	nRet = maps_view_add_object(g_HandleMapView, hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_add_object", MapServiceGetError(nRet), maps_view_object_destroy(hMarker); maps_view_object_destroy(hPolyline));
	
	nRet = maps_view_remove_all_objects(g_HandleMapView);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_remove_all_objects", MapServiceGetError(nRet), maps_view_object_destroy(hMarker); maps_view_object_destroy(hPolyline));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to retrieve all visual objects on the map.
/**
* @testcase 			ITc_maps_view_foreach_object_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			This function retrieves all visual objects, previously added to the map.
* @scenario				Create a visual object. Adds a visual object on the map. Retrieves all visual objects on the map.
* @apicovered			maps_view_foreach_object
* @passcase				if maps_view_foreach_object passes
* @failcase				if maps_view_foreach_object fails
* @precondition			view is created using maps_view_create(). \n
*						object is added using maps_view_add_object().
* @postcondition		This function invokes maps_view_object_cb() repeatedly to retrieve each visual object.
*/
int ITc_maps_view_foreach_object_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	gCheckCB = false;
	maps_coordinates_h hCoord1 = NULL, hCoord2 = NULL, hCoord3 = NULL;
	maps_coordinates_list_h hCoord_list = NULL;
	maps_view_object_h hPolyline = NULL;
	maps_view_object_h hMarker = NULL;
	
	double dX1 = 0.0, dX2 = 10.0, dY1 = 0.0, dY2 = 10.0;
	unsigned char cRed = '1';
	unsigned char cGreen = '1';
	unsigned char cBlue = '1';
	unsigned char cAlpha = '1';
	int nRet, nWidth = 1;
	
	gCheckBool = GetResourceDataPath();
	
	if(!gCheckBool)
	{
		FPRINTF("[Line : %d][%s] Resource Path is Null \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = maps_coordinates_create(dX1, dY1, &hCoord1);
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
	
	nRet = maps_view_add_object(g_HandleMapView, hPolyline);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_add_object", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));
	
	nRet = maps_coordinates_create(dX1, dY1, &hCoord3);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_view_object_destroy(hPolyline));
	CHECK_HANDLE_CLEANUP(hCoord3, "maps_coordinates_create", maps_view_object_destroy(hPolyline));

	nRet = maps_view_object_create_marker(hCoord3, gszImagePath, MAPS_VIEW_MARKER_PIN, &hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_object_create_marker", MapServiceGetError(nRet), maps_coordinates_destroy(hCoord3); maps_view_object_destroy(hPolyline));
	CHECK_HANDLE_CLEANUP(hMarker, "maps_view_object_create_marker", maps_coordinates_destroy(hCoord3); maps_view_object_destroy(hPolyline));

	nRet = maps_view_add_object(g_HandleMapView, hMarker);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_add_object", MapServiceGetError(nRet), maps_view_object_destroy(hMarker); maps_view_object_destroy(hPolyline));
	
	nRet = maps_view_foreach_object(g_HandleMapView, MapsViewCoordinateCB, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_view_foreach_object", MapServiceGetError(nRet), maps_view_object_destroy(hMarker); maps_view_object_destroy(hPolyline));
	
	if(gCheckCB == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked \\n", __LINE__, API_NAMESPACE);
		
		nRet = maps_view_remove_object(g_HandleMapView, hPolyline);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_remove_object", MapServiceGetError(nRet));
	
		return 1;
	}
	
	nRet = maps_view_remove_object(g_HandleMapView, hPolyline);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_view_remove_object", MapServiceGetError(nRet));
		
	return 0;
}

//& type: auto
//& purpose:  scenario to Move the View.
/**
* @testcase 			ITc_maps_view_move_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			This function moves View.
* @scenario				Moves the View.
* @apicovered			maps_view_move
* @passcase				if maps_view_move passes
* @failcase				if maps_view_move fails
* @precondition			view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_move_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	int nX = 10, nY = 10;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_view_move(g_HandleMapView, nX, nY);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_move API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_move API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_move", MapServiceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to resize the View.
/**
* @testcase 			ITc_maps_view_resize_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			This function changes the size of the given View.
* @scenario				Resizes the View.
* @apicovered			maps_view_resize
* @passcase				if maps_view_resize passes
* @failcase				if maps_view_resize fails
* @precondition			view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_resize_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	int nWidth = 10, nHeight = 10;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_view_resize(g_HandleMapView, nWidth, nHeight);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_resize API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_resize API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_resize", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to indicate and query whether the map should show public transit layer. 
/**
* @testcase 			ITc_maps_view_set_get_public_transit_enabled_p
* @author            	SRID(arvin.mittal)
* @reviewer         	SRID(a.pandia)
* @type 				auto
* @since_tizen 			3.0
* @description			This function is called to indicate or query whether public transit routes should be shown as a layer on the map
* @scenario				indicate whether the map should show public transit layer \n
*						query whether the map has public transit layer enabled.
* @apicovered			maps_view_set_public_transit_enabled, maps_view_get_public_transit_enabled
* @passcase				if maps_view_set_public_transit_enabled and maps_view_get_public_transit_enabled passes
* @failcase				if maps_view_set_public_transit_enabled or maps_view_get_public_transit_enabled fails
* @precondition			view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_set_get_public_transit_enabled_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	bool setEnabled = false;
	bool getEnabled = true;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_view_set_public_transit_enabled(g_HandleMapView, setEnabled);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_view_set_public_transit_enabled API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_view_set_public_transit_enabled API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_public_transit_enabled", MapServiceGetError(nRet));
	
	nRet = maps_view_get_public_transit_enabled(g_HandleMapView, &getEnabled);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_get_public_transit_enabled", MapServiceGetError(nRet));
	if(setEnabled != getEnabled)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose:  Sets and unset the event callback. 
/**
* @testcase 			ITc_maps_view_set_unset_event_cb_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Sets the event callback
* @scenario				Sets the event callback \n
*						Unset the event callback.
* @apicovered			maps_view_set_event_cb, maps_view_unset_event_cb
* @passcase				if maps_view_set_event_cb and maps_view_unset_event_cb passes
* @failcase				if maps_view_set_event_cb or maps_view_unset_event_cb fails
* @precondition			view is created using maps_view_create().
* @postcondition		NA
*/
int ITc_maps_view_set_unset_event_cb_p(void)
{
	START_TEST_VIEW(g_CheckInitErr,"maps_view");
	
	int nRet = maps_view_set_event_cb(g_HandleMapView, MAPS_VIEW_EVENT_GESTURE, MapsViewEventCb, NULL);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_set_event_cb", MapServiceGetError(nRet));
	
	nRet = maps_view_unset_event_cb(g_HandleMapView, MAPS_VIEW_EVENT_GESTURE);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_view_unset_event_cb", MapServiceGetError(nRet));
	
	return 0;
}
/** @} */
/** @} */
