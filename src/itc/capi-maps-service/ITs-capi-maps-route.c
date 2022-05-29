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

static maps_route_h g_route = NULL;
static maps_route_segment_h g_route_segment = NULL;

/** @addtogroup itc-maps-service
*  @ingroup itc
*  @{
*/

static bool MapsRouteSegmentPathCb(int index, int total, maps_coordinates_h coordinates, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsRouteSegmentPathCb callback\\n", __LINE__, API_NAMESPACE); 
    g_nCheckCb = true;
	
	return true;
}								   
static bool MapsRoutePathCb(int index, int total, maps_coordinates_h coordinates, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsRoutePathCb callback\\n", __LINE__, API_NAMESPACE); 
    g_nCheckCb = true;
	
	return true;
}
static bool MapsRouteSegmentCb(int index, int total, maps_route_segment_h segment, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsRouteSegmentCb callback\\n", __LINE__, API_NAMESPACE); 
    g_nCheckCb = true;
	if(g_nClone == 1)
	{
		g_nCheckRet = maps_route_segment_clone(segment, &g_route_segment);
	}
	return true;
}
// Callback function to get search route
static bool MapsServiceRouteFoundCb(maps_error_e error, int request_id, int index, int total, maps_route_h route, void* user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsServiceRouteFoundCb callback\\n", __LINE__, API_NAMESPACE);
	
	g_nCheckRet = maps_route_clone(route, &g_route);
	
	if (index + 1 < total) return true;

	g_nCheckCb = true;

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	return true;
}
// Callback Function to get list of service providers
static bool MapServiceProviderForeachCb(char* maps_provider, void* user_data)
{
	memset( g_szMapsProvider, '\0', sizeof(char)*BUFFER);
	strncpy(g_szMapsProvider, "HERE", sizeof(g_szMapsProvider)-1);
	FPRINTF("[Line : %d][%s] Provider list from maps_service_foreach_provider is = %s\\n", __LINE__, API_NAMESPACE, g_szMapsProvider);	
	g_nCheckCb = true;
	return false;
}

static void MapsRouteHelper(void)
{
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	int nRequestId = 0;
	maps_coordinates_h hOrigin = NULL;
	maps_coordinates_h hDestination = NULL;

	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	g_bStartupPre = true;
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_service_foreach_provider(MapServiceProviderForeachCb, NULL);
	if ( false == bMapsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_foreach_provider API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
			return;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_foreach_provider API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
			return;
		}
	}
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_service_foreach_provider API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		return;
	}
	
	FPRINTF("[Line : %d][%s] Provider list from maps_service_foreach_provider is = %s\\n", __LINE__, API_NAMESPACE, g_szMapsProvider);
	if(g_szMapsProvider == NULL)
	{
		 FPRINTF("[Line : %d][%s] g_szMapsProvider NULL\\n", __LINE__, API_NAMESPACE);
		 g_bStartupPre = false;
		 return;
	}
	
	nRet = maps_service_create(g_szMapsProvider, &g_hMapService);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_service_create API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		return;
	}
	if(g_hMapService == NULL)
	{
	    FPRINTF("[Line : %d][%s] g_hMapService NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		return;
	}
	char pstrValue[CONFIG_VALUE_LEN_MAX] = {0,};

	if ( true == GetValueFromConfigFile("HERE_MAPS_PROVIDER_KEY", pstrValue, API_NAMESPACE) )
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, pstrValue);
#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		return;
	}
	if(pstrValue == NULL)
	{
		g_bStartupPre = false;
		return;
	}
	
	nRet = maps_service_set_provider_key(g_hMapService, pstrValue);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_service_set_provider_key API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_service_destroy(g_hMapService);
		return;
	}
	nRet = maps_preference_create(&g_hMapsPref);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_preference_create API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_service_destroy(g_hMapService);
		return;
	}
	if(g_hMapsPref == NULL)
	{
	    FPRINTF("[Line : %d][%s] g_hMapsPref NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_service_destroy(g_hMapService);
		return;
	}

	nRet = maps_preference_set_max_results(g_hMapsPref, RESULT);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_preference_set_max_results API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}

	nRet = maps_coordinates_create(LATITUTE_ORG, LONGITUDE_ORG, &hOrigin);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_create API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(hOrigin == NULL)
	{
	    FPRINTF("[Line : %d][%s] hOrigin NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	nRet = maps_coordinates_create(LATITUTE_DEST, LONGITUDE_DEST, &hDestination);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_create API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
	    maps_coordinates_destroy(hOrigin);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(hDestination == NULL)
	{
	    FPRINTF("[Line : %d][%s] hDestination NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_coordinates_destroy(hOrigin);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	
	nRet = maps_service_search_route(g_hMapService, hOrigin, hDestination, g_hMapsPref, MapsServiceRouteFoundCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_search_route API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
			return;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_search_route API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
			return;
		}
	}
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_service_search_route API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
	    maps_coordinates_destroy(hOrigin);
		maps_coordinates_destroy(hDestination);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	
	RUN_POLLING_LOOP;
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Route is not received from maps_service_search_route \\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_coordinates_destroy(hOrigin);
		maps_coordinates_destroy(hDestination);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(g_route == NULL)
	{
	    FPRINTF("[Line : %d][%s] g_route NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_coordinates_destroy(hOrigin);
		maps_coordinates_destroy(hDestination);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(g_nCheckRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_route_clone API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
	    maps_coordinates_destroy(hOrigin);
		maps_coordinates_destroy(hDestination);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	
	nRet = maps_coordinates_destroy(hOrigin);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_destroy API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_coordinates_destroy(hDestination);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}	
	nRet = maps_coordinates_destroy(hDestination);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_destroy API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}	
	nRet = maps_preference_destroy(g_hMapsPref);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_preference_destroy API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_service_destroy(g_hMapService);
		return;
	}	
	nRet = maps_service_destroy(g_hMapService);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_service_destroy API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		return;
	}	
	return;
}

/**
 * @function 		ITs_maps_route_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_route_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	MapsRouteHelper();
	
	return;
}
/**
 * @function 		ITs_maps_route_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_route_cleanup(void)
{
	return;
}
//& type: auto
//& purpose:  scenario to clone the route handle.
/**
* @testcase 			ITc_maps_route_clone_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to clone the route handle.
* @scenario				maps_route_clone
* @apicovered			maps_route_clone
* @passcase				if maps_route_clone passes
* @failcase				if maps_route_clone fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_maps_route_clone_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;	
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to retrieve all paths of the route handle.
/**
* @testcase 			ITc_maps_route_foreach_path_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to retrieve all paths of the route handle.
* @scenario				maps_route_foreach_path
* @apicovered			maps_route_foreach_path
* @passcase				if maps_route_foreach_path passes
* @failcase				if maps_route_foreach_path fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_foreach_path_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;
	
	g_nCheckCb = 0;
	
	nRet = maps_route_foreach_path(g_route, MapsRoutePathCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_foreach_path", MapServiceGetError(nRet),maps_route_destroy(g_route));		   

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRoutePathCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_destroy(g_route);
		return 1;
	}
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}		
//& type: auto
//& purpose:  scenario to get the route bounding box.
/**
* @testcase 			ITc_maps_route_get_bounding_box_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the route bounding box.
* @scenario				maps_route_get_bounding_box
* @apicovered			maps_route_get_bounding_box
* @passcase				if maps_route_get_bounding_box passes
* @failcase				if maps_route_get_bounding_box fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_maps_route_get_bounding_box_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;
	maps_area_h bounding_box = NULL;
	
	nRet = maps_route_get_bounding_box(g_route, &bounding_box);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_get_bounding_box", MapServiceGetError(nRet),maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(bounding_box, "maps_route_get_bounding_box",maps_route_destroy(g_route));
				
    nRet = maps_area_destroy(bounding_box);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_area_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get the route destination.
/**
* @testcase 			ITc_maps_route_get_destination_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the route destination.
* @scenario				maps_route_get_destination
* @apicovered			maps_route_get_destination
* @passcase				if maps_route_get_destination passes
* @failcase				if maps_route_get_destination fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_get_destination_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;
	maps_coordinates_h destination = NULL;
	
	nRet = maps_route_get_destination(g_route, &destination);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_get_destination", MapServiceGetError(nRet),maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(destination, "maps_route_get_destination",maps_route_destroy(g_route));
	
    nRet = maps_coordinates_destroy(destination);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get the route distance unit.
/**
* @testcase 			ITc_maps_route_get_distance_unit_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the route distance unit.
* @scenario				maps_route_get_distance_unit
* @apicovered			maps_route_get_distance_unit
* @passcase				if maps_route_get_distance_unit passes
* @failcase				if maps_route_get_distance_unit fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_get_distance_unit_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;
	maps_distance_unit_e distance_unit = -1;
	
	nRet = maps_route_get_distance_unit(g_route, &distance_unit);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_get_distance_unit", MapServiceGetError(nRet),maps_route_destroy(g_route));
	
	if((distance_unit < MAPS_DISTANCE_UNIT_M)||(distance_unit > MAPS_DISTANCE_UNIT_YD))
	{
		FPRINTF("[Line : %d][%s] maps_route_get_distance_unit failed with invalid enum \\n", __LINE__, API_NAMESPACE);
		maps_route_destroy(g_route);
		return 1;
	}
	
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get the route origin.
/**
* @testcase 			ITc_maps_route_get_origin_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the route origin.
* @scenario				maps_route_get_origin
* @apicovered			maps_route_get_origin
* @passcase				if maps_route_get_origin passes
* @failcase				if maps_route_get_origin fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_get_origin_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;
	maps_coordinates_h origin = NULL;
	
	nRet = maps_route_get_origin(g_route, &origin);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_get_origin", MapServiceGetError(nRet),maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(origin, "maps_route_get_origin",maps_route_destroy(g_route));
	
    nRet = maps_coordinates_destroy(origin);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to get the route total distance.
/**
* @testcase 			ITc_maps_route_get_total_distance_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the route total distance.
* @scenario				maps_route_get_total_distance
* @apicovered			maps_route_get_total_distance
* @passcase				if maps_route_get_total_distance passes
* @failcase				if maps_route_get_total_distance fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_get_total_distance_p(void)
{
	START_TEST_ROUTE;

	int nRet;
	double total_distance = 0;
	
	nRet = maps_route_get_total_distance(g_route, &total_distance);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_get_total_distance", MapServiceGetError(nRet),maps_route_destroy(g_route));
	
	if(total_distance < 0)
	{
		FPRINTF("[Line : %d][%s] maps_route_get_total_distance returning negative value \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
  
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get the route total duration.
/**
* @testcase 			ITc_maps_route_get_total_duration_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the route total duration.
* @scenario				maps_route_get_total_duration
* @apicovered			maps_route_get_total_duration
* @passcase				if maps_route_get_total_duration passes
* @failcase				if maps_route_get_total_duration fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_get_total_duration_p(void)
{
	START_TEST_ROUTE;

	int nRet;
	long total_duration = 0;
	
	nRet = maps_route_get_total_duration(g_route, &total_duration);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_get_total_duration", MapServiceGetError(nRet),maps_route_destroy(g_route));
	
	if(total_duration < 0)
	{
		FPRINTF("[Line : %d][%s] maps_route_get_total_duration returning negative value \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
  
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get the route transport mode.
/**
* @testcase 			ITc_maps_route_get_transport_mode_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the route transport mode.
* @scenario				maps_route_get_transport_mode
* @apicovered			maps_route_get_transport_mode
* @passcase				if maps_route_get_transport_mode passes
* @failcase				if maps_route_get_transport_mode fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_get_transport_mode_p(void)
{
	START_TEST_ROUTE;

	int nRet;
	maps_route_transport_mode_e transport_mode = -1;
	
	nRet = maps_route_get_transport_mode(g_route, &transport_mode);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_get_transport_mode", MapServiceGetError(nRet),maps_route_destroy(g_route));
	
	if((transport_mode < MAPS_ROUTE_TRANSPORT_MODE_CAR)||(transport_mode > MAPS_ROUTE_TRANSPORT_MODE_TRUCK))
	{
		FPRINTF("[Line : %d][%s] maps_route_get_transport_mode failed with invalid enum \\n", __LINE__, API_NAMESPACE);
		maps_route_destroy(g_route);
		return 1;
	}
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to retrieve all segments of the route.
/**
* @testcase 			ITc_maps_route_foreach_segment_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to retrieve all segments of the route.
* @scenario				maps_route_foreach_segment
* @apicovered			maps_route_foreach_segment
* @passcase				if maps_route_foreach_segment passes
* @failcase				if maps_route_foreach_segment fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_foreach_segment_p(void)
{
	START_TEST_ROUTE;

	int nRet;
	
	g_nCheckCb = 0;
	g_nClone = 0;
	nRet = maps_route_foreach_segment(g_route, MapsRouteSegmentCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_foreach_segment", MapServiceGetError(nRet),maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_destroy(g_route);
		return 1;
	}
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to clone and destroy segment of the route.
/**
* @testcase 			ITc_maps_route_segment_clone_destroy_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to clone and destroy segment of the route.
* @scenario				maps_route_segment_clone, maps_route_segment_destroy
* @apicovered			maps_route_segment_clone, maps_route_segment_destroy
* @passcase				if maps_route_segment_clone, maps_route_segment_destroy passes
* @failcase				if maps_route_segment_clone, maps_route_segment_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_segment_clone_destroy_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;
	
	g_nCheckRet = 0;
	g_nCheckCb = 0;
	g_nClone = 1;
	nRet = maps_route_foreach_segment(g_route, MapsRouteSegmentCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_foreach_segment", MapServiceGetError(nRet),maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_segment_clone", MapServiceGetError(g_nCheckRet),maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_segment, "maps_route_segment_clone",maps_route_destroy(g_route));
	
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet),maps_route_destroy(g_route));
	
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get destination of the route.
/**
* @testcase 			ITc_maps_route_segment_get_destination_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get destination of the route.
* @scenario				maps_route_segment_get_destination
* @apicovered			maps_route_segment_get_destination
* @passcase				if maps_route_segment_get_destination passes
* @failcase				if maps_route_segment_get_destination fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_segment_get_destination_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;
	maps_coordinates_h destination = NULL;
	
	g_nCheckRet = 0;
	g_nCheckCb = 0;
	g_nClone = 1;
	nRet = maps_route_foreach_segment(g_route, MapsRouteSegmentCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_foreach_segment", MapServiceGetError(nRet),maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_segment_clone", MapServiceGetError(g_nCheckRet),maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_segment, "maps_route_segment_clone",maps_route_destroy(g_route));
	
	nRet = maps_route_segment_get_destination(g_route_segment, &destination);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_get_destination", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(destination, "maps_route_segment_get_destination",maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	nRet = maps_coordinates_destroy(destination);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get distance of the route.
/**
* @testcase 			ITc_maps_route_segment_get_distance_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get distance of the route.
* @scenario				maps_route_segment_get_distance
* @apicovered			maps_route_segment_get_distance
* @passcase				if maps_route_segment_get_distance passes
* @failcase				if maps_route_segment_get_distance fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_segment_get_distance_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;
	double distance = 0;
	
	g_nCheckRet = 0;
	g_nCheckCb = 0;
	g_nClone = 1;
	nRet = maps_route_foreach_segment(g_route, MapsRouteSegmentCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_foreach_segment", MapServiceGetError(nRet),maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_segment_clone", MapServiceGetError(g_nCheckRet),maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_segment, "maps_route_segment_clone",maps_route_destroy(g_route));
	
	nRet = maps_route_segment_get_distance(g_route_segment, &distance);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_get_distance", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	if(distance < 0)
	{
		FPRINTF("[Line : %d][%s] distance negative value \\n", __LINE__, API_NAMESPACE);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get duration of the route.
/**
* @testcase 			ITc_maps_route_segment_get_duration_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get duration of the route.
* @scenario				maps_route_segment_get_duration
* @apicovered			maps_route_segment_get_duration
* @passcase				if maps_route_segment_get_duration passes
* @failcase				if maps_route_segment_get_duration fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_segment_get_duration_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;
	long duration = 0;

	g_nCheckRet = 0;
	g_nCheckCb = 0;
	g_nClone = 1;
	nRet = maps_route_foreach_segment(g_route, MapsRouteSegmentCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_foreach_segment", MapServiceGetError(nRet),maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_segment_clone", MapServiceGetError(g_nCheckRet),maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_segment, "maps_route_segment_clone",maps_route_destroy(g_route));
	
	nRet = maps_route_segment_get_duration(g_route_segment, &duration);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_get_duration", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	if(duration < 0)
	{
		FPRINTF("[Line : %d][%s] duration negative value \\n", __LINE__, API_NAMESPACE);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get origin of the route.
/**
* @testcase 			ITc_maps_route_segment_get_origin_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get origin of the route.
* @scenario				maps_route_segment_get_origin
* @apicovered			maps_route_segment_get_origin
* @passcase				if maps_route_segment_get_origin passes
* @failcase				if maps_route_segment_get_origin fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_segment_get_origin_p(void)
{
	START_TEST_ROUTE;
	
	int nRet;
	maps_coordinates_h origin = NULL;
	
	g_nCheckRet = 0;
	g_nCheckCb = 0;
	g_nClone = 1;
	nRet = maps_route_foreach_segment(g_route, MapsRouteSegmentCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_foreach_segment", MapServiceGetError(nRet),maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_segment_clone", MapServiceGetError(g_nCheckRet),maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_segment, "maps_route_segment_clone",maps_route_destroy(g_route));
	
	nRet = maps_route_segment_get_origin(g_route_segment, &origin);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_get_origin", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(origin, "maps_route_segment_get_origin",maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	nRet = maps_coordinates_destroy(origin);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to retrieve all paths.
/**
* @testcase 			ITc_maps_route_segment_foreach_path_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to retrieve all paths.
* @scenario				maps_route_segment_foreach_path
* @apicovered			maps_route_segment_foreach_path
* @passcase				if maps_route_segment_foreach_path passes
* @failcase				if maps_route_segment_foreach_path fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_segment_foreach_path_p(void)
{
	START_TEST_ROUTE;

	int nRet;

	g_nCheckRet = 0;
	g_nCheckCb = 0;
	g_nClone = 1;
	nRet = maps_route_foreach_segment(g_route, MapsRouteSegmentCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_foreach_segment", MapServiceGetError(nRet),maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_segment_clone", MapServiceGetError(g_nCheckRet),maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_segment, "maps_route_segment_clone",maps_route_destroy(g_route));
	
	g_nCheckCb = 0;
	
	nRet = maps_route_segment_foreach_path(g_route_segment, MapsRouteSegmentPathCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_foreach_path", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentPathCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}   
/** @} */
/** @} */
