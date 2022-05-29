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
#ifndef _ITS_YACA_COMMON_H_
#define _ITS_YACA_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <glib.h>
#include <fcntl.h>
#include <system_info.h>
#include <yaca_crypto.h>
#include <yaca_error.h>
#include <yaca_key.h>
#include <yaca_sign.h>
#include <yaca_digest.h>
#include <yaca_simple.h>
#include <yaca_encrypt.h>
#include <yaca_seal.h>
#include <yaca_rsa.h>
#include <yaca_types.h>

#define API_NAMESPACE			"YACA_ITC"
#define MICROSECONDS_PER_SECOND	1000000
#define MINCOUNT				1
#define TIMEOUT_CB				30000


GMainLoop *g_pYacaMainLoop;
bool g_bFeatureUnsupported;
bool g_bYacaInit;
bool g_bCallbackHit;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bYacaInit )\
{\
	FPRINTF("[Line : %d][%s] Precondition of http failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	FreeResource;\
	return 1;\
}\
}

#define RUN_POLLING_LOOP {\
	if ( !g_bCallbackHit )\
{\
	g_pYacaMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, yacaTimeout, g_pYacaMainLoop);\
	g_main_loop_run(g_pYacaMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pYacaMainLoop = NULL;\
}\
}

#define TEST_MEM_SIZE 512

/**
 * Test strings, sizes include null-termination
 */
extern const char lorem8[];
extern const char lorem16[];
extern const char lorem1024[];
extern const char lorem4096[];

/**
 * Sizes of test strings
 */
#define LOREM8_SIZE ((size_t)8)
#define LOREM16_SIZE ((size_t)16)
#define LOREM1024_SIZE ((size_t)1024)
#define LOREM4096_SIZE ((size_t)4096)

/** @addtogroup itc-yaca
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

gboolean yacaTimeout(gpointer data);
char* YacaGetError(int nRet);

/** @} */
#endif  //_ITS_YACA_COMMON_H_
