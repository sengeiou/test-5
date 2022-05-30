/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ITs-battery-monitor-common.h"

/** @addtogroup itc-battery-monitor
*  @ingroup itc
*  @{
*/

/**
* @function		BatteryMonitorGetError
* @description		Maps battery monitor error enums to string values
* @parameter		nRet: error code returned
* @return		error string
*/
char* BatteryMonitorGetError(int nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
	case BATTERY_MONITOR_ERROR_NONE:			szErrorVal = "BATTERY_MONITOR_ERROR_NONE"; break;
	case BATTERY_MONITOR_ERROR_OUT_OF_MEMORY:		szErrorVal = "BATTERY_MONITOR_ERROR_OUT_OF_MEMORY"; break;
	case BATTERY_MONITOR_ERROR_INVALID_PARAMETER:		szErrorVal = "BATTERY_MONITOR_ERROR_INVALID_PARAMETER"; break;
	case BATTERY_MONITOR_ERROR_NO_DATA:			szErrorVal = "BATTERY_MONITOR_ERROR_NO_DATA"; break;
	case BATTERY_MONITOR_ERROR_PERMISSION_DENIED:		szErrorVal = "BATTERY_MONITOR_ERROR_PERMISSION_DENIED"; break;
	case BATTERY_MONITOR_ERROR_NOT_SUPPORTED:		szErrorVal = "BATTERY_MONITOR_ERROR_NOT_SUPPORTED"; break;
	case BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND:		szErrorVal = "BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND"; break;
	case BATTERY_MONITOR_ERROR_DB_FAILED:			szErrorVal = "BATTERY_MONITOR_ERROR_DB_FAILED"; break;
	case BATTERY_MONITOR_ERROR_DB_NOT_OPENED:		szErrorVal = "BATTERY_MONITOR_ERROR_DB_NOT_OPENED"; break;
	case BATTERY_MONITOR_ERROR_INTERNAL:			szErrorVal = "BATTERY_MONITOR_ERROR_INTERNAL"; break;
	}

	return szErrorVal;
}
/**
* @function             BatteryMonitorGetTime
* @description          returns start and end time
* @parameter            start and end pointers
* @return               integer value 0 on success and 1 on failure
*/

int BatteryMonitorGetTime(time_t *start, time_t *end)
{
        time_t ret_time;
        long int crr_time = 0;
        int tmin = 604800;
        time_t start_time;
        time_t end_time;
        time(&ret_time);
        if (ret_time == -1) {
                return 1;
        }
        crr_time = ret_time;
        start_time = 0;
        end_time = 0;
        start_time = (crr_time - tmin/2);
        end_time = (crr_time - 1);
        *start = start_time;
        *end = end_time;
        return 0;
}

/** @} */
