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
#ifndef _ITS_RPC-PORT_COMMON_H_
#define _ITS_RPC-PORT_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <fcntl.h>
#include <dlog.h>
#include <rpc-port.h>
#include <rpc-port-parcel.h>
#include <glib.h>
#include <app.h>

/** @addtogroup itc-rpc-port
*  @ingroup itc
*  @{
*/

bool g_bRpcPortCreation;
static GMainLoop *g_pMainLoop = NULL;


#define API_NAMESPACE			"DLOG_ITC"
#define TIMEOUT_CB				20000
#define PATH_LEN				1024

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bRpcPortCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of rpc-port failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define RUN_POLLING_LOOP {\
	if(g_bCallbackCalled == false)\
	{\
		g_pMainLoop = g_main_loop_new(NULL, false);\
		g_nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pMainLoop);\
		g_main_loop_run(g_pMainLoop);\
		g_source_remove(g_nTimeoutId);\
		g_pMainLoop = NULL;\
	}\
}

int __result;
#define normal_exit(result) do { \
	__result = result; \
	service_app_exit(); \
} while (0)

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

enum Message_method_e {
	Message_METHOD_Result,
	Message_METHOD_Callback,
	Message_METHOD_Send,
};
rpc_port_h g_hReceivedPort;
int g_nTimeoutId;

char* RpcPortGetError(int nRet);
bool g_bCallbackCalled;
bool g_bcallBackDisConnect;
bool g_callbackMsgreceived;
gboolean Timeout(gpointer data);
void GetFilePath(const char *pszFileName, char *pszBuf, unsigned int nSize);
void CreateFile(const char *pszFilePath, const char *pszMessage);

/** @} */
#endif  //_ITS_RPC-PORT_COMMON_H_
