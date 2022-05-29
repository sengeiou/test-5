//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_CAPI_NETWORK_UA_NATIVE_H__
#define __TCT_CAPI_NETWORK_UA_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_capi_network_ua_service_startup(void);
extern void ITs_capi_network_ua_service_cleanup(void);

extern void ITs_capi_network_ua_monitor_startup(void);
extern void ITs_capi_network_ua_monitor_cleanup(void);

extern void ITs_capi_network_ua_device_startup(void);
extern void ITs_capi_network_ua_device_cleanup(void);

extern void ITs_capi_network_ua_user_startup(void);
extern void ITs_capi_network_ua_user_cleanup(void);

extern void ITs_capi_network_ua_location_startup(void);
extern void ITs_capi_network_ua_location_cleanup(void);

extern int ITc_capi_network_ua_service_add_remove_p(void);
extern int ITc_capi_network_ua_service_create_destroy_p(void);
extern int ITc_capi_network_ua_get_default_service_p(void);
extern int ITc_capi_network_ua_service_update_p(void);
extern int ITc_capi_network_ua_service_get_name_p(void);
extern int ITc_capi_network_ua_service_set_get_detection_threshold_p(void);
extern int ITc_capi_network_ua_get_service_by_name_p(void);
extern int ITc_capi_network_ua_service_add_remove_user_p(void);
extern int ITc_capi_network_ua_service_get_user_by_account_p(void);
extern int ITc_capi_network_ua_service_foreach_users_p(void);
extern int ITc_capi_network_ua_foreach_service_p(void);

extern int ITc_capi_network_ua_monitor_create_destroy_p(void);
extern int ITc_capi_network_ua_monitor_add_remove_sensor_p(void);
extern int ITc_capi_network_ua_monitor_foreach_sensor_p(void);
extern int ITc_capi_network_ua_monitor_is_sensor_available_p(void);
extern int ITc_capi_network_ua_monitor_set_unset_sensor_status_changed_cb_p(void);
extern int ITc_capi_network_ua_monitor_start_stop_presence_detection_p(void);
extern int ITc_capi_network_ua_monitor_start_stop_absence_detection_p(void);

extern int ITc_capi_network_ua_device_create_destroy_p(void);
extern int ITc_capi_network_ua_device_get_mac_type_p(void);
extern int ITc_capi_network_ua_device_get_mac_address_p(void);
extern int ITc_capi_network_ua_device_get_device_id_p(void);
extern int ITc_capi_network_ua_device_set_get_os_info_p(void);
extern int ITc_capi_network_ua_device_set_get_wifi_bssid_p(void);
extern int ITc_capi_network_ua_device_set_get_wifi_ipv4_address(void);
extern int ITc_capi_network_ua_device_get_last_presence_p(void);
extern int ITc_capi_network_ua_device_get_pairing_required_p(void);
extern int ITc_capi_network_ua_device_get_by_mac_address_p(void);
extern int ITc_capi_network_ua_device_get_by_device_id_p(void);

extern int ITc_capi_network_ua_user_create_destroy_p(void);
extern int ITc_capi_network_ua_user_add_remove_p(void);
extern int ITc_capi_network_ua_user_get_account_p(void);
extern int ITc_capi_network_ua_monitor_set_location_period_p(void);

testcase tc_array[] = {
    {"ITc_capi_network_ua_service_add_remove_p", ITc_capi_network_ua_service_add_remove_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},
    {"ITc_capi_network_ua_service_create_destroy_p", ITc_capi_network_ua_service_create_destroy_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},
    {"ITc_capi_network_ua_get_default_service_p", ITc_capi_network_ua_get_default_service_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},
    {"ITc_capi_network_ua_service_update_p", ITc_capi_network_ua_service_update_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},
    {"ITc_capi_network_ua_service_get_name_p", ITc_capi_network_ua_service_get_name_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},
    {"ITc_capi_network_ua_service_set_get_detection_threshold_p", ITc_capi_network_ua_service_set_get_detection_threshold_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},
    {"ITc_capi_network_ua_get_service_by_name_p", ITc_capi_network_ua_get_service_by_name_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},
    {"ITc_capi_network_ua_service_add_remove_user_p", ITc_capi_network_ua_service_add_remove_user_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},
    {"ITc_capi_network_ua_service_get_user_by_account_p", ITc_capi_network_ua_service_get_user_by_account_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},
    {"ITc_capi_network_ua_service_foreach_users_p", ITc_capi_network_ua_service_foreach_users_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},
    {"ITc_capi_network_ua_foreach_service_p", ITc_capi_network_ua_foreach_service_p, ITs_capi_network_ua_service_startup, ITs_capi_network_ua_service_cleanup},

    {"ITc_capi_network_ua_monitor_create_destroy_p", ITc_capi_network_ua_monitor_create_destroy_p, ITs_capi_network_ua_monitor_startup, ITs_capi_network_ua_monitor_cleanup},
    {"ITc_capi_network_ua_monitor_add_remove_sensor_p", ITc_capi_network_ua_monitor_add_remove_sensor_p, ITs_capi_network_ua_monitor_startup, ITs_capi_network_ua_monitor_cleanup},
    {"ITc_capi_network_ua_monitor_foreach_sensor_p", ITc_capi_network_ua_monitor_foreach_sensor_p, ITs_capi_network_ua_monitor_startup, ITs_capi_network_ua_monitor_cleanup},
    {"ITc_capi_network_ua_monitor_is_sensor_available_p", ITc_capi_network_ua_monitor_is_sensor_available_p, ITs_capi_network_ua_monitor_startup, ITs_capi_network_ua_monitor_cleanup},
    {"ITc_capi_network_ua_monitor_set_unset_sensor_status_changed_cb_p", ITc_capi_network_ua_monitor_set_unset_sensor_status_changed_cb_p, ITs_capi_network_ua_monitor_startup, ITs_capi_network_ua_monitor_cleanup},
    {"ITc_capi_network_ua_monitor_start_stop_presence_detection_p", ITc_capi_network_ua_monitor_start_stop_presence_detection_p, ITs_capi_network_ua_monitor_startup, ITs_capi_network_ua_monitor_cleanup},
    {"ITc_capi_network_ua_monitor_start_stop_absence_detection_p", ITc_capi_network_ua_monitor_start_stop_absence_detection_p, ITs_capi_network_ua_monitor_startup, ITs_capi_network_ua_monitor_cleanup},

    {"ITc_capi_network_ua_device_create_destroy_p", ITc_capi_network_ua_device_create_destroy_p, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},
    {"ITc_capi_network_ua_device_get_mac_type_p", ITc_capi_network_ua_device_get_mac_type_p, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},
    {"ITc_capi_network_ua_device_get_mac_address_p", ITc_capi_network_ua_device_get_mac_address_p, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},
    {"ITc_capi_network_ua_device_get_device_id_p", ITc_capi_network_ua_device_get_device_id_p, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},
    {"ITc_capi_network_ua_device_set_get_os_info_p", ITc_capi_network_ua_device_set_get_os_info_p, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},
    {"ITc_capi_network_ua_device_set_get_wifi_bssid_p", ITc_capi_network_ua_device_set_get_wifi_bssid_p, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},
    {"ITc_capi_network_ua_device_set_get_wifi_ipv4_address", ITc_capi_network_ua_device_set_get_wifi_ipv4_address, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},
    {"ITc_capi_network_ua_device_get_last_presence_p", ITc_capi_network_ua_device_get_last_presence_p, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},
    {"ITc_capi_network_ua_device_get_pairing_required_p", ITc_capi_network_ua_device_get_pairing_required_p, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},
    {"ITc_capi_network_ua_device_get_by_mac_address_p", ITc_capi_network_ua_device_get_by_mac_address_p, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},
    {"ITc_capi_network_ua_device_get_by_device_id_p", ITc_capi_network_ua_device_get_by_device_id_p, ITs_capi_network_ua_device_startup, ITs_capi_network_ua_device_cleanup},

    {"ITc_capi_network_ua_user_create_destroy_p", ITc_capi_network_ua_user_create_destroy_p, ITs_capi_network_ua_user_startup, ITs_capi_network_ua_user_cleanup},
    {"ITc_capi_network_ua_user_add_remove_p", ITc_capi_network_ua_user_add_remove_p, ITs_capi_network_ua_user_startup, ITs_capi_network_ua_user_cleanup},
    {"ITc_capi_network_ua_user_get_account_p", ITc_capi_network_ua_user_get_account_p, ITs_capi_network_ua_user_startup, ITs_capi_network_ua_user_cleanup},
    {"ITc_capi_network_ua_monitor_set_location_period_p", ITc_capi_network_ua_monitor_set_location_period_p, ITs_capi_network_ua_location_startup, ITs_capi_network_ua_location_cleanup},
    {NULL, NULL}
};

#endif // __TCT_CAPI_NETWORK_UA_NATIVE_H__

