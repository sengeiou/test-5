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
#ifndef __TCT_CAPI-MESSAGE-PORT-NATIVE_H__
#define __TCT_CAPI-MESSAGE-PORT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_message_port_startup(void);
extern void ITs_message_port_cleanup(void);

extern int ITc_message_port_register_unregister_local_port_p(void);
extern int ITc_message_port_register_unregister_trusted_local_port_p(void);
extern int ITc_message_port_check_remote_port_p(void);
extern int ITc_message_port_check_trusted_remote_port_p(void);
extern int ITc_message_port_send_message_p(void);
extern int ITc_message_port_send_message_with_local_port_p(void);
extern int ITc_message_port_add_registered_cb_p(void);
extern int ITc_message_port_add_unregistered_cb_p(void);
extern int ITc_message_port_remove_registration_event_cb_p(void);

testcase tc_array[] = {
	{"ITc_message_port_register_unregister_local_port_p",ITc_message_port_register_unregister_local_port_p,ITs_message_port_startup,ITs_message_port_cleanup},
	{"ITc_message_port_register_unregister_trusted_local_port_p",ITc_message_port_register_unregister_trusted_local_port_p,ITs_message_port_startup,ITs_message_port_cleanup},
	{"ITc_message_port_check_remote_port_p",ITc_message_port_check_remote_port_p,ITs_message_port_startup,ITs_message_port_cleanup},
	{"ITc_message_port_check_trusted_remote_port_p",ITc_message_port_check_trusted_remote_port_p,ITs_message_port_startup,ITs_message_port_cleanup},
	{"ITc_message_port_send_message_p",ITc_message_port_send_message_p,ITs_message_port_startup,ITs_message_port_cleanup},
	{"ITc_message_port_send_message_with_local_port_p",ITc_message_port_send_message_with_local_port_p,ITs_message_port_startup,ITs_message_port_cleanup},
	{"ITc_message_port_add_registered_cb_p", ITc_message_port_add_registered_cb_p, ITs_message_port_startup,ITs_message_port_cleanup},
	{"ITc_message_port_add_unregistered_cb_p", ITc_message_port_add_unregistered_cb_p, ITs_message_port_startup, ITs_message_port_cleanup},
	{"ITc_message_port_remove_registration_event_cb_p", ITc_message_port_remove_registration_event_cb_p, ITs_message_port_startup, ITs_message_port_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAPI-MESSAGE-PORT-NATIVE_H__
