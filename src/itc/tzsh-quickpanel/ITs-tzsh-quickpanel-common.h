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
#ifndef _ITS_TZSH_QUICKPANEL_COMMON_H_
#define _ITS_TZSH_QUICKPANEL_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <tzsh_quickpanel.h>
#include <Elementary.h>
#include <pthread.h>
#include <glib.h>
#include <app.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

//Add helper function declarations here

#define API_NAMESPACE				"TZSH_QUICKPANEL_ITC"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	FreeResource;\
	return 1;\
}\
}

char* TzshQuickpanelGetError(int nRet);
Evas_Object* CreateWindow(const char *name);
void DeleteWin(void *data, Evas_Object *obj, void *event);

/** @} */
#endif  //_ITS_TZSH_QUICKPANEL_COMMON_H_
