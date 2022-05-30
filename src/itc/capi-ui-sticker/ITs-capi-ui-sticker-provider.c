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
 * @function		StickerDataProviderForeachCallback
 * @description  A sticker provider callback for iforeach all
 */
static void StickerDataProviderForeachCallback(sticker_data_h data_handle, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback  StickerDataProviderForeachCallback\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
}

/**
 * @function		StickerProviderInsertFinishedCallback
 * @description A sticker provider callback for insert finished
 */
static void StickerProviderInsertFinishedCallback(sticker_error_e error, void *user_data)
{
	g_bCallbackHit = true;
	FPRINTF("[Line : %d][%s] Inside callback  StickerProviderInsertFinishedCallback\\n", __LINE__, API_NAMESPACE);
	QUIT_GMAIN_LOOP;
}

/**
 * @function 		ITs_capi_ui_sticker_provider_startup
 * @description	 	Called before each test, set the service boolean true
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_ui_sticker_provider_startup(void)
{
	int nRet =-1;
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0)
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_capi_ui_sticker_provider_startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_bIsFeatureMismatched = false;
	g_bStickerCreation = false;
	g_bFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(FEATURE_STICKER, API_NAMESPACE);

	nRet = sticker_provider_create(&g_hStickerProviderHandle);
	if(!g_bFeatureIsSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] sticker_provider_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] sticker_provider_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] sticker_provider_create is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] sticker_provider_create is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_provider_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d]sticker_provider_create failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bStickerCreation = false;
	}
	else
	{
		g_bStickerCreation = true;
	}
	nRet = sticker_data_create(&g_hStickerDataHandle);
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_date_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_data_set_uri(g_hStickerDataHandle, STICKER_DATA_URI_WEB_RESOURCE, "www.samsung.com/ITC/provider");
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_set_uri failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_data_add_keyword(g_hStickerDataHandle, "smile");
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_add_keyword failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bStickerCreation = false;
	}
	nRet = sticker_data_add_keyword(g_hStickerDataHandle, "face");
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_add_keyword failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
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
	nRet = sticker_data_set_thumbnail(g_hStickerDataHandle, "/res/test.png");
	if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_set_thumbnail failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
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
	return;

}

/**
 * @function 		ITs_capi_ui_sticker_provider_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_ui_sticker_provider_cleanup(void)
{
	int nRet = -1;
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_capi_ui_sticker_provider_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	if (g_hStickerProviderHandle) {
		nRet = sticker_provider_delete_data_by_uri (g_hStickerProviderHandle, "www.samsung.com/ITC/provider");
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
 * @testcase 			ITc_capi_ui_sticker_data_sticker_provider_create_destroy_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Create and Destroy sticker provider handle
 * @scenario			Create and Destroy sticker provider handle
 * @apicovered			sticker_provider_create,sticker_provider_destroy
 * @passcase			When sticker_provider_create,sticker_provider_destroy and Precondition API's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition		None
 */
//& purpose: API to Check for Create and Destroy sticker provider handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_provider_create_destroy_p(void)
{
	START_TEST;
	int nRet = -1;
	sticker_provider_h hStickerProviderHandle = NULL;

	nRet = sticker_provider_create(&hStickerProviderHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_create", StickerGetError(nRet));
	CHECK_HANDLE(hStickerProviderHandle, "sticker_provider_create");

	nRet = sticker_provider_destroy(hStickerProviderHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_destroy", StickerGetError(nRet));

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_provider_insert_data_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Insert Data for sticker provider handle
 * @scenario			Insert Data for sticker provider handle
 * @apicovered			sticker_provider_insert_data
 * @passcase			When sticker_provider_insert_data and Precondition API's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Insert Data for sticker provider handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_provider_insert_data_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = sticker_provider_insert_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_insert_data", StickerGetError(nRet));

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_provider_insert_data_by_json_file_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Insert Data by json file for sticker provider handle
 * @scenario			Insert Data by json file for sticker provider handle
 * @apicovered			sticker_provider_insert_data_by_json_file
 * @passcase			When sticker_provider_insert_data_by_json_file and Precondition API's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Insert Data by json file for sticker provider handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_provider_insert_data_by_json_file_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszJsonPath = "/res/test.json";
	g_bCallbackHit = false;
	int nTimeoutId = 0;

	nRet = sticker_provider_insert_data_by_json_file(g_hStickerProviderHandle, pszJsonPath, StickerProviderInsertFinishedCallback, NULL);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_insert_data_by_json_file", StickerGetError(nRet));

	RUN_POLLING_LOOP;
	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_provider_update_data_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Update Data for sticker provider handle
 * @scenario			Update Data for sticker provider handle
 * @apicovered			sticker_provider_update_data
 * @passcase			When sticker_provider_update_data and Precondition API's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Update Data for sticker provider handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_provider_update_data_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = sticker_provider_insert_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_insert_data", StickerGetError(nRet));

	nRet = sticker_data_set_group_name( g_hStickerDataHandle, "Samsung");
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_set_group_name", StickerGetError(nRet));

	nRet = sticker_provider_update_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_update_data", StickerGetError(nRet));

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_provider_delete_data_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Delete Data for sticker provider handle
 * @scenario			Delete Data for sticker provider handle
 * @apicovered			sticker_provider_delete_data
 * @passcase			When sticker_provider_delete_data and Precondition API's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for delete Data for sticker provider handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_provider_delete_data_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = sticker_provider_insert_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_insert_data", StickerGetError(nRet));

	nRet = sticker_provider_delete_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_delete_data", StickerGetError(nRet));

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_provider_get_sticker_count_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Get Sticker count from sticker data provider handle
 * @scenario			Get Sticker count from sticker data provider handle
 * @apicovered			sticker_provider_get_sticker_count
 * @passcase			When sticker_provider_get_sticker_count and Precondition API's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Get Sticker count from sticker data provider handle
int ITc_capi_ui_sticker_data_sticker_provider_get_sticker_count_p(void)
{
	START_TEST;
	int nRet = -1;
	int nStickerCount = -1;

	nRet = sticker_provider_get_sticker_count(g_hStickerProviderHandle, &nStickerCount);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_get_sticker_count", StickerGetError(nRet));

	if(nStickerCount < 0)
	{
		FPRINTF("[%s:%d] nStickerCount value is not valid\\n", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_provider_data_foreach_all_p
 * @since_tizen			5.5
 * @author			SRID(manoj.g2)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Foreach for all srticker data provider handle
 * @scenario			Foreach for all srticker data provider handle
 * @apicovered			sticker_provider_data_foreach_all
 * @passcase			When sticker_provider_data_foreach_all and Precondition API's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to Check for Foreach for all sticker data provider handle
int ITc_capi_ui_sticker_data_sticker_provider_data_foreach_all_p(void)
{
	START_TEST;
	int nRet = -1;
	int nResult = -1;
	g_bCallbackHit = false;

	nRet = sticker_provider_insert_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_insert_data", StickerGetError(nRet));

	nRet = sticker_provider_data_foreach_all(g_hStickerProviderHandle, 0, 1000, &nResult, StickerDataProviderForeachCallback, NULL);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_data_foreach_all", StickerGetError(nRet));

	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	if(nResult < 0)
	{
		FPRINTF("[%s:%d] nResult value is not valid\\n", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_data_get_handle_p
 * @since_tizen			5.5
 * @author			SRID(priya.kohli)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Gets the sticker data handle for the given URI.
 * @scenario			Gets the sticker data handle for the given URI.
 * @apicovered			sticker_data_get_handle
 * @passcase			When sticker_data_get_handle and Precondition API's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to get the sticker data handle for the given URI.
int ITc_capi_ui_sticker_data_sticker_data_get_handle_p(void)
{
	START_TEST;
	int nRet = -1;
	sticker_data_h hStickerDataHandle = NULL;

	nRet = sticker_provider_insert_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_insert_data", StickerGetError(nRet));

	nRet = sticker_data_get_handle("www.samsung.com/ITC/provider", &hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_get_handle", StickerGetError(nRet));
	CHECK_HANDLE(hStickerDataHandle, "sticker_data_get_handle");

	nRet = sticker_provider_delete_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	PRINT_RESULT_NORETURN(STICKER_ERROR_NONE, nRet, "sticker_provider_delete_data", StickerGetError(nRet));

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_provider_delete_data_by_uri_p
 * @since_tizen			5.5
 * @author			SRID(priya.kohli)
 * @reviewer			SRID(shobhit.v)
 * @type 			auto
 * @description			Deletes a sticker data in the sticker database using URI.
 * @scenario			Deletes a sticker data in the sticker database using URI.
 * @apicovered			sticker_provider_delete_data_by_uri
 * @passcase			When sticker_provider_delete_data_by_uri and Precondition API's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to delete a sticker data in the sticker database using URI.
int ITc_capi_ui_sticker_data_sticker_provider_delete_data_by_uri_p(void)
{
	int nRet = -1;

	nRet = sticker_provider_insert_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_insert_data", StickerGetError(nRet));

	nRet = sticker_provider_delete_data_by_uri(g_hStickerProviderHandle, "www.samsung.com/ITC/provider");
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_delete_data_by_uri", StickerGetError(nRet));

	nRet = sticker_data_set_uri(g_hStickerDataHandle, STICKER_DATA_URI_WEB_RESOURCE, "www.samsung.com/ITC/provider");
	PRINT_RESULT_NORETURN(STICKER_ERROR_NONE, nRet, "sticker_data_set_uri", StickerGetError(nRet));

	return 0;
}

/**
 * @testcase 			ITc_capi_ui_sticker_data_sticker_provider_set_group_image_p
 * @since_tizen			6.5
 * @author				SRID(nibha.sharma)
 * @reviewer			SRID(shobhit.v)
 * @type 				auto
 * @description			Sets a sticker group image.
 * @scenario			Sets a sticker group image.
 * @apicovered			sticker_provider_set_group_image
 * @passcase			When sticker_provider_set_group_image and Precondition API's are successful.
 * @failcase			If target API fails or any precondition API fails
 * @precondition		None
 * @postcondition		None
 */
//& purpose: API to sets a sticker group image.
int ITc_capi_ui_sticker_data_sticker_provider_set_group_image_p(void)
{
	START_TEST;

	int nRet = -1;
	char *pszGroup = "tizen", *pszUri="www.valid.com/test/image.png";

	nRet = sticker_provider_insert_data(g_hStickerProviderHandle, g_hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_insert_data", StickerGetError(nRet));

	nRet = sticker_provider_set_group_image(g_hStickerProviderHandle, pszGroup, STICKER_DATA_URI_WEB_RESOURCE, pszUri);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_provider_set_group_image", StickerGetError(nRet));

    return 0;
}