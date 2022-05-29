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
#ifndef __TCT_SOFTAP_CORE_H__
#define __TCT_SOFTAP_CORE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_softap_startup(void);
extern void utc_softap_cleanup(void);

extern int utc_softap_create_n(void);
extern int utc_softap_create_p(void);
extern int utc_softap_destroy_n(void);
extern int utc_softap_destroy_p(void);
extern int utc_softap_is_enabled_n(void);
extern int utc_softap_is_enabled_p(void);
extern int utc_softap_get_mac_address_n(void);
extern int utc_softap_get_network_interface_name_n(void);
extern int utc_softap_set_ip_address_n(void);
extern int utc_softap_set_ip_address_p(void);
extern int utc_softap_get_ip_address_n(void);
extern int utc_softap_get_gateway_address_n(void);
extern int utc_softap_get_subnet_mask_n(void);
extern int utc_softap_foreach_connected_clients_n(void);
extern int utc_softap_foreach_connected_clients_p(void);
extern int utc_softap_set_enabled_cb_n(void);
extern int utc_softap_set_enabled_cb_p(void);
extern int utc_softap_unset_enabled_cb_n(void);
extern int utc_softap_unset_enabled_cb_p(void);
extern int utc_softap_set_disabled_cb_n(void);
extern int utc_softap_set_disabled_cb_p(void);
extern int utc_softap_unset_disabled_cb_n(void);
extern int utc_softap_unset_disabled_cb_p(void);
extern int utc_softap_set_client_connection_state_changed_cb_n(void);
extern int utc_softap_set_client_connection_state_changed_cb_p(void);
extern int utc_softap_unset_client_connection_state_changed_cb_n(void);
extern int utc_softap_unset_client_connection_state_changed_cb_p(void);
extern int utc_softap_set_security_type_changed_cb_n(void);
extern int utc_softap_set_security_type_changed_cb_p(void);
extern int utc_softap_unset_security_type_changed_cb_n(void);
extern int utc_softap_unset_security_type_changed_cb_p(void);
extern int utc_softap_set_ssid_visibility_changed_cb_n(void);
extern int utc_softap_set_ssid_visibility_changed_cb_p(void);
extern int utc_softap_unset_ssid_visibility_changed_cb_n(void);
extern int utc_softap_unset_ssid_visibility_changed_cb_p(void);
extern int utc_softap_set_passphrase_changed_cb_n(void);
extern int utc_softap_set_passphrase_changed_cb_p(void);
extern int utc_softap_unset_passphrase_changed_cb_n(void);
extern int utc_softap_unset_passphrase_changed_cb_p(void);
extern int utc_softap_set_security_type_n(void);
extern int utc_softap_set_security_type_p(void);
extern int utc_softap_get_security_type_n(void);
extern int utc_softap_get_security_type_p(void);
extern int utc_softap_set_ssid_n(void);
extern int utc_softap_set_ssid_p(void);
extern int utc_softap_get_ssid_n(void);
extern int utc_softap_get_ssid_p(void);
extern int utc_softap_set_ssid_visibility_n(void);
extern int utc_softap_set_ssid_visibility_p(void);
extern int utc_softap_get_ssid_visibility_n(void);
extern int utc_softap_get_ssid_visibility_p(void);
extern int utc_softap_set_passphrase_n(void);
extern int utc_softap_set_passphrase_p(void);
extern int utc_softap_get_passphrase_n(void);
extern int utc_softap_get_passphrase_p(void);
extern int utc_softap_push_wps_button_n(void);
extern int utc_softap_set_wps_pin_n(void);
extern int utc_softap_set_vendor_element_n(void);
extern int utc_softap_set_vendor_element_p(void);
extern int utc_softap_get_vendor_element_n(void);
extern int utc_softap_get_vendor_element_p(void);
extern int utc_softap_set_channel_n(void);
extern int utc_softap_set_channel_p(void);
extern int utc_softap_get_channel_n(void);
extern int utc_softap_get_channel_p(void);
extern int utc_softap_enable_dhcp_n(void);
extern int utc_softap_enable_dhcp_p(void);
extern int utc_softap_disable_dhcp_n(void);
extern int utc_softap_disable_dhcp_p(void);
extern int utc_softap_is_dhcp_enabled_n(void);
extern int utc_softap_is_dhcp_enabled_p(void);
extern int utc_softap_enable_dhcp_with_range_n(void);
extern int utc_softap_enable_dhcp_with_range_p(void);
extern int utc_softap_set_mode_n(void);
extern int utc_softap_set_mode_p(void);
extern int utc_softap_get_mode_n(void);
extern int utc_softap_get_mode_p(void);


testcase tc_array[] = {
    {"utc_softap_create_n", utc_softap_create_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_create_p", utc_softap_create_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_destroy_n", utc_softap_destroy_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_destroy_p", utc_softap_destroy_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_is_enabled_n", utc_softap_is_enabled_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_is_enabled_p", utc_softap_is_enabled_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_mac_address_n", utc_softap_get_mac_address_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_network_interface_name_n", utc_softap_get_network_interface_name_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_ip_address_n", utc_softap_set_ip_address_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_ip_address_p", utc_softap_set_ip_address_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_ip_address_n", utc_softap_get_ip_address_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_gateway_address_n", utc_softap_get_gateway_address_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_subnet_mask_n", utc_softap_get_subnet_mask_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_foreach_connected_clients_n", utc_softap_foreach_connected_clients_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_foreach_connected_clients_p", utc_softap_foreach_connected_clients_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_enabled_cb_n", utc_softap_set_enabled_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_enabled_cb_p", utc_softap_set_enabled_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_enabled_cb_n", utc_softap_unset_enabled_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_enabled_cb_p", utc_softap_unset_enabled_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_disabled_cb_n", utc_softap_set_disabled_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_disabled_cb_p", utc_softap_set_disabled_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_disabled_cb_n", utc_softap_unset_disabled_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_disabled_cb_p", utc_softap_unset_disabled_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_client_connection_state_changed_cb_n", utc_softap_set_client_connection_state_changed_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_client_connection_state_changed_cb_p", utc_softap_set_client_connection_state_changed_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_client_connection_state_changed_cb_n", utc_softap_unset_client_connection_state_changed_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_client_connection_state_changed_cb_p", utc_softap_unset_client_connection_state_changed_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_security_type_changed_cb_n", utc_softap_set_security_type_changed_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_security_type_changed_cb_p", utc_softap_set_security_type_changed_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_security_type_changed_cb_n", utc_softap_unset_security_type_changed_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_security_type_changed_cb_p", utc_softap_unset_security_type_changed_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_ssid_visibility_changed_cb_n", utc_softap_set_ssid_visibility_changed_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_ssid_visibility_changed_cb_p", utc_softap_set_ssid_visibility_changed_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_ssid_visibility_changed_cb_n", utc_softap_unset_ssid_visibility_changed_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_ssid_visibility_changed_cb_p", utc_softap_unset_ssid_visibility_changed_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_passphrase_changed_cb_n", utc_softap_set_passphrase_changed_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_passphrase_changed_cb_p", utc_softap_set_passphrase_changed_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_passphrase_changed_cb_n", utc_softap_unset_passphrase_changed_cb_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_unset_passphrase_changed_cb_p", utc_softap_unset_passphrase_changed_cb_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_security_type_n", utc_softap_set_security_type_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_security_type_p", utc_softap_set_security_type_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_security_type_n", utc_softap_get_security_type_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_security_type_p", utc_softap_get_security_type_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_ssid_n", utc_softap_set_ssid_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_ssid_p", utc_softap_set_ssid_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_ssid_n", utc_softap_get_ssid_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_ssid_p", utc_softap_get_ssid_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_ssid_visibility_n", utc_softap_set_ssid_visibility_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_ssid_visibility_p", utc_softap_set_ssid_visibility_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_ssid_visibility_n", utc_softap_get_ssid_visibility_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_ssid_visibility_p", utc_softap_get_ssid_visibility_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_passphrase_n", utc_softap_set_passphrase_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_set_passphrase_p", utc_softap_set_passphrase_p, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_passphrase_n", utc_softap_get_passphrase_n, utc_softap_startup, utc_softap_cleanup},
    {"utc_softap_get_passphrase_p", utc_softap_get_passphrase_p, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_push_wps_button_n", utc_softap_push_wps_button_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_set_wps_pin_n", utc_softap_set_wps_pin_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_set_vendor_element_n", utc_softap_set_vendor_element_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_set_vendor_element_p", utc_softap_set_vendor_element_p, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_get_vendor_element_n", utc_softap_get_vendor_element_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_get_vendor_element_p", utc_softap_get_vendor_element_p, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_set_channel_n", utc_softap_set_channel_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_set_channel_p", utc_softap_set_channel_p, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_get_channel_n", utc_softap_get_channel_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_get_channel_p", utc_softap_get_channel_p, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_enable_dhcp_n", utc_softap_enable_dhcp_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_enable_dhcp_p", utc_softap_enable_dhcp_p, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_disable_dhcp_n", utc_softap_disable_dhcp_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_disable_dhcp_p", utc_softap_disable_dhcp_p, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_is_dhcp_enabled_n", utc_softap_is_dhcp_enabled_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_is_dhcp_enabled_p", utc_softap_is_dhcp_enabled_p, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_enable_dhcp_with_range_n", utc_softap_enable_dhcp_with_range_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_enable_dhcp_with_range_p", utc_softap_enable_dhcp_with_range_p, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_set_mode_n", utc_softap_set_mode_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_set_mode_p", utc_softap_set_mode_p, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_get_mode_n", utc_softap_get_mode_n, utc_softap_startup, utc_softap_cleanup},
	{"utc_softap_get_mode_p", utc_softap_get_mode_p, utc_softap_startup, utc_softap_cleanup},
    {NULL, NULL}
};

#endif // __TCT_SOFTAP_CORE_H__
