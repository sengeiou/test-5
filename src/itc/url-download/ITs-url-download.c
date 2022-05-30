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
#include <dlog.h>

#define CONFIG_VALUE_LEN_MAX      1024    //maximum length of value

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
void ITs_url_download_startup(void)
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
void ITs_url_download_cleanup(void)
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
//& purpose: scenario to create a new download request and then unload all data concerning a download id from memory
/**
* @testcase 			ITc_download_create_destroy_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to create a new download request and then unload all data concerning a download id from memory
* @scenario				create a new download request\n
* 						unload all data concerning a download id from memory
* @apicovered			download_create, download_destroy
* @passcase				if download_create and download_destroy returns success
* @failcase				if download_create or download_destroy returns fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_create_destroy_p(void)
{
	START_TEST;
	int nRet = 0, nRequestID = 0;
	download_state_e eDownloadState = DOWNLOAD_STATE_NONE;

	nRet = download_create(&nRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_create", UrlDownloadGetError(nRet));

	nRet = download_get_state(nRequestID, &eDownloadState);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_get_state", UrlDownloadGetError(nRet), download_destroy(nRequestID));
	if ( eDownloadState != DOWNLOAD_STATE_READY )
	{
		FPRINTF("[Line : %d][%s] download_get_state, state returned = %s\\n", __LINE__, API_NAMESPACE, UrlDownloadState(eDownloadState));
		download_destroy(nRequestID);
		return 1;
	}

	nRet = download_destroy(nRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_destroy", UrlDownloadGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to add a HTTP header field to the download request and remove added HTTP header field from the download
/**
* @testcase 			ITc_download_add_remove_http_header_field_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to add a HTTP header field to the download request and remove added HTTP header field from the download
* @scenario				add a HTTP header field to the download request\n
* 						remove added HTTP header field from the download
* @apicovered			download_add_http_header_field, download_remove_http_header_field
* @passcase				if download_add_http_header_field and download_remove_http_header_field returns success
* @failcase				if download_add_http_header_field or download_remove_http_header_field returns fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_add_remove_http_header_field_p(void)
{
	START_TEST;
	int nRet = 0;
	const char *pszField = "TestField";
	const char *pszValue = "TestValue";
	nRet = download_add_http_header_field(g_nDownloadRequestID, pszField, pszValue);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_add_http_header_field", UrlDownloadGetError(nRet));

	nRet = download_remove_http_header_field(g_nDownloadRequestID, pszField);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_remove_http_header_field", UrlDownloadGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to register and unregister callback function to be invoked when progress of the download changes
/**
* @testcase 			ITc_download_set_unset_progress_cb_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to register and unregister callback function to be invoked when progress of the download changes
* @scenario				register callback function to be invoked when progress of the download changes\n
* 						check if callback is called after download progress is changed\n
* 						unregister callback function to be invoked when progress of the download changes\n
* 						check that callback is not called after download progress is changed
* @apicovered			download_set_progress_cb, download_unset_progress_cb, download_start, download_cancel
* @passcase				if download_set_progress_cb, download_unset_progress_cb returns success and callback is called after downloading progress is changed after callback is registered also callback should not be called after downloading progress is changed after callback is unregistered
* @failcase				if download_set_progress_cb, download_unset_progress_cb returns fail or callback is not called after downloading progress is changed after callback is registered or if callback is called after downloading progress is changed after callback is unregistered
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct URL of a file to be downloaded must be updated as URLDOWNLOAD_URL_I586 or URLDOWNLOAD_URL_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_unset_progress_cb_p(void)
{
	START_TEST;

	int nURLTimeoutId = -1;
	if ( UrlDownloadCreateEnv(g_nDownloadRequestID, false) != true )
	{
		FPRINTF("[Line : %d][%s] PreCondition in UrlDownloadCreateEnv failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = download_set_progress_cb(g_nDownloadRequestID, DownloadProgressCallback, NULL);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_progress_cb", UrlDownloadGetError(nRet));

	g_bCheckCb = false;
	nRet = download_start(g_nDownloadRequestID);

	RUN_POLLING_LOOP;

	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet), download_unset_progress_cb(g_nDownloadRequestID));
	if ( !g_bCheckCb )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		download_unset_progress_cb(g_nDownloadRequestID);
		return 1;
	}

	download_cancel(g_nDownloadRequestID);//No check for return state as downloading might have been completed by now

	// Target API
	nRet = download_unset_progress_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_progress_cb", UrlDownloadGetError(nRet));

	g_bCheckCb = false;
	nRet = download_start(g_nDownloadRequestID);

	RUN_POLLING_LOOP;

	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_start", UrlDownloadGetError(nRet));
	if ( g_bCheckCb )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = callback is invoked even after unregister\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: scenario to start and cancel downloading the current URL
/**
* @testcase 			ITc_download_start_cancel_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to start and cancel downloading the current URL
* @scenario				set the network type to all\n
* 						set the URL to download\n
* 						register download state change callback\n
* 						start the downloading the current URL\n
* 						cancel downloading the current URL\n
* 						unregister the callback
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb, download_start, download_cancel
* @passcase				if download_start, download_cancel returns success and all supporting returns success
* @failcase				if download_start, download_cancel returns fail or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct URL of a file to be downloaded must be updated as URLDOWNLOAD_URL_I586 or URLDOWNLOAD_URL_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_start_cancel_p(void)
{
	START_TEST;
	int nURLTimeoutId = -1;
	if ( UrlDownloadCreateEnv(g_nDownloadRequestID, false) != true )
	{
		FPRINTF("[Line : %d][%s] PreCondition in UrlDownloadCreateEnv failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nState = 0;
	g_bDownloadingState = false;
	int nRet = download_set_state_changed_cb(g_nDownloadRequestID, DownloadStateCallback, (void*)&nState);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_state_changed_cb", UrlDownloadGetError(nRet));

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

	nRet = download_cancel(g_nDownloadRequestID);
	PRINT_RESULT_CLEANUP(DOWNLOAD_ERROR_NONE, nRet, "download_cancel", UrlDownloadGetError(nRet), download_unset_state_changed_cb(g_nDownloadRequestID));

	nRet = download_unset_state_changed_cb(g_nDownloadRequestID);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_unset_state_changed_cb", UrlDownloadGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: scenario to start and cancel downloading the current URL
/**
* @testcase 			ITc_download_pause_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to start and cancel downloading the current URL
* @scenario				set the network type to all
* 						set the URL to download\n
* 						register download state change callback\n
* 						start the downloading the current URL\n
* 						pause the downloading the current URL\n
* 						cancel downloading the current URL\n
* 						unregister the callback
* @apicovered			download_set_state_changed_cb, download_unset_state_changed_cb, download_start, download_pause, download_cancel
* @passcase				if download_pause returns success and all supporting returns success
* @failcase				if download_pause returns fail or any supporting API fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created, Correct url of a large size file must be updated as URLDOWNLOAD_DOWNLOADURL_I586 or URLDOWNLOAD_DOWNLOADURL_ARM in TCT_Preconditions.txt
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_pause_p(void)
{
	START_TEST;

	int nURLTimeoutId = -1, nState = 0;
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
	nRet = download_pause(g_nDownloadRequestID);
	if ( nRet != DOWNLOAD_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] download_start failed, error returned = downloading state is not achieved\\n", __LINE__, API_NAMESPACE);
		download_cancel(g_nDownloadRequestID);
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
//& purpose: scenario to set the directory path of the temporary file used in the previous download request
/**
* @testcase 			ITc_download_set_temp_file_path_p
* @since_tizen 			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to set the directory path of the temporary file used in the previous download request
* @scenario				set the directory path of the temporary file used in the previous download request
* @apicovered			download_set_temp_file_path
* @passcase				if download_set_temp_file_path returns success
* @failcase				if download_set_temp_file_path returns fails
* @precondition			device must be connected to outside world through a working network using WiFi or Data Network, download request must be created
* @postcondition		unload all data concerning a download id from memory
*/
int ITc_download_set_temp_file_path_p(void)
{
	START_TEST;

	char *pszFilePath = UrlDownloadGetStorageDirectory();

	dlog_print(DLOG_ERROR, "NativeTCT", "[%s][%d] ITc_download_set_temp_file_path_p", __FILE__, __LINE__);

	if (pszFilePath == NULL)
	{
		FPRINTF("[%s][%d] UrlDownloadGetStorageDirectory() returned NULL\\n", __FILE__, __LINE__);
		return 1;
	}

	int nRet = download_set_temp_file_path(g_nDownloadRequestID, pszFilePath);
	FREE_MEMORY(pszFilePath);
	PRINT_RESULT(DOWNLOAD_ERROR_NONE, nRet, "download_set_temp_file_path %s", UrlDownloadGetError(nRet));
	dlog_print(DLOG_INFO, "NativeTCT", "[%s][%d] temp file path = [%s]", __FILE__, __LINE__, pszFilePath);
	return 0;
}
/** @} */
/** @} */
