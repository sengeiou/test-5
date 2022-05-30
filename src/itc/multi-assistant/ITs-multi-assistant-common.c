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
#include <stdio.h>
#include <string.h>
#include "tct_common.h"
#include <bundle.h>

#include <malloc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <glib.h>
#include <stdbool.h>
#include <app.h>
#include <dlog.h>

#include "ITs-multi-assistant-common.h"

/** @addtogroup itc-multi-assistant
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		MaGetError
* @description	 	Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char *MaGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
		case MA_ERROR_NONE:						szErrorVal = "MA_ERROR_NONE";					break;
		case MA_ERROR_OUT_OF_MEMORY:			szErrorVal = "MA_ERROR_OUT_OF_MEMORY";			break;
		case MA_ERROR_IO_ERROR:					szErrorVal = "MA_ERROR_IO_ERROR";				break;
		case MA_ERROR_INVALID_PARAMETER:		szErrorVal = "MA_ERROR_INVALID_PARAMETER";		break;
		case MA_ERROR_TIMED_OUT:				szErrorVal = "MA_ERROR_TIMED_OUT";				break;
		case MA_ERROR_RECORDER_BUSY:			szErrorVal = "MA_ERROR_RECORDER_BUSY";			break;
		case MA_ERROR_PERMISSION_DENIED:		szErrorVal = "MA_ERROR_PERMISSION_DENIED";		break;
		case MA_ERROR_NOT_SUPPORTED:			szErrorVal = "MA_ERROR_NOT_SUPPORTED";			break;
		case MA_ERROR_INVALID_STATE:			szErrorVal = "MA_ERROR_INVALID_STATE";			break;
		case MA_ERROR_INVALID_LANGUAGE:			szErrorVal = "MA_ERROR_INVALID_LANGUAGE";		break;
		case MA_ERROR_ENGINE_NOT_FOUND:			szErrorVal = "MA_ERROR_ENGINE_NOT_FOUND";		break;
		case MA_ERROR_OPERATION_FAILED:			szErrorVal = "MA_ERROR_OPERATION_FAILED";		break;
		case MA_ERROR_SERVICE_RESET:			szErrorVal = "MA_ERROR_SERVICE_RESET";			break;
		case MA_ERROR_NOT_SUPPORTED_FEATURE:	szErrorVal = "MA_ERROR_NOT_SUPPORTED_FEATURE";	break;
		default:								szErrorVal = "Unknown Error";					break;
	}
	return szErrorVal;
}
/** @} */
