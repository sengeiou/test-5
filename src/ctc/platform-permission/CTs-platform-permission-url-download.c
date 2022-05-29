#include "CTs-platform-permission-common.h"

/**
* @function         CTs_platform_permission_urldownload_startup
* @description         Called before each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_urldownload_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
	if (remove(ERR_LOG))
	{
		FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
	}
    }

#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_urldownload_cleanup
* @description         Called after each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_urldownload_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose: checking http://tizen.org/privilege/download privilege
//& type: auto
/**
* @testcase			CTc_Urldownload_Privilege_Download
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			create a new download request\n
* @apicovered		download_create
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		device must be connected to outside world through a working network using WiFi or Data Network,
* @postcondition	unload all data concerning a download id from memory
*/
int CTc_Urldownload_Privilege_Download(void)
{ 
	START_TEST;
	
	int nDownloadRequestID = 0;
	
	
	bool g_bIsTELEPHONYSupported =false;
	bool g_bIsWIFISupported =false;
	bool g_bIsWIFIDIRECTSupported =false;
	bool g_bIsUrlDownloadSupported =false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsTELEPHONYSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(WIFI_FEATURE, g_bIsWIFISupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_WIFIDIRECT, g_bIsWIFIDIRECTSupported, API_NAMESPACE);
	g_bIsUrlDownloadSupported = g_bIsTELEPHONYSupported && g_bIsWIFISupported && g_bIsWIFIDIRECTSupported;
	if ( false == g_bIsUrlDownloadSupported )
	{
		FPRINTF("[Line : %d][%s] [%s], [%s] and [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY,WIFI_FEATURE,FEATURE_WIFIDIRECT);
		return 0;
	}
	
	
	int nRet = download_create(&nDownloadRequestID);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "download_create", DownloadPrintErrorInfo(nRet), download_destroy(nDownloadRequestID), DOWNLOAD_ERROR_NONE);
	return 0;
}
