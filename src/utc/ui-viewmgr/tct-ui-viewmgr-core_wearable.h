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
#ifndef __TCT_UI-VIEWMGR-NATIVE_H__
#define __TCT_UI-VIEWMGR-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_ui_viewmgr_startup(void);
extern void utc_ui_viewmgr_cleanup(void);

extern int utc_ui_viewmgr_push_view_p(void);
extern int utc_ui_viewmgr_push_view_n(void);
extern int utc_ui_viewmgr_insert_view_before_p(void);
extern int utc_ui_viewmgr_insert_view_before_n(void);
extern int utc_ui_viewmgr_insert_view_after_p(void);
extern int utc_ui_viewmgr_insert_view_after_n(void);
extern int utc_ui_viewmgr_pop_view_p(void);
extern int utc_ui_viewmgr_pop_view_n(void);
extern int utc_ui_viewmgr_activate_p(void);
extern int utc_ui_viewmgr_activate_n(void);
extern int utc_ui_viewmgr_deactivate_p(void);
extern int utc_ui_viewmgr_deactivate_n(void);
extern int utc_ui_viewmgr_get_window_p(void);
extern int utc_ui_viewmgr_get_last_view_p(void);
extern int utc_ui_viewmgr_get_last_view_n(void);
extern int utc_ui_viewmgr_get_view_by_idx_p(void);
extern int utc_ui_viewmgr_get_view_by_idx_n(void);
extern int utc_ui_viewmgr_get_view_by_name_p(void);
extern int utc_ui_viewmgr_get_view_by_name_n(void);
extern int utc_ui_viewmgr_get_base_p(void);
extern int utc_ui_viewmgr_get_view_index_p(void);
extern int utc_ui_viewmgr_get_view_index_n(void);
extern int utc_ui_viewmgr_get_view_count_p(void);
extern int utc_ui_viewmgr_get_view_count_n(void);
extern int utc_ui_viewmgr_view_create_p(void);
extern int utc_ui_viewmgr_view_set_content_p(void);
extern int utc_ui_viewmgr_view_set_content_n(void);
extern int utc_ui_viewmgr_view_get_content_p(void);
extern int utc_ui_viewmgr_view_get_content_n(void);
extern int utc_ui_viewmgr_view_unset_content_p(void);
extern int utc_ui_viewmgr_view_unset_content_n(void);
extern int utc_ui_viewmgr_view_set_event_cb_p(void);
extern int utc_ui_viewmgr_view_set_event_cb_n(void);
extern int utc_ui_viewmgr_view_get_base_p(void);
extern int utc_ui_viewmgr_view_get_base_n(void);
extern int utc_ui_viewmgr_view_set_indicator_p(void);
extern int utc_ui_viewmgr_view_set_indicator_n(void);
extern int utc_ui_viewmgr_view_get_indicator_p(void);
extern int utc_ui_viewmgr_view_get_indicator_n(void);
extern int utc_ui_viewmgr_view_set_available_rotations_p(void);
extern int utc_ui_viewmgr_view_set_available_rotations_n(void);
extern int utc_ui_viewmgr_view_get_available_rotations_p(void);
extern int utc_ui_viewmgr_view_get_available_rotations_n(void);
extern int utc_ui_viewmgr_view_set_removable_content_p(void);
extern int utc_ui_viewmgr_view_set_removable_content_n(void);
extern int utc_ui_viewmgr_view_get_removable_content_p(void);
extern int utc_ui_viewmgr_view_get_removable_content_n(void);
extern int utc_ui_viewmgr_view_get_degree_p(void);
extern int utc_ui_viewmgr_view_get_degree_n(void);
extern int utc_ui_viewmgr_view_get_orientation_mode_p(void);
extern int utc_ui_viewmgr_view_get_orientation_mode_n(void);
extern int utc_ui_viewmgr_view_set_transition_style_p(void);
extern int utc_ui_viewmgr_view_set_transition_style_n(void);
extern int utc_ui_viewmgr_view_get_transition_style_p(void);
extern int utc_ui_viewmgr_view_get_transition_style_n(void);
extern int utc_ui_viewmgr_view_get_menu_p(void);
extern int utc_ui_viewmgr_view_get_menu_n(void);
extern int utc_ui_viewmgr_view_get_name_p(void);
extern int utc_ui_viewmgr_view_get_name_n(void);
extern int utc_ui_viewmgr_view_get_state_p(void);
extern int utc_ui_viewmgr_view_get_state_n(void);
extern int utc_ui_viewmgr_view_destroy_p(void);
extern int utc_ui_viewmgr_view_destroy_n(void);
extern int utc_ui_viewmgr_standard_view_create_p(void);
extern int utc_ui_viewmgr_standard_view_set_title_p(void);
extern int utc_ui_viewmgr_standard_view_set_title_n(void);
extern int utc_ui_viewmgr_standard_view_set_sub_title_p(void);
extern int utc_ui_viewmgr_standard_view_set_sub_title_n(void);
extern int utc_ui_viewmgr_standard_view_set_title_badge_p(void);
extern int utc_ui_viewmgr_standard_view_set_title_badge_n(void);
extern int utc_ui_viewmgr_standard_view_set_title_right_btn_p(void);
extern int utc_ui_viewmgr_standard_view_set_title_right_btn_n(void);
extern int utc_ui_viewmgr_standard_view_get_title_right_btn_p(void);
extern int utc_ui_viewmgr_standard_view_get_title_right_btn_n(void);
extern int utc_ui_viewmgr_standard_view_unset_title_right_btn_p(void);
extern int utc_ui_viewmgr_standard_view_unset_title_right_btn_n(void);
extern int utc_ui_viewmgr_standard_view_set_title_left_btn_p(void);
extern int utc_ui_viewmgr_standard_view_set_title_left_btn_n(void);
extern int utc_ui_viewmgr_standard_view_get_title_left_btn_p(void);
extern int utc_ui_viewmgr_standard_view_get_title_left_btn_n(void);
extern int utc_ui_viewmgr_standard_view_unset_title_left_btn_p(void);
extern int utc_ui_viewmgr_standard_view_unset_title_left_btn_n(void);
extern int utc_ui_viewmgr_standard_view_set_toolbar_p(void);
extern int utc_ui_viewmgr_standard_view_set_toolbar_n(void);
extern int utc_ui_viewmgr_standard_view_get_toolbar_p(void);
extern int utc_ui_viewmgr_standard_view_get_toolbar_n(void);
extern int utc_ui_viewmgr_standard_view_unset_toolbar_p(void);
extern int utc_ui_viewmgr_standard_view_unset_toolbar_n(void);
extern int utc_ui_viewmgr_standard_view_set_title_visible_p(void);
extern int utc_ui_viewmgr_standard_view_set_title_visible_n(void);
extern int utc_ui_viewmgr_popup_create_p(void);
extern int utc_ui_viewmgr_popup_create_n(void);
extern int utc_ui_viewmgr_popup_destroy_p(void);
extern int utc_ui_viewmgr_popup_destroy_n(void);
extern int utc_ui_viewmgr_popup_set_content_p(void);
extern int utc_ui_viewmgr_popup_set_content_n(void);
extern int utc_ui_viewmgr_popup_get_content_p(void);
extern int utc_ui_viewmgr_popup_get_content_n(void);
extern int utc_ui_viewmgr_popup_unset_content_p(void);
extern int utc_ui_viewmgr_popup_unset_content_n(void);
extern int utc_ui_viewmgr_popup_activate_p(void);
extern int utc_ui_viewmgr_popup_activate_n(void);
extern int utc_ui_viewmgr_popup_deactivate_p(void);
extern int utc_ui_viewmgr_popup_deactivate_n(void);
extern int utc_ui_viewmgr_popup_get_activated_p(void);
extern int utc_ui_viewmgr_popup_get_activated_n(void);
extern int utc_ui_viewmgr_popup_get_base_p(void);
extern int utc_ui_viewmgr_popup_get_base_n(void);
extern int utc_ui_viewmgr_popup_get_degree_p(void);
extern int utc_ui_viewmgr_popup_get_degree_n(void);
extern int utc_ui_viewmgr_popup_get_view_p(void);
extern int utc_ui_viewmgr_popup_get_view_n(void);

testcase tc_array[] = {
	{"utc_ui_viewmgr_push_view_p",utc_ui_viewmgr_push_view_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_push_view_n",utc_ui_viewmgr_push_view_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_insert_view_before_p",utc_ui_viewmgr_insert_view_before_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_insert_view_before_n",utc_ui_viewmgr_insert_view_before_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_insert_view_after_p",utc_ui_viewmgr_insert_view_after_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_insert_view_after_n",utc_ui_viewmgr_insert_view_after_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_pop_view_p",utc_ui_viewmgr_pop_view_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_pop_view_n",utc_ui_viewmgr_pop_view_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_activate_p",utc_ui_viewmgr_activate_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_activate_n",utc_ui_viewmgr_activate_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_deactivate_p",utc_ui_viewmgr_deactivate_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_deactivate_n",utc_ui_viewmgr_deactivate_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_window_p",utc_ui_viewmgr_get_window_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_last_view_p",utc_ui_viewmgr_get_last_view_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_last_view_n",utc_ui_viewmgr_get_last_view_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_view_by_idx_p",utc_ui_viewmgr_get_view_by_idx_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_view_by_idx_n",utc_ui_viewmgr_get_view_by_idx_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_view_by_name_p",utc_ui_viewmgr_get_view_by_name_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_view_by_name_n",utc_ui_viewmgr_get_view_by_name_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_base_p",utc_ui_viewmgr_get_base_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_view_index_p",utc_ui_viewmgr_get_view_index_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_view_index_n",utc_ui_viewmgr_get_view_index_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_view_count_p",utc_ui_viewmgr_get_view_count_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_get_view_count_n",utc_ui_viewmgr_get_view_count_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_create_p",utc_ui_viewmgr_view_create_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_content_p",utc_ui_viewmgr_view_set_content_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_content_n",utc_ui_viewmgr_view_set_content_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_content_p",utc_ui_viewmgr_view_get_content_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_content_n",utc_ui_viewmgr_view_get_content_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_unset_content_p",utc_ui_viewmgr_view_unset_content_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_unset_content_n",utc_ui_viewmgr_view_unset_content_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_event_cb_p",utc_ui_viewmgr_view_set_event_cb_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_event_cb_n",utc_ui_viewmgr_view_set_event_cb_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_base_p",utc_ui_viewmgr_view_get_base_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_base_n",utc_ui_viewmgr_view_get_base_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_indicator_p",utc_ui_viewmgr_view_set_indicator_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_indicator_n",utc_ui_viewmgr_view_set_indicator_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_indicator_p",utc_ui_viewmgr_view_get_indicator_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_indicator_n",utc_ui_viewmgr_view_get_indicator_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_available_rotations_p",utc_ui_viewmgr_view_set_available_rotations_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_available_rotations_n",utc_ui_viewmgr_view_set_available_rotations_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_available_rotations_p",utc_ui_viewmgr_view_get_available_rotations_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_available_rotations_n",utc_ui_viewmgr_view_get_available_rotations_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_removable_content_p",utc_ui_viewmgr_view_set_removable_content_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_removable_content_n",utc_ui_viewmgr_view_set_removable_content_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_removable_content_p",utc_ui_viewmgr_view_get_removable_content_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_removable_content_n",utc_ui_viewmgr_view_get_removable_content_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_degree_p",utc_ui_viewmgr_view_get_degree_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_degree_n",utc_ui_viewmgr_view_get_degree_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_orientation_mode_p",utc_ui_viewmgr_view_get_orientation_mode_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_orientation_mode_n",utc_ui_viewmgr_view_get_orientation_mode_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_transition_style_p",utc_ui_viewmgr_view_set_transition_style_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_set_transition_style_n",utc_ui_viewmgr_view_set_transition_style_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_transition_style_p",utc_ui_viewmgr_view_get_transition_style_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_transition_style_n",utc_ui_viewmgr_view_get_transition_style_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_menu_p",utc_ui_viewmgr_view_get_menu_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_menu_n",utc_ui_viewmgr_view_get_menu_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_name_p",utc_ui_viewmgr_view_get_name_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_name_n",utc_ui_viewmgr_view_get_name_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_state_p",utc_ui_viewmgr_view_get_state_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_get_state_n",utc_ui_viewmgr_view_get_state_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_destroy_p",utc_ui_viewmgr_view_destroy_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_view_destroy_n",utc_ui_viewmgr_view_destroy_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_create_p",utc_ui_viewmgr_standard_view_create_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_title_p",utc_ui_viewmgr_standard_view_set_title_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_title_n",utc_ui_viewmgr_standard_view_set_title_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_sub_title_p",utc_ui_viewmgr_standard_view_set_sub_title_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_sub_title_n",utc_ui_viewmgr_standard_view_set_sub_title_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_title_badge_p",utc_ui_viewmgr_standard_view_set_title_badge_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_title_badge_n",utc_ui_viewmgr_standard_view_set_title_badge_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_title_right_btn_p",utc_ui_viewmgr_standard_view_set_title_right_btn_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_title_right_btn_n",utc_ui_viewmgr_standard_view_set_title_right_btn_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_get_title_right_btn_p",utc_ui_viewmgr_standard_view_get_title_right_btn_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_get_title_right_btn_n",utc_ui_viewmgr_standard_view_get_title_right_btn_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_unset_title_right_btn_p",utc_ui_viewmgr_standard_view_unset_title_right_btn_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_unset_title_right_btn_n",utc_ui_viewmgr_standard_view_unset_title_right_btn_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_title_left_btn_p",utc_ui_viewmgr_standard_view_set_title_left_btn_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_title_left_btn_n",utc_ui_viewmgr_standard_view_set_title_left_btn_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_get_title_left_btn_p",utc_ui_viewmgr_standard_view_get_title_left_btn_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_get_title_left_btn_n",utc_ui_viewmgr_standard_view_get_title_left_btn_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_unset_title_left_btn_p",utc_ui_viewmgr_standard_view_unset_title_left_btn_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_unset_title_left_btn_n",utc_ui_viewmgr_standard_view_unset_title_left_btn_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_toolbar_p",utc_ui_viewmgr_standard_view_set_toolbar_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_toolbar_n",utc_ui_viewmgr_standard_view_set_toolbar_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_get_toolbar_p",utc_ui_viewmgr_standard_view_get_toolbar_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_get_toolbar_n",utc_ui_viewmgr_standard_view_get_toolbar_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_unset_toolbar_p",utc_ui_viewmgr_standard_view_unset_toolbar_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_unset_toolbar_n",utc_ui_viewmgr_standard_view_unset_toolbar_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_title_visible_p",utc_ui_viewmgr_standard_view_set_title_visible_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_standard_view_set_title_visible_n",utc_ui_viewmgr_standard_view_set_title_visible_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_create_p",utc_ui_viewmgr_popup_create_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_create_n",utc_ui_viewmgr_popup_create_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_destroy_p",utc_ui_viewmgr_popup_destroy_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_destroy_n",utc_ui_viewmgr_popup_destroy_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_set_content_p",utc_ui_viewmgr_popup_set_content_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_set_content_n",utc_ui_viewmgr_popup_set_content_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_get_content_p",utc_ui_viewmgr_popup_get_content_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_get_content_n",utc_ui_viewmgr_popup_get_content_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_unset_content_p",utc_ui_viewmgr_popup_unset_content_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_unset_content_n",utc_ui_viewmgr_popup_unset_content_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_activate_p",utc_ui_viewmgr_popup_activate_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_activate_n",utc_ui_viewmgr_popup_activate_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_deactivate_p",utc_ui_viewmgr_popup_deactivate_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_deactivate_n",utc_ui_viewmgr_popup_deactivate_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_get_activated_p",utc_ui_viewmgr_popup_get_activated_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_get_activated_n",utc_ui_viewmgr_popup_get_activated_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_get_base_p",utc_ui_viewmgr_popup_get_base_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_get_base_n",utc_ui_viewmgr_popup_get_base_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_get_degree_p",utc_ui_viewmgr_popup_get_degree_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_get_degree_n",utc_ui_viewmgr_popup_get_degree_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_get_view_p",utc_ui_viewmgr_popup_get_view_p,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{"utc_ui_viewmgr_popup_get_view_n",utc_ui_viewmgr_popup_get_view_n,utc_ui_viewmgr_startup,utc_ui_viewmgr_cleanup},
	{NULL, NULL}
};

#endif // __TCT_UI-VIEWMGR-NATIVE_H__