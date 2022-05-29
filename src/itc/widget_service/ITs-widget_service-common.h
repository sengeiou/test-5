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
#ifndef _ITS_WIDGET_SERVICE_COMMON_H_
#define _ITS_WIDGET_SERVICE_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include "tct_app_common.h"
#include <glib.h>
#include <widget_service.h>
#include <widget_errno.h>
#include <widget_viewer_evas.h>
#include <bundle.h>

/** @addtogroup itc-widget_sevice
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"WIDGET_SERVICE_ITC"
#define TIMEOUT_CB 					30000
#define PATH_LEN					1024
#define LANGUAGE					"en-us"
#define TESTSTRING					"Test"
#define TEST_TESTWIDGET_APPID		"org.tizen.testwidget"
#define WIDGET_SERVICE_FEATURE		"http://tizen.org/feature/shell.appwidget"

#define START_TEST {\
	FPRINTF("[Line: %d][%s] Starting test: %s\\n",  __LINE__, API_NAMESPACE,__FUNCTION__);\
	if ( g_bSkipExecutionWithPass )\
	{\
		FPRINTF("[Line: %d][%s] Feature http://tizen.org/feature/shell.appwidget is not supported so skipping test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( g_bSkipExecutionWithFail )\
	{\
		FPRINTF("[Line: %d][%s] Feature http://tizen.org/feature/shell.appwidget is not supported but API not returned WIDGET_ERROR_NOT_SUPPORTED\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	if ( !g_bWidgetCreation )\
	{\
		FPRINTF("[Line: %d][%s] Precondition of Widget-Service create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
	if ( g_bWidgetServiceCBFlag == false )\
	{\
		g_loop = g_main_loop_new(NULL, false);\
		nTimeoutId = g_timeout_add(TIMEOUT_CB, WidgetServiceTimeout, g_loop);\
		g_main_loop_run(g_loop);\
		g_source_remove(nTimeoutId);\
		g_loop = NULL;\
	}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line: %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define PRINT_RESULTNONE(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line: %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
	}\
	else \
	{\
		FPRINTF("[Line: %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
		return;\
	}\
}

#define VERDICTLASTRESULT(API) {\
	g_nRet = get_last_result();\
	if ( (g_nRet == WIDGET_ERROR_NONE) || (g_nRet == WIDGET_ERROR_NOT_EXIST) )\
	{\
		if ( DEBUG )\
		{\
			FPRINTF("[Line: %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
		}\
		return 0;\
	}\
	else \
	{\
		FPRINTF("[Line: %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, WidgetServiceGetError(g_nRet), g_nRet);\
		return 1;\
	}\
}

//Add global variables here
int g_nRet;
GMainLoop *g_loop;
bool g_bWidgetServiceCBFlag;
bool g_bWidgetCreation;
char g_szPkgid[PATH_LEN];
char g_szWidgetid[PATH_LEN];
char g_szInstanceId[PATH_LEN];
Evas_Object *g_hWindow;
Evas_Object *g_hWidget;

//Add helper function declarations here
char *WidgetServiceGetError(int nRet);
gboolean WidgetServiceTimeout(gpointer data);
void DeleteWidget(void);

/** @} */
#endif  //_ITS_WIDGET_SERVICE_COMMON_H_
