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
#ifndef __TCT_INM-NATIVE_H__
#define __TCT_INM-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_inm_startup(void);
extern void ITs_inm_cleanup(void);
extern void ITs_inm_link_startup(void);
extern void ITs_inm_link_cleanup(void);

extern int ITc_inm_get_ethernet_cable_state_p(void);
extern int ITc_inm_set_unset_ethernet_cable_state_changed_cb_p(void);
extern int ITc_inm_set_unset_wifi_module_state_changed_cb_p(void);
extern int ITc_inm_get_wifi_module_state_p(void);
extern int ITc_inm_set_unset_ip_conflict_cb_p(void);
extern int ITc_inm_ip_conflict_detect_is_enabled_p(void);
extern int ITc_inm_get_ip_conflict_state_p(void);
extern int ITc_inm_get_statistics_p(void);
extern int ITc_inm_reset_statistics_p(void);
extern int ITc_inm_set_unset_congestion_level_cb_p(void);
extern int ITc_inm_get_congestion_level_p(void);
extern int ITc_inm_set_unset_retry_tx_rate_cb_p(void);
extern int ITc_inm_get_retry_tx_rate_p(void);
extern int ITc_inm_set_unset_channel_interference_cb_p(void);
extern int ITc_inm_get_channel_interference_p(void);
extern int ITc_inm_set_unset_cellular_state_changed_cb_p(void);
extern int ITc_inm_get_cellular_state_p(void);
extern int ITc_inm_set_unset_wifi_state_changed_cb_p(void);
extern int ITc_inm_get_wifi_state_p(void);
extern int ITc_inm_set_unset_ethernet_state_changed_cb_p(void);
extern int ITc_inm_get_ethernet_state_p(void);
extern int ITc_inm_get_current_connection_p(void);
extern int ITc_inm_connection_clone_destroy_p(void);
extern int ITc_inm_get_destroy_connection_iterator_p(void);
extern int ITc_inm_connection_iterator_next_p(void);
extern int ITc_inm_connection_get_id_p(void);
extern int ITc_inm_connection_get_name_p(void);
extern int ITc_inm_connection_get_type_p(void);
extern int ITc_inm_connection_get_network_interface_name_p(void);
extern int ITc_inm_connection_get_state_p(void);
extern int ITc_inm_connection_get_ipv6_state_p(void);
extern int ITc_inm_connection_get_ip_config_type_p(void);
extern int ITc_inm_connection_get_ip_address_p(void);
extern int ITc_inm_connection_get_subnet_mask_p(void);
extern int ITc_inm_connection_get_gateway_address_p(void);
extern int ITc_inm_connection_get_dhcp_server_address_p(void);
extern int ITc_inm_connection_get_dhcp_lease_duration_p(void);
extern int ITc_inm_connection_get_dns_address_p(void);
extern int ITc_inm_connection_get_proxy_type_p(void);
extern int ITc_inm_connection_get_proxy_address_p(void);
extern int ITc_inm_connection_get_dns_config_type_p(void);
extern int ITc_inm_connection_get_prefix_length_p(void);
extern int ITc_inm_connection_refresh_p(void);
extern int ITc_inm_connection_set_unset_state_changed_cb_p(void);
extern int ITc_inm_wifi_set_unset_scan_state_changed_cb_p(void);
extern int ITc_inm_wifi_get_scan_state_p(void);
extern int ITc_inm_wifi_get_connected_ap_p(void);
extern int ITc_inm_wifi_foreach_found_ap_p(void);
extern int ITc_inm_wifi_ap_get_essid_p(void);
extern int ITc_inm_wifi_ap_get_raw_ssid_p(void);
extern int ITc_inm_wifi_ap_get_bssid_p(void);
extern int ITc_inm_wifi_ap_get_rssi_p(void);
extern int ITc_inm_wifi_ap_get_rssi_level_p(void);
extern int ITc_inm_wifi_ap_get_frequency_p(void);
extern int ITc_inm_wifi_ap_get_max_speed_p(void);
extern int ITc_inm_wifi_ap_is_favorite_p(void);
extern int ITc_inm_wifi_ap_is_passpoint_p(void);
extern int ITc_inm_wifi_ap_get_security_type_p(void);
extern int ITc_inm_wifi_ap_get_encryption_type_p(void);
extern int ITc_inm_wifi_ap_is_passphrase_required_p(void);
extern int ITc_inm_wifi_ap_is_wps_supported_p(void);
extern int ITc_inm_wifi_ap_get_disconnect_reason_p(void);
extern int ITc_inm_wifi_ap_get_assoc_status_code_p(void);
extern int ITc_inm_wifi_ap_foreach_vsie_p(void);
extern int ITc_inm_foreach_link_p(void);
extern int ITc_inm_connection_get_link_p(void);
extern int ITc_inm_link_destroy_p(void);
extern int ITc_inm_link_clone_p(void);
extern int ITc_inm_link_get_interface_name_p(void);
extern int ITc_inm_link_get_flags_p(void);
extern int ITc_inm_link_get_operation_state_p(void);
extern int ITc_inm_link_get_received_bytes_p(void);
extern int ITc_inm_link_get_sent_bytes_p(void);
extern int ITc_inm_link_foreach_address_destroy_p(void);
extern int ITc_inm_link_address_clone_p(void);
extern int ITc_inm_link_address_get_family_p(void);
extern int ITc_inm_link_address_get_prefix_length_p(void);
extern int ITc_inm_link_address_get_scope_p(void);
extern int ITc_inm_link_address_get_string_p(void);
extern int ITc_inm_link_foreach_route_p(void);
extern int ITc_inm_link_route_destroy_p(void);
extern int ITc_inm_link_route_clone_p(void);
extern int ITc_inm_link_route_get_destination_p(void);
extern int ITc_inm_link_route_get_gateway_p(void);
extern int ITc_inm_link_route_get_interface_p(void);
extern int ITc_inm_link_route_is_default_p(void);
extern int ITc_inm_link_route_get_type_p(void);
extern int ITc_inm_refresh_links_p(void);
extern int ITc_inm_arp_request_set_get_packet_interval_p(void);
extern int ITc_inm_arp_request_start_stop_p(void);
extern int ITc_inm_default_gateway_start_stop_checking_p(void);
extern int ITc_inm_default_dns_lookup_check_p(void);
extern int ITc_inm_reachable_urls_add_remove_url_to_check_p(void);
extern int ITc_inm_reachable_urls_start_stop_checking_p(void);
extern int ITc_inm_reachable_urls_is_check_running_p(void);

testcase tc_array[] = {
	{"ITc_inm_link_foreach_address_destroy_p",ITc_inm_link_foreach_address_destroy_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_address_clone_p",ITc_inm_link_address_clone_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_address_get_family_p",ITc_inm_link_address_get_family_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_address_get_prefix_length_p",ITc_inm_link_address_get_prefix_length_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_address_get_scope_p",ITc_inm_link_address_get_scope_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_address_get_string_p",ITc_inm_link_address_get_string_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_foreach_route_p",ITc_inm_link_foreach_route_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_route_clone_p",ITc_inm_link_route_clone_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_route_get_destination_p",ITc_inm_link_route_get_destination_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_route_get_gateway_p",ITc_inm_link_route_get_gateway_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_route_get_interface_p",ITc_inm_link_route_get_interface_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_route_is_default_p",ITc_inm_link_route_is_default_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_route_get_type_p",ITc_inm_link_route_get_type_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_route_destroy_p",ITc_inm_link_route_destroy_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_get_ethernet_cable_state_p",ITc_inm_get_ethernet_cable_state_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_set_unset_ethernet_cable_state_changed_cb_p",ITc_inm_set_unset_ethernet_cable_state_changed_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_set_unset_wifi_module_state_changed_cb_p",ITc_inm_set_unset_wifi_module_state_changed_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_wifi_module_state_p",ITc_inm_get_wifi_module_state_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_set_unset_ip_conflict_cb_p",ITc_inm_set_unset_ip_conflict_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_ip_conflict_detect_is_enabled_p",ITc_inm_ip_conflict_detect_is_enabled_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_ip_conflict_state_p",ITc_inm_get_ip_conflict_state_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_statistics_p",ITc_inm_get_statistics_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_reset_statistics_p",ITc_inm_reset_statistics_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_set_unset_congestion_level_cb_p",ITc_inm_set_unset_congestion_level_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_congestion_level_p",ITc_inm_get_congestion_level_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_set_unset_retry_tx_rate_cb_p",ITc_inm_set_unset_retry_tx_rate_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_retry_tx_rate_p",ITc_inm_get_retry_tx_rate_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_set_unset_channel_interference_cb_p",ITc_inm_set_unset_channel_interference_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_channel_interference_p",ITc_inm_get_channel_interference_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_set_unset_cellular_state_changed_cb_p",ITc_inm_set_unset_cellular_state_changed_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_cellular_state_p",ITc_inm_get_cellular_state_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_set_unset_wifi_state_changed_cb_p",ITc_inm_set_unset_wifi_state_changed_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_wifi_state_p",ITc_inm_get_wifi_state_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_set_unset_ethernet_state_changed_cb_p",ITc_inm_set_unset_ethernet_state_changed_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_ethernet_state_p",ITc_inm_get_ethernet_state_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_current_connection_p",ITc_inm_get_current_connection_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_clone_destroy_p",ITc_inm_connection_clone_destroy_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_get_destroy_connection_iterator_p",ITc_inm_get_destroy_connection_iterator_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_iterator_next_p",ITc_inm_connection_iterator_next_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_id_p",ITc_inm_connection_get_id_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_name_p",ITc_inm_connection_get_name_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_type_p",ITc_inm_connection_get_type_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_network_interface_name_p",ITc_inm_connection_get_network_interface_name_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_state_p",ITc_inm_connection_get_state_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_ipv6_state_p",ITc_inm_connection_get_ipv6_state_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_ip_config_type_p",ITc_inm_connection_get_ip_config_type_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_ip_address_p",ITc_inm_connection_get_ip_address_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_subnet_mask_p",ITc_inm_connection_get_subnet_mask_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_gateway_address_p",ITc_inm_connection_get_gateway_address_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_dhcp_server_address_p",ITc_inm_connection_get_dhcp_server_address_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_dhcp_lease_duration_p",ITc_inm_connection_get_dhcp_lease_duration_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_dns_address_p",ITc_inm_connection_get_dns_address_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_proxy_type_p",ITc_inm_connection_get_proxy_type_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_proxy_address_p",ITc_inm_connection_get_proxy_address_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_dns_config_type_p",ITc_inm_connection_get_dns_config_type_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_get_prefix_length_p",ITc_inm_connection_get_prefix_length_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_refresh_p",ITc_inm_connection_refresh_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_connection_set_unset_state_changed_cb_p",ITc_inm_connection_set_unset_state_changed_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_set_unset_scan_state_changed_cb_p",ITc_inm_wifi_set_unset_scan_state_changed_cb_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_get_scan_state_p",ITc_inm_wifi_get_scan_state_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_get_connected_ap_p",ITc_inm_wifi_get_connected_ap_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_foreach_found_ap_p",ITc_inm_wifi_foreach_found_ap_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_essid_p",ITc_inm_wifi_ap_get_essid_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_raw_ssid_p",ITc_inm_wifi_ap_get_raw_ssid_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_bssid_p",ITc_inm_wifi_ap_get_bssid_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_rssi_p",ITc_inm_wifi_ap_get_rssi_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_rssi_level_p",ITc_inm_wifi_ap_get_rssi_level_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_frequency_p",ITc_inm_wifi_ap_get_frequency_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_max_speed_p",ITc_inm_wifi_ap_get_max_speed_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_is_favorite_p",ITc_inm_wifi_ap_is_favorite_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_is_passpoint_p",ITc_inm_wifi_ap_is_passpoint_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_security_type_p",ITc_inm_wifi_ap_get_security_type_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_encryption_type_p",ITc_inm_wifi_ap_get_encryption_type_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_is_passphrase_required_p",ITc_inm_wifi_ap_is_passphrase_required_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_is_wps_supported_p",ITc_inm_wifi_ap_is_wps_supported_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_disconnect_reason_p",ITc_inm_wifi_ap_get_disconnect_reason_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_get_assoc_status_code_p",ITc_inm_wifi_ap_get_assoc_status_code_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_wifi_ap_foreach_vsie_p",ITc_inm_wifi_ap_foreach_vsie_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_foreach_link_p",ITc_inm_foreach_link_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_connection_get_link_p",ITc_inm_connection_get_link_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_destroy_p",ITc_inm_link_destroy_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_clone_p",ITc_inm_link_clone_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_get_interface_name_p",ITc_inm_link_get_interface_name_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_get_flags_p",ITc_inm_link_get_flags_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_get_operation_state_p",ITc_inm_link_get_operation_state_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_get_received_bytes_p",ITc_inm_link_get_received_bytes_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_link_get_sent_bytes_p",ITc_inm_link_get_sent_bytes_p,ITs_inm_link_startup,ITs_inm_link_cleanup},
	{"ITc_inm_refresh_links_p",ITc_inm_refresh_links_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_arp_request_set_get_packet_interval_p",ITc_inm_arp_request_set_get_packet_interval_p,ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_arp_request_start_stop_p", ITc_inm_arp_request_start_stop_p, ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_default_gateway_start_stop_checking_p", ITc_inm_default_gateway_start_stop_checking_p, ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_default_dns_lookup_check_p", ITc_inm_default_dns_lookup_check_p, ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_reachable_urls_add_remove_url_to_check_p", ITc_inm_reachable_urls_add_remove_url_to_check_p, ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_reachable_urls_start_stop_checking_p", ITc_inm_reachable_urls_start_stop_checking_p, ITs_inm_startup,ITs_inm_cleanup},
	{"ITc_inm_reachable_urls_is_check_running_p", ITc_inm_reachable_urls_is_check_running_p, ITs_inm_startup,ITs_inm_cleanup},
	{NULL, NULL}
};

#endif // __TCT_INM-NATIVE_H__
