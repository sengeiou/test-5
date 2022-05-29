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
#include "ITs-widget_service-common.h"

/** @addtogroup itc-widget_service
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
 * @function 		WidgetServiceGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet: error code returned
 * @return 			error string
 */
char* WidgetServiceGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{
		case WIDGET_ERROR_INVALID_PARAMETER:		szErrorVal = "WIDGET_ERROR_INVALID_PARAMETER";			break;
		case WIDGET_ERROR_OUT_OF_MEMORY:			szErrorVal = "WIDGET_ERROR_OUT_OF_MEMORY";				break;
		case WIDGET_ERROR_RESOURCE_BUSY:			szErrorVal = "WIDGET_ERROR_RESOURCE_BUSY";				break;
		case WIDGET_ERROR_PERMISSION_DENIED:		szErrorVal = "WIDGET_ERROR_PERMISSION_DENIED";			break;
		case WIDGET_ERROR_CANCELED:					szErrorVal = "WIDGET_ERROR_CANCELED";					break;
		case WIDGET_ERROR_IO_ERROR:					szErrorVal = "WIDGET_ERROR_IO_ERROR";					break;
		case WIDGET_ERROR_TIMED_OUT:				szErrorVal = "WIDGET_ERROR_TIMED_OUT";					break;
		case WIDGET_ERROR_NOT_SUPPORTED:			szErrorVal = "WIDGET_ERROR_NOT_SUPPORTED";				break;
		case WIDGET_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "WIDGET_ERROR_FILE_NO_SPACE_ON_DEVICE";	break;
		case WIDGET_ERROR_FAULT:					szErrorVal = "WIDGET_ERROR_FAULT";						break;
		case WIDGET_ERROR_ALREADY_EXIST:			szErrorVal = "WIDGET_ERROR_ALREADY_EXIST";				break;
		case WIDGET_ERROR_ALREADY_STARTED:			szErrorVal = "WIDGET_ERROR_ALREADY_STARTED";			break;
		case WIDGET_ERROR_NOT_EXIST:				szErrorVal = "WIDGET_ERROR_NOT_EXIST";					break;
		case WIDGET_ERROR_DISABLED:					szErrorVal = "WIDGET_ERROR_DISABLED";					break;
		case WIDGET_ERROR_MAX_EXCEEDED:				szErrorVal = "WIDGET_ERROR_MAX_EXCEEDED";					break;
		default:									szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

/**
 * @function 		WidgetServiceTimeout
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
gboolean WidgetServiceTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		pMainLoop = NULL;
	}
	FPRINTF("[Line: %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}
/** @} */