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
#ifndef __TCT_CAPI-NETWORK-SOFTAP-NATIVE_H__
#define __TCT_CAPI-NETWORK-SOFTAP-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_softap_startup(void);
extern void ITs_softap_cleanup(void);
extern int ITs_softap_create_destroy_p(void);
extern int ITs_softap_is_enabled_p(void);
extern int ITs_softap_set_unset_enabled_cb_p(void);
extern int ITs_softap_set_unset_disabled_cb_p(void);
extern int ITs_softap_foreach_connected_clients_p(void);
extern int ITs_softap_set_unset_client_connection_state_changed_cb_p(void);
extern int ITs_softap_set_unset_security_type_changed_cb_p(void);
extern int ITs_softap_set_unset_ssid_visibility_changed_cb_p(void);
extern int ITs_softap_set_unset_passphrase_changed_cb_p(void);
extern int ITs_softap_set_get_security_type_p(void);
extern int ITs_softap_set_get_ssid_p(void);
extern int ITs_softap_set_get_ssid_visibility_p(void);
extern int ITs_softap_set_get_passphrase_p(void);
extern int ITs_softap_set_get_vendor_element_p(void);
extern int ITs_softap_set_get_channel_p(void);
extern int ITs_softap_enable_disable_dhcp_p(void);
extern int ITs_softap_is_dhcp_enabled_p(void);
extern int ITs_softap_enable_dhcp_with_range_p(void);
extern int ITs_softap_set_get_mode_p(void);

testcase tc_array[] = {
 {"ITs_softap_create_destroy_p", ITs_softap_create_destroy_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_is_enabled_p", ITs_softap_is_enabled_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_unset_enabled_cb_p", ITs_softap_set_unset_enabled_cb_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_unset_disabled_cb_p", ITs_softap_set_unset_disabled_cb_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_foreach_connected_clients_p", ITs_softap_foreach_connected_clients_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_unset_client_connection_state_changed_cb_p", ITs_softap_set_unset_client_connection_state_changed_cb_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_unset_security_type_changed_cb_p", ITs_softap_set_unset_security_type_changed_cb_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_unset_ssid_visibility_changed_cb_p", ITs_softap_set_unset_ssid_visibility_changed_cb_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_unset_passphrase_changed_cb_p", ITs_softap_set_unset_passphrase_changed_cb_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_get_security_type_p", ITs_softap_set_get_security_type_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_get_ssid_p", ITs_softap_set_get_ssid_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_get_ssid_visibility_p", ITs_softap_set_get_ssid_visibility_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_get_passphrase_p", ITs_softap_set_get_passphrase_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_get_vendor_element_p", ITs_softap_set_get_vendor_element_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_get_channel_p", ITs_softap_set_get_channel_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_enable_disable_dhcp_p", ITs_softap_enable_disable_dhcp_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_is_dhcp_enabled_p", ITs_softap_is_dhcp_enabled_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_enable_dhcp_with_range_p", ITs_softap_enable_dhcp_with_range_p, ITs_softap_startup, ITs_softap_cleanup},
 {"ITs_softap_set_get_mode_p", ITs_softap_set_get_mode_p, ITs_softap_startup, ITs_softap_cleanup},
 {NULL, NULL}
};
#endif //__TCT_CAPI-NETWORK-SOFTAP-NATIVE_H__

