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
#include "tct-tts-native_mobile.h"
#endif  //MOBILE	//End MOBILE

#ifdef WEARABLE	//Starts WEARABLE
#include "tct-tts-native_wearable.h"
#endif  //WEARABLE	//End WEARABLE

#ifdef TV	//Starts TV
#include "tct-tts-native_tv.h"
#endif  //TV	//End TV

#ifdef TIZENIOT	//Starts TIZENIOT
#include "tct-tts-native_tizeniot.h"
#endif  //TIZENIOT	//End TIZENIOT


#include <stdio.h>
#include <string.h>
#include "tct_common.h"
#include <malloc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <glib.h>
#include <stdbool.h>

#include <app.h>
#include <dlog.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int g_argc;
char** g_argv = NULL;

void transfer_arg(int * argc, char ** argv[])
{
	*argc = g_argc;
	*argv = g_argv;
	dlog_print(DLOG_INFO, "NativeTCT", "[transfer_arg called] argc = %d, argv[0] = %s", *argc, (NULL == *argv) ? "NULL" : *argv[0]);
}
/*
int run_testcases()
{
    int result = -1;
    int i;
    gsize byte_size;
    const gchar* encoded_byte;
    guchar* byte = NULL;

    static const size_t sz_byte_len = sizeof(size_t);
    static const size_t sz_type = sizeof(int);
    static const size_t sz_keysize = sizeof(size_t);
    static const size_t sz_size = sizeof(size_t);

    char* func_name = fname;//argv[1];
    if (nNum > 2)
    {
        encoded_byte = key;//argv[3];
        byte = g_base64_decode(encoded_byte,&byte_size);
	byte += sz_byte_len; byte += sz_type;
        size_t keysize = *((size_t *)byte); byte += sz_keysize;
	byte += keysize;
        size_t size = *((size_t *)byte); byte += sz_size;
        void *val = (void *)byte; byte += size;
        func_name = strdup((char *)val);
    }

    dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Executing TC Name = %s", __FUNCTION__, __LINE__, func_name);

    for (i = 0; tc_array[i].name; i++)
    {
        if (!strncmp(func_name, tc_array[i].name, strlen(func_name)))
	{
	    DUMP_UTC_ERRLOG();
            if (tc_array[i].startup){
		dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup begin", func_name);
                tc_array[i].startup();
				dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup end", func_name);
            }
			
            dlog_print(DLOG_INFO, "NativeTCT", "%s : Body begin", func_name);
            result = tc_array[i].function();
	    dlog_print(DLOG_INFO, "NativeTCT", "%s : Body end", func_name);

            if (tc_array[i].cleanup){
				dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup begin", func_name);
                tc_array[i].cleanup();
				dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup end", func_name);
            }
			CLOSE_UTC_ERRLOG();
            FILE *fres = fopen("/tmp/tcresult","w"); fprintf(fres, "%d", result); fclose(fres); 

			if (0 == strncmp(func_name, "ITc_tts_set_unset_engine_changed_cb_p", strlen(func_name)) || 0 == strncmp("ITc_ttse_", func_name, strlen("ITc_ttse_"))) {
				dlog_print(DLOG_INFO, "NativeTCT", "%s must be exited", func_name);
				ui_app_exit();
			}
			return result;
        }
    }

    dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, func_name);

    printf("Unknown testcase name: \"%s\"\n", func_name);
    return 2;
}
*/

static bool app_create(void *data)
{
//	run_testcases();
	return true; // quit app
}

static void app_control(app_control_h app_control, void *data)
{
	int result = -1;
	int nRet = 0;
	int i;
	char *func_name = NULL;

	nRet = app_control_get_extra_data(app_control, "testcase_name", &func_name);
	if(nRet != APP_CONTROL_ERROR_NONE)
	{
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] app_control_get_extra_data returns error = %d", __FUNCTION__, __LINE__, nRet);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to fetch test case name: app_control_get_extra_data API call fails\\n", __FILE__, __LINE__);
		PRINT_TC_RESULT("%d",1);
		FREE_MEMORY_TC(func_name);
		return;
	}

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Executing TC Name = %s", __FUNCTION__, __LINE__, func_name);

	for (i = 0; tc_array[i].name; i++)
	{
		if (!strncmp(func_name, tc_array[i].name, strlen(func_name)))
		{
			DUMP_UTC_ERRLOG();
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup begin", func_name);
			if (tc_array[i].startup){
				tc_array[i].startup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup end", func_name);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body begin", func_name);
			result = tc_array[i].function();
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body end", func_name);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup begin", func_name);
			if (tc_array[i].cleanup){
				tc_array[i].cleanup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup end", func_name);
			CLOSE_UTC_ERRLOG();
			FILE *fres = fopen("/tmp/tcresult","w"); fprintf(fres, "%d", result); fclose(fres); 

			if (0 == strncmp(func_name, "ITc_tts_set_unset_engine_changed_cb_p", strlen(func_name)) || 0 == strncmp("ITc_ttse_", func_name, strlen("ITc_ttse_"))) {
				dlog_print(DLOG_INFO, "NativeTCT", "%s must be exited", func_name);
				ui_app_exit();
			}
			FREE_MEMORY_TC(func_name);
			return;
		}
	}

	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, func_name);

	printf("Unknown testcase name: \"%s\"\n", func_name);
	FREE_MEMORY_TC(func_name);
	return;
}

static void app_terminate(void *data)
{
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is now Terminating", __FUNCTION__, __LINE__);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	
	g_argc = argc;
	g_argv = argv;

	ui_app_lifecycle_callback_s event_callback = {0,};
	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.app_control = app_control;

	//setting gcda file location for coverage
	setenv("GCOV_PREFIX","/tmp",1);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Coverage *.gcda File location set to /tmp/home/abuild/rpmbuild/BUILD/ ", __FUNCTION__, __LINE__);

	ret = ui_app_main(argc, argv, &event_callback, NULL);
	if (ret != APP_ERROR_NONE)
	{
		printf("\n[Line No : %d]Unable to execute test cases: ui_app_main API call gets failed\n", __LINE__);
	}
	return ret;
}
