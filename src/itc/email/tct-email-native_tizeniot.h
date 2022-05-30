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
#ifndef __TCT_EMAIL-NATIVE_H__
#define __TCT_EMAIL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_email_startup(void);
extern void ITs_email_cleanup(void);

extern int ITc_email_add_remove_attach_p(void);
extern int ITc_email_add_remove_recipient_p(void);
extern int ITc_email_create_destroy_message_p(void);
extern int ITc_email_save_message_p(void);
extern int ITc_email_send_message_with_attachment_p(void);
extern int ITc_email_send_message_without_attachment_p(void);
extern int ITc_email_set_body_p(void);
extern int ITc_email_set_unset_message_sent_cb_p(void);
extern int ITc_email_set_subject_p(void);

testcase tc_array[] = {
	{"ITc_email_add_remove_attach_p",ITc_email_add_remove_attach_p,ITs_email_startup,ITs_email_cleanup},
	{"ITc_email_add_remove_recipient_p",ITc_email_add_remove_recipient_p,ITs_email_startup,ITs_email_cleanup},
	{"ITc_email_create_destroy_message_p",ITc_email_create_destroy_message_p,ITs_email_startup,ITs_email_cleanup},
	{"ITc_email_save_message_p",ITc_email_save_message_p,ITs_email_startup,ITs_email_cleanup},
	{"ITc_email_send_message_with_attachment_p",ITc_email_send_message_with_attachment_p,ITs_email_startup,ITs_email_cleanup},
	{"ITc_email_send_message_without_attachment_p",ITc_email_send_message_without_attachment_p,ITs_email_startup,ITs_email_cleanup},
	{"ITc_email_set_body_p",ITc_email_set_body_p,ITs_email_startup,ITs_email_cleanup},
	{"ITc_email_set_unset_message_sent_cb_p",ITc_email_set_unset_message_sent_cb_p,ITs_email_startup,ITs_email_cleanup},
	{"ITc_email_set_subject_p",ITc_email_set_subject_p,ITs_email_startup,ITs_email_cleanup},
	{NULL, NULL}
};

#endif // __TCT_EMAIL-NATIVE_H__
