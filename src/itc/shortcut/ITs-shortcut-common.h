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
#ifndef _ITS_SHORTCUT_COMMON_H_
#define _ITS_SHORTCUT_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include "tct_app_common.h"
//#include <shortcut.h>
#include <shortcut_manager.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <glib.h>
#include <app.h>
#include <Elementary.h>

/** @addtogroup itc-shortcut
*  @ingroup itc
*  @{
*/

int g_nTimeoutId;
GMainLoop *g_pShortcutMainLoop;
bool g_bCallbackHit;
bool g_bRequestCBCallbackHit;
bool g_b2CallbackValueCheck;
bool g_bCallbackHitRemoveCb;

#define API_NAMESPACE				"SHORTCUT_ITC"
#define TEST_SHORTCUT_APPID			"org.tizen.shortcut_test"
#define TIMEOUT_CB					15000
#define SHORTCUTPERIOD				-1.0f
#define	DUPLICATEALLOWED			1
#define PKGID						"native.shortcut-itc"
#define TESTSTRING					"Test"
#define SHORTCUT_FEATURE			"http://tizen.org/feature/shortcut"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define RUN_POLLING_LOOP {\
	g_pShortcutMainLoop = g_main_loop_new(NULL, false);\
	g_nTimeoutId = g_timeout_add(TIMEOUT_CB, ShortcutTimeoutFunction, g_pShortcutMainLoop);\
	g_main_loop_run(g_pShortcutMainLoop);\
	g_source_remove(g_nTimeoutId);\
	g_pShortcutMainLoop = NULL;\
	g_nTimeoutId = 0;\
}

#define QUIT_GMAIN_LOOP {\
		if ( g_pShortcutMainLoop )\
		{\
			g_main_loop_quit(g_pShortcutMainLoop);\
			g_pShortcutMainLoop = NULL;\
		}\
}\


#define QUIT_GMAIN_LOOP_CONDITIONAL(CallbackHit1, CallbackHit2) {\
		if(CallbackHit1 && CallbackHit2)\
		{\
			if ( g_pShortcutMainLoop )\
			{\
				g_main_loop_quit(g_pShortcutMainLoop);\
				g_pShortcutMainLoop = NULL;\
			}\
		}\
}\

#define CHECK_CALLBACK_STATUS(szApiName, bCallbackHit, bRequestCallbackHit) {\
	if ( (bCallbackHit == false) || (bRequestCallbackHit == false))\
	{\
		FPRINTF("[Line : %d][%s] After %s, Issues Found with CallBack\\n", __LINE__, API_NAMESPACE, szApiName);\
		return 1;\
	}\
	else\
	{\
		FPRINTF("[Line : %d][%s] After %s, callback invoked\\n", __LINE__, API_NAMESPACE, szApiName);\
		bCallbackHit = false;\
		bRequestCallbackHit = false;\
	}\
}

//Add helper function declarations here
char* ShortcutError(int nRet);
gboolean ShortcutTimeoutFunction(gpointer data);

/** @} */
#endif  //_ITS_SHORTCUT_COMMON_H_
