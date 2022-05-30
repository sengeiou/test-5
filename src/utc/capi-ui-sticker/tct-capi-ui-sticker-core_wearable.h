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
#ifndef __TCT_CAPI_UI_STICKER_NATIVE_H__
#define __TCT_CAPI_UI_STICKER_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

// Data
extern void utc_capi_ui_sticker_data_startup(void);
extern void utc_capi_ui_sticker_data_cleanup(void);

extern int utc_sticker_data_create_p(void);
extern int utc_sticker_data_create_n(void);

extern int utc_sticker_data_destroy_p(void);
extern int utc_sticker_data_destroy_n(void);

extern int utc_sticker_data_clone_p(void);
extern int utc_sticker_data_clone_n(void);

extern int utc_sticker_data_get_app_id_p(void);
extern int utc_sticker_data_get_app_id_n(void);

extern int utc_sticker_data_set_uri_p(void);
extern int utc_sticker_data_set_uri_n(void);
extern int utc_sticker_data_set_uri_n2(void);

extern int utc_sticker_data_get_uri_p(void);
extern int utc_sticker_data_get_uri_n(void);

extern int utc_sticker_data_foreach_keyword_p(void);
extern int utc_sticker_data_foreach_keyword_n(void);

extern int utc_sticker_data_add_keyword_p(void);
extern int utc_sticker_data_add_keyword_n(void);
extern int utc_sticker_data_add_keyword_n2(void);

extern int utc_sticker_data_remove_keyword_p(void);
extern int utc_sticker_data_remove_keyword_n(void);
extern int utc_sticker_data_remove_keyword_n2(void);

extern int utc_sticker_data_set_group_name_p(void);
extern int utc_sticker_data_set_group_name_n(void);

extern int utc_sticker_data_get_group_name_p(void);
extern int utc_sticker_data_get_group_name_n(void);

extern int utc_sticker_data_set_thumbnail_p(void);
extern int utc_sticker_data_set_thumbnail_n(void);
extern int utc_sticker_data_set_thumbnail_n2(void);

extern int utc_sticker_data_get_thumbnail_p(void);
extern int utc_sticker_data_get_thumbnail_n(void);

extern int utc_sticker_data_set_description_p(void);
extern int utc_sticker_data_set_description_n(void);

extern int utc_sticker_data_get_description_p(void);
extern int utc_sticker_data_get_description_n(void);

extern int utc_sticker_data_get_date_p(void);
extern int utc_sticker_data_get_date_n(void);

extern int utc_sticker_data_set_display_type_p(void);
extern int utc_sticker_data_set_display_type_n(void);

extern int utc_sticker_data_get_display_type_p(void);
extern int utc_sticker_data_get_display_type_n(void);

extern int utc_sticker_data_get_handle_p(void);
extern int utc_sticker_data_get_handle_n(void);
extern int utc_sticker_data_get_handle_n2(void);

// Provider
extern void utc_capi_ui_sticker_provider_startup(void);
extern void utc_capi_ui_sticker_provider_cleanup(void);

extern int utc_sticker_provider_create_p(void);
extern int utc_sticker_provider_create_n(void);

extern int utc_sticker_provider_destroy_p(void);
extern int utc_sticker_provider_destroy_n(void);

extern int utc_sticker_provider_insert_data_p(void);
extern int utc_sticker_provider_insert_data_n(void);

extern int utc_sticker_provider_insert_data_by_json_file_p(void);
extern int utc_sticker_provider_insert_data_by_json_file_n(void);
extern int utc_sticker_provider_insert_data_by_json_file_n2(void);

extern int utc_sticker_provider_update_data_p(void);
extern int utc_sticker_provider_update_data_n(void);

extern int utc_sticker_provider_delete_data_p(void);
extern int utc_sticker_provider_delete_data_n(void);

extern int utc_sticker_provider_get_sticker_count_p(void);
extern int utc_sticker_provider_get_sticker_count_n(void);

extern int utc_sticker_provider_data_foreach_all_p(void);
extern int utc_sticker_provider_data_foreach_all_n(void);

extern int utc_sticker_provider_delete_data_by_uri_p(void);
extern int utc_sticker_provider_delete_data_by_uri_n(void);
extern int utc_sticker_provider_delete_data_by_uri_n2(void);

// Consumer
extern void utc_capi_ui_sticker_consumer_startup(void);
extern void utc_capi_ui_sticker_consumer_cleanup(void);

extern int utc_sticker_consumer_create_p(void);
extern int utc_sticker_consumer_create_n(void);

extern int utc_sticker_consumer_destroy_p(void);
extern int utc_sticker_consumer_destroy_n(void);

extern int utc_sticker_consumer_data_foreach_all_p(void);
extern int utc_sticker_consumer_data_foreach_all_n(void);

extern int utc_sticker_consumer_data_foreach_by_keyword_p(void);
extern int utc_sticker_consumer_data_foreach_by_keyword_n(void);

extern int utc_sticker_consumer_data_foreach_by_group_p(void);
extern int utc_sticker_consumer_data_foreach_by_group_n(void);

extern int utc_sticker_consumer_data_foreach_by_type_p(void);
extern int utc_sticker_consumer_data_foreach_by_type_n(void);

extern int utc_sticker_consumer_group_list_foreach_all_p(void);
extern int utc_sticker_consumer_group_list_foreach_all_n(void);

extern int utc_sticker_consumer_keyword_list_foreach_all_p(void);
extern int utc_sticker_consumer_keyword_list_foreach_all_n(void);

extern int utc_sticker_consumer_data_foreach_by_display_type_p(void);
extern int utc_sticker_consumer_data_foreach_by_display_type_n(void);

extern int utc_sticker_consumer_group_list_foreach_by_display_type_p(void);
extern int utc_sticker_consumer_group_list_foreach_by_display_type_n(void);

extern int utc_sticker_consumer_add_recent_data_p(void);
extern int utc_sticker_consumer_add_recent_data_n(void);

extern int utc_sticker_consumer_get_recent_data_list_p(void);
extern int utc_sticker_consumer_get_recent_data_list_n(void);

extern int utc_sticker_consumer_set_event_cb_p(void);
extern int utc_sticker_consumer_set_event_cb_n(void);

extern int utc_sticker_consumer_unset_event_cb_p(void);
extern int utc_sticker_consumer_unset_event_cb_n(void);

testcase tc_array[] = {
    {"utc_sticker_data_create_p", utc_sticker_data_create_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_create_n", utc_sticker_data_create_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_destroy_p", utc_sticker_data_destroy_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_destroy_n", utc_sticker_data_destroy_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_clone_p", utc_sticker_data_clone_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_clone_n", utc_sticker_data_clone_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_app_id_p", utc_sticker_data_get_app_id_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_app_id_n", utc_sticker_data_get_app_id_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_uri_p", utc_sticker_data_set_uri_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_uri_n", utc_sticker_data_set_uri_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_uri_n2", utc_sticker_data_set_uri_n2, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_uri_p", utc_sticker_data_get_uri_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_uri_n", utc_sticker_data_get_uri_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_foreach_keyword_p", utc_sticker_data_foreach_keyword_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_foreach_keyword_n", utc_sticker_data_foreach_keyword_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_add_keyword_p", utc_sticker_data_add_keyword_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_add_keyword_n", utc_sticker_data_add_keyword_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_add_keyword_n2", utc_sticker_data_add_keyword_n2, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_remove_keyword_p", utc_sticker_data_remove_keyword_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_remove_keyword_n", utc_sticker_data_remove_keyword_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_remove_keyword_n2", utc_sticker_data_remove_keyword_n2, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_group_name_p", utc_sticker_data_set_group_name_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_group_name_n", utc_sticker_data_set_group_name_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_group_name_p", utc_sticker_data_get_group_name_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_group_name_n", utc_sticker_data_get_group_name_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_thumbnail_p", utc_sticker_data_set_thumbnail_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_thumbnail_n", utc_sticker_data_set_thumbnail_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_thumbnail_n2", utc_sticker_data_set_thumbnail_n2, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_thumbnail_p", utc_sticker_data_get_thumbnail_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_thumbnail_n", utc_sticker_data_get_thumbnail_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_description_p", utc_sticker_data_set_description_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_description_n", utc_sticker_data_set_description_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_description_p", utc_sticker_data_get_description_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_description_n", utc_sticker_data_get_description_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_date_p", utc_sticker_data_get_date_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_date_n", utc_sticker_data_get_date_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_display_type_p", utc_sticker_data_set_display_type_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_set_display_type_n", utc_sticker_data_set_display_type_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_display_type_p", utc_sticker_data_get_display_type_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_display_type_n", utc_sticker_data_get_display_type_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_handle_p", utc_sticker_data_get_handle_p, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_handle_n", utc_sticker_data_get_handle_n, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_data_get_handle_n2", utc_sticker_data_get_handle_n2, utc_capi_ui_sticker_data_startup, utc_capi_ui_sticker_data_cleanup},
    {"utc_sticker_provider_create_p", utc_sticker_provider_create_p, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_create_n", utc_sticker_provider_create_n, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_destroy_p", utc_sticker_provider_destroy_p, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_destroy_n", utc_sticker_provider_destroy_n, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_insert_data_p", utc_sticker_provider_insert_data_p, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_insert_data_n", utc_sticker_provider_insert_data_n, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_insert_data_by_json_file_p", utc_sticker_provider_insert_data_by_json_file_p, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_insert_data_by_json_file_n", utc_sticker_provider_insert_data_by_json_file_n, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_insert_data_by_json_file_n2", utc_sticker_provider_insert_data_by_json_file_n2, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_update_data_p", utc_sticker_provider_update_data_p, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_update_data_n", utc_sticker_provider_update_data_n, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_delete_data_p", utc_sticker_provider_delete_data_p, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_delete_data_n", utc_sticker_provider_delete_data_n, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_get_sticker_count_p", utc_sticker_provider_get_sticker_count_p, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_get_sticker_count_n", utc_sticker_provider_get_sticker_count_n, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_data_foreach_all_p", utc_sticker_provider_data_foreach_all_p, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_data_foreach_all_n", utc_sticker_provider_data_foreach_all_n, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_delete_data_by_uri_p", utc_sticker_provider_delete_data_by_uri_p, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_delete_data_by_uri_n", utc_sticker_provider_delete_data_by_uri_n, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_provider_delete_data_by_uri_n2", utc_sticker_provider_delete_data_by_uri_n2, utc_capi_ui_sticker_provider_startup, utc_capi_ui_sticker_provider_cleanup},
    {"utc_sticker_consumer_create_p", utc_sticker_consumer_create_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_create_n", utc_sticker_consumer_create_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_destroy_p", utc_sticker_consumer_destroy_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_destroy_n", utc_sticker_consumer_destroy_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_data_foreach_all_p", utc_sticker_consumer_data_foreach_all_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_data_foreach_all_n", utc_sticker_consumer_data_foreach_all_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_data_foreach_by_keyword_p", utc_sticker_consumer_data_foreach_by_keyword_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_data_foreach_by_keyword_n", utc_sticker_consumer_data_foreach_by_keyword_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_data_foreach_by_group_p", utc_sticker_consumer_data_foreach_by_group_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_data_foreach_by_group_n", utc_sticker_consumer_data_foreach_by_group_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_data_foreach_by_type_p", utc_sticker_consumer_data_foreach_by_type_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_data_foreach_by_type_n", utc_sticker_consumer_data_foreach_by_type_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_group_list_foreach_all_p", utc_sticker_consumer_group_list_foreach_all_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_group_list_foreach_all_n", utc_sticker_consumer_group_list_foreach_all_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_keyword_list_foreach_all_p", utc_sticker_consumer_keyword_list_foreach_all_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_keyword_list_foreach_all_n", utc_sticker_consumer_keyword_list_foreach_all_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_data_foreach_by_display_type_p", utc_sticker_consumer_data_foreach_by_display_type_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_data_foreach_by_display_type_n", utc_sticker_consumer_data_foreach_by_display_type_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_group_list_foreach_by_display_type_p", utc_sticker_consumer_group_list_foreach_by_display_type_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_group_list_foreach_by_display_type_n", utc_sticker_consumer_group_list_foreach_by_display_type_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_add_recent_data_p", utc_sticker_consumer_add_recent_data_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_add_recent_data_n", utc_sticker_consumer_add_recent_data_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_get_recent_data_list_p", utc_sticker_consumer_get_recent_data_list_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_get_recent_data_list_n", utc_sticker_consumer_get_recent_data_list_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_set_event_cb_p", utc_sticker_consumer_set_event_cb_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_set_event_cb_n", utc_sticker_consumer_set_event_cb_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_unset_event_cb_p", utc_sticker_consumer_unset_event_cb_p, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {"utc_sticker_consumer_unset_event_cb_n", utc_sticker_consumer_unset_event_cb_n, utc_capi_ui_sticker_consumer_startup, utc_capi_ui_sticker_consumer_cleanup},
    {NULL, NULL}
};

#endif // __TCT_CAPI_UI_STICKER_NATIVE_H__