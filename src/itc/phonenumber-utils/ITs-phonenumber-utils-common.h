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
#ifndef _ITS_PHONENUMBER_UTILS_COMMON_H_
#define _ITS_PHONENUMBER_UTILS_COMMON_H_

#include "tct_common.h"
#include <phone_number.h>
#include <utils_i18n.h>

/** @addtogroup itc-phonenumber-utils
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"PHONENUMBER_UTILS_ITC"
#define PHONE_NUMBER				"82242239483"
#define PHONE_FEATURE				"http://tizen.org/feature/network.telephony"

//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

char *PhoneNumberUtilsGetError(int nRet);
char* GetRegion(int nRet);
char* GetLanguage(int nRet);

bool g_bPhoneSupported;

/** @}*/

#endif  //_ITS_PHONENUMBER_UTILS_COMMON_H_
