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
#ifndef __TCT_ATTACH-PANEL-NATIVE_H__
#define __TCT_ATTACH-PANEL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_attach_panel_startup(void);
extern void utc_attach_panel_cleanup(void);

extern int utc_attach_panel_create_p(void);
extern int utc_attach_panel_create_p2(void);
extern int utc_attach_panel_create_n(void);
extern int utc_attach_panel_destroy_p(void);
extern int utc_attach_panel_destroy_n(void);
extern int utc_attach_panel_add_content_category_p(void);
extern int utc_attach_panel_add_content_category_n(void);
extern int utc_attach_panel_remove_content_category_p(void);
extern int utc_attach_panel_remove_content_category_n(void);
extern int utc_attach_panel_set_extra_data_p(void);
extern int utc_attach_panel_set_extra_data_n(void);
extern int utc_attach_panel_show_p(void);
extern int utc_attach_panel_show_n(void);
extern int utc_attach_panel_hide_p(void);
extern int utc_attach_panel_hide_n(void);
extern int utc_attach_panel_get_visibility_p(void);
extern int utc_attach_panel_get_visibility_n(void);
extern int utc_attach_panel_set_result_cb_p(void);
extern int utc_attach_panel_set_result_cb_n(void);
extern int utc_attach_panel_unset_result_cb_p(void);
extern int utc_attach_panel_unset_result_cb_n(void);
extern int utc_attach_panel_set_event_cb_p(void);
extern int utc_attach_panel_set_event_cb_n(void);
extern int utc_attach_panel_unset_event_cb_p(void);
extern int utc_attach_panel_unset_event_cb_n(void);
extern int utc_attach_panel_get_state_p(void);
extern int utc_attach_panel_get_state_n(void);
extern int utc_attach_panel_show_without_animation_p(void);
extern int utc_attach_panel_show_without_animation_n(void);
extern int utc_attach_panel_hide_without_animation_p(void);
extern int utc_attach_panel_hide_without_animation_n(void);

testcase tc_array[] = {
	{"utc_attach_panel_create_p",utc_attach_panel_create_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_create_p2",utc_attach_panel_create_p2,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_create_n",utc_attach_panel_create_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_destroy_p",utc_attach_panel_destroy_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_destroy_n",utc_attach_panel_destroy_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_add_content_category_p",utc_attach_panel_add_content_category_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_add_content_category_n",utc_attach_panel_add_content_category_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_remove_content_category_p",utc_attach_panel_remove_content_category_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_remove_content_category_n",utc_attach_panel_remove_content_category_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_set_extra_data_p",utc_attach_panel_set_extra_data_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_set_extra_data_n",utc_attach_panel_set_extra_data_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_show_p",utc_attach_panel_show_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_show_n",utc_attach_panel_show_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_hide_p",utc_attach_panel_hide_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_hide_n",utc_attach_panel_hide_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_get_visibility_p",utc_attach_panel_get_visibility_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_get_visibility_n",utc_attach_panel_get_visibility_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_set_result_cb_p",utc_attach_panel_set_result_cb_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_set_result_cb_n",utc_attach_panel_set_result_cb_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_unset_result_cb_p",utc_attach_panel_unset_result_cb_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_unset_result_cb_n",utc_attach_panel_unset_result_cb_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_set_event_cb_p",utc_attach_panel_set_event_cb_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_set_event_cb_n",utc_attach_panel_set_event_cb_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_unset_event_cb_p",utc_attach_panel_unset_event_cb_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_unset_event_cb_n",utc_attach_panel_unset_event_cb_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_get_state_p",utc_attach_panel_get_state_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_get_state_n",utc_attach_panel_get_state_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_show_without_animation_p",utc_attach_panel_show_without_animation_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_show_without_animation_n",utc_attach_panel_show_without_animation_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_hide_without_animation_p",utc_attach_panel_hide_without_animation_p,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{"utc_attach_panel_hide_without_animation_n",utc_attach_panel_hide_without_animation_n,utc_attach_panel_startup,utc_attach_panel_cleanup},
	{NULL, NULL}
};

#endif // __TCT_ATTACH-PANEL-NATIVE_H__
