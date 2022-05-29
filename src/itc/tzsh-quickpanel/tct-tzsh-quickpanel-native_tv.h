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
#ifndef __TCT_TZSH-QUICKPANEL-NATIVE_H__
#define __TCT_TZSH-QUICKPANEL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_tzsh_quickpanel_startup(void);
extern void ITs_tzsh_quickpanel_cleanup(void);

extern int ITc_tzsh_quickpanel_tzsh_create_destroy_p(void);
extern int ITc_tzsh_quickpanel_panel_create_destroy_p(void);
extern int ITc_tzsh_quickpanel_panel_show_hide_p(void);
extern int ITc_tzsh_quickpanel_visible_get_p(void);
extern int ITc_tzsh_quickpanel_orientation_get_p(void);
extern int ITc_tzsh_quickpanel_event_handler_Visible_add_delete_get_p(void);
extern int ITc_tzsh_quickpanel_event_handler_orientation_add_delete_get_p(void);
extern int ITc_tzsh_quickpanel_type_get_p(void);
extern int ITc_tzsh_quickpanel_scrollable_state_set_get_p(void);

testcase tc_array[] = {
	{"ITc_tzsh_quickpanel_tzsh_create_destroy_p",ITc_tzsh_quickpanel_tzsh_create_destroy_p,ITs_tzsh_quickpanel_startup,ITs_tzsh_quickpanel_cleanup},
	{"ITc_tzsh_quickpanel_panel_create_destroy_p",ITc_tzsh_quickpanel_panel_create_destroy_p,ITs_tzsh_quickpanel_startup,ITs_tzsh_quickpanel_cleanup},
	{"ITc_tzsh_quickpanel_panel_show_hide_p",ITc_tzsh_quickpanel_panel_show_hide_p,ITs_tzsh_quickpanel_startup,ITs_tzsh_quickpanel_cleanup},
	{"ITc_tzsh_quickpanel_visible_get_p",ITc_tzsh_quickpanel_visible_get_p,ITs_tzsh_quickpanel_startup,ITs_tzsh_quickpanel_cleanup},
	{"ITc_tzsh_quickpanel_orientation_get_p",ITc_tzsh_quickpanel_orientation_get_p,ITs_tzsh_quickpanel_startup,ITs_tzsh_quickpanel_cleanup},
	{"ITc_tzsh_quickpanel_event_handler_Visible_add_delete_get_p",ITc_tzsh_quickpanel_event_handler_Visible_add_delete_get_p,ITs_tzsh_quickpanel_startup,ITs_tzsh_quickpanel_cleanup},
	{"ITc_tzsh_quickpanel_event_handler_orientation_add_delete_get_p",ITc_tzsh_quickpanel_event_handler_orientation_add_delete_get_p,ITs_tzsh_quickpanel_startup,ITs_tzsh_quickpanel_cleanup},
	{"ITc_tzsh_quickpanel_type_get_p",ITc_tzsh_quickpanel_type_get_p,ITs_tzsh_quickpanel_startup,ITs_tzsh_quickpanel_cleanup},
	{"ITc_tzsh_quickpanel_scrollable_state_set_get_p",ITc_tzsh_quickpanel_scrollable_state_set_get_p, ITs_tzsh_quickpanel_startup, ITs_tzsh_quickpanel_cleanup},
	{NULL, NULL}
};

#endif // __TCT_TZSH-QUICKPANEL-NATIVE_H__
