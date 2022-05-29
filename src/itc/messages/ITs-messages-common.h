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
#ifndef _ITS_MESSAGES_COMMON_H_
#define _ITS_MESSAGES_COMMON_H_

#include "tct_common.h"
//#include <msg.h>
//#include <msg_transport.h>
//#include <msg_storage.h>
#include <messages.h>
#include <messages_types.h>
#include <app.h>
#include <glib.h>

/** @addtogroup itc-messages
* @ingroup		itc
* @{
*/

#define ADD_PORT					2
#define PATH_LEN					1024
#define TIMEOUT_CB 					30000
#define PUSH_TEST_APP_ID 			"TEST_APP_ID"
#define PUSH_TEST_CONTENT_TYPE 		"text/vnd.wap.connectivity-xml"

#define API_NAMESPACE				"MESSAGES_ITC"
#define TELEPHONY_FEATURE  			"http://tizen.org/feature/network.telephony.sms"
#define TELEPHONY_FEATURE_TELEPHONY		"http://tizen.org/feature/network.telephony"
#define TELEPHONY_FEATURE_MMS  		"http://tizen.org/feature/network.telephony.mms"
#define MESSAGES_IMAGE_FILE     	"Image.jpg"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureMismatch )\
{\
	return 1;\
}\
	if ( g_bFeatureNotSupported )\
{\
	return 0;\
}\
	if ( !g_bMessageService || !g_bMessagesCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of mesages create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
} 

#define START_TEST_MMS {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureMismatchMms )\
{\
	return 1;\
}\
	if ( g_bFeatureNotSupportedMms )\
{\
	return 0;\
}\
	if ( !g_bMessageServiceMms )\
{\
	FPRINTF("[Line : %d][%s] Precondition of mesages open service failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
} 

#define RUN_POLLING_LOOP {\
	if ( g_bMessagesCB == false )\
{\
	g_loop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, MessagesTimeout, g_loop);\
	g_main_loop_run(g_loop);\
	g_source_remove(nTimeoutId);\
	g_loop = NULL;\
}\
}

GMainLoop *g_loop;
bool g_bIsTelephonyFeatureSupported;
bool g_bIsTelephonyFeatureTelephonySupported;
bool g_bIsTelephonyFeatureMmsSupported;

char* MessagesGetError(int nRet);
gboolean MessagesTimeout(gpointer data);
bool MessagesAppendToAppDataPath(char* pInputPath, char* pFinalPath);
bool MessagesGetDataPath(char* pPath);

/** @} */ //end of itc-messages

#endif  //_ITS_MESSAGES_COMMON_H_
