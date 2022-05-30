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
#ifndef __TCT_NOTIFICATION-NATIVE_H__
#define __TCT_NOTIFICATION-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_notification_startup(void);
extern void ITs_notification_cleanup(void);

extern void ITs_notification_startup(void);
extern void ITs_notification_cleanup(void);
extern void ITs_notification_ex_item_startup(void);
extern void ITs_notification_ex_item_cleanup(void);
extern void ITs_notification_ex_reporter_startup(void);
extern void ITs_notification_ex_reporter_cleanup(void);
extern void ITs_notification_ex_action_app_control_startup(void);
extern void ITs_notification_ex_action_app_control_cleanup(void);
extern void ITs_notification_ex_button_startup(void);
extern void ITs_notification_ex_button_cleanup(void);
extern void ITs_notification_ex_chat_message_startup(void);
extern void ITs_notification_ex_chat_message_cleanup(void);
extern void ITs_notification_ex_checkbox_startup(void);
extern void ITs_notification_ex_checkbox_cleanup(void);
extern void ITs_notification_ex_entry_startup(void);
extern void ITs_notification_ex_entry_cleanup(void);
extern void ITs_notification_ex_group_startup(void);
extern void ITs_notification_ex_group_cleanup(void);
extern void ITs_notification_ex_image_startup(void);
extern void ITs_notification_ex_image_cleanup(void);
extern void ITs_notification_ex_input_selector_startup(void);
extern void ITs_notification_ex_input_selector_cleanup(void);
extern void ITs_notification_ex_multi_language_startup(void);
extern void ITs_notification_ex_multi_language_cleanup(void);
extern void ITs_notification_ex_progress_startup(void);
extern void ITs_notification_ex_progress_cleanup(void);
extern void ITs_notification_ex_text_startup(void);
extern void ITs_notification_ex_text_cleanup(void);
extern void ITs_notification_ex_time_startup(void);
extern void ITs_notification_ex_time_cleanup(void);
extern void ITs_notification_ex_visibility_action_startup(void);
extern void ITs_notification_ex_visibility_action_cleanup(void);

extern int ITc_notification_clone_p(void);
extern int ITc_notifiation_create_p(void);
extern int ITc_notification_delete_p(void);
extern int ITc_notification_free_p(void);
extern int ITc_notification_delete_all_p(void);
extern int ITc_notification_set_get_image_p(void);
extern int ITc_notification_set_get_layout_p(void);
extern int ITc_notification_set_get_led_p(void);
extern int ITc_notification_set_get_led_time_period_p(void);
extern int ITc_notification_set_get_size_p(void);
extern int ITc_notification_set_get_text_p(void);
extern int ITc_notification_set_get_sound_p(void);
extern int ITc_notification_set_get_vibration_p(void);
extern int ITc_notification_set_get_time_p(void);
extern int ITc_notification_set_get_time_from_text_p(void);
extern int ITc_notification_set_get_progress_p(void);
extern int ITc_notification_set_get_property_p(void);
extern int ITc_notification_set_get_display_applist_p(void);
extern int ITc_notification_get_type_p(void);
extern int ITc_notification_get_insert_time_p(void);
extern int ITc_notification_status_message_post_p(void);
extern int ITc_notification_update_p(void);
extern int ITc_notification_set_get_tag_p(void);
extern int ITc_notification_load_by_tag_p(void);
extern int ITc_notification_post_p(void);
extern int ITc_notification_set_get_launch_option_p(void);
extern int ITc_notification_set_get_event_handler_p(void);
extern int ITc_notification_get_pkgname_p(void);
extern int ITc_notification_add_remove_button_p(void);
extern int ITc_notification_set_get_auto_remove_p(void);
extern int ITc_notification_create_save_from_template_p(void);
extern int ITc_notification_get_noti_block_state_p(void);
extern int ITc_notification_set_text_input_p(void);
extern int ITc_notification_set_get_extension_image_size_p(void);
extern int ITc_noti_ex_action_app_control_create_p(void);
extern int ITc_noti_ex_action_app_control_set_get_p(void);
extern int ITc_noti_ex_action_visibility_create_destroy_p(void);
extern int ITc_noti_ex_action_visibility_set_p(void);
extern int ITc_noti_ex_action_get_type_p(void);
extern int ITc_noti_ex_action_is_local_p(void);
extern int ITc_noti_ex_action_execute_p(void);
extern int ITc_noti_ex_action_get_extra_p(void);
extern int ITc_noti_ex_item_button_create_p(void);
extern int ITc_noti_ex_item_button_get_title_p(void);
extern int ITc_noti_ex_item_chat_message_create_p(void);
extern int ITc_noti_ex_item_chat_message_get_name_p(void);
extern int ITc_noti_ex_item_chat_message_get_text_p(void);
extern int ITc_noti_ex_item_chat_message_get_image_p(void);
extern int ITc_noti_ex_item_chat_message_get_time_p(void);
extern int ITc_noti_ex_item_chat_message_get_message_type_p(void);
extern int ITc_noti_ex_item_checkbox_create_p(void);
extern int ITc_noti_ex_item_checkbox_get_title_p(void);
extern int ITc_noti_ex_item_entry_create_p(void);
extern int ITc_noti_ex_item_entry_set_get_text_p(void);
extern int ITc_noti_ex_item_group_create_destroy_p(void);
extern int ITc_noti_ex_item_group_set_direction_is_vertical_p(void);
extern int ITc_noti_ex_item_group_get_app_label_p(void);
extern int ITc_noti_ex_item_group_add_remove_child_p(void);
extern int ITc_noti_ex_item_group_foreach_child_p(void);
extern int ITc_noti_ex_item_image_create_p(void);
extern int ITc_noti_ex_item_image_get_image_path_p(void);
extern int ITc_noti_ex_item_input_selector_create_p(void);
extern int ITc_noti_ex_item_input_selector_set_get_contents_p(void);
extern int ITc_noti_ex_item_find_by_id_p(void);
extern int ITc_noti_ex_item_get_type_p(void);
extern int ITc_noti_ex_item_set_get_id_p(void);
extern int ITc_noti_ex_item_set_get_action_p(void);
extern int ITc_noti_ex_item_set_get_style_p(void);
extern int ITc_noti_ex_item_set_get_visible_p(void);
extern int ITc_noti_ex_item_set_get_enable_p(void);
extern int ITc_noti_ex_item_add_remove_receiver_p(void);
extern int ITc_noti_ex_item_get_receiver_list_p(void);
extern int ITc_noti_ex_item_set_get_policy_p(void);
extern int ITc_noti_ex_item_set_get_channel_p(void);
extern int ITc_noti_ex_item_set_get_led_info_p(void);
extern int ITc_noti_ex_item_set_get_sound_path_p(void);
extern int ITc_noti_ex_item_set_get_vibration_path_p(void);
extern int ITc_noti_ex_item_get_info_p(void);
extern int ITc_noti_ex_item_get_sender_app_id_p(void);
extern int ITc_noti_ex_item_set_get_tag_p(void);
extern int ITc_noti_ex_item_progress_create_p(void);
extern int ITc_noti_ex_item_progress_set_get_current_p(void);
extern int ITc_noti_ex_item_progress_get_min_max_p(void);
extern int ITc_noti_ex_item_text_create_p(void);
extern int ITc_noti_ex_item_text_set_get_contents_p(void);
extern int ITc_noti_ex_item_text_get_hyperlink_p(void);
extern int ITc_noti_ex_item_time_create_p(void);
extern int ITc_noti_ex_item_time_get_time_p(void);
extern int ITc_noti_ex_color_create_destroy_p(void);
extern int ITc_noti_ex_color_get_alpha_p(void);
extern int ITc_noti_ex_color_get_red_p(void);
extern int ITc_noti_ex_color_get_green_p(void);
extern int ITc_noti_ex_color_get_blue_p(void);
extern int ITc_noti_ex_padding_create_destroy_p(void);
extern int ITc_noti_ex_padding_get_left_p(void);
extern int ITc_noti_ex_padding_get_top_p(void);
extern int ITc_noti_ex_padding_get_right_p(void);
extern int ITc_noti_ex_padding_get_bottom_p(void);
extern int ITc_noti_ex_geometry_create_destroy_p(void);
extern int ITc_noti_ex_geometry_get_x_p(void);
extern int ITc_noti_ex_geometry_get_y_p(void);
extern int ITc_noti_ex_geometry_get_width_p(void);
extern int ITc_noti_ex_geometry_get_height_p(void);
extern int ITc_noti_ex_style_create_destroy_p(void);
extern int ITc_noti_ex_style_get_padding_p(void);
extern int ITc_noti_ex_style_get_color_p(void);
extern int ITc_noti_ex_style_get_geometry_p(void);
extern int ITc_noti_ex_led_info_create_destroy_p(void);
extern int ITc_noti_ex_led_info_set_get_on_period_p(void);
extern int ITc_noti_ex_led_info_set_get_off_period_p(void);
extern int ITc_noti_ex_led_info_get_color_p(void);
extern int ITc_noti_ex_item_info_set_get_hide_time_p(void);
extern int ITc_noti_ex_item_info_set_get_delete_time_p(void);
extern int ITc_noti_ex_style_set_get_background_image_p(void);
extern int ITc_noti_ex_style_set_get_background_color_p(void);
extern int ITc_noti_ex_item_check_type_exist_p(void);
extern int ITc_noti_ex_item_set_get_ongoing_state_p(void);
extern int ITc_noti_ex_item_progress_set_get_type_p(void);
extern int ITc_noti_ex_item_set_get_main_type_p(void);
extern int ITc_noti_ex_item_find_by_main_type_p(void);
extern int ITc_noti_ex_multi_lang_create_destroy_p(void);
extern int ITc_noti_ex_item_button_set_multi_language_title_p(void);
extern int ITc_noti_ex_item_checkbox_set_multi_language_title_p(void);
extern int ITc_noti_ex_item_text_set_multi_language_p(void);
extern int ITc_noti_ex_item_entry_set_multi_language_p(void);
extern int ITc_noti_ex_item_input_selector_set_multi_language_contents_p(void);
extern int ITc_noti_ex_item_checkbox_set_get_check_state_p(void);
extern int ITc_noti_ex_item_set_get_extension_data_p(void);
extern int ITc_noti_ex_item_info_get_time_p(void);
extern int ITc_noti_ex_reporter_create_destroy_p(void);
extern int ITc_noti_ex_reporter_post_p(void);
extern int ITc_noti_ex_reporter_post_list_p(void);
extern int ITc_noti_ex_reporter_update_p(void);
extern int ITc_noti_ex_reporter_delete_p(void);
extern int ITc_noti_ex_reporter_delete_all_p(void);
extern int ITc_noti_ex_reporter_find_by_root_id_p(void);

testcase tc_array[] = {
	{"ITc_notification_clone_p",ITc_notification_clone_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notifiation_create_p",ITc_notifiation_create_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_delete_p",ITc_notification_delete_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_free_p",ITc_notification_free_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_delete_all_p",ITc_notification_delete_all_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_image_p",ITc_notification_set_get_image_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_layout_p",ITc_notification_set_get_layout_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_led_p",ITc_notification_set_get_led_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_led_time_period_p",ITc_notification_set_get_led_time_period_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_size_p",ITc_notification_set_get_size_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_text_p",ITc_notification_set_get_text_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_sound_p",ITc_notification_set_get_sound_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_vibration_p",ITc_notification_set_get_vibration_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_time_p",ITc_notification_set_get_time_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_time_from_text_p",ITc_notification_set_get_time_from_text_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_progress_p",ITc_notification_set_get_progress_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_property_p",ITc_notification_set_get_property_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_display_applist_p",ITc_notification_set_get_display_applist_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_get_type_p",ITc_notification_get_type_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_get_insert_time_p",ITc_notification_get_insert_time_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_status_message_post_p",ITc_notification_status_message_post_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_update_p",ITc_notification_update_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_tag_p",ITc_notification_set_get_tag_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_load_by_tag_p",ITc_notification_load_by_tag_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_post_p",ITc_notification_post_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_launch_option_p",ITc_notification_set_get_launch_option_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_event_handler_p",ITc_notification_set_get_event_handler_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_get_pkgname_p",ITc_notification_get_pkgname_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_add_remove_button_p",ITc_notification_add_remove_button_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_auto_remove_p",ITc_notification_set_get_auto_remove_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_create_save_from_template_p",ITc_notification_create_save_from_template_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_get_noti_block_state_p",ITc_notification_get_noti_block_state_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_text_input_p",ITc_notification_set_text_input_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_notification_set_get_extension_image_size_p",ITc_notification_set_get_extension_image_size_p,ITs_notification_startup,ITs_notification_cleanup},
	{"ITc_noti_ex_action_app_control_create_p", ITc_noti_ex_action_app_control_create_p, ITs_notification_ex_action_app_control_startup, ITs_notification_ex_action_app_control_cleanup},
	{"ITc_noti_ex_action_app_control_set_get_p", ITc_noti_ex_action_app_control_set_get_p, ITs_notification_ex_action_app_control_startup, ITs_notification_ex_action_app_control_cleanup},
	{"ITc_noti_ex_action_visibility_create_destroy_p", ITc_noti_ex_action_visibility_create_destroy_p, ITs_notification_ex_visibility_action_startup, ITs_notification_ex_visibility_action_cleanup},
	{"ITc_noti_ex_action_visibility_set_p", ITc_noti_ex_action_visibility_set_p, ITs_notification_ex_visibility_action_startup, ITs_notification_ex_visibility_action_cleanup},
	{"ITc_noti_ex_action_get_type_p", ITc_noti_ex_action_get_type_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_action_is_local_p", ITc_noti_ex_action_is_local_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_action_execute_p", ITc_noti_ex_action_execute_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_action_get_extra_p", ITc_noti_ex_action_get_extra_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_button_create_p", ITc_noti_ex_item_button_create_p, ITs_notification_ex_button_startup, ITs_notification_ex_button_cleanup},
	{"ITc_noti_ex_item_button_get_title_p", ITc_noti_ex_item_button_get_title_p, ITs_notification_ex_button_startup, ITs_notification_ex_button_cleanup},
	{"ITc_noti_ex_item_chat_message_create_p", ITc_noti_ex_item_chat_message_create_p, ITs_notification_ex_chat_message_startup, ITs_notification_ex_chat_message_cleanup},
	{"ITc_noti_ex_item_chat_message_get_name_p", ITc_noti_ex_item_chat_message_get_name_p, ITs_notification_ex_chat_message_startup, ITs_notification_ex_chat_message_cleanup},
	{"ITc_noti_ex_item_chat_message_get_text_p", ITc_noti_ex_item_chat_message_get_text_p, ITs_notification_ex_chat_message_startup, ITs_notification_ex_chat_message_cleanup},
	{"ITc_noti_ex_item_chat_message_get_image_p", ITc_noti_ex_item_chat_message_get_image_p, ITs_notification_ex_chat_message_startup, ITs_notification_ex_chat_message_cleanup},
	{"ITc_noti_ex_item_chat_message_get_time_p", ITc_noti_ex_item_chat_message_get_time_p, ITs_notification_ex_chat_message_startup, ITs_notification_ex_chat_message_cleanup},
	{"ITc_noti_ex_item_chat_message_get_message_type_p", ITc_noti_ex_item_chat_message_get_message_type_p, ITs_notification_ex_chat_message_startup, ITs_notification_ex_chat_message_cleanup},
	{"ITc_noti_ex_item_checkbox_create_p", ITc_noti_ex_item_checkbox_create_p, ITs_notification_ex_checkbox_startup, ITs_notification_ex_checkbox_cleanup},
	{"ITc_noti_ex_item_checkbox_get_title_p", ITc_noti_ex_item_checkbox_get_title_p, ITs_notification_ex_checkbox_startup, ITs_notification_ex_checkbox_cleanup},
	{"ITc_noti_ex_item_entry_create_p", ITc_noti_ex_item_entry_create_p, ITs_notification_ex_entry_startup, ITs_notification_ex_entry_cleanup},
	{"ITc_noti_ex_item_entry_set_get_text_p", ITc_noti_ex_item_entry_set_get_text_p, ITs_notification_ex_entry_startup, ITs_notification_ex_entry_cleanup},
	{"ITc_noti_ex_item_group_create_destroy_p", ITc_noti_ex_item_group_create_destroy_p, ITs_notification_ex_group_startup, ITs_notification_ex_group_cleanup},
	{"ITc_noti_ex_item_group_set_direction_is_vertical_p", ITc_noti_ex_item_group_set_direction_is_vertical_p, ITs_notification_ex_group_startup, ITs_notification_ex_group_cleanup},
	{"ITc_noti_ex_item_group_get_app_label_p", ITc_noti_ex_item_group_get_app_label_p, ITs_notification_ex_group_startup, ITs_notification_ex_group_cleanup},
	{"ITc_noti_ex_item_group_add_remove_child_p", ITc_noti_ex_item_group_add_remove_child_p, ITs_notification_ex_group_startup, ITs_notification_ex_group_cleanup},
	{"ITc_noti_ex_item_group_foreach_child_p", ITc_noti_ex_item_group_foreach_child_p, ITs_notification_ex_group_startup, ITs_notification_ex_group_cleanup},
	{"ITc_noti_ex_item_image_create_p", ITc_noti_ex_item_image_create_p, ITs_notification_ex_image_startup, ITs_notification_ex_image_cleanup},
	{"ITc_noti_ex_item_image_get_image_path_p", ITc_noti_ex_item_image_get_image_path_p, ITs_notification_ex_image_startup, ITs_notification_ex_image_cleanup},
	{"ITc_noti_ex_item_input_selector_create_p", ITc_noti_ex_item_input_selector_create_p, ITs_notification_ex_input_selector_startup, ITs_notification_ex_input_selector_cleanup},
	{"ITc_noti_ex_item_input_selector_set_get_contents_p", ITc_noti_ex_item_input_selector_set_get_contents_p, ITs_notification_ex_input_selector_startup, ITs_notification_ex_input_selector_cleanup},
	{"ITc_noti_ex_item_find_by_id_p", ITc_noti_ex_item_find_by_id_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_get_type_p", ITc_noti_ex_item_get_type_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_id_p", ITc_noti_ex_item_set_get_id_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_action_p", ITc_noti_ex_item_set_get_action_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_style_p", ITc_noti_ex_item_set_get_style_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_visible_p", ITc_noti_ex_item_set_get_visible_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_enable_p", ITc_noti_ex_item_set_get_enable_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_add_remove_receiver_p", ITc_noti_ex_item_add_remove_receiver_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_get_receiver_list_p", ITc_noti_ex_item_get_receiver_list_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_policy_p", ITc_noti_ex_item_set_get_policy_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_channel_p", ITc_noti_ex_item_set_get_channel_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_led_info_p", ITc_noti_ex_item_set_get_led_info_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_sound_path_p", ITc_noti_ex_item_set_get_sound_path_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_vibration_path_p", ITc_noti_ex_item_set_get_vibration_path_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_get_info_p", ITc_noti_ex_item_get_info_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_get_sender_app_id_p", ITc_noti_ex_item_get_sender_app_id_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_tag_p", ITc_noti_ex_item_set_get_tag_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_progress_create_p", ITc_noti_ex_item_progress_create_p, ITs_notification_ex_progress_startup, ITs_notification_ex_progress_cleanup},
	{"ITc_noti_ex_item_progress_set_get_current_p", ITc_noti_ex_item_progress_set_get_current_p, ITs_notification_ex_progress_startup, ITs_notification_ex_progress_cleanup},
	{"ITc_noti_ex_item_progress_get_min_max_p", ITc_noti_ex_item_progress_get_min_max_p, ITs_notification_ex_progress_startup, ITs_notification_ex_progress_cleanup},
	{"ITc_noti_ex_item_text_create_p", ITc_noti_ex_item_text_create_p, ITs_notification_ex_text_startup, ITs_notification_ex_text_cleanup},
	{"ITc_noti_ex_item_text_set_get_contents_p", ITc_noti_ex_item_text_set_get_contents_p, ITs_notification_ex_text_startup, ITs_notification_ex_text_cleanup},
	{"ITc_noti_ex_item_text_get_hyperlink_p", ITc_noti_ex_item_text_get_hyperlink_p, ITs_notification_ex_text_startup, ITs_notification_ex_text_cleanup},
	{"ITc_noti_ex_item_time_create_p", ITc_noti_ex_item_time_create_p, ITs_notification_ex_time_startup, ITs_notification_ex_time_cleanup},
	{"ITc_noti_ex_item_time_get_time_p", ITc_noti_ex_item_time_get_time_p, ITs_notification_ex_time_startup, ITs_notification_ex_time_cleanup},
	{"ITc_noti_ex_color_create_destroy_p", ITc_noti_ex_color_create_destroy_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_color_get_alpha_p", ITc_noti_ex_color_get_alpha_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_color_get_red_p", ITc_noti_ex_color_get_red_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_color_get_green_p", ITc_noti_ex_color_get_green_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_color_get_blue_p", ITc_noti_ex_color_get_blue_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_padding_create_destroy_p", ITc_noti_ex_padding_create_destroy_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_padding_get_left_p", ITc_noti_ex_padding_get_left_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_padding_get_top_p", ITc_noti_ex_padding_get_top_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_padding_get_right_p", ITc_noti_ex_padding_get_right_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_padding_get_bottom_p", ITc_noti_ex_padding_get_bottom_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_geometry_create_destroy_p", ITc_noti_ex_geometry_create_destroy_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_geometry_get_x_p", ITc_noti_ex_geometry_get_x_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_geometry_get_y_p", ITc_noti_ex_geometry_get_y_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_geometry_get_width_p", ITc_noti_ex_geometry_get_width_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_geometry_get_height_p", ITc_noti_ex_geometry_get_height_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_style_create_destroy_p", ITc_noti_ex_style_create_destroy_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_style_get_padding_p", ITc_noti_ex_style_get_padding_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_style_get_color_p", ITc_noti_ex_style_get_color_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_style_get_geometry_p", ITc_noti_ex_style_get_geometry_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_led_info_create_destroy_p", ITc_noti_ex_led_info_create_destroy_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_led_info_set_get_on_period_p", ITc_noti_ex_led_info_set_get_on_period_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_led_info_set_get_off_period_p", ITc_noti_ex_led_info_set_get_off_period_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_led_info_get_color_p", ITc_noti_ex_led_info_get_color_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_info_set_get_hide_time_p", ITc_noti_ex_item_info_set_get_hide_time_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_info_set_get_delete_time_p", ITc_noti_ex_item_info_set_get_delete_time_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_style_set_get_background_image_p", ITc_noti_ex_style_set_get_background_image_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_style_set_get_background_color_p", ITc_noti_ex_style_set_get_background_color_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_check_type_exist_p", ITc_noti_ex_item_check_type_exist_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_set_get_ongoing_state_p", ITc_noti_ex_item_set_get_ongoing_state_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_progress_set_get_type_p", ITc_noti_ex_item_progress_set_get_type_p, ITs_notification_ex_progress_startup, ITs_notification_ex_progress_cleanup},
	{"ITc_noti_ex_item_set_get_main_type_p", ITc_noti_ex_item_set_get_main_type_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_find_by_main_type_p", ITc_noti_ex_item_find_by_main_type_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_multi_lang_create_destroy_p", ITc_noti_ex_multi_lang_create_destroy_p, ITs_notification_ex_multi_language_startup, ITs_notification_ex_multi_language_cleanup},
	{"ITc_noti_ex_item_button_set_multi_language_title_p", ITc_noti_ex_item_button_set_multi_language_title_p, ITs_notification_ex_button_startup, ITs_notification_ex_button_cleanup},
	{"ITc_noti_ex_item_checkbox_set_multi_language_title_p", ITc_noti_ex_item_checkbox_set_multi_language_title_p, ITs_notification_ex_checkbox_startup, ITs_notification_ex_checkbox_cleanup},
	{"ITc_noti_ex_item_text_set_multi_language_p", ITc_noti_ex_item_text_set_multi_language_p, ITs_notification_ex_text_startup, ITs_notification_ex_text_cleanup},
	{"ITc_noti_ex_item_entry_set_multi_language_p", ITc_noti_ex_item_entry_set_multi_language_p, ITs_notification_ex_entry_startup, ITs_notification_ex_entry_cleanup},
	{"ITc_noti_ex_item_input_selector_set_multi_language_contents_p", ITc_noti_ex_item_input_selector_set_multi_language_contents_p, ITs_notification_ex_input_selector_startup, ITs_notification_ex_input_selector_cleanup},
	{"ITc_noti_ex_item_checkbox_set_get_check_state_p", ITc_noti_ex_item_checkbox_set_get_check_state_p, ITs_notification_ex_checkbox_startup, ITs_notification_ex_checkbox_cleanup},
	{"ITc_noti_ex_item_set_get_extension_data_p", ITc_noti_ex_item_set_get_extension_data_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
	{"ITc_noti_ex_item_info_get_time_p", ITc_noti_ex_item_info_get_time_p, ITs_notification_ex_item_startup, ITs_notification_ex_item_cleanup},
        {"ITc_noti_ex_reporter_create_destroy_p", ITc_noti_ex_reporter_create_destroy_p, ITs_notification_ex_reporter_startup, ITs_notification_ex_reporter_cleanup},
        {"ITc_noti_ex_reporter_post_p", ITc_noti_ex_reporter_post_p, ITs_notification_ex_reporter_startup, ITs_notification_ex_reporter_cleanup},
	{"ITc_noti_ex_reporter_post_list_p", ITc_noti_ex_reporter_post_list_p, ITs_notification_ex_reporter_startup, ITs_notification_ex_reporter_cleanup},
	{"ITc_noti_ex_reporter_update_p", ITc_noti_ex_reporter_update_p, ITs_notification_ex_reporter_startup, ITs_notification_ex_reporter_cleanup},
	{"ITc_noti_ex_reporter_delete_p", ITc_noti_ex_reporter_delete_p, ITs_notification_ex_reporter_startup, ITs_notification_ex_reporter_cleanup},
	{"ITc_noti_ex_reporter_delete_all_p", ITc_noti_ex_reporter_delete_all_p, ITs_notification_ex_reporter_startup, ITs_notification_ex_reporter_cleanup},
	{"ITc_noti_ex_reporter_find_by_root_id_p", ITc_noti_ex_reporter_find_by_root_id_p, ITs_notification_ex_reporter_startup, ITs_notification_ex_reporter_cleanup},
	{NULL, NULL}
};

#endif // __TCT_NOTIFICATION-NATIVE_H__
