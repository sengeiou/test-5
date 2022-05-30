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
#ifndef __UTC_CONTACTS_SERVICE_TC_UTILS_H__
#define __UTC_CONTACTS_SERVICE_TC_UTILS_H__

#include <contacts.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CTSVC_TC_UTIL_ACCOUNT_USER_NAME "utc-test"
#define CTSVC_TC_UTIL_ACCOUNT_PACKAGE_NAME "com.samsung.app-test"

char* ctsvc_tc_util_get_file_path(const char *file);
#define CTSVC_FILE_IMAGE_C1 "test1.jpg"
#define CTSVC_FILE_IMAGE_C2 "test2.jpg"
#define CTSVC_FILE_IMAGE_U1 "test3.jpg"
#define CTSVC_FILE_IMAGE_U2 "test4.jpg"
#define CTSVC_FILE_VIBRATION_C1 "test1.mp3"
#define CTSVC_FILE_VIBRATION_C2 "test2.mp3"
#define CTSVC_FILE_VIBRATION_U1 "test3.mp3"
#define CTSVC_FILE_VIBRATION_U2 "test4.mp3"
#define CTSVC_FILE_MUSIC_C1 "test1.mp3"
#define CTSVC_FILE_MUSIC_C2 "test2.mp3"
#define CTSVC_FILE_MUSIC_U1 "test3.mp3"
#define CTSVC_FILE_MUSIC_U2 "test4.mp3"
#define CTSVC_FILE_VCARD "test.vcf"

#define CTSVC_VCARD_PATH ctsvc_tc_util_get_file_path(CTSVC_FILE_VCARD)
#define CTSVC_IMAGE_PATH_C1 ctsvc_tc_util_get_file_path(CTSVC_FILE_IMAGE_C1)
#define CTSVC_IMAGE_PATH_C2 ctsvc_tc_util_get_file_path(CTSVC_FILE_IMAGE_C2)
#define CTSVC_IMAGE_PATH_U1 ctsvc_tc_util_get_file_path(CTSVC_FILE_IMAGE_U1)
#define CTSVC_IMAGE_PATH_U2 ctsvc_tc_util_get_file_path(CTSVC_FILE_IMAGE_U2)
#define CTSVC_MUSIC_PATH_C1 ctsvc_tc_util_get_file_path(CTSVC_FILE_MUSIC_C1)
#define CTSVC_MUSIC_PATH_C2 ctsvc_tc_util_get_file_path(CTSVC_FILE_MUSIC_C2)
#define CTSVC_MUSIC_PATH_U1 ctsvc_tc_util_get_file_path(CTSVC_FILE_MUSIC_U1)
#define CTSVC_MUSIC_PATH_U2 ctsvc_tc_util_get_file_path(CTSVC_FILE_MUSIC_U2)
#define CTSVC_VIBRATION_C1 ctsvc_tc_util_get_file_path(CTSVC_FILE_VIBRATION_C1)
#define CTSVC_VIBRATION_C2 ctsvc_tc_util_get_file_path(CTSVC_FILE_VIBRATION_C2)
#define CTSVC_VIBRATION_U1 ctsvc_tc_util_get_file_path(CTSVC_FILE_VIBRATION_U1)
#define CTSVC_VIBRATION_U2 ctsvc_tc_util_get_file_path(CTSVC_FILE_VIBRATION_U2)

#define CTSVC_RINGTONE_PATH_C1 CTSVC_MUSIC_PATH_C1
#define CTSVC_RINGTONE_PATH_U1 CTSVC_MUSIC_PATH_U1
#define CTSVC_RINGTONE_PATH_C2 CTSVC_MUSIC_PATH_C2
#define CTSVC_RINGTONE_PATH_U2 CTSVC_MUSIC_PATH_U2
#define CTSVC_MESSAGE_ALERT_C1 CTSVC_MUSIC_PATH_C1
#define CTSVC_MESSAGE_ALERT_U1 CTSVC_MUSIC_PATH_U1
#define CTSVC_MESSAGE_ALERT_C2 CTSVC_MUSIC_PATH_C2
#define CTSVC_MESSAGE_ALERT_U2 CTSVC_MUSIC_PATH_U2

#define INVALID_COUNT 0
#define INVALID_ENUM -1
#define INVALID_DB_ID -1
#define LOCAL_DB_ID 0
#define INVALID_PROPERTY_ID 0
#define INVALID_CONNECT_FLAG 0x10
#define OFFSET_DEFAULT 0
#define LIMIT_DEFAULT 0
#define STRING_EQUAL 0

typedef int (*tc)(void);
typedef int (*tc_with_account_id)(int account_id);

typedef struct {
	tc add_bool;
	tc add_double;
	tc add_int;
	tc add_lli;
	tc add_str;
} ctsvc_tc_filter_plugin_s;


typedef struct {
	tc clone;
	tc create;
	tc destroy;
	tc get_uri_p;
	tc add_child_record;
	tc clone_child_record_list;
	tc remove_child_record;
	tc get_child_record_at_p;
	tc get_child_record_count;
	tc get_bool;
	tc get_double;
	tc get_int;
	tc get_lli;
	tc get_str;
	tc get_str_p;
	tc set_bool;
	tc set_double;
	tc set_int;
	tc set_lli;
	tc set_str;
	tc free_properties;
} ctsvc_tc_record_plugin_s;

typedef struct {
	tc db_add_changed_cb;
	tc db_remove_changed_cb;
	tc_with_account_id db_get_record;
	tc_with_account_id db_get_records_with_query;
	tc_with_account_id db_get_all_records;
	tc_with_account_id db_get_changes_by_version;
	tc_with_account_id db_get_count;
	tc_with_account_id db_get_count_with_query;
	tc_with_account_id db_insert_record;
	tc_with_account_id db_insert_records;
	tc_with_account_id db_update_record;
	tc_with_account_id db_update_records;
	tc_with_account_id db_delete_record;
	tc_with_account_id db_delete_records;
	tc_with_account_id db_replace_record;
	tc_with_account_id db_replace_records;
	tc_with_account_id db_search_records;
	tc_with_account_id db_search_records_with_query;
	tc_with_account_id db_search_records_with_range;
	tc_with_account_id db_search_records_for_snippet;
	tc_with_account_id db_search_records_with_query_for_snippet;
	tc_with_account_id db_search_records_with_range_for_snippet;
	tc_with_account_id db_get_count_for_search_records;
	tc_with_account_id db_get_count_for_search_records_with_query;
	tc_with_account_id db_get_count_for_search_records_with_range;
} ctsvc_tc_db_plugin_s;

typedef enum {
	PROPERTY_TYPE_CREATE1,
	PROPERTY_TYPE_CREATE2,
	PROPERTY_TYPE_CREATE3,
	PROPERTY_TYPE_CREATE4,
	PROPERTY_TYPE_CREATE5,
	PROPERTY_TYPE_UPDATE1,
	PROPERTY_TYPE_UPDATE2,
} ctsvc_property_type_e;

typedef enum {
	VIEW_ADDRESSBOOK=0,
	VIEW_GROUP=1,
	VIEW_PERSON=2,
	VIEW_SIMPLE_CONTACT=3,
	VIEW_CONTACT=4,
	VIEW_MY_PROFILE=5,
	VIEW_NAME=6,
	VIEW_NUMBER=7,
	VIEW_EMAIL=8,
	VIEW_ADDRESS=9,
	VIEW_NOTE=10,
	VIEW_URL=11,
	VIEW_EVENT=12,
	VIEW_GROUP_RELATION=13,
	VIEW_RELATIONSHIP=14,
	VIEW_IMAGE=15,
	VIEW_COMPANY=16,
	VIEW_NICKNAME=17,
	VIEW_MESSENGER=18,
	VIEW_EXTENSION=19,
	VIEW_SDN=20,
	VIEW_PROFILE=21,
	VIEW_ACTIVITY_PHOTO=22,
	VIEW_ACTIVITY=23,
	VIEW_SPEEDDIAL=24,
	VIEW_PHONE_LOG=25,
	VIEW_CONTACT_UPDATED_INFO=26,
	VIEW_MY_PROFILE_UPDATED_INFO=27,
	VIEW_GROUP_UPDATED_INFO=28,
	VIEW_GROUP_MEMBER_UPDATED_INFO=29,
	VIEW_GROUPREL_UPDATED_INFO=30,
	VIEW_PHONE_LOG_STAT=31,
	VIEW_SIP =32,
	VIEW_MAX,
} ctsvc_view_e;

typedef enum {
	PROPERTY_BOOL,
	PROPERTY_INT,
	PROPERTY_DOUBLE,
	PROPERTY_LLI,
	PROPERTY_STR,
} ctsvc_data_type_e;

typedef union {
	bool bool_val;
	int int_val;
	double double_val;
	char *str_val;
	long long int lli_val;
} ctsvc_data_value;

typedef struct {
	unsigned int property_id;
	ctsvc_data_type_e type;
	ctsvc_data_value val;
} ctsvc_property_s;

typedef struct {
	int create1_count;
	ctsvc_property_s *create1;
	int create2_count;
	ctsvc_property_s *create2;
	int create3_count;
	ctsvc_property_s *create3;
	int create4_count;
	ctsvc_property_s *create4;
	int create5_count;
	ctsvc_property_s *create5;
	int update1_count;
	ctsvc_property_s *update1;
	int update2_count;
	ctsvc_property_s *update2;
} ctsvc_view_s;

void ctsvc_tc_util_db_changed_cb(const char *view_uri, void *user_data);
void ctsvc_tc_util_setting_name_display_order_chagned_cb(contacts_name_display_order_e name_display_order, void* user_data);
void ctsvc_tc_util_setting_name_sorting_order_chagned_cb(contacts_name_sorting_order_e name_display_order, void* user_data);


int ctsvc_tc_util_account_insert(int *id);
int ctsvc_tc_util_account_delete();


int ctsvc_tc_util_record_compare_type(contacts_record_h record, ctsvc_data_type_e type, ctsvc_property_s *properties, int property_count);
int ctsvc_tc_util_record_compare(contacts_record_h record, ctsvc_property_s *properties, int property_count);
int ctsvc_tc_util_filter_set(contacts_filter_h filter, ctsvc_property_s *property_list, int property_count);
int ctsvc_tc_util_record_set_property(contacts_record_h record, ctsvc_property_s *property_list, int property_count);
int ctsvc_tc_util_filter_add_type(contacts_filter_h filter, ctsvc_data_type_e type, ctsvc_property_s *properties, int property_count);

ctsvc_property_s ctsvc_tc_util_create_bool_property(unsigned int property_id, bool value);
ctsvc_property_s ctsvc_tc_util_create_int_property(unsigned int property_id, int  value);
ctsvc_property_s ctsvc_tc_util_create_double_property(unsigned int property_id, double value);
ctsvc_property_s ctsvc_tc_util_create_str_property(unsigned int property_id, char *value);
ctsvc_property_s ctsvc_tc_util_create_lli_property(unsigned int property_id, long long int value);

int ctsvc_tc_util_print_property(ctsvc_property_s *property_list, int property_count);
const char *ctsvc_tc_util_get_view_uri(ctsvc_view_e view);
bool ctsvc_tc_util_is_sim_support();
bool ctsvc_tc_util_is_contact_support();

#endif // __UTC_CONTACTS_SERVICE_TC_UTILS_H__
