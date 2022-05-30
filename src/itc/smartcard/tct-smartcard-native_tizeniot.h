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
#ifndef __TCT_SMARTCARD-NATIVE_H__
#define __TCT_SMARTCARD-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_smartcard_startup(void);
extern void ITs_smartcard_cleanup(void);
extern void ITs_smartcard_service_startup(void);
extern void ITs_smartcard_service_cleanup(void);
extern void ITs_smartcard_reader_startup(void);
extern void ITs_smartcard_reader_cleanup(void);
extern void ITs_smartcard_session_startup(void);
extern void ITs_smartcard_session_cleanup(void);

extern int ITc_smartcard_initialize_deinitialize_p(void);
extern int ITc_smartcard_get_readers_p(void);
extern int ITc_smartcard_reader_get_name_p(void);
extern int ITc_smartcard_reader_is_secure_element_present_p(void);
extern int ITc_smartcard_reader_open_close_session_p(void);
extern int ITc_smartcard_get_version_p(void);
extern int ITc_smartcard_reader_set_unset_event_cb_p(void);
extern int ITc_smartcard_session_is_closed_p(void);
extern int ITc_smartcard_session_get_reader_p(void);
extern int ITc_smartcard_session_get_atr_p(void);

testcase tc_array[] = {
	{"ITc_smartcard_initialize_deinitialize_p",ITc_smartcard_initialize_deinitialize_p,ITs_smartcard_startup,ITs_smartcard_cleanup},
	{"ITc_smartcard_get_readers_p",ITc_smartcard_get_readers_p,ITs_smartcard_service_startup,ITs_smartcard_service_cleanup},
	{"ITc_smartcard_reader_get_name_p",ITc_smartcard_reader_get_name_p,ITs_smartcard_reader_startup,ITs_smartcard_reader_cleanup},
	{"ITc_smartcard_reader_is_secure_element_present_p",ITc_smartcard_reader_is_secure_element_present_p,ITs_smartcard_reader_startup,ITs_smartcard_reader_cleanup},
	{"ITc_smartcard_reader_open_close_session_p",ITc_smartcard_reader_open_close_session_p,ITs_smartcard_reader_startup,ITs_smartcard_reader_cleanup},
	{"ITc_smartcard_get_version_p",ITc_smartcard_get_version_p,ITs_smartcard_reader_startup,ITs_smartcard_reader_cleanup},
	{"ITc_smartcard_reader_set_unset_event_cb_p",ITc_smartcard_reader_set_unset_event_cb_p,ITs_smartcard_reader_startup,ITs_smartcard_reader_cleanup},
	{"ITc_smartcard_session_is_closed_p",ITc_smartcard_session_is_closed_p,ITs_smartcard_session_startup,ITs_smartcard_session_cleanup},
	{"ITc_smartcard_session_get_reader_p",ITc_smartcard_session_get_reader_p,ITs_smartcard_session_startup,ITs_smartcard_session_cleanup},
	{"ITc_smartcard_session_get_atr_p",ITc_smartcard_session_get_atr_p,ITs_smartcard_session_startup,ITs_smartcard_session_cleanup},
	{NULL, NULL}
};

#endif // __TCT_SMARTCARD-NATIVE_H__
