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
#ifndef __TCT_APPLICATION-NATIVE_H__
#define __TCT_APPLICATION-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_application_startup(void);
extern void ITs_application_cleanup(void);
extern void ITs_application_app_common_startup(void);
extern void ITs_application_app_common_cleanup(void);
extern void ITs_application_app_control_startup(void);
extern void ITs_application_app_control_cleanup(void);
extern void ITs_application_event_startup(void);
extern void ITs_application_event_cleanup(void);
extern void ITs_application_internationalization_startup(void);
extern void ITs_application_internationalization_cleanup(void);
extern void ITs_application_preference_startup(void);
extern void ITs_application_preference_cleanup(void);
extern void ITs_application_resourceManager_startup(void);
extern void ITs_application_resourceManager_cleanup(void);
extern void ITs_application_app_get_display_state_startup(void);
extern void ITs_application_app_get_display_state_cleanup(void);
extern void ITc_application_app_control_uri_startup(void);
extern void Itc_application_app_control_uri_cleanup(void);

extern int ITc_application_app_control_send_launch_request_async_p(void);
extern int ITc_application_ui_app_add_remove_event_handler_p(void);
extern int ITc_application_app_get_device_orientation_p(void);
extern int ITc_application_app_get_tep_resource_path_p(void);
extern int ITc_app_control_enable_app_started_result_event_p(void);
extern int ITc_application_app_get_cache_path_p(void);
extern int ITc_application_app_get_data_path_p(void);
extern int ITc_application_app_get_external_data_path_p(void);
extern int ITc_application_app_get_external_cache_path_p(void);
extern int ITc_application_app_get_external_shared_data_path_p(void);
extern int ITc_application_app_get_resource_path_p(void);
extern int ITc_application_app_get_shared_data_path_p(void);
extern int ITc_application_app_get_shared_resource_path_p(void);
extern int ITc_application_app_get_shared_trusted_path_p(void);
extern int ITc_application_app_get_id_p(void);
extern int ITc_application_app_get_version_p(void);
extern int ITc_application_app_get_name_p(void);
extern int ITc_application_app_control_create_destroy_p(void);
extern int ITc_application_app_control_set_get_operation_p(void);
extern int ITc_application_app_control_set_get_app_id_p(void);
extern int ITc_application_app_control_set_get_uri_p(void);
extern int ITc_application_app_control_set_get_mime_p(void);
extern int ITc_application_app_control_set_get_category_p(void);
extern int ITc_application_app_control_add_get_extra_data_p(void);
extern int ITc_application_app_control_add_get_extra_data_array_p(void);
extern int ITc_application_app_control_is_extra_data_array_p(void);
extern int ITc_application_app_control_clone_p(void);
extern int ITc_application_app_control_remove_extra_data_p(void);
extern int ITc_application_app_control_send_launch_terminate_request_p(void);
extern int ITc_application_app_control_for_each_app_matched_p(void);
extern int ITc_application_app_control_for_each_extra_data_p(void);
extern int ITc_application_app_control_set_get_launch_mode_p(void);
extern int ITc_app_event_add_remove_event_handler_p(void);
extern int ITc_application_event_publish_app_event_p(void);
extern int ITc_application_event_publish_trusted_app_event_p(void);
extern int ITc_application_event_keep_last_event_data_p(void);
extern int ITc_application_internationalization_i18n_get_text_p(void);
extern int ITc_application_preference_set_get_boolean_p(void);
extern int ITc_application_preference_set_get_double_p(void);
extern int ITc_application_preference_set_get_string_p(void);
extern int ITc_application_preference_is_existing_remove_p(void);
extern int ITc_application_preference_remove_all_p(void);
extern int ITc_application_preference_set_unset_changed_callback_p(void);
extern int ITc_application_preference_for_each_item_callback_p(void);
extern int ITc_application_preference_get_type_string_p(void);
extern int ITc_application_preference_get_type_int_p(void);
extern int ITc_application_preference_get_type_double_p(void);
extern int ITc_application_preference_get_type_boolean_p(void);
extern int ITc_application_app_resource_manager_init_release_p(void);
extern int ITc_application_app_resource_manager_get_p(void);
extern int ITc_application_app_watchdog_timer_enable_kick_disable_p(void);
extern int ITc_application_app_watchdog_timer_enable_disable_p(void);
extern int ITc_application_app_get_display_state_p(void);
extern int ITc_application_app_control_with_parameters_create_p(void);
extern int ITc_application_app_control_send_launch_request_sync_p(void);
extern int ITc_application_app_control_add_remove_action_handler_p(void);

extern int ITc_application_app_control_create_from_uri_handle_p(void);
extern int ITc_application_app_control_set_uri_by_handle_p(void);
extern int ITc_application_app_control_uri_create_destroy_p(void);
extern int ITc_application_app_control_uri_builder_create_destroy_p(void);
extern int ITc_application_app_control_uri_add_get_path_p(void);
extern int ITc_application_app_control_uri_builder_build_p(void);
extern int ITc_application_app_control_uri_encode_p(void);
extern int ITc_application_app_control_uri_set_get_scheme_p(void);
extern int ITc_application_app_control_uri_set_get_authority_p(void);
extern int Itc_application_app_control_uri_set_get_path_p(void);
extern int ITc_application_app_control_uri_set_get_fragment_p(void);
extern int ITc_application_app_control_uri_get_host_p(void);
extern int ITc_application_app_control_uri_get_port_p(void);
extern int ITc_application_app_control_uri_get_user_p(void);
extern int ITc_application_app_control_uri_add_get_query_p(void);
extern int ITc_application_app_control_uri_query_foreach_p(void);
extern int ITc_application_app_control_set_get_component_id_p(void);

testcase tc_array[] = {
	{"ITc_application_app_control_send_launch_request_async_p",ITc_application_app_control_send_launch_request_async_p,ITs_application_startup,ITs_application_cleanup},
	{"ITc_application_ui_app_add_remove_event_handler_p",ITc_application_ui_app_add_remove_event_handler_p,ITs_application_startup,ITs_application_cleanup},
	{"ITc_application_app_get_device_orientation_p",ITc_application_app_get_device_orientation_p,ITs_application_startup,ITs_application_cleanup},
	{"ITc_application_app_get_tep_resource_path_p",ITc_application_app_get_tep_resource_path_p,ITs_application_startup,ITs_application_cleanup},
	{"ITc_app_control_enable_app_started_result_event_p",ITc_app_control_enable_app_started_result_event_p,ITs_application_startup,ITs_application_cleanup},
	{"ITc_application_app_get_cache_path_p",ITc_application_app_get_cache_path_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_data_path_p",ITc_application_app_get_data_path_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_external_data_path_p",ITc_application_app_get_external_data_path_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_external_cache_path_p",ITc_application_app_get_external_cache_path_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_external_shared_data_path_p",ITc_application_app_get_external_shared_data_path_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_resource_path_p",ITc_application_app_get_resource_path_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_shared_data_path_p",ITc_application_app_get_shared_data_path_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_shared_resource_path_p",ITc_application_app_get_shared_resource_path_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_shared_trusted_path_p",ITc_application_app_get_shared_trusted_path_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_id_p",ITc_application_app_get_id_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_version_p",ITc_application_app_get_version_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_get_name_p",ITc_application_app_get_name_p,ITs_application_app_common_startup,ITs_application_app_common_cleanup},
	{"ITc_application_app_control_create_destroy_p",ITc_application_app_control_create_destroy_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_set_get_operation_p",ITc_application_app_control_set_get_operation_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_set_get_app_id_p",ITc_application_app_control_set_get_app_id_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_set_get_uri_p",ITc_application_app_control_set_get_uri_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
        {"ITc_application_app_control_set_get_component_id_p",ITc_application_app_control_set_get_component_id_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_set_get_mime_p",ITc_application_app_control_set_get_mime_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_set_get_category_p",ITc_application_app_control_set_get_category_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_add_get_extra_data_p",ITc_application_app_control_add_get_extra_data_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_add_get_extra_data_array_p",ITc_application_app_control_add_get_extra_data_array_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_is_extra_data_array_p",ITc_application_app_control_is_extra_data_array_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_clone_p",ITc_application_app_control_clone_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_remove_extra_data_p",ITc_application_app_control_remove_extra_data_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_send_launch_terminate_request_p",ITc_application_app_control_send_launch_terminate_request_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_for_each_app_matched_p",ITc_application_app_control_for_each_app_matched_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_for_each_extra_data_p",ITc_application_app_control_for_each_extra_data_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_set_get_launch_mode_p",ITc_application_app_control_set_get_launch_mode_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_app_event_add_remove_event_handler_p",ITc_app_event_add_remove_event_handler_p,ITs_application_event_startup,ITs_application_event_cleanup},
	{"ITc_application_event_publish_app_event_p",ITc_application_event_publish_app_event_p,ITs_application_event_startup,ITs_application_event_cleanup},
	{"ITc_application_event_publish_trusted_app_event_p",ITc_application_event_publish_trusted_app_event_p,ITs_application_event_startup,ITs_application_event_cleanup},
	{"ITc_application_event_keep_last_event_data_p",ITc_application_event_keep_last_event_data_p,ITs_application_event_startup,ITs_application_event_cleanup},
	{"ITc_application_internationalization_i18n_get_text_p",ITc_application_internationalization_i18n_get_text_p,ITs_application_internationalization_startup,ITs_application_internationalization_cleanup},
	{"ITc_application_preference_set_get_boolean_p",ITc_application_preference_set_get_boolean_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_preference_set_get_double_p",ITc_application_preference_set_get_double_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_preference_set_get_string_p",ITc_application_preference_set_get_string_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_preference_is_existing_remove_p",ITc_application_preference_is_existing_remove_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_preference_remove_all_p",ITc_application_preference_remove_all_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_preference_set_unset_changed_callback_p",ITc_application_preference_set_unset_changed_callback_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_preference_for_each_item_callback_p",ITc_application_preference_for_each_item_callback_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_preference_get_type_string_p",ITc_application_preference_get_type_string_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_preference_get_type_int_p",ITc_application_preference_get_type_int_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_preference_get_type_double_p",ITc_application_preference_get_type_double_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_preference_get_type_boolean_p",ITc_application_preference_get_type_boolean_p,ITs_application_preference_startup,ITs_application_preference_cleanup},
	{"ITc_application_app_resource_manager_init_release_p",ITc_application_app_resource_manager_init_release_p,ITs_application_resourceManager_startup,ITs_application_resourceManager_cleanup},
	{"ITc_application_app_resource_manager_get_p",ITc_application_app_resource_manager_get_p,ITs_application_resourceManager_startup,ITs_application_resourceManager_cleanup},
	{"ITc_application_app_watchdog_timer_enable_kick_disable_p",ITc_application_app_watchdog_timer_enable_kick_disable_p,NULL,NULL},
	{"ITc_application_app_watchdog_timer_enable_disable_p",ITc_application_app_watchdog_timer_enable_disable_p,NULL,NULL},
	{"ITc_application_app_get_display_state_p",ITc_application_app_get_display_state_p,ITs_application_app_get_display_state_startup,ITs_application_app_get_display_state_cleanup},
	{"ITc_application_app_control_with_parameters_create_p",ITc_application_app_control_with_parameters_create_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_send_launch_request_sync_p",ITc_application_app_control_send_launch_request_sync_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_add_remove_action_handler_p",ITc_application_app_control_add_remove_action_handler_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_create_from_uri_handle_p",ITc_application_app_control_create_from_uri_handle_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_set_uri_by_handle_p",ITc_application_app_control_set_uri_by_handle_p,ITs_application_app_control_startup,ITs_application_app_control_cleanup},
	{"ITc_application_app_control_uri_create_destroy_p",ITc_application_app_control_uri_create_destroy_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_builder_create_destroy_p",ITc_application_app_control_uri_builder_create_destroy_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_add_get_path_p",ITc_application_app_control_uri_add_get_path_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_builder_build_p",ITc_application_app_control_uri_builder_build_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_encode_p",ITc_application_app_control_uri_encode_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_set_get_scheme_p",ITc_application_app_control_uri_set_get_scheme_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_set_get_authority_p",ITc_application_app_control_uri_set_get_authority_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"Itc_application_app_control_uri_set_get_path_p",Itc_application_app_control_uri_set_get_path_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_set_get_fragment_p",ITc_application_app_control_uri_set_get_fragment_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_get_host_p",ITc_application_app_control_uri_get_host_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_get_port_p",ITc_application_app_control_uri_get_port_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_get_user_p",ITc_application_app_control_uri_get_user_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_add_get_query_p",ITc_application_app_control_uri_add_get_query_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{"ITc_application_app_control_uri_query_foreach_p",ITc_application_app_control_uri_query_foreach_p,ITc_application_app_control_uri_startup,Itc_application_app_control_uri_cleanup},
	{NULL, NULL}
};

#endif // __TCT_APPLICATION-NATIVE_H__
