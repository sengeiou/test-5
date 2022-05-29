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
#ifndef __TCT_WIFI-DIRECT-NATIVE_H__
#define __TCT_WIFI-DIRECT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_wifi_direct_startup(void);
extern void ITs_wifi_direct_cleanup(void);

extern int ITc_wifi_direct_initialize_p(void);
extern int ITc_wifi_direct_deinitialize_p(void);
extern int ITc_wifi_direct_init_deinit_display_p(void);
extern int ITc_wifi_direct_set_get_display_p(void);
extern int ITc_wifi_direct_set_get_display_availability_p(void);
extern int ITc_wifi_direct_get_supported_wps_mode_p(void);
extern int ITc_wifi_direct_foreach_supported_wps_types_p(void);
extern int ITc_wifi_direct_get_local_wps_type_p(void);
extern int ITc_wifi_direct_get_mac_address_p(void);
extern int ITc_wifi_direct_set_get_max_clients_p(void);
extern int ITc_wifi_direct_get_primary_device_type_p(void);
extern int ITc_wifi_direct_set_get_req_wps_type_p(void);
extern int ITc_wifi_direct_get_secondary_device_type_p(void);
extern int ITc_wifi_direct_get_ssid_p(void);
extern int ITc_wifi_direct_set_auto_connectionmode_is_auto_connection_p(void);
extern int ITc_wifi_direct_is_discoverable_p(void);
extern int ITc_wifi_direct_set_unset_device_state_changed_cb_p(void);
extern int ITc_wifi_direct_activate_deactivate_p(void);
extern int ITc_wifi_direct_init_miracast_p(void);
extern int ITc_wifi_direct_get_state_p(void);
extern int ITc_wifi_direct_is_listening_only_p(void);
extern int ITc_wifi_direct_create_destroy_group_p(void);
extern int ITc_wifi_direct_is_autonomous_group_p(void);
extern int ITc_wifi_direct_is_group_owner_p(void);
extern int ITc_wifi_direct_set_get_device_name_p(void);
extern int ITc_wifi_direct_set_get_group_owner_intent_p(void);
extern int ITc_wifi_direct_set_wps_pin_p(void);
extern int ITc_wifi_direct_foreach_discovered_peers_p(void);
extern int ITc_wifi_direct_foreach_persistent_groups_p(void);
extern int ITc_wifi_direct_register_deregister_service_p(void);
extern int ITc_wifi_direct_start_cancel_discovery_p(void);
extern int ITc_wifi_direct_set_unset_discovery_state_changed_cb_p(void);
extern int ITc_wifi_direct_set_unset_peer_found_cb_p(void);
extern int ITc_wifi_direct_start_cancel_service_discovery_p(void);
extern int ITc_wifi_direct_set_unset_service_state_changed_cb_p(void);
extern int ITc_wifi_direct_start_discovery_specific_channel_p(void);
extern int ITc_wifi_direct_set_unset_client_ip_address_assigned_cb_p(void);
extern int ITc_wifi_direct_set_unset_connection_state_changed_cb_p(void);
extern int ITc_wifi_direct_set_auto_group_removal_p(void);
extern int ITc_wifi_direct_set_get_session_timer_p(void);
extern int ITc_wifi_direct_set_unset_state_changed_cb_p(void);

extern int ITc_wifi_direct_start_discovery_specific_freq_p(void);
extern int ITc_wifi_direct_add_get_remove_vsie_p(void);
extern int ITc_wifi_direct_set_get_wps_config_method_p(void);
extern int ITc_wifi_direct_create_group_with_ssid_p(void);
extern int ITc_wifi_direct_set_get_go_intent_per_type_p(void);
extern int ITc_wifi_direct_set_unset_peer_info_connection_state_changed_cb_p(void);

testcase tc_array[] = {
	{"ITc_wifi_direct_initialize_p",ITc_wifi_direct_initialize_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_deinitialize_p",ITc_wifi_direct_deinitialize_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_init_deinit_display_p",ITc_wifi_direct_init_deinit_display_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_get_display_p", ITc_wifi_direct_set_get_display_p, ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_get_display_availability_p", ITc_wifi_direct_set_get_display_availability_p, ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_get_supported_wps_mode_p",ITc_wifi_direct_get_supported_wps_mode_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_foreach_supported_wps_types_p",ITc_wifi_direct_foreach_supported_wps_types_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_get_local_wps_type_p",ITc_wifi_direct_get_local_wps_type_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_get_mac_address_p",ITc_wifi_direct_get_mac_address_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_get_max_clients_p",ITc_wifi_direct_set_get_max_clients_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_get_primary_device_type_p",ITc_wifi_direct_get_primary_device_type_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_get_req_wps_type_p",ITc_wifi_direct_set_get_req_wps_type_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_get_secondary_device_type_p",ITc_wifi_direct_get_secondary_device_type_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_get_ssid_p",ITc_wifi_direct_get_ssid_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_auto_connectionmode_is_auto_connection_p",ITc_wifi_direct_set_auto_connectionmode_is_auto_connection_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_is_discoverable_p",ITc_wifi_direct_is_discoverable_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_unset_device_state_changed_cb_p",ITc_wifi_direct_set_unset_device_state_changed_cb_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_activate_deactivate_p",ITc_wifi_direct_activate_deactivate_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_init_miracast_p",ITc_wifi_direct_init_miracast_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_get_state_p",ITc_wifi_direct_get_state_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_is_listening_only_p",ITc_wifi_direct_is_listening_only_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_create_destroy_group_p",ITc_wifi_direct_create_destroy_group_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_is_autonomous_group_p",ITc_wifi_direct_is_autonomous_group_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_is_group_owner_p",ITc_wifi_direct_is_group_owner_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_get_device_name_p",ITc_wifi_direct_set_get_device_name_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_get_group_owner_intent_p",ITc_wifi_direct_set_get_group_owner_intent_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_wps_pin_p",ITc_wifi_direct_set_wps_pin_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_foreach_discovered_peers_p",ITc_wifi_direct_foreach_discovered_peers_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_foreach_persistent_groups_p",ITc_wifi_direct_foreach_persistent_groups_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_register_deregister_service_p",ITc_wifi_direct_register_deregister_service_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_start_cancel_discovery_p",ITc_wifi_direct_start_cancel_discovery_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_unset_discovery_state_changed_cb_p",ITc_wifi_direct_set_unset_discovery_state_changed_cb_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_unset_peer_found_cb_p",ITc_wifi_direct_set_unset_peer_found_cb_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_start_cancel_service_discovery_p",ITc_wifi_direct_start_cancel_service_discovery_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_unset_service_state_changed_cb_p",ITc_wifi_direct_set_unset_service_state_changed_cb_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_start_discovery_specific_channel_p",ITc_wifi_direct_start_discovery_specific_channel_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_unset_client_ip_address_assigned_cb_p",ITc_wifi_direct_set_unset_client_ip_address_assigned_cb_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_unset_connection_state_changed_cb_p",ITc_wifi_direct_set_unset_connection_state_changed_cb_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_auto_group_removal_p",ITc_wifi_direct_set_auto_group_removal_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_get_session_timer_p",ITc_wifi_direct_set_get_session_timer_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_set_unset_state_changed_cb_p",ITc_wifi_direct_set_unset_state_changed_cb_p,ITs_wifi_direct_startup,ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_start_discovery_specific_freq_p", ITc_wifi_direct_start_discovery_specific_freq_p, ITs_wifi_direct_startup, ITs_wifi_direct_cleanup},
	{"ITc_wifi_direct_add_get_remove_vsie_p", ITc_wifi_direct_add_get_remove_vsie_p, ITs_wifi_direct_startup, ITs_wifi_direct_cleanup},
        {"ITc_wifi_direct_set_get_wps_config_method_p", ITc_wifi_direct_set_get_wps_config_method_p, ITs_wifi_direct_startup, ITs_wifi_direct_cleanup},
        {"ITc_wifi_direct_create_group_with_ssid_p", ITc_wifi_direct_create_group_with_ssid_p, ITs_wifi_direct_startup, ITs_wifi_direct_cleanup},
        {"ITc_wifi_direct_set_get_go_intent_per_type_p", ITc_wifi_direct_set_get_go_intent_per_type_p, ITs_wifi_direct_startup, ITs_wifi_direct_cleanup},
        {"ITc_wifi_direct_set_unset_peer_info_connection_state_changed_cb_p", ITc_wifi_direct_set_unset_peer_info_connection_state_changed_cb_p, ITs_wifi_direct_startup, ITs_wifi_direct_cleanup},
	{NULL, NULL}
};

#endif // __TCT_WIFI-DIRECT-NATIVE_H__
