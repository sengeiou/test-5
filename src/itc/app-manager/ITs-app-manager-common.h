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
#ifndef _ITS_APP_MANAGER_COMMON_H_
#define _ITS_APP_MANAGER_COMMON_H_

#include "tct_common.h"
#include "tct_app_common.h"

#include <glib.h>
#include <glib-object.h>
#include <string.h>

//Add test package related includes here

#include <app.h>
#include <app_manager.h>
#include <app_context.h>
#include <app_info.h>

/** @addtogroup itc-app-manager
*  @ingroup itc
*  @{
*/

#define TIME_DELAY					20
#define USLEEPDELAY					500000
#define LOCALE						"No Locale"
#define GMAINTIMEOUT				10000 		//10 seconds
#define TEST_TESTAPPLICATION_APPID	"org.tizen.testapplication"
#define TEST_APPMANAGERTESTFILE_APPID	"org.tizen.appmanagertestfile"
#define TEST_COMPONENTBASED_APPID	"org.example.componentbased"
#define TEST_HELLOWORLD_APPID "org.tizen.helloworld"
#define MKEY						"test"
#define MVALUE						"metavalue"
#define API_NAMESPACE				"APP_MANAGER_ITC"
#define TIMEOUT_CB					15000

//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bAppManagerOpen )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of App Manager Open failed\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, AppManagerCallbackTimeout, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pMainLoop = NULL;\
}

bool g_bAppManagerOpen;
app_context_h pstAppContext;
bool g_bAppManagerCallback;
GMainLoop *g_pMainLoop;
app_control_h g_app_control_handler;
bool g_bResCallBackIsHit;

char *AppManagerGetError(int nRet);
char* AppControlGetError(int nRet);
char* AppManagerGetStaus(int nStatus);
char* AppManagerGetAppComponent(app_info_app_component_type_e nStatus);
gboolean AppManagerCallbackTimeout(gpointer data);
void AppManagerAppContextChangeCallback(app_context_h app_context, app_context_event_e event, void *user_data);
void* AppManagerCreateEventLoop(void* pArg);
void AppManagerAppContextEventCallback(app_context_h app_context, app_context_event_e event, void *user_data);
bool AppInfoMetaDataFilterForeachCallback (app_info_h app_info, void *user_data);
bool AppInfoMetaDataCallback(const char *metadata_key, const char *metadata_value, void *user_data);
bool AppManagerAppContextCallback(app_context_h app_context, void *user_data);
bool AppManagerEventCallback(const char *type, const char *app_id,app_manager_event_type_e event_type,app_manager_event_state_e event_state,
		app_manager_event_h handle, void *user_data);

/** @} */
#endif  //_ITS_APP_MANAGER_COMMON_H_
