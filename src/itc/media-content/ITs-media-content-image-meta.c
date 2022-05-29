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
#include "ITs-media-content-common.h"

//& set: MediaContent

/** @addtogroup itc-media-content
*  @ingroup itc
*  @{
*/

/****************************************************Enums Start****************************************************/

/*****************************************************Enums End*****************************************************/

/**
 * @function 		ITs_media_content_image_meta_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_image_meta_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	char *pszMediaId = NULL;
	g_bMediaContentStartup = false;
	g_bIsScanFeatureSupported = false;
	g_bIsScanFeatureNotSupported = false;
	g_bScanFeatureMismatch= false;

	g_bIsScanFeatureSupported = TCTCheckSystemInfoFeatureSupported(SCAN_FEATURE, API_NAMESPACE);

	int nRet = media_content_connect();
	PRINT_RESULTNONE(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_connect", MediaContentGetError(nRet));

	nRet = GetInternalStorageIdandPath();
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetInternalStorageId", "Return Value Not Correct", media_content_disconnect());

	nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetFolderPath", "Return Value Not Correct", media_content_disconnect());
	CopyFileInfo("image");

	AppendPaths(g_szInternalStoragePath, TESTTEXT, g_szTextPath);
	nRet = media_info_insert_to_db(g_szTextPath, &g_hTextInfo);
	if ( !g_bIsScanFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bScanFeatureMismatch = true;
		}
		else
		{
			g_bIsScanFeatureNotSupported = true;
		}
		media_content_disconnect();
		return;
	}
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());
	AppendPaths(g_szImageFolder, TESTIMAGE, g_szImagePath);
	nRet = media_info_insert_to_db(g_szImagePath, &g_hImageInfo);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());
	nRet = media_info_get_media_id(g_hImageInfo, &pszMediaId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet), media_content_disconnect());
	memset(g_szImageId, 0, PATHLEN);
	strncpy(g_szImageId, pszMediaId, PATHLEN - 1);
	FREE_MEMORY(pszMediaId);

	nRet = media_info_get_image(g_hImageInfo, &g_hImageMeta);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_image", MediaContentGetError(nRet), media_content_disconnect());

	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_image_meta_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_image_meta_cleanup(void)
{
	if(g_hTextInfo)
	{
		media_info_destroy(g_hTextInfo);
	}
	if(g_hImageMeta)
	{
		image_meta_destroy(g_hImageMeta);
	}
	if(g_hImageInfo)
	{
		media_info_destroy(g_hImageInfo);
	}
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
		struct stat stBuff;
		if ( stat("image", &stBuff) == 0 )
		{
			if (remove("image"))
			{
				FPRINTF("[Line : %d][%s] TEST SUIT clean-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
			}
		}
		if(g_szImagePath)
		{
			media_content_scan_file(g_szImagePath);
		}
		media_content_disconnect();
	}
	return;
}

/** @addtogroup itc-media-content-testcases
*  @brief 		Integration testcases for module media-content
*  @ingroup 	itc-media-content
*  @{
*/

/**
* @testcase 			ITc_image_meta_clone_destroy_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test image_meta_clone and image_meta_destroy
* @scenario				Call image_meta_clone and image_meta_destroy
* @apicovered			image_meta_clone, image_meta_destroy
* @passcase				When image_meta_clone and image_meta_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test image_meta_clone and image_meta_destroy
//& type: auto
int ITc_image_meta_clone_destroy_p(void)
{
	START_TEST_PLAYLIST;

	image_meta_h hImageMeta = NULL;
	int nRet = image_meta_clone(&hImageMeta, g_hImageMeta);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hImageMeta, "image_meta_clone");

	nRet = image_meta_destroy(hImageMeta);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_image_meta_get_media_id_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test image_meta_get_media_id
* @scenario				Call image_meta_get_media_id
* @apicovered			image_meta_get_media_id
* @passcase				When image_meta_get_media_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test image_meta_get_media_id
//& type: auto
int ITc_image_meta_get_media_id_p(void)
{
	START_TEST_PLAYLIST;

	char *pszMediaId = NULL;
	int nRet = image_meta_get_media_id(g_hImageMeta, &pszMediaId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_get_media_id", MediaContentGetError(nRet));
	CHECK_HANDLE(pszMediaId, "image_meta_get_media_id");
	FREE_MEMORY(pszMediaId);

	return 0;
}

/**
* @testcase 			ITc_image_meta_get_height_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test image_meta_get_height
* @scenario				Call image_meta_get_height
* @apicovered			image_meta_get_height
* @passcase				When image_meta_get_height is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test image_meta_get_height
//& type: auto
int ITc_image_meta_get_height_p(void)
{
	START_TEST_PLAYLIST;

	int nHeight = 0;
	int nRet = image_meta_get_height(g_hImageMeta, &nHeight);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_get_height", MediaContentGetError(nRet));
	CHECK_COUNT(nHeight, "image_meta_get_height");

	return 0;

}

/**
-* @testcase                    ITc_image_meta_get_orientation_p
-* @since_tizen                 2.3
-* @author                              SRID(abhishek1.g)
-* @reviewer                            SRID(gupta.sanjay)
-* @type                                auto
-* @description                 Test  image_meta_get_orientation
-* @scenario                            Call  image_meta_get_orientation
-* @apicovered                 image_meta_get_orientation
-* @passcase                            When  image_meta_get_orientation is successful
-* @failcase                            If target API fails or any precondition API fails
-* @precondition                        NA
-* @postcondition               NA
-*/
//& purpose: Test  image_meta_get_orientation
//& type: auto
int ITc_image_meta_get_orientation_p(void)
{
       START_TEST_PLAYLIST;

       int nRet = 0;
       int nEnumCounter = 0;
       media_content_orientation_e nGetOrientation = MEDIA_CONTENT_ORIENTATION_NOT_AVAILABLE;

       nRet = image_meta_get_orientation(g_hImageMeta, &nGetOrientation);
       PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_get_orientation", MediaContentGetError(nRet));
       return 0;
}

/**
* @testcase 			ITc_image_meta_get_width_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test image_meta_get_width
* @scenario				Call image_meta_get_width
* @apicovered			image_meta_get_width
* @passcase				When image_meta_get_width is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test image_meta_get_width
//& type: auto
int ITc_image_meta_get_width_p(void)
{
	START_TEST_PLAYLIST;

	int nWidth = 0;
	int nRet = image_meta_get_width(g_hImageMeta, &nWidth);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_get_width", MediaContentGetError(nRet));
	CHECK_COUNT(nWidth, "image_meta_get_width");

	return 0;
}

/**
* @testcase 			ITc_image_meta_get_date_taken_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test image_meta_get_date_taken
* @scenario				Call image_meta_get_date_taken
* @apicovered			image_meta_get_date_taken
* @passcase				When image_meta_get_date_taken is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test image_meta_get_date_taken
//& type: auto
int ITc_image_meta_get_date_taken_p(void)
{
	START_TEST_PLAYLIST;

	char *pszDateTaken = NULL;
	int nRet = image_meta_get_date_taken(g_hImageMeta, &pszDateTaken);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_get_date_taken", MediaContentGetError(nRet));
	CHECK_HANDLE(pszDateTaken, "image_meta_get_date_taken");
	FREE_MEMORY(pszDateTaken);

	return 0;
}

/**
* @testcase 			ITc_image_meta_get_model_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test image_meta_get_model
* @scenario				Call image_meta_get_model
* @apicovered			image_meta_get_model
* @passcase				When image_meta_get_model is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test image_meta_get_model
//& type: auto
int ITc_image_meta_get_model_p(void)
{
	START_TEST_PLAYLIST;

	char *pszModel = NULL;
	int nRet = image_meta_get_model(g_hImageMeta, &pszModel);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_get_model", MediaContentGetError(nRet));
	CHECK_HANDLE(pszModel, "image_meta_get_model");
	FREE_MEMORY(pszModel);

	return 0;
}

/**
* @testcase 			ITc_image_meta_get_exposure_time_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test image_meta_get_exposure_time
* @scenario				Call image_meta_get_exposure_time
* @apicovered			image_meta_get_exposure_time
* @passcase				When image_meta_get_exposure_time is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test image_meta_get_exposure_time
//& type: auto
int ITc_image_meta_get_exposure_time_p(void)
{
	START_TEST_PLAYLIST;

	char *pszExposureTime = NULL;
	int nRet = image_meta_get_exposure_time(g_hImageMeta, &pszExposureTime);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_get_exposure_time", MediaContentGetError(nRet));
	CHECK_HANDLE(pszExposureTime, "image_meta_get_exposure_time");
	FREE_MEMORY(pszExposureTime);

	return 0;
}

/**
* @testcase 			ITc_image_meta_get_iso_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test image_meta_get_iso
* @scenario				Call image_meta_get_iso
* @apicovered			image_meta_get_iso
* @passcase				When image_meta_get_iso is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test image_meta_get_iso
//& type: auto
int ITc_image_meta_get_iso_p(void)
{
	START_TEST_PLAYLIST;

	int nIso = 0;
	int nRet = image_meta_get_iso(g_hImageMeta, &nIso);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_get_iso", MediaContentGetError(nRet));
	CHECK_COUNT(nIso, "image_meta_get_iso");

	return 0;
}

/**
* @testcase 			ITc_image_meta_get_fnumber_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test image_meta_get_fnumber
* @scenario				Call image_meta_get_fnumber
* @apicovered			image_meta_get_fnumber
* @passcase				When image_meta_get_fnumber is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test image_meta_get_fnumber
//& type: auto
int ITc_image_meta_get_fnumber_p(void)
{
	START_TEST_PLAYLIST;

	double dFnumber = 0;
	int nRet = image_meta_get_fnumber(g_hImageMeta, &dFnumber);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_get_fnumber", MediaContentGetError(nRet));

	return 0;
}

/** @} */
/** @} */
