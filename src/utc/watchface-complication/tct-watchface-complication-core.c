/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <glib.h>
#include <stdbool.h>
#include "tct_common.h"
#include "utc-watchface-complication.h"
#include <service_app.h>
#include <watchface-complication-provider.h>
#include <dlog.h>

#ifdef WEARABLE
#include "tct-watchface-complication-core_wearable.h"
#endif
#define COMPLICATION_TEST_APP "org.tizen.complication_test"

static bool app_create(void *data)
{
	return true;
}

static void app_control(app_control_h app_control, void *data)
{
	char* pszGetTCName = NULL;
	int i=0, result=0, nRet=0;
	bool is_editing = false;
	char* caller_app_id = NULL;
	watchface_complication_event_type_e event_type = WATCHFACE_COMPLICATION_EVENT_NONE;

	watchface_complication_provider_setup_is_editing(app_control, &is_editing);
	if (is_editing) {
		bundle *context = NULL;
		char *cmd = NULL;
		watchface_complication_provider_setup_get_context(app_control, &context);
		bundle_get_str(context, "CONTEXT_DATA", &cmd);

		app_control_clone(&__test_control, app_control);
		if (cmd && strcmp(cmd, SETUP_IS_EDITING_TEST_VAL) == 0)
			_utc_watchface_complication_provider_setup_is_editing_p_checker();
		else if (cmd && strcmp(cmd, SETUP_REPLY_TO_EDITOR_TEST_VAL) == 0)
			_utc_watchface_complication_provider_setup_reply_to_editor_p_checker();
		else if (cmd && strcmp(cmd, SETUP_GET_CONTEXT_TEST_VAL) == 0)
			_utc_watchface_complication_provider_setup_get_context_p_checker();
		return;
	}

	nRet = watchface_complication_provider_event_get_type(app_control, &event_type);
	if (event_type != WATCHFACE_COMPLICATION_EVENT_NONE) {
		app_control_clone(&__test_control, app_control);
		if (__event_cmd && strcmp(__event_cmd, EVENT_GET_EVENT_TYPE_TEST_VAL) == 0)
			__utc_watchface_complication_provider_event_get_type_p_checker();
		else if (__event_cmd && strcmp(__event_cmd, EVENT_GET_PROVIDER_ID_TEST_VAL) == 0)
			__utc_watchface_complication_provider_event_get_provider_id_p_checker();
		else if (__event_cmd && strcmp(__event_cmd, EVENT_GET_COMP_TYPE_TEST_VAL) == 0)
			__utc_watchface_complication_provider_event_get_complication_type_p_checker();
		else if (__event_cmd && strcmp(__event_cmd, EVENT_GET_CONTEXT_TEST_VAL) == 0)
			__utc_watchface_complication_provider_event_get_context_p_checker();
		return;
	}

	app_control_get_caller(app_control, &caller_app_id);
	if (caller_app_id != NULL && strcmp(caller_app_id, COMPLICATION_TEST_APP) == 0) {
		free(caller_app_id);
		return;
	}
	free(caller_app_id);

	nRet = app_control_get_extra_data(app_control, "testcase_name", &pszGetTCName);
	if(nRet != APP_CONTROL_ERROR_NONE)
	{
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] app_control_get_extra_data returns error = %d", __FUNCTION__, __LINE__, nRet);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to fetch test case name: app_control_get_extra_data API call fails\\n", __FILE__, __LINE__);
		PRINT_TC_RESULT("%d",1);
		FREE_MEMORY_TC(pszGetTCName);
		return;
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
			FREE_MEMORY_TC(pszGetTCName);
			return;
		}
	}

	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, pszGetTCName);
	PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to execute %s : Unknown Test Case Name\\n", __FILE__, __LINE__, pszGetTCName);
	PRINT_TC_RESULT("%d",1);
	FREE_MEMORY_TC(pszGetTCName);
	return;
}

static void app_terminate(void *data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is now Terminating", __FUNCTION__, __LINE__);
}

int main(int argc, char *argv[])
{
	int ret = 0;

	service_app_lifecycle_callback_s event_callback = {0,};
	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.app_control = app_control;

	//setting gcda file location for coverage
	setenv("GCOV_PREFIX","/tmp",1);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Coverage *.gcda File location set to /tmp/home/abuild/rpmbuild/BUILD/ ", __FUNCTION__, __LINE__);

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Main Function is Invoked", __FUNCTION__, __LINE__);
	ret = service_app_main(argc, argv, &event_callback, NULL);
	if (ret != APP_ERROR_NONE)
	{
		dlog_print(DLOG_ERROR, "NativeTCT", "Application service_app_main call gets failed. err = %d", ret);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Application service_app_main call gets failed. err = %d\\n", __FILE__, __LINE__, ret);
		PRINT_TC_RESULT("%d",1);
		return ret;
	}
	PRINT_TC_RESULT("%d", __result);
	dlog_print(DLOG_INFO, "NativeTCT", "result [%d] ", ret);

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is Terminated", __FUNCTION__, __LINE__);
	return ret;
}

