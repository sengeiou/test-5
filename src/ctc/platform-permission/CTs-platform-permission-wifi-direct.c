#include "CTs-platform-permission-common.h"
#define  MAC_ADDRESS "BC:D1:1F:32:D8:7D"
/**
* @function         CTs_platform_permission_wifidirect_startup
* @description         Called before each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_wifidirect_startup(void)
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

	bool g_bIsWIFISupported =false;
	bool g_bIsWIFIDIRECTSupported =false;
	bool g_bIsWIFIDIRECTDIPLAYSupported =false;
	bool g_bIsWIFIDIRECTDISCOVERYSupported =false;
	g_bIsSupported = false;

	IS_FEATURE_SUPPORTED(WIFI_FEATURE, g_bIsWIFISupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_WIFIDIRECT, g_bIsWIFIDIRECTSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_WIFIDIRECT_DISPLAY, g_bIsWIFIDIRECTDIPLAYSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_WIFIDIRECT_DISCOVERY, g_bIsWIFIDIRECTDISCOVERYSupported, API_NAMESPACE);

	g_bIsSupported = g_bIsWIFISupported && g_bIsWIFIDIRECTSupported && g_bIsWIFIDIRECTDIPLAYSupported && g_bIsWIFIDIRECTDISCOVERYSupported;
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_wifidirect_cleanup
* @description         Called after each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_wifidirect_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose: Checking tizen.org/privilege/wifidirect privilege
//& type: auto
/**
* @testcase			CTc_Network_Privilege_WifiDirect
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario			Initialize WifiDirect\n
* 					Deinitialize WifiDirect
* @apicovered		wifi_direct_initialize and wifi_direct_deinitialize
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Network_Privilege_WifiDirect(void)
{
	START_TEST;
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Features is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = wifi_direct_initialize();
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "wifi_direct_initialize", WifiDirectPrintErrorInfo(nRet), wifi_direct_deinitialize(), WIFI_DIRECT_ERROR_NONE);
	return 0;
}

//& purpose: Checking tizen.org/privilege/wifidirect privilege
//& type: auto
/**
* @testcase			CTc_Network_Privilege_WifiDirect_display_port
* @since_tize			2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario
* @apicovered			wifi_direct_get_peer_display_port
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_Network_Privilege_WifiDirect_display_port(void)
{
	START_TEST;
	int port =1000;

	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Features is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = wifi_direct_get_peer_display_port(MAC_ADDRESS , &port);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "wifi_direct_get_peer_display_port", WifiDirectPrintErrorInfo(nRet));

	return 0;
}
//& purpose: Checking tizen.org/privilege/wifidirect privilege
//& type: auto
/**
* @testcase			CTc_Network_Privilege_WifiDirect_display_hdcp
* @since_tizen			2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario
* @apicovered			wifi_direct_get_peer_display_hdcp
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_Network_Privilege_WifiDirect_display_hdcp(void)
{
	START_TEST;
	int hdcp =1000;

	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Features is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = wifi_direct_get_peer_display_hdcp(MAC_ADDRESS , &hdcp);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "wifi_direct_get_peer_display_hdcp", WifiDirectPrintErrorInfo(nRet));

	return 0;
}
//& purpose: Checking tizen.org/privilege/wifidirect privilege
//& type: auto
/**
* @testcase			CTc_Network_Privilege_WifiDirect_display_thoughput
* @since_tizen			2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario
* @apicovered			wifi_direct_get_peer_display_thoughput
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_Network_Privilege_WifiDirect_display_thoughput(void)
{
	START_TEST;
	int throughput =1000;

	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Features is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = wifi_direct_get_peer_display_throughput(MAC_ADDRESS , &throughput);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "wifi_direct_get_peer_display_throughput", WifiDirectPrintErrorInfo(nRet));

	return 0;
}
//& purpose: Checking tizen.org/privilege/wifidirect privilege
//& type: auto
/**
* @testcase			CTc_Network_Privilege_WifiDirect_display_type
* @since_tizen			2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario
* @apicovered			wifi_direct_get_peer_display_type
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_Network_Privilege_WifiDirect_display_type(void)
{
	START_TEST;
	wifi_direct_display_type_e type;

	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Features is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = wifi_direct_get_peer_display_type(MAC_ADDRESS , &type);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "wifi_direct_get_peer_display_type", WifiDirectPrintErrorInfo(nRet));

	return 0;
}
//& purpose: Checking tizen.org/privilege/wifidirect privilege
//& type: auto
/**
* @testcase			CTc_Network_Privilege_WifiDirect_display_availability
* @since_tizen			2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario
* @apicovered			wifi_direct_get_peer_display_isavailable
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA
*/
int CTc_Network_Privilege_WifiDirect_display_availability(void)
{
	START_TEST;
	wifi_direct_display_type_e type;
	bool isavailable =false;

	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Features is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = wifi_direct_get_peer_display_availability(MAC_ADDRESS, &isavailable);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "wifi_direct_get_peer_display_availability", WifiDirectPrintErrorInfo(nRet));

	return 0;
}
