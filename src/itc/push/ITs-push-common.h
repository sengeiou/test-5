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
#ifndef _ITS_PUSH_COMMON_H_
#define _ITS_PUSH_COMMON_H_

#include "tct_common.h"

//Add test package related includes here

#include <push-service.h>
#include <app.h>
#include <pthread.h>
#include <glib.h>
//#include <aul.h>
#include <system_info.h>

// For the sending feature
#include <json-glib/json-glib.h>
#include <curl/curl.h>
#include <net_connection.h>

/** @addtogroup itc-push
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE							"PUSH_ITC"
#define APP_DATA_MAX_SIZE						4096
#define MAX_BODY_LENGTH							APP_DATA_MAX_SIZE + 500

//Add helper function declarations here
#ifdef TV
#define SLEEP_TIME					10
#else
#define SLEEP_TIME					5
#endif

#define TIMEOUT_CB					90000
#define PUSH_FEATURE				"http://tizen.org/feature/network.push"

typedef enum {
	PUSH_ACTION_DISCARD = 0,
	PUSH_ACTION_ALERT,
	PUSH_ACTION_SILENT,
	PUSH_ACTION_LAUNCH,
} push_action_e;

typedef enum {
	PUSH_BADGE_OPTION_MAINTAIN = 0,
	PUSH_BADGE_OPTION_NONE = 0,
	PUSH_BADGE_OPTION_INCREASE,
	PUSH_BADGE_OPTION_DECREASE,
	PUSH_BADGE_OPTION_SET,
} push_badge_option_e;

bool g_bStateCallbackHit;
bool g_bNotifyCallbackHit;
bool g_bRegisteredState;
bool g_bCallbackReturnValue;
bool g_bCallbackHit;
GMainLoop *g_pPushMainLoop;
bool g_bIsPushFeatureSupported;

#define START_TEST {\
	FPRINTF( "[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define RUN_POLLING_LOOP {\
	g_pPushMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pPushMainLoop);\
	g_main_loop_run(g_pPushMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pPushMainLoop = NULL;\
}

typedef struct outgoing_notification_s {
	const char *app_id;
	const char *app_secret;
	const char *reg_id;
	const char *request_id;
	const char *sender;
	const char *app_data;
	int app_data_size;
	const char *alert_message;
	push_action_e action;
	push_badge_option_e badge_option;
	int badge_number;
	int type;
	int delay;
	long time_stamp;
	const char *session_info;
} OutgoingNotification;

char* PushServiceGetError(int nRet);
void PushServiceDisconnect();
bool PushServiceConnect(push_service_state_cb pFnCallback);
gboolean Timeout(gpointer data);
int SendPushDataToServer(const char *push_app_id, const char *app_secret, const char *reg_id, const char *request_id,
						 const char *app_data, int app_data_size, const char *alert_message, push_action_e action,
						 push_badge_option_e badge_option, int badge_number, long time_stamp, int type, int delay,
						 const char *sender, bool verbose);
size_t CurlResponseCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
int GetResultFromJson(char* json_string);
bool PushServiceConnectSendDisconnect();
/** @} */
#endif  //_ITS_PUSH_COMMON_H_
