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
#ifndef _ITS_EFL_UTIL_COMMON_H_
#define _ITS_EFL_UTIL_COMMON_H_

#include "tct_common.h"

//Add test package related includes here
#include <glib.h>
#include <efl_util.h>
#include <Elementary.h>

/** @addtogroup itc-efl-util
 *  @ingroup itc
 *  @{
 */
 
#define TESTSTRINGSIZE			120*sizeof(char)
#define TIMEOUT					30000
#define API_NAMESPACE			"EFL_UTIL_ITC"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bEflUtilCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of efl_util failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}
#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line: %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}




//Add helper function declarations here

bool g_bEflUtilCreation;

char* EflUtilGetError(int nRet);
bool EflUtilCreateNotificationWindow(Evas_Object **pstWindow);
void EflUtilDeleteWindow(void *pData, Evas_Object *pstWindow, void *pEvent);
void WaitForAsync();
gboolean TimeoutFunction(gpointer data);
char *GetScreenMode(int nMode);
/** @} */
#endif  //_ITS_EFL_UTIL_COMMON_H_
