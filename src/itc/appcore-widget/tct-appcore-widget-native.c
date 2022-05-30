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
#include "tct-appcore-widget-native_mobile.h"
#endif  //MOBILE	//End MOBILE

#ifdef WEARABLE	//Starts WEARABLE
#include "tct-appcore-widget-native_wearable.h"
#endif  //WEARABLE	//End WEARABLE

#ifdef TV	//Starts TV
#include "tct-appcore-widget-native_tv.h"
#endif  //TV	//End TV

#ifdef TIZENIOT	//Starts TIZENIOT
#include "tct-appcore-widget-native_tizeniot.h"
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

#include <stdbool.h>
#include "ITs-appcore-widget-common.h"
#include <widget_app.h>

static char *func_name = NULL;
int result;
int run_testcases(void)
{
	result = -1;
	int i;

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Executing TC Name = %s", __FUNCTION__, __LINE__, func_name);
	for (i = 0; tc_array[i].name; i++)
	{
		if (func_name && !strncmp(func_name, tc_array[i].name, strlen(func_name)))
		{
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup begin", func_name);
			if (tc_array[i].startup)
			{
				tc_array[i].startup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup end", func_name);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body begin", func_name);
			result = tc_array[i].function();
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body end", func_name);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup begin", func_name);
			if (tc_array[i].cleanup)
			{
				tc_array[i].cleanup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup end", func_name);
			return result;
		}
	}
	
	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, func_name);
	printf("Unknown testcase name: \"%s\"\n", func_name);

	return 2;
}

static widget_class_h widget_app_create(void *user_data)
{
	run_testcases();
	return NULL;
}

static int check_func_name(int argc, char **argv)
{
	gsize byte_size;
	const gchar *encoded_byte;
	guchar *byte = NULL;
	static const size_t sz_byte_len = sizeof(size_t);
	static const size_t sz_type = sizeof(int);
	static const size_t sz_keysize = sizeof(size_t);
	static const size_t sz_size = sizeof(size_t);

	if (argc > 2)
	{
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

		func_name = strdup((char *)val);
		if (!strcmp(func_name, "ITc_appcore_widget_widget_app_main_exit_p"))
		{
			return 1;
		}
	}

	return 0;
}

static int check_support(int eCompare, int eRetVal, char* api, char* error){
	bool g_bAppcoreWidgetFeatureSupported = false;
	system_info_get_platform_bool(APPCORE_WIDGET_FEATURE, &g_bAppcoreWidgetFeatureSupported);
	CHECK_SUPPORT(eCompare, eRetVal, api, error);
	return 0;
}

int main(int argc, char *argv[])
{
	widget_app_lifecycle_callback_s event_callback = {0,};

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Main Function is Invoked", __FUNCTION__, __LINE__);
	if (check_func_name(argc, argv))
	{
		run_testcases();
	}
	else
	{
		//setting gcda file location for coverage
		setenv("GCOV_PREFIX","/tmp",1);
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Coverage *.gcda File location set to /tmp/home/abuild/rpmbuild/BUILD/ ", __FUNCTION__, __LINE__);

		event_callback.create = widget_app_create;
		int nRet = widget_app_main(argc, argv, &event_callback, NULL);
		result = check_support(WIDGET_ERROR_NOT_SUPPORTED, nRet, "widget_app_main", AppcoreWidgetGetError(nRet));
	}

	if (func_name)
	{
		free(func_name);
	}

	FILE *fres = fopen("/tmp/tcresult","w");
	fprintf(fres, "%d", result);
	fclose(fres);

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is Terminated", __FUNCTION__, __LINE__);
	return 0;
}
