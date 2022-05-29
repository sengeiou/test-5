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
#ifndef _ITS_APPLICATION_COMMON_H_
#define _ITS_APPLICATION_COMMON_H_

#include "tct_common.h"
#include "tct_app_common.h"

#include "app.h"
#include "app_alarm.h"
#include "app_control.h"
#include "app_preference.h"
#include "app_resource_manager.h"
#include "app_event.h"
#include "app_info.h"
#include "app_common.h"
#include "bundle.h"
#include <app_control.h>
#include <app_control_uri.h>
#include <glib.h>
#include <glib-object.h>

/** @addtogroup itc-application
*  @ingroup itc
*  @{
*/
GMainLoop *g_pApplicationMainLoop;

#define API_NAMESPACE				"APPLICATION_ITC"
#define WAIT_CALLBACK				5
#define PATH_LEN					1024

#define IMAGE_ID					"tizen_logo.png"
#define EDJ_ID						"rsc1.edc"
#define SOUND_ID					"Kalimba.mp3"
#define TIMEOUT_CB					10000
#define TEST_HELLOWORLD_APPID		"org.tizen.helloworld"
#define TEST_TESTAPPLICATION_APPID	"org.tizen.testapplication"
#define FEATURE_APP			"http://tizen.org/feature/display.state"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define START_TEST_DISPLAY {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bAppInfoCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition to create app info failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}


#define RUN_POLLING_LOOP {\
	g_pApplicationMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pApplicationMainLoop);\
	g_main_loop_run(g_pApplicationMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pApplicationMainLoop = NULL;\
}


#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
        if ( Handle == NULL )\
{\
        FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
        FreeResource;\
        return 1;\
}\
}

gboolean Timeout(gpointer data);
char* AppControlGetError(int nRet);
char* AppControlUriGetError(int nRet);
char* PreferenceGetError(int nRet);
char* AlarmGetError(int nRet);
char* AppGetError(int nRet);
char* AppResourceGetError(int nRet);
char* AppControlGetLaunchMode(app_control_launch_mode_e nRet);
bool ApplicationGetDataPath(char* pPath); // this function outputs tha application data path
bool ApplicationAppendToAppDataPath(char* pInputPath, char* pFinalPath); // this function appends the input string to app data path and outputs the final resultant path
char* BundleGetError(int nRet);
char* EventGetError(int nRet);
/** @} */
#endif  //_ITS_APPLICATION_COMMON_H_
