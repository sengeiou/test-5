//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-notification-common.h"
#include <notification.h>

bool CreateNotification(notification_type_e eNotificationType);

notification_h g_NotificationHandle;
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

/**
* @function 		NotificationGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* NotificationGetError(int nRet)
{
	char *szErrorVal = NULL;
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
	default:										szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function 		CreateNotification
* @description 	Creates internal structure data and returns a notification handle.
* @parameter       NotificationType
* @return			NA
*/
bool CreateNotification(notification_type_e eNotificationType)
{
	int nRet = 0;
	FreeAndDeleteNotificationResourceHandle();
	g_NotificationHandle = notification_create(eNotificationType);
	CHECK_HANDLE(g_NotificationHandle, "notification_create");

	nRet = notification_post(g_NotificationHandle);
	if ( nRet != NOTIFICATION_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] notification_post failed, error returned = %s\\n", __LINE__, API_NAMESPACE, NotificationGetError(nRet));
		return false;
	}

	return true;
}

/** @addtogroup itc-notification
* @ingroup		itc
* @{
*/

//& set: notification

/**
* @function 		ITs_notification_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_notification_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Notification_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_notification_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_notification_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Notification_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	itc-notification-testcases
* @brief 		Integration testcases for module notification
* @ingroup		itc-notification
* @{
*/

//& type : auto
//& purpose: Creates a notification clone.
/**
* @testcase	 			ITc_notification_clone_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a notification clone.
* @scenario				Create notification\n
*						Perform notification_clone API\n
*						Check return value and also check clone value is null or not.
* @apicovered			notification_create, notification_clone
* @passcase				notification_clone is successful and return correct value
* @failcase				notification_clone gets failed or return null value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_clone_p(void)
{
	START_TEST;
	notification_error_e eRetNotiErr;

	notification_type_e noti_type[] = { NOTIFICATION_TYPE_NOTI, NOTIFICATION_TYPE_ONGOING };
	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		notification_h cloneNotiHandler = NULL;
		g_NotificationHandle = notification_create(noti_type[enum_counter]);
		if ( NULL == g_NotificationHandle )
		{
			FPRINTF("[Line : %d][%s] notification_create failed for notification_type_e enum value = %d, returns null handle value\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter]);
			return 1;
		}

		eRetNotiErr = notification_clone(g_NotificationHandle, &cloneNotiHandler);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_clone", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		if ( NULL == cloneNotiHandler )
		{
			FPRINTF("[Line : %d][%s] notification_clone returns null handler for notification_type_e enum value = %d\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter]);
			FreeAndDeleteNotificationResourceHandle();
			return 1;
		}
		notification_free(cloneNotiHandler);
		FreeAndDeleteNotificationResourceHandle();
	}
	return 0;
}

//& type : auto
//& purpose: Creates notification handle
/**
* @testcase	 			ITc_notifiation_create_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates notification handle
* @scenario				Creates notification handle\n
*						Free and delete the handle
* @apicovered			notification_create
* @passcase				notifiation_create is successful and return valid handle
* @failcase				notifiation_create gets failed or return invalid handle
* @precondition			NA
* @postcondition		NA
*/
int ITc_notifiation_create_p(void)
{
	START_TEST;

	notification_type_e noti_type[] = { NOTIFICATION_TYPE_NOTI, NOTIFICATION_TYPE_ONGOING };
	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		g_NotificationHandle = notification_create(noti_type[enum_counter]);
		if ( NULL == g_NotificationHandle )
		{
			FPRINTF("[Line : %d][%s] notification_create failed for notification_type_e enum value = %d, returns null handle value\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter]);
			return 1;
		}
		FreeAndDeleteNotificationResourceHandle();
	}
	return 0;
}

//& type : auto
//& purpose: Creates and deleted notification handle
/**
* @testcase	 			ITc_notification_delete_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates and deleted notification handle
* @scenario				Creates notification handle\n
*						Free and delete the handle
* @apicovered			notification_create, notification_free, notification_delete
* @passcase				notifiation_delete is successful and behave properly
* @failcase				notifiation_delete gets failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_delete_p(void)
{
	START_TEST;

	notification_error_e eRetNotiErr;

	notification_type_e noti_type[] = { NOTIFICATION_TYPE_NOTI, NOTIFICATION_TYPE_ONGOING };
	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		g_NotificationHandle = notification_create(noti_type[enum_counter]);
		if ( NULL == g_NotificationHandle )
		{
			FPRINTF("[Line : %d][%s] notification_create failed for notification_type_e enum value = %d, returns null handle vale\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter]);
			return 1;
		}

		eRetNotiErr = notification_delete(g_NotificationHandle);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_delete", NotificationGetError(eRetNotiErr), notification_free(g_NotificationHandle););

		notification_free(g_NotificationHandle);
	}
	return 0;
}

//& type : auto
//& purpose: Creates and frees notification handle
/**
* @testcase	 			ITc_notification_free_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates and frees notification handle
* @scenario				Creates notification handle\n
*						Free and delete the handle
* @apicovered			notification_create, notification_free, notification_delete
* @passcase				notifiation_free is successful and behave properly
* @failcase				notifiation_free gets failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_free_p(void)
{
	START_TEST;

	notification_error_e eRetNotiErr;
	notification_type_e noti_type[] = { NOTIFICATION_TYPE_NOTI, NOTIFICATION_TYPE_ONGOING };

	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		g_NotificationHandle = notification_create(noti_type[enum_counter]);
		if ( NULL == g_NotificationHandle )
		{
			FPRINTF("[Line : %d][%s] notification_create failed for notification_type_e enum value = %d, returns null handle vale\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter]);
			return 1;
		}
		notification_delete(g_NotificationHandle);
		eRetNotiErr = notification_free(g_NotificationHandle);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_free", NotificationGetError(eRetNotiErr), FREE_MEMORY(g_NotificationHandle));
	}
	return 0;
}

//& type : auto
//& purpose: Creates and deletes all notifications.
/**
* @testcase	 			ITc_notification_delete_all_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates and deletes all notifications.
* @scenario				Create notification\n
*						Delete all notifications of the given type
* @apicovered			notification_create, notification_delete_all
* @passcase				notification_delete_all is successful after notification_create operation.
* @failcase				Return error code for notification_delete_all or notification_create reports error
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_delete_all_p(void)
{
	START_TEST;

	notification_error_e eRetNotiErr;

	notification_type_e noti_type[] = { NOTIFICATION_TYPE_NOTI, NOTIFICATION_TYPE_ONGOING };
	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		g_NotificationHandle = notification_create(noti_type[enum_counter]);
		if ( NULL == g_NotificationHandle )
		{
			FPRINTF("[Line : %d][%s] notification_create failed for notification_type_e enum value = %d, returns null handle vale\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter]);
			return 1;
		}

		eRetNotiErr = notification_delete_all(noti_type[enum_counter]);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_delete_all", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		FreeAndDeleteNotificationResourceHandle();
	}
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification image
/**
* @testcase	 			ITc_notification_set_get_image_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification image
* @scenario				Creates notification\n
*						Set image\n
*						Get image\n
*						Validate the get image
* @apicovered			notification_get_image, notification_set_image
* @passcase				notification_set_image and notification_get_image are successful and return correct value
* @failcase				notification_set_image or notification_get_image gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_image_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;

	notification_image_type_e noti_type[] = {
	NOTIFICATION_IMAGE_TYPE_ICON, /**< Icon */
	NOTIFICATION_IMAGE_TYPE_ICON_FOR_INDICATOR, /**< Indicator icon */
	NOTIFICATION_IMAGE_TYPE_ICON_FOR_LOCK, /**< Lock screen icon */
	NOTIFICATION_IMAGE_TYPE_THUMBNAIL, /**< Thumbnail */
	NOTIFICATION_IMAGE_TYPE_THUMBNAIL_FOR_LOCK, /**< Lock screen thumbnail */
	NOTIFICATION_IMAGE_TYPE_ICON_SUB, /**< Icon */
	NOTIFICATION_IMAGE_TYPE_BACKGROUND, /**< image displayed on background */
	NOTIFICATION_IMAGE_TYPE_LIST_1, /**< Image for thumbnail list */
	NOTIFICATION_IMAGE_TYPE_LIST_2, /**< Image for thumbnail list */
	NOTIFICATION_IMAGE_TYPE_LIST_3, /**< Image for thumbnail list */
	NOTIFICATION_IMAGE_TYPE_LIST_4, /**< Image for thumbnail list */
	NOTIFICATION_IMAGE_TYPE_LIST_5, /**< Image for thumbnail list */
	NOTIFICATION_IMAGE_TYPE_BUTTON_1, /**< Image for button 1 */
	NOTIFICATION_IMAGE_TYPE_BUTTON_2, /**< Image for button 2 */
	NOTIFICATION_IMAGE_TYPE_BUTTON_3, /**< Image for button 3 */
	NOTIFICATION_IMAGE_TYPE_BUTTON_4, /**< Image for button 4 */
	NOTIFICATION_IMAGE_TYPE_BUTTON_5, /**< Image for button 5 */
	NOTIFICATION_IMAGE_TYPE_BUTTON_6, /**< Image for button 6 */
	NOTIFICATION_IMAGE_TYPE_TEXT_INPUT_BUTTON, /**< Image for message reply(Since 3.0) */
	NOTIFICATION_IMAGE_TYPE_EXTENSION, /**< Image for extended notification (Since 4.0) */
	NOTIFICATION_IMAGE_TYPE_BUTTON_7, /**< Image for button 7 (Since 5.0) */
	NOTIFICATION_IMAGE_TYPE_BUTTON_8, /**< Image for button 8 (Since 5.0) */
	NOTIFICATION_IMAGE_TYPE_BUTTON_9, /**< Image for button 9 (Since 5.0) */
	NOTIFICATION_IMAGE_TYPE_BUTTON_10, /**< Image for button 10 (Since 5.0) */
	};

	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		eRetNotiErr  = notification_set_image(g_NotificationHandle, noti_type[enum_counter],(char*)APP_IMAGE_FULL_PATH);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_image", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		char *pszGetImage = NULL;
		eRetNotiErr  = notification_get_image(g_NotificationHandle, noti_type[enum_counter], &pszGetImage);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_image", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		if ( 0 != strcmp(APP_IMAGE_FULL_PATH, pszGetImage) )
		{
			FPRINTF("[Line : %d][%s] Mismatch happened for notification_image_type_e enum value = %d, setvalue = %s, get value = %s\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter], APP_IMAGE_FULL_PATH, pszGetImage);
			FreeAndDeleteNotificationResourceHandle();
			return 1;
		}
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification layout.
/**
* @testcase	 			ITc_notification_set_get_layout_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification layout.
* @scenario				Creates notification\n
*						Set layout\n
*						Get layout\n
*						Validate the get layout
* @apicovered			notification_get_layout, notification_set_layout
* @passcase				notification_set_layout and notification_get_layout are successful and return correct value
* @failcase				notification_set_layout or notification_get_layout gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_layout_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr = notification_set_layout(g_NotificationHandle,NOTIFICATION_LY_NOTI_EVENT_SINGLE);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_layout", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	notification_ly_type_e eRetLyType = NOTIFICATION_LY_NONE;
	eRetNotiErr  = notification_get_layout(g_NotificationHandle, &eRetLyType);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_layout", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	if ( NOTIFICATION_LY_NOTI_EVENT_SINGLE != eRetLyType )
	{
		FPRINTF("[Line : %d][%s] Mismatch happened, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, NOTIFICATION_LY_NOTI_EVENT_SINGLE, eRetLyType);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification led.
/**
* @testcase	 			ITc_notification_set_get_led_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification led.
* @scenario				Creates notification\n
*						Set led\n
*						Get led\n
*						Validate the get led
* @apicovered			notification_get_led, notification_set_led
* @passcase				notification_set_led and notification_get_led are successful and return correct value
* @failcase				notification_set_led or notification_get_led gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_led_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}
	notification_error_e eRetNotiErr;
	notification_led_op_e noti_type[] = { NOTIFICATION_LED_OP_ON, NOTIFICATION_LED_OP_ON_CUSTOM_COLOR};
	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		eRetNotiErr  = notification_set_led(g_NotificationHandle, noti_type[enum_counter], NOTIFICATION_LED_COLOR);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_led", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		notification_led_op_e eRetLedOpType = NOTIFICATION_LED_OP_OFF;
		eRetNotiErr  = notification_get_led(g_NotificationHandle, &eRetLedOpType,NULL);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_led", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		if ( noti_type[enum_counter] != eRetLedOpType)
		{
			FPRINTF("[Line : %d][%s] Mismatch happened for notification_led_op_e enum value = %d, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter], noti_type[enum_counter], eRetLedOpType);
			FreeAndDeleteNotificationResourceHandle();
			return 1;
		}
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification led_time_period.
/**
* @testcase	 			ITc_notification_set_get_led_time_period_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification led_time_period.
* @scenario				Creates notification\n
*						Set led_time_period\n
*						Get led_time_period\n
*						Validate the get led_time_period
* @apicovered			notification_get_led_time_period, notification_set_led_time_period
* @passcase				notification_set_led_time_period and notification_get_led_time_period are successful and return correct value
* @failcase				notification_set_led_time_period or notification_get_led_time_period gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_led_time_period_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;

	int nSetLedOnMs = 100, nSetLedOffMs = 100, nGetLedOnMs = 0, nGetLedOffMs = 0;
	eRetNotiErr  = notification_set_led_time_period(g_NotificationHandle, nSetLedOnMs, nSetLedOffMs);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_led_time_period", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	eRetNotiErr  = notification_get_led_time_period(g_NotificationHandle, &nGetLedOnMs, &nGetLedOffMs);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_led_time_period", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	if ( (nSetLedOnMs != nGetLedOnMs) || (nSetLedOffMs != nGetLedOffMs) )
	{
		FPRINTF("[Line : %d][%s] Mismatch happened , set value = (%d,%d), get value = (%d,%d)\\n", __LINE__, API_NAMESPACE, nSetLedOnMs, nSetLedOffMs, nGetLedOnMs, nGetLedOffMs);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification size.
/**
* @testcase	 			ITc_notification_set_get_size_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification size.
* @scenario				Creates notification\n
*						Set size\n
*						Get size\n
*						Validate the get size
* @apicovered			notification_get_size, notification_set_size
* @passcase				notification_set_size and notification_get_size are successful and return correct value
* @failcase				notification_set_size or notification_get_size gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_size_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;
	eRetNotiErr  = notification_set_size(g_NotificationHandle, NOTIFICATION_SET_SIZE_VAL);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_size", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	double dGetSizeVal = 0.0;
	eRetNotiErr  = notification_get_size(g_NotificationHandle, &dGetSizeVal);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_size", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	if ( NOTIFICATION_SET_SIZE_VAL != dGetSizeVal )
	{
		FPRINTF("[Line : %d][%s] Mismatch happened, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, (int)NOTIFICATION_SET_SIZE_VAL, (int)dGetSizeVal);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification text.
/**
* @testcase	 			ITc_notification_set_get_text_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification text.
* @scenario				Creates notification\n
*						Set text\n
*						Get text\n
*						Validate the set text
* @apicovered			notification_get_text, notification_set_text
* @passcase				notification_set_text and notification_get_text are successful and set correct value
* @failcase				notification_set_text or notification_get_text gets failed or set incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_text_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;

	notification_text_type_e noti_type[] = {
	NOTIFICATION_TEXT_TYPE_TITLE , /**< Title */
	NOTIFICATION_TEXT_TYPE_CONTENT, /**< Content */
	NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, /**< Content for content display option is off of the Settings */
	NOTIFICATION_TEXT_TYPE_EVENT_COUNT, /**< Text to display event count */
	NOTIFICATION_TEXT_TYPE_INFO_1, /**< Box contents 1 */
	NOTIFICATION_TEXT_TYPE_INFO_SUB_1, /**< Box contents 1-1 */
	NOTIFICATION_TEXT_TYPE_INFO_2, /**< Box contents 2 */
	NOTIFICATION_TEXT_TYPE_INFO_SUB_2, /**< Box contents 2-1 */
	NOTIFICATION_TEXT_TYPE_INFO_3, /**< Box contents 3 */
	NOTIFICATION_TEXT_TYPE_INFO_SUB_3, /**< Box contents 3-1 */
	NOTIFICATION_TEXT_TYPE_GROUP_TITLE, /**< Group title */
	NOTIFICATION_TEXT_TYPE_GROUP_CONTENT, /**< Group content */
	NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, /**< Group content for content display option is off of the Settings */
	NOTIFICATION_TEXT_TYPE_BUTTON_1, /**< Text on button 1 */
	NOTIFICATION_TEXT_TYPE_BUTTON_2, /**< Text on button 2 */
	NOTIFICATION_TEXT_TYPE_BUTTON_3, /**< Text on button 3 */
	NOTIFICATION_TEXT_TYPE_BUTTON_4, /**< Text on button 4 */
	NOTIFICATION_TEXT_TYPE_BUTTON_5, /**< Text on button 5 */
	NOTIFICATION_TEXT_TYPE_BUTTON_6, /**< Text on button 6 */
	NOTIFICATION_TEXT_TYPE_TEXT_INPUT_PLACEHOLDER, /**< Guide text on the message reply box(Since 3.0) */
	NOTIFICATION_TEXT_TYPE_TEXT_INPUT_BUTTON, /**< Text on button the on message reply box(Since 3.0) */
	NOTIFICATION_TEXT_TYPE_CONTENT_EXTENSION, /**< Content for extended notification (Since 4.0) */
	NOTIFICATION_TEXT_TYPE_BUTTON_7, /**< Text on button 7 (Since 5.0) */
	NOTIFICATION_TEXT_TYPE_BUTTON_8, /**< Text on button 8 (Since 5.0) */
	NOTIFICATION_TEXT_TYPE_BUTTON_9, /**< Text on button 9 (Since 5.0) */
	NOTIFICATION_TEXT_TYPE_BUTTON_10, /**< Text on button 10 (Since 5.0) */

	};

	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		eRetNotiErr  = notification_set_text(g_NotificationHandle, noti_type[enum_counter],(char*)BASIC_TEXT, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_text", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		char *pszGetText = NULL;
		eRetNotiErr  = notification_get_text(g_NotificationHandle, noti_type[enum_counter], &pszGetText);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_text", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		if ( 0 != strcmp(pszGetText, BASIC_TEXT) )
		{
			FPRINTF("[Line : %d][%s] Mismatch happened for notification_text_type_e enum value = %d, setvalue = %s, get value = %s\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter], BASIC_TEXT, pszGetText);
			FreeAndDeleteNotificationResourceHandle();
			return 1;
		}
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification sound.
/**
* @testcase	 			ITc_notification_set_get_sound_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification sound.
* @scenario				Creates notification\n
*						Set sound\n
*						Get sound\n
*						Validate the get sound
* @apicovered			notification_get_sound, notification_set_sound
* @passcase				notification_set_sound and notification_get_sound are successful and return correct value
* @failcase				notification_set_sound or notification_get_sound gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_sound_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;

	notification_sound_type_e noti_type[] = { NOTIFICATION_SOUND_TYPE_DEFAULT,
		NOTIFICATION_SOUND_TYPE_USER_DATA};

	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		eRetNotiErr  = notification_set_sound(g_NotificationHandle, noti_type[enum_counter], (char*)DEFAULT_FILE_PATH);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_sound", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		notification_sound_type_e eSoundType = -1;
		const char *pszGetSoundPath = NULL;

		eRetNotiErr  = notification_get_sound(g_NotificationHandle, &eSoundType, &pszGetSoundPath);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_sound", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		if ( noti_type[enum_counter] != eSoundType )
		{
			FPRINTF("[Line : %d][%s] Mismatch happened for notification_sound_type_e enum value = %d, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter], noti_type[enum_counter], eSoundType);
			FreeAndDeleteNotificationResourceHandle();
			return 1;
		}
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification vibration.
/**
* @testcase	 			ITc_notification_set_get_vibration_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification vibration.
* @scenario				Creates notification\n
*						Set vibration\n
*						Get vibration\n
*						Validate the get vibration
* @apicovered			notification_get_vibration, notification_set_vibration
* @passcase				notification_set_vibration and notification_get_vibration are successful and return correct value
* @failcase				notification_set_vibration or notification_get_vibration gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_vibration_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;
	notification_vibration_type_e noti_type[] = { NOTIFICATION_VIBRATION_TYPE_DEFAULT, NOTIFICATION_VIBRATION_TYPE_USER_DATA};
	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		eRetNotiErr  = notification_set_vibration(g_NotificationHandle, noti_type[enum_counter],(char*)DEFAULT_FILE_PATH);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_vibration", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		const char *pszGetVibrationPath = NULL;
		notification_vibration_type_e eVibrationType = -1;
		eRetNotiErr  = notification_get_vibration(g_NotificationHandle, &eVibrationType, &pszGetVibrationPath);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_vibration", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		if ( noti_type[enum_counter] != eVibrationType )
		{
			FPRINTF("[Line : %d][%s] Mismatch happened for notification_vibration_type_e enum value = %d, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter], noti_type[enum_counter], eVibrationType);
			FreeAndDeleteNotificationResourceHandle();
			return 1;
		}
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification time.
/**
* @testcase	 			ITc_notification_set_get_time_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification time.
* @scenario				Creates notification\n
*						Set time\n
*						Get time\n
*						Validate the get time
* @apicovered			notification_get_time, notification_set_time
* @passcase				notification_set_time and notification_get_time are successful and return correct value
* @failcase				notification_set_time or notification_get_time gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_time_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;

	time_t setTime = time(NULL);

	eRetNotiErr  = notification_set_time(g_NotificationHandle, setTime);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_time", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	time_t getTime = 0;

	eRetNotiErr  = notification_get_time(g_NotificationHandle, &getTime);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_time", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	if ( getTime != setTime )
	{
		FPRINTF("[Line : %d][%s] Mismatch happened, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, (int)setTime, (int)getTime);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification time_from_text.
/**
* @testcase	 			ITc_notification_set_get_time_from_text_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification time_from_text.
* @scenario				Creates notification\n
*						Set time_to_text\n
*						Get time_from_text\n
*						Validate the get time_from_text
* @apicovered			notification_get_time_from_text, notification_set_time_to_text
* @passcase				notification_set_time_to_text and notification_get_time_from_text are successful and return correct value
* @failcase				notification_set_time_to_text or notification_get_time_from_text gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_time_from_text_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;

	time_t setTime = time(NULL);

	notification_text_type_e noti_type[] = {
	NOTIFICATION_TEXT_TYPE_TITLE , /**< Title */
	NOTIFICATION_TEXT_TYPE_CONTENT, /**< Content */
	NOTIFICATION_TEXT_TYPE_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, /**< Content for content display option is off of the Settings */
	NOTIFICATION_TEXT_TYPE_EVENT_COUNT, /**< Text to display event count */
	NOTIFICATION_TEXT_TYPE_INFO_1, /**< Box contents 1 */
	NOTIFICATION_TEXT_TYPE_INFO_SUB_1, /**< Box contents 1-1 */
	NOTIFICATION_TEXT_TYPE_INFO_2, /**< Box contents 2 */
	NOTIFICATION_TEXT_TYPE_INFO_SUB_2, /**< Box contents 2-1 */
	NOTIFICATION_TEXT_TYPE_INFO_3, /**< Box contents 3 */
	NOTIFICATION_TEXT_TYPE_INFO_SUB_3, /**< Box contents 3-1 */
	NOTIFICATION_TEXT_TYPE_GROUP_TITLE, /**< Group title */
	NOTIFICATION_TEXT_TYPE_GROUP_CONTENT, /**< Group content */
	NOTIFICATION_TEXT_TYPE_GROUP_CONTENT_FOR_DISPLAY_OPTION_IS_OFF, /**< Group content for content display option is off of the Settings */
	NOTIFICATION_TEXT_TYPE_BUTTON_1, /**< Text on button 1 */
	NOTIFICATION_TEXT_TYPE_BUTTON_2, /**< Text on button 2 */
	NOTIFICATION_TEXT_TYPE_BUTTON_3, /**< Text on button 3 */
	NOTIFICATION_TEXT_TYPE_BUTTON_4, /**< Text on button 4 */
	NOTIFICATION_TEXT_TYPE_BUTTON_5, /**< Text on button 5 */
	NOTIFICATION_TEXT_TYPE_BUTTON_6, /**< Text on button 6 */
	NOTIFICATION_TEXT_TYPE_TEXT_INPUT_PLACEHOLDER, /**< Guide text on the message reply box(Since 3.0) */
	NOTIFICATION_TEXT_TYPE_TEXT_INPUT_BUTTON, /**< Text on button the on message reply box(Since 3.0) */
	NOTIFICATION_TEXT_TYPE_CONTENT_EXTENSION, /**< Content for extended notification (Since 4.0) */
	};

	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		eRetNotiErr  = notification_set_time_to_text(g_NotificationHandle, noti_type[enum_counter], setTime);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_time_to_text", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		time_t getTime = 0;

		eRetNotiErr  = notification_get_time_from_text(g_NotificationHandle, noti_type[enum_counter], &getTime);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_time_from_text", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		if ( getTime != setTime )
		{
			FPRINTF("[Line : %d][%s] Mismatch happened for notification_text_type_e enum value = %d, setvalue = %d, get value = %d\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter], (int)setTime, (int)getTime);
			FreeAndDeleteNotificationResourceHandle();
			return 1;
		}
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification progress.
/**
* @testcase	 			ITc_notification_set_get_progress_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification progress.
* @scenario				Creates notification\n
*						Set progress\n
*						Get progress\n
*						Validate the get progress
* @apicovered			notification_get_progress, notification_set_progress
* @passcase				notification_set_progress and notification_get_progress are successful and return correct value
* @failcase				notification_set_progress or notification_get_progress gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_progress_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;

	eRetNotiErr  = notification_set_progress(g_NotificationHandle,NOTIFICATION_SET_PROGRESS_VAL);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_progress", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	double dGetProgressVal = 0.0;

	eRetNotiErr  = notification_get_progress(g_NotificationHandle, &dGetProgressVal);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_progress", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	if ( NOTIFICATION_SET_PROGRESS_VAL != dGetProgressVal )
	{
		FPRINTF("[Line : %d][%s] Mismatch happened, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, (int)NOTIFICATION_SET_PROGRESS_VAL, (int)dGetProgressVal);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification property.
/**
* @testcase	 			ITc_notification_set_get_property_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification property
* @scenario				Creates notification\n
*						Set property\n
*						Get property\n
*						Validate the get property
* @apicovered			notification_get_property, notification_set_property
* @passcase				notification_set_property and notification_get_property are successful and return correct value
* @failcase				notification_set_property or notification_get_property gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_property_p(void)
{
	START_TEST;

	notification_error_e eRetNotiErr;

	enum _notification_property noti_type[] = { NOTIFICATION_PROP_DISPLAY_ONLY_SIMMODE,
		NOTIFICATION_PROP_DISABLE_APP_LAUNCH,
		NOTIFICATION_PROP_DISABLE_AUTO_DELETE,
		NOTIFICATION_PROP_LAUNCH_UG,
		NOTIFICATION_PROP_DISABLE_TICKERNOTI,
		NOTIFICATION_PROP_PERMANENT_DISPLAY,
		NOTIFICATION_PROP_DISABLE_UPDATE_ON_INSERT,
		NOTIFICATION_PROP_DISABLE_UPDATE_ON_DELETE,
		NOTIFICATION_PROP_VOLATILE_DISPLAY};

	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		g_NotificationHandle = notification_create(NOTIFICATION_TYPE_NOTI);
		if ( NULL == g_NotificationHandle )
		{
			FPRINTF("[Line : %d][%s] notification_create returned NULL handle\\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		eRetNotiErr  = notification_set_property(g_NotificationHandle, noti_type[enum_counter]);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_property", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		int nGetNotiProperty = 0;

		eRetNotiErr  = notification_get_property(g_NotificationHandle, &nGetNotiProperty);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_property", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		if ( nGetNotiProperty != noti_type[enum_counter] )
		{
			FPRINTF("[Line : %d][%s] Mismatch happened for _notification_property enum value = %d, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter], noti_type[enum_counter], nGetNotiProperty);
			FreeAndDeleteNotificationResourceHandle();
			return 1;
		}
		FreeAndDeleteNotificationResourceHandle();
	}
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification display_applist.
/**
* @testcase	 			ITc_notification_set_get_display_applist_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification display_applist.
* @scenario				Creates notification\n
*						Set display_applist\n
*						Get display_applist\n
*						Validate the get display_applist
* @apicovered			notification_get_display_applist, notification_set_display_applist
* @passcase				notification_set_display_applist and notification_get_display_applist are successful and return correct value
* @failcase				notification_set_display_applist or notification_get_display_applist gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_display_applist_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;

	enum _notification_display_applist noti_type[] = { NOTIFICATION_DISPLAY_APP_NOTIFICATION_TRAY,
		NOTIFICATION_DISPLAY_APP_TICKER,
		NOTIFICATION_DISPLAY_APP_LOCK,
		NOTIFICATION_DISPLAY_APP_INDICATOR,
		NOTIFICATION_DISPLAY_APP_ALL};

	int enum_size = sizeof(noti_type) / sizeof(noti_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		eRetNotiErr  = notification_set_display_applist(g_NotificationHandle, noti_type[enum_counter]);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_display_applist", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		int nGetDisplayApplistVal = 0;
		eRetNotiErr  = notification_get_display_applist(g_NotificationHandle, &nGetDisplayApplistVal);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_display_applist", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

		if ( noti_type[enum_counter] != nGetDisplayApplistVal )
		{
			FPRINTF("[Line : %d][%s] Mismatch happened for _notification_display_applist enum value = %d, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, noti_type[enum_counter], noti_type[enum_counter], nGetDisplayApplistVal);
			FreeAndDeleteNotificationResourceHandle();
			return 1;
		}
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Get the notification type.
/**
* @testcase	 			ITc_notification_get_type_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Get the notification type.
* @scenario				Creates notification of NOTIFICATION_TYPE_NOTI type\n
*						Get type\n
*						Validate the get type
* @apicovered			notification_get_type
* @passcase				notification_get_type is successful and return correct value
* @failcase				notification_get_type gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_get_type_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;

	notification_type_e eGetNotificationType = NOTIFICATION_TYPE_NONE;
	eRetNotiErr  = notification_get_type(g_NotificationHandle, &eGetNotificationType);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_type", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	if ( NOTIFICATION_TYPE_NOTI != eGetNotificationType )
	{
		FPRINTF("[Line : %d][%s] Mismatch happened, expected value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, NOTIFICATION_TYPE_NOTI, eGetNotificationType);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Get Insertion time of the inserted notification.
/**
* @testcase	 			ITc_notification_get_insert_time_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Get Insertion time of the inserted notification.
* @scenario				Create notification\n
*						Set package name to the notification\n
*						Insert notification and fetch private id\n
*						Get Insertion Time
* @apicovered			notification_get_insert_time
* @passcase				notification_get_insert_time is successful and returns valid value
* @failcase				notification_get_insert_time returns error or invalid value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_get_insert_time_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;
	time_t ret_time = 0;

	eRetNotiErr = notification_get_insert_time(g_NotificationHandle, &ret_time);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_insert_time", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	if ( ret_time <= 0 )
	{
		FPRINTF("[Line : %d][%s] notification_get_insert_time returns invalid value = %d\\n", __LINE__, API_NAMESPACE, (int)ret_time);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type: auto
//& purpose: Post notification status message.
/**
* @testcase 				ITc_notification_status_message_post_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Post notification status message.
* @scenario				Set notification status monitor message callback\n
*						Post status Message\n
*						Check monitor message callback\n
*						Unset the callback
* @apicovered			notification_status_message_post
* @passcase				notification_status_message_post should be successful and behave properly
* @failcase				notification_status_message_post gets failed or didn't behaved properly
* @precondition			none
* @postcondition		none
*/
int ITc_notification_status_message_post_p(void)
{
	START_TEST;

	notification_error_e eRetNotiErr = notification_status_message_post(BASIC_TEXT);
	PRINT_RESULT(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_status_message_post", NotificationGetError(eRetNotiErr));
	usleep(WAIT_CALLBACK*MICROSECONDS_PER_SECOND);
	return 0;
}

//& type : auto
//& purpose: Updates notification data.
/**
* @testcase	 			ITc_notification_update_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Updates notification data.
* @scenario				Create notification\n
*						Set package name to the notification\n
*						Insert notification and fetch private id\n
*						Call notification_update to update notification data
* @apicovered			notification_update
* @passcase				notification_update is successful.
* @failcase				notification_update returns error
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_update_p(void)
{
	START_TEST;
	notification_error_e eRetNotiErr = NOTIFICATION_ERROR_NONE;
	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	eRetNotiErr = notification_set_text(g_NotificationHandle, NOTIFICATION_TEXT_TYPE_TITLE, "updated", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);	//sample text : "updated"
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_text", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	eRetNotiErr = notification_update(g_NotificationHandle);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_update", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set/Get the notification tag.
/**
* @testcase	 			ITc_notification_set_get_tag_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the notification tag.
* @scenario				Creates notification\n
*						Set tag\n
*						Get tag\n
*						Validate the get tag
* @apicovered			notification_get_tag, notification_set_tag
* @passcase				notification_set_tag and notification_get_tag are successful and return correct value
* @failcase				notification_set_tag or notification_get_tag gets failed or return incorrect value
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_tag_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	char* pSetTag = NOTIFICATION_TAG;

	const char* pGetTag = NULL;
	notification_error_e eRetNotiErr  = notification_set_tag(g_NotificationHandle,NOTIFICATION_TAG);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_tag", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	eRetNotiErr  = notification_get_tag(g_NotificationHandle, &pGetTag);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_tag", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	if ( NULL == pGetTag )
	{
		FPRINTF("[Line : %d][%s] notification_get_tag output NULL tag value\\n", __LINE__, API_NAMESPACE);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}

	if ( 0 != strcmp(pGetTag, pSetTag) )
	{
		FPRINTF("[Line : %d][%s] Mismatch happened, set value = (%s), get value = (%s)\\n", __LINE__, API_NAMESPACE, pSetTag, pGetTag);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}

	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Loads the notification tag.
/**
* @testcase	 			ITc_notification_load_by_tag_p
* @since_tizen 			2.3
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Loads the notification tag.
* @scenario				Creates notification\n
*						Set tag\n
*						Load tag
* @apicovered			notification_set_tag, notification_load_by_tag
* @passcase				notification_load_by_tag is successful and behave properly
* @failcase				notification_load_by_tag gets failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_load_by_tag_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;

	char* pSetTag = NOTIFICATION_TAG;
	eRetNotiErr  = notification_set_tag(g_NotificationHandle,pSetTag);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_tag", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	eRetNotiErr = notification_post(g_NotificationHandle);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_post", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	notification_h hNotificationHandle = NULL;
	hNotificationHandle = notification_load_by_tag(pSetTag);

	if ( NULL == hNotificationHandle )
	{
		FPRINTF("[Line : %d][%s] notification_load_by_tag returned NULL handle\\n", __LINE__, API_NAMESPACE);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type: auto
//& purpose: Post notification
/**
* @testcase	 			ITc_notification_post_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Post notification
* @scenario				Create notification handle\n
*						Set Pkg name\n
*						Insert notification handle\n
*						call notification_post.
* @apicovered			notification_create, notification_post
* @passcase				notification_post is successful and behave properly
* @failcase				notification_post gets failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_post_p(void)
{
	START_TEST;

	FreeAndDeleteNotificationResourceHandle();
	g_NotificationHandle = notification_create(NOTIFICATION_TYPE_NOTI);
	CHECK_HANDLE(g_NotificationHandle, "notification_create");

	notification_error_e eRetNotiErr = NOTIFICATION_ERROR_NONE;

	eRetNotiErr = notification_post(g_NotificationHandle);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_post", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););

	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type: auto
//& purpose: Set/Get launch option for a notification
/**
* @testcase	 			ITc_notification_set_get_launch_option_p
* @since_tizen 			2.3
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get launch option for a notification
* @scenario				Create notification handle\n
*						Set Pkg name\n
*						Insert notification handle\n
*						call notification_set_launch_option\n
*						call notification_get_launch_option and validate result
* @apicovered			notification_set_launch_option, notification_get_launch_option
* @passcase				notification_set_launch_option and notification_get_launch_option are successful and behave properly
* @failcase				notification_set_launch_option or notification_get_launch_option gets failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_set_get_launch_option_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", Application_AppControlGetError(nRet));
	if(NULL == hAppControl)
	{
		FPRINTF("[Line : %d][%s]app_control_create returned NULL handle value\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char* pSetAppID = "org.tizen.app";	//dummy app id
	nRet = app_control_set_app_id(hAppControl, pSetAppID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", Application_AppControlGetError(nRet), app_control_destroy(hAppControl););

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		app_control_destroy(hAppControl);
		return 1;
	}

	notification_error_e eRetNotiErr = NOTIFICATION_ERROR_NONE;

	eRetNotiErr = notification_set_launch_option(g_NotificationHandle, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, (void*)hAppControl);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_launch_option", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle();app_control_destroy(hAppControl););

	app_control_h hGetAppControl;
	nRet = app_control_create(&hGetAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", Application_AppControlGetError(nRet),FreeAndDeleteNotificationResourceHandle();app_control_destroy(hAppControl););
	if(NULL == hGetAppControl)
	{
		FPRINTF("[Line : %d][%s]app_control_create returned NULL handle value\\n", __LINE__, API_NAMESPACE);
		FreeAndDeleteNotificationResourceHandle();
		app_control_destroy(hAppControl);
		return 1;
	}

	eRetNotiErr = notification_get_launch_option(g_NotificationHandle, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, (void*)&hGetAppControl);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_launch_option", NotificationGetError(eRetNotiErr), app_control_destroy(hGetAppControl);FreeAndDeleteNotificationResourceHandle();app_control_destroy(hAppControl));

	char* pszGetVal = NULL;
	app_control_get_app_id(hGetAppControl, &pszGetVal);

	if ( NULL == pszGetVal )
	{
		FPRINTF("[Line : %d][%s]set and get operation mismatch occurs, set app id = %s, get app id = NULL\\n",__LINE__, API_NAMESPACE, pSetAppID);
		app_control_destroy(hGetAppControl);
		FreeAndDeleteNotificationResourceHandle();
		app_control_destroy(hAppControl);
		return 1;
	}

	//check for value mismatch
	if ( 0 != strcmp(pSetAppID, pszGetVal) )
	{
		FPRINTF("[Line : %d][%s]set and get operation mis-match occurs, set app id = %s, get app id = %s\\n ",__LINE__, API_NAMESPACE, pSetAppID, pszGetVal);
		FREE_MEMORY(pszGetVal);
		app_control_destroy(hGetAppControl);
		FreeAndDeleteNotificationResourceHandle();
		app_control_destroy(hAppControl);
		return 1;
	}


	FREE_MEMORY(pszGetVal);
	app_control_destroy(hGetAppControl);
	FreeAndDeleteNotificationResourceHandle();
	app_control_destroy(hAppControl);
	return 0;
}

//& type: auto
//& purpose: Set/Get event handler for a notification
/**
* @testcase	 			ITc_notification_set_get_event_handler_p
* @since_tizen 			2.4
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get event handler for a notification
* @scenario				Create notification handle\n
*						Set Pkg name\n
*						Insert notification handle\n
*						call notification_set_event_handler\n
*						call notification_get_event_handler and validate result
* @apicovered			notification_set_event_handler, notification_get_event_handler
* @passcase				notification_set_event_handler and notification_get_event_handler are successful and behave properly
* @failcase				notification_set_event_handler or notification_get_event_handler gets failed
* @precondition			NA
* @postcondition		NA
*/

int ITc_notification_set_get_event_handler_p(void)
{
	START_TEST;

	int nRetVal = -1;
	app_control_h hAppControl = NULL;
	app_control_h hGetAppControl = NULL;
	char* pszGetVal = NULL;

	nRetVal = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRetVal, "app_control_create", Application_AppControlGetError(nRetVal));

	CHECK_HANDLE(hAppControl, "app_control_create");

	char* pszSetAppID = "org.tizen.app";	//dummy app id
	nRetVal = app_control_set_app_id(hAppControl, pszSetAppID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRetVal, "app_control_set_app_id", Application_AppControlGetError(nRetVal), app_control_destroy(hAppControl););


	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI))
	{
		app_control_destroy(hAppControl);
		return 1;
	}

	nRetVal = app_control_create(&hGetAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRetVal, "app_control_create", Application_AppControlGetError(nRetVal),FreeAndDeleteNotificationResourceHandle(); app_control_destroy(hAppControl));

	CHECK_HANDLE_CLEANUP(hGetAppControl, "app_control_create", app_control_destroy(hAppControl); FreeAndDeleteNotificationResourceHandle());

	notification_error_e eRetNotiErr = NOTIFICATION_ERROR_NONE;

	notification_event_type_e eNoti_event_type[] =
	{
		NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_1,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_2,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_3,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_4,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_5,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_6,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_ICON,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_THUMBNAIL,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_TEXT_INPUT_BUTTON,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_7,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_8,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_9,
		NOTIFICATION_EVENT_TYPE_CLICK_ON_BUTTON_10
	};

	int enum_size = sizeof(eNoti_event_type) / sizeof(eNoti_event_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{

		//Target API
		eRetNotiErr = notification_set_event_handler(g_NotificationHandle, eNoti_event_type[enum_counter], hAppControl);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_event_handler", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle();app_control_destroy(hAppControl););

		//Target API
		eRetNotiErr = notification_get_event_handler(g_NotificationHandle, eNoti_event_type[enum_counter], &hGetAppControl);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_event_handler", NotificationGetError(eRetNotiErr),app_control_destroy(hGetAppControl);FreeAndDeleteNotificationResourceHandle();app_control_destroy(hAppControl));

		pszGetVal = NULL;
		app_control_get_app_id(hGetAppControl, &pszGetVal);

		CHECK_HANDLE_CLEANUP(pszGetVal, "app_control_get_app_id", app_control_destroy(hGetAppControl); app_control_destroy(hAppControl); FreeAndDeleteNotificationResourceHandle());

		//check for value mismatch
		if ( 0 != strcmp(pszSetAppID, pszGetVal) )
		{
			FPRINTF("[Line : %d][%s] set and get operation mis-match occurs, set app id = %s, get app id = %s\\n",  __LINE__, API_NAMESPACE, pszSetAppID, pszGetVal);
			FREE_MEMORY(pszGetVal);
			app_control_destroy(hGetAppControl);
			FreeAndDeleteNotificationResourceHandle();
			app_control_destroy(hAppControl);
			return 1;
		}
	}

	FREE_MEMORY(pszGetVal);
	app_control_destroy(hGetAppControl);
	FreeAndDeleteNotificationResourceHandle();
	app_control_destroy(hAppControl);

	return 0;
}

//& type : auto
//& purpose: Gets the package name
/**
* @testcase	 			ITc_notification_get_pkgname_p
* @since_tizen 			2.4
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the package name
* @scenario				Creates notification\n
*						Gets package name
* @apicovered			notification_get_pkgname
* @passcase				notification_get_pkgname is successful and behave properly
* @failcase				notification_get_pkgname gets failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_get_pkgname_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;
	char* pkgname = NULL;
	eRetNotiErr  = notification_get_pkgname(g_NotificationHandle, &pkgname);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_pkgname", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle());
	CHECK_HANDLE_CLEANUP(pkgname, "notification_get_pkgname", FreeAndDeleteNotificationResourceHandle());

	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Add and Remove Button
/**
* @testcase	 			ITc_notification_add_remove_button_p
* @since_tizen 			2.4
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Add and Remove Button
* @scenario				Creates notification\n
*						Add and remove button
* @apicovered			notification_add_button, notification_remove_button
* @passcase				notification_add_button and notification_remove_button is successful and behave properly
* @failcase				notification_add_button and notification_remove_button gets failed
* @precondition			NA
* @postcondition		NA
*/
int ITc_notification_add_remove_button_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}
	notification_error_e eRetNotiErr;

	notification_button_index_e eNoti_Button_index[] =
	{
		NOTIFICATION_BUTTON_1,
		NOTIFICATION_BUTTON_2,
		NOTIFICATION_BUTTON_3,
		NOTIFICATION_BUTTON_4,
		NOTIFICATION_BUTTON_5,
		NOTIFICATION_BUTTON_6,
		NOTIFICATION_BUTTON_7,
		NOTIFICATION_BUTTON_8,
		NOTIFICATION_BUTTON_9,
		NOTIFICATION_BUTTON_10
	} ;

	int enum_size = sizeof(eNoti_Button_index) / sizeof(eNoti_Button_index[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		eRetNotiErr  = notification_add_button(g_NotificationHandle, eNoti_Button_index[enum_counter]);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_add_button", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle());

		eRetNotiErr  = notification_remove_button(g_NotificationHandle, eNoti_Button_index[enum_counter]);
		PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_remove_button", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle());
	}

	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

//& type : auto
//& purpose: Set and Get auto remove
/**
* @testcase             ITc_notification_set_get_auto_remove_p
* @since_tizen          2.4
* @author               SRID(nibha.sharma)
* @reviewer             SRID(gupta.sanjay)
* @type                 auto
* @description          Set and Get auto remove
* @scenario             Creates notification\n
*                       Set and Get auto remove
* @apicovered           notification_set_auto_remove, notification_get_auto_remove
* @passcase             notification_set_auto_remove and notification_get_auto_remove is successful and behave properly
* @failcase             notification_set_auto_remove and notification_get_auto_remove gets failed
* @precondition         NA
* @postcondition        NA
*/
int ITc_notification_set_get_auto_remove_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_ONGOING) )
	{
			return 1;
	}

	bool bGetAutoRmv, bSetAutoRmv = false;
	notification_error_e eRetNotiErr;

	eRetNotiErr  = notification_set_auto_remove(g_NotificationHandle, bSetAutoRmv);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_auto_remove", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle());

	eRetNotiErr = notification_get_auto_remove(g_NotificationHandle, &bGetAutoRmv);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_auto_remove", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle());

	if ( bGetAutoRmv != bSetAutoRmv )
	{
		FPRINTF("[Line : %d][%s] set and get auto remove mis-match occurs, set auto remove = %d, get auto remove = %d\\n", __LINE__, API_NAMESPACE, bSetAutoRmv, bGetAutoRmv);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}

	FreeAndDeleteNotificationResourceHandle();
	return 0;
}


//& purpose:  Loads/Saves a notification template from the notification database
//& type : auto
/**
* @testcase 			ITc_notification_create_save_from_template_p
* @since_tizen 			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Loads/Saves a notification template from the notification database
* @scenario				notification_create_from_template, notification_save_as_template
* @apicovered			notification_create_from_template, notification_save_as_template
* @passcase				When API return NOTIFICATION_ERROR_NONE
* @failcase				When API not return NOTIFICATION_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_notification_create_save_from_template_p(void)
{
	START_TEST;
	int nRet = -1;
	const char *pTemplateName = "CALL_ACCEPT";
	notification_h hNotification;
	
	hNotification = notification_create(NOTIFICATION_TYPE_NOTI);
	CHECK_HANDLE(hNotification, "notification_create");
	
	nRet  = notification_set_text(hNotification, NOTIFICATION_TEXT_TYPE_TITLE, "I'm Title", "TITLE", NOTIFICATION_VARIABLE_TYPE_NONE);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_set_text", NotificationGetError(nRet),FREE_MEMORY(hNotification));
		
	//Target API
	nRet =  notification_save_as_template(hNotification, pTemplateName);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_save_as_template", NotificationGetError(nRet),FREE_MEMORY(hNotification));
	FREE_MEMORY(hNotification);
	
	//Target API
	hNotification =  notification_create_from_template(pTemplateName);
	CHECK_HANDLE(hNotification, "notification_create_from_template");
	FREE_MEMORY(hNotification);
		
	return 0;
}

//& type : auto
//& purpose: Gets notification block state
/**
* @testcase             ITc_notification_get_noti_block_state_p
* @since_tizen          3.0
* @author               SRID(a.pandia1)
* @reviewer             SRID(shobhit.v)
* @type                 auto
* @description          Gets notification block state
* @scenario             Gets notification block state
* @apicovered           notification_get_noti_block_state
* @passcase             notification_get_noti_block_state is successful
* @failcase             notification_get_noti_block_state gets failed
* @precondition         NA
* @postcondition        NA
*/
int ITc_notification_get_noti_block_state_p(void)
{
	START_TEST;

	notification_error_e eRetNotiErr;
	notification_block_state_e eBlockState = -1;
	
	eRetNotiErr  = notification_get_noti_block_state(&eBlockState);
	PRINT_RESULT(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_noti_block_state", NotificationGetError(eRetNotiErr));

	if ( eBlockState < NOTIFICATION_BLOCK_STATE_ALLOWED || eBlockState > NOTIFICATION_BLOCK_STATE_DO_NOT_DISTURB )
	{
		FPRINTF("[Line : %d][%s] Invalid block state output parameter \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Sets a text input box to reply directly on the notification.
/**
* @testcase	 			ITc_notification_set_text_input_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets a text input box to reply directly on the notification.
* @scenario				Create notification handle\n
*						Set Pkg name\n
*						Insert notification handle\n
*						call notification_set_text_input
* @apicovered			notification_set_text_input
* @passcase				notification_set_text_input is successful and behave properly
* @failcase				notification_set_text_input gets failed
* @precondition			NA
* @postcondition		NA
*/

int ITc_notification_set_text_input_p(void)
{
	START_TEST;

	char* pSetAppID = "org.tizen.app";	//dummy app id
	notification_h hNotification;
	app_control_h hAppControl;

	hNotification = notification_create(NOTIFICATION_TYPE_NOTI);
	CHECK_HANDLE(hNotification, "notification_create");

	int nRet = notification_set_text_input(hNotification, 160);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_set_text_input", NotificationGetError(nRet),FREE_MEMORY(hNotification));

	nRet  = notification_set_text(hNotification, NOTIFICATION_TEXT_TYPE_TEXT_INPUT_PLACEHOLDER, "I'm Title", "TITLE", NOTIFICATION_VARIABLE_TYPE_NONE);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_set_text", NotificationGetError(nRet),FREE_MEMORY(hNotification));

	nRet  = notification_set_text(hNotification, NOTIFICATION_TEXT_TYPE_TEXT_INPUT_BUTTON, "I'm Title", "TITLE", NOTIFICATION_VARIABLE_TYPE_NONE);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_set_text", NotificationGetError(nRet),FREE_MEMORY(hNotification));

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", Application_AppControlGetError(nRet));
	if(NULL == hAppControl)
	{
		FPRINTF("[Line : %d][%s]app_control_create returned NULL handle value\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(hNotification);
		return 1;
	}

	nRet = app_control_set_app_id(hAppControl, pSetAppID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", Application_AppControlGetError(nRet), FREE_MEMORY(hNotification);app_control_destroy(hAppControl));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", Application_AppControlGetError(nRet), FREE_MEMORY(hNotification);app_control_destroy(hAppControl););

	nRet = notification_set_event_handler(hNotification, NOTIFICATION_EVENT_TYPE_CLICK_ON_TEXT_INPUT_BUTTON, hAppControl);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_set_event_handler", NotificationGetError(nRet), FreeAndDeleteNotificationResourceHandle();FREE_MEMORY(hNotification);app_control_destroy(hAppControl););

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", Application_AppControlGetError(nRet),FREE_MEMORY(hNotification));

	nRet  = notification_post(hNotification);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "notification_post", Application_AppControlGetError(nRet));
	FREE_MEMORY(hNotification);

	return 0;
}

//& type : auto
//& purpose: Set/Get image height for extended notification
/**
* @testcase	 			ITc_notification_set_get_extension_imgae_size_p
* @since_tizen 				4.0
* @author            			SRID(maneesha.k)
* @reviewer         			SRID(shobhit.v)
* @type 				auto
* @description				Set/Get the extension image size
* @scenario				Creates notification\n
*						Set size\n
*						Get size\n
*						Validate the get size
* @apicovered				notification_set_extension_image_size, notification_get_extension_image_size
* @passcase				notification_set_extensions_image_size and notification_get_extension_image_size are successful and return correct value
* @failcase				notification_set_extension_image_size or notification_get_extension_image_size gets failed or return incorrect value
* @precondition				NA
* @postcondition			NA
*/
int ITc_notification_set_get_extension_image_size_p(void)
{
	START_TEST;

	if ( false == CreateNotification(NOTIFICATION_TYPE_NOTI) )
	{
		return 1;
	}

	notification_error_e eRetNotiErr;
	int nSetExtImage = 20, nGetExtImage;

	
	eRetNotiErr  = notification_set_extension_image_size(g_NotificationHandle,
						nSetExtImage);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_set_extension_image_size", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););


	eRetNotiErr  = notification_get_extension_image_size(g_NotificationHandle,
						&nGetExtImage);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, eRetNotiErr, "notification_get_extension_image_size", NotificationGetError(eRetNotiErr), FreeAndDeleteNotificationResourceHandle(););


	if ( nSetExtImage != nGetExtImage )
	{
		FPRINTF("[Line : %d][%s] Mismatch happened, set value = %d, get value = %d\\n", __LINE__, API_NAMESPACE, nSetExtImage, nGetExtImage);
		FreeAndDeleteNotificationResourceHandle();
		return 1;
	}
	FreeAndDeleteNotificationResourceHandle();
	return 0;
}

/** @} */ //end of itc-notification
/** @} */ //end of itc-notification-testcases
