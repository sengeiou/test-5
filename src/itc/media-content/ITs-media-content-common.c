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
#include "ITs-media-content-common.h"

/** @addtogroup itc-media-content
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/****************************************************Callback Start****************************************************/

/**
 * @function 		StorageForeachCallBack
 * @description	 	Callback Function
 * @parameter		int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data
 * @return 			NA
 */
static bool StorageForeachCallBack(int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "StorageForeachCallBack");
#endif
	FPRINTF("[Line : %d][%s] %spath\\n", __LINE__, API_NAMESPACE, path);
	if ( type == STORAGE_TYPE_INTERNAL )
	{
		g_nInternalStorageId = storage_id;
		memset(g_szInternalStoragePath, 0, PATHLEN);
		strncpy(g_szInternalStoragePath, path, PATHLEN -1 );
	}
	else if ( type == STORAGE_TYPE_EXTERNAL || type == STORAGE_TYPE_EXTENDED_INTERNAL )
	{
		g_nExternalStorageId = storage_id;
		memset(g_szExternalStoragePath, 0, PATHLEN);
		strncpy(g_szExternalStoragePath, path, PATHLEN -1 );
	}
	if ( type == STORAGE_TYPE_EXTERNAL || type == STORAGE_TYPE_EXTENDED_INTERNAL || type == STORAGE_TYPE_INTERNAL )
	{
		g_CallBackHit = true;
		QuitGmainLoop();
		return false;
	}

	return true;
}

/*****************************************************Callback End*****************************************************/

/**
* @function 		MediaContentGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaContentGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch(nRet)
	{
		case MEDIA_CONTENT_ERROR_NONE:						szErrorVal = "MEDIA_CONTENT_ERROR_NONE";						break;
		case MEDIA_CONTENT_ERROR_INVALID_PARAMETER:			szErrorVal = "MEDIA_CONTENT_ERROR_INVALID_PARAMETER";			break;
		case MEDIA_CONTENT_ERROR_OUT_OF_MEMORY:				szErrorVal = "MEDIA_CONTENT_ERROR_OUT_OF_MEMORY";				break;
		case MEDIA_CONTENT_ERROR_INVALID_OPERATION:			szErrorVal = "MEDIA_CONTENT_ERROR_INVALID_OPERATION";			break;
		case MEDIA_CONTENT_FILE_NO_SPACE_ON_DEVICE:			szErrorVal = "MEDIA_CONTENT_FILE_NO_SPACE_ON_DEVICE";			break;
		case MEDIA_CONTENT_ERROR_PERMISSION_DENIED:			szErrorVal = "MEDIA_CONTENT_ERROR_PERMISSION_DENIED";			break;
		case MEDIA_CONTENT_ERROR_DB_FAILED:					szErrorVal = "MEDIA_CONTENT_ERROR_DB_FAILED";					break;
		case MEDIA_CONTENT_ERROR_DB_BUSY:					szErrorVal = "MEDIA_CONTENT_ERROR_DB_BUSY";						break;
		case MEDIA_CONTENT_ERROR_NETWORK:					szErrorVal = "MEDIA_CONTENT_ERROR_NETWORK";						break;
		case MEDIA_CONTENT_ERROR_UNSUPPORTED_CONTENT:		szErrorVal = "MEDIA_CONTENT_ERROR_UNSUPPORTED_CONTENT";			break;
		case MEDIA_CONTENT_ERROR_NOT_SUPPORTED:				szErrorVal = "MEDIA_CONTENT_ERROR_NOT_SUPPORTED";				break;		 
		default: 											szErrorVal = "Unknown Error";									break;
	}
	return szErrorVal;
}

/**
* @function 		StorageGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* StorageGetError(storage_error_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case STORAGE_ERROR_NONE:				szErrorVal = "STORAGE_ERROR_NONE";					break;
		case STORAGE_ERROR_INVALID_PARAMETER:	szErrorVal = "STORAGE_ERROR_INVALID_PARAMETER";		break;
		case STORAGE_ERROR_OUT_OF_MEMORY:		szErrorVal = "STORAGE_ERROR_OUT_OF_MEMORY";			break;
		case STORAGE_ERROR_NOT_SUPPORTED:		szErrorVal = "STORAGE_ERROR_NOT_SUPPORTED";			break;
		case STORAGE_ERROR_OPERATION_FAILED:	szErrorVal = "STORAGE_ERROR_OPERATION_FAILED";		break;
		default:								szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}

/**
 * @function 		TimeoutFunction
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
gboolean TimeoutFunction(gpointer data)
{
	FPRINTF("[Line : %d][%s] Timeout after %d seconds\\n", __LINE__, API_NAMESPACE, TIMEOUT_CB/1000);
	QuitGmainLoop();
	return false;
}

/**
* @function 		IterateGmainLoop
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void IterateGmainLoop(void)
{
	if(g_CallBackHit == false)
	{
		g_pMainLoop = g_main_loop_new(NULL, false);
		g_nTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, NULL);
		g_main_loop_run(g_pMainLoop);

		g_source_remove(g_nTimeoutId);
		g_nTimeoutId = 0;

		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		QuitGmainLoop
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
void QuitGmainLoop(void)
{
	if(g_pMainLoop)
	{
		g_main_loop_quit(g_pMainLoop);
	}
}

/**
* @function 		GetInternalStorageIdandPath
* @description	 	Called to get internal storage id and path
* @parameter		NA
* @return 			NA
*/
bool GetInternalStorageIdandPath(void)
{
	g_CallBackHit = false;
	int nRet = storage_foreach_device_supported(StorageForeachCallBack, NULL);
	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_foreach_device_supported", StorageGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "storage_foreach_device_supported", "CallBack Not Invoked");

	return 0;
}

/**
* @function 		AppendPaths
* @description	 	Join 2 paths
* @parameter		NA
* @return 			NA
*/
void AppendPaths(char *FirstPath, char *SecondPath, char *FinalPath)
{
	memset(FinalPath, 0, PATHLEN);
	strncpy(FinalPath, FirstPath, PATHLEN-1);
	strncat(FinalPath, "/", PATHLEN-1-strlen(FinalPath));
	strncat(FinalPath, SecondPath, PATHLEN-1-strlen(FinalPath));

	FPRINTF("[Line : %d][%s] Appended Path is : %s\\n", __LINE__, API_NAMESPACE, FinalPath);
}

/**
* @function 		GetFolderPath
* @description	 	Get Specific Folder Path
* @parameter		NA
* @return 			NA
*/
bool GetFolderPath(int WhichFolder, char *FinalPath)
{
	char* pszTempPath = NULL;
	int nRet = storage_get_directory(g_nInternalStorageId, WhichFolder, &pszTempPath);
	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_get_directory", StorageGetError(nRet));
	CHECK_HANDLE(pszTempPath, "storage_get_directory");

	memset(FinalPath, 0, PATHLEN);
	strncpy(FinalPath, pszTempPath, PATHLEN-1);
	FREE_MEMORY(pszTempPath);

	FPRINTF("[Line : %d][%s] Folder Path is : %s\\n", __LINE__, API_NAMESPACE, FinalPath);
	return 0;
}

/**
* @function 		AppendSlash
* @description	 	Join 2 paths
* @parameter		NA
* @return 			NA
*/
void AppendSlash(char *FirstPath, char *FinalPath)
{
	memset(FinalPath, 0, PATHLEN);
	strncpy(FinalPath, FirstPath, PATHLEN-1);
	strncat(FinalPath, "/", PATHLEN-1-strlen(FinalPath));

	FPRINTF("[Line : %d][%s] Appended Path is : %s\\n", __LINE__, API_NAMESPACE, FinalPath);
}

/**
* @function 		DeleteAllMedia
* @description	 	Delete All Media From DB
* @parameter		NA
* @return 			NA
*/
bool DeleteAllMedia(void)
{
	filter_h hFilter = NULL;
	int nRet = media_filter_create(&hFilter);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_create", MediaContentGetError(nRet));

	nRet = media_filter_set_condition(hFilter, "MEDIA_TYPE=0 OR MEDIA_TYPE=1 OR MEDIA_TYPE=2 OR MEDIA_TYPE=3", MEDIA_CONTENT_COLLATE_NOCASE);
	PRINT_RESULT_CLEANUP(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_set_condition", MediaContentGetError(nRet), media_filter_destroy(hFilter));

	nRet = media_filter_destroy(hFilter);
	PRINT_RESULT(MEDIA_CONTENT_ERROR_NONE, nRet, "media_filter_destroy", MediaContentGetError(nRet));

	return 0;
}

/**
* @function 		GetExternalStorageIdandPath
* @description	 	Called to get internal storage id and path
* @parameter		NA
* @return 			NA
*/
bool GetExternalStorageIdandPath(void)
{
	g_CallBackHit = false;
	int nRet = storage_foreach_device_supported(StorageForeachCallBack, NULL);
	PRINT_RESULT(STORAGE_ERROR_NONE, nRet, "storage_foreach_device_supported", StorageGetError(nRet));

	IterateGmainLoop();
	PRINT_RESULT(true, g_CallBackHit, "storage_foreach_device_supported", "CallBack Not Invoked");

	return 0;
}

/**
* @function 		RemoveFileInfo
* @parameter		NA
* @return 			NA
*/
void RemoveFileInfo(const char *data)
{
	FPRINTF("[Line : %d][%s] %s\\n", __LINE__, API_NAMESPACE,data);
	char pszCommand[256] = {0, };
	memset(pszCommand, 0, sizeof(pszCommand));
	if ( 0 == strncmp(data, "audio", strlen(data)) )
	{
		snprintf(pszCommand, sizeof(pszCommand), "/bin/rm -rf %s", g_szAudioPath);
	}
	else if ( 0 == strncmp(data, "image", strlen(data)) )
	{
		snprintf(pszCommand, sizeof(pszCommand), "/bin/rm -rf %s", g_szImagePath);
	}
	else if ( 0 == strncmp(data, "video", strlen(data)) )
	{
		snprintf(pszCommand, sizeof(pszCommand), "/bin/rm -rf %s", g_szVideoPath);
	}
	FPRINTF("[Line : %d][%s] %s\\n", __LINE__, API_NAMESPACE,pszCommand);
	system(pszCommand);
	return;
}

/**
* @function 		CopyFileInfo
* @parameter		NA
* @return 			NA
*/
void CopyFileInfo(const char *data)
{
	FPRINTF("[Line : %d][%s] %s\\n", __LINE__, API_NAMESPACE,data);
	char pszCommand[256] = {0, };
	memset(pszCommand, 0x0, sizeof(pszCommand));
	if ( 0 == strncmp(data, "audio", strlen(data)) )
	{
		snprintf(pszCommand, sizeof(pszCommand), "/bin/cp %s/res/TestAudio.mp3 %s/TestAudio.mp3", g_szAudioFolder,g_szAudioFolder);
	}
	else if ( 0 == strncmp(data, "image", strlen(data)) )
	{
		snprintf(pszCommand, sizeof(pszCommand), "/bin/cp %s/res/TestImage.jpg %s/TestImage.jpg", g_szImageFolder,g_szImageFolder);
	}
	else if ( 0 == strncmp(data, "video", strlen(data)) )
	{
		snprintf(pszCommand, sizeof(pszCommand), "/bin/cp %s/res/TestVideo.mp4 %s/TestVideo.mp4", g_szVideoFolder,g_szVideoFolder);
	}

	system(pszCommand);
	FPRINTF("[Line : %d][%s] %s\\n", __LINE__, API_NAMESPACE,pszCommand);
	return;
}
/** @} */
