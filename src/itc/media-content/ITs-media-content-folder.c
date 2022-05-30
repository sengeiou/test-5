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
 * @function 		ForeachFolderCb
 * @description	 	Callback Function
 * @parameter		media_folder_h folder, void *user_data
 * @return 			NA
 */
static bool ForeachFolderCb(media_folder_h folder, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachFolderCb");
#endif

	char *pszFolderInfo = NULL;
	int nRet = media_folder_get_name(folder, &pszFolderInfo);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_get_name", MediaContentGetError(nRet), QuitGmainLoop());

	if((pszFolderInfo != NULL) && (strcmp(pszFolderInfo, FOLDERNAME) == 0))
	{
		nRet = media_folder_clone(&g_hFolder, folder);
		PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_clone", MediaContentGetError(nRet), FREE_MEMORY(pszFolderInfo); QuitGmainLoop());

		g_CallBackHit = true;
		FREE_MEMORY(pszFolderInfo);
		QuitGmainLoop();
		return false;
	}

	FREE_MEMORY(pszFolderInfo);
	return true;
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

	g_CallBackHit = true;
	QuitGmainLoop();
	return false;
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_media_content_folder_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_folder_startup(void)
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

	AppendPaths(g_szInternalStoragePath, FOLDERFILE, g_szFolderFilePath);

	nRet = media_content_scan_file(g_szFolderFilePath);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());

	g_CallBackHit = false;
	nRet = media_folder_foreach_folder_from_db(NULL, ForeachFolderCb, TESTSTRING);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_foreach_folder_from_db", MediaContentGetError(nRet), media_content_disconnect());
	IterateGmainLoop();
	PRINT_RESULTNONE_CLEANUP(true, g_CallBackHit, "media_folder_foreach_folder_from_db", "CallBack Not Invoked", media_content_disconnect());

	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_folder_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_folder_cleanup(void)
{
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
		media_folder_destroy(g_hFolder);
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
* @testcase 			ITc_media_folder_get_folder_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_folder_get_folder_count_from_db
* @scenario				Call media_folder_get_folder_count_from_db
* @apicovered			media_folder_get_folder_count_from_db
* @passcase				When media_folder_get_folder_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_folder_get_folder_count_from_db
//& type: auto
int ITc_media_folder_get_folder_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nCount = -1;
	int nRet = media_folder_get_folder_count_from_db(NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_get_folder_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_folder_get_folder_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_folder_foreach_folder_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_folder_foreach_folder_from_db
* @scenario				Call media_folder_foreach_folder_from_db
* @apicovered			media_folder_foreach_folder_from_db
* @passcase				When media_folder_foreach_folder_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_folder_foreach_folder_from_db
//& type: auto
int ITc_media_folder_foreach_folder_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = media_folder_destroy(g_hFolder);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_destroy", MediaContentGetError(nRet));
	g_hFolder = NULL;

	g_CallBackHit = false;
	nRet = media_folder_foreach_folder_from_db(NULL, ForeachFolderCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_foreach_folder_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_folder_foreach_folder_from_db", "CallBack Not Invoked");

	return 0;
}

/**
* @testcase 			ITc_media_folder_clone_destroy_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_folder_clone and media_folder_destroy
* @scenario				Call media_folder_clone and media_folder_destroy
* @apicovered			media_folder_clone, media_folder_destroy
* @passcase				When media_folder_clone and media_folder_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_folder_clone and media_folder_destroy
//& type: auto
int ITc_media_folder_clone_destroy_p(void)
{
	START_TEST_PLAYLIST;

	media_folder_h hFolder = NULL;
	int nRet = media_folder_clone(&hFolder, g_hFolder);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hFolder, "media_folder_clone");

	nRet = media_folder_destroy(hFolder);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_folder_get_folder_id_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_folder_get_folder_id
* @scenario				Call media_folder_get_folder_id
* @apicovered			media_folder_get_folder_id
* @passcase				When media_folder_get_folder_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_folder_get_folder_id
//& type: auto
int ITc_media_folder_get_folder_id_p(void)
{
	START_TEST_PLAYLIST;

	char *pszFolderId = NULL;
	int nRet = media_folder_get_folder_id(g_hFolder, &pszFolderId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_get_folder_id", MediaContentGetError(nRet));
	CHECK_HANDLE(pszFolderId, "media_folder_get_folder_id");
	FREE_MEMORY(pszFolderId);

	return 0;
}

/**
* @testcase 			ITc_media_folder_get_media_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_folder_get_media_count_from_db
* @scenario				Call media_folder_get_media_count_from_db
* @apicovered			media_folder_get_media_count_from_db
* @passcase				When media_folder_get_media_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_folder_get_media_count_from_db
//& type: auto
int ITc_media_folder_get_media_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	char *pszFolderId = NULL;
	int nRet = media_folder_get_folder_id(g_hFolder, &pszFolderId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_get_folder_id", MediaContentGetError(nRet));
	CHECK_HANDLE(pszFolderId, "media_folder_get_folder_id");

	int nCount = -1;
	nRet = media_folder_get_media_count_from_db(pszFolderId, NULL, &nCount);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_get_media_count_from_db", MediaContentGetError(nRet), FREE_MEMORY(pszFolderId));
	CHECK_COUNT_CLEANUP(nCount, "media_folder_get_media_count_from_db", FREE_MEMORY(pszFolderId));

	FREE_MEMORY(pszFolderId);
	return 0;
}

/**
* @testcase 			ITc_media_folder_foreach_media_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_folder_foreach_media_from_db
* @scenario				Call media_folder_foreach_media_from_db
* @apicovered			media_folder_foreach_media_from_db
* @passcase				When media_folder_foreach_media_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_folder_foreach_media_from_db
//& type: auto
int ITc_media_folder_foreach_media_from_db_p(void)
{
	START_TEST_PLAYLIST;

	char *pszFolderId = NULL;
	int nRet = media_folder_get_folder_id(g_hFolder, &pszFolderId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_get_folder_id", MediaContentGetError(nRet));
	CHECK_HANDLE(pszFolderId, "media_folder_get_folder_id");

	g_CallBackHit = false;
	nRet = media_folder_foreach_media_from_db(pszFolderId, NULL, ForeachMediaCb, TESTSTRING);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_foreach_media_from_db", MediaContentGetError(nRet), FREE_MEMORY(pszFolderId));
	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "media_folder_foreach_media_from_db", "CallBack Not Invoked", FREE_MEMORY(pszFolderId));

	FREE_MEMORY(pszFolderId);
	return 0;
}

/**
* @testcase 			ITc_media_folder_get_name_p
* @since_tizen			2.3
* @author				SRID(manoj.g2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Test media_folder_get_name
* @scenario				Call media_folder_get_name
* @apicovered			media_folder_get_name
* @passcase				When media_folder_get_name is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_folder_get_name
//& type: auto
int ITc_media_folder_get_name_p(void)
{
	START_TEST_PLAYLIST;
	char *pszFolderInfo = NULL;

	int nRet = media_folder_get_name(g_hFolder, &pszFolderInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_get_name", MediaContentGetError(nRet));
	CHECK_HANDLE(pszFolderInfo, "media_folder_get_name");

	FREE_MEMORY(pszFolderInfo);
	return 0;
}

/**
* @testcase 			ITc_media_folder_get_path_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_folder_get_path
* @scenario				Call media_folder_get_path
* @apicovered			media_folder_get_path
* @passcase				When media_folder_get_path is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_folder_get_path
//& type: auto
int ITc_media_folder_get_path_p(void)
{
	START_TEST_PLAYLIST;

	char *pszFolderInfo = NULL;
	int nRet = media_folder_get_path(g_hFolder, &pszFolderInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_get_path", MediaContentGetError(nRet));
	CHECK_HANDLE(pszFolderInfo, "media_folder_get_path");
	FREE_MEMORY(pszFolderInfo);

	return 0;
}

/**
* @testcase 			ITc_media_folder_get_folder_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_folder_get_folder_from_db
* @scenario				Call media_folder_get_folder_from_db
* @apicovered			media_folder_get_folder_from_db
* @passcase				When media_folder_get_folder_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_folder_get_folder_from_db
//& type: auto
int ITc_media_folder_get_folder_from_db_p(void)
{
	START_TEST_PLAYLIST;

	char *pszFolderId = NULL;
	int nRet = media_folder_get_folder_id(g_hFolder, &pszFolderId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_get_folder_id", MediaContentGetError(nRet));
	CHECK_HANDLE(pszFolderId, "media_folder_get_folder_id");

	media_folder_h hFolder = NULL;
	nRet = media_folder_get_folder_from_db(pszFolderId, &hFolder);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_get_folder_from_db", MediaContentGetError(nRet), FREE_MEMORY(pszFolderId));
	CHECK_HANDLE_CLEANUP(hFolder, "media_folder_get_folder_from_db", FREE_MEMORY(pszFolderId));

	nRet = media_folder_destroy(hFolder);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_folder_destroy", MediaContentGetError(nRet), FREE_MEMORY(pszFolderId));

	FREE_MEMORY(pszFolderId);
	return 0;
}


/** @} */
/** @} */
