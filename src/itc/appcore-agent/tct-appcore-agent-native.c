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
#include "tct_common.h"

#ifdef MOBILE	//Starts MOBILE
#include "tct-appcore-agent-native_mobile.h"
#endif  //MOBILE	//End MOBILE

#ifdef WEARABLE	//Starts WEARABLE
#include "tct-appcore-agent-native_wearable.h"
#endif  //WEARABLE	//End WEARABLE

#ifdef TV	//Starts TV
#include "tct-appcore-agent-native_tv.h"
#endif  //TV	//End TV

#ifdef TIZENIOT	//Starts TIZENIOT
#include "tct-appcore-agent-native_tizeniot.h"
#endif  //TIZENIOT	//End TIZENIOT


#include <malloc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <glib.h>
#include <stdbool.h>

#include <app.h>
#include <dlog.h>
#include "ITs-appcore-agent-common.h"
#include <service_app.h>

static char *pszGetTCName;

static bool app_create(void *data)
{
	return true;
}

static int check_func_name(int argc, char **argv)
{
	gsize byte_size;
	const gchar *encoded_byte;
	guchar *byte = NULL;
	const size_t sz_byte_len = sizeof(size_t);
	const size_t sz_type = sizeof(int);
	const size_t sz_keysize = sizeof(size_t);
	const size_t sz_size = sizeof(size_t);

	if (argc > 2) {
		encoded_byte = argv[3];
		byte = g_base64_decode(encoded_byte, &byte_size);
		byte += sz_byte_len;
		byte += sz_type;
		size_t keysize = *((size_t *)byte);
		byte += sz_keysize;
		byte += keysize;
		size_t size = *((size_t *)byte);
		byte += sz_size;
		void *val = (void *)byte;
		byte += size;

		pszGetTCName = strdup((char *)val);
		if (pszGetTCName) {
			if (!strcmp(pszGetTCName, "ITc_appcore_agent_service_app_main_exit_p")) {
				return 1;
			}
		}
	}

	return 0;
}

static gboolean run_testcases(gpointer user_data) {

	int i;

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Executing TC Name = %s", __FUNCTION__, __LINE__, pszGetTCName);
	for (i = 0; tc_array[i].name; i++) {
		if (strncmp(pszGetTCName, tc_array[i].name, strlen(pszGetTCName)) == 0) {
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup begin", pszGetTCName);			
			if (tc_array[i].startup) {
			tc_array[i].startup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup end", pszGetTCName);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body begin", pszGetTCName);
			tc_array[i].function();
			dlog_print(DLOG_INFO, "NativeTCT", "%s", pszGetTCName);
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body end", pszGetTCName);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup begin", pszGetTCName);
			if (tc_array[i].cleanup) {
				tc_array[i].cleanup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup end", pszGetTCName);
			return FALSE;
		}
	}

	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, pszGetTCName);
	PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to execute %s : Unknown Test Case Name\\n", __FILE__, __LINE__, pszGetTCName);
	g_result = 1;
	service_app_exit();

	return FALSE;
}

static void app_control(app_control_h app_control, void *data)
{

	int nRet;

	nRet = app_control_get_extra_data(app_control, "testcase_name", &pszGetTCName);
	if (nRet != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] app_control_get_extra_data returns error = %d", __FUNCTION__, __LINE__, nRet);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to fetch test case name: app_control_get_extra_data API call fails\\n", __FILE__, __LINE__);
		g_result = 1;
		service_app_exit();
		return;
	}

	g_idle_add(run_testcases, NULL);

	return;
}

static void app_terminate(void *data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is now Terminating", __FUNCTION__, __LINE__);
}

int main(int argc, char *argv[])
{
	int ret = 0;

	//setting gcda file location for coverage
	setenv("GCOV_PREFIX", "/tmp", 1);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Coverage *.gcda File location set to /tmp/home/abuild/rpmbuild/BUILD/ ", __FUNCTION__, __LINE__);

	if (check_func_name(argc, argv)) {
		g_argc = argc;
		g_argv = argv;
		run_testcases(NULL);
	} else {

		service_app_lifecycle_callback_s event_callback = {0,};
		event_callback.create = app_create;
		event_callback.terminate = app_terminate;
		event_callback.app_control = app_control;

		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Main Function is Invoked", __FUNCTION__, __LINE__);
		ret = service_app_main(argc, argv, &event_callback, NULL);
		if (ret != APP_ERROR_NONE) {
			dlog_print(DLOG_ERROR, "NativeTCT", "Application ui_app_main call gets failed. err = %d", ret);
			PRINT_UTC_LOG("\\n[%s][Line : %d]Application ui_app_main call gets failed. err = %d\\n", __FILE__, __LINE__, ret);
			PRINT_TC_RESULT("%d", 1);
			return ret;
		}
	}

	PRINT_TC_RESULT("%d", g_result);
	FREE_MEMORY_TC(pszGetTCName);

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is Terminated", __FUNCTION__, __LINE__);
	return ret;
}
