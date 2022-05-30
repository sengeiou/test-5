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
#include "ITs-dlog-common.h"

/** @addtogroup itc-dlog
*  @ingroup itc
*  @{
*/

//Add helper function definitions here
/**
* @function 		DlogGetPriorityListValue
* @description	 	Initialize Macro or return value if already initialized
* @parameter		[earrPriority] Enum container array
*					[nTotalEnums] Enum Count
*					[nType] Request Type
* @return 			If requested, Enum Value
*/
char *DlogGetPriorityListValue(log_priority earrPriority[], int *nTotalEnums, int nType)
{
	if ( nType == SETENUM )
	{
		int nIterator = 0;
		log_priority nEnumList[] = {DLOG_DEBUG, DLOG_INFO, DLOG_WARN, DLOG_ERROR};
		*nTotalEnums = sizeof(nEnumList) / sizeof(nEnumList[0]);
		for ( nIterator = 0; nIterator<(*nTotalEnums); nIterator++ )
		{
			earrPriority[nIterator] = nEnumList[nIterator];
		}
		return NULL;
	}
	else if ( nType == GETENUM )
	{
		char *szReturnVal = NULL;
		switch ( earrPriority[*nTotalEnums] )
		{
		case DLOG_DEBUG:	szReturnVal = "DLOG_DEBUG";			break;
		case DLOG_INFO:		szReturnVal = "DLOG_INFO";			break;
		case DLOG_WARN:		szReturnVal = "DLOG_WARN";			break;
		case DLOG_ERROR:	szReturnVal = "DLOG_ERROR";			break;
		default:			szReturnVal = "Unknown Enum";		break;
		}
		return szReturnVal;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Wrong Argument Passed to DlogGetPriorityListValue\\n", __LINE__, API_NAMESPACE);
		return NULL;
	}
}

/**
* @function 		DlogGetPriority
* @description	 	Maps log_priority enums 
* @parameter		priority : priority level
* @return 			priority level string
*/
char* DlogGetPriority(log_priority priority)
{
	char *szPriorityVal = NULL;
	switch ( priority )
	{
	case DLOG_UNKNOWN:		szPriorityVal = "DLOG_UNKNOWN";			break;
	case DLOG_DEFAULT:		szPriorityVal = "DLOG_DEFAULT";			break;
	case DLOG_VERBOSE:		szPriorityVal = "DLOG_VERBOSE";			break;
	case DLOG_DEBUG:		szPriorityVal = "DLOG_DEBUG";			break;
	case DLOG_INFO:			szPriorityVal = "DLOG_INFO";			break;
	case DLOG_WARN:			szPriorityVal = "DLOG_WARN";			break;
	case DLOG_ERROR:		szPriorityVal = "DLOG_ERROR";			break;
	case DLOG_FATAL:		szPriorityVal = "DLOG_FATAL";			break;
	case DLOG_SILENT:		szPriorityVal = "DLOG_SILENT";			break;
	case DLOG_PRIO_MAX:		szPriorityVal = "DLOG_PRIO_MAX";		break;
	default:				szPriorityVal = "Unknown Priority";		break;
	}

	return szPriorityVal;
}

/**
* @function 		DlogGetError
* @description	 	Maps dlog_error_e enums 
* @parameter		error : error level
* @return 			error string
*/
char* DlogGetError(dlog_error_e error)
{
	char *szErrorVal = NULL;
	switch ( error )
	{
	case DLOG_ERROR_NONE:				szErrorVal = "DLOG_ERROR_NONE";					break;
	case DLOG_ERROR_INVALID_PARAMETER:	szErrorVal = "DLOG_ERROR_INVALID_PARAMETER";	break;
	case DLOG_ERROR_NOT_PERMITTED:		szErrorVal = "DLOG_ERROR_NOT_PERMITTED";		break;
	default:							szErrorVal = "Unknown Error";					break;
	}

	return szErrorVal;
}
/** @} */
