#include "CTs-platform-permission-common.h"


/**
* @function 		WifiManagerGetError
* @description	 	Display the details error information
* @parameter		nRet : error code returned
* @return 			error string
*/
char* WifiManagerGetError(int nRet)
{
	char *pszErrorVal = "Unknown Error";

	switch ( nRet )
	{
		case WIFI_MANAGER_ERROR_NONE:							pszErrorVal = "WIFI_MANAGER_ERROR_NONE";							break;
		case WIFI_MANAGER_ERROR_INVALID_PARAMETER:				pszErrorVal = "WIFI_MANAGER_ERROR_INVALID_PARAMETER";				break;
		case WIFI_MANAGER_ERROR_OUT_OF_MEMORY:					pszErrorVal = "WIFI_MANAGER_ERROR_OUT_OF_MEMORY";					break;
		case WIFI_MANAGER_ERROR_INVALID_OPERATION:				pszErrorVal = "WIFI_MANAGER_ERROR_INVALID_OPERATION";				break;
		case WIFI_MANAGER_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED:	pszErrorVal = "WIFI_MANAGER_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED";	break;
		case WIFI_MANAGER_ERROR_OPERATION_FAILED:				pszErrorVal = "WIFI_MANAGER_ERROR_OPERATION_FAILED";				break;	
		case WIFI_MANAGER_ERROR_NO_CONNECTION:					pszErrorVal = "WIFI_MANAGER_ERROR_NO_CONNECTION";					break;
		case WIFI_MANAGER_ERROR_NOW_IN_PROGRESS:				pszErrorVal = "WIFI_MANAGER_ERROR_NOW_IN_PROGRESS";					break;
		case WIFI_MANAGER_ERROR_ALREADY_EXISTS:					pszErrorVal = "WIFI_MANAGER_ERROR_ALREADY_EXISTS";					break;
		case WIFI_MANAGER_ERROR_OPERATION_ABORTED:				pszErrorVal = "WIFI_MANAGER_ERROR_OPERATION_ABORTED";				break;
		case WIFI_MANAGER_ERROR_DHCP_FAILED:					pszErrorVal = "WIFI_MANAGER_ERROR_DHCP_FAILED";						break;	
		case WIFI_MANAGER_ERROR_INVALID_KEY:					pszErrorVal = "WIFI_MANAGER_ERROR_INVALID_KEY";						break;
		case WIFI_MANAGER_ERROR_NO_REPLY:						pszErrorVal = "WIFI_MANAGER_ERROR_NO_REPLY";						break;
		case WIFI_MANAGER_ERROR_SECURITY_RESTRICTED:			pszErrorVal = "WIFI_MANAGER_ERROR_SECURITY_RESTRICTED";				break;
	}
	return pszErrorVal;
}
/**
* @function         CTs_platform_permission_wifi_manager_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_wifi_manager_startup(void)
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
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_wifi_manager_startup\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function         CTs_platform_permission_wifi_manager_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_wifi_manager_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_wifi_manager_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose: Checking  http://tizen.org/privilege/network.get  privilege
//& type: auto
/**
* @testcase			CTc_Wifi_Manager_Privilege_NetworkGet
* @since_tizen		3.0
* @author			SRID(shilpa.j)
* @reviewer			SRID()
* @type 			auto
* @scenario			Initializes Wi-Fi Manager\n
*					Deinitializes Wi-Fi Manager
* @apicovered		wifi_manager_initialize and wifi_manager_deinitialize
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Wifi_Manager_Privilege_NetworkGet(void)
{
	START_TEST;
	wifi_manager_h hWifi;
	IS_FEATURE_SUPPORTED(WIFI_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIFI_FEATURE);
		return 0;
	}

	
	int nRet = wifi_manager_initialize(&hWifi);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "wifi_manager_initialize", WifiManagerGetError(nRet),  wifi_manager_deinitialize(hWifi), WIFI_MANAGER_ERROR_NONE);

	return 0;
}
