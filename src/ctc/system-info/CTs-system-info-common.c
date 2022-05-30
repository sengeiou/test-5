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
#include "CTs-system-info-common.h"

/** @addtogroup ctc-system-info
* @ingroup		ctc
* @{
*/

//Add helper function definitions here

/**
* @function 				SystemInfoGetErrorCode
* @description 				print the error of sysinfo information
* @parameter	[IN]		nResult, the error code
* @return 					NA
*/
char* SystemInfoGetErrorCode(int nResult)
{
	char *pszErrLog = NULL;
	switch ( nResult )
	{
	case SYSTEM_INFO_ERROR_PERMISSION_DENIED:	pszErrLog = "SYSTEM_INFO_ERROR_PERMISSION_DENIED";	break;
	case SYSTEM_INFO_ERROR_INVALID_PARAMETER:	pszErrLog = "SYSTEM_INFO_ERROR_INVALID_PARAMETER";	break;
	case SYSTEM_INFO_ERROR_OUT_OF_MEMORY:		pszErrLog = "SYSTEM_INFO_ERROR_OUT_OF_MEMORY";		break;
	case SYSTEM_INFO_ERROR_IO_ERROR:			pszErrLog = "SYSTEM_INFO_ERROR_IO_ERROR";			break;
	default:									pszErrLog = "UNKNOWN";
	}

	return pszErrLog;
}

/** @} */ //end of ctc-system-info