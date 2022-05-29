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
#ifndef _ITS_COMP_BASED_APP_COMMON_H_
#define _ITS_COMP_BASED_APP_COMMON_H_

#include "tct_common.h"
#include "tct_app_common.h"
#include <string.h>

//Add test package related includes here
#include <app.h>
#include <app_manager.h>
#include <component_based_app.h>
#include <component_manager.h>
#include <app_control.h>

/** @addtogroup itc-component-based-app
*  @ingroup itc
*  @{
*/
#define TEST_HELLOWORLD_APPID		"org.tizen.helloworld"
#define TEST_COMPONENTBASED_APPID	"org.example.componentbased"
#define TEST_SERVICE_COMP_ID		"service_comp_test"
#define TEST_FRAME_COMP_ID		"frame_comp_test"
#define TEST_COMP_EXTRA_KEY		"component_itc_func"
#define API_NAMESPACE			"COMP_BASED_APP_ITC"

#define TIZEN_FEATURE_SCREEN   "http://tizen.org/feature/screen"
#define START_TEST		FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

//Add helper function declarations here
char* AppGetError(int nRet);
char* AppControlGetError(int nRet);
char* CompManagerAppGetError(int nRet);
char* AppControlGetResult(int nRet);

int AppControlSend(const char *pszAppID, const char *pszCompID, const char *pszExtraData);
int AppControlSendAsync(const char *pszAppID, const char *pszCompID, const char *pszExtraData);

/** @} */
#endif  //_ITS_COMP_BASED_APP_COMMON_H_
