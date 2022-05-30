//
// Copyright (c) 2015 Samsung Electronics Co., Ltd.
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
#include <widget_app.h>
#include <widget_app_efl.h>
#include <dlog.h>
#include <system_info.h>

#include "tct_common.h"
#include "assert_common.h"

#ifdef MOBILE
#include "tct-appcore-widget-core_mobile.h"
#endif

#ifdef WEARABLE
#include "tct-appcore-widget-core_wearable.h"
#endif

#ifdef TV
#include "tct-appcore-widget-core_tv.h"
#endif

#ifdef TIZENIOT    //Starts TIZENIOT
#include "tct-appcore-widget-core_tizeniot.h"
#endif  //TIZENIOT    //End TIZENIOT


#include <app.h>
#include <Elementary.h>

#define FEATURE_SHELL_APPWIDGET "http://tizen.org/feature/shell.appwidget"

static int widget_obj_create(widget_context_h context, bundle *content, int w,
                             int h, void *user_data)
{
	widget_app_exit();
	return 0;
}

static int widget_obj_destroy(widget_context_h context,
                              widget_app_destroy_type_e reason, bundle *content, void *user_data)
{
	return 0;
}

static int widget_obj_pause(widget_context_h context, void *user_data)
{
	return 0;
}

static int widget_obj_resume(widget_context_h context, void *user_data)
{
	return 0;
}

static int widget_obj_update(widget_context_h context, bundle *content,
                             int force, void *user_data)
{
	return 0;
}

static int widget_obj_resize(widget_context_h context, int w, int h, void *user_data)
{
	return 0;
}

static bool app_create(void *data)
{
	return true;
}

char* pszGetTCName = NULL;
static int check_func_name(int argc, char **argv)
{
	gsize byte_size;
	const gchar *encoded_byte;
	guchar *byte = NULL;
	guchar *org = NULL;
	const size_t sz_byte_len = sizeof(size_t);
	const size_t sz_type = sizeof(int);
	const size_t sz_keysize = sizeof(size_t);
	const size_t sz_size = sizeof(size_t);

	if (argc > 2) {
		encoded_byte = argv[3];
		byte = g_base64_decode(encoded_byte, &byte_size);
		org = byte;
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
		g_free(org);
		if (pszGetTCName) {
			if (!strcmp(pszGetTCName, "utc_appcore_widget_widget_app_main_p")
					|| !strcmp(pszGetTCName, "utc_appcore_widget_widget_app_main_n1")
					|| !strcmp(pszGetTCName, "utc_appcore_widget_widget_app_main_n2")
					|| !strcmp(pszGetTCName, "utc_appcore_widget_widget_app_main_n3")
					|| !strcmp(pszGetTCName, "utc_appcore_widget_widget_app_exit_p")) {
				return 1;
			}
		}
	}

	return 0;
}

static gboolean run_testcases(gpointer user_data) {

	int i=0, result=0, nRet=0;

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
			return FALSE;
		}
	}

	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, pszGetTCName);
	PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to execute %s : Unknown Test Case Name\\n", __FILE__, __LINE__, pszGetTCName);
	PRINT_TC_RESULT("%d",1);
	FREE_MEMORY_TC(pszGetTCName);

	return FALSE;
}

static widget_class_h widget_app_create(void *user_data)
{
	widget_instance_lifecycle_callback_s ops = {
		.create = widget_obj_create,
		.destroy = widget_obj_destroy,
		.pause = widget_obj_pause,
		.resume = widget_obj_resume,
		.update = widget_obj_update,
		.resize = widget_obj_resize,
	};

	g_idle_add(run_testcases, NULL);
	return widget_app_class_create(ops, user_data);
}

static void app_control(app_control_h app_control, void *data)
{

	int i=0, result=0, nRet=0;
	nRet = app_control_get_extra_data(app_control, "testcase_name", &pszGetTCName);
	if(nRet != APP_CONTROL_ERROR_NONE)
	{
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] app_control_get_extra_data returns error = %d", __FUNCTION__, __LINE__, nRet);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to fetch test case name: app_control_get_extra_data API call fails\\n", __FILE__, __LINE__);
		PRINT_TC_RESULT("%d",1);
		FREE_MEMORY_TC(pszGetTCName);
		return;
	}

	run_testcases(NULL);


	return;
}

static void widget_app_terminate(void *data)
{
	widget_app_exit();
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Widget application Package is now Terminating", __FUNCTION__, __LINE__);
}

static void app_terminate(void *data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is now Terminating", __FUNCTION__, __LINE__);
}

int main(int argc, char *argv[])
{
	int ret = 0;

	//setting gcda file location for coverage
	setenv("GCOV_PREFIX","/tmp",1);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Coverage *.gcda File location set to /tmp/home/abuild/rpmbuild/BUILD/ ", __FUNCTION__, __LINE__);

	if (check_func_name(argc, argv)) {
		run_testcases(NULL);
	} else {
		int ret;
		bool feature;

		ret = system_info_get_platform_bool(FEATURE_SHELL_APPWIDGET, &feature);
	        if (!feature) {
			ui_app_lifecycle_callback_s event_callback = {0,};
			event_callback.create = app_create;
			event_callback.terminate = app_terminate;
			event_callback.app_control = app_control;

			dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Main Function is Invoked", __FUNCTION__, __LINE__);
			ret = ui_app_main(argc, argv, &event_callback, NULL);
			if (ret != APP_ERROR_NONE)
			{
				dlog_print(DLOG_ERROR, "NativeTCT", "Application ui_app_main call gets failed. err = %d", ret);
				PRINT_UTC_LOG("\\n[%s][Line : %d]Application ui_app_main call gets failed. err = %d\\n", __FILE__, __LINE__, ret);
				PRINT_TC_RESULT("%d",1);
				FREE_MEMORY_TC(pszGetTCName);
				return ret;
			}
		} else {
			widget_app_lifecycle_callback_s event_callback = {0,};
			event_callback.create = widget_app_create;
			event_callback.terminate = widget_app_terminate;

			dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Widget application Main Function is Invoked", __FUNCTION__, __LINE__);
			ret = widget_app_main(argc, argv, &event_callback, NULL);
			if (ret != WIDGET_ERROR_NONE)
			{
				dlog_print(DLOG_ERROR, "NativeTCT", "Widget application widget_app_main call gets failed. err = %d", ret);
				PRINT_UTC_LOG("\\n[%s][Line : %d] Widget application widget_app_main call gets failed. err = %d\\n", __FILE__, __LINE__, ret);
				PRINT_TC_RESULT("%d",1);
				FREE_MEMORY_TC(pszGetTCName);
				return ret;
			}
		}
	}

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is Terminated", __FUNCTION__, __LINE__);
	FREE_MEMORY_TC(pszGetTCName);
	return ret;
}
