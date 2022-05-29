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
#include "assert.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

#include <system_info.h>
#include <vpn_service.h>

#define UTC_VPN_IF_VPNSVC_TEST "vpnsvc_test"
#define UTC_VPN_IF_WLAN "wlan0"
#define UTC_VPN_IF_JUNK "junk"
#define VPNSVC_IP4_STRING_LEN 16
#define TIMEOUT_SEC 30

vpnsvc_h g_handle = NULL;
static bool g_vpn_supported = true;

/**
 * @function		utc_vpn_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_vpn_startup(void)
{
	char *name = UTC_VPN_IF_VPNSVC_TEST;
	int ret = VPNSVC_ERROR_NONE;
	system_info_get_platform_bool("http://tizen.org/feature/network.vpn", &g_vpn_supported);
	int int_value;

	if(g_vpn_supported == false) {
		g_handle = NULL;
		return;
	}

	ret = vpnsvc_init(name, &g_handle);

	if(ret != VPNSVC_ERROR_NONE) {
		fprintf(stderr, "utc_vpn_startup(): Failed ret = %d\n", ret);
	}
	else {
		fprintf(stderr, "vpnsvc_init Success if_fd:%d index:%d\n", vpnsvc_get_iface_fd(g_handle, &int_value), vpnsvc_get_iface_index(g_handle, &int_value));
	}
}

/**
 * @function		utc_vpn_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_vpn_cleanup(void)
{
	if(g_handle) {
		vpnsvc_deinit(g_handle);
	}

	g_handle = NULL;
}


/**
 * @testcase		utc_vpn_vpnsvc_init_p
 * @since_tizen		3.0
 * @description		Initialize VPN interface
 * @scenario		Initialize and De-Initialize\n
 * 					VPN interface
 */
int utc_vpn_vpnsvc_init_p(void)
{
	char *name = UTC_VPN_IF_VPNSVC_TEST;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_init(NULL, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_deinit(g_handle);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	g_handle = NULL;

	ret = vpnsvc_init(name, &g_handle);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_init_n
 * @since_tizen		3.0
 * @description		vpnsvc_init should fail on Invalid parameter
 * @scenario		Check vpnsvc_init by passing invalid vpnsvc_h as parameter
 */
int utc_vpn_vpnsvc_init_n(void)
{
	char *name = NULL;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_init(NULL, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}


	//Invalid Parameter
	ret = vpnsvc_init(name, &g_handle);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_deinit_p
 * @since_tizen		3.0
 * @description		De-Initialize VPN interface
 * @scenario		Initialize and De-Initialize\n
 * 					VPN interface
 */
int utc_vpn_vpnsvc_deinit_p(void)
{
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_deinit(NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_deinit(g_handle);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	g_handle = NULL;

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_deinit_n
 * @since_tizen		3.0
 * @description		vpnsvc_deinit should fail on Invalid parameter
 * @scenario		Check vpnsvc_deinit by passing invalid vpnsvc_h as parameter
 */
int utc_vpn_vpnsvc_deinit_n(void)
{
	int ret = VPNSVC_ERROR_NONE;
	vpnsvc_h null_handle = NULL;

	if(g_vpn_supported == false) {
		ret = vpnsvc_deinit(null_handle);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	//Invalid Parameter
	ret = vpnsvc_deinit(null_handle);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_protect_p
 * @since_tizen		3.0
 * @description		Prevent the VPN traffic routed to itself
 * @scenario		Prevent the VPN traffic
 */
int utc_vpn_vpnsvc_protect_p(void)
{
	int ret = VPNSVC_ERROR_NONE;
	int sock;
	char *interface = UTC_VPN_IF_WLAN;

	if(g_vpn_supported == false) {
		ret = vpnsvc_protect(NULL, 0, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	if ((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "socket failed\n");
		return 1;
	}

	ret = vpnsvc_protect(g_handle, sock, interface);
	close(sock);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_protect_n
 * @since_tizen		3.0
 * @description		vpnsvc_protect should fail on Invalid parameter
 * @scenario		Check vpnsvc_protect by passing invalid interface as parameter
 */
int utc_vpn_vpnsvc_protect_n(void)
{
	int ret = VPNSVC_ERROR_NONE;
	int sock;
	char *interface = UTC_VPN_IF_JUNK;
	vpnsvc_h null_handle = NULL;

	if(g_vpn_supported == false) {
		ret = vpnsvc_protect(NULL, 0, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	if ((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "socket failed\n");
		return 1;
    }

	ret = vpnsvc_protect(null_handle, sock, interface);
	close(sock);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_block_networks_p
 * @since_tizen		3.0
 * @description		Block traffic except specified allowing networks
 * @scenario		check the vpnsvc_block_networks api
 */
int utc_vpn_vpnsvc_block_networks_p(void)
{
	char* block_nets[2];
	int block_prefix[2];
	int block_nr_nets = 2;
	char* allow_nets[2];
	int allow_prefix[2];
	int allow_nr_nets = 2;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_block_networks(NULL, NULL, NULL, 0, NULL, NULL, 0);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	block_nets[0] = malloc(sizeof(char) * VPNSVC_IP4_STRING_LEN);
	block_nets[1] = malloc(sizeof(char) * VPNSVC_IP4_STRING_LEN);
	memset(block_nets[0], 0, sizeof(char) * VPNSVC_IP4_STRING_LEN);
	memset(block_nets[1], 0, sizeof(char) * VPNSVC_IP4_STRING_LEN);
	strncpy(block_nets[0], "125.209.222.141", VPNSVC_IP4_STRING_LEN);
	block_prefix[0] = 32;
	strncpy(block_nets[1], "180.70.134.19", VPNSVC_IP4_STRING_LEN);
	block_prefix[1] = 32;

	allow_nets[0] = malloc(sizeof(char) * VPNSVC_IP4_STRING_LEN);
	allow_nets[1] = malloc(sizeof(char) * VPNSVC_IP4_STRING_LEN);
	memset(allow_nets[0], 0, sizeof(char) * VPNSVC_IP4_STRING_LEN);
	memset(allow_nets[1], 0, sizeof(char) * VPNSVC_IP4_STRING_LEN);
	strncpy(allow_nets[0], "216.58.221.142", VPNSVC_IP4_STRING_LEN);
	allow_prefix[0] = 32;
	strncpy(allow_nets[1], "206.190.36.45", VPNSVC_IP4_STRING_LEN);
	allow_prefix[1] = 32;

	ret = vpnsvc_block_networks(g_handle, block_nets, block_prefix, block_nr_nets, allow_nets, allow_prefix, allow_nr_nets);

	free(block_nets[0]);
	free(block_nets[1]);
	free(allow_nets[0]);
	free(allow_nets[1]);

	assert_eq(ret, VPNSVC_ERROR_NONE);

	ret = vpnsvc_unblock_networks(g_handle);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_block_networks_n
 * @since_tizen		3.0
 * @description		vpnsvc_block_networks should fail on Invalid parameter
 * @scenario		Check vpnsvc_block_networks by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_block_networks_n(void)
{
	vpnsvc_h null_handle = NULL;
	char* block_nets[2];
	int block_prefix[2];
	int block_nr_nets = 2;
	char* allow_nets[2];
	int allow_prefix[2];
	int allow_nr_nets = 2;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_block_networks(NULL, NULL, NULL, 0, NULL, NULL, 0);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_block_networks(null_handle, block_nets, block_prefix, block_nr_nets, allow_nets, allow_prefix, allow_nr_nets);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_unblock_networks_p
 * @since_tizen		3.0
 * @description		Remove restrictions imposed by vpnsvc_block_network
 * @scenario		check vpnsvc_unblock_networks by passing valid vpnsvc_h handle
 */
int utc_vpn_vpnsvc_unblock_networks_p(void)
{
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_unblock_networks(NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_unblock_networks(g_handle);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_unblock_networks_n
 * @since_tizen		3.0
 * @description		vpnsvc_unblock_networks should fail on Invalid parameter
 * @scenario		Check vpnsvc_unblock_networks by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_unblock_networks_n(void)
{
	vpnsvc_h null_handle = NULL;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_unblock_networks(null_handle);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_unblock_networks(null_handle);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_get_iface_fd_p
 * @since_tizen		3.0
 * @description		Get fd of VPN interface
 * @scenario		check vpnsvc_get_iface_fd by passing valid vpnsvc_h handle
 */
int utc_vpn_vpnsvc_get_iface_fd_p(void)
{
	int sock;
	int int_value;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_get_iface_fd(NULL, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	sock = vpnsvc_get_iface_fd(g_handle, &int_value);
	if(sock != 0) {
        fprintf(stderr, "invalid fd\n");
        return 1;
    }

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_get_iface_fd_n
 * @since_tizen		3.0
 * @description		vpnsvc_get_iface_fd should fail on Invalid parameter
 * @scenario		Check vpnsvc_get_iface_fd by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_get_iface_fd_n(void)
{
	vpnsvc_h null_handle = NULL;
	int sock;
	int ret = VPNSVC_ERROR_NONE;
	int int_value;

	if(g_vpn_supported == false) {
		ret = vpnsvc_get_iface_fd(null_handle, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	sock = vpnsvc_get_iface_fd(null_handle, &int_value);
	assert_eq(sock, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_get_iface_index_p
 * @since_tizen		3.0
 * @description		Get index of VPN interface
 * @scenario		check vpnsvc_get_iface_index by passing valid vpnsvc_h handle
 */
int utc_vpn_vpnsvc_get_iface_index_p(void)
{
	int index;
	int int_value;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_get_iface_index(NULL, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	index = vpnsvc_get_iface_index(g_handle, &int_value);
	if(index != 0) {
        fprintf(stderr, "invalid index\n");
        return 1;
    }

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_get_iface_index_n
 * @since_tizen		3.0
 * @description		vpnsvc_get_iface_index should fail on Invalid parameter
 * @scenario		Check vpnsvc_get_iface_index by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_get_iface_index_n(void)
{
	vpnsvc_h null_handle = NULL;
	int index;
	int ret = VPNSVC_ERROR_NONE;
	int int_value;

	if(g_vpn_supported == false) {
		ret = vpnsvc_get_iface_index(null_handle, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	index = vpnsvc_get_iface_index(null_handle, &int_value);
	assert_eq(index, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_get_iface_name_p
 * @since_tizen		3.0
 * @description		Get name of VPN interface
 * @scenario		check vpnsvc_get_iface_name by passing valid vpnsvc_h handle
 */
int utc_vpn_vpnsvc_get_iface_name_p(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *get_if_name = NULL;

	if(g_vpn_supported == false) {
		ret = vpnsvc_get_iface_name(NULL, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_get_iface_name(g_handle, &get_if_name);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_get_iface_name_n
 * @since_tizen		3.0
 * @description		vpnsvc_get_iface_name should fail on Invalid parameter
 * @scenario		Check vpnsvc_get_iface_name by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_get_iface_name_n(void)
{
	vpnsvc_h null_handle = NULL;
	char *get_if_name = NULL;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_get_iface_name(null_handle, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_get_iface_name(null_handle, &get_if_name);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_set_mtu_p
 * @since_tizen		3.0
 * @description		Set mtu of VPN interface
 * @scenario		check vpnsvc_set_mtu by passing valid vpnsvc_h handle
 */
int utc_vpn_vpnsvc_set_mtu_p(void)
{
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_set_mtu(NULL, 0);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_set_mtu(g_handle, 9000);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_set_mtu_n
 * @since_tizen		3.0
 * @description		vpnsvc_set_mtu should fail on Invalid parameter
 * @scenario		Check vpnsvc_set_mtu by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_set_mtu_n(void)
{
	vpnsvc_h null_handle = NULL;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_set_mtu(null_handle, 0);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}


	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_set_mtu(null_handle, 9000);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_set_blocking_p
 * @since_tizen		3.0
 * @description		Set Blocking Mode for VPN interface
 * @scenario		check vpnsvc_set_blocking by setting blocking to true
 */
int utc_vpn_vpnsvc_set_blocking_p(void)
{
	bool blocking = true;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_set_blocking(NULL, false);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_set_blocking(g_handle, blocking);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_set_blocking_n
 * @since_tizen		3.0
 * @description		vpnsvc_set_blocking should fail on Invalid parameter
 * @scenario		Check vpnsvc_set_blocking by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_set_blocking_n(void)
{
	vpnsvc_h null_handle = NULL;
	bool blocking = true;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_set_blocking(null_handle, false);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_set_blocking(null_handle, blocking);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_set_session_p
 * @since_tizen		3.0
 * @description		Set Session Name for VPN
 * @scenario		check vpnsvc_set_session by setting set_session
 */
int utc_vpn_vpnsvc_set_session_p(void)
{
	int ret = VPNSVC_ERROR_NONE;

	char *set_session = "vpnsvc_test VPN Session";

	if(g_vpn_supported == false) {
		ret = vpnsvc_set_session(NULL, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}


	ret = vpnsvc_set_session(g_handle, set_session);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_set_session_n
 * @since_tizen		3.0
 * @description		vpnsvc_set_session should fail on Invalid parameter
 * @scenario		Check vpnsvc_set_session by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_set_session_n(void)
{
	vpnsvc_h null_handle = NULL;
	char *set_session = "vpnsvc_test VPN Session";
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_set_session(null_handle, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_set_session(null_handle, set_session);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_get_session_p
 * @since_tizen		3.0
 * @description		Get Session Name for VPN
 * @scenario		check vpnsvc_get_session by getting session parameter
 */
int utc_vpn_vpnsvc_get_session_p(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *set_session = "vpnsvc_test VPN Session";
	char *get_session = NULL;

	if(g_vpn_supported == false) {
		ret = vpnsvc_get_session(NULL, NULL);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_set_session(g_handle, set_session);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	ret = vpnsvc_get_session(g_handle, &get_session);
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_get_session_n
 * @since_tizen		3.0
 * @description		vpnsvc_get_session should fail on Invalid parameter
 * @scenario		Check vpnsvc_get_session by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_get_session_n(void)
{
	vpnsvc_h null_handle = NULL;
	char *get_session = NULL;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_get_session(null_handle, &get_session);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_get_session(null_handle, &get_session);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_vpn_vpnsvc_read_n
 * @since_tizen		3.0
 * @description		vpnsvc_read should fail on Invalid parameter
 * @scenario		Check vpnsvc_read by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_read_n(void)
{
	vpnsvc_h null_handle = NULL;
	int timeout_ms = 1000*TIMEOUT_SEC;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_read(NULL, 0);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_read(null_handle, timeout_ms);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_vpn_vpnsvc_write_n
 * @since_tizen		3.0
 * @description		vpnsvc_write should fail on Invalid parameter
 * @scenario		Check vpnsvc_write by passing invalid vpnsvc_h handle as parameter
 */
int utc_vpn_vpnsvc_write_n(void)
{
	vpnsvc_h null_handle = NULL;
	char *data = "vpnsvc_write_data";
	int size = strlen(data)+1;
	int ret = VPNSVC_ERROR_NONE;

	if(g_vpn_supported == false) {
		ret = vpnsvc_write(NULL, NULL, 0);
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_write(null_handle, data, size);
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_set_local_ip_address_n
 * @since_tizen		3.0
 * @description		vpnsvc_set_local_ip_addres should fail on Invalid parameter
 * @scenario		Check vpnsvc_set_local_ip_address by passing invalid parameter
 */
int utc_vpn_vpnsvc_set_local_ip_address_n(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *local_ip = "192.168.123.45";

	ret = vpnsvc_set_local_ip_address(NULL, local_ip);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_set_local_ip_address(g_handle, NULL);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_set_local_ip_address(NULL, NULL);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_set_local_ip_address_p
 * @since_tizen		3.0
 * @description		Set local IP for VPN
 * @scenario		check vpnsvc_set_local_ip_address_p by passing valid local_ip
 */
int utc_vpn_vpnsvc_set_local_ip_address_p(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *local_ip = "192.168.123.45";

	if (!g_handle && g_vpn_supported) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_set_local_ip_address(g_handle, local_ip);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_set_remote_ip_address_n
 * @since_tizen		3.0
 * @description		vpnsvc_set_remote_ip_addres should fail on Invalid parameter
 * @scenario		Check vpnsvc_set_remote_ip_address by passing invalid parameter
 */
int utc_vpn_vpnsvc_set_remote_ip_address_n(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *remote_ip = "192.168.123.123";

	ret = vpnsvc_set_remote_ip_address(NULL, remote_ip);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_set_remote_ip_address(g_handle, NULL);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_set_remote_ip_address(NULL, NULL);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_set_remote_ip_address_p
 * @since_tizen		3.0
 * @description		Set local IP for VPN
 * @scenario		check vpnsvc_set_remote_ip_address_p by passing valid remote_ip
 */
int utc_vpn_vpnsvc_set_remote_ip_address_p(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *remote_ip = "192.168.123.123";

	if (!g_handle && g_vpn_supported) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_set_remote_ip_address(g_handle, remote_ip);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_update_settings_n1
 * @since_tizen		3.0
 * @description		vpnsvc_update_settings should fail on Invalid parameter
 * @scenario		check vpnsvc_update_settings by passing invalid parameter
 */
int utc_vpn_vpnsvc_update_settings_n1(void)
{
	int ret = VPNSVC_ERROR_NONE;

	ret = vpnsvc_update_settings(NULL);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	if (!g_handle) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_update_settings(g_handle);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_update_settings_n2
 * @since_tizen		3.0
 * @description		vpnsvc_update_settings should fail on IO error
 * @scenario		check vpnsvc_update_settings by passing invalid local & remote IP
 */
int utc_vpn_vpnsvc_update_settings_n2(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *local_ip = "192.168.3.12";
	char *remote_ip = "192.168.3.32";
	char *invalid_ip = "224.0.0.0";

	// Local IP is valid but remote IP isn't valid.
	ret = vpnsvc_set_local_ip_address(g_handle, local_ip);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_NONE);

	ret = vpnsvc_set_remote_ip_address(g_handle, invalid_ip);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_NONE);

	ret = vpnsvc_update_settings(g_handle);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, VPNSVC_ERROR_IO_ERROR);

	// Remote IP is valid but local IP isn't valid.
	ret = vpnsvc_set_local_ip_address(g_handle, invalid_ip);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_NONE);

	ret = vpnsvc_set_remote_ip_address(g_handle, remote_ip);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_NONE);

	ret = vpnsvc_update_settings(g_handle);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, VPNSVC_ERROR_IO_ERROR);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_update_settings_p
 * @since_tizen		3.0
 * @description		Update VPN settings
 * @scenario		check vpnsvc_update_settings by passing valid parameter
 */
int utc_vpn_vpnsvc_update_settings_p(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *local_ip = "192.168.123.45";
	char *remote_ip = "192.168.123.123";

	if (!g_handle && g_vpn_supported) {
		fprintf(stderr, "g_handle is null\n");
		return 1;
	}

	ret = vpnsvc_set_local_ip_address(g_handle, local_ip);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_NONE);

	ret = vpnsvc_set_remote_ip_address(g_handle, remote_ip);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_NONE);

	ret = vpnsvc_update_settings(g_handle);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_add_route_n
 * @since_tizen		3.0
 * @description		vpnsvc_add_route should fail on Invalid parameter
 * @scenario		check vpnsvc_add_route by passing invalid parameter
 */
int utc_vpn_vpnsvc_add_route_n(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *route_ip = "192.168.123.123";
	int prefix = 32;

	ret = vpnsvc_add_route(NULL, route_ip, prefix);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_add_route(g_handle, NULL, prefix);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_add_route(NULL, NULL, prefix);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_remove_route_n
 * @since_tizen		3.0
 * @description		vpnsvc_remove_route should fail on Invalid parameter
 * @scenario		check vpnsvc_remove_route by passing invalid parameter
 */
int utc_vpn_vpnsvc_remove_route_n(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *route_ip = "192.168.123.123";
	int prefix = 32;

	ret = vpnsvc_remove_route(NULL, route_ip, prefix);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_remove_route(g_handle, NULL, prefix);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_remove_route(NULL, NULL, prefix);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_add_dns_server_n
 * @since_tizen		3.0
 * @description		vpnsvc_add_dns_server should fail on Invalid parameter
 * @scenario		check vpnsvc_add_dns_server by passing invalid parameter
 */
int utc_vpn_vpnsvc_add_dns_server_n(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *dns_server = "192.168.123.123";

	ret = vpnsvc_add_dns_server(NULL, dns_server);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_add_dns_server(g_handle, NULL);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_add_dns_server(NULL, NULL);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_vpn_vpnsvc_remove_dns_server_n
 * @since_tizen		3.0
 * @description		vpnsvc_remove_dns_server should fail on Invalid parameter
 * @scenario		check vpnsvc_remove_dns_server by passing invalid parameter
 */
int utc_vpn_vpnsvc_remove_dns_server_n(void)
{
	int ret = VPNSVC_ERROR_NONE;
	char *dns_server = "192.168.123.123";

	ret = vpnsvc_remove_dns_server(NULL, dns_server);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_remove_dns_server(g_handle, NULL);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	ret = vpnsvc_remove_dns_server(NULL, NULL);
	if(g_vpn_supported == false) {
		assert_eq(ret, VPNSVC_ERROR_NOT_SUPPORTED);
		return 0;
	}
	assert_eq(ret, VPNSVC_ERROR_INVALID_PARAMETER);

	return 0;
}
