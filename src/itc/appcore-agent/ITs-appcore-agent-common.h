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
#ifndef _ITS_APPCORE_AGENT_COMMON_H_
#define _ITS_APPCORE_AGENT_COMMON_H_

#include "assert.h"
#include "tct_common.h"
#include <service_app.h>
#include <sys/time.h>
#include <signal.h>
#include <Ecore.h>
#include <glib-object.h>
#include <glib-2.0/glib.h>

/** @addtogroup itc-appcore-agent
*  @ingroup itc
*  @{
*/
#define TIMELOG				20
#define API_NAMESPACE		"APPCORE_AGENT_ITC"
//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define normal_exit(result) do { \
		g_result = result; \
		service_app_exit(); \
	} while (0)

int g_result;
int g_argc;
char* g_argv;

char* AppcoreAgentGetError(int nRet);
/** @} */
#endif  //_ITS_APPCORE_AGENT_COMMON_H_
