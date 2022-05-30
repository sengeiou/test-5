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

/**
 * @function 		ITs_media_content_video_meta_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_video_meta_startup(void)
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

	nRet = GetFolderPath(STORAGE_DIRECTORY_VIDEOS, g_szVideoFolder);
	PRINT_RESULTNONE_CLEANUP(0, nRet, "GetFolderPath", "Return Value Not Correct", media_content_disconnect());
	CopyFileInfo("video");

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

	AppendPaths(g_szVideoFolder, TESTVIDEO, g_szVideoPath);
	nRet = media_info_insert_to_db(g_szVideoPath, &g_hVideoInfo);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());
	nRet = media_info_get_media_id(g_hVideoInfo, &pszMediaId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet), media_content_disconnect());
	memset(g_szVideoId, 0, PATHLEN);
	strncpy(g_szVideoId, pszMediaId, PATHLEN - 1);
	FREE_MEMORY(pszMediaId);

	nRet = media_info_get_video(g_hVideoInfo, &g_hVideoMeta);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_video", MediaContentGetError(nRet), media_content_disconnect());

	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_video_meta_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_video_meta_cleanup(void)
{
	if(g_hTextInfo)
	{
		media_info_destroy(g_hTextInfo);
	}
	if(g_hVideoMeta)
	{
		video_meta_destroy(g_hVideoMeta);
	}
	if(g_hVideoInfo)
	{
		media_info_destroy(g_hVideoInfo);
	}
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
		struct stat stBuff;
		if ( stat("video", &stBuff) == 0 )
		{
			if (remove("video"))
			{
				FPRINTF("[Line : %d][%s] TEST SUIT clean-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
			}
		}
		if(g_szVideoPath)
		{
			media_content_scan_file(g_szVideoPath);
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
* @testcase 			ITc_video_meta_clone_destroy_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_clone and video_meta_destroy
* @scenario				Call video_meta_clone and video_meta_destroy
* @apicovered			video_meta_clone, video_meta_destroy
* @passcase				When video_meta_clone and video_meta_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_clone and video_meta_destroy
//& type: auto
int ITc_video_meta_clone_destroy_p(void)
{
	START_TEST_PLAYLIST;

	video_meta_h hVideoMeta = NULL;
	int nRet = video_meta_clone(&hVideoMeta, g_hVideoMeta);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hVideoMeta, "video_meta_clone");

	nRet = video_meta_destroy(hVideoMeta);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_album_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_album
* @scenario				Call video_meta_get_album
* @apicovered			video_meta_get_album
* @passcase				When video_meta_get_album is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_album
//& type: auto
int ITc_video_meta_get_album_p(void)
{
	START_TEST_PLAYLIST;

	char *pszAlbum = NULL;
	int nRet = video_meta_get_album(g_hVideoMeta, &pszAlbum);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_album", MediaContentGetError(nRet));
	CHECK_HANDLE(pszAlbum, "video_meta_get_album");
	FREE_MEMORY(pszAlbum);

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_album_artist_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_album_artist
* @scenario				Call video_meta_get_album_artist
* @apicovered			video_meta_get_album_artist
* @passcase				When video_meta_get_album_artist is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_album_artist
//& type: auto
int ITc_video_meta_get_album_artist_p(void)
{
	START_TEST_PLAYLIST;

	char *pszAlbumArtist = NULL;
	int nRet = video_meta_get_album_artist(g_hVideoMeta, &pszAlbumArtist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_album_artist", MediaContentGetError(nRet));
	CHECK_HANDLE(pszAlbumArtist, "video_meta_get_album_artist");
	FREE_MEMORY(pszAlbumArtist);

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_artist_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_artist
* @scenario				Call video_meta_get_artist
* @apicovered			video_meta_get_artist
* @passcase				When video_meta_get_artist is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_artist
//& type: auto
int ITc_video_meta_get_artist_p(void)
{
	START_TEST_PLAYLIST;

	char *pszArtist = NULL;
	int nRet = video_meta_get_artist(g_hVideoMeta, &pszArtist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_artist", MediaContentGetError(nRet));
	CHECK_HANDLE(pszArtist, "video_meta_get_artist");
	FREE_MEMORY(pszArtist);

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_bit_rate_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_bit_rate
* @scenario				Call video_meta_get_bit_rate
* @apicovered			video_meta_get_bit_rate
* @passcase				When video_meta_get_bit_rate is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_bit_rate
//& type: auto
int ITc_video_meta_get_bit_rate_p(void)
{
	START_TEST_PLAYLIST;

	int nBitRate = 0;
	int nRet = video_meta_get_bit_rate(g_hVideoMeta, &nBitRate);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_bit_rate", MediaContentGetError(nRet));
	CHECK_COUNT(nBitRate, "video_meta_get_bit_rate");

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_composer_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_composer
* @scenario				Call video_meta_get_composer
* @apicovered			video_meta_get_composer
* @passcase				When video_meta_get_composer is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_composer
//& type: auto
int ITc_video_meta_get_composer_p(void)
{
	START_TEST_PLAYLIST;

	char *pszComposer = NULL;
	int nRet = video_meta_get_composer(g_hVideoMeta, &pszComposer);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_composer", MediaContentGetError(nRet));
	CHECK_HANDLE(pszComposer, "video_meta_get_composer");
	FREE_MEMORY(pszComposer);

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_copyright_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_copyright
* @scenario				Call video_meta_get_copyright
* @apicovered			video_meta_get_copyright
* @passcase				When video_meta_get_copyright is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_copyright
//& type: auto
int ITc_video_meta_get_copyright_p(void)
{
	START_TEST_PLAYLIST;

	char *pszCopyright = NULL;
	int nRet = video_meta_get_copyright(g_hVideoMeta, &pszCopyright);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_copyright", MediaContentGetError(nRet));
	CHECK_HANDLE(pszCopyright, "video_meta_get_copyright");
	FREE_MEMORY(pszCopyright);

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_duration_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_duration
* @scenario				Call video_meta_get_duration
* @apicovered			video_meta_get_duration
* @passcase				When video_meta_get_duration is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_duration
//& type: auto
int ITc_video_meta_get_duration_p(void)
{
	START_TEST_PLAYLIST;

	int nDuration = 0;
	int nRet = video_meta_get_duration(g_hVideoMeta, &nDuration);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_duration", MediaContentGetError(nRet));
	CHECK_COUNT(nDuration, "video_meta_get_duration");

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_genre_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_genre
* @scenario				Call video_meta_get_genre
* @apicovered			video_meta_get_genre
* @passcase				When video_meta_get_genre is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_genre
//& type: auto
int ITc_video_meta_get_genre_p(void)
{
	START_TEST_PLAYLIST;

	char *pszGenre = NULL;
	int nRet = video_meta_get_genre(g_hVideoMeta, &pszGenre);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_genre", MediaContentGetError(nRet));
	CHECK_HANDLE(pszGenre, "video_meta_get_genre");
	FREE_MEMORY(pszGenre);

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_media_id_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_media_id
* @scenario				Call video_meta_get_media_id
* @apicovered			video_meta_get_media_id
* @passcase				When video_meta_get_media_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_media_id
//& type: auto
int ITc_video_meta_get_media_id_p(void)
{
	START_TEST_PLAYLIST;

	char *pszMediaId = NULL;
	int nRet = video_meta_get_media_id(g_hVideoMeta, &pszMediaId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_media_id", MediaContentGetError(nRet));
	CHECK_HANDLE(pszMediaId, "video_meta_get_media_id");
	FREE_MEMORY(pszMediaId);

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_recorded_date_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_recorded_date
* @scenario				Call video_meta_get_recorded_date
* @apicovered			video_meta_get_recorded_date
* @passcase				When video_meta_get_recorded_date is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_recorded_date
//& type: auto
int ITc_video_meta_get_recorded_date_p(void)
{
	START_TEST_PLAYLIST;

	char *pszRecordedDate = NULL;
	int nRet = video_meta_get_recorded_date(g_hVideoMeta, &pszRecordedDate);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_recorded_date", MediaContentGetError(nRet));
	CHECK_HANDLE(pszRecordedDate, "video_meta_get_recorded_date");
	FREE_MEMORY(pszRecordedDate);

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_track_num_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_track_num
* @scenario				Call video_meta_get_track_num
* @apicovered			video_meta_get_track_num
* @passcase				When video_meta_get_track_num is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_track_num
//& type: auto
int ITc_video_meta_get_track_num_p(void)
{
	START_TEST_PLAYLIST;

	char *pszTrackNum = NULL;
	int nRet = video_meta_get_track_num(g_hVideoMeta, &pszTrackNum);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_track_num", MediaContentGetError(nRet));
	CHECK_HANDLE(pszTrackNum, "video_meta_get_track_num");
	FREE_MEMORY(pszTrackNum);

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_year_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_year
* @scenario				Call video_meta_get_year
* @apicovered			video_meta_get_year
* @passcase				When video_meta_get_year is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_year
//& type: auto
int ITc_video_meta_get_year_p(void)
{
	START_TEST_PLAYLIST;

	char *pszYear = NULL;
	int nRet = video_meta_get_year(g_hVideoMeta, &pszYear);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_year", MediaContentGetError(nRet));
	CHECK_HANDLE(pszYear, "video_meta_get_year");
	FREE_MEMORY(pszYear);

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_height_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_height
* @scenario				Call video_meta_get_height
* @apicovered			video_meta_get_height
* @passcase				When video_meta_get_height is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_height
//& type: auto
int ITc_video_meta_get_height_p(void)
{
	START_TEST_PLAYLIST;

	int nHeight = 0;
	int nRet = video_meta_get_height(g_hVideoMeta, &nHeight);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_height", MediaContentGetError(nRet));
	CHECK_COUNT(nHeight, "video_meta_get_height");

	return 0;
}

/**
* @testcase 			ITc_video_meta_get_width_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test video_meta_get_width
* @scenario				Call video_meta_get_width
* @apicovered			video_meta_get_width
* @passcase				When video_meta_get_width is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test video_meta_get_width
//& type: auto
int ITc_video_meta_get_width_p(void)
{
	START_TEST_PLAYLIST;

	int nWidth = 0;
	int nRet = video_meta_get_width(g_hVideoMeta, &nWidth);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_width", MediaContentGetError(nRet));
	CHECK_COUNT(nWidth, "video_meta_get_width");

	return 0;
}

//& purpose: Test video_meta_get_rotation
//& type: auto
/**
* @testcase 			ITc_video_meta_get_rotation_p
* @since_tizen			4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Test video_meta_get_rotation
* @scenario				Call video_meta_get_rotation
* @apicovered			video_meta_get_rotation
* @passcase				When video_meta_get_rotation is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_video_meta_get_rotation_p(void)
{
	START_TEST_PLAYLIST;

	int nRotation = 0;
	int nRet = video_meta_get_rotation(g_hVideoMeta, &nRotation);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "video_meta_get_rotation", MediaContentGetError(nRet));
	if(nRotation < 0 || nRotation >= 360)
	{
		FPRINTF("[Line: %d][%s] nRotation value returned is %d not correct\\n", __LINE__, API_NAMESPACE,nRotation);
		return 1;
	}

	return 0;
}
/** @} */
/** @} */
