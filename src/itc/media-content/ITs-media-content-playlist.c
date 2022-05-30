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
 * @function 		ForeachPlaylistCb
 * @description	 	Callback Function
 * @parameter		media_playlist_h playlist, void *user_data
 * @return 			NA
 */
static bool ForeachPlaylistCb(media_playlist_h playlist, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachPlaylistCb");
#endif

	char *pszPlaylistInfo = NULL;
	int nRet = media_playlist_get_name(playlist, &pszPlaylistInfo);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_name", MediaContentGetError(nRet), QuitGmainLoop());

	if((pszPlaylistInfo != NULL) && (strcmp(pszPlaylistInfo, PLAYLISTNAME) == 0))
	{
		nRet = media_playlist_clone(&g_hPlaylist, playlist);
		PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_clone", MediaContentGetError(nRet), FREE_MEMORY(pszPlaylistInfo); QuitGmainLoop());

		g_CallBackHit = true;
		FREE_MEMORY(pszPlaylistInfo);
		QuitGmainLoop();
		return false;
	}

	FREE_MEMORY(pszPlaylistInfo);
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

	media_content_type_e eMediaType = MEDIA_CONTENT_TYPE_OTHERS;
	int nRet = media_info_get_media_type(media, &eMediaType);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_type", MediaContentGetError(nRet), QuitGmainLoop());

	if(MEDIA_CONTENT_TYPE_MUSIC == eMediaType)
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

/**
 * @function 		ForeachPlaylistMemberCb
 * @description	 	Callback Function
 * @parameter		int playlist_member_id, media_info_h media, void *user_data
 * @return 			NA
 */
static bool ForeachPlaylistMemberCb(int playlist_member_id, media_info_h media, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachPlaylistMemberCb");
#endif

	g_nPlaylistMemberId = playlist_member_id;
	g_CallBackHit = true;
	QuitGmainLoop();
	return false;
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_media_content_playlist_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_playlist_startup(void)
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

	nRet = GetFolderPath(STORAGE_DIRECTORY_MUSIC, g_szAudioFolder);
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetFolderPath", "Return Value Not Correct", media_content_disconnect());
	CopyFileInfo("audio");

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

	AppendPaths(g_szAudioFolder, TESTAUDIO, g_szAudioPath);

	nRet = media_content_scan_file(g_szAudioPath);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());

	nRet = media_playlist_insert_to_db(PLAYLISTNAME, &g_hPlaylist);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());

	nRet = media_playlist_get_playlist_id(g_hPlaylist, &g_nPlaylistId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_insert_to_db", MediaContentGetError(nRet), media_playlist_destroy(g_hPlaylist); media_content_disconnect());

	g_CallBackHit = false;
	nRet = media_info_foreach_media_from_db(NULL, ForeachMediaCb, TESTSTRING);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_foreach_media_from_db", MediaContentGetError(nRet), media_playlist_delete_from_db(g_nPlaylistId); media_playlist_destroy(g_hPlaylist); media_content_disconnect());
	IterateGmainLoop();
	PRINT_RESULTNONE_CLEANUP(true, g_CallBackHit, "media_info_foreach_media_from_db", "CallBack Not Invoked", media_playlist_delete_from_db(g_nPlaylistId); media_playlist_destroy(g_hPlaylist); media_content_disconnect());

	nRet = media_playlist_add_media(g_hPlaylist, g_szMediaId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_add_media", MediaContentGetError(nRet), media_playlist_delete_from_db(g_nPlaylistId); media_playlist_destroy(g_hPlaylist); media_content_disconnect());

	nRet = media_playlist_update_to_db(g_hPlaylist);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_update_to_db", MediaContentGetError(nRet), media_playlist_delete_from_db(g_nPlaylistId); media_playlist_destroy(g_hPlaylist); media_content_disconnect());

	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_playlist_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_playlist_cleanup(void)
{
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
		media_playlist_delete_from_db(g_nPlaylistId);
		media_playlist_destroy(g_hPlaylist);
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
* @testcase 			ITc_media_playlist_get_playlist_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_get_playlist_count_from_db
* @scenario				Call media_playlist_get_playlist_count_from_db
* @apicovered			media_playlist_get_playlist_count_from_db
* @passcase				When media_playlist_get_playlist_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_get_playlist_count_from_db
//& type: auto
int ITc_media_playlist_get_playlist_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nCount = -1;
	int nRet = media_playlist_get_playlist_count_from_db(NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_playlist_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_playlist_get_playlist_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_playlist_foreach_playlist_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_foreach_playlist_from_db
* @scenario				Call media_playlist_foreach_playlist_from_db
* @apicovered			media_playlist_foreach_playlist_from_db
* @passcase				When media_playlist_foreach_playlist_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_foreach_playlist_from_db
//& type: auto
int ITc_media_playlist_foreach_playlist_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = media_playlist_destroy(g_hPlaylist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_destroy", MediaContentGetError(nRet));
	g_hPlaylist = NULL;

	g_CallBackHit = false;
	nRet = media_playlist_foreach_playlist_from_db(NULL, ForeachPlaylistCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_foreach_playlist_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_playlist_foreach_playlist_from_db", "CallBack Not Invoked");

	return 0;
}

/**
* @testcase 			ITc_media_playlist_clone_destroy_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_clone and media_playlist_destroy
* @scenario				Call media_playlist_clone and media_playlist_destroy
* @apicovered			media_playlist_clone, media_playlist_destroy
* @passcase				When media_playlist_clone and media_playlist_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_clone and media_playlist_destroy
//& type: auto
int ITc_media_playlist_clone_destroy_p(void)
{
	START_TEST_PLAYLIST;

	media_playlist_h hPlaylist = NULL;
	int nRet = media_playlist_clone(&hPlaylist, g_hPlaylist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hPlaylist, "media_playlist_clone");

	nRet = media_playlist_destroy(hPlaylist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_playlist_get_playlist_id_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_get_playlist_id
* @scenario				Call media_playlist_get_playlist_id
* @apicovered			media_playlist_get_playlist_id
* @passcase				When media_playlist_get_playlist_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_get_playlist_id
//& type: auto
int ITc_media_playlist_get_playlist_id_p(void)
{
	START_TEST_PLAYLIST;

	int nPlaylistId = -1;
	int nRet = media_playlist_get_playlist_id(g_hPlaylist, &nPlaylistId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_playlist_id", MediaContentGetError(nRet));
	CHECK_COUNT(nPlaylistId, "media_playlist_get_playlist_id");

	return 0;
}

/**
* @testcase 			ITc_media_playlist_get_media_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_get_media_count_from_db
* @scenario				Call media_playlist_get_media_count_from_db
* @apicovered			media_playlist_get_media_count_from_db
* @passcase				When media_playlist_get_media_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_get_media_count_from_db
//& type: auto
int ITc_media_playlist_get_media_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nPlaylistId = -1;
	int nRet = media_playlist_get_playlist_id(g_hPlaylist, &nPlaylistId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_playlist_id", MediaContentGetError(nRet));
	CHECK_COUNT(nPlaylistId, "media_playlist_get_playlist_id");

	int nCount = -1;
	nRet = media_playlist_get_media_count_from_db(nPlaylistId, NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_media_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_playlist_get_media_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_playlist_foreach_media_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_foreach_media_from_db
* @scenario				Call media_playlist_foreach_media_from_db
* @apicovered			media_playlist_foreach_media_from_db
* @passcase				When media_playlist_foreach_media_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_foreach_media_from_db
//& type: auto
int ITc_media_playlist_foreach_media_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nPlaylistId = -1;
	int nRet = media_playlist_get_playlist_id(g_hPlaylist, &nPlaylistId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_playlist_id", MediaContentGetError(nRet));
	CHECK_COUNT(nPlaylistId, "media_playlist_get_playlist_id");

	g_CallBackHit = false;
	nRet = media_playlist_foreach_media_from_db(nPlaylistId, NULL, ForeachPlaylistMemberCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_foreach_media_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_playlist_foreach_media_from_db", "CallBack Not Invoked");

	return 0;
}

/**
* @testcase 			ITc_media_playlist_set_get_name_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_set_name and media_playlist_get_name
* @scenario				Call media_playlist_set_name, media_playlist_get_name
* @apicovered			media_playlist_set_name, media_playlist_get_name
* @passcase				When media_playlist_set_name and media_playlist_get_name is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_set_name and media_playlist_get_name
//& type: auto
int ITc_media_playlist_set_get_name_p(void)
{
	START_TEST_PLAYLIST;
	char *pszPlaylistInfo = NULL;

	int nRet = media_playlist_set_name(g_hPlaylist, PLAYLISTNAME);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_set_name", MediaContentGetError(nRet));

	nRet = media_playlist_get_name(g_hPlaylist, &pszPlaylistInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_name", MediaContentGetError(nRet));
	CHECK_HANDLE(pszPlaylistInfo, "media_playlist_get_name");
	PRINT_RESULT_CLEANUP(0, strcmp(pszPlaylistInfo, PLAYLISTNAME), "media_playlist_get_name", "Playlist Name Mismatch", FREE_MEMORY(pszPlaylistInfo));

	FREE_MEMORY(pszPlaylistInfo);
	return 0;
}

/**
* @testcase 			ITc_media_playlist_get_playlist_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_get_playlist_from_db
* @scenario				Call media_playlist_get_playlist_from_db
* @apicovered			media_playlist_get_playlist_from_db
* @passcase				When media_playlist_get_playlist_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_get_playlist_from_db
//& type: auto
int ITc_media_playlist_get_playlist_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nPlaylistId = -1;
	int nRet = media_playlist_get_playlist_id(g_hPlaylist, &nPlaylistId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_playlist_id", MediaContentGetError(nRet));
	CHECK_COUNT(nPlaylistId, "media_playlist_get_playlist_id");

	media_playlist_h hPlaylist = NULL;
	nRet = media_playlist_get_playlist_from_db(nPlaylistId, &hPlaylist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_playlist_from_db", MediaContentGetError(nRet));
	CHECK_HANDLE(hPlaylist, "media_playlist_get_playlist_from_db");

	nRet = media_playlist_destroy(hPlaylist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_playlist_update_to_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_update_to_db
* @scenario				Call media_playlist_update_to_db
* @apicovered			media_playlist_update_to_db
* @passcase				When media_playlist_update_to_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_update_to_db
//& type: auto
int ITc_media_playlist_update_to_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = media_playlist_update_to_db(g_hPlaylist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_update_to_db", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_playlist_insert_delete_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_insert_to_db and media_playlist_delete_from_db
* @scenario				Call media_playlist_insert_to_db, media_playlist_delete_from_db
* @apicovered			media_playlist_insert_to_db, media_playlist_delete_from_db
* @passcase				When media_playlist_insert_to_db and media_playlist_delete_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_insert_to_db and media_playlist_delete_from_db
//& type: auto
int ITc_media_playlist_insert_delete_from_db_p(void)
{
	START_TEST_PLAYLIST;
	media_playlist_h hMediaPlaylist = NULL;
	int nPlaylistId = -1;

	int nRet = media_playlist_insert_to_db(PLAYLISTNAMENEW, &hMediaPlaylist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_insert_to_db", MediaContentGetError(nRet));

	nRet = media_playlist_get_playlist_id(hMediaPlaylist, &nPlaylistId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_playlist_id", MediaContentGetError(nRet));
	CHECK_COUNT(nPlaylistId, "media_playlist_get_playlist_id");

	nRet = media_playlist_delete_from_db(nPlaylistId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_delete_from_db", MediaContentGetError(nRet));

	nRet = media_playlist_destroy(hMediaPlaylist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_playlist_set_get_thumbnail_path_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_set_thumbnail_path and media_playlist_get_thumbnail_path
* @scenario				Call media_playlist_set_thumbnail_path, media_playlist_get_thumbnail_path
* @apicovered			media_playlist_set_thumbnail_path, media_playlist_get_thumbnail_path
* @passcase				When media_playlist_set_thumbnail_path and media_playlist_get_thumbnail_path is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_set_thumbnail_path and media_playlist_get_thumbnail_path
//& type: auto
int ITc_media_playlist_set_get_thumbnail_path_p(void)
{
	START_TEST_PLAYLIST;
	char *pszPlaylistInfo = NULL;

	int nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", "Return Value Not Correct");
	AppendPaths(g_szImageFolder, THUMBNAILIMAGE, g_szImagePath);

	nRet = media_content_scan_file(g_szImagePath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet));

	nRet = media_playlist_set_thumbnail_path(g_hPlaylist, g_szImagePath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_set_thumbnail_path", MediaContentGetError(nRet));

	nRet = media_playlist_get_thumbnail_path(g_hPlaylist, &pszPlaylistInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_thumbnail_path", MediaContentGetError(nRet));
	CHECK_HANDLE(pszPlaylistInfo, "media_playlist_get_thumbnail_path");
	PRINT_RESULT_CLEANUP(0, strcmp(pszPlaylistInfo, g_szImagePath), "media_playlist_get_thumbnail_path", "Playlist Name Mismatch", FREE_MEMORY(pszPlaylistInfo));

	FREE_MEMORY(pszPlaylistInfo);
	return 0;
}

/**
* @testcase 			ITc_media_playlist_add_remove_media_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_add_media and media_playlist_remove_media
* @scenario				Call media_playlist_add_media, media_playlist_remove_media
* @apicovered			media_playlist_add_media, media_playlist_remove_media
* @passcase				When media_playlist_add_media and media_playlist_remove_media is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_add_media and media_playlist_remove_media
//& type: auto
int ITc_media_playlist_add_remove_media_p(void)
{
	START_TEST_PLAYLIST;
	int nPlaylistId = -1;

	int nRet = media_playlist_get_playlist_id(g_hPlaylist, &nPlaylistId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_playlist_id", MediaContentGetError(nRet));
	CHECK_COUNT(nPlaylistId, "media_playlist_get_playlist_id");

	g_CallBackHit = false;
	nRet = media_playlist_foreach_media_from_db(nPlaylistId, NULL, ForeachPlaylistMemberCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_foreach_media_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_playlist_foreach_media_from_db", "CallBack Not Invoked");

	nRet = media_playlist_remove_media(g_hPlaylist, g_nPlaylistMemberId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_remove_media", MediaContentGetError(nRet));

	nRet = media_playlist_add_media(g_hPlaylist, g_szMediaId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_add_media", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_playlist_set_get_play_order_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_set_play_order and media_playlist_get_play_order
* @scenario				Call media_playlist_set_play_order, media_playlist_get_play_order
* @apicovered			media_playlist_set_play_order, media_playlist_get_play_order
* @passcase				When media_playlist_set_play_order and media_playlist_get_play_order is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_set_play_order and media_playlist_get_play_order
//& type: auto
int ITc_media_playlist_set_get_play_order_p(void)
{
	START_TEST_PLAYLIST;
	int nPlayOrder = -1;
	int nPlaylistId = -1;

	int nRet = media_playlist_get_playlist_id(g_hPlaylist, &nPlaylistId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_playlist_id", MediaContentGetError(nRet));
	CHECK_COUNT(nPlaylistId, "media_playlist_get_playlist_id");

	g_CallBackHit = false;
	nRet = media_playlist_foreach_media_from_db(nPlaylistId, NULL, ForeachPlaylistMemberCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_foreach_media_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_playlist_foreach_media_from_db", "CallBack Not Invoked");

	nRet = media_playlist_set_play_order(g_hPlaylist, g_nPlaylistMemberId, 1);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_set_play_order", MediaContentGetError(nRet));

	nRet = media_playlist_get_play_order(g_hPlaylist, g_nPlaylistMemberId, &nPlayOrder);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_play_order", MediaContentGetError(nRet));
	PRINT_RESULT(1, nPlayOrder, "media_playlist_get_play_order", "Playlist Order Mismatch");

	return 0;
}

/**
* @testcase 			ITc_media_playlist_import_export_to_file_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_playlist_import_from_file and media_playlist_export_to_file
* @scenario				Call media_playlist_import_from_file, media_playlist_export_to_file
* @apicovered			media_playlist_import_from_file, media_playlist_export_to_file
* @passcase				When media_playlist_import_from_file and media_playlist_export_to_file is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_playlist_import_from_file and media_playlist_export_to_file
//& type: auto
int ITc_media_playlist_import_export_to_file_p(void)
{
	START_TEST_PLAYLIST;
	int nPlaylistId = -1;
	media_playlist_h hMediaPlaylist = NULL;

	AppendPaths(g_szAudioFolder, TESTPLAYLIST, g_szPlayListPath);
	FPRINTF("[Line : %d][%s] g_szPlayListPath : %s\\n", __LINE__, API_NAMESPACE, g_szPlayListPath);
	int nRet = media_playlist_export_to_file(g_hPlaylist, g_szPlayListPath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_export_to_file", MediaContentGetError(nRet));

	nRet = media_playlist_import_from_file(g_szPlayListPath, PLAYLISTNAMENEW, &hMediaPlaylist);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_import_from_file", MediaContentGetError(nRet), remove(g_szPlayListPath));
	remove(g_szPlayListPath);

	nRet = media_playlist_get_playlist_id(hMediaPlaylist, &nPlaylistId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_get_playlist_id", MediaContentGetError(nRet));
	CHECK_COUNT(nPlaylistId, "media_playlist_get_playlist_id");

	nRet = media_playlist_delete_from_db(nPlaylistId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_delete_from_db", MediaContentGetError(nRet));

	nRet = media_playlist_destroy(hMediaPlaylist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_playlist_destroy", MediaContentGetError(nRet));

	return 0;
}

/** @} */
/** @} */
