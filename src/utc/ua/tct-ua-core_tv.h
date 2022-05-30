/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __TCT_UA_NATIVE_H__
#define __TCT_UA_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_ua_startup(void);
extern void utc_ua_cleanup(void);

/* User Awareness Common APIs */
extern int utc_ua_foreach_service_p(void);
extern int utc_ua_foreach_service_n(void);
extern int utc_ua_get_default_service_p(void);
extern int utc_ua_get_default_service_n(void);
extern int utc_ua_get_service_by_name_p(void);
extern int utc_ua_get_service_by_name_n(void);

/* User Awareness Monitor APIs */
extern int utc_ua_monitor_create_p(void);
extern int utc_ua_monitor_create_n(void);
extern int utc_ua_monitor_destroy_p(void);
extern int utc_ua_monitor_destroy_n(void);
extern int utc_ua_monitor_add_sensor_p(void);
extern int utc_ua_monitor_add_sensor_n(void);
extern int utc_ua_monitor_remove_sensor_p(void);
extern int utc_ua_monitor_remove_sensor_n(void);
extern int utc_ua_monitor_foreach_sensor_p(void);
extern int utc_ua_monitor_foreach_sensor_n(void);
extern int utc_ua_monitor_is_sensor_available_p(void);
extern int utc_ua_monitor_is_sensor_available_n(void);
extern int utc_ua_monitor_set_sensor_status_changed_cb_p(void);
extern int utc_ua_monitor_set_sensor_status_changed_cb_n(void);
extern int utc_ua_monitor_unset_sensor_status_changed_cb_p(void);
extern int utc_ua_monitor_unset_sensor_status_changed_cb_n(void);
extern int utc_ua_monitor_start_scan_n(void);
extern int utc_ua_monitor_stop_scan_n(void);
extern int utc_ua_monitor_start_presence_detection_p(void);
extern int utc_ua_monitor_start_presence_detection_n(void);
extern int utc_ua_monitor_stop_presence_detection_p(void);
extern int utc_ua_monitor_stop_presence_detection_n(void);
extern int utc_ua_monitor_start_absence_detection_p(void);
extern int utc_ua_monitor_start_absence_detection_n(void);
extern int utc_ua_monitor_stop_absence_detection_p(void);
extern int utc_ua_monitor_stop_absence_detection_n(void);

/* User Awareness User APIs */
extern int utc_ua_user_create_p(void);
extern int utc_ua_user_create_n(void);
extern int utc_ua_user_destroy_p(void);
extern int utc_ua_user_destroy_n(void);
extern int utc_ua_user_add_p(void);
extern int utc_ua_user_add_n(void);
extern int utc_ua_user_remove_p(void);
extern int utc_ua_user_remove_n(void);
extern int utc_ua_user_get_account_p(void);
extern int utc_ua_user_get_account_n(void);
extern int utc_ua_user_add_device_n(void);
extern int utc_ua_user_remove_device_n(void);
extern int utc_ua_user_foreach_devices_n(void);

/* User Awareness Service APIs */
extern int utc_ua_service_create_p(void);
extern int utc_ua_service_create_n(void);
extern int utc_ua_service_destroy_p(void);
extern int utc_ua_service_destroy_n(void);
extern int utc_ua_service_add_p(void);
extern int utc_ua_service_add_n(void);
extern int utc_ua_service_update_p(void);
extern int utc_ua_service_update_n(void);
extern int utc_ua_service_remove_p(void);
extern int utc_ua_service_remove_n(void);
extern int utc_ua_service_get_name_p(void);
extern int utc_ua_service_get_name_n(void);
extern int utc_ua_service_set_detection_threshold_p(void);
extern int utc_ua_service_set_detection_threshold_n(void);
extern int utc_ua_service_get_detection_threshold_p(void);
extern int utc_ua_service_get_detection_threshold_n(void);
extern int utc_ua_service_get_user_by_account_p(void);
extern int utc_ua_service_get_user_by_account_n(void);
extern int utc_ua_service_add_user_p(void);
extern int utc_ua_service_add_user_n(void);
extern int utc_ua_service_remove_user_p(void);
extern int utc_ua_service_remove_user_n(void);
extern int utc_ua_service_foreach_users_p(void);
extern int utc_ua_service_foreach_users_n(void);

/* User Awareness Device APIs */
extern int utc_ua_device_create_p(void);
extern int utc_ua_device_create_n(void);
extern int utc_ua_device_destroy_p(void);
extern int utc_ua_device_destroy_n(void);
extern int utc_ua_device_get_mac_type_p(void);
extern int utc_ua_device_get_mac_type_n(void);
extern int utc_ua_device_set_os_info_p(void);
extern int utc_ua_device_set_os_info_n(void);
extern int utc_ua_device_get_os_info_p(void);
extern int utc_ua_device_get_os_info_n(void);
extern int utc_ua_device_get_mac_address_p(void);
extern int utc_ua_device_get_mac_address_n(void);
extern int utc_ua_device_get_device_id_p(void);
extern int utc_ua_device_get_device_id_n(void);
extern int utc_ua_device_set_wifi_bssid_p(void);
extern int utc_ua_device_set_wifi_bssid_n(void);
extern int utc_ua_device_get_wifi_bssid_p(void);
extern int utc_ua_device_get_wifi_bssid_n(void);
extern int utc_ua_device_set_wifi_ipv4_address_p(void);
extern int utc_ua_device_set_wifi_ipv4_address_n(void);
extern int utc_ua_device_get_wifi_ipv4_address_p(void);
extern int utc_ua_device_get_wifi_ipv4_address_n(void);
extern int utc_ua_device_get_last_presence_p(void);
extern int utc_ua_device_get_last_presence_n(void);
extern int utc_ua_device_get_pairing_required_p(void);
extern int utc_ua_device_get_pairing_required_n(void);
extern int utc_ua_device_update_n(void);
extern int utc_ua_device_get_by_mac_address_p(void);
extern int utc_ua_device_get_by_mac_address_n(void);
extern int utc_ua_device_get_by_device_id_p(void);
extern int utc_ua_device_get_by_device_id_n(void);

/* User Awareness Sensor APIs */
extern int utc_ua_sensor_get_status_n(void);
extern int utc_ua_sensor_get_timestamp_n(void);
extern int utc_ua_sensor_get_type_n(void);

/* User Awareness Location APIs */
extern int utc_ua_monitor_set_location_period_p(void);
extern int utc_ua_monitor_set_location_period_n(void);
extern int utc_ua_location_get_distance_n(void);
extern int utc_ua_location_get_position_n(void);
extern int utc_ua_monitor_start_location_detection_n(void);
extern int utc_ua_monitor_stop_location_detection_n(void);

testcase tc_array[] = {
	/* User Awareness Common APIs */
	{"utc_ua_foreach_service_p", utc_ua_foreach_service_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_foreach_service_n", utc_ua_foreach_service_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_get_default_service_p", utc_ua_get_default_service_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_get_default_service_n", utc_ua_get_default_service_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_get_service_by_name_p", utc_ua_get_service_by_name_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_get_service_by_name_n", utc_ua_get_service_by_name_n, utc_ua_startup, utc_ua_cleanup},
	/* User Awareness Monitor APIs */
	{"utc_ua_monitor_create_p", utc_ua_monitor_create_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_create_n", utc_ua_monitor_create_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_destroy_p", utc_ua_monitor_destroy_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_destroy_n", utc_ua_monitor_destroy_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_add_sensor_p", utc_ua_monitor_add_sensor_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_add_sensor_n", utc_ua_monitor_add_sensor_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_remove_sensor_p", utc_ua_monitor_remove_sensor_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_remove_sensor_n", utc_ua_monitor_remove_sensor_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_foreach_sensor_p", utc_ua_monitor_foreach_sensor_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_foreach_sensor_n", utc_ua_monitor_foreach_sensor_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_is_sensor_available_p", utc_ua_monitor_is_sensor_available_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_is_sensor_available_n", utc_ua_monitor_is_sensor_available_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_set_sensor_status_changed_cb_p", utc_ua_monitor_set_sensor_status_changed_cb_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_set_sensor_status_changed_cb_n", utc_ua_monitor_set_sensor_status_changed_cb_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_unset_sensor_status_changed_cb_p", utc_ua_monitor_unset_sensor_status_changed_cb_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_unset_sensor_status_changed_cb_n", utc_ua_monitor_unset_sensor_status_changed_cb_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_start_scan_n", utc_ua_monitor_start_scan_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_stop_scan_n", utc_ua_monitor_stop_scan_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_start_presence_detection_p", utc_ua_monitor_start_presence_detection_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_start_presence_detection_n", utc_ua_monitor_start_presence_detection_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_stop_presence_detection_p", utc_ua_monitor_stop_presence_detection_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_stop_presence_detection_n", utc_ua_monitor_stop_presence_detection_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_start_absence_detection_p", utc_ua_monitor_start_absence_detection_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_start_absence_detection_n", utc_ua_monitor_start_absence_detection_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_stop_absence_detection_p", utc_ua_monitor_stop_absence_detection_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_stop_absence_detection_n", utc_ua_monitor_stop_absence_detection_n, utc_ua_startup, utc_ua_cleanup},
	/* User Awareness User APIs */
	{"utc_ua_user_create_p", utc_ua_user_create_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_create_n", utc_ua_user_create_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_destroy_p", utc_ua_user_destroy_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_destroy_n", utc_ua_user_destroy_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_add_p", utc_ua_user_add_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_add_n", utc_ua_user_add_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_remove_p", utc_ua_user_remove_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_remove_n", utc_ua_user_remove_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_get_account_p", utc_ua_user_get_account_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_get_account_n", utc_ua_user_get_account_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_add_device_n", utc_ua_user_add_device_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_remove_device_n", utc_ua_user_remove_device_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_user_foreach_devices_n", utc_ua_user_foreach_devices_n, utc_ua_startup, utc_ua_cleanup},
	/* User Awareness Service APIs */
	{"utc_ua_service_create_p", utc_ua_service_create_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_create_n", utc_ua_service_create_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_destroy_p", utc_ua_service_destroy_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_destroy_n", utc_ua_service_destroy_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_add_p", utc_ua_service_add_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_add_n", utc_ua_service_add_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_update_p", utc_ua_service_update_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_update_n", utc_ua_service_update_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_remove_p", utc_ua_service_remove_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_remove_n", utc_ua_service_remove_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_get_name_p", utc_ua_service_get_name_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_get_name_n", utc_ua_service_get_name_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_set_detection_threshold_p", utc_ua_service_set_detection_threshold_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_set_detection_threshold_n", utc_ua_service_set_detection_threshold_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_get_detection_threshold_p", utc_ua_service_get_detection_threshold_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_get_detection_threshold_n", utc_ua_service_get_detection_threshold_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_get_user_by_account_p", utc_ua_service_get_user_by_account_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_get_user_by_account_n", utc_ua_service_get_user_by_account_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_add_user_p", utc_ua_service_add_user_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_add_user_n", utc_ua_service_add_user_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_remove_user_p", utc_ua_service_remove_user_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_remove_user_n", utc_ua_service_remove_user_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_foreach_users_p", utc_ua_service_foreach_users_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_service_foreach_users_n", utc_ua_service_foreach_users_n, utc_ua_startup, utc_ua_cleanup},
	/* User Awareness Device APIs */
	{"utc_ua_device_create_p", utc_ua_device_create_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_create_n", utc_ua_device_create_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_destroy_p", utc_ua_device_destroy_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_destroy_n", utc_ua_device_destroy_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_mac_type_p", utc_ua_device_get_mac_type_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_mac_type_n", utc_ua_device_get_mac_type_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_set_os_info_p", utc_ua_device_set_os_info_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_set_os_info_n", utc_ua_device_set_os_info_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_os_info_p", utc_ua_device_get_os_info_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_os_info_n", utc_ua_device_get_os_info_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_mac_address_p", utc_ua_device_get_mac_address_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_mac_address_n", utc_ua_device_get_mac_address_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_device_id_p", utc_ua_device_get_device_id_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_device_id_n", utc_ua_device_get_device_id_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_set_wifi_bssid_p", utc_ua_device_set_wifi_bssid_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_set_wifi_bssid_n", utc_ua_device_set_wifi_bssid_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_wifi_bssid_p", utc_ua_device_get_wifi_bssid_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_wifi_bssid_n", utc_ua_device_get_wifi_bssid_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_set_wifi_ipv4_address_p", utc_ua_device_set_wifi_ipv4_address_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_set_wifi_ipv4_address_n", utc_ua_device_set_wifi_ipv4_address_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_wifi_ipv4_address_p", utc_ua_device_get_wifi_ipv4_address_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_wifi_ipv4_address_n", utc_ua_device_get_wifi_ipv4_address_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_last_presence_p", utc_ua_device_get_last_presence_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_last_presence_n", utc_ua_device_get_last_presence_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_pairing_required_p", utc_ua_device_get_pairing_required_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_pairing_required_n", utc_ua_device_get_pairing_required_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_update_n", utc_ua_device_update_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_by_mac_address_p", utc_ua_device_get_by_mac_address_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_by_mac_address_n", utc_ua_device_get_by_mac_address_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_by_device_id_p", utc_ua_device_get_by_device_id_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_device_get_by_device_id_n", utc_ua_device_get_by_device_id_n, utc_ua_startup, utc_ua_cleanup},
	/* User Awareness Sensor APIs */
	{"utc_ua_sensor_get_status_n", utc_ua_sensor_get_status_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_sensor_get_timestamp_n", utc_ua_sensor_get_timestamp_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_sensor_get_type_n", utc_ua_sensor_get_type_n, utc_ua_startup, utc_ua_cleanup},
	/* User Awareness Location APIs */
	{"utc_ua_monitor_set_location_period_p", utc_ua_monitor_set_location_period_p, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_set_location_period_n", utc_ua_monitor_set_location_period_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_location_get_distance_n", utc_ua_location_get_distance_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_location_get_position_n", utc_ua_location_get_position_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_start_location_detection_n", utc_ua_monitor_start_location_detection_n, utc_ua_startup, utc_ua_cleanup},
	{"utc_ua_monitor_stop_location_detection_n", utc_ua_monitor_stop_location_detection_n, utc_ua_startup, utc_ua_cleanup},

	{NULL, NULL}
};

#endif // __TCT_UA_NATIVE_H__
