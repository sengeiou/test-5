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
#ifndef __TCT_PUSH-NATIVE_H__
#define __TCT_PUSH-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_push_service_startup(void);

extern int utc_sppc_push_service_connect_n(void);
extern int utc_sppc_push_service_connect_p(void);
extern int utc_sppc_push_service_register_n(void);
extern int utc_sppc_push_service_register_p(void);
extern int utc_sppc_push_service_get_registration_id_p(void);
extern int utc_sppc_push_service_get_registration_id_n(void);
extern int utc_sppc_push_service_deregister_p(void);
extern int utc_sppc_push_service_deregister_n(void);
extern int utc_sppc_push_service_get_unread_notification_n(void);
extern int utc_sppc_push_service_get_unread_notification_p(void);
extern int utc_sppc_push_service_request_unread_notification_n(void);
extern int utc_sppc_push_service_request_unread_notification_p(void);
extern int utc_sppc_push_service_get_notification_data_n(void);
extern int utc_sppc_push_service_get_notification_data_p(void);
extern int utc_sppc_push_service_get_notification_message_n(void);
extern int utc_sppc_push_service_get_notification_message_p(void);
extern int utc_sppc_push_service_get_notification_time_n(void);
extern int utc_sppc_push_service_get_notification_time_p(void);
extern int utc_sppc_push_service_app_control_to_noti_data_n(void);
extern int utc_sppc_push_service_app_control_to_notification_n(void);
extern int utc_sppc_push_service_get_notification_request_id_n(void);
extern int utc_sppc_push_service_get_notification_request_id_p(void);
extern int utc_sppc_push_service_get_notification_sender_n(void);
extern int utc_sppc_push_service_get_notification_sender_p(void);
extern int utc_sppc_push_service_get_notification_session_info_n(void);
extern int utc_sppc_push_service_get_notification_session_info_p(void);
extern int utc_sppc_push_service_get_notification_type_n(void);
extern int utc_sppc_push_service_get_notification_type_p(void);

testcase tc_array[] = {
	{"utc_sppc_push_service_connect_n",utc_sppc_push_service_connect_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_connect_p",utc_sppc_push_service_connect_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_register_n",utc_sppc_push_service_register_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_register_p",utc_sppc_push_service_register_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_registration_id_p",utc_sppc_push_service_get_registration_id_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_registration_id_n",utc_sppc_push_service_get_registration_id_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_deregister_p",utc_sppc_push_service_deregister_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_deregister_n",utc_sppc_push_service_deregister_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_unread_notification_n",utc_sppc_push_service_get_unread_notification_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_unread_notification_p",utc_sppc_push_service_get_unread_notification_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_request_unread_notification_n",utc_sppc_push_service_request_unread_notification_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_request_unread_notification_p",utc_sppc_push_service_request_unread_notification_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_data_n",utc_sppc_push_service_get_notification_data_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_data_p",utc_sppc_push_service_get_notification_data_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_message_n",utc_sppc_push_service_get_notification_message_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_message_p",utc_sppc_push_service_get_notification_message_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_time_n",utc_sppc_push_service_get_notification_time_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_time_p",utc_sppc_push_service_get_notification_time_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_app_control_to_noti_data_n",utc_sppc_push_service_app_control_to_noti_data_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_app_control_to_notification_n",utc_sppc_push_service_app_control_to_notification_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_request_id_n",utc_sppc_push_service_get_notification_request_id_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_request_id_p",utc_sppc_push_service_get_notification_request_id_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_sender_n",utc_sppc_push_service_get_notification_sender_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_sender_p",utc_sppc_push_service_get_notification_sender_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_session_info_n",utc_sppc_push_service_get_notification_session_info_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_session_info_p",utc_sppc_push_service_get_notification_session_info_p,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_type_n",utc_sppc_push_service_get_notification_type_n,utc_push_service_startup,NULL},
	{"utc_sppc_push_service_get_notification_type_p",utc_sppc_push_service_get_notification_type_p,utc_push_service_startup,NULL},
	{NULL, NULL}
};

#endif // __TCT_PUSH-NATIVE_H__
