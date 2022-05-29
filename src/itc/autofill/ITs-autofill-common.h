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
#ifndef _ITS_AUTOFILL_COMMON_H_
#define _ITS_AUTOFILL_COMMON_H_

#include "tct_common.h"
#include "tct_app_common.h"

#include <glib.h>
#include <glib-object.h>
#include <string.h>

//Add test package related includes here

#include <app.h>
#include <autofill.h>
#include <autofill_common.h>
#include <autofill_error.h>
#include <autofill_service.h>
#include <app_common.h>

/** @addtogroup itc-app-manager
*  @ingroup itc
*  @{
*/
static bool g_bCallBackHit;
static char* g_pszId = "id";
static char* g_pszLabel = "label";
static char *g_pszServiceMessage = "Login with Tizen autofill service";
static char *g_pszPresentationText = "tester1";
static char *g_pszViewId = "login";
static char *g_pszAppId = "org.tizen.autofill-test";
static char *g_pszValue = "test";
static char *g_pszServiceName = "Tizen autofill service";
static bool g_bAuthenticationNeeded = true;
static bool g_bAutofillDataPresent = true;
static bool g_bSensitive = false;
static bool g_bAutofillServiceCreation = false;
static GMainLoop *g_mainloop = NULL;


#define API_NAMESPACE				"AUTOFILL_ITC"
#define TIMEOUT_CB					10000
#define VIEW_ID "login"
#define PATH_LEN					1024

//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define START_TEST_CHECK_INITIALIZE {\
	FPRINTF("[Line:%d][%s] Starting test check initialize : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bAutofillServiceCreation ) {\
		FPRINTF("[Line:%d][%s] Precondition Failed.\\n", __LINE__, API_NAMESPACE);\
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

char* AutofillGetError(autofill_error_e nRet);
bool ApplicationGetDataPath(char* pPath); // this function outputs tha application data path

/** @} */
#endif  //_ITS_AUTOFILL_COMMON_H_
