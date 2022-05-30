/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TCT_INTELLIGENT_NETWORK_MONITORING_NATIVE_H__
#define __TCT_INTELLIGENT_NETWORK_MONITORING_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_inm_startup(void);
extern void utc_inm_cleanup(void);

extern int utc_inm_set_ethernet_cable_state_changed_cb_n(void);
extern int utc_inm_unset_ethernet_cable_state_changed_cb_n(void);
extern int utc_inm_get_ethernet_cable_state_p(void);
extern int utc_inm_get_ethernet_cable_state_n(void);
extern int utc_inm_set_wifi_module_state_changed_cb_n(void);
extern int utc_inm_unset_wifi_module_state_changed_cb_n(void);
extern int utc_inm_get_wifi_module_state_p(void);
extern int utc_inm_get_wifi_module_state_n(void);
extern int utc_inm_set_ip_conflict_cb_n(void);
extern int utc_inm_unset_ip_conflict_cb_n(void);
extern int utc_inm_ip_conflict_detect_is_enabled_p(void);
extern int utc_inm_ip_conflict_detect_is_enabled_n(void);
extern int utc_inm_get_ip_conflict_state_p(void);
extern int utc_inm_get_ip_conflict_state_n(void);
extern int utc_inm_get_statistics_p(void);
extern int utc_inm_get_statistics_n(void);
extern int utc_inm_reset_statistics_p(void);
extern int utc_inm_reset_statistics_n(void);
extern int utc_inm_set_congestion_level_cb_n(void);
extern int utc_inm_unset_congestion_level_cb_n(void);
extern int utc_inm_get_congestion_level_p(void);
extern int utc_inm_get_congestion_level_n(void);
extern int utc_inm_set_retry_tx_rate_cb_n(void);
extern int utc_inm_unset_retry_tx_rate_cb_n(void);
extern int utc_inm_get_retry_tx_rate_p(void);
extern int utc_inm_get_retry_tx_rate_n(void);
extern int utc_inm_set_channel_interference_cb_n(void);
extern int utc_inm_unset_channel_interference_cb_n(void);
extern int utc_inm_get_channel_interference_p(void);
extern int utc_inm_get_channel_interference_n(void);
extern int utc_inm_set_cellular_state_changed_cb_n(void);
extern int utc_inm_unset_cellular_state_changed_cb_n(void);
extern int utc_inm_get_cellular_state_p(void);
extern int utc_inm_get_cellular_state_n(void);
extern int utc_inm_set_wifi_state_changed_cb_n(void);
extern int utc_inm_unset_wifi_state_changed_cb_n(void);
extern int utc_inm_get_wifi_state_p(void);
extern int utc_inm_get_wifi_state_n(void);
extern int utc_inm_set_ethernet_state_changed_cb_n(void);
extern int utc_inm_unset_ethernet_state_changed_cb_n(void);
extern int utc_inm_get_ethernet_state_p(void);
extern int utc_inm_get_ethernet_state_n(void);
extern int utc_inm_get_current_connection_p(void);
extern int utc_inm_get_current_connection_n(void);
extern int utc_inm_connection_destroy_p(void);
extern int utc_inm_connection_destroy_n(void);
extern int utc_inm_connection_clone_p(void);
extern int utc_inm_connection_clone_n(void);
extern int utc_inm_get_connection_iterator_p(void);
extern int utc_inm_get_connection_iterator_n(void);
extern int utc_inm_connection_iterator_next_p(void);
extern int utc_inm_connection_iterator_next_n(void);
extern int utc_inm_destroy_connection_iterator_p(void);
extern int utc_inm_destroy_connection_iterator_n(void);
extern int utc_inm_connection_get_id_p(void);
extern int utc_inm_connection_get_id_n(void);
extern int utc_inm_connection_get_name_p(void);
extern int utc_inm_connection_get_name_n(void);
extern int utc_inm_connection_get_type_p(void);
extern int utc_inm_connection_get_type_n(void);
extern int utc_inm_connection_get_network_interface_name_p(void);
extern int utc_inm_connection_get_network_interface_name_n(void);
extern int utc_inm_connection_get_state_p(void);
extern int utc_inm_connection_get_state_n(void);
extern int utc_inm_connection_get_ipv6_state_p(void);
extern int utc_inm_connection_get_ipv6_state_n(void);
extern int utc_inm_connection_get_ip_config_type_p(void);
extern int utc_inm_connection_get_ip_config_type_n(void);
extern int utc_inm_connection_get_ip_address_p(void);
extern int utc_inm_connection_get_ip_address_n(void);
extern int utc_inm_connection_get_subnet_mask_p(void);
extern int utc_inm_connection_get_subnet_mask_n(void);
extern int utc_inm_connection_get_gateway_address_p(void);
extern int utc_inm_connection_get_gateway_address_n(void);
extern int utc_inm_connection_get_dhcp_server_address_p(void);
extern int utc_inm_connection_get_dhcp_server_address_n(void);
extern int utc_inm_connection_get_dhcp_lease_duration_p(void);
extern int utc_inm_connection_get_dhcp_lease_duration_n(void);
extern int utc_inm_connection_get_dns_address_p(void);
extern int utc_inm_connection_get_dns_address_n(void);
extern int utc_inm_connection_get_proxy_type_p(void);
extern int utc_inm_connection_get_proxy_type_n(void);
extern int utc_inm_connection_get_proxy_address_p(void);
extern int utc_inm_connection_get_proxy_address_n(void);
extern int utc_inm_connection_get_dns_config_type_p(void);
extern int utc_inm_connection_get_dns_config_type_n(void);
extern int utc_inm_connection_get_prefix_length_p(void);
extern int utc_inm_connection_get_prefix_length_n(void);
extern int utc_inm_connection_set_state_changed_cb_n(void);
extern int utc_inm_connection_unset_state_changed_cb_n(void);
extern int utc_inm_wifi_set_scan_state_changed_cb_n(void);
extern int utc_inm_wifi_unset_scan_state_changed_cb_n(void);
extern int utc_inm_wifi_get_scan_state_p(void);
extern int utc_inm_wifi_get_scan_state_n(void);
extern int utc_inm_wifi_get_connected_ap_p(void);
extern int utc_inm_wifi_get_connected_ap_n(void);
extern int utc_inm_wifi_foreach_found_ap_p(void);
extern int utc_inm_wifi_foreach_found_ap_n(void);
extern int utc_inm_wifi_ap_get_essid_p(void);
extern int utc_inm_wifi_ap_get_essid_n(void);
extern int utc_inm_wifi_ap_get_raw_ssid_p(void);
extern int utc_inm_wifi_ap_get_raw_ssid_n(void);
extern int utc_inm_wifi_ap_get_bssid_p(void);
extern int utc_inm_wifi_ap_get_bssid_n(void);
extern int utc_inm_wifi_ap_get_rssi_p(void);
extern int utc_inm_wifi_ap_get_rssi_n(void);
extern int utc_inm_wifi_ap_get_rssi_level_p(void);
extern int utc_inm_wifi_ap_get_rssi_level_n(void);
extern int utc_inm_wifi_ap_get_frequency_p(void);
extern int utc_inm_wifi_ap_get_frequency_n(void);
extern int utc_inm_wifi_ap_get_max_speed_p(void);
extern int utc_inm_wifi_ap_get_max_speed_n(void);
extern int utc_inm_wifi_ap_is_favorite_p(void);
extern int utc_inm_wifi_ap_is_favorite_n(void);
extern int utc_inm_wifi_ap_is_passpoint_p(void);
extern int utc_inm_wifi_ap_is_passpoint_n(void);
extern int utc_inm_wifi_ap_get_security_type_p(void);
extern int utc_inm_wifi_ap_get_security_type_n(void);
extern int utc_inm_wifi_ap_get_encryption_type_p(void);
extern int utc_inm_wifi_ap_get_encryption_type_n(void);
extern int utc_inm_wifi_ap_is_passphrase_required_p(void);
extern int utc_inm_wifi_ap_is_passphrase_required_n(void);
extern int utc_inm_wifi_ap_is_wps_supported_p(void);
extern int utc_inm_wifi_ap_is_wps_supported_n(void);
extern int utc_inm_wifi_ap_get_disconnect_reason_p(void);
extern int utc_inm_wifi_ap_get_disconnect_reason_n(void);
extern int utc_inm_wifi_ap_get_assoc_status_code_p(void);
extern int utc_inm_wifi_ap_get_assoc_status_code_n(void);
extern int utc_inm_wifi_ap_foreach_vsie_p(void);
extern int utc_inm_wifi_ap_foreach_vsie_n(void);

extern int utc_inm_inm_foreach_link_p(void);
extern int utc_inm_inm_foreach_link_n(void);
extern int utc_inm_connection_get_link_p(void);
extern int utc_inm_connection_get_link_n(void);
extern int utc_inm_refresh_links_p(void);
extern int utc_inm_refresh_links_n(void);

extern void utc_inm_link_startup(void);
extern void utc_inm_link_cleanup(void);
extern int utc_inm_link_destroy_p(void);
extern int utc_inm_link_destroy_n(void);
extern int utc_inm_link_clone_p(void);
extern int utc_inm_link_clone_n(void);
extern int utc_inm_link_get_interface_name_p(void);
extern int utc_inm_link_get_interface_name_n(void);
extern int utc_inm_link_get_flags_p(void);
extern int utc_inm_link_get_flags_n(void);
extern int utc_inm_link_get_operation_state_p(void);
extern int utc_inm_link_get_operation_state_n(void);
extern int utc_inm_link_get_received_bytes_p(void);
extern int utc_inm_link_get_received_bytes_n(void);
extern int utc_inm_link_get_sent_bytes_p(void);
extern int utc_inm_link_get_sent_bytes_n(void);
extern int utc_inm_link_foreach_address_p(void);
extern int utc_inm_link_foreach_address_n(void);
extern int utc_inm_link_foreach_route_p(void);
extern int utc_inm_link_foreach_route_n(void);

extern void utc_inm_link_address_startup(void);
extern void utc_inm_link_address_cleanup(void);
extern int utc_inm_link_address_destroy_p(void);
extern int utc_inm_link_address_destroy_n(void);
extern int utc_inm_link_address_clone_p(void);
extern int utc_inm_link_address_clone_n(void);
extern int utc_inm_link_address_get_family_p(void);
extern int utc_inm_link_address_get_family_n(void);
extern int utc_inm_link_address_get_prefix_length_p(void);
extern int utc_inm_link_address_get_family_n(void);
extern int utc_inm_link_address_get_scope_p(void);
extern int utc_inm_link_address_get_scope_n(void);
extern int utc_inm_link_address_get_string_p(void);
extern int utc_inm_link_address_get_string_n(void);

extern void utc_inm_link_route_startup(void);
extern void utc_inm_link_route_cleanup(void);
extern int utc_inm_link_route_destroy_p(void);
extern int utc_inm_link_route_destroy_n(void);
extern int utc_inm_link_route_clone_p(void);
extern int utc_inm_link_route_clone_n(void);
extern int utc_inm_link_route_get_destination_p(void);
extern int utc_inm_link_route_get_destination_n(void);
extern int utc_inm_link_route_get_gateway_p(void);
extern int utc_inm_link_route_get_gateway_n(void);
extern int utc_inm_link_route_get_interface_p(void);
extern int utc_inm_link_route_get_interface_n(void);
extern int utc_inm_link_route_is_default_p(void);
extern int utc_inm_link_route_is_default_n(void);
extern int utc_inm_link_route_get_type_p(void);
extern int utc_inm_link_route_get_type_n(void);

extern void utc_inm_active_startup(void);
extern void utc_inm_active_cleanup(void);
extern int utc_inm_arp_request_set_packet_interval_p(void);
extern int utc_inm_arp_request_set_packet_interval_n(void);
extern int utc_inm_arp_request_get_packet_interval_p(void);
extern int utc_inm_arp_request_get_packet_interval_n(void);
extern int utc_inm_arp_request_start_stop_p(void);
extern int utc_inm_arp_request_start_n(void);
extern int utc_inm_arp_request_stop_n(void);
extern int utc_inm_arp_request_start_stop_n(void);
extern int utc_inm_default_gateway_start_stop_checking_p(void);
extern int utc_inm_default_gateway_start_checking_n(void);
extern int utc_inm_default_gateway_stop_checking_n(void);
extern int utc_inm_default_dns_lookup_check_p(void);
extern int utc_inm_default_dns_lookup_check_n(void);
extern int utc_inm_reachable_urls_add_remove_url_to_check_p(void);
extern int utc_inm_reachable_urls_add_url_to_check_n(void);
extern int utc_inm_reachable_urls_remove_url_to_check_n(void);
extern int utc_inm_reachable_default_urls_start_stop_checking_p(void);
extern int utc_inm_reachable_urls_start_checking_n(void);
extern int utc_inm_reachable_user_urls_start_stop_checking_p(void);
extern int utc_inm_reachable_urls_stop_checking_n(void);
extern int utc_inm_reachable_urls_is_check_running_p(void);
extern int utc_inm_reachable_urls_is_check_running_n(void);

testcase tc_array[] = {
    {"utc_inm_set_ethernet_cable_state_changed_cb_n", utc_inm_set_ethernet_cable_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_unset_ethernet_cable_state_changed_cb_n", utc_inm_unset_ethernet_cable_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_ethernet_cable_state_p", utc_inm_get_ethernet_cable_state_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_ethernet_cable_state_n", utc_inm_get_ethernet_cable_state_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_set_wifi_module_state_changed_cb_n", utc_inm_set_wifi_module_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_unset_wifi_module_state_changed_cb_n", utc_inm_unset_wifi_module_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_wifi_module_state_p", utc_inm_get_wifi_module_state_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_wifi_module_state_n", utc_inm_get_wifi_module_state_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_set_ip_conflict_cb_n", utc_inm_set_ip_conflict_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_unset_ip_conflict_cb_n", utc_inm_unset_ip_conflict_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_ip_conflict_detect_is_enabled_p", utc_inm_ip_conflict_detect_is_enabled_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_ip_conflict_detect_is_enabled_n", utc_inm_ip_conflict_detect_is_enabled_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_ip_conflict_state_p", utc_inm_get_ip_conflict_state_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_ip_conflict_state_n", utc_inm_get_ip_conflict_state_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_statistics_p", utc_inm_get_statistics_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_statistics_n", utc_inm_get_statistics_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_reset_statistics_p", utc_inm_reset_statistics_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_reset_statistics_n", utc_inm_reset_statistics_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_set_congestion_level_cb_n", utc_inm_set_congestion_level_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_unset_congestion_level_cb_n", utc_inm_unset_congestion_level_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_congestion_level_p", utc_inm_get_congestion_level_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_congestion_level_n", utc_inm_get_congestion_level_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_set_retry_tx_rate_cb_n", utc_inm_set_retry_tx_rate_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_unset_retry_tx_rate_cb_n", utc_inm_unset_retry_tx_rate_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_retry_tx_rate_p", utc_inm_get_retry_tx_rate_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_retry_tx_rate_n", utc_inm_get_retry_tx_rate_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_set_channel_interference_cb_n", utc_inm_set_channel_interference_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_unset_channel_interference_cb_n", utc_inm_unset_channel_interference_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_channel_interference_p", utc_inm_get_channel_interference_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_channel_interference_n", utc_inm_get_channel_interference_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_set_cellular_state_changed_cb_n", utc_inm_set_cellular_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_unset_cellular_state_changed_cb_n", utc_inm_unset_cellular_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_cellular_state_p", utc_inm_get_cellular_state_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_cellular_state_n", utc_inm_get_cellular_state_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_set_wifi_state_changed_cb_n", utc_inm_set_wifi_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_unset_wifi_state_changed_cb_n", utc_inm_unset_wifi_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_wifi_state_p", utc_inm_get_wifi_state_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_wifi_state_n", utc_inm_get_wifi_state_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_set_ethernet_state_changed_cb_n", utc_inm_set_ethernet_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_unset_ethernet_state_changed_cb_n", utc_inm_unset_ethernet_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_ethernet_state_p", utc_inm_get_ethernet_state_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_ethernet_state_n", utc_inm_get_ethernet_state_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_current_connection_p", utc_inm_get_current_connection_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_current_connection_n", utc_inm_get_current_connection_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_destroy_p", utc_inm_connection_destroy_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_destroy_n", utc_inm_connection_destroy_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_clone_p", utc_inm_connection_clone_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_clone_n", utc_inm_connection_clone_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_connection_iterator_p", utc_inm_get_connection_iterator_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_get_connection_iterator_n", utc_inm_get_connection_iterator_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_iterator_next_p", utc_inm_connection_iterator_next_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_iterator_next_n", utc_inm_connection_iterator_next_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_destroy_connection_iterator_p", utc_inm_destroy_connection_iterator_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_destroy_connection_iterator_n", utc_inm_destroy_connection_iterator_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_id_p", utc_inm_connection_get_id_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_id_n", utc_inm_connection_get_id_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_name_p", utc_inm_connection_get_name_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_name_n", utc_inm_connection_get_name_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_type_p", utc_inm_connection_get_type_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_type_n", utc_inm_connection_get_type_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_network_interface_name_p", utc_inm_connection_get_network_interface_name_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_network_interface_name_n", utc_inm_connection_get_network_interface_name_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_state_p", utc_inm_connection_get_state_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_state_n", utc_inm_connection_get_state_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_ipv6_state_p", utc_inm_connection_get_ipv6_state_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_ipv6_state_n", utc_inm_connection_get_ipv6_state_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_ip_config_type_p", utc_inm_connection_get_ip_config_type_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_ip_config_type_n", utc_inm_connection_get_ip_config_type_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_ip_address_p", utc_inm_connection_get_ip_address_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_ip_address_n", utc_inm_connection_get_ip_address_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_subnet_mask_p", utc_inm_connection_get_subnet_mask_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_subnet_mask_n", utc_inm_connection_get_subnet_mask_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_gateway_address_p", utc_inm_connection_get_gateway_address_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_gateway_address_n", utc_inm_connection_get_gateway_address_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_dhcp_server_address_p", utc_inm_connection_get_dhcp_server_address_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_dhcp_server_address_n", utc_inm_connection_get_dhcp_server_address_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_dhcp_lease_duration_p", utc_inm_connection_get_dhcp_lease_duration_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_dhcp_lease_duration_n", utc_inm_connection_get_dhcp_lease_duration_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_dns_address_p", utc_inm_connection_get_dns_address_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_dns_address_n", utc_inm_connection_get_dns_address_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_proxy_type_p", utc_inm_connection_get_proxy_type_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_proxy_type_n", utc_inm_connection_get_proxy_type_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_proxy_address_p", utc_inm_connection_get_proxy_address_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_proxy_address_n", utc_inm_connection_get_proxy_address_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_dns_config_type_p", utc_inm_connection_get_proxy_address_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_dns_config_type_n", utc_inm_connection_get_dns_config_type_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_prefix_length_p", utc_inm_connection_get_prefix_length_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_prefix_length_n", utc_inm_connection_get_prefix_length_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_set_state_changed_cb_n", utc_inm_connection_set_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_unset_state_changed_cb_n", utc_inm_connection_unset_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_set_scan_state_changed_cb_n", utc_inm_wifi_set_scan_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_unset_scan_state_changed_cb_n", utc_inm_wifi_unset_scan_state_changed_cb_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_get_scan_state_p", utc_inm_wifi_get_scan_state_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_get_scan_state_n", utc_inm_wifi_get_scan_state_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_get_connected_ap_p", utc_inm_wifi_get_connected_ap_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_get_connected_ap_n", utc_inm_wifi_get_connected_ap_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_foreach_found_ap_p", utc_inm_wifi_foreach_found_ap_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_foreach_found_ap_n", utc_inm_wifi_foreach_found_ap_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_essid_p", utc_inm_wifi_ap_get_essid_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_essid_n", utc_inm_wifi_ap_get_essid_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_raw_ssid_p", utc_inm_wifi_ap_get_raw_ssid_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_raw_ssid_n", utc_inm_wifi_ap_get_raw_ssid_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_bssid_p", utc_inm_wifi_ap_get_bssid_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_bssid_n", utc_inm_wifi_ap_get_bssid_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_rssi_p", utc_inm_wifi_ap_get_rssi_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_rssi_n", utc_inm_wifi_ap_get_rssi_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_rssi_level_p", utc_inm_wifi_ap_get_rssi_level_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_rssi_level_n", utc_inm_wifi_ap_get_rssi_level_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_frequency_p", utc_inm_wifi_ap_get_frequency_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_frequency_n", utc_inm_wifi_ap_get_frequency_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_max_speed_p", utc_inm_wifi_ap_get_max_speed_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_max_speed_n", utc_inm_wifi_ap_get_max_speed_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_is_favorite_p", utc_inm_wifi_ap_is_favorite_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_is_favorite_n", utc_inm_wifi_ap_is_favorite_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_is_passpoint_p", utc_inm_wifi_ap_is_passpoint_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_is_passpoint_n", utc_inm_wifi_ap_is_passpoint_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_security_type_p", utc_inm_wifi_ap_get_security_type_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_security_type_n", utc_inm_wifi_ap_get_security_type_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_encryption_type_p", utc_inm_wifi_ap_get_encryption_type_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_encryption_type_n", utc_inm_wifi_ap_get_encryption_type_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_is_passphrase_required_p", utc_inm_wifi_ap_is_passphrase_required_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_is_passphrase_required_n", utc_inm_wifi_ap_is_passphrase_required_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_is_wps_supported_p", utc_inm_wifi_ap_is_wps_supported_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_is_wps_supported_n", utc_inm_wifi_ap_is_wps_supported_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_disconnect_reason_p", utc_inm_wifi_ap_get_disconnect_reason_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_disconnect_reason_n", utc_inm_wifi_ap_get_disconnect_reason_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_assoc_status_code_p", utc_inm_wifi_ap_get_assoc_status_code_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_get_assoc_status_code_n", utc_inm_wifi_ap_get_assoc_status_code_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_foreach_vsie_p", utc_inm_wifi_ap_foreach_vsie_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_wifi_ap_foreach_vsie_n", utc_inm_wifi_ap_foreach_vsie_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_inm_foreach_link_p", utc_inm_inm_foreach_link_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_inm_foreach_link_n", utc_inm_inm_foreach_link_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_link_p", utc_inm_connection_get_link_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_connection_get_link_n", utc_inm_connection_get_link_n, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_refresh_links_p",  utc_inm_refresh_links_p, utc_inm_startup, utc_inm_cleanup},
    {"utc_inm_refresh_links_n", utc_inm_refresh_links_n, utc_inm_startup, utc_inm_cleanup},

    {"utc_inm_link_destroy_p", utc_inm_link_destroy_p, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_destroy_n", utc_inm_link_destroy_n, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_clone_p", utc_inm_link_clone_p, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_clone_n", utc_inm_link_clone_n, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_get_interface_name_p", utc_inm_link_get_interface_name_p, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_get_interface_name_n", utc_inm_link_get_interface_name_n, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_get_flags_p", utc_inm_link_get_flags_p, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_get_flags_n", utc_inm_link_get_flags_n, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_get_operation_state_p", utc_inm_link_get_operation_state_p, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_get_operation_state_n", utc_inm_link_get_operation_state_n, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_get_received_bytes_p", utc_inm_link_get_received_bytes_p, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_get_received_bytes_n", utc_inm_link_get_received_bytes_n, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_get_sent_bytes_p", utc_inm_link_get_sent_bytes_p, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_get_sent_bytes_n", utc_inm_link_get_sent_bytes_n, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_foreach_address_p", utc_inm_link_foreach_address_p, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_foreach_address_n", utc_inm_link_foreach_address_n, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_foreach_route_p", utc_inm_link_foreach_route_p, utc_inm_link_startup, utc_inm_link_cleanup},
    {"utc_inm_link_foreach_route_n", utc_inm_link_foreach_route_n, utc_inm_link_startup, utc_inm_link_cleanup},

    {"utc_inm_link_address_destroy_p", utc_inm_link_address_destroy_p, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_destroy_n", utc_inm_link_address_destroy_n, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_clone_p", utc_inm_link_address_clone_p, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_clone_n", utc_inm_link_address_clone_n, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_get_family_p", utc_inm_link_address_get_family_p, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_get_family_n", utc_inm_link_address_get_family_n, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_get_prefix_length_p", utc_inm_link_address_get_prefix_length_p, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_get_family_n", utc_inm_link_address_get_family_n, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_get_scope_p", utc_inm_link_address_get_scope_p, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_get_scope_n", utc_inm_link_address_get_scope_n, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_get_string_p", utc_inm_link_address_get_string_p, utc_inm_link_address_startup, utc_inm_link_address_cleanup},
    {"utc_inm_link_address_get_string_n", utc_inm_link_address_get_string_n, utc_inm_link_address_startup, utc_inm_link_address_cleanup},

    {"utc_inm_link_route_destroy_p", utc_inm_link_route_destroy_p, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_destroy_n", utc_inm_link_route_destroy_n, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_clone_p", utc_inm_link_route_clone_p, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_clone_n", utc_inm_link_route_clone_n, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_get_destination_p", utc_inm_link_route_get_destination_p, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_get_destination_n", utc_inm_link_route_get_destination_n, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_get_gateway_p", utc_inm_link_route_get_gateway_p, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_get_gateway_n", utc_inm_link_route_get_gateway_n, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_get_interface_p", utc_inm_link_route_get_interface_p, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_get_interface_n", utc_inm_link_route_get_interface_n, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_is_default_p", utc_inm_link_route_is_default_p, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_is_default_n", utc_inm_link_route_is_default_n, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_get_type_p", utc_inm_link_route_get_type_p, utc_inm_link_route_startup, utc_inm_link_route_cleanup},
    {"utc_inm_link_route_get_type_n", utc_inm_link_route_get_type_n, utc_inm_link_route_startup, utc_inm_link_route_cleanup},

    {"utc_inm_arp_request_set_packet_interval_p",  utc_inm_arp_request_set_packet_interval_p, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_arp_request_set_packet_interval_n", utc_inm_arp_request_set_packet_interval_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_arp_request_get_packet_interval_p",  utc_inm_arp_request_get_packet_interval_p, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_arp_request_get_packet_interval_n", utc_inm_arp_request_get_packet_interval_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_arp_request_start_stop_p",  utc_inm_arp_request_start_stop_p, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_arp_request_start_n", utc_inm_arp_request_start_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_arp_request_stop_n", utc_inm_arp_request_stop_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_arp_request_start_stop_n",  utc_inm_arp_request_start_stop_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_default_gateway_start_stop_checking_p", utc_inm_default_gateway_start_stop_checking_p, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_default_gateway_start_checking_n",  utc_inm_default_gateway_start_checking_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_default_gateway_stop_checking_n",  utc_inm_default_gateway_stop_checking_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_default_dns_lookup_check_p",  utc_inm_default_dns_lookup_check_p, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_default_dns_lookup_check_n",  utc_inm_default_dns_lookup_check_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_reachable_urls_add_remove_url_to_check_p",  utc_inm_reachable_urls_add_remove_url_to_check_p, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_reachable_urls_add_url_to_check_n",  utc_inm_reachable_urls_add_url_to_check_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_reachable_urls_remove_url_to_check_n",  utc_inm_reachable_urls_remove_url_to_check_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_reachable_default_urls_start_stop_checking_p",  utc_inm_reachable_default_urls_start_stop_checking_p, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_reachable_urls_start_checking_n",  utc_inm_reachable_urls_start_checking_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_reachable_user_urls_start_stop_checking_p", utc_inm_reachable_user_urls_start_stop_checking_p, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_reachable_urls_stop_checking_n",  utc_inm_reachable_urls_stop_checking_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_reachable_urls_is_check_running_p", utc_inm_reachable_urls_is_check_running_p, utc_inm_active_startup, utc_inm_active_cleanup},
    {"utc_inm_reachable_urls_is_check_running_n",  utc_inm_reachable_urls_is_check_running_n, utc_inm_active_startup, utc_inm_active_cleanup},
    {NULL, NULL}
};


#endif // __TCT_INTELLIGENT_NETWORk_MONITORING_NATIVE_H__
