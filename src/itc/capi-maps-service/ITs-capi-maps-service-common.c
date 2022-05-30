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
#include "ITs-capi-maps-service-common.h"

/** @addtogroup itc-maps-service
*  @ingroup itc
*  @{
*/
static bool bMapsRemovedProviders = false;
/**
* @function 		MapsCallbackTimeout
* @description	 	callback function to terminate g_main loop
* @parameter		data : user data sent to callback
* @return 			NA
*/
gboolean MapsCallbackTimeout(gpointer data)
{
	GMainLoop* pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	return false;
}

/**
* @function 		GetResourceDataPath
* @description	 	Gets the resource data path
* @parameter		void
* @return 			bool
*/
bool GetResourceDataPath(void)
{
	char *pszResPath = app_get_resource_path();
	if (pszResPath) {
		snprintf(gszImagePath, BUFF_LEN, "%s%s", pszResPath, IMAGE_FILENAME);
		FREE_MEMORY_TC(pszResPath);
		return true;
	}
	
	return false;
}

/**
* @function 		MapServiceGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MapServiceGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case MAPS_ERROR_NONE:					szErrorVal = "MAPS_ERROR_NONE";						break;
		case MAPS_ERROR_PERMISSION_DENIED:   	szErrorVal = "MAPS_ERROR_PERMISSION_DENIED";		break;
		case MAPS_ERROR_OUT_OF_MEMORY:       	szErrorVal = "MAPS_ERROR_OUT_OF_MEMORY";			break;
		case MAPS_ERROR_INVALID_PARAMETER:   	szErrorVal = "MAPS_ERROR_INVALID_PARAMETER";		break;
		case MAPS_ERROR_NOT_SUPPORTED:       	szErrorVal = "MAPS_ERROR_NOT_SUPPORTED";			break;
		case MAPS_ERROR_CONNECTION_TIME_OUT: 	szErrorVal = "MAPS_ERROR_CONNECTION_TIME_OUT";		break;
		case MAPS_ERROR_NETWORK_UNREACHABLE: 	szErrorVal = "MAPS_ERROR_NETWORK_UNREACHABLE";		break;
		case MAPS_ERROR_INVALID_OPERATION:   	szErrorVal = "MAPS_ERROR_INVALID_OPERATION";		break;
		case MAPS_ERROR_KEY_NOT_AVAILABLE:   	szErrorVal = "MAPS_ERROR_KEY_NOT_AVAILABLE";		break;
		case MAPS_ERROR_RESOURCE_BUSY:	    	szErrorVal = "MAPS_ERROR_RESOURCE_BUSY";			break;
		case MAPS_ERROR_CANCELED:            	szErrorVal = "MAPS_ERROR_CANCELED";					break;
		case MAPS_ERROR_UNKNOWN:				szErrorVal = "MAPS_ERROR_UNKNOWN";					break;
		case MAPS_ERROR_SERVICE_NOT_AVAILABLE:	szErrorVal = "MAPS_ERROR_SERVICE_NOT_AVAILABLE";	break;
		case MAPS_ERROR_NOT_FOUND:           	szErrorVal = "MAPS_ERROR_NOT_FOUND";				break;
		case MAPS_ERROR_USER_NOT_CONSENTED:     szErrorVal = "MAPS_ERROR_USER_NOT_CONSENTED";		break;
		default : 					           	szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}
// Callback Function to get list of service providers
bool MapsServiceProviderForeachHERECb(char* maps_provider, void* user_data)
{
	memset( g_szMapsProvider, '\0', sizeof(char)*BUFFER);
	if(maps_provider != NULL)
	{
		strncpy(g_szMapsProvider, "HERE", sizeof(g_szMapsProvider)-1);
		FPRINTF("[Line : %d][%s] Provider list from maps_service_foreach_provider is = %s\\n", __LINE__, API_NAMESPACE, g_szMapsProvider);	
	}
	else
		return false;
	
	g_nCheckCb = true;
	return true;
}
// Callback function to get the place view URI
bool MapsPlaceCb(int index, maps_place_h place, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsPlaceCb callback\\n", __LINE__, API_NAMESPACE);
	if(index ==0)
	{
		g_nCheckRet = maps_place_clone(place, &g_maps_place);
	}

	return true;
}
// Callback function to search place list by coordinates
void MapsServiceSearchPlaceListCb(maps_error_e error, int request_id, int total, maps_place_list_h place_list, void *user_data)
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
	FPRINTF("[Line : %d][%s] Inside MapsServiceGetPlaceDetailsCb callback\\n", __LINE__, API_NAMESPACE);
	g_nCheckCb = true;
	
	g_nCheckRet = maps_place_clone(place, &g_maps_place);

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}
// Callback function to search place by coordinates
static bool MapsServiceSearchPlaceHereCb(maps_error_e error, int request_id , int index, int total, maps_place_h place, void* user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsServiceSearchPlaceCb callback\\n", __LINE__, API_NAMESPACE);
	/*if(g_maps_place != NULL)
	{
		FPRINTF("[Line : %d][%s] DESTROY g_maps_place\\n", __LINE__, API_NAMESPACE);
		maps_place_destroy(g_maps_place);
	}*/
	g_nCheckRet = maps_place_clone(place, &g_maps_place);
	
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
void MapsPlaceLocationHandleHelperHERE(void)
{
	int nRequestId = 0;
	maps_place_filter_h hPlaceFilter = NULL;
	maps_coordinates_h hMapCoords = NULL;
	
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	g_bStartupPre = true;
	
	g_nCheckRet = 0;
	g_nCheckCb = 0;
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	int nRet = maps_service_foreach_provider(MapsServiceProviderForeachHERECb, NULL);
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
	nRet = maps_preference_set_property(g_hMapsPref, MAPS_PLACE_FILTER_SORT_BY, "distance");
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_preference_set_property API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	nRet = maps_place_filter_create(&hPlaceFilter);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_place_filter_create API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(hPlaceFilter == NULL)
	{
	    FPRINTF("[Line : %d][%s] hPlaceFilter NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	//nRet = maps_place_filter_set_keyword(hPlaceFilter, pszKeyword);
	//PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_keyword", MapServiceGetError(nRet), maps_place_filter_destroy(hPlaceFilter));

	nRet = maps_place_filter_set_place_name(hPlaceFilter, "Berlin");
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_place_filter_set_place_name API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	nRet = maps_coordinates_create(LATITUTE_LOCATION, LONGITUDE_LOCATION, &hMapCoords);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_create API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(hMapCoords == NULL)
	{
	    FPRINTF("[Line : %d][%s] hMapCoords NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	
	nRet = maps_service_search_place(g_hMapService, hMapCoords, DISTANCELOC, hPlaceFilter, g_hMapsPref, MapsServiceSearchPlaceHereCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
			return;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
			return;
		}
	}
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_service_search_place API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	
	RUN_POLLING_LOOP;
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Place is not received from maps_service_search_place \\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(g_nCheckRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_place_clone API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(g_maps_place == NULL)
	{
	    FPRINTF("[Line : %d][%s] g_maps_place NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	nRet = maps_coordinates_destroy(hMapCoords);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_destroy API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	nRet = maps_place_filter_destroy(hPlaceFilter);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_place_filter_destroy API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
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
void MapsPlaceHandleHelperHERE(void)
{
	int nRequestId = 0, nRet;
	char *pszKeyword = "restaurant";
	maps_place_filter_h hPlaceFilter = NULL;
	maps_coordinates_h hMapCoords = NULL;
	maps_area_h hArea = NULL;
	
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	g_bStartupPre = true;
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	bool bInternetFeatureSupported = TCTCheckSystemInfoFeatureSupported(INTERNET_FEATURE, API_NAMESPACE);
	
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	
	nRet = maps_service_foreach_provider(MapsServiceProviderForeachHERECb, NULL);
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
		FPRINTF("[Line : %d][%s] pstrValue NULL\\n", __LINE__, API_NAMESPACE);
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
	nRet = maps_place_filter_create(&hPlaceFilter);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_place_filter_create API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(hPlaceFilter == NULL)
	{
	    FPRINTF("[Line : %d][%s] hPlaceFilter NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	nRet = maps_place_filter_set_keyword(hPlaceFilter, pszKeyword);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_place_filter_set_keyword API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	nRet = maps_place_filter_set_place_name(hPlaceFilter, "Berlin");
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_place_filter_set_place_name API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	nRet = maps_coordinates_create(LATITUTE, LONGITUDE, &hMapCoords);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_create API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(hMapCoords == NULL)
	{
	    FPRINTF("[Line : %d][%s] hMapCoords NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	nRet = maps_area_create_circle(hMapCoords, DISTANCE, &hArea);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_area_create_circle API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	if(hArea == NULL)
	{
	    FPRINTF("[Line : %d][%s] hArea NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
    g_nCheckRet = 0;
	g_nCheckCb = 0;
	
	//Target API
	nRet = maps_service_search_place_list(g_hMapService, hArea, hPlaceFilter, g_hMapsPref, MapsServiceSearchPlaceListCb, NULL, &nRequestId);
	if ( false == bInternetFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place_list API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
			return;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_service_search_place_list API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
			return;
		}
	}
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_service_search_place_list API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
	    maps_area_destroy(hArea);
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Place is not received from maps_service_search_place_list \\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_area_destroy(hArea);
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService); 
		return;
	}
	if(g_nCheckRet != MAPS_ERROR_NONE)
	{
	    FPRINTF("[Line : %d][%s] maps_place_clone API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_area_destroy(hArea);
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService); 
		return;
	}
	if(g_maps_place == NULL)
	{
	    FPRINTF("[Line : %d][%s] g_maps_place NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_area_destroy(hArea);
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService); 
		return;
	}
	if(g_szPlaceURI != NULL)
	{
		free(g_szPlaceURI);
		g_szPlaceURI = NULL;
	}
	maps_place_get_uri(g_maps_place, &g_szPlaceURI);
	if(g_szPlaceURI == NULL)
	{
		FPRINTF("[Line : %d][%s] g_szPlaceURI NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
	    maps_area_destroy(hArea);
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService); 
		return;
	}

	g_nCheckCb = 0;
	g_nCheckRet = 0;
	nRet = maps_service_get_place_details(g_hMapService,g_szPlaceURI,MapsServiceGetPlaceDetailsCb, NULL, &nRequestId);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_service_get_place_details API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
	    maps_area_destroy(hArea);
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService);
		return;
	}
	RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] Place is not received from maps_service_get_place_details \\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_area_destroy(hArea);
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService); 
		return;
	}
	if(g_nCheckRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_place_clone API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_area_destroy(hArea);
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService); 
		return;
	}
	if(g_maps_place == NULL)
	{
	    FPRINTF("[Line : %d][%s] g_maps_place NULL\\n", __LINE__, API_NAMESPACE);
		g_bStartupPre = false;
		maps_area_destroy(hArea);
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService); 
		return;
	}
	nRet = maps_area_destroy(hArea);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_area_destroy API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_coordinates_destroy(hMapCoords);
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService); 
		return;
	}
	nRet = maps_coordinates_destroy(hMapCoords);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_coordinates_destroy API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
		g_bStartupPre = false;
		maps_place_filter_destroy(hPlaceFilter);
		maps_preference_destroy(g_hMapsPref);
		maps_service_destroy(g_hMapService); 
		return;
	}
	nRet = maps_place_filter_destroy(hPlaceFilter);
	if(nRet != MAPS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] maps_place_filter_destroy API failed %s\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
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

bool MapsProviderCb(char *maps_provider, void *user_data)
{
	free(maps_provider);
	return true;
}

/** @} */
//Add helper function definitions here
