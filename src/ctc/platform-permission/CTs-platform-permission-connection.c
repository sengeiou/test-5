#include "CTs-platform-permission-common.h"
#define FEATURE_BLUETOOTH_TETHERING "http://tizen.org/feature/network.tethering.bluetooth"
/**
* @function         CTs_platform_permission_connection_startup
* @description         Called before each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_connection_startup(void)
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
* @function         CTs_platform_permission_connection_cleanup
* @description         Called after each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_connection_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}
//& purpose: checking http://tizen.org/privilege/network.get
//& type: auto
/**
* @testcase			CTc_Connection_Privilege_NetworkGet
* @since_tizen		2.3
* @author			SRID(shobhit.v)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @scenario			Creates a profile handle
* @apicovered		connection_create
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Connection_Privilege_NetworkGet(void)
{
	START_TEST;

	connection_h connection = NULL;
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if (!g_bIsSupported)
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;	
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_WIFI, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_WIFI);
		return 0;			
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, g_bIsSupported, API_NAMESPACE);
	if( !g_bIsSupported ) 
	{	
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	
	g_bIsSupported = false;	
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH_TETHERING, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH_TETHERING);
		return 0;
	}
	
	int nRet = connection_create(&connection);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "connection_create", NetworkConnectionPrintErrorMsg(nRet), connection_destroy(connection),CONNECTION_ERROR_NONE);
	return 0;
}