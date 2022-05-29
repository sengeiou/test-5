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

media_info_h g_hInfo;

/** @addtogroup itc-media-content
*  @ingroup itc
*  @{
*/

/****************************************************Callback Start****************************************************/

/**
 * @function 		ForeachRecDateCb
 * @description	 	Callback Function
 * @parameter		media_info_h media, void *user_data
 * @return 			NA
 */
static bool ForeachRecDateCb(media_info_h media, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachRecDateCb");
#endif

	char *pszRecordedDate = NULL;
	char *pszFilePath = NULL;
	audio_meta_h audio;

	int nRet = media_info_get_file_path(media, &pszFilePath);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_file_path", MediaContentGetError(nRet), QuitGmainLoop());

	if (pszFilePath) 
	{
		if (strcmp(pszFilePath, g_szAudioPath) == 0)
		{
			nRet = media_info_get_audio(media, &audio);
			PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_audio", MediaContentGetError(nRet), FREE_MEMORY(pszFilePath);QuitGmainLoop());
			if (audio == NULL) 
			{
				FPRINTF("[Line : %d][%s] %s audio is NULL\\n", __LINE__, API_NAMESPACE, "media_info_get_audio");
				FREE_MEMORY(pszFilePath);
				return false;
			}

			nRet = audio_meta_get_recorded_date(audio, &pszRecordedDate);
			PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_recorded_date", MediaContentGetError(nRet), FREE_MEMORY(pszFilePath);QuitGmainLoop());
			if (strcmp(TESTKEYWORD, pszRecordedDate) == 0)
			{
				FPRINTF("[Line : %d][%s] %s value matches\\n", __LINE__, API_NAMESPACE, "audio_meta_get_recorded_date");
				g_CallBackHit = true;
				FREE_MEMORY(pszRecordedDate);
				QuitGmainLoop();
			}
			else 
			{
				FREE_MEMORY(pszRecordedDate);
				QuitGmainLoop();
			}
			FREE_MEMORY(pszFilePath);
			if(audio)
			{
				audio_meta_destroy(audio);
			}
			return false;
		}
		FREE_MEMORY(pszFilePath);
	} 
	else 
	{
		return false;
	}
	
	FREE_MEMORY(pszRecordedDate);
	return true;
	
}

/**
 * @function 		ForeachGenreCb
 * @description	 	Callback Function
 * @parameter		media_info_h media, void *user_data
 * @return 			NA
 */
static bool ForeachGenreCb(media_info_h media, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachGenreCb");
#endif

	char *pszGenre = NULL;
	char *pszFilePath = NULL;
	audio_meta_h audio;
	
	int nRet = media_info_get_file_path(media, &pszFilePath);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_file_path", MediaContentGetError(nRet), QuitGmainLoop());

	if (pszFilePath) 
	{
		if (strcmp(pszFilePath, g_szAudioPath) == 0)
		{
			nRet = media_info_get_audio(media, &audio);
			PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_audio", MediaContentGetError(nRet), FREE_MEMORY(pszFilePath);QuitGmainLoop());
			if (audio == NULL) 
			{
				FPRINTF("[Line : %d][%s] %s audio is NULL\\n", __LINE__, API_NAMESPACE, "media_info_get_audio");
				FREE_MEMORY(pszFilePath);
				return false;
			}
			nRet = audio_meta_get_genre(audio, &pszGenre);
			PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_genre", MediaContentGetError(nRet), FREE_MEMORY(pszFilePath);QuitGmainLoop());
			if (strcmp(TESTDESCRIPTION, pszGenre) == 0)
			{
				FPRINTF("[Line : %d][%s] %s value matches\\n", __LINE__, API_NAMESPACE, "audio_meta_get_genre");
				g_CallBackHit = true;
				FREE_MEMORY(pszGenre);
				QuitGmainLoop();
			}
			else 
			{
				FREE_MEMORY(pszGenre);
				QuitGmainLoop();
			}
			FREE_MEMORY(pszFilePath);
			if(audio)
			{
				audio_meta_destroy(audio);
			}
			return false;
		}
		FREE_MEMORY(pszFilePath);
	} 
	else 
	{
		FPRINTF("[Line : %d][%s] %s MEDIA_CONTENT_ERROR_INVALID_OPERATION\\n", __LINE__, API_NAMESPACE, "media_info_get_file_path");
		return false;
	}
	
	FREE_MEMORY(pszGenre);
	return true;
	
}

/**
 * @function 		ForeachArtistCb
 * @description	 	Callback Function
 * @parameter		media_info_h media, void *user_data
 * @return 			NA
 */
static bool ForeachArtistCb(media_info_h media, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachArtistCb");
#endif

	char *pszArtist = NULL;
	char *pszFilePath = NULL;
	audio_meta_h audio;
	
	int nRet = media_info_get_file_path(media, &pszFilePath);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_file_path", MediaContentGetError(nRet), QuitGmainLoop());
	
	if (pszFilePath) 
	{
		if (strcmp(pszFilePath, g_szAudioPath) == 0)
		{
			
			int nRet = media_info_get_audio(media, &audio);
			PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_audio", MediaContentGetError(nRet), FREE_MEMORY(pszFilePath);QuitGmainLoop());
			if (audio == NULL) 
			{
				FPRINTF("[Line : %d][%s] %s audio is NULL\\n", __LINE__, API_NAMESPACE, "media_info_get_audio");
				FREE_MEMORY(pszFilePath);
				return false;
			}
			nRet = audio_meta_get_artist(audio, &pszArtist);
			PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_artist", MediaContentGetError(nRet), FREE_MEMORY(pszFilePath);QuitGmainLoop());
			if (strcmp(TESTARTIST, pszArtist) == 0)
			{
				FPRINTF("[Line : %d][%s] %s value matches\\n", __LINE__, API_NAMESPACE, "audio_meta_get_artist");
				g_CallBackHit = true;
				FREE_MEMORY(pszArtist);
				QuitGmainLoop();
			}
			else 
			{
				FPRINTF("[Line : %d][%s] %s value not matched, \\n", __LINE__, API_NAMESPACE, "audio_meta_get_artist");
				FREE_MEMORY(pszArtist);
				QuitGmainLoop();
			}
			FREE_MEMORY(pszFilePath);
			if(audio)
			{
				audio_meta_destroy(audio);
			}
			return false;
		}

		FREE_MEMORY(pszFilePath);
	} 
	else 
	{
		FPRINTF("[Line : %d][%s] %s MEDIA_CONTENT_ERROR_INVALID_OPERATION\\n", __LINE__, API_NAMESPACE, "media_info_get_file_path");
		return false;
	}
	
	FREE_MEMORY(pszArtist);
	return true;
}

/**
 * @function 		ForeachAlbumCb
 * @description	 	Callback Function
 * @parameter		media_info_h media, void *user_data
 * @return 			NA
 */
static bool ForeachAlbumCb(media_info_h media, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachAlbumCb");
#endif

	char *pszAlbum = NULL;
	char *pszFilePath = NULL;
	audio_meta_h audio;

	int nRet = media_info_get_file_path(media, &pszFilePath);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_file_path", MediaContentGetError(nRet), QuitGmainLoop());
	
	if (pszFilePath) 
	{
		if (strcmp(pszFilePath, g_szAudioPath) == 0)
		{
			int nRet = media_info_get_audio(media, &audio);
			PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_audio", MediaContentGetError(nRet), FREE_MEMORY(pszFilePath);QuitGmainLoop());
			if (audio == NULL) 
			{
				FPRINTF("[Line : %d][%s] %s audio is NULL\\n", __LINE__, API_NAMESPACE, "media_info_get_audio");
				FREE_MEMORY(pszFilePath);
				return false;
			}
			nRet = audio_meta_get_album(audio, &pszAlbum);
			PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_album", MediaContentGetError(nRet), FREE_MEMORY(pszFilePath);QuitGmainLoop());
			if (strcmp(TESTAUDIO, pszAlbum) == 0)
			{
				FPRINTF("[Line : %d][%s] %s value matches\\n", __LINE__, API_NAMESPACE, "audio_meta_get_album");
				g_CallBackHit = true;
				FREE_MEMORY(pszAlbum);
				QuitGmainLoop();
			}
			else 
			{
				FPRINTF("[Line : %d][%s] %s value not matched, \\n", __LINE__, API_NAMESPACE, "audio_meta_get_album");
				FREE_MEMORY(pszAlbum);
				QuitGmainLoop();
			}
			FREE_MEMORY(pszFilePath);
			if(audio)
			{
				audio_meta_destroy(audio);
			}
			return false;
		}

		FREE_MEMORY(pszFilePath);
	} 
	else 
	{
		FPRINTF("[Line : %d][%s] %s MEDIA_CONTENT_ERROR_INVALID_OPERATION\\n", __LINE__, API_NAMESPACE, "media_info_get_file_path");
		return false;
	}
	
	FREE_MEMORY(pszAlbum);
	return true;
}

/**
 * @function 		ForeachTitleCb
 * @description	 	Callback Function
 * @parameter		media_info_h media, void *user_data
 * @return 			NA
 */
static bool ForeachTitleCb(media_info_h media, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachTitleCb");
#endif

	char *pszTitle = NULL;
	char *pszFilePath = NULL;

	int nRet = media_info_get_file_path(media, &pszFilePath);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_file_path", MediaContentGetError(nRet), QuitGmainLoop());
	
	if (pszFilePath) 
	{
		if (strcmp(pszFilePath, g_szVideoPath) == 0)
		{
			nRet = media_info_get_title(media, &pszTitle);
			PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_title", MediaContentGetError(nRet), FREE_MEMORY(pszFilePath);QuitGmainLoop());
			if (strcmp(TESTTITLE, pszTitle) == 0)
			{
				FPRINTF("[Line : %d][%s] %s value matches\\n", __LINE__, API_NAMESPACE, "media_info_get_title");
				g_CallBackHit = true;
				FREE_MEMORY(pszTitle);
				QuitGmainLoop();
			}
			else 
			{
				FPRINTF("[Line : %d][%s] %s value not matched, \\n", __LINE__, API_NAMESPACE, "media_info_get_title");
				FREE_MEMORY(pszTitle);
				QuitGmainLoop();
			}
			FREE_MEMORY(pszFilePath);
			return false;
		}

		FREE_MEMORY(pszFilePath);
	} 
	else 
	{
		FPRINTF("[Line : %d][%s] %s MEDIA_CONTENT_ERROR_INVALID_OPERATION\\n", __LINE__, API_NAMESPACE, "media_info_get_file_path");
		return false;
	}
	
	FREE_MEMORY(pszTitle);
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

/**
 * @function 		InsertBatchCb
 * @description	 	Callback Function
 * @parameter		media_content_error_e error, void *user_data
 * @return 			NA
 */
static void InsertBatchCb(media_content_error_e error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "InsertBatchCb");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
	return;
}

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

	int nRet = media_bookmark_get_bookmark_id(bookmark, &g_nBookmarkId);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_insert_to_db", MediaContentGetError(nRet), QuitGmainLoop());

	g_CallBackHit = true;
	QuitGmainLoop();
	return false;
}

/**
 * @function 		ForeachFaceCb
 * @description	 	Callback Function
 * @parameter		media_face_h face, void *user_data
 * @return 			NA
 */
static bool ForeachFaceCb(media_face_h face, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachFaceCb");
#endif

	int nRet = media_face_get_face_id(face,  &g_pszFaceId);
	PRINT_RESULTFALSE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_get_face_id", MediaContentGetError(nRet), QuitGmainLoop());

	g_CallBackHit = true;
	QuitGmainLoop();
	return false;
}

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

/*****************************************************Callback End*****************************************************/
/**
 * @function 		ITs_media_content_info_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_info_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	char *pszMediaId = NULL;
	g_hTextInfo = NULL;
	g_bMediaContentStartup = false;
	g_hAudioInfo = NULL;
	g_hImageInfo = NULL;
	g_hVideoInfo = NULL;
	g_hBookInfo = NULL;
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
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());

	AppendPaths(g_szAudioFolder, TESTAUDIO, g_szAudioPath);

	nRet = media_info_insert_to_db(g_szAudioPath, &g_hAudioInfo);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());
	nRet = media_info_get_media_id(g_hAudioInfo, &pszMediaId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet), media_content_disconnect());
	memset(g_szAudioId, 0, PATHLEN);
	strncpy(g_szAudioId, pszMediaId, PATHLEN - 1);
	FREE_MEMORY(pszMediaId);

	nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetFolderPath", "Return Value Not Correct", media_content_disconnect());
	CopyFileInfo("image");

	AppendPaths(g_szImageFolder, TESTIMAGE, g_szImagePath);
	nRet = media_info_insert_to_db(g_szImagePath, &g_hImageInfo);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());
	nRet = media_info_get_media_id(g_hImageInfo, &pszMediaId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet), media_content_disconnect());
	memset(g_szImageId, 0, PATHLEN);
	strncpy(g_szImageId, pszMediaId, PATHLEN - 1);
	FREE_MEMORY(pszMediaId);

	nRet = GetFolderPath(STORAGE_DIRECTORY_VIDEOS, g_szVideoFolder);
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetFolderPath", "Return Value Not Correct", media_content_disconnect());
	CopyFileInfo("video");

	AppendPaths(g_szVideoFolder, TESTVIDEO, g_szVideoPath);
	nRet = media_info_insert_to_db(g_szVideoPath, &g_hVideoInfo);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());
	nRet = media_info_get_media_id(g_hVideoInfo, &pszMediaId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet), media_content_disconnect());
	memset(g_szVideoId, 0, PATHLEN);
	strncpy(g_szVideoId, pszMediaId, PATHLEN - 1);
	FREE_MEMORY(pszMediaId);

	AppendPaths(g_szInternalStoragePath, TESTBOOK, g_szBookPath);
	nRet = media_info_insert_to_db(g_szBookPath, &g_hBookInfo);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_insert_to_db", MediaContentGetError(nRet), media_content_disconnect());

	g_bMediaContentStartup = true;

	return;
}

/**
 * @function 		ITs_media_content_info_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_info_cleanup(void)
{
	if(g_hTextInfo)
	{
		media_info_destroy(g_hTextInfo);
		g_hTextInfo = NULL;
	}
	if(g_hAudioInfo)
	{
		media_info_destroy(g_hAudioInfo);
		g_hAudioInfo = NULL;
	}
	if(g_hImageInfo)
	{
		media_info_destroy(g_hImageInfo);
		g_hImageInfo = NULL;
	}
	if(g_hVideoInfo)
	{
		media_info_destroy(g_hVideoInfo);
		g_hVideoInfo = NULL;
	}
	if(g_hBookInfo)
	{
		media_info_destroy(g_hBookInfo);
		g_hBookInfo = NULL;
	}
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
		if(g_szAudioPath)
		{
			RemoveFileInfo("audio");
			media_content_scan_file(g_szAudioPath);
		}
		if(g_szVideoPath)
		{
			RemoveFileInfo("video");
			media_content_scan_file(g_szVideoPath);
		}
		if(g_szImagePath)
		{
			RemoveFileInfo("image");
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
* @testcase 			ITc_media_info_get_media_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_media_count_from_db
* @scenario				Call media_info_get_media_count_from_db
* @apicovered			media_info_get_media_count_from_db
* @passcase				When media_info_get_media_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_media_count_from_db
//& type: auto
int ITc_media_info_get_media_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nCount = -1;
	int nRet = media_info_get_media_count_from_db(NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_info_get_media_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_info_foreach_media_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_foreach_media_from_db
* @scenario				Call media_info_foreach_media_from_db
* @apicovered			media_info_foreach_media_from_db
* @passcase				When media_info_foreach_media_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_foreach_media_from_db
//& type: auto
int ITc_media_info_foreach_media_from_db_p(void)
{
	START_TEST_PLAYLIST;

	g_CallBackHit = false;
	int nRet = media_info_foreach_media_from_db(NULL, ForeachMediaCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_foreach_media_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_info_foreach_media_from_db", "CallBack Not Invoked");

	return 0;
}

/**
* @testcase 			ITc_media_info_clone_destroy_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_clone and media_info_destroy
* @scenario				Call media_info_clone and media_info_destroy
* @apicovered			media_info_clone, media_info_destroy
* @passcase				When media_info_clone and media_info_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_clone and media_info_destroy
//& type: auto
int ITc_media_info_clone_destroy_p(void)
{
	START_TEST_PLAYLIST;

	media_info_h hInfo = NULL;
	int nRet = media_info_clone(&hInfo, g_hAudioInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hInfo, "media_info_clone");

	nRet = media_info_destroy(hInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_info_insert_to_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_insert_to_db
* @scenario				Call media_info_insert_to_db
* @apicovered			media_info_insert_to_db
* @passcase				When media_info_insert_to_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_insert_to_db
//& type: auto
int ITc_media_info_insert_to_db_p(void)
{
	START_TEST_PLAYLIST;
	char *pszMediaId = NULL;

	int nRet = media_info_destroy(g_hAudioInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_destroy", MediaContentGetError(nRet));

	RemoveFileInfo("audio");
	nRet = media_content_scan_file(g_szAudioPath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet));
	CopyFileInfo("audio");

	nRet = media_info_insert_to_db(g_szAudioPath, &g_hAudioInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_insert_to_db", MediaContentGetError(nRet));
	CHECK_HANDLE(g_hAudioInfo, "media_info_insert_to_db");

	nRet = media_info_get_media_id(g_hAudioInfo, &pszMediaId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet));
	memset(g_szAudioId, 0, PATHLEN);
	strncpy(g_szAudioId, pszMediaId, PATHLEN - 1);
	FREE_MEMORY(pszMediaId);

	return 0;
}

/**
* @testcase 			ITc_media_info_generate_thumbnail_p
* @since_tizen			5.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Test ITc_media_info_generate_thumbnail_p and media_info_get_thumbnail_path
* @scenario				Call ITc_media_info_generate_thumbnail_p and media_info_get_thumbnail_path
* @apicovered			ITc_media_info_generate_thumbnail_p, media_info_get_thumbnail_path
* @passcase				When media_info_generate_thumbnail and media_info_get_thumbnail_path is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_generate_thumbnail and media_info_get_thumbnail_path
//& type: auto
int ITc_media_info_generate_thumbnail_p(void)
{
	START_TEST_PLAYLIST;
	char *pszThumbNailPath = NULL;

	int nRet = media_info_generate_thumbnail(g_hAudioInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "ITc_media_info_generate_thumbnail_p", MediaContentGetError(nRet));

	nRet = media_info_get_thumbnail_path(g_hAudioInfo, &pszThumbNailPath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_thumbnail_path", MediaContentGetError(nRet));
	CHECK_HANDLE(pszThumbNailPath, "media_info_get_thumbnail_path");
	FREE_MEMORY(pszThumbNailPath);

	return 0;
}

/**
* @testcase 			ITc_media_info_insert_batch_to_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_insert_batch_to_db
* @scenario				call media_info_insert_batch_to_db
* @apicovered			media_info_insert_batch_to_db
* @passcase				When media_info_insert_batch_to_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test  media_info_insert_batch_to_db
//& type: auto
int ITc_media_info_insert_batch_to_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = media_info_destroy(g_hImageInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_destroy", MediaContentGetError(nRet));
	g_hImageInfo = NULL;

	RemoveFileInfo("image");
	nRet = media_content_scan_file(g_szImagePath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet));
	CopyFileInfo("image");

	nRet = media_info_destroy(g_hAudioInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_destroy", MediaContentGetError(nRet));
	g_hAudioInfo = NULL;

	RemoveFileInfo("audio");
	nRet = media_content_scan_file(g_szAudioPath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet));
	CopyFileInfo("audio");

	nRet = media_info_destroy(g_hVideoInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_destroy", MediaContentGetError(nRet));
	g_hVideoInfo = NULL;

	RemoveFileInfo("video");
	nRet = media_content_scan_file(g_szVideoPath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet));
	CopyFileInfo("video");

	const char* pszInsertPathList[3] = {g_szAudioPath, g_szImagePath, g_szVideoPath};
	g_CallBackHit = false;
	nRet = media_info_insert_batch_to_db(pszInsertPathList, sizeof(pszInsertPathList) / sizeof(pszInsertPathList[0]), InsertBatchCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_insert_batch_to_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_info_insert_batch_to_db", "CallBack Not Invoked");

	return 0;
}

/**
* @testcase 			ITc_media_info_foreach_bookmark_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_foreach_bookmark_from_db
* @scenario				Call media_info_foreach_bookmark_from_db
* @apicovered			media_info_foreach_bookmark_from_db
* @passcase				When media_info_foreach_bookmark_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_foreach_bookmark_from_db
//& type: auto
int ITc_media_info_foreach_bookmark_from_db_p(void)
{
	START_TEST_PLAYLIST;

	time_t stTime = {0};
	time(&stTime);
	int nRet = media_bookmark_insert_to_db(g_szVideoId, stTime, g_szImagePath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_insert_to_db", MediaContentGetError(nRet));

	g_CallBackHit = false;
	nRet = media_info_foreach_bookmark_from_db(g_szVideoId, NULL, ForeachBookmarkCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_foreach_bookmark_from_db", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_info_foreach_bookmark_from_db", "CallBack Not Invoked");

	nRet = media_bookmark_delete_from_db(g_nBookmarkId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_bookmark_delete_from_db", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_info_foreach_tag_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_foreach_tag_from_db
* @scenario				Call media_info_foreach_tag_from_db
* @apicovered			media_info_foreach_tag_from_db
* @passcase				When media_info_foreach_tag_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_foreach_tag_from_db
//& type: auto
int ITc_media_info_foreach_tag_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nTagId = -1;
	media_tag_h hMediaTag = NULL;
	int nRet = media_tag_insert_to_db(TAGNAMENEW, &hMediaTag);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_insert_to_db", MediaContentGetError(nRet));

	nRet = media_tag_get_tag_id(hMediaTag, &nTagId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_get_tag_id", MediaContentGetError(nRet));
	CHECK_COUNT(nTagId, "media_tag_get_tag_id");

	nRet = media_tag_add_media(hMediaTag, g_szVideoId);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_add_media", MediaContentGetError(nRet), media_tag_delete_from_db(nTagId); media_tag_destroy(hMediaTag));

	nRet = media_tag_update_to_db(hMediaTag);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_update_to_db", MediaContentGetError(nRet), media_tag_delete_from_db(nTagId); media_tag_destroy(hMediaTag));

	g_CallBackHit = false;
	nRet = media_info_foreach_tag_from_db(g_szVideoId, NULL, ForeachTagCb, TESTSTRING);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_foreach_tag_from_db", MediaContentGetError(nRet), media_tag_delete_from_db(nTagId); media_tag_destroy(hMediaTag));
	IterateGmainLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "media_info_foreach_tag_from_db", "CallBack Not Invoked", media_tag_delete_from_db(nTagId); media_tag_destroy(hMediaTag));

	nRet = media_tag_delete_from_db(nTagId);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_delete_from_db", MediaContentGetError(nRet), media_tag_destroy(hMediaTag));

	nRet = media_tag_destroy(hMediaTag);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_tag_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_info_get_bookmark_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_bookmark_count_from_db
* @scenario				Call media_info_get_bookmark_count_from_db
* @apicovered			media_info_get_bookmark_count_from_db
* @passcase				When media_info_get_bookmark_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_bookmark_count_from_db
//& type: auto
int ITc_media_info_get_bookmark_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nCount = -1;
	int nRet = media_info_get_bookmark_count_from_db(g_szVideoId, NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_bookmark_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_info_get_bookmark_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_info_get_tag_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_tag_count_from_db
* @scenario				Call media_info_get_tag_count_from_db
* @apicovered			media_info_get_tag_count_from_db
* @passcase				When media_info_get_tag_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_tag_count_from_db
//& type: auto
int ITc_media_info_get_tag_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nCount = -1;
	int nRet = media_info_get_tag_count_from_db(g_szVideoId, NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_tag_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_info_get_tag_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_info_update_to_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_update_to_db
* @scenario				Call media_info_update_to_db
* @apicovered			media_info_update_to_db
* @passcase				When media_info_update_to_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_update_to_db
//& type: auto
int ITc_media_info_update_to_db_p(void)
{
	START_TEST_PLAYLIST;

	int nRet = media_info_update_to_db(g_hAudioInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_update_to_db", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_info_get_media_id_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_media_id
* @scenario				Call media_info_get_media_id
* @apicovered			media_info_get_media_id
* @passcase				When media_info_get_media_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_media_id
//& type: auto
int ITc_media_info_get_media_id_p(void)
{
	START_TEST_PLAYLIST;

	char *pszAudioId = NULL;
	int nRet = media_info_get_media_id(g_hAudioInfo, &pszAudioId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet));
	CHECK_HANDLE(pszAudioId, "media_info_get_media_id");
	FREE_MEMORY(pszAudioId);

	return 0;
}

/**
* @testcase 			ITc_media_info_get_media_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_media_from_db
* @scenario				Call media_info_get_media_from_db
* @apicovered			media_info_get_media_from_db
* @passcase				When media_info_get_media_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_media_from_db
//& type: auto
int ITc_media_info_get_media_from_db_p(void)
{
	START_TEST_PLAYLIST;

	media_info_h hInfo = NULL;
	int nRet = media_info_get_media_from_db(g_szAudioId, &hInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_from_db", MediaContentGetError(nRet));
	CHECK_HANDLE(hInfo, "media_info_get_media_from_db");

	nRet = media_info_destroy(hInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_destroy", MediaContentGetError(nRet));
	return 0;
}

/**
* @testcase 			ITc_media_info_get_added_time_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_added_time
* @scenario				Call media_info_get_added_time
* @apicovered			media_info_get_added_time
* @passcase				When media_info_get_added_time is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_added_time
//& type: auto
int ITc_media_info_get_added_time_p(void)
{
	START_TEST_PLAYLIST;

	time_t stGetTime = {0};

	int nRet = media_info_get_added_time(g_hImageInfo, &stGetTime);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_added_time", MediaContentGetError(nRet));
	
	return 0;
}

/**
* @testcase 			ITc_media_info_get_altitude_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_altitude
* @scenario				Call media_info_get_altitude
* @apicovered			media_info_get_altitude
* @passcase				When media_info_get_altitude is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test  media_info_get_altitude
//& type: auto
int ITc_media_info_get_altitude_p(void)
{
	START_TEST_PLAYLIST;

	double dGetAltitude = 0;

	int nRet = media_info_get_altitude(g_hImageInfo, &dGetAltitude);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_altitude", MediaContentGetError(nRet));
	return 0;
}


/**
* @testcase 			ITc_media_info_get_description_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_description
* @scenario				Call media_info_get_description
* @apicovered			media_info_get_description
* @passcase				When media_info_get_description is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_description
//& type: auto
int ITc_media_info_get_description_p(void)
{
	START_TEST_PLAYLIST;

	char *pszDescription = NULL;

	int nRet = media_info_get_description(g_hVideoInfo, &pszDescription);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_description", MediaContentGetError(nRet));
	CHECK_HANDLE(pszDescription, "media_info_get_description");
	FREE_MEMORY(pszDescription);

	return 0;
}

/**
* @testcase 			ITc_media_info_get_display_name_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @display_name			Test media_info_get_display_name
* @scenario				Call media_info_get_display_name
* @apicovered			media_info_get_display_name
* @passcase				When media_info_get_display_name is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_display_name
//& type: auto
int ITc_media_info_get_display_name_p(void)
{
	START_TEST_PLAYLIST;

	char *pszDisplayName = NULL;

	int nRet = media_info_get_display_name(g_hVideoInfo, &pszDisplayName);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_display_name", MediaContentGetError(nRet));
	CHECK_HANDLE(pszDisplayName, "media_info_get_display_name");
	FREE_MEMORY(pszDisplayName);


	return 0;
}
/**
* @testcase 			ITc_media_info_set_get_favorite_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_set_favorite and media_info_get_favorite
* @scenario				Call media_info_set_favorite, media_info_get_favorite
* @apicovered			media_info_set_favorite, media_info_get_favorite
* @passcase				When media_info_set_favorite and media_info_get_favorite is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_set_favorite and media_info_get_favorite
//& type: auto
int ITc_media_info_set_get_favorite_p(void)
{
	START_TEST_PLAYLIST;

	bool bSetFavorite = true;
	bool bGetFavorite = false;

	int nRet = media_info_set_favorite(g_hAudioInfo, bSetFavorite);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_set_favorite", MediaContentGetError(nRet));

	nRet = media_info_get_favorite(g_hAudioInfo, &bGetFavorite);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_favorite", MediaContentGetError(nRet));
	PRINT_RESULT((int)bSetFavorite, (int)bGetFavorite, "media_info_get_favorite","Favorite Mismatch");

	return 0;
}

/**
* @testcase 			ITc_media_info_get_file_path_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_file_path
* @scenario				Call media_info_get_file_path
* @apicovered			media_info_get_file_path
* @passcase				When media_info_get_file_path is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_file_path
//& type: auto
int ITc_media_info_get_file_path_p(void)
{
	START_TEST_PLAYLIST;

	char *pszFilePath = NULL;
	int nRet = media_info_get_file_path(g_hVideoInfo, &pszFilePath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_file_path", MediaContentGetError(nRet));
	CHECK_HANDLE(pszFilePath, "media_info_get_file_path");
	FREE_MEMORY(pszFilePath);

	return 0;
}

/**
* @testcase 			ITc_media_info_get_image_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_image
* @scenario				Call media_info_get_image
* @apicovered			media_info_get_image
* @passcase				When media_info_get_image is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_image
//& type: auto
int ITc_media_info_get_image_p(void)
{
	START_TEST_PLAYLIST;

	image_meta_h hImage = NULL;
	int nRet = media_info_get_image(g_hImageInfo, &hImage);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_image", MediaContentGetError(nRet));
	CHECK_HANDLE(hImage, "media_info_get_image");

	nRet = image_meta_destroy(hImage);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "image_meta_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_info_get_audio_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_audio
* @scenario				Call media_info_get_audio
* @apicovered			media_info_get_audio
* @passcase				When media_info_get_audio is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_audio
//& type: auto
int ITc_media_info_get_audio_p(void)
{
	START_TEST_PLAYLIST;

	audio_meta_h hAudio = NULL;
	int nRet = media_info_get_audio(g_hAudioInfo, &hAudio);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_audio", MediaContentGetError(nRet));
	CHECK_HANDLE(hAudio, "media_info_get_audio");

	nRet = audio_meta_destroy(hAudio);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_info_get_video_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_video
* @scenario				Call media_info_get_video
* @apicovered			media_info_get_video
* @passcase				When media_info_get_video is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_video
//& type: auto
int ITc_media_info_get_video_p(void)
{
	START_TEST_PLAYLIST;

	video_meta_h hVideo = NULL;
	int nRet = media_info_get_video(g_hVideoInfo, &hVideo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_video", MediaContentGetError(nRet));
	CHECK_HANDLE(hVideo, "media_info_get_video");

	nRet = video_meta_destroy(hVideo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_info_get_modified_time_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_modified_time
* @scenario				Call media_info_get_modified_time
* @apicovered			media_info_get_modified_time
* @passcase				When media_info_get_modified_time is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_modified_time
//& type: auto
int ITc_media_info_get_modified_time_p(void)
{
	START_TEST_PLAYLIST;

	time_t stModifiedTime = {0};
	int nRet = media_info_get_modified_time(g_hVideoInfo, &stModifiedTime);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_modified_time", MediaContentGetError(nRet));
	CHECK_COUNT(stModifiedTime, "media_info_get_modified_time");

	return 0;
}

/**
* @testcase 			ITc_media_info_get_latitude_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_latitude
* @scenario				Call media_info_get_latitude
* @apicovered			media_info_get_latitude
* @passcase				When media_info_get_latitude is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_latitude
//& type: auto
int ITc_media_info_get_latitude_p(void)
{
	START_TEST_PLAYLIST;

	double dGetLatitude = 0;

	int nRet = media_info_get_latitude(g_hImageInfo, &dGetLatitude);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_latitude", MediaContentGetError(nRet));
	return 0;
}

/**
* @testcase 			ITc_media_info_get_longitude_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test  media_info_get_longitude
* @scenario				Call media_info_get_longitude
* @apicovered			 media_info_get_longitude
* @passcase				When media_info_get_longitude is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test  media_info_get_longitude
//& type: auto
int ITc_media_info_get_longitude_p(void)
{
	START_TEST_PLAYLIST;

	double dGetLongitude = 0;

	int nRet = media_info_get_longitude(g_hImageInfo, &dGetLongitude);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_longitude", MediaContentGetError(nRet));
	return 0;
}

/**
* @testcase 			ITc_media_info_get_rating_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_rating
* @scenario				Call media_info_get_rating
* @apicovered			media_info_get_rating
* @passcase				When media_info_get_rating is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_rating
//& type: auto
int ITc_media_info_get_rating_p(void)
{
	START_TEST_PLAYLIST;

	int nGetRating = 1;

	int nRet = media_info_get_rating(g_hAudioInfo, &nGetRating);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_rating", MediaContentGetError(nRet));
	return 0;
}
/**
* @testcase 			ITc_media_info_is_drm_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_is_drm
* @scenario				Call media_info_is_drm
* @apicovered			media_info_is_drm
* @passcase				When media_info_is_drm is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_is_drm
//& type: auto
int ITc_media_info_is_drm_p(void)
{
	START_TEST_PLAYLIST;

	bool bIsDrm = false;
	int nRet = media_info_is_drm(g_hVideoInfo, &bIsDrm);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_is_drm", MediaContentGetError(nRet));
	if(bIsDrm == false)
	{
	FPRINTF("[Line : %d][%s] bIsDrm is false \\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

/**
* @testcase 			ITc_media_info_get_media_type_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_media_type
* @scenario				Call media_info_get_media_type
* @apicovered			media_info_get_media_type
* @passcase				When media_info_get_media_type is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_media_type
//& type: auto
int ITc_media_info_get_media_type_p(void)
{
	START_TEST_PLAYLIST;

	media_content_type_e eMediaType = MEDIA_CONTENT_TYPE_OTHERS;
	int nRet = media_info_get_media_type(g_hVideoInfo, &eMediaType);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_type", MediaContentGetError(nRet));
	CHECK_COUNT(eMediaType, "media_info_get_media_type");

	return 0;
}

/**
* @testcase 			ITc_media_info_get_mime_type_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_mime_type
* @scenario				Call media_info_get_mime_type
* @apicovered			media_info_get_mime_type
* @passcase				When media_info_get_mime_type is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_mime_type
//& type: auto
int ITc_media_info_get_mime_type_p(void)
{
	START_TEST_PLAYLIST;

	char *pszMimeType = NULL;
	int nRet = media_info_get_mime_type(g_hVideoInfo, &pszMimeType);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_mime_type", MediaContentGetError(nRet));
	CHECK_HANDLE(pszMimeType, "media_info_get_mime_type");
	FREE_MEMORY(pszMimeType);

	return 0;
}

/**
* @testcase 			ITc_media_info_get_size_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_size
* @scenario				Call media_info_get_size
* @apicovered			media_info_get_size
* @passcase				When media_info_get_size is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_size
//& type: auto
int ITc_media_info_get_size_p(void)
{
	START_TEST_PLAYLIST;

	unsigned long long ullSize = 0;
	int nRet = media_info_get_size(g_hVideoInfo, &ullSize);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_size", MediaContentGetError(nRet));
	CHECK_VALUE_INT((int)ullSize, "media_info_get_size");

	return 0;
}

/**
* @testcase 			ITc_media_info_get_timeline_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_timeline
* @scenario				Call media_info_get_timeline
* @apicovered			media_info_get_timeline
* @passcase				When media_info_get_timeline is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_timeline
//& type: auto
int ITc_media_info_get_timeline_p(void)
{
	START_TEST_PLAYLIST;

	time_t stTimeline = 0;
	int nRet = media_info_get_timeline(g_hVideoInfo, &stTimeline);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_timeline", MediaContentGetError(nRet));
	CHECK_COUNT(stTimeline, "media_info_get_timeline");

	return 0;
}

/**
* @testcase 			ITc_media_info_get_title_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_title
* @scenario				Call media_info_get_title
* @apicovered			media_info_get_title
* @passcase				When media_info_get_title is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_title
//& type: auto
int ITc_media_info_get_title_p(void)
{
	START_TEST_PLAYLIST;

	char *pszTitle = NULL;
	int nRet = media_info_get_title(g_hVideoInfo, &pszTitle);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_title", MediaContentGetError(nRet));
	CHECK_HANDLE(pszTitle, "media_info_get_title");
	FREE_MEMORY(pszTitle);

	return 0;
}


/**
* @testcase 			ITc_media_info_move_to_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_move_to_db
* @scenario				Call media_info_move_to_db
* @apicovered			media_info_move_to_db
* @passcase				When media_info_move_to_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_move_to_db
//& type: auto
int ITc_media_info_move_to_db_p(void)
{
	START_TEST_PLAYLIST;

	RemoveFileInfo("audio");
	int nRet = media_content_scan_file(g_szAudioPath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet));

	nRet = media_info_move_to_db(g_hAudioInfo, g_szAudioPath);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_move_to_db", MediaContentGetError(nRet));

	return 0;
}


/**
* @testcase 			ITc_media_info_get_face_count_from_db_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_get_face_count_from_db
* @scenario				Call media_info_get_face_count_from_db
* @apicovered			media_info_get_face_count_from_db
* @passcase				When media_info_get_face_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_face_count_from_db
//& type: auto
int ITc_media_info_get_face_count_from_db_p(void)
{
	START_TEST_PLAYLIST;
	
	int nCount = -1;
	int nRet = media_info_get_face_count_from_db(g_szVideoId, NULL, &nCount);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_face_count_from_db", MediaContentGetError(nRet));
	CHECK_COUNT(nCount, "media_info_get_face_count_from_db");

	return 0;
}

/**
* @testcase 			ITc_media_info_foreach_face_from_db_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_info_foreach_face_from_db
* @scenario				Call media_info_foreach_face_from_db
* @apicovered			media_info_foreach_face_from_db
* @passcase				When media_info_foreach_face_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_foreach_face_from_db
//& type: auto
int ITc_media_info_foreach_face_from_db_p(void)
{
	START_TEST_PLAYLIST;
	
	int nRet = media_face_create(g_szImageId,&g_hFace);		
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_create", MediaContentGetError(nRet));
	CHECK_HANDLE(g_hFace, "media_face_create");	
		
	nRet = media_face_set_face_rect(g_hFace, 20, 22, 70, 70);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_face_rect", MediaContentGetError(nRet), media_face_destroy(g_hFace));
	
	nRet = media_face_set_orientation(g_hFace, 3);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_orientation", MediaContentGetError(nRet), media_face_destroy(g_hFace));
	
	nRet = media_face_set_tag(g_hFace, NULL);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_set_tag", MediaContentGetError(nRet), media_face_destroy(g_hFace));
	
	nRet = media_face_insert_to_db(g_hFace);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_insert_to_db", MediaContentGetError(nRet),media_face_destroy(g_hFace));
	
	g_CallBackHit = false;
	nRet = media_info_foreach_face_from_db(g_szImageId, NULL, ForeachFaceCb, TESTSTRING);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_foreach_face_from_db", MediaContentGetError(nRet),media_face_destroy(g_hFace));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_info_foreach_face_from_db", "CallBack Not Invoked");

	nRet = media_face_destroy(g_hFace);
	PRINT_RESULT_NORETURN(MEDIA_CONTENT_ERROR_NONE, nRet, "media_face_destroy", MediaContentGetError(nRet));
	
	return 0;
}


/**
* @testcase 			ITc_media_info_is_360_content_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer				SRID(shilpa.j)
* @type 				auto
* @description			Test media_info_is_360_content
* @scenario				Call media_info_is_360_content
* @apicovered			media_info_is_360_content
* @passcase				When media_info_is_360_content is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_is_360_content
//& type: auto
int ITc_media_info_is_360_content_p(void)
{
	START_TEST_PLAYLIST;
	
	bool bIs360 = false;
	int nRet = media_info_is_360_content(g_hVideoInfo, &bIs360);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_is_360_content", MediaContentGetError(nRet));
	if(bIs360 == false)
	{
		FPRINTF("[Line : %d][%s] bIs360 is false \\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

/**
* @testcase 			ITc_media_info_get_media_from_db_by_path_p
* @since_tizen			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(manu.tiwari)
* @type 				auto
* @description			Test media_info_get_media_from_db_by_path
* @scenario				Call media_info_get_media_from_db_by_path
* @apicovered			media_info_get_media_from_db_by_path
* @passcase				When media_info_get_media_from_db_by_path is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_info_get_media_from_db_by_path
//& type: auto
int ITc_media_info_get_media_from_db_by_path_p(void)
{
	START_TEST_PLAYLIST;

	media_info_h hInfo = NULL;

	int nRet = media_info_get_media_from_db_by_path(g_szAudioPath, &hInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_from_db_by_path", MediaContentGetError(nRet));
	CHECK_HANDLE(hInfo, "media_info_get_media_from_db_by_path");

	nRet = media_info_destroy(hInfo);
	PRINT_RESULT_NORETURN(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
 * @testcase		ITc_media_info_get_book_p
 * @since_tizen 	6.5
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		media_info_get_book
 * @apicovered          media_info_get_book
 * @passcase		MEDIA_CONTENT_ERROR_NONE returned by media_info_get_book
 * @failcase		MEDIA_CONTENT_ERROR_NONE not returned by media_info_get_book
 * @precondition	NA
 * @postcondition	NA
 */
 
int ITc_media_info_get_book_p(void)
{
	START_TEST_PLAYLIST;

	book_meta_h hInfoBook = NULL;
	media_info_h hInfo = NULL;

	int nRet = media_info_clone(&hInfo, g_hBookInfo);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hInfo, "media_info_clone");

	//Target API
	nRet = media_info_get_book(hInfo, &hInfoBook);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_book", MediaContentGetError(nRet), media_info_destroy(hInfo));
	CHECK_HANDLE_CLEANUP(hInfoBook, "media_info_get_book", media_info_destroy(hInfo));

	nRet = book_meta_destroy(hInfoBook);
	PRINT_RESULT_NORETURN(MEDIA_CONTENT_ERROR_NONE, nRet, "book_meta_destroy", MediaContentGetError(nRet));

	nRet = media_info_destroy(hInfo);
	PRINT_RESULT_NORETURN(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_destroy", MediaContentGetError(nRet));

	return 0;
}
/** @} */
/** @} */
