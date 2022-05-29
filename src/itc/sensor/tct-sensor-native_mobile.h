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

#ifndef __TCT_SENSOR-NATIVE_H__
#define __TCT_SENSOR-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_sensor_listener_startup(void);
extern void ITs_sensor_listener_cleanup(void);
extern void ITs_sensor_util_startup(void);
extern void ITs_sensor_util_cleanup(void);
extern void ITs_sensor_recorder_startup(void);
extern void ITs_sensor_recorder_cleanup(void);
extern void ITs_sensor_provider_startup(void);
extern void ITs_sensor_provider_cleanup(void);

extern int ITc_sensor_is_supported_p(void);
extern int ITc_sensor_get_default_sensor_p(void);
extern int ITc_sensor_get_fifo_count_p(void);
extern int ITc_sensor_get_max_batch_count_p(void);
extern int ITc_sensor_get_max_range_p(void);
extern int ITc_sensor_get_min_range_p(void);
extern int ITc_sensor_get_min_interval_p(void);
extern int ITc_sensor_get_name_p(void);
extern int ITc_sensor_get_resolution_p(void);
extern int ITc_sensor_get_sensor_list_p(void);
extern int ITc_sensor_get_type_p(void);
extern int ITc_sensor_get_vendor_p(void);
extern int ITc_sensor_create_destroy_listener_p(void);
extern int ITc_sensor_listener_set_interval_p(void);
extern int ITc_sensor_listener_set_option_p(void);
extern int ITc_sensor_listener_start_stop_p(void);
extern int ITc_sensor_listener_read_data_list_p(void);
extern int ITc_sensor_listener_flush_p(void);
extern int ITc_sensor_listener_set_unset_events_cb_p(void);
extern int ITc_sensor_is_wake_up_p(void);
extern int ITc_sensor_listener_set_attribute_int_p(void);
extern int ITc_sensor_util_get_angle_change_p(void);
extern int ITc_sensor_util_get_declination_p(void);
extern int ITc_sensor_util_get_orientation_p(void);
extern int ITc_sensor_util_get_rotation_matrix_p(void);
extern int ITc_sensor_util_get_rotation_matrix_from_vector_p(void);
extern int ITc_sensor_util_get_altitude_p(void);
extern int ITc_sensor_util_remap_coordinate_system_p(void);
extern int ITc_sensor_util_get_inclination_p(void);
extern int ITc_sensor_recorder_is_supported_p(void);
extern int ITc_sensor_recorder_start_stop_p(void);
extern int ITc_sensor_recorder_create_destroy_option_p(void);
extern int ITc_sensor_recorder_option_set_int_p(void);
extern int ITc_sensor_recorder_create_destroy_query_p(void);
extern int ITc_sensor_recorder_query_set_int_p(void);
extern int ITc_sensor_recorder_query_set_time_p(void);
extern int ITc_sensor_recorder_read_p(void);
extern int ITc_sensor_recorder_read_sync_p(void);
extern int ITc_sensor_recorder_data_get_time_p(void);
extern int ITc_sensor_recorder_data_get_int_p(void);
extern int ITc_sensor_recorder_data_get_double_p(void);
extern int ITc_sensor_sensor_is_supported_by_uri_p(void);
extern int ITc_sensor_get_default_sensor_by_uri_p(void);
extern int ITc_sensor_get_sensor_list_by_uri_p(void);
extern int ITc_sensor_get_uri_p(void);
extern int ITc_sensor_create_destroy_provider_p(void);
extern int ITc_sensor_add_remove_provider_p(void);
extern int ITc_sensor_provider_set_name_p(void);
extern int ITc_sensor_provider_set_vendor_p(void);
extern int ITc_sensor_provider_set_range_p(void);
extern int ITc_sensor_provider_set_resolution_p(void);
extern int ITc_sensor_add_remove_sensor_added_cb_p(void);
extern int ITc_sensor_add_remove_sensor_removed_cb_p(void);
extern int ITc_sensor_provider_set_start_cb_p(void);
extern int ITc_sensor_provider_set_stop_cb_p(void);
extern int ITc_sensor_provider_set_interval_changed_cb_p(void);
extern int ITc_sensor_provider_publish_events_p(void);
extern int ITc_sensor_listener_set_unset_events_cb_led_green_batch_p(void);

testcase tc_array[] = {
	{"ITc_sensor_is_supported_p",ITc_sensor_is_supported_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_default_sensor_p",ITc_sensor_get_default_sensor_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_fifo_count_p",ITc_sensor_get_fifo_count_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_max_batch_count_p",ITc_sensor_get_max_batch_count_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_max_range_p",ITc_sensor_get_max_range_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_min_range_p",ITc_sensor_get_min_range_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_min_interval_p",ITc_sensor_get_min_interval_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_name_p",ITc_sensor_get_name_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_resolution_p",ITc_sensor_get_resolution_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_sensor_list_p",ITc_sensor_get_sensor_list_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_type_p",ITc_sensor_get_type_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_vendor_p",ITc_sensor_get_vendor_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_create_destroy_listener_p",ITc_sensor_create_destroy_listener_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_listener_set_interval_p",ITc_sensor_listener_set_interval_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_listener_set_option_p",ITc_sensor_listener_set_option_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_listener_start_stop_p",ITc_sensor_listener_start_stop_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_listener_read_data_list_p",ITc_sensor_listener_read_data_list_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_listener_flush_p",ITc_sensor_listener_flush_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_listener_set_unset_events_cb_p",ITc_sensor_listener_set_unset_events_cb_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_is_wake_up_p",ITc_sensor_is_wake_up_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_listener_set_attribute_int_p",ITc_sensor_listener_set_attribute_int_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_util_get_angle_change_p",ITc_sensor_util_get_angle_change_p,ITs_sensor_util_startup,ITs_sensor_util_cleanup},
	{"ITc_sensor_util_get_declination_p",ITc_sensor_util_get_declination_p,ITs_sensor_util_startup,ITs_sensor_util_cleanup},
	{"ITc_sensor_util_get_orientation_p",ITc_sensor_util_get_orientation_p,ITs_sensor_util_startup,ITs_sensor_util_cleanup},
	{"ITc_sensor_util_get_rotation_matrix_p",ITc_sensor_util_get_rotation_matrix_p,ITs_sensor_util_startup,ITs_sensor_util_cleanup},
	{"ITc_sensor_util_get_rotation_matrix_from_vector_p",ITc_sensor_util_get_rotation_matrix_from_vector_p,ITs_sensor_util_startup,ITs_sensor_util_cleanup},
	{"ITc_sensor_util_get_altitude_p", ITc_sensor_util_get_altitude_p,ITs_sensor_util_startup,ITs_sensor_util_cleanup},
	{"ITc_sensor_util_remap_coordinate_system_p",ITc_sensor_util_remap_coordinate_system_p,ITs_sensor_util_startup,ITs_sensor_util_cleanup},
	{"ITc_sensor_util_get_inclination_p",ITc_sensor_util_get_inclination_p,ITs_sensor_util_startup,ITs_sensor_util_cleanup},
	{"ITc_sensor_recorder_is_supported_p",ITc_sensor_recorder_is_supported_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_start_stop_p",ITc_sensor_recorder_start_stop_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_create_destroy_option_p",ITc_sensor_recorder_create_destroy_option_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_option_set_int_p",ITc_sensor_recorder_option_set_int_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_create_destroy_query_p",ITc_sensor_recorder_create_destroy_query_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_query_set_int_p",ITc_sensor_recorder_query_set_int_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_query_set_time_p",ITc_sensor_recorder_query_set_time_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_read_p",ITc_sensor_recorder_read_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_read_sync_p",ITc_sensor_recorder_read_sync_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_data_get_time_p",ITc_sensor_recorder_data_get_time_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_data_get_int_p",ITc_sensor_recorder_data_get_int_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},
	{"ITc_sensor_recorder_data_get_double_p",ITc_sensor_recorder_data_get_double_p,ITs_sensor_recorder_startup,ITs_sensor_recorder_cleanup},	
	{"ITc_sensor_sensor_is_supported_by_uri_p",ITc_sensor_sensor_is_supported_by_uri_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_default_sensor_by_uri_p",ITc_sensor_get_default_sensor_by_uri_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_sensor_list_by_uri_p",ITc_sensor_get_sensor_list_by_uri_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_get_uri_p",ITc_sensor_get_uri_p,ITs_sensor_listener_startup,ITs_sensor_listener_cleanup},
	{"ITc_sensor_create_destroy_provider_p",ITc_sensor_create_destroy_provider_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_add_remove_provider_p",ITc_sensor_add_remove_provider_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_provider_set_name_p",ITc_sensor_provider_set_name_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_provider_set_vendor_p",ITc_sensor_provider_set_vendor_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_provider_set_range_p",ITc_sensor_provider_set_range_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_provider_set_resolution_p",ITc_sensor_provider_set_resolution_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_add_remove_sensor_added_cb_p",ITc_sensor_add_remove_sensor_added_cb_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_add_remove_sensor_removed_cb_p",ITc_sensor_add_remove_sensor_removed_cb_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_provider_set_start_cb_p",ITc_sensor_provider_set_start_cb_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},	
	{"ITc_sensor_provider_set_stop_cb_p",ITc_sensor_provider_set_stop_cb_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_provider_set_interval_changed_cb_p",ITc_sensor_provider_set_interval_changed_cb_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_provider_publish_events_p",ITc_sensor_provider_publish_events_p,ITs_sensor_provider_startup,ITs_sensor_provider_cleanup},
	{"ITc_sensor_listener_set_unset_events_cb_led_green_batch_p",ITc_sensor_listener_set_unset_events_cb_led_green_batch_p,ITs_sensor_listener_startup, ITs_sensor_listener_cleanup},
	{NULL, NULL}
};

#endif // __TCT_SENSOR-NATIVE_H__
