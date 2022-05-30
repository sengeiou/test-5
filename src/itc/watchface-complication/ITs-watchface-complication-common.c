//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
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
#include "ITs-watchface-complication-common.h"

/** @addtogroup itc-watchface-complication
*  @ingroup itc
*  @{
*/

/**
* @function 		WatchfaceComplicationGetError
* @description	 	Maps error enums to string values for watchface
* @parameter		nRet : error code returned
* @return 			error string
*/
char* WatchfaceComplicationGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch( nRet )
	{

		case WATCHFACE_COMPLICATION_ERROR_NONE:				szErrorVal = "TIZEN_ERROR_NONE";			break;
		case WATCHFACE_COMPLICATION_ERROR_OUT_OF_MEMORY:		szErrorVal = "TIZEN_ERROR_OUT_OF_MEMORY";		break;
		case WATCHFACE_COMPLICATION_ERROR_INVALID_PARAMETER:		szErrorVal = "TIZEN_ERROR_INVALID_PARAMETER";		break;
		case WATCHFACE_COMPLICATION_ERROR_IO_ERROR:			szErrorVal = "TIZEN_ERROR_IO_ERROR";			break;
		case WATCHFACE_COMPLICATION_ERROR_NO_DATA:			szErrorVal = "TIZEN_ERROR_NO_DATA";			break;
		case WATCHFACE_COMPLICATION_ERROR_PERMISSION_DENIED:		szErrorVal = "TIZEN_ERROR_PERMISSION_DENIED";		break;
		case WATCHFACE_COMPLICATION_ERROR_NOT_SUPPORTED:		szErrorVal = "TIZEN_ERROR_NOT_SUPPORTED";		break;
		case WATCHFACE_COMPLICATION_ERROR_DB:				szErrorVal = "TIZEN_ERROR_COMPLICATION | 0x1";		break;
		case WATCHFACE_COMPLICATION_ERROR_DBUS:				szErrorVal = "TIZEN_ERROR_COMPLICATION | 0x2";		break;
                case WATCHFACE_COMPLICATION_ERROR_EDIT_NOT_READY:		szErrorVal = "TIZEN_ERROR_COMPLICATION | 0x3";		break;
		case WATCHFACE_COMPLICATION_ERROR_EXIST_ID:			szErrorVal = "TIZEN_ERROR_COMPLICATION | 0x4";		break;
		case WATCHFACE_COMPLICATION_ERROR_NOT_EXIST:			szErrorVal = "TIZEN_ERROR_COMPLICATION | 0x5";		break;
 		case WATCHFACE_COMPLICATION_ERROR_PROVIDER_NOT_AVAILABLE:	szErrorVal = "TIZEN_ERROR_COMPLICATION";		break;
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
	case APP_CONTROL_ERROR_NONE:				szErrorVal = "APP_CONTROL_ERROR_NONE";break;
	case APP_CONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_CONTROL_ERROR_INVALID_PARAMETER";break;
	case APP_CONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_CONTROL_ERROR_OUT_OF_MEMORY";break;
	case APP_CONTROL_ERROR_APP_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_APP_NOT_FOUND";break;
	case APP_CONTROL_ERROR_KEY_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_KEY_NOT_FOUND";break;
	case APP_CONTROL_ERROR_KEY_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_KEY_REJECTED";break;
	case APP_CONTROL_ERROR_INVALID_DATA_TYPE:		szErrorVal = "APP_CONTROL_ERROR_INVALID_DATA_TYPE";break;
	case APP_CONTROL_ERROR_LAUNCH_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_REJECTED";break;
	case APP_CONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_CONTROL_ERROR_PERMISSION_DENIED";break;
	case APP_CONTROL_ERROR_LAUNCH_FAILED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_FAILED";break;
	case APP_CONTROL_ERROR_TIMED_OUT:			szErrorVal = "APP_CONTROL_ERROR_TIMED_OUT";break;
	default:						szErrorVal = "Undefined Error";break;
	}
	return szErrorVal;
}

/**
* @function 		BundleGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* BundleGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case BUNDLE_ERROR_NONE:					szErrorVal = "BUNDLE_ERROR_NONE";				break;
	case BUNDLE_ERROR_OUT_OF_MEMORY:			szErrorVal = "BUNDLE_ERROR_OUT_OF_MEMORY";			break;
	case BUNDLE_ERROR_INVALID_PARAMETER:			szErrorVal = "BUNDLE_ERROR_INVALID_PARAMETER";			break;
	case BUNDLE_ERROR_KEY_NOT_AVAILABLE:			szErrorVal = "BUNDLE_ERROR_KEY_NOT_AVAILABLE";			break;
	case BUNDLE_ERROR_KEY_EXISTS:				szErrorVal = "BUNDLE_ERROR_KEY_EXISTS";				break;
	default:						szErrorVal = "Unknown Error";					break;
	}
	return szErrorVal;
}

/**
 * @function 		TimeoutFunction
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
gboolean TimeoutFunction(gpointer data)
{
	g_nTimeoutId = 0;
	QuitGmainLoop();
	return G_SOURCE_REMOVE;
}

/**
* @function 		IterateGmainLoop
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void IterateGmainLoop(void)
{
	if(g_bCallBackHit != true)
	{
		g_pMainLoop = g_main_loop_new(NULL, false);
		g_nTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_pMainLoop);
		g_main_loop_run(g_pMainLoop);
		g_source_remove(g_nTimeoutId);
		g_nTimeoutId = 0;
		g_pMainLoop = NULL;
	}
}

void QuitGmainLoop(void)
{
	if(g_nTimeoutId)
	{
		g_source_remove(g_nTimeoutId);
		g_nTimeoutId = 0;
	}

	if(g_pMainLoop)
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}
