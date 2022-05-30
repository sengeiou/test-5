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
#ifndef __TCT_VPN-SERVICE-NATIVE_H__
#define __TCT_VPN-SERVICE-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_vpn_service_startup(void);
extern void ITs_vpn_service_cleanup(void);

extern int ITc_vpnsvc_init_deinit_p(void);
extern int ITc_vpnsvc_set_get_session_p(void);
extern int ITc_vpnsvc_get_iface_fd_p(void);
extern int ITc_vpnsvc_get_iface_index_p(void);
extern int ITc_vpnsvc_get_iface_name_p(void);
extern int ITc_vpnsvc_set_mtu_p(void);
extern int ITc_vpnsvc_set_blocking_p(void);
extern int ITc_vpnsvc_block_unblock_networks_p(void);
extern int ITc_vpnsvc_protect_p(void);
extern int ITc_vpnsvc_set_local_ip_address_p(void);
extern int ITc_vpnsvc_set_remote_ip_address_p(void);
extern int ITc_vpnsvc_update_settings_p(void);

testcase tc_array[] = {
	{"ITc_vpnsvc_init_deinit_p",ITc_vpnsvc_init_deinit_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_set_get_session_p",ITc_vpnsvc_set_get_session_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_get_iface_fd_p",ITc_vpnsvc_get_iface_fd_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_get_iface_index_p",ITc_vpnsvc_get_iface_index_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_get_iface_name_p",ITc_vpnsvc_get_iface_name_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_set_mtu_p",ITc_vpnsvc_set_mtu_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_set_blocking_p",ITc_vpnsvc_set_blocking_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_block_unblock_networks_p",ITc_vpnsvc_block_unblock_networks_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_protect_p",ITc_vpnsvc_protect_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_set_local_ip_address_p",ITc_vpnsvc_set_local_ip_address_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_set_remote_ip_address_p",ITc_vpnsvc_set_remote_ip_address_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{"ITc_vpnsvc_update_settings_p",ITc_vpnsvc_update_settings_p,ITs_vpn_service_startup,ITs_vpn_service_cleanup},
	{NULL, NULL}
};

#endif // __TCT_VPN-SERVICE-NATIVE_H__
