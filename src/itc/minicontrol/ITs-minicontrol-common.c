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
#include "ITs-minicontrol-common.h"

/** @addtogroup itc-minicontrol
*  @ingroup minicontrol
*  @{
*/
//Add helper function definitions here

/**
* @function 		MinicontrolGetError
* @description	 	Maps minicontrol_error_e enums to string values
* @parameter		nRet : error code returned
* @return 			minicontrol error string
*/
char* MinicontrolGetError(minicontrol_error_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case MINICONTROL_ERROR_NONE:					szErrorVal = "MINICONTROL_ERROR_NONE";					break;
	case MINICONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "MINICONTROL_ERROR_INVALID_PARAMETER";		break;
	case MINICONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "MINICONTROL_ERROR_OUT_OF_MEMORY";			break;
	case MINICONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "MINICONTROL_ERROR_PERMISSION_DENIED";		break;
	case MINICONTROL_ERROR_IPC_FAILURE:				szErrorVal = "MINICONTROL_ERROR_IPC_FAILURE";			break;
	case MINICONTROL_ERROR_NOT_SUPPORTED: 			szErrorVal = "MINICONTROL_ERROR_NOT_SUPPORTED"; 			break;
	case MINICONTROL_ERROR_ELM_FAILURE: 			szErrorVal = "MINICONTROL_ERROR_ELM_FAILURE" ;			break;
	case MINICONTROL_ERROR_UNKNOWN:					szErrorVal = "MINICONTROL_ERROR_UNKNOWN"; 				break;
	default:										szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

/**
* @function 		MinicontrolGetEvent
* @description	 	Maps minicontrol_event_e enums to string values
* @parameter		nType : minicontrol event enum
* @return 			minicontrol type string
*/
char* MinicontrolGetEvent(minicontrol_event_e nType)
{
	char *szType = "Unknown Minicontrol Event";
	switch ( nType )
	{
	case MINICONTROL_EVENT_START:			szType = "MINICONTROL_EVENT_START";				break;
	case MINICONTROL_EVENT_STOP:			szType = "MINICONTROL_EVENT_STOP";				break;
	case MINICONTROL_EVENT_RESIZE:			szType = "MINICONTROL_EVENT_RESIZE";			break;
	case MINICONTROL_EVENT_REQUEST_HIDE:	szType = "MINICONTROL_EVENT_REQUEST_HIDE";		break;
	case MINICONTROL_EVENT_REQUEST_ANGLE:	szType = "MINICONTROL_EVENT_REQUEST_ANGLE";		break;
	case MINICONTROL_EVENT_REPORT_ANGLE:	szType = "MINICONTROL_EVENT_REPORT_ANGLE";		break;
	}

	return szType;
}

/**
* @function 		MinicontrolGetProviderEvent
* @description	 	Maps minicontrol_provider_event_e enums to string values
* @parameter		nType : minicontrol provider event type enum
* @return 			minicontrol type string
*/
char* MinicontrolGetProviderEvent(minicontrol_provider_event_e nType)
{
	char *szType = "Unknown Minicontrol Provider Event";
	switch ( nType )
	{
	case MINICONTROL_PROVIDER_EVENT_REQUEST_HIDE:			szType = "MINICONTROL_PROVIDER_EVENT_REQUEST_HIDE";			break;
	case MINICONTROL_PROVIDER_EVENT_REQUEST_ANGLE:			szType = "MINICONTROL_PROVIDER_EVENT_REQUEST_ANGLE";		break;
	}

	return szType;
}

/**
* @function 		MinicontrolGetViewerEvent
* @description	 	Maps minicontrol_viewer_event_e enums to string values
* @parameter		nType : minicontrol viewer event type enum
* @return 			minicontrol type string
*/
char* MinicontrolGetViewerEvent(minicontrol_viewer_event_e nType)
{
	char *szType = "Unknown Minicontrol Provider Event";
	switch ( nType )
	{
	case MINICONTROL_VIEWER_EVENT_REPORT_ANGLE:			szType = "MINICONTROL_VIEWER_EVENT_REPORT_ANGLE";				break;
	case MINICONTROL_VIEWER_EVENT_SHOW:			szType = "MINICONTROL_VIEWER_EVENT_SHOW";				break;
	case MINICONTROL_VIEWER_EVENT_HIDE:			szType = "MINICONTROL_VIEWER_EVENT_HIDE";				break;
	}

	return szType;
}
/**
* @function 		MinicontrolGetProviderEvent
* @description	 	Maps minicontrol_target_viewer_e enums to string values
* @parameter		nType : minicontrol provider event type enum
* @return 			minicontrol type string
*/
char* MinicontrolGetTargetViewer(minicontrol_target_viewer_e nType)
{
	char *szType = "Unknown Minicontrol Provider Event";
	switch ( nType )
	{
	case MINICONTROL_TARGET_VIEWER_QUICK_PANEL:				szType = "MINICONTROL_TARGET_VIEWER_QUICK_PANEL";			break;
	case MINICONTROL_TARGET_VIEWER_STOCK_LOCK_SCREEN:		szType = "MINICONTROL_TARGET_VIEWER_STOCK_LOCK_SCREEN";		break;
	case MINICONTROL_TARGET_VIEWER_CUSTOM_LOCK_SCREEN:		szType = "MINICONTROL_TARGET_VIEWER_CUSTOM_LOCK_SCREEN";	break;
	}

	return szType;
}

/**
* @function 		MinicontrolCallBackTimeout
* @description	 	callback function to terminate g_main loop
* @parameter		data : user data sent to callback
* @return 			NA
*/
gboolean MinicontrolCallBackTimeout(gpointer data)
{
	GMainLoop* pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	return false;
}

/** @} */
