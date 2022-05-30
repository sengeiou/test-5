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

/**
* @function 		ITs_url_download_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_url_download_set_get_startup(void)
{
	g_bUrlDownloadOpen = false;
	g_bDownloadNotSupported = false;
	g_bDownloadMismatch = false;
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Url_Download_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = download_create(&g_nDownloadRequestID);
	bool bFeatureDownload  = TCTCheckSystemInfoFeatureSupported(DOWNLOAD_FEATURE, API_NAMESPACE);

	if(!bFeatureDownload)
	{
		if(nRet == DOWNLOAD_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] download_create() returned %s error for unsupported feature :success \\n", __LINE__,
				API_NAMESPACE, UrlDownloadGetError(nRet));
			g_bDownloadNotSupported = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] download_create() returned %s error for unsupported feature, error mismatch :Failure \\n",
			 __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
			g_bDownloadMismatch = true;
		}

		return;
	}

	if ( nRet != DOWNLOAD_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] download_create failed in startup, error returned = %s\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
	}
	else
	{
		g_bUrlDownloadOpen = true;
#if DEBUG
		FPRINTF("[Line : %d][%s] download_create passed in startup\\n", __LINE__, API_NAMESPACE);
#endif
	}
}

/**
* @function 		ITs_url_download_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_url_download_set_get_cleanup(void)
{

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Url_Download_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bUrlDownloadOpen )
	{
		int nRet = download_destroy(g_nDownloadRequestID);
		if ( nRet != DOWNLOAD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] download_destroy failed in cleanup, error returned = %s\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
		}
		else
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] download_destroy passed in cleanup\\n", __LINE__, API_NAMESPACE);
#endif
		}
	}
}

/** @addtogroup itc-url-download-testcases
*  @brief 		Integration testcases for module url-download
*  @ingroup 	itc-url-download
*  @{
*/

//& type: auto
//& purpose: scenario to set and get app control handle to register notification messages
/**
* @testcase 			ITc_download_set_get_notification_app_control_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to set and get app control handle to register notification messages
* @scenario				create a app control handle\n
* 						set app control handle to register notification messages\n
* 						get app control handle to register notification messages\n
* 						compare set and get values\n
* 						free the get app control handle\n
* 						destroy the app control handle
* @apicovered			download_set_notification_app_control, download_get_notification_app_control
* @passcase				if download_set_notification_app_control and download_get_notification_app_control returns success and set and get values are same
* @failcase				if download_set_notification_app_control or download_get_notification_app_control returns failure or set and get values are not same
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_get_notification_app_control_p(void)
{
	START_TEST;
	int nRet = 0;
	app_control_h pstAppControlHandle = {0};
	app_control_h pstGetAppControlHandle = {0};
	char *pszKey = "Sample_Key";		//sample key-value string
	char *pszValue = "Sample_Value";

	nRet = app_control_create(&pstAppControlHandle);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", UrlDownloadAppControlGetError(nRet));
	CHECK_HANDLE(pstAppControlHandle,"app_control_create");

	nRet = app_control_add_extra_data(pstAppControlHandle, pszKey, pszValue);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_extra_data", UrlDownloadAppControlGetError(nRet), app_control_destroy(pstAppControlHandle));

	nRet = download_set_notification_app_control(g_nDownloadRequestID, DOWNLOAD_NOTIFICATION_APP_CONTROL_TYPE_ONGOING, pstAppControlHandle);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_set_notification_app_control", UrlDownloadGetError(nRet), app_control_destroy(pstAppControlHandle));

	// Target API
	nRet = download_get_notification_app_control(g_nDownloadRequestID, DOWNLOAD_NOTIFICATION_APP_CONTROL_TYPE_ONGOING, &pstGetAppControlHandle);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_notification_app_control", UrlDownloadGetError(nRet), app_control_destroy(pstAppControlHandle));
	CHECK_HANDLE_CLEANUP(pstGetAppControlHandle,"download_get_notification_app_control",app_control_destroy(pstAppControlHandle));
	FREE_MEMORY(pstGetAppControlHandle);

	nRet = app_control_destroy(pstAppControlHandle);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", UrlDownloadAppControlGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to set auto download to enable and check if auto download is enabled
/**
* @testcase 			ITc_download_set_get_auto_download_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to enable auto download and check if auto download is enabled
* @scenario				enable auto download\n
* 						get auto download value\n
* 						check if auto download is enabled
* @apicovered			download_get_auto_download, download_set_auto_download
* @passcase				if download_get_auto_download and download_set_auto_download returns success
* @failcase				if download_get_auto_download or download_set_auto_download returns fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_get_auto_download_p(void)
{
	START_TEST;
	int nRet = 0;
	bool bSetStatus = true, bGetStatus;

	nRet = download_set_auto_download(g_nDownloadRequestID, bSetStatus);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_auto_download", UrlDownloadGetError(nRet));

	// Target API
	nRet = download_get_auto_download(g_nDownloadRequestID, &bGetStatus);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_get_auto_download", UrlDownloadGetError(nRet));
	if ( bGetStatus != bSetStatus)
	{
		FPRINTF("[Line : %d][%s] download_get_auto_download failed, error returned = Get and Set values are not same\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: scenario to set and get the destination path for the downloaded file and compare the set get path
/**
* @testcase 			ITc_download_set_get_destination_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to set and get the destination path for the downloaded file and compare the set get path
* @scenario				set the destination path for the downloaded file\n
* 						get the destination path for the downloaded file\n
* 						check if destination path are same
* @apicovered			download_set_destination, download_get_destination
* @passcase				if download_set_destination, download_get_destination returns success and get path is same as set path
* @failcase				if download_set_destination, download_get_destination returns fail or get path is not same as set path
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_get_destination_p(void)
{
	START_TEST;
	int nRet = 0;
	char *pszGetStatus = NULL;
	char *pszSetStatus = UrlDownloadGetStorageDirectory();

	if (pszSetStatus == NULL)
	{
		FPRINTF("[Line : %d][%s] UrlDownloadGetStorageDirectory() returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] ITc_download_set_get_destination_p: input path [%s]\\n", __LINE__, API_NAMESPACE, pszSetStatus);
#endif
	nRet = download_set_destination(g_nDownloadRequestID, pszSetStatus);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_set_destination", UrlDownloadGetError(nRet),FREE_MEMORY(pszSetStatus));

	// Target API
	nRet = download_get_destination(g_nDownloadRequestID, &pszGetStatus);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_destination", UrlDownloadGetError(nRet),FREE_MEMORY(pszSetStatus));
	if(strcmp(pszSetStatus,pszGetStatus) != 0)
	{
		FPRINTF("[Line : %d][%s] download_get_destination, error = set get value are not same. set value = %s get value = %s \\n", __LINE__, API_NAMESPACE, pszSetStatus, pszGetStatus);
		FREE_MEMORY(pszSetStatus);
		FREE_MEMORY(pszGetStatus);
		return 1;
	}
	FREE_MEMORY(pszSetStatus);
	FREE_MEMORY(pszGetStatus);
	return 0;
}

//& type: auto
//& purpose: scenario to set and get the name for the downloaded file and compare the set get value
/**
* @testcase 			ITc_download_set_get_file_name_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to set and get the name for the downloaded file and compare the set get value
* @scenario				set the name for the downloaded file\n
* 						get the name for the downloaded file\n
* 						check if set and get values are same
* @apicovered			download_set_file_name, download_get_file_name
* @passcase				if download_set_file_name, download_get_file_name returns success and get value is same as set value
* @failcase				if download_set_file_name, download_get_file_name returns fail or get value is not same as set value
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_get_file_name_p(void)
{
	START_TEST;
	int nRet = 0;
	char *pszSetStatus = "TestFileName", *pszGetStatus = NULL;

	nRet = download_set_file_name(g_nDownloadRequestID, pszSetStatus);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_file_name", UrlDownloadGetError(nRet));

	// Target API
	nRet = download_get_file_name(g_nDownloadRequestID, &pszGetStatus);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_get_file_name", UrlDownloadGetError(nRet));
	if(strcmp(pszSetStatus,pszGetStatus) != 0)
	{
		FPRINTF("[Line : %d][%s] download_get_file_name, error = set get value are not same. set value = %s get value = %s \\n", __LINE__, API_NAMESPACE, pszSetStatus, pszGetStatus);
		FREE_MEMORY(pszGetStatus);
		return 1;
	}
	FREE_MEMORY(pszGetStatus);
	return 0;
}

//& type: auto
//& purpose: scenario to set and get the allowed network type for the downloaded file and compare the set get value
/**
* @testcase 			ITc_download_set_get_network_type_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to set and get the allowed network type for the downloaded file and compare the set get value
* @scenario				set the allowed network type for the downloaded file\n
* 						get the allowed network type for the downloaded file\n
* 						check if set and get values are same
* @apicovered			download_set_network_type, download_get_network_type
* @passcase				if download_set_network_type, download_get_network_type returns success and get value is same as set value
* @failcase				if download_set_network_type, download_get_network_type returns fail or get value is not same as set value
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_get_network_type_p(void)
{
	START_TEST;
	g_bIsTelephonyFeatureSupported = false;
	g_bIsWifiFeatureSupported = false;
	g_bIsWifiDirectFeatureSupported = false;
	bool isSupported = false;

    g_bIsTelephonyFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);
    g_bIsWifiFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
    g_bIsWifiDirectFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIFI_DIRECT_FEATURE, API_NAMESPACE);

	download_network_type_e eGetNewtorkType, eSetNewtorkType[] = {	DOWNLOAD_NETWORK_DATA_NETWORK,
		DOWNLOAD_NETWORK_WIFI,
		DOWNLOAD_NETWORK_WIFI_DIRECT,
		DOWNLOAD_NETWORK_ALL };

	int nEnumSize = sizeof(eSetNewtorkType) / sizeof(eSetNewtorkType[0]);
	int nEnumCounter = 0;

	for (nEnumCounter = 0;nEnumCounter < nEnumSize;nEnumCounter++)
	{
		// Target API
		int nRet = download_set_network_type(g_nDownloadRequestID, eSetNewtorkType[nEnumCounter]);
		switch (eSetNewtorkType[nEnumCounter])
		{
			case DOWNLOAD_NETWORK_DATA_NETWORK:
				if ( !g_bIsTelephonyFeatureSupported )
				{
					if ( nRet != DOWNLOAD_ERROR_NOT_SUPPORTED )
					{
						FPRINTF("[Line : %d][%s] download_set_network_type returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
						return 1;
					}
					isSupported = false;
					FPRINTF("[Line : %d][%s] download_set_network_type API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
				}
				else
				{
					isSupported = true;
				}
				break;
			case DOWNLOAD_NETWORK_WIFI:
				if ( !g_bIsWifiFeatureSupported )
				{
					if ( nRet != DOWNLOAD_ERROR_NOT_SUPPORTED )
					{
						FPRINTF("[Line : %d][%s] download_set_network_type returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
						return 1;
					}
					isSupported = false;
					FPRINTF("[Line : %d][%s] download_set_network_type API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
				}
				else
				{
					isSupported = true;
				}
				break;
			case DOWNLOAD_NETWORK_WIFI_DIRECT:
				if ( !g_bIsWifiDirectFeatureSupported )
				{
					if ( nRet != DOWNLOAD_ERROR_NOT_SUPPORTED )
					{
						FPRINTF("[Line : %d][%s] download_set_network_type returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
						return 1;
					}
					isSupported = false;
					FPRINTF("[Line : %d][%s] download_set_network_type API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
				}
				else
				{
					isSupported = true;
				}
				break;
			case DOWNLOAD_NETWORK_ALL:
				if ( !g_bIsTelephonyFeatureSupported && !g_bIsWifiFeatureSupported && !g_bIsWifiDirectFeatureSupported)
				{
					if ( nRet != DOWNLOAD_ERROR_NOT_SUPPORTED )
					{
						FPRINTF("[Line : %d][%s] download_set_network_type returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
						return 1;
					}
					isSupported = false;
					FPRINTF("[Line : %d][%s] download_set_network_type API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
				}
				else
				{
					isSupported = true;
				}
				break;
		}
		if(isSupported == true)
		{
			PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_network_type", UrlDownloadGetError(nRet));
			nRet = download_get_network_type(g_nDownloadRequestID, &eGetNewtorkType);
			PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_get_network_type", UrlDownloadGetError(nRet));
			if ( eSetNewtorkType[nEnumCounter] != eGetNewtorkType )
			{
				FPRINTF("[Line : %d][%s] download_get_network_type failed, error returned = Get and Set values are not same. Get Value = %s, Set Value = %s\\n", __LINE__, API_NAMESPACE, UrlDownloadNetworkType(eGetNewtorkType), UrlDownloadNetworkType(eSetNewtorkType[nEnumCounter]));
				return 1;
			}
		}
		else
		{
			PRINT_RESULT(DOWNLOAD_ERROR_NOT_SUPPORTED, nRet, "download_set_network_type", UrlDownloadGetError(nRet));
			nRet = download_get_network_type(g_nDownloadRequestID, &eGetNewtorkType);
			PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_get_network_type", UrlDownloadGetError(nRet));
		}

	}

	return 0;
}

//& type: auto
//& purpose: scenario to set and get the description of a notification and compare the set get value
/**
* @testcase 			ITc_download_set_get_notification_description_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to set and get the description of a notification and compare the set get value
* @scenario				set the description of a notification\n
* 						get the description of a notification\n
* 						check if set and get values are same
* @apicovered			download_get_notification_description, download_set_notification_description
* @passcase				if download_get_notification_description, download_set_notification_description returns success and get value is same as set value
* @failcase				if download_get_notification_description, download_set_notification_description returns fail or get value is not same as set value
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_get_notification_description_p(void)
{
	START_TEST;

	char *pszSetNotification = "NotificationDummy", *pszGetNotification = NULL;
	int nRet = download_set_notification_description(g_nDownloadRequestID, pszSetNotification);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_notification_description", UrlDownloadGetError(nRet));

	// Target API
	nRet = download_get_notification_description(g_nDownloadRequestID, &pszGetNotification);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_get_notification_description", UrlDownloadGetError(nRet));
	if ( strcmp(pszGetNotification, pszSetNotification) != 0 )
	{
		FPRINTF("[Line : %d][%s] download_get_notification_description failed, error returned = Get and Set values are not same. Get Value = %s, Set Value = %s\\n", __LINE__, API_NAMESPACE, pszGetNotification, pszSetNotification);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: scenario to set and get the title of a notification and compare the set get value
/**
* @testcase 			ITc_download_set_get_notification_title_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to set and get the title of a notification and compare the set get value
* @scenario				set the title of a notification\n
* 						get the title of a notification\n
* 						check if set and get values are same
* @apicovered			download_get_notification_title, download_set_notification_title
* @passcase				if download_get_notification_title, download_set_notification_title returns success and get value is same as set value
* @failcase				if download_get_notification_title, download_set_notification_title returns fail or get value is not same as set value
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_get_notification_title_p(void)
{
	START_TEST;

	char *pszSetNotification = "NotificationDummy", *pszGetNotification = NULL;
	int nRet = download_set_notification_title(g_nDownloadRequestID, pszSetNotification);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_notification_title", UrlDownloadGetError(nRet));

	// Target API
	nRet = download_get_notification_title(g_nDownloadRequestID, &pszGetNotification);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_get_notification_title", UrlDownloadGetError(nRet));
	if ( strcmp(pszGetNotification, pszSetNotification) != 0 )
	{
		FPRINTF("[Line : %d][%s] download_get_notification_title failed, error returned = Get and Set values are not same. Get Value = %s, Set Value = %s\\n", __LINE__, API_NAMESPACE, pszGetNotification, pszSetNotification);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: scenario to set and get an option value to register notification messages and compare the set get value
/**
* @testcase 			ITc_download_set_get_notification_type_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to set and get an option value to register notification messages and compare the set get value
* @scenario				set an option value to register notification messages\n
* 						get an option value to register notification messages\n
* 						check if set and get values are same
* @apicovered			download_set_notification_type, download_get_notification_type
* @passcase				if download_set_notification_type, download_get_notification_type returns success and get value is same as set value
* @failcase				if download_set_notification_type, download_get_notification_type returns fail or get value is not same as set value
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_get_notification_type_p(void)
{
	START_TEST;

	download_notification_type_e eGetDownloadNotification, eSetDownloadNotification [] = { DOWNLOAD_NOTIFICATION_TYPE_NONE,
		DOWNLOAD_NOTIFICATION_TYPE_COMPLETE_ONLY,
		DOWNLOAD_NOTIFICATION_TYPE_ALL };

	int nEnumSize = sizeof(eSetDownloadNotification) / sizeof(eSetDownloadNotification[0]);
	int nEnumCounter = 0;

	for (nEnumCounter = 0;nEnumCounter < nEnumSize;nEnumCounter++)
	{
		int nRet = download_set_notification_type(g_nDownloadRequestID, eSetDownloadNotification[nEnumCounter]);
		PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_notification_type", UrlDownloadGetError(nRet));

		// Target API
		nRet = download_get_notification_type(g_nDownloadRequestID, &eGetDownloadNotification);
		PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_get_notification_type", UrlDownloadGetError(nRet));
		if ( eGetDownloadNotification != eSetDownloadNotification[nEnumCounter] )
		{
			FPRINTF("[Line : %d][%s] download_get_notification_type failed, error returned = Get and Set values are not same. Get Value = %s, Set Value = %s\\n", __LINE__, API_NAMESPACE, UrlDownloadNotificationType(eGetDownloadNotification), UrlDownloadNotificationType(eSetDownloadNotification[nEnumCounter]));
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: scenario to set and get the URL to download and compare the set get value
/**
* @testcase 			ITc_download_set_get_url_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to set and get the URL to download and compare the set get value
* @scenario				set the URL to download\n
* 						get the URL to download\n
* 						check if set and get values are same
* @apicovered			download_get_url, download_set_url
* @passcase				if download_get_url, download_set_url returns success and get value is same as set value
* @failcase				if download_get_url, download_set_url returns fail or get value is not same as set value
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_get_url_p(void)
{
	START_TEST;

	char *pszSetURL = "tizen.com", *pszGetURL = NULL;
	int nRet = download_set_url(g_nDownloadRequestID, pszSetURL);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_url", UrlDownloadGetError(nRet));

	// Target API
	nRet = download_get_url(g_nDownloadRequestID, &pszGetURL);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_get_url", UrlDownloadGetError(nRet));
	if ( strcmp(pszGetURL, pszSetURL) != 0 )
	{
		FPRINTF("[Line : %d][%s] download_get_url failed, error returned = Get and Set values are not same. Get Value = %s, Set Value = %s\\n", __LINE__, API_NAMESPACE, pszGetURL, pszSetURL);
		FREE_MEMORY(pszGetURL);
		return 1;
	}
	FREE_MEMORY(pszGetURL);
	return 0;
}

//& type: auto
//& purpose: scenario to register and unregister callback function to be invoked when a download state is changed
/**
* @testcase 			ITc_download_set_get_state_changed_cb_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to register and unregister callback function to be invoked when a download state is changed
* @scenario				register callback function to be invoked when a download state is changed\n
* 						check if callback is called after download state is changed\n
* 						unregister callback function to be invoked when a download state is changed\n
* 						check that callback is not called after download state is changed
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb,download_start, download_cancel
* @passcase				if download_set_state_changed_cb, download_unset_state_changed_cb returns success and callback is called after downloading state is changed after callback is registered also callback should not be called after downloading state is changed after callback is unregistered
* @failcase				if download_set_state_changed_cb, download_unset_state_changed_cb returns fail or callback is not called after downloading state is changed after callback is registered or if callback is called after downloading state is changed after callback is unregistered
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct URL of a file to be downloaded must be updated as URLDOWNLOAD_URL_I586 or URLDOWNLOAD_URL_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_get_state_changed_cb_p(void)
{
	START_TEST;

	int nState = 0, nURLTimeoutId = -1;
	if ( UrlDownloadCreateEnv(g_nDownloadRequestID, false) != true )
	{
		FPRINTF("[Line : %d][%s] PreCondition in UrlDownloadCreateEnv failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = download_set_state_changed_cb(g_nDownloadRequestID, DownloadStateCallback, (void*)&nState);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_state_changed_cb", UrlDownloadGetError(nRet));

	g_bDownloadingState = false;
	nRet = download_start(g_nDownloadRequestID);
	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( !g_bDownloadingState )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	download_cancel(g_nDownloadRequestID);//No check for return state as downloading might have been completed by now

	// Target API
	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));

	g_bDownloadingState = false;
	nRet = download_start(g_nDownloadRequestID);

	RUN_POLLING_LOOP;

	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet));
	if ( g_bDownloadingState )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = callback is invoked even after unregister\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}
