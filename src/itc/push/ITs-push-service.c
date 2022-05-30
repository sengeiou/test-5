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
#include "ITs-push-common.h"

/** @addtogroup itc-push
*  @ingroup itc
*  @{
*/

//& set: Push
push_service_connection_h g_hServiceConnection = NULL;
bool g_bGetNotificationCallback = false;
bool g_bFeatureMismatch = false;
bool g_bFeatureNotSupported = false;

//Callbacks

/**
* @function 		PushServiceResultCB
* @description	 	Called with the result of a registration/deregistration.
* @parameter		push_service_result_e res, const char *msg, void *data
* @return 			NA
*/
static void PushServiceResultCB(push_service_result_e res, const char *msg, void *data)
{
	g_bCallbackReturnValue = false;
	g_bCallbackHit = true;

	switch ( res )
	{
	case PUSH_SERVICE_RESULT_SUCCESS  :
		FPRINTF("[Line : %d][%s] Service Result: PUSH_SERVICE_RESULT_SUCCESS\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PUSH_SERVICE_RESULT_TIMEOUT   :
		FPRINTF("[Line : %d][%s] Service Result: PUSH_SERVICE_RESULT_TIMEOUT\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_RESULT_SERVER_ERROR  :
		FPRINTF("[Line : %d][%s] Service Result: PUSH_SERVICE_RESULT_SERVER_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_RESULT_SYSTEM_ERROR  :
		FPRINTF("[Line : %d][%s] Service Result: PUSH_SERVICE_RESULT_SYSTEM_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	}
	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
		g_pPushMainLoop = NULL;
	}

	return;
}

/**
* @function 		PushServiceResultNewCB
* @description	 	Called with the result of a registration/deregistration.
* @parameter		push_service_result_e res, const char *msg, void *data
* @return 			NA
*/
static void PushServiceResultNewCB(push_service_result_e res, const char *msg, void *data)
{
	g_bCallbackReturnValue = false;
	g_bCallbackHit = true;

	switch ( res )
	{
	case PUSH_SERVICE_RESULT_SUCCESS  :
		FPRINTF("[Line : %d][%s] Service Result: PUSH_SERVICE_RESULT_SUCCESS\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case PUSH_SERVICE_RESULT_TIMEOUT   :
		FPRINTF("[Line : %d][%s] Service Result: PUSH_SERVICE_RESULT_TIMEOUT\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_RESULT_SERVER_ERROR  :
		FPRINTF("[Line : %d][%s] Service Result: PUSH_SERVICE_RESULT_SERVER_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_RESULT_SYSTEM_ERROR  :
		FPRINTF("[Line : %d][%s] Service Result: PUSH_SERVICE_RESULT_SYSTEM_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	}
	return;
}

/**
* @function 		PushServiceNotifyCB
* @description	 	Called to handle a notification.
* @parameter		const push_service_notification_h noti, void *data
* @return 			NA
*/
static void PushServiceNotifyCB(const push_service_notification_h noti, void *data)
{
	g_bNotifyCallbackHit = true;
	return;
}

/**
* @function 		ConnectDisconnectPushServiceStateCB
* @description	 	Called when the registration state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void ConnectDisconnectPushServiceStateCB(push_service_state_e st, const char *err, void *data)
{
	g_bStateCallbackHit = true;
	if ( st == PUSH_SERVICE_STATE_REGISTERED )
	{
		g_bRegisteredState = true;
	}

	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
		g_pPushMainLoop = NULL;
	}

	return;
}

/**
* @function 		GetNotificationDataPushServiceStateCB
* @description	 	Called when the registration state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void GetNotificationDataPushServiceStateCB(push_service_state_e st, const char *err, void *data)
{
	push_service_notification_h pstNotification = NULL;
	char *pszData = NULL;
	int nRet = -1;

	g_bStateCallbackHit = true;
	switch ( st )
	{
	case PUSH_SERVICE_STATE_UNREGISTERED :
		{
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_UNREGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_register(g_hServiceConnection, PushServiceResultNewCB, NULL);
			if ( nRet != PUSH_SERVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE,PushServiceGetError(nRet),g_bCallbackHit);
				break;
			}
			return;
		}
	case PUSH_SERVICE_STATE_REGISTERED :
		{
			g_bRegisteredState = true;
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_REGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_get_unread_notification(g_hServiceConnection, &pstNotification);
			PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_unread_notification", PushServiceGetError(nRet));

			if ( pstNotification != NULL )
			{
				// Target API
				nRet = push_service_get_notification_data(pstNotification, &pszData);
				PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_notification_data", PushServiceGetError(nRet));
				if (pszData == NULL)
				{
					FPRINTF("[Line : %d][%s] push_service_get_notification_data, error returned = data is NULL\\n", __LINE__, API_NAMESPACE);
				}
				FREE_MEMORY(pszData);
				push_service_free_notification(pstNotification);
				g_bGetNotificationCallback = true;
			}
		}
		break;
	case PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_PING_CHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PING_CHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_ERROR  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_ERROR\\n", __LINE__, API_NAMESPACE);
		break;

	}

	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
		g_pPushMainLoop = NULL;
	}

	return;
}

/**
* @function 		GetNotificationMessagePushServiceStateCB
* @description	 	Called when the registration state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void GetNotificationMessagePushServiceStateCB(push_service_state_e st, const char *err, void *data)
{
	push_service_notification_h pstNotification = NULL;
	char *pszData = NULL;
	int nRet = -1;

	g_bStateCallbackHit = true;
	switch ( st )
	{
	case PUSH_SERVICE_STATE_UNREGISTERED :
		{
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_UNREGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_register(g_hServiceConnection, PushServiceResultNewCB, NULL);
			if ( nRet != PUSH_SERVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE,PushServiceGetError(nRet), g_bCallbackHit);
				break;
			}
			return;
		}
	case PUSH_SERVICE_STATE_REGISTERED :
		{
			g_bRegisteredState = true;
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_REGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_get_unread_notification(g_hServiceConnection, &pstNotification);
			if ( nRet != PUSH_SERVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] push_service_get_unread_notification failed, error returned = %s\\n", __LINE__, API_NAMESPACE,PushServiceGetError(nRet));
			}

			if ( pstNotification != NULL )
			{
				// Target API
				nRet = push_service_get_notification_message(pstNotification, &pszData);
				if ( nRet != PUSH_SERVICE_ERROR_NONE )
				{
					FPRINTF("[Line : %d][%s] push_service_get_notification_message , error returned = %s\\n", __LINE__, API_NAMESPACE, PushServiceGetError(nRet));
				}
				if ( pszData == NULL )
				{
					FPRINTF("[Line : %d][%s] push_service_get_notification_message , error returned = data is NULL\\n", __LINE__, API_NAMESPACE);
				}
				FREE_MEMORY(pszData);
				push_service_free_notification(pstNotification);
				g_bGetNotificationCallback = true;

			}
		}
		break;
	case PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_PING_CHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PING_CHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_ERROR  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	}

	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
	}

	return;
}

/**
* @function 		GetNotificationTimePushServiceStateCB
* @description	 	Called when the registration state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void GetNotificationTimePushServiceStateCB(push_service_state_e st, const char *err, void *data)
{
	push_service_notification_h pstNotification = NULL;
	long long int llnTime = 0;
	int nRet = -1;

	g_bStateCallbackHit = true;
	switch ( st )
	{
	case PUSH_SERVICE_STATE_UNREGISTERED :
		{
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_UNREGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_register(g_hServiceConnection, PushServiceResultNewCB, NULL);
			if ( nRet != PUSH_SERVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE,PushServiceGetError(nRet),g_bCallbackHit);
				break;
			}
			return;
		}
	case PUSH_SERVICE_STATE_REGISTERED :
		{
			g_bRegisteredState = true;
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_REGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_get_unread_notification(g_hServiceConnection, &pstNotification);
			PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_unread_notification", PushServiceGetError(nRet));
			if ( pstNotification != NULL )
			{
				// Target API
				nRet = push_service_get_notification_time(pstNotification, &llnTime);	
				PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_notification_time", PushServiceGetError(nRet));
				if ( llnTime == 0 )
				{
					FPRINTF("[Line : %d][%s] push_service_get_notification_time , error returned = data is NULL\\n", __LINE__, API_NAMESPACE);
				}
				push_service_free_notification(pstNotification);
				g_bGetNotificationCallback = true;
			}
		}
		break;
	case PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_PING_CHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PING_CHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_ERROR  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	}
	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
	}

	return;
}

/**
* @function 		GetNotificationSenderPushServiceStateCB
* @description	 	Called when the registration state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void GetNotificationSenderPushServiceStateCB(push_service_state_e st, const char *err, void *data)
{
	push_service_notification_h pstNotification = NULL;
	char *pszSender = NULL;
	int nRet = -1;

	g_bStateCallbackHit = true;
	switch ( st )
	{
	case PUSH_SERVICE_STATE_UNREGISTERED :
		{
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_UNREGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_register(g_hServiceConnection, PushServiceResultNewCB, NULL);
			if ( nRet != PUSH_SERVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE,PushServiceGetError(nRet),g_bCallbackHit);
				break;
			}
			return;
		}
	case PUSH_SERVICE_STATE_REGISTERED :
		{
			g_bRegisteredState = true;
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_REGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_get_unread_notification(g_hServiceConnection, &pstNotification);
			PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_unread_notification", PushServiceGetError(nRet));
			if ( pstNotification != NULL )
			{
				// Target API
				nRet = push_service_get_notification_sender(pstNotification, &pszSender); 
				PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_unread_notification", PushServiceGetError(nRet));
				if ( pszSender == NULL )
				{
					FPRINTF("[Line : %d][%s] push_service_get_notification_sender, error returned = Sender is NULL\\n", __LINE__, API_NAMESPACE);
				}
				FREE_MEMORY(pszSender);
				push_service_free_notification(pstNotification);
				g_bGetNotificationCallback = true;
			}
		}
		break;
	case PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_PING_CHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PING_CHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_ERROR  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	}

	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
	}

	return;
}

/**
* @function 		GetNotificationSessionInfoPushServiceStateCB
* @description	 	Called when the registration state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void GetNotificationSessionInfoPushServiceStateCB(push_service_state_e st, const char *err, void *data)
{
	push_service_notification_h pstNotification = NULL;
	char *pszSessionInfo = NULL;
	int nRet = -1;

	g_bStateCallbackHit = true;
	switch ( st )
	{
	case PUSH_SERVICE_STATE_UNREGISTERED :
		{
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_UNREGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_register(g_hServiceConnection, PushServiceResultNewCB, NULL);
			if ( nRet != PUSH_SERVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE,PushServiceGetError(nRet),g_bCallbackHit);
				break;
			}
			return;
		}
	case PUSH_SERVICE_STATE_REGISTERED :
		{
			g_bRegisteredState = true;
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_REGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_get_unread_notification(g_hServiceConnection, &pstNotification);
			PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_unread_notification", PushServiceGetError(nRet));
			if ( pstNotification != NULL )
			{
				// Target API
				nRet = push_service_get_notification_session_info(pstNotification, &pszSessionInfo);
				PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_notification_session_info", PushServiceGetError(nRet));
				if ( pszSessionInfo == NULL )
				{
					FPRINTF("[Line : %d][%s] push_service_get_notification_session_info , error returned = Session ID is NULL\\n", __LINE__, API_NAMESPACE);
				}
				FREE_MEMORY(pszSessionInfo);
				push_service_free_notification(pstNotification);
				g_bGetNotificationCallback = true;
			}
		}
		break;
	case PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_PING_CHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PING_CHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_ERROR  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	}

	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
	}

	return;
}

/**
* @function 		GetNotificationRequestIdPushServiceStateCB
* @description	 	Called when the registration state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void GetNotificationRequestIdPushServiceStateCB(push_service_state_e st, const char *err, void *data)
{
	push_service_notification_h pstNotification = NULL;
	char *pszRequestId = NULL;
	int nRet = -1;

	g_bStateCallbackHit = true;
	switch ( st )
	{
	case PUSH_SERVICE_STATE_UNREGISTERED :
		{
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_UNREGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_register(g_hServiceConnection, PushServiceResultNewCB, NULL);
			if ( nRet != PUSH_SERVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE,PushServiceGetError(nRet),g_bCallbackHit);
				break;
			}
			return;
		}
	case PUSH_SERVICE_STATE_REGISTERED :
		{
			g_bRegisteredState = true;
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_REGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_get_unread_notification(g_hServiceConnection, &pstNotification);
			PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_unread_notification", PushServiceGetError(nRet));

			if ( pstNotification != NULL )
			{
				// Target API
				nRet = push_service_get_notification_request_id(pstNotification, &pszRequestId);
				PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_notification_request_id", PushServiceGetError(nRet));
				if (pszRequestId == NULL)
				{
					FPRINTF("[Line : %d][%s] push_service_get_notification_request_id , error returned = Request ID is NULL\\n", __LINE__, API_NAMESPACE);
				}
				FREE_MEMORY(pszRequestId);
				push_service_free_notification(pstNotification);
				g_bGetNotificationCallback = true;
			}
		}
		break;
	case PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_PING_CHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PING_CHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_ERROR  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	}

	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
	}

	return;
}

/**
* @function 		GetNotificationTypePushServiceStateCB
* @description	 	Called when the registration state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void GetNotificationTypePushServiceStateCB(push_service_state_e st, const char *err, void *data)
{
	push_service_notification_h pstNotification = NULL;
	int nType = -1;
	int nRet = -1;

	g_bStateCallbackHit = true;
	switch ( st )
	{
	case PUSH_SERVICE_STATE_UNREGISTERED :
		{
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_UNREGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_register(g_hServiceConnection, PushServiceResultNewCB, NULL);
			if ( nRet != PUSH_SERVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE,PushServiceGetError(nRet),g_bCallbackHit);
				break;
			}
			return;
		}
	case PUSH_SERVICE_STATE_REGISTERED :
		{
			g_bRegisteredState = true;
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_REGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_get_unread_notification(g_hServiceConnection, &pstNotification);
			PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_unread_notification", PushServiceGetError(nRet));
			if ( pstNotification != NULL )
			{
				// Target API
				nRet = push_service_get_notification_type(pstNotification, &nType);
				PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_notification_type", PushServiceGetError(nRet));
				if ( nType < 0 )
				{
					FPRINTF("[Line : %d][%s] push_service_get_notification_type , type returned = %d\\n", __LINE__, API_NAMESPACE, nType);
				}
				push_service_free_notification(pstNotification);
				g_bGetNotificationCallback = true;

			}
		}
		break;
	case PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_PING_CHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PING_CHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_ERROR  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	}

	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
	}

	return;
}

/**
* @function 		GetNotificationRequestUnreadPushServiceStateCB
* @description	 	Called when the registration state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void GetNotificationRequestUnreadPushServiceStateCB(push_service_state_e st, const char *err, void *data)
{
	int nRet = -1;
	g_bStateCallbackHit = true;

	switch ( st )
	{
	case PUSH_SERVICE_STATE_UNREGISTERED :
		{
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_UNREGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_register(g_hServiceConnection, PushServiceResultNewCB, NULL);
			if ( nRet != PUSH_SERVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE,PushServiceGetError(nRet),g_bCallbackHit);
				break;
			}
			return;
		}
	case PUSH_SERVICE_STATE_REGISTERED :
		{
			g_bRegisteredState = true;
			// Target API
			nRet = push_service_request_unread_notification(g_hServiceConnection);
			PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_request_unread_notification", PushServiceGetError(nRet));
			g_bGetNotificationCallback = true;
		}
		break;

	case PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_PING_CHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PING_CHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_ERROR  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	}

	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
	}

	return;
}

/**
* @function 		GetNotificationUnreadFreeNotificationCB
* @description	 	Called when the registration state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void GetNotificationUnreadFreeNotificationCB(push_service_state_e st, const char *err, void *data)
{
	push_service_notification_h pstNotification = NULL;
	g_bStateCallbackHit = true;
	int nRet = -1;

	switch ( st )
	{
	case PUSH_SERVICE_STATE_UNREGISTERED :
		{
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_UNREGISTERED\\n", __LINE__, API_NAMESPACE);
			nRet = push_service_register(g_hServiceConnection, PushServiceResultNewCB, NULL);
			if ( nRet != PUSH_SERVICE_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE,PushServiceGetError(nRet),g_bCallbackHit);
				break;
			}
			return;
		}
	case PUSH_SERVICE_STATE_REGISTERED :
		{
			g_bRegisteredState = true;
			FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_REGISTERED\\n", __LINE__, API_NAMESPACE);
			// Target API
			nRet = push_service_get_unread_notification(g_hServiceConnection, &pstNotification);
			PRINT_RESULT_NORETURN(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_unread_notification", PushServiceGetError(nRet));

			if ( pstNotification != NULL )
			{
				// Target API
				push_service_free_notification(pstNotification);
			}
			g_bGetNotificationCallback = true;
		}
		break;
	case PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PROVISIONING_IPCHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_PING_CHANGE  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_PING_CHANGE\\n", __LINE__, API_NAMESPACE);
		break;
	case PUSH_SERVICE_STATE_ERROR  :
		FPRINTF("[Line : %d][%s] Service State: PUSH_SERVICE_STATE_ERROR\\n", __LINE__, API_NAMESPACE);
		break;
	}

	if ( g_pPushMainLoop )
	{
		g_main_loop_quit(g_pPushMainLoop);
	}

	return;
}

/*********************************************************************/
//Helper Functions

/**
* @function 		PushServiceConnect
* @description	 	Connect to the push service
* @parameter		bIsRegisteration : Registration to be done from callback
* @return 			true : success, false : failure
*/
bool PushServiceConnect(push_service_state_cb pFnCallback)
{
	int nTimeoutId = 0;
	g_bStateCallbackHit = false;
	char appId[CONFIG_VALUE_LEN_MAX] = {0,};

	if ( true == GetValueFromConfigFile("PUSH_APPID", appId, API_NAMESPACE) )
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, appId);
#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = push_service_connect(appId, pFnCallback, PushServiceNotifyCB, NULL, &g_hServiceConnection);
	FPRINTF("[Line : %d][%s] connect was called\\n", __LINE__, API_NAMESPACE);
	if ( !g_bIsPushFeatureSupported )
	{
		if ( nRet != PUSH_SERVICE_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("\\n [Line : %d][%s]  push_service_connect returned %s error for unsupported feature", __LINE__, API_NAMESPACE, PushServiceGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("\\n [Line : %d][%s]  push_service_connect API call correctly returned %s error for unsupported feature", __LINE__, API_NAMESPACE, PushServiceGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return false;
	}
	
	if ( nRet != PUSH_SERVICE_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] push_service_connect failed in precondition, error returned = %s\\n", __LINE__, API_NAMESPACE, PushServiceGetError(nRet));
		return false;
	}
	RUN_POLLING_LOOP;

	if ( !g_bStateCallbackHit )
	{
		FPRINTF("[Line : %d][%s] push_service_connect failed in precondition, error returned = Callback not invoked\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	return true;
}

/**
* @function 		PushServiceDisconnect
* @description	 	Closes the connection and releases resources
* @parameter		NA
* @return 			NA
*/
void PushServiceDisconnect()
{
	push_service_disconnect(g_hServiceConnection);
}

/**
* @function 		PushServiceConnectSendDisconnect
* @description	 	connects, send notification, disconnects
* @parameter		NA
* @return 			NA
*/
bool PushServiceConnectSendDisconnect()
{
	char* pszRegId = NULL;
	int nTimeoutId = 0;
	int nRet = -1;
	char appId[CONFIG_VALUE_LEN_MAX] = {0,};
	char appSecret[CONFIG_VALUE_LEN_MAX] = {0,};

	if ( true == GetValueFromConfigFile("PUSH_APPID", appId, API_NAMESPACE) )
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, appId);
#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( true == GetValueFromConfigFile("PUSH_APPSECRET", appSecret, API_NAMESPACE) )
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, appSecret);
#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( !PushServiceConnect(ConnectDisconnectPushServiceStateCB) )
	{
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	if ( !g_bRegisteredState )
	{
		FPRINTF("[Line : %d][%s] App not registered. Trying to register\\n", __LINE__, API_NAMESPACE);
		nRet = push_service_register(g_hServiceConnection, PushServiceResultCB, NULL);
		RUN_POLLING_LOOP;
		if ( nRet != PUSH_SERVICE_ERROR_NONE || g_bCallbackHit == false )
		{
			FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE, PushServiceGetError(nRet), g_bCallbackHit);
			PushServiceDisconnect();
			return false;
		}
		if ( !g_bCallbackReturnValue )
		{
			FPRINTF("[Line : %d][%s] push_service_register failed, error returned = Register state not achieved\\n", __LINE__, API_NAMESPACE);
			PushServiceDisconnect();
			return false;
		}
	}

	nRet = push_service_get_registration_id(g_hServiceConnection,&pszRegId);
	if ( nRet != PUSH_SERVICE_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] push_service_get_registration_id failed , error returned = %s\\n", __LINE__, API_NAMESPACE, PushServiceGetError(nRet));
		PushServiceDisconnect();
		return false;
	}
	if ( pszRegId == NULL )
	{
		FPRINTF("[Line : %d][%s] push_service_get_registration_id returned Registration ID = NULL\\n", __LINE__, API_NAMESPACE);
		PushServiceDisconnect();
		return false;
	}

	PushServiceDisconnect();
	sleep(5);

	nRet = SendPushDataToServer(appId , appSecret, pszRegId, "000101", "App_Data_to_send", 16, "Alert-Message-to-Quick-Panel", PUSH_ACTION_ALERT, PUSH_BADGE_OPTION_INCREASE, 1, 1L, 0, 0, appId, true);
	sleep(5);

	return true;
}

/**
* @testcase 			ITs_push_service_startup
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Called before each test, creates connection to push service
* @apicovered			NA
* @passcase				NA
* @failcase				NA
* @precondition			NA
* @postcondition		NA
*/
void ITs_push_service_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	
	g_bIsPushFeatureSupported = TCTCheckSystemInfoFeatureSupported(PUSH_FEATURE, API_NAMESPACE);
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;
	
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Push_Service_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @testcase 			ITs_push_service_cleanup
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Called after each test, Closes the connection and releases all its resources
* @apicovered			NA
* @passcase				NA
* @failcase				NA
* @precondition			NA
* @postcondition		NA
*/
void ITs_push_service_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Push_Service_p\\n", __LINE__, API_NAMESPACE);
#endif
	sleep(SLEEP_TIME);
	return;
}


/** @addtogroup itc-push-testcases
*  @brief 		Integration testcases for module push
*  @ingroup 	itc-push
*  @{
*/

//& purpose: Connects/Disconnects to the push service.
//& type: auto

/**
* @testcase 			ITc_push_service_connect_disconnect_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Connects/Disconnects to the push service
* @apicovered			push_service_connect() , push_service_disconnect()
* @passcase				If push_service_connect and push_service_disconnect returns success and callbacks are invoked
* @failcase				If push_service_connect and push_service_disconnect fails to complete the scenario cycle in <@pass-case>
* @precondition			There is no connection for the app_id to the push service.
* @postcondition		The state callback will be called
*/
int ITc_push_service_connect_disconnect_p(void)
{
	START_TEST;	
	int nTimeoutId = 0;
	g_bStateCallbackHit = false;
	char appId[CONFIG_VALUE_LEN_MAX] = {0,};

	if ( true == GetValueFromConfigFile("PUSH_APPID", appId, API_NAMESPACE) )
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, appId);
#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Target API
	int nRet = push_service_connect(appId, ConnectDisconnectPushServiceStateCB, PushServiceNotifyCB, NULL, &g_hServiceConnection);
	if ( !g_bIsPushFeatureSupported )
	{
		if ( nRet != PUSH_SERVICE_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("\\n [Line : %d][%s]  push_service_connect returned %s error for unsupported feature", __LINE__, API_NAMESPACE, PushServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("\\n [Line : %d][%s]  push_service_connect API call correctly returned %s error for unsupported feature", __LINE__, API_NAMESPACE, PushServiceGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_connect", PushServiceGetError(nRet));
	RUN_POLLING_LOOP;

	if ( !g_bStateCallbackHit )
	{
		FPRINTF("[Line : %d][%s] push_service_connect failed , error returned = Callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	// Target API
	push_service_disconnect(g_hServiceConnection);

	return 0;
}

//& purpose: Registers/Deregisters an application to the push server.
//& type: auto


/**
* @testcase 			ITc_push_service_register_deregister_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Registers/Deregisters an application to the push server
* @apicovered			push_service_register() , push_service_deregister()
* @passcase				If push_service_connect, push_service_disconnect, push_service_register and push_service_deregister returns success and callbacks are invoked
* @failcase				If any API fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		NA
*/

int ITc_push_service_register_deregister_p(void)
{
	START_TEST;	
	int nTimeoutId = 0;
	g_bRegisteredState = false;
	int nRet = -1;

	if ( !PushServiceConnect(ConnectDisconnectPushServiceStateCB) )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( g_bRegisteredState )
	{
		nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		PRINT_RESULT_CLEANUP(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet),PushServiceDisconnect());
		RUN_POLLING_LOOP;
		if ( !g_bCallbackHit )
		{
			FPRINTF("[Line : %d][%s] push_service_deregister failed, error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
			PushServiceDisconnect();
			return 1;
		}
		if ( !g_bCallbackReturnValue )
		{
			FPRINTF("[Line : %d][%s] push_service_deregister failed, error returned = callback returned error\\n", __LINE__, API_NAMESPACE);
			PushServiceDisconnect();
			return 1;
		}
	}

	g_bCallbackHit = false;
	g_bCallbackReturnValue = false;

	// Target API
	nRet = push_service_register(g_hServiceConnection, PushServiceResultCB, NULL);
	PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_register", PushServiceGetError(nRet));
	RUN_POLLING_LOOP;

	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] push_service_register failed , error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( !g_bCallbackReturnValue )
	{
		FPRINTF("[Line : %d][%s] push_service_register failed , error returned = registration state not achieved\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bCallbackHit = false;
	g_bCallbackReturnValue = false;
	// Target API
	nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
	PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	RUN_POLLING_LOOP; //check this
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] push_service_deregister failed , error returned = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( !g_bCallbackReturnValue )
	{
		FPRINTF("[Line : %d][%s] push_service_deregister failed , error returned = callback returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	PushServiceDisconnect();

	return 0;
}

//& purpose: Gets the registration ID in PUSH_STATE_REGISTERED state.
//& type: auto

/**
* @testcase 			ITc_push_service_get_registration_id_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Gets the registration ID in PUSH_STATE_REGISTERED state.
* @apicovered			push_service_get_registration_id
* @passcase				If push_service_get_registration_id returns success and all pre-conditions pass
* @failcase				If any API fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		NA
*/
int ITc_push_service_get_registration_id_p(void)
{
	START_TEST;	
	g_bRegisteredState = false;
	int nTimeoutId = 0;
	int nRet = -1;
	g_bCallbackReturnValue = false;
	if ( !PushServiceConnect(ConnectDisconnectPushServiceStateCB) )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if ( !g_bRegisteredState )
	{
		nRet = push_service_register(g_hServiceConnection, PushServiceResultCB, NULL);
		RUN_POLLING_LOOP;
		if ( nRet != PUSH_SERVICE_ERROR_NONE || g_bCallbackHit == false )
		{
			FPRINTF("[Line : %d][%s] push_service_register failed, error returned = %s, g_bCallbackHit = %d\\n", __LINE__, API_NAMESPACE, PushServiceGetError(nRet), g_bCallbackHit);
			PushServiceDisconnect();
			return 1;
		}
		if ( !g_bCallbackReturnValue )
		{
			FPRINTF("[Line : %d][%s] push_service_register failed, error returned = Register state not achieved\\n", __LINE__, API_NAMESPACE);
			PushServiceDisconnect();
			return 1;
		}
	}

	char* pszRegId = NULL;
	nRet = -1;
	// Target API
	nRet = push_service_get_registration_id(g_hServiceConnection,&pszRegId);
	PRINT_RESULT_CLEANUP(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_get_registration_id", PushServiceGetError(nRet),push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);FREE_MEMORY(pszRegId));

	if ( pszRegId == NULL )
	{
		FPRINTF("[Line : %d][%s] push_service_get_registration_id returned Registration ID = NULL\\n", __LINE__, API_NAMESPACE);
		push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		return 1;
	}
	FREE_MEMORY(pszRegId);

	nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
	PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	PushServiceDisconnect();

	return 0;
}

//& purpose: Gets notification data sent by the server.
//& type: auto

/**
* @testcase 			ITc_push_service_get_notification_data_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Gets notification data sent by the server.
* @apicovered			PushServiceConnectSendDisconnect, PushServiceConnect, push_service_deregister,PushServiceDisconnect
* @passcase				If it returns 0
* @failcase				If api fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		The data must be released using free().
*/
int ITc_push_service_get_notification_data_p(void)
{
	START_TEST;
	g_bRegisteredState = false;
	g_bGetNotificationCallback = false;

	bool bResult = PushServiceConnectSendDisconnect();
	if ( bResult == false )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnectSendDisconnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bRegisteredState = false;
	bResult = PushServiceConnect(GetNotificationDataPushServiceStateCB);
	if ( g_bRegisteredState )
	{
		int nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	}
	PushServiceDisconnect();

	if ( (g_bGetNotificationCallback == true) && (bResult == true) )
	{
		return 0;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
}

//& purpose: Gets the notification message sent by the server.
//& type: auto

/**
* @testcase 			ITc_push_service_get_notification_message_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Gets notification data sent by the server.
* @apicovered			PushServiceConnectSendDisconnect, PushServiceConnect, push_service_deregister,PushServiceDisconnect
* @passcase				If it returns 0
* @failcase				If api fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		The msg must be released using free().
*/
int ITc_push_service_get_notification_message_p(void)
{
	START_TEST;
	g_bRegisteredState = false;
	g_bGetNotificationCallback = false;
	int nRet;

	bool bResult = PushServiceConnectSendDisconnect();
	if ( bResult == false )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnectSendDisconnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bRegisteredState = false;
	bResult = PushServiceConnect(GetNotificationMessagePushServiceStateCB);
	if ( g_bRegisteredState )
	{
		nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	}
	PushServiceDisconnect();

	if ( (g_bGetNotificationCallback == true) && (bResult == true) )
	{
		return 0;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
}

//& purpose: Gets the received time of the notification message.
//& type: auto

/**
* @testcase 			ITc_push_service_get_notification_time_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Gets the received time of the notification message.
* @apicovered			PushServiceConnectSendDisconnect, PushServiceConnect, push_service_deregister,PushServiceDisconnect
* @passcase				If it returns 0
* @failcase				If api fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		NA
*/
int ITc_push_service_get_notification_time_p(void)
{
	START_TEST;
	g_bRegisteredState = false;
	g_bGetNotificationCallback = false;

	bool bResult = PushServiceConnectSendDisconnect();
	if ( bResult == false )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnectSendDisconnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bRegisteredState = false;
	bResult = PushServiceConnect(GetNotificationTimePushServiceStateCB);
	if ( g_bRegisteredState )
	{
		int nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	}
	PushServiceDisconnect();

	if ( (g_bGetNotificationCallback == true) && (bResult == true) )
	{
		return 0;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
}

//& purpose: Gets the sender of the notification.
//& type: auto

/**
* @testcase 			ITc_push_service_get_notification_sender_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Gets the sender of the notification.
* @apicovered			PushServiceConnectSendDisconnect, PushServiceConnect, push_service_deregister,PushServiceDisconnect
* @passcase				If it returns 0
* @failcase				If api fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		NA
*/
int ITc_push_service_get_notification_sender_p(void)
{
	START_TEST;
	g_bRegisteredState = false;
	g_bGetNotificationCallback = false;

	bool bResult = PushServiceConnectSendDisconnect();
	if ( bResult == false )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnectSendDisconnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bRegisteredState = false;
	bResult = PushServiceConnect(GetNotificationSenderPushServiceStateCB);
	if ( g_bRegisteredState )
	{
		int nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	}
	PushServiceDisconnect();

	if ( (g_bGetNotificationCallback == true) && (bResult == true) )
	{
		return 0;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
}

//& purpose: Gets the session ID of the notification.
//& type: auto

/**
* @testcase 			ITc_push_service_get_notification_session_info_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Gets the session ID of the notification.
* @apicovered			PushServiceConnectSendDisconnect, PushServiceConnect, push_service_deregister,PushServiceDisconnect
* @passcase				If it returns 0
* @failcase				If api fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		NA
*/
int ITc_push_service_get_notification_session_info_p(void)
{
	START_TEST;
	g_bRegisteredState = false;
	g_bGetNotificationCallback = false;

	bool bResult = PushServiceConnectSendDisconnect();
	if ( bResult == false )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnectSendDisconnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bRegisteredState = false;
	bResult = PushServiceConnect(GetNotificationSessionInfoPushServiceStateCB);
	if ( g_bRegisteredState )
	{
		int nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	}
	PushServiceDisconnect();

	if ( (g_bGetNotificationCallback == true) && (bResult == true) )
	{
		return 0;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
}

//& purpose: Gets the request ID assigned by the sender.
//& type: auto

/**
* @testcase 			ITc_push_service_get_notification_request_id_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Called when the registration state is refreshed.
* @apicovered			PushServiceConnectSendDisconnect, PushServiceConnect, push_service_deregister,PushServiceDisconnect
* @passcase				If it returns 0
* @failcase				If api fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		The request_id must be released using free().
*/
int ITc_push_service_get_notification_request_id_p(void)
{
	START_TEST;
	g_bRegisteredState = false;
	g_bGetNotificationCallback = false;

	bool bResult = PushServiceConnectSendDisconnect();
	if ( bResult == false )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnectSendDisconnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bRegisteredState = false;
	bResult = PushServiceConnect(GetNotificationRequestIdPushServiceStateCB);
	if ( g_bRegisteredState )
	{
		int nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	}
	PushServiceDisconnect();

	if ( (g_bGetNotificationCallback == true) && (bResult == true) )
	{
		return 0;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
}

//& purpose: Gets the value in the type field of the notification.
//& type: auto

/**
* @testcase 			ITc_push_service_get_notification_type_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Gets the value in the type field of the notification.
* @apicovered			PushServiceConnectSendDisconnect, PushServiceConnect, push_service_deregister,PushServiceDisconnect
* @passcase				If it returns 0
* @failcase				If api fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		NA
*/
int ITc_push_service_get_notification_type_p(void)
{
	START_TEST;
	g_bRegisteredState = false;
	g_bGetNotificationCallback = false;

	bool bResult = PushServiceConnectSendDisconnect();
	if ( bResult == false )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnectSendDisconnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bRegisteredState = false;
	bResult = PushServiceConnect(GetNotificationTypePushServiceStateCB);
	if ( g_bRegisteredState )
	{
		int nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	}
	PushServiceDisconnect();

	if ( (g_bGetNotificationCallback == true) && (bResult == true) )
	{
		return 0;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
}

//& purpose: Requests unread notification messages to the push server.
//& type: auto

/**
* @testcase 			ITc_push_service_request_unread_notification_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Requests unread notification messages to the push server ,check callback.
* @apicovered			PushServiceConnectSendDisconnect, PushServiceConnect, push_service_deregister,PushServiceDisconnect
* @passcase				If it returns 0
* @failcase				If api fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		NA
*/
int ITc_push_service_request_unread_notification_p(void)
{
	START_TEST;
	g_bRegisteredState = false;
	g_bGetNotificationCallback = false;

	bool bResult = PushServiceConnectSendDisconnect();
	if ( bResult == false )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnectSendDisconnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bRegisteredState = false;
	bResult = PushServiceConnect(GetNotificationRequestUnreadPushServiceStateCB);
	if ( g_bRegisteredState )
	{
		int nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	}
	PushServiceDisconnect();

	if ( (g_bGetNotificationCallback == true) && (bResult == true) )
	{
		return 0;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
}

//& purpose: Gets the unread notification
//& type: auto

/**
* @testcase 			ITc_push_service_get_unread_free_notification_p
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @since_tizen 			2.3
* @description			NA
* @scenario				Get unread notification, Free notification
* @apicovered			PushServiceConnectSendDisconnect, PushServiceConnect, push_service_deregister,PushServiceDisconnect
* @passcase				If it returns 0
* @failcase				If api fails to complete the scenario cycle in <@pass-case>
* @precondition			NA
* @postcondition		NA
*/
int ITc_push_service_get_unread_free_notification_p(void)
{
	START_TEST;
	g_bRegisteredState = false;
	g_bGetNotificationCallback = false;

	bool bResult = PushServiceConnectSendDisconnect();
	if ( bResult == false )
	{
		if(true == g_bFeatureMismatch)
		{
			return 1;
		}
		if(true == g_bFeatureNotSupported)
		{
			return 0;
		}
		
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnectSendDisconnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	g_bRegisteredState = false;
	bResult = PushServiceConnect(GetNotificationUnreadFreeNotificationCB);
	if ( g_bRegisteredState )
	{
		int nRet = push_service_deregister(g_hServiceConnection, PushServiceResultCB, NULL);
		PRINT_RESULT(PUSH_SERVICE_ERROR_NONE, nRet, "push_service_deregister", PushServiceGetError(nRet));
	}
	PushServiceDisconnect();

	if ( (g_bGetNotificationCallback == true) && (bResult == true) )
	{
		return 0;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Precondition failed in PushServiceConnect\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
}
/** @} */
/** @} */
