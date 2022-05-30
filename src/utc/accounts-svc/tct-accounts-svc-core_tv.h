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
#ifndef __TCT_ACCOUNTS-SVC-NATIVE_H__
#define __TCT_ACCOUNTS-SVC-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_account_startup(void);
extern void utc_account_cleanup(void);

extern int utc_account_connect_p(void);
extern int utc_account_connect_readonly_p(void);
extern int utc_account_disconnect_p(void);
extern int utc_account_destroy_p(void);
extern int utc_account_destroy_n(void);
extern int utc_account_create_p(void);
extern int utc_account_create_n(void);
extern int utc_account_insert_to_db_p(void);
extern int utc_account_insert_to_db_n(void);
extern int utc_account_set_display_name_p(void);
extern int utc_account_set_display_name_n(void);
extern int utc_account_set_user_name_p(void);
extern int utc_account_set_user_name_n(void);
extern int utc_account_set_icon_path_p(void);
extern int utc_account_set_icon_path_n(void);
extern int utc_account_set_domain_name_p(void);
extern int utc_account_set_domain_name_n(void);
extern int utc_account_set_email_address_p(void);
extern int utc_account_set_email_address_n(void);
extern int utc_account_set_source_p(void);
extern int utc_account_set_source_n(void);
extern int utc_account_set_custom_p(void);
extern int utc_account_set_custom_n(void);
extern int utc_account_get_custom_p(void);
extern int utc_account_get_custom_n(void);
extern int utc_account_get_custom_all_p(void);
extern int utc_account_get_custom_all_n(void);
extern int utc_account_set_package_name_p(void);
extern int utc_account_set_package_name_n(void);
extern int utc_account_set_access_token_p(void);
extern int utc_account_set_access_token_n(void);
extern int utc_account_set_auth_type_p(void);
extern int utc_account_set_auth_type_n(void);
extern int utc_account_set_secret_p(void);
extern int utc_account_set_secret_n(void);
extern int utc_account_set_sync_support_p(void);
extern int utc_account_set_sync_support_n(void);
extern int utc_account_set_user_text_p(void);
extern int utc_account_set_user_text_n(void);
extern int utc_account_set_user_int_p(void);
extern int utc_account_set_user_int_n(void);
extern int utc_account_set_capability_p(void);
extern int utc_account_set_capability_n(void);
extern int utc_account_get_capability_all_p(void);
extern int utc_account_get_capability_all_n(void);
extern int utc_account_get_display_name_p(void);
extern int utc_account_get_display_name_n(void);
extern int utc_account_get_account_id_p(void);
extern int utc_account_get_account_id_n(void);
extern int utc_account_get_user_name_p(void);
extern int utc_account_get_user_name_n(void);
extern int utc_account_get_icon_path_p(void);
extern int utc_account_get_icon_path_n(void);
extern int utc_account_get_domain_name_p(void);
extern int utc_account_get_domain_name_n(void);
extern int utc_account_get_email_address_p(void);
extern int utc_account_get_email_address_n(void);
extern int utc_account_get_source_p(void);
extern int utc_account_get_source_n(void);
extern int utc_account_get_package_name_p(void);
extern int utc_account_get_package_name_n(void);
extern int utc_account_get_access_token_p(void);
extern int utc_account_get_access_token_n(void);
extern int utc_account_get_auth_type_p(void);
extern int utc_account_get_auth_type_n(void);
extern int utc_account_get_secret_p(void);
extern int utc_account_get_sync_support_p(void);
extern int utc_account_get_secret_n(void);
extern int utc_account_get_sync_support_n(void);
extern int utc_account_get_user_text_p(void);
extern int utc_account_get_user_text_n(void);
extern int utc_account_get_user_int_p(void);
extern int utc_account_get_user_int_n(void);
extern int utc_account_get_capability_p(void);
extern int utc_account_get_capability_n(void);
extern int utc_account_foreach_account_from_db_p(void);
extern int utc_account_foreach_account_from_db_n(void);
extern int utc_account_query_account_by_account_id_p(void);
extern int utc_account_query_account_by_account_id_n(void);
extern int utc_account_query_deleted_account_info_by_account_id_p(void);
extern int utc_account_query_deleted_account_info_by_account_id_n(void);
extern int utc_account_query_account_by_user_name_p(void);
extern int utc_account_query_account_by_user_name_n(void);
extern int utc_account_query_account_by_package_name_p(void);
extern int utc_account_query_account_by_package_name_n(void);
extern int utc_account_query_account_by_capability_p(void);
extern int utc_account_query_account_by_capability_n(void);
extern int utc_account_query_account_by_capability_type_p(void);
extern int utc_account_query_account_by_capability_type_n(void);
extern int utc_account_query_capability_by_account_id_p(void);
extern int utc_account_query_capability_by_account_id_n(void);
extern int utc_account_get_total_count_from_db_p(void);
extern int utc_account_get_total_count_from_db_n(void);
extern int utc_account_update_sync_status_by_id_p(void);
extern int utc_account_update_sync_status_by_id_n(void);
extern int utc_account_delete_from_db_by_id_p(void);
extern int utc_account_delete_from_db_by_id_n(void);
extern int utc_account_delete_from_db_by_user_name_p(void);
extern int utc_account_delete_from_db_by_user_name_n(void);
extern int utc_account_delete_from_db_by_package_name_p(void);
extern int utc_account_delete_from_db_by_package_name_n(void);
extern int utc_account_update_to_db_by_id_p(void);
extern int utc_account_update_to_db_by_id_n(void);
extern int utc_account_update_to_db_by_user_name_p(void);
extern int utc_account_update_to_db_by_user_name_n(void);
extern int utc_account_subscribe_create_p(void);
extern int utc_account_subscribe_create_n(void);
extern int utc_account_subscribe_notification_p(void);
extern int utc_account_subscribe_notification_n(void);
extern int utc_account_unsubscribe_notification_p(void);
extern int utc_account_unsubscribe_notification_n(void);
extern int utc_account_type_create_p(void);
extern int utc_account_type_create_n(void);
extern int utc_account_type_destroy_p(void);
extern int utc_account_type_destroy_n(void);
extern int utc_account_type_get_app_id_p(void);
extern int utc_account_type_get_app_id_n(void);
extern int utc_account_type_get_icon_path_p(void);
extern int utc_account_type_get_icon_path_n(void);
extern int utc_account_type_get_label_by_locale_p(void);
extern int utc_account_type_get_label_by_locale_n(void);
extern int utc_account_type_get_label_p(void);
extern int utc_account_type_get_label_n(void);
extern int utc_account_type_get_multiple_account_support_p(void);
extern int utc_account_type_get_multiple_account_support_n(void);
extern int utc_account_type_get_provider_feature_all_p(void);
extern int utc_account_type_get_provider_feature_all_n(void);
extern int utc_account_type_get_service_provider_id_p(void);
extern int utc_account_type_get_service_provider_id_n(void);
extern int utc_account_type_get_small_icon_path_p(void);
extern int utc_account_type_get_small_icon_path_n(void);
extern int utc_account_type_query_by_app_id_p(void);
extern int utc_account_type_query_by_app_id_n(void);
extern int utc_account_type_query_app_id_exist_p(void);
extern int utc_account_type_query_app_id_exist_n(void);
extern int utc_account_type_query_by_provider_feature_p(void);
extern int utc_account_type_query_by_provider_feature_n(void);
extern int utc_account_type_query_label_by_app_id_p(void);
extern int utc_account_type_query_label_by_app_id_n(void);
extern int utc_account_type_query_label_by_locale_p(void);
extern int utc_account_type_query_label_by_locale_n(void);
extern int utc_account_type_query_provider_feature_by_app_id_p(void);
extern int utc_account_type_query_provider_feature_by_app_id_n(void);
extern int utc_account_type_query_supported_feature_p(void);
extern int utc_account_type_query_supported_feature_n(void);
extern int utc_account_update_to_db_by_id_ex_p(void);
extern int utc_account_update_to_db_by_id_ex_n(void);
extern int utc_account_type_foreach_account_type_from_db_p(void);
extern int utc_account_type_foreach_account_type_from_db_n(void);

testcase tc_array[] = {
	{"utc_account_connect_p",utc_account_connect_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_connect_readonly_p",utc_account_connect_readonly_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_disconnect_p",utc_account_disconnect_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_destroy_p",utc_account_destroy_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_destroy_n",utc_account_destroy_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_create_p",utc_account_create_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_create_n",utc_account_create_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_insert_to_db_p",utc_account_insert_to_db_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_insert_to_db_n",utc_account_insert_to_db_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_display_name_p",utc_account_set_display_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_display_name_n",utc_account_set_display_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_user_name_p",utc_account_set_user_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_user_name_n",utc_account_set_user_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_icon_path_p",utc_account_set_icon_path_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_icon_path_n",utc_account_set_icon_path_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_domain_name_p",utc_account_set_domain_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_domain_name_n",utc_account_set_domain_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_email_address_p",utc_account_set_email_address_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_email_address_n",utc_account_set_email_address_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_source_p",utc_account_set_source_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_source_n",utc_account_set_source_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_custom_p",utc_account_set_custom_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_custom_n",utc_account_set_custom_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_custom_p",utc_account_get_custom_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_custom_n",utc_account_get_custom_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_custom_all_p",utc_account_get_custom_all_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_custom_all_n",utc_account_get_custom_all_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_package_name_p",utc_account_set_package_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_package_name_n",utc_account_set_package_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_access_token_p",utc_account_set_access_token_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_access_token_n",utc_account_set_access_token_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_auth_type_p",utc_account_set_auth_type_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_auth_type_n",utc_account_set_auth_type_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_secret_p",utc_account_set_secret_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_secret_n",utc_account_set_secret_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_sync_support_p",utc_account_set_sync_support_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_sync_support_n",utc_account_set_sync_support_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_user_text_p",utc_account_set_user_text_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_user_text_n",utc_account_set_user_text_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_user_int_p",utc_account_set_user_int_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_user_int_n",utc_account_set_user_int_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_capability_p",utc_account_set_capability_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_set_capability_n",utc_account_set_capability_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_capability_all_p",utc_account_get_capability_all_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_capability_all_n",utc_account_get_capability_all_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_display_name_p",utc_account_get_display_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_display_name_n",utc_account_get_display_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_account_id_p",utc_account_get_account_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_account_id_n",utc_account_get_account_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_user_name_p",utc_account_get_user_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_user_name_n",utc_account_get_user_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_icon_path_p",utc_account_get_icon_path_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_icon_path_n",utc_account_get_icon_path_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_domain_name_p",utc_account_get_domain_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_domain_name_n",utc_account_get_domain_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_email_address_p",utc_account_get_email_address_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_email_address_n",utc_account_get_email_address_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_source_p",utc_account_get_source_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_source_n",utc_account_get_source_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_package_name_p",utc_account_get_package_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_package_name_n",utc_account_get_package_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_access_token_p",utc_account_get_access_token_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_access_token_n",utc_account_get_access_token_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_auth_type_p",utc_account_get_auth_type_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_auth_type_n",utc_account_get_auth_type_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_secret_p",utc_account_get_secret_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_sync_support_p",utc_account_get_sync_support_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_secret_n",utc_account_get_secret_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_sync_support_n",utc_account_get_sync_support_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_user_text_p",utc_account_get_user_text_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_user_text_n",utc_account_get_user_text_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_user_int_p",utc_account_get_user_int_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_user_int_n",utc_account_get_user_int_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_capability_p",utc_account_get_capability_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_capability_n",utc_account_get_capability_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_foreach_account_from_db_p",utc_account_foreach_account_from_db_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_foreach_account_from_db_n",utc_account_foreach_account_from_db_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_account_by_account_id_p",utc_account_query_account_by_account_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_account_by_account_id_n",utc_account_query_account_by_account_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_deleted_account_info_by_account_id_p",utc_account_query_deleted_account_info_by_account_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_deleted_account_info_by_account_id_n",utc_account_query_deleted_account_info_by_account_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_account_by_user_name_p",utc_account_query_account_by_user_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_account_by_user_name_n",utc_account_query_account_by_user_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_account_by_package_name_p",utc_account_query_account_by_package_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_account_by_package_name_n",utc_account_query_account_by_package_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_account_by_capability_p",utc_account_query_account_by_capability_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_account_by_capability_n",utc_account_query_account_by_capability_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_account_by_capability_type_p",utc_account_query_account_by_capability_type_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_account_by_capability_type_n",utc_account_query_account_by_capability_type_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_capability_by_account_id_p",utc_account_query_capability_by_account_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_query_capability_by_account_id_n",utc_account_query_capability_by_account_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_total_count_from_db_p",utc_account_get_total_count_from_db_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_get_total_count_from_db_n",utc_account_get_total_count_from_db_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_update_sync_status_by_id_p",utc_account_update_sync_status_by_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_update_sync_status_by_id_n",utc_account_update_sync_status_by_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_delete_from_db_by_id_p",utc_account_delete_from_db_by_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_delete_from_db_by_id_n",utc_account_delete_from_db_by_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_delete_from_db_by_user_name_p",utc_account_delete_from_db_by_user_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_delete_from_db_by_user_name_n",utc_account_delete_from_db_by_user_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_delete_from_db_by_package_name_p",utc_account_delete_from_db_by_package_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_delete_from_db_by_package_name_n",utc_account_delete_from_db_by_package_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_update_to_db_by_id_p",utc_account_update_to_db_by_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_update_to_db_by_id_n",utc_account_update_to_db_by_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_update_to_db_by_user_name_p",utc_account_update_to_db_by_user_name_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_update_to_db_by_user_name_n",utc_account_update_to_db_by_user_name_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_subscribe_create_p",utc_account_subscribe_create_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_subscribe_create_n",utc_account_subscribe_create_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_subscribe_notification_p",utc_account_subscribe_notification_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_subscribe_notification_n",utc_account_subscribe_notification_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_unsubscribe_notification_p",utc_account_unsubscribe_notification_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_unsubscribe_notification_n",utc_account_unsubscribe_notification_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_create_p",utc_account_type_create_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_create_n",utc_account_type_create_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_destroy_p",utc_account_type_destroy_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_destroy_n",utc_account_type_destroy_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_app_id_p",utc_account_type_get_app_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_app_id_n",utc_account_type_get_app_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_icon_path_p",utc_account_type_get_icon_path_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_icon_path_n",utc_account_type_get_icon_path_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_label_by_locale_p",utc_account_type_get_label_by_locale_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_label_by_locale_n",utc_account_type_get_label_by_locale_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_label_p",utc_account_type_get_label_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_label_n",utc_account_type_get_label_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_multiple_account_support_p",utc_account_type_get_multiple_account_support_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_multiple_account_support_n",utc_account_type_get_multiple_account_support_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_provider_feature_all_p",utc_account_type_get_provider_feature_all_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_provider_feature_all_n",utc_account_type_get_provider_feature_all_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_service_provider_id_p",utc_account_type_get_service_provider_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_service_provider_id_n",utc_account_type_get_service_provider_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_small_icon_path_p",utc_account_type_get_small_icon_path_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_get_small_icon_path_n",utc_account_type_get_small_icon_path_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_by_app_id_p",utc_account_type_query_by_app_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_by_app_id_n",utc_account_type_query_by_app_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_app_id_exist_p",utc_account_type_query_app_id_exist_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_app_id_exist_n",utc_account_type_query_app_id_exist_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_by_provider_feature_p",utc_account_type_query_by_provider_feature_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_by_provider_feature_n",utc_account_type_query_by_provider_feature_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_label_by_app_id_p",utc_account_type_query_label_by_app_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_label_by_app_id_n",utc_account_type_query_label_by_app_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_label_by_locale_p",utc_account_type_query_label_by_locale_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_label_by_locale_n",utc_account_type_query_label_by_locale_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_provider_feature_by_app_id_p",utc_account_type_query_provider_feature_by_app_id_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_provider_feature_by_app_id_n",utc_account_type_query_provider_feature_by_app_id_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_supported_feature_p",utc_account_type_query_supported_feature_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_query_supported_feature_n",utc_account_type_query_supported_feature_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_update_to_db_by_id_ex_p",utc_account_update_to_db_by_id_ex_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_update_to_db_by_id_ex_n",utc_account_update_to_db_by_id_ex_n,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_foreach_account_type_from_db_p",utc_account_type_foreach_account_type_from_db_p,utc_account_startup,utc_account_cleanup},
	{"utc_account_type_foreach_account_type_from_db_n",utc_account_type_foreach_account_type_from_db_n,utc_account_startup,utc_account_cleanup},
	{NULL, NULL}
};

#endif // __TCT_ACCOUNTS-SVC-NATIVE_H__
