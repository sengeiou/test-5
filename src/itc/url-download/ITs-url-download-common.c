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
#include "ITs-url-download-common.h"

/** @addtogroup itc-url-download
*  @ingroup itc
*  @{
*/

/**
* @function 		UrlDownloadGetError
* @description	 	Maps enum values to string values
* @parameter		nRet : enum value
* @return 			string to enum value
*/
char* UrlDownloadGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case DOWNLOAD_ERROR_NONE:					szErrorVal = "DOWNLOAD_ERROR_NONE";							break;
	case DOWNLOAD_ERROR_INVALID_PARAMETER:		szErrorVal = "DOWNLOAD_ERROR_INVALID_PARAMETER";			break;
	case DOWNLOAD_ERROR_OUT_OF_MEMORY:			szErrorVal = "DOWNLOAD_ERROR_OUT_OF_MEMORY";				break;
	case DOWNLOAD_ERROR_NETWORK_UNREACHABLE:	szErrorVal = "DOWNLOAD_ERROR_NETWORK_UNREACHABLE";			break;
	case DOWNLOAD_ERROR_CONNECTION_TIMED_OUT:	szErrorVal = "DOWNLOAD_ERROR_CONNECTION_TIMED_OUT";			break;
	case DOWNLOAD_ERROR_NO_SPACE:				szErrorVal = "DOWNLOAD_ERROR_NO_SPACE";						break;
	case DOWNLOAD_ERROR_FIELD_NOT_FOUND:		szErrorVal = "DOWNLOAD_ERROR_FIELD_NOT_FOUND";				break;
	case DOWNLOAD_ERROR_PERMISSION_DENIED:		szErrorVal = "DOWNLOAD_ERROR_PERMISSION_DENIED";			break;
	case DOWNLOAD_ERROR_INVALID_STATE:			szErrorVal = "DOWNLOAD_ERROR_INVALID_STATE";				break;
	case DOWNLOAD_ERROR_CONNECTION_FAILED:		szErrorVal = "DOWNLOAD_ERROR_CONNECTION_FAILED";			break;
	case DOWNLOAD_ERROR_INVALID_URL:			szErrorVal = "DOWNLOAD_ERROR_INVALID_URL";					break;
	case DOWNLOAD_ERROR_INVALID_DESTINATION:	szErrorVal = "DOWNLOAD_ERROR_INVALID_DESTINATION";			break;
	case DOWNLOAD_ERROR_TOO_MANY_DOWNLOADS:		szErrorVal = "DOWNLOAD_ERROR_TOO_MANY_DOWNLOADS";			break;
	case DOWNLOAD_ERROR_QUEUE_FULL:				szErrorVal = "DOWNLOAD_ERROR_QUEUE_FULL";					break;
	case DOWNLOAD_ERROR_ALREADY_COMPLETED:		szErrorVal = "DOWNLOAD_ERROR_ALREADY_COMPLETED";			break;
	case DOWNLOAD_ERROR_FILE_ALREADY_EXISTS:	szErrorVal = "DOWNLOAD_ERROR_FILE_ALREADY_EXISTS";			break;
	case DOWNLOAD_ERROR_CANNOT_RESUME:			szErrorVal = "DOWNLOAD_ERROR_CANNOT_RESUME";				break;
	case DOWNLOAD_ERROR_TOO_MANY_REDIRECTS:		szErrorVal = "DOWNLOAD_ERROR_TOO_MANY_REDIRECTS";			break;
	case DOWNLOAD_ERROR_UNHANDLED_HTTP_CODE:	szErrorVal = "DOWNLOAD_ERROR_UNHANDLED_HTTP_CODE";			break;
	case DOWNLOAD_ERROR_REQUEST_TIMEOUT:		szErrorVal = "DOWNLOAD_ERROR_REQUEST_TIMEOUT";				break;
	case DOWNLOAD_ERROR_RESPONSE_TIMEOUT:		szErrorVal = "DOWNLOAD_ERROR_RESPONSE_TIMEOUT";				break;
	case DOWNLOAD_ERROR_SYSTEM_DOWN:			szErrorVal = "DOWNLOAD_ERROR_SYSTEM_DOWN";					break;
	case DOWNLOAD_ERROR_ID_NOT_FOUND:			szErrorVal = "DOWNLOAD_ERROR_ID_NOT_FOUND";					break;
	case DOWNLOAD_ERROR_INVALID_NETWORK_TYPE:	szErrorVal = "DOWNLOAD_ERROR_INVALID_NETWORK_TYPE";			break;
	case DOWNLOAD_ERROR_NO_DATA:				szErrorVal = "DOWNLOAD_ERROR_NO_DATA";						break;
	case DOWNLOAD_ERROR_IO_ERROR:				szErrorVal = "DOWNLOAD_ERROR_IO_ERROR";						break;
	case DOWNLOAD_ERROR_NOT_SUPPORTED:		szErrorVal = "DOWNLOAD_ERROR_NOT_SUPPORTED";				break;
	default:					szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}

/**
* @function 		UrlDownloadNetworkType
* @description	 	Maps enum values to string values
* @parameter		nRet : enum value
* @return 			string to enum value
*/
char* UrlDownloadNetworkType(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case DOWNLOAD_NETWORK_DATA_NETWORK:			szErrorVal = "DOWNLOAD_NETWORK_DATA_NETWORK";			break;
	case DOWNLOAD_NETWORK_WIFI:					szErrorVal = "DOWNLOAD_NETWORK_WIFI";					break;
	case DOWNLOAD_NETWORK_WIFI_DIRECT:			szErrorVal = "DOWNLOAD_NETWORK_WIFI_DIRECT";			break;
	case DOWNLOAD_NETWORK_ALL:					szErrorVal = "DOWNLOAD_NETWORK_ALL";					break;
	default:									szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

/**
* @function 		UrlDownloadNotificationType
* @description	 	Maps enum values to string values
* @parameter		nRet : enum value
* @return 			string to enum value
*/
char* UrlDownloadNotificationType(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case DOWNLOAD_NOTIFICATION_TYPE_NONE:				szErrorVal = "DOWNLOAD_NOTIFICATION_TYPE_NONE";				break;
	case DOWNLOAD_NOTIFICATION_TYPE_COMPLETE_ONLY:		szErrorVal = "DOWNLOAD_NOTIFICATION_TYPE_COMPLETE_ONLY";	break;
	case DOWNLOAD_NOTIFICATION_TYPE_ALL:				szErrorVal = "DOWNLOAD_NOTIFICATION_TYPE_ALL";				break;
	default:											szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}


/**
* @function 		UrlDownloadState
* @description	 	Maps enum values to string values
* @parameter		nRet : enum value
* @return 			string to enum value
*/
char* UrlDownloadState(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case DOWNLOAD_STATE_NONE:					szErrorVal = "DOWNLOAD_STATE_NONE";					break;
	case DOWNLOAD_STATE_READY:					szErrorVal = "DOWNLOAD_STATE_READY";				break;
	case DOWNLOAD_STATE_QUEUED:					szErrorVal = "DOWNLOAD_STATE_QUEUED";				break;
	case DOWNLOAD_STATE_DOWNLOADING:			szErrorVal = "DOWNLOAD_STATE_DOWNLOADING";			break;
	case DOWNLOAD_STATE_PAUSED:					szErrorVal = "DOWNLOAD_STATE_PAUSED";				break;
	case DOWNLOAD_STATE_COMPLETED:				szErrorVal = "DOWNLOAD_STATE_COMPLETED";			break;
	case DOWNLOAD_STATE_FAILED:					szErrorVal = "DOWNLOAD_STATE_FAILED";				break;
	case DOWNLOAD_STATE_CANCELED:				szErrorVal = "DOWNLOAD_STATE_CANCELED";				break;
	default:									szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}

/**
* @function 		UrlDownloadAppControlGetError
* @description	 	Maps enum values to string values
* @parameter		nRet : enum value
* @return 			string to enum value
*/
char* UrlDownloadAppControlGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case APP_CONTROL_ERROR_NONE :					szErrorVal = "APP_CONTROL_ERROR_NONE";					break;
	case APP_CONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_CONTROL_ERROR_INVALID_PARAMETER";		break;
	case APP_CONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_CONTROL_ERROR_OUT_OF_MEMORY";			break;
	case APP_CONTROL_ERROR_APP_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_APP_NOT_FOUND";			break;
	case APP_CONTROL_ERROR_KEY_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_KEY_NOT_FOUND";			break;
	case APP_CONTROL_ERROR_KEY_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_KEY_REJECTED";			break;
	case APP_CONTROL_ERROR_INVALID_DATA_TYPE:		szErrorVal = "APP_CONTROL_ERROR_INVALID_DATA_TYPE";		break;
	case APP_CONTROL_ERROR_LAUNCH_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_REJECTED";		break;
	case APP_CONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_CONTROL_ERROR_PERMISSION_DENIED";		break;
	default:										szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

/**
* @function 		UrlDownloadCreateEnv
* @description	 	create the pre-requisite conditions
* @parameter		nRequestId : download request id, bIsDownload : flag to check if download is required
* @return 			true : for sucess, false : for error
*/
bool UrlDownloadCreateEnv(int nRequestId, bool bIsDownload)
{
	int nRet = 0;

	download_network_type_e eSetNewtorkType[] = { DOWNLOAD_NETWORK_DATA_NETWORK, DOWNLOAD_NETWORK_WIFI };
	int nEnumSize = sizeof(eSetNewtorkType) / sizeof(eSetNewtorkType[0]);
	int nEnumCounter = 0, allowedNetworkTypeCount = 0;

	bool isTelephonyFeatureSupported = false;
	bool isWifiFeatureSupported = false;
	bool isWifiDirectFeatureSupported = false;

	isTelephonyFeatureSupported= TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);
	isWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	isWifiDirectFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_DIRECT_FEATURE, API_NAMESPACE);

	if (!isTelephonyFeatureSupported && !isWifiFeatureSupported && !isWifiDirectFeatureSupported) {
		for (nEnumCounter = 0;nEnumCounter < nEnumSize;nEnumCounter++)
		{
			nRet = download_set_network_type(nRequestId, eSetNewtorkType[nEnumCounter]);
			if ( nRet == DOWNLOAD_ERROR_NONE )
			{
				allowedNetworkTypeCount++;
				FPRINTF("[Line : %d][%s] download_set_network_type succeeded for iteration %d\\n", __LINE__, API_NAMESPACE, nEnumCounter);
			}
		}
		if ( allowedNetworkTypeCount == 2 )
		{
			nRet = download_set_network_type(nRequestId, DOWNLOAD_NETWORK_ALL);
			if ( nRet != DOWNLOAD_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] download_set_network_type failed for DOWNLOAD_NETWORK_ALL\\n", __LINE__, API_NAMESPACE, nEnumCounter);
				return false;
			}
		}
		else if ( allowedNetworkTypeCount == 0 )
		{
			FPRINTF("[Line : %d][%s] download_set_network_type failed for data network and wifi\\n", __LINE__, API_NAMESPACE);
			return false;
		}
	}

	char pstrValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( bIsDownload )
	{
		if ( true == GetValueFromConfigFile("URLDOWNLOAD_DOWNLOADURL", pstrValue, API_NAMESPACE) )
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, pstrValue);
#endif
		}
		else
		{
			FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
			return false;
		}

		nRet = download_set_url(nRequestId, pstrValue);
		if ( nRet != DOWNLOAD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] download_set_url failed, error returned = %s\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
			return false;
		}
	}
	else
	{
		if ( true == GetValueFromConfigFile("URLDOWNLOAD_URL", pstrValue, API_NAMESPACE) )
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, pstrValue);
#endif
		}
		else
		{
			FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
			return false;
		}

		nRet = download_set_url(nRequestId, pstrValue);
		if ( nRet != DOWNLOAD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] download_set_url failed, error returned = %s\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
			return false;
		}
	}

	if ( nRet != DOWNLOAD_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] download_set_url failed, error returned = %s\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
		return false;
	}
	else
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] download_set_url passed\\n", __LINE__, API_NAMESPACE);
#endif
	}
	return true;
}

/**
* @function 		UrlDownloadCallbackTimeout
* @description	 	callback function to terminate g_main loop
* @parameter		data : user data sent to callback
* @return 			NA
*/
gboolean UrlDownloadCallbackTimeout(gpointer data)
{
	GMainLoop* pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	return FALSE;
}

/**
* @function 		UrlDownloadCreateEventLoop
* @description	 	Create Event Loop to support callbacks
* @parameter		pArg : handle to g_main loop
* @return 			NA
*/
/*void* UrlDownloadCreateEventLoop(void* pArg)
{
	g_type_init();
	g_pMainLoop = g_main_loop_new(NULL, FALSE);

	int nTimeoutId = g_timeout_add(GMAINTIMEOUT, UrlDownloadCallbackTimeout, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTimeoutId);
	g_pMainLoop = NULL;
	return NULL;
}*/

/**
* @function 		DownloadProgressCallback
* @description	 	callback function for downloading progress change
* @parameter		download_id : download request id, received : size of the data received in bytes, user_data : user data passed to callback
* @return 			NA
*/
void DownloadProgressCallback (int download_id, unsigned long long received, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DownloadProgressCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		DownloadStateCallback
* @description	 	callback function for downloading state change
* @parameter		download_id : download request id, state : downloading state, user_data : user data passed to callback
* @return 			NA
*/
void DownloadStateCallback(int download_id, download_state_e state, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DownloadStateCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	int *pnComplete = (int *)user_data;
	if ( state == DOWNLOAD_STATE_DOWNLOADING )
	{
		g_bDownloadingState = true;
		if ( *pnComplete == 0 )
		{
			g_bCheckCb = true;
			if ( g_pMainLoop )
			{
				g_main_loop_quit(g_pMainLoop);
				g_main_loop_unref(g_pMainLoop);
				g_pMainLoop = NULL;
			}
		}
	}

	if ( state == DOWNLOAD_STATE_COMPLETED || state == DOWNLOAD_STATE_FAILED )
	{
		g_bDownloadingComplete = true;
		if ( *pnComplete == 1 )
		{
			g_bCheckCb = true;
			if ( g_pMainLoop )
			{
				g_main_loop_quit(g_pMainLoop);
				g_main_loop_unref(g_pMainLoop);
				g_pMainLoop = NULL;
			}
		}
	}
}

/**
* @function 		UrlDownloadGetStorageDirectory
* @description	 	Get download directory from configuration file
* @parameter		N/A
* @return 			download directory
*/
char* UrlDownloadGetStorageDirectory(void)
{
	char *pszFilePath = NULL;
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

	if ( true == GetValueForTCTSetting("DEVICE_PHYSICAL_STORAGE_30", pszValue, API_NAMESPACE ))
	{
		int path_size = strlen(pszValue) + strlen("/Downloads") + 1;
		pszFilePath = (char*)calloc(path_size, sizeof(char));
		if( NULL == pszFilePath )
		{
			return NULL;
		}
		snprintf(pszFilePath, path_size, "%s/Downloads", pszValue);
	}
	else
	{
		return NULL;
	}

	return pszFilePath;
}

/** @} */
