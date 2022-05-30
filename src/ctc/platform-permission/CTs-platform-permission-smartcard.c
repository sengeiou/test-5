#include "CTs-platform-permission-common.h"
#include <smartcard.h>

#define SE_FEATURE			"http://tizen.org/feature/network.secure_element"
#define SE_UICC_FEATURE		"http://tizen.org/feature/network.secure_element.uicc"
#define SE_ESE_FEATURE		"http://tizen.org/feature/network.secure_element.ese"


bool g_bIsUICCSupported;
bool g_bIsESESupported;
bool g_bIsSmartcardSupported;
/**
* @function 		CTs_platform_permission_smartcard_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_smartcard_startup(void)
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
* @function 		CTs_platform_permission_smartcard_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_smartcard_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
 * @function 		SmartcardGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
/*char* SmartcardGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case SMARTCARD_ERROR_NONE:						szErrorVal = "SMARTCARD_ERROR_NONE";				break;
		case SMARTCARD_ERROR_GENERAL:					szErrorVal = "SMARTCARD_ERROR_GENERAL";				break;
		case SMARTCARD_ERROR_IO_ERROR:					szErrorVal = "SMARTCARD_ERROR_IO_ERROR";			break;
		case SMARTCARD_ERROR_NO_SUCH_ELEMENT:			szErrorVal = "SMARTCARD_ERROR_NO_SUCH_ELEMENT";		break;
		case SMARTCARD_ERROR_ILLEGAL_STATE:				szErrorVal = "SMARTCARD_ERROR_ILLEGAL_STATE";		break;
		case SMARTCARD_ERROR_INVALID_PARAMETER:			szErrorVal = "SMARTCARD_ERROR_INVALID_PARAMETER";	break;
		case SMARTCARD_ERROR_ILLEGAL_REFERENCE:			szErrorVal = "SMARTCARD_ERROR_ILLEGAL_REFERENCE";	break;
		case SMARTCARD_ERROR_OPERATION_NOT_SUPPORTED:	szErrorVal = "SMARTCARD_ERROR_OPERATION_NOT_SUPPORTED";break;
		case SMARTCARD_ERROR_PERMISSION_DENIED:			szErrorVal = "SMARTCARD_ERROR_PERMISSION_DENIED";	break;
		case SMARTCARD_ERROR_CHANNEL_NOT_AVAILABLE:		szErrorVal = "SMARTCARD_ERROR_CHANNEL_NOT_AVAILABLE";break;
		case SMARTCARD_ERROR_NOT_INITIALIZED:			szErrorVal = "SMARTCARD_ERROR_NOT_INITIALIZED";		break;
		case SMARTCARD_ERROR_NOT_SUPPORTED:				szErrorVal = "SMARTCARD_ERROR_NOT_SUPPORTED";		break;
		default:										szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}*/
//& purpose Initializes and deinitializes smartcard service
//& type: auto
/**
* @testcase 		CTc_SmartCard_PrivilegeSecureElement_initialize_deinitialize
* @since_tizen		2.3.1
* @author           SRID(manoj.g2)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @description		Initializes and deinitializes smartcard service
* @scenario			Initialize smartcard service\n
*					De-initialize smartcard service
* @apicovered		smartcard_initialize, smartcard_deinitialize
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED 
* @precondition		NA
* @postcondition	smartcard_deinitialize should be called
*/
int CTc_SmartCard_PrivilegeSecureElement_initialize_deinitialize(void)
{
	START_TEST;

	// Target API
	bool bIsUICCSupported =false;
	bool bIsESESupported =false;
	bool bIsSESupported =false;
	bool bIsSupported =false;
	IS_FEATURE_SUPPORTED(SE_UICC_FEATURE, bIsUICCSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(SE_ESE_FEATURE, bIsESESupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(SE_FEATURE, bIsSESupported, API_NAMESPACE);
	bIsSupported = bIsUICCSupported && bIsESESupported && bIsSESupported;
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = smartcard_initialize();
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "smartcard_initialize", SmartcardGetError(nRet),smartcard_deinitialize(),SMARTCARD_ERROR_NONE);
	
	return 0;
}