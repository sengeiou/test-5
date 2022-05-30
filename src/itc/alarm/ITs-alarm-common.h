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
#include "bundle.h"
#include <notification.h>

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

#define TIMEOUT_CB					10000
#define TEST_HELLOWORLD_APPID		"org.tizen.helloworld"
#define TEST_TESTAPPLICATION_APPID	"org.tizen.testapplication"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define RUN_POLLING_LOOP {\
	g_pApplicationMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pApplicationMainLoop);\
	g_main_loop_run(g_pApplicationMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pApplicationMainLoop = NULL;\
}

gboolean Timeout(gpointer data);
char* AppControlGetError(int nRet);
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
