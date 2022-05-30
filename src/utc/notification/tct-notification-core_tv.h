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
#ifndef __TCT_NOTIFICATION_NATIVE_H__
#define __TCT_NOTIFICATION_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_notification_startup(void);
extern void utc_notification_cleanup(void);
extern void utc_notification_ex_item_startup(void);
extern void utc_notification_ex_item_cleanup(void);
extern void utc_notification_ex_manager_startup(void);
extern void utc_notification_ex_manager_cleanup(void);
extern void utc_notification_ex_reporter_startup(void);
extern void utc_notification_ex_reporter_cleanup(void);
extern void utc_notification_ex_image_startup(void);
extern void utc_notification_ex_image_cleanup(void);
extern void utc_notification_ex_input_selector_startup(void);
extern void utc_notification_ex_input_selector_cleanup(void);
extern void utc_notification_ex_progress_startup(void);
extern void utc_notification_ex_progress_cleanup(void);
extern void utc_notification_ex_text_startup(void);
extern void utc_notification_ex_text_cleanup(void);
extern void utc_notification_ex_time_startup(void);
extern void utc_notification_ex_time_cleanup(void);
extern void utc_notification_ex_visibility_action_startup(void);
extern void utc_notification_ex_visibility_action_cleanup(void);
extern void utc_notification_ex_app_control_action_startup(void);
extern void utc_notification_ex_app_control_action_cleanup(void);
extern void utc_notification_ex_button_startup(void);
extern void utc_notification_ex_button_cleanup(void);
extern void utc_notification_ex_chat_message_startup(void);
extern void utc_notification_ex_chat_message_cleanup(void);
extern void utc_notification_ex_checkbox_startup(void);
extern void utc_notification_ex_checkbox_cleanup(void);
extern void utc_notification_ex_entry_startup(void);
extern void utc_notification_ex_entry_cleanup(void);
extern void utc_notification_ex_event_info_startup(void);
extern void utc_notification_ex_event_info_cleanup(void);
extern void utc_notification_ex_group_startup(void);
extern void utc_notification_ex_group_cleanup(void);
extern void utc_notification_ex_multi_language_startup(void);
extern void utc_notification_ex_multi_language_cleanup(void);

extern int utc_notification_create_1_n(void);
extern int utc_notification_create_2_n(void);
extern int utc_notification_create_1_p(void);
extern int utc_notification_create_2_p(void);
extern int utc_notification_set_image_n(void);
extern int utc_notification_set_image_1_p(void);
extern int utc_notification_set_image_2_p(void);
extern int utc_notification_set_image_3_p(void);
extern int utc_notification_set_image_4_p(void);
extern int utc_notification_set_image_5_p(void);
extern int utc_notification_set_image_6_p(void);
extern int utc_notification_set_image_7_p(void);
extern int utc_notification_set_image_8_p(void);
extern int utc_notification_set_image_9_p(void);
extern int utc_notification_set_image_10_p(void);
extern int utc_notification_set_image_11_p(void);
extern int utc_notification_set_image_12_p(void);
extern int utc_notification_set_image_13_p(void);
extern int utc_notification_set_image_14_p(void);
extern int utc_notification_set_image_15_p(void);
extern int utc_notification_set_image_16_p(void);
extern int utc_notification_set_image_17_p(void);
extern int utc_notification_set_image_18_p(void);
extern int utc_notification_set_image_19_p(void);
extern int utc_notification_set_image_20_p(void);
extern int utc_notification_set_image_21_p(void);
extern int utc_notification_set_image_22_p(void);
extern int utc_notification_set_image_23_p(void);
extern int utc_notification_get_image_n(void);
extern int utc_notification_get_image_1_p(void);
extern int utc_notification_get_image_2_p(void);
extern int utc_notification_get_image_3_p(void);
extern int utc_notification_get_image_4_p(void);
extern int utc_notification_get_image_5_p(void);
extern int utc_notification_get_image_6_p(void);
extern int utc_notification_get_image_7_p(void);
extern int utc_notification_get_image_8_p(void);
extern int utc_notification_get_image_9_p(void);
extern int utc_notification_get_image_10_p(void);
extern int utc_notification_get_image_11_p(void);
extern int utc_notification_get_image_12_p(void);
extern int utc_notification_get_image_13_p(void);
extern int utc_notification_get_image_14_p(void);
extern int utc_notification_get_image_15_p(void);
extern int utc_notification_get_image_16_p(void);
extern int utc_notification_get_image_17_p(void);
extern int utc_notification_get_image_18_p(void);
extern int utc_notification_get_image_19_p(void);
extern int utc_notification_get_image_20_p(void);
extern int utc_notification_get_image_21_p(void);
extern int utc_notification_get_image_22_p(void);
extern int utc_notification_get_image_23_p(void);
extern int utc_notification_set_time_n(void);
extern int utc_notification_set_time_p(void);
extern int utc_notification_get_time_n(void);
extern int utc_notification_get_time_1_p(void);
extern int utc_notification_get_time_2_p(void);
extern int utc_notification_get_insert_time_n(void);
extern int utc_notification_get_insert_time_1_p(void);
extern int utc_notification_get_insert_time_2_p(void);
extern int utc_notification_set_text_n(void);
extern int utc_notification_set_text_1_p(void);
extern int utc_notification_set_text_2_p(void);
extern int utc_notification_set_text_3_p(void);
extern int utc_notification_set_text_4_p(void);
extern int utc_notification_set_text_5_p(void);
extern int utc_notification_set_text_6_p(void);
extern int utc_notification_set_text_7_p(void);
extern int utc_notification_set_text_8_p(void);
extern int utc_notification_set_text_9_p(void);
extern int utc_notification_set_text_10_p(void);
extern int utc_notification_set_text_11_p(void);
extern int utc_notification_set_text_12_p(void);
extern int utc_notification_set_text_13_p(void);
extern int utc_notification_set_text_14_p(void);
extern int utc_notification_set_text_15_p(void);
extern int utc_notification_set_text_16_p(void);
extern int utc_notification_set_text_17_p(void);
extern int utc_notification_set_text_18_p(void);
extern int utc_notification_set_text_19_p(void);
extern int utc_notification_set_text_20_p(void);
extern int utc_notification_set_text_21_p(void);
extern int utc_notification_set_text_22_p(void);
extern int utc_notification_set_text_23_p(void);
extern int utc_notification_set_text_24_p(void);
extern int utc_notification_set_text_25_p(void);
extern int utc_notification_get_text_n(void);
extern int utc_notification_get_text_1_p(void);
extern int utc_notification_get_text_2_p(void);
extern int utc_notification_get_text_3_p(void);
extern int utc_notification_get_text_4_p(void);
extern int utc_notification_get_text_5_p(void);
extern int utc_notification_get_text_6_p(void);
extern int utc_notification_get_text_7_p(void);
extern int utc_notification_get_text_8_p(void);
extern int utc_notification_get_text_9_p(void);
extern int utc_notification_get_text_10_p(void);
extern int utc_notification_get_text_11_p(void);
extern int utc_notification_get_text_12_p(void);
extern int utc_notification_get_text_13_p(void);
extern int utc_notification_get_text_14_p(void);
extern int utc_notification_get_text_15_p(void);
extern int utc_notification_get_text_16_p(void);
extern int utc_notification_get_text_17_p(void);
extern int utc_notification_get_text_18_p(void);
extern int utc_notification_get_text_19_p(void);
extern int utc_notification_get_text_20_p(void);
extern int utc_notification_get_text_21_p(void);
extern int utc_notification_get_text_22_p(void);
extern int utc_notification_get_text_23_p(void);
extern int utc_notification_set_time_to_text_n(void);
extern int utc_notification_set_time_to_text_1_p(void);
extern int utc_notification_set_time_to_text_2_p(void);
extern int utc_notification_set_time_to_text_3_p(void);
extern int utc_notification_set_time_to_text_4_p(void);
extern int utc_notification_set_time_to_text_5_p(void);
extern int utc_notification_set_time_to_text_6_p(void);
extern int utc_notification_set_time_to_text_7_p(void);
extern int utc_notification_set_time_to_text_8_p(void);
extern int utc_notification_set_time_to_text_9_p(void);
extern int utc_notification_set_time_to_text_10_p(void);
extern int utc_notification_set_time_to_text_11_p(void);
extern int utc_notification_set_time_to_text_12_p(void);
extern int utc_notification_set_time_to_text_13_p(void);
extern int utc_notification_set_time_to_text_14_p(void);
extern int utc_notification_set_time_to_text_15_p(void);
extern int utc_notification_set_time_to_text_16_p(void);
extern int utc_notification_set_time_to_text_17_p(void);
extern int utc_notification_set_time_to_text_18_p(void);
extern int utc_notification_set_time_to_text_19_p(void);
extern int utc_notification_get_time_from_text_n(void);
extern int utc_notification_get_time_from_text_1_p(void);
extern int utc_notification_get_time_from_text_2_p(void);
extern int utc_notification_get_time_from_text_3_p(void);
extern int utc_notification_get_time_from_text_4_p(void);
extern int utc_notification_get_time_from_text_5_p(void);
extern int utc_notification_get_time_from_text_6_p(void);
extern int utc_notification_get_time_from_text_7_p(void);
extern int utc_notification_get_time_from_text_8_p(void);
extern int utc_notification_get_time_from_text_9_p(void);
extern int utc_notification_get_time_from_text_10_p(void);
extern int utc_notification_get_time_from_text_11_p(void);
extern int utc_notification_get_time_from_text_12_p(void);
extern int utc_notification_get_time_from_text_13_p(void);
extern int utc_notification_get_time_from_text_14_p(void);
extern int utc_notification_get_time_from_text_15_p(void);
extern int utc_notification_get_time_from_text_16_p(void);
extern int utc_notification_get_time_from_text_17_p(void);
extern int utc_notification_get_time_from_text_18_p(void);
extern int utc_notification_get_time_from_text_19_p(void);
extern int utc_notification_get_time_from_text_20_p(void);
extern int utc_notification_set_sound_n(void);
extern int utc_notification_set_sound_p(void);
extern int utc_notification_get_sound_n(void);
extern int utc_notification_get_sound_1_p(void);
extern int utc_notification_get_sound_2_p(void);
extern int utc_notification_set_vibration_n(void);
extern int utc_notification_set_vibration_p(void);
extern int utc_notification_get_vibration_n(void);
extern int utc_notification_get_vibration_1_p(void);
extern int utc_notification_get_vibration_2_p(void);
extern int utc_notification_set_led_n(void);
extern int utc_notification_set_led_p(void);
extern int utc_notification_get_led_n(void);
extern int utc_notification_get_led_1_p(void);
extern int utc_notification_get_led_2_p(void);
extern int utc_notification_set_led_time_period_n(void);
extern int utc_notification_set_led_time_period_p(void);
extern int utc_notification_get_led_time_period_n(void);
extern int utc_notification_get_led_time_period_1_p(void);
extern int utc_notification_get_led_time_period_2_p(void);
extern int utc_notification_set_property_n(void);
extern int utc_notification_set_property_1_p(void);
extern int utc_notification_set_property_2_p(void);
extern int utc_notification_set_property_3_p(void);
extern int utc_notification_set_property_4_p(void);
extern int utc_notification_set_property_5_p(void);
extern int utc_notification_set_property_6_p(void);
extern int utc_notification_get_property_n(void);
extern int utc_notification_get_property_1_p(void);
extern int utc_notification_get_property_2_p(void);
extern int utc_notification_set_display_applist_n(void);
extern int utc_notification_set_display_applist_p(void);
extern int utc_notification_get_display_applist_n(void);
extern int utc_notification_get_display_applist_1_p(void);
extern int utc_notification_get_display_applist_2_p(void);
extern int utc_notification_set_size_n(void);
extern int utc_notification_set_size_p(void);
extern int utc_notification_get_size_n(void);
extern int utc_notification_get_size_1_p(void);
extern int utc_notification_get_size_2_p(void);
extern int utc_notification_set_progress_n(void);
extern int utc_notification_set_progress_p(void);
extern int utc_notification_get_progress_n(void);
extern int utc_notification_get_progress_1_p(void);
extern int utc_notification_get_progress_2_p(void);
extern int utc_notification_set_layout_n(void);
extern int utc_notification_set_layout_1_p(void);
extern int utc_notification_set_layout_2_p(void);
extern int utc_notification_set_layout_3_p(void);
extern int utc_notification_set_layout_4_p(void);
extern int utc_notification_set_layout_5_p(void);
extern int utc_notification_get_layout_n(void);
extern int utc_notification_get_layout_1_p(void);
extern int utc_notification_get_layout_2_p(void);
extern int utc_notification_get_type_n(void);
extern int utc_notification_get_type_1_p(void);
extern int utc_notification_get_type_2_p(void);
extern int utc_notification_update_n(void);
extern int utc_notification_update_p(void);
extern int utc_notification_delete_n(void);
extern int utc_notification_delete_p(void);
extern int utc_notification_clone_n(void);
extern int utc_notification_clone_p(void);
extern int utc_notification_free_n(void);
extern int utc_notification_free_p(void);
extern int utc_notification_status_message_post_n(void);
extern int utc_notification_status_message_post_p(void);
extern int utc_notification_set_tag_n(void);
extern int utc_notification_set_tag_p(void);
extern int utc_notification_get_tag_n(void);
extern int utc_notification_get_tag_1_p(void);
extern int utc_notification_get_tag_2_p(void);
extern int utc_notification_load_by_tag_1_n(void);
extern int utc_notification_load_by_tag_2_n(void);
extern int utc_notification_load_by_tag_p(void);
extern int utc_notification_delete_all_1_p(void);
extern int utc_notification_delete_all_2_p(void);
extern int utc_notification_post_n(void);
extern int utc_notification_post_p(void);
extern int utc_notification_set_launch_option_n(void);
extern int utc_notification_set_launch_option_p(void);
extern int utc_notification_get_launch_option_n(void);
extern int utc_notification_get_launch_option_p(void);
extern int utc_notification_get_pkgname_n(void);
extern int utc_notification_get_pkgname_p(void);
extern int utc_notification_set_event_handler_n(void);
extern int utc_notification_set_event_handler_p(void);
extern int utc_notification_get_event_handler_n(void);
extern int utc_notification_get_event_handler_p(void);
extern int utc_notification_add_button_n(void);
extern int utc_notification_add_button_p(void);
extern int utc_notification_remove_button_n(void);
extern int utc_notification_remove_button_p(void);
extern int utc_notification_set_auto_remove_n(void);
extern int utc_notification_set_auto_remove_p(void);
extern int utc_notification_get_auto_remove_n(void);
extern int utc_notification_get_auto_remove_p(void);
extern int utc_notification_save_as_template_n(void);
extern int utc_notification_save_as_template_p(void);
extern int utc_notification_create_from_template_n1(void);
extern int utc_notification_create_from_template_n2(void);
extern int utc_notification_create_from_template_p(void);
extern int utc_notification_get_noti_block_state_n(void);
extern int utc_notification_get_noti_block_state_p(void);
extern int utc_notification_set_text_input_n(void);
extern int utc_notification_set_text_input_p(void);
extern int utc_notification_set_extension_image_size_n(void);
extern int utc_notification_set_extension_image_size_p(void);
extern int utc_notification_get_extension_image_size_n(void);
extern int utc_notification_get_extension_image_size_p(void);
extern int utc_noti_ex_color_create_p(void);
extern int utc_noti_ex_color_create_n(void);
extern int utc_noti_ex_color_destroy_p(void);
extern int utc_noti_ex_color_destroy_n(void);
extern int utc_noti_ex_color_get_alpha_p(void);
extern int utc_noti_ex_color_get_alpha_n(void);
extern int utc_noti_ex_color_get_red_p(void);
extern int utc_noti_ex_color_get_red_n(void);
extern int utc_noti_ex_color_get_green_p(void);
extern int utc_noti_ex_color_get_green_n(void);
extern int utc_noti_ex_color_get_blue_p(void);
extern int utc_noti_ex_color_get_blue_n(void);
extern int utc_noti_ex_padding_create_p(void);
extern int utc_noti_ex_padding_create_n(void);
extern int utc_noti_ex_padding_destroy_p(void);
extern int utc_noti_ex_padding_destroy_n(void);
extern int utc_noti_ex_padding_get_left_p(void);
extern int utc_noti_ex_padding_get_left_n(void);
extern int utc_noti_ex_padding_get_top_p(void);
extern int utc_noti_ex_padding_get_top_n(void);
extern int utc_noti_ex_padding_get_right_p(void);
extern int utc_noti_ex_padding_get_right_n(void);
extern int utc_noti_ex_padding_get_bottom_p(void);
extern int utc_noti_ex_padding_get_bottom_n(void);
extern int utc_noti_ex_geometry_create_p(void);
extern int utc_noti_ex_geometry_create_n(void);
extern int utc_noti_ex_geometry_destroy_p(void);
extern int utc_noti_ex_geometry_destroy_n(void);
extern int utc_noti_ex_geometry_get_x_p(void);
extern int utc_noti_ex_geometry_get_x_n(void);
extern int utc_noti_ex_geometry_get_y_p(void);
extern int utc_noti_ex_geometry_get_y_n(void);
extern int utc_noti_ex_geometry_get_width_p(void);
extern int utc_noti_ex_geometry_get_width_n(void);
extern int utc_noti_ex_geometry_get_height_p(void);
extern int utc_noti_ex_geometry_get_height_n(void);
extern int utc_noti_ex_style_create_p(void);
extern int utc_noti_ex_style_create_n(void);
extern int utc_noti_ex_style_destroy_p(void);
extern int utc_noti_ex_style_destroy_n(void);
extern int utc_noti_ex_style_get_padding_p(void);
extern int utc_noti_ex_style_get_padding_n(void);
extern int utc_noti_ex_style_get_color_p(void);
extern int utc_noti_ex_style_get_color_n(void);
extern int utc_noti_ex_style_get_geometry_p(void);
extern int utc_noti_ex_style_get_geometry_n(void);
extern int utc_noti_ex_style_set_background_image_p(void);
extern int utc_noti_ex_style_set_background_image_n(void);
extern int utc_noti_ex_style_get_background_image_p(void);
extern int utc_noti_ex_style_get_background_image_n(void);
extern int utc_noti_ex_style_set_background_color_p(void);
extern int utc_noti_ex_style_set_background_color_n(void);
extern int utc_noti_ex_style_get_background_color_p(void);
extern int utc_noti_ex_style_get_background_color_n(void);
extern int utc_noti_ex_led_info_create_p(void);
extern int utc_noti_ex_led_info_create_n(void);
extern int utc_noti_ex_led_info_destroy_p(void);
extern int utc_noti_ex_led_info_destroy_n(void);
extern int utc_noti_ex_led_info_set_on_period_p(void);
extern int utc_noti_ex_led_info_set_on_period_n(void);
extern int utc_noti_ex_led_info_get_on_period_p(void);
extern int utc_noti_ex_led_info_get_on_period_n(void);
extern int utc_noti_ex_led_info_set_off_period_p(void);
extern int utc_noti_ex_led_info_set_off_period_n(void);
extern int utc_noti_ex_led_info_get_off_period_p(void);
extern int utc_noti_ex_led_info_get_off_period_n(void);
extern int utc_noti_ex_led_info_get_color_p(void);
extern int utc_noti_ex_led_info_get_color_n(void);
extern int utc_noti_ex_action_destroy_p(void);
extern int utc_noti_ex_action_destroy_n(void);
extern int utc_noti_ex_action_get_type_p(void);
extern int utc_noti_ex_action_get_type_n(void);
extern int utc_noti_ex_action_is_local_p(void);
extern int utc_noti_ex_action_is_local_n(void);
extern int utc_noti_ex_action_execute_p(void);
extern int utc_noti_ex_action_execute_n(void);
extern int utc_noti_ex_action_get_extra_p(void);
extern int utc_noti_ex_action_get_extra_n(void);
extern int utc_noti_ex_item_info_get_hide_time_p(void);
extern int utc_noti_ex_item_info_get_hide_time_n(void);
extern int utc_noti_ex_item_info_set_hide_time_p(void);
extern int utc_noti_ex_item_info_set_hide_time_n(void);
extern int utc_noti_ex_item_info_get_delete_time_p(void);
extern int utc_noti_ex_item_info_get_delete_time_n(void);
extern int utc_noti_ex_item_info_set_delete_time_p(void);
extern int utc_noti_ex_item_info_set_delete_time_n(void);
extern int utc_noti_ex_item_info_get_time_p(void);
extern int utc_noti_ex_item_info_get_time_n(void);
extern int utc_noti_ex_item_destroy_p(void);
extern int utc_noti_ex_item_destroy_p_n(void);
extern int utc_noti_ex_item_find_by_id_p(void);
extern int utc_noti_ex_item_find_by_id_n(void);
extern int utc_noti_ex_item_get_type_p(void);
extern int utc_noti_ex_item_get_type_n(void);
extern int utc_noti_ex_item_get_id_p(void);
extern int utc_noti_ex_item_get_id_n(void);
extern int utc_noti_ex_item_set_id_p(void);
extern int utc_noti_ex_item_set_id_n(void);
extern int utc_noti_ex_item_get_action_p(void);
extern int utc_noti_ex_item_get_action_n(void);
extern int utc_noti_ex_item_set_action_p(void);
extern int utc_noti_ex_item_set_action_n(void);
extern int utc_noti_ex_item_get_style_p(void);
extern int utc_noti_ex_item_get_style_n(void);
extern int utc_noti_ex_item_set_style_p(void);
extern int utc_noti_ex_item_set_style_n(void);
extern int utc_noti_ex_item_set_visible_p(void);
extern int utc_noti_ex_item_set_visible_n(void);
extern int utc_noti_ex_item_get_visible_p(void);
extern int utc_noti_ex_item_get_visible_n(void);
extern int utc_noti_ex_item_set_enable_p(void);
extern int utc_noti_ex_item_set_enable_n(void);
extern int utc_noti_ex_item_get_enable_p(void);
extern int utc_noti_ex_item_get_enable_n(void);
extern int utc_noti_ex_item_add_receiver_p(void);
extern int utc_noti_ex_item_add_receiver_n(void);
extern int utc_noti_ex_item_get_receiver_list_p(void);
extern int utc_noti_ex_item_get_receiver_list_n(void);
extern int utc_noti_ex_item_remove_receiver_p(void);
extern int utc_noti_ex_item_remove_receiver_n(void);
extern int utc_noti_ex_item_set_policy_p(void);
extern int utc_noti_ex_item_set_policy_n(void);
extern int utc_noti_ex_item_get_policy_p(void);
extern int utc_noti_ex_item_get_policy_n(void);
extern int utc_noti_ex_item_set_channel_p(void);
extern int utc_noti_ex_item_set_channel_n(void);
extern int utc_noti_ex_item_get_channel_p(void);
extern int utc_noti_ex_item_get_channel_n(void);
extern int utc_noti_ex_item_set_led_info_p(void);
extern int utc_noti_ex_item_set_led_info_n(void);
extern int utc_noti_ex_item_get_led_info_p(void);
extern int utc_noti_ex_item_get_led_info_n(void);
extern int utc_noti_ex_item_set_sound_path_p(void);
extern int utc_noti_ex_item_set_sound_path_n(void);
extern int utc_noti_ex_item_get_sound_path_p(void);
extern int utc_noti_ex_item_get_sound_path_n(void);
extern int utc_noti_ex_item_set_vibration_path_p(void);
extern int utc_noti_ex_item_set_vibration_path_n(void);
extern int utc_noti_ex_item_get_vibration_path_p(void);
extern int utc_noti_ex_item_get_vibration_path_n(void);
extern int utc_noti_ex_item_get_info_p(void);
extern int utc_noti_ex_item_get_info_n(void);
extern int utc_noti_ex_item_get_sender_app_id_p(void);
extern int utc_noti_ex_item_get_sender_app_id_n(void);
extern int utc_noti_ex_item_set_tag_p(void);
extern int utc_noti_ex_item_set_tag_n(void);
extern int utc_noti_ex_item_get_tag_p(void);
extern int utc_noti_ex_item_get_tag_n(void);
extern int utc_noti_ex_item_set_ongoing_state_p(void);
extern int utc_noti_ex_item_set_ongoing_state_n(void);
extern int utc_noti_ex_item_get_ongoing_state_p(void);
extern int utc_noti_ex_item_get_ongoing_state_n(void);
extern int utc_noti_ex_item_check_type_exist_p(void);
extern int utc_noti_ex_item_check_type_exist_n(void);
extern int utc_noti_ex_item_set_main_type_p(void);
extern int utc_noti_ex_item_set_main_type_n(void);
extern int utc_noti_ex_item_get_main_type_p(void);
extern int utc_noti_ex_item_get_main_type_n(void);
extern int utc_noti_ex_item_find_by_main_type_p(void);
extern int utc_noti_ex_item_find_by_main_type_n(void);
extern int utc_noti_ex_reporter_create_p(void);
extern int utc_noti_ex_reporter_create_n(void);
extern int utc_noti_ex_reporter_destroy_p(void);
extern int utc_noti_ex_reporter_destroy_n(void);
extern int utc_noti_ex_reporter_post_p(void);
extern int utc_noti_ex_reporter_post_n(void);
extern int utc_noti_ex_reporter_post_list_p(void);
extern int utc_noti_ex_reporter_post_list_n(void);
extern int utc_noti_ex_reporter_update_p(void);
extern int utc_noti_ex_reporter_update_n(void);
extern int utc_noti_ex_reporter_delete_p(void);
extern int utc_noti_ex_reporter_delete_n(void);
extern int utc_noti_ex_reporter_delete_all_p(void);
extern int utc_noti_ex_reporter_delete_all_n(void);
extern int utc_noti_ex_reporter_find_by_root_id_p(void);
extern int utc_noti_ex_reporter_find_by_root_id_n(void);
extern int utc_noti_ex_item_image_create_p(void);
extern int utc_noti_ex_item_image_create_n(void);
extern int utc_noti_ex_item_image_get_image_path_p(void);
extern int utc_noti_ex_item_image_get_image_path_n(void);
extern int utc_noti_ex_item_input_selector_create_p(void);
extern int utc_noti_ex_item_input_selector_create_n(void);
extern int utc_noti_ex_item_input_selector_set_contents_p(void);
extern int utc_noti_ex_item_input_selector_set_contents_n(void);
extern int utc_noti_ex_item_input_selector_get_contents_p(void);
extern int utc_noti_ex_item_input_selector_get_contents_n(void);
extern int utc_noti_ex_item_progress_create_p(void);
extern int utc_noti_ex_item_progress_create_n(void);
extern int utc_noti_ex_item_progress_set_current_p(void);
extern int utc_noti_ex_item_progress_set_current_n(void);
extern int utc_noti_ex_item_progress_get_current_p(void);
extern int utc_noti_ex_item_progress_get_current_n(void);
extern int utc_noti_ex_item_progress_get_min_p(void);
extern int utc_noti_ex_item_progress_get_min_n(void);
extern int utc_noti_ex_item_progress_get_max_p(void);
extern int utc_noti_ex_item_progress_get_max_n(void);
extern int utc_noti_ex_item_progress_set_type_p(void);
extern int utc_noti_ex_item_progress_set_type_n(void);
extern int utc_noti_ex_item_progress_get_type_p(void);
extern int utc_noti_ex_item_progress_get_type_n(void);
extern int utc_noti_ex_item_text_create_p(void);
extern int utc_noti_ex_item_text_create_n(void);
extern int utc_noti_ex_item_text_set_contents_p(void);
extern int utc_noti_ex_item_text_set_contents_n(void);
extern int utc_noti_ex_item_text_get_contents_p(void);
extern int utc_noti_ex_item_text_get_contents_n(void);
extern int utc_noti_ex_item_text_get_hyperlink_p(void);
extern int utc_noti_ex_item_text_get_hyperlink_n(void);
extern int utc_noti_ex_item_time_create_p(void);
extern int utc_noti_ex_item_time_create_n(void);
extern int utc_noti_ex_item_time_get_time_p(void);
extern int utc_noti_ex_item_time_get_time_n(void);
extern int utc_noti_ex_action_visibility_create_p(void);
extern int utc_noti_ex_action_visibility_create_n(void);
extern int utc_noti_ex_action_visibility_set_p(void);
extern int utc_noti_ex_action_visibility_set_n(void);
extern int utc_noti_ex_action_app_control_create_p(void);
extern int utc_noti_ex_action_app_control_create_n(void);
extern int utc_noti_ex_action_app_control_set_p(void);
extern int utc_noti_ex_action_app_control_set_n(void);
extern int utc_noti_ex_action_app_control_get_p(void);
extern int utc_noti_ex_action_app_control_get_n(void);
extern int utc_noti_ex_item_button_create_p(void);
extern int utc_noti_ex_item_button_create_n(void);
extern int utc_noti_ex_item_button_get_title_p(void);
extern int utc_noti_ex_item_button_get_title_n(void);
extern int utc_noti_ex_item_chat_message_create_p(void);
extern int utc_noti_ex_item_chat_message_create_n(void);
extern int utc_noti_ex_item_chat_message_get_name_p(void);
extern int utc_noti_ex_item_chat_message_get_name_n(void);
extern int utc_noti_ex_item_chat_message_get_text_p(void);
extern int utc_noti_ex_item_chat_message_get_text_n(void);
extern int utc_noti_ex_item_chat_message_get_image_p(void);
extern int utc_noti_ex_item_chat_message_get_image_n(void);
extern int utc_noti_ex_item_chat_message_get_time_p(void);
extern int utc_noti_ex_item_chat_message_get_time_n(void);
extern int utc_noti_ex_item_chat_message_get_message_type_p(void);
extern int utc_noti_ex_item_chat_message_get_message_type_n(void);
extern int utc_noti_ex_item_checkbox_create_p(void);
extern int utc_noti_ex_item_checkbox_create_n(void);
extern int utc_noti_ex_item_checkbox_get_title_p(void);
extern int utc_noti_ex_item_checkbox_get_title_n(void);
extern int utc_noti_ex_item_checkbox_get_check_state_p(void);
extern int utc_noti_ex_item_checkbox_get_check_state_n(void);
extern int utc_noti_ex_item_checkbox_set_check_state_p(void);
extern int utc_noti_ex_item_checkbox_set_check_state_n(void);
extern int utc_noti_ex_item_entry_create_p(void);
extern int utc_noti_ex_item_entry_create_n(void);
extern int utc_noti_ex_item_entry_get_text_p(void);
extern int utc_noti_ex_item_entry_get_text_n(void);
extern int utc_noti_ex_item_entry_set_text_p(void);
extern int utc_noti_ex_item_entry_set_text_n(void);
extern int utc_noti_ex_event_info_clone_n(void);
extern int utc_noti_ex_event_info_destroy_n(void);
extern int utc_noti_ex_event_info_get_event_type_n(void);
extern int utc_noti_ex_event_info_get_owner_n(void);
extern int utc_noti_ex_event_info_get_channel_n(void);
extern int utc_noti_ex_event_info_get_item_id_n(void);
extern int utc_noti_ex_event_info_get_request_id_n(void);
extern int utc_noti_ex_item_group_create_p(void);
extern int utc_noti_ex_item_group_create_n(void);
extern int utc_noti_ex_item_group_set_direction_p(void);
extern int utc_noti_ex_item_group_set_direction_n(void);
extern int utc_noti_ex_item_group_is_vertical_p(void);
extern int utc_noti_ex_item_group_is_vertical_n(void);
extern int utc_noti_ex_item_group_get_app_label_p(void);
extern int utc_noti_ex_item_group_get_app_label_n(void);
extern int utc_noti_ex_item_group_add_child_p(void);
extern int utc_noti_ex_item_group_add_child_n(void);
extern int utc_noti_ex_item_group_remove_child_p(void);
extern int utc_noti_ex_item_group_remove_child_n(void);
extern int utc_noti_ex_item_group_foreach_child_p(void);
extern int utc_noti_ex_item_group_foreach_child_n(void);
extern int utc_noti_ex_multi_lang_create_p(void);
extern int utc_noti_ex_multi_lang_create_n(void);
extern int utc_noti_ex_multi_lang_destroy_p(void);
extern int utc_noti_ex_multi_lang_destroy_n(void);
extern int utc_noti_ex_item_button_set_multi_language_title_p(void);
extern int utc_noti_ex_item_button_set_multi_language_title_n(void);
extern int utc_noti_ex_item_checkbox_set_multi_language_title_p(void);
extern int utc_noti_ex_item_checkbox_set_multi_language_title_n(void);
extern int utc_noti_ex_item_entry_set_multi_language_p(void);
extern int utc_noti_ex_item_entry_set_multi_language_n(void);
extern int utc_noti_ex_item_input_selector_set_multi_language_contents_p(void);
extern int utc_noti_ex_item_input_selector_set_multi_language_contents_n(void);
extern int utc_noti_ex_item_text_set_multi_language_p(void);
extern int utc_noti_ex_item_text_set_multi_language_n(void);
extern int utc_noti_ex_item_get_extension_data_n1(void);
extern int utc_noti_ex_item_get_extension_data_n2(void);
extern int utc_noti_ex_item_get_extension_data_n3(void);
extern int utc_noti_ex_item_get_extension_data_p(void);
extern int utc_noti_ex_item_set_extension_data_n1(void);
extern int utc_noti_ex_item_set_extension_data_n2(void);
extern int utc_noti_ex_item_set_extension_data_n3(void);
extern int utc_noti_ex_item_set_extension_data_p(void);

testcase tc_array[] = {
	{"utc_notification_create_1_n",utc_notification_create_1_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_create_2_n",utc_notification_create_2_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_create_1_p",utc_notification_create_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_create_2_p",utc_notification_create_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_n",utc_notification_set_image_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_1_p",utc_notification_set_image_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_2_p",utc_notification_set_image_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_3_p",utc_notification_set_image_3_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_4_p",utc_notification_set_image_4_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_5_p",utc_notification_set_image_5_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_6_p",utc_notification_set_image_6_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_7_p",utc_notification_set_image_7_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_8_p",utc_notification_set_image_8_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_9_p",utc_notification_set_image_9_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_10_p",utc_notification_set_image_10_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_11_p",utc_notification_set_image_11_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_12_p",utc_notification_set_image_12_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_13_p",utc_notification_set_image_13_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_14_p",utc_notification_set_image_14_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_15_p",utc_notification_set_image_15_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_16_p",utc_notification_set_image_16_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_17_p",utc_notification_set_image_17_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_18_p",utc_notification_set_image_18_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_19_p",utc_notification_set_image_19_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_20_p",utc_notification_set_image_20_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_21_p",utc_notification_set_image_21_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_22_p",utc_notification_set_image_22_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_image_23_p",utc_notification_set_image_23_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_n",utc_notification_get_image_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_1_p",utc_notification_get_image_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_2_p",utc_notification_get_image_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_3_p",utc_notification_get_image_3_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_4_p",utc_notification_get_image_4_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_5_p",utc_notification_get_image_5_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_6_p",utc_notification_get_image_6_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_7_p",utc_notification_get_image_7_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_8_p",utc_notification_get_image_8_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_9_p",utc_notification_get_image_9_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_10_p",utc_notification_get_image_10_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_11_p",utc_notification_get_image_11_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_12_p",utc_notification_get_image_12_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_13_p",utc_notification_get_image_13_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_14_p",utc_notification_get_image_14_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_15_p",utc_notification_get_image_15_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_16_p",utc_notification_get_image_16_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_17_p",utc_notification_get_image_17_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_18_p",utc_notification_get_image_18_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_19_p",utc_notification_get_image_19_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_20_p",utc_notification_get_image_20_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_21_p",utc_notification_get_image_21_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_22_p",utc_notification_get_image_22_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_image_23_p",utc_notification_get_image_23_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_n",utc_notification_set_time_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_p",utc_notification_set_time_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_n",utc_notification_get_time_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_1_p",utc_notification_get_time_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_2_p",utc_notification_get_time_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_insert_time_n",utc_notification_get_insert_time_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_insert_time_1_p",utc_notification_get_insert_time_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_insert_time_2_p",utc_notification_get_insert_time_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_n",utc_notification_set_text_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_1_p",utc_notification_set_text_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_2_p",utc_notification_set_text_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_3_p",utc_notification_set_text_3_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_4_p",utc_notification_set_text_4_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_5_p",utc_notification_set_text_5_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_6_p",utc_notification_set_text_6_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_7_p",utc_notification_set_text_7_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_8_p",utc_notification_set_text_8_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_9_p",utc_notification_set_text_9_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_10_p",utc_notification_set_text_10_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_11_p",utc_notification_set_text_11_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_12_p",utc_notification_set_text_12_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_13_p",utc_notification_set_text_13_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_14_p",utc_notification_set_text_14_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_15_p",utc_notification_set_text_15_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_16_p",utc_notification_set_text_16_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_17_p",utc_notification_set_text_17_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_18_p",utc_notification_set_text_18_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_19_p",utc_notification_set_text_19_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_20_p",utc_notification_set_text_20_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_21_p",utc_notification_set_text_21_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_22_p",utc_notification_set_text_22_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_23_p",utc_notification_set_text_23_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_24_p",utc_notification_set_text_24_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_25_p",utc_notification_set_text_25_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_n",utc_notification_get_text_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_1_p",utc_notification_get_text_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_2_p",utc_notification_get_text_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_3_p",utc_notification_get_text_3_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_4_p",utc_notification_get_text_4_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_5_p",utc_notification_get_text_5_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_6_p",utc_notification_get_text_6_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_7_p",utc_notification_get_text_7_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_8_p",utc_notification_get_text_8_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_9_p",utc_notification_get_text_9_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_10_p",utc_notification_get_text_10_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_11_p",utc_notification_get_text_11_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_12_p",utc_notification_get_text_12_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_13_p",utc_notification_get_text_13_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_14_p",utc_notification_get_text_14_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_15_p",utc_notification_get_text_15_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_16_p",utc_notification_get_text_16_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_17_p",utc_notification_get_text_17_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_18_p",utc_notification_get_text_18_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_19_p",utc_notification_get_text_19_p, utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_20_p",utc_notification_get_text_20_p, utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_21_p",utc_notification_get_text_21_p, utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_22_p",utc_notification_get_text_22_p, utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_text_23_p",utc_notification_get_text_23_p, utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_n",utc_notification_set_time_to_text_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_1_p",utc_notification_set_time_to_text_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_2_p",utc_notification_set_time_to_text_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_3_p",utc_notification_set_time_to_text_3_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_4_p",utc_notification_set_time_to_text_4_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_5_p",utc_notification_set_time_to_text_5_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_6_p",utc_notification_set_time_to_text_6_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_7_p",utc_notification_set_time_to_text_7_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_8_p",utc_notification_set_time_to_text_8_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_9_p",utc_notification_set_time_to_text_9_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_10_p",utc_notification_set_time_to_text_10_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_11_p",utc_notification_set_time_to_text_11_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_12_p",utc_notification_set_time_to_text_12_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_13_p",utc_notification_set_time_to_text_13_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_14_p",utc_notification_set_time_to_text_14_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_15_p",utc_notification_set_time_to_text_15_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_16_p",utc_notification_set_time_to_text_16_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_17_p",utc_notification_set_time_to_text_17_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_18_p",utc_notification_set_time_to_text_18_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_time_to_text_19_p",utc_notification_set_time_to_text_19_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_n",utc_notification_get_time_from_text_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_1_p",utc_notification_get_time_from_text_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_2_p",utc_notification_get_time_from_text_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_3_p",utc_notification_get_time_from_text_3_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_4_p",utc_notification_get_time_from_text_4_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_5_p",utc_notification_get_time_from_text_5_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_6_p",utc_notification_get_time_from_text_6_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_7_p",utc_notification_get_time_from_text_7_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_8_p",utc_notification_get_time_from_text_8_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_9_p",utc_notification_get_time_from_text_9_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_10_p",utc_notification_get_time_from_text_10_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_11_p",utc_notification_get_time_from_text_11_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_12_p",utc_notification_get_time_from_text_12_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_13_p",utc_notification_get_time_from_text_13_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_14_p",utc_notification_get_time_from_text_14_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_15_p",utc_notification_get_time_from_text_15_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_16_p",utc_notification_get_time_from_text_16_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_17_p",utc_notification_get_time_from_text_17_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_18_p",utc_notification_get_time_from_text_18_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_19_p",utc_notification_get_time_from_text_19_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_time_from_text_20_p",utc_notification_get_time_from_text_20_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_sound_n",utc_notification_set_sound_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_sound_p",utc_notification_set_sound_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_sound_n",utc_notification_get_sound_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_sound_1_p",utc_notification_get_sound_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_sound_2_p",utc_notification_get_sound_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_vibration_n",utc_notification_set_vibration_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_vibration_p",utc_notification_set_vibration_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_vibration_n",utc_notification_get_vibration_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_vibration_1_p",utc_notification_get_vibration_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_vibration_2_p",utc_notification_get_vibration_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_led_n",utc_notification_set_led_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_led_p",utc_notification_set_led_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_led_n",utc_notification_get_led_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_led_1_p",utc_notification_get_led_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_led_2_p",utc_notification_get_led_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_led_time_period_n",utc_notification_set_led_time_period_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_led_time_period_p",utc_notification_set_led_time_period_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_led_time_period_n",utc_notification_get_led_time_period_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_led_time_period_1_p",utc_notification_get_led_time_period_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_led_time_period_2_p",utc_notification_get_led_time_period_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_property_n",utc_notification_set_property_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_property_1_p",utc_notification_set_property_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_property_2_p",utc_notification_set_property_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_property_3_p",utc_notification_set_property_3_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_property_4_p",utc_notification_set_property_4_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_property_5_p",utc_notification_set_property_5_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_property_6_p",utc_notification_set_property_6_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_property_n",utc_notification_get_property_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_property_1_p",utc_notification_get_property_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_property_2_p",utc_notification_get_property_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_display_applist_n",utc_notification_set_display_applist_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_display_applist_p",utc_notification_set_display_applist_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_display_applist_n",utc_notification_get_display_applist_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_display_applist_1_p",utc_notification_get_display_applist_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_display_applist_2_p",utc_notification_get_display_applist_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_size_n",utc_notification_set_size_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_size_p",utc_notification_set_size_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_size_n",utc_notification_get_size_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_size_1_p",utc_notification_get_size_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_size_2_p",utc_notification_get_size_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_progress_n",utc_notification_set_progress_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_progress_p",utc_notification_set_progress_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_progress_n",utc_notification_get_progress_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_progress_1_p",utc_notification_get_progress_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_progress_2_p",utc_notification_get_progress_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_layout_n",utc_notification_set_layout_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_layout_1_p",utc_notification_set_layout_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_layout_2_p",utc_notification_set_layout_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_layout_3_p",utc_notification_set_layout_3_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_layout_4_p",utc_notification_set_layout_4_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_layout_5_p",utc_notification_set_layout_5_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_layout_n",utc_notification_get_layout_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_layout_1_p",utc_notification_get_layout_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_layout_2_p",utc_notification_get_layout_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_type_n",utc_notification_get_type_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_type_1_p",utc_notification_get_type_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_type_2_p",utc_notification_get_type_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_update_n",utc_notification_update_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_update_p",utc_notification_update_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_delete_n",utc_notification_delete_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_delete_p",utc_notification_delete_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_clone_n",utc_notification_clone_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_clone_p",utc_notification_clone_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_free_n",utc_notification_free_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_free_p",utc_notification_free_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_status_message_post_n",utc_notification_status_message_post_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_status_message_post_p",utc_notification_status_message_post_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_tag_n",utc_notification_set_tag_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_tag_p",utc_notification_set_tag_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_tag_n",utc_notification_get_tag_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_tag_1_p",utc_notification_get_tag_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_tag_2_p",utc_notification_get_tag_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_load_by_tag_1_n",utc_notification_load_by_tag_1_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_load_by_tag_2_n",utc_notification_load_by_tag_2_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_load_by_tag_p",utc_notification_load_by_tag_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_delete_all_1_p",utc_notification_delete_all_1_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_delete_all_2_p",utc_notification_delete_all_2_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_post_n",utc_notification_post_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_post_p",utc_notification_post_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_launch_option_n",utc_notification_set_launch_option_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_launch_option_p",utc_notification_set_launch_option_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_launch_option_n",utc_notification_get_launch_option_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_launch_option_p",utc_notification_get_launch_option_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_pkgname_n",utc_notification_get_pkgname_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_pkgname_p",utc_notification_get_pkgname_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_event_handler_n",utc_notification_set_event_handler_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_event_handler_p",utc_notification_set_event_handler_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_event_handler_n",utc_notification_get_event_handler_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_event_handler_p",utc_notification_get_event_handler_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_add_button_n",utc_notification_add_button_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_add_button_p",utc_notification_add_button_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_remove_button_n",utc_notification_remove_button_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_remove_button_p",utc_notification_remove_button_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_auto_remove_n",utc_notification_set_auto_remove_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_auto_remove_p",utc_notification_set_auto_remove_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_auto_remove_n",utc_notification_get_auto_remove_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_auto_remove_p",utc_notification_get_auto_remove_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_save_as_template_n",utc_notification_save_as_template_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_save_as_template_p",utc_notification_save_as_template_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_create_from_template_n1",utc_notification_create_from_template_n1,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_create_from_template_n2",utc_notification_create_from_template_n2,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_create_from_template_p",utc_notification_create_from_template_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_noti_block_state_n",utc_notification_get_noti_block_state_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_noti_block_state_p",utc_notification_get_noti_block_state_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_input_n",utc_notification_set_text_input_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_text_input_p",utc_notification_set_text_input_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_extension_image_size_n",utc_notification_set_extension_image_size_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_set_extension_image_size_p",utc_notification_set_extension_image_size_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_extension_image_size_n",utc_notification_get_extension_image_size_n,utc_notification_startup,utc_notification_cleanup},
	{"utc_notification_get_extension_image_size_p",utc_notification_get_extension_image_size_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_noti_ex_color_create_p",utc_noti_ex_color_create_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_create_n",utc_noti_ex_color_create_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_destroy_p",utc_noti_ex_color_destroy_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_destroy_n",utc_noti_ex_color_destroy_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_get_alpha_p",utc_noti_ex_color_get_alpha_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_get_alpha_n",utc_noti_ex_color_get_alpha_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_get_red_p",utc_noti_ex_color_get_red_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_get_red_n",utc_noti_ex_color_get_red_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_get_green_p",utc_noti_ex_color_get_green_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_get_green_n",utc_noti_ex_color_get_green_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_get_blue_p",utc_noti_ex_color_get_blue_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_color_get_blue_n",utc_noti_ex_color_get_blue_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_create_p",utc_noti_ex_padding_create_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_create_n",utc_noti_ex_padding_create_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_destroy_p",utc_noti_ex_padding_destroy_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_destroy_n",utc_noti_ex_padding_destroy_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_get_left_p",utc_noti_ex_padding_get_left_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_get_left_n",utc_noti_ex_padding_get_left_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_get_top_p",utc_noti_ex_padding_get_top_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_get_top_n",utc_noti_ex_padding_get_top_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_get_right_p",utc_noti_ex_padding_get_right_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_get_right_n",utc_noti_ex_padding_get_right_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_get_bottom_p",utc_noti_ex_padding_get_bottom_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_padding_get_bottom_n",utc_noti_ex_padding_get_bottom_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_create_p",utc_noti_ex_geometry_create_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_create_n",utc_noti_ex_geometry_create_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_destroy_p",utc_noti_ex_geometry_destroy_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_destroy_n",utc_noti_ex_geometry_destroy_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_get_x_p",utc_noti_ex_geometry_get_x_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_get_x_n",utc_noti_ex_geometry_get_x_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_get_y_p",utc_noti_ex_geometry_get_y_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_get_y_n",utc_noti_ex_geometry_get_y_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_get_width_p",utc_noti_ex_geometry_get_width_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_get_width_n",utc_noti_ex_geometry_get_width_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_get_height_p",utc_noti_ex_geometry_get_height_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_geometry_get_height_n",utc_noti_ex_geometry_get_height_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_create_p",utc_noti_ex_style_create_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_create_n",utc_noti_ex_style_create_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_destroy_p",utc_noti_ex_style_destroy_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_destroy_n",utc_noti_ex_style_destroy_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_get_padding_p",utc_noti_ex_style_get_padding_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_get_padding_n",utc_noti_ex_style_get_padding_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_get_color_p",utc_noti_ex_style_get_color_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_get_color_n",utc_noti_ex_style_get_color_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_get_geometry_p",utc_noti_ex_style_get_geometry_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_get_geometry_n",utc_noti_ex_style_get_geometry_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_set_background_image_p",utc_noti_ex_style_set_background_image_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_set_background_image_n",utc_noti_ex_style_set_background_image_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_get_background_image_p",utc_noti_ex_style_get_background_image_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_get_background_image_n",utc_noti_ex_style_get_background_image_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_set_background_color_p",utc_noti_ex_style_set_background_color_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_set_background_color_n",utc_noti_ex_style_set_background_color_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_get_background_color_p",utc_noti_ex_style_get_background_color_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_style_get_background_color_n",utc_noti_ex_style_get_background_color_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_create_p",utc_noti_ex_led_info_create_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_create_n",utc_noti_ex_led_info_create_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_destroy_p",utc_noti_ex_led_info_destroy_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_destroy_n",utc_noti_ex_led_info_destroy_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_set_on_period_p",utc_noti_ex_led_info_set_on_period_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_set_on_period_n",utc_noti_ex_led_info_set_on_period_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_get_on_period_p",utc_noti_ex_led_info_get_on_period_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_get_on_period_n",utc_noti_ex_led_info_get_on_period_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_set_off_period_p",utc_noti_ex_led_info_set_off_period_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_set_off_period_n",utc_noti_ex_led_info_set_off_period_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_get_off_period_p",utc_noti_ex_led_info_get_off_period_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_get_off_period_n",utc_noti_ex_led_info_get_off_period_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_get_color_p",utc_noti_ex_led_info_get_color_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_led_info_get_color_n",utc_noti_ex_led_info_get_color_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_action_destroy_p",utc_noti_ex_action_destroy_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_action_destroy_n",utc_noti_ex_action_destroy_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_action_get_type_p",utc_noti_ex_action_get_type_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_action_get_type_n",utc_noti_ex_action_get_type_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_action_is_local_p",utc_noti_ex_action_is_local_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_action_is_local_n",utc_noti_ex_action_is_local_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_action_execute_p",utc_noti_ex_action_execute_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_action_execute_n",utc_noti_ex_action_execute_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_action_get_extra_p",utc_noti_ex_action_get_extra_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_action_get_extra_n",utc_noti_ex_action_get_extra_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_info_get_hide_time_p",utc_noti_ex_item_info_get_hide_time_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_info_get_hide_time_n",utc_noti_ex_item_info_get_hide_time_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_info_set_hide_time_p",utc_noti_ex_item_info_set_hide_time_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_info_set_hide_time_n",utc_noti_ex_item_info_set_hide_time_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_info_get_delete_time_p",utc_noti_ex_item_info_get_delete_time_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_info_get_delete_time_n",utc_noti_ex_item_info_get_delete_time_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_info_set_delete_time_p",utc_noti_ex_item_info_set_delete_time_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_info_set_delete_time_n",utc_noti_ex_item_info_set_delete_time_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_info_get_time_p",utc_noti_ex_item_info_get_time_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_info_get_time_n",utc_noti_ex_item_info_get_time_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_destroy_p",utc_noti_ex_item_destroy_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_destroy_p_n",utc_noti_ex_item_destroy_p_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_find_by_id_p",utc_noti_ex_item_find_by_id_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_find_by_id_n",utc_noti_ex_item_find_by_id_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_type_p",utc_noti_ex_item_get_type_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_type_n",utc_noti_ex_item_get_type_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_id_p",utc_noti_ex_item_get_id_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_id_n",utc_noti_ex_item_get_id_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_id_p",utc_noti_ex_item_set_id_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_id_n",utc_noti_ex_item_set_id_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_action_p",utc_noti_ex_item_get_action_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_action_n",utc_noti_ex_item_get_action_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_action_p",utc_noti_ex_item_set_action_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_action_n",utc_noti_ex_item_set_action_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_style_p",utc_noti_ex_item_get_style_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_style_n",utc_noti_ex_item_get_style_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_style_p",utc_noti_ex_item_set_style_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_style_n",utc_noti_ex_item_set_style_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_visible_p",utc_noti_ex_item_set_visible_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_visible_n",utc_noti_ex_item_set_visible_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_visible_p",utc_noti_ex_item_get_visible_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_visible_n",utc_noti_ex_item_get_visible_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_enable_p",utc_noti_ex_item_set_enable_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_enable_n",utc_noti_ex_item_set_enable_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_enable_p",utc_noti_ex_item_get_enable_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_enable_n",utc_noti_ex_item_get_enable_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_add_receiver_p",utc_noti_ex_item_add_receiver_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_add_receiver_n",utc_noti_ex_item_add_receiver_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_receiver_list_p",utc_noti_ex_item_get_receiver_list_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_receiver_list_n",utc_noti_ex_item_get_receiver_list_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_remove_receiver_p",utc_noti_ex_item_remove_receiver_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_remove_receiver_n",utc_noti_ex_item_remove_receiver_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_policy_p",utc_noti_ex_item_set_policy_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_policy_n",utc_noti_ex_item_set_policy_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_policy_p",utc_noti_ex_item_get_policy_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_policy_n",utc_noti_ex_item_get_policy_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_channel_p",utc_noti_ex_item_set_channel_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_channel_n",utc_noti_ex_item_set_channel_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_channel_p",utc_noti_ex_item_get_channel_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_channel_n",utc_noti_ex_item_get_channel_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_led_info_p",utc_noti_ex_item_set_led_info_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_led_info_n",utc_noti_ex_item_set_led_info_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_led_info_p",utc_noti_ex_item_get_led_info_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_led_info_n",utc_noti_ex_item_get_led_info_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_sound_path_p",utc_noti_ex_item_set_sound_path_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_sound_path_n",utc_noti_ex_item_set_sound_path_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_sound_path_p",utc_noti_ex_item_get_sound_path_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_sound_path_n",utc_noti_ex_item_get_sound_path_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_vibration_path_p",utc_noti_ex_item_set_vibration_path_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_vibration_path_n",utc_noti_ex_item_set_vibration_path_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_vibration_path_p",utc_noti_ex_item_get_vibration_path_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_vibration_path_n",utc_noti_ex_item_get_vibration_path_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_info_p",utc_noti_ex_item_get_info_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_info_n",utc_noti_ex_item_get_info_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_sender_app_id_p",utc_noti_ex_item_get_sender_app_id_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_sender_app_id_n",utc_noti_ex_item_get_sender_app_id_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_tag_p",utc_noti_ex_item_set_tag_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_tag_n",utc_noti_ex_item_set_tag_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_tag_p",utc_noti_ex_item_get_tag_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_tag_n",utc_noti_ex_item_get_tag_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_ongoing_state_p",utc_noti_ex_item_set_ongoing_state_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_ongoing_state_n",utc_noti_ex_item_set_ongoing_state_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_ongoing_state_p",utc_noti_ex_item_get_ongoing_state_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_ongoing_state_n",utc_noti_ex_item_get_ongoing_state_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_check_type_exist_p",utc_noti_ex_item_check_type_exist_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_check_type_exist_n",utc_noti_ex_item_check_type_exist_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_main_type_p",utc_noti_ex_item_set_main_type_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_set_main_type_n",utc_noti_ex_item_set_main_type_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_main_type_p",utc_noti_ex_item_get_main_type_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_get_main_type_n",utc_noti_ex_item_get_main_type_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_find_by_main_type_p",utc_noti_ex_item_find_by_main_type_p,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_item_find_by_main_type_n",utc_noti_ex_item_find_by_main_type_n,utc_notification_ex_item_startup,utc_notification_ex_item_cleanup},
	{"utc_noti_ex_reporter_create_p",utc_noti_ex_reporter_create_p,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_create_n",utc_noti_ex_reporter_create_n,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_destroy_p",utc_noti_ex_reporter_destroy_p,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_destroy_n",utc_noti_ex_reporter_destroy_n,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_post_p",utc_noti_ex_reporter_post_p,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_post_n",utc_noti_ex_reporter_post_n,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_post_list_p",utc_noti_ex_reporter_post_list_p,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_post_list_n",utc_noti_ex_reporter_post_list_n,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_update_p",utc_noti_ex_reporter_update_p,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_update_n",utc_noti_ex_reporter_update_n,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_delete_p",utc_noti_ex_reporter_delete_p,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_delete_n",utc_noti_ex_reporter_delete_n,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_delete_all_p",utc_noti_ex_reporter_delete_all_p,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_delete_all_n",utc_noti_ex_reporter_delete_all_n,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_find_by_root_id_p",utc_noti_ex_reporter_find_by_root_id_p,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_reporter_find_by_root_id_n",utc_noti_ex_reporter_find_by_root_id_n,utc_notification_ex_reporter_startup,utc_notification_ex_reporter_cleanup},
	{"utc_noti_ex_item_image_create_p",utc_noti_ex_item_image_create_p,utc_notification_ex_image_startup,utc_notification_ex_image_cleanup},
	{"utc_noti_ex_item_image_create_n",utc_noti_ex_item_image_create_n,utc_notification_ex_image_startup,utc_notification_ex_image_cleanup},
	{"utc_noti_ex_item_image_get_image_path_p",utc_noti_ex_item_image_get_image_path_p,utc_notification_ex_image_startup,utc_notification_ex_image_cleanup},
	{"utc_noti_ex_item_image_get_image_path_n",utc_noti_ex_item_image_get_image_path_n,utc_notification_ex_image_startup,utc_notification_ex_image_cleanup},
	{"utc_noti_ex_item_input_selector_create_p",utc_noti_ex_item_input_selector_create_p,utc_notification_ex_input_selector_startup,utc_notification_ex_input_selector_cleanup},
	{"utc_noti_ex_item_input_selector_create_n",utc_noti_ex_item_input_selector_create_n,utc_notification_ex_input_selector_startup,utc_notification_ex_input_selector_cleanup},
	{"utc_noti_ex_item_input_selector_set_contents_p",utc_noti_ex_item_input_selector_set_contents_p,utc_notification_ex_input_selector_startup,utc_notification_ex_input_selector_cleanup},
	{"utc_noti_ex_item_input_selector_set_contents_n",utc_noti_ex_item_input_selector_set_contents_n,utc_notification_ex_input_selector_startup,utc_notification_ex_input_selector_cleanup},
	{"utc_noti_ex_item_input_selector_get_contents_p",utc_noti_ex_item_input_selector_get_contents_p,utc_notification_ex_input_selector_startup,utc_notification_ex_input_selector_cleanup},
	{"utc_noti_ex_item_input_selector_get_contents_n",utc_noti_ex_item_input_selector_get_contents_n,utc_notification_ex_input_selector_startup,utc_notification_ex_input_selector_cleanup},
	{"utc_noti_ex_item_progress_create_p",utc_noti_ex_item_progress_create_p,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_create_n",utc_noti_ex_item_progress_create_n,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_set_current_p",utc_noti_ex_item_progress_set_current_p,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_set_current_n",utc_noti_ex_item_progress_set_current_n,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_get_current_p",utc_noti_ex_item_progress_get_current_p,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_get_current_n",utc_noti_ex_item_progress_get_current_n,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_get_min_p",utc_noti_ex_item_progress_get_min_p,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_get_min_n",utc_noti_ex_item_progress_get_min_n,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_get_max_p",utc_noti_ex_item_progress_get_max_p,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_get_max_n",utc_noti_ex_item_progress_get_max_n,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_set_type_p",utc_noti_ex_item_progress_set_type_p,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_set_type_n",utc_noti_ex_item_progress_set_type_n,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_get_type_p",utc_noti_ex_item_progress_get_type_p,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_progress_get_type_n",utc_noti_ex_item_progress_get_type_n,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_text_create_p",utc_noti_ex_item_text_create_p,utc_notification_ex_text_startup,utc_notification_ex_text_cleanup},
	{"utc_noti_ex_item_text_create_n",utc_noti_ex_item_text_create_n,utc_notification_ex_text_startup,utc_notification_ex_text_cleanup},
	{"utc_noti_ex_item_text_set_contents_p",utc_noti_ex_item_text_set_contents_p,utc_notification_ex_text_startup,utc_notification_ex_text_cleanup},
	{"utc_noti_ex_item_text_set_contents_n",utc_noti_ex_item_text_set_contents_n,utc_notification_ex_text_startup,utc_notification_ex_text_cleanup},
	{"utc_noti_ex_item_text_get_contents_p",utc_noti_ex_item_text_get_contents_p,utc_notification_ex_text_startup,utc_notification_ex_text_cleanup},
	{"utc_noti_ex_item_text_get_contents_n",utc_noti_ex_item_text_get_contents_n,utc_notification_ex_text_startup,utc_notification_ex_text_cleanup},
	{"utc_noti_ex_item_text_get_hyperlink_p",utc_noti_ex_item_text_get_hyperlink_p,utc_notification_ex_text_startup,utc_notification_ex_text_cleanup},
	{"utc_noti_ex_item_text_get_hyperlink_n",utc_noti_ex_item_text_get_hyperlink_n,utc_notification_ex_text_startup,utc_notification_ex_text_cleanup},
	{"utc_noti_ex_item_time_create_p",utc_noti_ex_item_time_create_p,utc_notification_ex_time_startup,utc_notification_ex_time_cleanup},
	{"utc_noti_ex_item_time_create_n",utc_noti_ex_item_time_create_n,utc_notification_ex_time_startup,utc_notification_ex_time_cleanup},
	{"utc_noti_ex_item_time_get_time_p",utc_noti_ex_item_time_get_time_p,utc_notification_ex_time_startup,utc_notification_ex_time_cleanup},
	{"utc_noti_ex_item_time_get_time_n",utc_noti_ex_item_time_get_time_n,utc_notification_ex_time_startup,utc_notification_ex_time_cleanup},
	{"utc_noti_ex_action_visibility_create_p",utc_noti_ex_action_visibility_create_p,utc_notification_ex_visibility_action_startup,utc_notification_ex_visibility_action_cleanup},
	{"utc_noti_ex_action_visibility_create_n",utc_noti_ex_action_visibility_create_n,utc_notification_ex_visibility_action_startup,utc_notification_ex_visibility_action_cleanup},
	{"utc_noti_ex_action_visibility_set_p",utc_noti_ex_action_visibility_set_p,utc_notification_ex_visibility_action_startup,utc_notification_ex_visibility_action_cleanup},
	{"utc_noti_ex_action_visibility_set_n",utc_noti_ex_action_visibility_set_n,utc_notification_ex_visibility_action_startup,utc_notification_ex_visibility_action_cleanup},
	{"utc_noti_ex_action_app_control_create_p",utc_noti_ex_action_app_control_create_p,utc_notification_ex_app_control_action_startup,utc_notification_ex_app_control_action_cleanup},
	{"utc_noti_ex_action_app_control_create_n",utc_noti_ex_action_app_control_create_n,utc_notification_ex_app_control_action_startup,utc_notification_ex_app_control_action_cleanup},
	{"utc_noti_ex_action_app_control_set_p",utc_noti_ex_action_app_control_set_p,utc_notification_ex_app_control_action_startup,utc_notification_ex_app_control_action_cleanup},
	{"utc_noti_ex_action_app_control_set_n",utc_noti_ex_action_app_control_set_n,utc_notification_ex_app_control_action_startup,utc_notification_ex_app_control_action_cleanup},
	{"utc_noti_ex_action_app_control_get_p",utc_noti_ex_action_app_control_get_p,utc_notification_ex_app_control_action_startup,utc_notification_ex_app_control_action_cleanup},
	{"utc_noti_ex_action_app_control_get_n",utc_noti_ex_action_app_control_get_n,utc_notification_ex_app_control_action_startup,utc_notification_ex_app_control_action_cleanup},
	{"utc_noti_ex_item_button_create_p",utc_noti_ex_item_button_create_p,utc_notification_ex_button_startup,utc_notification_ex_button_cleanup},
	{"utc_noti_ex_item_button_create_n",utc_noti_ex_item_button_create_n,utc_notification_ex_button_startup,utc_notification_ex_button_cleanup},
	{"utc_noti_ex_item_button_get_title_p",utc_noti_ex_item_button_get_title_p,utc_notification_ex_button_startup,utc_notification_ex_button_cleanup},
	{"utc_noti_ex_item_button_get_title_n",utc_noti_ex_item_button_get_title_n,utc_notification_ex_button_startup,utc_notification_ex_button_cleanup},
	{"utc_noti_ex_item_chat_message_create_p",utc_noti_ex_item_chat_message_create_p,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_create_n",utc_noti_ex_item_chat_message_create_n,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_get_name_p",utc_noti_ex_item_chat_message_get_name_p,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_get_name_n",utc_noti_ex_item_chat_message_get_name_n,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_get_text_p",utc_noti_ex_item_chat_message_get_text_p,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_get_text_n",utc_noti_ex_item_chat_message_get_text_n,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_get_image_p",utc_noti_ex_item_chat_message_get_image_p,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_get_image_n",utc_noti_ex_item_chat_message_get_image_n,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_get_time_p",utc_noti_ex_item_chat_message_get_time_p,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_get_time_n",utc_noti_ex_item_chat_message_get_time_n,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_get_message_type_p",utc_noti_ex_item_chat_message_get_message_type_p,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_chat_message_get_message_type_n",utc_noti_ex_item_chat_message_get_message_type_n,utc_notification_ex_chat_message_startup,utc_notification_ex_chat_message_cleanup},
	{"utc_noti_ex_item_checkbox_create_p",utc_noti_ex_item_checkbox_create_p,utc_notification_ex_checkbox_startup,utc_notification_ex_checkbox_cleanup},
	{"utc_noti_ex_item_checkbox_create_n",utc_noti_ex_item_checkbox_create_n,utc_notification_ex_checkbox_startup,utc_notification_ex_checkbox_cleanup},
	{"utc_noti_ex_item_checkbox_get_title_p",utc_noti_ex_item_checkbox_get_title_p,utc_notification_ex_checkbox_startup,utc_notification_ex_checkbox_cleanup},
	{"utc_noti_ex_item_checkbox_get_title_n",utc_noti_ex_item_checkbox_get_title_n,utc_notification_ex_checkbox_startup,utc_notification_ex_checkbox_cleanup},
	{"utc_noti_ex_item_checkbox_get_check_state_p",utc_noti_ex_item_checkbox_get_check_state_p,utc_notification_ex_checkbox_startup,utc_notification_ex_checkbox_cleanup},
	{"utc_noti_ex_item_checkbox_get_check_state_n",utc_noti_ex_item_checkbox_get_check_state_n,utc_notification_ex_checkbox_startup,utc_notification_ex_checkbox_cleanup},
	{"utc_noti_ex_item_checkbox_set_check_state_p",utc_noti_ex_item_checkbox_set_check_state_p,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_checkbox_set_check_state_n",utc_noti_ex_item_checkbox_set_check_state_n,utc_notification_ex_progress_startup,utc_notification_ex_progress_cleanup},
	{"utc_noti_ex_item_entry_create_p",utc_noti_ex_item_entry_create_p,utc_notification_ex_entry_startup,utc_notification_ex_entry_cleanup},
	{"utc_noti_ex_item_entry_create_n",utc_noti_ex_item_entry_create_n,utc_notification_ex_entry_startup,utc_notification_ex_entry_cleanup},
	{"utc_noti_ex_item_entry_get_text_p",utc_noti_ex_item_entry_get_text_p,utc_notification_ex_entry_startup,utc_notification_ex_entry_cleanup},
	{"utc_noti_ex_item_entry_get_text_n",utc_noti_ex_item_entry_get_text_n,utc_notification_ex_entry_startup,utc_notification_ex_entry_cleanup},
	{"utc_noti_ex_item_entry_set_text_p",utc_noti_ex_item_entry_set_text_p,utc_notification_ex_entry_startup,utc_notification_ex_entry_cleanup},
	{"utc_noti_ex_item_entry_set_text_n",utc_noti_ex_item_entry_set_text_n,utc_notification_ex_entry_startup,utc_notification_ex_entry_cleanup},
	{"utc_noti_ex_event_info_clone_n",utc_noti_ex_event_info_clone_n,utc_notification_ex_event_info_startup,utc_notification_ex_event_info_cleanup},
	{"utc_noti_ex_event_info_destroy_n",utc_noti_ex_event_info_destroy_n,utc_notification_ex_event_info_startup,utc_notification_ex_event_info_cleanup},
	{"utc_noti_ex_event_info_get_event_type_n",utc_noti_ex_event_info_get_event_type_n,utc_notification_ex_event_info_startup,utc_notification_ex_event_info_cleanup},
	{"utc_noti_ex_event_info_get_owner_n",utc_noti_ex_event_info_get_owner_n,utc_notification_ex_event_info_startup,utc_notification_ex_event_info_cleanup},
	{"utc_noti_ex_event_info_get_channel_n",utc_noti_ex_event_info_get_channel_n,utc_notification_ex_event_info_startup,utc_notification_ex_event_info_cleanup},
	{"utc_noti_ex_event_info_get_item_id_n",utc_noti_ex_event_info_get_item_id_n,utc_notification_ex_event_info_startup,utc_notification_ex_event_info_cleanup},
	{"utc_noti_ex_event_info_get_request_id_n",utc_noti_ex_event_info_get_request_id_n,utc_notification_ex_event_info_startup,utc_notification_ex_event_info_cleanup},
	{"utc_noti_ex_item_group_create_p",utc_noti_ex_item_group_create_p,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_create_n",utc_noti_ex_item_group_create_n,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_set_direction_p",utc_noti_ex_item_group_set_direction_p,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_set_direction_n",utc_noti_ex_item_group_set_direction_n,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_is_vertical_p",utc_noti_ex_item_group_is_vertical_p,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_is_vertical_n",utc_noti_ex_item_group_is_vertical_n,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_get_app_label_p",utc_noti_ex_item_group_get_app_label_p,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_get_app_label_n",utc_noti_ex_item_group_get_app_label_n,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_add_child_p",utc_noti_ex_item_group_add_child_p,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_add_child_n",utc_noti_ex_item_group_add_child_n,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_remove_child_p",utc_noti_ex_item_group_remove_child_p,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_remove_child_n",utc_noti_ex_item_group_remove_child_n,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_foreach_child_p",utc_noti_ex_item_group_foreach_child_p,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_item_group_foreach_child_n",utc_noti_ex_item_group_foreach_child_n,utc_notification_ex_group_startup,utc_notification_ex_group_cleanup},
	{"utc_noti_ex_multi_lang_create_p",utc_noti_ex_multi_lang_create_p,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_multi_lang_create_n",utc_noti_ex_multi_lang_create_n,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_multi_lang_destroy_p",utc_noti_ex_multi_lang_destroy_p,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_multi_lang_destroy_n",utc_noti_ex_multi_lang_destroy_n,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_button_set_multi_language_title_p",utc_noti_ex_item_button_set_multi_language_title_p,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_button_set_multi_language_title_n",utc_noti_ex_item_button_set_multi_language_title_n,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_checkbox_set_multi_language_title_p",utc_noti_ex_item_checkbox_set_multi_language_title_p,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_checkbox_set_multi_language_title_n",utc_noti_ex_item_checkbox_set_multi_language_title_n,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_entry_set_multi_language_p",utc_noti_ex_item_entry_set_multi_language_p,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_entry_set_multi_language_n",utc_noti_ex_item_entry_set_multi_language_n,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_input_selector_set_multi_language_contents_p",utc_noti_ex_item_input_selector_set_multi_language_contents_p,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_input_selector_set_multi_language_contents_n",utc_noti_ex_item_input_selector_set_multi_language_contents_n,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_text_set_multi_language_p",utc_noti_ex_item_text_set_multi_language_p,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_text_set_multi_language_n",utc_noti_ex_item_text_set_multi_language_n,utc_notification_ex_multi_language_startup,utc_notification_ex_multi_language_cleanup},
	{"utc_noti_ex_item_get_extension_data_n1",utc_noti_ex_item_get_extension_data_n1,utc_notification_startup,utc_notification_cleanup},
	{"utc_noti_ex_item_get_extension_data_n2",utc_noti_ex_item_get_extension_data_n2,utc_notification_startup,utc_notification_cleanup},
	{"utc_noti_ex_item_get_extension_data_n3",utc_noti_ex_item_get_extension_data_n3,utc_notification_startup,utc_notification_cleanup},
	{"utc_noti_ex_item_get_extension_data_p",utc_noti_ex_item_get_extension_data_p,utc_notification_startup,utc_notification_cleanup},
	{"utc_noti_ex_item_set_extension_data_n1",utc_noti_ex_item_set_extension_data_n1,utc_notification_startup,utc_notification_cleanup},
	{"utc_noti_ex_item_set_extension_data_n2",utc_noti_ex_item_set_extension_data_n2,utc_notification_startup,utc_notification_cleanup},
	{"utc_noti_ex_item_set_extension_data_n3",utc_noti_ex_item_set_extension_data_n3,utc_notification_startup,utc_notification_cleanup},
	{"utc_noti_ex_item_set_extension_data_p",utc_noti_ex_item_set_extension_data_p,utc_notification_startup,utc_notification_cleanup},
	{NULL, NULL}
};
#endif // __TCT_NOTIFICATION_NATIVE_H__
