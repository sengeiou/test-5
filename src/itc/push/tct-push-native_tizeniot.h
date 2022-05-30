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

extern void ITs_push_service_startup(void);
extern void ITs_push_service_cleanup(void);

extern int ITc_push_service_connect_disconnect_p(void);
extern int ITc_push_service_register_deregister_p(void);
extern int ITc_push_service_get_registration_id_p(void);
extern int ITc_push_service_get_notification_data_p(void);
extern int ITc_push_service_get_notification_message_p(void);
extern int ITc_push_service_get_notification_time_p(void);
extern int ITc_push_service_get_notification_sender_p(void);
extern int ITc_push_service_get_notification_session_info_p(void);
extern int ITc_push_service_get_notification_request_id_p(void);
extern int ITc_push_service_get_notification_type_p(void);
extern int ITc_push_service_request_unread_notification_p(void);
extern int ITc_push_service_get_unread_free_notification_p(void);

testcase tc_array[] = {
	{"ITc_push_service_connect_disconnect_p",ITc_push_service_connect_disconnect_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_register_deregister_p",ITc_push_service_register_deregister_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_get_registration_id_p",ITc_push_service_get_registration_id_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_get_notification_data_p",ITc_push_service_get_notification_data_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_get_notification_message_p",ITc_push_service_get_notification_message_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_get_notification_time_p",ITc_push_service_get_notification_time_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_get_notification_sender_p",ITc_push_service_get_notification_sender_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_get_notification_session_info_p",ITc_push_service_get_notification_session_info_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_get_notification_request_id_p",ITc_push_service_get_notification_request_id_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_get_notification_type_p",ITc_push_service_get_notification_type_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_request_unread_notification_p",ITc_push_service_request_unread_notification_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{"ITc_push_service_get_unread_free_notification_p",ITc_push_service_get_unread_free_notification_p,ITs_push_service_startup,ITs_push_service_cleanup},
	{NULL, NULL}
};

#endif // __TCT_PUSH-NATIVE_H__
