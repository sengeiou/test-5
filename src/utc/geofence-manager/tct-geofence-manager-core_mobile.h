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

extern void utc_geofence_manager_startup(void);
extern void utc_geofence_manager_cleanup(void);

extern int utc_geofence_manager_is_supported_p(void);
extern int utc_geofence_manager_is_supported_n(void);
extern int utc_geofence_manager_create_p(void);
extern int utc_geofence_manager_create_n(void);
extern int utc_geofence_manager_destroy_p(void);
extern int utc_geofence_manager_destroy_n(void);
extern int utc_geofence_manager_set_geofence_event_cb_p(void);
extern int utc_geofence_manager_set_geofence_event_cb_n1(void);
extern int utc_geofence_manager_set_geofence_event_cb_n2(void);
extern int utc_geofence_manager_unset_geofence_event_cb_p(void);
extern int utc_geofence_manager_unset_geofence_event_cb_n(void);
extern int utc_geofence_create_geopoint_p(void);
extern int utc_geofence_create_geopoint_n1(void);
extern int utc_geofence_create_geopoint_n2(void);
extern int utc_geofence_create_geopoint_n3(void);
extern int utc_geofence_create_geopoint_n4(void);
extern int utc_geofence_create_geopoint_n5(void);
extern int utc_geofence_create_geopoint_n6(void);
extern int utc_geofence_create_bluetooth_p(void);
extern int utc_geofence_create_bluetooth_n1(void);
extern int utc_geofence_create_bluetooth_n2(void);
extern int utc_geofence_create_bluetooth_n3(void);
extern int utc_geofence_create_bluetooth_n4(void);
extern int utc_geofence_create_wifi_p(void);
extern int utc_geofence_create_wifi_n1(void);
extern int utc_geofence_create_wifi_n2(void);
extern int utc_geofence_create_wifi_n3(void);
extern int utc_geofence_create_wifi_n4(void);
extern int utc_geofence_destroy_p(void);
extern int utc_geofence_destroy_n(void);
extern int utc_geofence_manager_add_place_p(void);
extern int utc_geofence_manager_add_place_n1(void);
extern int utc_geofence_manager_add_place_n2(void);
extern int utc_geofence_manager_add_place_n3(void);
extern int utc_geofence_manager_add_fence_p1(void);
extern int utc_geofence_manager_add_fence_p2(void);
extern int utc_geofence_manager_add_fence_p3(void);
extern int utc_geofence_manager_add_fence_n1(void);
extern int utc_geofence_manager_add_fence_n2(void);
extern int utc_geofence_manager_add_fence_n3(void);
extern int utc_geofence_manager_add_fence_n4(void);
extern int utc_geofence_manager_add_fence_n5(void);
extern int utc_geofence_manager_update_place_p(void);
extern int utc_geofence_manager_update_place_n1(void);
extern int utc_geofence_manager_update_place_n2(void);
extern int utc_geofence_manager_update_place_n3(void);
extern int utc_geofence_manager_update_place_n4(void);
extern int utc_geofence_manager_foreach_geofence_list_p(void);
extern int utc_geofence_manager_foreach_geofence_list_n1(void);
extern int utc_geofence_manager_foreach_geofence_list_n2(void);
extern int utc_geofence_manager_foreach_place_geofence_list_p(void);
extern int utc_geofence_manager_foreach_place_geofence_list_n1(void);
extern int utc_geofence_manager_foreach_place_geofence_list_n2(void);
extern int utc_geofence_manager_foreach_place_geofence_list_n3(void);
extern int utc_geofence_manager_foreach_place_geofence_list_n4(void);
extern int utc_geofence_manager_foreach_place_list_p(void);
extern int utc_geofence_manager_foreach_place_list_n1(void);
extern int utc_geofence_manager_foreach_place_list_n2(void);
extern int utc_geofence_manager_remove_place_p(void);
extern int utc_geofence_manager_remove_place_n1(void);
extern int utc_geofence_manager_remove_place_n2(void);
extern int utc_geofence_manager_remove_place_n3(void);
extern int utc_geofence_manager_remove_place_n4(void);
extern int utc_geofence_manager_remove_fence_p1(void);
extern int utc_geofence_manager_remove_fence_p2(void);
extern int utc_geofence_manager_remove_fence_p3(void);
extern int utc_geofence_manager_remove_fence_n1(void);
extern int utc_geofence_manager_remove_fence_n2(void);
extern int utc_geofence_manager_remove_fence_n3(void);
extern int utc_geofence_manager_set_geofence_state_changed_cb_p(void);
extern int utc_geofence_manager_set_geofence_state_changed_cb_n1(void);
extern int utc_geofence_manager_set_geofence_state_changed_cb_n2(void);
extern int utc_geofence_manager_unset_geofence_state_changed_cb_p(void);
extern int utc_geofence_manager_unset_geofence_state_changed_cb_n1(void);
extern int utc_geofence_manager_set_geofence_proximity_state_changed_cb_p(void);
extern int utc_geofence_manager_set_geofence_proximity_state_changed_cb_n1(void);
extern int utc_geofence_manager_set_geofence_proximity_state_changed_cb_n2(void);
extern int utc_geofence_manager_unset_geofence_proximity_state_changed_cb_p(void);
extern int utc_geofence_manager_unset_geofence_proximity_state_changed_cb_n1(void);
extern int utc_geofence_manager_start_p1(void);
extern int utc_geofence_manager_start_p2(void);
extern int utc_geofence_manager_start_p3(void);
extern int utc_geofence_manager_start_n1(void);
extern int utc_geofence_manager_start_n2(void);
extern int utc_geofence_manager_start_n3(void);
extern int utc_geofence_manager_start_n4(void);
extern int utc_geofence_manager_stop_p1(void);
extern int utc_geofence_manager_stop_p2(void);
extern int utc_geofence_manager_stop_p3(void);
extern int utc_geofence_manager_stop_n1(void);
extern int utc_geofence_manager_stop_n2(void);
extern int utc_geofence_status_create_p(void);
extern int utc_geofence_status_create_n(void);
extern int utc_geofence_status_destroy_p(void);
extern int utc_geofence_status_destroy_n(void);
extern int utc_geofence_status_get_state_p(void);
extern int utc_geofence_status_get_state_n(void);
extern int utc_geofence_status_get_duration_p(void);
extern int utc_geofence_status_get_duration_n(void);
extern int utc_geofence_manager_get_place_name_p(void);
extern int utc_geofence_manager_get_place_name_n1(void);
extern int utc_geofence_manager_get_place_name_n2(void);
extern int utc_geofence_manager_get_place_name_n3(void);
extern int utc_geofence_get_address_p(void);
extern int utc_geofence_get_address_n1(void);
extern int utc_geofence_get_address_n2(void);
extern int utc_geofence_get_latitude_p(void);
extern int utc_geofence_get_latitude_n1(void);
extern int utc_geofence_get_latitude_n2(void);
extern int utc_geofence_get_longitude_p(void);
extern int utc_geofence_get_longitude_n1(void);
extern int utc_geofence_get_longitude_n2(void);
extern int utc_geofence_get_radius_p(void);
extern int utc_geofence_get_radius_n1(void);
extern int utc_geofence_get_radius_n2(void);
extern int utc_geofence_get_bssid_p(void);
extern int utc_geofence_get_bssid_n1(void);
extern int utc_geofence_get_bssid_n2(void);
extern int utc_geofence_get_ssid_p(void);
extern int utc_geofence_get_ssid_n1(void);
extern int utc_geofence_get_ssid_n2(void);
extern int utc_geofence_get_place_id_p(void);
extern int utc_geofence_get_place_id_n1(void);
extern int utc_geofence_get_place_id_n2(void);
extern int utc_geofence_get_type_p1(void);
extern int utc_geofence_get_type_p2(void);
extern int utc_geofence_get_type_p3(void);
extern int utc_geofence_get_type_n1(void);
extern int utc_geofence_get_type_n2(void);

testcase tc_array[] = {
	{"utc_geofence_manager_is_supported_p",utc_geofence_manager_is_supported_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_is_supported_n",utc_geofence_manager_is_supported_n,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_create_p",utc_geofence_manager_create_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_create_n",utc_geofence_manager_create_n,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_destroy_p",utc_geofence_manager_destroy_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_destroy_n",utc_geofence_manager_destroy_n,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_set_geofence_event_cb_p",utc_geofence_manager_set_geofence_event_cb_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_set_geofence_event_cb_n1",utc_geofence_manager_set_geofence_event_cb_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_set_geofence_event_cb_n2",utc_geofence_manager_set_geofence_event_cb_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_unset_geofence_event_cb_p",utc_geofence_manager_unset_geofence_event_cb_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_unset_geofence_event_cb_n",utc_geofence_manager_unset_geofence_event_cb_n,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_geopoint_p",utc_geofence_create_geopoint_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_geopoint_n1",utc_geofence_create_geopoint_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_geopoint_n2",utc_geofence_create_geopoint_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_geopoint_n3",utc_geofence_create_geopoint_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_geopoint_n4",utc_geofence_create_geopoint_n4,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_geopoint_n5",utc_geofence_create_geopoint_n5,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_geopoint_n6",utc_geofence_create_geopoint_n6,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_bluetooth_p",utc_geofence_create_bluetooth_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_bluetooth_n1",utc_geofence_create_bluetooth_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_bluetooth_n2",utc_geofence_create_bluetooth_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_bluetooth_n3",utc_geofence_create_bluetooth_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_bluetooth_n4",utc_geofence_create_bluetooth_n4,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_wifi_p",utc_geofence_create_wifi_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_wifi_n1",utc_geofence_create_wifi_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_wifi_n2",utc_geofence_create_wifi_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_wifi_n3",utc_geofence_create_wifi_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_create_wifi_n4",utc_geofence_create_wifi_n4,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_destroy_p",utc_geofence_destroy_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_destroy_n",utc_geofence_destroy_n,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_place_p",utc_geofence_manager_add_place_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_place_n1",utc_geofence_manager_add_place_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_place_n2",utc_geofence_manager_add_place_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_place_n3",utc_geofence_manager_add_place_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_fence_p1",utc_geofence_manager_add_fence_p1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_fence_p2",utc_geofence_manager_add_fence_p2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_fence_p3",utc_geofence_manager_add_fence_p3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_fence_n1",utc_geofence_manager_add_fence_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_fence_n2",utc_geofence_manager_add_fence_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_fence_n3",utc_geofence_manager_add_fence_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_fence_n4",utc_geofence_manager_add_fence_n4,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_add_fence_n5",utc_geofence_manager_add_fence_n5,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_update_place_p",utc_geofence_manager_update_place_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_update_place_n1",utc_geofence_manager_update_place_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_update_place_n2",utc_geofence_manager_update_place_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_update_place_n3",utc_geofence_manager_update_place_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_update_place_n4",utc_geofence_manager_update_place_n4,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_geofence_list_p",utc_geofence_manager_foreach_geofence_list_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_geofence_list_n1",utc_geofence_manager_foreach_geofence_list_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_geofence_list_n2",utc_geofence_manager_foreach_geofence_list_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_place_geofence_list_p",utc_geofence_manager_foreach_place_geofence_list_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_place_geofence_list_n1",utc_geofence_manager_foreach_place_geofence_list_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_place_geofence_list_n2",utc_geofence_manager_foreach_place_geofence_list_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_place_geofence_list_n3",utc_geofence_manager_foreach_place_geofence_list_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_place_geofence_list_n4",utc_geofence_manager_foreach_place_geofence_list_n4,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_place_list_p",utc_geofence_manager_foreach_place_list_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_place_list_n1",utc_geofence_manager_foreach_place_list_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_foreach_place_list_n2",utc_geofence_manager_foreach_place_list_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_place_p",utc_geofence_manager_remove_place_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_place_n1",utc_geofence_manager_remove_place_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_place_n2",utc_geofence_manager_remove_place_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_place_n3",utc_geofence_manager_remove_place_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_place_n4",utc_geofence_manager_remove_place_n4,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_fence_p1",utc_geofence_manager_remove_fence_p1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_fence_p2",utc_geofence_manager_remove_fence_p2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_fence_p3",utc_geofence_manager_remove_fence_p3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_fence_n1",utc_geofence_manager_remove_fence_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_fence_n2",utc_geofence_manager_remove_fence_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_remove_fence_n3",utc_geofence_manager_remove_fence_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_set_geofence_state_changed_cb_p",utc_geofence_manager_set_geofence_state_changed_cb_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_set_geofence_state_changed_cb_n1",utc_geofence_manager_set_geofence_state_changed_cb_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_set_geofence_state_changed_cb_n2",utc_geofence_manager_set_geofence_state_changed_cb_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_unset_geofence_state_changed_cb_p",utc_geofence_manager_unset_geofence_state_changed_cb_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_unset_geofence_state_changed_cb_n1",utc_geofence_manager_unset_geofence_state_changed_cb_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_set_geofence_proximity_state_changed_cb_p",utc_geofence_manager_set_geofence_proximity_state_changed_cb_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_set_geofence_proximity_state_changed_cb_n1",utc_geofence_manager_set_geofence_proximity_state_changed_cb_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_set_geofence_proximity_state_changed_cb_n2",utc_geofence_manager_set_geofence_proximity_state_changed_cb_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_unset_geofence_proximity_state_changed_cb_p",utc_geofence_manager_unset_geofence_proximity_state_changed_cb_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_unset_geofence_proximity_state_changed_cb_n1",utc_geofence_manager_unset_geofence_proximity_state_changed_cb_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_start_p1",utc_geofence_manager_start_p1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_start_p2",utc_geofence_manager_start_p2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_start_p3",utc_geofence_manager_start_p3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_start_n1",utc_geofence_manager_start_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_start_n2",utc_geofence_manager_start_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_start_n3",utc_geofence_manager_start_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_start_n4",utc_geofence_manager_start_n4,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_stop_p1",utc_geofence_manager_stop_p1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_stop_p2",utc_geofence_manager_stop_p2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_stop_p3",utc_geofence_manager_stop_p3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_stop_n1",utc_geofence_manager_stop_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_stop_n2",utc_geofence_manager_stop_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_status_create_p",utc_geofence_status_create_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_status_create_n",utc_geofence_status_create_n,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_status_destroy_p",utc_geofence_status_destroy_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_status_destroy_n",utc_geofence_status_destroy_n,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_status_get_state_p",utc_geofence_status_get_state_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_status_get_state_n",utc_geofence_status_get_state_n,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_status_get_duration_p",utc_geofence_status_get_duration_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_status_get_duration_n",utc_geofence_status_get_duration_n,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_get_place_name_p",utc_geofence_manager_get_place_name_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_get_place_name_n1",utc_geofence_manager_get_place_name_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_get_place_name_n2",utc_geofence_manager_get_place_name_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_manager_get_place_name_n3",utc_geofence_manager_get_place_name_n3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_address_p",utc_geofence_get_address_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_address_n1",utc_geofence_get_address_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_address_n2",utc_geofence_get_address_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_latitude_p",utc_geofence_get_latitude_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_latitude_n1",utc_geofence_get_latitude_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_latitude_n2",utc_geofence_get_latitude_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_longitude_p",utc_geofence_get_longitude_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_longitude_n1",utc_geofence_get_longitude_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_longitude_n2",utc_geofence_get_longitude_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_radius_p",utc_geofence_get_radius_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_radius_n1",utc_geofence_get_radius_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_radius_n2",utc_geofence_get_radius_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_bssid_p",utc_geofence_get_bssid_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_bssid_n1",utc_geofence_get_bssid_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_bssid_n2",utc_geofence_get_bssid_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_ssid_p",utc_geofence_get_ssid_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_ssid_n1",utc_geofence_get_ssid_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_ssid_n2",utc_geofence_get_ssid_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_place_id_p",utc_geofence_get_place_id_p,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_place_id_n1",utc_geofence_get_place_id_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_place_id_n2",utc_geofence_get_place_id_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_type_p1",utc_geofence_get_type_p1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_type_p2",utc_geofence_get_type_p2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_type_p3",utc_geofence_get_type_p3,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_type_n1",utc_geofence_get_type_n1,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{"utc_geofence_get_type_n2",utc_geofence_get_type_n2,utc_geofence_manager_startup,utc_geofence_manager_cleanup},
	{NULL, NULL}
};

#endif // __TCT_GEOFENCE-MANAGER-NATIVE_H__
