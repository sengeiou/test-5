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
#include "ITs-cbhm-common.h"

/** @addtogroup itc-cbhm
*  @ingroup itc
*  @{
*/

/**
* @function 		CbhmGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char *CbhmGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case CBHM_ERROR_NONE:					szErrorVal = "CBHM_ERROR_NONE";					break;
		case CBHM_ERROR_OUT_OF_MEMORY:			szErrorVal = "CBHM_ERROR_OUT_OF_MEMORY";		break;
		case CBHM_ERROR_NOT_SUPPORTED:			szErrorVal = "CBHM_ERROR_NOT_SUPPORTED";		break;
		case CBHM_ERROR_INVALID_PARAMETER:		szErrorVal = "CBHM_ERROR_INVALID_PARAMETER";	break;
		case CBHM_ERROR_NO_DATA:				szErrorVal = "CBHM_ERROR_NO_DATA";				break;
		case CBHM_ERROR_CONNECTION_REFUSED:		szErrorVal = "CBHM_ERROR_CONNECTION_REFUSED";	break;
		//case CBHM_ERROR_ALREADY_IN_USE:			szErrorVal = "CBHM_ERROR_ALREADY_IN_USE";		break; //Giving undeclared build error
		default:								szErrorVal = "Unknown Error";					break;
	}

	return szErrorVal;
}

/**
 * @function 		Timeout
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */ 
gboolean Timeout(gpointer data)
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