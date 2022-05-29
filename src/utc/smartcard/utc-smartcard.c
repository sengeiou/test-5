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

#include "utc-smartcard.h"
#include <system_info.h>

#define  SE_FEATURE "http://tizen.org/feature/network.secure_element"
#define  SE_UICC_FEATURE "http://tizen.org/feature/network.secure_element.uicc"
#define  SE_ESE_FEATURE "http://tizen.org/feature/network.secure_element.ese"

bool _is_support_smartcard()
{
	bool ret = false;
	bool is_supported_se = false;
	bool is_supported_se_uicc = false;
	bool is_supported_se_ese = false;

	system_info_get_platform_bool(SE_FEATURE, &is_supported_se);
	system_info_get_platform_bool(SE_UICC_FEATURE, &is_supported_se_uicc);
	system_info_get_platform_bool(SE_ESE_FEATURE, &is_supported_se_ese);

	if(is_supported_se && (is_supported_se_uicc || is_supported_se_ese))
		ret = true;

	return ret;
}
