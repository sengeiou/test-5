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

extern void utc_tzsh_quickpanel_startup(void);
extern void utc_tzsh_quickpanel_cleanup(void);

extern int utc_tzsh_create_n1(void);
extern int utc_tzsh_create_p1(void);
extern int utc_tzsh_destroy_n1(void);
extern int utc_tzsh_destroy_p1(void);
extern int utc_tzsh_quickpanel_create_n1(void);
extern int utc_tzsh_quickpanel_create_p1(void);
extern int utc_tzsh_quickpanel_create_with_type_n1(void);
extern int utc_tzsh_quickpanel_create_with_type_n2(void);
extern int utc_tzsh_quickpanel_create_with_type_p1(void);
extern int utc_tzsh_quickpanel_create_with_type_p2(void);
extern int utc_tzsh_quickpanel_destroy_n1(void);
extern int utc_tzsh_quickpanel_destroy_p1(void);
extern int utc_tzsh_quickpanel_destroy_p2(void);
extern int utc_tzsh_quickpanel_show_n1(void);
extern int utc_tzsh_quickpanel_show_p1(void);
extern int utc_tzsh_quickpanel_hide_n1(void);
extern int utc_tzsh_quickpanel_hide_p1(void);
extern int utc_tzsh_quickpanel_scrollable_set_n1(void);
extern int utc_tzsh_quickpanel_scrollable_set_p1(void);
extern int utc_tzsh_quickpanel_scrollable_get_n1(void);
extern int utc_tzsh_quickpanel_scrollable_get_p1(void);
extern int utc_tzsh_quickpanel_scrollable_get_p2(void);
extern int utc_tzsh_quickpanel_scrollable_state_set_n1(void);
extern int utc_tzsh_quickpanel_scrollable_state_set_p1(void);
extern int utc_tzsh_quickpanel_scrollable_state_get_n1(void);
extern int utc_tzsh_quickpanel_scrollable_state_get_p1(void);
extern int utc_tzsh_quickpanel_scrollable_state_get_p2(void);
extern int utc_tzsh_quickpanel_visible_get_n1(void);
extern int utc_tzsh_quickpanel_visible_get_n2(void);
extern int utc_tzsh_quickpanel_visible_get_p1(void);
extern int utc_tzsh_quickpanel_visible_get_p2(void);
extern int utc_tzsh_quickpanel_orientation_get_n1(void);
extern int utc_tzsh_quickpanel_orientation_get_p1(void);
extern int utc_tzsh_quickpanel_event_handler_add_n1(void);
extern int utc_tzsh_quickpanel_event_handler_add_n2(void);
extern int utc_tzsh_quickpanel_event_handler_add_p1(void);
extern int utc_tzsh_quickpanel_event_handler_add_p2(void);
extern int utc_tzsh_quickpanel_event_handler_del_n1(void);
extern int utc_tzsh_quickpanel_event_handler_del_p1(void);
extern int utc_tzsh_quickpanel_event_visible_get_n1(void);
extern int utc_tzsh_quickpanel_event_orientation_get_n1(void);
extern int utc_tzsh_quickpanel_type_get_n1(void);
extern int utc_tzsh_quickpanel_type_get_p1(void);

testcase tc_array[] = {
	{"utc_tzsh_create_n1",utc_tzsh_create_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_create_p1",utc_tzsh_create_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_destroy_n1",utc_tzsh_destroy_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_destroy_p1",utc_tzsh_destroy_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_create_n1",utc_tzsh_quickpanel_create_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_create_p1",utc_tzsh_quickpanel_create_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_create_with_type_n1",utc_tzsh_quickpanel_create_with_type_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_create_with_type_n2",utc_tzsh_quickpanel_create_with_type_n2,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_create_with_type_p1",utc_tzsh_quickpanel_create_with_type_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_create_with_type_p2",utc_tzsh_quickpanel_create_with_type_p2,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_destroy_n1",utc_tzsh_quickpanel_destroy_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_destroy_p1",utc_tzsh_quickpanel_destroy_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_destroy_p2",utc_tzsh_quickpanel_destroy_p2,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_show_n1",utc_tzsh_quickpanel_show_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_show_p1",utc_tzsh_quickpanel_show_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_hide_n1",utc_tzsh_quickpanel_hide_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_hide_p1",utc_tzsh_quickpanel_hide_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_scrollable_set_n1",utc_tzsh_quickpanel_scrollable_set_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_scrollable_set_p1",utc_tzsh_quickpanel_scrollable_set_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_scrollable_get_n1",utc_tzsh_quickpanel_scrollable_get_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_scrollable_get_p1",utc_tzsh_quickpanel_scrollable_get_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_scrollable_get_p2",utc_tzsh_quickpanel_scrollable_get_p2,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_scrollable_state_set_n1",utc_tzsh_quickpanel_scrollable_state_set_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_scrollable_state_set_p1",utc_tzsh_quickpanel_scrollable_state_set_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_scrollable_state_get_n1",utc_tzsh_quickpanel_scrollable_state_get_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_scrollable_state_get_p1",utc_tzsh_quickpanel_scrollable_state_get_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_scrollable_state_get_p2",utc_tzsh_quickpanel_scrollable_state_get_p2,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_visible_get_n1",utc_tzsh_quickpanel_visible_get_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_visible_get_n2",utc_tzsh_quickpanel_visible_get_n2,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_visible_get_p1",utc_tzsh_quickpanel_visible_get_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_visible_get_p2",utc_tzsh_quickpanel_visible_get_p2,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_orientation_get_n1",utc_tzsh_quickpanel_orientation_get_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_orientation_get_p1",utc_tzsh_quickpanel_orientation_get_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_event_handler_add_n1",utc_tzsh_quickpanel_event_handler_add_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_event_handler_add_n2",utc_tzsh_quickpanel_event_handler_add_n2,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_event_handler_add_p1",utc_tzsh_quickpanel_event_handler_add_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_event_handler_add_p2",utc_tzsh_quickpanel_event_handler_add_p2,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_event_handler_del_n1",utc_tzsh_quickpanel_event_handler_del_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_event_handler_del_p1",utc_tzsh_quickpanel_event_handler_del_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_event_visible_get_n1",utc_tzsh_quickpanel_event_visible_get_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_event_orientation_get_n1",utc_tzsh_quickpanel_event_orientation_get_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_type_get_n1",utc_tzsh_quickpanel_type_get_n1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{"utc_tzsh_quickpanel_type_get_p1",utc_tzsh_quickpanel_type_get_p1,utc_tzsh_quickpanel_startup,utc_tzsh_quickpanel_cleanup},
	{NULL, NULL}
};

#endif // __TCT_TZSH-QUICKPANEL-NATIVE_H__
