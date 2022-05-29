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
/*static gboolean Timeout_Function(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}*/
static bool MapsPlaceCategoriesCb(int index, int total, maps_place_category_h category, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsPlaceCategoriesCb callback\\n", __LINE__, API_NAMESPACE); 
    g_nCheckCb = true;
	
	return true;
}

/**
 * @function 		ITs_maps_place_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_place_startup(void)
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
 * @function 		ITs_maps_place_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_place_cleanup(void)
{
	return;
}

//& type: auto
//& purpose:  scenario to obtains the distance for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_place_get_distance_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to obtains the distance for a specified coordinates boundary.
* @scenario				maps_place_get_distance
* @apicovered			maps_place_get_distance
* @passcase				if maps_place_get_distance passes
* @failcase				if maps_place_get_distance fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_maps_place_get_distance_p(void)
{
	START_TEST_PLACE;
	
	int distance = 0;
	int nRet;

	nRet = maps_place_get_distance(g_maps_place,&distance);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_get_distance", MapServiceGetError(nRet),maps_place_destroy(g_maps_place));
	
	if(distance < 0)
	{
		FPRINTF("[Line : %d][%s] Invalid distance\\n", __LINE__, API_NAMESPACE);
		maps_place_destroy(g_maps_place);
		return 1;
	}

	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to obtains the id for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_place_get_id_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to obtains the id for a specified coordinates boundary.
* @scenario				maps_place_get_id
* @apicovered			maps_place_get_id
* @passcase				if maps_place_get_id passes
* @failcase				if maps_place_get_id fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_maps_place_get_id_p(void)
{
	START_TEST_PLACE;
	
	char *id = NULL;
	int nRet;
	
	nRet = maps_place_get_id(g_maps_place,&id);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_get_id", MapServiceGetError(nRet),maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(id, "maps_place_get_id",maps_place_destroy(g_maps_place));
		
	free(id);
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to obtains the location for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_place_get_location_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to obtains the location for a specified coordinates boundary.
* @scenario				maps_place_get_location
* @apicovered			maps_place_get_location
* @passcase				if maps_place_get_location passes
* @failcase				if maps_place_get_location fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_maps_place_get_location_p(void)
{
	START_TEST_PLACE;
	
	maps_coordinates_h location = NULL;
	int nRet;
	
	nRet = maps_place_get_location(g_maps_place,&location);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_get_location", MapServiceGetError(nRet),maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(location, "maps_place_get_location",maps_place_destroy(g_maps_place));
	
	nRet = maps_coordinates_destroy(location);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_coordinates_destroy", MapServiceGetError(nRet));
	nRet = maps_place_destroy(g_maps_place);	
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to obtains the name for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_place_get_name_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to obtains the name for a specified coordinates boundary.
* @scenario				maps_place_get_name
* @apicovered			maps_place_get_name
* @passcase				if maps_place_get_name passes
* @failcase				if maps_place_get_name fails
* @precondition			NA
* @postcondition		NA
*/

int ITc_maps_place_get_name_p(void)
{
	START_TEST_PLACE;
	
	char *name = NULL;
	int nRet;
	
	nRet = maps_place_get_name(g_maps_place,&name);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_get_name", MapServiceGetError(nRet), maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(name, "maps_place_get_name",maps_place_destroy(g_maps_place));
	
	free(name);	
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to obtains the rating for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_place_get_rating_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to obtains the rating for a specified coordinates boundary.
* @scenario				maps_place_get_rating
* @apicovered			maps_place_get_rating
* @passcase				if maps_place_get_rating passes
* @failcase				if maps_place_get_rating fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_get_rating_p(void)
{
	START_TEST_PLACE;
	
	maps_place_rating_h rating = NULL;
	int nRet;
	
	nRet = maps_place_get_rating(g_maps_place,&rating);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_get_rating", MapServiceGetError(nRet), maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(rating, "maps_place_get_rating", maps_place_destroy(g_maps_place));
	
	nRet = maps_place_rating_destroy(rating);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_rating_destroy", MapServiceGetError(nRet));
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to clone and destroy the rating for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_place_rating_clone_destroy_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to clone and destroy the rating for a specified coordinates boundary.
* @scenario				maps_place_rating_clone, maps_place_rating_destroy
* @apicovered			maps_place_rating_clone, maps_place_rating_destroy
* @passcase				if maps_place_rating_clone and maps_place_rating_destroy passes
* @failcase				if maps_place_rating_clone and maps_place_rating_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_rating_clone_destroy_p(void)
{
	START_TEST_PLACE;
	
	maps_place_rating_h rating = NULL;
	maps_place_rating_h hRating = NULL;
	int nRet;

	nRet = maps_place_get_rating(g_maps_place, &rating);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_get_rating", MapServiceGetError(nRet),maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(rating, "maps_place_get_rating",maps_place_destroy(g_maps_place));
	
	nRet = maps_place_rating_clone(rating, &hRating);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_rating_clone", MapServiceGetError(nRet), maps_place_rating_destroy(rating);maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(hRating, "maps_place_rating_clone", maps_place_rating_destroy(rating);maps_place_destroy(g_maps_place));
	
	nRet = maps_place_rating_destroy(hRating);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_rating_destroy", MapServiceGetError(nRet), maps_place_rating_destroy(rating);maps_place_destroy(g_maps_place));
	
	nRet = maps_place_rating_destroy(rating);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_rating_destroy", MapServiceGetError(nRet));
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to obtains the place rating average
/**
* @testcase 			ITc_maps_place_rating_get_average_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to obtains the place rating average.
* @scenario				maps_place_rating_get_average
* @apicovered			maps_place_rating_get_average
* @passcase				if maps_place_rating_get_average passes
* @failcase				if maps_place_rating_get_average fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_rating_get_average_p(void)
{
	START_TEST_PLACE;
	
	maps_place_rating_h rating = NULL;
	double average = 0.0;
	int nRet;
	
	nRet = maps_place_get_rating(g_maps_place,&rating);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_get_rating", MapServiceGetError(nRet), maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(rating, "maps_place_get_rating", maps_place_destroy(g_maps_place));
	
	nRet = maps_place_rating_get_average(rating, &average);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_rating_get_average", MapServiceGetError(nRet), maps_place_rating_destroy(rating);maps_place_destroy(g_maps_place));
	
	if(average < 0)
	{
		FPRINTF("[Line : %d][%s] Invalid average\\n", __LINE__, API_NAMESPACE);
		maps_place_rating_destroy(rating);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	nRet = maps_place_rating_destroy(rating);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_rating_destroy", MapServiceGetError(nRet));
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to obtains the place rating count
/**
* @testcase 			ITc_maps_place_rating_get_count_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to obtains the place rating count.
* @scenario				maps_place_rating_get_count
* @apicovered			maps_place_rating_get_count
* @passcase				if maps_place_rating_get_count passes
* @failcase				if maps_place_rating_get_count fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_rating_get_count_p(void)
{
	START_TEST_PLACE;
	
	maps_place_rating_h rating = NULL;
	int count = 0;
	int nRet;

	nRet = maps_place_get_rating(g_maps_place,&rating);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_get_rating", MapServiceGetError(nRet), maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(rating, "maps_place_get_rating", maps_place_destroy(g_maps_place));
	
	nRet = maps_place_rating_get_count(rating, &count);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_rating_get_count", MapServiceGetError(nRet), maps_place_rating_destroy(rating);maps_place_destroy(g_maps_place));
	
	if(count < 0)
	{
		FPRINTF("[Line : %d][%s] Invalid count\\n", __LINE__, API_NAMESPACE);
		maps_place_rating_destroy(rating);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	nRet = maps_place_rating_destroy(rating);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_rating_destroy", MapServiceGetError(nRet));
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to obtains the address for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_place_get_address_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to obtains the address for a specified coordinates boundary.
* @scenario				maps_place_get_address
* @apicovered			maps_place_get_address
* @passcase				if maps_place_get_address passes
* @failcase				if maps_place_get_address fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_get_address_p(void)
{
	START_TEST_PLACE;
	
	maps_address_h address = NULL;
	int nRet;
	
	nRet = maps_place_get_address(g_maps_place,&address);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_get_address", MapServiceGetError(nRet), maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(address, "maps_place_get_address", maps_place_destroy(g_maps_place));
	
	nRet = maps_address_destroy(address);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_address_destroy", MapServiceGetError(nRet));
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get the place related link for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_place_get_related_link_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the place related link for a specified coordinates boundary.
* @scenario				maps_place_get_related_link
* @apicovered			maps_place_get_related_link
* @passcase				if maps_place_get_related_link passes
* @failcase				if maps_place_get_related_link fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_get_related_link_p(void)
{
	START_TEST_PLACE;
	
	maps_place_link_object_h related = NULL;
	int nRet;

	nRet = maps_place_get_related_link(g_maps_place,&related);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_get_related_link", MapServiceGetError(nRet), maps_place_destroy(g_maps_place));
	CHECK_HANDLE_CLEANUP(related, "maps_place_get_related_link", maps_place_destroy(g_maps_place));
	
	nRet = maps_place_link_object_destroy(related);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_link_object_destroy", MapServiceGetError(nRet));
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose:  scenario to clone the place handle.
/**
* @testcase 			ITc_maps_place_clone_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to clone the place handle.
* @scenario				maps_place_clone
* @apicovered			maps_place_clone
* @passcase				if maps_place_clone passes
* @failcase				if maps_place_clone fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_clone_p(void)
{
	START_TEST_PLACE;

	int nRet;

	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}					
//& type: auto
//& purpose:  scenario to Retrieves all categories for a specified coordinates boundary.
/**
* @testcase 			ITc_maps_place_foreach_category_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to Retrieves all categories for a specified coordinates boundary.
* @scenario				maps_place_foreach_category
* @apicovered			maps_place_foreach_category
* @passcase				if maps_place_foreach_category passes
* @failcase				if maps_place_foreach_category fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_foreach_category_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	/*maps_place_category_h hPlaceCategory;
	
	nRet = maps_place_category_create(&hPlaceCategory);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_category_create", MapServiceGetError(nRet));
	CHECK_HANDLE(hPlaceCategory, "maps_place_category_create");*/

	g_nCheckCb = false;
	nRet = maps_place_foreach_category(g_maps_place, MapsPlaceCategoriesCb, NULL);
	PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_foreach_category", MapServiceGetError(nRet), maps_place_destroy(g_maps_place));
	
   // RUN_POLLING_LOOP;
	
	if(g_nCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] MapsPlaceCategoriesCb not invoked \\n", __LINE__, API_NAMESPACE);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
  
	return 0;	
}
/** @} */
/** @} */
