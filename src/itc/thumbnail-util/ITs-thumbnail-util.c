//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-thumbnail-util-common.h"

/** @addtogroup itc-thumbnail-util
* @ingroup		itc
* @{
*/

//& set: ThumbnailUtil

thumbnail_h g_stHandleThumbnail = NULL;
char* g_pszRequestId = NULL;
bool g_bThumbnailCreation = false;
bool g_bThumbnailCallbackCheck = false;
bool g_bThumbnailPathCreation = true;

/**
* @function 		thumbnail_completed_cb
* @description	 	Called before each test extracting the thumbnail for the given media
* @parameter		NA
* @return 			NA
*/
static void thumbnail_completed_cb(thumbnail_util_error_e error, const char *request_id, int raw_width, int raw_height, unsigned char *raw_data, int raw_size, void *user_data)
{
	g_bThumbnailCallbackCheck = true;
	if (g_pThumbnailUtilMainLoop)
	{
		g_main_loop_quit(g_pThumbnailUtilMainLoop);
	}

	return;
}

/**
* @function 		ITs_thumbnail_util_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_thumbnail_util_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITC_Thumbnail_Util_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = 0;
	nRet = thumbnail_util_create(&g_stHandleThumbnail);
	if ( nRet == THUMBNAIL_UTIL_ERROR_NONE )
	{
		g_bThumbnailCreation = true;
	}
	else
	{
		FPRINTF("[Line : %d][%s] thumbnail_util_create failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ThumbnailUtilGetError(nRet));
		g_bThumbnailCreation = false;
	}

	return;
}

/**
* @function 		ITs_thumbnail_util_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_thumbnail_util_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITC_Thumbnail_Util_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = 0;
	if ( g_bThumbnailCreation )
	{
		nRet = thumbnail_util_destroy(g_stHandleThumbnail);
		if ( nRet != THUMBNAIL_UTIL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] thumbnail_util_destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ThumbnailUtilGetError(nRet));
		}
	}

	return;
}

/** @addtogroup	itc-thumbnail-util-testcases
* @brief 		Integration testcases for module thumbnail-util
* @ingroup		itc-thumbnail-util
* @{
*/

//& purpose: Creates and destroys a thumbnail util handle
//& type: auto
/**
* @testcase 		ITc_thumnail_util_create_destroy_p
* @since_tizen		2.4
* @author			SRID(ajay.kr1)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Creates and destroys a thumbnail util handle
* @scenario			Create a thumbnail-util handle\n
*					Destroy the thumbnail-util handle
* @apicovered		thumbnail_util_create and thumbnail_util_destroy
* @passcase			When thumbnail_util_create and thumbnail_util_destroy is successful
* @failcase			If target thumbnail_util_create and thumbnail_util_destroy fails or any precondition api fails
* @precondition		None
* @postcondition	None
*/
int ITc_thumnail_util_create_destroy_p(void)
{
	START_TEST;

	thumbnail_h stHandleThumbnail = NULL;

	//Target API
	int nRet = thumbnail_util_create(&stHandleThumbnail);
	PRINT_RESULT(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_create", ThumbnailUtilGetError(nRet));

	//Target API
	nRet = thumbnail_util_destroy(stHandleThumbnail);
	PRINT_RESULT(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_destroy", ThumbnailUtilGetError(nRet));

	return 0;
}

//& purpose: Sets the path of original media file
//& type: auto
/**
* @testcase 		ITc_thumnail_util_set_path_p
* @since_tizen		2.4
* @author			SRID(ajay.kr1)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Sets the path of original media file
* @scenario			Set the path of original media file
* @apicovered		thumbnail_util_set_path
* @passcase			When thumbnail_util_set_path is successful
* @failcase			If target thumbnail_util_set_path fails
* @precondition		None
* @postcondition	None
*/
int ITc_thumnail_util_set_path_p(void)
{
	START_TEST;

	char* pszPath = ThumbnailGetDataPath(SAMPLE_FILE_1);
	if(pszPath == NULL )
	{
		FPRINTF("[Line : %d][%s] ThumbnailGetDataPath failed, error returned \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	//Target API
	int nRet = thumbnail_util_set_path(g_stHandleThumbnail, pszPath);
	PRINT_RESULT_CLEANUP(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_set_path", ThumbnailUtilGetError(nRet),FREE_MEMORY(pszPath));
	FREE_MEMORY(pszPath);

	return 0;
}

//& purpose: Sets the size of thumbnail to be extracted
//& type: auto
/**
* @testcase 		ITc_thumnail_util_set_size_p
* @since_tizen		2.4
* @author			SRID(ajay.kr1)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Sets the size of thumbnail to be extracted
* @scenario			Set the size of thumbnail to be extracted
* @apicovered		thumbnail_util_set_size
* @passcase			When thumbnail_util_set_size is successful
* @failcase			If target thumbnail_util_set_size fails
* @precondition		Create a thumbnail info handle by calling thumbnail_util_create()
* @postcondition	None
*/
int ITc_thumnail_util_set_size_p(void)
{
	START_TEST;

	//Target API
	int nRet = thumbnail_util_set_size(g_stHandleThumbnail, MEDIA_IMAGE_WIDTH, MEDIA_IMAGE_HEIGHT);
	PRINT_RESULT(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_set_size", ThumbnailUtilGetError(nRet));

	return 0;
}

//& purpose: Extracts the thumbnail for the given media, asynchronously
//& type: auto
/**
* @testcase 		ITc_thumnail_util_extract_p
* @since_tizen		2.4
* @author			SRID(ajay.kr1)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Extracts the thumbnail for the given media
* @scenario			Extract the thumbnail
* @apicovered		thumbnail_util_set_path, thumbnail_util_set_size, thumbnail_util_extract, thumbnail_util_cancel
* @passcase			When thumbnail_util_extract is successful
* @failcase			If target thumbnail_util_extract fails
* @precondition		Create a thumbnail info handle by calling thumbnail_util_create()
* @postcondition	None
*/
int ITc_thumnail_util_extract_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	g_pszRequestId = NULL;
	g_bThumbnailCallbackCheck = false;

	char* pszPath = ThumbnailGetDataPath(SAMPLE_FILE_1);
	if(pszPath == NULL )
	{
		FPRINTF("[Line : %d][%s] ThumbnailGetDataPath failed, error returned \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = thumbnail_util_set_path(g_stHandleThumbnail, pszPath);
	PRINT_RESULT_CLEANUP(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_set_path", ThumbnailUtilGetError(nRet),FREE_MEMORY(pszPath));

	nRet = thumbnail_util_set_size(g_stHandleThumbnail, MEDIA_IMAGE_WIDTH, MEDIA_IMAGE_HEIGHT);
	PRINT_RESULT_CLEANUP(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_set_size", ThumbnailUtilGetError(nRet),FREE_MEMORY(pszPath));

	//Target API
	nRet = thumbnail_util_extract(g_stHandleThumbnail, thumbnail_completed_cb, NULL, &g_pszRequestId);
	PRINT_RESULT_CLEANUP(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_extract", ThumbnailUtilGetError(nRet),FREE_MEMORY(pszPath));

	RUN_POLLING_LOOP;
	if ( !g_bThumbnailCallbackCheck )
	{
		FPRINTF("[Line : %d][%s] Callback failed\\n", __LINE__, API_NAMESPACE);
		thumbnail_util_cancel(g_stHandleThumbnail, g_pszRequestId);
		FREE_MEMORY(g_pszRequestId);
		FREE_MEMORY(pszPath);
		return 1;
	}

	if ( g_pszRequestId == NULL )
	{
		FPRINTF("[Line : %d][%s] thumbnail_util_extract failed, not extracted any request id. \\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszPath);
		return 1;
	}

	FREE_MEMORY(g_pszRequestId);
	FREE_MEMORY(pszPath);

	return 0;
}

//& purpose: Extract the thumbnail for the given media & cancels the thumbnail extraction request in between
//& type: auto
/**
* @testcase 		ITc_thumnail_util_extract_cancel_p
* @since_tizen		2.4
* @author			SRID(ajay.kr1)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Extracts the thumbnail & cancels the thumbnail extraction request for the given media
* @scenario			Extract the thumbnail\n
*					Cancel the thumbnail extraction request
* @apicovered		thumbnail_util_set_path, thumbnail_util_set_size, thumbnail_util_extract, thumbnail_util_cancel
* @passcase			When thumbnail_util_cancel is successful
* @failcase			If target thumbnail_util_cancel fails
* @precondition		Create a thumbnail info handle by calling thumbnail_util_create()
* @postcondition	None
*/
int ITc_thumnail_util_extract_cancel_p(void)
{
	START_TEST;

	g_pszRequestId = NULL;

	char* pszPath = ThumbnailGetDataPath(SAMPLE_FILE_1);
	if(pszPath == NULL )
	{
		FPRINTF("[Line : %d][%s] ThumbnailGetDataPath failed, error returned \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = thumbnail_util_set_path(g_stHandleThumbnail, pszPath);
	PRINT_RESULT_CLEANUP(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_set_path", ThumbnailUtilGetError(nRet),FREE_MEMORY(pszPath));

	nRet = thumbnail_util_set_size(g_stHandleThumbnail, MEDIA_IMAGE_WIDTH, MEDIA_IMAGE_HEIGHT);
	PRINT_RESULT_CLEANUP(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_set_size", ThumbnailUtilGetError(nRet),FREE_MEMORY(pszPath));

	nRet = thumbnail_util_extract(g_stHandleThumbnail, thumbnail_completed_cb, NULL, &g_pszRequestId);
	PRINT_RESULT_CLEANUP(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_extract", ThumbnailUtilGetError(nRet),FREE_MEMORY(pszPath));

	if ( g_pszRequestId == NULL )
	{
		FPRINTF("[Line : %d][%s] thumbnail_util_extract failed, not extracted any request id. \\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszPath);
		return 1;
	}

	//Target API
	nRet = thumbnail_util_cancel(g_stHandleThumbnail, g_pszRequestId);
	FREE_MEMORY(g_pszRequestId);
	PRINT_RESULT_CLEANUP(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_cancel", ThumbnailUtilGetError(nRet),FREE_MEMORY(pszPath));
	FREE_MEMORY(pszPath);
	return 0;
}

//& purpose: To extracts the thumbnail for the given media into a file, synchronously.
//& type: auto
/**
* @testcase 		ITc_thumbnail_util_extract_to_file
* @since_tizen		5.0
* @author			SRID(priya.kohli)
* @reviewer			SRID(a.pandia1)
* @type 			auto
* @description		Extracts the thumbnail for the given media into a file, synchronously.
* @scenario			This function creates thumbnail from a given media file.
					The generated thumbnail is saved in the given thumbnail path.
* @apicovered		thumbnail_util_extract_to_file
* @passcase			When ITc_thumbnail_util_extract_to_file is successful
* @failcase			If ITc_thumbnail_util_extract_to_file fails
* @precondition		Create a thumbnail info handle by calling thumbnail_util_create()
* @postcondition	None
*/
int ITc_thumbnail_util_extract_to_file(void)
{
	START_TEST;

	int nWidth = 320;
	int nHeight = 240;
	char* pszPath = ThumbnailGetDataPath(SAMPLE_FILE_1);
	if(pszPath == NULL)
	{
		FPRINTF("[Line : %d][%s] ThumbnailGetDataPath failed, error returned \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char* pszThumbPath = ThumbnailGetDataPath(SAMPLE_FILE_2);
	if(pszThumbPath == NULL)
	{
		FPRINTF("[Line : %d][%s] ThumbnailGetDataPath failed, error returned \\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszPath);
		return 1;
	}

	int nRet = thumbnail_util_extract_to_file(pszPath, nWidth, nHeight, pszThumbPath);
	FREE_MEMORY(pszPath);
	FREE_MEMORY(pszThumbPath);
	PRINT_RESULT(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_extract_to_file", ThumbnailUtilGetError(nRet));

	return 0;
}

//& purpose: To extract the thumbnail for the given media into a buffer, synchronously.
//& type: auto
/**
* @testcase 		ITc_thumbnail_util_extract_to_buffer
* @since_tizen		5.0
* @author			SRID(priya.kohli)
* @reviewer			SRID(a.pandia1)
* @type 			auto
* @description		Extracts the thumbnail for the given media into a buffer, synchronously.
* @scenario			This function creates thumbnails from a given media file.
					The generated thumbnail is returned as a raw data stream.
* @apicovered		thumbnail_util_extract_to_buffer
* @passcase			When ITc_thumbnail_util_extract_to_buffer is successful
* @failcase			If ITc_thumbnail_util_extract_to_buffer fails
* @precondition		Create a thumbnail info handle by calling thumbnail_util_create()
* @postcondition	None
*/
int ITc_thumbnail_util_extract_to_buffer(void)
{
	START_TEST;
	char* pszBuf = NULL;
	int nWidth = 320;
	int nHeight = 240;
	int nThumbWidth = 0;
	int nThumbHeight = 0;
	size_t nSize = 0;

	char* pszPath = ThumbnailGetDataPath(SAMPLE_FILE_1);
	if(pszPath == NULL)
	{
		FPRINTF("[Line : %d][%s] ThumbnailGetDataPath failed, error returned \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = thumbnail_util_extract_to_buffer(pszPath, nWidth, nHeight, &pszBuf, &nSize, &nThumbWidth, &nThumbHeight);
	if(pszBuf == NULL)
	{
		FPRINTF("[Line : %d][%s] thumbnail_util_extract_to_buffer failed, pszBuf is NULL \\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszPath);
		return 1;
	}
	FREE_MEMORY(pszBuf);
	FREE_MEMORY(pszPath);
	PRINT_RESULT(THUMBNAIL_UTIL_ERROR_NONE, nRet, "thumbnail_util_extract_to_buffer", ThumbnailUtilGetError(nRet));

	if(!nSize)
	{
		FPRINTF("[Line : %d][%s] nSize value not correct. nSize =  \\n", __LINE__, API_NAMESPACE, nSize);
		return 1;
	}

	if(!nThumbWidth)
	{
		FPRINTF("[Line : %d][%s] nThumbWidth value not correct. nThumbWidth =  \\n", __LINE__, API_NAMESPACE, nThumbWidth);
		return 1;
	}

	if(!nThumbHeight)
	{
		FPRINTF("[Line : %d][%s] nThumbHeight value not correct. nThumbHeight =  \\n", __LINE__, API_NAMESPACE, nThumbHeight);
		return 1;
	}

	return 0;
}

/** @} */ //end of thumbnail-util
/** @} */ //end of itc-thumbnail-util-testcases
