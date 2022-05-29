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
static maps_place_contact_h g_place_contact = NULL;

	
static bool MapsPlaceContactsCb(int index, int total, maps_place_contact_h contact, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsPlaceContactsCb callback\\n", __LINE__, API_NAMESPACE); 
    g_nCheckCb = true;
	if(g_nClone == 1)
	{
		g_nCheckRet = maps_place_contact_clone(contact, &g_place_contact);
	}
	
	return true;
}
/**
 * @function 		ITs_maps_place_contact_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_place_contact_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	MapsPlaceHandleHelperHERE();
	
	return;
}


/**
 * @function 		ITs_maps_place_contact_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_place_contact_cleanup(void)
{
	return;
}
//& type: auto
//& purpose:  scenario to retrieve all contacts for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_place_foreach_contact_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to retrieve all contacts
* @scenario				maps_place_foreach_contact
* @apicovered			maps_place_foreach_contact
* @passcase				if maps_place_foreach_contact passes
* @failcase				if maps_place_foreach_contact fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_foreach_contact_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	g_nCheckCb = 0;
	g_nClone = 0;
	
	nRet = maps_place_foreach_contact(g_maps_place, MapsPlaceContactsCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_foreach_contact", MapServiceGetError(nRet),maps_place_destroy(g_maps_place));
	
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsPlaceContactsCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_place_destroy(g_maps_place);
		return 1;
	}
    nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}		   
//& type: auto
//& purpose:  scenario to clone and destroy the place contact handle.
/**
* @testcase 			ITc_maps_place_contact_clone_destroy_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to clone and destroy the place contact handle.
* @scenario				maps_place_contact_clone, maps_place_contact_destroy
* @apicovered			maps_place_contact_clone, maps_place_contact_destroy
* @passcase				if maps_place_contact_clone and maps_place_contact_destroy passes
* @failcase				if maps_place_contact_clone and maps_place_contact_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_contact_clone_destroy_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	
	nRet = maps_place_foreach_contact(g_maps_place, MapsPlaceContactsCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_foreach_contact", MapServiceGetError(nRet),maps_place_destroy(g_maps_place));
	
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsPlaceContactsCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_contact_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(g_place_contact, "maps_place_contact_clone",maps_place_destroy(g_maps_place));
	
	nRet = maps_place_contact_destroy(g_place_contact);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_contact_destroy", MapServiceGetError(nRet),maps_place_destroy(g_maps_place));
	
    nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get label of the place contact handle.
/**
* @testcase 			ITc_maps_place_contact_get_label_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get label of the place contact handle.
* @scenario				maps_place_contact_get_label
* @apicovered			maps_place_contact_get_label
* @passcase				if maps_place_contact_get_label passes
* @failcase				if maps_place_contact_get_label fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_contact_get_label_p(void)
{
	START_TEST_PLACE;

	int nRet;
	char* label = NULL;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	
	nRet = maps_place_foreach_contact(g_maps_place, MapsPlaceContactsCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_foreach_contact", MapServiceGetError(nRet),maps_place_destroy(g_maps_place);maps_place_contact_destroy(g_place_contact));
	
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsPlaceContactsCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_place_destroy(g_maps_place);
		maps_place_contact_destroy(g_place_contact);
		return 1;
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_contact_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(g_place_contact, "maps_place_contact_clone",maps_place_destroy(g_maps_place));
	
	nRet = maps_place_contact_get_label(g_place_contact, &label);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_contact_get_label", MapServiceGetError(nRet),maps_place_contact_destroy(g_place_contact);maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(label, "maps_place_contact_get_label",maps_place_contact_destroy(g_place_contact);maps_place_destroy(g_maps_place));
		
	free(label);
	nRet = maps_place_contact_destroy(g_place_contact);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_contact_destroy", MapServiceGetError(nRet));
    nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get type of the place contact handle.
/**
* @testcase 			ITc_maps_place_contact_get_type_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get type of the place contact handle.
* @scenario				maps_place_contact_get_type
* @apicovered			maps_place_contact_get_type
* @passcase				if maps_place_contact_get_type passes
* @failcase				if maps_place_contact_get_type fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_contact_get_type_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	char* type = NULL;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	
	nRet = maps_place_foreach_contact(g_maps_place, MapsPlaceContactsCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_foreach_contact", MapServiceGetError(nRet),maps_place_destroy(g_maps_place);maps_place_contact_destroy(g_place_contact));
	
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsPlaceContactsCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_place_destroy(g_maps_place);
		maps_place_contact_destroy(g_place_contact);
		return 1;
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_contact_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(g_place_contact, "maps_place_contact_clone",maps_place_destroy(g_maps_place));

	nRet = maps_place_contact_get_type(g_place_contact, &type);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_contact_get_type", MapServiceGetError(nRet),maps_place_contact_destroy(g_place_contact);maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(type, "maps_place_contact_get_type",maps_place_contact_destroy(g_place_contact);maps_place_destroy(g_maps_place));
		
	free(type);
	nRet = maps_place_contact_destroy(g_place_contact);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_contact_destroy", MapServiceGetError(nRet));
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get value of the place contact handle.
/**
* @testcase 			ITc_maps_place_contact_get_value_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get value of the place contact handle.
* @scenario				maps_place_contact_get_value
* @apicovered			maps_place_contact_get_value
* @passcase				if maps_place_contact_get_value passes
* @failcase				if maps_place_contact_get_value fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_contact_get_value_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	char* value = NULL;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	
	nRet = maps_place_foreach_contact(g_maps_place, MapsPlaceContactsCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_foreach_contact", MapServiceGetError(nRet),maps_place_destroy(g_maps_place);maps_place_contact_destroy(g_place_contact));
	
	//RUN_POLLING_LOOP;

	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsPlaceContactsCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_place_destroy(g_maps_place);
		maps_place_contact_destroy(g_place_contact);
		return 1;
	}
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_contact_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(g_place_contact, "maps_place_contact_clone",maps_place_destroy(g_maps_place));

	nRet = maps_place_contact_get_value(g_place_contact, &value);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_contact_get_value", MapServiceGetError(nRet),maps_place_contact_destroy(g_place_contact);maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(value, "maps_place_contact_get_value",maps_place_contact_destroy(g_place_contact);maps_place_destroy(g_maps_place));
		
	free(value);
	nRet = maps_place_contact_destroy(g_place_contact);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_contact_destroy", MapServiceGetError(nRet));
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
/** @} */
/** @} */
