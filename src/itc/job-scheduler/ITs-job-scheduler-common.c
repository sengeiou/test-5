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
#include "ITs-job-scheduler-common.h"

/** @addtogroup itc-job-scheduler
*  @ingroup itc
*  @{
*/

/**
* @function 		JobGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char *JobGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case JOB_ERROR_NONE:					szErrorVal = "JOB_ERROR_NONE";						break;
	case JOB_ERROR_INVALID_PARAMETER:		szErrorVal = "JOB_ERROR_INVALID_PARAMETER";			break;
	case JOB_ERROR_OUT_OF_MEMORY:			szErrorVal = "JOB_ERROR_OUT_OF_MEMORY";				break;
	case JOB_ERROR_IO_ERROR:				szErrorVal = "JOB_ERROR_IO_ERROR";					break;
	case JOB_ERROR_NOT_INITIALIZED:			szErrorVal = "JOB_ERROR_NOT_INITIALIZED";			break;
	case JOB_ERROR_NO_SUCH_JOB:				szErrorVal = "JOB_ERROR_NO_SUCH_JOB";				break;
	case JOB_ERROR_ALREADY_EXIST:			szErrorVal = "JOB_ERROR_ALREADY_EXIST";				break;
	case JOB_ERROR_PERMISSION_DENIED:		szErrorVal = "JOB_ERROR_PERMISSION_DENIED";			break;
	case JOB_ERROR_NOT_SUPPORTED:			szErrorVal = "JOB_ERROR_NOT_SUPPORTED";				break;
	default:								szErrorVal = "Undefined Error";						break;
	}

	return szErrorVal;
}
/** @} */
