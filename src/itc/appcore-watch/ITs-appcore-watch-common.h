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
#ifndef _ITS_APPCORE_WATCH_COMMON_H_
#define _ITS_APPCORE_WATCH_COMMON_H_

#include "assert.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "tct_common.h"

//Add test package related includes here
#include <signal.h>
#include <watch_app.h>
#include <Evas.h>

#define TIMEZONE_BUFFER_MAX			1024
#define TIMEOUT_CB 					5000
#define WATCH_APP_FEATURE		"http://tizen.org/feature/watch_app"
#define API_NAMESPACE			"APPCORE_WATCH_ITC"

FILE *g_fpLog;
GMainLoop *g_pAppcoreWatchMainLoop;

//Add helper function declarations here

#define FPRINTF(...) {\
	g_fpLog = fopen(ERR_LOG,"a");\
	fprintf(g_fpLog, __VA_ARGS__);\
	fclose(g_fpLog);\
}

#define START_TEST {\
	FPRINTF("[Line : %d][appcore_watch_ITC] Starting test : %s\\n", __LINE__, __FUNCTION__);\
}

#define RUN_POLLING_LOOP {\
	g_pAppcoreWatchMainLoop = g_main_loop_new(NULL, false);\
	nAppcoreWatchTimeoutId = g_timeout_add(TIMEOUT_CB, AppcoreWatchTimeout, g_pAppcoreWatchMainLoop);\
	g_main_loop_run(g_pAppcoreWatchMainLoop);\
	g_source_remove(nAppcoreWatchTimeoutId);\
	g_pAppcoreWatchMainLoop = NULL;\
}

#define CHECK_SUPPORT(eCompare, eRetVal, API, Error) {\
	if ( !g_bAppcoreWatchFeatureSupported )\
	{\
		if ( eRetVal == eCompare )\
		{\
			FPRINTF("[Line : %d][%s] Feature %s is not supported. Skipping Test\\n", __LINE__, API_NAMESPACE, WATCH_APP_FEATURE);\
			return 0;\
		}\
		else\
		{\
			FPRINTF("[Line : %d][%s] Feature %s is not supported but API %s returned = %s\\n", __LINE__, API_NAMESPACE, WATCH_APP_FEATURE, API, Error);\
			return 1;\
		}\
	}\
}


//Add helper function declarations here
char* AppcoreWatchGetError(int nRet);
void handler(int sig);
void event_callback(void *event, void *data);
bool watch_app_create_callback(int width, int height, void *user_data);
void watch_app_terminate_callback(void *user_data);
void watch_app_control_callback(app_control_h app_control, void *user_data);
void watch_app_pause_callback(void *user_data);
void watch_app_resume_callback(void *user_data);
void watch_app_time_tick_callback(watch_time_h watch_time, void *user_data);
void watch_app_ambient_tick_callback(watch_time_h watch_time, void *user_data);
void watch_app_ambient_changed_callback(bool ambient_mode, void *user_data);
gboolean AppcoreWatchTimeout(gpointer data);
#endif  //_ITS_APPCORE_WATCH_COMMON_H_
