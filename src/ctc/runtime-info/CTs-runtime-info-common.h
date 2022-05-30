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
#ifndef _CTS_RUNTIME_INFO_COMMON_H_
#define _CTS_RUNTIME_INFO_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <runtime_info.h>

/** @addtogroup ctc-runtime-info
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE			"RUNTIME_INFO_CTC"
#define	USER_DATA				"user data"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define PRINT_KEY_STATUS(Variable, KEY) {\
if (g_bRuntimeKeyNotSupported)\
{\
	FPRINTF("[Line : %d][%s] %s Key is not supported\\n", __LINE__, API_NAMESPACE, KEY);\
}\
else if ( Variable )\
{\
	FPRINTF("[Line : %d][%s] %s Key is Enabled\\n", __LINE__, API_NAMESPACE, KEY);\
}\
else\
{\
	FPRINTF("[Line : %d][%s] %s Key is Disabled\\n", __LINE__, API_NAMESPACE, KEY);\
}\
return 0;\
}

bool g_bRuntimeKeyState;
bool g_bRuntimeKeyNotSupported;

//Add helper function declarations here

char* RuntimeGetError(int nResult);
bool RuntimeGetSystemState(runtime_info_key_e eRuntimeInfoKey);

/** @} */ //end of ctc-runtime-info

#endif //_CTS_RUNTIME_INFO_COMMON_H_
