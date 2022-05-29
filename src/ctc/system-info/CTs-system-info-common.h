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
#ifndef _CTS_SYSTEM_INFO_COMMON_H_
#define _CTS_SYSTEM_INFO_COMMON_H_

#include "tct_common.h"

//Add test package related includes here
#include <system_info.h>

/** @addtogroup ctc-system-info
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE			"SYSTEM_INFO_CTC"
#define SCREEN_BPP_FEATURE 		"http://tizen.org/feature/screen.bpp"
#define USB_HOST_FEATURE		"http://tizen.org/feature/usb.host"
#define USB_ACCESSORY_FEATURE	"http://tizen.org/feature/usb.accessory"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

//Add helper function declarations here

char* SystemInfoGetErrorCode(int nResult);

/** @} */ //end of ctc-system-info

#endif   //_CTS_SYSTEM_INFO_COMMON_H_
