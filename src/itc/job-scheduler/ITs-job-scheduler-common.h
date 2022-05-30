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
#ifndef _ITS_JOB_SCHEDULER_COMMON_H_
#define _ITS_JOB_SCHEDULER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"

#include <job_scheduler.h>
#include <job_error.h>
#include <job_info.h>
#include <dlog.h>

/** @addtogroup itc-%{itc-job_scheduler}
*  @ingroup itc
*  @{
*/
#define API_NAMESPACE				"JOB_SCHEDULER_ITC"
#define BATTERY_FEATURE				"http://tizen.org/feature/battery"
#define NETWORK_FEATURE				"http://tizen.org/feature/network.wifi"
#define LOCATION_FEATURE			"http://tizen.org/feature/location.gps"
#define USB_FEATURE					"http://tizen.org/feature/usb.host"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bJobSchedulerInit )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of Job Scheduler failed so leaving test \\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define JOB_ID "TestJob"

static job_info_h job_info;
static job_service_h job_service;

bool g_bJobSchedulerInit;
bool g_bBatteryFeatureNotSupported;
bool g_bLocationFeatureNotSupported;
bool g_bUsbFeatureNotSupported;
bool g_bNetworkFeatureNotSupported;


char *JobGetError(int nRet);

/** @} */
#endif  //_ITS_JOB_SCHEDULER_COMMON_H_
