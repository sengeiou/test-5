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
#ifndef _ITS_SCREEN_MIRRORING_COMMON_H_
#define _ITS_SCREEN_MIRRORING_COMMON_H_

#include "tct_common.h"
//#include <scmirroring_src.h>
#include <scmirroring_sink.h>

#include <sys/time.h>
#include <glib-object.h>
#include <glib.h>
#include <Elementary.h>

/** @addtogroup itc-screen-mirroring
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE							"SCREEN_MIRRORING_ITC"
#define SCREEN_MIRRORING_WIFI_DIRECT_FEATURE 	"http://tizen.org/feature/network.wifi.direct.display"

//Add test package related includes here

bool g_bIsFeatureSupported;
bool g_bIsFeatureSupportMismatch;

//Add helper function declarations here
#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__,API_NAMESPACE, __FUNCTION__);\
	if ( g_bIsFeatureSupportMismatch )\
	{\
		return 1;\
	}\
	if ( ! g_bIsFeatureSupported )\
	{\
		return 0;\
	}\
}
//Add helper function declarations here

gboolean SMirroringCallbackTimeout(gpointer data);
char* ScreenMirroringInfoGetError(int nRet);
char* ScreenMirroringInfoDisplayType(scmirroring_display_type_e nRet);
char* ScreenMirroringInfoResolution(scmirroring_resolution_e nRet);
char* ScreenMirroringSinkState(scmirroring_sink_state_e nRet);
/** @} */

#endif  //_ITS_SCREEN_MIRRORING_COMMON_H_
