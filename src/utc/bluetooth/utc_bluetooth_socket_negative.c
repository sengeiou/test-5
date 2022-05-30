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
#include <bluetooth.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>
#include <string.h>
#include <system_info.h>

//& set: BluetoothSocketNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static const char *data = "dts_test";
static char *address = "D8:90:E8:EE:2B:3A";
static bool bt_supported = false;

/**
 * @function		utc_bluetooth_socket_negative_startup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then intialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_socket_negative_startup(void)
{
#ifdef TV
#ifndef TV_PRODUCT
	bt_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);
#else
	bt_supported = true;
#endif
#else
    bt_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);
#endif

    startup_flag = BT_ERROR_NONE;

    if(bt_supported) {
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
 * @function		utc_bluetooth_socket_negative_cleanup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then deintialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_socket_negative_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_data_received_cb_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the data
 *				received callback and check for error. If bluetooth is initialized, set the data received callback with NULL parameters.
 * @senario		Check if BT is supported and then set bt_socket_set_data_received_cb with NULL params. Check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_set_data_received_cb_n(void)
{
	if(!bt_supported) {
		ret = bt_socket_set_data_received_cb(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

#ifdef TV
    ret = bt_socket_set_data_received_cb(NULL, NULL);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
#else
	ret = bt_deinitialize();
	assert_eq(ret,BT_ERROR_NONE);

	ret = bt_socket_set_data_received_cb(NULL, NULL);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
#endif

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_data_received_cb_n1
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the data
 *				received callback and check for error. If bluetooth is initialized, set the data received callback with NULL parameters.
 * @senario		Check if BT is supported and then set bt_socket_set_data_received_cb with NULL params. Check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_set_data_received_cb_n1(void)
{
    if(!bt_supported) {
        ret = bt_socket_set_data_received_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_set_data_received_cb(NULL, NULL);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_connection_state_changed_cb_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the connection
 *				state changed callback and check for error. If bluetooth is initialized, set connection state changed callback with NULL params.
 * @senario		Check if BT is supported and then set bt_socket_set_connection_state_changed_cb with NULL parameters.
 *				Check for error BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_set_connection_state_changed_cb_n(void)
{
	if(!bt_supported) {
		ret = bt_socket_set_connection_state_changed_cb(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

#ifdef TV
    ret = bt_socket_set_connection_state_changed_cb(NULL, NULL);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
#else
	ret = bt_deinitialize();
	assert_eq(ret,BT_ERROR_NONE);

	ret = bt_socket_set_connection_state_changed_cb(NULL, NULL);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
#endif
	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_connection_state_changed_cb_n1
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the connection
 *				state changed callback and check for error. If bluetooth is initialized, set connection state changed callback with NULL params.
 * @senario		Check if BT is supported and then set bt_socket_set_connection_state_changed_cb with NULL parameters.
 *				Check for error BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_set_connection_state_changed_cb_n1(void)
{
    if(!bt_supported) {
        ret = bt_socket_set_connection_state_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_set_connection_state_changed_cb(NULL, NULL);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_unset_data_received_cb_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				unset the data received callback and check for error. If bluetooth is initialized, deinitialize bluetooth
 *				and unset data received callback.
 * @senario		Check if BT is supported and then set and unset data received callback on the device
 *				and check for BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_socket_unset_data_received_cb_n(void)
{
    if(!bt_supported) {
        ret = bt_socket_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_socket_unset_data_received_cb();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_unset_connection_state_changed_cb_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				unset the connection state changed callback and check for error. If bluetooth is initialized, deinitialize
 *				bluetooth and unset connection state changed callback.
 * @senario		Check if BT is supported and then deinitialize bt and unset connection state changed callback on the device
 *				and check for BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_socket_unset_connection_state_changed_cb_n(void)
{
    if(!bt_supported) {
        ret = bt_socket_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_socket_unset_connection_state_changed_cb();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_create_rfcomm_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, create rfcomm socket
 *				and check for error. If bluetooth is initialized, deinitialize bt and create rfcomm socket with NULL parameters.
 * @senario		Check if BT is supported and then deinitialize bluetooth and create rfcomm socket on the device and check for BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_socket_create_rfcomm_n(void)
{
    if(!bt_supported) {
        ret = bt_socket_create_rfcomm(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_socket_create_rfcomm(NULL, NULL);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_create_rfcomm_n1
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, create rfcomm socket
 *				and check for error. If bluetooth is initialized, create rfcomm socket with NULL parameters.
 * @senario		Check if BT is supported then create rfcomm socket on the device and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_create_rfcomm_n1(void)
{
    if(!bt_supported) {
        ret = bt_socket_create_rfcomm(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_create_rfcomm(NULL, NULL);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_destroy_rfcomm_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				destroy the rfcomm socket and check for error. If bluetooth is initialized, then destroy rfcomm socket
 *				with invalid parameter.
 * @senario		Check if BT is supported and then call bt_socket_destroy_rfcomm on the device with invalid parameter.
 *				Check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_destroy_rfcomm_n(void)
{
	if(!bt_supported) {
		ret = bt_socket_destroy_rfcomm(-1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

#ifdef TV
    ret = bt_socket_destroy_rfcomm(-1);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
#else
	ret = bt_deinitialize();
	assert_eq(ret,BT_ERROR_NONE);

	ret = bt_socket_destroy_rfcomm(-1);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
#endif

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_listen_and_accept_rfcomm_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call bt_socket_listen_and_accept_rfcomm and check for error. If bluetooth is initialized, then
 *				 listen and accept for rfcomm connection with invalid paramters.
 * @senario		Check if BT is supported and then call bt_socket_listen_and_accept_rfcomm on the device with invalid parameters
 *				and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_listen_and_accept_rfcomm_n(void)
{
	if(!bt_supported) {
		ret = bt_socket_listen_and_accept_rfcomm(1, 1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

#ifdef TV
    ret = bt_socket_listen_and_accept_rfcomm(-1, 1);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
#else
	ret = bt_deinitialize();
	assert_eq(ret,BT_ERROR_NONE);

	ret = bt_socket_listen_and_accept_rfcomm(1, 1);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
#endif

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_connect_rfcomm_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call bt_socket_connect_rfcomm and check for error. If bluetooth is initialized, then
 *				call rfcomm  connect api with invalid paramters.
 * @senario		Check if BT is supported and then call bt_socket_connect_rfcomm on the device with invalid parameters
 *				and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_connect_rfcomm_n(void)
{
	char *uuid = "";

	if(!bt_supported) {
#ifdef TV
        ret = bt_socket_connect_rfcomm(address, NULL);
#else
		ret = bt_socket_connect_rfcomm(address, uuid);
#endif
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

#ifdef TV
    ret = bt_socket_connect_rfcomm(address, NULL);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
#else
	ret = bt_deinitialize();
	assert_eq(ret,BT_ERROR_NONE);

	ret = bt_socket_connect_rfcomm(address, uuid);
	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
#endif


	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_disconnect_rfcomm_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call bt_socket_disconnect_rfcomm and check for error. If bluetooth is initialized, then call
 *				rfcomm  disconnect api with invalid paramter.
 * @senario		Check if BT is supported and then call bt_socket_disconnect_rfcomm on the device with invalid parameters
 *				and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_disconnect_rfcomm_n(void)
{
	if(!bt_supported) {
		ret = bt_socket_disconnect_rfcomm(-1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret,BT_ERROR_NONE);

#ifdef TV
    ret = bt_socket_disconnect_rfcomm(1);
#else
	ret = bt_socket_disconnect_rfcomm(-1);
#endif

	assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_send_data_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call bt_socket_send_data and check for error. If bluetooth is initialized, then call send data over bt socket
 *				with invalid paramter.
 * @senario		Check if BT is supported and then call bt_socket_send_data on the device with invalid parameters
 *				and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_send_data_n(void)
{
	if(!bt_supported) {
        ret = bt_socket_send_data(1, data, strlen(data));
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_deinitialize();
	assert_eq(ret,BT_ERROR_NONE);

    ret = bt_socket_send_data(1, data, strlen(data));
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_connection_requested_cb_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				set  bt_socket_set_connection_requested_cb and check for error. If bluetooth is initialized, then
 *				set connected requested callback with invalid paramter.
 * @senario		Check if BT is supported and then call bt_socket_set_connection_requested_cb on the device with invalid parameters
 *				and check for BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_socket_set_connection_requested_cb_n(void)
{
    if(!bt_supported) {
        ret = bt_socket_set_connection_requested_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_set_connection_requested_cb(NULL, NULL);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

    return 0;
}

static void bt_socket_connection_requested_cb_func (int socket_fd, const char *remote_address, void *user_data) {
}

/**
 * @testcase		utc_bluetooth_bt_socket_unset_connection_requested_cb_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call  bt_socket_unset_connection_requested_cb and check for error. If bluetooth is initialized, then deinitlaize bluetooth and
 *				unset connected requested callbackr.
 * @senario		Check if BT is supported then deinitialize bluetooth and call bt_socket_unset_connection_requested_cb on the device
 *				and check for BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_socket_unset_connection_requested_cb_n(void)
{
    if(!bt_supported) {
        ret = bt_socket_unset_connection_requested_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_set_connection_requested_cb(bt_socket_connection_requested_cb_func, NULL);
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_socket_unset_connection_requested_cb();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    bt_deinitialize();
    bt_socket_unset_connection_requested_cb();

    return 0;
}
