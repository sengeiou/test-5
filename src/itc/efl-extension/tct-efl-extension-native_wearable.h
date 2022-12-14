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
#ifndef __TCT_EFL-EXT-NATIVE_H__
#define __TCT_EFL-EXT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_efl_ext_startup(void);
extern void ITs_efl_ext_cleanup(void);

extern int ITc_eext_circle_object_scroller_add_p(void);
extern int ITc_eext_circle_object_scroller_policy_set_get_p(void);
extern int ITc_eext_rotary_object_event_callback_add_del_p(void);
extern int ITc_eext_rotary_object_event_callback_priority_add_del_p(void);
extern int ITc_eext_rotary_event_handler_add_del_p(void);
extern int ITc_eext_rotary_object_event_activated_set_p(void);
extern int ITc_eext_circle_object_line_width_set_get_p(void);
extern int ITc_eext_circle_object_angle_set_get_p(void);
extern int ITc_eext_circle_object_angle_offset_set_get_p(void);
extern int ITc_eext_circle_object_angle_min_max_set_get_p(void);
extern int ITc_eext_circle_object_value_min_max_set_get_p(void);
extern int ITc_eext_circle_object_value_set_get_p(void);
extern int ITc_eext_circle_object_color_set_get_p(void);
extern int ITc_eext_circle_object_radius_set_get_p(void);
extern int ITc_eext_circle_object_disabled_set_get_p(void);
extern int ITc_eext_circle_object_add_p(void);
extern int ITc_eext_circle_object_genlist_add_p(void);
extern int ITc_eext_circle_object_genlist_scroller_policy_set_get_p(void);
extern int ITc_eext_circle_object_slider_add_p(void);
extern int ITc_eext_circle_object_slider_step_set_get_p(void);
extern int ITc_eext_circle_object_datetime_add_p(void);
extern int ITc_eext_circle_object_progressbar_add_p(void);
extern int ITc_eext_circle_surface_conformant_add_delete_p(void);
extern int ITc_eext_circle_surface_layout_add_delete_p(void);
extern int ITc_eext_circle_surface_naviframe_add_delete_p(void);
extern int ITc_eext_rotary_selector_add_p(void);
extern int ITc_eext_rotary_selector_item_append_del_p(void);
extern int ITc_eext_rotary_selector_item_prepend_clear_p(void);
extern int ITc_eext_rotary_selector_item_insert_after_p(void);
extern int ITc_eext_rotary_selector_item_insert_before_p(void);
extern int ITc_eext_rotary_selector_item_part_text_set_get_p(void);
extern int ITc_eext_rotary_selector_item_domain_translatable_part_text_set_get_p(void);
extern int ITc_eext_rotary_selector_item_part_content_set_get_p(void);
extern int ITc_eext_rotary_selector_part_content_set_get_p(void);
extern int ITc_eext_rotary_selector_item_part_color_set_get_p(void);
extern int ITc_eext_rotary_selector_part_color_set_get_p(void);
extern int ITc_eext_rotary_selector_selected_item_set_get_p(void);
extern int ITc_eext_rotary_selector_items_get_p(void);
extern int ITc_eext_more_option_add_delete_p(void);
extern int ITc_eext_more_option_direction_set_get_p(void);
extern int ITc_eext_more_option_item_append_del_p(void);
extern int ITc_eext_more_option_item_prepend_del_p(void);
extern int ITc_eext_more_option_item_insert_after_clear_p(void);
extern int ITc_eext_more_option_item_insert_before_clear_p(void);
extern int ITc_eext_more_option_item_part_text_set_get_p(void);
extern int ITc_eext_more_option_item_domain_translatable_part_text_set_get_p(void);
extern int ITc_eext_more_option_item_part_content_set_get_p(void);
extern int ITc_eext_more_option_opened_set_get_p(void);
extern int ITc_eext_more_option_items_get_p(void);
extern int ITc_eext_circle_object_spinner_add_p(void);
extern int ITc_eext_circle_object_spinner_angle_set_p(void);
extern int ITc_eext_circle_object_item_value_set_get_p(void);
extern int ITc_eext_circle_object_item_color_set_get_p(void);
extern int ITc_eext_circle_object_item_radius_set_get_p(void);
extern int ITc_eext_circle_object_item_line_width_set_get_p(void);
extern int ITc_eext_circle_object_item_angle_set_get_p(void);
extern int ITc_eext_circle_object_item_angle_offset_set_get_p(void);
extern int ITc_eext_circle_object_item_angle_min_max_set_get_p(void);
extern int ITc_eext_circle_object_item_value_min_max_set_get_p(void);
extern int ITc_efl_ext_eext_circle_object_mirrored_set_get_p(void);
extern int ITc_eext_more_option_editing_enable_set_get_p(void);
extern int ITc_eext_more_option_add_item_enabled_set_get_p(void);
extern int ITc_eext_more_option_item_delete_enabled_set_get_p(void);
extern int ITc_eext_rotary_selector_editing_enabled_set_get_p(void);
extern int ITc_eext_rotary_selector_add_item_enabled_set_get_p(void);
extern int ITc_eext_rotary_selector_item_delete_enabled_set_get_p(void);
extern int ITc_eext_panel_part_content_get_set(void);
extern int ITc_eext_panel_add(void);
extern int ITc_eext_rotary_event_activated_object_get_p(void);
extern int ITc_eext_popup_add_p(void);

testcase tc_array[] = {
	{"ITc_eext_circle_object_scroller_add_p",ITc_eext_circle_object_scroller_add_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_scroller_policy_set_get_p",ITc_eext_circle_object_scroller_policy_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_object_event_callback_add_del_p",ITc_eext_rotary_object_event_callback_add_del_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_object_event_callback_priority_add_del_p",ITc_eext_rotary_object_event_callback_priority_add_del_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_event_handler_add_del_p",ITc_eext_rotary_event_handler_add_del_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_object_event_activated_set_p",ITc_eext_rotary_object_event_activated_set_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_line_width_set_get_p",ITc_eext_circle_object_line_width_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_angle_set_get_p",ITc_eext_circle_object_angle_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_angle_offset_set_get_p",ITc_eext_circle_object_angle_offset_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_angle_min_max_set_get_p",ITc_eext_circle_object_angle_min_max_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_value_min_max_set_get_p",ITc_eext_circle_object_value_min_max_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_value_set_get_p",ITc_eext_circle_object_value_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_color_set_get_p",ITc_eext_circle_object_color_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_radius_set_get_p",ITc_eext_circle_object_radius_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_disabled_set_get_p",ITc_eext_circle_object_disabled_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_add_p",ITc_eext_circle_object_add_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_genlist_add_p",ITc_eext_circle_object_genlist_add_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_genlist_scroller_policy_set_get_p",ITc_eext_circle_object_genlist_scroller_policy_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_slider_add_p",ITc_eext_circle_object_slider_add_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_slider_step_set_get_p",ITc_eext_circle_object_slider_step_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_datetime_add_p",ITc_eext_circle_object_datetime_add_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_progressbar_add_p",ITc_eext_circle_object_progressbar_add_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_surface_conformant_add_delete_p",ITc_eext_circle_surface_conformant_add_delete_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_surface_layout_add_delete_p",ITc_eext_circle_surface_layout_add_delete_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_surface_naviframe_add_delete_p",ITc_eext_circle_surface_naviframe_add_delete_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_add_p",ITc_eext_rotary_selector_add_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_item_append_del_p",ITc_eext_rotary_selector_item_append_del_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_item_prepend_clear_p",ITc_eext_rotary_selector_item_prepend_clear_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_item_insert_after_p",ITc_eext_rotary_selector_item_insert_after_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_item_insert_before_p",ITc_eext_rotary_selector_item_insert_before_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_item_part_text_set_get_p",ITc_eext_rotary_selector_item_part_text_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_item_domain_translatable_part_text_set_get_p",ITc_eext_rotary_selector_item_domain_translatable_part_text_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_item_part_content_set_get_p",ITc_eext_rotary_selector_item_part_content_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_part_content_set_get_p",ITc_eext_rotary_selector_part_content_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_item_part_color_set_get_p",ITc_eext_rotary_selector_item_part_color_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_part_color_set_get_p",ITc_eext_rotary_selector_part_color_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_selected_item_set_get_p",ITc_eext_rotary_selector_selected_item_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_items_get_p",ITc_eext_rotary_selector_items_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_add_delete_p",ITc_eext_more_option_add_delete_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_direction_set_get_p",ITc_eext_more_option_direction_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_item_append_del_p",ITc_eext_more_option_item_append_del_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_item_prepend_del_p",ITc_eext_more_option_item_prepend_del_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_item_insert_after_clear_p",ITc_eext_more_option_item_insert_after_clear_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_item_insert_before_clear_p",ITc_eext_more_option_item_insert_before_clear_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_item_part_text_set_get_p",ITc_eext_more_option_item_part_text_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_item_domain_translatable_part_text_set_get_p",ITc_eext_more_option_item_domain_translatable_part_text_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_item_part_content_set_get_p",ITc_eext_more_option_item_part_content_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_opened_set_get_p",ITc_eext_more_option_opened_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_items_get_p",ITc_eext_more_option_items_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_spinner_add_p",ITc_eext_circle_object_spinner_add_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_spinner_angle_set_p",ITc_eext_circle_object_spinner_angle_set_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_item_value_set_get_p",ITc_eext_circle_object_item_value_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_item_color_set_get_p",ITc_eext_circle_object_item_color_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_item_radius_set_get_p",ITc_eext_circle_object_item_radius_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_item_line_width_set_get_p",ITc_eext_circle_object_item_line_width_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_item_angle_set_get_p",ITc_eext_circle_object_item_angle_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_item_angle_offset_set_get_p",ITc_eext_circle_object_item_angle_offset_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_item_angle_min_max_set_get_p",ITc_eext_circle_object_item_angle_min_max_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_circle_object_item_value_min_max_set_get_p",ITc_eext_circle_object_item_value_min_max_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_efl_ext_eext_circle_object_mirrored_set_get_p",ITc_efl_ext_eext_circle_object_mirrored_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_editing_enable_set_get_p",ITc_eext_more_option_editing_enable_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_add_item_enabled_set_get_p",ITc_eext_more_option_add_item_enabled_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_more_option_item_delete_enabled_set_get_p",ITc_eext_more_option_item_delete_enabled_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_editing_enabled_set_get_p",ITc_eext_rotary_selector_editing_enabled_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_add_item_enabled_set_get_p",ITc_eext_rotary_selector_add_item_enabled_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_selector_item_delete_enabled_set_get_p",ITc_eext_rotary_selector_item_delete_enabled_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_panel_add",ITc_eext_panel_add,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_panel_part_content_get_set",ITc_eext_panel_part_content_get_set,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_rotary_event_activated_object_get_p", ITc_eext_rotary_event_activated_object_get_p, ITs_efl_ext_startup, ITs_efl_ext_cleanup},
	{"ITc_eext_popup_add_p", ITc_eext_popup_add_p, ITs_efl_ext_startup, ITs_efl_ext_cleanup},
	{NULL, NULL}
};

#endif // __TCT_EFL-EXT-NATIVE_H__
