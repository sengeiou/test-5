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
static maps_place_review_h g_place_review = NULL;

static bool MapsPlaceReviewsCb(int index, int total, maps_place_review_h review, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsPlaceReviewsCb callback\\n", __LINE__, API_NAMESPACE); 
    g_nCheckCb = true;
	if(g_nClone == 1)
	{
		g_nCheckRet = maps_place_review_clone(review, &g_place_review);
	}
	
	return true;
}
/**
 * @function 		ITs_maps_place_review_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_place_review_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	MapsPlaceLocationHandleHelperHERE();
	
	return;
}
/**
 * @function 		ITs_maps_place_review_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_place_review_cleanup(void)
{
	return;
}

//& type: auto
//& purpose:  scenario to retrieve all reviews.
/**
* @testcase 			ITc_maps_place_foreach_review_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to retrieve all reviews
* @scenario				maps_place_foreach_review
* @apicovered			maps_place_foreach_review
* @passcase				if maps_place_foreach_review passes
* @failcase				if maps_place_foreach_review fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_foreach_review_p(void)
{
	START_TEST_PLACE;

	int nRet;
	g_nCheckCb = 0;
	g_nClone = 0;
	nRet = maps_place_foreach_review(g_maps_place, MapsPlaceReviewsCb, NULL);
	if((nRet != MAPS_ERROR_NONE)&&(nRet != MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_review", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceReviewsCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
	}
    nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));	

	return 0;
}  
//& type: auto
//& purpose:  scenario to clone and destroy the place review handle.
/**
* @testcase 			ITc_maps_place_review_clone_destroy_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to clone and destroy the place review handle.
* @scenario				maps_place_review_clone, maps_place_review_destroy
* @apicovered			maps_place_review_clone, maps_place_review_destroy
* @passcase				if maps_place_review_clone and maps_place_review_destroy passes
* @failcase				if maps_place_review_clone and maps_place_review_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_review_clone_destroy_p(void)
{
	START_TEST_PLACE;

	int nRet;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;

	nRet = maps_place_foreach_review(g_maps_place, MapsPlaceReviewsCb, NULL);
	if((nRet != MAPS_ERROR_NONE)&&(nRet != MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_review", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceReviewsCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}

		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_review_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_review, "maps_place_review_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_review_destroy(g_place_review);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_review_destroy", MapServiceGetError(nRet),maps_place_destroy(g_maps_place));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get the place review date.
/**
* @testcase 			ITc_maps_place_review_get_date_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the place review date.
* @scenario				maps_place_review_get_date
* @apicovered			maps_place_review_get_date
* @passcase				if maps_place_review_get_date passes
* @failcase				if maps_place_review_get_date fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_review_get_date_p(void)
{
	START_TEST_PLACE;

	char *date = NULL;
	int nRet;

	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_review(g_maps_place, MapsPlaceReviewsCb, NULL);
	if((nRet != MAPS_ERROR_NONE)&&(nRet != MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_review", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceReviewsCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_review_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_review, "maps_place_review_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_review_get_date(g_place_review, &date);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_review_get_date", MapServiceGetError(nRet),maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(date, "maps_place_review_get_date",maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));
		free(date);
		nRet = maps_place_review_destroy(g_place_review);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_review_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get the place review date.
/**
* @testcase 			ITc_maps_place_review_get_description_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the place review date.
* @scenario				maps_place_review_get_description
* @apicovered			maps_place_review_get_description
* @passcase				if maps_place_review_get_description passes
* @failcase				if maps_place_review_get_description fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_review_get_description_p(void)
{
	START_TEST_PLACE;

	char *description = NULL;
	int nRet;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;

	nRet = maps_place_foreach_review(g_maps_place, MapsPlaceReviewsCb, NULL);
	if((nRet != MAPS_ERROR_NONE)&&(nRet != MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_review", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceReviewsCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}

		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_review_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_review, "maps_place_review_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_review_get_description(g_place_review, &description);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_review_get_description", MapServiceGetError(nRet),maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(description, "maps_place_review_get_description",maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));

		free(description);
		nRet = maps_place_review_destroy(g_place_review);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_review_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get the place review language.
/**
* @testcase 			ITc_maps_place_review_get_language_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the place review language.
* @scenario				maps_place_review_get_language
* @apicovered			maps_place_review_get_language
* @passcase				if maps_place_review_get_language passes
* @failcase				if maps_place_review_get_language fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_review_get_language_p(void)
{
	START_TEST_PLACE;

	char *language = NULL;
	int nRet;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_review(g_maps_place, MapsPlaceReviewsCb, NULL);
	if((nRet != MAPS_ERROR_NONE)&&(nRet != MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_review", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceReviewsCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}

		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_review_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_review, "maps_place_review_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_review_get_language(g_place_review, &language);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_review_get_language", MapServiceGetError(nRet),maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(language, "maps_place_review_get_language",maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));

		free(language);
		nRet = maps_place_review_destroy(g_place_review);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_review_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get the place review media..
/**
* @testcase 			ITc_maps_place_review_get_media_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the place review media..
* @scenario				maps_place_review_get_media
* @apicovered			maps_place_review_get_media
* @passcase				if maps_place_review_get_media passes
* @failcase				if maps_place_review_get_media fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_review_get_media_p(void)
{
	START_TEST_PLACE;

	maps_place_media_h media = NULL;
	int nRet;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_review(g_maps_place, MapsPlaceReviewsCb, NULL);
	if((nRet != MAPS_ERROR_NONE)&&(nRet != MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_review", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceReviewsCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_review_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_review, "maps_place_review_clone",maps_place_destroy(g_maps_place));
		nRet = maps_place_review_get_media(g_place_review, &media);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_review_get_media", MapServiceGetError(nRet),maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(media, "maps_place_review_get_media",maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));
		nRet = maps_place_media_destroy(media);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_media_destroy", MapServiceGetError(nRet));
		nRet = maps_place_review_destroy(g_place_review);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_review_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get the place review rating.
/**
* @testcase 			ITc_maps_place_review_get_rating_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the place review rating.
* @scenario				maps_place_review_get_rating
* @apicovered			maps_place_review_get_rating
* @passcase				if maps_place_review_get_rating passes
* @failcase				if maps_place_review_get_rating fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_review_get_rating_p(void)
{
	START_TEST_PLACE;

	double rating = 0;
	int nRet;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_review(g_maps_place, MapsPlaceReviewsCb, NULL);
	if((nRet != MAPS_ERROR_NONE)&&(nRet != MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_review", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceReviewsCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_review_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_review, "maps_place_review_clone",maps_place_destroy(g_maps_place));
		nRet = maps_place_review_get_rating(g_place_review, &rating);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_review_get_rating", MapServiceGetError(nRet),maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));

		if(rating < 0)
		{
			FPRINTF("[Line : %d][%s] maps_place_review_get_rating failed with invalid rating \\n", __LINE__, API_NAMESPACE);
			maps_place_review_destroy(g_place_review);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		nRet = maps_place_review_destroy(g_place_review);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_review_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get the place review title.
/**
* @testcase 			ITc_maps_place_review_get_title_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description		    scenario to get the place review title
* @scenario				maps_place_review_get_title
* @apicovered			maps_place_review_get_title
* @passcase				if maps_place_review_get_title passes
* @failcase				if maps_place_review_get_title fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_review_get_title_p(void)
{
	START_TEST_PLACE;
	
	char *title = NULL;
	int nRet;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_review(g_maps_place, MapsPlaceReviewsCb, NULL);
	if((nRet != MAPS_ERROR_NONE)&&(nRet != MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_review", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceReviewsCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_review_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_review, "maps_place_review_clone",maps_place_destroy(g_maps_place));
		nRet = maps_place_review_get_title(g_place_review, &title);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_review_get_title", MapServiceGetError(nRet),maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(title, "maps_place_review_get_title",maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));
		free(title);
		nRet = maps_place_review_destroy(g_place_review);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_review_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get the place review user link.
/**
* @testcase 			ITc_maps_place_review_get_user_link_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description		    scenario to get the place review user link.
* @scenario				maps_place_review_get_user_link
* @apicovered			maps_place_review_get_user_link
* @passcase				if maps_place_review_get_user_link passes
* @failcase				if maps_place_review_get_user_link fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_review_get_user_link_p(void)
{
	START_TEST_PLACE;
	
	maps_place_link_object_h user = NULL;
	int nRet;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	
	nRet = maps_place_foreach_review(g_maps_place, MapsPlaceReviewsCb, NULL);
	if((nRet != MAPS_ERROR_NONE)&&(nRet != MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_review", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceReviewsCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_review_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_review, "maps_place_review_clone",maps_place_destroy(g_maps_place));
		nRet = maps_place_review_get_user_link(g_place_review, &user);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_review_get_user_link", MapServiceGetError(nRet),maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(user, "maps_place_review_get_user_link",maps_place_review_destroy(g_place_review);maps_place_destroy(g_maps_place));
		nRet = maps_place_link_object_destroy(user);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_link_object_destroy", MapServiceGetError(nRet));
		nRet = maps_place_review_destroy(g_place_review);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_review_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}
/** @} */
/** @} */
