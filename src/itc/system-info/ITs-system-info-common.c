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
#include "ITs-system-info-common.h"

/** @addtogroup itc-system-info
*  @ingroup itc
*  @{
*/
//Add helper function definitions here

/**
* @function 		SystemInfoGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SystemInfoGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case SYSTEM_INFO_ERROR_NONE :				szErrorVal = "SYSTEM_INFO_ERROR_NONE";					break; 
	case SYSTEM_INFO_ERROR_INVALID_PARAMETER :	szErrorVal = "SYSTEM_INFO_ERROR_INVALID_PARAMETER";		break; 
	case SYSTEM_INFO_ERROR_IO_ERROR :			szErrorVal = "SYSTEM_INFO_ERROR_IO_ERROR";				break;
	case SYSTEM_INFO_ERROR_OUT_OF_MEMORY :		szErrorVal = "SYSTEM_INFO_ERROR_OUT_OF_MEMORY";			break;
	case SYSTEM_INFO_ERROR_NOT_SUPPORTED :		szErrorVal = "SYSTEM_INFO_ERROR_NOT_SUPPORTED";			break;
	default :									szErrorVal = "Unknown error";							break;
	}
	return szErrorVal;
}
/** @} */