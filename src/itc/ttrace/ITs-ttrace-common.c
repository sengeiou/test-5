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
#include "ITs-ttrace-common.h"

/** @addtogroup itc-ttrace
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		TTraceGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* TTraceGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch(nRet)
	{
		case TRACE_ERROR_NONE:				szErrorVal = "TRACE_ERROR_NONE";				break;
		case TRACE_ERROR_IO_ERROR:			szErrorVal = "TRACE_ERROR_IO_ERROR";			break;
		default: 							szErrorVal = "TRACE_ERROR_UNKNOWN";				break;
	}
	return szErrorVal;
}

/** @} */