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
#ifndef __TCT_WIFI_MANAGER_NATIVE_H__
#define __TCT_WIFI_MANAGER_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_wifi_manager_ap_startup(void);
extern void utc_wifi_manager_ap_cleanup(void);
extern void utc_wifi_manager_config_startup(void);
extern void utc_wifi_manager_config_cleanup(void);
extern void utc_wifi_manager_startup(void);
extern void utc_wifi_manager_cleanup(void);
extern void utc_wifi_manager_tdls_startup(void);
extern void utc_wifi_manager_tdls_cleanup(void);

extern int utc_wifi_manager_ap_create_p(void);
extern int utc_wifi_manager_ap_create_n(void);
extern int utc_wifi_manager_ap_hidden_create_p(void);
extern int utc_wifi_manager_ap_hidden_create_n(void);
extern int utc_wifi_manager_ap_clone_p(void);
extern int utc_wifi_manager_ap_clone_n(void);
extern int utc_wifi_manager_ap_get_essid_p(void);
extern int utc_wifi_manager_ap_get_essid_n(void);
extern int utc_wifi_manager_ap_get_bssid_p(void);
extern int utc_wifi_manager_ap_get_bssid_n(void);
extern int utc_wifi_manager_ap_get_rssi_p(void);
extern int utc_wifi_manager_ap_get_rssi_n(void);
extern int utc_wifi_manager_ap_get_rssi_level_p(void);
extern int utc_wifi_manager_ap_get_rssi_level_n(void);
extern int utc_wifi_manager_ap_get_raw_ssid_p(void);
extern int utc_wifi_manager_ap_get_raw_ssid_n(void);
extern int utc_wifi_manager_ap_get_frequency_p(void);
extern int utc_wifi_manager_ap_get_frequency_n(void);
extern int utc_wifi_manager_ap_get_max_speed_p(void);
extern int utc_wifi_manager_ap_get_max_speed_n(void);
extern int utc_wifi_manager_ap_is_favorite_p(void);
extern int utc_wifi_manager_ap_is_favorite_n(void);
extern int utc_wifi_manager_ap_is_passpoint_p(void);
extern int utc_wifi_manager_ap_is_passpoint_n(void);
extern int utc_wifi_manager_ap_get_connection_state_p(void);
extern int utc_wifi_manager_ap_get_connection_state_n(void);
extern int utc_wifi_manager_ap_get_ip_config_type_p(void);
extern int utc_wifi_manager_ap_get_ip_config_type_n(void);
extern int utc_wifi_manager_ap_set_ip_config_type_p(void);
extern int utc_wifi_manager_ap_set_ip_config_type_n(void);
extern int utc_wifi_manager_ap_get_ip_address_p(void);
extern int utc_wifi_manager_ap_get_ip_address_n(void);
extern int utc_wifi_manager_ap_set_ip_address_p(void);
extern int utc_wifi_manager_ap_set_ip_address_n(void);
extern int utc_wifi_manager_ap_get_subnet_mask_p(void);
extern int utc_wifi_manager_ap_get_subnet_mask_n(void);
extern int utc_wifi_manager_ap_set_subnet_mask_p(void);
extern int utc_wifi_manager_ap_set_subnet_mask_n(void);
extern int utc_wifi_manager_ap_get_gateway_address_p(void);
extern int utc_wifi_manager_ap_get_gateway_address_n(void);
extern int utc_wifi_manager_ap_set_gateway_address_p(void);
extern int utc_wifi_manager_ap_set_gateway_address_n(void);
extern int utc_wifi_manager_ap_get_dhcp_server_address_p(void);
extern int utc_wifi_manager_ap_get_dhcp_server_address_n(void);
extern int utc_wifi_manager_ap_get_dhcp_lease_duration_p(void);
extern int utc_wifi_manager_ap_get_dhcp_lease_duration_n(void);
extern int utc_wifi_manager_ap_get_proxy_address_p(void);
extern int utc_wifi_manager_ap_get_proxy_address_n(void);
extern int utc_wifi_manager_ap_set_proxy_address_p(void);
extern int utc_wifi_manager_ap_set_proxy_address_n(void);
extern int utc_wifi_manager_ap_get_proxy_type_p(void);
extern int utc_wifi_manager_ap_get_proxy_type_n(void);
extern int utc_wifi_manager_ap_set_proxy_type_p(void);
extern int utc_wifi_manager_ap_set_proxy_type_n(void);
extern int utc_wifi_manager_ap_get_dns_address_p(void);
extern int utc_wifi_manager_ap_get_dns_address_n(void);
extern int utc_wifi_manager_ap_set_dns_address_p(void);
extern int utc_wifi_manager_ap_set_dns_address_n(void);
extern int utc_wifi_manager_ap_get_security_type_p(void);
extern int utc_wifi_manager_ap_get_security_type_n(void);
extern int utc_wifi_manager_ap_set_security_type_p(void);
extern int utc_wifi_manager_ap_set_security_type_n(void);
extern int utc_wifi_manager_ap_get_encryption_type_p(void);
extern int utc_wifi_manager_ap_get_encryption_type_n(void);
extern int utc_wifi_manager_ap_set_encryption_type_p(void);
extern int utc_wifi_manager_ap_set_encryption_type_n(void);
extern int utc_wifi_manager_ap_is_passphrase_required_p(void);
extern int utc_wifi_manager_ap_is_passphrase_required_n(void);
extern int utc_wifi_manager_ap_set_passphrase_p(void);
extern int utc_wifi_manager_ap_set_passphrase_n(void);
extern int utc_wifi_manager_ap_is_wps_supported_p(void);
extern int utc_wifi_manager_ap_is_wps_supported_n(void);
extern int utc_wifi_manager_ap_set_eap_passphrase_p(void);
extern int utc_wifi_manager_ap_set_eap_passphrase_n(void);
extern int utc_wifi_manager_ap_get_eap_passphrase_p(void);
extern int utc_wifi_manager_ap_get_eap_passphrase_n(void);
extern int utc_wifi_manager_ap_get_eap_ca_cert_file_p(void);
extern int utc_wifi_manager_ap_get_eap_ca_cert_file_n(void);
extern int utc_wifi_manager_ap_set_eap_ca_cert_file_p(void);
extern int utc_wifi_manager_ap_set_eap_ca_cert_file_n(void);
extern int utc_wifi_manager_ap_get_eap_client_cert_file_p(void);
extern int utc_wifi_manager_ap_get_eap_client_cert_file_n(void);
extern int utc_wifi_manager_ap_set_eap_client_cert_file_p(void);
extern int utc_wifi_manager_ap_set_eap_client_cert_file_n(void);
extern int utc_wifi_manager_ap_get_eap_private_key_file_p(void);
extern int utc_wifi_manager_ap_get_eap_private_key_file_n(void);
extern int utc_wifi_manager_ap_set_eap_private_key_info_p(void);
extern int utc_wifi_manager_ap_set_eap_private_key_info_n(void);
extern int utc_wifi_manager_ap_get_eap_type_p(void);
extern int utc_wifi_manager_ap_get_eap_type_n(void);
extern int utc_wifi_manager_ap_set_eap_type_p(void);
extern int utc_wifi_manager_ap_set_eap_type_n(void);
extern int utc_wifi_manager_ap_get_eap_auth_type_p(void);
extern int utc_wifi_manager_ap_get_eap_auth_type_n(void);
extern int utc_wifi_manager_ap_set_eap_auth_type_p(void);
extern int utc_wifi_manager_ap_set_eap_auth_type_n(void);
extern int utc_wifi_manager_ap_get_disconnect_reason_p(void);
extern int utc_wifi_manager_ap_get_disconnect_reason_n(void);
extern int utc_wifi_manager_ap_refresh_p(void);
extern int utc_wifi_manager_ap_refresh_n(void);
extern int utc_wifi_manager_ap_get_error_state_p(void);
extern int utc_wifi_manager_ap_get_error_state_n(void);
extern int utc_wifi_manager_ap_get_prefix_length_p(void);
extern int utc_wifi_manager_ap_get_prefix_length_n(void);
extern int utc_wifi_manager_ap_set_prefix_length_p(void);
extern int utc_wifi_manager_ap_set_prefix_length_n(void);
extern int utc_wifi_manager_ap_get_dns_config_type_p(void);
extern int utc_wifi_manager_ap_get_dns_config_type_n(void);
extern int utc_wifi_manager_ap_set_dns_config_type_p(void);
extern int utc_wifi_manager_ap_set_dns_config_type_n(void);
extern int utc_wifi_manager_ap_foreach_ipv6_address_p(void);
extern int utc_wifi_manager_ap_foreach_ipv6_address_n(void);
extern int utc_wifi_manager_ap_get_assoc_status_code_p(void);
extern int utc_wifi_manager_ap_get_assoc_status_code_n(void);
extern int utc_wifi_manager_ap_foreach_vsie_p(void);
extern int utc_wifi_manager_ap_foreach_vsie_n(void);
extern int utc_wifi_manager_ap_destroy_p(void);
extern int utc_wifi_manager_ap_destroy_n(void);
extern int utc_wifi_manager_config_create_p(void);
extern int utc_wifi_manager_config_create_n(void);
extern int utc_wifi_manager_config_save_p(void);
extern int utc_wifi_manager_config_save_n(void);
extern int utc_wifi_manager_config_destroy_p(void);
extern int utc_wifi_manager_config_destroy_n(void);
extern int utc_wifi_manager_config_foreach_configuration_p(void);
extern int utc_wifi_manager_config_foreach_configuration_n(void);
extern int utc_wifi_manager_config_clone_p(void);
extern int utc_wifi_manager_config_clone_n(void);
extern int utc_wifi_manager_config_remove_p(void);
extern int utc_wifi_manager_config_remove_n(void);
extern int utc_wifi_manager_config_get_name_p(void);
extern int utc_wifi_manager_config_get_name_n(void);
extern int utc_wifi_manager_config_get_security_type_p(void);
extern int utc_wifi_manager_config_get_security_type_n(void);
extern int utc_wifi_manager_config_set_proxy_address_p(void);
extern int utc_wifi_manager_config_set_proxy_address_n(void);
extern int utc_wifi_manager_config_get_proxy_address_p(void);
extern int utc_wifi_manager_config_get_proxy_address_n(void);
extern int utc_wifi_manager_config_set_hidden_ap_property_p(void);
extern int utc_wifi_manager_config_set_hidden_ap_property_n(void);
extern int utc_wifi_manager_config_get_hidden_ap_property_p(void);
extern int utc_wifi_manager_config_get_hidden_ap_property_n(void);
extern int utc_wifi_manager_config_get_eap_anonymous_identity_p(void);
extern int utc_wifi_manager_config_get_eap_anonymous_identity_n(void);
extern int utc_wifi_manager_config_set_eap_anonymous_identity_p(void);
extern int utc_wifi_manager_config_set_eap_anonymous_identity_n(void);
extern int utc_wifi_manager_config_get_eap_ca_cert_file_p(void);
extern int utc_wifi_manager_config_get_eap_ca_cert_file_n(void);
extern int utc_wifi_manager_config_set_eap_ca_cert_file_p(void);
extern int utc_wifi_manager_config_set_eap_ca_cert_file_n(void);
extern int utc_wifi_manager_config_get_eap_client_cert_file_p(void);
extern int utc_wifi_manager_config_get_eap_client_cert_file_n(void);
extern int utc_wifi_manager_config_set_eap_client_cert_file_p(void);
extern int utc_wifi_manager_config_set_eap_client_cert_file_n(void);
extern int utc_wifi_manager_config_get_eap_identity_p(void);
extern int utc_wifi_manager_config_get_eap_identity_n(void);
extern int utc_wifi_manager_config_set_eap_identity_p(void);
extern int utc_wifi_manager_config_set_eap_identity_n(void);
extern int utc_wifi_manager_config_get_eap_type_p(void);
extern int utc_wifi_manager_config_get_eap_type_n(void);
extern int utc_wifi_manager_config_set_eap_type_p(void);
extern int utc_wifi_manager_config_set_eap_type_n(void);
extern int utc_wifi_manager_config_get_eap_auth_type_p(void);
extern int utc_wifi_manager_config_get_eap_auth_type_n(void);
extern int utc_wifi_manager_config_set_eap_auth_type_p(void);
extern int utc_wifi_manager_config_set_eap_auth_type_n(void);
extern int utc_wifi_manager_config_get_eap_subject_match_p(void);
extern int utc_wifi_manager_config_get_eap_subject_match_n(void);
extern int utc_wifi_manager_config_set_eap_subject_match_p(void);
extern int utc_wifi_manager_config_set_eap_subject_match_n(void);
extern int utc_wifi_manager_config_set_eap_private_key_info_p(void);
extern int utc_wifi_manager_config_set_eap_private_key_info_n1(void);
extern int utc_wifi_manager_config_get_eap_private_key_file_p(void);
extern int utc_wifi_manager_config_get_eap_private_key_file_n1(void);
extern int utc_wifi_manager_config_set_ip_config_type_p(void);
extern int utc_wifi_manager_config_set_ip_config_type_n1(void);
extern int utc_wifi_manager_config_get_ip_config_type_p(void);
extern int utc_wifi_manager_config_get_ip_config_type_n1(void);
extern int utc_wifi_manager_config_set_ip_address_p(void);
extern int utc_wifi_manager_config_set_ip_address_n1(void);
extern int utc_wifi_manager_config_get_ip_address_p(void);
extern int utc_wifi_manager_config_get_ip_address_n1(void);
extern int utc_wifi_manager_config_set_subnet_mask_p(void);
extern int utc_wifi_manager_config_set_subnet_mask_n1(void);
extern int utc_wifi_manager_config_get_subnet_mask_p(void);
extern int utc_wifi_manager_config_get_subnet_mask_n1(void);
extern int utc_wifi_manager_config_set_gateway_address_p(void);
extern int utc_wifi_manager_config_set_gateway_address_n1(void);
extern int utc_wifi_manager_config_get_gateway_address_p(void);
extern int utc_wifi_manager_config_get_gateway_address_n1(void);
extern int utc_wifi_manager_config_set_dns_config_type_p(void);
extern int utc_wifi_manager_config_set_dns_config_type_n1(void);
extern int utc_wifi_manager_config_get_dns_config_type_p(void);
extern int utc_wifi_manager_config_get_dns_config_type_n1(void);
extern int utc_wifi_manager_config_set_dns_address_p(void);
extern int utc_wifi_manager_config_set_dns_address_n1(void);
extern int utc_wifi_manager_config_get_dns_address_p(void);
extern int utc_wifi_manager_config_get_dns_address_n1(void);
extern int utc_wifi_manager_config_set_prefix_length_p(void);
extern int utc_wifi_manager_config_set_prefix_length_n1(void);
extern int utc_wifi_manager_config_get_prefix_length_p(void);
extern int utc_wifi_manager_config_get_prefix_length_n1(void);
extern int utc_wifi_manager_initialize_p(void);
extern int utc_wifi_manager_initialize_n(void);
extern int utc_wifi_manager_activate_n(void);
extern int utc_wifi_manager_activate_p(void);
extern int utc_wifi_manager_activate_with_wifi_picker_tested_n(void);
extern int utc_wifi_manager_activate_with_wifi_picker_tested_p(void);
extern int utc_wifi_manager_is_activated_p(void);
extern int utc_wifi_manager_is_activated_n(void);
extern int utc_wifi_manager_get_connection_state_p(void);
extern int utc_wifi_manager_get_connection_state_n(void);
extern int utc_wifi_manager_get_module_state_p(void);
extern int utc_wifi_manager_get_module_state_n(void);
extern int utc_wifi_manager_get_mac_address_p(void);
extern int utc_wifi_manager_get_mac_address_n(void);
extern int utc_wifi_manager_foreach_found_ap_p(void);
extern int utc_wifi_manager_foreach_found_ap_n(void);
extern int utc_wifi_manager_scan_specific_ap_n(void);
extern int utc_wifi_manager_scan_specific_ap_p(void);
extern int utc_wifi_manager_bssid_scan_n(void);
extern int utc_wifi_manager_bssid_scan_p(void);
extern int utc_wifi_manager_foreach_found_specific_ap_n(void);
extern int utc_wifi_manager_foreach_found_specific_ap_p(void);
extern int utc_wifi_manager_foreach_found_bssid_ap_n(void);
extern int utc_wifi_manager_foreach_found_bssid_ap_p(void);
extern int utc_wifi_manager_set_device_state_changed_cb_p(void);
extern int utc_wifi_manager_set_device_state_changed_cb_n(void);
extern int utc_wifi_manager_unset_device_state_changed_cb_p(void);
extern int utc_wifi_manager_unset_device_state_changed_cb_n(void);
extern int utc_wifi_manager_set_background_scan_cb_p(void);
extern int utc_wifi_manager_set_background_scan_cb_n(void);
extern int utc_wifi_manager_unset_background_scan_cb_p(void);
extern int utc_wifi_manager_unset_background_scan_cb_n(void);
extern int utc_wifi_manager_set_scan_state_changed_cb_p(void);
extern int utc_wifi_manager_set_scan_state_changed_cb_n(void);
extern int utc_wifi_manager_unset_scan_state_changed_cb_p(void);
extern int utc_wifi_manager_unset_scan_state_changed_cb_n(void);
extern int utc_wifi_manager_set_connection_state_changed_cb_p(void);
extern int utc_wifi_manager_set_connection_state_changed_cb_n(void);
extern int utc_wifi_manager_unset_connection_state_changed_cb_p(void);
extern int utc_wifi_manager_unset_connection_state_changed_cb_n(void);
extern int utc_wifi_manager_set_rssi_level_changed_cb_p(void);
extern int utc_wifi_manager_set_rssi_level_changed_cb_n(void);
extern int utc_wifi_manager_unset_rssi_level_changed_cb_p(void);
extern int utc_wifi_manager_unset_rssi_level_changed_cb_n(void);
extern int utc_wifi_manager_set_module_state_changed_cb_n(void);
extern int utc_wifi_manager_unset_module_state_changed_cb_n(void);
extern int utc_wifi_manager_deinitialize_p(void);
extern int utc_wifi_manager_deinitialize_n(void);
extern int utc_wifi_manager_get_network_interface_name_p(void);
extern int utc_wifi_manager_get_network_interface_name_n(void);
extern int utc_wifi_manager_scan_p(void);
extern int utc_wifi_manager_scan_n(void);
extern int utc_wifi_manager_get_scan_state_p(void);
extern int utc_wifi_manager_get_scan_state_n(void);
extern int utc_wifi_manager_deactivate_n(void);
extern int utc_wifi_manager_deactivate_p(void);
extern int utc_wifi_manager_connect_n(void);
extern int utc_wifi_manager_connect_p(void);
extern int utc_wifi_manager_connect_hidden_ap_n(void);
extern int utc_wifi_manager_connect_hidden_ap_n2(void);
extern int utc_wifi_manager_connect_hidden_ap_p(void);
extern int utc_wifi_manager_update_ap_n(void);
extern int utc_wifi_manager_update_ap_p(void);
extern int utc_wifi_manager_disconnect_n(void);
extern int utc_wifi_manager_disconnect_p(void);
extern int utc_wifi_manager_connect_by_wps_pin_n(void);
extern int utc_wifi_manager_connect_by_wps_pbc_n(void);
extern int utc_wifi_manager_connect_by_wps_pin_without_ssid_n(void);
extern int utc_wifi_manager_connect_by_wps_pbc_without_ssid_n(void);
extern int utc_wifi_manager_cancel_wps_n(void);
extern int utc_wifi_manager_get_connected_ap_p(void);
extern int utc_wifi_manager_get_connected_ap_n(void);
extern int utc_wifi_manager_forget_ap_n(void);
extern int utc_wifi_manager_forget_ap_p(void);
extern int utc_wifi_manager_forget_ap_async_n(void);
extern int utc_wifi_manager_forget_ap_async_p(void);
extern int utc_wifi_manager_tdls_start_discovery_n(void);
extern int utc_wifi_manager_tdls_connect_n(void);
extern int utc_wifi_manager_tdls_disconnect_n(void);
extern int utc_wifi_manager_tdls_enable_channel_switching_n(void);
extern int utc_wifi_manager_tdls_disable_channel_switching_n(void);
extern int utc_wifi_manager_tdls_set_discovered_cb_p(void);
extern int utc_wifi_manager_tdls_set_discovered_cb_n(void);
extern int utc_wifi_manager_tdls_unset_discovered_cb_p(void);
extern int utc_wifi_manager_tdls_unset_discovered_cb_n(void);
extern int utc_wifi_manager_tdls_get_connected_peer_n(void);
extern int utc_wifi_manager_tdls_set_state_changed_cb_p(void);
extern int utc_wifi_manager_tdls_set_state_changed_cb_n(void);
extern int utc_wifi_manager_tdls_unset_state_changed_cb_p(void);
extern int utc_wifi_manager_tdls_unset_state_changed_cb_n(void);
extern int utc_wifi_manager_specific_scan_create_p(void);
extern int utc_wifi_manager_specific_scan_create_n(void);
extern int utc_wifi_manager_specific_scan_destroy_p(void);
extern int utc_wifi_manager_specific_scan_destroy_n(void);
extern int utc_wifi_manager_specific_scan_set_ssid_p(void);
extern int utc_wifi_manager_specific_scan_set_ssid_n(void);
extern int utc_wifi_manager_specific_scan_set_freq_p(void);
extern int utc_wifi_manager_specific_scan_set_freq_n(void);
extern int utc_wifi_manager_specific_ap_start_multi_scan_p(void);
extern int utc_wifi_manager_specific_ap_start_multi_scan_n(void);
extern int utc_wifi_manager_add_vsie_p(void);
extern int utc_wifi_manager_add_vsie_n(void);
extern int utc_wifi_manager_get_vsie_p(void);
extern int utc_wifi_manager_get_vsie_n(void);
extern int utc_wifi_manager_remove_vsie_p(void);
extern int utc_wifi_manager_remove_vsie_n(void);
extern int utc_wifi_manager_set_ip_conflict_cb_n(void);
extern int utc_wifi_manager_unset_ip_conflict_cb_n(void);
extern int utc_wifi_manager_set_ip_conflict_detect_enable_p(void);
extern int utc_wifi_manager_set_ip_conflict_detect_enable_n(void);
extern int utc_wifi_manager_ip_conflict_detect_is_enabled_p(void);
extern int utc_wifi_manager_ip_conflict_detect_is_enabled_n(void);
extern int utc_wifi_manager_get_ip_conflict_state_p(void);
extern int utc_wifi_manager_get_ip_conflict_state_n(void);
extern int utc_wifi_manager_is_5ghz_band_supported_p(void);
extern int utc_wifi_manager_is_5ghz_band_supported_n1(void);
extern int utc_wifi_manager_is_5ghz_band_supported_n2(void);
extern int utc_wifi_manager_specific_scan_get_max_ssids_p(void);
extern int utc_wifi_manager_specific_scan_get_max_ssids_n1(void);
extern int utc_wifi_manager_specific_scan_get_max_ssids_n2(void);
extern int utc_wifi_manager_ap_get_eap_anonymous_identity_p(void);
extern int utc_wifi_manager_ap_get_eap_anonymous_identity_n1(void);
extern int utc_wifi_manager_ap_get_eap_anonymous_identity_n2(void);
extern int utc_wifi_manager_ap_set_eap_anonymous_identity_p(void);
extern int utc_wifi_manager_ap_set_eap_anonymous_identity_n1(void);
extern int utc_wifi_manager_ap_set_eap_anonymous_identity_n2(void);
extern int utc_wifi_manager_ap_is_hidden_p(void);
extern int utc_wifi_manager_ap_is_hidden_n1(void);
extern int utc_wifi_manager_ap_is_hidden_n2(void);

testcase tc_array[] = {
    {"utc_wifi_manager_ap_create_p", utc_wifi_manager_ap_create_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_create_n", utc_wifi_manager_ap_create_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_hidden_create_p", utc_wifi_manager_ap_hidden_create_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_hidden_create_n", utc_wifi_manager_ap_hidden_create_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_clone_p", utc_wifi_manager_ap_clone_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_clone_n", utc_wifi_manager_ap_clone_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_essid_p", utc_wifi_manager_ap_get_essid_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_essid_n", utc_wifi_manager_ap_get_essid_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_raw_ssid_p", utc_wifi_manager_ap_get_raw_ssid_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_raw_ssid_n", utc_wifi_manager_ap_get_raw_ssid_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_bssid_p", utc_wifi_manager_ap_get_bssid_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_bssid_n", utc_wifi_manager_ap_get_bssid_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_rssi_p", utc_wifi_manager_ap_get_rssi_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_rssi_n", utc_wifi_manager_ap_get_rssi_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_rssi_level_p", utc_wifi_manager_ap_get_rssi_level_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_rssi_level_n", utc_wifi_manager_ap_get_rssi_level_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_frequency_p", utc_wifi_manager_ap_get_frequency_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_frequency_n", utc_wifi_manager_ap_get_frequency_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_max_speed_p", utc_wifi_manager_ap_get_max_speed_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_max_speed_n", utc_wifi_manager_ap_get_max_speed_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_favorite_p", utc_wifi_manager_ap_is_favorite_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_favorite_n", utc_wifi_manager_ap_is_favorite_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_passpoint_p", utc_wifi_manager_ap_is_passpoint_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_passpoint_n", utc_wifi_manager_ap_is_passpoint_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_connection_state_p", utc_wifi_manager_ap_get_connection_state_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_connection_state_n", utc_wifi_manager_ap_get_connection_state_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_ip_config_type_p", utc_wifi_manager_ap_get_ip_config_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_ip_config_type_n", utc_wifi_manager_ap_get_ip_config_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_ip_config_type_p", utc_wifi_manager_ap_set_ip_config_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_ip_config_type_n", utc_wifi_manager_ap_set_ip_config_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_ip_address_p", utc_wifi_manager_ap_get_ip_address_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_ip_address_n", utc_wifi_manager_ap_get_ip_address_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_ip_address_p", utc_wifi_manager_ap_set_ip_address_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_ip_address_n", utc_wifi_manager_ap_set_ip_address_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_subnet_mask_p", utc_wifi_manager_ap_get_subnet_mask_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_subnet_mask_n", utc_wifi_manager_ap_get_subnet_mask_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_subnet_mask_p", utc_wifi_manager_ap_set_subnet_mask_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_subnet_mask_n", utc_wifi_manager_ap_set_subnet_mask_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_gateway_address_p", utc_wifi_manager_ap_get_gateway_address_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_gateway_address_n", utc_wifi_manager_ap_get_gateway_address_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_gateway_address_p", utc_wifi_manager_ap_set_gateway_address_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_gateway_address_n", utc_wifi_manager_ap_set_gateway_address_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_dhcp_server_address_p", utc_wifi_manager_ap_get_dhcp_server_address_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_dhcp_server_address_n", utc_wifi_manager_ap_get_dhcp_server_address_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_dhcp_lease_duration_p", utc_wifi_manager_ap_get_dhcp_lease_duration_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_dhcp_lease_duration_n", utc_wifi_manager_ap_get_dhcp_lease_duration_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_proxy_address_p", utc_wifi_manager_ap_get_proxy_address_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_proxy_address_n", utc_wifi_manager_ap_get_proxy_address_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_proxy_address_p", utc_wifi_manager_ap_set_proxy_address_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_proxy_address_n", utc_wifi_manager_ap_set_proxy_address_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_proxy_type_p", utc_wifi_manager_ap_get_proxy_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_proxy_type_n", utc_wifi_manager_ap_get_proxy_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_proxy_type_p", utc_wifi_manager_ap_set_proxy_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_proxy_type_n", utc_wifi_manager_ap_set_proxy_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_dns_address_p", utc_wifi_manager_ap_get_dns_address_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_dns_address_n", utc_wifi_manager_ap_get_dns_address_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_dns_address_p", utc_wifi_manager_ap_set_dns_address_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_dns_address_n", utc_wifi_manager_ap_set_dns_address_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_security_type_p", utc_wifi_manager_ap_get_security_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_security_type_n", utc_wifi_manager_ap_get_security_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_security_type_p", utc_wifi_manager_ap_set_security_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_security_type_n", utc_wifi_manager_ap_set_security_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_encryption_type_p", utc_wifi_manager_ap_get_encryption_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_encryption_type_n", utc_wifi_manager_ap_get_encryption_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_encryption_type_p", utc_wifi_manager_ap_set_encryption_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_encryption_type_n", utc_wifi_manager_ap_set_encryption_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_passphrase_required_p", utc_wifi_manager_ap_is_passphrase_required_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_passphrase_required_n", utc_wifi_manager_ap_is_passphrase_required_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_passphrase_p", utc_wifi_manager_ap_set_passphrase_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_passphrase_n", utc_wifi_manager_ap_set_passphrase_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_wps_supported_p", utc_wifi_manager_ap_is_wps_supported_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_wps_supported_n", utc_wifi_manager_ap_is_wps_supported_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_passphrase_p", utc_wifi_manager_ap_set_eap_passphrase_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_passphrase_n", utc_wifi_manager_ap_set_eap_passphrase_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_passphrase_p", utc_wifi_manager_ap_get_eap_passphrase_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_passphrase_n", utc_wifi_manager_ap_get_eap_passphrase_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_ca_cert_file_p", utc_wifi_manager_ap_get_eap_ca_cert_file_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_ca_cert_file_n", utc_wifi_manager_ap_get_eap_ca_cert_file_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_ca_cert_file_p", utc_wifi_manager_ap_set_eap_ca_cert_file_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_ca_cert_file_n", utc_wifi_manager_ap_set_eap_ca_cert_file_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_client_cert_file_p", utc_wifi_manager_ap_get_eap_client_cert_file_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_client_cert_file_n", utc_wifi_manager_ap_get_eap_client_cert_file_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_client_cert_file_p", utc_wifi_manager_ap_set_eap_client_cert_file_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_client_cert_file_n", utc_wifi_manager_ap_set_eap_client_cert_file_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_private_key_file_p", utc_wifi_manager_ap_get_eap_private_key_file_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_private_key_file_n", utc_wifi_manager_ap_get_eap_private_key_file_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_private_key_info_p", utc_wifi_manager_ap_set_eap_private_key_info_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_private_key_info_n", utc_wifi_manager_ap_set_eap_private_key_info_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_type_p", utc_wifi_manager_ap_get_eap_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_type_n", utc_wifi_manager_ap_get_eap_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_type_p", utc_wifi_manager_ap_set_eap_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_type_n", utc_wifi_manager_ap_set_eap_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_auth_type_p", utc_wifi_manager_ap_get_eap_auth_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_auth_type_n", utc_wifi_manager_ap_get_eap_auth_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_auth_type_p", utc_wifi_manager_ap_set_eap_auth_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_auth_type_n", utc_wifi_manager_ap_set_eap_auth_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_disconnect_reason_p", utc_wifi_manager_ap_get_disconnect_reason_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_disconnect_reason_n", utc_wifi_manager_ap_get_disconnect_reason_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_refresh_p", utc_wifi_manager_ap_refresh_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_refresh_n", utc_wifi_manager_ap_refresh_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_get_error_state_p", utc_wifi_manager_ap_get_error_state_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_get_error_state_n", utc_wifi_manager_ap_get_error_state_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_get_prefix_length_p", utc_wifi_manager_ap_get_prefix_length_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_get_prefix_length_n", utc_wifi_manager_ap_get_prefix_length_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_set_prefix_length_p", utc_wifi_manager_ap_set_prefix_length_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_set_prefix_length_n", utc_wifi_manager_ap_set_prefix_length_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_get_dns_config_type_p", utc_wifi_manager_ap_get_dns_config_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_get_dns_config_type_n", utc_wifi_manager_ap_get_dns_config_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_set_dns_config_type_p", utc_wifi_manager_ap_set_dns_config_type_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_set_dns_config_type_n", utc_wifi_manager_ap_set_dns_config_type_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_foreach_ipv6_address_p", utc_wifi_manager_ap_foreach_ipv6_address_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
	{"utc_wifi_manager_ap_foreach_ipv6_address_n", utc_wifi_manager_ap_foreach_ipv6_address_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_assoc_status_code_p", utc_wifi_manager_ap_get_assoc_status_code_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_assoc_status_code_n", utc_wifi_manager_ap_get_assoc_status_code_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_foreach_vsie_p", utc_wifi_manager_ap_foreach_vsie_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_foreach_vsie_n", utc_wifi_manager_ap_foreach_vsie_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_destroy_p", utc_wifi_manager_ap_destroy_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_destroy_n", utc_wifi_manager_ap_destroy_n, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_config_create_p", utc_wifi_manager_config_create_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_create_n", utc_wifi_manager_config_create_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_save_p", utc_wifi_manager_config_save_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_save_n", utc_wifi_manager_config_save_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_destroy_p", utc_wifi_manager_config_destroy_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_destroy_n", utc_wifi_manager_config_destroy_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_foreach_configuration_p", utc_wifi_manager_config_foreach_configuration_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_foreach_configuration_n", utc_wifi_manager_config_foreach_configuration_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_clone_p", utc_wifi_manager_config_clone_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_clone_n", utc_wifi_manager_config_clone_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_remove_p", utc_wifi_manager_config_remove_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_remove_n", utc_wifi_manager_config_remove_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_name_p", utc_wifi_manager_config_get_name_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_name_n", utc_wifi_manager_config_get_name_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_security_type_p", utc_wifi_manager_config_get_security_type_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_security_type_n", utc_wifi_manager_config_get_security_type_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_proxy_address_p", utc_wifi_manager_config_set_proxy_address_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_proxy_address_n", utc_wifi_manager_config_set_proxy_address_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_proxy_address_p", utc_wifi_manager_config_get_proxy_address_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_proxy_address_n", utc_wifi_manager_config_get_proxy_address_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_hidden_ap_property_p", utc_wifi_manager_config_set_hidden_ap_property_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_hidden_ap_property_n", utc_wifi_manager_config_set_hidden_ap_property_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_hidden_ap_property_p", utc_wifi_manager_config_get_hidden_ap_property_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_hidden_ap_property_n", utc_wifi_manager_config_get_hidden_ap_property_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_anonymous_identity_p", utc_wifi_manager_config_get_eap_anonymous_identity_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_anonymous_identity_n", utc_wifi_manager_config_get_eap_anonymous_identity_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_anonymous_identity_p", utc_wifi_manager_config_set_eap_anonymous_identity_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_anonymous_identity_n", utc_wifi_manager_config_set_eap_anonymous_identity_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_ca_cert_file_p", utc_wifi_manager_config_get_eap_ca_cert_file_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_ca_cert_file_n", utc_wifi_manager_config_get_eap_ca_cert_file_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_ca_cert_file_p", utc_wifi_manager_config_set_eap_ca_cert_file_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_ca_cert_file_n", utc_wifi_manager_config_set_eap_ca_cert_file_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_client_cert_file_p", utc_wifi_manager_config_get_eap_client_cert_file_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_client_cert_file_n", utc_wifi_manager_config_get_eap_client_cert_file_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_client_cert_file_p", utc_wifi_manager_config_set_eap_client_cert_file_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_client_cert_file_n", utc_wifi_manager_config_set_eap_client_cert_file_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_identity_p", utc_wifi_manager_config_get_eap_identity_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_identity_n", utc_wifi_manager_config_get_eap_identity_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_identity_p", utc_wifi_manager_config_set_eap_identity_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_identity_n", utc_wifi_manager_config_set_eap_identity_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_type_p", utc_wifi_manager_config_get_eap_type_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_type_n", utc_wifi_manager_config_get_eap_type_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_type_p", utc_wifi_manager_config_set_eap_type_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_type_n", utc_wifi_manager_config_set_eap_type_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_auth_type_p", utc_wifi_manager_config_get_eap_auth_type_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_auth_type_n", utc_wifi_manager_config_get_eap_auth_type_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_auth_type_p", utc_wifi_manager_config_set_eap_auth_type_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_auth_type_n", utc_wifi_manager_config_set_eap_auth_type_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_subject_match_p", utc_wifi_manager_config_get_eap_subject_match_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_subject_match_n", utc_wifi_manager_config_get_eap_subject_match_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_subject_match_p", utc_wifi_manager_config_set_eap_subject_match_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_subject_match_n", utc_wifi_manager_config_set_eap_subject_match_n, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_private_key_info_p", utc_wifi_manager_config_set_eap_private_key_info_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_eap_private_key_info_n1", utc_wifi_manager_config_set_eap_private_key_info_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_private_key_file_p", utc_wifi_manager_config_get_eap_private_key_file_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_eap_private_key_file_n1", utc_wifi_manager_config_get_eap_private_key_file_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_ip_config_type_p", utc_wifi_manager_config_set_ip_config_type_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_ip_config_type_n1", utc_wifi_manager_config_set_ip_config_type_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_ip_config_type_p", utc_wifi_manager_config_get_ip_config_type_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_ip_config_type_n1", utc_wifi_manager_config_get_ip_config_type_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_ip_address_p", utc_wifi_manager_config_set_ip_address_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_ip_address_n1", utc_wifi_manager_config_set_ip_address_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_ip_address_p", utc_wifi_manager_config_get_ip_address_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_ip_address_n1", utc_wifi_manager_config_get_ip_address_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_subnet_mask_p", utc_wifi_manager_config_set_subnet_mask_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_subnet_mask_n1", utc_wifi_manager_config_set_subnet_mask_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_subnet_mask_p", utc_wifi_manager_config_get_subnet_mask_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_subnet_mask_n1", utc_wifi_manager_config_get_subnet_mask_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_gateway_address_p", utc_wifi_manager_config_set_gateway_address_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_gateway_address_n1", utc_wifi_manager_config_set_gateway_address_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_gateway_address_p", utc_wifi_manager_config_get_gateway_address_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_gateway_address_n1", utc_wifi_manager_config_get_gateway_address_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_dns_config_type_p", utc_wifi_manager_config_set_dns_config_type_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_dns_config_type_n1", utc_wifi_manager_config_set_dns_config_type_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_dns_config_type_p", utc_wifi_manager_config_get_dns_config_type_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_dns_config_type_n1", utc_wifi_manager_config_get_dns_config_type_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_dns_address_p", utc_wifi_manager_config_set_dns_address_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_dns_address_n1", utc_wifi_manager_config_set_dns_address_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_dns_address_p", utc_wifi_manager_config_get_dns_address_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_dns_address_n1", utc_wifi_manager_config_get_dns_address_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_prefix_length_p", utc_wifi_manager_config_set_prefix_length_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_set_prefix_length_n1", utc_wifi_manager_config_set_prefix_length_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_prefix_length_p", utc_wifi_manager_config_get_prefix_length_p, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_config_get_prefix_length_n1", utc_wifi_manager_config_get_prefix_length_n1, utc_wifi_manager_config_startup, utc_wifi_manager_config_cleanup},
    {"utc_wifi_manager_initialize_p", utc_wifi_manager_initialize_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_initialize_n", utc_wifi_manager_initialize_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_activate_n", utc_wifi_manager_activate_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_activate_p", utc_wifi_manager_activate_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_activate_with_wifi_picker_tested_n", utc_wifi_manager_activate_with_wifi_picker_tested_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_activate_with_wifi_picker_tested_p", utc_wifi_manager_activate_with_wifi_picker_tested_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_is_activated_p", utc_wifi_manager_is_activated_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_is_activated_n", utc_wifi_manager_is_activated_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_connection_state_p", utc_wifi_manager_get_connection_state_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_connection_state_n", utc_wifi_manager_get_connection_state_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_module_state_p", utc_wifi_manager_get_module_state_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_module_state_n", utc_wifi_manager_get_module_state_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_mac_address_p", utc_wifi_manager_get_mac_address_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_mac_address_n", utc_wifi_manager_get_mac_address_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_foreach_found_ap_p", utc_wifi_manager_foreach_found_ap_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_foreach_found_ap_n", utc_wifi_manager_foreach_found_ap_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_scan_specific_ap_n", utc_wifi_manager_scan_specific_ap_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_scan_specific_ap_p", utc_wifi_manager_scan_specific_ap_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_bssid_scan_n", utc_wifi_manager_bssid_scan_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_bssid_scan_p", utc_wifi_manager_bssid_scan_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_foreach_found_specific_ap_n", utc_wifi_manager_foreach_found_specific_ap_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_foreach_found_specific_ap_p", utc_wifi_manager_foreach_found_specific_ap_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_foreach_found_bssid_ap_n", utc_wifi_manager_foreach_found_bssid_ap_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_foreach_found_bssid_ap_p", utc_wifi_manager_foreach_found_bssid_ap_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_device_state_changed_cb_p", utc_wifi_manager_set_device_state_changed_cb_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_device_state_changed_cb_n", utc_wifi_manager_set_device_state_changed_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_unset_device_state_changed_cb_p", utc_wifi_manager_unset_device_state_changed_cb_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_unset_device_state_changed_cb_n", utc_wifi_manager_unset_device_state_changed_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_background_scan_cb_p", utc_wifi_manager_set_background_scan_cb_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_background_scan_cb_n", utc_wifi_manager_set_background_scan_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_unset_background_scan_cb_p", utc_wifi_manager_unset_background_scan_cb_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_unset_background_scan_cb_n", utc_wifi_manager_unset_background_scan_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
	{"utc_wifi_manager_set_scan_state_changed_cb_p", utc_wifi_manager_set_scan_state_changed_cb_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
	{"utc_wifi_manager_set_scan_state_changed_cb_n", utc_wifi_manager_set_scan_state_changed_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
	{"utc_wifi_manager_unset_scan_state_changed_cb_p", utc_wifi_manager_unset_scan_state_changed_cb_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
	{"utc_wifi_manager_unset_scan_state_changed_cb_n", utc_wifi_manager_unset_scan_state_changed_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_connection_state_changed_cb_p", utc_wifi_manager_set_connection_state_changed_cb_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_connection_state_changed_cb_n", utc_wifi_manager_set_connection_state_changed_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_unset_connection_state_changed_cb_p", utc_wifi_manager_unset_connection_state_changed_cb_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_unset_connection_state_changed_cb_n", utc_wifi_manager_unset_connection_state_changed_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_rssi_level_changed_cb_p", utc_wifi_manager_set_rssi_level_changed_cb_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_rssi_level_changed_cb_n", utc_wifi_manager_set_rssi_level_changed_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_unset_rssi_level_changed_cb_p", utc_wifi_manager_unset_rssi_level_changed_cb_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_unset_rssi_level_changed_cb_n", utc_wifi_manager_unset_rssi_level_changed_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_module_state_changed_cb_n", utc_wifi_manager_set_module_state_changed_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_unset_module_state_changed_cb_n", utc_wifi_manager_unset_module_state_changed_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_deinitialize_p", utc_wifi_manager_deinitialize_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_deinitialize_n", utc_wifi_manager_deinitialize_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_network_interface_name_p", utc_wifi_manager_get_network_interface_name_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_network_interface_name_n", utc_wifi_manager_get_network_interface_name_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_scan_p", utc_wifi_manager_scan_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_scan_n", utc_wifi_manager_scan_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
	{"utc_wifi_manager_get_scan_state_p", utc_wifi_manager_get_scan_state_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
	{"utc_wifi_manager_get_scan_state_n", utc_wifi_manager_get_scan_state_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_deactivate_n", utc_wifi_manager_deactivate_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_deactivate_p", utc_wifi_manager_deactivate_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_connect_n", utc_wifi_manager_connect_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_connect_p", utc_wifi_manager_connect_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_connect_hidden_ap_n", utc_wifi_manager_connect_hidden_ap_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_connect_hidden_ap_n2", utc_wifi_manager_connect_hidden_ap_n2, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_connect_hidden_ap_p", utc_wifi_manager_connect_hidden_ap_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_update_ap_n", utc_wifi_manager_update_ap_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_update_ap_p", utc_wifi_manager_update_ap_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_disconnect_n", utc_wifi_manager_disconnect_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_disconnect_p", utc_wifi_manager_disconnect_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_connect_by_wps_pin_n", utc_wifi_manager_connect_by_wps_pin_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_connect_by_wps_pbc_n", utc_wifi_manager_connect_by_wps_pbc_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_connect_by_wps_pin_without_ssid_n", utc_wifi_manager_connect_by_wps_pin_without_ssid_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_connect_by_wps_pbc_without_ssid_n", utc_wifi_manager_connect_by_wps_pbc_without_ssid_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_cancel_wps_n", utc_wifi_manager_cancel_wps_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_connected_ap_p", utc_wifi_manager_get_connected_ap_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_connected_ap_n", utc_wifi_manager_get_connected_ap_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_forget_ap_n", utc_wifi_manager_forget_ap_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_forget_ap_p", utc_wifi_manager_forget_ap_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_forget_ap_async_n", utc_wifi_manager_forget_ap_async_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_forget_ap_async_p", utc_wifi_manager_forget_ap_async_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
	{"utc_wifi_manager_tdls_start_discovery_n", utc_wifi_manager_tdls_start_discovery_n, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
	{"utc_wifi_manager_tdls_connect_n", utc_wifi_manager_tdls_connect_n, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
    {"utc_wifi_manager_tdls_disconnect_n", utc_wifi_manager_tdls_disconnect_n, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
	{"utc_wifi_manager_tdls_enable_channel_switching_n", utc_wifi_manager_tdls_enable_channel_switching_n, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
	{"utc_wifi_manager_tdls_disable_channel_switching_n", utc_wifi_manager_tdls_disable_channel_switching_n, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
	{"utc_wifi_manager_tdls_set_discovered_cb_p", utc_wifi_manager_tdls_set_discovered_cb_p, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
	{"utc_wifi_manager_tdls_set_discovered_cb_n", utc_wifi_manager_tdls_set_discovered_cb_n, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
	{"utc_wifi_manager_tdls_unset_discovered_cb_p", utc_wifi_manager_tdls_unset_discovered_cb_p, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
	{"utc_wifi_manager_tdls_unset_discovered_cb_n", utc_wifi_manager_tdls_unset_discovered_cb_n, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
    {"utc_wifi_manager_tdls_get_connected_peer_n", utc_wifi_manager_tdls_get_connected_peer_n, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
    {"utc_wifi_manager_tdls_set_state_changed_cb_p", utc_wifi_manager_tdls_set_state_changed_cb_p, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
    {"utc_wifi_manager_tdls_set_state_changed_cb_n", utc_wifi_manager_tdls_set_state_changed_cb_n, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
    {"utc_wifi_manager_tdls_unset_state_changed_cb_p", utc_wifi_manager_tdls_unset_state_changed_cb_p, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
    {"utc_wifi_manager_tdls_unset_state_changed_cb_n", utc_wifi_manager_tdls_unset_state_changed_cb_n, utc_wifi_manager_tdls_startup, utc_wifi_manager_tdls_cleanup},
    {"utc_wifi_manager_specific_scan_create_p", utc_wifi_manager_specific_scan_create_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_scan_create_n", utc_wifi_manager_specific_scan_create_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_scan_destroy_p", utc_wifi_manager_specific_scan_destroy_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_scan_destroy_n", utc_wifi_manager_specific_scan_destroy_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_scan_set_ssid_p", utc_wifi_manager_specific_scan_set_ssid_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_scan_set_ssid_n", utc_wifi_manager_specific_scan_set_ssid_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_scan_set_freq_p", utc_wifi_manager_specific_scan_set_freq_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_scan_set_freq_n", utc_wifi_manager_specific_scan_set_freq_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_ap_start_multi_scan_p", utc_wifi_manager_specific_ap_start_multi_scan_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_ap_start_multi_scan_n", utc_wifi_manager_specific_ap_start_multi_scan_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_add_vsie_p", utc_wifi_manager_add_vsie_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_add_vsie_n", utc_wifi_manager_add_vsie_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_vsie_p", utc_wifi_manager_get_vsie_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_vsie_n", utc_wifi_manager_get_vsie_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_remove_vsie_p", utc_wifi_manager_remove_vsie_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_remove_vsie_n", utc_wifi_manager_remove_vsie_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_ip_conflict_cb_n", utc_wifi_manager_set_ip_conflict_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_unset_ip_conflict_cb_n", utc_wifi_manager_unset_ip_conflict_cb_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_ip_conflict_detect_enable_p", utc_wifi_manager_set_ip_conflict_detect_enable_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_set_ip_conflict_detect_enable_n", utc_wifi_manager_set_ip_conflict_detect_enable_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_ip_conflict_detect_is_enabled_p", utc_wifi_manager_ip_conflict_detect_is_enabled_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_ip_conflict_detect_is_enabled_n", utc_wifi_manager_ip_conflict_detect_is_enabled_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_ip_conflict_state_p", utc_wifi_manager_get_ip_conflict_state_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_get_ip_conflict_state_n", utc_wifi_manager_get_ip_conflict_state_n, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_is_5ghz_band_supported_p", utc_wifi_manager_is_5ghz_band_supported_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_is_5ghz_band_supported_n1", utc_wifi_manager_is_5ghz_band_supported_n1, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_is_5ghz_band_supported_n2", utc_wifi_manager_is_5ghz_band_supported_n2, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_scan_get_max_ssids_p", utc_wifi_manager_specific_scan_get_max_ssids_p, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_scan_get_max_ssids_n1", utc_wifi_manager_specific_scan_get_max_ssids_n1, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_specific_scan_get_max_ssids_n2", utc_wifi_manager_specific_scan_get_max_ssids_n2, utc_wifi_manager_startup, utc_wifi_manager_cleanup},
    {"utc_wifi_manager_ap_get_eap_anonymous_identity_p", utc_wifi_manager_ap_get_eap_anonymous_identity_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_anonymous_identity_n1", utc_wifi_manager_ap_get_eap_anonymous_identity_n1, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_get_eap_anonymous_identity_n2", utc_wifi_manager_ap_get_eap_anonymous_identity_n2, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_anonymous_identity_p", utc_wifi_manager_ap_set_eap_anonymous_identity_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_anonymous_identity_n1", utc_wifi_manager_ap_set_eap_anonymous_identity_n1, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_set_eap_anonymous_identity_n2", utc_wifi_manager_ap_set_eap_anonymous_identity_n1, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_hidden_p", utc_wifi_manager_ap_is_hidden_p, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_hidden_n1", utc_wifi_manager_ap_is_hidden_n1, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {"utc_wifi_manager_ap_is_hidden_n2", utc_wifi_manager_ap_is_hidden_n2, utc_wifi_manager_ap_startup, utc_wifi_manager_ap_cleanup},
    {NULL, NULL}
};


#endif // __TCT_WIFI_MANAGER_NATIVE_H__
