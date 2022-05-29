#include "CTs-platform-permission-common.h"
#include <phone_number.h>

#define PHONE_NUMBER				"82242239483"
#define PHONE_FEATURE				"http://tizen.org/feature/network.telephony"

bool g_bPhoneIssupportedFeature = false;
bool g_bIsConnected = false;

/**
 * @function		PhoneNumberUtilsGetError
 * @description		Maps error enums to string values
 * @parameter		nRet: error code returned
 * @return			error string
 */
char *PhoneNumberUtilsGetError(int nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
		case PHONE_NUMBER_ERROR_NONE:						szErrorVal = "PHONE_NUMBER_ERROR_NONE";							break;
		case PHONE_NUMBER_ERROR_IO_ERROR:					szErrorVal = "PHONE_NUMBER_ERROR_IO_ERROR";						break;
		case PHONE_NUMBER_ERROR_OUT_OF_MEMORY:				szErrorVal = "PHONE_NUMBER_ERROR_OUT_OF_MEMORY";				break;
		case PHONE_NUMBER_ERROR_INVALID_PARAMETER:			szErrorVal = "PHONE_NUMBER_ERROR_INVALID_PARAMETER";			break;
		case PHONE_NUMBER_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "PHONE_NUMBER_ERROR_FILE_NO_SPACE_ON_DEVICE";		break;
		case PHONE_NUMBER_ERROR_NOT_SUPPORTED:				szErrorVal = "PHONE_NUMBER_ERROR_NOT_SUPPORTED";				break;
		case PHONE_NUMBER_ERROR_NO_DATA:					szErrorVal = "PHONE_NUMBER_ERROR_NO_DATA";						break;
	}
	return szErrorVal;
}
/**
 * @function		CTs_platform_permission_phonenumber_utils_startup
 * @description		Called before each test
 * @parameter		NA
 * @return 			NA
 */
void CTs_platform_permission_phonenumber_utils_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);

	IS_FEATURE_SUPPORTED(PHONE_FEATURE, g_bPhoneIssupportedFeature, API_NAMESPACE);
	int nRet = phone_number_connect();
	if ( nRet != PHONE_NUMBER_ERROR_NONE )
	{
		g_bIsConnected = false;
		FPRINTF("[Line : %d][%s] phone_number_connect fail in startup error returned : %s \\n", __LINE__, API_NAMESPACE , PhoneNumberUtilsGetError(nRet));
		return;
	}
	
	g_bIsConnected = true;
}

/**
 * @function 		CTs_platform_permission_phonenumber_utils_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void CTs_platform_permission_phonenumber_utils_cleanup(void)
{

	int nRet = phone_number_disconnect();
	if ( nRet != PHONE_NUMBER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] phone_number_disconnect fail in cleanup error returned : %s \\n", __LINE__, API_NAMESPACE , PhoneNumberUtilsGetError(nRet));
		return;
	}

}

//& type: auto
//& purpose: check tizen.org/privilege/telephony Privilege
/**
 * @testcase                            CTc_PhoneNumber_PrivilegePhoneNumberUtils_get_normalized_number
 * @since_tizen                         3.0
 * @author                              SRID(manoj.g2)
 * @reviewer                            SRID(shobhit.v)
 * @type                                auto
 * @description                         Gets the normalized number
 * @scenario                            Gets the normalized number
 * @apicovered                          phone_number_get_normalized_number
 * @passcase                            If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase                            If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
 * @precondition                        Phone number should be connect
 * @postcondition                       Phone number should be disconnect
 */
int CTc_PhoneNumber_PrivilegePhoneNumberUtils_get_normalized_number(void)
{
	START_TEST;

	if ( g_bPhoneIssupportedFeature == false )
	{
		FPRINTF("[Line : %d][%s] %s Feature is not supported\\n", __LINE__, API_NAMESPACE, PHONE_FEATURE);
		return 0;
	}
	if(g_bIsConnected == false)
	{
		FPRINTF("[Line : %d][%s] phone_number_get_normalized_number failed ,g_bIsConnected is false\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nRet = PHONE_NUMBER_ERROR_NONE;
	char *pNormalizedNumber = NULL;

	nRet = phone_number_get_normalized_number(PHONE_NUMBER, &pNormalizedNumber);
	FREE_MEMORY(pNormalizedNumber);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "phone_number_get_normalized_number", PhoneNumberUtilsGetError(nRet));
	return 0;

}
