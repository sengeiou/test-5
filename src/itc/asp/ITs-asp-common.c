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
#include "ITs-asp-common.h"

/** @addtogroup itc-asp
*  @ingroup itc
*  @{
*/

/**
* @function 		AspOutputGetError
* @description	 	Maps error enums to string values
* @parameter		nRet: error code returned
* @return 			error string
*/
char* AspOutputGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case ASP_ERROR_NONE:					szErrorVal = "ASP_ERROR_NONE";					break;
	case ASP_ERROR_NOT_PERMITTED: 			szErrorVal = "ASP_ERROR_NOT_PERMITTED";			break;
	case ASP_ERROR_OUT_OF_MEMORY:			szErrorVal = "ASP_ERROR_OUT_OF_MEMORY";			break;
	case ASP_ERROR_PERMISSION_DENIED:		szErrorVal = "ASP_ERROR_PERMISSION_DENIED";		break;
	case ASP_ERROR_RESOURCE_BUSY: 			szErrorVal = "ASP_ERROR_RESOURCE_BUSY";			break;
	case ASP_ERROR_INVALID_PARAMETER: 		szErrorVal = "ASP_ERROR_INVALID_PARAMETER";		break;
	case ASP_ERROR_CONNECTION_TIME_OUT: 	szErrorVal = "ASP_ERROR_CONNECTION_TIME_OUT";	break;
	case ASP_ERROR_NOT_SUPPORTED: 			szErrorVal = "ASP_ERROR_NOT_SUPPORTED";			break;
	case ASP_ERROR_NOT_INITIALIZED: 		szErrorVal = "ASP_ERROR_NOT_INITIALIZED";		break;
	case ASP_ERROR_ALREADY_INITIALIZED: 	szErrorVal = "ASP_ERROR_ALREADY_INITIALIZED";	break;
	case ASP_ERROR_COMMUNICATION_FAILED: 	szErrorVal = "ASP_ERROR_COMMUNICATION_FAILED";	break;
	case ASP_ERROR_OPERATION_FAILED: 		szErrorVal = "ASP_ERROR_OPERATION_FAILED";		break;
	case ASP_ERROR_IN_PROGRESS: 			szErrorVal = "ASP_ERROR_IN_PROGRESS";			break;
	case ASP_ERROR_SERVICE_NOT_FOUND: 		szErrorVal = "ASP_ERROR_SERVICE_NOT_FOUND";		break;
	case ASP_ERROR_SESSION_NOT_FOUND: 		szErrorVal = "ASP_ERROR_SESSION_NOT_FOUND";		break;
	case ASP_ERROR_NETWORK_ROLE_REJECTED: 	szErrorVal = "ASP_ERROR_NETWORK_ROLE_REJECTED";	break;
	default: 								szErrorVal = "Unknown Error";					break;
	}
	return szErrorVal;
}

/** @} */