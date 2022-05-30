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

maps_place_filter_h g_HandlePlaceFilter = NULL;
bool g_CallbackFilterCheck = false;
//& set: MapsService


/**
 * @function 		ITs_maps_service_item_place_filter_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_item_place_filter_startup(void)
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
	int nRet = maps_place_filter_create(&g_HandlePlaceFilter);
	if ( false == bMapsFeatureSupported)
	{
		g_bFeatureSupported = false;
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_place_filter_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_place_filter_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_place_filter_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_HandlePlaceFilter = NULL;
	}
	return;
}


/**
 * @function 		ITs_maps_service_item_place_filter_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_item_place_filter_cleanup(void)
{
	if((g_HandlePlaceFilter != NULL)&& (g_bFeatureSupported == true))
	{
		maps_place_filter_destroy(g_HandlePlaceFilter);
	}
	return;
}

/**
* @function 		MapsPlaceFilterPropertiesCallback
* @description	 	callback function for fetching the list of Place Filter Properties
* @parameter		index : current index of property, total : total amount of properties, key : key of property, value : value of property, user_data : user data passed to callback function
* @return 			false
*/
bool MapsPlaceFilterPropertiesCallback(int index, int total, char* key, void* value, void* user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback MapsPlaceFilterPropertiesCallback is called \\n", __LINE__, API_NAMESPACE);
#endif
	g_CallbackFilterCheck = true;
	return false;	
}


/** @addtogroup itc-maps-service-testcases
*  @brief 		Integration testcases for module maps-service
*  @ingroup 	itc-maps-service
*  @{
*/


//& type: auto
//& purpose:  scenario to create and destroy a new filter handle
/**
* @testcase 			ITc_maps_place_filter_create_destroy_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to create and destroy a new filter handle
* @scenario				creates a new place filter handle \n
* 						destroy the place filter handle\n
* @apicovered			maps_place_filter_create, maps_place_filter_destroy
* @passcase				if maps_place_filter_create and maps_place_filter_destroy passes
* @failcase				if maps_place_filter_create or maps_place_filter_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_filter_create_destroy_p(void)
{
	START_TEST(g_HandlePlaceFilter, "maps_place_filter");
	maps_place_filter_destroy(g_HandlePlaceFilter);
	g_HandlePlaceFilter = NULL;
	
	maps_place_filter_h LocalHandleMapFilter = NULL;
	int nRet = maps_place_filter_create(&LocalHandleMapFilter);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_create", MapServiceGetError(nRet));
	CHECK_HANDLE(LocalHandleMapFilter, "maps_place_filter_create");
	
	nRet = maps_place_filter_destroy(LocalHandleMapFilter);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_destroy", MapServiceGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to clone and destroy a new filter handle
/**
* @testcase 			ITc_maps_place_filter_clone_destroy_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to clone and destroy a new filter handle
* @scenario				clone a new place filter handle \n
* 						destroy the place filter handle\n
* @apicovered			maps_place_filter_clone, maps_place_filter_destroy
* @passcase				if maps_place_filter_clone and maps_place_filter_destroy passes
* @failcase				if maps_place_filter_clone or maps_place_filter_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_filter_clone_destroy_p(void)
{
	START_TEST(g_HandlePlaceFilter, "maps_place_filter");
	
	maps_place_filter_h LocalHandleMapFilter = NULL;
	int nRet = maps_place_filter_clone(g_HandlePlaceFilter, &LocalHandleMapFilter);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_clone", MapServiceGetError(nRet));
	CHECK_HANDLE(LocalHandleMapFilter, "maps_place_filter_clone");
	
	nRet = maps_place_filter_destroy(LocalHandleMapFilter);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_destroy", MapServiceGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the filter value in an assignment with a specified string key
/**
* @testcase 			ITc_maps_place_filter_set_get_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get filter value in an assignment with a specified string key
* @scenario				set the filter value in an assignment with a specified string key \n
* 						get the filter value in an assignment with a specified string key\n
* 						compare the set and get values \n
* @apicovered			maps_place_filter_set, maps_place_filter_get
* @passcase				if maps_place_filter_set and maps_place_filter_get passes
* @failcase				if maps_place_filter_set or maps_place_filter_get fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_filter_set_get_p(void)
{
	START_TEST(g_HandlePlaceFilter, "maps_place_filter");
	char *pszKey = "MyFilterKey";
	char *pszSetValue = "Value";
	char *pszGetValue = NULL;
	int nRet =  maps_place_filter_set(g_HandlePlaceFilter, pszKey, pszSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_set", MapServiceGetError(nRet));
	
	nRet = maps_place_filter_get(g_HandlePlaceFilter, pszKey, &pszGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_get", MapServiceGetError(nRet));
	if(pszGetValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Get value = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	if(strcmp(pszSetValue,pszGetValue) != 0)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pszSetValue, pszGetValue);
		FREE_MEMORY(pszGetValue);
		return 1;
	}
	FREE_MEMORY(pszGetValue);
	
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the keyword filter value in an assignment with a specified string key
/**
* @testcase 			ITc_maps_place_filter_set_get_keyword_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get keyword filter value in an assignment with a specified string key
* @scenario				set the keyword filter value in an assignment with a specified string key \n
* 						get the keyword filter value in an assignment with a specified string key\n
* 						compare the set and get values \n
* @apicovered			maps_place_filter_set_keyword, maps_place_filter_get_keyword
* @passcase				if maps_place_filter_set_keyword and maps_place_filter_get_keyword passes
* @failcase				if maps_place_filter_set_keyword or maps_place_filter_get_keyword fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_filter_set_get_keyword_p(void)
{
	START_TEST(g_HandlePlaceFilter, "maps_place_filter");
	char *pszSetValue = "KEYWORD";
	char *pszGetValue = NULL;
	int nRet =  maps_place_filter_set_keyword(g_HandlePlaceFilter, pszSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_keyword", MapServiceGetError(nRet));
	
	nRet = maps_place_filter_get_keyword(g_HandlePlaceFilter, &pszGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_get_keyword", MapServiceGetError(nRet));
	if(pszGetValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Get value = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	if(strcmp(pszSetValue,pszGetValue) != 0)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pszSetValue, pszGetValue);
		FREE_MEMORY(pszGetValue);
		return 1;
	}	
	FREE_MEMORY(pszGetValue);
	
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get the place name filter value in an assignment with a specified string key
/**
* @testcase 			ITc_maps_place_filter_set_get_place_name_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get place name filter value in an assignment with a specified string key
* @scenario				set the place name filter value in an assignment with a specified string key \n
* 						get the place name filter value in an assignment with a specified string key\n
* 						compare the set and get values \n
* @apicovered			maps_place_filter_set_place_name, maps_place_filter_get_place_name
* @passcase				if maps_place_filter_set_place_name and maps_place_filter_get_place_name passes
* @failcase				if maps_place_filter_set_place_name or maps_place_filter_get_place_name fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_filter_set_get_place_name_p(void)
{
	START_TEST(g_HandlePlaceFilter, "maps_place_filter");
	char *pszSetValue = "PLACE";
	char *pszGetValue = NULL;
	int nRet =  maps_place_filter_set_place_name(g_HandlePlaceFilter, pszSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_place_name", MapServiceGetError(nRet));
	
	nRet = maps_place_filter_get_place_name(g_HandlePlaceFilter, &pszGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_get_place_name", MapServiceGetError(nRet));
	if(pszGetValue == NULL)
	{
		FPRINTF("[Line : %d][%s] Get value = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	if(strcmp(pszSetValue,pszGetValue) != 0)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pszSetValue, pszGetValue);
		FREE_MEMORY(pszGetValue);
		return 1;
	}	
	FREE_MEMORY(pszGetValue);
	
	return 0;
}


//& type: auto
//& purpose:  scenario to retrieves all place filter properties
/**
* @testcase 			ITc_maps_place_filter_foreach_property_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to retrieves all place filter properties
* @scenario				set the place name filter value in an assignment with a specified string key \n
* 						set the keyword filter value \n
* 						retrieves all place filter properties \n
* @apicovered			maps_place_filter_set_place_name, maps_place_filter_set_keyword, maps_place_filter_foreach_property
* @passcase				if maps_place_filter_set_place_name and maps_place_filter_set_keyword and maps_place_filter_foreach_property passes
* @failcase				if maps_place_filter_set_place_name or maps_place_filter_set_keyword or maps_place_filter_foreach_property fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_filter_foreach_property_p(void)
{
	START_TEST(g_HandlePlaceFilter, "maps_place_filter");
	char *pszSetValue = "PLACE";
	char *pszSetKeywordValue = "KEYWORDTEST";
	g_CallbackFilterCheck = false ;
	int nRet =  maps_place_filter_set_place_name(g_HandlePlaceFilter, pszSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_place_name", MapServiceGetError(nRet));
	
	nRet = maps_place_filter_set_keyword(g_HandlePlaceFilter, pszSetKeywordValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_keyword", MapServiceGetError(nRet));
	
	nRet = maps_place_filter_foreach_property(g_HandlePlaceFilter, MapsPlaceFilterPropertiesCallback, NULL);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_foreach_property", MapServiceGetError(nRet));
	if(!g_CallbackFilterCheck)
	{
		FPRINTF("[Line : %d][%s] maps_place_filter_foreach_property failed, error = Callback function not invoked \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose:  Scenario to set and get the category
/**
* @testcase 			ITc_maps_place_filter_set_get_category_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			Scenario to set and get the category
* @scenario				Create Category \n
* 						Set category \n
* 						Get category \n
* @apicovered			maps_place_category_create, maps_place_filter_set_category and maps_place_filter_get_category
* @passcase				if maps_place_filter_set_category and maps_place_filter_get_category passes
* @failcase				if maps_place_filter_set_category or maps_place_filter_get_category fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_filter_set_get_category_p(void)
{
	START_TEST(g_HandlePlaceFilter, "maps_place_filter");
	maps_place_category_h setCategory = NULL;
	maps_place_category_h getCategory = NULL;
	int nRet = -1;
	
	nRet = maps_place_category_create(&setCategory);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_create", MapServiceGetError(nRet));
	
	nRet = maps_place_filter_set_category(g_HandlePlaceFilter, setCategory);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_category", MapServiceGetError(nRet));
	
	nRet = maps_place_filter_get_category(g_HandlePlaceFilter, &getCategory);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_get_category", MapServiceGetError(nRet));
	
	maps_place_category_destroy(getCategory);
	
	return 0;
}

//& type: auto
//& purpose:  scenario to set and Get the place address
/**
* @testcase 			ITc_maps_place_filter_set_get_place_address_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to set and Get the place address
* @scenario				set the place address \n
* 						get the place address\n
* 						compare the set and get values \n
* @apicovered			maps_place_filter_set_place_address, maps_place_filter_get_place_address
* @passcase				if maps_place_filter_set_place_address and maps_place_filter_get_place_address passes
* @failcase				if maps_place_filter_set_place_address or maps_place_filter_get_place_address fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_filter_set_get_place_address_p(void)
{
	START_TEST(g_HandlePlaceFilter, "maps_place_filter");
	char *pszSetAddr = "Samsung";
	char *pszGetAddr = NULL;
	
	int nRet =  maps_place_filter_set_place_address(g_HandlePlaceFilter, pszSetAddr);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_set_place_address", MapServiceGetError(nRet));
	
	nRet = maps_place_filter_get_place_address(g_HandlePlaceFilter, &pszGetAddr);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_filter_get_place_address", MapServiceGetError(nRet));
	if(pszGetAddr == NULL)
	{
		FPRINTF("[Line : %d][%s] Get value = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	if(strcmp(pszSetAddr,pszGetAddr) != 0)
	{
		FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pszSetAddr, pszGetAddr);
		FREE_MEMORY(pszGetAddr);
		return 1;
	}	
	FREE_MEMORY(pszGetAddr);
	
	return 0;
}

/** @} */
/** @} */
