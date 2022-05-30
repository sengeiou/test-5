/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <glib.h>
#include <dlog.h>
#include <service_app.h>

#include "tct_common.h"

#ifdef MOBILE
#include "tct-job-scheduler-core_mobile.h"
#endif

#ifdef WEARABLE
#include "tct-job-scheduler-core_wearable.h"
#endif

#ifdef TIZENIOT
#include "tct-job-scheduler-core_tizeniot.h"
#endif


#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "NativeTCT"
#define KEY_TESTCASE_NAME "testcase_name"
#define GCOV_PATH "/tmp/home/abuild/rpmbuild/BUILD/"

static bool __app_create(void *data)
{
	return true;
}

static gboolean __run_testcase(gpointer data)
{
	char *testcase = (char *)data;
	int ret;
	int i;

	if (testcase == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Invalid parameter");
		return G_SOURCE_REMOVE;
	}

	dlog_print(DLOG_INFO, LOG_TAG, "Executing TC Name = %s", testcase);
	for (i = 0; tc_array[i].name; i++) {
		if (strcmp(testcase, tc_array[i].name) == 0) {
			DUMP_UTC_ERRLOG();
			dlog_print(DLOG_INFO, LOG_TAG, "%s: Startup begin",testcase);
			if (tc_array[i].startup) {
				tc_array[i].startup();
			}
			dlog_print(DLOG_INFO, LOG_TAG, "%s: Startup end",testcase);

			dlog_print(DLOG_INFO, LOG_TAG, "%s: Body begin", testcase);
			ret = tc_array[i].function();
			dlog_print(DLOG_INFO, LOG_TAG, "%s: Result(%d)",testcase,ret);
			dlog_print(DLOG_INFO, LOG_TAG, "%s: Body end", testcase);

			dlog_print(DLOG_INFO, LOG_TAG, "%s: Cleanup begin",testcase);
			if (tc_array[i].cleanup) {
				tc_array[i].cleanup();
			}
			dlog_print(DLOG_INFO, LOG_TAG, "%s: Cleanup end",testcase);

			PRINT_TC_RESULT("%d", ret);
			free(testcase);

			return G_SOURCE_REMOVE;
		}
	}

	dlog_print(DLOG_ERROR, LOG_TAG,
			"Unable to execute %s : Unknown Test Case Name",
			testcase);
	PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to execute %s : Unknown Test Case Name\\n", __FILE__, __LINE__, testcase);
	PRINT_TC_RESULT("%d", 1);
	free(testcase);
	service_app_exit();

	return G_SOURCE_REMOVE;
}

static void __app_control(app_control_h app_control, void *user_data)
{
	int ret;
	char *testcase = NULL;

	ret = app_control_get_extra_data(app_control, KEY_TESTCASE_NAME,
			&testcase);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Failed to get extra data %d", ret);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to fetch test case name: app_control_get_extra_data API call fails\\n", __FILE__, __LINE__);
		PRINT_TC_RESULT("%d", 1);
		service_app_exit();
		return;
	}

	g_idle_add(__run_testcase, testcase);
}

static void __app_terminate(void *user_data)
{
	dlog_print(DLOG_INFO, LOG_TAG,
			"Application Package is now Terminating");
}

int main(int argc, char *argv[])
{
	int ret;
	service_app_lifecycle_callback_s lifecycle_callbacks = {
		.create = __app_create,
		.terminate = __app_terminate,
		.app_control = __app_control
	};

	/* setting gcda file location for coverage */
	setenv("GCOV_PREFIX", "/tmp", 1);
	dlog_print(DLOG_INFO, LOG_TAG,
			"Coverage *.gcda File location set to /tmp");

	dlog_print(DLOG_INFO, LOG_TAG, "Application Main Function is Invoked");
	ret = service_app_main(argc, argv, &lifecycle_callbacks, NULL);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "service_app_main returns %d",
				ret);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Application ui_app_main call gets failed. err = %d\\n", __FILE__, __LINE__, ret);
		PRINT_TC_RESULT("%d", 1);
		return ret;
	}

	dlog_print(DLOG_INFO, LOG_TAG, "Application Package is Terminated");
	return ret;
}
