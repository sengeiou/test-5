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
#ifndef _ITS_WIDGET_VIEWER_EVAS_COMMON_H_
#define _ITS_WIDGET_VIEWER_EVAS_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include "tct_app_common.h"
#include "assert.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glib.h>
#include <app.h>
#include "widget_service.h"
#include "widget_errno.h"
#include <Evas.h>
#include <Ecore_Evas.h>
#include <Edje.h>
#include <Elementary.h>

#include "widget_viewer_evas.h"

/** @addtogroup itc-widget_viewer_evas
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"WIDGET_SERVICE_ITC"
#define TIMEOUT_CB 					30.0F	//30 seconds
#define PATH_LEN					1024
#define SAMPLE_WIDGET				TEST_SAMPLE_APPID
#define WIDGET_VIEWER_EVAS_FEATURE	"http://tizen.org/feature/shell.appwidget"
#define TEST_SAMPLE_APPID			"org.tizen.sample"

#define START_TEST {\
	FPRINTF("Starting test: %s\\n",__FUNCTION__);\
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
		FPRINTF("[Line: %d][%s] Precondition of Widget-Viewer create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

const char *g_pWidgetID;
const char *g_pTitleString;
const char *g_pContentString;
int g_nRet;
typedef int (*test_case_cb)(Evas_Object *widget);

char *WidgetViewerGetError(int nRet);
Eina_Bool WidgetViewerTimeout(void *data);
void WidgetViewerGetWidgetId(Evas_Object *widget);
void WidgetViewerFeedMouseUpEvent(Evas_Object *widget);
void WidgetViewerTcFreeze(Evas_Object *widget);
void WidgetViewerGetTitleString(Evas_Object *widget);
void WidgetViewerPause(Evas_Object *widget);
void WidgetViewerResume(Evas_Object *widget);
void WidgetViewerThaw(Evas_Object *widget);
void WidgetViewerGetContent(Evas_Object *widget);
void WidgetViewerActivate(Evas_Object *widget);
int WidgetViewerAsyncRetCallback(test_case_cb cb, struct widget_evas_event_info *info);

/** @} */
#endif  //_ITS_WIDGET_VIEWER_EVAS_COMMON_H_
