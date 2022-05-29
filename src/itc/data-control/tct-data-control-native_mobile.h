//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef __TCT_DATA-CONTROL-NATIVE_H__
#define __TCT_DATA-CONTROL-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_data_control_sql_startup(void);
extern void ITs_data_control_sql_cleanup(void);
extern void ITs_data_control_map_startup(void);
extern void ITs_data_control_map_cleanup(void);
extern void ITs_data_control_provider_startup(void);
extern void ITs_data_control_provider_cleanup(void);
extern void ITs_data_control_noti_startup(void);
extern void ITs_data_control_noti_cleanup(void);
extern void ITs_data_control_map_bulk_startup(void);
extern void ITs_data_control_map_bulk_cleanup(void);
extern void ITs_data_control_sql_bulk_startup(void);
extern void ITs_data_control_sql_bulk_cleanup(void);

extern int ITc_data_control_sql_data_control_sql_destroy_create_p(void);
extern int ITc_data_control_sql_data_control_sql_set_get_data_id_p(void);
extern int ITc_data_control_sql_data_control_sql_set_get_provider_id_p(void);
extern int ITc_data_control_sql_data_control_sql_register_unregister_response_cb_p(void);
extern int ITc_data_control_sql_data_control_sql_insert_delete_p(void);
extern int ITc_data_control_sql_data_control_sql_update_select_p(void);
extern int ITc_data_control_sql_data_control_sql_select_with_page_p(void);
extern int ITc_data_control_sql_data_control_sql_get_blob_data_p(void);
extern int ITc_data_control_sql_data_control_sql_get_int_data_p(void);
extern int ITc_data_control_sql_data_control_sql_get_int64_data_p(void);
extern int ITc_data_control_sql_data_control_sql_get_text_data_p(void);
extern int ITc_data_control_sql_data_control_sql_get_double_data_p(void);
extern int ITc_data_control_sql_data_control_sql_get_column_count_p(void);
extern int ITc_data_control_sql_data_control_sql_get_column_item_size_p(void);
extern int ITc_data_control_sql_data_control_sql_get_column_item_type_p(void);
extern int ITc_data_control_sql_data_control_sql_get_column_name_p(void);
extern int ITc_data_control_sql_data_control_sql_step_first_last_p(void);
extern int ITc_data_control_sql_data_control_sql_step_next_previous_p(void);
extern int ITc_data_control_map_data_control_map_destroy_create_p(void);
extern int ITc_data_control_map_data_control_map_set_get_data_id_p(void);
extern int ITc_data_control_map_data_control_map_set_get_p(void);
extern int ITc_data_control_map_data_control_map_set_get_provider_id_p(void);
extern int ITc_data_control_map_data_control_map_register_unregister_response_cb_p(void);
extern int ITc_data_control_map_data_control_map_add_remove_p(void);
extern int ITc_data_control_map_data_control_map_get_with_page_p(void);
extern int ITc_data_control_provider_data_control_provider_create_delete_statement_p(void);
extern int ITc_data_control_provider_data_control_provider_create_insert_statement_p(void);
extern int ITc_data_control_provider_data_control_provider_create_update_statement_p(void);
extern int ITc_data_control_provider_data_control_provider_create_select_statement_p(void);
extern int ITc_data_control_provider_data_control_provider_sql_register_unregister_cb_p(void);
extern int ITc_data_control_provider_data_control_provider_map_register_unregister_cb_p(void);
extern int ITc_data_control_provider_data_control_provider_match_data_id_p(void);
extern int ITc_data_control_provider_data_control_provider_match_provider_id_p(void);
extern int ITc_data_control_provider_add_remove_data_change_consumer_filter_cb_p(void);
extern int ITc_data_control_provider_foreach_data_change_consumer_p(void);
extern int ITs_data_control_add_remove_data_change_cb_p(void);
extern int ITc_data_control_sql_register_response_cb_p(void);
extern int ITc_data_control_provider_send_data_change_noti_p(void);
extern int ITc_data_control_map_bind_unbind_response_cb_p(void);
extern int ITc_data_control_map_bind_unbind_add_bulk_data_response_cb_p(void);
extern int ITc_data_control_map_get_handle_id_p(void);
extern int ITc_data_control_sql_bind_unbind_response_cb_p(void);
extern int ITc_data_control_sql_bind_unbind_insert_bulk_data_response_cb_p(void);
extern int ITc_data_control_sql_get_handle_id_p(void);

testcase tc_array[] = {
	{"ITc_data_control_sql_data_control_sql_destroy_create_p",ITc_data_control_sql_data_control_sql_destroy_create_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_set_get_data_id_p",ITc_data_control_sql_data_control_sql_set_get_data_id_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_set_get_provider_id_p",ITc_data_control_sql_data_control_sql_set_get_provider_id_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_register_unregister_response_cb_p",ITc_data_control_sql_data_control_sql_register_unregister_response_cb_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_insert_delete_p",ITc_data_control_sql_data_control_sql_insert_delete_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_update_select_p",ITc_data_control_sql_data_control_sql_update_select_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_select_with_page_p",ITc_data_control_sql_data_control_sql_select_with_page_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_get_blob_data_p",ITc_data_control_sql_data_control_sql_get_blob_data_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_get_int_data_p",ITc_data_control_sql_data_control_sql_get_int_data_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_get_int64_data_p",ITc_data_control_sql_data_control_sql_get_int64_data_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_get_text_data_p",ITc_data_control_sql_data_control_sql_get_text_data_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_get_double_data_p",ITc_data_control_sql_data_control_sql_get_double_data_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_get_column_count_p",ITc_data_control_sql_data_control_sql_get_column_count_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_get_column_item_size_p",ITc_data_control_sql_data_control_sql_get_column_item_size_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_get_column_item_type_p",ITc_data_control_sql_data_control_sql_get_column_item_type_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_get_column_name_p",ITc_data_control_sql_data_control_sql_get_column_name_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_step_first_last_p",ITc_data_control_sql_data_control_sql_step_first_last_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_sql_data_control_sql_step_next_previous_p",ITc_data_control_sql_data_control_sql_step_next_previous_p,ITs_data_control_sql_startup,ITs_data_control_sql_cleanup},
	{"ITc_data_control_map_data_control_map_destroy_create_p",ITc_data_control_map_data_control_map_destroy_create_p,ITs_data_control_map_startup,ITs_data_control_map_cleanup},
	{"ITc_data_control_map_data_control_map_set_get_data_id_p",ITc_data_control_map_data_control_map_set_get_data_id_p,ITs_data_control_map_startup,ITs_data_control_map_cleanup},
	{"ITc_data_control_map_data_control_map_set_get_p",ITc_data_control_map_data_control_map_set_get_p,ITs_data_control_map_startup,ITs_data_control_map_cleanup},
	{"ITc_data_control_map_data_control_map_set_get_provider_id_p",ITc_data_control_map_data_control_map_set_get_provider_id_p,ITs_data_control_map_startup,ITs_data_control_map_cleanup},
	{"ITc_data_control_map_data_control_map_register_unregister_response_cb_p",ITc_data_control_map_data_control_map_register_unregister_response_cb_p,ITs_data_control_map_startup,ITs_data_control_map_cleanup},
	{"ITc_data_control_map_data_control_map_add_remove_p",ITc_data_control_map_data_control_map_add_remove_p,ITs_data_control_map_startup,ITs_data_control_map_cleanup},
	{"ITc_data_control_map_data_control_map_get_with_page_p",ITc_data_control_map_data_control_map_get_with_page_p,ITs_data_control_map_startup,ITs_data_control_map_cleanup},
	{"ITc_data_control_provider_data_control_provider_create_delete_statement_p",ITc_data_control_provider_data_control_provider_create_delete_statement_p,ITs_data_control_provider_startup,ITs_data_control_provider_cleanup},
	{"ITc_data_control_provider_data_control_provider_create_insert_statement_p",ITc_data_control_provider_data_control_provider_create_insert_statement_p,ITs_data_control_provider_startup,ITs_data_control_provider_cleanup},
	{"ITc_data_control_provider_data_control_provider_create_update_statement_p",ITc_data_control_provider_data_control_provider_create_update_statement_p,ITs_data_control_provider_startup,ITs_data_control_provider_cleanup},
	{"ITc_data_control_provider_data_control_provider_create_select_statement_p",ITc_data_control_provider_data_control_provider_create_select_statement_p,ITs_data_control_provider_startup,ITs_data_control_provider_cleanup},
	{"ITc_data_control_provider_data_control_provider_sql_register_unregister_cb_p",ITc_data_control_provider_data_control_provider_sql_register_unregister_cb_p,ITs_data_control_provider_startup,ITs_data_control_provider_cleanup},
	{"ITc_data_control_provider_data_control_provider_map_register_unregister_cb_p",ITc_data_control_provider_data_control_provider_map_register_unregister_cb_p,ITs_data_control_provider_startup,ITs_data_control_provider_cleanup},
	{"ITc_data_control_provider_data_control_provider_match_data_id_p",ITc_data_control_provider_data_control_provider_match_data_id_p,ITs_data_control_provider_startup,ITs_data_control_provider_cleanup},
	{"ITc_data_control_provider_data_control_provider_match_provider_id_p",ITc_data_control_provider_data_control_provider_match_provider_id_p,ITs_data_control_provider_startup,ITs_data_control_provider_cleanup},
	{"ITc_data_control_provider_add_remove_data_change_consumer_filter_cb_p",ITc_data_control_provider_add_remove_data_change_consumer_filter_cb_p,ITs_data_control_provider_startup,ITs_data_control_provider_cleanup},
	{"ITc_data_control_provider_foreach_data_change_consumer_p",ITc_data_control_provider_foreach_data_change_consumer_p,ITs_data_control_provider_startup,ITs_data_control_provider_cleanup},
	{"ITs_data_control_add_remove_data_change_cb_p",ITs_data_control_add_remove_data_change_cb_p,ITs_data_control_noti_startup,ITs_data_control_noti_cleanup},
	{"ITc_data_control_sql_register_response_cb_p",ITc_data_control_sql_register_response_cb_p,ITs_data_control_noti_startup,ITs_data_control_noti_cleanup},
	{"ITc_data_control_provider_send_data_change_noti_p",ITc_data_control_provider_send_data_change_noti_p,ITs_data_control_noti_startup,ITs_data_control_noti_cleanup},
	{"ITc_data_control_map_bind_unbind_response_cb_p",ITc_data_control_map_bind_unbind_response_cb_p,ITs_data_control_map_bulk_startup,ITs_data_control_map_bulk_cleanup},
	{"ITc_data_control_map_bind_unbind_add_bulk_data_response_cb_p",ITc_data_control_map_bind_unbind_add_bulk_data_response_cb_p,ITs_data_control_map_bulk_startup,ITs_data_control_map_bulk_cleanup},
	{"ITc_data_control_map_get_handle_id_p",ITc_data_control_map_get_handle_id_p,ITs_data_control_map_bulk_startup,ITs_data_control_map_bulk_cleanup},
	{"ITc_data_control_sql_bind_unbind_response_cb_p",ITc_data_control_sql_bind_unbind_response_cb_p,ITs_data_control_sql_bulk_startup,ITs_data_control_sql_bulk_cleanup},
	{"ITc_data_control_sql_bind_unbind_insert_bulk_data_response_cb_p",ITc_data_control_sql_bind_unbind_insert_bulk_data_response_cb_p,ITs_data_control_sql_bulk_startup,ITs_data_control_sql_bulk_cleanup},
	{"ITc_data_control_sql_get_handle_id_p",ITc_data_control_sql_get_handle_id_p,ITs_data_control_sql_bulk_startup,ITs_data_control_sql_bulk_cleanup},
	{NULL, NULL}
};

#endif // __TCT_DATA-CONTROL-NATIVE_H__