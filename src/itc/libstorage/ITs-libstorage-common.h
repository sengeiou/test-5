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
#ifndef _ITS_LIBSTORAGE_COMMON_H_
#define _ITS_LIBSTORAGE_COMMON_H_

#include "tct_common.h"

#include <storage.h>
#include <glib-2.0/glib.h>
#include <pthread.h>

/** @addtogroup itc-libstorage
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE       "LIBSTORAGE_ITC"

//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

/*
#define CHECK_CALLBACK_STATUS(szApiName, nErrorCount) {\
int nTimeoutId = g_timeout_add(10000, TimeoutFunction, g_pMainLoop);\
g_main_loop_run(g_pMainLoop);\
g_source_remove(nTimeoutId);\
if ( g_bLibStorageCallbackHit == false )\
{\
FPRINTF("[Line : %d][%s] After %s, callback has not been invoked. Iteration %d\\n", __LINE__, API_NAMESPACE, szApiName, nLoopCount);\
nErrorCount++;\
continue;\
}\
else if ( g_bLibStorageCallbackResultValid == false )\
{\
FPRINTF("[Line : %d][%s] After %s, callback having invalid values. Iteration %d\\n", __LINE__, API_NAMESPACE, szApiName, nLoopCount);\
nErrorCount++;\
continue;\
}\
else\
{\
g_bLibStorageCallbackHit = false;\
}\
}
*/

char* StorageGetError(storage_error_e nRet);
char* StorageGetType(storage_type_e nType);
char* StorageGetDirectory(storage_directory_e nType);
char* StorageGetState(storage_state_e nState);
/** @} */
#endif  //_ITS_LIBSTORAGE_COMMON_H_
