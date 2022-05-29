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
#include "ITs-capi-ui-inputmethod-manager-common.h"

/** @addtogroup itc-inputmethod-manager
* @ingroup		itc
* @{
*/

//Add helper function definitions here

/**
 * @function 		InputmethodManagerGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* InputmethodManagerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case IME_MANAGER_ERROR_NONE:
			szErrorVal = "IME_MANAGER_ERROR_NONE";
			break;
		case IME_MANAGER_ERROR_INVALID_PARAMETER:
			szErrorVal = "IME_MANAGER_ERROR_INVALID_PARAMETER";
			break;
		case IME_MANAGER_ERROR_PERMISSION_DENIED:
			szErrorVal = "IME_MANAGER_ERROR_PERMISSION_DENIED";
			break;
		case IME_MANAGER_ERROR_OPERATION_FAILED:
			szErrorVal = "IME_MANAGER_ERROR_OPERATION_FAILED";
			break;
		default:
			szErrorVal = "Unknown Error";
			break;
	}

	return szErrorVal;
}

/** @} */ //end of inputmethod-manager
