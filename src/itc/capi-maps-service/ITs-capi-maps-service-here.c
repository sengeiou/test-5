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
static gboolean Timeout_Function(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

//& set: MapsService

static bool MapServiceMultiRevGeocodeCb(maps_error_e result, int request_id, int total, maps_address_list_h address_list, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapServiceMultiRevGeocodeCb callback\\n", __LINE__, API_NAMESPACE);
	maps_address_list_destroy(address_list);

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
static bool MapsServiceProviderForeachCb(char* maps_provider, void* user_data)
{
	memset( g_szMapsProvider, '\0', sizeof(char)*BUFFER);
	strncpy(g_szMapsProvider, "HERE", sizeof(g_szMapsProvider)-1);
	FPRINTF("[Line : %d][%s] Provider list from maps_service_foreach_provider is = %s\\n", __LINE__, API_NAMESPACE, g_szMapsProvider);	
	g_nCheckCb = true;
	return false;
}

// Callback function to get coordinates of the given address
static bool MapsLocationCoordinatesCb(maps_error_e result, int request_id, int index, int total, maps_coordinates_h coord, void* user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsLocationCoordinatesCb callback\\n", __LINE__, API_NAMESPACE);
	maps_coordinates_destroy(coord);
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

// Callback function to get address of the given coordinates
static void MapsCoordinatesAddressCb(maps_error_e result, int request_id, int index, int total, maps_address_h address, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsCoordinatesAddressCb callback\\n", __LINE__, API_NAMESPACE);
	maps_address_destroy(address);
	if (index + 1 < total) return;

	g_nCheckCb = true;

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

// Callback function to search place by coordinates
static bool MapsServiceSearchPlaceCb(maps_error_e error, int request_id , int index, int total, maps_place_h place, void* user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsServiceSearchPlaceCb callback\\n", __LINE__, API_NAMESPACE);
	maps_place_destroy(place);
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

// Callback function to get the place view URI
static bool MapsPlaceCb(int index, maps_place_h place, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsPlaceCb callback\\n", __LINE__, API_NAMESPACE);
	if(index ==0)
	{	
		maps_place_get_uri(place,&g_szPlaceURI);
	}

	return true;
}

// Callback function to search place list by coordinates
static void MapsServiceSearchPlaceListCb(maps_error_e error, int request_id, int total, maps_place_list_h place_list, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsServiceSearchPlaceListCb callback\\n", __LINE__, API_NAMESPACE);

	g_nCheckCb = true;

	if(place_list)
		maps_place_list_foreach(place_list,MapsPlaceCb,NULL);

	if(place_list)
		maps_place_list_destroy(place_list);

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

// Callback function 
static void MapsServiceGetPlaceDetailsCb(maps_error_e error, int request_id, maps_place_h place, void *user_data)
{
	g_nCheckCb = true;
	if(place)
		maps_place_destroy(place);

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

// Callback function to get search route
static bool MapsServiceRouteFoundCb(maps_error_e error, int request_id, int index, int total, maps_route_h route, void* user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsServiceRouteFoundCb callback\\n", __LINE__, API_NAMESPACE);
	maps_route_destroy(route);
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

static void MapsServiceRequestUserConsentCb(bool consented, const char *maps_provider, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsServiceRequestUserConsentCb callback\\n", __LINE__, API_NAMESPACE);
	g_nCheckCb = true;

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
 * @function 		ITs_maps_service_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_startup(void)
{
	int nResults = 10;
    g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
    bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	int nRet = maps_service_foreach_provider(MapsServiceProviderForeachCb, NULL);
	if ( false == bMapsFeatureSupported)
	{
		g_bFeatureSupported = false;
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_foreach_provider API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_foreach_provider API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}
	if ( nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_service_foreach_provider fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_bFeatureMismatch = true;
		return;
	}
	else {
		memset( g_szMapsProvider, '\0', sizeof(char)*BUFFER);
		strncpy(g_szMapsProvider, "HERE", sizeof(g_szMapsProvider)-1);
		FPRINTF("[Line : %d][%s] Provider list from maps_service_foreach_provider is = %s\\n", __LINE__, API_NAMESPACE, g_szMapsProvider);
	}

	nRet = maps_service_create(g_szMapsProvider, &g_hMapService);
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_service_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_hMapService = NULL;
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
		return;
	}

	nRet = maps_service_set_provider_key(g_hMapService, pstrValue);
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_service_set_provider_key fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		maps_service_destroy(g_hMapService);
		g_hMapService = NULL;
		return;
	}

	nRet = maps_preference_create(&g_hMapsPref);
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_preference_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_hMapsPref = NULL;
	}

	nRet = maps_preference_set_max_results(g_hMapsPref, nResults);
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_preference_set_max_results fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_hMapsPref = NULL;
	}	
	return;
}


/**
 * @function 		ITs_maps_service_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_cleanup(void)
{
	int nRet = -1;
	if(g_hMapService != NULL)
	{
		nRet = maps_service_destroy(g_hMapService);
		if ( nRet != MAPS_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] maps_service_destroy fail in cleanup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		}
		g_hMapService = NULL;
	}

	if(g_hMapsPref != NULL)
	{
		nRet = maps_preference_destroy(g_hMapsPref);
		if ( nRet != MAPS_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] maps_preference_destroy fail in cleanup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		}
		g_hMapsPref = NULL;
	}
	return;
}

//& type: auto
//& purpose:  scenario to creates and destroy new maps service handle
/**
* @testcase 			ITc_maps_service_create_destroy_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to creates and destroy new maps service handle
* @scenario				creates new maps service handle \n
* 						destroy maps service handle\n
* @apicovered			maps_service_create, maps_service_destroy
* @passcase				if maps_service_create and maps_service_destroy passes
* @failcase				if maps_service_create or maps_service_destroy fails or handle created is NULL
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_create_destroy_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	maps_service_h hMapsService = NULL;

	int nRet = maps_service_create(g_szMapsProvider, &hMapsService);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hMapsService,"maps_service_create");

	nRet = maps_service_destroy(hMapsService);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_destroy", MapServiceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the maps preference
/**
* @testcase 			ITc_maps_service_set_get_preference_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the maps preference
* @scenario				set the maps preference \n
* 						get the maps preference\n
* @apicovered			maps_service_set_preference, maps_service_get_preference
* @passcase				if maps_service_set_preference and maps_service_get_preference passes
* @failcase				if maps_service_set_preference or maps_service_get_preference fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_set_get_preference_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");	
	maps_preference_h hMapsGetPref = NULL;

	int nRet = maps_service_set_preference(g_hMapService, g_hMapsPref);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_set_preference", MapServiceGetError(nRet));

	nRet = maps_service_get_preference(g_hMapService, &hMapsGetPref);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_get_preference", MapServiceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the maps key for maps service request
/**
* @testcase 			ITc_maps_service_set_get_provider_key_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the maps key for maps service request
* @scenario				set the maps key for maps service request \n
* 						get the maps key for maps service request \n
* 						compare the set and get values \n
* @apicovered			maps_service_set_provider_key, maps_service_get_provider_key
* @passcase				if maps_service_set_provider_key, maps_service_get_provider_key passes and set and get key values match
* @failcase				if maps_service_set_provider_key or maps_service_get_provider_key fails or set and get key values doesn't match
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_set_get_provider_key_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	char *pszGetKey = NULL;
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
		return 1;
	}

	int nRet = maps_service_set_provider_key(g_hMapService, pstrValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_set_provider_key", MapServiceGetError(nRet));

	nRet = maps_service_get_provider_key(g_hMapService, &pszGetKey);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_get_provider_key", MapServiceGetError(nRet));
	FPRINTF("[Line : %d][%s] maps_service_get_provider_key is = %s\\n", __LINE__, API_NAMESPACE, pszGetKey);

	if(pszGetKey == NULL)
	{
		FPRINTF("[Line : %d][%s] Get value = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(strcmp(pstrValue, pszGetKey) != 0)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pstrValue, pszGetKey);
		FREE_MEMORY(pszGetKey);
		return 1;
	}
	FREE_MEMORY(pszGetKey);

	return 0;
}


//& type: auto
//& purpose:  scenario to check if the Maps Service supports a request and data feature
/**
* @testcase 			ITc_maps_service_provider_is_service_data_supported_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to check if the Maps Service supports a request and data feature
* @scenario				check if the Maps Service supports a request \n
* 						check if the Maps Service supports a data feature \n
* @apicovered			maps_service_provider_is_service_supported, maps_service_provider_is_data_supported
* @passcase				if maps_service_provider_is_service_supported, maps_service_provider_is_data_supported passes and set and get key values match
* @failcase				if maps_service_provider_is_service_supported or maps_service_provider_is_data_supported fails or set and get key values doesn't match
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_provider_is_service_data_supported_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	bool bSeviceSupported = false;
	bool bDataSupported = false;

	int nRet = maps_service_provider_is_service_supported(g_hMapService, MAPS_SERVICE_GEOCODE, &bSeviceSupported);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_provider_is_service_supported", MapServiceGetError(nRet));

	nRet = maps_service_provider_is_data_supported(g_hMapService, MAPS_PLACE_ADDRESS, &bDataSupported);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_provider_is_data_supported", MapServiceGetError(nRet));

	if(bSeviceSupported != true && bSeviceSupported != false)
	{
		FPRINTF("[Line : %d][%s] Output bool value for API maps_service_provider_is_service_supported is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(bDataSupported != true && bDataSupported != false)
	{
		FPRINTF("[Line : %d][%s] Output bool value for API maps_service_provider_is_data_supported is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose:  scenario to get the list of available Maps Providers
/**
* @testcase 			ITc_maps_service_foreach_provider_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to get the list of available Maps Providers
* @scenario				get the list of available Maps Providers \n
* @apicovered			maps_service_foreach_provider
* @passcase				if maps_service_foreach_provider passes and the list is not NULL
* @failcase				if maps_service_foreach_provider fails or the list is NULL
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_foreach_provider_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	
	g_nCheckCb = false;

	int nRet = maps_service_foreach_provider(MapsServiceProviderForeachCb, NULL);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_foreach_provider", MapServiceGetError(nRet));

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Provider list from maps_service_foreach_provider is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose:  scenario to get the position coordinates for a given address
/**
* @testcase 			ITc_maps_service_geocode_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to get the position coordinates for a given address
* @scenario				create the preference \n
* 						get the position coordinates for a given address \n
* @apicovered			maps_service_geocode
* @passcase				if maps_service_geocode passes and the callback function is hit
* @failcase				if maps_service_geocode fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_geocode_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	g_nCheckCb = false;
	int nRequestId = 0;
	char *pszPlaceName = "Berlin";
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_service_geocode(g_hMapService, pszPlaceName, g_hMapsPref, MapsLocationCoordinatesCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_geocode API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_geocode API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_geocode", MapServiceGetError(nRet));

	RUN_POLLING_LOOP;
	
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Coordinates are not received from maps_service_geocode \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose:  scenario to cancels the service request
/**
* @testcase 			ITc_maps_service_cancel_request_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to cancels the service request
* @scenario				create the preference \n
* 						get the position coordinates for a given address \n
* 						cancels the service request \n
* @apicovered			maps_service_cancel_request, maps_service_geocode
* @passcase				if maps_service_cancel_request passes and the callback function is hit
* @failcase				if maps_service_cancel_request fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_cancel_request_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	g_nCheckCb = false;
	int nRequestId = 0;
	char *pszPlaceName = "London";

	int nRet = maps_service_geocode(g_hMapService, pszPlaceName, g_hMapsPref, MapsLocationCoordinatesCb, NULL, &nRequestId);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_geocode", MapServiceGetError(nRet));

	nRet = maps_service_cancel_request(g_hMapService, nRequestId);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_cancel_request", MapServiceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose:  scenario to get the position coordinates for a given structured address
/**
* @testcase 			ITc_maps_service_geocode_by_structured_address_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to get the position coordinates for a given structured address
* @scenario				create the preference \n
* 						create the address for a city \n
* 						get the position coordinates for a given structured address \n
* @apicovered			maps_service_geocode_by_structured_address
* @passcase				if maps_service_geocode_by_structured_address passes and the callback function is hit
* @failcase				if maps_service_geocode_by_structured_address fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_geocode_by_structured_address_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	g_nCheckCb = false;
	int nRequestId = 0;
	maps_address_h hAddress = NULL;
	char *pszPlaceName = "Berlin";
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_address_create(&hAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hAddress, "maps_preference_create");

	nRet = maps_address_set_city(hAddress, pszPlaceName);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_address_set_city", MapServiceGetError(nRet), maps_address_destroy(hAddress));

	nRet = maps_service_geocode_by_structured_address(g_hMapService, hAddress, g_hMapsPref, MapsLocationCoordinatesCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_geocode_by_structured_address API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_geocode_by_structured_address API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_geocode_by_structured_address", MapServiceGetError(nRet), maps_address_destroy(hAddress));

	RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Coordinates are not received from maps_service_geocode_by_structured_address \\n", __LINE__, API_NAMESPACE);
		maps_address_destroy(hAddress);
		return 1;
	}

	maps_address_destroy(hAddress);
	return 0;
}

//& type: auto
//& purpose:  scenario to get the position coordinates for a given address within the specified bounding box
/**
* @testcase 			ITc_maps_service_geocode_inside_area_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to get the position coordinates for a given address within the specified bounding box
* @scenario				create the preference \n
* 						create the address for a city \n
* 						get the position coordinates for a given address within the specified bounding box \n
* @apicovered			maps_service_geocode_inside_area
* @passcase				if maps_service_geocode_inside_area passes and the callback function is hit
* @failcase				if maps_service_geocode_inside_area fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_geocode_inside_area_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	g_nCheckCb = false;
	int nRequestId = 0;
	maps_area_h hArea = NULL;
	maps_coordinates_h hTopLeft = NULL;
	maps_coordinates_h hBottomRight = NULL;
	char *pszPlaceName = "Berlin";
	double dTopLatitude = 53.507651, dTopLongitude = 10.068970;
	double dBotmLatitude = 51.055207, dBotmLongitude = 17.111206;
    bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dTopLatitude, dTopLongitude, &hTopLeft);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hTopLeft, "maps_coordinates_create");

	nRet = maps_coordinates_create(dBotmLatitude, dBotmLongitude, &hBottomRight);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet),maps_coordinates_destroy(hTopLeft));
	CHECK_HANDLE_CLEANUP(hBottomRight, "maps_coordinates_create", maps_coordinates_destroy(hTopLeft));

	nRet = maps_area_create_rectangle(hTopLeft, hBottomRight, &hArea);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_area_create_rectangle", MapServiceGetError(nRet), 
						 maps_coordinates_destroy(hTopLeft); maps_coordinates_destroy(hBottomRight));
	CHECK_HANDLE_CLEANUP(hArea, "maps_area_create_rectangle", 
						 maps_coordinates_destroy(hTopLeft); maps_coordinates_destroy(hBottomRight));

	nRet = maps_service_geocode_inside_area(g_hMapService, pszPlaceName, hArea, g_hMapsPref, MapsLocationCoordinatesCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_geocode_inside_area API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_geocode_inside_area API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_geocode_inside_area", MapServiceGetError(nRet), 
						 maps_coordinates_destroy(hTopLeft); maps_coordinates_destroy(hBottomRight); maps_area_destroy(hArea));

	RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Coordinates are not received from maps_service_geocode_inside_area \\n", __LINE__, API_NAMESPACE);
		maps_coordinates_destroy(hTopLeft);
		maps_coordinates_destroy(hBottomRight);
		maps_area_destroy(hArea);
		return 1;
	}

	maps_coordinates_destroy(hTopLeft);
	maps_coordinates_destroy(hBottomRight);
	maps_area_destroy(hArea);	
	return 0;
}

//& type: auto
//& purpose:  scenario to get the address for a given position coordinates
/**
* @testcase 			ITc_maps_service_reverse_geocode_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to get the address for a given position coordinates
* @scenario				create the preference \n
* 						get the address for a given position coordinates \n
* @apicovered			maps_service_reverse_geocode
* @passcase				if maps_service_reverse_geocode passes and the callback function is hit
* @failcase				if maps_service_reverse_geocode fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_reverse_geocode_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	g_nCheckCb = false;
	int nRequestId = 0;
	double dLatitude = 25.944594, dLongitude = 62.554303;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_service_reverse_geocode(g_hMapService, dLatitude, dLongitude, g_hMapsPref, MapsCoordinatesAddressCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_reverse_geocode API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_reverse_geocode API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			return 0;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_reverse_geocode", MapServiceGetError(nRet));

	RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Coordinates are not received from maps_service_reverse_geocode \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose:  scenario to obtain the place information for a specified distance around a given coordinates position
/**
* @testcase 			ITc_maps_service_search_place_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to obtain the place information for a specified distance around a given coordinates position
* @scenario				create the preference \n
* 						create filter handle and set keyword and place name \n
* 						create coordinates handle \n
* 						obtain the place information for a specified distance around a given coordinates position \n
* @apicovered			maps_service_search_place, maps_place_filter_create, maps_place_filter_set_keyword, maps_place_filter_set_place_name, maps_coordinates_create
* @passcase				if maps_service_search_place passes and the callback function is hit
* @failcase				if maps_service_search_place fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_search_place_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	g_nCheckCb = false;
	int nRequestId = 0, nDistance = 500;
	char *pszKeyword = "restaurant";
	double dLatitude = 52.5167, dLongitude = 13.383;
	maps_place_filter_h hPlaceFilter = NULL;
	maps_coordinates_h hMapCoords = NULL;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_place_filter_create(&hPlaceFilter);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_create", MapServiceGetError(nRet));

	nRet = maps_place_filter_set_keyword(hPlaceFilter, pszKeyword);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_keyword", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_place_filter_set_place_name(hPlaceFilter, "Berlin");
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_place_name", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_coordinates_create(dLatitude, dLongitude, &hMapCoords);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_service_search_place(g_hMapService, hMapCoords, nDistance, hPlaceFilter, g_hMapsPref, MapsServiceSearchPlaceCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_search_place", MapServiceGetError(nRet),
						 maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hMapCoords));

	RUN_POLLING_LOOP;
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Place is not received from maps_service_search_place \\n", __LINE__, API_NAMESPACE);
		maps_place_filter_destroy(hPlaceFilter);
		maps_coordinates_destroy(hMapCoords);
		return 1;
	}

	nRet = maps_place_filter_destroy(hPlaceFilter);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_destroy", MapServiceGetError(nRet),
						 maps_coordinates_destroy(hMapCoords));
	nRet = maps_coordinates_destroy(hMapCoords);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_destroy", MapServiceGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to obtain the place information for a specified free-formed address string
/**
* @testcase 			ITc_maps_service_search_place_by_address_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to obtain the place information for a specified free-formed address string
* @scenario				create the preference \n
* 						create filter handle and set keyword and place name \n
* 						create area handle by top left and bottom right \n
* 						obtain the place information for a specified free-formed address string \n
* @apicovered			maps_service_search_place_by_address, maps_place_filter_create, maps_place_filter_set_keyword, maps_place_filter_set_place_name, maps_coordinates_create, maps_area_create_rectangle
* @passcase				if maps_service_search_place_by_address passes and the callback function is hit
* @failcase				if maps_service_search_place_by_address fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_search_place_by_address_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	g_nCheckCb = false;
	int nRequestId = 0;
	char *pszKeyword = "restaurant", *pszPlaceName = "Berlin";
	double dTopLatitude = 15.665354, dTopLongitude = 74.311523;
	double dBotmLatitude = 10.617418, dBotmLongitude = 79.145508;
	maps_place_filter_h hPlaceFilter = NULL;
	maps_area_h hArea = NULL;
	maps_coordinates_h hTopLeft = NULL;
	maps_coordinates_h hBottomRight = NULL;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_place_filter_create(&hPlaceFilter);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_create", MapServiceGetError(nRet));

	nRet = maps_place_filter_set_keyword(hPlaceFilter, pszKeyword);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_keyword", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_place_filter_set_place_name(hPlaceFilter, pszPlaceName);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_place_name", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_coordinates_create(dTopLatitude, dTopLongitude, &hTopLeft);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));
	CHECK_HANDLE_CLEANUP(hTopLeft, "maps_coordinates_create", maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_coordinates_create(dBotmLatitude, dBotmLongitude, &hBottomRight);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet),
						 maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hTopLeft));
	CHECK_HANDLE_CLEANUP(hBottomRight, "maps_coordinates_create", maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hTopLeft));

	nRet = maps_area_create_rectangle(hTopLeft, hBottomRight, &hArea);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_area_create_rectangle", MapServiceGetError(nRet), 
						 maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hTopLeft); maps_coordinates_destroy(hBottomRight));
	CHECK_HANDLE_CLEANUP(hArea, "maps_area_create_rectangle", 
						 maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hTopLeft); maps_coordinates_destroy(hBottomRight));

	nRet = maps_service_search_place_by_address(g_hMapService, pszPlaceName, hArea, hPlaceFilter, g_hMapsPref, MapsServiceSearchPlaceCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place_by_address API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place_by_address API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_search_place_by_address", MapServiceGetError(nRet),
						 maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hTopLeft); maps_coordinates_destroy(hBottomRight); maps_area_destroy(hArea));

	RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Place is not received from maps_service_search_place_by_address \\n", __LINE__, API_NAMESPACE);
		maps_place_filter_destroy(hPlaceFilter);
		maps_coordinates_destroy(hTopLeft);
		maps_coordinates_destroy(hBottomRight);
		maps_area_destroy(hArea);
		return 1;
	}

	maps_place_filter_destroy(hPlaceFilter);
	maps_coordinates_destroy(hTopLeft);
	maps_coordinates_destroy(hBottomRight);
	maps_area_destroy(hArea);
	return 0;
}

//& type: auto
//& purpose:  scenario to obtain the place information for a specified coordinates boundary
/**
* @testcase 			ITc_maps_service_search_place_by_area_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to obtain the place information for a specified coordinates boundary
* @scenario				create the preference \n
* 						create filter handle and set keyword and place name \n
* 						create area handle by top left and bottom right \n
* 						obtain the place information for a specified coordinates boundary \n
* @apicovered			maps_service_search_place_by_area, maps_place_filter_create, maps_place_filter_set_keyword, maps_place_filter_set_place_name, maps_coordinates_create, maps_area_create_rectangle
* @passcase				if maps_service_search_place_by_area passes and the callback function is hit
* @failcase				if maps_service_search_place_by_area fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_search_place_by_area_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	int nRequestId = 0;
	char *pszKeyword = "restaurant";
	double dTopLatitude = 15.665354, dTopLongitude = 74.311523;
	double dBotmLatitude = 10.617418, dBotmLongitude = 79.145508;
	maps_place_filter_h hPlaceFilter = NULL;
	maps_area_h hArea = NULL;
	maps_coordinates_h hTopLeft = NULL;
	maps_coordinates_h hBottomRight = NULL;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_place_filter_create(&hPlaceFilter);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_create", MapServiceGetError(nRet));

	nRet = maps_place_filter_set_keyword(hPlaceFilter, pszKeyword);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_keyword", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_place_filter_set_place_name(hPlaceFilter, "Berlin");
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_place_name", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_coordinates_create(dTopLatitude, dTopLongitude, &hTopLeft);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));
	CHECK_HANDLE_CLEANUP(hTopLeft, "maps_coordinates_create", maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_coordinates_create(dBotmLatitude, dBotmLongitude, &hBottomRight);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet),
						 maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hTopLeft));
	CHECK_HANDLE_CLEANUP(hBottomRight, "maps_coordinates_create", maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hTopLeft));
	
	nRet = maps_area_create_rectangle(hTopLeft, hBottomRight, &hArea);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_area_create_rectangle", MapServiceGetError(nRet), 
						 maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hTopLeft); maps_coordinates_destroy(hBottomRight));
	CHECK_HANDLE_CLEANUP(hArea, "maps_area_create_rectangle", 
						 maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hTopLeft); maps_coordinates_destroy(hBottomRight));
						 
	nRet = maps_service_search_place_by_area(g_hMapService, hArea, hPlaceFilter, g_hMapsPref, MapsServiceSearchPlaceCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place_by_area API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place_by_area API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_search_place_by_area", MapServiceGetError(nRet),
						 maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hTopLeft); maps_coordinates_destroy(hBottomRight); maps_area_destroy(hArea));

	RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Place is not received from maps_service_search_place_by_area \\n", __LINE__, API_NAMESPACE);
		maps_place_filter_destroy(hPlaceFilter);
		maps_coordinates_destroy(hTopLeft);
		maps_coordinates_destroy(hBottomRight);
		maps_area_destroy(hArea);
		return 1;
	}

	nRet = maps_place_filter_destroy(hPlaceFilter);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_destroy", MapServiceGetError(nRet),
						  maps_coordinates_destroy(hTopLeft); maps_coordinates_destroy(hBottomRight); maps_area_destroy(hArea));
	nRet = maps_coordinates_destroy(hTopLeft);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet),
						  maps_coordinates_destroy(hBottomRight); maps_area_destroy(hArea));
	nRet = maps_coordinates_destroy(hBottomRight);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet),
						  maps_area_destroy(hArea));
	nRet = maps_area_destroy(hArea);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_area_destroy", MapServiceGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to get the route information for a specified origin and destination coordinates
/**
* @testcase 			ITc_maps_service_search_route_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to get the route information for a specified origin and destination coordinates
* @scenario				create the preference \n
* 						create origin and destination coordinates \n
* 						get the route information for a specified origin and destination coordinates \n
* @apicovered			maps_service_search_route, maps_coordinates_create
* @passcase				if maps_service_search_route passes and the callback function is hit
* @failcase				if maps_service_search_route fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_search_route_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	g_nCheckCb = false;
	int nRequestId = 0;
	double dOrigLatitude = 37.564263, dOrigLongitude = 126.974676;
	double dDestLatitude = 37.557120, dDestLongitude = 126.992410;
	maps_coordinates_h hOrigin = NULL;
	maps_coordinates_h hDestination = NULL;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_create(dOrigLatitude, dOrigLongitude, &hOrigin);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hOrigin, "maps_coordinates_create");

	nRet = maps_coordinates_create(dDestLatitude, dDestLongitude, &hDestination);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(hOrigin));
	CHECK_HANDLE_CLEANUP(hDestination, "maps_coordinates_create", maps_coordinates_destroy(hOrigin));

	nRet = maps_service_search_route(g_hMapService, hOrigin, hDestination, g_hMapsPref, MapsServiceRouteFoundCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_search_route API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_search_route API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_search_route", MapServiceGetError(nRet),
						 maps_coordinates_destroy(hOrigin); maps_coordinates_destroy(hDestination));

	RUN_POLLING_LOOP;
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Route is not received from maps_service_search_route \\n", __LINE__, API_NAMESPACE);
		maps_coordinates_destroy(hOrigin);
		maps_coordinates_destroy(hDestination);
		return 1;
	}

	maps_coordinates_destroy(hOrigin);
	maps_coordinates_destroy(hDestination);
	return 0;
}

//& type: auto
//& purpose:  scenario to get the route information for the route passing through a specified set of way points
/**
* @testcase 			ITc_maps_service_search_route_waypoints_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to get the route information for the route passing through a specified set of way points
* @scenario				create the preference \n
* 						create way point coordinates \n
* 						get the route information for the route passing through a specified set of way points \n
* @apicovered			maps_service_search_route_waypoints, maps_coordinates_create
* @passcase				if maps_service_search_route_waypoints passes and the callback function is hit
* @failcase				if maps_service_search_route_waypoints fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_search_route_waypoints_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	g_nCheckCb = false;
	int nRequestId = 0, nWayPoints = 3;
	double dWp1Latitude = 37.564263, dWp1Longitude = 126.974676;
	double dWp2Latitude = 37.557120, dWp2Longitude = 126.992410;
	double dWp3Latitude = 37.550120, dWp3Longitude = 126.982410;
	maps_coordinates_h *p_wayPoints = NULL;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	p_wayPoints = (maps_coordinates_h *)g_malloc(sizeof(maps_coordinates_h)*nWayPoints);

	int nRet = maps_coordinates_create(dWp1Latitude, dWp1Longitude, &p_wayPoints[0]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), g_free(p_wayPoints));
	CHECK_HANDLE_CLEANUP(p_wayPoints[0], "maps_coordinates_create", g_free(p_wayPoints));

	nRet = maps_coordinates_create(dWp2Latitude, dWp2Longitude, &p_wayPoints[1]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_coordinates_destroy(p_wayPoints[0]);g_free(p_wayPoints));
	CHECK_HANDLE_CLEANUP(p_wayPoints[1], "maps_coordinates_create", maps_coordinates_destroy(p_wayPoints[0]); g_free(p_wayPoints));

	nRet = maps_coordinates_create(dWp3Latitude, dWp3Longitude, &p_wayPoints[2]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), 
						 maps_coordinates_destroy(p_wayPoints[0]); maps_coordinates_destroy(p_wayPoints[1]); g_free(p_wayPoints));
	CHECK_HANDLE_CLEANUP(p_wayPoints[2], "maps_coordinates_create", 
						 maps_coordinates_destroy(p_wayPoints[0]); maps_coordinates_destroy(p_wayPoints[1]); g_free(p_wayPoints));

	nRet = maps_service_search_route_waypoints(g_hMapService, p_wayPoints, nWayPoints, g_hMapsPref, MapsServiceRouteFoundCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_search_route_waypoints API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			maps_coordinates_destroy(p_wayPoints[0]);
			maps_coordinates_destroy(p_wayPoints[1]);
			maps_coordinates_destroy(p_wayPoints[2]);
			g_free(p_wayPoints);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_search_route_waypoints API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			maps_coordinates_destroy(p_wayPoints[0]);
			maps_coordinates_destroy(p_wayPoints[1]);
			maps_coordinates_destroy(p_wayPoints[2]);
			g_free(p_wayPoints);
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_search_route_waypoints", MapServiceGetError(nRet),
						 maps_coordinates_destroy(p_wayPoints[0]); maps_coordinates_destroy(p_wayPoints[1]); maps_coordinates_destroy(p_wayPoints[2]); g_free(p_wayPoints));

	RUN_POLLING_LOOP;
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Route is not received from maps_service_search_route_waypoints \\n", __LINE__, API_NAMESPACE);
		maps_coordinates_destroy(p_wayPoints[0]); 
		maps_coordinates_destroy(p_wayPoints[1]); 
		maps_coordinates_destroy(p_wayPoints[2]);
		g_free(p_wayPoints);
		return 1;
	}

	maps_coordinates_destroy(p_wayPoints[0]); 
	maps_coordinates_destroy(p_wayPoints[1]); 
	maps_coordinates_destroy(p_wayPoints[2]);
	g_free(p_wayPoints);

	return 0;
}

//& type: auto
//& purpose:  scenario to get the address for given multiple position coordinates
/**
* @testcase 			ITc_maps_service_multi_reverse_geocode_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get the address for given multiple position coordinates
* @scenario				create the coordinate list \n
* 						get the address for multiple given position coordinates \n
* @apicovered			maps_service_multi_reverse_geocode
* @passcase				if maps_service_multi_reverse_geocode passes and the callback function is hit
* @failcase				if maps_service_multi_reverse_geocode fails or the callback function is not hit
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_multi_reverse_geocode_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");

	g_nCheckCb = false;
	maps_coordinates_list_h hMapCoordinateList = NULL;
	int nRequestId = 0;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_coordinates_list_create(&hMapCoordinateList);
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_list_create fail , error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		FREE_MEMORY(hMapCoordinateList);
		return 1;
	}
	if (hMapCoordinateList == NULL)
	{
		FPRINTF("[Line : %d][%s] hMapCoordinateList handle is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	maps_coordinates_h *hMapCoordinate = NULL;
	hMapCoordinate = (maps_coordinates_h *)g_malloc(sizeof(maps_coordinates_h)*4);
	if (hMapCoordinate == NULL)
	{
		FPRINTF("[Line : %d][%s] Memory Allocation Failed for hMapCoordinate \\n", __LINE__, API_NAMESPACE);
		maps_coordinates_list_destroy(hMapCoordinateList);
		return 1;
	}

	nRet = maps_coordinates_create(.09, 1.8, &hMapCoordinate[0]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet),maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));
	CHECK_HANDLE_CLEANUP(hMapCoordinate[0], "maps_coordinates_create",maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));

	nRet = maps_coordinates_create(0.1618996, 8.997, &hMapCoordinate[1]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet),maps_coordinates_destroy(hMapCoordinate[0]);maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));
	CHECK_HANDLE_CLEANUP(hMapCoordinate[1], "maps_coordinates_create",maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));

	nRet = maps_coordinates_create(0.79660710, -7.986800809087, &hMapCoordinate[2]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet),maps_coordinates_destroy(hMapCoordinate[0]);maps_coordinates_destroy(hMapCoordinate[1]);maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));
	CHECK_HANDLE_CLEANUP(hMapCoordinate[2], "maps_coordinates_create",maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));

	nRet = maps_coordinates_create(.03, 1.4, &hMapCoordinate[3]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet),maps_coordinates_destroy(hMapCoordinate[0]);maps_coordinates_destroy(hMapCoordinate[1]);maps_coordinates_destroy(hMapCoordinate[2]);maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));
	CHECK_HANDLE_CLEANUP(hMapCoordinate[3], "maps_coordinates_create",maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));


	nRet = maps_coordinates_list_append(hMapCoordinateList, hMapCoordinate[0]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet),maps_coordinates_destroy(hMapCoordinate[0]);maps_coordinates_destroy(hMapCoordinate[1]);maps_coordinates_destroy(hMapCoordinate[2]);maps_coordinates_destroy(hMapCoordinate[3]);maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));

	nRet = maps_coordinates_list_append(hMapCoordinateList, hMapCoordinate[1]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet),maps_coordinates_destroy(hMapCoordinate[1]);maps_coordinates_destroy(hMapCoordinate[2]);maps_coordinates_destroy(hMapCoordinate[3]);maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));

	nRet = maps_coordinates_list_append(hMapCoordinateList, hMapCoordinate[2]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet),maps_coordinates_destroy(hMapCoordinate[2]);maps_coordinates_destroy(hMapCoordinate[3]);maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));

	nRet = maps_coordinates_list_append(hMapCoordinateList, hMapCoordinate[3]);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_append", MapServiceGetError(nRet),maps_coordinates_destroy(hMapCoordinate[3]);maps_coordinates_list_destroy(hMapCoordinateList);g_free(hMapCoordinate));
			
	nRet = maps_service_multi_reverse_geocode(g_hMapService, hMapCoordinateList, g_hMapsPref, MapServiceMultiRevGeocodeCb, NULL, &nRequestId);	
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_multi_reverse_geocode API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			maps_coordinates_list_destroy(hMapCoordinateList);
			g_free(hMapCoordinate);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_multi_reverse_geocode API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			//g_bFeatureMismatch = true;
			maps_coordinates_list_destroy(hMapCoordinateList);
			g_free(hMapCoordinate);
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_multi_reverse_geocode", MapServiceGetError(nRet),maps_coordinates_destroy(hMapCoordinate[0]);maps_coordinates_destroy(hMapCoordinate[1]);maps_coordinates_destroy(hMapCoordinate[2]);maps_coordinates_destroy(hMapCoordinate[3]);maps_coordinates_list_destroy(hMapCoordinateList);FREE_MEMORY(hMapCoordinate));

	RUN_POLLING_LOOP;
	
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Coordinates are not received from maps_service_reverse_geocode \\n", __LINE__, API_NAMESPACE);
		//g_bFeatureMismatch = true;
		maps_coordinates_list_destroy(hMapCoordinateList);
		g_free(hMapCoordinate);
		return 1;
	}
	
	
	nRet = maps_coordinates_list_destroy(hMapCoordinateList);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_list_destroy", MapServiceGetError(nRet),g_free(hMapCoordinate));
			
	g_free(hMapCoordinate);

	return 0;
}

//& type: auto
//& purpose:  scenario to obtains the brief Place information for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_service_search_place_list_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to obtains the brief Place information for a specified coordinates boundary.
* @scenario				maps_service_search_place_list
* @apicovered			maps_service_search_place_list
* @passcase				if maps_service_search_place_list passes
* @failcase				if maps_service_search_place_list fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_maps_service_search_place_list_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");	
	
	g_nCheckCb = false;
	int nRequestId = 0, nDistance = 504295;
	char *pszKeyword = "restaurant";
	double dLatitude = 52.5167, dLongitude = 13.383;
	maps_place_filter_h hPlaceFilter = NULL;
	maps_coordinates_h hMapCoords = NULL;
	maps_area_h hArea = NULL;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_place_filter_create(&hPlaceFilter);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hPlaceFilter, "maps_place_filter_create");

	nRet = maps_place_filter_set_keyword(hPlaceFilter, pszKeyword);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_keyword", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_place_filter_set_place_name(hPlaceFilter, "Berlin");
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_place_name", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_coordinates_create(dLatitude, dLongitude, &hMapCoords);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));
	CHECK_HANDLE(hMapCoords, "maps_coordinates_create");

	nRet = maps_area_create_circle(hMapCoords, nDistance, &hArea);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_area_create_circle", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hMapCoords));
	CHECK_HANDLE_CLEANUP(hArea, "maps_area_create_circle", maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hMapCoords));
						 
	//Target API
	nRet = maps_service_search_place_list(g_hMapService, hArea, hPlaceFilter, g_hMapsPref, MapsServiceSearchPlaceListCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place_list API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place_list API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_search_place_list", MapServiceGetError(nRet),maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hMapCoords); maps_area_destroy(hArea));

	RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Place is not received from maps_service_search_place_list \\n", __LINE__, API_NAMESPACE);
		maps_place_filter_destroy(hPlaceFilter);
		maps_coordinates_destroy(hMapCoords);
		maps_area_destroy(hArea);
		return 1;
	}

	nRet = maps_place_filter_destroy(hPlaceFilter);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_destroy", MapServiceGetError(nRet),maps_coordinates_destroy(hMapCoords); maps_area_destroy(hArea));
	nRet = maps_coordinates_destroy(hMapCoords);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet),maps_area_destroy(hArea));
	nRet = maps_area_destroy(hArea);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_area_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to obtains the Detail place information for a specified place uri
/**
* @testcase 			ITc_maps_service_get_place_details_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to obtains the Detail place information for a specified place uri
* @scenario				maps_service_get_place_details
* @apicovered			maps_service_get_place_details
* @passcase				if maps_service_get_place_details passes
* @failcase				if maps_service_get_place_details fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_service_get_place_details_p(void)
{
	START_TEST(g_hMapService, "maps_service");
	CHECK_HANDLE(g_hMapsPref, "maps_preference_create");	
	
	g_nCheckCb = false;
	int nRequestId = 0, nDistance = 504295;
	char *pszKeyword = "restaurant";
	double dLatitude = 52.5167, dLongitude = 13.383;
	maps_place_filter_h hPlaceFilter = NULL;
	maps_coordinates_h hMapCoords = NULL;
	maps_area_h hArea = NULL;
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_place_filter_create(&hPlaceFilter);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hPlaceFilter, "maps_place_filter_create");
	
	nRet = maps_place_filter_set_keyword(hPlaceFilter, pszKeyword);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_keyword", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_place_filter_set_place_name(hPlaceFilter, "Berlin");
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_place_name", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_coordinates_create(dLatitude, dLongitude, &hMapCoords);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_create", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));
	CHECK_HANDLE(hMapCoords, "maps_coordinates_create");

	nRet = maps_area_create_circle(hMapCoords, nDistance, &hArea);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_area_create_circle", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hMapCoords));
	CHECK_HANDLE_CLEANUP(hArea, "maps_area_create_circle", maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hMapCoords));

	if(g_szPlaceURI != NULL)
	{
		free(g_szPlaceURI);
		g_szPlaceURI = NULL;
	}

	nRet = maps_service_search_place_list(g_hMapService, hArea, hPlaceFilter, g_hMapsPref, MapsServiceSearchPlaceListCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place_list API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureMismatch = true;
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place_list API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			//g_bFeatureNotSupported = true;
			return 0;
		}
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_search_place_list", MapServiceGetError(nRet),maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hMapCoords); maps_area_destroy(hArea));

	RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Place is not received from maps_service_search_place_list \\n", __LINE__, API_NAMESPACE);
		maps_place_filter_destroy(hPlaceFilter);
		maps_coordinates_destroy(hMapCoords);
		maps_area_destroy(hArea);
		return 1;
	}

	//Target API
	g_nCheckCb = false;
	nRet = maps_service_get_place_details(g_hMapService,g_szPlaceURI,MapsServiceGetPlaceDetailsCb, NULL, &nRequestId);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_service_get_place_details", MapServiceGetError(nRet),maps_place_filter_destroy(hPlaceFilter); maps_coordinates_destroy(hMapCoords); maps_area_destroy(hArea));
	
	RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Place is not received from maps_service_get_place_details \\n", __LINE__, API_NAMESPACE);
		maps_place_filter_destroy(hPlaceFilter);
		maps_coordinates_destroy(hMapCoords);
		maps_area_destroy(hArea);
		return 1;
	}

	nRet = maps_place_filter_destroy(hPlaceFilter);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_destroy", MapServiceGetError(nRet),maps_coordinates_destroy(hMapCoords); maps_area_destroy(hArea));
	
	nRet = maps_coordinates_destroy(hMapCoords);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet),maps_area_destroy(hArea));
	
	nRet = maps_area_destroy(hArea);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_area_destroy", MapServiceGetError(nRet));
	
	return 0;
}


//& type: auto
//& purpose:  scenario to get the user's consent to use maps data
/**
* @testcase 			ITc_maps_service_request_user_consent_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get the user's consent to use maps data
* @scenario				scenario to get the user's consent to use maps data
* @apicovered			maps_service_request_user_consent
* @passcase				if maps_service_request_user_consent passes and the callback function is hit
* @failcase				if maps_service_request_user_consent fails or the callback function is not hit
* @precondition			Call maps_service_foreach_provider() to get a available Maps Providers.
* @postcondition		callback called
*/
int ITc_maps_service_request_user_consent_p(void)
{
	START_TEST(g_hMapService, "maps_service");

	bool g_bFeatureSupported = false;
	g_nCheckCb = false;
	
	IS_FEATURE_SUPPORTED(MAPS_FEATURE, g_bFeatureSupported, API_NAMESPACE);
	
	int nRet = maps_service_request_user_consent(g_szMapsProvider, MapsServiceRequestUserConsentCb, NULL); 
	if ( !g_bFeatureSupported )
	{
		if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
		{
		   FPRINTF("[Line : %d][%s] Feature not supported \\n", __LINE__, API_NAMESPACE);
		   return 0;
		}
		else
		{
		   FPRINTF("[Line : %d][%s] Feature mismatch \\n", __LINE__, API_NAMESPACE);
		   return 1;
		}
	}
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_service_geocode", MapServiceGetError(nRet));

	RUN_POLLING_LOOP;
	
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Coordinates are not received from maps_service_geocode \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/** @} */
/** @} */
