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
#ifndef _ITS_CBHM_COMMON_H_
#define _ITS_CBHM_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <cbhm.h>
#include <glib.h>
#include <Elementary.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE			"CBHM_ITC"
#define TIMEOUT_CB					20000
bool g_bCbhmInit;
GMainLoop *g_mainloop;

#define START_TEST {\
	FPRINTF("[Line : %d] Starting test : %s\\n", __LINE__ ,__FUNCTION__);\
	if ( !g_bCbhmInit )\
	{\
		FPRINTF("[Line : %d] [API_NAMESPACE] Precondition of cbhm failed\\n", __LINE__);\
		return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
	g_mainloop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_mainloop);\
	g_main_loop_run(g_mainloop);\
	g_source_remove(nTimeoutId);\
	g_mainloop = NULL;\
}

char *CbhmGetError(int nRet);
gboolean Timeout(gpointer data);

/** @} */
#endif  //_ITS_CBHM_COMMON_H_
