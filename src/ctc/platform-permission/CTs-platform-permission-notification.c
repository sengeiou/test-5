#include "CTs-platform-permission-common.h"
#include <notification.h>
#define NOTIFICATION_TAG					"notification_tag"
#define FREE_NOTIFICATION(notification)  		if(notification != NULL) {notification_free(notification);}
#define DELETE_NOTIFICATION(notification)		if(notification != NULL) {notification_delete(notification);}

bool CreateNotification(notification_type_e eNotificationType);
void FreeAndDeleteNotificationResourceHandle();
char* NotificationGetError(int nRet);
notification_h g_NotificationHandle;

/**
* @function 		NotificationGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* NotificationGetError(int nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
	case NOTIFICATION_ERROR_NONE:					szErrorVal = "NOTIFICATION_ERROR_NONE";						break;
	case NOTIFICATION_ERROR_INVALID_PARAMETER:		szErrorVal = "NOTIFICATION_ERROR_INVALID_PARAMETER";		break;
	case NOTIFICATION_ERROR_OUT_OF_MEMORY:			szErrorVal = "NOTIFICATION_ERROR_OUT_OF_MEMORY";			break;
	case NOTIFICATION_ERROR_FROM_DB:				szErrorVal = "NOTIFICATION_ERROR_FROM_DB";					break;
	case NOTIFICATION_ERROR_ALREADY_EXIST_ID:		szErrorVal = "NOTIFICATION_ERROR_ALREADY_EXIST_ID";			break;
	case NOTIFICATION_ERROR_FROM_DBUS:				szErrorVal = "NOTIFICATION_ERROR_FROM_DBUS";				break;
	case NOTIFICATION_ERROR_NOT_EXIST_ID:			szErrorVal = "NOTIFICATION_ERROR_NOT_EXIST_ID";				break;
	case NOTIFICATION_ERROR_IO_ERROR:				szErrorVal = "NOTIFICATION_ERROR_IO_ERROR";					break;
	case NOTIFICATION_ERROR_SERVICE_NOT_READY:		szErrorVal = "NOTIFICATION_ERROR_SERVICE_NOT_READY";		break;
	case NOTIFICATION_ERROR_PERMISSION_DENIED:		szErrorVal = "NOTIFICATION_ERROR_PERMISSION_DENIED";		break;
	}

	return szErrorVal;
}
/**
* @function 		CTs_platform_permission_notification_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_notification_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_notification_startup\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}
/**
* @function 		CTs_platform_permission_notification_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_notification_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_notification_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		CreateNotification
* @description 	Creates internal structure data and returns a notification handle.
* @parameter       NotificationType
* @return			NA
*/
bool CreateNotification(notification_type_e eNotificationType)
{
	FreeAndDeleteNotificationResourceHandle();

	g_NotificationHandle = notification_create(eNotificationType);
	CHECK_HANDLE(g_NotificationHandle, "notification_create");

	return true;
}

/**
* @function 		FreeAndDeleteNotificationResourceHandle
* @description 	Free internal data structure and notification handle.
* @parameter
* @return			NA
*/
void FreeAndDeleteNotificationResourceHandle()
{
	DELETE_NOTIFICATION(g_NotificationHandle);
	FREE_NOTIFICATION(g_NotificationHandle);
	g_NotificationHandle = NULL;
}
//& purpose: check tizen.org/privilege/notification privilege.
//& type: auto
/**
* @testcase			CTc_Notification_PrivilegeNotification_delete
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Creates internal structure data and returns a notification handle\n
* 					Deletes a notification with the given handle\n
* 					Frees the internal structure data of a notification handle
* @apicovered		notification_create, notification_delete and notification_free
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_Notification_PrivilegeNotification_delete(void)
{
	int nRet;

	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	nRet = notification_delete(g_NotificationHandle);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "notification_delete", NotificationGetError(nRet), FreeAndDeleteNotificationResourceHandle(););

	FreeAndDeleteNotificationResourceHandle();

	return 0;
}

//& purpose: check tizen.org/privilege/notification privilege.
//& type: auto
/**
* @testcase			CTc_Notification_PrivilegeNotification_delete_all
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Creates internal structure data and returns a notification handle\n
* 					Deletes all notification with the given notification type\n
* 					Frees the internal structure data of a notification handle
* @apicovered		notification_create, notification_delete_all, notification_free
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_Notification_PrivilegeNotification_delete_all(void)
{
	int nRet;

	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	nRet = notification_delete_all(NOTIFICATION_TYPE_NOTI);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "notification_delete_all", NotificationGetError(nRet), FreeAndDeleteNotificationResourceHandle(););

	FreeAndDeleteNotificationResourceHandle();
	return 0;
}
//& purpose: check tizen.org/privilege/notification privilege.
//& type: auto
/**
* @testcase			CTc_Notification_PrivilegeNotification_post
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Creates internal structure data and returns a notification handle\n
* 					Deletes all notification with the given notification type\n
* 					Deletes a notification with the given handle\n
* 					Frees the internal structure data of a notification handle
* @apicovered		notification_create,notification_post and notification_free
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_Notification_PrivilegeNotification_post(void)
{
	int nRet;

	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	nRet = notification_post(g_NotificationHandle);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "notification_post", NotificationGetError(nRet), FreeAndDeleteNotificationResourceHandle(););

	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& purpose: check tizen.org/privilege/notification privilege.
//& type: auto
/**
* @testcase			CTc_Notification_PrivilegeNotification_load_by_tag
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Creates internal structure data and returns a notification handle\n
*					load notification by tag\n
* 					Frees the internal structure data of a notification handle
* @apicovered		notification_load_by_tag
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_Notification_PrivilegeNotification_load_by_tag(void)
{
	int nRet;
	char* pSetTag = NOTIFICATION_TAG;

	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_load_by_tag(pSetTag);
	nRet = get_last_result();
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "notification_load_by_tag", NotificationGetError(nRet), FreeAndDeleteNotificationResourceHandle(););

	FreeAndDeleteNotificationResourceHandle();
	return 0;
}


//& purpose: check tizen.org/privilege/notification privilege.
//& type: auto
/**
* @testcase			CTc_Notification_PrivilegeNotification_update
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @scenario			Creates internal structure data and returns a notification handle\n
* 					update notification\n
* 					Frees the internal structure data of a notification handle
* @apicovered		notification_update
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_Notification_PrivilegeNotification_update(void)
{
	int nRet;

	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	nRet = notification_update(g_NotificationHandle);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "notification_update", NotificationGetError(nRet), FreeAndDeleteNotificationResourceHandle(););

	FreeAndDeleteNotificationResourceHandle();
	return 0;
}
