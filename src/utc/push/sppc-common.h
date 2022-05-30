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
#ifndef __SPPC_COMMON_H__
#define __SPPC_COMMON_H__

#include <dlog.h>
#include "tct_common.h"
#include <net_connection.h>

#define API_NAMESPACE	"PUSH_UTC"
#define _PUSH_SAFE_FREE(p) do{if(p){free(p);p=NULL;}}while(0)
#define _LOG(fmt, args...) { \
	dlog_print (DLOG_INFO, "core-push-tests", "[%s:%d] "fmt"\n", __func__, __LINE__, ##args); \
}

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

int SendPushDataToServer(const char *push_app_id, const char *app_secret, const char *reg_id, const char *request_id,
					const char *app_data, int app_data_size, const char *alert_message, push_action_e action,
					push_badge_option_e badge_option, int badge_number, long time_stamp, int type, int delay,
					const char *sender, bool verbose);
int GetAppId(char **app_id);
int GetAppSecret(char **app_secret);

#endif
