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
#ifndef __TCT_SCREEN-MIRRORING-NATIVE_H__
#define __TCT_SCREEN-MIRRORING-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_screen_mirroring_startup(void);
extern void ITs_screen_mirroring_cleanup(void);

extern int ITc_scmirroring_sink_set_ip_and_port_p(void);
extern int ITc_scmirroring_sink_set_display_p(void);
extern int ITc_scmirroring_sink_set_resolution_p(void);
extern int ITc_scmirroring_sink_set_unset_state_changed_cb_p(void);
extern int ITc_scmirroring_sink_create_destroy_p(void);
extern int ITc_scmirroring_sink_get_current_state_p(void);

testcase tc_array[] = {
	{"ITc_scmirroring_sink_set_ip_and_port_p",ITc_scmirroring_sink_set_ip_and_port_p,ITs_screen_mirroring_startup,ITs_screen_mirroring_cleanup},
	{"ITc_scmirroring_sink_set_display_p",ITc_scmirroring_sink_set_display_p,ITs_screen_mirroring_startup,ITs_screen_mirroring_cleanup},
	{"ITc_scmirroring_sink_set_resolution_p",ITc_scmirroring_sink_set_resolution_p,ITs_screen_mirroring_startup,ITs_screen_mirroring_cleanup},
	{"ITc_scmirroring_sink_set_unset_state_changed_cb_p",ITc_scmirroring_sink_set_unset_state_changed_cb_p,ITs_screen_mirroring_startup,ITs_screen_mirroring_cleanup},
	{"ITc_scmirroring_sink_create_destroy_p",ITc_scmirroring_sink_create_destroy_p,ITs_screen_mirroring_startup,ITs_screen_mirroring_cleanup},
	{"ITc_scmirroring_sink_get_current_state_p",ITc_scmirroring_sink_get_current_state_p,ITs_screen_mirroring_startup,ITs_screen_mirroring_cleanup},
	{NULL, NULL}
};

#endif // __TCT_SCREEN-MIRRORING-NATIVE_H__
