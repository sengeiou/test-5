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
#ifndef _ITS_MINICONTROL_COMMON_H_
#define _ITS_MINICONTROL_COMMON_H_

#include "assert.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib-2.0/glib.h>
#include <glib.h>
#include <pthread.h>
#include <Evas.h>
#include <Elementary.h>
#include <minicontrol-viewer.h>
#include <minicontrol-provider.h>
//#include <minicontrol-monitor.h>
#include "tct_common.h"

/** @addtogroup itc-minicontrol
*  @ingroup minicontrol
*  @{
*/
#define TARGET_APP_ID "org.tizen.music-player"
#define MINICONTROL_NAME "minicontrol-itc"
#define API_NAMESPACE       "MINICONTROL_ITC"
#define GMAINTIMEOUT		10000 		//10 seconds
#define MINICONTROL_FEATURE		"http://tizen.org/feature/minicontrol"
//Add test package related includes here


//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}
#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	g_timeout_id = g_timeout_add(GMAINTIMEOUT, MinicontrolCallBackTimeout, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(g_timeout_id);\
	g_pMainLoop = NULL;\
}

//Add helper function declarations here

char* MinicontrolGetError(minicontrol_error_e nRet);
char* MinicontrolGetEvent(minicontrol_event_e nType);
char* MinicontrolGetProviderEvent(minicontrol_provider_event_e nType);
char* MinicontrolGetViewerEvent(minicontrol_viewer_event_e nType);
char* MinicontrolGetTargetViewer(minicontrol_target_viewer_e nType);
gboolean MinicontrolCallBackTimeout(gpointer data);

/** @}*/
#endif  //_ITS_MINICONTROL_COMMON_H_
