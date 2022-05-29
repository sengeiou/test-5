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
#ifndef _ITS_PACKAGE_MANAGER_COMMON_H_
#define _ITS_PACKAGE_MANAGER_COMMON_H_

#include "tct_common.h"
#include "tct_app_common.h"

//Add test package related includes here

#include <package_manager.h>
#include <package_archive_info.h>
#include <pthread.h>
#include <glib.h>
#include <app.h>

/** @addtogroup itc-package-manager
*  @ingroup itc
*  @{
*/

//Add helper function declarations here
#define LOG				100
#define MICROSECONDS_PER_SECOND		1000000
#define TIMEOUT_CB			60000
#define SLEEP_TIME			5
#define PATH_LEN			1024
#define USER_DATA			NULL
#define FILTER_PROPERTY			"PMINFO_PKGINFO_PROP_PACKAGE_UPDATE"
#define API_NAMESPACE			"PACKAGE_MANAGER_ITC"

#define TEST_NATIVETESTAPP_APPID	"native-testapp-itc"
#define TEST_TESTAPP_APPID		"org.tizen.testapp"
#define TEST_SAMPLE_TESTAPP_APPID	"org.example.sampletpk"
#define TEST_HELLO_WORLDAPP_APPID	"org.tizen.helloworld"
#define TEST_HELLO_WORLD2APP_APPID	"org.tizen.helloworld2"

#define TEST_TESTAPP_NAME	"org.tizen.testapp-1.0.0-arm.tpk"
#define TESTAPP_API_VESION	"2.4"
#define TESTAPP_AUTHOR_NAME	"Test"
#define TESTAPP_API_DESCRIPTION	"This is test description."
#define TESTAPP_LABEL_NAME	"testapp"
#define TESTAPP_PACKAGE_ID	"org.tizen.testapp"
#define TESTAPP_TYPE		"tpk"
#define TESTAPP_VERSION		"1.0.0"

#define TEST_TESTAPP_SAMPLE_NAME	"org.example.sampletpk.tpk"
#define TESTAPP_SAMPLE_AUTHOR_NAME	"Test"
#define TESTAPP_SAMPLE_API_DESCRIPTION	"This is test description."


#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bPackageManagerCreation )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of Package-Manager create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
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

#define RUN_POLLING_LOOP {\
	g_pPacakageManagerMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pPacakageManagerMainLoop);\
	g_main_loop_run(g_pPacakageManagerMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pPacakageManagerMainLoop = NULL;\
}

bool g_bCallbackHit;
bool g_bCallbackReturnValue;
bool g_bEventTypeInstall;
package_manager_h g_hAppfwPackageManagerHandler;
bool g_bPackageManagerCreation;
GMainLoop *g_pPacakageManagerMainLoop;
package_size_info_h g_hSizeInfo;

char* PackageManagerGetError(int nRet);
char* PackageManagerGetEnum(int nRet);
char* PackageManagerGetEnumForComponent(int nRet);
gboolean Timeout(gpointer data);
/** @} */
#endif  //_ITS_PACKAGE_MANAGER_COMMON_H_
