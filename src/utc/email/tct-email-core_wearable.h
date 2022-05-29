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

extern void utc_messaging_email_startup(void);
extern void utc_messaging_email_cleanup(void);

extern int utc_messaging_email_create_message_p(void);
extern int utc_messaging_email_create_message_n(void);
extern int utc_messaging_email_destroy_message_p(void);
extern int utc_messaging_email_destroy_message_n(void);
extern int utc_messaging_email_set_subject_p(void);
extern int utc_messaging_email_set_subject_n(void);
extern int utc_messaging_email_set_body_p(void);
extern int utc_messaging_email_set_body_n(void);
extern int utc_messaging_email_add_recipient_p(void);
extern int utc_messaging_email_add_recipient_n(void);
extern int utc_messaging_email_remove_all_recipients_p(void);
extern int utc_messaging_email_remove_all_recipients_n(void);
extern int utc_messaging_email_save_message_p(void);
extern int utc_messaging_email_save_message_n(void);
extern int utc_messaging_email_add_attach_p(void);
extern int utc_messaging_email_add_attach_n(void);
extern int utc_messaging_email_remove_all_attachments_p(void);
extern int utc_messaging_email_remove_all_attachments_n(void);
extern int utc_messaging_email_send_message_p(void);
extern int utc_messaging_email_send_message_n(void);
extern int utc_messaging_email_set_message_sent_cb_p(void);
extern int utc_messaging_email_set_message_sent_cb_n(void);
extern int utc_messaging_email_unset_message_sent_cb_p(void);
extern int utc_messaging_email_unset_message_sent_cb_n(void);

testcase tc_array[] = {
	{"utc_messaging_email_create_message_p",utc_messaging_email_create_message_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_create_message_n",utc_messaging_email_create_message_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_destroy_message_p",utc_messaging_email_destroy_message_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_destroy_message_n",utc_messaging_email_destroy_message_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_set_subject_p",utc_messaging_email_set_subject_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_set_subject_n",utc_messaging_email_set_subject_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_set_body_p",utc_messaging_email_set_body_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_set_body_n",utc_messaging_email_set_body_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_add_recipient_p",utc_messaging_email_add_recipient_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_add_recipient_n",utc_messaging_email_add_recipient_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_remove_all_recipients_p",utc_messaging_email_remove_all_recipients_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_remove_all_recipients_n",utc_messaging_email_remove_all_recipients_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_save_message_p",utc_messaging_email_save_message_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_save_message_n",utc_messaging_email_save_message_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_add_attach_p",utc_messaging_email_add_attach_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_add_attach_n",utc_messaging_email_add_attach_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_remove_all_attachments_p",utc_messaging_email_remove_all_attachments_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_remove_all_attachments_n",utc_messaging_email_remove_all_attachments_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_send_message_p",utc_messaging_email_send_message_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_send_message_n",utc_messaging_email_send_message_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_set_message_sent_cb_p",utc_messaging_email_set_message_sent_cb_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_set_message_sent_cb_n",utc_messaging_email_set_message_sent_cb_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_unset_message_sent_cb_p",utc_messaging_email_unset_message_sent_cb_p,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{"utc_messaging_email_unset_message_sent_cb_n",utc_messaging_email_unset_message_sent_cb_n,utc_messaging_email_startup,utc_messaging_email_cleanup},
	{NULL, NULL}
};

#endif // __TCT_EMAIL-NATIVE_H__
