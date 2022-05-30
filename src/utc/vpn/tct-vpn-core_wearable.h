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
#ifndef __TCT_VPN-NATIVE_H__
#define __TCT_VPN-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_vpn_startup(void);
extern void utc_vpn_cleanup(void);

extern int utc_vpn_vpnsvc_init_p(void);
extern int utc_vpn_vpnsvc_init_n(void);
extern int utc_vpn_vpnsvc_deinit_p(void);
extern int utc_vpn_vpnsvc_deinit_n(void);
extern int utc_vpn_vpnsvc_protect_p(void);
extern int utc_vpn_vpnsvc_protect_n(void);
extern int utc_vpn_vpnsvc_block_networks_p(void);
extern int utc_vpn_vpnsvc_block_networks_n(void);
extern int utc_vpn_vpnsvc_unblock_networks_p(void);
extern int utc_vpn_vpnsvc_unblock_networks_n(void);
extern int utc_vpn_vpnsvc_get_iface_fd_p(void);
extern int utc_vpn_vpnsvc_get_iface_fd_n(void);
extern int utc_vpn_vpnsvc_get_iface_index_p(void);
extern int utc_vpn_vpnsvc_get_iface_index_n(void);
extern int utc_vpn_vpnsvc_get_iface_name_p(void);
extern int utc_vpn_vpnsvc_get_iface_name_n(void);
extern int utc_vpn_vpnsvc_set_mtu_p(void);
extern int utc_vpn_vpnsvc_set_mtu_n(void);
extern int utc_vpn_vpnsvc_set_blocking_p(void);
extern int utc_vpn_vpnsvc_set_blocking_n(void);
extern int utc_vpn_vpnsvc_set_session_p(void);
extern int utc_vpn_vpnsvc_set_session_n(void);
extern int utc_vpn_vpnsvc_get_session_p(void);
extern int utc_vpn_vpnsvc_get_session_n(void);
extern int utc_vpn_vpnsvc_read_n(void);
extern int utc_vpn_vpnsvc_write_n(void);
extern int utc_vpn_vpnsvc_set_local_ip_address_n(void);
extern int utc_vpn_vpnsvc_set_local_ip_address_p(void);
extern int utc_vpn_vpnsvc_set_remote_ip_address_n(void);
extern int utc_vpn_vpnsvc_set_remote_ip_address_p(void);
extern int utc_vpn_vpnsvc_update_settings_n1(void);
extern int utc_vpn_vpnsvc_update_settings_n2(void);
extern int utc_vpn_vpnsvc_update_settings_p(void);
extern int utc_vpn_vpnsvc_add_route_n(void);
extern int utc_vpn_vpnsvc_remove_route_n(void);
extern int utc_vpn_vpnsvc_add_dns_server_n(void);
extern int utc_vpn_vpnsvc_remove_dns_server_n(void);

testcase tc_array[] = {
	{"utc_vpn_vpnsvc_init_p",utc_vpn_vpnsvc_init_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_init_n",utc_vpn_vpnsvc_init_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_deinit_p",utc_vpn_vpnsvc_deinit_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_deinit_n",utc_vpn_vpnsvc_deinit_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_protect_p",utc_vpn_vpnsvc_protect_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_protect_n",utc_vpn_vpnsvc_protect_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_block_networks_p",utc_vpn_vpnsvc_block_networks_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_block_networks_n",utc_vpn_vpnsvc_block_networks_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_unblock_networks_p",utc_vpn_vpnsvc_unblock_networks_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_unblock_networks_n",utc_vpn_vpnsvc_unblock_networks_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_get_iface_fd_p",utc_vpn_vpnsvc_get_iface_fd_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_get_iface_fd_n",utc_vpn_vpnsvc_get_iface_fd_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_get_iface_index_p",utc_vpn_vpnsvc_get_iface_index_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_get_iface_index_n",utc_vpn_vpnsvc_get_iface_index_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_get_iface_name_p",utc_vpn_vpnsvc_get_iface_name_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_get_iface_name_n",utc_vpn_vpnsvc_get_iface_name_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_set_mtu_p",utc_vpn_vpnsvc_set_mtu_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_set_mtu_n",utc_vpn_vpnsvc_set_mtu_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_set_blocking_p",utc_vpn_vpnsvc_set_blocking_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_set_blocking_n",utc_vpn_vpnsvc_set_blocking_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_set_session_p",utc_vpn_vpnsvc_set_session_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_set_session_n",utc_vpn_vpnsvc_set_session_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_get_session_p",utc_vpn_vpnsvc_get_session_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_get_session_n",utc_vpn_vpnsvc_get_session_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_read_n",utc_vpn_vpnsvc_read_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_write_n",utc_vpn_vpnsvc_write_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_set_local_ip_address_n",utc_vpn_vpnsvc_set_local_ip_address_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_set_local_ip_address_p",utc_vpn_vpnsvc_set_local_ip_address_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_set_remote_ip_address_n",utc_vpn_vpnsvc_set_remote_ip_address_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_set_remote_ip_address_p",utc_vpn_vpnsvc_set_remote_ip_address_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_update_settings_n1",utc_vpn_vpnsvc_update_settings_n1,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_update_settings_n2",utc_vpn_vpnsvc_update_settings_n2,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_update_settings_p",utc_vpn_vpnsvc_update_settings_p,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_add_route_n",utc_vpn_vpnsvc_add_route_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_remove_route_n",utc_vpn_vpnsvc_remove_route_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_add_dns_server_n",utc_vpn_vpnsvc_add_dns_server_n,utc_vpn_startup,utc_vpn_cleanup},
	{"utc_vpn_vpnsvc_remove_dns_server_n",utc_vpn_vpnsvc_remove_dns_server_n,utc_vpn_startup,utc_vpn_cleanup},
	{NULL, NULL}
};

#endif // __TCT_VPN-NATIVE_H__
