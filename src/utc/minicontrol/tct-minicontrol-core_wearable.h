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
#ifndef __TCT_MINICONTROL-NATIVE_H__
#define __TCT_MINICONTROL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_minicontrol_startup(void);
extern void utc_minicontrol_cleanup(void);

extern int utc_minicontrol_create_window_p(void);
extern int utc_minicontrol_create_window_n(void);
extern int utc_minicontrol_send_event_p(void);
extern int utc_minicontrol_send_event_n(void);
extern int utc_minicontrol_viewer_add_p(void);
extern int utc_minicontrol_viewer_add_n(void);
extern int utc_minicontrol_viewer_send_event_p1(void);
extern int utc_minicontrol_viewer_send_event_p2(void);
extern int utc_minicontrol_viewer_send_event_n(void);
extern int utc_minicontrol_viewer_set_event_cb_p(void);
extern int utc_minicontrol_viewer_set_event_cb_n(void);
extern int utc_minicontrol_viewer_unset_event_cb_p(void);

testcase tc_array[] = {
	{"utc_minicontrol_create_window_p",utc_minicontrol_create_window_p,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_create_window_n",utc_minicontrol_create_window_n,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_send_event_p",utc_minicontrol_send_event_p,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_send_event_n",utc_minicontrol_send_event_n,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_viewer_add_p",utc_minicontrol_viewer_add_p,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_viewer_add_n",utc_minicontrol_viewer_add_n,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_viewer_send_event_p1",utc_minicontrol_viewer_send_event_p1,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_viewer_send_event_p2",utc_minicontrol_viewer_send_event_p2,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_viewer_send_event_n",utc_minicontrol_viewer_send_event_n,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_viewer_set_event_cb_p",utc_minicontrol_viewer_set_event_cb_p,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_viewer_set_event_cb_n",utc_minicontrol_viewer_set_event_cb_n,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{"utc_minicontrol_viewer_unset_event_cb_p",utc_minicontrol_viewer_unset_event_cb_p,utc_minicontrol_startup,utc_minicontrol_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MINICONTROL-NATIVE_H__
