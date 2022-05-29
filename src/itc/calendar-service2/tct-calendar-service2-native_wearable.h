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
#ifndef __TCT_CALENDAR-SERVICE2-NATIVE_H__
#define __TCT_CALENDAR-SERVICE2-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_calendar_service1_startup(void);
extern void ITs_calendar_service1_cleanup(void);
extern void ITs_calendar_service2_database_startup(void);
extern void ITs_calendar_service2_database_cleanup(void);
extern void ITs_calendar_service2_filter_startup(void);
extern void ITs_calendar_service2_filter_cleanup(void);
extern void ITs_calendar_service2_list_startup(void);
extern void ITs_calendar_service2_list_cleanup(void);
extern void ITs_calendar_service2_query_startup(void);
extern void ITs_calendar_service2_query_cleanup(void);
extern void ITs_calendar_service2_record_startup(void);
extern void ITs_calendar_service2_record_cleanup(void);
extern void ITs_calendar_service2_reminder_startup(void);
extern void ITs_calendar_service2_reminder_cleanup(void);
extern void ITs_calendar_service2_vcalendar_startup(void);
extern void ITs_calendar_service2_vcalendar_cleanup(void);
extern void ITs_calendar_service2_contacts_startup(void);
extern void ITs_calendar_service2_contacts_cleanup(void);

extern int ITc_calendar_connect_disconnect_p(void);
extern int ITc_calendar_connect_disconnect_on_thread_p(void);
extern int ITc_calendar_connect_with_flags_p(void);
extern int ITc_calendar_db_insert_delete_record_p(void);
extern int ITc_calendar_db_insert_delete_records_p(void);
extern int ITc_calendar_db_get_record_p(void);
extern int ITc_calendar_db_get_all_records_p(void);
extern int ITc_calendar_db_update_record_p(void);
extern int ITc_calendar_db_update_records_p(void);
extern int ITc_calendar_db_get_changes_by_version_p(void);
extern int ITc_calendar_db_get_changes_exception_by_version_p(void);
extern int ITc_calendar_db_get_count_p(void);
extern int ITc_calendar_db_get_count_with_query_p(void);
extern int ITc_calendar_db_get_current_version_p(void);
extern int ITc_calendar_db_get_last_change_version_p(void);
extern int ITc_calendar_db_get_records_with_query_p(void);
extern int ITc_calendar_db_replace_record_p(void);
extern int ITc_calendar_db_replace_records_p(void);
extern int ITc_calendar_db_insert_vcalendars_p(void);
extern int ITc_calendar_db_replace_vcalendars_p(void);
extern int ITc_calendar_db_add_remove_changed_cb_p(void);
extern int ITc_calendar_db_clean_after_sync_p(void);
extern int ITc_calendar_add_changed_cb_p(void);
extern int ITc_calendar_filter_create_destroy_p(void);
extern int ITc_calendar_filter_add_caltime_p(void);
extern int ITc_calendar_filter_add_double_p(void);
extern int ITc_calendar_filter_add_int_p(void);
extern int ITc_calendar_filter_add_lli_p(void);
extern int ITc_calendar_filter_add_str_p(void);
extern int ITc_calendar_filter_add_operator_p(void);
extern int ITc_calendar_filter_add_filter_p(void);
extern int ITc_calendar_list_create_destroy_p(void);
extern int ITc_calendar_list_add_remove_p(void);
extern int ITc_calendar_list_first_last_p(void);
extern int ITc_calendar_list_get_count_p(void);
extern int ITc_calendar_list_get_current_record_p_p(void);
extern int ITc_calendar_list_next_prev_p(void);
extern int ITc_calendar_query_create_destroy_p(void);
extern int ITc_calendar_query_set_distinct_p(void);
extern int ITc_calendar_query_set_projection_p(void);
extern int ITc_calendar_query_set_sort_filter_p(void);
extern int ITc_calendar_record_add_remove_child_record_p(void);
extern int ITc_calendar_record_get_child_record_count_p(void);
extern int ITc_calendar_record_create_destroy_p(void);
extern int ITc_calendar_record_clone_p(void);
extern int ITc_calendar_record_set_get_caltime_p(void);
extern int ITc_calendar_record_set_get_double_p(void);
extern int ITc_calendar_record_set_get_int_p(void);
extern int ITc_calendar_record_set_get_lli_p(void);
extern int ITc_calendar_record_set_get_str_p(void);
extern int ITc_calendar_record_get_str_p_p(void);
extern int ITc_calendar_record_get_uri_p_p(void);
extern int ITc_calendar_record_clone_child_record_list_p(void);
extern int ITc_calendar_record_get_child_record_at_p_p(void);
extern int ITc_calendar_reminder_add_remove_cb_p(void);
extern int ITc_calendar_vcalendar_make_from_records_p(void);
extern int ITc_calendar_vcalendar_parse_to_calendar_p(void);
extern int ITc_calendar_vcalendar_parse_to_calendar_foreach_p(void);
extern int ITc_calendar_add_delete_contacts_p(void);
extern int ITc_calendar_modify_contacts_p(void);

testcase tc_array[] = {
	{"ITc_calendar_connect_disconnect_p",ITc_calendar_connect_disconnect_p,ITs_calendar_service1_startup,ITs_calendar_service1_cleanup},
	{"ITc_calendar_connect_disconnect_on_thread_p",ITc_calendar_connect_disconnect_on_thread_p,ITs_calendar_service1_startup,ITs_calendar_service1_cleanup},
	{"ITc_calendar_connect_with_flags_p",ITc_calendar_connect_with_flags_p,ITs_calendar_service1_startup,ITs_calendar_service1_cleanup},
	{"ITc_calendar_db_insert_delete_record_p",ITc_calendar_db_insert_delete_record_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_insert_delete_records_p",ITc_calendar_db_insert_delete_records_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_get_record_p",ITc_calendar_db_get_record_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_get_all_records_p",ITc_calendar_db_get_all_records_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_update_record_p",ITc_calendar_db_update_record_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_update_records_p",ITc_calendar_db_update_records_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_get_changes_by_version_p",ITc_calendar_db_get_changes_by_version_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_get_changes_exception_by_version_p",ITc_calendar_db_get_changes_exception_by_version_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_get_count_p",ITc_calendar_db_get_count_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_get_count_with_query_p",ITc_calendar_db_get_count_with_query_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_get_current_version_p",ITc_calendar_db_get_current_version_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_get_last_change_version_p",ITc_calendar_db_get_last_change_version_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_get_records_with_query_p",ITc_calendar_db_get_records_with_query_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_replace_record_p",ITc_calendar_db_replace_record_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_replace_records_p",ITc_calendar_db_replace_records_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_insert_vcalendars_p",ITc_calendar_db_insert_vcalendars_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_replace_vcalendars_p",ITc_calendar_db_replace_vcalendars_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_add_remove_changed_cb_p",ITc_calendar_db_add_remove_changed_cb_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_db_clean_after_sync_p",ITc_calendar_db_clean_after_sync_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_add_changed_cb_p",ITc_calendar_add_changed_cb_p,ITs_calendar_service2_database_startup,ITs_calendar_service2_database_cleanup},
	{"ITc_calendar_filter_create_destroy_p",ITc_calendar_filter_create_destroy_p,ITs_calendar_service2_filter_startup,ITs_calendar_service2_filter_cleanup},
	{"ITc_calendar_filter_add_caltime_p",ITc_calendar_filter_add_caltime_p,ITs_calendar_service2_filter_startup,ITs_calendar_service2_filter_cleanup},
	{"ITc_calendar_filter_add_double_p",ITc_calendar_filter_add_double_p,ITs_calendar_service2_filter_startup,ITs_calendar_service2_filter_cleanup},
	{"ITc_calendar_filter_add_int_p",ITc_calendar_filter_add_int_p,ITs_calendar_service2_filter_startup,ITs_calendar_service2_filter_cleanup},
	{"ITc_calendar_filter_add_lli_p",ITc_calendar_filter_add_lli_p,ITs_calendar_service2_filter_startup,ITs_calendar_service2_filter_cleanup},
	{"ITc_calendar_filter_add_str_p",ITc_calendar_filter_add_str_p,ITs_calendar_service2_filter_startup,ITs_calendar_service2_filter_cleanup},
	{"ITc_calendar_filter_add_operator_p",ITc_calendar_filter_add_operator_p,ITs_calendar_service2_filter_startup,ITs_calendar_service2_filter_cleanup},
	{"ITc_calendar_filter_add_filter_p",ITc_calendar_filter_add_filter_p,ITs_calendar_service2_filter_startup,ITs_calendar_service2_filter_cleanup},
	{"ITc_calendar_list_create_destroy_p",ITc_calendar_list_create_destroy_p,ITs_calendar_service2_list_startup,ITs_calendar_service2_list_cleanup},
	{"ITc_calendar_list_add_remove_p",ITc_calendar_list_add_remove_p,ITs_calendar_service2_list_startup,ITs_calendar_service2_list_cleanup},
	{"ITc_calendar_list_first_last_p",ITc_calendar_list_first_last_p,ITs_calendar_service2_list_startup,ITs_calendar_service2_list_cleanup},
	{"ITc_calendar_list_get_count_p",ITc_calendar_list_get_count_p,ITs_calendar_service2_list_startup,ITs_calendar_service2_list_cleanup},
	{"ITc_calendar_list_get_current_record_p_p",ITc_calendar_list_get_current_record_p_p,ITs_calendar_service2_list_startup,ITs_calendar_service2_list_cleanup},
	{"ITc_calendar_list_next_prev_p",ITc_calendar_list_next_prev_p,ITs_calendar_service2_list_startup,ITs_calendar_service2_list_cleanup},
	{"ITc_calendar_query_create_destroy_p",ITc_calendar_query_create_destroy_p,ITs_calendar_service2_query_startup,ITs_calendar_service2_query_cleanup},
	{"ITc_calendar_query_set_distinct_p",ITc_calendar_query_set_distinct_p,ITs_calendar_service2_query_startup,ITs_calendar_service2_query_cleanup},
	{"ITc_calendar_query_set_projection_p",ITc_calendar_query_set_projection_p,ITs_calendar_service2_query_startup,ITs_calendar_service2_query_cleanup},
	{"ITc_calendar_query_set_sort_filter_p",ITc_calendar_query_set_sort_filter_p,ITs_calendar_service2_query_startup,ITs_calendar_service2_query_cleanup},
	{"ITc_calendar_record_add_remove_child_record_p",ITc_calendar_record_add_remove_child_record_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_get_child_record_count_p",ITc_calendar_record_get_child_record_count_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_create_destroy_p",ITc_calendar_record_create_destroy_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_clone_p",ITc_calendar_record_clone_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_set_get_caltime_p",ITc_calendar_record_set_get_caltime_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_set_get_double_p",ITc_calendar_record_set_get_double_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_set_get_int_p",ITc_calendar_record_set_get_int_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_set_get_lli_p",ITc_calendar_record_set_get_lli_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_set_get_str_p",ITc_calendar_record_set_get_str_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_get_str_p_p",ITc_calendar_record_get_str_p_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_get_uri_p_p",ITc_calendar_record_get_uri_p_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_clone_child_record_list_p",ITc_calendar_record_clone_child_record_list_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_record_get_child_record_at_p_p",ITc_calendar_record_get_child_record_at_p_p,ITs_calendar_service2_record_startup,ITs_calendar_service2_record_cleanup},
	{"ITc_calendar_reminder_add_remove_cb_p",ITc_calendar_reminder_add_remove_cb_p,ITs_calendar_service2_reminder_startup,ITs_calendar_service2_reminder_cleanup},
	{"ITc_calendar_vcalendar_make_from_records_p",ITc_calendar_vcalendar_make_from_records_p,ITs_calendar_service2_vcalendar_startup,ITs_calendar_service2_vcalendar_cleanup},
	{"ITc_calendar_vcalendar_parse_to_calendar_p",ITc_calendar_vcalendar_parse_to_calendar_p,ITs_calendar_service2_vcalendar_startup,ITs_calendar_service2_vcalendar_cleanup},
	{"ITc_calendar_vcalendar_parse_to_calendar_foreach_p",ITc_calendar_vcalendar_parse_to_calendar_foreach_p,ITs_calendar_service2_vcalendar_startup,ITs_calendar_service2_vcalendar_cleanup},
	{"ITc_calendar_add_delete_contacts_p",ITc_calendar_add_delete_contacts_p,ITs_calendar_service2_contacts_startup,ITs_calendar_service2_contacts_cleanup},
	{"ITc_calendar_modify_contacts_p",ITc_calendar_modify_contacts_p,ITs_calendar_service2_contacts_startup,ITs_calendar_service2_contacts_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CALENDAR-SERVICE2-NATIVE_H__