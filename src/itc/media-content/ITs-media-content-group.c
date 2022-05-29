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

media_group_e g_eMediaGroup[] = {
								MEDIA_CONTENT_GROUP_DISPLAY_NAME,
								MEDIA_CONTENT_GROUP_TYPE,
								MEDIA_CONTENT_GROUP_MIME_TYPE,
								MEDIA_CONTENT_GROUP_SIZE,
								MEDIA_CONTENT_GROUP_ADDED_TIME,
								MEDIA_CONTENT_GROUP_MODIFIED_TIME,
								MEDIA_CONTENT_GROUP_TITLE,
								MEDIA_CONTENT_GROUP_ARTIST,
								MEDIA_CONTENT_GROUP_ALBUM_ARTIST,
								MEDIA_CONTENT_GROUP_GENRE,
								MEDIA_CONTENT_GROUP_COMPOSER,
								MEDIA_CONTENT_GROUP_YEAR,
								MEDIA_CONTENT_GROUP_RECORDED_DATE,
								MEDIA_CONTENT_GROUP_COPYRIGHT,
								MEDIA_CONTENT_GROUP_TRACK_NUM,
								MEDIA_CONTENT_GROUP_DESCRIPTION,
								MEDIA_CONTENT_GROUP_LONGITUDE,
								MEDIA_CONTENT_GROUP_LATITUDE,
								MEDIA_CONTENT_GROUP_ALTITUDE,
								MEDIA_CONTENT_GROUP_RATING
							  };

/*****************************************************Enums End*****************************************************/


/****************************************************Callback Start****************************************************/

/**
 * @function 		ForeachGroupCb
 * @description	 	Callback Function
 * @parameter		const char *group_name, void *user_data
 * @return 			NA
 */
static bool ForeachGroupCb(const char *group_name, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "ForeachGroupCb");
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

	g_CallBackHit = true;
	QuitGmainLoop();
	return false;
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_media_content_group_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_group_startup(void)
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

	AppendPaths(g_szInternalStoragePath, TESTAUDIO, g_szAudioPath);

	nRet = media_content_scan_file(g_szAudioPath);
	PRINT_RESULTNONE_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet), media_content_disconnect());

	g_bMediaContentStartup = true;
	return;
}

/**
 * @function 		ITs_media_content_group_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_group_cleanup(void)
{
	if(g_bMediaContentStartup && g_bIsScanFeatureSupported)
	{
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
* @testcase 			ITc_media_group_get_group_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_group_get_group_count_from_db
* @scenario				Call media_group_get_group_count_from_db
* @apicovered			media_group_get_group_count_from_db
* @passcase				When media_group_get_group_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_group_get_group_count_from_db
//& type: auto
int ITc_media_group_get_group_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nEnumCounter = 0;
	int nEnumSize = sizeof(g_eMediaGroup) / sizeof(g_eMediaGroup[0]);
	for (nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		int nCount = -1;
		int nRet = media_group_get_group_count_from_db(NULL, g_eMediaGroup[nEnumCounter], &nCount);
		PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_group_get_group_count_from_db", MediaContentGetError(nRet));
		CHECK_COUNT(nCount, "media_group_get_group_count_from_db");
	}

	return 0;
}

/**
* @testcase 			ITc_media_group_foreach_group_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_group_foreach_group_from_db
* @scenario				Call media_group_foreach_group_from_db
* @apicovered			media_group_foreach_group_from_db
* @passcase				When media_group_foreach_group_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_group_foreach_group_from_db
//& type: auto
int ITc_media_group_foreach_group_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nEnumCounter = 0;
	int nEnumSize = sizeof(g_eMediaGroup) / sizeof(g_eMediaGroup[0]);
	for (nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		int nCount = -1;
		int nRet = media_group_get_group_count_from_db(NULL, g_eMediaGroup[nEnumCounter], &nCount);
		PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_group_get_group_count_from_db", MediaContentGetError(nRet));
		CHECK_COUNT(nCount, "media_group_get_group_count_from_db");
		if(nCount == 0)
		{
			continue;
		}

		g_CallBackHit = false;
		nRet = media_group_foreach_group_from_db(NULL, g_eMediaGroup[nEnumCounter], ForeachGroupCb, TESTSTRING);
		PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_group_foreach_group_from_db", MediaContentGetError(nRet));
		IterateGmainLoop();
		PRINT_RESULT(true, g_CallBackHit, "media_group_foreach_group_from_db", "CallBack Not Invoked");
	}

	return 0;
}

/**
* @testcase 			ITc_media_group_get_media_count_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_group_get_media_count_from_db
* @scenario				Call media_group_get_media_count_from_db
* @apicovered			media_group_get_media_count_from_db
* @passcase				When media_group_get_media_count_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_group_get_media_count_from_db
//& type: auto
int ITc_media_group_get_media_count_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nEnumCounter = 0;
	int nEnumSize = sizeof(g_eMediaGroup) / sizeof(g_eMediaGroup[0]);
	for (nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		int nCount = -1;
		int nRet = media_group_get_media_count_from_db(NULL, g_eMediaGroup[nEnumCounter], NULL, &nCount);
		PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_group_get_media_count_from_db", MediaContentGetError(nRet));
		CHECK_COUNT(nCount, "media_group_get_media_count_from_db");
	}

	return 0;
}

/**
* @testcase 			ITc_media_group_foreach_media_from_db_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_group_foreach_media_from_db
* @scenario				Call media_group_foreach_media_from_db
* @apicovered			media_group_foreach_media_from_db
* @passcase				When media_group_foreach_media_from_db is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_group_foreach_media_from_db
//& type: auto
int ITc_media_group_foreach_media_from_db_p(void)
{
	START_TEST_PLAYLIST;

	int nEnumCounter = 0;
	int nEnumSize = sizeof(g_eMediaGroup) / sizeof(g_eMediaGroup[0]);
	for (nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		int nCount = -1;
		int nRet = media_group_get_media_count_from_db(NULL, g_eMediaGroup[nEnumCounter], NULL, &nCount);
		PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_group_get_media_count_from_db", MediaContentGetError(nRet));
		CHECK_COUNT(nCount, "media_group_get_media_count_from_db");
		if(nCount == 0)
		{
			continue;
		}

		g_CallBackHit = false;
		nRet = media_group_foreach_media_from_db(NULL, g_eMediaGroup[nEnumCounter], NULL, ForeachMediaCb, TESTSTRING);
		PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_group_foreach_media_from_db", MediaContentGetError(nRet));
		IterateGmainLoop();
		PRINT_RESULT(true, g_CallBackHit, "media_group_foreach_media_from_db", "CallBack Not Invoked");
	}

	return 0;
}

/** @} */
/** @} */
