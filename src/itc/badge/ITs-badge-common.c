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
#include "ITs-badge-common.h"

/** @addtogroup itc-badge
*  @ingroup itc
*  @{
*/

/**
* @function 		BadgeGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char *BadgeGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case BADGE_ERROR_INVALID_PARAMETER:		szErrorVal = "BADGE_ERROR_INVALID_PARAMETER";		break;
	case BADGE_ERROR_OUT_OF_MEMORY:			szErrorVal = "BADGE_ERROR_OUT_OF_MEMORY";			break;
	case BADGE_ERROR_IO_ERROR:				szErrorVal = "BADGE_ERROR_IO_ERROR";				break;
	case BADGE_ERROR_FROM_DB:				szErrorVal = "BADGE_ERROR_FROM_DB";					break;
	case BADGE_ERROR_ALREADY_EXIST:			szErrorVal = "BADGE_ERROR_ALREADY_EXIST";			break;
	case BADGE_ERROR_FROM_DBUS:				szErrorVal = "BADGE_ERROR_FROM_DBUS";				break;
	case BADGE_ERROR_NOT_EXIST:				szErrorVal = "BADGE_ERROR_NOT_EXIST";				break;
	case BADGE_ERROR_PERMISSION_DENIED:		szErrorVal = "BADGE_ERROR_PERMISSION_DENIED";		break;
	case BADGE_ERROR_SERVICE_NOT_READY:		szErrorVal = "BADGE_ERROR_SERVICE_NOT_READY";		break;
	case BADGE_ERROR_INVALID_PACKAGE:		szErrorVal = "BADGE_ERROR_INVALID_PACKAGE";			break;
	case BADGE_ERROR_NOT_SUPPORTED:			szErrorVal = "BADGE_ERROR_NOT_SUPPORTED";			break;
	default:								szErrorVal = "Unknown Error";						break;
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
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	return false;
}

/**
* @function 		IterateGmainLoop
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void IterateGmainLoop(void)
{
	g_pMainLoop = g_main_loop_new(NULL, false);
	g_nTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(g_nTimeoutId);
	g_nTimeoutId = 0;
	g_pMainLoop = NULL;
}

/**
* @function 		QuitGmainLoop
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
void QuitGmainLoop(void)
{
	if(g_pMainLoop != NULL)
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/** @} */
