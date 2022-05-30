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
#ifndef _ITS_ACCOUNTS_SVC_COMMON_H_
#define _ITS_ACCOUNTS_SVC_COMMON_H_

/************************** Headers **********************************************/
#include "tct_common.h"
#include <pthread.h>
#include <account.h>
#include <glib.h>
#include <app.h>
#include <system_info.h>

/************************************************************************/
/** @addtogroup itc-accounts-svc
*  @ingroup itc
*  @{
*/
typedef enum {
	_PROFILE_UNKNOWN = 0,
	_PROFILE_MOBILE = 0x1,
	_PROFILE_WEARABLE = 0x2,
	_PROFILE_TV = 0x4,
	_PROFILE_IVI = 0x8,
	_PROFILE_COMMON = 0x10,
} tizen_profile_t;

#define API_NAMESPACE			"ACCOUNTS_SVC_ITC"
#define ICONPATH			"icontexto_256.png"
#define SERVICEPROID			"http://tizen.org/account/capability/contact"
#define TIMEOUT_CB			10000
#define ACCESSTOKEN			"access-token"
#define APPID				"native.accounts-svc-itc"
#define EMAILID				"TCTSampleAccount@tizen.org"
#define USERNAME			"TizenLite Test"
#define PATH_LEN			1024
#define BUFFERSIZE			256
#define BUFFER				20
#define CALENDAR_CAPABILITY		"http://tizen.org/account/capability/calendar"
#define CONTACT_CAPABILITY		"http://tizen.org/account/capability/contact"
#define ACCOUNT_ICON_PATH		"/shared/res/account.png"
#define ACCOUNT_SMALL_ICON_PATH 	"/shared/res/account_small.png"
#define SERVICE_PROVIDER_ID		"http://www.tizen.org/"
#define MULTIPLE_ACCOUNT_SUPPORT	1
#define RPM_INSTALL_LOCATION		"/usr/apps/native-accounts-svc-itc"
#define TPK_APP_PREFIX			"org.tizen."
#define ACCOUNT_FEATURE			"http://tizen.org/feature/account"

#define START_TEST {\
	FPRINTF("\\n[Line : %d][%s] Starting test : %s\\n",__LINE__, API_NAMESPACE,__FUNCTION__);\
	if(g_bAccountNotSupported)\
	{\
		FPRINTF("[Line : %d][%s] Feature =%s  not supported	 :success ", __LINE__, API_NAMESPACE, ACCOUNT_FEATURE);\
		return 0;\
	}\
	else if (g_bAccountMismatch)\
	{\
		FPRINTF("[Line : %d][%s] Precondition of Account Creation feature=%s:Mismatch,failure  ", __LINE__, API_NAMESPACE, ACCOUNT_FEATURE);\
		return 1;\
	}\
	if (!g_bAccountCreation)\
	{\
	FPRINTF("\\n[Line : %d][%s] Precondition of Account Creation failed\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}
#define RUN_POLLING_LOOP {\
	mainloop = g_main_loop_new(NULL, false);\
	nAccountTimeoutId = g_timeout_add(TIMEOUT_CB, AccountTimeout, mainloop);\
	g_main_loop_run(mainloop);\
	g_source_remove(nAccountTimeoutId);\
	mainloop = NULL;\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

/* Accessing system info */
int system_info_get_platform_string(const char *key, char **value);

/*********************** Global Variables *******************************/

bool g_bAccountLabelCB;
bool g_bAccountNotSupported;
bool g_bAccountMismatch;

/************************************************************************/

/*********************** Global Functions *******************************/

// Gets Error Msg
char* AccManagerGetErrorMSG(int nRet);
char* AccountGetSecret(int nRet);
char* AccountGetCapabilityState(int nRet);
char* AccountGetAuthType(int nRet);
char* AccountGetSyncState(int nRet);
bool AccManagerAppendToAppDataPath(char* pInputPath, char* pFinalPath);
bool AccManagerGetDataPath(char* pAppDataPath);
char* AppGetError(int nRet);
/************************************************************************/
/** @} */
#endif  //_ITS_ACCOUNTS_SVC_COMMON_H_
