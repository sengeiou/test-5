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
#ifndef __TCT_CAPI_UI_AUTOFILL_NATIVE_H__
#define __TCT_CAPI_UI_AUTOFILL_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

// common
extern void utc_capi_ui_autofill_common_startup(void);
extern void utc_capi_ui_autofill_common_cleanup(void);

extern int utc_autofill_item_create_p(void);
extern int utc_autofill_item_create_n(void);
extern int utc_autofill_item_destroy_p(void);
extern int utc_autofill_item_destroy_n(void);

extern int utc_autofill_item_clone_p(void);
extern int utc_autofill_item_clone_n(void);

extern int utc_autofill_item_set_autofill_hint_p(void);
extern int utc_autofill_item_set_autofill_hint_n(void);
extern int utc_autofill_item_get_autofill_hint_p(void);
extern int utc_autofill_item_get_autofill_hint_n(void);

extern int utc_autofill_item_set_id_p(void);
extern int utc_autofill_item_set_id_n(void);
extern int utc_autofill_item_get_id_p(void);
extern int utc_autofill_item_get_id_n(void);

extern int utc_autofill_item_set_label_p(void);
extern int utc_autofill_item_set_label_n(void);
extern int utc_autofill_item_get_label_p(void);
extern int utc_autofill_item_get_label_n(void);

extern int utc_autofill_item_set_sensitive_data_p(void);
extern int utc_autofill_item_set_sensitive_data_n(void);
extern int utc_autofill_item_get_sensitive_data_p(void);
extern int utc_autofill_item_get_sensitive_data_n(void);

extern int utc_autofill_item_set_value_p(void);
extern int utc_autofill_item_set_value_n(void);
extern int utc_autofill_item_get_value_p(void);
extern int utc_autofill_item_get_value_n(void);

extern int utc_autofill_auth_info_create_p(void);
extern int utc_autofill_auth_info_create_n(void);
extern int utc_autofill_auth_info_destroy_p(void);
extern int utc_autofill_auth_info_destroy_n(void);

extern int utc_autofill_auth_info_set_app_id_p(void);
extern int utc_autofill_auth_info_set_app_id_n(void);
extern int utc_autofill_auth_info_get_app_id_p(void);
extern int utc_autofill_auth_info_get_app_id_n(void);

extern int utc_autofill_auth_info_set_view_id_p(void);
extern int utc_autofill_auth_info_set_view_id_n(void);
extern int utc_autofill_auth_info_get_view_id_p(void);
extern int utc_autofill_auth_info_get_view_id_n(void);

extern int utc_autofill_auth_info_set_autofill_data_present_p(void);
extern int utc_autofill_auth_info_set_autofill_data_present_n(void);
extern int utc_autofill_auth_info_get_autofill_data_present_p(void);
extern int utc_autofill_auth_info_get_autofill_data_present_n(void);

extern int utc_autofill_auth_info_set_authentication_needed_p(void);
extern int utc_autofill_auth_info_set_authentication_needed_n(void);
extern int utc_autofill_auth_info_get_authentication_needed_p(void);
extern int utc_autofill_auth_info_get_authentication_needed_n(void);

extern int utc_autofill_auth_info_set_service_name_p(void);
extern int utc_autofill_auth_info_set_service_name_n(void);
extern int utc_autofill_auth_info_get_service_name_p(void);
extern int utc_autofill_auth_info_get_service_name_n(void);

extern int utc_autofill_auth_info_set_service_message_p(void);
extern int utc_autofill_auth_info_set_service_message_n(void);
extern int utc_autofill_auth_info_get_service_message_p(void);
extern int utc_autofill_auth_info_get_service_message_n(void);

extern int utc_autofill_auth_info_set_service_logo_image_path_p(void);
extern int utc_autofill_auth_info_set_service_logo_image_path_n(void);
extern int utc_autofill_auth_info_get_service_logo_image_path_p(void);
extern int utc_autofill_auth_info_get_service_logo_image_path_n(void);

extern int utc_autofill_view_info_create_p(void);
extern int utc_autofill_view_info_create_n(void);
extern int utc_autofill_view_info_destroy_p(void);
extern int utc_autofill_view_info_destroy_n(void);

extern int utc_autofill_view_info_set_app_id_p(void);
extern int utc_autofill_view_info_set_app_id_n(void);
extern int utc_autofill_view_info_get_app_id_p(void);
extern int utc_autofill_view_info_get_app_id_n(void);

extern int utc_autofill_view_info_set_view_id_p(void);
extern int utc_autofill_view_info_set_view_id_n(void);
extern int utc_autofill_view_info_get_view_id_p(void);
extern int utc_autofill_view_info_get_view_id_n(void);

extern int utc_autofill_view_info_add_item_p(void);
extern int utc_autofill_view_info_add_item_n(void);

extern int utc_autofill_view_info_foreach_item_p(void);
extern int utc_autofill_view_info_foreach_item_n(void);

extern int utc_autofill_save_view_info_create_p(void);
extern int utc_autofill_save_view_info_create_n(void);
extern int utc_autofill_save_view_info_destroy_p(void);
extern int utc_autofill_save_view_info_destroy_n(void);

extern int utc_autofill_save_view_info_set_app_id_p(void);
extern int utc_autofill_save_view_info_set_app_id_n(void);
extern int utc_autofill_save_view_info_get_app_id_p(void);
extern int utc_autofill_save_view_info_get_app_id_n(void);

extern int utc_autofill_save_view_info_set_view_id_p(void);
extern int utc_autofill_save_view_info_set_view_id_n(void);
extern int utc_autofill_save_view_info_get_view_id_p(void);
extern int utc_autofill_save_view_info_get_view_id_n(void);

extern int utc_autofill_save_view_info_set_view_title_p(void);
extern int utc_autofill_save_view_info_set_view_title_n(void);
extern int utc_autofill_save_view_info_get_view_title_p(void);
extern int utc_autofill_save_view_info_get_view_title_n(void);

extern int utc_autofill_save_view_info_add_item_p(void);
extern int utc_autofill_save_view_info_add_item_n(void);

extern int utc_autofill_save_view_info_foreach_item_p(void);
extern int utc_autofill_save_view_info_foreach_item_n(void);

extern int utc_autofill_fill_response_create_p(void);
extern int utc_autofill_fill_response_create_n(void);
extern int utc_autofill_fill_response_destroy_p(void);
extern int utc_autofill_fill_response_destroy_n(void);

extern int utc_autofill_fill_response_set_app_id_p(void);
extern int utc_autofill_fill_response_set_app_id_n(void);
extern int utc_autofill_fill_response_get_app_id_p(void);
extern int utc_autofill_fill_response_get_app_id_n(void);

extern int utc_autofill_fill_response_set_view_id_p(void);
extern int utc_autofill_fill_response_set_view_id_n(void);
extern int utc_autofill_fill_response_get_view_id_p(void);
extern int utc_autofill_fill_response_get_view_id_n(void);

extern int utc_autofill_fill_response_add_group_p(void);
extern int utc_autofill_fill_response_add_group_n(void);

extern int utc_autofill_fill_response_foreach_group_p(void);
extern int utc_autofill_fill_response_foreach_group_n(void);

extern int utc_autofill_fill_response_get_group_count_p(void);
extern int utc_autofill_fill_response_get_group_count_n(void);

extern int utc_autofill_fill_response_group_add_item_p(void);
extern int utc_autofill_fill_response_group_add_item_n(void);

extern int utc_autofill_fill_response_group_create_p(void);
extern int utc_autofill_fill_response_group_create_n(void);

extern int utc_autofill_fill_response_group_destroy_p(void);
extern int utc_autofill_fill_response_group_destroy_n(void);

extern int utc_autofill_fill_response_group_clone_p(void);
extern int utc_autofill_fill_response_group_clone_n(void);

extern int utc_autofill_fill_response_group_foreach_item_p(void);
extern int utc_autofill_fill_response_group_foreach_item_n(void);

extern int utc_autofill_fill_response_item_create_p(void);
extern int utc_autofill_fill_response_item_create_n(void);

extern int utc_autofill_fill_response_item_destroy_p(void);
extern int utc_autofill_fill_response_item_destroy_n(void);

extern int utc_autofill_fill_response_item_clone_p(void);
extern int utc_autofill_fill_response_item_clone_n(void);

extern int utc_autofill_fill_response_item_set_id_p(void);
extern int utc_autofill_fill_response_item_set_id_n(void);

extern int utc_autofill_fill_response_item_get_id_p(void);
extern int utc_autofill_fill_response_item_get_id_n(void);

extern int utc_autofill_fill_response_item_set_value_p(void);
extern int utc_autofill_fill_response_item_set_value_n(void);

extern int utc_autofill_fill_response_item_get_value_p(void);
extern int utc_autofill_fill_response_item_get_value_n(void);

extern int utc_autofill_fill_response_item_set_presentation_text_p(void);
extern int utc_autofill_fill_response_item_set_presentation_text_n(void);

extern int utc_autofill_fill_response_item_get_presentation_text_p(void);
extern int utc_autofill_fill_response_item_get_presentation_text_n(void);

extern int utc_autofill_fill_response_item_set_autofill_hint_p(void);
extern int utc_autofill_fill_response_item_set_autofill_hint_n(void);

extern int utc_autofill_fill_response_item_get_autofill_hint_p(void);
extern int utc_autofill_fill_response_item_get_autofill_hint_n(void);

extern int utc_autofill_save_item_create_p(void);
extern int utc_autofill_save_item_create_n(void);
extern int utc_autofill_save_item_destroy_p(void);
extern int utc_autofill_save_item_destroy_n(void);

extern int utc_autofill_save_item_clone_p(void);
extern int utc_autofill_save_item_clone_n(void);

extern int utc_autofill_save_item_set_autofill_hint_p(void);
extern int utc_autofill_save_item_set_autofill_hint_n(void);
extern int utc_autofill_save_item_get_autofill_hint_p(void);
extern int utc_autofill_save_item_get_autofill_hint_n(void);

extern int utc_autofill_save_item_set_id_p(void);
extern int utc_autofill_save_item_set_id_n(void);
extern int utc_autofill_save_item_get_id_p(void);
extern int utc_autofill_save_item_get_id_n(void);

extern int utc_autofill_save_item_set_label_p(void);
extern int utc_autofill_save_item_set_label_n(void);
extern int utc_autofill_save_item_get_label_p(void);
extern int utc_autofill_save_item_get_label_n(void);

extern int utc_autofill_save_item_set_sensitive_data_p(void);
extern int utc_autofill_save_item_set_sensitive_data_n(void);
extern int utc_autofill_save_item_get_sensitive_data_p(void);
extern int utc_autofill_save_item_get_sensitive_data_n(void);

extern int utc_autofill_save_item_set_value_p(void);
extern int utc_autofill_save_item_set_value_n(void);
extern int utc_autofill_save_item_get_value_p(void);
extern int utc_autofill_save_item_get_value_n(void);

extern int utc_autofill_error_info_create_p(void);
extern int utc_autofill_error_info_create_n(void);
extern int utc_autofill_error_info_destroy_p(void);
extern int utc_autofill_error_info_destroy_n(void);
extern int utc_autofill_error_info_set_app_id_p(void);
extern int utc_autofill_error_info_set_app_id_n(void);
extern int utc_autofill_error_info_get_app_id_p(void);
extern int utc_autofill_error_info_get_app_id_n(void);
extern int utc_autofill_error_info_set_error_code_p(void);
extern int utc_autofill_error_info_set_error_code_n(void);
extern int utc_autofill_error_info_get_error_code_p(void);
extern int utc_autofill_error_info_get_error_code_n(void);

// client
extern void utc_capi_ui_autofill_startup(void);
extern void utc_capi_ui_autofill_cleanup(void);

extern int utc_autofill_create_p(void);
extern int utc_autofill_create_n(void);

extern int utc_autofill_destroy_p(void);
extern int utc_autofill_destroy_n(void);

extern int utc_autofill_connect_p(void);
extern int utc_autofill_connect_n(void);

extern int utc_autofill_auth_info_request_p(void);
extern int utc_autofill_auth_info_request_n(void);

extern int utc_autofill_auth_info_set_received_cb_p(void);
extern int utc_autofill_auth_info_set_received_cb_n(void);

extern int utc_autofill_auth_info_unset_received_cb_p(void);
extern int utc_autofill_auth_info_unset_received_cb_n(void);

extern int utc_autofill_fill_request_p(void);
extern int utc_autofill_fill_request_n(void);

extern int utc_autofill_cancel_fill_request_p(void);
extern int utc_autofill_cancel_fill_request_n(void);

extern int utc_autofill_fill_response_set_received_cb_p(void);
extern int utc_autofill_fill_response_set_received_cb_n(void);

extern int utc_autofill_fill_response_unset_received_cb_p(void);
extern int utc_autofill_fill_response_unset_received_cb_n(void);

extern int utc_autofill_commit_p(void);
extern int utc_autofill_commit_n(void);

extern int utc_autofill_error_info_set_received_cb_p(void);
extern int utc_autofill_error_info_set_received_cb_n(void);

extern int utc_autofill_error_info_unset_received_cb_p(void);
extern int utc_autofill_error_info_unset_received_cb_n(void);

// service
extern void utc_capi_ui_autofill_service_startup(void);
extern void utc_capi_ui_autofill_service_cleanup(void);

extern int utc_autofill_service_initialize_p(void);
extern int utc_autofill_service_deinitialize_p(void);

extern int utc_autofill_service_set_auth_info_requested_cb_p(void);
extern int utc_autofill_service_set_auth_info_requested_cb_n(void);

extern int utc_autofill_service_unset_auth_info_requested_cb_p(void);

extern int utc_autofill_service_send_auth_info_cb_n(void);

extern int utc_autofill_service_set_fill_requested_cb_p(void);
extern int utc_autofill_service_set_fill_requested_cb_n(void);

extern int utc_autofill_service_unset_fill_requested_cb_p(void);

extern int utc_autofill_service_set_cancel_fill_requested_cb_p(void);
extern int utc_autofill_service_set_cancel_fill_requested_cb_n(void);

extern int utc_autofill_service_unset_cancel_fill_requested_cb_p(void);

extern int utc_autofill_service_send_fill_response_n(void);

extern int utc_autofill_service_send_error_info_cb_n(void);

extern int utc_autofill_service_set_committed_cb_p(void);
extern int utc_autofill_service_set_committed_cb_n(void);

extern int utc_autofill_service_unset_committed_cb_p(void);

extern int utc_autofill_service_set_terminate_received_cb_p(void);
extern int utc_autofill_service_set_terminate_received_cb_n(void);

extern int utc_autofill_service_unset_terminate_received_cb_p(void);

testcase tc_array[] = {
    // common
    {"utc_autofill_item_create_p", utc_autofill_item_create_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_create_n", utc_autofill_item_create_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_destroy_p", utc_autofill_item_destroy_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_destroy_n", utc_autofill_item_destroy_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_item_clone_p", utc_autofill_item_clone_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_clone_n", utc_autofill_item_clone_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_item_set_autofill_hint_p", utc_autofill_item_set_autofill_hint_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_set_autofill_hint_n", utc_autofill_item_set_autofill_hint_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_get_autofill_hint_p", utc_autofill_item_get_autofill_hint_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_get_autofill_hint_n", utc_autofill_item_get_autofill_hint_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_item_set_id_p", utc_autofill_item_set_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_set_id_n", utc_autofill_item_set_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_get_id_p", utc_autofill_item_get_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_get_id_n", utc_autofill_item_get_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_item_set_label_p", utc_autofill_item_set_label_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_set_label_n", utc_autofill_item_set_label_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_get_label_p", utc_autofill_item_get_label_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_get_label_n", utc_autofill_item_get_label_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_item_set_sensitive_data_p", utc_autofill_item_set_sensitive_data_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_set_sensitive_data_n", utc_autofill_item_set_sensitive_data_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_get_sensitive_data_p", utc_autofill_item_get_sensitive_data_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_get_sensitive_data_n", utc_autofill_item_get_sensitive_data_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_item_set_value_p", utc_autofill_item_set_value_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_set_value_n", utc_autofill_item_set_value_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_get_value_p", utc_autofill_item_get_value_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_item_get_value_n", utc_autofill_item_get_value_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_auth_info_create_p", utc_autofill_auth_info_create_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_create_n", utc_autofill_auth_info_create_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_destroy_p", utc_autofill_auth_info_destroy_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_destroy_n", utc_autofill_auth_info_destroy_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_auth_info_set_app_id_p", utc_autofill_auth_info_set_app_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_set_app_id_n", utc_autofill_auth_info_set_app_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_app_id_p", utc_autofill_auth_info_get_app_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_app_id_n", utc_autofill_auth_info_get_app_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_auth_info_set_view_id_p", utc_autofill_auth_info_set_view_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_set_view_id_n", utc_autofill_auth_info_set_view_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_view_id_p", utc_autofill_auth_info_get_view_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_view_id_n", utc_autofill_auth_info_get_view_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_auth_info_set_autofill_data_present_p", utc_autofill_auth_info_set_autofill_data_present_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_set_autofill_data_present_n", utc_autofill_auth_info_set_autofill_data_present_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_autofill_data_present_p", utc_autofill_auth_info_get_autofill_data_present_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_autofill_data_present_n", utc_autofill_auth_info_get_autofill_data_present_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_auth_info_set_authentication_needed_p", utc_autofill_auth_info_set_authentication_needed_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_set_authentication_needed_n", utc_autofill_auth_info_set_authentication_needed_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_authentication_needed_p", utc_autofill_auth_info_get_authentication_needed_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_authentication_needed_n", utc_autofill_auth_info_get_authentication_needed_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_auth_info_set_service_name_p", utc_autofill_auth_info_set_service_name_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_set_service_name_n", utc_autofill_auth_info_set_service_name_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_service_name_p", utc_autofill_auth_info_get_service_name_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_service_name_n", utc_autofill_auth_info_get_service_name_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_auth_info_set_service_message_p", utc_autofill_auth_info_set_service_message_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_set_service_message_n", utc_autofill_auth_info_set_service_message_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_service_message_p", utc_autofill_auth_info_get_service_message_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_service_message_n", utc_autofill_auth_info_get_service_message_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_auth_info_set_service_logo_image_path_p", utc_autofill_auth_info_set_service_logo_image_path_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_set_service_logo_image_path_n", utc_autofill_auth_info_set_service_logo_image_path_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_service_logo_image_path_p", utc_autofill_auth_info_get_service_logo_image_path_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_auth_info_get_service_logo_image_path_n", utc_autofill_auth_info_get_service_logo_image_path_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_view_info_create_p", utc_autofill_view_info_create_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_create_n", utc_autofill_view_info_create_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_destroy_p", utc_autofill_view_info_destroy_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_destroy_n", utc_autofill_view_info_destroy_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_view_info_set_app_id_p", utc_autofill_view_info_set_app_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_set_app_id_n", utc_autofill_view_info_set_app_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_get_app_id_p", utc_autofill_view_info_get_app_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_get_app_id_n", utc_autofill_view_info_get_app_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_view_info_set_view_id_p", utc_autofill_view_info_set_view_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_set_view_id_n", utc_autofill_view_info_set_view_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_get_view_id_p", utc_autofill_view_info_get_view_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_get_view_id_n", utc_autofill_view_info_get_view_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_view_info_add_item_p", utc_autofill_view_info_add_item_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_add_item_n", utc_autofill_view_info_add_item_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_view_info_foreach_item_p", utc_autofill_view_info_foreach_item_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_view_info_foreach_item_n", utc_autofill_view_info_foreach_item_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_create_p", utc_autofill_fill_response_create_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_create_n", utc_autofill_fill_response_create_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_destroy_p", utc_autofill_fill_response_destroy_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_destroy_n", utc_autofill_fill_response_destroy_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_set_app_id_p", utc_autofill_fill_response_set_app_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_set_app_id_n", utc_autofill_fill_response_set_app_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_get_app_id_p", utc_autofill_fill_response_get_app_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_get_app_id_n", utc_autofill_fill_response_get_app_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_set_view_id_p", utc_autofill_fill_response_set_view_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_set_view_id_n", utc_autofill_fill_response_set_view_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_get_view_id_p", utc_autofill_fill_response_get_view_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_get_view_id_n", utc_autofill_fill_response_get_view_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_add_group_p", utc_autofill_fill_response_add_group_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_add_group_n", utc_autofill_fill_response_add_group_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_foreach_group_p", utc_autofill_fill_response_foreach_group_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_foreach_group_n", utc_autofill_fill_response_foreach_group_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_get_group_count_p", utc_autofill_fill_response_get_group_count_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_get_group_count_n", utc_autofill_fill_response_get_group_count_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_group_add_item_p", utc_autofill_fill_response_group_add_item_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_group_add_item_n", utc_autofill_fill_response_group_add_item_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_group_create_p", utc_autofill_fill_response_group_create_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_group_create_n", utc_autofill_fill_response_group_create_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_group_destroy_p", utc_autofill_fill_response_group_destroy_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_group_destroy_n", utc_autofill_fill_response_group_destroy_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_group_clone_p", utc_autofill_fill_response_group_clone_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_group_clone_n", utc_autofill_fill_response_group_clone_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_group_foreach_item_p", utc_autofill_fill_response_group_foreach_item_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_group_foreach_item_n", utc_autofill_fill_response_group_foreach_item_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_view_info_create_p", utc_autofill_save_view_info_create_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_create_n", utc_autofill_save_view_info_create_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_destroy_p", utc_autofill_save_view_info_destroy_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_destroy_n", utc_autofill_save_view_info_destroy_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_view_info_set_app_id_p", utc_autofill_save_view_info_set_app_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_set_app_id_n", utc_autofill_save_view_info_set_app_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_get_app_id_p", utc_autofill_save_view_info_get_app_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_get_app_id_n", utc_autofill_save_view_info_get_app_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_view_info_set_view_id_p", utc_autofill_save_view_info_set_view_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_set_view_id_n", utc_autofill_save_view_info_set_view_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_get_view_id_p", utc_autofill_save_view_info_get_view_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_get_view_id_n", utc_autofill_save_view_info_get_view_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_view_info_set_view_title_p", utc_autofill_save_view_info_set_view_title_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_set_view_title_n", utc_autofill_save_view_info_set_view_title_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_get_view_title_p", utc_autofill_save_view_info_get_view_title_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_get_view_title_n", utc_autofill_save_view_info_get_view_title_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_view_info_add_item_p", utc_autofill_save_view_info_add_item_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_add_item_n", utc_autofill_save_view_info_add_item_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_view_info_foreach_item_p", utc_autofill_save_view_info_foreach_item_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_view_info_foreach_item_n", utc_autofill_save_view_info_foreach_item_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_create_p", utc_autofill_fill_response_item_create_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_create_n", utc_autofill_fill_response_item_create_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_destroy_p", utc_autofill_fill_response_item_destroy_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_destroy_n", utc_autofill_fill_response_item_destroy_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_clone_p", utc_autofill_fill_response_item_clone_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_clone_n", utc_autofill_fill_response_item_clone_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_set_id_p", utc_autofill_fill_response_item_set_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_set_id_n", utc_autofill_fill_response_item_set_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_get_id_p", utc_autofill_fill_response_item_get_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_get_id_n", utc_autofill_fill_response_item_get_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_set_value_p", utc_autofill_fill_response_item_set_value_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_set_value_n", utc_autofill_fill_response_item_set_value_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_get_value_p", utc_autofill_fill_response_item_get_value_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_get_value_n", utc_autofill_fill_response_item_get_value_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_set_presentation_text_p", utc_autofill_fill_response_item_set_presentation_text_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_set_presentation_text_n", utc_autofill_fill_response_item_set_presentation_text_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_get_presentation_text_p", utc_autofill_fill_response_item_get_presentation_text_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_get_presentation_text_n", utc_autofill_fill_response_item_get_presentation_text_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_set_autofill_hint_p", utc_autofill_fill_response_item_set_autofill_hint_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_set_autofill_hint_n", utc_autofill_fill_response_item_set_autofill_hint_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_fill_response_item_get_autofill_hint_p", utc_autofill_fill_response_item_get_autofill_hint_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_fill_response_item_get_autofill_hint_n", utc_autofill_fill_response_item_get_autofill_hint_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_item_create_p", utc_autofill_save_item_create_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_create_n", utc_autofill_save_item_create_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_destroy_p", utc_autofill_save_item_destroy_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_destroy_n", utc_autofill_save_item_destroy_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_clone_p", utc_autofill_save_item_clone_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_clone_n", utc_autofill_save_item_clone_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_item_set_autofill_hint_p", utc_autofill_save_item_set_autofill_hint_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_set_autofill_hint_n", utc_autofill_save_item_set_autofill_hint_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_get_autofill_hint_p", utc_autofill_save_item_get_autofill_hint_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_get_autofill_hint_n", utc_autofill_save_item_get_autofill_hint_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_item_set_id_p", utc_autofill_save_item_set_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_set_id_n", utc_autofill_save_item_set_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_get_id_p", utc_autofill_save_item_get_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_get_id_n", utc_autofill_save_item_get_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_item_set_label_p", utc_autofill_save_item_set_label_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_set_label_n", utc_autofill_save_item_set_label_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_get_label_p", utc_autofill_save_item_get_label_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_get_label_n", utc_autofill_save_item_get_label_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_item_set_sensitive_data_p", utc_autofill_save_item_set_sensitive_data_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_set_sensitive_data_n", utc_autofill_save_item_set_sensitive_data_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_get_sensitive_data_p", utc_autofill_save_item_get_sensitive_data_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_get_sensitive_data_n", utc_autofill_save_item_get_sensitive_data_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_save_item_set_value_p", utc_autofill_save_item_set_value_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_set_value_n", utc_autofill_save_item_set_value_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_get_value_p", utc_autofill_save_item_get_value_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_save_item_get_value_n", utc_autofill_save_item_get_value_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_error_info_create_p", utc_autofill_error_info_create_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_error_info_create_n", utc_autofill_error_info_create_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_error_info_destroy_p", utc_autofill_error_info_destroy_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_error_info_destroy_n", utc_autofill_error_info_destroy_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_error_info_set_app_id_p", utc_autofill_error_info_set_app_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_error_info_set_app_id_n", utc_autofill_error_info_set_app_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_error_info_get_app_id_p", utc_autofill_error_info_get_app_id_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_error_info_get_app_id_n", utc_autofill_error_info_get_app_id_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    {"utc_autofill_error_info_set_error_code_p", utc_autofill_error_info_set_error_code_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_error_info_set_error_code_n", utc_autofill_error_info_set_error_code_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_error_info_get_error_code_p", utc_autofill_error_info_get_error_code_p, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},
    {"utc_autofill_error_info_get_error_code_n", utc_autofill_error_info_get_error_code_n, utc_capi_ui_autofill_common_startup, utc_capi_ui_autofill_common_cleanup},

    // client
    {"utc_autofill_create_p", utc_autofill_create_p, NULL, NULL},
    {"utc_autofill_create_n", utc_autofill_create_n, NULL, NULL},

    {"utc_autofill_destroy_p", utc_autofill_destroy_p, NULL, NULL},
    {"utc_autofill_destroy_n", utc_autofill_destroy_n, NULL, NULL},

    {"utc_autofill_connect_p", utc_autofill_connect_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_connect_n", utc_autofill_connect_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_auth_info_request_p", utc_autofill_auth_info_request_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_auth_info_request_n", utc_autofill_auth_info_request_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_auth_info_set_received_cb_p", utc_autofill_auth_info_set_received_cb_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_auth_info_set_received_cb_n", utc_autofill_auth_info_set_received_cb_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_auth_info_unset_received_cb_p", utc_autofill_auth_info_unset_received_cb_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_auth_info_unset_received_cb_n", utc_autofill_auth_info_unset_received_cb_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_fill_request_p", utc_autofill_fill_request_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_fill_request_n", utc_autofill_fill_request_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_cancel_fill_request_p", utc_autofill_cancel_fill_request_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_cancel_fill_request_n", utc_autofill_cancel_fill_request_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_fill_response_set_received_cb_p", utc_autofill_fill_response_set_received_cb_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_fill_response_set_received_cb_n", utc_autofill_fill_response_set_received_cb_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_fill_response_unset_received_cb_p", utc_autofill_fill_response_unset_received_cb_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_fill_response_unset_received_cb_n", utc_autofill_fill_response_unset_received_cb_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_commit_p", utc_autofill_commit_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_commit_n", utc_autofill_commit_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_error_info_set_received_cb_p", utc_autofill_error_info_set_received_cb_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_error_info_set_received_cb_n", utc_autofill_error_info_set_received_cb_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_error_info_unset_received_cb_p", utc_autofill_error_info_unset_received_cb_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_error_info_unset_received_cb_n", utc_autofill_error_info_unset_received_cb_n, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    // service
    {"utc_autofill_service_initialize_p", utc_autofill_service_initialize_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},
    {"utc_autofill_service_deinitialize_p", utc_autofill_service_deinitialize_p, utc_capi_ui_autofill_startup, utc_capi_ui_autofill_cleanup},

    {"utc_autofill_service_set_auth_info_requested_cb_p", utc_autofill_service_set_auth_info_requested_cb_p, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_set_auth_info_requested_cb_n", utc_autofill_service_set_auth_info_requested_cb_n, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_unset_auth_info_requested_cb_p", utc_autofill_service_unset_auth_info_requested_cb_p, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_send_auth_info_cb_n", utc_autofill_service_send_auth_info_cb_n, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_set_fill_requested_cb_p", utc_autofill_service_set_fill_requested_cb_p, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_set_fill_requested_cb_n", utc_autofill_service_set_fill_requested_cb_n, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_unset_fill_requested_cb_p", utc_autofill_service_unset_fill_requested_cb_p, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_set_cancel_fill_requested_cb_p", utc_autofill_service_set_cancel_fill_requested_cb_p, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_set_cancel_fill_requested_cb_n", utc_autofill_service_set_cancel_fill_requested_cb_n, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_unset_cancel_fill_requested_cb_p", utc_autofill_service_unset_cancel_fill_requested_cb_p, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_send_fill_response_n", utc_autofill_service_send_fill_response_n, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_send_error_info_cb_n", utc_autofill_service_send_error_info_cb_n, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_set_committed_cb_p", utc_autofill_service_set_committed_cb_p, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_set_committed_cb_n", utc_autofill_service_set_committed_cb_n, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_unset_committed_cb_p", utc_autofill_service_unset_committed_cb_p, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_set_terminate_received_cb_p", utc_autofill_service_set_terminate_received_cb_p, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_set_terminate_received_cb_n", utc_autofill_service_set_terminate_received_cb_n, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},
    {"utc_autofill_service_unset_terminate_received_cb_p", utc_autofill_service_unset_terminate_received_cb_p, utc_capi_ui_autofill_service_startup, utc_capi_ui_autofill_service_cleanup},

    {NULL, NULL}
};

#endif // __TCT_CAPI_UI_AUTOFILL_NATIVE_H__
