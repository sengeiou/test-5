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
#include "tct_common.h"

#ifdef MOBILE	//Starts MOBILE
#include "tct-vulkan-native_mobile.h"
#endif  //MOBILE	//End MOBILE

#ifdef WEARABLE	//Starts WEARABLE
#include "tct-vulkan-native_wearable.h"
#endif  //WEARABLE	//End WEARABLE

#ifdef TV	//Starts TV
#include "tct-vulkan-native_tv.h"
#endif  //TV	//End TV

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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include <SDL.h>

int
SDL_main(int argc, char *argv[])
{
    Uint8 done = 0;
    SDL_Event event;
    SDL_SetMainReady();

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

    if (argc < 2) {
        printf("Usage: %s <testcase name>\n", argv[0]);
        PRINT_TC_RESULT("%d", result=2);
        return result;
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
        PRINT_TC_RESULT("%d", result=2);
	return result;
    }

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s", SDL_GetError());

    PRINT_TC_RESULT("%d", result=-1);
	FREE_MEMORY_TC(func_name);
    return result;
    }

    for(i = 0; tc_array[i].name; i++){
        if (!strncmp(func_name, tc_array[i].name, strlen(func_name))) {
               dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup begin", func_name);
            if ( tc_array[i].startup )
            {
                tc_array[i].startup();
            }
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup end", func_name);

            dlog_print(DLOG_INFO, "NativeTCT", "%s : Body begin", func_name);
            result = tc_array[i].function();
            dlog_print(DLOG_INFO, "NativeTCT", "result : %d", result);
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body end", func_name);
			
            dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup begin", func_name);
            if ( tc_array[i].cleanup )
            {
                tc_array[i].cleanup();
            }
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup end", func_name);

            dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is Terminated", __FUNCTION__, __LINE__);
            PRINT_TC_RESULT("%d", result);

            FREE_MEMORY_TC(func_name);
//            SDL_Quit();

	        return result;
        }
    }

    dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, func_name);

    printf("Unknown testcase name: \"%s\"\n", func_name);
    PRINT_TC_RESULT("%d", result=2);

    FREE_MEMORY_TC(func_name);

    return result;
}

