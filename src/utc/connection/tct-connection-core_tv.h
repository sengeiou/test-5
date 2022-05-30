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
#ifndef __TCT_CONNECTION_CORE_H__
#define __TCT_CONNECTION_CORE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_connection_profile_startup(void);
extern void utc_connection_profile_cleanup(void);
extern void utc_network_connection_startup(void);
extern void utc_network_connection_cleanup(void);

extern int utc_connection_profile_create_p(void);
extern int utc_connection_profile_create_n(void);
extern int utc_connection_profile_clone_p(void);
extern int utc_connection_profile_clone_n(void);
extern int utc_connection_profile_get_name_p(void);
extern int utc_connection_profile_get_name_n(void);
extern int utc_connection_profile_get_id_p(void);
extern int utc_connection_profile_get_id_n(void);
extern int utc_connection_profile_get_type_p(void);
extern int utc_connection_profile_get_type_n(void);
extern int utc_connection_profile_get_network_interface_name_p(void);
extern int utc_connection_profile_get_network_interface_name_n(void);
extern int utc_connection_profile_get_state_p(void);
extern int utc_connection_profile_get_state_n(void);
extern int utc_connection_profile_get_ip_config_type_p(void);
extern int utc_connection_profile_get_ip_config_type_n(void);
extern int utc_connection_profile_get_ip_address_p(void);
extern int utc_connection_profile_get_ip_address_n(void);
extern int utc_connection_profile_get_subnet_mask_p(void);
extern int utc_connection_profile_get_subnet_mask_n(void);
extern int utc_connection_profile_get_gateway_address_p(void);
extern int utc_connection_profile_get_gateway_address_n(void);
extern int utc_connection_profile_get_dhcp_server_address_p(void);
extern int utc_connection_profile_get_dhcp_server_address_n(void);
extern int utc_connection_profile_get_dhcp_lease_duration_p(void);
extern int utc_connection_profile_get_dhcp_lease_duration_n(void);
extern int utc_connection_profile_get_dns_address_p(void);
extern int utc_connection_profile_get_dns_address_n(void);
extern int utc_connection_profile_get_proxy_type_p(void);
extern int utc_connection_profile_get_proxy_type_n(void);
extern int utc_connection_profile_get_proxy_address_p(void);
extern int utc_connection_profile_get_proxy_address_n(void);
extern int utc_connection_profile_set_ip_config_type_p(void);
extern int utc_connection_profile_set_ip_config_type_n(void);
extern int utc_connection_profile_set_ip_address_p(void);
extern int utc_connection_profile_set_ip_address_n(void);
extern int utc_connection_profile_set_subnet_mask_p(void);
extern int utc_connection_profile_set_subnet_mask_n(void);
extern int utc_connection_profile_set_gateway_address_p(void);
extern int utc_connection_profile_set_gateway_address_n(void);
extern int utc_connection_profile_set_dns_address_p(void);
extern int utc_connection_profile_set_dns_address_n(void);
extern int utc_connection_profile_set_proxy_type_p(void);
extern int utc_connection_profile_set_proxy_type_n(void);
extern int utc_connection_profile_set_proxy_address_p(void);
extern int utc_connection_profile_set_proxy_address_n(void);
extern int utc_connection_profile_set_state_changed_cb_p(void);
extern int utc_connection_profile_set_state_changed_cb_n(void);
extern int utc_connection_profile_unset_state_changed_cb_p(void);
extern int utc_connection_profile_unset_state_changed_cb_n(void);
extern int utc_connection_profile_set_cellular_service_type_p(void);
extern int utc_connection_profile_set_cellular_service_type_n(void);
extern int utc_connection_profile_set_cellular_apn_p(void);
extern int utc_connection_profile_set_cellular_apn_n(void);
extern int utc_connection_profile_set_cellular_auth_info_p(void);
extern int utc_connection_profile_set_cellular_auth_info_n(void);
extern int utc_connection_profile_set_cellular_home_url_p(void);
extern int utc_connection_profile_set_cellular_home_url_n(void);
extern int utc_connection_profile_set_cellular_pdn_type_p(void);
extern int utc_connection_profile_set_cellular_pdn_type_n(void);
extern int utc_connection_profile_set_cellular_roam_pdn_type_p(void);
extern int utc_connection_profile_set_cellular_roam_pdn_type_n(void);
extern int utc_connection_profile_get_cellular_service_type_p(void);
extern int utc_connection_profile_get_cellular_service_type_n(void);
extern int utc_connection_profile_get_cellular_apn_p(void);
extern int utc_connection_profile_get_cellular_apn_n(void);
extern int utc_connection_profile_get_cellular_auth_info_p(void);
extern int utc_connection_profile_get_cellular_auth_info_n(void);
extern int utc_connection_profile_get_cellular_home_url_p(void);
extern int utc_connection_profile_get_cellular_home_url_n(void);
extern int utc_connection_profile_get_cellular_pdn_type_p(void);
extern int utc_connection_profile_get_cellular_pdn_type_n(void);
extern int utc_connection_profile_get_cellular_roam_pdn_type_p(void);
extern int utc_connection_profile_get_cellular_roam_pdn_type_n(void);
extern int utc_connection_profile_is_cellular_roaming_p(void);
extern int utc_connection_profile_is_cellular_roaming_n(void);
extern int utc_connection_profile_is_cellular_hidden_p(void);
extern int utc_connection_profile_is_cellular_hidden_n(void);
extern int utc_connection_profile_is_cellular_editable_p(void);
extern int utc_connection_profile_is_cellular_editable_n(void);
extern int utc_connection_profile_is_cellular_default_p(void);
extern int utc_connection_profile_is_cellular_default_n(void);
extern int utc_connection_profile_refresh_p(void);
extern int utc_connection_profile_refresh_n(void);
extern int utc_connection_profile_get_wifi_essid_p(void);
extern int utc_connection_profile_get_wifi_essid_n(void);
extern int utc_connection_profile_get_wifi_bssid_p(void);
extern int utc_connection_profile_get_wifi_bssid_n(void);
extern int utc_connection_profile_get_wifi_rssi_p(void);
extern int utc_connection_profile_get_wifi_rssi_n(void);
extern int utc_connection_profile_get_wifi_frequency_p(void);
extern int utc_connection_profile_get_wifi_frequency_n(void);
extern int utc_connection_profile_get_wifi_max_speed_p(void);
extern int utc_connection_profile_get_wifi_max_speed_n(void);
extern int utc_connection_profile_get_wifi_security_type_p(void);
extern int utc_connection_profile_get_wifi_security_type_n(void);
extern int utc_connection_profile_get_wifi_encryption_type_p(void);
extern int utc_connection_profile_get_wifi_encryption_type_n(void);
extern int utc_connection_profile_is_wifi_passphrase_required_p(void);
extern int utc_connection_profile_is_wifi_passphrase_required_n(void);
extern int utc_connection_profile_set_wifi_passphrase_p(void);
extern int utc_connection_profile_set_wifi_passphrase_n(void);
extern int utc_connection_profile_is_wifi_wps_supported_p(void);
extern int utc_connection_profile_is_wifi_wps_supported_n(void);
extern int utc_connection_profile_get_ipv6_state_p(void);
extern int utc_connection_profile_get_ipv6_state_n(void);
extern int utc_connection_profile_get_prefix_length_p(void);
extern int utc_connection_profile_get_prefix_length_n(void);
extern int utc_connection_profile_set_prefix_length_p(void);
extern int utc_connection_profile_set_prefix_length_n(void);
extern int utc_connection_profile_get_dns_config_type_p(void);
extern int utc_connection_profile_get_dns_config_type_n(void);
extern int utc_connection_profile_set_dns_config_type_p(void);
extern int utc_connection_profile_set_dns_config_type_n(void);
extern int utc_connection_profile_destroy_p(void);
extern int utc_connection_profile_destroy_n(void);
extern int utc_connection_create_p(void);
extern int utc_connection_create_n(void);
extern int utc_connection_get_ip_address_p(void);
extern int utc_connection_get_ip_address_n(void);
extern int utc_connection_get_proxy_p(void);
extern int utc_connection_get_proxy_n(void);
extern int utc_connection_get_type_n(void);
extern int utc_connection_get_type_p(void);
extern int utc_connection_is_metered_network_n(void);
extern int utc_connection_is_metered_network_p(void);
extern int utc_connection_get_cellular_state_n(void);
extern int utc_connection_get_cellular_state_p(void);
extern int utc_connection_get_ethernet_state_n(void);
extern int utc_connection_get_ethernet_state_p(void);
extern int utc_connection_get_wifi_state_n(void);
extern int utc_connection_get_wifi_state_p(void);
extern int utc_connection_get_bt_state_n(void);
extern int utc_connection_get_bt_state_p(void);
extern int utc_connection_get_mac_address_n(void);
extern int utc_connection_get_mac_address_p(void);
extern int utc_connection_set_ethernet_cable_state_chaged_cb_n(void);
extern int utc_connection_unset_ethernet_cable_state_chaged_cb_n(void);
extern int utc_connection_get_ethernet_cable_state_n(void);
extern int utc_connection_get_ethernet_cable_state_p(void);
extern int utc_connection_get_current_profile_p(void);
extern int utc_connection_get_current_profile_n(void);
extern int utc_connection_get_default_cellular_service_profile_p(void);
extern int utc_connection_get_default_cellular_service_profile_n(void);
extern int utc_connection_set_default_cellular_service_profile_p(void);
extern int utc_connection_set_default_cellular_service_profile_n(void);
extern int utc_connection_set_default_cellular_service_profile_async_p(void);
extern int utc_connection_set_default_cellular_service_profile_async_n(void);
extern int utc_connection_set_type_changed_cb_n(void);
extern int utc_connection_set_type_changed_cb_p(void);
extern int utc_connection_unset_type_changed_cb_n(void);
extern int utc_connection_unset_type_changed_cb_p(void);
extern int utc_connection_set_ip_address_changed_cb_n(void);
extern int utc_connection_set_ip_address_changed_cb_p(void);
extern int utc_connection_unset_ip_address_changed_cb_n(void);
extern int utc_connection_unset_ip_address_changed_cb_p(void);
extern int utc_connection_set_proxy_address_changed_cb_n(void);
extern int utc_connection_set_proxy_address_changed_cb_p(void);
extern int utc_connection_unset_proxy_address_changed_cb_n(void);
extern int utc_connection_unset_proxy_address_changed_cb_p(void);
extern int utc_connection_get_statistics_p(void);
extern int utc_connection_get_statistics_n(void);
extern int utc_connection_reset_statistics_p(void);
extern int utc_connection_reset_statistics_n(void);
extern int utc_connection_add_route_n1(void);
extern int utc_connection_add_route_n2(void);
extern int utc_connection_remove_route_n1(void);
extern int utc_connection_remove_route_n2(void);
extern int utc_connection_add_route_ipv6_n1(void);
extern int utc_connection_add_route_ipv6_n2(void);
extern int utc_connection_remove_route_ipv6_n1(void);
extern int utc_connection_remove_route_ipv6_n2(void);
extern int utc_connection_add_route_entry_n1(void);
extern int utc_connection_add_route_entry_n2(void);
extern int utc_connection_remove_route_entry_n1(void);
extern int utc_connection_remove_route_entry_n2(void);
extern int utc_connection_get_profile_iterator_n(void);
extern int utc_connection_get_profile_iterator_p(void);
extern int utc_connection_destroy_profile_iterator_n(void);
extern int utc_connection_destroy_profile_iterator_p(void);
extern int utc_connection_profile_iterator_has_next_n(void);
extern int utc_connection_profile_iterator_has_next_p(void);
extern int utc_connection_profile_iterator_next_n(void);
extern int utc_connection_profile_iterator_next_p(void);
extern int utc_connection_add_profile_p(void);
extern int utc_connection_add_profile_n(void);
extern int utc_connection_close_profile_p(void);
extern int utc_connection_close_profile_n(void);
extern int utc_connection_update_profile_p(void);
extern int utc_connection_update_profile_n(void);
extern int utc_connection_remove_profile_p(void);
extern int utc_connection_remove_profile_n(void);
extern int utc_connection_open_profile_p(void);
extern int utc_connection_open_profile_n(void);
extern int utc_connection_reset_profile_p(void);
extern int utc_connection_reset_profile_n(void);
extern int utc_connection_foreach_ipv6_address_p(void);
extern int utc_connection_foreach_ipv6_address_n(void);
extern int utc_connection_set_ethernet_cable_state_changed_cb_n(void);
extern int utc_connection_unset_ethernet_cable_state_changed_cb_n(void);
extern int utc_connection_destroy_p(void);
extern int utc_connection_destroy_n(void);

testcase tc_array[] = {
    {"utc_connection_profile_create_p", utc_connection_profile_create_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_create_n", utc_connection_profile_create_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_clone_p", utc_connection_profile_clone_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_clone_n", utc_connection_profile_clone_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_name_p", utc_connection_profile_get_name_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_name_n", utc_connection_profile_get_name_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_id_p", utc_connection_profile_get_id_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_id_n", utc_connection_profile_get_id_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_type_p", utc_connection_profile_get_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_type_n", utc_connection_profile_get_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_network_interface_name_p", utc_connection_profile_get_network_interface_name_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_network_interface_name_n", utc_connection_profile_get_network_interface_name_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_state_p", utc_connection_profile_get_state_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_state_n", utc_connection_profile_get_state_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_ip_config_type_p", utc_connection_profile_get_ip_config_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_ip_config_type_n", utc_connection_profile_get_ip_config_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_ip_address_p", utc_connection_profile_get_ip_address_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_ip_address_n", utc_connection_profile_get_ip_address_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_subnet_mask_p", utc_connection_profile_get_subnet_mask_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_subnet_mask_n", utc_connection_profile_get_subnet_mask_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_gateway_address_p", utc_connection_profile_get_gateway_address_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_gateway_address_n", utc_connection_profile_get_gateway_address_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_dhcp_server_address_p", utc_connection_profile_get_dhcp_server_address_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_dhcp_server_address_n", utc_connection_profile_get_dhcp_server_address_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_dhcp_lease_duration_p", utc_connection_profile_get_dhcp_lease_duration_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_dhcp_lease_duration_n", utc_connection_profile_get_dhcp_lease_duration_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_dns_address_p", utc_connection_profile_get_dns_address_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_dns_address_n", utc_connection_profile_get_dns_address_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_proxy_type_p", utc_connection_profile_get_proxy_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_proxy_type_n", utc_connection_profile_get_proxy_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_proxy_address_p", utc_connection_profile_get_proxy_address_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_proxy_address_n", utc_connection_profile_get_proxy_address_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_ip_config_type_p", utc_connection_profile_set_ip_config_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_ip_config_type_n", utc_connection_profile_set_ip_config_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_ip_address_p", utc_connection_profile_set_ip_address_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_ip_address_n", utc_connection_profile_set_ip_address_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_subnet_mask_p", utc_connection_profile_set_subnet_mask_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_subnet_mask_n", utc_connection_profile_set_subnet_mask_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_gateway_address_p", utc_connection_profile_set_gateway_address_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_gateway_address_n", utc_connection_profile_set_gateway_address_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_dns_address_p", utc_connection_profile_set_dns_address_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_dns_address_n", utc_connection_profile_set_dns_address_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_proxy_type_p", utc_connection_profile_set_proxy_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_proxy_type_n", utc_connection_profile_set_proxy_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_proxy_address_p", utc_connection_profile_set_proxy_address_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_proxy_address_n", utc_connection_profile_set_proxy_address_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_state_changed_cb_p", utc_connection_profile_set_state_changed_cb_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_state_changed_cb_n", utc_connection_profile_set_state_changed_cb_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_unset_state_changed_cb_p", utc_connection_profile_unset_state_changed_cb_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_unset_state_changed_cb_n", utc_connection_profile_unset_state_changed_cb_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_service_type_p", utc_connection_profile_set_cellular_service_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_service_type_n", utc_connection_profile_set_cellular_service_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_apn_p", utc_connection_profile_set_cellular_apn_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_apn_n", utc_connection_profile_set_cellular_apn_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_auth_info_p", utc_connection_profile_set_cellular_auth_info_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_auth_info_n", utc_connection_profile_set_cellular_auth_info_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_home_url_p", utc_connection_profile_set_cellular_home_url_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_home_url_n", utc_connection_profile_set_cellular_home_url_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_pdn_type_p", utc_connection_profile_set_cellular_pdn_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_pdn_type_n", utc_connection_profile_set_cellular_pdn_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_roam_pdn_type_p", utc_connection_profile_set_cellular_roam_pdn_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_cellular_roam_pdn_type_n", utc_connection_profile_set_cellular_roam_pdn_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_service_type_p", utc_connection_profile_get_cellular_service_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_service_type_n", utc_connection_profile_get_cellular_service_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_apn_p", utc_connection_profile_get_cellular_apn_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_apn_n", utc_connection_profile_get_cellular_apn_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_auth_info_p", utc_connection_profile_get_cellular_auth_info_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_auth_info_n", utc_connection_profile_get_cellular_auth_info_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_home_url_p", utc_connection_profile_get_cellular_home_url_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_home_url_n", utc_connection_profile_get_cellular_home_url_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_pdn_type_p", utc_connection_profile_get_cellular_pdn_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_pdn_type_n", utc_connection_profile_get_cellular_pdn_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_roam_pdn_type_p", utc_connection_profile_get_cellular_roam_pdn_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_cellular_roam_pdn_type_n", utc_connection_profile_get_cellular_roam_pdn_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_cellular_roaming_p", utc_connection_profile_is_cellular_roaming_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_cellular_roaming_n", utc_connection_profile_is_cellular_roaming_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_cellular_hidden_p", utc_connection_profile_is_cellular_hidden_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_cellular_hidden_n", utc_connection_profile_is_cellular_hidden_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_cellular_editable_p", utc_connection_profile_is_cellular_editable_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_cellular_editable_n", utc_connection_profile_is_cellular_editable_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_cellular_default_p", utc_connection_profile_is_cellular_default_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_cellular_default_n", utc_connection_profile_is_cellular_default_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_refresh_p", utc_connection_profile_refresh_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_refresh_n", utc_connection_profile_refresh_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_essid_p", utc_connection_profile_get_wifi_essid_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_essid_n", utc_connection_profile_get_wifi_essid_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_bssid_p", utc_connection_profile_get_wifi_bssid_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_bssid_n", utc_connection_profile_get_wifi_bssid_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_rssi_p", utc_connection_profile_get_wifi_rssi_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_rssi_n", utc_connection_profile_get_wifi_rssi_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_frequency_p", utc_connection_profile_get_wifi_frequency_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_frequency_n", utc_connection_profile_get_wifi_frequency_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_max_speed_p", utc_connection_profile_get_wifi_max_speed_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_max_speed_n", utc_connection_profile_get_wifi_max_speed_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_security_type_p", utc_connection_profile_get_wifi_security_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_security_type_n", utc_connection_profile_get_wifi_security_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_encryption_type_p", utc_connection_profile_get_wifi_encryption_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_wifi_encryption_type_n", utc_connection_profile_get_wifi_encryption_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_wifi_passphrase_required_p", utc_connection_profile_is_wifi_passphrase_required_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_wifi_passphrase_required_n", utc_connection_profile_is_wifi_passphrase_required_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_wifi_passphrase_p", utc_connection_profile_set_wifi_passphrase_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_wifi_passphrase_n", utc_connection_profile_set_wifi_passphrase_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_is_wifi_wps_supported_p", utc_connection_profile_is_wifi_wps_supported_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
	{"utc_connection_profile_is_wifi_wps_supported_n", utc_connection_profile_is_wifi_wps_supported_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_ipv6_state_p", utc_connection_profile_get_ipv6_state_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_ipv6_state_n", utc_connection_profile_get_ipv6_state_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_prefix_length_p", utc_connection_profile_get_prefix_length_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_prefix_length_n", utc_connection_profile_get_prefix_length_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_prefix_length_p", utc_connection_profile_set_prefix_length_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_prefix_length_n", utc_connection_profile_set_prefix_length_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_dns_config_type_p", utc_connection_profile_get_dns_config_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_get_dns_config_type_n", utc_connection_profile_get_dns_config_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_dns_config_type_p", utc_connection_profile_set_dns_config_type_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_set_dns_config_type_n", utc_connection_profile_set_dns_config_type_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_destroy_p", utc_connection_profile_destroy_p, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_profile_destroy_n", utc_connection_profile_destroy_n, utc_connection_profile_startup, utc_connection_profile_cleanup},
    {"utc_connection_create_p", utc_connection_create_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_create_n", utc_connection_create_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_ip_address_p", utc_connection_get_ip_address_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_ip_address_n", utc_connection_get_ip_address_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_proxy_p", utc_connection_get_proxy_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_proxy_n", utc_connection_get_proxy_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_type_n", utc_connection_get_type_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_type_p", utc_connection_get_type_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_is_metered_network_n", utc_connection_is_metered_network_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_is_metered_network_p", utc_connection_is_metered_network_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_cellular_state_n", utc_connection_get_cellular_state_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_cellular_state_p", utc_connection_get_cellular_state_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_ethernet_state_n", utc_connection_get_ethernet_state_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_ethernet_state_p", utc_connection_get_ethernet_state_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_wifi_state_n", utc_connection_get_wifi_state_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_wifi_state_p", utc_connection_get_wifi_state_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_bt_state_n", utc_connection_get_bt_state_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_bt_state_p", utc_connection_get_bt_state_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_mac_address_n", utc_connection_get_mac_address_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_mac_address_p", utc_connection_get_mac_address_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_ethernet_cable_state_chaged_cb_n", utc_connection_set_ethernet_cable_state_chaged_cb_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_unset_ethernet_cable_state_chaged_cb_n", utc_connection_unset_ethernet_cable_state_chaged_cb_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_ethernet_cable_state_n", utc_connection_get_ethernet_cable_state_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_ethernet_cable_state_p", utc_connection_get_ethernet_cable_state_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_current_profile_p", utc_connection_get_current_profile_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_current_profile_n", utc_connection_get_current_profile_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_default_cellular_service_profile_p", utc_connection_get_default_cellular_service_profile_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_default_cellular_service_profile_n", utc_connection_get_default_cellular_service_profile_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_default_cellular_service_profile_p", utc_connection_set_default_cellular_service_profile_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_default_cellular_service_profile_n", utc_connection_set_default_cellular_service_profile_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_default_cellular_service_profile_async_p", utc_connection_set_default_cellular_service_profile_async_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_default_cellular_service_profile_async_n", utc_connection_set_default_cellular_service_profile_async_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_type_changed_cb_n", utc_connection_set_type_changed_cb_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_type_changed_cb_p", utc_connection_set_type_changed_cb_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_unset_type_changed_cb_n", utc_connection_unset_type_changed_cb_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_unset_type_changed_cb_p", utc_connection_unset_type_changed_cb_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_ip_address_changed_cb_n", utc_connection_set_ip_address_changed_cb_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_ip_address_changed_cb_p", utc_connection_set_ip_address_changed_cb_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_unset_ip_address_changed_cb_n", utc_connection_unset_ip_address_changed_cb_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_unset_ip_address_changed_cb_p", utc_connection_unset_ip_address_changed_cb_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_proxy_address_changed_cb_n", utc_connection_set_proxy_address_changed_cb_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_set_proxy_address_changed_cb_p", utc_connection_set_proxy_address_changed_cb_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_unset_proxy_address_changed_cb_n", utc_connection_unset_proxy_address_changed_cb_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_unset_proxy_address_changed_cb_p", utc_connection_unset_proxy_address_changed_cb_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_statistics_p", utc_connection_get_statistics_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_statistics_n", utc_connection_get_statistics_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_reset_statistics_p", utc_connection_reset_statistics_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_reset_statistics_n", utc_connection_reset_statistics_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_add_route_n1", utc_connection_add_route_n1, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_add_route_n2", utc_connection_add_route_n2, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_remove_route_n1", utc_connection_remove_route_n1, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_remove_route_n2", utc_connection_remove_route_n2, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_add_route_ipv6_n1", utc_connection_add_route_ipv6_n1, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_add_route_ipv6_n2", utc_connection_add_route_ipv6_n2, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_remove_route_ipv6_n1", utc_connection_remove_route_ipv6_n1, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_remove_route_ipv6_n2", utc_connection_remove_route_ipv6_n2, utc_network_connection_startup, utc_network_connection_cleanup},
	{"utc_connection_add_route_entry_n1", utc_connection_add_route_entry_n1, utc_network_connection_startup, utc_network_connection_cleanup},
	{"utc_connection_add_route_entry_n2", utc_connection_add_route_entry_n2, utc_network_connection_startup, utc_network_connection_cleanup},
	{"utc_connection_remove_route_entry_n1", utc_connection_remove_route_entry_n1, utc_network_connection_startup, utc_network_connection_cleanup},
	{"utc_connection_remove_route_entry_n2", utc_connection_remove_route_entry_n2, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_profile_iterator_n", utc_connection_get_profile_iterator_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_get_profile_iterator_p", utc_connection_get_profile_iterator_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_destroy_profile_iterator_n", utc_connection_destroy_profile_iterator_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_destroy_profile_iterator_p", utc_connection_destroy_profile_iterator_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_profile_iterator_has_next_n", utc_connection_profile_iterator_has_next_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_profile_iterator_has_next_p", utc_connection_profile_iterator_has_next_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_profile_iterator_next_n", utc_connection_profile_iterator_next_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_profile_iterator_next_p", utc_connection_profile_iterator_next_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_add_profile_p", utc_connection_add_profile_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_add_profile_n", utc_connection_add_profile_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_close_profile_p", utc_connection_close_profile_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_close_profile_n", utc_connection_close_profile_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_update_profile_p", utc_connection_update_profile_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_update_profile_n", utc_connection_update_profile_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_remove_profile_p", utc_connection_remove_profile_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_remove_profile_n", utc_connection_remove_profile_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_open_profile_p", utc_connection_open_profile_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_open_profile_n", utc_connection_open_profile_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_reset_profile_p", utc_connection_reset_profile_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_reset_profile_n", utc_connection_reset_profile_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_foreach_ipv6_address_p", utc_connection_foreach_ipv6_address_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_foreach_ipv6_address_n", utc_connection_foreach_ipv6_address_n, utc_network_connection_startup, utc_network_connection_cleanup},
	{"utc_connection_set_ethernet_cable_state_changed_cb_n", utc_connection_set_ethernet_cable_state_changed_cb_n, utc_network_connection_startup, utc_network_connection_cleanup},
	{"utc_connection_unset_ethernet_cable_state_changed_cb_n", utc_connection_unset_ethernet_cable_state_changed_cb_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_destroy_p", utc_connection_destroy_p, utc_network_connection_startup, utc_network_connection_cleanup},
    {"utc_connection_destroy_n", utc_connection_destroy_n, utc_network_connection_startup, utc_network_connection_cleanup},
    {NULL, NULL}
};

#endif // __TCT_CONNECTION_CORE_H__
