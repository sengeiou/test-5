//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
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
#include <service_app.h>
#include <dlog.h>
#include <watchface-complication-provider.h>
#include "tct_common.h"
#include "ITs-watchface-complication-common.h"

#ifdef WEARABLE	//Starts WEARABLE
#include "tct-watchface-complication-native_wearable.h"
#endif  //WEARABLE	//End WEARABLE
#define COMPLICATION_TEST_APP "org.tizen.complication_test"

static bool app_create(void *data)
{
	return true;
}

static void app_control(app_control_h app_control, void *data)
{
	char* pszGetTCName = NULL;
	int i=0, result=0, nRet=0;
	bool bIsEditing = false;
	char* pszCallerAppId = NULL;
	watchface_complication_event_type_e eEventType = WATCHFACE_COMPLICATION_EVENT_NONE;

	nRet = watchface_complication_provider_setup_is_editing(app_control, &bIsEditing);
	if(nRet != WATCHFACE_COMPLICATION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] watchface_complication_provider_setup_is_editing returned %s error\\n", __LINE__, API_NAMESPACE, WatchfaceComplicationGetError(nRet));
		return;
	}

	if (bIsEditing) {
		bundle *pszContext = NULL;
		char *pszCmd = NULL;
		nRet = watchface_complication_provider_setup_get_context(app_control, &pszContext);
		if(nRet != WATCHFACE_COMPLICATION_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] watchface_complication_provider_setup_is_editing returned %s error\\n", __LINE__, API_NAMESPACE, 					WatchfaceComplicationGetError(nRet));
			return;
		}
		if(pszContext == NULL)
		{
			FPRINTF("[Line : %d][%s] watchface_complication_provider_setup_is_editing failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
			return;
		}
		bundle_get_str(pszContext, "CONTEXT_DATA", &pszCmd);
		nRet = get_last_result();
		if(nRet != BUNDLE_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] bundle_get_str returned %s error\\n", __LINE__, API_NAMESPACE, BundleGetError(nRet));
			FREE_MEMORY(pszContext);
			return;	
		}
		if(pszCmd == NULL)
		{
			FPRINTF("[Line : %d][%s] bundle_get_str failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
			FREE_MEMORY(pszContext);
			return;
		}
		g_hTestControl = NULL;
		nRet = app_control_clone(&g_hTestControl, app_control);
		if(nRet != APP_CONTROL_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] app_control_clone returned %s error\\n", __LINE__, API_NAMESPACE, AppControlGetError(nRet));
			FREE_MEMORY(pszContext);
			FREE_MEMORY(pszCmd);
			return;
		}
		if(g_hTestControl == NULL)
		{
			FPRINTF("[Line : %d][%s] app_control_clone failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
			FREE_MEMORY(pszContext);
			FREE_MEMORY(pszCmd);
			return;
		}
		if (pszCmd && strcmp(pszCmd, SETUP_IS_EDITING_TEST_VAL) == 0)
			WatchfaceComplicationProviderSetupIsEditingChecker();
		else if (pszCmd && strcmp(pszCmd, SETUP_REPLY_TO_EDITOR_TEST_VAL) == 0)
			WatchfaceComplicationProviderSetupReplyToEditorChecker();
		else if (pszCmd && strcmp(pszCmd, SETUP_GET_CONTEXT_TEST_VAL) == 0)
			WatchfaceComplicationProviderSetupGetContextChecker();
		FREE_MEMORY(pszContext);
		FREE_MEMORY(pszCmd);
		return;
	}

	nRet = watchface_complication_provider_event_get_type(app_control, &eEventType);
	if(nRet != WATCHFACE_COMPLICATION_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] watchface_complication_provider_event_get_type returned %s error\\n", __LINE__, API_NAMESPACE, 				WatchfaceComplicationGetError(nRet));
		return;
	}

	if (eEventType != WATCHFACE_COMPLICATION_EVENT_NONE) {
		nRet = app_control_clone(&g_hTestControl, app_control);
		if(nRet != APP_CONTROL_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] app_control_clone returned %s error\\n", __LINE__, API_NAMESPACE, AppControlGetError(nRet));
			return;
		}
		if(g_hTestControl == NULL)
		{
			FPRINTF("[Line : %d][%s] app_control_clone failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
			return;
		}
		if (g_pszEventCmd && strcmp(g_pszEventCmd, EVENT_GET_EVENT_TYPE_TEST_VAL) == 0)
			WatchfaceComplicationProviderEventGetTypeChecker();
		else if (g_pszEventCmd && strcmp(g_pszEventCmd, EVENT_GET_PROVIDER_ID_TEST_VAL) == 0)
			WatchfaceComplicationProviderEventGetProviderIdChecker();
		else if (g_pszEventCmd && strcmp(g_pszEventCmd, EVENT_GET_COMP_TYPE_TEST_VAL) == 0)
			WatchfaceComplicationProviderEventGetComplicationTypeChecker();
		else if (g_pszEventCmd && strcmp(g_pszEventCmd, EVENT_GET_CONTEXT_TEST_VAL) == 0)
			WatchfaceComplicationProviderEventGetContextChecker();
		return;
	}

	nRet = app_control_get_caller(app_control, &pszCallerAppId);
	if (pszCallerAppId != NULL && strcmp(pszCallerAppId, COMPLICATION_TEST_APP) == 0) {
		FREE_MEMORY(pszCallerAppId);
		return;
	}
	FREE_MEMORY(pszCallerAppId);

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

			PRINT_TC_RESULT("%d",result);
			FREE_MEMORY_TC(pszGetTCName);
			return;
		}
	}

	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, pszGetTCName);
	PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to execute %s : Unknown Test Case Name\\n", __FILE__, __LINE__, pszGetTCName);
	PRINT_TC_RESULT("%d",1);
	FREE_MEMORY_TC(pszGetTCName);
	app_control_destroy(app_control);
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
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is Terminated", __FUNCTION__, __LINE__);
	return ret;
}

