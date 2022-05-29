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
#ifndef _ITS_IOTCON_COMMON_H_
#define _ITS_IOTCON_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include "assert.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <dlog.h>
#include <iotcon.h>
#include <net_connection.h>

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/
#define TIMEOUT_CB					5000
#define API_NAMESPACE				"IOTCON_SERVICE_ITC"
#define ICL_OPTIONID_MIN 			2048
#define GMAINTIMEOUT				30000
#define REPRESENTATION_KEY          "key"
#define REP_NTH_CHILD          		1
#define IOTCON_TIMEOUT				10
#define LITE_RESOURCE_BR            "brightness"
#define KEY							"key"
#define VALUE						"value"
#define REMOTE_RESOURCE				"core.led"
#define LIGHT_RESOURCE              "core.light"
#define LIGHT_RESOURCE2             "core.light2"
#define REMOTE_IP					"coap://11.22.33.44"
#define REMOTE_RESOURCE_LED			"/a/led"
#define REMOTE_RESOURCE_LIGHT       "/a/light"
#define VAL1						0
#define VAL2						1
#define VAL3						2
#define VAL4						3
#define ASSIGNVAL1					10
#define ASSIGNVAL2					20
#define ASSIGNVAL3					30
#define IOTCON_FEATURE		    	"http://tizen.org/feature/iot.ocf"
#define WIFI_FEATURE		    	"http://tizen.org/feature/network.wifi"
#define ETHERNET_FEATURE	    	"http://tizen.org/feature/network.ethernet"

#define LOCAL_HOST_ADDRESS "127.0.0.1"
#define LIGHT_RESOURCE_TYPE "core.light"
#define LIGHT_RESOURCE_TYPE2 "core.light2"
#define LIGHT_RESOURCE_TYPE3 "core.light3"
#define LIGHT_RESOURCE_URI "/a/light"
#define LED_RESOURCE_TYPE "core.led"
#define LED_RESOURCE_URI "/a/led"
#define PRESENCE_INTERVAL 10
#define TIMEOUT_COUNT_MAX 3

bool g_CallBackHit;
int g_nTimeoutId;
bool g_bIotconConnect;
bool g_bResCallback;
int g_nBrightness;
iotcon_lite_resource_h g_hLiteLightResource;
bool g_bCheckCb;
int g_nCheckAPICb;
bool g_nGetCb, g_nPutCb, g_nPostCb, g_nDeleteCb;
bool g_bCheckOnObserveCb, g_bCheckOnResponseCb, g_bCheckFoundResourceCb;
bool g_bFeatureUnsupported;
GMainLoop *g_pMainLoop;
char *g_ipv4_address;
bool g_bFeatureWifi;
bool g_bFeatureEthernet;
connection_h g_conn_h;

gboolean TimeoutFunction(gpointer data);
int icitc_send_ok_response(iotcon_request_h request);

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if(g_bFeatureUnsupported)\
	{\
		FPRINTF("[Line : %d][%s] Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( !g_bIotconConnect )\
	{\
		FPRINTF("[Line : %d][%s] Iotcon connection failed , Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define CALLBACK_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bResCallback )\
	{\
		FPRINTF("[Line : %d][%s] Iotcon connection failed , Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}
#define START_TEST_SERVICE{\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}


#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nIotconTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nIotconTimeoutId);\
	g_pMainLoop = NULL;\
}

#define PROPERTY_VALUE(api, pstValue) {\
	if (IOTCON_ERROR_NONE != nRet)\
	{\
		FPRINTF("[Line : %d][%s] %s failed. error returned = %s \\n", __LINE__, API_NAMESPACE, api, IotConGetError(nRet));\
	}\
	if ( pstValue == NULL)\
	{\
		FPRINTF("[Line : %d][%s] %s failed. property returned NULL value\\n", __LINE__, API_NAMESPACE, api);\
		return;\
	}\
	else\
	{\
		FPRINTF("[Line : %d][%s] %s Success. property value is: %s\\n", __LINE__, API_NAMESPACE, api, pstValue);\
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

char *IotConGetError(int nRet);
gboolean IotConsCallbackTimeout(gpointer data);
void IotconDestroyLiteResource(void);
int IotconCreateLiteResource(void);
int ic_get_svr_db_path(char **path);
void icitc_get_client_ipv4_address(void);
void icitc_free_client_ipv4_address(void);

/** @} */
#endif  //_ITS_IOTCON_COMMON_H_
