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
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlog.h>

#ifdef MOBILE
#include "tct-dali-core-core_mobile.h"
#endif /*MOBILE*/
#ifdef WEARABLE
#include "tct-dali-core-core_wearable.h"
#endif /*WEARABLE*/
#ifdef TV
#include "tct-dali-core-core_tv.h"
#endif /*TV*/
#ifdef TIZENIOT	//Starts TIZENIOT
#include "tct-dali-core-core_tizeniot.h"
#endif  //TIZENIOT	//End TIZENIOT


int gArgc;
char ** gArgv;
int test_return_value;

int main(int argc, const char *argv[])
{
    int result = -1;
    int i;
    int smack_mode = 0;
    int byte_size;
    char* encoded_byte;
    unsigned char* byte=NULL;

    static const size_t sz_byte_len = sizeof(size_t);
    static const size_t sz_type = sizeof(int);
    static const size_t sz_keysize = sizeof(size_t);
    static const size_t sz_size = sizeof(size_t);

    gArgc = argc;
    gArgv = (char **)argv;

    if (argc < 2) {
        printf("Usage: %s <testcase name>\n", argv[0]);
        return 2;
    }
    else if (argc > 2) {
      smack_mode = 1;
    }

    char* func_name = (char*)argv[1];

    if (smack_mode) {
        encoded_byte=(char*)argv[3];

        byte=g_base64_decode(encoded_byte,(gsize*)&byte_size);

        size_t byte_len = *((size_t *)byte); byte += sz_byte_len;
        int type = *((int *)byte); byte += sz_type;
        size_t keysize = *((size_t *)byte); byte += sz_keysize;
        char *key = (char *)byte; byte += keysize;
        size_t size = *((size_t *)byte); byte += sz_size;
        void *val = (void *)byte; byte += size;

        func_name = strdup((char *)val);
    }
    
    if(!func_name)
    {
	printf("Testcase name is empty.\n");
	return 2;
    }
    
    //setting gcda file location for coverage
    setenv("GCOV_PREFIX","/tmp",1);
    dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Coverage *.gcda File location set to /tmp/home/abuild/rpmbuild/BUILD/ ", __FUNCTION__, __LINE__);
	
    dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Executing TC Name = %s", __FUNCTION__, __LINE__, func_name);

    for (i = 0; tc_array[i].name; i++) {
        if (!strncmp(func_name, tc_array[i].name, strlen(func_name))) {
			
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup begin", func_name);
            if ( tc_array[i].startup )
			{
				tc_array[i].startup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup end", func_name);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body begin", func_name);
			result = tc_array[i].function();
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body end", func_name);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup begin", func_name);
			if ( tc_array[i].cleanup )
			{
				tc_array[i].cleanup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup end", func_name);

			free(func_name);
			return result;
			}
    }

    dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, func_name);	


    printf("Unknown testcase name: \"%s\"\n", func_name);
    free(func_name);
    return 2;
}
