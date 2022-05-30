#include "CTs-platform-permission-common.h"
#define PUSH_FEATURE "http://tizen.org/feature/network.push"

/**
* @function 		PushServiceGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* PushServiceGetError(int nRet)
{
	char *szErrorVal = "UNKNOWN_ERROR";

	switch ( nRet )
	{
	case PUSH_SERVICE_ERROR_NONE:				szErrorVal = "PUSH_SERVICE_ERROR_NONE";					break; 
	case PUSH_SERVICE_ERROR_OUT_OF_MEMORY:		szErrorVal = "PUSH_SERVICE_ERROR_OUT_OF_MEMORY";		break; 
	case PUSH_SERVICE_ERROR_INVALID_PARAMETER:	szErrorVal = "PUSH_SERVICE_ERROR_INVALID_PARAMETER";	break; 
	case PUSH_SERVICE_ERROR_NOT_CONNECTED:		szErrorVal = "PUSH_SERVICE_ERROR_NOT_CONNECTED";		break;
	case PUSH_SERVICE_ERROR_NO_DATA:			szErrorVal = "PUSH_SERVICE_ERROR_NO_DATA";				break;
	case PUSH_SERVICE_ERROR_OPERATION_FAILED:	szErrorVal = "PUSH_SERVICE_ERROR_OPERATION_FAILED";		break;
	case PUSH_SERVICE_ERROR_PERMISSION_DENIED:	szErrorVal = "PUSH_SERVICE_ERROR_PERMISSION_DENIED";	break;
	}
	return szErrorVal;
}

/**
* @function 		CTs_platform_permission_sppc_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_sppc_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_sppc_startup\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function 		CTs_platform_permission_sppc_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_sppc_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_sppc_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 			Push_service_notify_cb
* @description 			Called to handle a notification.
* @parameter	[IN]	hNoti		A handle of the notification
*				[IN]	pUserData	User data passed to this callback
* @return				NA
*/
static void Push_service_notify_cb(push_service_notification_h hNoti, void *pUserData)
{
	FPRINTF("[Line : %d][%s] Called to handle a notification\\n", __LINE__, API_NAMESPACE);
}
/**
* @function 			Push_service_state_cb
* @description 			Called when the registration state is refreshed.
* @parameter	[IN]	eState		Registration state
*				[IN]	pszErr	Error message
*				[IN]	pUserData	User data passed to this callback
* @return				NA
*/
static void Push_service_state_cb(push_service_state_e eState, const char *pszErr, void *pUserData)
{
	FPRINTF("[Line : %d][%s] Called when the registration state is refreshed\\n", __LINE__, API_NAMESPACE);
}
//& purpose: Checking tizen.org/privilege/push privilege
//& type: auto
/**
* @testcase			CTc_Messaging_PrivilegePush_service_connect
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Connects to the push service and sets callback functions\n
* 					Disconnect the message handle and releases all its resources
* @apicovered		push_service_connect and push_service_disconnect
* @passcase			If privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Messaging_PrivilegePush_service_connect(void)
{
	START_TEST;

	bool bWifiSupport = true;
	bool bMobDataSupport = true;

	IS_FEATURE_SUPPORTED(WIFI_FEATURE, bWifiSupport, API_NAMESPACE);
	if ( !bWifiSupport )
	{
		FPRINTF("[Line : %d][%s] Wifi Connection feature is not supported in the target device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	IS_FEATURE_SUPPORTED(TELEPHONY_FEATURE, bMobDataSupport, API_NAMESPACE);
	if ( !bMobDataSupport )
	{
		FPRINTF("[Line : %d][%s] Mobile Data feature is not supported in the target device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	push_service_connection_h hPushServiceConnection = NULL;
	int nRet = push_service_connect(APPID, Push_service_state_cb, Push_service_notify_cb, NULL, &hPushServiceConnection);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "push_service_connect", PushServiceGetError(nRet), push_service_disconnect(hPushServiceConnection), PUSH_SERVICE_ERROR_NONE);

	return 0;
}
/**
 * @testcase		CTc_Messaging_PrivilegePush_app_control_to_noti_data
 * @since_tizen		2.3
 * @description		test case of push_service_app_control_to_noti_data()
 * @scenario		Try to app control operation to pass noti data with invalid parameter and check return value
 * @author			SRID(manoj.g2)
 * @reviewer		SRID(shobhit.v)
 * @type 			auto
 * @apicovered		push_service_app_control_to_noti_data
 * @passcase		If privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase		If privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
 * @precondition	NA
 * @postcondition	NA
*/
int CTc_Messaging_PrivilegePush_app_control_to_noti_data(void)
{
    int ret;
    //char *notidata;
    app_control_h app_control;
	bool bPushSupport =false;
	IS_FEATURE_SUPPORTED(PUSH_FEATURE, bPushSupport, API_NAMESPACE);
	if ( !bPushSupport )
	{
		FPRINTF("[Line : %d][%s] Mobile Data feature is not supported in the target device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
    	ret = app_control_create(&app_control);
 	PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, ret, "app_control_create", PushServiceGetError(ret));
	ret = app_control_add_extra_data (app_control, "http://tizen.org/appcontrol/data/push/appdata", "data@home");
 	PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, ret, "app_control_add_extra_data", PushServiceGetError(ret));
	
    //notidata = push_service_app_control_to_noti_data(app_control, "libpush.operation.handle");
	push_service_app_control_to_noti_data(app_control, "libpush.operation.handle");
    	ret=  get_last_result();
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, ret, "push_service_app_control_to_noti_data", PushServiceGetError(ret),app_control_destroy(app_control));

	app_control_destroy(app_control);
	return 0;
}
/**
 * @testcase		CTc_Messaging_PrivilegePush_app_control_to_notification
 * @since_tizen		2.3
 * @description		test case of push_service_app_control_to_notification
 * @scenario		Try to app control operation to pass noti data with invalid parameter and check return value
 * @author			SRID(manoj.g2)
 * @reviewer		SRID(shobhit.v)
 * @type 			auto
 * @apicovered		push_service_app_control_to_notification
 * @passcase		If privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase		If privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
 * @precondition	NA
 * @postcondition	NA
*/
int CTc_Messaging_PrivilegePush_app_control_to_notification(void)
{
    int ret;
    app_control_h app_control;
	bool bPushSupport =false;
	push_service_notification_h noti = NULL;
	IS_FEATURE_SUPPORTED(PUSH_FEATURE, bPushSupport, API_NAMESPACE);
	if ( !bPushSupport )
	{
		FPRINTF("[Line : %d][%s] Mobile Data feature is not supported in the target device\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
    ret = app_control_create(&app_control);
 	PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, ret, "app_control_create", PushServiceGetError(ret));

app_control_add_extra_data (app_control, "http://tizen.org/appcontrol/data/push/appdata", "data@home");
 PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, ret, "app_control_add_extra_data", PushServiceGetError(ret));
 ret = push_service_app_control_to_notification(app_control, "libpush.operation.handle" , &noti);
	//ret = push_service_app_control_to_notification(app_control, APP_CONTROL_OPERATION_DEFAULT , &noti);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, ret, "push_service_app_control_to_notification", PushServiceGetError(ret),app_control_destroy(app_control));
	
	app_control_destroy(app_control);
	
    return 0;
}
