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
#ifndef _CTS_WIFI_DIRECT_COMMON_H_
#define _CTS_WIFI_DIRECT_COMMON_H_

#include "tct_common.h"
#include <sys/stat.h>

/** @addtogroup ctc-wifi-direct
* @ingroup		ctc
* @{
*/

//Add test package related includes here

#define API_NAMESPACE			"WIFI_DIRECT_CTC"
#define FEATURE_WIFI			"http://tizen.org/feature/network.wifi"
#define FEATURE_WIFI_DIRECT		"http://tizen.org/feature/network.wifi.direct"

//Add helper function declarations here
#define START_TEST {\
	FPRINTF("\\n[Line : %d][%s] Starting test : %s\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

/** @} */ //end of ctc-wifi-direct

#endif  //_CTS_WIFI_DIRECT_COMMON_H_
