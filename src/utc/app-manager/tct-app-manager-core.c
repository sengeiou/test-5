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

#include "assert_common.h"
#include "tct_common.h"

#ifdef MOBILE
#include "tct-app-manager-core_mobile.h"
#endif

#ifdef WEARABLE
#include "tct-app-manager-core_wearable.h"
#endif

#ifdef TV
#include "tct-app-manager-core_tv.h"
#endif

#ifdef TIZENIOT    
#include "tct-app-manager-core_tizeniot.h"
#endif 




	
	
	


static char *pszGetTCName;
static void (*cleanup_func)(void);

static bool app_create(void *data)
{
	return true;
}

static gboolean __run_testcases(gpointer data)
{
	int i;

	utc_result = -1;
	cleanup_func = NULL;
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Executing TC Name = %s", __FUNCTION__, __LINE__, pszGetTCName);
	for (i = 0; tc_array[i].name; i++) {
		if (strncmp(pszGetTCName, tc_array[i].name, strlen(pszGetTCName)) == 0) {
			DUMP_UTC_ERRLOG();
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup begin", pszGetTCName);
			if (tc_array[i].startup) {
				tc_array[i].startup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup end", pszGetTCName);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body begin", pszGetTCName);
			tc_array[i].function();
			dlog_print(DLOG_INFO, "NativeTCT", "%s", pszGetTCName);
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body end", pszGetTCName);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup function pointer assigned", pszGetTCName);
			if (tc_array[i].cleanup){
				cleanup_func = tc_array[i].cleanup;
			}

			return FALSE;
		}
	}

	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, pszGetTCName);
	PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to execute %s : Unknown Test Case Name\\n", __FILE__, __LINE__, pszGetTCName);
	PRINT_TC_RESULT("%d", 1);
	FREE_MEMORY_TC(pszGetTCName);
	ui_app_exit();
	return FALSE;
}

static void app_control(app_control_h app_control, void *data)
{
	int nRet;

	nRet = app_control_get_extra_data(app_control, "testcase_name", &pszGetTCName);
	if (nRet != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] app_control_get_extra_data returns error = %d", __FUNCTION__, __LINE__, nRet);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to fetch test case name: app_control_get_extra_data API call fails\\n", __FILE__, __LINE__);
		PRINT_TC_RESULT("%d", 1);
		FREE_MEMORY_TC(pszGetTCName);
		ui_app_exit();
		return;
	}

	g_idle_add(__run_testcases, NULL);

	return;
}

static void app_terminate(void *data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is now Terminating", __FUNCTION__, __LINE__);
}

int main(int argc, char *argv[])
{
	int ret;
	
	ui_app_lifecycle_callback_s event_callback = {0,};

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.app_control = app_control;

	//setting gcda file location for coverage
	setenv("GCOV_PREFIX", "/tmp", 1);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Coverage *.gcda File location set to /tmp/home/abuild/rpmbuild/BUILD/ ", __FUNCTION__, __LINE__);

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Main Function is Invoked", __FUNCTION__, __LINE__);
	ret = ui_app_main(argc, argv, &event_callback, NULL);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, "NativeTCT", "Application ui_app_main call gets failed. err = %d", ret);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Application ui_app_main call gets failed. err = %d\\n", __FILE__, __LINE__, ret);
		PRINT_TC_RESULT("%d", 1);
		return ret;
	}

	CLOSE_UTC_ERRLOG();
	PRINT_TC_RESULT("%d", utc_result);
	if (cleanup_func){
		dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup begin", pszGetTCName);
		cleanup_func();
		dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup end", pszGetTCName);
	}
	FREE_MEMORY_TC(pszGetTCName);

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is Terminated", __FUNCTION__, __LINE__);
	return ret;
}
