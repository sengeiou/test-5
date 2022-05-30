//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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

#include "ITs-capi-ui-sticker-common.h"

/** @addtogroup itc-capi-ui-sticker
 *  @ingroup itc
 *  @{
 */

//& set: capi-ui-sticker

/**
 * @function		StickerConsumerGroupImageListForeachCallback
 * @description  A sticker consumer callback for foreach all group image
 */
static void StickerConsumerGroupImageListForeachCallback(const char *group, sticker_data_uri_type_e type, const char *uri, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback  StickerConsumerGroupImageListForeachCallback\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
}

/**
 * @function		StickerDataConsumerForeachCallback
 * @description  A sticker consumer callback for foreach all
 */
static void StickerDataConsumerForeachCallback(sticker_data_h data_handle, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback  StickerDataConsumerForeachCallback\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
}

/**
 * @function		StickerConsumerGroupListCallback
 * @description A sticker consumer callback for group list
 */
static void StickerConsumerGroupListCallback(const char *group, void *user_data)
{
	g_bCallbackHit = true;
	FPRINTF("[Line : %d][%s] Inside callback  StickerConsumerGroupListCallback\\n", __LINE__, API_NAMESPACE);
}


/**
 * @function		StickerConsumerKeywordListCallback
 * @description A sticker consumer callback for keyword list
 */
static void StickerConsumerKeywordListCallback(const char *keyword, void *user_data)
{
	g_bCallbackHit = true;
	FPRINTF("[Line : %d][%s] Inside callback  StickerConsumerKeywordListCallback\\n", __LINE__, API_NAMESPACE);
}

/**
 * @function		StickerConsumerSetEventCallback
 * @description		A sticker consumer callback for set event
 */
static void StickerConsumerSetEventCallback(sticker_consumer_event_type_e event_type, sticker_data_h data_handle, void *user_data)
{
	g_bCallbackHit = true;
	FPRINTF("[Line : %d][%s] Inside callback  StickerConsumerSetEventCallback\\n", __LINE__, API_NAMESPACE);
}

/**
 * @function 		ITs_capi_ui_sticker_consumer_startup
 * @description	 	Called before each test, set the service boolean true
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_ui_sticker_consumer_startup(void)
{
	int nRet =-1;
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0)
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_capi_ui_sticker_consumer_startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_bIsFeatureMismatched = false;
	g_bStickerCreation = false;
	char *pszGroup = "tizen", *pszUri="www.valid.com/test/test.png";
	g_bFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(FEATURE_STICKER, API_NAMESPACE);

	nRet = sticker_consumer_create(&g_hStickerConsumerHandle);
	if(!g_bFeatureIsSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] sticker_consumer_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] sticker_consumer_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] sticker_consumer_create is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] sticker_consumer_create is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_consumer_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d]sticker_consumer_create failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bStickerCreation = false;
	}
	else
	{
		g_bStickerCreation = true;
	}
	nRet = sticker_provider_create(&g_hStickerProviderHandle);
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_provider_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_data_create(&g_hStickerDataHandle);
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_data_set_uri(g_hStickerDataHandle, STICKER_DATA_URI_WEB_RESOURCE, "www.samsung.com/ITC/consumer");
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_set_uri failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_data_add_keyword(g_hStickerDataHandle, "cute");
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_add_keyword failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_data_set_group_name(g_hStickerDataHandle, "tizen");
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_set_group_name failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_data_set_description(g_hStickerDataHandle, "TCT Test");
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_set_description failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_data_set_display_type(g_hStickerDataHandle, STICKER_DATA_DISP_WALLPAPER);
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_set_display_type failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_provider_insert_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_provider_insert_data failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_provider_set_group_image(g_hStickerProviderHandle, pszGroup, STICKER_DATA_URI_WEB_RESOURCE, pszUri);
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_provider_set_group_image failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	return;

}

/**
 * @function 		ITs_capi_ui_sticker_consumer_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_ui_sticker_consumer_cleanup(void)
{
	int nRet = -1;
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_capi_ui_sticker_consumer_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	if (g_hStickerConsumerHandle) {
		nRet = sticker_consumer_destroy(g_hStickerConsumerHandle);
		if(nRet !=0)
		{
			FPRINTF("sticker_consumer_destroy failed\\n");
			dlog_print(DLOG_ERROR, "NativeTCT", "sticker_consumer_destroy failed");
		}
		g_hStickerConsumerHandle = NULL;
	}
	if (g_hStickerProviderHandle) {
		nRet = sticker_provider_delete_data_by_uri (g_hStickerProviderHandle, "www.samsung.com/ITC/consumer");
		if(nRet !=0)
		{
			FPRINTF("sticker_provider_delete_data_by_uri failed\\n");
			dlog_print(DLOG_ERROR, "NativeTCT", "sticker_provider_delete_data_by_uri failed");
		}

		nRet = sticker_provider_destroy (g_hStickerProviderHandle);
		if(nRet !=0)
		{
			FPRINTF("sticker_provider_destroy failed\\n");
			dlog_print(DLOG_ERROR, "NativeTCT", "sticker_provider_destroy failed");
		}
		g_hStickerProviderHandle = NULL;
	}
	if (g_hStickerDataHandle) {
		nRet = sticker_data_destroy (g_hStickerDataHandle);
		if(nRet !=0)
		{
			FPRINTF("sticker_data_destroy failed\\n");
			dlog_print(DLOG_ERROR, "NativeTCT", "sticker_data_destroy failed");
		}
		g_hStickerDataHandle = NULL;

	}
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_create_destroy_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Create and Destroy sticker consumer handle
 * @scenario			Create and Destroy sticker consumer handle
 * @apicovered			sticker_consumer_create,sticker_consumer_destroy
 * @passcase			When sticker_consumer_create,sticker_consumer_destroy and Precondition APi's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Create and Destroy sticker consumer handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_consumer_create_destroy_p(void)
{
	START_TEST;
	int nRet = -1;
	sticker_consumer_h hStickerConsumerHandle = NULL;

	nRet = sticker_consumer_create(&hStickerConsumerHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_create", StickerGetError(nRet));
	CHECK_HANDLE(hStickerConsumerHandle, "sticker_consumer_create");

	nRet = sticker_consumer_destroy(hStickerConsumerHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_destroy", StickerGetError(nRet));

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_data_foreach_all_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Foreach for all sticker data consumer handle
 * @scenario			Foreach for all sticker data consumer handle
 * @apicovered			sticker_provider_data_foreach_all
 * @passcase			When sticker_consumer_data_foreach_all and Precondition APi's are  successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Foreach for all sticker data consumer handle
int ITc_capi_ui_sticker_data_sticker_consumer_data_foreach_all_p(void)
{
	START_TEST;
	int nRet = -1;
	int nResult = -1;
	g_bCallbackHit = false;

	nRet = sticker_consumer_data_foreach_all(g_hStickerConsumerHandle, 0, 1000, &nResult, StickerDataConsumerForeachCallback, NULL);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_data_foreach_all", StickerGetError(nRet));

	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	if(nResult < 0)
	{
		FPRINTF("[%s:%d] nResult value is not valid\\n", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_data_foreach_by_keyword_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Foreach for all sticker data consumer handle by keyword
 * @scenario			Foreach for all sticker data consumer handle by keyword
 * @apicovered			sticker_consumer_data_foreach_by_keyword
 * @passcase			When sticker_consumer_data_foreach_by_keyword and Precondition APi's are  successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Foreach for all sticker data consumer handle by keyword
int ITc_capi_ui_sticker_data_sticker_consumer_data_foreach_by_keyword_p(void)
{
	START_TEST;
	int nRet = -1;
	int nResult = -1;
	g_bCallbackHit = false;

	nRet = sticker_consumer_data_foreach_by_keyword(g_hStickerConsumerHandle, 0, 1000, &nResult, "cute", StickerDataConsumerForeachCallback, NULL);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_data_foreach_by_keyword", StickerGetError(nRet));

	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	if(nResult < 0)
	{
		FPRINTF("[%s:%d] nResult value is not valid\\n", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_data_foreach_by_group_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Foreach for all sticker data consumer handle by group
 * @scenario			Foreach for all sticker data consumer handle by group
 * @apicovered			sticker_consumer_data_foreach_by_group
 * @passcase			When sticker_consumer_data_foreach_by_group and Precondition APi's are  successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Foreach for all sticker data consumer handle by group
int ITc_capi_ui_sticker_data_sticker_consumer_data_foreach_by_group_p(void)
{
	START_TEST;
	int nRet = -1;
	int nResult = -1;
	g_bCallbackHit = false;

	nRet = sticker_consumer_data_foreach_by_group(g_hStickerConsumerHandle, 0, 1000, &nResult, "tizen", StickerDataConsumerForeachCallback, NULL);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_data_foreach_by_group", StickerGetError(nRet));

	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	if(nResult < 0)
	{
		FPRINTF("[%s:%d] nResult value is not valid\\n", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_data_foreach_by_type_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Foreach for all sticker data consumer handle by type
 * @scenario			Foreach for all sticker data consumer handle by type
 * @apicovered			sticker_consumer_data_foreach_by_type
 * @passcase			When sticker_consumer_data_foreach_by_type and Precondition APi's are  successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Foreach for all sticker data consumer handle by type
int ITc_capi_ui_sticker_data_sticker_consumer_data_foreach_by_type_p(void)
{
	START_TEST;
	int nRet = -1;
	int nResult = -1;
	g_bCallbackHit = false;

	nRet = sticker_consumer_data_foreach_by_type(g_hStickerConsumerHandle, 0, 1000, &nResult, STICKER_DATA_URI_WEB_RESOURCE, StickerDataConsumerForeachCallback, NULL);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_data_foreach_by_type", StickerGetError(nRet));

	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	if(nResult < 0)
	{
		FPRINTF("[%s:%d] nResult value is not valid\\n", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_group_list_foreach_all_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Foreach for all sticker data consumer for a group list
 * @scenario			Foreach for all sticker data consumer for a group list
 * @apicovered			sticker_consumer_group_list_foreach_all
 * @passcase			When sticker_consumer_group_list_foreach_all and Precondition APi's are  successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Foreach for all sticker data consumer for a group list
int ITc_capi_ui_sticker_data_sticker_consumer_group_list_foreach_all_p(void)
{
	START_TEST;
	int nRet = -1;
	g_bCallbackHit = false;

	nRet = sticker_consumer_group_list_foreach_all(g_hStickerConsumerHandle, StickerConsumerGroupListCallback, NULL);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_group_list_foreach_all", StickerGetError(nRet));

	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	return 0;
}


/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_keyword_list_foreach_all_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Foreach for all sticker data consumer for a keyword list
 * @scenario			Foreach for all sticker data consumer for a keyword list
 * @apicovered			sticker_consumer_keyword_list_foreach_all
 * @passcase			When sticker_consumer_keyword_list_foreach_all and Precondition APi's are  successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Foreach for all sticker data consumer for a keyword list
int ITc_capi_ui_sticker_data_sticker_consumer_keyword_list_foreach_all_p(void)
{
	START_TEST;
	int nRet = -1;
	g_bCallbackHit = false;

	nRet = sticker_consumer_keyword_list_foreach_all(g_hStickerConsumerHandle, StickerConsumerKeywordListCallback, NULL);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_keyword_list_foreach_all", StickerGetError(nRet));

	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_data_foreach_by_display_type_p
 * @since_tizen			5.5
 * @author			SRID(priya.kohli)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Retrieves all sticker data in the sticker database using display type
 * @scenario			Retrieves all sticker data in the sticker database using display type
 * @apicovered			sticker_consumer_data_foreach_by_display_type
 * @passcase			When sticker_consumer_data_foreach_by_display_type and Precondition APi's are  successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to retrieve all sticker data in the sticker database using display type
int ITc_capi_ui_sticker_data_sticker_consumer_data_foreach_by_display_type_p(void)
{
	START_TEST;
	int nRet = -1;
	int nResult = -1;
	int nOffset  = 0;
	int nCnt = 1000;
	void *userData = NULL;

	g_bCallbackHit = false;

	nRet = sticker_consumer_data_foreach_by_display_type(g_hStickerConsumerHandle, nOffset, nCnt, &nResult, STICKER_DATA_DISP_WALLPAPER, StickerDataConsumerForeachCallback, userData);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_data_foreach_by_display_type", StickerGetError(nRet));
	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));
	if(nResult < 0)
	{
		FPRINTF("[%s:%d] nResult value is not valid\\n", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_group_list_foreach_by_display_type_p
 * @since_tizen			5.5
 * @author			SRID(priya.kohli)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Retrieves all group names assigned to stickers with a matching display @a type.
 * @scenario			Retrieves all group names assigned to stickers with a matching display @a type.
 * @apicovered			sticker_consumer_group_list_foreach_by_display_type
 * @passcase			When sticker_consumer_group_list_foreach_by_display_type and Precondition APi's are  successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to retrieve all group names assigned to stickers with a matching display @a type.
int ITc_capi_ui_sticker_data_sticker_consumer_group_list_foreach_by_display_type_p(void)
{
	START_TEST;
	int nRet = -1;
	void *userData = NULL;

	g_bCallbackHit = false;

	nRet = sticker_consumer_group_list_foreach_by_display_type(g_hStickerConsumerHandle, STICKER_DATA_DISP_WALLPAPER, StickerConsumerGroupListCallback, userData);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_group_list_foreach_by_display_type", StickerGetError(nRet));
	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_add_get_recent_data_p
 * @since_tizen			5.5
 * @author			SRID(priya.kohli)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Adds entry to recently used stickers list and gets the entry.
 * @scenario			Adds entry to recently used stickers list and gets the entry.
 * @apicovered			sticker_consumer_add_recent_data,sticker_consumer_get_recent_data_list
 * @passcase			When sticker_consumer_add_recent_data,sticker_consumer_get_recent_data_list and Precondition APi's are  successful.
 * @failcase			If target APIs fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to add entry to recently used stickers list and get the entry.
int ITc_capi_ui_sticker_data_sticker_consumer_add_get_recent_data_p(void)
{
	START_TEST;
	int nRet = -1;
	int nResult = -1;
	void *userData = NULL;
	int nCount = 1;
	g_bCallbackHit = false;

	nRet = sticker_consumer_add_recent_data(g_hStickerConsumerHandle, g_hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_add_recent_data", StickerGetError(nRet));

	nRet = sticker_consumer_get_recent_data_list(g_hStickerConsumerHandle, nCount, &nResult, StickerDataConsumerForeachCallback, userData);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_get_recent_data_list", StickerGetError(nRet));

	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));
	if(nResult < 0)
	{
		FPRINTF("[%s:%d] nResult value is not valid\\n", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_set_unset_event_cb_p
 * @since_tizen			5.5
 * @author			SRID(priya.kohli)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Registers and unregisters a callback function to be invoked when the stickers are inserted, deleted, or updated.
 * @scenario			Registers and unregisters a callback function to be invoked when the stickers are inserted, deleted, or updated.
 * @apicovered			sticker_consumer_set_event_cb, sticker_consumer_unset_event_cb
 * @passcase			When sticker_consumer_set_event_cb, sticker_consumer_unset_event_cb and Precondition APi's are  successful.
 * @failcase			If target APIs fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to register and unregister a callback function to be invoked when the stickers are inserted, deleted, or updated.
int ITc_capi_ui_sticker_data_sticker_consumer_set_unset_event_cb_p(void)
{
	START_TEST;
	int nRet = -1;
	void *userData = NULL;
	g_bCallbackHit = false;
	int nTimeoutId = 0;

	nRet = sticker_consumer_set_event_cb(g_hStickerConsumerHandle, StickerConsumerSetEventCallback, userData);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_set_event_cb", StickerGetError(nRet));

	RUN_POLLING_LOOP;
	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	nRet = sticker_consumer_unset_event_cb(g_hStickerConsumerHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_unset_event_cb", StickerGetError(nRet));

	 return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_consumer_group_image_list_foreach_all_p
 * @since_tizen			6.5
 * @author				SRID(nibha.sharma)
 * @reviewer			SRID(shobhit.v)
 * @type 				auto
 * @description			Retrieves images of all sticker groups.
 * @scenario			Retrieves images of all sticker groups.
 * @apicovered			sticker_consumer_group_image_list_foreach_all
 * @passcase			When sticker_consumer_group_image_list_foreach_all and Precondition APi's are  successful.
 * @failcase			If target APIs fails or callback is not hit or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to retrieves images of all sticker groups.
int ITc_capi_ui_sticker_data_sticker_consumer_group_image_list_foreach_all_p(void)
{
	START_TEST;

	int nRet = -1;
	g_bCallbackHit = false;

	nRet = sticker_consumer_group_image_list_foreach_all(g_hStickerConsumerHandle, StickerConsumerGroupImageListForeachCallback, NULL);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_consumer_group_image_list_foreach_all", StickerGetError(nRet));
	PRINT_RESULT(g_bCallbackHit, true, "StickerConsumerGroupImageListForeachCallback callback not hit,", "g_bCallbackHit");

	return 0;
}
