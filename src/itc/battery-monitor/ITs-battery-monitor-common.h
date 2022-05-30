/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#ifndef _ITS_BATTERY_MONITOR_COMMON_H_
#define _ITS_BATTERY_MONITOR_COMMON_H_

#include "tct_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <dlog.h>
#include <system_info.h>
#include "battery_monitor.h"
#include <app.h>
#include <time.h>

/** @addtogroup itc-battery-monitor
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"BATTERY-MONITOR_ITC"
#define BATTERY_FEATURE				"http://tizen.org/feature/battery"
#define TEST_APP_ID				"org.tizen.w-home"

#define START_TEST_NO_CHECK { \
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

bool g_bBatteryFeatureNotSupported;

char* BatteryMonitorGetError(int nRet);
int BatteryMonitorGetTime(time_t *start, time_t *end);
/** @} */
#endif  //_ITS_BATTERY_MONITOR_COMMON_H_
