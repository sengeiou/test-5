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
#ifndef _ITS_APPCORE_WIDGET_COMMON_H_
#define _ITS_APPCORE_WIDGET_COMMON_H_

#include "tct_common.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

//Add test package related includes here
#include "bundle.h"
#include <widget_app.h>
#include <widget_app_efl.h>
//#include <widget_viewer.h>
#include <widget_viewer_evas.h>
#include <Evas.h>

/** @addtogroup itc-appcore-widget
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE			"APPCORE_WIDGET_ITC"
#define TIMEZONE_BUFFER_MAX		1024
#define MAX_CONTEXT_COUNT		100
#define TESTSTRING				"Test"
#define APPCORE_WIDGET_FEATURE	"http://tizen.org/feature/shell.appwidget"
#define CLASSID					"MultiClass"

widget_context_h g_hWidgetContexts[MAX_CONTEXT_COUNT];
int g_nContextCount;

//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define CHECK_SUPPORT(eCompare, eRetVal, API, Error) {\
	if ( !g_bAppcoreWidgetFeatureSupported )\
	{\
		if ( eRetVal == eCompare )\
		{\
			FPRINTF("[Line : %d][%s] Feature %s is not supported. Skipping Test\\n", __LINE__, API_NAMESPACE, APPCORE_WIDGET_FEATURE);\
			return 0;\
		}\
		else\
		{\
			FPRINTF("[Line : %d][%s] Feature %s is not supported but API %s returned = %s\\n", __LINE__, API_NAMESPACE, APPCORE_WIDGET_FEATURE, API, Error);\
			return 1;\
		}\
	}\
}

//Add helper function declarations here
char* AppcoreWidgetGetError(int nRet);
char* BundleGetError(int nRet);

gboolean handler(gpointer user_data);
void event_callback(void *event, void *data);
int widget_instance_create_callback(widget_context_h context, bundle *content, int w, int h, void *user_data);
int widget_instance_destroy_callback(widget_context_h context, widget_app_destroy_type_e reason, bundle *content, void *user_data);
int widget_instance_pause_callback(widget_context_h context, void *user_data);
int widget_instance_resume_callback(widget_context_h context, void *user_data);
int widget_instance_resize_callback(widget_context_h context, int w, int h, void *user_data);
int widget_instance_update_callback(widget_context_h context, bundle *content, int force, void *user_data);
widget_class_h widget_app_create_callback(void *user_data);
void widget_app_terminate_callback(void *user_data);
bool widget_context_callback(widget_context_h context, void *data);

/** @} */ //end of itc-appcore-widget

#endif  //_ITS_APPCORE_WIDGET_COMMON_H_
