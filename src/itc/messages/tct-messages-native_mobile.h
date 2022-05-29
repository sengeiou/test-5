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
#ifndef __TCT_MESSAGES-NATIVE_H__
#define __TCT_MESSAGES-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_messages_mms_startup(void);
extern void ITs_messages_mms_cleanup(void);
extern void ITs_messages_startup(void);
extern void ITs_messages_cleanup(void);

extern int ITc_messages_mms_add_get_attachement_p(void);
extern int ITc_messages_mms_get_attachement_count_p(void);
extern int ITc_messages_mms_set_get_subject_p(void);
extern int ITc_messages_mms_remove_all_attachments_p(void);
extern int ITc_messages_add_get_address_p(void);
extern int ITc_messages_get_mboxType_p(void);
extern int ITc_messages_get_message_count_p(void);
extern int ITc_messages_add_get_sms_listening_port_p(void);
extern int ITc_messages_get_message_type_p(void);
extern int ITc_messages_set_get_text_p(void);
extern int ITc_messages_get_time_p(void);
extern int ITc_messages_set_get_sim_id_p(void);
extern int ITc_messages_push_add_remove_incoming_cb_p(void);
extern int ITc_messages_push_register_deregister_p(void);
extern int ITc_messages_push_reregister_p(void);
extern int ITc_messages_send_message_p(void);
extern int ITc_messages_search_getid_searchbyid_freemessage_p(void);
extern int ITc_messages_foreach_message_p(void);
extern int ITc_messages_add_message_p(void);
extern int ITc_messages_set_mbox_type_p(void);
extern int ITc_messages_set_time_p(void);

testcase tc_array[] = {
	{"ITc_messages_mms_add_get_attachement_p",ITc_messages_mms_add_get_attachement_p,ITs_messages_mms_startup,ITs_messages_mms_cleanup},
	{"ITc_messages_mms_get_attachement_count_p",ITc_messages_mms_get_attachement_count_p,ITs_messages_mms_startup,ITs_messages_mms_cleanup},
	{"ITc_messages_mms_set_get_subject_p",ITc_messages_mms_set_get_subject_p,ITs_messages_mms_startup,ITs_messages_mms_cleanup},
	{"ITc_messages_mms_remove_all_attachments_p",ITc_messages_mms_remove_all_attachments_p,ITs_messages_mms_startup,ITs_messages_mms_cleanup},
	{"ITc_messages_add_get_address_p",ITc_messages_add_get_address_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_get_mboxType_p",ITc_messages_get_mboxType_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_get_message_count_p",ITc_messages_get_message_count_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_add_get_sms_listening_port_p",ITc_messages_add_get_sms_listening_port_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_get_message_type_p",ITc_messages_get_message_type_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_set_get_text_p",ITc_messages_set_get_text_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_get_time_p",ITc_messages_get_time_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_set_get_sim_id_p",ITc_messages_set_get_sim_id_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_push_add_remove_incoming_cb_p",ITc_messages_push_add_remove_incoming_cb_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_push_register_deregister_p",ITc_messages_push_register_deregister_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_push_reregister_p",ITc_messages_push_reregister_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_send_message_p",ITc_messages_send_message_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_search_getid_searchbyid_freemessage_p",ITc_messages_search_getid_searchbyid_freemessage_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_foreach_message_p",ITc_messages_foreach_message_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_add_message_p",ITc_messages_add_message_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_set_mbox_type_p",ITc_messages_set_mbox_type_p,ITs_messages_startup,ITs_messages_cleanup},
	{"ITc_messages_set_time_p",ITc_messages_set_time_p,ITs_messages_startup,ITs_messages_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MESSAGES-NATIVE_H__
