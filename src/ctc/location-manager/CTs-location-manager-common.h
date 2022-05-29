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
#ifndef _CTS_LOCATION_MANAGER_COMMON_H_
#define _CTS_LOCATION_MANAGER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <locations.h>

/** @addtogroup ctc-location-manager
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE		"LOCATION_MANAGER_CTC"
#define GPS_FEATURE			"http://tizen.org/feature/location.gps"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

//Add helper function declarations here

/** @} */ //end of ctc-location-manager

#endif  //_CTS_LOCATION_MANAGER_COMMON_H_