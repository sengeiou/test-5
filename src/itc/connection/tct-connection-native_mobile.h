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
#ifndef __TCT_CONNECTION_NATIVE_H__
#define __TCT_CONNECTION_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_connection_cellular_profile_startup(void);
extern void ITs_connection_cellular_profile_cleanup(void);
extern void ITs_connection_ethernet_profile_startup(void);
extern void ITs_connection_ethernet_profile_cleanup(void);
extern void ITs_connection_profile_startup(void);
extern void ITs_connection_profile_cleanup(void);
extern void ITs_connection_startup(void);
extern void ITs_connection_cleanup(void);
extern void ITs_connection_wifi_profile_startup(void);
extern void ITs_connection_wifi_profile_cleanup(void);

extern int ITc_connection_profile_set_get_cellular_apn_p(void);
extern int ITc_connection_profile_set_get_cellular_auth_info_p(void);
extern int ITc_connection_profile_set_get_cellular_home_url_p(void);
extern int ITc_connection_profile_set_get_cellular_service_type_p(void);
extern int ITc_connection_profile_is_cellular_roaming_p(void);
extern int ITc_connection_profile_is_cellular_editable_p(void);
extern int ITc_connection_profile_is_cellular_hidden_p(void);
extern int ITc_connection_get_cellular_state_p(void);
extern int ITc_connection_set_get_default_cellular_service_profile_p(void);
extern int ITc_connection_set_default_cellular_service_profile_async_p(void);
extern int ITc_connection_profile_is_cellular_default_p(void);
extern int ITc_connection_set_unset_ethernet_cable_state_changed_cb_p(void);
extern int ITc_connection_get_ethernet_cable_state_p(void);
extern int ITc_connection_get_ethernet_state_p(void);
extern int ITc_connection_get_mac_address_p(void);
extern int ITc_connection_profile_create_destroy_p(void);
extern int ITc_connection_profile_get_name_p(void);
extern int ITc_connection_profile_get_id_p(void);
extern int ITc_connection_profile_get_type_p(void);
extern int ITc_connection_profile_get_network_interface_name_p(void);
extern int ITc_connection_profile_clone_p(void);
extern int ITc_connection_profile_get_state_p(void);
extern int ITc_connection_profile_set_get_dns_address_p(void);
extern int ITc_connection_profile_set_get_gateway_p(void);
extern int ITc_connection_profile_set_get_ip_address_p(void);
extern int ITc_connection_profile_set_get_ip_config_type_p(void);
extern int ITc_connection_profile_set_get_proxy_type_p(void);
extern int ITc_connection_profile_set_get_proxy_address_p(void);
extern int ITc_connection_profile_set_get_subnet_mask_p(void);
extern int ITc_connection_profile_set_unset_state_changed_cb_p(void);
extern int ITc_connection_open_close_profile_p(void);
extern int ITc_connection_profile_refresh_p(void);
extern int ITc_connection_reset_profile_p(void);
extern int ITc_connection_add_remove_profile_p(void);
extern int ITc_connection_create_destroy_p(void);
extern int ITc_connection_get_bt_state_p(void);
extern int ITc_connection_get_type_p(void);
extern int ITc_connection_get_proxy_p(void);
extern int ITc_connection_get_ip_address_p(void);
extern int ITc_connection_get_statistics_p(void);
extern int ITc_connection_get_current_profile_p(void);
extern int ITc_connection_reset_statistics_p(void);
extern int ITc_connection_get_destroy_profile_iterator_p(void);
extern int ITc_connection_profile_iterator_has_next_next_p(void);
extern int ITc_connection_set_unset_type_changed_cb_p(void);
extern int ITc_connection_set_unset_ip_address_changed_cb_p(void);
extern int ITc_connection_set_unset_proxy_address_changed_cb_p(void);
extern int ITc_connection_profile_get_wifi_bssid_p(void);
extern int ITc_connection_profile_get_wifi_essid_p(void);
extern int ITc_connection_profile_get_wifi_frequency_p(void);
extern int ITc_connection_profile_get_wifi_max_speed_p(void);
extern int ITc_connection_profile_get_wifi_rssi_p(void);
extern int ITc_connection_profile_get_wifi_security_type_p(void);
extern int ITc_connection_profile_get_wifi_encryption_type_p(void);
extern int ITc_connection_profile_is_wifi_passphrase_required_p(void);
extern int ITc_connection_profile_is_wifi_wps_supported_p(void);
extern int ITc_connection_profile_set_wifi_passphrase_p(void);
extern int ITc_connection_update_profile_p(void);
extern int ITc_connection_get_wifi_state_p(void);
extern int ITc_connection_profile_set_get_cellular_pdn_type_p(void);
extern int ITc_connection_profile_set_get_cellular_roam_pdn_type_p(void);
extern int ITc_connection_foreach_ipv6_address_p(void);
extern int ITc_connection_profile_get_ipv6_state_p(void);
extern int ITc_connection_profile_set_get_prefix_length_p(void);
extern int ITc_connection_profile_set_get_dns_config_type_p(void);
extern int ITc_connection_profile_get_dhcp_server_address_p(void);
extern int ITc_connection_profile_get_dhcp_lease_duration_p(void);
extern int ITc_connection_is_metered_network_p(void);
extern int ITc_connection_set_unset_internet_state_changed_cb_p(void);
extern int ITc_connection_profile_get_internet_state_p(void);

testcase tc_array[] = {
    {"ITc_connection_profile_get_dhcp_server_address_p",ITc_connection_profile_get_dhcp_server_address_p,ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_set_get_cellular_apn_p", ITc_connection_profile_set_get_cellular_apn_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_profile_set_get_cellular_auth_info_p", ITc_connection_profile_set_get_cellular_auth_info_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_profile_set_get_cellular_home_url_p", ITc_connection_profile_set_get_cellular_home_url_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_profile_set_get_cellular_service_type_p", ITc_connection_profile_set_get_cellular_service_type_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_profile_is_cellular_roaming_p", ITc_connection_profile_is_cellular_roaming_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_profile_is_cellular_editable_p", ITc_connection_profile_is_cellular_editable_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_profile_is_cellular_hidden_p", ITc_connection_profile_is_cellular_hidden_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_get_cellular_state_p", ITc_connection_get_cellular_state_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_set_get_default_cellular_service_profile_p", ITc_connection_set_get_default_cellular_service_profile_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_set_default_cellular_service_profile_async_p", ITc_connection_set_default_cellular_service_profile_async_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_profile_is_cellular_default_p", ITc_connection_profile_is_cellular_default_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_set_unset_ethernet_cable_state_changed_cb_p", ITc_connection_set_unset_ethernet_cable_state_changed_cb_p, ITs_connection_ethernet_profile_startup, ITs_connection_ethernet_profile_cleanup},
    {"ITc_connection_get_ethernet_cable_state_p", ITc_connection_get_ethernet_cable_state_p, ITs_connection_ethernet_profile_startup, ITs_connection_ethernet_profile_cleanup},
    {"ITc_connection_get_ethernet_state_p", ITc_connection_get_ethernet_state_p, ITs_connection_ethernet_profile_startup, ITs_connection_ethernet_profile_cleanup},
    {"ITc_connection_get_mac_address_p", ITc_connection_get_mac_address_p, ITs_connection_ethernet_profile_startup, ITs_connection_ethernet_profile_cleanup},
    {"ITc_connection_profile_create_destroy_p", ITc_connection_profile_create_destroy_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_get_name_p", ITc_connection_profile_get_name_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_get_id_p", ITc_connection_profile_get_id_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_get_type_p", ITc_connection_profile_get_type_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_get_network_interface_name_p", ITc_connection_profile_get_network_interface_name_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_clone_p", ITc_connection_profile_clone_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_get_state_p", ITc_connection_profile_get_state_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_set_get_dns_address_p", ITc_connection_profile_set_get_dns_address_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_set_get_gateway_p", ITc_connection_profile_set_get_gateway_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_set_get_ip_address_p", ITc_connection_profile_set_get_ip_address_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_set_get_ip_config_type_p", ITc_connection_profile_set_get_ip_config_type_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_set_get_proxy_type_p", ITc_connection_profile_set_get_proxy_type_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_set_get_proxy_address_p", ITc_connection_profile_set_get_proxy_address_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_set_get_subnet_mask_p", ITc_connection_profile_set_get_subnet_mask_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_set_unset_state_changed_cb_p", ITc_connection_profile_set_unset_state_changed_cb_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_open_close_profile_p", ITc_connection_open_close_profile_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_profile_refresh_p", ITc_connection_profile_refresh_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_reset_profile_p", ITc_connection_reset_profile_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_add_remove_profile_p", ITc_connection_add_remove_profile_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {"ITc_connection_create_destroy_p", ITc_connection_create_destroy_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_get_bt_state_p", ITc_connection_get_bt_state_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_get_type_p", ITc_connection_get_type_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_get_proxy_p", ITc_connection_get_proxy_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_get_ip_address_p", ITc_connection_get_ip_address_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_get_statistics_p", ITc_connection_get_statistics_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_get_current_profile_p", ITc_connection_get_current_profile_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_reset_statistics_p", ITc_connection_reset_statistics_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_get_destroy_profile_iterator_p", ITc_connection_get_destroy_profile_iterator_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_profile_iterator_has_next_next_p", ITc_connection_profile_iterator_has_next_next_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_set_unset_type_changed_cb_p", ITc_connection_set_unset_type_changed_cb_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_set_unset_ip_address_changed_cb_p", ITc_connection_set_unset_ip_address_changed_cb_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_set_unset_proxy_address_changed_cb_p", ITc_connection_set_unset_proxy_address_changed_cb_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_profile_get_wifi_bssid_p", ITc_connection_profile_get_wifi_bssid_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_get_wifi_essid_p", ITc_connection_profile_get_wifi_essid_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_get_wifi_frequency_p", ITc_connection_profile_get_wifi_frequency_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_get_wifi_max_speed_p", ITc_connection_profile_get_wifi_max_speed_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_get_wifi_rssi_p", ITc_connection_profile_get_wifi_rssi_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_get_wifi_security_type_p", ITc_connection_profile_get_wifi_security_type_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_get_wifi_encryption_type_p", ITc_connection_profile_get_wifi_encryption_type_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_is_wifi_passphrase_required_p", ITc_connection_profile_is_wifi_passphrase_required_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_is_wifi_wps_supported_p", ITc_connection_profile_is_wifi_wps_supported_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_set_wifi_passphrase_p", ITc_connection_profile_set_wifi_passphrase_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_update_profile_p", ITc_connection_update_profile_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_get_wifi_state_p", ITc_connection_get_wifi_state_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_set_get_cellular_pdn_type_p", ITc_connection_profile_set_get_cellular_pdn_type_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_profile_set_get_cellular_roam_pdn_type_p", ITc_connection_profile_set_get_cellular_roam_pdn_type_p, ITs_connection_cellular_profile_startup, ITs_connection_cellular_profile_cleanup},
    {"ITc_connection_foreach_ipv6_address_p", ITc_connection_foreach_ipv6_address_p, ITs_connection_startup, ITs_connection_cleanup},
    {"ITc_connection_profile_get_ipv6_state_p", ITc_connection_profile_get_ipv6_state_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_set_get_prefix_length_p", ITc_connection_profile_set_get_prefix_length_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_set_get_dns_config_type_p", ITc_connection_profile_set_get_dns_config_type_p, ITs_connection_wifi_profile_startup, ITs_connection_wifi_profile_cleanup},
    {"ITc_connection_profile_get_dhcp_lease_duration_p", ITc_connection_profile_get_dhcp_lease_duration_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
	{"ITc_connection_is_metered_network_p", ITc_connection_is_metered_network_p, ITs_connection_startup, ITs_connection_cleanup},
	{"ITc_connection_set_unset_internet_state_changed_cb_p", ITc_connection_set_unset_internet_state_changed_cb_p, ITs_connection_startup, ITs_connection_cleanup},
	{"ITc_connection_profile_get_internet_state_p", ITc_connection_profile_get_internet_state_p, ITs_connection_profile_startup, ITs_connection_profile_cleanup},
    {NULL, NULL}
};

#endif // __TCT_CONNECTION_NATIVE_H__
