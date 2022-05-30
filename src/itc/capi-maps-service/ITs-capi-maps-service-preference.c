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

maps_preference_h g_HandlePreference = NULL;
bool g_bPreferenceCheck = false;
//& set: MapsService


/**
 * @function 		ITs_maps_service_item_preference_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_item_preference_startup(void)
{
	struct stat stBuff;   
	
	g_bFeatureSupported = true;
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	int nRet = maps_preference_create(&g_HandlePreference);
	if ( false == bMapsFeatureSupported)
	{
		g_bFeatureSupported = false;
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_preference_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_preference_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_preference_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_HandlePreference = NULL;
	}
	return;
}


/**
 * @function 		ITs_maps_service_item_preference_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_item_preference_cleanup(void)
{
	if((g_HandlePreference != NULL)&& (g_bFeatureSupported == true))
	{
		maps_preference_destroy(g_HandlePreference);
	}
	return;
}

/**
* @function 		MapsPreferencePropertiesCallback
* @description	 	callback function for capturing context event callbacks
* @parameter		index : current index of property, total : total amount of properties, key : key of property, value : value of property, user_data : user data passed to callback function
* @return 			0 on being called
*/
bool MapsPreferencePropertiesCallback(int index, int total, char* key, char* value, void* user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback MapsPreferencePropertiesCallback is called \\n", __LINE__, API_NAMESPACE);
#endif
	g_bPreferenceCheck = true;
	return false;	
}



/** @addtogroup itc-maps-service-testcases
*  @brief 		Integration testcases for module maps-service
*  @ingroup 	itc-maps-service
*  @{
*/

//& type: auto
//& purpose:  scenario to create and destroy new maps preference handle.
/**
* @testcase 			ITc_maps_preference_create_destroy_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to create and destroy new maps preference handle
* @scenario				creates new maps preference handle \n
* 						destroy the maps preference handle \n
* @apicovered			maps_preference_create, maps_preference_destroy
* @passcase				if maps_preference_create and maps_preference_destroy passes
* @failcase				if maps_preference_create or maps_preference_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_create_destroy_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	maps_preference_destroy(g_HandlePreference);
	g_HandlePreference = NULL;
	
	maps_preference_h LocalHandle = NULL;
	int nRet = maps_preference_create(&LocalHandle);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_create", MapServiceGetError(nRet));
	CHECK_HANDLE(LocalHandle, "maps_preference_create");
	
	nRet = maps_preference_destroy(LocalHandle);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_destroy", MapServiceGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to clone and destroy maps preference handle
/**
* @testcase 			ITc_maps_preference_clone_destroy_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to clone and destroy maps preference handle
* @scenario				clone a maps preference handle \n
* 						destroy the maps preference handle \n
* @apicovered			maps_preference_clone, maps_preference_destroy
* @passcase				if maps_preference_clone and maps_preference_destroy passes
* @failcase				if maps_preference_clone or maps_preference_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_clone_destroy_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");	
	maps_place_filter_h LocalHandle = NULL;
	int nRet = maps_preference_clone(g_HandlePreference, &LocalHandle);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_clone", MapServiceGetError(nRet));
	CHECK_HANDLE(LocalHandle, "maps_preference_clone");
	
	nRet = maps_preference_destroy(LocalHandle);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_destroy", MapServiceGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the maps distance unit
/**
* @testcase 			ITc_maps_preference_set_get_distance_unit_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the maps distance unit
* @scenario				set the maps distance unit \n
* 						get the maps distance unit\n
* 						compare the set and get values \n
* @apicovered			maps_preference_set_distance_unit, maps_preference_get_distance_unit
* @passcase				if maps_preference_set_distance_unit and maps_preference_get_distance_unit passes
* @failcase				if maps_preference_set_distance_unit or maps_preference_get_distance_unit fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_set_get_distance_unit_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	maps_distance_unit_e eMapGetDistanceUnit;
	maps_distance_unit_e eMapSetDistanceUnit[] = { MAPS_DISTANCE_UNIT_M,
												MAPS_DISTANCE_UNIT_KM,
												MAPS_DISTANCE_UNIT_FT,
												MAPS_DISTANCE_UNIT_YD };
	int nRet =  0, nLoopCount = 0;
	int nMapDistanceArraySize = sizeof(eMapSetDistanceUnit) / sizeof(eMapSetDistanceUnit[0]);
	for(nLoopCount = 0; nLoopCount < nMapDistanceArraySize; nLoopCount++)
	{
		nRet = maps_preference_set_distance_unit(g_HandlePreference, eMapSetDistanceUnit[nLoopCount]);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_distance_unit", MapServiceGetError(nRet));
		
		nRet = maps_preference_get_distance_unit(g_HandlePreference, &eMapGetDistanceUnit);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_get_distance_unit", MapServiceGetError(nRet));
		
		if(eMapGetDistanceUnit != eMapSetDistanceUnit[nLoopCount])
		{
			FPRINTF("[Line : %d][%s] Mismatch in value, set = %d, get = %d\\n", __LINE__, API_NAMESPACE, eMapSetDistanceUnit[nLoopCount], eMapGetDistanceUnit);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the maps country code
/**
* @testcase 			ITc_maps_preference_set_get_country_code_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the maps country code
* @scenario				set the maps country code \n
* 						get the maps country code\n
* 						compare the set and get values \n
* @apicovered			maps_preference_set_country_code, maps_preference_get_country_code
* @passcase				if maps_preference_set_country_code and maps_preference_get_country_code passes
* @failcase				if maps_preference_set_country_code or maps_preference_get_country_code fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_set_get_country_code_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	char *pszSetValue = "IN";
	char *pszGetValue = NULL;
	int nRet = maps_preference_set_country_code(g_HandlePreference, pszSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_country_code", MapServiceGetError(nRet));
	
	nRet = maps_preference_get_country_code(g_HandlePreference, &pszGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_get_country_code", MapServiceGetError(nRet));
	
	if(pszGetValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Get value = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	if(strcmp(pszSetValue, pszGetValue) != 0)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pszSetValue, pszGetValue);
		FREE_MEMORY(pszGetValue);
		return 1;
	}
	FREE_MEMORY(pszGetValue);
	
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the language
/**
* @testcase 			ITc_maps_preference_set_get_language_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the language
* @scenario				set the language \n
* 						get the language\n
* 						compare the set and get values \n
* @apicovered			maps_preference_set_language, maps_preference_get_language
* @passcase				if maps_preference_set_language and maps_preference_get_language passes
* @failcase				if maps_preference_set_language or maps_preference_get_language fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_set_get_language_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	char *pszSetValue = "English";
	char *pszGetValue = NULL;
	int nRet = maps_preference_set_language(g_HandlePreference, pszSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_language", MapServiceGetError(nRet));
	
	nRet = maps_preference_get_language(g_HandlePreference, &pszGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_get_language", MapServiceGetError(nRet));
	
	if(pszGetValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Get value = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	if(strcmp(pszSetValue, pszGetValue) != 0)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pszSetValue, pszGetValue);
		FREE_MEMORY(pszGetValue);
		return 1;
	}
	FREE_MEMORY(pszGetValue);
	
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the language
/**
* @testcase 			ITc_maps_preference_set_get_max_results_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the language
* @scenario				set the language \n
* 						get the language\n
* 						compare the set and get values \n
* @apicovered			maps_preference_set_max_results, maps_preference_get_max_results
* @passcase				if maps_preference_set_max_results and maps_preference_get_max_results passes
* @failcase				if maps_preference_set_max_results or maps_preference_get_max_results fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_set_get_max_results_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	int nSetMaxValue = 24;
	int nGetMaxValue = 0;
	int nRet = maps_preference_set_max_results(g_HandlePreference, nSetMaxValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_max_results", MapServiceGetError(nRet));
	
	nRet = maps_preference_get_max_results(g_HandlePreference, &nGetMaxValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_get_max_results", MapServiceGetError(nRet));
	
	if(nSetMaxValue != nGetMaxValue)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %d, get = %d\\n", __LINE__, API_NAMESPACE, nSetMaxValue, nGetMaxValue);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the route feature
/**
* @testcase 			ITc_maps_preference_set_get_route_feature_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the route feature
* @scenario				set the route feature \n
* 						get the route feature \n
* 						compare the set and get values \n
* @apicovered			maps_preference_set_route_feature, maps_preference_get_route_feature
* @passcase				if maps_preference_set_route_feature and maps_preference_get_route_feature passes
* @failcase				if maps_preference_set_route_feature or maps_preference_get_route_feature fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_set_get_route_feature_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	maps_route_feature_e eMapGetRouteFeature;
	maps_route_feature_e eMapSetRouteFeature[] = {  MAPS_ROUTE_FEATURE_NO,			
													MAPS_ROUTE_FEATURE_TOLL,		
													MAPS_ROUTE_FEATURE_MOTORWAY,	
													MAPS_ROUTE_FEATURE_BOATFERRY,	
													MAPS_ROUTE_FEATURE_RAILFERRY,	
													MAPS_ROUTE_FEATURE_PUBLICTTRANSIT,
													MAPS_ROUTE_FEATURE_TUNNEL,		
													MAPS_ROUTE_FEATURE_DIRTROAD,	
													MAPS_ROUTE_FEATURE_PARKS,		
													MAPS_ROUTE_FEATURE_HOVLANE,		
													MAPS_ROUTE_FEATURE_STAIRS		
												};
	int nRet =  0, nLoopCount = 0;
	int nMapDistanceArraySize = sizeof(eMapSetRouteFeature) / sizeof(eMapSetRouteFeature[0]);
	for(nLoopCount = 0; nLoopCount < nMapDistanceArraySize; nLoopCount++)
	{
		nRet = maps_preference_set_route_feature(g_HandlePreference, eMapSetRouteFeature[nLoopCount]);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_route_feature", MapServiceGetError(nRet));
		
		nRet = maps_preference_get_route_feature(g_HandlePreference, &eMapGetRouteFeature);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_get_route_feature", MapServiceGetError(nRet));
		
		if(eMapGetRouteFeature != eMapSetRouteFeature[nLoopCount])
		{
			FPRINTF("[Line : %d][%s] Mismatch in value, set = %d, get = %d\\n", __LINE__, API_NAMESPACE, eMapSetRouteFeature[nLoopCount], eMapGetRouteFeature);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the route feature weight
/**
* @testcase 			ITc_maps_preference_set_get_route_feature_weight_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the route feature weight
* @scenario				set the route feature weight \n
* 						get the route feature weight \n
* 						compare the set and get values \n
* @apicovered			maps_preference_set_route_feature_weight, maps_preference_get_route_feature_weight
* @passcase				if maps_preference_set_route_feature_weight and maps_preference_get_route_feature_weight passes
* @failcase				if maps_preference_set_route_feature_weight or maps_preference_get_route_feature_weight fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_set_get_route_feature_weight_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	maps_route_feature_weight_e eMapGetValue;
	maps_route_feature_weight_e eMapSetValue[] = { MAPS_ROUTE_FEATURE_WEIGHT_NORMAL,
											MAPS_ROUTE_FEATURE_WEIGHT_PREFER,
											MAPS_ROUTE_FEATURE_WEIGHT_AVOID,
											MAPS_ROUTE_FEATURE_WEIGHT_SOFTEXCLUDE,
											MAPS_ROUTE_FEATURE_WEIGHT_STRICTEXCLUDE
											};
	int nRet =  0, nLoopCount = 0;
	int nMapDistanceArraySize = sizeof(eMapSetValue) / sizeof(eMapSetValue[0]);
	for(nLoopCount = 0; nLoopCount < nMapDistanceArraySize; nLoopCount++)
	{
		nRet = maps_preference_set_route_feature_weight(g_HandlePreference, eMapSetValue[nLoopCount]);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_route_feature_weight", MapServiceGetError(nRet));
		
		nRet = maps_preference_get_route_feature_weight(g_HandlePreference, &eMapGetValue);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_get_route_feature_weight", MapServiceGetError(nRet));
		
		if(eMapGetValue != eMapSetValue[nLoopCount])
		{
			FPRINTF("[Line : %d][%s] Mismatch in value, set = %d, get = %d\\n", __LINE__, API_NAMESPACE, eMapSetValue[nLoopCount], eMapGetValue);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose:  scenario txo set and get the route optimization
/**
* @testcase 			ITc_maps_preference_set_get_route_optimization_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the route optimization
* @scenario				set the route optimization \n
* 						get the route optimization \n
* 						compare the set and get values \n
* @apicovered			maps_preference_set_route_optimization, maps_preference_get_route_optimization
* @passcase				if maps_preference_set_route_optimization and maps_preference_get_route_optimization passes
* @failcase				if maps_preference_set_route_optimization or maps_preference_get_route_optimization fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_set_get_route_optimization_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	maps_route_optimization_e eMapGetValue;
	maps_route_optimization_e eMapSetValue[] = { MAPS_ROUTE_TYPE_FASTEST,
											MAPS_ROUTE_TYPE_SHORTEST,
											MAPS_ROUTE_TYPE_ECONOMIC,
											MAPS_ROUTE_TYPE_SCENIC,	
											MAPS_ROUTE_TYPE_FASTESTNOW,
											MAPS_ROUTE_TYPE_DIRECTDRIVE
										   };
											
	int nRet =  0, nLoopCount = 0;
	int nMapDistanceArraySize = sizeof(eMapSetValue) / sizeof(eMapSetValue[0]);
	for(nLoopCount = 0; nLoopCount < nMapDistanceArraySize; nLoopCount++)
	{
		nRet = maps_preference_set_route_optimization(g_HandlePreference, eMapSetValue[nLoopCount]);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_route_optimization", MapServiceGetError(nRet));
		
		nRet = maps_preference_get_route_optimization(g_HandlePreference, &eMapGetValue);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_get_route_optimization", MapServiceGetError(nRet));
		
		if(eMapGetValue != eMapSetValue[nLoopCount])
		{
			FPRINTF("[Line : %d][%s] Mismatch in value, set = %d, get = %d\\n", __LINE__, API_NAMESPACE, eMapSetValue[nLoopCount], eMapGetValue);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose:  scenario txo set and get the route transport mode
/**
* @testcase 			ITc_maps_preference_set_get_route_transport_mode_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the route transport mode
* @scenario				set the route transport mode \n
* 						get the route transport mode \n
* 						compare the set and get values \n
* @apicovered			maps_preference_set_route_transport_mode, maps_preference_get_route_transport_mode
* @passcase				if maps_preference_set_route_transport_mode and maps_preference_get_route_transport_mode passes
* @failcase				if maps_preference_set_route_transport_mode or maps_preference_get_route_transport_mode fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_set_get_route_transport_mode_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	maps_route_transport_mode_e eMapGetValue;
	maps_route_transport_mode_e eMapSetValue[] = { MAPS_ROUTE_TRANSPORT_MODE_CAR,
											MAPS_ROUTE_TRANSPORT_MODE_PEDESTRIAN,
											MAPS_ROUTE_TRANSPORT_MODE_BICYCLE,	
											MAPS_ROUTE_TRANSPORT_MODE_PUBLICTRANSIT,
											MAPS_ROUTE_TRANSPORT_MODE_TRUCK
										  };
											
	int nRet =  0, nLoopCount = 0;
	int nMapDistanceArraySize = sizeof(eMapSetValue) / sizeof(eMapSetValue[0]);
	for(nLoopCount = 0; nLoopCount < nMapDistanceArraySize; nLoopCount++)
	{
		nRet = maps_preference_set_route_transport_mode(g_HandlePreference, eMapSetValue[nLoopCount]);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_route_transport_mode", MapServiceGetError(nRet));
		
		nRet = maps_preference_get_route_transport_mode(g_HandlePreference, &eMapGetValue);
		PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_get_route_transport_mode", MapServiceGetError(nRet));
		
		if(eMapGetValue != eMapSetValue[nLoopCount])
		{
			FPRINTF("[Line : %d][%s] Mismatch in value, set = %d, get = %d\\n", __LINE__, API_NAMESPACE, eMapSetValue[nLoopCount], eMapGetValue);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the property
/**
* @testcase 			ITc_maps_preference_set_get_property_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the property
* @scenario				set the property \n
* 						get the property \n
* 						compare the set and get values \n
* @apicovered			maps_preference_set_property, maps_preference_get
* @passcase				if maps_preference_set_property and maps_preference_get passes
* @failcase				if maps_preference_set_property or maps_preference_get fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_set_get_property_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	char *pszSetKey = "MYKEY";
	char *pszSetValue = "MYVALUE";
	char *pszGetValue = NULL;
	int nRet = maps_preference_set_property(g_HandlePreference, pszSetKey, pszSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_property", MapServiceGetError(nRet));
	
	nRet = maps_preference_get(g_HandlePreference, pszSetKey, &pszGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_get", MapServiceGetError(nRet));
	
	if(pszGetValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Get value = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	if(strcmp(pszSetValue, pszGetValue) != 0)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pszSetValue, pszGetValue);
		FREE_MEMORY(pszGetValue);
		return 1;
	}
	FREE_MEMORY(pszGetValue);
	
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the property
/**
* @testcase 			ITc_maps_preference_foreach_property_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get the property
* @scenario				set the property \n
* 						check foreach property \n
* @apicovered			maps_preference_set_property, maps_preference_get
* @passcase				if maps_preference_set_property and maps_preference_foreach_property passes
* @failcase				if maps_preference_set_property or maps_preference_foreach_property fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_preference_foreach_property_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	char *pszSetKey = "MYKEY1";
	char *pszSetValue = "MYVALUE1";
	g_bPreferenceCheck = false; 
	int nRet = maps_preference_set_property(g_HandlePreference, pszSetKey, pszSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_property", MapServiceGetError(nRet));
	
	nRet = maps_preference_foreach_property(g_HandlePreference, MapsPreferencePropertiesCallback, NULL);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_foreach_property", MapServiceGetError(nRet));
	if(!g_bPreferenceCheck)
	{
		FPRINTF("[Line : %d][%s] maps_preference_foreach_property failed, error = Callback function not invoked \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the enable status of alternative routes.
/**
* @testcase 			ITc_maps_preference_set_get_route_alternatives_enabled_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 		3.0
* @description		scenario to set and get the enable status of alternative routes.
* @scenario			Set the enable status of alternative routes. \n
* 					Get the enable status of alternative routes.\n
* 					compare the set and get values \n
* @apicovered			maps_preference_set_route_alternatives_enabled, maps_preference_get_route_alternatives_enabled
* @passcase			if maps_preference_set_route_alternatives_enabled and maps_preference_get_route_alternatives_enabled passes
* @failcase			if maps_preference_set_route_alternatives_enabled or maps_preference_get_route_alternatives_enabled fails
* @precondition		NA
* @postcondition		NA
*/
int ITc_maps_preference_set_get_route_alternatives_enabled_p(void)
{
	START_TEST(g_HandlePreference, "maps_preference");
	
	bool bSetEnable = true;
	bool bGetEnable = false;
	
	int nRet = maps_preference_set_route_alternatives_enabled(g_HandlePreference, bSetEnable);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_set_route_alternatives_enabled", MapServiceGetError(nRet));
	
	nRet = maps_preference_get_route_alternatives_enabled(g_HandlePreference, &bGetEnable);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_preference_get_route_alternatives_enabled", MapServiceGetError(nRet));
	
	if(bSetEnable != bGetEnable)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %d, get = %d\\n", __LINE__, API_NAMESPACE, bSetEnable, bGetEnable);
		return 1;
	}
		
	return 0;
}
/** @} */
/** @} */
