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
#ifndef _ITS_PRIVILEGE_INFO_COMMON_H__
#define _ITS_PRIVILEGE_INFO_COMMON_H__

//Add test package related includes here

#include "tct_common.h"
#include <privilege_information.h>

/** @addtogroup itc-privilege-info
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"PRIVILEGE_INFO_ITC"
#define LOG							100

bool g_bIsPrivilegeInfoInitialized;
bool g_bIsPrivilegePrivacyFeature;
#define START_TEST {\
	FPRINTF("\\n[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bIsPrivilegeInfoInitialized )\
{\
	FPRINTF("\\n[Line : %d][%s] Precondition of key-manager failed so leaving test\\n",__LINE__, API_NAMESPACE);\
	return 1;\
}\
}

char* PrivilegeinfoGetError(int nRet);
/** @} */
#endif  //_ITS_PRIVILEGE_INFO_H_
