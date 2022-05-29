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
 * @function 		ForeachAlbumCb
 * @description	 	Callback Function
 * @parameter		media_album_h album, void *user_data
 * @return 			NA
 */
static bool ForeachAlbumCb(media_album_h album, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachAlbumCb");
#endif

	char *pszAlbumInfo = NULL;
	int nRet = media_album_get_name(album, &pszAlbumInfo);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_name", MediaContentGetError(nRet), QuitGmainLoop());

	if((pszAlbumInfo != NULL) && (strcmp(pszAlbumInfo, ALBUMNAME) == 0))
	{
		nRet = media_album_clone(&g_hAlbum, album);
		PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_clone", MediaContentGetError(nRet), FREE_MEMORY(pszAlbumInfo); QuitGmainLoop());

		g_CallBackHit = true;
		FREE_MEMORY(pszAlbumInfo);
		QuitGmainLoop();
		return false;
	}

	FREE_MEMORY(pszAlbumInfo);
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
 * @function 		ITs_media_content_album_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_album_startup(void)
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

	AppendPaths(g_szInternalStoragePath, TESTAUDIO, g_szAudioPath);
	nRet = media_content_scan_file(g_szAudioPath);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());

	g_CallBackHit = false;
	nRet = media_album_foreach_album_from_db(NULL, ForeachAlbumCb, TESTSTRING);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_foreach_album_from_db", MediaContentGetError(nRet), media_content_disconnect());
	IterateGmainLoop();
	PRINT_RESULTNONE_CLEANUP(true, g_CallBackHit, "media_album_foreach_album_from_db", "CallBack Not Invoked", media_content_disconnect());

	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_album_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_album_cleanup(void)
{
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
		media_album_destroy(g_hAlbum);
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
* @testcase 			ITc_media_album_get_album_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_album_get_album_count_from_db
* @scenario				Call media_album_get_album_count_from_db
* @apicovered			media_album_get_album_count_from_db
* @passcase				When media_album_get_album_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_album_get_album_count_from_db
//& type: auto
int ITc_media_album_get_album_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nCount = -1;
	int nRet = media_album_get_album_count_from_db(NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_album_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_album_get_album_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_album_foreach_album_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_album_foreach_album_from_db
* @scenario				Call media_album_foreach_album_from_db
* @apicovered			media_album_foreach_album_from_db
* @passcase				When media_album_foreach_album_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_album_foreach_album_from_db
//& type: auto
int ITc_media_album_foreach_album_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = media_album_destroy(g_hAlbum);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_destroy", MediaContentGetError(nRet));
	g_hAlbum = NULL;

	g_CallBackHit = false;
	nRet = media_album_foreach_album_from_db(NULL, ForeachAlbumCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_foreach_album_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_album_foreach_album_from_db", "CallBack Not Invoked");

	return 0;
}

/**
* @testcase 			ITc_media_album_clone_destroy_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_album_clone and media_album_destroy
* @scenario				Call media_album_clone and media_album_destroy
* @apicovered			media_album_clone, media_album_destroy
* @passcase				When media_album_clone and media_album_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_album_clone and media_album_destroy
//& type: auto
int ITc_media_album_clone_destroy_p(void)
{
	START_TEST_PLAYLIST;

	media_album_h hAlbum = NULL;
	int nRet = media_album_clone(&hAlbum, g_hAlbum);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hAlbum, "media_album_clone");

	nRet = media_album_destroy(hAlbum);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_album_get_album_id_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_album_get_album_id
* @scenario				Call media_album_get_album_id
* @apicovered			media_album_get_album_id
* @passcase				When media_album_get_album_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_album_get_album_id
//& type: auto
int ITc_media_album_get_album_id_p(void)
{
	START_TEST_PLAYLIST;

	int nAlbumId = -1;
	int nRet = media_album_get_album_id(g_hAlbum, &nAlbumId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_album_id", MediaContentGetError(nRet));
	CHECK_COUNT(nAlbumId, "media_album_get_album_id");

	return 0;
}

/**
* @testcase 			ITc_media_album_get_media_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_album_get_media_count_from_db
* @scenario				Call media_album_get_media_count_from_db
* @apicovered			media_album_get_media_count_from_db
* @passcase				When media_album_get_media_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_album_get_media_count_from_db
//& type: auto
int ITc_media_album_get_media_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nAlbumId = -1;
	int nRet = media_album_get_album_id(g_hAlbum, &nAlbumId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_album_id", MediaContentGetError(nRet));
	CHECK_COUNT(nAlbumId, "media_album_get_album_id");

	int nCount = -1;
	nRet = media_album_get_media_count_from_db(nAlbumId, NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_media_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_album_get_media_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_album_foreach_media_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_album_foreach_media_from_db
* @scenario				Call media_album_foreach_media_from_db
* @apicovered			media_album_foreach_media_from_db
* @passcase				When media_album_foreach_media_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_album_foreach_media_from_db
//& type: auto
int ITc_media_album_foreach_media_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nAlbumId = -1;
	int nRet = media_album_get_album_id(g_hAlbum, &nAlbumId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_album_id", MediaContentGetError(nRet));
	CHECK_COUNT(nAlbumId, "media_album_get_album_id");

	g_CallBackHit = false;
	nRet = media_album_foreach_media_from_db(nAlbumId, NULL, ForeachMediaCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_foreach_media_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_album_foreach_media_from_db", "CallBack Not Invoked");

	return 0;
}

/**
* @testcase 			ITc_media_album_get_name_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_album_get_name
* @scenario				Call media_album_get_name
* @apicovered			media_album_get_name
* @passcase				When media_album_get_name is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_album_get_name
//& type: auto
int ITc_media_album_get_name_p(void)
{
	START_TEST_PLAYLIST;

	char *pszAlbumInfo = NULL;
	int nRet = media_album_get_name(g_hAlbum, &pszAlbumInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_name", MediaContentGetError(nRet));
	CHECK_HANDLE(pszAlbumInfo, "media_album_get_name");
	FREE_MEMORY(pszAlbumInfo);

	return 0;
}

/**
* @testcase 			ITc_media_album_get_artist_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_album_get_artist
* @scenario				Call media_album_get_artist
* @apicovered			media_album_get_artist
* @passcase				When media_album_get_artist is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_album_get_artist
//& type: auto
int ITc_media_album_get_artist_p(void)
{
	START_TEST_PLAYLIST;

	char *pszAlbumInfo = NULL;
	int nRet = media_album_get_artist(g_hAlbum, &pszAlbumInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_artist", MediaContentGetError(nRet));
	CHECK_HANDLE(pszAlbumInfo, "media_album_get_artist");
	FREE_MEMORY(pszAlbumInfo);

	return 0;
}

/**
* @testcase 			ITc_media_album_get_album_art_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_album_get_album_art
* @scenario				Call media_album_get_album_art
* @apicovered			media_album_get_album_art
* @passcase				When media_album_get_album_art is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_album_get_album_art
//& type: auto
int ITc_media_album_get_album_art_p(void)
{
	START_TEST_PLAYLIST;

	char *pszAlbumInfo = NULL;
	int nRet = media_album_get_album_art(g_hAlbum, &pszAlbumInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_album_art", MediaContentGetError(nRet));
	CHECK_HANDLE(pszAlbumInfo, "media_album_get_album_art");
	FREE_MEMORY(pszAlbumInfo);

	return 0;
}

/**
* @testcase 			ITc_media_album_get_album_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_album_get_album_from_db
* @scenario				Call media_album_get_album_from_db
* @apicovered			media_album_get_album_from_db
* @passcase				When media_album_get_album_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_album_get_album_from_db
//& type: auto
int ITc_media_album_get_album_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nAlbumId = -1;
	int nRet = media_album_get_album_id(g_hAlbum, &nAlbumId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_album_id", MediaContentGetError(nRet));
	CHECK_COUNT(nAlbumId, "media_album_get_album_id");

	media_album_h hAlbum = NULL;
	nRet = media_album_get_album_from_db(nAlbumId, &hAlbum);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_get_album_from_db", MediaContentGetError(nRet));
	CHECK_HANDLE(hAlbum, "media_album_get_album_from_db");

	nRet = media_album_destroy(hAlbum);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_album_destroy", MediaContentGetError(nRet));

	return 0;
}

/** @} */
/** @} */
