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
#ifndef _ITS_DEVICE_COMMON_H_
#define _ITS_DEVICE_COMMON_H_

//Add test package related includes here

#include "tct_common.h"

#include <device/battery.h>
#include <device/callback.h>
#include <device/display.h>
#include <device/haptic.h>
#include <device/led.h>
#include <device/power.h>
#include <glib.h>
#include <stdbool.h>
#include <device/ir.h>

/** @addtogroup itc-device
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE			"DEVICE_ITC"
#define LOG				100
#define MICROSECONDS_PER_SECOND		1000000
#define TIMEOUT_CB 			5000
#define LED_FEATURE			"http://tizen.org/feature/led"
#define DISPLAY_FEATURE             "http://tizen.org/feature/camera.back.flash"
#define IR_FEATURE			"http://tizen.org/feature/consumer_ir"
#define DISPLAY_STATE_FEATURE		"http://tizen.org/feature/display.state"
#define THERMAL_AP_FEATURE              "http://tizen.org/feature/thermistor.ap"
#define THERMAL_CP_FEATURE              "http://tizen.org/feature/thermistor.cp"
#define THERMAL_BATTERY_FEATURE        "http://tizen.org/feature/thermistor.battery"
#define DISPLAY_FEATURE_MAIN	       "http://tizen.org/feature/display"

GMainLoop *g_pDeviceMainLoop;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

//Add helper function declarations here

char* DeviceGetError(int nRet);
char* DeviceGetCallbackType(int type);
char* DeviceGetDisplayState(int state);
char* DeviceGetLedFlag(int flag);
char* DeviceGetPowerLock(int lock);
/** @} */
#endif  //_ITS_DEVICE_COMMON_H_
