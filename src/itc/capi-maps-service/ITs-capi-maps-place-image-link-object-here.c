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
static maps_place_image_h g_place_image = NULL;

static bool MapsPlaceImagesCb(int index, int total, maps_place_image_h image, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside MapsPlaceImagesCb callback\\n", __LINE__, API_NAMESPACE);
    g_nCheckCb = true;
	if(g_nClone == 1)
	{
		g_nCheckRet = maps_place_image_clone(image, &g_place_image);
	}
	return true;
}
/**
 * @function 		ITs_maps_place_image_linkobj_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_place_image_linkobj_startup(void)
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
 * @function 		ITs_maps_place_image_linkobj_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_maps_place_image_linkobj_cleanup(void)
{
	return;
}
//& type: auto
//& purpose:  scenario to retrieve all place images.
/**
* @testcase 			ITc_maps_place_foreach_image_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to retrieve all place images
* @scenario				maps_place_foreach_image
* @apicovered			maps_place_foreach_image
* @passcase				if maps_place_foreach_image passes
* @failcase				if maps_place_foreach_image fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_foreach_image_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	g_nCheckCb = 0;
	g_nClone = 0;
	nRet = maps_place_foreach_image(g_maps_place, MapsPlaceImagesCb, NULL);
	if(!(nRet == MAPS_ERROR_NONE || nRet == MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_image", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceImagesCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}	
	   
//& type: auto
//& purpose:  scenario to clone and destroy the place image handle.
/**
* @testcase 			ITc_maps_place_image_clone_destroy_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to clone and destroy the place image handle.
* @scenario				maps_place_image_clone, maps_place_image_destroy
* @apicovered			maps_place_image_clone, maps_place_image_destroy
* @passcase				if maps_place_image_clone and maps_place_image_destroy passes
* @failcase				if maps_place_image_clone and maps_place_image_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_image_clone_destroy_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	
	g_nClone = 1;
	nRet = maps_place_foreach_image(g_maps_place, MapsPlaceImagesCb, NULL);
	if(!(nRet == MAPS_ERROR_NONE || nRet == MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_image", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceImagesCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_image_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_image, "maps_place_image_clone",maps_place_destroy(g_maps_place));
		nRet = maps_place_image_destroy(g_place_image);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_image_destroy", MapServiceGetError(nRet),maps_place_destroy(g_maps_place));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose:  scenario to get id of the place image handle.
/**
* @testcase 			ITc_maps_place_image_get_ids_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get id of the place image handle.
* @scenario				maps_place_image_get_id
* @apicovered			maps_place_image_get_id
* @passcase				if maps_place_image_get_id passes
* @failcase				if maps_place_image_get_id fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_image_get_ids_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	char *id = NULL;
	
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_image(g_maps_place, MapsPlaceImagesCb, NULL);
	if(!(nRet == MAPS_ERROR_NONE || nRet == MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_image", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceImagesCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_image_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_image, "maps_place_image_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_image_get_id(g_place_image, &id);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_image_get_id", MapServiceGetError(nRet),maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(id,"maps_place_image_get_id",maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		free(id);
		nRet = maps_place_image_destroy(g_place_image);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_image_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get media of the place image handle.
/**
* @testcase 			ITc_maps_place_image_get_media_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get media of the place image handle.
* @scenario				maps_place_image_get_media
* @apicovered			maps_place_image_get_media
* @passcase				if maps_place_image_get_media passes
* @failcase				if maps_place_image_get_media fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_image_get_media_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	maps_place_media_h media = NULL;
	
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_image(g_maps_place, MapsPlaceImagesCb, NULL);
	if(!(nRet == MAPS_ERROR_NONE || nRet == MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_image", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceImagesCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_image_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_image, "maps_place_image_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_image_get_media(g_place_image, &media);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_image_get_media", MapServiceGetError(nRet),maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(media,"maps_place_image_get_media",maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		nRet = maps_place_media_destroy(media);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_media_destroy", MapServiceGetError(nRet));
		nRet = maps_place_image_destroy(g_place_image);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_image_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get url of the place image handle.
/**
* @testcase 			ITc_maps_place_image_get_url_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get url of the place image handle.
* @scenario				maps_place_image_get_url
* @apicovered			maps_place_image_get_url
* @passcase				if maps_place_image_get_url passes
* @failcase				if maps_place_image_get_url fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_image_get_url_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	char *url = NULL;
	
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_image(g_maps_place, MapsPlaceImagesCb, NULL);
	if(!(nRet == MAPS_ERROR_NONE || nRet == MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_image", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceImagesCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_image_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_image, "maps_place_image_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_image_get_url(g_place_image, &url);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_image_get_url", MapServiceGetError(nRet),maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(url,"maps_place_image_get_url",maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		free(url);
		nRet = maps_place_image_destroy(g_place_image);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_image_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get user link of the place image handle.
/**
* @testcase 			ITc_maps_place_image_get_user_link_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get user link of the place image handle.
* @scenario				maps_place_image_get_user_link
* @apicovered			maps_place_image_get_user_link
* @passcase				if maps_place_image_get_user_link passes
* @failcase				if maps_place_image_get_user_link fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_image_get_user_link_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	maps_place_link_object_h user = NULL;

	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_image(g_maps_place, MapsPlaceImagesCb, NULL);
	if(!(nRet == MAPS_ERROR_NONE || nRet == MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_image", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceImagesCb not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_image_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_image, "maps_place_image_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_image_get_user_link(g_place_image, &user);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_image_get_user_link", MapServiceGetError(nRet),maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(user,"maps_place_image_get_user_link",maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		nRet = maps_place_link_object_destroy(user);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_link_object_destroy", MapServiceGetError(nRet));
		nRet = maps_place_image_destroy(g_place_image);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_image_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to clone and destroy the place link object handle.
/**
* @testcase 			ITc_maps_place_link_object_clone_destroy_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to clone and destroy the place link object handle.
* @scenario				maps_place_link_object_clone and maps_place_link_object_destroy
* @apicovered			maps_place_link_object_clone and maps_place_link_object_destroy
* @passcase				if maps_place_link_object_clone, maps_place_link_object_destroy passes
* @failcase				if maps_place_link_object_clone, maps_place_link_object_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_link_object_clone_destroy_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	
	maps_place_link_object_h user = NULL;
	maps_place_link_object_h hUser = NULL;
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_image(g_maps_place, MapsPlaceImagesCb, NULL);
	if(!(nRet == MAPS_ERROR_NONE || nRet == MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_image", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceImagesCb1 not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_image_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_image, "maps_place_image_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_image_get_user_link(g_place_image, &user);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_image_get_user_link", MapServiceGetError(nRet),maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(user, "maps_place_image_get_user_link",maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		nRet = maps_place_link_object_clone(user, &hUser);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_link_object_clone", MapServiceGetError(nRet),maps_place_link_object_destroy(user);maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(hUser, "maps_place_link_object_clone",maps_place_link_object_destroy(user);maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		nRet = maps_place_link_object_destroy(hUser);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_link_object_destroy", MapServiceGetError(nRet),maps_place_link_object_destroy(user);maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		nRet = maps_place_link_object_destroy(user);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_link_object_destroy", MapServiceGetError(nRet));
		nRet = maps_place_image_destroy(g_place_image);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_image_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get the place link object id.
/**
* @testcase 			ITc_maps_place_link_object_get_id_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the place link object id.
* @scenario				maps_place_link_object_get_id
* @apicovered			maps_place_link_object_get_id
* @passcase				if maps_place_link_object_get_id passes
* @failcase				if maps_place_link_object_get_id fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_link_object_get_id_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	maps_place_link_object_h user = NULL;
	char *id = NULL;
	
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_image(g_maps_place, MapsPlaceImagesCb, NULL);
	if(!(nRet == MAPS_ERROR_NONE || nRet == MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_image", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceImagesCb1 not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_image_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_image, "maps_place_image_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_image_get_user_link(g_place_image, &user);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_image_get_user_link", MapServiceGetError(nRet),maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(user, "maps_place_image_get_user_link",maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		nRet = maps_place_link_object_get_id(user, &id);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_link_object_get_id", MapServiceGetError(nRet),maps_place_link_object_destroy(user);maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(id,"maps_place_link_object_get_id",maps_place_link_object_destroy(user);maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		free(id);
		nRet = maps_place_link_object_destroy(user);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_link_object_destroy", MapServiceGetError(nRet));
		nRet = maps_place_image_destroy(g_place_image);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_image_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
//& type: auto
//& purpose:  scenario to get the place link object name.
/**
* @testcase 			ITc_maps_place_link_object_get_name_p
* @author            	SRID(manu.tiwari)
* @reviewer         	SRID(amritanshu.p1)
* @type 				auto
* @since_tizen 			@if MOBILE 2.4 @elseif WEARABLE 2.3.2 @endif
* @description			scenario to get the place link object name.
* @scenario				maps_place_link_object_get_name
* @apicovered			maps_place_link_object_get_name
* @passcase				if maps_place_link_object_get_name passes
* @failcase				if maps_place_link_object_get_name fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_maps_place_link_object_get_name_p(void)
{
	START_TEST_PLACE;
	
	int nRet;
	maps_place_link_object_h user = NULL;
	char *name = NULL;
	
	g_nCheckCb = 0;
	g_nCheckRet = 0;
	g_nClone = 1;
	nRet = maps_place_foreach_image(g_maps_place, MapsPlaceImagesCb, NULL);
	if(!(nRet == MAPS_ERROR_NONE || nRet == MAPS_ERROR_NOT_FOUND))
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "maps_place_foreach_image", MapServiceGetError(nRet), nRet);
		maps_place_destroy(g_maps_place);
		return 1;
	}
	//RUN_POLLING_LOOP;
	if(nRet == MAPS_ERROR_NONE)
	{
		if(g_nCheckCb != true)
		{
			FPRINTF("[Line : %d][%s] MapsPlaceImagesCb1 not invoked \\n", __LINE__, API_NAMESPACE);
			maps_place_destroy(g_maps_place);
			return 1;
		}
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, g_nCheckRet, "maps_place_image_clone", MapServiceGetError(g_nCheckRet),maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(g_place_image, "maps_place_image_clone",maps_place_destroy(g_maps_place));

		nRet = maps_place_image_get_user_link(g_place_image, &user);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_image_get_user_link", MapServiceGetError(nRet),maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(user, "maps_place_image_get_user_link",maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		nRet = maps_place_link_object_get_name(user, &name);
		PRINT_RESULT_CLEANUP(MAPS_ERROR_NONE, nRet, "maps_place_link_object_get_name", MapServiceGetError(nRet),maps_place_link_object_destroy(user);maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));
		CHECK_HANDLE_CLEANUP(name,"maps_place_link_object_get_name",maps_place_link_object_destroy(user);maps_place_image_destroy(g_place_image);maps_place_destroy(g_maps_place));

		free(name);
		nRet = maps_place_link_object_destroy(user);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_link_object_destroy", MapServiceGetError(nRet));
		nRet = maps_place_image_destroy(g_place_image);
		PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_image_destroy", MapServiceGetError(nRet));
	}
	nRet = maps_place_destroy(g_maps_place);
	PRINT_RESULT_NORETURN(MAPS_ERROR_NONE, nRet, "maps_place_destroy", MapServiceGetError(nRet));

	return 0;
}
/** @} */
/** @} */