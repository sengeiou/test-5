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
 * @function 		ITs_media_content_audio_meta_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_audio_meta_startup(void)
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
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());
	AppendPaths(g_szAudioFolder, TESTAUDIO, g_szAudioPath);
	nRet = media_info_insert_to_db(g_szAudioPath, &g_hAudioInfo);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());
	nRet = media_info_get_media_id(g_hAudioInfo, &pszMediaId);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_media_id", MediaContentGetError(nRet), media_content_disconnect());
	memset(g_szAudioId, 0, PATHLEN);
	strncpy(g_szAudioId, pszMediaId, PATHLEN-1);
	FREE_MEMORY(pszMediaId);

	nRet = media_info_get_audio(g_hAudioInfo, &g_hAudioMeta);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_info_get_audio", MediaContentGetError(nRet), media_content_disconnect());

	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_audio_meta_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_audio_meta_cleanup(void)
{
	if(g_hTextInfo)
	{
		media_info_destroy(g_hTextInfo);
	}
	if(g_hAudioMeta)
	{
		audio_meta_destroy(g_hAudioMeta);
	}
	if(g_hAudioInfo)
	{
		media_info_destroy(g_hAudioInfo);
	}
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
		struct stat stBuff;
		if ( stat("audio", &stBuff) == 0 )
		{
			if (remove("audio"))
			{
				FPRINTF("[Line : %d][%s] TEST SUIT clean-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
			}
		}
		if(g_szAudioPath)
		{
			media_content_scan_file(g_szAudioPath);
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
* @testcase 			ITc_audio_meta_clone_destroy_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_clone and audio_meta_destroy
* @scenario				Call audio_meta_clone and audio_meta_destroy
* @apicovered			audio_meta_clone, audio_meta_destroy
* @passcase				When audio_meta_clone and audio_meta_destroy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_clone and audio_meta_destroy
//& type: auto
int ITc_audio_meta_clone_destroy_p(void)
{
	START_TEST_PLAYLIST;

	audio_meta_h hAudioMeta = NULL;
	int nRet = audio_meta_clone(&hAudioMeta, g_hAudioMeta);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_clone", MediaContentGetError(nRet));
	CHECK_HANDLE(hAudioMeta, "audio_meta_clone");

	nRet = audio_meta_destroy(hAudioMeta);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_album_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_album
* @scenario				Call audio_meta_get_album
* @apicovered			audio_meta_get_album
* @passcase				When audio_meta_get_album is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_album
//& type: auto
int ITc_audio_meta_get_album_p(void)
{
	START_TEST_PLAYLIST;

	char *pszAlbum = NULL;
	int nRet = audio_meta_get_album(g_hAudioMeta, &pszAlbum);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_album", MediaContentGetError(nRet));
	CHECK_HANDLE(pszAlbum, "audio_meta_get_album");
	FREE_MEMORY(pszAlbum);

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_album_artist_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_album_artist
* @scenario				Call audio_meta_get_album_artist
* @apicovered			audio_meta_get_album_artist
* @passcase				When audio_meta_get_album_artist is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_album_artist
//& type: auto
int ITc_audio_meta_get_album_artist_p(void)
{
	START_TEST_PLAYLIST;

	char *pszAlbumArtist = NULL;
	int nRet = audio_meta_get_album_artist(g_hAudioMeta, &pszAlbumArtist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_album_artist", MediaContentGetError(nRet));
	CHECK_HANDLE(pszAlbumArtist, "audio_meta_get_album_artist");
	FREE_MEMORY(pszAlbumArtist);

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_artist_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_artist
* @scenario				Call audio_meta_get_artist
* @apicovered			audio_meta_get_artist
* @passcase				When audio_meta_get_artist is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_artist
//& type: auto
int ITc_audio_meta_get_artist_p(void)
{
	START_TEST_PLAYLIST;

	char *pszArtist = NULL;
	int nRet = audio_meta_get_artist(g_hAudioMeta, &pszArtist);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_artist", MediaContentGetError(nRet));
	CHECK_HANDLE(pszArtist, "audio_meta_get_artist");
	FREE_MEMORY(pszArtist);

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_bit_rate_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_bit_rate
* @scenario				Call audio_meta_get_bit_rate
* @apicovered			audio_meta_get_bit_rate
* @passcase				When audio_meta_get_bit_rate is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_bit_rate
//& type: auto
int ITc_audio_meta_get_bit_rate_p(void)
{
	START_TEST_PLAYLIST;

	int nBitRate = 0;
	int nRet = audio_meta_get_bit_rate(g_hAudioMeta, &nBitRate);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_bit_rate", MediaContentGetError(nRet));
	CHECK_COUNT(nBitRate, "audio_meta_get_bit_rate");

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_bitpersample_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_bitpersample
* @scenario				Call audio_meta_get_bitpersample
* @apicovered			audio_meta_get_bitpersample
* @passcase				When audio_meta_get_bitpersample is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_bitpersample
//& type: auto
int ITc_audio_meta_get_bitpersample_p(void)
{
	START_TEST_PLAYLIST;

	int nBitpersample = 0;
	int nRet = audio_meta_get_bitpersample(g_hAudioMeta, &nBitpersample);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_bitpersample", MediaContentGetError(nRet));
	CHECK_COUNT(nBitpersample, "audio_meta_get_bitpersample");

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_channel_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_channel
* @scenario				Call audio_meta_get_channel
* @apicovered			audio_meta_get_channel
* @passcase				When audio_meta_get_channel is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_channel
//& type: auto
int ITc_audio_meta_get_channel_p(void)
{
	START_TEST_PLAYLIST;

	int nChannel = 0;
	int nRet = audio_meta_get_channel(g_hAudioMeta, &nChannel);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_channel", MediaContentGetError(nRet));
	CHECK_COUNT(nChannel, "audio_meta_get_channel");

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_composer_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_composer
* @scenario				Call audio_meta_get_composer
* @apicovered			audio_meta_get_composer
* @passcase				When audio_meta_get_composer is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_composer
//& type: auto
int ITc_audio_meta_get_composer_p(void)
{
	START_TEST_PLAYLIST;

	char *pszComposer = NULL;
	int nRet = audio_meta_get_composer(g_hAudioMeta, &pszComposer);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_composer", MediaContentGetError(nRet));
	CHECK_HANDLE(pszComposer, "audio_meta_get_composer");
	FREE_MEMORY(pszComposer);

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_copyright_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_copyright
* @scenario				Call audio_meta_get_copyright
* @apicovered			audio_meta_get_copyright
* @passcase				When audio_meta_get_copyright is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_copyright
//& type: auto
int ITc_audio_meta_get_copyright_p(void)
{
	START_TEST_PLAYLIST;

	char *pszCopyright = NULL;
	int nRet = audio_meta_get_copyright(g_hAudioMeta, &pszCopyright);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_copyright", MediaContentGetError(nRet));
	CHECK_HANDLE(pszCopyright, "audio_meta_get_copyright");
	FREE_MEMORY(pszCopyright);

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_duration_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_duration
* @scenario				Call audio_meta_get_duration
* @apicovered			audio_meta_get_duration
* @passcase				When audio_meta_get_duration is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_duration
//& type: auto
int ITc_audio_meta_get_duration_p(void)
{
	START_TEST_PLAYLIST;

	int nDuration = 0;
	int nRet = audio_meta_get_duration(g_hAudioMeta, &nDuration);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_duration", MediaContentGetError(nRet));
	CHECK_COUNT(nDuration, "audio_meta_get_duration");

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_genre_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_genre
* @scenario				Call audio_meta_get_genre
* @apicovered			audio_meta_get_genre
* @passcase				When audio_meta_get_genre is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_genre
//& type: auto
int ITc_audio_meta_get_genre_p(void)
{
	START_TEST_PLAYLIST;

	char *pszGenre = NULL;
	int nRet = audio_meta_get_genre(g_hAudioMeta, &pszGenre);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_genre", MediaContentGetError(nRet));
	CHECK_HANDLE(pszGenre, "audio_meta_get_genre");
	FREE_MEMORY(pszGenre);

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_media_id_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_media_id
* @scenario				Call audio_meta_get_media_id
* @apicovered			audio_meta_get_media_id
* @passcase				When audio_meta_get_media_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_media_id
//& type: auto
int ITc_audio_meta_get_media_id_p(void)
{
	START_TEST_PLAYLIST;

	char *pszMediaId = NULL;
	int nRet = audio_meta_get_media_id(g_hAudioMeta, &pszMediaId);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_media_id", MediaContentGetError(nRet));
	CHECK_HANDLE(pszMediaId, "audio_meta_get_media_id");
	FREE_MEMORY(pszMediaId);

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_recorded_date_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_recorded_date
* @scenario				Call audio_meta_get_recorded_date
* @apicovered			audio_meta_get_recorded_date
* @passcase				When audio_meta_get_recorded_date is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_recorded_date
//& type: auto
int ITc_audio_meta_get_recorded_date_p(void)
{
	START_TEST_PLAYLIST;

	char *pszRecordedDate = NULL;
	int nRet = audio_meta_get_recorded_date(g_hAudioMeta, &pszRecordedDate);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_recorded_date", MediaContentGetError(nRet));
	CHECK_HANDLE(pszRecordedDate, "audio_meta_get_recorded_date");
	FREE_MEMORY(pszRecordedDate);

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_sample_rate_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_sample_rate
* @scenario				Call audio_meta_get_sample_rate
* @apicovered			audio_meta_get_sample_rate
* @passcase				When audio_meta_get_sample_rate is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_sample_rate
//& type: auto
int ITc_audio_meta_get_sample_rate_p(void)
{
	START_TEST_PLAYLIST;

	int nSampleRate = 0;
	int nRet = audio_meta_get_sample_rate(g_hAudioMeta, &nSampleRate);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_sample_rate", MediaContentGetError(nRet));
	CHECK_COUNT(nSampleRate, "audio_meta_get_sample_rate");

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_track_num_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_track_num
* @scenario				Call audio_meta_get_track_num
* @apicovered			audio_meta_get_track_num
* @passcase				When audio_meta_get_track_num is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_track_num
//& type: auto
int ITc_audio_meta_get_track_num_p(void)
{
	START_TEST_PLAYLIST;

	char *pszTrackNum = NULL;
	int nRet = audio_meta_get_track_num(g_hAudioMeta, &pszTrackNum);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_track_num", MediaContentGetError(nRet));
	CHECK_HANDLE(pszTrackNum, "audio_meta_get_track_num");
	FREE_MEMORY(pszTrackNum);

	return 0;
}

/**
* @testcase 			ITc_audio_meta_get_year_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test audio_meta_get_year
* @scenario				Call audio_meta_get_year
* @apicovered			audio_meta_get_year
* @passcase				When audio_meta_get_year is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test audio_meta_get_year
//& type: auto
int ITc_audio_meta_get_year_p(void)
{
	START_TEST_PLAYLIST;

	char *pszYear = NULL;
	int nRet = audio_meta_get_year(g_hAudioMeta, &pszYear);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "audio_meta_get_year", MediaContentGetError(nRet));
	CHECK_HANDLE(pszYear, "audio_meta_get_year");
	FREE_MEMORY(pszYear);

	return 0;
}

/** @} */
/** @} */
