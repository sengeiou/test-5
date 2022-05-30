//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#ifndef _ITS_COMPONENT_MANAGER_COMMON_H_
#define _ITS_COMPONENT_MANAGER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <fcntl.h>
#include <dlog.h>
#include <component_manager.h>
#include "tct_app_common.h"
#include <glib.h>
#include <glib-object.h>
/** @addtogroup itc-component-manager
*  @ingroup itc
*  @{
*/

bool g_bComponentManagerCreation;

#define API_NAMESPACE			"COMPONENT_MANAGER_ITC"
#define MAXENUMSIZE				50
#define SETENUM					1
#define GETENUM					0


#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bComponentManagerCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of Component-manager failed so leaving test\\n", __LINE__, API_NAMESPACE);\
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

char* ComponentManagerGetError(component_manager_error_e error);
typedef bool (*common_do_cb)(void *user_data);
int AppControlCommonLaunchRequest(const char *app_id, const char *component_id, const char *extra);
bool CommonWaitUntilDone(common_do_cb callback, void *user_data);




/** @} */
#endif  //_ITS_COMPONENT_MANAGER_COMMON_H_
