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

extern void ITs_accounts_svc_startup(void);
extern void ITs_accounts_svc_cleanup(void);

extern int ITc_account_type_foreach_account_type_from_db_p(void);
extern int ITc_account_type_query_provider_feature_by_app_id_p(void);
extern int ITc_account_query_from_db_by_package_name_p(void);
extern int ITc_account_create_destroy_p(void);
extern int ITc_account_set_get_user_name_p(void);
extern int ITc_account_set_get_user_text_p(void);
extern int ITc_account_set_get_user_int_p(void);
extern int ITc_account_set_get_display_name_p(void);
extern int ITc_account_set_get_domain_name_p(void);
extern int ITc_account_set_get_email_address_p(void);
extern int ITc_account_set_get_auth_type_p(void);
extern int ITc_account_set_get_source_p(void);
extern int ITc_account_set_get_icon_path_p(void);
extern int ITc_account_set_get_package_name_p(void);
extern int ITc_account_set_get_access_token_p(void);
extern int ITc_account_set_get_capability_p(void);
extern int ITc_account_set_get_custom_p(void);
extern int ITc_account_set_get_secret_p(void);
extern int ITc_account_set_get_sync_support_p(void);
extern int ITc_account_subscribe_unsubscribe_notification_p(void);
extern int ITc_account_type_create_destroy_p(void);
extern int ITc_account_type_get_icon_path_p(void);
extern int ITc_account_type_get_app_id_p(void);
extern int ITc_account_type_get_small_icon_path_p(void);
extern int ITc_account_type_get_service_provider_id_p(void);
extern int ITc_account_type_get_provider_feature_all_p(void);
extern int ITc_account_type_get_multiple_account_support_p(void);
extern int ITc_account_type_query_by_app_id_p(void);
extern int ITc_account_type_get_label_p(void);
extern int ITc_account_type_query_label_by_app_id_p(void);
extern int ITc_account_type_query_supported_feature_p(void);
extern int ITc_account_type_query_app_id_exist_update_to_db_p(void);
extern int ITc_account_insert_to_db_delete_by_id_p(void);
extern int ITc_account_query_account_by_account_id_p(void);
extern int ITc_account_query_from_db_update_by_user_name_p(void);
extern int ITc_account_foreach_account_from_db_p(void);
extern int ITc_account_get_total_count_from_db_p(void);
extern int ITc_account_get_account_id_p(void);
extern int ITc_account_update_to_db_by_id_ex_p(void);
extern int ITc_account_update_sync_status_by_id_p(void);
extern int ITc_account_query_capability_by_account_id_p(void);
extern int ITc_account_query_account_by_capability_type_p(void);
extern int ITc_account_query_account_by_capability_p(void);
extern int ITc_account_update_to_db_by_id_p(void);
extern int ITc_account_type_query_label_by_locale_p(void);
extern int ITc_account_delete_from_db_by_package_name_p(void);
extern int ITc_account_delete_by_user_name_p(void);
extern int ITc_account_type_query_by_provider_feature_p(void);
extern int ITc_account_query_deleted_account_info_by_account_id_p(void);

testcase tc_array[] = {
	{"ITc_account_type_foreach_account_type_from_db_p",ITc_account_type_foreach_account_type_from_db_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_query_provider_feature_by_app_id_p",ITc_account_type_query_provider_feature_by_app_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_query_from_db_by_package_name_p",ITc_account_query_from_db_by_package_name_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_create_destroy_p",ITc_account_create_destroy_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_user_name_p",ITc_account_set_get_user_name_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_user_text_p",ITc_account_set_get_user_text_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_user_int_p",ITc_account_set_get_user_int_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_display_name_p",ITc_account_set_get_display_name_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_domain_name_p",ITc_account_set_get_domain_name_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_email_address_p",ITc_account_set_get_email_address_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_auth_type_p",ITc_account_set_get_auth_type_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_source_p",ITc_account_set_get_source_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_icon_path_p",ITc_account_set_get_icon_path_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_package_name_p",ITc_account_set_get_package_name_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_access_token_p",ITc_account_set_get_access_token_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_capability_p",ITc_account_set_get_capability_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_custom_p",ITc_account_set_get_custom_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_secret_p",ITc_account_set_get_secret_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_set_get_sync_support_p",ITc_account_set_get_sync_support_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_subscribe_unsubscribe_notification_p",ITc_account_subscribe_unsubscribe_notification_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_create_destroy_p",ITc_account_type_create_destroy_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_get_icon_path_p",ITc_account_type_get_icon_path_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_get_app_id_p",ITc_account_type_get_app_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_get_small_icon_path_p",ITc_account_type_get_small_icon_path_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_get_service_provider_id_p",ITc_account_type_get_service_provider_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_get_provider_feature_all_p",ITc_account_type_get_provider_feature_all_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_get_multiple_account_support_p",ITc_account_type_get_multiple_account_support_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_query_by_app_id_p",ITc_account_type_query_by_app_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_get_label_p",ITc_account_type_get_label_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_query_label_by_app_id_p",ITc_account_type_query_label_by_app_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_query_supported_feature_p",ITc_account_type_query_supported_feature_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_query_app_id_exist_update_to_db_p",ITc_account_type_query_app_id_exist_update_to_db_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_insert_to_db_delete_by_id_p",ITc_account_insert_to_db_delete_by_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_query_account_by_account_id_p",ITc_account_query_account_by_account_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_query_from_db_update_by_user_name_p",ITc_account_query_from_db_update_by_user_name_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_foreach_account_from_db_p",ITc_account_foreach_account_from_db_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_get_total_count_from_db_p",ITc_account_get_total_count_from_db_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_get_account_id_p",ITc_account_get_account_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_update_to_db_by_id_ex_p",ITc_account_update_to_db_by_id_ex_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_update_sync_status_by_id_p",ITc_account_update_sync_status_by_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_query_capability_by_account_id_p",ITc_account_query_capability_by_account_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_query_account_by_capability_type_p",ITc_account_query_account_by_capability_type_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_query_account_by_capability_p",ITc_account_query_account_by_capability_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_update_to_db_by_id_p",ITc_account_update_to_db_by_id_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_query_label_by_locale_p",ITc_account_type_query_label_by_locale_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_delete_from_db_by_package_name_p",ITc_account_delete_from_db_by_package_name_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_delete_by_user_name_p",ITc_account_delete_by_user_name_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_type_query_by_provider_feature_p",ITc_account_type_query_by_provider_feature_p,ITs_accounts_svc_startup,ITs_accounts_svc_cleanup},
	{"ITc_account_query_deleted_account_info_by_account_id_p", ITc_account_query_deleted_account_info_by_account_id_p, ITs_accounts_svc_startup, ITs_accounts_svc_cleanup},
	{NULL, NULL}
};

#endif // __TCT_ACCOUNTS-SVC-NATIVE_H__
