//
// Copyright (c) 2022 Samsung Electronics Co., Ltd.
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
#include <bluetooth.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>
#include <string.h>
#include <system_info.h>

static int startup_flag = BT_ERROR_NONE;
static int socket_fd = 0;
static int ret = BT_ERROR_NONE;
static int l2cap_test_psm = 37;
static bool bt_supported = false;
static bool le_supported = false;
static bool le_coc_supported = false;

static void socket_l2cap_channel_connection_state_changed_cb_for_socket_p(int result,
		bt_socket_connection_state_e connection_state,
		bt_socket_l2cap_le_connection_s *connection, void *user_data)
{
}

/**
 * @function		utc_bluetooth_bt_socket_l2cap_channel_positive_startup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then intialize the bluetooth on the device successfully and retrieve the adapter state.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_bt_socket_l2cap_channel_positive_startup(void)
{
	bt_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

	le_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.le", &le_supported);

	le_coc_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.le.coc", &le_coc_supported);

	startup_flag = BT_ERROR_NONE;

	if(bt_supported && le_supported && le_coc_supported) {
		ret = bt_initialize();
		if(BT_ERROR_NONE != ret) {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "bt_initialize failed (code: %d)\n", ret);
			startup_flag = ret;
			return;
			}

		bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;

		ret = bt_adapter_get_state(&adapter_state);
		if (adapter_state != BT_ADAPTER_ENABLED) {
			fprintf(stdout, "BT is not enabled!!");
			startup_flag = BT_ERROR_NOT_ENABLED;
		}
	}
}

/**
 * @function		utc_bluetooth_bt_socket_l2cap_channel_positive_cleanup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then deintialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_bt_socket_l2cap_channel_positive_cleanup(void)
{
	if(bt_supported && le_supported && le_coc_supported)
		bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_l2cap_channel_connection_state_changed_cb_p
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the connection
 *				state changed callback and check for error. If bluetooth is initialized, set and unset connection state changed callback successfully.
 * @senario		Check if BT is supported and then set bt_socket_set_l2cap_channel_connection_state_changed_cb on the device and check for expected result.
 */
int utc_bluetooth_bt_socket_set_l2cap_channel_connection_state_changed_cb_p(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_set_l2cap_channel_connection_state_changed_cb(socket_l2cap_channel_connection_state_changed_cb_for_socket_p, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_set_l2cap_channel_connection_state_changed_cb(socket_l2cap_channel_connection_state_changed_cb_for_socket_p, NULL);
	assert_eq(ret, BT_ERROR_NONE);

	bt_socket_unset_l2cap_channel_connection_state_changed_cb();

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_create_l2cap_channel_p
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, create l2cap channel
 *				and check for error. If bluetooth is initialized, then create l2cap channel successfully.
 * @senario		Check if BT is supported and then call bt_socket_create_l2cap_channel on the device and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_create_l2cap_channel_p(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_create_l2cap_channel(l2cap_test_psm, &socket_fd);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_create_l2cap_channel(l2cap_test_psm, &socket_fd);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_destroy_l2cap_channel(socket_fd);
	assert_eq(ret, BT_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_bluetooth_bt_socket_listen_l2cap_channel_p
 * @since_tizen 7.0
 * @description Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *                              call bt_socket_listen_l2cap_channel and check for error. If bluetooth is initialized, then create l2cap channel
 *                              and listen for l2cap connection successfully.
 * @senario             Check if BT is supported and then call bt_socket_create_l2cap_channel and bt_socket_listen_l2cap_channel on the device
 *                              and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_listen_l2cap_channel_p(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_listen_l2cap_channel(socket_fd, 1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_create_l2cap_channel(l2cap_test_psm, &socket_fd);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_listen_l2cap_channel(socket_fd, 1);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_destroy_l2cap_channel(socket_fd);
	assert_eq(ret, BT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_listen_and_accept_l2cap_channel_p
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call bt_socket_listen_and_accept_l2cap_channel and check for error. If bluetooth is initialized, then create l2cap channel
 *				and listen and accept for l2cap connection successfully.
 * @senario		Check if BT is supported and then call bt_socket_create_l2cap_channel and bt_socket_listen_and_accept_l2cap_channel on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_listen_and_accept_l2cap_channel_p(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_listen_and_accept_l2cap_channel(socket_fd, 1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_create_l2cap_channel(l2cap_test_psm, &socket_fd);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_listen_and_accept_l2cap_channel(socket_fd, 1);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_destroy_l2cap_channel(socket_fd);
	assert_eq(ret, BT_ERROR_NONE);

	return 0;
}

/**
 * @testcase            utc_bluetooth_bt_socket_get_l2cap_psm_p
 * @since_tizen 7.0
 * @description Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *                              call bt_socket_get_l2cap_psm and check for error. If bluetooth is initialized, then create l2cap channel
 *                              and get psm for l2cap channel successfully.
 * @senario             Check if BT is supported and then call bt_socket_create_l2cap_channel, bt_socket_listen_and_accept_l2cap_channel
 *                              and bt_socket_get_l2cap_psm on the device and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_get_l2cap_psm_p(void)
{
	int psm = -1;
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_get_l2cap_psm(socket_fd, &psm);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_create_l2cap_channel(l2cap_test_psm, &socket_fd);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_listen_and_accept_l2cap_channel(socket_fd, 1);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_get_l2cap_psm(socket_fd, &psm);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_destroy_l2cap_channel(socket_fd);
	assert_eq(ret, BT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_destroy_l2cap_channel_p
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				destroy the l2cap channel and check for error. If bluetooth is initialized, then create l2cap channel
 *				and destroy l2cap channel successfully.
 * @senario		Check if BT is supported and then call bt_socket_create_l2cap_channel and bt_socket_destroy_l2cap_channel on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_destroy_l2cap_channel_p(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_destroy_l2cap_channel(socket_fd);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_create_l2cap_channel(l2cap_test_psm, &socket_fd);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_destroy_l2cap_channel(socket_fd);
	assert_eq(ret, BT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_unset_l2cap_channel_connection_state_changed_cb_p
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				unset the connection state changed callback and check for error. If bluetooth is initialized, then set
 *				connection state changed callback and unset connection state changed successfully.
 * @senario		Check if BT is supported and then set and unset connection state changed callback on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_unset_l2cap_channel_connection_state_changed_cb_p(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_unset_l2cap_channel_connection_state_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_set_l2cap_channel_connection_state_changed_cb(socket_l2cap_channel_connection_state_changed_cb_for_socket_p, NULL);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_unset_l2cap_channel_connection_state_changed_cb();
	assert_eq(ret, BT_ERROR_NONE);

	return 0;
}

static void bt_socket_connection_requested_cb_func(int socket_fd, const char *remote_address, void *user_data) {
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_l2cap_channel_connection_requested_cb_p
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				set the connection requested callback and check for error. If bluetooth is initialized, then set
 *				connection requested callback and unset connection requested callback successfully.
 * @senario		Check if BT is supported and then set and unset connection requested callback on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_set_l2cap_channel_connection_requested_cb_p(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_set_l2cap_channel_connection_requested_cb(bt_socket_connection_requested_cb_func, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_set_l2cap_channel_connection_requested_cb(bt_socket_connection_requested_cb_func, NULL);
	assert_eq(ret, BT_ERROR_NONE);

	bt_socket_unset_l2cap_channel_connection_requested_cb();

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_unset_l2cap_channel_connection_requested_cb_p
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				unset the connection requested callback and check for error. If bluetooth is initialized, then set
 *				connection requested callback and unset connection requested callback successfully and check for error.
 * @senario		Check if BT is supported and then set and unset connection requested callback on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_unset_l2cap_channel_connection_requested_cb_p(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_unset_l2cap_channel_connection_requested_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_set_l2cap_channel_connection_requested_cb(bt_socket_connection_requested_cb_func, NULL);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_unset_l2cap_channel_connection_requested_cb();
	assert_eq(ret, BT_ERROR_NONE);

	return 0;
}
