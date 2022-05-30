//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-stc-common.h"

/** @addtogroup itc-stc
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

char* StcGetError(int nRet)
{
	char *szErrorVal = "Undefined Error";

	switch ( nRet )
	{
	case STC_ERROR_NONE:									szErrorVal = "STC_ERROR_NONE";									break;
	case STC_ERROR_OPERATION_FAILED:						szErrorVal = "STC_ERROR_OPERATION_FAILED";						break;
	case STC_ERROR_OUT_OF_MEMORY:							szErrorVal = "STC_ERROR_OUT_OF_MEMORY";							break;
	case STC_ERROR_INVALID_PARAMETER:						szErrorVal = "STC_ERROR_INVALID_PARAMETER";						break;
	case STC_ERROR_INVALID_OPERATION:						szErrorVal = "STC_ERROR_INVALID_OPERATION ";					break;
	case STC_ERROR_NOT_SUPPORTED:							szErrorVal = "STC_ERROR_NOT_SUPPORTED";							break;
	case STC_ERROR_PERMISSION_DENIED:						szErrorVal = "STC_ERROR_PERMISSION_DENIED";						break;
	}

	return szErrorVal;
}

/**
* @function			StcMakeTime
* @description		Creates time_t type
* @parameter		int
* @parameter		int
* @parameter		int
* @parameter		int
* @parameter		int
* @return			time_t
*/
time_t StcMakeTime(int year, int mon, int day, int hour, int min)
{
	struct tm curr = { 0, };
	curr.tm_year = year - 1900;
	curr.tm_mon = mon - 1;
	curr.tm_mday = day;
	curr.tm_hour = hour;
	curr.tm_min = min;
	return mktime(&curr);
}
/** @} */
