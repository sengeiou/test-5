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
#ifndef __TCT_GEOFENCE-MANAGER-NATIVE_H__
#define __TCT_GEOFENCE-MANAGER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_geofence_manager_startup(void);
extern void ITs_geofence_manager_cleanup(void);
extern void ITs_geofence_startup(void);
extern void ITs_geofence_cleanup(void);

extern int ITc_geofence_manager_is_supported_p(void);
extern int ITc_geofence_manager_create_destroy_p(void);
extern int ITc_geofence_manager_set_unset_geofence_event_cb_p(void);
extern int ITc_geofence_manager_start_stop_p(void);
extern int ITc_geofence_manager_add_update_remove_place_p(void);
extern int ITc_geofence_manager_set_unset_geofence_state_changed_cb_p(void);
extern int ITc_geofence_manager_add_remove_fence_p(void);
extern int ITc_geofence_manager_foreach_geofence_list_p(void);
extern int ITc_geofence_manager_foreach_place_geofence_list_p(void);
extern int ITc_geofence_manager_foreach_place_list_p(void);
extern int ITc_geofence_manager_get_place_name_p(void);
extern int ITc_geofence_manager_set_unset_geofence_proximity_state_changed_cb_p(void);
extern int ITc_geofence_get_type_p(void);
extern int ITc_geofence_get_place_id_p(void);
extern int ITc_geofence_get_latitude_p(void);
extern int ITc_geofence_get_longitude_p(void);
extern int ITc_geofence_get_radius_p(void);
extern int ITc_geofence_get_bssid_p(void);
extern int ITc_geofence_get_ssid_p(void);
extern int ITc_geofence_get_address_p(void);
extern int ITc_geofence_create_geopoint_desroy_p(void);
extern int ITc_geofence_create_bluetooth_destroy_p(void);
extern int ITc_geofence_create_wifi_destroy_p(void);
extern int ITc_geofence_status_create_destroy_p(void);
extern int ITc_geofence_status_get_state_p(void);
extern int ITc_geofence_status_get_duration_p(void);

testcase tc_array[] = {
	{"ITc_geofence_manager_is_supported_p",ITc_geofence_manager_is_supported_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_create_destroy_p",ITc_geofence_manager_create_destroy_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_set_unset_geofence_event_cb_p",ITc_geofence_manager_set_unset_geofence_event_cb_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_start_stop_p",ITc_geofence_manager_start_stop_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_add_update_remove_place_p",ITc_geofence_manager_add_update_remove_place_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_set_unset_geofence_state_changed_cb_p",ITc_geofence_manager_set_unset_geofence_state_changed_cb_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_add_remove_fence_p",ITc_geofence_manager_add_remove_fence_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_foreach_geofence_list_p",ITc_geofence_manager_foreach_geofence_list_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_foreach_place_geofence_list_p",ITc_geofence_manager_foreach_place_geofence_list_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_foreach_place_list_p",ITc_geofence_manager_foreach_place_list_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_get_place_name_p",ITc_geofence_manager_get_place_name_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_manager_set_unset_geofence_proximity_state_changed_cb_p",ITc_geofence_manager_set_unset_geofence_proximity_state_changed_cb_p,ITs_geofence_manager_startup,ITs_geofence_manager_cleanup},
	{"ITc_geofence_get_type_p",ITc_geofence_get_type_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_get_place_id_p",ITc_geofence_get_place_id_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_get_latitude_p",ITc_geofence_get_latitude_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_get_longitude_p",ITc_geofence_get_longitude_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_get_radius_p",ITc_geofence_get_radius_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_get_bssid_p",ITc_geofence_get_bssid_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_get_ssid_p",ITc_geofence_get_ssid_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_get_address_p",ITc_geofence_get_address_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_create_geopoint_desroy_p",ITc_geofence_create_geopoint_desroy_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_create_bluetooth_destroy_p",ITc_geofence_create_bluetooth_destroy_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_create_wifi_destroy_p",ITc_geofence_create_wifi_destroy_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_status_create_destroy_p",ITc_geofence_status_create_destroy_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_status_get_state_p",ITc_geofence_status_get_state_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{"ITc_geofence_status_get_duration_p",ITc_geofence_status_get_duration_p,ITs_geofence_startup,ITs_geofence_cleanup},
	{NULL, NULL}
};

#endif // __TCT_GEOFENCE-MANAGER-NATIVE_H__
