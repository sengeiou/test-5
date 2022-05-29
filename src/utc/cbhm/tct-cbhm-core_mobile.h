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
#ifndef __TCT_CBHM-NATIVE_H__
#define __TCT_CBHM-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_cbhm_startup(void);
extern void utc_cbhm_cleanup(void);

extern int utc_cbhm_open_service_p(void);
extern int utc_cbhm_open_service_n(void);
extern int utc_cbhm_close_service_p(void);
extern int utc_cbhm_close_service_n(void);
extern int utc_cbhm_show_p(void);
extern int utc_cbhm_show_n(void);
extern int utc_cbhm_hide_p(void);
extern int utc_cbhm_hide_n(void);
extern int utc_cbhm_selection_set_p1(void);
extern int utc_cbhm_selection_set_p2(void);
extern int utc_cbhm_selection_set_p3(void);
extern int utc_cbhm_selection_set_p4(void);
extern int utc_cbhm_selection_set_p5(void);
extern int utc_cbhm_selection_set_p6(void);
extern int utc_cbhm_selection_set_n(void);
extern int utc_cbhm_selection_get_p(void);
extern int utc_cbhm_selection_get_n(void);
extern int utc_cbhm_item_count_get_p(void);
extern int utc_cbhm_item_count_get_n(void);
extern int utc_cbhm_selection_type_set_p(void);
extern int utc_cbhm_selection_type_set_n(void);
extern int utc_cbhm_selection_type_get_p(void);
extern int utc_cbhm_selection_type_get_n(void);
extern int utc_cbhm_item_selected_callback_add_p(void);
extern int utc_cbhm_item_selected_callback_add_n(void);
extern int utc_cbhm_item_selected_callback_remove_p(void);
extern int utc_cbhm_item_selected_callback_remove_n(void);
extern int utc_cbhm_item_changed_callback_add_p(void);
extern int utc_cbhm_item_changed_callback_add_n(void);
extern int utc_cbhm_item_changed_callback_remove_p(void);
extern int utc_cbhm_item_changed_callback_remove_n(void);
extern int utc_cbhm_state_get_p(void);
extern int utc_cbhm_state_get_n(void);
extern int utc_cbhm_latest_item_type_get_p(void);
extern int utc_cbhm_latest_item_type_get_n(void);
extern int utc_cbhm_monitor_callback_add_p(void);
extern int utc_cbhm_monitor_callback_add_n(void);
extern int utc_cbhm_monitor_callback_remove_p(void);
extern int utc_cbhm_monitor_callback_remove_n(void);

testcase tc_array[] = {
	{"utc_cbhm_open_service_p",utc_cbhm_open_service_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_open_service_n",utc_cbhm_open_service_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_close_service_p",utc_cbhm_close_service_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_close_service_n",utc_cbhm_close_service_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_show_p",utc_cbhm_show_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_show_n",utc_cbhm_show_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_hide_p",utc_cbhm_hide_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_hide_n",utc_cbhm_hide_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_set_p1",utc_cbhm_selection_set_p1,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_set_p2",utc_cbhm_selection_set_p2,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_set_p3",utc_cbhm_selection_set_p3,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_set_p4",utc_cbhm_selection_set_p4,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_set_p5",utc_cbhm_selection_set_p5,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_set_p6",utc_cbhm_selection_set_p6,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_set_n",utc_cbhm_selection_set_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_get_p",utc_cbhm_selection_get_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_get_n",utc_cbhm_selection_get_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_item_count_get_p",utc_cbhm_item_count_get_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_item_count_get_n",utc_cbhm_item_count_get_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_type_set_p",utc_cbhm_selection_type_set_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_type_set_n",utc_cbhm_selection_type_set_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_type_get_p",utc_cbhm_selection_type_get_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_selection_type_get_n",utc_cbhm_selection_type_get_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_item_selected_callback_add_p",utc_cbhm_item_selected_callback_add_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_item_selected_callback_add_n",utc_cbhm_item_selected_callback_add_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_item_selected_callback_remove_p",utc_cbhm_item_selected_callback_remove_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_item_selected_callback_remove_n",utc_cbhm_item_selected_callback_remove_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_item_changed_callback_add_p",utc_cbhm_item_changed_callback_add_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_item_changed_callback_add_n",utc_cbhm_item_changed_callback_add_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_item_changed_callback_remove_p",utc_cbhm_item_changed_callback_remove_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_item_changed_callback_remove_n",utc_cbhm_item_changed_callback_remove_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_state_get_p",utc_cbhm_state_get_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_state_get_n",utc_cbhm_state_get_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_latest_item_type_get_p",utc_cbhm_latest_item_type_get_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_latest_item_type_get_n",utc_cbhm_latest_item_type_get_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_monitor_callback_add_p",utc_cbhm_monitor_callback_add_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_monitor_callback_add_n",utc_cbhm_monitor_callback_add_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_monitor_callback_remove_p",utc_cbhm_monitor_callback_remove_p,utc_cbhm_startup,utc_cbhm_cleanup},
	{"utc_cbhm_monitor_callback_remove_n",utc_cbhm_monitor_callback_remove_n,utc_cbhm_startup,utc_cbhm_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CBHM-NATIVE_H__
