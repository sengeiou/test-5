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
#include "ITs-appcore-agent-common.h"

/** @addtogroup itc-appcore-agent
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		AppcoreAgentGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppcoreAgentGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case APP_ERROR_INVALID_PARAMETER:	szErrorVal = "APP_ERROR_INVALID_PARAMETER";		break;
	case APP_ERROR_OUT_OF_MEMORY:		szErrorVal = "APP_ERROR_OUT_OF_MEMORY";			break;
	case APP_ERROR_INVALID_CONTEXT:		szErrorVal = "APP_ERROR_INVALID_CONTEXT";		break;
	case APP_ERROR_NO_SUCH_FILE:		szErrorVal = "APP_ERROR_NO_SUCH_FILE";			break;
	case APP_ERROR_ALREADY_RUNNING:		szErrorVal = "APP_ERROR_ALREADY_RUNNING";		break;
	default:							szErrorVal = "Unknown Error";					break;
	}

	return szErrorVal;
}
/** @} */