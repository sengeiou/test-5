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
#include "ITs-shortcut-common.h"

/** @addtogroup itc-shortcut
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
 * @function 		ShortcutError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* ShortcutError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
		case SHORTCUT_ERROR_NONE:				szErrorVal = "SHORTCUT_ERROR_NONE";					break;
		case SHORTCUT_ERROR_NO_SPACE:			szErrorVal = "SHORTCUT_ERROR_NO_SPACE";				break;
		case SHORTCUT_ERROR_EXIST:				szErrorVal = "SHORTCUT_ERROR_EXIST";				break;
		case SHORTCUT_ERROR_FAULT:				szErrorVal = "SHORTCUT_ERROR_FAULT";				break;
		case SHORTCUT_ERROR_NOT_SUPPORTED:		szErrorVal = "SHORTCUT_ERROR_NOT_SUPPORTED";		break;
		case SHORTCUT_ERROR_RESOURCE_BUSY:		szErrorVal = "SHORTCUT_ERROR_RESOURCE_BUSY";		break;
		case SHORTCUT_ERROR_INVALID_PARAMETER:	szErrorVal = "SHORTCUT_ERROR_INVALID_PARAMETER";	break;
		case SHORTCUT_ERROR_COMM:				szErrorVal = "SHORTCUT_ERROR_COMM";					break;
		case SHORTCUT_ERROR_OUT_OF_MEMORY:		szErrorVal = "SHORTCUT_ERROR_OUT_OF_MEMORY";		break;
		case SHORTCUT_ERROR_IO_ERROR:			szErrorVal = "SHORTCUT_ERROR_IO_ERROR";				break;
		case SHORTCUT_ERROR_PERMISSION_DENIED:	szErrorVal = "SHORTCUT_ERROR_PERMISSION_DENIED";	break;
		default:								szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}
/**
 * @function 		ShortcutTimeoutFunction
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
gboolean ShortcutTimeoutFunction(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	return false;
}

/** @} */