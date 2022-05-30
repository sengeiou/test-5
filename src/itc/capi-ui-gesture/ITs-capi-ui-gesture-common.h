//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
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
#ifndef _ITS_CAPI_UI_GESTURE_COMMON_H_
#define _ITS_CAPI_UI_GESTURE_COMMON_H_

//Add test package related includes here

#include <system_info.h>
#include <dlog.h>

#include "tct_common.h"
#include <app.h>
#include <app_common.h>
#include <gesture.h>

#include <glib.h>
#include <glib-object.h>
/** @addtogroup itc-%{capi-ui-gesture}
*  @ingroup itc
*  @{
*/

//Add helper function declarations here
#define API_NAMESPACE			"GESTURE_ITC"
#define GESTURE_FEATURE			"tizen.org/feature/sensor.gesture_recognition"

#define START_TEST {\
	FPRINTF("[Line:%d][%s] Starting test check initialize : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] Starting test check initialize : %s", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bIsFeatureMismatched ) {\
		FPRINTF("[Line:%d][%s] Feature Mismatch Error\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Mismatch Error", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	if ( !g_bIsGestureFeatureSupported ) {\
		FPRINTF("[Line : %d][%s] Feature Unsupported\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR, "NativeTCT", "[Line:%d][%s] Feature Unsupported", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( !g_bGestureHandleCreated ) {\
		FPRINTF("[Line:%d][%s] Precondition gesture handle creation Failed\\n", __LINE__, API_NAMESPACE);\
		dlog_print(DLOG_ERROR,"NativeTCT", "[Line:%d][%s] Precondition Failed", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

bool g_bIsFeatureMismatched;
bool g_bIsGestureFeatureSupported;
bool g_bGestureHandleCreated;
hand_gesture_h g_hHandGesture;

char* GestureGetError(int nRet);

/** @} */
#endif  //_ITS_CAPI_UI_GESTURE_COMMON_H_
