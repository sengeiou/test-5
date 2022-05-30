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
static maps_route_maneuver_h g_route_maneuver = NULL;

/** @addtogroup itc-maps-service
*  @ingroup itc
*  @{
*/							   
static bool MapsRouteSegmentManeuverCb(int index, int total, maps_route_maneuver_h maneuver, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsRouteSegmentManeuverCb callback\\n", __LINE__, API_NAMESPACE); 
	g_nCheckCb = true;
	if(g_nClone == 1)
	{
		g_nCheckRet = maps_route_maneuver_clone(maneuver, &g_route_maneuver);
	}
	
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
	    FPRINTF("[Line : %d][%s] maps_route_clone NULL\\n", __LINE__, API_NAMESPACE);
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
 * @function 		ITs_maps_route_maneuver_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_route_maneuver_startup(void)
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
 * @function 		ITs_maps_route_maneuver_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_route_maneuver_cleanup(void)
{
	return;
}
//& type: auto
//& purpose:  scenario to retrieve all maneuvers of the path.
/**
* @testcase 			ITc_maps_route_segment_foreach_maneuver_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to retrieve all maneuvers of the path.
* @scenario				maps_route_segment_foreach_maneuver
* @apicovered			maps_route_segment_foreach_maneuver
* @passcase				if maps_route_segment_foreach_maneuver passes
* @failcase				if maps_route_segment_foreach_maneuver fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_segment_foreach_maneuver_p(void)
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
	g_nClone = 0;
	nRet = maps_route_segment_foreach_maneuver(g_route_segment, MapsRouteSegmentManeuverCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_foreach_maneuver", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentManeuverCb not invoked \\n", __LINE__, API_NAMESPACE);
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
//& purpose:  scenario to clone and destroy maneuvers of the path.
/**
* @testcase 			ITc_maps_route_maneuver_clone_destroy_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to clone and destroy maneuvers of the path.
* @scenario				maps_route_maneuver_clone, maps_route_maneuver_destroy
* @apicovered			maps_route_maneuver_clone, maps_route_maneuver_destroy
* @passcase				if maps_route_maneuver_clone, maps_route_maneuver_destroy passes
* @failcase				if maps_route_maneuver_clone, maps_route_maneuver_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_maneuver_clone_destroy_p(void)
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
	
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_route_segment_foreach_maneuver(g_route_segment, MapsRouteSegmentManeuverCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_foreach_maneuver", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentManeuverCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_maneuver_clone", MapServiceGetError(g_nCheckRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_maneuver, "maps_route_maneuver_clone",maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	nRet = maps_route_maneuver_destroy(g_route_maneuver);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_destroy", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}	
//& type: auto
//& purpose:  scenario to get direction id of maneuvers of the path..
/**
* @testcase 			ITc_maps_route_maneuver_get_direction_id_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get direction id of maneuvers of the path.
* @scenario				maps_route_maneuver_get_direction_id
* @apicovered			maps_route_maneuver_get_direction_id
* @passcase				if maps_route_maneuver_get_direction_id passes
* @failcase				if maps_route_maneuver_get_direction_id fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_maneuver_get_direction_id_p(void)
{
	START_TEST_ROUTE;

	int nRet;
	maps_route_direction_e direction_id = -1;
	
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
	
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_route_segment_foreach_maneuver(g_route_segment, MapsRouteSegmentManeuverCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_foreach_maneuver", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentManeuverCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_maneuver_clone", MapServiceGetError(g_nCheckRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_maneuver, "maps_route_maneuver_clone",maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	nRet = maps_route_maneuver_get_direction_id(g_route_maneuver, &direction_id);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_get_direction_id", MapServiceGetError(nRet),maps_route_maneuver_destroy(g_route_maneuver);maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	if( (direction_id < MAPS_ROUTE_DIRECTION_NONE)||(direction_id > MAPS_ROUTE_DIRECTION_EAST) )
	{
		FPRINTF("[Line : %d][%s] maps_route_maneuver_get_direction_id failed with invalid enum \\n", __LINE__, API_NAMESPACE);
		maps_route_maneuver_destroy(g_route_maneuver);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	nRet = maps_route_maneuver_destroy(g_route_maneuver);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_destroy", MapServiceGetError(nRet));
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}	
//& type: auto
//& purpose:  scenario to get the distance to next instruction of the route maneuver.
/**
* @testcase 			ITc_maps_route_maneuver_get_distance_to_next_instruction_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			Gets the distance to next instruction of the route maneuver.
* @scenario				maps_route_maneuver_get_distance_to_next_instruction
* @apicovered			maps_route_maneuver_get_distance_to_next_instruction
* @passcase				if maps_route_maneuver_get_distance_to_next_instruction passes
* @failcase				if maps_route_maneuver_get_distance_to_next_instruction fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_maneuver_get_distance_to_next_instruction_p(void)
{
	START_TEST_ROUTE;

	int nRet;
	double distance_to_next_instruction = 0;

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
	
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_route_segment_foreach_maneuver(g_route_segment, MapsRouteSegmentManeuverCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_foreach_maneuver", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentManeuverCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_maneuver_clone", MapServiceGetError(g_nCheckRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_maneuver, "maps_route_maneuver_clone",maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	nRet = maps_route_maneuver_get_distance_to_next_instruction(g_route_maneuver,&distance_to_next_instruction);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_get_distance_to_next_instruction", MapServiceGetError(nRet),maps_route_maneuver_destroy(g_route_maneuver);maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));						
	
	if(distance_to_next_instruction < 0)
	{
		FPRINTF("[Line : %d][%s] maps_route_maneuver_get_distance_to_next_instruction failed with invalid value \\n", __LINE__, API_NAMESPACE);
		maps_route_maneuver_destroy(g_route_maneuver);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	
	nRet = maps_route_maneuver_destroy(g_route_maneuver);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_destroy", MapServiceGetError(nRet));
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get the instruction text (narrative) of the route maneuver.
/**
* @testcase 			ITc_maps_route_maneuver_get_instruction_text_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the instruction text (narrative) of the route maneuver.
* @scenario				maps_route_maneuver_get_instruction_text
* @apicovered			maps_route_maneuver_get_instruction_text
* @passcase				if maps_route_maneuver_get_instruction_text passes
* @failcase				if maps_route_maneuver_get_instruction_text fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_maneuver_get_instruction_text_p(void)
{
	START_TEST_ROUTE;

	int nRet;
	char *instruction_text = NULL;
	
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
	
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_route_segment_foreach_maneuver(g_route_segment, MapsRouteSegmentManeuverCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_foreach_maneuver", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentManeuverCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_maneuver_clone", MapServiceGetError(g_nCheckRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_maneuver, "maps_route_maneuver_clone",maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	nRet = maps_route_maneuver_get_instruction_text(g_route_maneuver, &instruction_text);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_get_instruction_text", MapServiceGetError(nRet),maps_route_maneuver_destroy(g_route_maneuver);maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));						
	CHECK_HANDLE_CLEANUP(instruction_text, "maps_route_maneuver_get_instruction_text",maps_route_maneuver_destroy(g_route_maneuver);maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
    free(instruction_text);
	nRet = maps_route_maneuver_destroy(g_route_maneuver);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_destroy", MapServiceGetError(nRet));
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get the route maneuver position..
/**
* @testcase 			ITc_maps_route_maneuver_get_position_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the route maneuver position..
* @scenario				maps_route_maneuver_get_position
* @apicovered			maps_route_maneuver_get_position
* @passcase				if maps_route_maneuver_get_position passes
* @failcase				if maps_route_maneuver_get_position fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_maneuver_get_position_p(void)
{
	START_TEST_ROUTE;

	int nRet;
	maps_coordinates_h position = NULL;

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
	
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_route_segment_foreach_maneuver(g_route_segment, MapsRouteSegmentManeuverCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_foreach_maneuver", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentManeuverCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_maneuver_clone", MapServiceGetError(g_nCheckRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_maneuver, "maps_route_maneuver_clone",maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	nRet = maps_route_maneuver_get_position(g_route_maneuver, &position);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_get_position", MapServiceGetError(nRet),maps_route_maneuver_destroy(g_route_maneuver);maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));						
	CHECK_HANDLE_CLEANUP(position, "maps_route_maneuver_get_position",maps_route_maneuver_destroy(g_route_maneuver);maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
    nRet = maps_coordinates_destroy(position);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	
	nRet = maps_route_maneuver_destroy(g_route_maneuver);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_destroy", MapServiceGetError(nRet));
	
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get the time to next instruction of the route maneuver.
/**
* @testcase 			ITc_maps_route_maneuver_get_time_to_next_instruction_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the time to next instruction of the route maneuver.
* @scenario				maps_route_maneuver_get_time_to_next_instruction
* @apicovered			maps_route_maneuver_get_time_to_next_instruction
* @passcase				if maps_route_maneuver_get_time_to_next_instruction passes
* @failcase				if maps_route_maneuver_get_time_to_next_instruction fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_maneuver_get_time_to_next_instruction_p(void)
{
	START_TEST_ROUTE;

	int nRet;
	int time_to_next_instruction = 0;

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
	
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_route_segment_foreach_maneuver(g_route_segment, MapsRouteSegmentManeuverCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_foreach_maneuver", MapServiceGetError(nRet),maps_route_destroy(g_route);maps_route_segment_destroy(g_route_segment));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentManeuverCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_maneuver_clone", MapServiceGetError(g_nCheckRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_maneuver, "maps_route_maneuver_clone",maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	
	nRet = maps_route_maneuver_get_time_to_next_instruction(g_route_maneuver, &time_to_next_instruction);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_get_time_to_next_instruction", MapServiceGetError(nRet),maps_route_maneuver_destroy(g_route_maneuver);maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));						
	if(time_to_next_instruction < 0)
	{
		FPRINTF("[Line : %d][%s] maps_route_maneuver_get_time_to_next_instruction failed with invalid value \\n", __LINE__, API_NAMESPACE);
		maps_route_maneuver_destroy(g_route_maneuver);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	nRet = maps_route_maneuver_destroy(g_route_maneuver);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_destroy", MapServiceGetError(nRet));
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to gets the route maneuver turn type.
/**
* @testcase 			ITc_maps_route_maneuver_get_turn_type_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to gets the route maneuver turn type.
* @scenario				maps_route_maneuver_get_turn_type
* @apicovered			maps_route_maneuver_get_turn_type
* @passcase				if maps_route_maneuver_get_turn_type passes
* @failcase				if maps_route_maneuver_get_turn_type fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_route_maneuver_get_turn_type_p(void)
{
	START_TEST_ROUTE;

	int nRet;
	maps_route_turn_type_e turn_type = -1;

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
	
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_route_segment_foreach_maneuver(g_route_segment, MapsRouteSegmentManeuverCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_segment_foreach_maneuver", MapServiceGetError(nRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsRouteSegmentManeuverCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_route_maneuver_clone", MapServiceGetError(g_nCheckRet),maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));
	CHECK_HANDLE_CLEANUP(g_route_maneuver, "maps_route_maneuver_clone",maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));

	nRet = maps_route_maneuver_get_turn_type(g_route_maneuver, &turn_type);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_get_turn_type", MapServiceGetError(nRet),maps_route_maneuver_destroy(g_route_maneuver);maps_route_segment_destroy(g_route_segment);maps_route_destroy(g_route));						
	
	if((turn_type < MAPS_ROUTE_TURN_TYPE_NONE)||(turn_type > MAPS_ROUTE_TURN_TYPE_STRAIGHT_FORK))
	{
		FPRINTF("[Line : %d][%s] maps_route_maneuver_get_turn_type failed with invalid enum \\n", __LINE__, API_NAMESPACE);
		maps_route_maneuver_destroy(g_route_maneuver);
		maps_route_segment_destroy(g_route_segment);
		maps_route_destroy(g_route);
		return 1;
	}
	nRet = maps_route_maneuver_destroy(g_route_maneuver);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_maneuver_destroy", MapServiceGetError(nRet));
	nRet = maps_route_segment_destroy(g_route_segment);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_segment_destroy", MapServiceGetError(nRet));
	nRet = maps_route_destroy(g_route);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_route_destroy", MapServiceGetError(nRet));
	
	return 0;
}
		   
/** @} */
/** @} */
