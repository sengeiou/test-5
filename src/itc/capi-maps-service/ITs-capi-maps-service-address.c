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

maps_address_h g_HandleMapAddress = NULL;
maps_address_list_h g_HandleMapAddressList = NULL;
bool g_bCbCalledAddressList = false;
//& set: MapsService

/**
* @function 		MapsAddressListCallback
* @description	 	callback function 
* @parameter		int index, maps_address_h addr, void *user_data
* @return 			false
*/
bool MapsAddressListCallback(int index, maps_address_h addr, void *user_data)
{
#if DEGUG
	FPRINTF("[Line : %d][%s] Callback MapsAddressListCallback is called \\n", __LINE__, API_NAMESPACE);
#endif
	if (addr == NULL)
	{
		FPRINTF("[Line : %d][%s]Address Handle is NULL \\n", __LINE__, API_NAMESPACE);
		return true;
	}
	g_bCbCalledAddressList = true;
	return false;	
}

/**
 * @function 		ITs_maps_service_address_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_address_startup(void)
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
	
	int nRet = maps_address_create(&g_HandleMapAddress);
	if ( false == bMapsFeatureSupported)
	{
		g_bFeatureSupported = false;
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] maps_address_create API call returned mismatch %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] maps_address_create API call correctly returned %s error for unsupported maps feature\\n", __LINE__, API_NAMESPACE, MapServiceGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}
		
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_address_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		g_HandleMapAddress = NULL;
		return;
	}
	
	nRet = maps_address_list_create(&g_HandleMapAddressList);
	if ( nRet != MAPS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] maps_address_list_create fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , MapServiceGetError(nRet));
		return;
	}
	
	return;
}


/**
 * @function 		ITs_maps_service_address_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_service_address_cleanup(void)
{
	if((g_HandleMapAddress != NULL)&& (g_bFeatureSupported == true))
	{
		maps_address_destroy(g_HandleMapAddress);
	}
	if(g_HandleMapAddressList != NULL)
	{
		maps_address_list_destroy(g_HandleMapAddressList);
	}
	
	return;
}

/** @addtogroup itc-maps-service-testcases
*  @brief 		Integration testcases for module maps-service
*  @ingroup 	itc-maps-service
*  @{
*/

//& type: auto
//& purpose:  scenario to creates and destroy a new address handle
/**
* @testcase 			ITc_maps_address_create_destroy_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to creates and destroy a new address handle
* @scenario				creates a new address handle\n
* 						destroy the address handle\n
* @apicovered			maps_address_create, maps_address_destroy
* @passcase				if maps_address_create and maps_address_destroy passes
* @failcase				if maps_address_create or maps_address_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_create_destroy_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	maps_address_destroy(g_HandleMapAddress);
	g_HandleMapAddress = NULL;
	
	maps_address_h LocalHandleMapAddress = NULL;
	int nRet = maps_address_create(&LocalHandleMapAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_create", MapServiceGetError(nRet));
	CHECK_HANDLE(LocalHandleMapAddress, "maps_address_create");
	
	nRet = maps_address_destroy(LocalHandleMapAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_destroy", MapServiceGetError(nRet));
	return 0;
}


//& type: auto
//& purpose:  scenario to clone address handle
/**
* @testcase 			ITc_maps_address_clone_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to clone address handle
* @scenario				clone address handle\n
* 						destroy cloned address handle\n
* @apicovered			maps_address_clone, maps_address_destroy
* @passcase				if maps_address_clone and maps_address_destroy passes
* @failcase				if maps_address_clone or maps_address_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_clone_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	maps_address_h LocalHandleMapAddress = NULL;
	int nRet = maps_address_clone(g_HandleMapAddress, &LocalHandleMapAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_clone", MapServiceGetError(nRet));
	CHECK_HANDLE(LocalHandleMapAddress, "maps_address_clone");
	
	nRet = maps_address_destroy(LocalHandleMapAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_destroy", MapServiceGetError(nRet));
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get building number
/**
* @testcase 			ITc_maps_address_set_get_building_number_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get building number
* @scenario				set building number\n
* 						get building number\n
* 						compare the set and get building number\n
* @apicovered			maps_address_set_building_number, maps_address_get_building_number
* @passcase				if maps_address_set_building_number and maps_address_get_building_number passes and set get values are same
* @failcase				if maps_address_set_building_number or maps_address_get_building_number fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_set_get_building_number_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	char *szSetValue = "BUILDING";
	char *szGetValue = NULL;
	int nRet = maps_address_set_building_number(g_HandleMapAddress, szSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_set_building_number", MapServiceGetError(nRet));
	
	nRet = maps_address_get_building_number(g_HandleMapAddress, &szGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_get_building_number", MapServiceGetError(nRet));
	COMPARE_STRING(szSetValue, szGetValue, "maps_address_get_building_number");
	CHECK_VALUE_STRING(szGetValue, "maps_address_get_building_numbers");
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get city
/**
* @testcase 			ITc_maps_address_set_get_city_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get city
* @scenario				set city\n
* 						get city\n
* 						compare the set and get city\n
* @apicovered			maps_address_set_city, maps_address_get_city
* @passcase				if maps_address_set_city and maps_address_get_city passes and set get values are same
* @failcase				if maps_address_set_city or maps_address_get_city fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_set_get_city_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	char *szSetValue = "CITY";
	char *szGetValue = NULL;
	int nRet = maps_address_set_city(g_HandleMapAddress, szSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_set_city", MapServiceGetError(nRet));
	
	nRet = maps_address_get_city(g_HandleMapAddress, &szGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_get_city", MapServiceGetError(nRet));
	COMPARE_STRING(szSetValue, szGetValue, "maps_address_get_city");
	CHECK_VALUE_STRING(szGetValue, "maps_address_get_citys");
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get country
/**
* @testcase 			ITc_maps_address_set_get_country_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get country
* @scenario				set country\n
* 						get country\n
* 						compare the set and get country\n
* @apicovered			maps_address_set_country, maps_address_get_country
* @passcase				if maps_address_set_country and maps_address_get_country passes  and set get values are same
* @failcase				if maps_address_set_country or maps_address_get_country fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_set_get_country_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	char *szSetValue = "COUNTRY";
	char *szGetValue = NULL;
	int nRet = maps_address_set_country(g_HandleMapAddress, szSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_set_country", MapServiceGetError(nRet));
	
	nRet = maps_address_get_country(g_HandleMapAddress, &szGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_get_country", MapServiceGetError(nRet));
	COMPARE_STRING(szSetValue, szGetValue, "maps_address_get_country");
	CHECK_VALUE_STRING(szGetValue, "maps_address_get_country");
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get country code
/**
* @testcase 			ITc_maps_address_set_get_country_code_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get country_code
* @scenario				set country code\n
* 						get country code\n
* 						compare the set and get country_code\n
* @apicovered			maps_address_set_country_code, maps_address_get_country_code
* @passcase				if maps_address_set_country_code and maps_address_get_country_code passes  and set get values are same
* @failcase				if maps_address_set_country_code or maps_address_get_country_code fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_set_get_country_code_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	char *szSetValue = "COUNTRY_CODE";
	char *szGetValue = NULL;
	int nRet = maps_address_set_country_code(g_HandleMapAddress, szSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_set_country_code", MapServiceGetError(nRet));
	
	nRet = maps_address_get_country_code(g_HandleMapAddress, &szGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_get_country_code", MapServiceGetError(nRet));
	COMPARE_STRING(szSetValue, szGetValue, "maps_address_get_country_code");
	CHECK_VALUE_STRING(szGetValue, "maps_address_get_country_code");
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get county
/**
* @testcase 			ITc_maps_address_set_get_county_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get county
* @scenario				set county\n
* 						get county\n
* 						compare the set and get county\n
* @apicovered			maps_address_set_county, maps_address_get_county
* @passcase				if maps_address_set_county and maps_address_get_county passes  and set get values are same
* @failcase				if maps_address_set_county or maps_address_get_county fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_set_get_county_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	char *szSetValue = "COUNTY";
	char *szGetValue = NULL;
	int nRet = maps_address_set_county(g_HandleMapAddress, szSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_set_county", MapServiceGetError(nRet));
	
	nRet = maps_address_get_county(g_HandleMapAddress, &szGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_get_county", MapServiceGetError(nRet));
	COMPARE_STRING(szSetValue, szGetValue, "maps_address_get_county");
	CHECK_VALUE_STRING(szGetValue, "maps_address_get_county");
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get district
/**
* @testcase 			ITc_maps_address_set_get_district_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get district
* @scenario				set district\n
* 						get district\n
* 						compare the set and get district\n
* @apicovered			maps_address_set_district, maps_address_get_district
* @passcase				if maps_address_set_district and maps_address_get_district passes  and set get values are same
* @failcase				if maps_address_set_district or maps_address_get_district fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_set_get_district_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	char *szSetValue = "DISTRICT";
	char *szGetValue = NULL;
	int nRet = maps_address_set_district(g_HandleMapAddress, szSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_set_district", MapServiceGetError(nRet));
	
	nRet = maps_address_get_district(g_HandleMapAddress, &szGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_get_district", MapServiceGetError(nRet));
	COMPARE_STRING(szSetValue, szGetValue, "maps_address_get_district");
	CHECK_VALUE_STRING(szGetValue, "maps_address_get_district");
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get freetext
/**
* @testcase 			ITc_maps_address_set_get_freetext_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get freetext
* @scenario				set freetext\n
* 						get freetext\n
* 						compare the set and get freetext\n
* @apicovered			maps_address_set_freetext, maps_address_get_freetext
* @passcase				if maps_address_set_freetext and maps_address_get_freetext passes  and set get values are same
* @failcase				if maps_address_set_freetext or maps_address_get_freetext fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_set_get_freetext_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	char *szSetValue = "FREE TEXT";
	char *szGetValue = NULL;
	int nRet = maps_address_set_freetext(g_HandleMapAddress, szSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_set_freetext", MapServiceGetError(nRet));
	
	nRet = maps_address_get_freetext(g_HandleMapAddress, &szGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_get_freetext", MapServiceGetError(nRet));
	COMPARE_STRING(szSetValue, szGetValue, "maps_address_get_freetext");
	CHECK_VALUE_STRING(szGetValue, "maps_address_get_freetext");
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get postal code
/**
* @testcase 			ITc_maps_address_set_get_postal_code_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get postal_code
* @scenario				set postal code\n
* 						get postal code\n
* 						compare the set and get postal_code\n
* @apicovered			maps_address_set_postal_code, maps_address_get_postal_code
* @passcase				if maps_address_set_postal_code and maps_address_get_postal_code passes  and set get values are same
* @failcase				if maps_address_set_postal_code or maps_address_get_postal_code fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_set_get_postal_code_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	char *szSetValue = "POSTAL CODE";
	char *szGetValue = NULL;
	int nRet = maps_address_set_postal_code(g_HandleMapAddress, szSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_set_postal_code", MapServiceGetError(nRet));
	
	nRet = maps_address_get_postal_code(g_HandleMapAddress, &szGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_get_postal_code", MapServiceGetError(nRet));
	COMPARE_STRING(szSetValue, szGetValue, "maps_address_get_postal_code");
	CHECK_VALUE_STRING(szGetValue, "maps_address_get_postal_code");
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get state
/**
* @testcase 			ITc_maps_address_set_get_state_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get state
* @scenario				set state\n
* 						get state\n
* 						compare the set and get state\n
* @apicovered			maps_address_set_state, maps_address_get_state
* @passcase				if maps_address_set_state and maps_address_get_state passes  and set get values are same
* @failcase				if maps_address_set_state or maps_address_get_state fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_set_get_state_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	char *szSetValue = "STATE";
	char *szGetValue = NULL;
	int nRet = maps_address_set_state(g_HandleMapAddress, szSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_set_state", MapServiceGetError(nRet));
	
	nRet = maps_address_get_state(g_HandleMapAddress, &szGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_get_state", MapServiceGetError(nRet));
	COMPARE_STRING(szSetValue, szGetValue, "maps_address_get_state");
	CHECK_VALUE_STRING(szGetValue, "maps_address_get_state");
	return 0;
}

//& type: auto
//& purpose:  scenario to set and get street
/**
* @testcase 			ITc_maps_address_set_get_street_p
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.4
* @description			scenario to set and get street
* @scenario				set street\n
* 						get street\n
* 						compare the set and get street\n
* @apicovered			maps_address_set_street, maps_address_get_street
* @passcase				if maps_address_set_street and maps_address_get_street passes  and set get values are same
* @failcase				if maps_address_set_street or maps_address_get_street fails or set get values are not same
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_set_get_street_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	char *szSetValue = "STREET";
	char *szGetValue = NULL;
	int nRet = maps_address_set_street(g_HandleMapAddress, szSetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_set_street", MapServiceGetError(nRet));
	
	nRet = maps_address_get_street(g_HandleMapAddress, &szGetValue);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_get_street", MapServiceGetError(nRet));
	COMPARE_STRING(szSetValue, szGetValue, "maps_address_get_street");
	CHECK_VALUE_STRING(szGetValue, "maps_address_get_street");
	return 0;
}

//& type: auto
//& purpose:  scenario to create and destroy  address list
/**
* @testcase 			ITc_maps_address_list_create_destroy_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to create and destroy  address list
* @scenario				create list\n
* 						destroy list\n
* @apicovered			maps_address_list_create, maps_address_list_destroy
* @passcase				if maps_address_list_create and maps_address_list_destroy passes  
* @failcase				if maps_address_list_create or maps_address_list_destroy fails 
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_list_create_destroy_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	
	maps_address_list_h LocalHandleAddrList = NULL;
	int nRet = maps_address_list_create(&LocalHandleAddrList);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_list_create", MapServiceGetError(nRet));
	if (LocalHandleAddrList == NULL)
	{
		FPRINTF("[Line : %d][%s]LocalHandleAddrList is empty \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = maps_address_list_destroy(LocalHandleAddrList);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_list_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to append and remove list
/**
* @testcase 			ITc_maps_address_list_append_remove_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to append and remove list
* @scenario				append and remove list\n
* @apicovered			maps_address_list_append and maps_address_list_remove
* @passcase				if maps_address_list_append  and maps_address_list_remove passes  
* @failcase				if maps_address_list_append and maps_address_list_remove fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_list_append_remove_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	START_TEST(g_HandleMapAddressList, "maps_address_list");

	int nRet = maps_address_list_append(g_HandleMapAddressList, g_HandleMapAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_list_append", MapServiceGetError(nRet));
	
	nRet = maps_address_list_remove(g_HandleMapAddressList, g_HandleMapAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_list_remove", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to get length of list
/**
* @testcase 			ITc_maps_address_list_get_length_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get length of list
* @scenario				get length of list\n
* @apicovered			maps_address_list_get_length
* @passcase				if maps_address_list_get_length passes  
* @failcase				if maps_address_list_get_length fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_list_get_length_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	START_TEST(g_HandleMapAddressList, "maps_address_list");

	int dGetLength = 0;
	
	int nRet = maps_address_list_append(g_HandleMapAddressList, g_HandleMapAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_list_append", MapServiceGetError(nRet));
	
	nRet  = maps_address_list_get_length(g_HandleMapAddressList, &dGetLength);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_list_get_length", MapServiceGetError(nRet));
	
	if(dGetLength != 1)
	{
		FPRINTF("[Line : %d][%s] dGetLength is mismatch, failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = maps_address_list_remove(g_HandleMapAddressList, g_HandleMapAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_list_remove", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to check list addrss
/**
* @testcase 			ITc_maps_address_list_foreach_p
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to check list addrss
* @scenario				check list addrss\n
* @apicovered			maps_address_list_foreach
* @passcase				if maps_address_list_foreach passes  
* @failcase				if maps_address_list_foreach fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_address_list_foreach_p(void)
{
	START_TEST(g_HandleMapAddress, "maps_address");
	START_TEST(g_HandleMapAddressList, "maps_address_list");

	int nRet = maps_address_list_append(g_HandleMapAddressList, g_HandleMapAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_list_append", MapServiceGetError(nRet));
	
	g_bCbCalledAddressList = false;
		
	nRet = maps_address_list_foreach(g_HandleMapAddressList, MapsAddressListCallback, NULL);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_list_foreach", MapServiceGetError(nRet));
	if(!g_bCbCalledAddressList)
	{
		FPRINTF("[Line : %d][%s] maps_address_list_foreach failed, error = Callback function not invoked \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = maps_address_list_remove(g_HandleMapAddressList, g_HandleMapAddress);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_address_list_remove", MapServiceGetError(nRet));
	
	return 0;
}
/** @} */
/** @} */
