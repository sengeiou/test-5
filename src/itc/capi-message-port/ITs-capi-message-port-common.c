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
#include "ITs-capi-message-port-common.h"

extern app_control_h g_app_control_handler;

/** @addtogroup itc-message-port
* @ingroup		itc
* @{
*/

/**
* @function 		MessagePortGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MessagePortGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case MESSAGE_PORT_ERROR_IO_ERROR:				szErrorVal = "MESSAGE_PORT_ERROR_IO_ERROR";					break;
	case MESSAGE_PORT_ERROR_OUT_OF_MEMORY:			szErrorVal = "MESSAGE_PORT_ERROR_OUT_OF_MEMORY";			break;
	case MESSAGE_PORT_ERROR_INVALID_PARAMETER:		szErrorVal = "MESSAGE_PORT_ERROR_INVALID_PARAMETER";		break;
	case MESSAGE_PORT_ERROR_PORT_NOT_FOUND:			szErrorVal = "MESSAGE_PORT_ERROR_PORT_NOT_FOUND";			break;
	case MESSAGE_PORT_ERROR_CERTIFICATE_NOT_MATCH:	szErrorVal = "MESSAGE_PORT_ERROR_CERTIFICATE_NOT_MATCH";	break;
	case MESSAGE_PORT_ERROR_MAX_EXCEEDED:			szErrorVal = "MESSAGE_PORT_ERROR_MAX_EXCEEDED";				break;
	case MESSAGE_PORT_ERROR_RESOURCE_UNAVAILABLE:	szErrorVal = "MESSAGE_PORT_ERROR_RESOURCE_UNAVAILABLE";		break;
	default:										szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function 		AppControlGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppControlGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case APP_CONTROL_ERROR_NONE:					szErrorVal = "APP_CONTROL_ERROR_NONE";						break;
	case APP_CONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_CONTROL_ERROR_INVALID_PARAMETER";			break;
	case APP_CONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_CONTROL_ERROR_OUT_OF_MEMORY";				break;
	case APP_CONTROL_ERROR_APP_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_APP_NOT_FOUND";				break;
	case APP_CONTROL_ERROR_KEY_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_KEY_NOT_FOUND";				break;
	case APP_CONTROL_ERROR_KEY_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_KEY_REJECTED";				break;
	case APP_CONTROL_ERROR_INVALID_DATA_TYPE:		szErrorVal = "APP_CONTROL_ERROR_INVALID_DATA_TYPE";			break;
	case APP_CONTROL_ERROR_LAUNCH_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_REJECTED";			break;
	case APP_CONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_CONTROL_ERROR_PERMISSION_DENIED";			break;
	case APP_CONTROL_ERROR_LAUNCH_FAILED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_FAILED";				break;
	case APP_CONTROL_ERROR_TIMED_OUT:				szErrorVal = "APP_CONTROL_ERROR_TIMED_OUT";					break;
	default:										szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function            reply_cb
* @description         Callback function for quit wait_for_async
* @parameter
* @return              FALSE
*/
void reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data)
{
       g_main_loop_quit(g_pMessagePortMainLoop);
}

/**
* @function            timeout_func
* @description         Callback function called after timeout
* @parameter
* @return              FALSE
*/
static gboolean timeout_func(gpointer data)
{
    FPRINTF("[Line : %d][%s] g_main_loop timeout \\n", __LINE__, API_NAMESPACE);
    g_main_loop_quit((GMainLoop *) data);
    return G_SOURCE_REMOVE;
}

/**
* @function 		LaunchAppToSendMsg
* @description	 	launches application needed for send message
* @parameter		NA
* @return 		true : if app is launched successfully, false : if app is not launched
*/
bool LaunchAppToSendMsg(const char *pszRemoteAppId)
{
	bool bIsRunning = false;
	int nCounter = COUNTER;
	
	int nRet = app_control_create(&g_app_control_handler);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_create fail error returned : %s \\n", __LINE__, API_NAMESPACE , AppControlGetError(nRet));
		return false;
	}
		
	if ( g_app_control_handler == NULL )
	{
		FPRINTF("[Line : %d][%s] app_control_create fail created handle value null \\n", __LINE__, API_NAMESPACE);
		app_control_destroy(g_app_control_handler);
		return false;
	}
	
	nRet = app_control_set_app_id(g_app_control_handler , pszRemoteAppId);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_set_app_id fail error returned : %s \\n", __LINE__, API_NAMESPACE , AppControlGetError(nRet));
		app_control_destroy(g_app_control_handler);
		return false;
	}
	
	int messageport_timeout_id = 0;
	nRet = app_control_send_launch_request(g_app_control_handler, reply_cb, NULL);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_send_launch_request fail error returned : %s \\n", __LINE__, API_NAMESPACE , AppControlGetError(nRet));
		app_control_destroy(g_app_control_handler);
		return false;
	}
	RUN_POLLING_LOOP;
	app_manager_is_running(pszRemoteAppId, &bIsRunning);
	
	if ( !bIsRunning )
	{
		FPRINTF("[Line : %d][%s] app_control_send_launch_request failed \\n", __LINE__, API_NAMESPACE);
		app_control_destroy(g_app_control_handler);
		return false;
	}
	return true;
}

/**
* @function 		TerminateSendToApp
* @description	 	terminates application launched for sending message
* @parameter		NA
* @return 			NA
*/
void TerminateSendToApp()
{
	app_control_send_terminate_request(g_app_control_handler);
	app_control_destroy(g_app_control_handler);	
}
/** @} */ //end of itc-message-port
