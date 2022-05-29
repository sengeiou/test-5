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
#ifndef _ITS_SYSTEM_SETTINGS_COMMON_H_
#define _ITS_SYSTEM_SETTINGS_COMMON_H_

#include "tct_common.h"
#include <system_settings.h>

/** @addtogroup itc-system-settings
*  @ingroup itc
*  @{
*/
//Add helper function declarations here
#define API_NAMESPACE	"SYSTEM_SETTINGS_ITC"
#define SYSTEM_SETTINGS_WEARABLE_PROFILE "wearable"
#define SYSTEM_SETTINGS_PROFILE_FEATURE	"http://tizen.org/feature/profile"

#define SYSTEM_SETTINGS_FEATURE	"http://tizen.org/feature/systemsetting"

#define SYSTEM_SETTINGS_NETWORK_WIFI_FEATURE  "http://tizen.org/feature/network.wifi"
#define SYSTEM_SETTINGS_FONT_FEATURE  "http://tizen.org/feature/systemsetting.font"
#define SYSTEM_SETTINGS_WALLPAPER_HOME_SCREEN_FEATURE "http://tizen.org/feature/systemsetting.home_screen"
#define SYSTEM_SETTINGS_LOCK_SCREEN_FEATURE "http://tizen.org/feature/systemsetting.lock_screen"
#define SYSTEM_SETTINGS_NOTIFICATION_EMAIL_FEATURE "http://tizen.org/feature/systemsetting.notification_email"
#define SYSTEM_SETTINGS_TELEPHONY_FEATURE "http://tizen.org/feature/network.telephony"
#define SYSTEM_SETTINGS_INCOMING_CALL_FEATURE "http://tizen.org/feature/systemsetting.incoming_call"
#define SYSTEM_SETTINGS_ACCESSIBILITY_GRAYSCALE_FEATURE "http://tizen.org/feature/accessibility.grayscale"
#define SYSTEM_SETTINGS_ACCESSIBILITY_NEGATIVE_FEATURE "http://tizen.org/feature/accessibility.negative"
#define SYSTEM_SETTINGS_ROTATING_BEZEL_FEATURE "http://tizen.org/feature/input.rotating_bezel"


#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

char* SystemSettingsGetError(int nRet);
char* SystemSettingsGetKey(int nVal);

/** @} */
#endif  //_ITS_SYSTEM_SETTINGS_COMMON_H_
