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
static maps_place_category_h g_hPlaceCategory;

//& set: MapsServicePlaceCategory
/**
 * @function 		ITs_maps_place_category_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_place_category_startup(void)
{
	struct stat stBuff;   
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	
	bool bMapsFeatureSupported = TCTCheckSystemInfoFeatureSupported(MAPS_FEATURE, API_NAMESPACE);
	
	g_bCategoryCreate = false;
	int nRet = maps_place_category_create(&g_hPlaceCategory);
	if ( false == bMapsFeatureSupported)
	{
		g_bFeatureSupported = false;
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_place_category_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_place_category_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_place_category_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		return;
	}
	else if (g_hPlaceCategory == NULL)
	{
		FPRINTF("[Line : %d][%s] maps_place_category_create fail in startup error returned : place category handle is NULL \\n", __LINE__, API_NAMESPACE);
		return;
	}
	
	g_bCategoryCreate = true;
	return;
}


/**
 * @function 		ITs_maps_place_category_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_place_category_cleanup(void)
{
	if(g_hPlaceCategory != NULL)
	{
		maps_place_category_destroy(g_hPlaceCategory);
	}
	return;
}


/** @addtogroup itc-maps-service-testcases
*  @brief 		Integration testcases for module maps-service
*  @ingroup 	itc-maps-service
*  @{
*/


//& type: auto
//& purpose:  scenario to create and destroy a new place category handle
/**
* @testcase 			ITc_maps_place_category_create_destroy_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to create and destroy a place category handle
* @scenario				creates a new place category handle \n
* 						destroy the place category handle\n
* @apicovered			maps_place_category_create, maps_place_category_destroy
* @passcase				if maps_place_category_create and maps_place_category_destroy passes
* @failcase				if maps_place_category_create or maps_place_category_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_category_create_destroy_p(void)
{
	START_TEST_PLACE_CATEGORY;
	maps_place_category_h hPlaceCategory = NULL;
	
	int nRet = maps_place_category_create(&hPlaceCategory);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hPlaceCategory, "maps_place_category_create");

	nRet = maps_place_category_destroy(hPlaceCategory);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to clone a new place category handle
/**
* @testcase 			ITc_maps_place_category_clone_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to clone a place category handle
* @scenario				clones a new place category handle \n
* @apicovered			maps_place_category_clone
* @passcase				if maps_place_category_clone passes
* @failcase				if maps_place_category_clone fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_category_clone_p(void)
{
	START_TEST_PLACE_CATEGORY;
	
	maps_place_category_h hClonePlaceCategory = NULL;

	int nRet = maps_place_category_clone(g_hPlaceCategory, &hClonePlaceCategory);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_clone", MapServiceGetError(nRet));
	CHECK_HANDLE(hClonePlaceCategory, "maps_place_category_clone");

	nRet = maps_place_category_destroy(hClonePlaceCategory);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_category_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to set and get id of place category
/**
* @testcase 			ITc_maps_place_category_set_get_id_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to set and get id of place category
* @scenario				scenario to set and get id of place category \n
* @apicovered			maps_place_category_set_id, maps_place_category_get_id
* @passcase				if maps_place_category_set_id and maps_place_category_get_id passes
* @failcase				if maps_place_category_set_id and maps_place_category_get_id fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_category_set_get_id_p(void)
{
	START_TEST_PLACE_CATEGORY;
	char *pszId = "CategoryId";
	char *pszGetId = NULL;
	
	int nRet =  maps_place_category_set_id(g_hPlaceCategory, pszId);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_set_id", MapServiceGetError(nRet));
	
	nRet = maps_place_category_get_id(g_hPlaceCategory, &pszGetId);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_get_id", MapServiceGetError(nRet));
	
	if(strcmp(pszId,pszGetId) != 0)
	{
		FPRINTF("[Line : %d][%s] maps_place_category_get_id, error = set get value are not same. set value = %s get value = %s \\n", __LINE__, API_NAMESPACE, pszId, pszGetId);
		free(pszGetId);
		return 1;
	}
	free(pszGetId);

	return 0;
}

//& type: auto
//& purpose:  scenario to set and get name of place category
/**
* @testcase 			ITc_maps_place_category_set_get_name_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to set and get name of place category
* @scenario				scenario to set and get name of place category \n
* @apicovered			maps_place_category_set_name, maps_place_category_get_name
* @passcase				if maps_place_category_set_name and maps_place_category_get_name passes
* @failcase				if maps_place_category_set_name and maps_place_category_get_name fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_category_set_get_name_p(void)
{
	START_TEST_PLACE_CATEGORY;
	char *pszName = "MyPlace";
	char *pszGetName = NULL;
	
	int nRet =  maps_place_category_set_name(g_hPlaceCategory, pszName);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_set_name", MapServiceGetError(nRet));
	
	nRet = maps_place_category_get_name(g_hPlaceCategory, &pszGetName);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_get_name", MapServiceGetError(nRet));
	
	if(strcmp(pszName,pszGetName) != 0)
	{
		FPRINTF("[Line : %d][%s] maps_place_category_get_name, error = set get value are not same. set value = %s get value = %s \\n", __LINE__, API_NAMESPACE, pszName, pszGetName);
		free(pszGetName);
		return 1;
	}
	free(pszGetName);
	
	return 0;
}
//& type: auto
//& purpose:  scenario to set and get url of place category
/**
* @testcase 			ITc_maps_place_category_set_get_url_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to set and get url of place category
* @scenario				scenario to set and get url of place category \n
* @apicovered			maps_place_category_set_url, maps_place_category_get_url
* @passcase				if maps_place_category_set_url and maps_place_category_get_url passes
* @failcase				if maps_place_category_set_url and maps_place_category_get_url fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_category_set_get_url_p(void)
{
	START_TEST_PLACE_CATEGORY;
	
	char *pszUrl = "http://MyUrl.com";
	char *pszGetUrl = NULL;
	
	int nRet =  maps_place_category_set_url(g_hPlaceCategory, pszUrl);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_set_url", MapServiceGetError(nRet));
	
	nRet = maps_place_category_get_url(g_hPlaceCategory, &pszGetUrl);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_get_url", MapServiceGetError(nRet));
	
	if(strcmp(pszUrl,pszGetUrl) != 0)
	{
		FPRINTF("[Line : %d][%s] maps_place_category_get_url, error = set get value are not same. set value = %s get value = %s \\n", __LINE__, API_NAMESPACE, pszUrl, pszGetUrl);
		free(pszGetUrl);
		return 1;
	}
	free(pszGetUrl);
	
	return 0;
}		
/** @} */
/** @} */
