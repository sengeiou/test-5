#include <messages.h>
#include <messages_types.h>
#include "CTs-platform-permission-common.h"

#define FEATURE_NETWORK_TELEPHONY		"http://tizen.org/feature/network.telephony"
#define FEATURE_NETWORK_TELEPHONY_SMS		"http://tizen.org/feature/network.telephony.sms"

#define FEATURE_NETWORK_TELEPHONY_MMS		"http://tizen.org/feature/network.telephony.mms"
messages_service_h g_hMessagesService;
/**
* @function 		CTs_platform_permission_messages_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_messages_startup(void)
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
* @function 		CTs_platform_permission_messages_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_messages_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& purpose: Checking tizen.org/privilege/message.read privilege
//& type: auto
/**
* @testcase			CTc_Messaging_PrivilegeMessageRead_open_close_service
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Opens a handle for a messaging service\n
* 					Closes a handle for a messaging service
* @apicovered		messages_open_service and messages_close_service
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Messaging_PrivilegeMessageRead_open_close_service(void)
{
	START_TEST;
	g_hMessagesService = NULL;
	bool bIsSupported =false;
	bool bIsTeleSupported =false;
	bool bIsTeleMmsSupported =false;
	bool bIsTeleSmsSupported =false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, bIsTeleSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY_MMS, bIsTeleMmsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY_SMS, bIsTeleSmsSupported, API_NAMESPACE);
	
	bIsSupported = bIsTeleSupported && bIsTeleMmsSupported && bIsTeleSmsSupported;
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s]  Feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int nRet = messages_open_service(&g_hMessagesService);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "messages_open_service", MessagesPrintErrorInfo(nRet), messages_close_service(g_hMessagesService), MESSAGES_ERROR_NONE);
	
	return 0;
}
