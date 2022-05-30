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
#ifndef _CTS_DEVICE_COMMON_H_
#define _CTS_DEVICE_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <device/led.h>

/** @addtogroup ctc-device
* @ingroup		ctc
* @{
*/

#define LED_FEATURE				"http://tizen.org/feature/led"
#define API_NAMESPACE			"DEVICE_CTC"

#define START_TEST {\
	FPRINTF("\\n[Line : %d][%s] Starting test : %s", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

//Add helper function declarations here

char* DeviceGetError(int nRet);
char* DeviceGetLedFlag(int nFlag);

/** @} */ //end of ctc-device

#endif  //_CTS_DEVICE_COMMON_H_