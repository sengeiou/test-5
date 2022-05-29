//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
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
#ifndef _ITS_WATCHFACE_COMMON_H_
#define _ITS_WATCHFACE_COMMON_H_

//Add test package related includes here
#include <stdbool.h>
#include <glib.h>
#include <service_app.h>
#include <dlog.h>
#include <app_control.h>

#include "tct_common.h"
#include <watchface-complication-provider.h>
#include <watchface-editable.h>

/** @addtogroup itc-watchface-complication
*  @ingroup itc
*  @{
*/

bool g_bWatchfaceCreation;
GMainLoop *g_pMainLoop;
int g_nTimeoutId;
bool g_bCallBackHit;
bool g_bCheckerHit;
bool g_bWatchApp;
bool g_bFeatureNotSupported;
bool g_bIsFeatureMismatched;
app_control_h g_hTestControl;
char *g_pszEditableGetName;
char *g_pszEventCmd;
static char g_pszCheckUserData[] = "check_user_data";

#define pszEditableSetName 		"TEST"
#define API_NAMESPACE			"WATCHFACE_ITC"
#define MAXENUMSIZE				50
#define SETENUM					1
#define GETENUM					0
#define FEATURE_WATCH_APP 		"http://tizen.org/feature/watch_app"
#define TIMEOUT_CB				10000

#define SETUP_IS_EDITING_TEST_VAL "SETUP_IS_EDITING_TEST_VAL"
#define SETUP_REPLY_TO_EDITOR_TEST_VAL "SETUP_REPLY_TO_EDITOR_TEST_VAL"
#define SETUP_GET_CONTEXT_TEST_VAL "SETUP_GET_CONTEXT_VAL"

#define EVENT_GET_PROVIDER_ID_TEST_VAL "EVENT_GET_PROVIDER_ID_TEST_VAL"
#define EVENT_GET_COMP_TYPE_TEST_VAL "EVENT_GET_COMP_TYPE_TEST_VAL"
#define EVENT_GET_CONTEXT_TEST_VAL "EVENT_GET_CONTEXT_TEST_VAL"
#define EVENT_GET_EVENT_TYPE_TEST_VAL "EVENT_GET_EVENT_TYPE_TEST_VAL"


#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define CALLBACK_EXIT(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
{\
	if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
}\
}\
	else \
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
	return;\
}\
}

#define CALLBACK_EXIT_CLEANUP(eCompare, eRetVal, API, Error, FreeResource) {\
	if ( eRetVal == eCompare )\
{\
	if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
}\
}\
	else \
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
	FreeResource;\
	return;\
}\
}

#define CALLBACK_CHECK_HANDLE_EXIT(Handle, API) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	return;\
}\
}

#define CALLBACK_CHECK_HANDLE_EXIT_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	FreeResource;\
	return;\
}\
}

#define CHECK_HANDLE(Handle, API) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	return 1;\
}\
}

#define CHECK_HANDLE_EXIT(Handle, API) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
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

#define CHECK_HANDLE_EXIT_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	FreeResource;\
	return 1;\
}\
}

#define PRINT_RESULT_EXIT(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
{\
	if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
}\
}\
	else \
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
	return 1;\
}\
}

#define PRINT_RESULT_EXIT_NORETURN(eCompare, eRetVal, API, Error) {\
	if ( eRetVal == eCompare )\
{\
	if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
}\
}\
	else \
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
	return;\
}\
}

#define PRINT_RESULT_EXIT_CLEANUP(eCompare, eRetVal, API, Error, FreeResource) {\
	if ( eRetVal == eCompare )\
{\
	if ( DEBUG )\
{\
	FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
}\
}\
else \
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
	FreeResource;\
	return 1;\
}\
}

#define ISFEATURE_SUPPORTED_EXIT(eCompare, eRetVal, API) {\
	if ( !g_bWatchApp )\
{\
	if ( eCompare == eRetVal )\
{\
	FPRINTF("[Line:%d][%s] FeatureWatchApp not supported\\n", __LINE__, API_NAMESPACE);\
	g_bFeatureNotSupported = true;\
	return 0;\
}\
	else \
{\
	g_bIsFeatureMismatched = true;\
	FPRINTF("[Line : %d][%s] %s failed due to feature mismatch.\\n", __LINE__, API_NAMESPACE, API);\
	return 1;\
}\
}\
}

#define CALLBACK_ISFEATURE_SUPPORTED_EXIT(eCompare, eRetVal, API) {\
	if ( !g_bWatchApp )\
{\
	if ( eCompare == eRetVal )\
{\
	FPRINTF("[Line:%d][%s] FeatureWatchApp not supported\\n", __LINE__, API_NAMESPACE);\
	g_bFeatureNotSupported = true;\
	return;\
}\
	else \
{\
	g_bIsFeatureMismatched = true;\
	FPRINTF("[Line : %d][%s] %s failed due to feature mismatch.\\n", __LINE__, API_NAMESPACE, API);\
	return;\
}\
}\
}

#define WATCHFACE_COMPLICATION_PROVIDER_REMOVE_UPDATED_REQUESTED_CB_EXIT(PROVIDER_ID, UpdateRequestedCb2, nRet)\
{\
	nRet = watchface_complication_provider_remove_update_requested_cb(PROVIDER_ID, UpdateRequestedCb2);\
	PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_provider_remove_update_requested_cb", WatchfaceComplicationGetError(nRet));\
}

#define WATCHFACE_COMPLICATION_REMOVE_UPDATED_CB_EXIT(hHandle, Callback, nRet)\
{\
	nRet = watchface_complication_remove_updated_cb(hHandle, Callback);\
	PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_remove_updated_cb", WatchfaceComplicationGetError(nRet));\
	nRet = watchface_complication_destroy(hHandle);\
	PRINT_RESULT_NORETURN(nRet, WATCHFACE_COMPLICATION_ERROR_NONE, "watchface_complication_destroy", WatchfaceComplicationGetError(nRet));\
}

char* WatchfaceComplicationGetError(int nRet);
char* AppControlGetError(int nRet);
char* BundleGetError(int nRet);
gboolean TimeoutFunction(gpointer data);
void IterateGmainLoop(void);
void QuitGmainLoop(void);
extern void WatchfaceComplicationProviderSetupGetContextChecker(void);
extern void WatchfaceComplicationProviderSetupReplyToEditorChecker(void);
extern void WatchfaceComplicationProviderSetupIsEditingChecker(void);
extern void WatchfaceComplicationProviderEventGetTypeChecker(void);
extern void WatchfaceComplicationProviderEventGetProviderIdChecker(void);
extern void WatchfaceComplicationProviderEventGetComplicationTypeChecker(void);
extern void WatchfaceComplicationProviderEventGetContextChecker(void);


/** @} */
#endif  //_ITS_watchface_COMMON_H_
