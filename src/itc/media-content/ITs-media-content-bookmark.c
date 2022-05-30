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
 * @function 		ForeachBookmarkCb
 * @description	 	Callback Function
 * @parameter		media_bookmark_h bookmark, void *user_data
 * @return 			NA
 */
static bool ForeachBookmarkCb(media_bookmark_h bookmark, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachBookmarkCb");
#endif

	int nRet = media_bookmark_clone(&g_hBookmark, bookmark);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet), QuitGmainLoop());

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

	if(MEDIA_CONTENT_TYPE_VIDEO == eMediaType)
	{
		char *szMediaId = NULL;
		nRet = media_info_get_media_id(media, &szMediaId);
		PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet), QuitGmainLoop());

		memset(g_szMediaId, 0, PATHLEN);
		strncpy(g_szMediaId, szMediaId, PATHLEN-1);
		FREE_MEMORY(szMediaId);
		g_CallBackHit = true;
		QuitGmainLoop();
		return false;
	}

	return true;
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_media_content_bookmark_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_bookmark_startup(void)
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

	nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetFolderPath", "Return Value Not Correct", media_content_disconnect());
	CopyFileInfo("image");

	AppendPaths(g_szImageFolder, BOOKMARKIMAGE, g_szImagePath);

	nRet = media_content_scan_file(g_szImagePath);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());

	nRet = GetFolderPath(STORAGE_DIRECTORY_VIDEOS, g_szVideoFolder);
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetFolderPath", "Return Value Not Correct", media_content_disconnect());
	CopyFileInfo("video");
	AppendPaths(g_szVideoFolder, TESTVIDEO, g_szVideoPath);

	nRet = media_content_scan_file(g_szVideoPath);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());

	g_CallBackHit = false;
	nRet = media_info_foreach_media_from_db(NULL, ForeachMediaCb, TESTSTRING);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_foreach_media_from_db", MediaContentGetError(nRet), media_content_disconnect());
	IterateGmainLoop();
	PRINT_RESULTNONE_CLEANUP(true, g_CallBackHit, "media_info_foreach_media_from_db", "CallBack Not Invoked", media_content_disconnect());

	time_t stTime = {0};
	time(&stTime);
	nRet = media_bookmark_insert_to_db(g_szMediaId, stTime, g_szImagePath);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());

	g_CallBackHit = false;
	nRet = media_info_foreach_bookmark_from_db(g_szMediaId, NULL, ForeachBookmarkCb, TESTSTRING);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_foreach_bookmark_from_db", MediaContentGetError(nRet), media_content_disconnect());
	IterateGmainLoop();
	PRINT_RESULTNONE_CLEANUP(true, g_CallBackHit, "media_info_foreach_bookmark_from_db", "CallBack Not Invoked", media_content_disconnect());

	nRet = media_bookmark_get_bookmark_id(g_hBookmark, &g_nBookmarkId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_insert_to_db", MediaContentGetError(nRet), media_bookmark_delete_from_db(g_nBookmarkId); media_bookmark_destroy(g_hBookmark); media_content_disconnect());

	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_bookmark_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_bookmark_cleanup(void)
{
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
		media_bookmark_delete_from_db(g_nBookmarkId);
		media_bookmark_destroy(g_hBookmark);
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
* @testcase 			ITc_media_bookmark_get_bookmark_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_bookmark_get_bookmark_count_from_db
* @scenario				Call media_bookmark_get_bookmark_count_from_db
* @apicovered			media_bookmark_get_bookmark_count_from_db
* @passcase				When media_bookmark_get_bookmark_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_bookmark_get_bookmark_count_from_db
//& type: auto
int ITc_media_bookmark_get_bookmark_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nCount = -1;
	int nRet = media_bookmark_get_bookmark_count_from_db(NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_get_bookmark_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_bookmark_get_bookmark_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_bookmark_get_bookmark_id_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_bookmark_get_bookmark_id
* @scenario				Call media_bookmark_get_bookmark_id
* @apicovered			media_bookmark_get_bookmark_id
* @passcase				When media_bookmark_get_bookmark_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_bookmark_get_bookmark_id
//& type: auto
int ITc_media_bookmark_get_bookmark_id_p(void)
{
	START_TEST_PLAYLIST;

	int nBookmarkId = -1;
	int nRet = media_bookmark_get_bookmark_id(g_hBookmark, &nBookmarkId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_get_bookmark_id", MediaContentGetError(nRet));
	CHECK_COUNT(nBookmarkId, "media_bookmark_get_bookmark_id");

	return 0;
}

/**
* @testcase 			ITc_media_bookmark_get_thumbnail_path_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_bookmark_get_thumbnail_path
* @scenario				Call media_bookmark_get_thumbnail_path
* @apicovered			media_bookmark_get_thumbnail_path
* @passcase				When media_bookmark_get_thumbnail_path is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_bookmark_get_thumbnail_path
//& type: auto
int ITc_media_bookmark_get_thumbnail_path_p(void)
{
	START_TEST_PLAYLIST;

	char *pszBookmarkInfo = NULL;
	int nRet = media_bookmark_get_thumbnail_path(g_hBookmark, &pszBookmarkInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_get_thumbnail_path", MediaContentGetError(nRet));
	CHECK_HANDLE(pszBookmarkInfo, "media_bookmark_get_thumbnail_path");
	FREE_MEMORY(pszBookmarkInfo);

	return 0;
}

/**
* @testcase 			ITc_media_bookmark_clone_destroy_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_bookmark_clone and media_bookmark_destroy
* @scenario				Call media_bookmark_clone and media_bookmark_destroy
* @apicovered			media_bookmark_clone, media_bookmark_destroy
* @passcase				When media_bookmark_clone and media_bookmark_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_bookmark_clone and media_bookmark_destroy
//& type: auto
int ITc_media_bookmark_clone_destroy_p(void)
{
	START_TEST_PLAYLIST;

	media_bookmark_h hBookmark = NULL;
	int nRet = media_bookmark_clone(&hBookmark, g_hBookmark);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hBookmark, "media_bookmark_clone");

	nRet = media_bookmark_destroy(hBookmark);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_bookmark_get_marked_time_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_bookmark_get_marked_time
* @scenario				Call media_bookmark_get_marked_time
* @apicovered			media_bookmark_get_marked_time
* @passcase				When media_bookmark_get_marked_time is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_bookmark_get_marked_time
//& type: auto
int ITc_media_bookmark_get_marked_time_p(void)
{
	START_TEST_PLAYLIST;
	time_t stTime = {0};

	int nRet = media_bookmark_get_marked_time(g_hBookmark, &stTime);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_get_marked_time", MediaContentGetError(nRet));
	CHECK_COUNT(stTime, "media_bookmark_get_marked_time");

	return 0;
}

/**
* @testcase 			ITc_media_bookmark_insert_delete_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_bookmark_delete_from_db and media_bookmark_insert_to_db
* @scenario				Call media_bookmark_delete_from_db and media_bookmark_insert_to_db
* @apicovered			media_bookmark_delete_from_db, media_bookmark_insert_to_db
* @passcase				When media_bookmark_delete_from_db and media_bookmark_insert_to_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_bookmark_delete_from_db and media_bookmark_insert_to_db
//& type: auto
int ITc_media_bookmark_insert_delete_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = media_bookmark_delete_from_db(g_nBookmarkId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_delete_from_db", MediaContentGetError(nRet));

	nRet = media_bookmark_destroy(g_hBookmark);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_destroy", MediaContentGetError(nRet));
	g_hBookmark = NULL;

	time_t stTime = {0};
	time(&stTime);
	nRet = media_bookmark_insert_to_db(g_szMediaId, stTime, g_szImagePath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_insert_to_db", MediaContentGetError(nRet));

	g_CallBackHit = false;
	nRet = media_info_foreach_bookmark_from_db(g_szMediaId, NULL, ForeachBookmarkCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_foreach_bookmark_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_info_foreach_bookmark_from_db", "CallBack Not Invoked");

	nRet = media_bookmark_get_bookmark_id(g_hBookmark, &g_nBookmarkId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_insert_to_db", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_bookmark_set_get_name_p
* @since_tizen			4.0
* @author				SRID(j.abhishek)
* @reviewer				SRID(nibha.sharma)
* @type 				auto
* @description			Test media_bookmark_set_name and media_bookmark_get_name
* @scenario				Call media_bookmark_set_name and media_bookmark_get_name
* @apicovered			media_bookmark_set_name, media_bookmark_get_name
* @passcase				When media_bookmark_set_name and media_bookmark_get_name returns no error and is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_bookmark_set_name and media_bookmark_get_name
//& type: auto

int ITc_media_bookmark_set_get_name_p(void)
{
	START_TEST_PLAYLIST;

	char *pszBookMarkGetName = NULL;
	const char *pszBookMarkSetName = "test_name";
	int nRet = MEDIA_CONTENT_ERROR_NONE;

	nRet = media_bookmark_set_name(g_hBookmark, pszBookMarkSetName);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_set_name", MediaContentGetError(nRet));

	nRet = media_bookmark_get_name(g_hBookmark, &pszBookMarkGetName);

	if(!pszBookMarkGetName)
	{
		FPRINTF("[Line : %d][%s] media_bookmark_get_name returned NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(strcmp(pszBookMarkSetName, pszBookMarkGetName))
	{
		FPRINTF("[Line : %d][%s] media_bookmark_get_name error = value returned [ %s ] is not correct\\n", __LINE__, API_NAMESPACE, pszBookMarkGetName);
		FREE_MEMORY(pszBookMarkGetName);
		return 1;
	}

	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_get_name", MediaContentGetError(nRet));
	FREE_MEMORY(pszBookMarkGetName);
	return 0;
}

/**
* @testcase 			ITc_media_bookmark_update_to_db_p
* @since_tizen			4.0
* @author				SRID(j.abhishek)
* @reviewer				SRID(nibha.sharma)
* @type 				auto
* @description			Test media_bookmark_update_to_db
* @scenario				Call media_bookmark_update_to_db
* @apicovered			media_bookmark_update_to_db
* @passcase				When media_bookmark_update_to_db returns no error and is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_bookmark_set_name and media_bookmark_get_name
//& type: auto

int ITc_media_bookmark_update_to_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = MEDIA_CONTENT_ERROR_NONE;

	nRet = media_bookmark_update_to_db(g_hBookmark);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_update_to_db", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_bookmark_foreach_bookmark_from_db_p
* @since_tizen			4.0
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Test for foreach bookamrk from db
* @scenario				Call media_bookmark_foreach_bookmark_from_db
* @apicovered			media_bookmark_foreach_bookmark_from_db
* @passcase				When edia_filter_create and media_bookmark_foreach_bookmark_from_db returns no error and is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			media_filter_create
* @postcondition		media_filter_destroy
*/
//& purpose: Test for foreach bookamrk from db
//& type: auto

int ITc_media_bookmark_foreach_bookmark_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = -1;
	filter_h hFilter = NULL;

	g_CallBackHit = false;

	nRet = media_filter_create(&hFilter);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_create", MediaContentGetError(nRet));
	CHECK_HANDLE(hFilter, "media_filter_create");

	nRet = media_bookmark_foreach_bookmark_from_db(hFilter, ForeachBookmarkCb, NULL);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_foreach_bookmark_from_db", MediaContentGetError(nRet), media_filter_destroy(hFilter));
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "media_bookmark_foreach_bookmark_from_db", "CallBack Not Invoked", media_filter_destroy(hFilter));

	media_filter_destroy(hFilter);

	return 0;
}

/** @} */
/** @} */
