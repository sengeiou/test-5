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
#include "ITs-fido-client-common.h"

/** @addtogroup itc-fido-client
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		FidoClientGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* FidoClientGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case FIDO_ERROR_NONE:					szErrorVal = "FIDO_ERROR_NONE";					break;
	case FIDO_ERROR_OUT_OF_MEMORY:		    szErrorVal = "FIDO_ERROR_OUT_OF_MEMORY";			break;
	case FIDO_ERROR_INVALID_PARAMETER:	    szErrorVal = "FIDO_ERROR_INVALID_PARAMETER";		break;
	case FIDO_ERROR_PERMISSION_DENIED:	    szErrorVal = "FIDO_ERROR_PERMISSION_DENIED";		break;
	case FIDO_ERROR_NOT_SUPPORTED:			szErrorVal = "FIDO_ERROR_NOT_SUPPORTED";				break;
	default:								szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}
/**
* @function         TimeoutFunction
* @description      Called if some callback is not invoked for a particular timeout
* @parameter        gpointer data
* @return           gboolean
*/ 
gboolean TimeoutFunction(gpointer data)
{
    g_main_loop_quit((GMainLoop *)data);
    return false;
}

/** @} */