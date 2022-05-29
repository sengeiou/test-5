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

//& set: BluetoothSocketPositive

static int startup_flag = BT_ERROR_NONE;
static int socket_fd = 0;
static int ret = BT_ERROR_NONE;
static const char *rfcomm_test_uuid_spp = "00001101-0000-1000-8000-00805F9B34FB";
static bool bt_supported = false;


static void socket_data_received_cb_for_socket_p(bt_socket_received_data_s *data,
                    void *user_data)
{
}

static void socket_connection_state_changed_cb_for_socket_p(int result,
                bt_socket_connection_state_e connection_state,
                bt_socket_connection_s *connection, void *user_data)
{
}

/**
 * @function		utc_bluetooth_bt_socket_positive_startup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then intialize the bluetooth on the device successfully and retrieve the adapter state.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_bt_socket_positive_startup(void)
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

        bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;

        ret = bt_adapter_get_state(&adapter_state);
        if (adapter_state != BT_ADAPTER_ENABLED) {
                fprintf(stdout, "BT is not enabled!!");
                startup_flag = BT_ERROR_NOT_ENABLED;
                //disable_bluetooth_le_adapter();
        }
    }
}

/**
 * @function		utc_bluetooth_bt_socket_positive_cleanup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then deintialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_bt_socket_positive_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_data_received_cb_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the data
 *				received callback and check for error. If bluetooth is initialized, set and unset the data received callback successfully.
 * @senario		Check if BT is supported and then set bt_socket_set_data_received_cb on the device and check for expected result.
 */
int utc_bluetooth_bt_socket_set_data_received_cb_p(void)
{
    if(!bt_supported) {
        ret = bt_socket_set_data_received_cb(socket_data_received_cb_for_socket_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_set_data_received_cb(socket_data_received_cb_for_socket_p, NULL);
    assert_eq(ret, BT_ERROR_NONE);

    bt_socket_unset_data_received_cb();

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_connection_state_changed_cb_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the connection
 *				state changed callback and check for error. If bluetooth is initialized, set and unset connection state changed callback successfully.
 * @senario		Check if BT is supported and then set bt_socket_set_connection_state_changed_cb on the device and check for expected result.
 */
int utc_bluetooth_bt_socket_set_connection_state_changed_cb_p(void)
{
    if(!bt_supported) {
        ret = bt_socket_set_connection_state_changed_cb(socket_connection_state_changed_cb_for_socket_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_set_connection_state_changed_cb(socket_connection_state_changed_cb_for_socket_p, NULL);
    assert_eq(ret, BT_ERROR_NONE);

    bt_socket_unset_connection_state_changed_cb();

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_create_rfcomm_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, create rfcomm socket
 *				and check for error. If bluetooth is initialized, then create rfcomm socket successfully.
 * @senario		Check if BT is supported and then call bt_socket_create_rfcomm on the device and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_create_rfcomm_p(void)
{
    if(!bt_supported) {
        ret = bt_socket_create_rfcomm(rfcomm_test_uuid_spp, &socket_fd);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_create_rfcomm(rfcomm_test_uuid_spp, &socket_fd);
    assert_eq(ret, BT_ERROR_NONE);

#ifdef TV
	ret = bt_socket_destroy_rfcomm(socket_fd);
#endif

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_listen_and_accept_rfcomm_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				call bt_socket_listen_and_accept_rfcomm and check for error. If bluetooth is initialized, then create rfcomm socket
 *				and listen and accept for rfcomm connection successfully.
 * @senario		Check if BT is supported and then call bt_socket_create_rfcomm and  bt_socket_listen_and_accept_rfcomm on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_listen_and_accept_rfcomm_p(void)
{
    if(!bt_supported) {
        ret = bt_socket_listen_and_accept_rfcomm(socket_fd, 1);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_create_rfcomm(rfcomm_test_uuid_spp, &socket_fd);
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_socket_listen_and_accept_rfcomm(socket_fd, 1);
    assert_eq(ret, BT_ERROR_NONE);

#ifdef TV
    ret = bt_socket_destroy_rfcomm(socket_fd);
#endif

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_destroy_rfcomm_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				destroy the rfcomm socket and check for error. If bluetooth is initialized, then create rfcomm socket
 *				and destroy rfcomm socket successfully.
 * @senario		Check if BT is supported and then call bt_socket_create_rfcomm and  bt_socket_destroy_rfcomm on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_destroy_rfcomm_p(void)
{
    if(!bt_supported) {
        ret = bt_socket_destroy_rfcomm(socket_fd);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_create_rfcomm(rfcomm_test_uuid_spp, &socket_fd);
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_socket_destroy_rfcomm(socket_fd);
    assert_eq(ret, BT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_unset_data_received_cb_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				unset the data received callback and check for error. If bluetooth is initialized, then set data received callback
 *				and unset data received callback successfully.
 * @senario		Check if BT is supported and then set and unset data received callback on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_unset_data_received_cb_p(void)
{
    if(!bt_supported) {
        ret = bt_socket_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_set_data_received_cb(socket_data_received_cb_for_socket_p, NULL);
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_socket_unset_data_received_cb();
    assert_eq(ret, BT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_unset_connection_state_changed_cb_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				unset the connection state changed callback and check for error. If bluetooth is initialized, then set
 *				connection state changed callback and unset connection state changed successfully.
 * @senario		Check if BT is supported and then set and unset connection state changed callback on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_unset_connection_state_changed_cb_p(void)
{
    if(!bt_supported) {
        ret = bt_socket_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_set_connection_state_changed_cb(socket_connection_state_changed_cb_for_socket_p, NULL);
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_socket_unset_connection_state_changed_cb();
    assert_eq(ret, BT_ERROR_NONE);

    return 0;
}

static void bt_socket_connection_requested_cb_func (int socket_fd, const char *remote_address, void *user_data) {
}

/**
 * @testcase		utc_bluetooth_bt_socket_set_connection_requested_cb_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				set the connection requested callback and check for error. If bluetooth is initialized, then set
 *				connection requested callback and unset connection requested callback successfully.
 * @senario		Check if BT is supported and then set and unset connection requested callback on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_set_connection_requested_cb_p(void)
{
    if(!bt_supported) {
        ret = bt_socket_set_connection_requested_cb(bt_socket_connection_requested_cb_func, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_set_connection_requested_cb(bt_socket_connection_requested_cb_func, NULL);
    assert_eq(ret, BT_ERROR_NONE);

    bt_socket_unset_connection_requested_cb();

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_socket_unset_connection_requested_cb_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device,
 *				unset the connection requested callback and check for error. If bluetooth is initialized, then set
 *				connection requested callback and unset connection requested callback successfully and check for error.
 * @senario		Check if BT is supported and then set and unset connection requested callback on the device
 *				and check for BT_ERROR_NONE.
 */
int utc_bluetooth_bt_socket_unset_connection_requested_cb_p(void)
{
    if(!bt_supported) {
        ret = bt_socket_unset_connection_requested_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_socket_set_connection_requested_cb(bt_socket_connection_requested_cb_func, NULL);
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_socket_unset_connection_requested_cb();
    assert_eq(ret, BT_ERROR_NONE);

    return 0;
}
