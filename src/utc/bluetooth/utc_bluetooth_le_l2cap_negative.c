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
static int ret = BT_ERROR_NONE;
static const char *data = "dts_test";
static char *address = "D8:90:E8:EE:2B:3A";
static bool bt_supported = false;
static bool le_supported = false;
static bool le_coc_supported = false;

/**
 * @function		utc_bluetooth_bt_socket_l2cap_channel_negative_startup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then intialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_bt_socket_l2cap_channel_negative_startup(void)
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
    }
}

/**
 * @function		utc_bluetooth_bt_socket_l2cap_channel_negative_cleanup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then deintialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_bt_socket_l2cap_channel_negative_cleanup(void)
{
	if(bt_supported && le_supported && le_coc_supported)
		bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_l2cap_channel_connection_state_changed_cb_n
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the connection
 *				state changed callback and check for error. If bluetooth is initialized, set connection state changed callback with NULL params.
 * @senario		Check if BT is supported and then set bt_socket_l2cap_channel_set_connection_state_changed_cb with NULL parameters.
 *				Check for error BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_set_l2cap_channel_connection_state_changed_cb_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_set_l2cap_channel_connection_state_changed_cb(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_set_l2cap_channel_connection_state_changed_cb(NULL, NULL);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_l2cap_channel_set_connection_state_changed_cb_n1
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the connection
 *				state changed callback and check for error. If bluetooth is initialized, set connection state changed callback with NULL params.
 * @senario		Check if BT is supported and then set bt_socket_l2cap_channel_set_connection_state_changed_cb with NULL parameters.
 *				Check for error BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_set_l2cap_channel_connection_state_changed_cb_n1(void)
{
    if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_set_l2cap_channel_connection_state_changed_cb(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_set_l2cap_channel_connection_state_changed_cb(NULL, NULL);
	assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_l2cap_channel_unset_connection_state_changed_cb_n
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				unset the connection state changed callback and check for error. If bluetooth is initialized, deinitialize
 *				bluetooth and unset connection state changed callback.
 * @senario		Check if BT is supported and then deinitialize bt and unset connection state changed callback on the device
 *				and check for BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_socket_unset_l2cap_channel_connection_state_changed_cb_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_unset_l2cap_channel_connection_state_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_unset_l2cap_channel_connection_state_changed_cb();
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_create_l2cap_channel_n
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, create l2cap channel
 *				and check for error. If bluetooth is initialized, deinitialize bt and create l2cap channel with NULL parameters.
 * @senario		Check if BT is supported and then deinitialize bluetooth and create l2cap channel on the device and check for BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_socket_create_l2cap_channel_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_create_l2cap_channel(0, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_create_l2cap_channel(0, NULL);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_create_l2cap_channel_n1
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, create l2cap channel
 *				and check for error. If bluetooth is initialized, create l2cap channel with NULL parameters.
 * @senario		Check if BT is supported then create l2cap channel on the device and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_create_l2cap_channel_n1(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_create_l2cap_channel(0, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_create_l2cap_channel(0, NULL);
	assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_destroy_l2cap_channel_n
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				destroy the l2cap channel and check for error. If bluetooth is initialized, then destroy l2cap channel
 *				with invalid parameter.
 * @senario		Check if BT is supported and then call bt_socket_destroy_l2cap_channel on the device with invalid parameter.
 *				Check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_destroy_l2cap_channel_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_destroy_l2cap_channel(-1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_destroy_l2cap_channel(-1);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase            utc_bluetooth_bt_socket_listen_l2cap_channel_n
 * @since_tizen 7.0
 * @description Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *                              call bt_socket_listen_l2cap_channel and check for error. If bluetooth is initialized, then
 *                               listen for l2cap connection with invalid paramters.
 * @senario             Check if BT is supported and then call bt_socket_listen_l2cap_channel on the device with invalid parameters
 *                              and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_listen_l2cap_channel_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_listen_l2cap_channel(1, 1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_listen_l2cap_channel(1, 1);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase            utc_bluetooth_bt_socket_accept_l2cap_channel_n
 * @since_tizen 7.0
 * @description Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *                              call bt_socket_accept_l2cap_channel and check for error. If bluetooth is initialized, then
 *                               accept l2cap connection with invalid paramters.
 * @senario             Check if BT is supported and then call bt_socket_accept_l2cap_channel on the device with invalid parameters
 *                              and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_accept_l2cap_channel_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_accept_l2cap_channel(1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_accept_l2cap_channel(1);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase            utc_bluetooth_bt_socket_reject_l2cap_channel_n
 * @since_tizen 7.0
 * @description Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *                              call bt_socket_reject_l2cap_channel and check for error. If bluetooth is initialized, then
 *                               reject l2cap connection with invalid paramters.
 * @senario             Check if BT is supported and then call bt_socket_reject_l2cap_channel on the device with invalid parameters
 *                              and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_reject_l2cap_channel_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_reject_l2cap_channel(1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_reject_l2cap_channel(1);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_listen_and_accept_l2cap_channel_n
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call bt_socket_listen_and_accept_l2cap_channel and check for error. If bluetooth is initialized, then
 *				 listen and accept for l2cap connection with invalid paramters.
 * @senario		Check if BT is supported and then call bt_socket_listen_and_accept_l2cap_channel on the device with invalid parameters
 *				and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_listen_and_accept_l2cap_channel_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_listen_and_accept_l2cap_channel(1, 1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_listen_and_accept_l2cap_channel(1, 1);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase            utc_bluetooth_bt_socket_get_l2cap_psm_n
 * @since_tizen 7.0
 * @description Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *                              call bt_socket_get_l2cap_psm and check for error. If bluetooth is initialized, then
 *                               get psm for l2cap connection with invalid paramters.
 * @senario             Check if BT is supported and then call bt_socket_get_l2cap_psm on the device with invalid parameters
 *                              and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_get_l2cap_psm_n(void)
{
	int psm = -1;
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_get_l2cap_psm(1, &psm);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_get_l2cap_psm(1, &psm);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_connect_l2cap_channel_n
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call bt_socket_connect_l2cap_channel and check for error. If bluetooth is initialized, then
 *				call l2cap connect api with invalid paramters.
 * @senario		Check if BT is supported and then call bt_socket_connect_l2cap_channel on the device with invalid parameters
 *				and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_connect_l2cap_channel_n(void)
{
	int psm = -1;

	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_connect_l2cap_channel(address, psm);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_connect_l2cap_channel(address, psm);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_disconnect_l2cap_channel_n
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call bt_socket_disconnect_l2cap_channel and check for error. If bluetooth is initialized, then call
 *				l2cap disconnect api with invalid paramter.
 * @senario		Check if BT is supported and then call bt_socket_disconnect_l2cap_channel on the device with invalid parameters
 *				and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_disconnect_l2cap_channel_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_disconnect_l2cap_channel(-1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_disconnect_l2cap_channel(-1);

	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_send_data_l2cap_channel_n
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call bt_socket_send_data_l2cap_channel and check for error. If bluetooth is initialized, then call send data over l2cap channel
 *				with invalid paramter.
 * @senario		Check if BT is supported and then call bt_socket_send_data_l2cap_channel on the device with invalid parameters
 *				and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_send_data_l2cap_channel_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_send_data_l2cap_channel(1, data, strlen(data));
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_send_data_l2cap_channel(1, data, strlen(data));
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_l2cap_channel_connection_requested_cb_n
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				set bt_socket_set_l2cap_channel_connection_requested_cb and check for error. If bluetooth is initialized, then
 *				set connected requested callback with invalid paramter.
 * @senario		Check if BT is supported and then call bt_socket_set_l2cap_channel_connection_requested_cb on the device with invalid parameters
 *				and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_set_l2cap_channel_connection_requested_cb_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_set_l2cap_channel_connection_requested_cb(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_set_l2cap_channel_connection_requested_cb(NULL, NULL);
	assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

	return 0;
}

static void bt_socket_connection_requested_cb_func (int socket_fd, const char *remote_address, void *user_data) {
}

/**
 * @testcase		utc_bluetooth_bt_socket_unset_l2cap_channel_connection_requested_cb_n
 * @since_tizen	7.0
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call  bt_socket_unset_l2cap_channel_connection_requested_cb and check for error. If bluetooth is initialized, then deinitlaize bluetooth and
 *				unset connected requested callbackr.
 * @senario		Check if BT is supported then deinitialize bluetooth and call bt_socket_unset_l2cap_channel_connection_requested_cb on the device
 *				and check for BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_socket_unset_l2cap_channel_connection_requested_cb_n(void)
{
	if(!bt_supported || !le_supported || !le_coc_supported) {
		ret = bt_socket_unset_l2cap_channel_connection_requested_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_socket_set_l2cap_channel_connection_requested_cb(bt_socket_connection_requested_cb_func, NULL);
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	ret = bt_socket_unset_l2cap_channel_connection_requested_cb();
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	bt_deinitialize();
	bt_socket_unset_l2cap_channel_connection_requested_cb();

	return 0;
}
