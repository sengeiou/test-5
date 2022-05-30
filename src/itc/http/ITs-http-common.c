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
#include "ITs-http-common.h"

/** @addtogroup itc-http
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		HttpGetError
* @description	 	Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* HttpGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
		case HTTP_ERROR_NONE:					szErrorVal = "HTTP_ERROR_NONE";						break;
		case HTTP_ERROR_OUT_OF_MEMORY:			szErrorVal = "HTTP_ERROR_OUT_OF_MEMORY";			break;
		case HTTP_ERROR_PERMISSION_DENIED:		szErrorVal = "HTTP_ERROR_PERMISSION_DENIED";		break;
		case HTTP_ERROR_INVALID_PARAMETER:		szErrorVal = "HTTP_ERROR_INVALID_PARAMETER";		break;
		case HTTP_ERROR_INVALID_OPERATION:		szErrorVal = "HTTP_ERROR_INVALID_OPERATION";		break;
		case HTTP_ERROR_OPERATION_FAILED:		szErrorVal = "HTTP_ERROR_OPERATION_FAILED";			break;
		case HTTP_ERROR_COULDNT_RESOLVE_HOST:	szErrorVal = "HTTP_ERROR_COULDNT_RESOLVE_HOST";		break;
		case HTTP_ERROR_COULDNT_CONNECT:		szErrorVal = "HTTP_ERROR_COULDNT_CONNECT";			break;
		case HTTP_ERROR_OPERATION_TIMEDOUT:		szErrorVal = "HTTP_ERROR_OPERATION_TIMEDOUT";		break;
		case HTTP_ERROR_SSL_CONNECT_ERROR:		szErrorVal = "HTTP_ERROR_SSL_CONNECT_ERROR";		break;
		case HTTP_ERROR_NOT_SUPPORTED:			szErrorVal = "HTTP_ERROR_NOT_SUPPORTED";			break;
		case HTTP_ERROR_CANCELED:				szErrorVal = "HTTP_ERROR_CANCELED";					break;
		default:								szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}


/**
* @function 		httpTimeout
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/ 
gboolean httpTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	FPRINTF("[Line : %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/** @} */

