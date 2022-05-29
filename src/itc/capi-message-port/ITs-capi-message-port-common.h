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
#ifndef _ITS_MESSAGE_PORT_COMMON_H_
#define _ITS_MESSAGE_PORT_COMMON_H_

#include "tct_common.h"
#include "tct_app_common.h"
#include <message_port.h>
#include <app_manager.h>
#include <stdlib.h>
#include <app.h>
#include <glib.h>

/** @addtogroup itc-message-port
* @ingroup		itc
* @{
*/

#define API_NAMESPACE					"MESSAGE_PORT_ITC"
#define COUNTER 						30
#define TIMEOUT_CB						20000
#define TEST_MESSAGEPORT_APPID			"org.tizen.messageportapp"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define START_TEST_REMOTE {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bMessagePort )\
	{\
	FPRINTF("[Line : %d][%s] Precondition for Remote Application failed \\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}
#define RUN_POLLING_LOOP {\
	g_pMessagePortMainLoop = g_main_loop_new(NULL, false);\
	messageport_timeout_id = g_timeout_add(TIMEOUT_CB, timeout_func, g_pMessagePortMainLoop);\
	g_main_loop_run(g_pMessagePortMainLoop);\
	g_source_remove(messageport_timeout_id);\
	g_pMessagePortMainLoop = NULL;\
}
static const int g_nLocalPortId = 1;
static const char g_szLocalPort[] = "my_test_local_port";
static const char g_szRemotePort[] = "my_test_remote_port";
static const char g_szRemoteAppId[] = "org.tizen.messageportapp";

static const char g_szTerminatedRemoteAppId[]= "org.tizen.messageportapp3";

GMainLoop *g_pMessagePortMainLoop;

//Add helper function declarations here

char* MessagePortGetError(int nRet);
char* AppControlGetError(int nRet);
bool LaunchAppToSendMsg(const char *pszRemoteAppId);
void TerminateSendToApp();

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) //Starts MOBILE or WEARABLE or TIZENIOT
static gboolean timeout_func(gpointer data);
#endif  // End MOBILE or WEARABLE or TIZENIOT

#ifdef TV	//Starts TV
gboolean TimeoutFunction(gpointer data);
#endif  //TV	//End TV

void reply_cb(app_control_h request, app_control_h reply, app_control_result_e result, void *user_data);
/** @} */ //end of itc-message-port

#endif  //_ITS_MESSAGE_PORT_COMMON_H_
