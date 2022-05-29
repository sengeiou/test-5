#include "CTs-platform-permission-common.h"
#include <email.h>
/**
* @function 		EmailGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* EmailGetError(int nRet)
{
	char *szErrorVal = "Undefined Error";

	switch ( nRet )
	{
	case EMAILS_ERROR_NONE:									szErrorVal = "EMAILS_ERROR_NONE";								break;
	case EMAILS_ERROR_OUT_OF_MEMORY:						szErrorVal = "EMAILS_ERROR_OUT_OF_MEMORY";						break;
	case EMAILS_ERROR_INVALID_PARAMETER:					szErrorVal = "EMAILS_ERROR_INVALID_PARAMETER";					break;
	case EMAILS_ERROR_SERVER_NOT_READY:						szErrorVal = "EMAILS_ERROR_SERVER_NOT_READY";					break;
	case EMAILS_ERROR_COMMUNICATION_WITH_SERVER_FAILED:		szErrorVal = "EMAILS_ERROR_COMMUNICATION_WITH_SERVER_FAILED";	break;
	case EMAILS_ERROR_OPERATION_FAILED:						szErrorVal = "EMAILS_ERROR_OPERATION_FAILED";					break;
	case EMAILS_ERROR_ACCOUNT_NOT_FOUND:					szErrorVal = "EMAILS_ERROR_ACCOUNT_NOT_FOUND";					break;
	case EMAILS_ERROR_DB_FAILED:							szErrorVal = "EMAILS_ERROR_DB_FAILED";							break;
	case EMAILS_ERROR_PERMISSION_DENIED:					szErrorVal = "EMAILS_ERROR_PERMISSION_DENIED";					break;
	}

	return szErrorVal;
}
/**
* @function 		CTs_platform_permission_email_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_email_startup(void)
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
* @function 		CTs_platform_permission_email_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_email_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& purpose: Checking tizen.org/privilege/email privilege
//& type: auto
/**
* @testcase			CTc_Email_PrivilegeMessagingEmail_create_message
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates an email message handle for sending an email message\n
* 					Destroys an email message handle and releases all its resources
* @apicovered		email_create_message and email_destroy_message
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Email_PrivilegeMessagingEmail_create_message(void)
{
	START_TEST;
	bool bIsSupported = false;
	email_h hEmailHandle = NULL;

	IS_FEATURE_SUPPORTED(FEATURE_EMAIL, bIsSupported, API_NAMESPACE);
        if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_EMAIL);
                return 0;
        }
	int nRet = email_create_message(&hEmailHandle);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "email_create_message", EmailGetError(nRet), email_destroy_message(hEmailHandle), EMAILS_ERROR_NONE);

	return 0;
}
