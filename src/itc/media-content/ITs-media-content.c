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

#ifdef TV	//Starts TV
bool g_CallBackHitint;
#endif  //TV	//End TV

/** @addtogroup itc-media-content
*  @ingroup itc
*  @{
*/

/****************************************************Callback Start****************************************************/

/**
 * @function 		FolderScanCompletedCb
 * @description	 	Callback Function
 * @parameter		media_content_error_e error, void* user_data
 * @return 			NA
 */
static void FolderScanCompletedCb(media_content_error_e error, void* user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "FolderScanCompletedCb");
#endif

	g_CallBackHit = true;
#ifdef TV	//Starts TV
	g_CallBackHitint = true;
#endif  	//End TV
	QuitGmainLoop();
	return;
}

/**
 * @function 		DataBaseUpdatedCb
 * @description	 	Callback Function
 * @parameter		media_content_error_e error, int pid, media_content_db_update_item_type_e update_item, media_content_db_update_type_e update_type, media_content_type_e media_type, char* uuid, char* path, char* mime_type, void* user_data
 * @return 			NA
 */
static void DataBaseUpdatedCb(media_content_error_e error, int pid, media_content_db_update_item_type_e update_item, media_content_db_update_type_e update_type, media_content_type_e media_type, char* uuid, char* path, char* mime_type, void* user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "DataBaseUpdatedCb");
#endif

	g_CallBackHit = true;
	QuitGmainLoop();
	return;
}

/*****************************************************Callback End*****************************************************/

/**
 * @function 		ITs_media_content_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	g_bMediaContentStartup = false;
	int nRet = media_content_connect();
	PRINT_RESULTNONE(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_connect", MediaContentGetError(nRet));

	g_bMediaContentStartup = true;
	return;
}


/**
 * @function 		ITs_media_content_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_media_content_cleanup(void)
{
	if(g_bMediaContentStartup)
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
* @testcase 			ITc_media_content_connect_disconnect_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_content_connect and media_content_disconnect
* @scenario				Call media_content_connect and media_content_disconnect
* @apicovered			media_content_connect, media_content_disconnect
* @passcase				When media_content_connect and media_content_disconnect is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_content_connect and media_content_disconnect
//& type: auto
int ITc_media_content_connect_disconnect_p(void)
{
	START_TEST;

	int nRet = media_content_disconnect();
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_disconnect", MediaContentGetError(nRet));

	nRet = media_content_connect();
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_connect", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_content_scan_file_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_content_scan_file
* @scenario				Call media_content_scan_file
* @apicovered			media_content_scan_file
* @passcase				When media_content_scan_file is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_content_scan_file
//& type: auto
int ITc_media_content_scan_file_p(void)
{
	START_TEST;
	bool bIsFeatureSupported = true;

	int nRet = GetInternalStorageIdandPath();
	PRINT_RESULT(0, nRet, "GetInternalStorageId", "Return Value Not Correct");
	AppendPaths(g_szInternalStoragePath, TESTTEXT, g_szTextPath);

	bIsFeatureSupported = TCTCheckSystemInfoFeatureSupported(SCAN_FEATURE, API_NAMESPACE);

	nRet = media_content_scan_file(g_szTextPath);
	if ( !bIsFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] media_content_scan_file returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE,  MediaContentGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] media_content_scan_file correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE,  MediaContentGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_media_content_scan_folder_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_content_scan_folder
* @scenario				Call media_content_scan_folder
* @apicovered			media_content_scan_folder
* @passcase				When media_content_scan_folder is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_content_scan_folder
//& type: auto
int ITc_media_content_scan_folder_p(void)
{
	START_TEST;

	int nRet = GetInternalStorageIdandPath();
	PRINT_RESULT(0, nRet, "GetInternalStorageId", "Return Value Not Correct");

	nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", "Return Value Not Correct");

	g_CallBackHit = false;
	nRet = media_content_scan_folder(g_szImageFolder, false, FolderScanCompletedCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_folder", MediaContentGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_content_scan_folder", "CallBack Related Issue");

	return 0;
}

/**
* @testcase 			ITc_media_content_cancel_scan_folder_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test media_content_cancel_scan_folder
* @scenario				Call media_content_cancel_scan_folder
* @apicovered			media_content_cancel_scan_folder
* @passcase				When media_content_cancel_scan_folder is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_content_cancel_scan_folder
//& type: auto
int ITc_media_content_cancel_scan_folder_p(void)
{
	START_TEST;

	int nRet = GetInternalStorageIdandPath();
	PRINT_RESULT(0, nRet, "GetInternalStorageId", "Return Value Not Correct");

	nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", "Return Value Not Correct");

	nRet = media_content_scan_folder(g_szImageFolder, false, FolderScanCompletedCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_folder", MediaContentGetError(nRet));

	nRet = media_content_cancel_scan_folder(g_szImageFolder);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_cancel_scan_folder", MediaContentGetError(nRet));

	return 0;
}
#ifdef TV	//Starts TV
/**
* @testcase 			ITc_media_content_add_remove_db_updated_cb_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Test media_content_add_db_updated_cb and media_content_remove_db_updated_cb
* @scenario				Call media_content_add_db_updated_cb and media_content_remove_db_updated_cb
* @apicovered			media_content_add_db_updated_cb, media_content_remove_db_updated_cb
* @passcase				When media_content_add_db_updated_cb and media_content_remove_db_updated_cb is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_content_add_db_updated_cb and media_content_remove_db_updated_cb
//& type: auto
int ITc_media_content_add_remove_db_updated_cb_p(void)
{
	START_TEST;

	media_content_noti_h hNotiHandle;

	int nRet = GetInternalStorageIdandPath();
	PRINT_RESULT(0, nRet, "GetInternalStorageId", "Return Value Not Correct");
	AppendPaths(g_szInternalStoragePath, REMOVEIMAGE, g_szImagePath);

	nRet = GetFolderPath(STORAGE_DIRECTORY_IMAGES, g_szImageFolder);
	PRINT_RESULT(0, nRet, "GetFolderPath", "Return Value Not Correct");

	g_CallBackHit = false;
	nRet = media_content_add_db_updated_cb(DataBaseUpdatedCb, TESTSTRING,&hNotiHandle);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_add_db_updated_cb", MediaContentGetError(nRet));

	nRet = media_content_scan_folder(g_szImageFolder, false, FolderScanCompletedCb, TESTSTRING);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_folder", MediaContentGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_content_add_db_updated_cb", "CallBack Not Invoked");

	nRet = media_content_remove_db_updated_cb(hNotiHandle);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_remove_db_updated_cb", MediaContentGetError(nRet));

	return 0;
}

#endif  	//End TV

#if defined(MOBILE) || defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or TIZENIOT or WEARABLE

/**
* @testcase 			ITc_media_content_add_remove_db_updated_cb_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			Test media_content_add_db_updated_cb and media_content_remove_db_updated_cb
* @scenario				Call media_content_add_db_updated_cb and media_content_remove_db_updated_cb
* @apicovered			media_content_add_db_updated_cb, media_content_remove_db_updated_cb
* @passcase				When media_content_add_db_updated_cb and media_content_remove_db_updated_cb is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
//& purpose: Test media_content_add_db_updated_cb and media_content_remove_db_updated_cb
//& type: auto
int ITc_media_content_add_remove_db_updated_cb_p(void)
{
	START_TEST;

	media_content_noti_h hNotiHandle;
	bool bIsFeatureSupported = true;

	int nRet = GetInternalStorageIdandPath();
	PRINT_RESULT(0, nRet, "GetInternalStorageId", "Return Value Not Correct");
	AppendPaths(g_szInternalStoragePath, TESTTEXT, g_szTextPath);

	g_CallBackHit = false;
	nRet = media_content_add_db_updated_cb(DataBaseUpdatedCb, NULL,&hNotiHandle);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_add_db_updated_cb", MediaContentGetError(nRet));

	bIsFeatureSupported = TCTCheckSystemInfoFeatureSupported(SCAN_FEATURE, API_NAMESPACE);

	nRet = media_content_scan_file(g_szTextPath);
	if ( !bIsFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] media_content_scan_file returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE,  MediaContentGetError(nRet));
			media_content_remove_db_updated_cb(hNotiHandle);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] media_content_scan_file correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE,  MediaContentGetError(nRet));
			media_content_remove_db_updated_cb(hNotiHandle);
			return 0;
		}
	}
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_scan_file", MediaContentGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "media_content_add_db_updated_cb", "CallBack Not Invoked");

	nRet = media_content_remove_db_updated_cb(hNotiHandle);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_content_remove_db_updated_cb", MediaContentGetError(nRet));

	return 0;
}
#endif // End MOBILE or TIZENIOT WEARABLE

/** @} */
/** @} */
