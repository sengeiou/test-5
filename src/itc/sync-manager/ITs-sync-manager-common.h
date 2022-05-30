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
#ifndef _ITS_SYNC_MANAGER_COMMON_H_
#define _ITS_SYNC_MANAGER_COMMON_H_

#include "tct_common.h"
#include "assert.h"
#include <bundle.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Add test package related includes here
#include <sync_manager.h>
#include <sync_adapter.h>
#include <sync-error.h>
#include <glib.h>
#include <glib-object.h>
#include <Ecore.h>

/** @addtogroup itc-sync-manager
*  @ingroup itc
*  @{
*/

//Add global variables here
bool g_bSyncManagerInit;
account_h g_hAccount;
bundle *g_pBundle;
int g_nAccId;
bool g_bCallbackHit;
GMainLoop *g_pSyncManagerMainLoop;
bool g_bSetupReady;
bool g_bIsSyncFeatureSupported;

//Add Macros here
#define API_NAMESPACE			"SYNC_MANAGER_ITC"
#define TIMEOUT					10000
#define AAPID					"native-sync-manager-itc"
#define SYNCJOBNAME				"syncjob"
#define BUNDLEKEY				"str"
#define BUNDLEVALUE				"String user_data sample."
#define SYNC_FEATURE			"http://tizen.org/feature/account.sync"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bSyncManagerInit )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of dlog failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

//Add CallBack function declarations here
bool SyncAdapterStartCallback(account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data);
void SyncAdapterCancelCallback(account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data);

//Add helper function declarations here
char* SyncManagerGetError(int nRet);
void WaitForAsync(void);
gboolean TimeoutFunction(gpointer data);
bool CreateAccount(void);
bool DeleteAccount(void);
bool CreateBundle(void);
bool DeleteBundle(void);
bool CreateSetup(void);
bool DestroySetup(void);

/** @} */
#endif  //_ITS_SYNC_MANAGER_COMMON_H_
