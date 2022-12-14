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
#ifndef __TCT_PACKAGE-MANAGER-NATIVE_H__
#define __TCT_PACKAGE-MANAGER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_package_manager_filter_add_bool_cleanup(void);
extern void utc_package_manager_filter_count_cleanup(void);
extern void utc_package_manager_filter_foreach_cleanup(void);

extern int utc_package_manager_package_info_clone_p(void);
extern int utc_package_manager_package_info_clone_n(void);
extern int utc_ApplicationFW_package_info_create_p(void);
extern int utc_ApplicationFW_package_info_create_n1(void);
extern int utc_ApplicationFW_package_info_create_n2(void);
extern int utc_package_manager_package_info_destroy_p(void);
extern int utc_package_manager_package_info_destroy_n(void);
extern int utc_package_manager_package_info_foreach_app_from_package_p(void);
extern int utc_package_manager_package_info_foreach_app_from_package_n(void);
extern int utc_package_manager_package_info_foreach_cert_info_p(void);
extern int utc_package_manager_package_info_foreach_cert_info_n(void);
extern int utc_package_manager_package_info_foreach_dependency_info_p(void);
extern int utc_package_manager_package_info_foreach_dependency_info_n(void);
extern int utc_package_manager_package_info_foreach_dependency_info_depends_on_p(void);
extern int utc_package_manager_package_info_foreach_dependency_info_depends_on_n(void);
extern int utc_package_manager_package_info_foreach_privilege_info_p(void);
extern int utc_package_manager_package_info_foreach_privilege_info_n(void);
extern int utc_package_manager_package_info_foreach_required_privilege_p(void);
extern int utc_package_manager_package_info_foreach_required_privilege_n(void);
extern int utc_package_manager_package_info_foreach_res_allowed_package_p(void);
extern int utc_package_manager_package_info_foreach_res_allowed_package_n(void);
extern int utc_package_manager_package_info_get_icon_p(void);
extern int utc_package_manager_package_info_get_icon_n(void);
extern int utc_package_manager_package_info_get_installed_storage_p(void);
extern int utc_package_manager_package_info_get_installed_storage_n(void);
extern int utc_package_manager_package_info_get_installed_time_p(void);
extern int utc_package_manager_package_info_get_installed_time_n(void);
extern int utc_package_manager_package_info_get_label_p(void);
extern int utc_package_manager_package_info_get_label_n(void);
extern int utc_package_manager_package_info_get_main_app_id_p(void);
extern int utc_package_manager_package_info_get_main_app_id_n(void);
extern int utc_package_manager_package_info_get_package_p(void);
extern int utc_package_manager_package_info_get_package_n(void);
extern int utc_package_manager_package_info_get_res_type_p(void);
extern int utc_package_manager_package_info_get_res_type_n(void);
extern int utc_package_manager_package_info_get_res_version_p(void);
extern int utc_package_manager_package_info_get_res_version_n(void);
extern int utc_package_manager_package_info_get_root_path_p(void);
extern int utc_package_manager_package_info_get_root_path_n(void);
extern int utc_package_manager_package_info_get_type_p(void);
extern int utc_package_manager_package_info_get_type_n(void);
extern int utc_package_manager_package_info_get_version_p(void);
extern int utc_package_manager_package_info_get_version_n(void);
extern int utc_package_managerpackage_info_is_accessible_p(void);
extern int utc_package_managerpackage_info_is_accessible_n(void);
extern int utc_package_manager_package_info_is_equal_p(void);
extern int utc_package_manager_package_info_is_equal_n(void);
extern int utc_package_manager_package_info_is_preload_package_p(void);
extern int utc_package_manager_package_info_is_preload_package_n(void);
extern int utc_package_manager_package_info_is_removable_package_p(void);
extern int utc_package_manager_package_info_is_removable_package_n(void);
extern int utc_package_manager_package_info_is_system_package_p(void);
extern int utc_package_manager_package_info_is_system_package_n(void);
extern int utc_ApplicationFW_package_manager_clear_cache_dir_p(void);
extern int utc_ApplicationFW_package_manager_clear_cache_dir_n(void);
extern int utc_ApplicationFW_package_manager_compare_app_cert_info_p(void);
extern int utc_ApplicationFW_package_manager_compare_app_cert_info_n1(void);
extern int utc_ApplicationFW_package_manager_compare_app_cert_info_n2(void);
extern int utc_ApplicationFW_package_manager_compare_package_cert_info_p(void);
extern int utc_ApplicationFW_package_manager_compare_package_cert_info_n(void);
extern int utc_ApplicationFW_package_manager_create_p(void);
extern int utc_ApplicationFW_package_manager_create_n(void);
extern int utc_ApplicationFW_package_manager_destroy_p(void);
extern int utc_ApplicationFW_package_manager_destroy_n(void);
extern int utc_ApplicationFW_package_manager_foreach_package_info_p(void);
extern int utc_ApplicationFW_package_manager_foreach_package_info_n(void);
extern int utc_ApplicationFW_package_manager_get_package_id_by_app_id_p(void);
extern int utc_ApplicationFW_package_manager_get_package_id_by_app_id_n(void);
extern int utc_ApplicationFW_package_manager_get_package_info_p(void);
extern int utc_ApplicationFW_package_manager_get_package_info_n1(void);
extern int utc_ApplicationFW_package_manager_get_package_info_n2(void);
extern int utc_ApplicationFW_package_manager_get_package_size_info_p(void);
extern int utc_ApplicationFW_package_manager_get_package_size_info_n(void);
extern int utc_ApplicationFW_package_manager_get_permission_type_p(void);
extern int utc_ApplicationFW_package_manager_get_permission_type_n(void);
extern int utc_ApplicationFW_package_manager_get_total_package_size_info_p(void);
extern int utc_ApplicationFW_package_manager_get_total_package_size_info_n(void);
extern int utc_ApplicationFW_package_manager_is_preload_package_by_app_id_p(void);
extern int utc_ApplicationFW_package_manager_is_preload_package_by_app_id_n(void);
extern int utc_ApplicationFW_package_manager_set_event_cb_p(void);
extern int utc_ApplicationFW_package_manager_set_event_cb_n(void);
extern int utc_ApplicationFW_package_manager_set_event_status_p1(void);
extern int utc_ApplicationFW_package_manager_set_event_status_p2(void);
extern int utc_ApplicationFW_package_manager_set_event_status_n(void);
extern int utc_ApplicationFW_package_manager_unset_event_cb_p(void);
extern int utc_ApplicationFW_package_manager_unset_event_cb_n(void);
extern int utc_package_manager_package_manager_filter_create_p(void);
extern int utc_package_manager_package_manager_filter_create_n(void);
extern int utc_package_manager_package_manager_filter_add_bool_p(void);
extern int utc_package_manager_package_manager_filter_add_bool_n1(void);
extern int utc_package_manager_package_manager_filter_add_bool_n2(void);
extern int utc_package_manager_package_manager_filter_add_string_p(void);
extern int utc_package_manager_package_manager_filter_add_string_n1(void);
extern int utc_package_manager_package_manager_filter_add_string_n2(void);
extern int utc_package_manager_package_manager_filter_add_string_n3(void);
extern int utc_package_manager_package_manager_filter_count_p(void);
extern int utc_package_manager_package_manager_filter_count_n1(void);
extern int utc_package_manager_package_manager_filter_count_n2(void);
extern int utc_package_manager_package_manager_filter_foreach_package_info_p(void);
extern int utc_package_manager_package_manager_filter_foreach_package_info_n(void);
extern int utc_package_manager_package_manager_filter_destroy_p(void);
extern int utc_package_manager_package_manager_filter_destroy_n(void);
extern int utc_ApplicationFW_package_size_info_get_data_size_p(void);
extern int utc_ApplicationFW_package_size_info_get_data_size_n(void);
extern int utc_ApplicationFW_package_size_info_get_app_size_p(void);
extern int utc_ApplicationFW_package_size_info_get_app_size_n(void);
extern int utc_ApplicationFW_package_size_info_get_cache_size_p(void);
extern int utc_ApplicationFW_package_size_info_get_cache_size_n(void);
extern int utc_ApplicationFW_package_size_info_get_external_data_size_p(void);
extern int utc_ApplicationFW_package_size_info_get_external_data_size_n(void);
extern int utc_ApplicationFW_package_size_info_get_external_app_size_p(void);
extern int utc_ApplicationFW_package_size_info_get_external_app_size_n(void);
extern int utc_ApplicationFW_package_size_info_get_external_cache_size_p(void);
extern int utc_ApplicationFW_package_size_info_get_external_cache_size_n(void);
extern int utc_ApplicationFW_package_info_updateinfo_create_p(void);
extern int utc_ApplicationFW_package_info_updateinfo_create_n1(void);
extern int utc_ApplicationFW_package_info_updateinfo_create_n2(void);
extern int utc_ApplicationFW_package_info_updateinfo_destroy_p(void);
extern int utc_ApplicationFW_package_info_updateinfo_destroy_n(void);
extern int utc_ApplicationFW_package_info_updateinfo_foreach_info_p(void);
extern int utc_ApplicationFW_package_info_updateinfo_foreach_info_n(void);
extern int utc_ApplicationFW_package_info_updateinfo_get_pkgid_p(void);
extern int utc_ApplicationFW_package_info_updateinfo_get_pkgid_n1(void);
extern int utc_ApplicationFW_package_info_updateinfo_get_pkgid_n2(void);
extern int utc_ApplicationFW_package_info_updateinfo_get_type_p(void);
extern int utc_ApplicationFW_package_info_updateinfo_get_type_n1(void);
extern int utc_ApplicationFW_package_info_updateinfo_get_type_n2(void);
extern int utc_ApplicationFW_package_info_updateinfo_get_version_p(void);
extern int utc_ApplicationFW_package_info_updateinfo_get_version_n1(void);
extern int utc_ApplicationFW_package_info_updateinfo_get_version_n2(void);
extern int utc_ApplicationFW_package_archive_info_create_p(void);
extern int utc_ApplicationFW_package_archive_info_create_n(void);
extern int utc_ApplicationFW_package_archive_info_destroy_p(void);
extern int utc_ApplicationFW_package_archive_info_destroy_n(void);
extern int utc_ApplicationFW_package_archive_info_foreach_direct_dependency_p(void);
extern int utc_ApplicationFW_package_archive_info_foreach_direct_dependency_n(void);
extern int utc_ApplicationFW_package_archive_info_get_api_version_p(void);
extern int utc_ApplicationFW_package_archive_info_get_api_version_n(void);
extern int utc_ApplicationFW_package_archive_info_get_author_p(void);
extern int utc_ApplicationFW_package_archive_info_get_author_n(void);
extern int utc_ApplicationFW_package_archive_info_get_description_p(void);
extern int utc_ApplicationFW_package_archive_info_get_description_n(void);
extern int utc_ApplicationFW_package_archive_info_get_icon_p(void);
extern int utc_ApplicationFW_package_archive_info_get_icon_n(void);
extern int utc_ApplicationFW_package_archive_info_get_label_p(void);
extern int utc_ApplicationFW_package_archive_info_get_label_n(void);
extern int utc_ApplicationFW_package_archive_info_get_package_p(void);
extern int utc_ApplicationFW_package_archive_info_get_package_n(void);
extern int utc_ApplicationFW_package_archive_info_get_type_p(void);
extern int utc_ApplicationFW_package_archive_info_get_type_n(void);
extern int utc_ApplicationFW_package_archive_info_get_version_p(void);
extern int utc_ApplicationFW_package_archive_info_get_version_n(void);

testcase tc_array[] = {
	{"utc_package_manager_package_info_clone_p",utc_package_manager_package_info_clone_p,NULL,NULL},
	{"utc_package_manager_package_info_clone_n",utc_package_manager_package_info_clone_n,NULL,NULL},
	{"utc_ApplicationFW_package_info_create_p",utc_ApplicationFW_package_info_create_p,NULL,NULL},
	{"utc_ApplicationFW_package_info_create_n1",utc_ApplicationFW_package_info_create_n1,NULL,NULL},
	{"utc_ApplicationFW_package_info_create_n2",utc_ApplicationFW_package_info_create_n2,NULL,NULL},
	{"utc_package_manager_package_info_destroy_p",utc_package_manager_package_info_destroy_p,NULL,NULL},
	{"utc_package_manager_package_info_destroy_n",utc_package_manager_package_info_destroy_n,NULL,NULL},
	{"utc_package_manager_package_info_foreach_app_from_package_p",utc_package_manager_package_info_foreach_app_from_package_p,NULL,NULL},
	{"utc_package_manager_package_info_foreach_app_from_package_n",utc_package_manager_package_info_foreach_app_from_package_n,NULL,NULL},
	{"utc_package_manager_package_info_foreach_cert_info_p",utc_package_manager_package_info_foreach_cert_info_p,NULL,NULL},
	{"utc_package_manager_package_info_foreach_cert_info_n",utc_package_manager_package_info_foreach_cert_info_n,NULL,NULL},
	{"utc_package_manager_package_info_foreach_dependency_info_p",utc_package_manager_package_info_foreach_dependency_info_p,NULL,NULL},
	{"utc_package_manager_package_info_foreach_dependency_info_n",utc_package_manager_package_info_foreach_dependency_info_n,NULL,NULL},
	{"utc_package_manager_package_info_foreach_dependency_info_depends_on_p",utc_package_manager_package_info_foreach_dependency_info_depends_on_p,NULL,NULL},
	{"utc_package_manager_package_info_foreach_dependency_info_depends_on_n",utc_package_manager_package_info_foreach_dependency_info_depends_on_n,NULL,NULL},
	{"utc_package_manager_package_info_foreach_privilege_info_p",utc_package_manager_package_info_foreach_privilege_info_p,NULL,NULL},
	{"utc_package_manager_package_info_foreach_privilege_info_n",utc_package_manager_package_info_foreach_privilege_info_n,NULL,NULL},
	{"utc_package_manager_package_info_foreach_required_privilege_p",utc_package_manager_package_info_foreach_required_privilege_p,NULL,NULL},
	{"utc_package_manager_package_info_foreach_required_privilege_n",utc_package_manager_package_info_foreach_required_privilege_n,NULL,NULL},
	{"utc_package_manager_package_info_foreach_res_allowed_package_p",utc_package_manager_package_info_foreach_res_allowed_package_p,NULL,NULL},
	{"utc_package_manager_package_info_foreach_res_allowed_package_n",utc_package_manager_package_info_foreach_res_allowed_package_n,NULL,NULL},
	{"utc_package_manager_package_info_get_icon_p",utc_package_manager_package_info_get_icon_p,NULL,NULL},
	{"utc_package_manager_package_info_get_icon_n",utc_package_manager_package_info_get_icon_n,NULL,NULL},
	{"utc_package_manager_package_info_get_installed_storage_p",utc_package_manager_package_info_get_installed_storage_p,NULL,NULL},
	{"utc_package_manager_package_info_get_installed_storage_n",utc_package_manager_package_info_get_installed_storage_n,NULL,NULL},
	{"utc_package_manager_package_info_get_installed_time_p",utc_package_manager_package_info_get_installed_time_p,NULL,NULL},
	{"utc_package_manager_package_info_get_installed_time_n",utc_package_manager_package_info_get_installed_time_n,NULL,NULL},
	{"utc_package_manager_package_info_get_label_p",utc_package_manager_package_info_get_label_p,NULL,NULL},
	{"utc_package_manager_package_info_get_label_n",utc_package_manager_package_info_get_label_n,NULL,NULL},
	{"utc_package_manager_package_info_get_main_app_id_p",utc_package_manager_package_info_get_main_app_id_p,NULL,NULL},
	{"utc_package_manager_package_info_get_main_app_id_n",utc_package_manager_package_info_get_main_app_id_n,NULL,NULL},
	{"utc_package_manager_package_info_get_package_p",utc_package_manager_package_info_get_package_p,NULL,NULL},
	{"utc_package_manager_package_info_get_package_n",utc_package_manager_package_info_get_package_n,NULL,NULL},
	{"utc_package_manager_package_info_get_res_type_p",utc_package_manager_package_info_get_res_type_p,NULL,NULL},
	{"utc_package_manager_package_info_get_res_type_n",utc_package_manager_package_info_get_res_type_n,NULL,NULL},
	{"utc_package_manager_package_info_get_res_version_p",utc_package_manager_package_info_get_res_version_p,NULL,NULL},
	{"utc_package_manager_package_info_get_res_version_n",utc_package_manager_package_info_get_res_version_n,NULL,NULL},
	{"utc_package_manager_package_info_get_root_path_p",utc_package_manager_package_info_get_root_path_p,NULL,NULL},
	{"utc_package_manager_package_info_get_root_path_n",utc_package_manager_package_info_get_root_path_n,NULL,NULL},
	{"utc_package_manager_package_info_get_type_p",utc_package_manager_package_info_get_type_p,NULL,NULL},
	{"utc_package_manager_package_info_get_type_n",utc_package_manager_package_info_get_type_n,NULL,NULL},
	{"utc_package_manager_package_info_get_version_p",utc_package_manager_package_info_get_version_p,NULL,NULL},
	{"utc_package_manager_package_info_get_version_n",utc_package_manager_package_info_get_version_n,NULL,NULL},
	{"utc_package_managerpackage_info_is_accessible_p",utc_package_managerpackage_info_is_accessible_p,NULL,NULL},
	{"utc_package_managerpackage_info_is_accessible_n",utc_package_managerpackage_info_is_accessible_n,NULL,NULL},
	{"utc_package_manager_package_info_is_equal_p",utc_package_manager_package_info_is_equal_p,NULL,NULL},
	{"utc_package_manager_package_info_is_equal_n",utc_package_manager_package_info_is_equal_n,NULL,NULL},
	{"utc_package_manager_package_info_is_preload_package_p",utc_package_manager_package_info_is_preload_package_p,NULL,NULL},
	{"utc_package_manager_package_info_is_preload_package_n",utc_package_manager_package_info_is_preload_package_n,NULL,NULL},
	{"utc_package_manager_package_info_is_removable_package_p",utc_package_manager_package_info_is_removable_package_p,NULL,NULL},
	{"utc_package_manager_package_info_is_removable_package_n",utc_package_manager_package_info_is_removable_package_n,NULL,NULL},
	{"utc_package_manager_package_info_is_system_package_p",utc_package_manager_package_info_is_system_package_p,NULL,NULL},
	{"utc_package_manager_package_info_is_system_package_n",utc_package_manager_package_info_is_system_package_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_clear_cache_dir_p",utc_ApplicationFW_package_manager_clear_cache_dir_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_clear_cache_dir_n",utc_ApplicationFW_package_manager_clear_cache_dir_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_compare_app_cert_info_p",utc_ApplicationFW_package_manager_compare_app_cert_info_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_compare_app_cert_info_n1",utc_ApplicationFW_package_manager_compare_app_cert_info_n1,NULL,NULL},
	{"utc_ApplicationFW_package_manager_compare_app_cert_info_n2",utc_ApplicationFW_package_manager_compare_app_cert_info_n2,NULL,NULL},
	{"utc_ApplicationFW_package_manager_compare_package_cert_info_p",utc_ApplicationFW_package_manager_compare_package_cert_info_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_compare_package_cert_info_n",utc_ApplicationFW_package_manager_compare_package_cert_info_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_create_p",utc_ApplicationFW_package_manager_create_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_create_n",utc_ApplicationFW_package_manager_create_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_destroy_p",utc_ApplicationFW_package_manager_destroy_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_destroy_n",utc_ApplicationFW_package_manager_destroy_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_foreach_package_info_p",utc_ApplicationFW_package_manager_foreach_package_info_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_foreach_package_info_n",utc_ApplicationFW_package_manager_foreach_package_info_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_package_id_by_app_id_p",utc_ApplicationFW_package_manager_get_package_id_by_app_id_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_package_id_by_app_id_n",utc_ApplicationFW_package_manager_get_package_id_by_app_id_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_package_info_p",utc_ApplicationFW_package_manager_get_package_info_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_package_info_n1",utc_ApplicationFW_package_manager_get_package_info_n1,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_package_info_n2",utc_ApplicationFW_package_manager_get_package_info_n2,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_package_size_info_p",utc_ApplicationFW_package_manager_get_package_size_info_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_package_size_info_n",utc_ApplicationFW_package_manager_get_package_size_info_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_permission_type_p",utc_ApplicationFW_package_manager_get_permission_type_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_permission_type_n",utc_ApplicationFW_package_manager_get_permission_type_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_total_package_size_info_p", utc_ApplicationFW_package_manager_get_total_package_size_info_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_get_total_package_size_info_n", utc_ApplicationFW_package_manager_get_total_package_size_info_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_is_preload_package_by_app_id_p",utc_ApplicationFW_package_manager_is_preload_package_by_app_id_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_is_preload_package_by_app_id_n",utc_ApplicationFW_package_manager_is_preload_package_by_app_id_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_set_event_cb_p",utc_ApplicationFW_package_manager_set_event_cb_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_set_event_cb_n",utc_ApplicationFW_package_manager_set_event_cb_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_set_event_status_p1",utc_ApplicationFW_package_manager_set_event_status_p1,NULL,NULL},
	{"utc_ApplicationFW_package_manager_set_event_status_p2",utc_ApplicationFW_package_manager_set_event_status_p2,NULL,NULL},
	{"utc_ApplicationFW_package_manager_set_event_status_n",utc_ApplicationFW_package_manager_set_event_status_n,NULL,NULL},
	{"utc_ApplicationFW_package_manager_unset_event_cb_p",utc_ApplicationFW_package_manager_unset_event_cb_p,NULL,NULL},
	{"utc_ApplicationFW_package_manager_unset_event_cb_n",utc_ApplicationFW_package_manager_unset_event_cb_n,NULL,NULL},
	{"utc_package_manager_package_manager_filter_create_p",utc_package_manager_package_manager_filter_create_p,NULL,NULL},
	{"utc_package_manager_package_manager_filter_create_n",utc_package_manager_package_manager_filter_create_n,NULL,NULL},
	{"utc_package_manager_package_manager_filter_add_bool_p",utc_package_manager_package_manager_filter_add_bool_p,NULL,utc_package_manager_filter_add_bool_cleanup},
	{"utc_package_manager_package_manager_filter_add_bool_n1",utc_package_manager_package_manager_filter_add_bool_n1,NULL,utc_package_manager_filter_add_bool_cleanup},
	{"utc_package_manager_package_manager_filter_add_bool_n2",utc_package_manager_package_manager_filter_add_bool_n2,NULL,utc_package_manager_filter_add_bool_cleanup},
	{"utc_package_manager_package_manager_filter_add_string_p",utc_package_manager_package_manager_filter_add_string_p,NULL,NULL},
	{"utc_package_manager_package_manager_filter_add_string_n1",utc_package_manager_package_manager_filter_add_string_n1,NULL,NULL},
	{"utc_package_manager_package_manager_filter_add_string_n2",utc_package_manager_package_manager_filter_add_string_n2,NULL,NULL},
	{"utc_package_manager_package_manager_filter_add_string_n3",utc_package_manager_package_manager_filter_add_string_n3,NULL,NULL},
	{"utc_package_manager_package_manager_filter_count_p",utc_package_manager_package_manager_filter_count_p,NULL,utc_package_manager_filter_count_cleanup},
	{"utc_package_manager_package_manager_filter_count_n1",utc_package_manager_package_manager_filter_count_n1,NULL,utc_package_manager_filter_count_cleanup},
	{"utc_package_manager_package_manager_filter_count_n2",utc_package_manager_package_manager_filter_count_n2,NULL,utc_package_manager_filter_count_cleanup},
	{"utc_package_manager_package_manager_filter_foreach_package_info_p",utc_package_manager_package_manager_filter_foreach_package_info_p,NULL,utc_package_manager_filter_foreach_cleanup},
	{"utc_package_manager_package_manager_filter_foreach_package_info_n",utc_package_manager_package_manager_filter_foreach_package_info_n,NULL,utc_package_manager_filter_foreach_cleanup},
	{"utc_package_manager_package_manager_filter_destroy_p",utc_package_manager_package_manager_filter_destroy_p,NULL,NULL},
	{"utc_package_manager_package_manager_filter_destroy_n",utc_package_manager_package_manager_filter_destroy_n,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_data_size_p",utc_ApplicationFW_package_size_info_get_data_size_p,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_data_size_n",utc_ApplicationFW_package_size_info_get_data_size_n,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_app_size_p",utc_ApplicationFW_package_size_info_get_app_size_p,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_app_size_n",utc_ApplicationFW_package_size_info_get_app_size_n,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_cache_size_p",utc_ApplicationFW_package_size_info_get_cache_size_p,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_cache_size_n",utc_ApplicationFW_package_size_info_get_cache_size_n,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_external_data_size_p",utc_ApplicationFW_package_size_info_get_external_data_size_p,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_external_data_size_n",utc_ApplicationFW_package_size_info_get_external_data_size_n,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_external_app_size_p",utc_ApplicationFW_package_size_info_get_external_app_size_p,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_external_app_size_n",utc_ApplicationFW_package_size_info_get_external_app_size_n,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_external_cache_size_p",utc_ApplicationFW_package_size_info_get_external_cache_size_p,NULL,NULL},
	{"utc_ApplicationFW_package_size_info_get_external_cache_size_n",utc_ApplicationFW_package_size_info_get_external_cache_size_n,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_create_p",utc_ApplicationFW_package_info_updateinfo_create_p,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_create_n1",utc_ApplicationFW_package_info_updateinfo_create_n1,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_create_n2",utc_ApplicationFW_package_info_updateinfo_create_n2,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_destroy_p",utc_ApplicationFW_package_info_updateinfo_destroy_p,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_destroy_n",utc_ApplicationFW_package_info_updateinfo_destroy_n,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_foreach_info_p",utc_ApplicationFW_package_info_updateinfo_foreach_info_p,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_foreach_info_n",utc_ApplicationFW_package_info_updateinfo_foreach_info_n,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_get_pkgid_p",utc_ApplicationFW_package_info_updateinfo_get_pkgid_p,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_get_pkgid_n1",utc_ApplicationFW_package_info_updateinfo_get_pkgid_n1,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_get_pkgid_n2",utc_ApplicationFW_package_info_updateinfo_get_pkgid_n2,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_get_type_p",utc_ApplicationFW_package_info_updateinfo_get_type_p,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_get_type_n1",utc_ApplicationFW_package_info_updateinfo_get_type_n1,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_get_type_n2",utc_ApplicationFW_package_info_updateinfo_get_type_n2,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_get_version_p",utc_ApplicationFW_package_info_updateinfo_get_version_p,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_get_version_n1",utc_ApplicationFW_package_info_updateinfo_get_version_n1,NULL,NULL},
	{"utc_ApplicationFW_package_info_updateinfo_get_version_n2",utc_ApplicationFW_package_info_updateinfo_get_version_n2,NULL,NULL},
	{"utc_ApplicationFW_package_archive_info_create_p", utc_ApplicationFW_package_archive_info_create_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_create_n", utc_ApplicationFW_package_archive_info_create_n, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_destroy_p", utc_ApplicationFW_package_archive_info_destroy_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_destroy_n", utc_ApplicationFW_package_archive_info_destroy_n, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_foreach_direct_dependency_p", utc_ApplicationFW_package_archive_info_foreach_direct_dependency_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_foreach_direct_dependency_n", utc_ApplicationFW_package_archive_info_foreach_direct_dependency_n, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_api_version_p", utc_ApplicationFW_package_archive_info_get_api_version_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_api_version_n", utc_ApplicationFW_package_archive_info_get_api_version_n, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_author_p", utc_ApplicationFW_package_archive_info_get_author_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_author_n", utc_ApplicationFW_package_archive_info_get_author_n, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_description_p", utc_ApplicationFW_package_archive_info_get_description_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_description_n", utc_ApplicationFW_package_archive_info_get_description_n, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_icon_p", utc_ApplicationFW_package_archive_info_get_icon_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_icon_n", utc_ApplicationFW_package_archive_info_get_icon_n, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_label_p", utc_ApplicationFW_package_archive_info_get_label_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_label_n", utc_ApplicationFW_package_archive_info_get_label_n, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_package_p", utc_ApplicationFW_package_archive_info_get_package_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_package_n", utc_ApplicationFW_package_archive_info_get_package_n, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_type_p", utc_ApplicationFW_package_archive_info_get_type_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_type_n", utc_ApplicationFW_package_archive_info_get_type_n, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_version_p", utc_ApplicationFW_package_archive_info_get_version_p, NULL, NULL},
	{"utc_ApplicationFW_package_archive_info_get_version_n", utc_ApplicationFW_package_archive_info_get_version_n, NULL, NULL},
	{NULL, NULL}
};

#endif // __TCT_PACKAGE-MANAGER-NATIVE_H__
