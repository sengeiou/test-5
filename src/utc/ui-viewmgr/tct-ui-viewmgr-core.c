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
#include "tct_common.h"

#ifdef MOBILE	//Starts MOBILE
#include "tct-ui-viewmgr-core_mobile.h"
#endif  //MOBILE	//End MOBILE

#ifdef WEARABLE	//Starts WEARABLE
#include "tct-ui-viewmgr-core_wearable.h"
#endif  //WEARABLE	//End WEARABLE

#ifdef TV	//Starts TV
#include "tct-ui-viewmgr-core_tv.h"
#endif  //TV	//End TV

#ifdef TIZENIOT	//Starts TIZENIOT
#include "tct-ui-viewmgr-core_tizeniot.h"
#endif  //TIZENIOT	//End TIZENIOT

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <glib.h>
#include <stdbool.h>
#include <app.h>
#include <dlog.h>


#include <ui_viewmanager.h>

static void create_base_page()
{
	ui_view *view;

	view = ui_view_create("base_page");
	ui_view_set_transition_style(view, "none");

	ui_viewmgr_push_view(view);
}

static bool app_create(void *user_data, void *event_info)
{
	dlog_print(DLOG_ERROR, "NativeTCT", "app crate called");
	create_base_page();

	return true;
}

static bool app_control(void *user_data, void *event_info)
{
	app_control_h app_control = (app_control_h)event_info;

	char* pszGetTCName = NULL;
	int i=0, result=0, nRet=0;
	nRet = app_control_get_extra_data(app_control, "testcase_name", &pszGetTCName);
	if(nRet != APP_CONTROL_ERROR_NONE)
	{
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] app_control_get_extra_data returns error = %d", __FUNCTION__, __LINE__, nRet);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to fetch test case name: app_control_get_extra_data API call fails\\n", __FILE__, __LINE__);
		PRINT_TC_RESULT("%d",1);
		FREE_MEMORY_TC(pszGetTCName);
		return 1;
	}

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Executing TC Name = %s", __FUNCTION__, __LINE__, pszGetTCName);
	for ( i = 0; tc_array[i].name; i++ )
	{
		if ( 0 == strncmp(pszGetTCName, tc_array[i].name, strlen(pszGetTCName)) )
		{
			DUMP_UTC_ERRLOG();
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup begin", pszGetTCName);
			if ( tc_array[i].startup )
			{
				tc_array[i].startup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup end", pszGetTCName);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body begin", pszGetTCName);
			result = tc_array[i].function();
			dlog_print(DLOG_INFO, "NativeTCT", "%s returns value = %d", pszGetTCName, result);
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body end", pszGetTCName);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup begin", pszGetTCName);
			if ( tc_array[i].cleanup )
			{
				tc_array[i].cleanup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup end", pszGetTCName);

			CLOSE_UTC_ERRLOG();
			PRINT_TC_RESULT("%d",result);
			FREE_MEMORY_TC(pszGetTCName);
			return 1;
		}
	}

	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, pszGetTCName);
	PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to execute %s : Unknown Test Case Name\\n", __FILE__, __LINE__, pszGetTCName);
	PRINT_TC_RESULT("%d",1);
	FREE_MEMORY_TC(pszGetTCName);
	return 1;
}

int main(int argc, char *argv[])
{
	int ret = 0;

	ui_application_event_s events[]= {
		{UI_APPLICATION_EVENT_CREATE, app_create},
		{UI_APPLICATION_EVENT_CONTROL, app_control}
	};

	//setting gcda file location for coverage
	setenv("GCOV_PREFIX","/tmp",1);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Coverage *.gcda File location set to /tmp/home/abuild/rpmbuild/BUILD/ ", __FUNCTION__, __LINE__);

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] test Application Main Function is Invoked", __FUNCTION__, __LINE__);

	//Initialize ui_app. ui_app initializes basic resources including ui_viewmgr internally.
	if (UI_VIEWMGR_ERROR_NONE != ui_application_init())
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_init() is failed");
		return 0;
	}

	//Run ui_app. Now it requests to run an application mainloop.
	if (UI_VIEWMGR_ERROR_NONE != ui_application_run(argc, argv, events, 2, NULL))
	{
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_run() is failed");
		return 0;
	}

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is Terminated", __FUNCTION__, __LINE__);
	return ret;
}
