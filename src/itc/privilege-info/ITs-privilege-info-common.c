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
#include "ITs-privilege-info-common.h"

/** @addtogroup itc-privilege-info
*  @ingroup itc
*  @{
*/

/**
* @function 		PrivilegeinfoGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* PrivilegeinfoGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case PRVINFO_ERROR_NONE:				szErrorVal = "PRVINFO_ERROR_NONE";					break;
	case PRVINFO_ERROR_OUT_OF_MEMORY:		szErrorVal = "PRVINFO_ERROR_OUT_OF_MEMORY";			break;
	case PRVINFO_ERROR_INVALID_PARAMETER:	szErrorVal = "PRVINFO_ERROR_INVALID_PARAMETER";		break;
	case PRVINFO_ERROR_INTERNAL_ERROR:		szErrorVal = "PRVINFO_ERROR_INTERNAL_ERROR";		break;
        case PRVINFO_ERROR_NOT_SUPPORTED:       szErrorVal = "PRVINFO_ERROR_NOT_SUPPORTED";            break;
	default:								szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}
/** @} */
