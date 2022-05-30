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
#ifndef _ITS_RUNTIME_INFO_COMMON_H_
#define _ITS_RUNTIME_INFO_COMMON_H_

#include "tct_common.h"
#include "runtime_info.h"
#include <app.h>

/** @addtogroup itc-runtime-info
*  @ingroup itc
*  @{
*/

#define LOG							100
#define API_NAMESPACE				"RUNTIME_INFO_ITC"
#define PATH_LEN					1024


#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

//Add helper function declarations here

char* RuntimeInfoGetError(int nRet);
char* RuntimeGetKeyString(int nRet);
bool RuntimeInfoGetDataPath(char* pPath); // this function outputs tha application data path
bool RuntimeInfoAppendToAppDataPath(char* pInputPath, char* pFinalPath); // this function appends the input string to app data path and outputs the final resultant path

/** @} */

#endif  //_ITS_RUNTIME_INFO_COMMON_H_
