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
#ifndef _ITS_TTRACE_COMMON_H_
#define _ITS_TTRACE_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <trace.h>

/** @addtogroup itc-ttrace
*  @ingroup itc
*  @{
*/

//Add test package related defines here
#define API_NAMESPACE			"TTRACE_ITC"
#define TRACECOMMAND			"TestTrace"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bTTraceCreation )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of ttrace failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define CHECK_TRACE_RESULT(eCompare, API) {\
	g_nRet = get_last_result();\
	PRINT_RESULT(eCompare, g_nRet, API, TTraceGetError(g_nRet));\
}

//Add test package related global variables here
bool g_bTTraceCreation;
int g_nRet;

//Add helper function declarations here
char* TTraceGetError(int nRet);


/** @} */
#endif  //_ITS_TTRACE_COMMON_H_
