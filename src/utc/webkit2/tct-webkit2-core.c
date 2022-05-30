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
#include "tct_common.h"

#ifdef MOBILE
#include "tct-webkit2-core_mobile.h"
#endif

#ifdef TV
#include "tct-webkit2-core_tv.h"
#endif

#ifdef WEARABLE
#include "tct-webkit2-core_wearable.h"
#endif

#ifdef TIZENIOT    
#include "tct-webkit2-core_tizeniot.h"
#endif //TIZENIOT

static char* key;
static char* fname;
static int nNum;
int run_testcases()
{
    int result = -1;
    int i;
    gsize byte_size;
    const gchar* encoded_byte;
    guchar* byte = NULL;
    guchar *org = NULL;

    static const size_t sz_byte_len = sizeof(size_t);
    static const size_t sz_type = sizeof(int);
    static const size_t sz_keysize = sizeof(size_t);
    static const size_t sz_size = sizeof(size_t);

    char* func_name = fname;//argv[1];
    if (nNum > 2)
	{
        encoded_byte = key;//argv[3];
        byte = g_base64_decode(encoded_byte,&byte_size);
        org = byte;
	byte += sz_byte_len; byte += sz_type;
        size_t keysize = *((size_t *)byte); byte += sz_keysize;
	byte += keysize;
        size_t size = *((size_t *)byte); byte += sz_size;
        void *val = (void *)byte; byte += size;
        func_name = strdup((char *)val);
        g_free(org);
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
            free(func_name);
            return result;
        }
    }

    dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, func_name);	


    printf("Unknown testcase name: \"%s\"\n", func_name);
    free(func_name);
    return 2;
}


static bool app_create(void *data)
{
	run_testcases();
	return false; // quit app
}

int main(int argc, char *argv[])
{
	int ret = 0;
	fname = argv[1];
	key = argv[3];
	nNum = argc;
	ui_app_lifecycle_callback_s event_callback = {0,};
	event_callback.create = app_create;

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
