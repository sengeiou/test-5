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
* @function 		ITs_url_download_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_url_download_get_startup(void)
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
void ITs_url_download_get_cleanup(void)
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

//& type: auto
//& purpose: scenario to get the value associated with a added HTTP header field
/**
* @testcase 			ITc_download_get_http_header_field_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get the value associated with a added HTTP header field
* @scenario				add a HTTP header field to the download request\n
* 						get the value associated with a added HTTP header field\n
* 						remove added HTTP header field from the download
* @apicovered			download_add_http_header_field, download_get_http_header_field, download_remove_http_header_field
* @passcase				if download_add_http_header_field, download_get_http_header_field, download_remove_http_header_field returns success
* @failcase				if download_add_http_header_field, download_get_http_header_field, download_remove_http_header_field returns fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_http_header_field_p(void)
{
	START_TEST;
	int nRet = 0;
	const char *pszField = "TestField";
	const char *pszValue = "TestValue";
	char *pszGetValue = NULL;

	nRet = download_add_http_header_field(g_nDownloadRequestID, pszField, pszValue);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_add_http_header_field", UrlDownloadGetError(nRet));

	nRet = download_get_http_header_field(g_nDownloadRequestID, pszField, &pszGetValue);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_http_header_field", UrlDownloadGetError(nRet), download_remove_http_header_field(g_nDownloadRequestID, pszField));
	if ( pszGetValue == NULL )
	{
		FPRINTF("[Line : %d][%s] download_get_http_header_field failed, value returned = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( strcmp(pszGetValue, pszValue) != 0 )
	{
		FPRINTF("[Line : %d][%s] download_get_http_header_field failed, error returned = Add and Get value are not same. Add Value = %s, Get Value = %s\\n", __LINE__, API_NAMESPACE, pszValue, pszGetValue);
		download_remove_http_header_field(g_nDownloadRequestID, pszField);
		FREE_MEMORY(pszGetValue);
		return 1;
	}

	FREE_MEMORY(pszGetValue);

	nRet = download_remove_http_header_field(g_nDownloadRequestID, pszField);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_remove_http_header_field", UrlDownloadGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: scenario to get list of all the value associated with HTTP header field
/**
* @testcase 			ITc_download_get_http_header_field_list_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get list of all the value associated with HTTP header field
* @scenario				add a HTTP header field to the download request\n
* 						get list of all the value associated with HTTP header field\n
* 						remove added HTTP header field from the download
* @apicovered			download_add_http_header_field, download_get_http_header_field_list, download_remove_http_header_field
* @passcase				if download_add_http_header_field, download_get_http_header_field_list, download_remove_http_header_field returns success
* @failcase				if download_add_http_header_field, download_get_http_header_field_list, download_remove_http_header_field returns fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_http_header_field_list_p(void)
{
	START_TEST;
	int nRet = 0, nLength = 0;
	const char *pszField = "TestField";
	const char *pszValue = "TestValue";
	char **pszGetList = NULL;

	nRet = download_add_http_header_field(g_nDownloadRequestID, pszField, pszValue);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_add_http_header_field", UrlDownloadGetError(nRet));

	nRet = download_get_http_header_field_list(g_nDownloadRequestID, &pszGetList, &nLength);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_http_header_field_list", UrlDownloadGetError(nRet), download_remove_http_header_field(g_nDownloadRequestID, pszField));
	FREE_MEMORY(pszGetList);
	if ( nLength <= 0 )
	{
		FPRINTF("[Line : %d][%s] download_get_http_header_field_list failed, error returned = Get list count is not correct\\n", __LINE__, API_NAMESPACE);
		download_remove_http_header_field(g_nDownloadRequestID, pszField);
		return 1;
	}

	nRet = download_remove_http_header_field(g_nDownloadRequestID, pszField);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_remove_http_header_field", UrlDownloadGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to get the full path of the temporary file to store downloaded content
/**
* @testcase 			ITc_download_get_temp_path_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get the full path of the temporary file to store downloaded content
* @scenario				set the network type to all\n
* 						set the URL to download\n
* 						register download state change callback\n
* 						start the downloading the current URL\n
* 						get the full path of the temporary file to store downloaded content\n
* 						cancel downloading the current URL\n
* 						unregister the callback
* @apicovered			download_get_temp_path, download_set_state_changed_cb, download_unset_state_changed_cb, download_start, download_cancel
* @passcase				if download_get_temp_path returns success and get value is same as set value
* @failcase				if download_get_temp_path returns fail or get value is not same as set value
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_temp_path_p(void)
{
	START_TEST;

	int nState = 1, nURLTimeoutId = -1;
	char *pszTempPath = NULL;

	if ( UrlDownloadCreateEnv(g_nDownloadRequestID, true) != true )
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
		FPRINTF("[Line : %d][%s] download_start failed, error returned = downloading state is not achieved\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	// Target API
	nRet = download_get_temp_path(g_nDownloadRequestID, &pszTempPath);
	if ( nRet != DOWNLOAD_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] download_get_temp_path failed, error returned = %s\\n", __LINE__, API_NAMESPACE, UrlDownloadGetError(nRet));
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}
	if ( pszTempPath == NULL )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = downloading state is not achieved, temp path is NULL\\n", __LINE__, API_NAMESPACE);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	nRet = download_cancel(g_nDownloadRequestID);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_cancel", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to get the content name of downloaded file
/**
* @testcase 			ITc_download_get_content_name_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get the content name of downloaded file
* @scenario				set the network type to all\n
* 						set the URL to download\n
* 						register download state change callback\n
* 						start the downloading the current URL\n
* 						get the content name of downloaded file\n
* 						unregister the callback
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb, download_start, download_cancel, download_get_content_name
* @passcase				if download_get_content_name returns success and all supporting returns success
* @failcase				if download_get_content_name returns fail or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct url of a large size file must be updated as URLDOWNLOAD_DOWNLOADURL_I586 or URLDOWNLOAD_DOWNLOADURL_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_content_name_p(void)
{
	START_TEST;

	int nURLTimeoutId = -1, nState = 1;
	char *pszContentName = NULL;

	if ( UrlDownloadCreateEnv(g_nDownloadRequestID, false) != true )
	{
		FPRINTF("[Line : %d][%s] PreCondition in UrlDownloadCreateEnv failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = download_set_state_changed_cb(g_nDownloadRequestID, DownloadStateCallback, (void*)&nState);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_state_changed_cb", UrlDownloadGetError(nRet));

	g_bDownloadingComplete = false;
	nRet = download_start(g_nDownloadRequestID);

	RUN_POLLING_LOOP;

	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));

	if ( !g_bDownloadingComplete )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = downloading state complete is not achieved\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	// Target API
	nRet = download_get_content_name(g_nDownloadRequestID, &pszContentName);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_content_name", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( pszContentName == NULL )
	{
		FPRINTF("[Line : %d][%s] download_get_content_name failed, error returned = content name returned is NULL\\n", __LINE__, API_NAMESPACE);
		download_unset_state_changed_cb(g_nDownloadRequestID);
	}

	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to get the total size of downloaded content
/**
* @testcase 			ITc_download_get_content_size_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get the total size of downloaded content
* @scenario				set the network type to all\n
* 						set the URL to download\n
* 						register download state change callback\n
* 						start the downloading the current URL\n
* 						get the total size of downloaded content\n
* 						unregister the callback
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb, download_start, download_cancel, download_get_content_size
* @passcase				if download_get_content_size returns success and all supporting returns success
* @failcase				if download_get_content_size returns fail or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct url of a large size file must be updated as URLDOWNLOAD_DOWNLOADURL_I586 or URLDOWNLOAD_DOWNLOADURL_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_content_size_p(void)
{
	START_TEST;

	int nURLTimeoutId = -1, nState = 1;
	unsigned long long ullContentSize = 0L;

	if ( UrlDownloadCreateEnv(g_nDownloadRequestID, false) != true )
	{
		FPRINTF("[Line : %d][%s] PreCondition in UrlDownloadCreateEnv failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = download_set_state_changed_cb(g_nDownloadRequestID, DownloadStateCallback, (void*)&nState);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_state_changed_cb", UrlDownloadGetError(nRet));

	g_bDownloadingComplete = false;
	nRet = download_start(g_nDownloadRequestID);

	RUN_POLLING_LOOP;

	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( !g_bDownloadingComplete )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = downloading state complete is not achieved\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	// Target API
	nRet = download_get_content_size(g_nDownloadRequestID, &ullContentSize);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_content_size", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( ullContentSize == 0 )
	{
		FPRINTF("[Line : %d][%s] download_get_content_size failed, error returned = content size returned is zero\\n", __LINE__, API_NAMESPACE);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to get the absolute path to save the downloaded file
/**
* @testcase 			ITc_download_get_downloaded_file_path_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get the absolute path to save the downloaded file
* @scenario				set the network type to all\n
* 						set the URL to download\n
* 						register download state change callback\n
* 						start the downloading the current URL\n
* 						get the absolute path to save the downloaded file\n
* 						unregister the callback
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb, download_start, download_get_downloaded_file_path
* @passcase				if download_get_downloaded_file_path returns success and all supporting returns success
* @failcase				if download_get_downloaded_file_path returns fail or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct url of a large size file must be updated as URLDOWNLOAD_DOWNLOADURL_I586 or URLDOWNLOAD_DOWNLOADURL_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_downloaded_file_path_p(void)
{
	START_TEST;

	int nURLTimeoutId = -1, nState = 1;
	char *pszFilePath = NULL;

	if ( UrlDownloadCreateEnv(g_nDownloadRequestID, false) != true )
	{
		FPRINTF("[Line : %d][%s] PreCondition in UrlDownloadCreateEnv failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = download_set_state_changed_cb(g_nDownloadRequestID, DownloadStateCallback, (void*)&nState);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_state_changed_cb", UrlDownloadGetError(nRet));

	g_bDownloadingComplete = false;
	nRet = download_start(g_nDownloadRequestID);

	RUN_POLLING_LOOP;

	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( !g_bDownloadingComplete )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = downloading state complete is not achieved\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	// Target API
	nRet = download_get_downloaded_file_path(g_nDownloadRequestID, &pszFilePath);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_downloaded_file_path", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( pszFilePath == NULL )
	{
		FPRINTF("[Line : %d][%s] download_get_downloaded_file_path failed, error returned = file path returned is NULL\\n", __LINE__, API_NAMESPACE);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));
	return 0;
}
#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE)
//& type: auto
//& purpose: scenario to get an etag value from the HTTP response header when making a HTTP request for resume
/**
* @testcase 			ITc_download_get_etag_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get an etag value from the HTTP response header when making a HTTP request for resume
* @scenario				set the network type to all\n
* 						set the URL to download\n
* 						register download state change callback\n
* 						start the downloading the current URL\n
* 						get the etag value from the HTTP response header when making a HTTP request for resume\n
* 						unregister the callback
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb, download_set_url, download_start, download_get_etag
* @passcase				if download_get_etag returns success and all supporting returns success
* @failcase				if download_get_etag returns fail or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct url having etag response must be updated as URLDOWNLOAD_URLWITHETAG_I586 or URLDOWNLOAD_URLWITHETAG_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_etag_p(void)
{
	START_TEST;

	int nURLTimeoutId = -1, nState = 1;
	char *pszFilePath = NULL;
	char pstrValue[CONFIG_VALUE_LEN_MAX] = {0,};

	download_network_type_e eSetNewtorkType = DOWNLOAD_NETWORK_ALL;
	int nRet = download_set_network_type(g_nDownloadRequestID, eSetNewtorkType);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_network_type", UrlDownloadGetError(nRet));

	if ( true == GetValueFromConfigFile("URLDOWNLOAD_URLWITHETAG", pstrValue, API_NAMESPACE) )
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, pstrValue);
#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = download_set_url(g_nDownloadRequestID, pstrValue);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_url", UrlDownloadGetError(nRet));

	nRet = download_set_state_changed_cb(g_nDownloadRequestID, DownloadStateCallback, (void*)&nState);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_state_changed_cb", UrlDownloadGetError(nRet));

	g_bDownloadingState = false;
	nRet = download_start(g_nDownloadRequestID);
	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));

	if ( !g_bDownloadingState )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = downloading state is not achieved\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	// Target API
	nRet = download_get_etag(g_nDownloadRequestID, &pszFilePath);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_etag", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( pszFilePath == NULL )
	{
		FPRINTF("[Line : %d][%s] download_get_etag failed, error returned = eTag returned is NULL\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));
	return 0;
}
#endif //End MOBILE or WEARABLE

#ifdef TV	//Starts TV
//& type: auto
//& purpose: scenario to get an etag value from the HTTP response header when making a HTTP request for resume
/**
* @testcase 			ITc_download_get_etag_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get an etag value from the HTTP response header when making a HTTP request for resume
* @scenario				set the network type to all\n
* 						set the URL to download\n
* 						register download state change callback\n
* 						start the downloading the current URL\n
* 						get the etag value from the HTTP response header when making a HTTP request for resume\n
* 						unregister the callback
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb, download_set_url, download_start, download_get_etag
* @passcase				if download_get_etag returns success and all supporting returns success
* @failcase				if download_get_etag returns fail or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct url having etag response must be updated as URLDOWNLOAD_URLWITHETAG_I586 or URLDOWNLOAD_URLWITHETAG_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_etag_p(void)
{
	START_TEST;

	int nURLTimeoutId = -1, nState = 1;
	char *pszFilePath = NULL;
	char pstrValue[CONFIG_VALUE_LEN_MAX] = {0,};

	download_network_type_e eSetNewtorkType = DOWNLOAD_NETWORK_ALL;
	int nRet = download_set_network_type(g_nDownloadRequestID, eSetNewtorkType);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_network_type", UrlDownloadGetError(nRet));

	if ( true == GetValueFromConfigFile("URLDOWNLOAD_URL", pstrValue, API_NAMESPACE) )
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, pstrValue);
#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = download_set_url(g_nDownloadRequestID, pstrValue);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_url", UrlDownloadGetError(nRet));

	nRet = download_set_state_changed_cb(g_nDownloadRequestID, DownloadStateCallback, (void*)&nState);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_state_changed_cb", UrlDownloadGetError(nRet));

	g_bDownloadingState = false;
	nRet = download_start(g_nDownloadRequestID);
	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));

	if ( !g_bDownloadingState )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = downloading state is not achieved\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	// Target API
	nRet = download_get_etag(g_nDownloadRequestID, &pszFilePath);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_etag", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( pszFilePath == NULL )
	{
		FPRINTF("[Line : %d][%s] download_get_etag failed, error returned = eTag returned is NULL\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));
	return 0;
}
#endif  //TV	//End TV
//& type: auto
//& purpose: scenario to get a HTTP status code when a download error occurs
/**
* @testcase 			ITc_download_get_http_status_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get a HTTP status code when a download error occurs
* @scenario				set the network type to all\n
* 						set a URL to download\n
* 						register download state change callback\n
* 						start the downloading the URL\n
* 						get the a HTTP status code when a download error occurs\n
* 						unregister the callback
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb, download_start, download_get_http_status
* @passcase				if download_get_http_status returns success and all supporting returns success
* @failcase				if download_get_http_status returns fail or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct url of a large size file must be updated as URLDOWNLOAD_DOWNLOADURL_I586 or URLDOWNLOAD_DOWNLOADURL_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_http_status_p(void)
{
	START_TEST;

	int nStatus = 0, nDownloadStatus = 1, nURLTimeoutId = -1;
	if ( UrlDownloadCreateEnv(g_nDownloadRequestID, false) != true )
	{
		FPRINTF("[Line : %d][%s] PreCondition in UrlDownloadCreateEnv failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = download_set_state_changed_cb(g_nDownloadRequestID, DownloadStateCallback, (void*)&nDownloadStatus);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_state_changed_cb", UrlDownloadGetError(nRet));

	g_bDownloadingState = false;
	nRet = download_start(g_nDownloadRequestID);

	RUN_POLLING_LOOP;

	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));

	if ( !g_bDownloadingState )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = downloading state is not achieved\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	// Target API
	nRet = download_get_http_status(g_nDownloadRequestID, &nStatus);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_http_status", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( nStatus == 0 )
	{
		FPRINTF("[Line : %d][%s] download_get_http_status failed, error returned = http status returned is zero\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to get MIME type of the downloaded content
/**
* @testcase 			ITc_download_get_mime_type_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get MIME type of the downloaded content
* @scenario				set the network type to all\n
* 						set the URL to download\n
* 						register download state change callback\n
* 						start the downloading the current URL\n
* 						get the MIME type of the downloaded content\n
* 						unregister the callback
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb, download_start, download_get_mime_type
* @passcase				if download_get_mime_type returns success and all supporting returns success
* @failcase				if download_get_mime_type returns fail or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct url of a large size file must be updated as URLDOWNLOAD_DOWNLOADURL_I586 or URLDOWNLOAD_DOWNLOADURL_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_mime_type_p(void)
{
	START_TEST;

	int nURLTimeoutId = -1, nState = 1;
	char *pszMimeType = NULL;

	if ( UrlDownloadCreateEnv(g_nDownloadRequestID, false) != true )
	{
		FPRINTF("[Line : %d][%s] PreCondition in UrlDownloadCreateEnv failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = download_set_state_changed_cb(g_nDownloadRequestID, DownloadStateCallback, (void*)&nState);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_state_changed_cb", UrlDownloadGetError(nRet));

	g_bDownloadingComplete = false;
	nRet = download_start(g_nDownloadRequestID);

	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( !g_bDownloadingComplete )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = downloading state complete is not achieved\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	// Target API
	nRet = download_get_mime_type(g_nDownloadRequestID, &pszMimeType);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_mime_type", UrlDownloadGetError(nRet), download_cancel(g_nDownloadRequestID);download_unset_state_changed_cb(g_nDownloadRequestID));
	if ( pszMimeType == NULL )
	{
		FPRINTF("[Line : %d][%s] download_get_mime_type failed, error returned = Mime type returned is NULL\\n", __LINE__, API_NAMESPACE);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to get the current state of the download
/**
* @testcase 			ITc_download_get_state_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get the current state of the download
* @scenario				create a new download request\n
* 						get the current state of the download\n
* 						unload all data concerning a download id from memory
* @apicovered			download_get_state, download_create, download_destroy
* @passcase				if download_get_state returns success and supporting API returns success
* @failcase				if download_get_state returns fails or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_state_p(void)
{
	START_TEST;

	int nRequestID = 0;
	download_state_e eState = 0;

	int nRet = download_create(&nRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_create", UrlDownloadGetError(nRet));

	nRet = download_get_state(g_nDownloadRequestID, &eState);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_state", UrlDownloadGetError(nRet), download_destroy(g_nDownloadRequestID));

	if(strcmp(UrlDownloadState(eState),"Unknown Error") == 0)
	{
		FPRINTF("[Line : %d][%s] download_get_state, state returned = Unknown Error\\n", __LINE__, API_NAMESPACE);
		download_destroy(g_nDownloadRequestID);
		return 1;
	}

	nRet = download_destroy(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_destroy", UrlDownloadGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to error value when the download is failed
/**
* @testcase 			ITc_download_get_error_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to get the current state of the download
* @scenario				set the network type to all\n
* 						set a wrong URL to download\n
* 						register download state change callback\n
* 						start the downloading the wrong URL\n
* 						get error value when the download is failed\n
* 						unregister the callback
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb, download_set_url, download_start, download_get_error
* @passcase				if download_get_error returns success and supporting API returns success
* @failcase				if download_get_error returns fails or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_get_error_p(void)
{
	START_TEST;
	int nState = 1;
	int nURLTimeoutId = -1;
	const char *pszWrongUrl = "https://www.dummydatawhichdoesnotexist12334.com/";
	download_network_type_e eSetNewtorkType = DOWNLOAD_NETWORK_ALL;
	download_error_e eError = DOWNLOAD_ERROR_NONE;

	int nRet = download_set_network_type(g_nDownloadRequestID, eSetNewtorkType);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_network_type", UrlDownloadGetError(nRet));

	nRet = download_set_url(g_nDownloadRequestID, pszWrongUrl);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_url", UrlDownloadGetError(nRet));

	nRet = download_set_state_changed_cb(g_nDownloadRequestID, DownloadStateCallback, (void *)&nState);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_state_changed_cb", UrlDownloadGetError(nRet));

	nRet = download_start(g_nDownloadRequestID);

	RUN_POLLING_LOOP;

	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));

	nRet = download_get_error(g_nDownloadRequestID, &eError);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_error", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));

	if(strcmp(UrlDownloadGetError(eError),"Unknown Error") == 0)
	{
		FPRINTF("[Line : %d][%s] download_get_error, state returned = Unknown Error \\n", __LINE__, API_NAMESPACE);
		download_unset_state_changed_cb(g_nDownloadRequestID);
		return 1;
	}

	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));
	return 0;
}
