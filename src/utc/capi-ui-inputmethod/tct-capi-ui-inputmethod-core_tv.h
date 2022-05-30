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
#ifndef __TCT_CAPI-UI-INPUTMETHOD-NATIVE_H__
#define __TCT_CAPI-UI-INPUTMETHOD-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_capi_ui_inputmethod_startup(void);
extern void utc_capi_ui_inputmethod_cleanup(void);

extern int utc_ime_run_p(void);
extern int utc_ime_event_set_focus_in_cb_p(void);
extern int utc_ime_event_set_focus_out_cb_p(void);
extern int utc_ime_event_set_surrounding_text_updated_cb_p(void);
extern int utc_ime_event_set_input_context_reset_cb_p(void);
extern int utc_ime_event_set_cursor_position_updated_cb_p(void);
extern int utc_ime_event_set_language_requested_cb_p(void);
extern int utc_ime_event_set_language_set_cb_p(void);
extern int utc_ime_event_set_imdata_set_cb_p(void);
extern int utc_ime_event_set_imdata_requested_cb_p(void);
extern int utc_ime_event_set_layout_set_cb_p(void);
extern int utc_ime_event_set_return_key_type_set_cb_p(void);
extern int utc_ime_event_set_return_key_state_set_cb_p(void);
extern int utc_ime_event_set_geometry_requested_cb_p(void);
extern int utc_ime_event_set_process_key_event_cb_p(void);
extern int utc_ime_event_set_display_language_changed_cb_p(void);
extern int utc_ime_event_set_rotation_degree_changed_cb_p(void);
extern int utc_ime_event_set_accessibility_state_changed_cb_p(void);
extern int utc_ime_event_set_option_window_created_cb_p(void);
extern int utc_ime_event_set_option_window_destroyed_cb_p(void);
extern int utc_ime_send_key_event_p(void);
extern int utc_ime_commit_string_p(void);
extern int utc_ime_show_preedit_string_p(void);
extern int utc_ime_hide_preedit_string_p(void);
extern int utc_ime_update_preedit_string_p(void);
extern int utc_ime_request_surrounding_text_p(void);
extern int utc_ime_delete_surrounding_text_p(void);
extern int utc_ime_get_surrounding_text_p(void);
extern int utc_ime_set_selection_p(void);
extern int utc_ime_get_main_window_p(void);
extern int utc_ime_set_size_p(void);
extern int utc_ime_create_option_window_p(void);
extern int utc_ime_destroy_option_window_p(void);
extern int utc_ime_event_set_prediction_hint_set_cb_p(void);
extern int utc_ime_send_private_command_p(void);
extern int utc_ime_event_set_mime_type_set_request_cb_p(void);
extern int utc_ime_commit_content_p(void);
extern int utc_ime_set_floating_mode_p(void);
extern int utc_ime_set_floating_drag_start_p(void);
extern int utc_ime_set_floating_drag_end_p(void);
extern int utc_ime_get_selected_text_p(void);
extern int utc_ime_request_hide_p(void);
extern int utc_ime_event_set_prediction_hint_data_set_cb_p(void);
extern int utc_ime_update_input_panel_event_p(void);
extern int utc_ime_event_set_process_key_event_with_keycode_cb_p(void);
extern int utc_ime_set_candidate_visibility_state_p(void);
extern int utc_ime_run_n(void);
extern int utc_ime_run_n2(void);
extern int utc_ime_event_set_focus_in_cb_n(void);
extern int utc_ime_event_set_focus_out_cb_n(void);
extern int utc_ime_event_set_surrounding_text_updated_cb_n(void);
extern int utc_ime_event_set_input_context_reset_cb_n(void);
extern int utc_ime_event_set_cursor_position_updated_cb_n(void);
extern int utc_ime_event_set_language_requested_cb_n(void);
extern int utc_ime_event_set_language_set_cb_n(void);
extern int utc_ime_event_set_imdata_set_cb_n(void);
extern int utc_ime_event_set_imdata_requested_cb_n(void);
extern int utc_ime_event_set_layout_set_cb_n(void);
extern int utc_ime_event_set_return_key_type_set_cb_n(void);
extern int utc_ime_event_set_return_key_state_set_cb_n(void);
extern int utc_ime_event_set_geometry_requested_cb_n(void);
extern int utc_ime_event_set_process_key_event_cb_n(void);
extern int utc_ime_event_set_display_language_changed_cb_n(void);
extern int utc_ime_event_set_rotation_degree_changed_cb_n(void);
extern int utc_ime_event_set_accessibility_state_changed_cb_n(void);
extern int utc_ime_event_set_option_window_created_cb_n(void);
extern int utc_ime_event_set_option_window_destroyed_cb_n(void);
extern int utc_ime_send_key_event_n(void);
extern int utc_ime_commit_string_n(void);
extern int utc_ime_commit_string_n2(void);
extern int utc_ime_show_preedit_string_n(void);
extern int utc_ime_hide_preedit_string_n(void);
extern int utc_ime_update_preedit_string_n(void);
extern int utc_ime_update_preedit_string_n2(void);
extern int utc_ime_request_surrounding_text_n(void);
extern int utc_ime_request_surrounding_text_n2(void);
extern int utc_ime_delete_surrounding_text_n(void);
extern int utc_ime_delete_surrounding_text_n2(void);
extern int utc_ime_get_surrounding_text_n(void);
extern int utc_ime_set_selection_n(void);
extern int utc_ime_get_main_window_n(void);
extern int utc_ime_set_size_n(void);
extern int utc_ime_set_size_n2(void);
extern int utc_ime_create_option_window_n(void);
extern int utc_ime_create_option_window_n2(void);
extern int utc_ime_destroy_option_window_n(void);
extern int utc_ime_destroy_option_window_n2(void);
extern int utc_ime_destroy_option_window_n3(void);
extern int utc_ime_context_get_layout_n(void);
extern int utc_ime_context_get_layout_n2(void);
extern int utc_ime_context_get_layout_variation_n(void);
extern int utc_ime_context_get_layout_variation_n2(void);
extern int utc_ime_context_get_cursor_position_n(void);
extern int utc_ime_context_get_cursor_position_n2(void);
extern int utc_ime_context_get_autocapital_type_n(void);
extern int utc_ime_context_get_autocapital_type_n2(void);
extern int utc_ime_context_get_return_key_type_n(void);
extern int utc_ime_context_get_return_key_type_n2(void);
extern int utc_ime_context_get_return_key_state_n(void);
extern int utc_ime_context_get_return_key_state_n2(void);
extern int utc_ime_context_get_prediction_mode_n(void);
extern int utc_ime_context_get_prediction_mode_n2(void);
extern int utc_ime_context_get_password_mode_n(void);
extern int utc_ime_context_get_password_mode_n2(void);
extern int utc_ime_context_get_input_hint_n(void);
extern int utc_ime_context_get_input_hint_n2(void);
extern int utc_ime_context_get_bidi_direction_n(void);
extern int utc_ime_context_get_bidi_direction_n2(void);
extern int utc_ime_context_get_language_n(void);
extern int utc_ime_context_get_language_n2(void);
extern int utc_ime_device_info_get_name_n(void);
extern int utc_ime_device_info_get_name_n2(void);
extern int utc_ime_device_info_get_class_n(void);
extern int utc_ime_device_info_get_class_n2(void);
extern int utc_ime_device_info_get_subclass_n(void);
extern int utc_ime_device_info_get_subclass_n2(void);
extern int utc_ime_event_set_prediction_hint_set_cb_n(void);
extern int utc_ime_send_private_command_n(void);
extern int utc_ime_send_private_command_n2(void);
extern int utc_ime_event_set_mime_type_set_request_cb_n(void);
extern int utc_ime_commit_content_n(void);
extern int utc_ime_commit_content_n2(void);
extern int utc_ime_set_floating_mode_n(void);
extern int utc_ime_set_floating_drag_start_n(void);
extern int utc_ime_set_floating_drag_end_n(void);
extern int utc_ime_get_selected_text_n(void);
extern int utc_ime_get_selected_text_n2(void);
extern int utc_ime_request_hide_n(void);
extern int utc_ime_event_set_prediction_hint_data_set_cb_n(void);
extern int utc_ime_update_input_panel_event_n(void);
extern int utc_ime_event_set_process_key_event_with_keycode_cb_n(void);
extern int utc_ime_set_candidate_visibility_state_n(void);

testcase tc_array[] = {
	{"utc_ime_run_p",utc_ime_run_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_focus_in_cb_p",utc_ime_event_set_focus_in_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_focus_out_cb_p",utc_ime_event_set_focus_out_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_surrounding_text_updated_cb_p",utc_ime_event_set_surrounding_text_updated_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_input_context_reset_cb_p",utc_ime_event_set_input_context_reset_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_cursor_position_updated_cb_p",utc_ime_event_set_cursor_position_updated_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_language_requested_cb_p",utc_ime_event_set_language_requested_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_language_set_cb_p",utc_ime_event_set_language_set_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_imdata_set_cb_p",utc_ime_event_set_imdata_set_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_imdata_requested_cb_p",utc_ime_event_set_imdata_requested_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_layout_set_cb_p",utc_ime_event_set_layout_set_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_return_key_type_set_cb_p",utc_ime_event_set_return_key_type_set_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_return_key_state_set_cb_p",utc_ime_event_set_return_key_state_set_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_geometry_requested_cb_p",utc_ime_event_set_geometry_requested_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_process_key_event_cb_p",utc_ime_event_set_process_key_event_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_display_language_changed_cb_p",utc_ime_event_set_display_language_changed_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_rotation_degree_changed_cb_p",utc_ime_event_set_rotation_degree_changed_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_accessibility_state_changed_cb_p",utc_ime_event_set_accessibility_state_changed_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_option_window_created_cb_p",utc_ime_event_set_option_window_created_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_option_window_destroyed_cb_p",utc_ime_event_set_option_window_destroyed_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_send_key_event_p",utc_ime_send_key_event_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_commit_string_p",utc_ime_commit_string_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_show_preedit_string_p",utc_ime_show_preedit_string_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_hide_preedit_string_p",utc_ime_hide_preedit_string_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_update_preedit_string_p",utc_ime_update_preedit_string_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_request_surrounding_text_p",utc_ime_request_surrounding_text_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_delete_surrounding_text_p",utc_ime_delete_surrounding_text_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_get_surrounding_text_p",utc_ime_get_surrounding_text_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_selection_p",utc_ime_set_selection_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_get_main_window_p",utc_ime_get_main_window_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_size_p",utc_ime_set_size_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_create_option_window_p",utc_ime_create_option_window_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_destroy_option_window_p",utc_ime_destroy_option_window_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_prediction_hint_set_cb_p",utc_ime_event_set_prediction_hint_set_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_send_private_command_p",utc_ime_send_private_command_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_mime_type_set_request_cb_p",utc_ime_event_set_mime_type_set_request_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_commit_content_p",utc_ime_commit_content_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_floating_mode_p",utc_ime_set_floating_mode_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_floating_drag_start_p",utc_ime_set_floating_drag_start_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_floating_drag_end_p",utc_ime_set_floating_drag_end_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_get_selected_text_p",utc_ime_get_selected_text_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_request_hide_p",utc_ime_request_hide_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_prediction_hint_data_set_cb_p",utc_ime_event_set_prediction_hint_data_set_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_update_input_panel_event_p",utc_ime_update_input_panel_event_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_process_key_event_with_keycode_cb_p",utc_ime_event_set_process_key_event_with_keycode_cb_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_candidate_visibility_state_p",utc_ime_set_candidate_visibility_state_p,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_run_n",utc_ime_run_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_run_n2",utc_ime_run_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_focus_in_cb_n",utc_ime_event_set_focus_in_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_focus_out_cb_n",utc_ime_event_set_focus_out_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_surrounding_text_updated_cb_n",utc_ime_event_set_surrounding_text_updated_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_input_context_reset_cb_n",utc_ime_event_set_input_context_reset_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_cursor_position_updated_cb_n",utc_ime_event_set_cursor_position_updated_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_language_requested_cb_n",utc_ime_event_set_language_requested_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_language_set_cb_n",utc_ime_event_set_language_set_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_imdata_set_cb_n",utc_ime_event_set_imdata_set_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_imdata_requested_cb_n",utc_ime_event_set_imdata_requested_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_layout_set_cb_n",utc_ime_event_set_layout_set_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_return_key_type_set_cb_n",utc_ime_event_set_return_key_type_set_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_return_key_state_set_cb_n",utc_ime_event_set_return_key_state_set_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_geometry_requested_cb_n",utc_ime_event_set_geometry_requested_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_process_key_event_cb_n",utc_ime_event_set_process_key_event_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_display_language_changed_cb_n",utc_ime_event_set_display_language_changed_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_rotation_degree_changed_cb_n",utc_ime_event_set_rotation_degree_changed_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_accessibility_state_changed_cb_n",utc_ime_event_set_accessibility_state_changed_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_option_window_created_cb_n",utc_ime_event_set_option_window_created_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_option_window_destroyed_cb_n",utc_ime_event_set_option_window_destroyed_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_send_key_event_n",utc_ime_send_key_event_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_commit_string_n",utc_ime_commit_string_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_commit_string_n2",utc_ime_commit_string_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_show_preedit_string_n",utc_ime_show_preedit_string_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_hide_preedit_string_n",utc_ime_hide_preedit_string_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_update_preedit_string_n",utc_ime_update_preedit_string_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_update_preedit_string_n2",utc_ime_update_preedit_string_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_request_surrounding_text_n",utc_ime_request_surrounding_text_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_request_surrounding_text_n2",utc_ime_request_surrounding_text_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_delete_surrounding_text_n",utc_ime_delete_surrounding_text_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_delete_surrounding_text_n2",utc_ime_delete_surrounding_text_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_get_surrounding_text_n",utc_ime_get_surrounding_text_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_selection_n",utc_ime_set_selection_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_get_main_window_n",utc_ime_get_main_window_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_size_n",utc_ime_set_size_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_size_n2",utc_ime_set_size_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_create_option_window_n",utc_ime_create_option_window_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_create_option_window_n2",utc_ime_create_option_window_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_destroy_option_window_n",utc_ime_destroy_option_window_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_destroy_option_window_n2",utc_ime_destroy_option_window_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_destroy_option_window_n3",utc_ime_destroy_option_window_n3,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_layout_n",utc_ime_context_get_layout_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_layout_n2",utc_ime_context_get_layout_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_layout_variation_n",utc_ime_context_get_layout_variation_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_layout_variation_n2",utc_ime_context_get_layout_variation_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_cursor_position_n",utc_ime_context_get_cursor_position_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_cursor_position_n2",utc_ime_context_get_cursor_position_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_autocapital_type_n",utc_ime_context_get_autocapital_type_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_autocapital_type_n2",utc_ime_context_get_autocapital_type_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_return_key_type_n",utc_ime_context_get_return_key_type_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_return_key_type_n2",utc_ime_context_get_return_key_type_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_return_key_state_n",utc_ime_context_get_return_key_state_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_return_key_state_n2",utc_ime_context_get_return_key_state_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_prediction_mode_n",utc_ime_context_get_prediction_mode_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_prediction_mode_n2",utc_ime_context_get_prediction_mode_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_password_mode_n",utc_ime_context_get_password_mode_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_password_mode_n2",utc_ime_context_get_password_mode_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_input_hint_n",utc_ime_context_get_input_hint_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_input_hint_n2",utc_ime_context_get_input_hint_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_bidi_direction_n",utc_ime_context_get_bidi_direction_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_bidi_direction_n2",utc_ime_context_get_bidi_direction_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_language_n",utc_ime_context_get_language_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_context_get_language_n2",utc_ime_context_get_language_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_device_info_get_name_n",utc_ime_device_info_get_name_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_device_info_get_name_n2",utc_ime_device_info_get_name_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_device_info_get_class_n",utc_ime_device_info_get_class_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_device_info_get_class_n2",utc_ime_device_info_get_class_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_device_info_get_subclass_n",utc_ime_device_info_get_subclass_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_device_info_get_subclass_n2",utc_ime_device_info_get_subclass_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_prediction_hint_set_cb_n",utc_ime_event_set_prediction_hint_set_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_send_private_command_n",utc_ime_send_private_command_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_send_private_command_n2",utc_ime_send_private_command_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_mime_type_set_request_cb_n",utc_ime_event_set_mime_type_set_request_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_commit_content_n",utc_ime_commit_content_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_commit_content_n2",utc_ime_commit_content_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_floating_mode_n",utc_ime_set_floating_mode_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_floating_drag_start_n",utc_ime_set_floating_drag_start_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_floating_drag_end_n",utc_ime_set_floating_drag_end_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_get_selected_text_n",utc_ime_get_selected_text_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_get_selected_text_n2",utc_ime_get_selected_text_n2,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_request_hide_n",utc_ime_request_hide_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_prediction_hint_data_set_cb_n",utc_ime_event_set_prediction_hint_data_set_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_update_input_panel_event_n",utc_ime_update_input_panel_event_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_event_set_process_key_event_with_keycode_cb_n",utc_ime_event_set_process_key_event_with_keycode_cb_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{"utc_ime_set_candidate_visibility_state_n",utc_ime_set_candidate_visibility_state_n,utc_capi_ui_inputmethod_startup,utc_capi_ui_inputmethod_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAPI-UI-INPUTMETHOD-NATIVE_H__