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
 * @function		StickerDataForeachKeywordCallback
 * @description A sticker data foreach callback for keyword
 */
static void StickerDataForeachKeywordCallback(const char *keyword, void *user_data)
{
   	FPRINTF("[Line : %d][%s] Inside callback  StickerDataForeachKeywordCallback\\n", __LINE__, API_NAMESPACE);
    	g_bCallbackHit = true;
}

/**
* @function 		ITs_capi_ui_sticker_data_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_capi_ui_sticker_data_startup(void)
{
	int nRet =-1;
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0)
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_capi_ui_sticker_data_startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_bIsFeatureMismatched = false;
	g_bStickerCreation = false;
	g_bFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(FEATURE_STICKER, API_NAMESPACE);

	nRet = sticker_data_create(&g_hStickerDataHandle);
	if(!g_bFeatureIsSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] sticker_data_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] sticker_data_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] sticker_data_create is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] sticker_data_create is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != STICKER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] sticker_data_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d]sticker_data_create failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bStickerCreation = false;
	}
	else
	{
		g_bStickerCreation = true;
	}

	return;

}

/**
* @function 		ITs_capi_ui_sticker_data_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_capi_ui_sticker_data_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_capi_ui_sticker_data_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	if (g_hStickerDataHandle) {
		int nRet = sticker_data_destroy (g_hStickerDataHandle);
		if(nRet !=0)
		{
				FPRINTF("sticker_data_destroy failed\\n");
				dlog_print(DLOG_ERROR, "NativeTCT", "sticker_data_destroy failed");
		}
		g_hStickerDataHandle = NULL;
	}
}

/**
* @testcase 			ITc_capi_ui_sticker_data_sticker_data_create_destroy_p
* @since_tizen			5.5
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Create and Destroy sticker data handle
* @scenario				Create and Destroy sticker data handle
* @apicovered			sticker_data_create,sticker_data_destroy
* @passcase				When sticker_data_create,sticker_data_destroy is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Create and Destroy sticker data handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_create_destroy_p(void)
{
	START_TEST;
	int nRet = -1;
	sticker_data_h hStickerDataHandle = NULL;

	nRet = sticker_data_create(&hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_create", StickerGetError(nRet));
	CHECK_HANDLE(hStickerDataHandle, "sticker_data_create");

	nRet = sticker_data_destroy(hStickerDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_destroy", StickerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_capi_ui_sticker_data_sticker_data_clone_p
* @since_tizen			5.5
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			clone sticker data handle
* @scenario				clone sticker data handle
* @apicovered			sticker_data_clone
* @passcase				When sticker_data_clone and Precondition API are successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for clone sticker data handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_clone_p(void)
{
	START_TEST;
	int nRet = -1;
	sticker_data_h hStickerCloneDataHandle = NULL;

	nRet = sticker_data_clone(g_hStickerDataHandle, &hStickerCloneDataHandle);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_clone", StickerGetError(nRet));
	CHECK_HANDLE(hStickerCloneDataHandle, "sticker_data_clone");

	nRet = sticker_data_destroy(hStickerCloneDataHandle);
	PRINT_RESULT_NORETURN(STICKER_ERROR_NONE, nRet, "sticker_data_destroy", StickerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_capi_ui_sticker_data_sticker_data_get_app_id_p
* @since_tizen			5.5
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Get sticker data App ID
* @scenario				Get sticker data App ID
* @apicovered			sticker_data_get_app_id
* @passcase				When sticker_data_get_app_id and Precondition API are successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Get sticker data App ID
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_get_app_id_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszAppID = NULL;

    	nRet = sticker_data_get_app_id(g_hStickerDataHandle, &pszAppID);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_get_app_id", StickerGetError(nRet));
	CHECK_HANDLE(pszAppID, "sticker_data_get_app_id");

	FREE_MEMORY(pszAppID);

	return 0;
}

/**
* @testcase 			ITc_capi_ui_sticker_data_sticker_data_set_get_uri_p
* @since_tizen			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Set and GetUri for sticker data handle
* @scenario			Set and GetUri for sticker data handle
* @apicovered			sticker_data_set_uri, sticker_data_get_uri
* @passcase			When sticker_data_set_uri, sticker_data_get_uri and Precondition API are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and Get Uri for sticker data handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_set_get_uri_p(void)
{
	START_TEST;
	int nRet = -1;
	sticker_data_uri_type_e eUriType =-1;
    	char *pszStickerWebUri = NULL;

	nRet = sticker_data_set_uri(g_hStickerDataHandle, STICKER_DATA_URI_WEB_RESOURCE, "www.tizen.org");
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_set_uri", StickerGetError(nRet));

	nRet = sticker_data_get_uri(g_hStickerDataHandle, &eUriType, &pszStickerWebUri);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_get_uri", StickerGetError(nRet));
	CHECK_HANDLE(pszStickerWebUri, "sticker_data_get_uri");

	PRINT_RESULT_CLEANUP(STICKER_DATA_URI_WEB_RESOURCE, eUriType, "Uri type mismatch", StickerGetError(nRet),FREE_MEMORY(pszStickerWebUri));
	if(strcmp(pszStickerWebUri,"www.tizen.org") != 0)
	{
		FPRINTF("Sticker Uri mismatch\\n");
		FREE_MEMORY(pszStickerWebUri);
		return 1;
	}

	FREE_MEMORY(pszStickerWebUri);

	return 0;
}

/**
* @testcase 			ITc_capi_ui_sticker_data_sticker_data_foreach_keyword_p
* @since_tizen			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			foreach sticker data keyword
* @scenario			foreach sticker data keyword
* @apicovered			sticker_data_foreach_keyword
* @passcase			When sticker_data_foreach_keyword and Precondition API are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for foreach sticker data keyword
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_foreach_keyword_p(void)
{
	START_TEST;
	int nRet = -1;

	g_bCallbackHit = false;

	nRet = sticker_data_add_keyword(g_hStickerDataHandle, "test");
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_add_keyword", StickerGetError(nRet));

	nRet = sticker_data_foreach_keyword(g_hStickerDataHandle, StickerDataForeachKeywordCallback, NULL);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_foreach_keyword", StickerGetError(nRet));
	PRINT_RESULT(g_bCallbackHit, true, "callback not hit", StickerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_capi_ui_sticker_data_sticker_data_add_remove_keyword_p
* @since_tizen			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Add and remove sticker data keyword
* @scenario			Add and remove sticker data keyword
* @apicovered			sticker_data_add_keyword, sticker_data_remove_keyword
* @passcase			When sticker_data_add_keyword, sticker_data_remove_keyword and Precondition API are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Add and remove sticker data keyword
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_add_remove_keyword_p(void)
{
	START_TEST;
	int nRet = -1;

	nRet = sticker_data_add_keyword(g_hStickerDataHandle, "test");
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_add_keyword", StickerGetError(nRet));

	nRet = sticker_data_add_keyword(g_hStickerDataHandle, "face");
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_add_keyword", StickerGetError(nRet));

	nRet = sticker_data_remove_keyword(g_hStickerDataHandle, "test");
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_remove_keyword", StickerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_capi_ui_sticker_data_sticker_data_set_get_group_name_p
* @since_tizen			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Set and group name for sticker data handle
* @scenario			Set and group name for sticker data handle
* @apicovered			sticker_data_set_group_name, sticker_data_get_group_name
* @passcase			When sticker_data_set_group_name, sticker_data_get_group_name is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and group name for sticker data handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_set_get_group_name_p(void)
{
	START_TEST;
	int nRet = -1;
    	char *pszGetGroupName = NULL;

	nRet = sticker_data_set_group_name(g_hStickerDataHandle, "samsung");
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_set_group_name", StickerGetError(nRet));

	nRet = sticker_data_get_group_name(g_hStickerDataHandle, &pszGetGroupName);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_get_group_name", StickerGetError(nRet));
	CHECK_HANDLE(pszGetGroupName, "sticker_data_get_group_name");

	if(strcmp(pszGetGroupName,"samsung") != 0)
	{
		FPRINTF("Sticker Group name mismatch\\n");
		FREE_MEMORY(pszGetGroupName);
		return 1;
	}

	FREE_MEMORY(pszGetGroupName);

	return 0;
}

/**
* @testcase 			ITc_capi_ui_sticker_data_sticker_data_set_get_thumbnail_p
* @since_tizen			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Set and thumbnail for sticker data handle
* @scenario			Set and thumbnail for sticker data handle
* @apicovered			sticker_data_set_thumbnail, sticker_data_get_thumbnail
* @passcase			When sticker_data_set_thumbnail, sticker_data_get_thumbnail is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and thumbnail for sticker data handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_set_get_thumbnail_p(void)
{
	START_TEST;
	int nRet = -1;
    	char *pszGetThumbNail = NULL;

	nRet = sticker_data_set_thumbnail(g_hStickerDataHandle, "/res/test.png");
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_set_thumbnail", StickerGetError(nRet));

	nRet = sticker_data_get_thumbnail(g_hStickerDataHandle, &pszGetThumbNail);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_get_thumbnail", StickerGetError(nRet));
	CHECK_HANDLE(pszGetThumbNail, "sticker_data_get_thumbnail");

	FREE_MEMORY(pszGetThumbNail);

	return 0;
}

/**
* @testcase 			ITc_capi_ui_sticker_data_sticker_data_set_get_description_p
* @since_tizen			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			Set and description for sticker data handle
* @scenario			Set and description for sticker data handle
* @apicovered			sticker_data_set_description, sticker_data_get_description
* @passcase			When sticker_data_set_description, sticker_data_get_description is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and description for sticker data handle
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_set_get_description_p(void)
{
	START_TEST;
	int nRet = -1;
    	char *pszGetDescription = NULL;

	nRet = sticker_data_set_description(g_hStickerDataHandle, "TCT Test");
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_set_description", StickerGetError(nRet));

	nRet = sticker_data_get_description(g_hStickerDataHandle, &pszGetDescription);
	PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_get_description", StickerGetError(nRet));
	CHECK_HANDLE(pszGetDescription, "sticker_data_get_description");

	if(strcmp(pszGetDescription,"TCT Test") != 0)
	{
		FPRINTF("Sticker description mismatch and get description is %s\\n", pszGetDescription);
		FREE_MEMORY(pszGetDescription);
		return 1;
	}

	FREE_MEMORY(pszGetDescription);

	return 0;
}

/**
* @testcase 			ITc_capi_ui_sticker_data_sticker_data_get_date_p
* @since_tizen			5.5
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Get sticker data date
* @scenario				Get sticker data date
* @apicovered			sticker_data_get_date
* @passcase				When sticker_data_get_date is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Get sticker data date
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_get_date_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszStickerDate = NULL;
    	nRet = sticker_data_get_date(g_hStickerDataHandle, &pszStickerDate);
	PRINT_RESULT(STICKER_ERROR_NO_DATA, nRet, "sticker_data_get_date", StickerGetError(nRet));
	/* In this API if no data return from DB then STICKER_ERROR_NO_DATA error code will return  so we are checking against this error code*/

	FREE_MEMORY(pszStickerDate);

	return 0;
}

/**
* @testcase                     ITc_capi_ui_sticker_data_sticker_data_set_get_display_type_p
* @since_tizen			5.5
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and gets the display type of the sticker.
* @scenario				Sets and gets the display type of the sticker.
* @apicovered			sticker_data_set_display_type, sticker_data_get_display_type
* @passcase				When target APIs are successful and set, get values are same.
* @failcase				If any of the target API fails or any precondition API fails or set, get values are not same.
* @precondition			None
* @postcondition		None
*/
//& purpose: API to set and get the display type of the sticker.
//& type: auto
int ITc_capi_ui_sticker_data_sticker_data_set_get_display_type_p(void)
{
	START_TEST;
	int nRet = -1;
	sticker_data_display_type_e eGetDispType;

	sticker_data_display_type_e eDisplayType[] =  {STICKER_DATA_DISP_EMOJI,
						STICKER_DATA_DISP_WALLPAPER};

	int nSize = sizeof(eDisplayType)/sizeof(eDisplayType[0]);
	for(int nCount = 0; nCount < nSize; nCount++)
	{
		nRet = sticker_data_set_display_type(g_hStickerDataHandle, eDisplayType[nCount]);
		PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_set_display_type", StickerGetError(nRet));

		nRet = sticker_data_get_display_type(g_hStickerDataHandle, &eGetDispType);
		PRINT_RESULT(STICKER_ERROR_NONE, nRet, "sticker_data_get_display_type", StickerGetError(nRet));
		if(eDisplayType[nCount] != eGetDispType)
		{
			FPRINTF("[%s:%d] Set and Get display type value mismatch\\n", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}
