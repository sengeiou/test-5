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

/****************************************************Callback Start****************************************************/

/**
 * @function 		ForeachTagCb
 * @description	 	Callback Function
 * @parameter		media_tag_h tag, void *user_data
 * @return 			NA
 */
static bool ForeachTagCb(media_tag_h tag, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachTagCb");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
	return false;
}

/**
 * @function 		ForeachMediaCb
 * @description	 	Callback Function
 * @parameter		media_info_h media, void *user_data
 * @return 			NA
 */
static bool ForeachMediaCb(media_info_h media, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachMediaCb");
#endif

	media_content_type_e eMediaType = MEDIA_CONTENT_TYPE_OTHERS;
	int nRet = media_info_get_media_type(media, &eMediaType);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_type", MediaContentGetError(nRet), QuitGmainLoop());

	if(MEDIA_CONTENT_TYPE_IMAGE == eMediaType)
	{
		char *szMediaId = NULL;
		nRet = media_info_get_media_id(media, &szMediaId);
		PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet), QuitGmainLoop());

		memset(g_szMediaId, 0, PATHLEN);
		strncpy(g_szMediaId, szMediaId, PATHLEN - 1);
		FREE_MEMORY(szMediaId);
		g_CallBackHit = true;
		QuitGmainLoop();
		return false;
	}

	return true;
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_media_content_tag_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_tag_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

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

	nRet = media_content_scan_file(g_szTextPath);
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

	nRet = media_content_scan_file(g_szImagePath);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());

	nRet = media_tag_insert_to_db(TAGNAME, &g_hTag);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());

	nRet = media_tag_get_tag_id(g_hTag, &g_nTagId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_insert_to_db", MediaContentGetError(nRet), media_tag_delete_from_db(g_nTagId); media_tag_destroy(g_hTag); media_content_disconnect());

	g_CallBackHit = false;
	nRet = media_info_foreach_media_from_db(NULL, ForeachMediaCb, TESTSTRING);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_foreach_media_from_db", MediaContentGetError(nRet), media_tag_delete_from_db(g_nTagId); media_tag_destroy(g_hTag); media_content_disconnect());
	IterateGmainLoop();
	PRINT_RESULTNONE_CLEANUP(true, g_CallBackHit, "media_info_foreach_media_from_db", "CallBack Not Invoked", media_tag_delete_from_db(g_nTagId); media_tag_destroy(g_hTag); media_content_disconnect());

	nRet = media_tag_add_media(g_hTag, g_szMediaId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_add_media", MediaContentGetError(nRet), media_tag_delete_from_db(g_nTagId); media_tag_destroy(g_hTag); media_content_disconnect());

	nRet = media_tag_update_to_db(g_hTag);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_update_to_db", MediaContentGetError(nRet), media_tag_delete_from_db(g_nTagId); media_tag_destroy(g_hTag); media_content_disconnect());

	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_tag_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_tag_cleanup(void)
{
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
		media_tag_remove_media(g_hTag, g_szMediaId);
		media_tag_update_to_db(g_hTag);
		media_tag_delete_from_db(g_nTagId);
		media_tag_destroy(g_hTag);
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
* @testcase 			ITc_media_tag_get_tag_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_get_tag_count_from_db
* @scenario				Call media_tag_get_tag_count_from_db
* @apicovered			media_tag_get_tag_count_from_db
* @passcase				When media_tag_get_tag_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_get_tag_count_from_db
//& type: auto
int ITc_media_tag_get_tag_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nCount = -1;
	int nRet = media_tag_get_tag_count_from_db(NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_get_tag_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_tag_get_tag_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_tag_foreach_tag_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_foreach_tag_from_db
* @scenario				Call media_tag_foreach_tag_from_db
* @apicovered			media_tag_foreach_tag_from_db
* @passcase				When media_tag_foreach_tag_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_foreach_tag_from_db
//& type: auto
int ITc_media_tag_foreach_tag_from_db_p(void)
{
	START_TEST_PLAYLIST;

	g_CallBackHit = false;
	int nRet = media_tag_foreach_tag_from_db(NULL, ForeachTagCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_foreach_tag_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_tag_foreach_tag_from_db", "CallBack Not Invoked");

	return 0;
}

/**
* @testcase 			ITc_media_tag_clone_destroy_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_clone and media_tag_destroy
* @scenario				Call media_tag_clone and media_tag_destroy
* @apicovered			media_tag_clone, media_tag_destroy
* @passcase				When media_tag_clone and media_tag_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_clone and media_tag_destroy
//& type: auto
int ITc_media_tag_clone_destroy_p(void)
{
	START_TEST_PLAYLIST;

	media_tag_h hTag = NULL;
	int nRet = media_tag_clone(&hTag, g_hTag);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hTag, "media_tag_clone");

	nRet = media_tag_destroy(hTag);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_tag_get_tag_id_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_get_tag_id
* @scenario				Call media_tag_get_tag_id
* @apicovered			media_tag_get_tag_id
* @passcase				When media_tag_get_tag_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_get_tag_id
//& type: auto
int ITc_media_tag_get_tag_id_p(void)
{
	START_TEST_PLAYLIST;

	int nTagId = -1;
	int nRet = media_tag_get_tag_id(g_hTag, &nTagId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_get_tag_id", MediaContentGetError(nRet));
	CHECK_COUNT(nTagId, "media_tag_get_tag_id");

	return 0;
}

/**
* @testcase 			ITc_media_tag_get_media_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_get_media_count_from_db
* @scenario				Call media_tag_get_media_count_from_db
* @apicovered			media_tag_get_media_count_from_db
* @passcase				When media_tag_get_media_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_get_media_count_from_db
//& type: auto
int ITc_media_tag_get_media_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nTagId = -1;
	int nRet = media_tag_get_tag_id(g_hTag, &nTagId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_get_tag_id", MediaContentGetError(nRet));
	CHECK_COUNT(nTagId, "media_tag_get_tag_id");

	int nCount = -1;
	nRet = media_tag_get_media_count_from_db(nTagId, NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_get_media_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_tag_get_media_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_tag_foreach_media_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_foreach_media_from_db
* @scenario				Call media_tag_foreach_media_from_db
* @apicovered			media_tag_foreach_media_from_db
* @passcase				When media_tag_foreach_media_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_foreach_media_from_db
//& type: auto
int ITc_media_tag_foreach_media_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nTagId = -1;
	int nRet = media_tag_get_tag_id(g_hTag, &nTagId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_get_tag_id", MediaContentGetError(nRet));
	CHECK_COUNT(nTagId, "media_tag_get_tag_id");

	g_CallBackHit = false;
	nRet = media_tag_foreach_media_from_db(nTagId, NULL, ForeachMediaCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_foreach_media_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_tag_foreach_media_from_db", "CallBack Not Invoked");

	return 0;
}

/**
* @testcase 			ITc_media_tag_get_tag_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_get_tag_from_db
* @scenario				Call media_tag_get_tag_from_db
* @apicovered			media_tag_get_tag_from_db
* @passcase				When media_tag_get_tag_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_get_tag_from_db
//& type: auto
int ITc_media_tag_get_tag_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nTagId = -1;
	int nRet = media_tag_get_tag_id(g_hTag, &nTagId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_get_tag_id", MediaContentGetError(nRet));
	CHECK_COUNT(nTagId, "media_tag_get_tag_id");

	media_tag_h hTag = NULL;
	nRet = media_tag_get_tag_from_db(nTagId, &hTag);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_get_tag_from_db", MediaContentGetError(nRet));
	CHECK_HANDLE(hTag, "media_tag_get_tag_from_db");

	nRet = media_tag_destroy(hTag);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_tag_set_get_name_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_set_name and media_tag_get_name
* @scenario				Call media_tag_set_name, media_tag_get_name
* @apicovered			media_tag_set_name, media_tag_get_name
* @passcase				When media_tag_set_name and media_tag_get_name is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_set_name and media_tag_get_name
//& type: auto
int ITc_media_tag_set_get_name_p(void)
{
	START_TEST_PLAYLIST;
	char *pszTagInfo = NULL;

	int nRet = media_tag_set_name(g_hTag, TAGNAME);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_set_name", MediaContentGetError(nRet));

	nRet = media_tag_get_name(g_hTag, &pszTagInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_get_name", MediaContentGetError(nRet));
	CHECK_HANDLE(pszTagInfo, "media_tag_get_name");
	PRINT_RESULT_CLEANUP(0, strcmp(pszTagInfo, TAGNAME), "media_tag_get_name", "Tag Name Mismatch", FREE_MEMORY(pszTagInfo));

	FREE_MEMORY(pszTagInfo);
	return 0;
}

/**
* @testcase 			ITc_media_tag_add_remove_media_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_add_media and media_tag_remove_media
* @scenario				Call media_tag_add_media, media_tag_remove_media
* @apicovered			media_tag_add_media, media_tag_remove_media
* @passcase				When media_tag_add_media and media_tag_remove_media is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_add_media and media_tag_remove_media
//& type: auto
int ITc_media_tag_add_remove_media_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = media_tag_remove_media(g_hTag, g_szMediaId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_remove_media", MediaContentGetError(nRet));

	nRet = media_tag_add_media(g_hTag, g_szMediaId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_add_media", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_tag_update_to_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_update_to_db
* @scenario				Call media_tag_update_to_db
* @apicovered			media_tag_update_to_db
* @passcase				When media_tag_update_to_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_update_to_db
//& type: auto
int ITc_media_tag_update_to_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = media_tag_update_to_db(g_hTag);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_update_to_db", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_tag_insert_delete_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_tag_insert_to_db and media_tag_delete_from_db
* @scenario				Call media_tag_insert_to_db, media_tag_delete_from_db
* @apicovered			media_tag_insert_to_db, media_tag_delete_from_db
* @passcase				When media_tag_insert_to_db and media_tag_delete_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_tag_insert_to_db and media_tag_delete_from_db
//& type: auto
int ITc_media_tag_insert_delete_from_db_p(void)
{
	START_TEST_PLAYLIST;
	media_tag_h hMediaTag = NULL;
	int nTagId = -1;

	int nRet = media_tag_insert_to_db(TAGNAMENEW, &hMediaTag);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_insert_to_db", MediaContentGetError(nRet));

	nRet = media_tag_get_tag_id(hMediaTag, &nTagId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_get_tag_id", MediaContentGetError(nRet));
	CHECK_COUNT(nTagId, "media_tag_get_tag_id");

	nRet = media_tag_delete_from_db(nTagId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_delete_from_db", MediaContentGetError(nRet));

	nRet = media_tag_destroy(hMediaTag);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_destroy", MediaContentGetError(nRet));

	return 0;
}

/** @} */
/** @} */
