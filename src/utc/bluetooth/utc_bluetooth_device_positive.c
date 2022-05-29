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


//& set: BluetoothDevicePositive

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool callback_result = false;
static bt_device_info_s *device_info = NULL;
static const char *remote_address = "B8:5E:7B:E7:92:7D";
static bool bt_supported = false;


static void device_bonded_cb(int result, bt_device_info_s * device_info,
                void *user_data)
{

}

static void device_unbonded_cb(int result, char *remote_address, void *user_data)
{

}

static void device_authorization_state_changed_cb(bt_device_authorization_e authorization_state,
        char *address, void *user_data)
{

}

static bool bonded_device_cb_for_device_p(bt_device_info_s *dev_info, void *user_data)
{
    return false;
}

static void bt_connection_state_changed_cb(bool connected,
        bt_device_connection_info_s *conn_info, void *user_data)
{

}

/**
 * @function		utc_bluetooth_device_positive_startup
 * @description	check if bluetooth is supported, initialize bluetooth and check the adapter state and
 * 				store adapter state for further use.
 * @parameter	NA
 * @return		NA
 */
void utc_bluetooth_device_positive_startup(void)
{
    bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;

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


    if(bt_supported) {
        startup_flag = BT_ERROR_NONE;
        ret = bt_initialize();
        if(BT_ERROR_NONE != ret) {
            fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
            fprintf(stderr, "bt_initialize failed (code: %d)\n", ret);
            startup_flag = ret;
            return;
        }

        callback_result = false;
        ret = bt_adapter_get_state(&adapter_state);
        if (adapter_state != BT_ADAPTER_ENABLED) {
                fprintf(stdout, "BT is not enabled!!");
                startup_flag = BT_ERROR_NOT_ENABLED;
        }
    }
}

/**
 * @function		utc_bluetooth_device_positive_cleanup
 * @description 	check if bluetooth is supported, clear the device information resources and release all the bluetooth resources.
 * @parameter	NA
 * @return		NA
 */
void utc_bluetooth_device_positive_cleanup(void)
{
    if(bt_supported) {
        free(device_info);
        device_info = NULL;

        bt_deinitialize();
    }
}

/**
 * @testcase		utc_bluetooth_bt_device_set_bond_created_cb_p
 * @since_tizen	2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then register a callback for bond creation
 *				and check for errors.
 * @scenario		Registers a callback function to be invoked when the bond creates.
 */
int utc_bluetooth_bt_device_set_bond_created_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_bond_created_cb(device_bonded_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        bt_device_unset_bond_created_cb();
    } else {
        ret = bt_device_set_bond_created_cb(device_bonded_cb, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_bond_destroyed_cb_p
 * @since_tizen	2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then register a callback for bond destroy
 *				and check for errors.
 * @scenario		Registers a callback function to be invoked when the bond destroys.
 */
int utc_bluetooth_bt_device_set_bond_destroyed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_bond_destroyed_cb(device_unbonded_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        bt_device_unset_bond_destroyed_cb();
    } else {
        ret = bt_device_set_bond_destroyed_cb(device_unbonded_cb, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_authorization_changed_cb_p
 * @since_tizen	2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then register a callback for change in device authorization
 *				and check for errors.
 * @scenario		Registers a callback function to be invoked when the authorization of device changes.
 */
int utc_bluetooth_bt_device_set_authorization_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_authorization_changed_cb(device_authorization_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        bt_device_unset_authorization_changed_cb();
    } else {
        ret = bt_device_set_authorization_changed_cb(device_authorization_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_get_service_mask_from_uuid_list_p
 * @since_tizen	2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then retrive the service class of the uuid from uuid list
 *				and check for errors.
 * @scenario		Get the service mask from the uuid list.
 */
int utc_bluetooth_bt_device_get_service_mask_from_uuid_list_p(void)
{
    char* uuid = "00001101-0000-1000-8000-00805f9b34fb";
    int no_of_service = 1;
    bt_service_class_t service_mask_list;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_get_service_mask_from_uuid_list(&uuid, no_of_service,
        				  &service_mask_list);
        assert_eq(ret, BT_ERROR_NONE);
    } else{
        ret = bt_device_get_service_mask_from_uuid_list(&uuid, no_of_service,
        				  &service_mask_list);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_is_profile_connected_p
 * @since_tizen	2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then retrive the profile connection state with
 *				respect to remote address and profile and check for errors.
 * @scenario		Gets the profile connected status if bluetooth is supported else throws an error.
 
 */
int utc_bluetooth_bt_device_is_profile_connected_p(void)
{
    bt_profile_e bt_profile = BT_PROFILE_RFCOMM;
    bool is_connected = FALSE;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_is_profile_connected(remote_address, bt_profile,
        			&is_connected);

        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_device_is_profile_connected(remote_address, bt_profile,
        			&is_connected);

        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_unset_bond_created_cb_p
 * @since_tizen	2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then unregister a callback for bond creation
 *				and check for errors.
 * @scenario		Unregisters the callback function for bond creation.
 */
int utc_bluetooth_bt_device_unset_bond_created_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_bond_created_cb(device_bonded_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_device_unset_bond_created_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_device_unset_bond_created_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_foreach_bonded_device_p
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then all bonded device information is listed from the device list
 *				and check for errors.
 * scenario		Retrieves the device information of all bonded devices.
 */
int utc_bluetooth_bt_adapter_foreach_bonded_device_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_foreach_bonded_device(bonded_device_cb_for_device_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_foreach_bonded_device(bonded_device_cb_for_device_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_unset_bond_destroyed_cb_p
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then unregister a callback for bond destroy
 *				and check for errors.
 * @scenario		Unregisters the callback function for bond destroy.
 */
int utc_bluetooth_bt_device_unset_bond_destroyed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_bond_destroyed_cb(device_unbonded_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_device_unset_bond_destroyed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_device_unset_bond_destroyed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_unset_authorization_changed_cb_p
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then register a callback for change in device authorization
 *				and check for errors.
 * @scenraio		Unregisters the callback function for device authorization changes.
 */
int utc_bluetooth_bt_device_unset_authorization_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_authorization_changed_cb(device_authorization_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_device_unset_authorization_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_device_unset_authorization_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_connection_state_changed_cb_p
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then register a callback for change in connection state
 *				and check for errors.
 * scenario		Registers a callback function to be invoked when the connection state is changed.
 */
int utc_bluetooth_bt_device_set_connection_state_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_connection_state_changed_cb(bt_connection_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        bt_device_unset_connection_state_changed_cb();
    } else {
        ret = bt_device_set_connection_state_changed_cb(bt_connection_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_unset_connection_state_changed_cb_p
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then unregister a callback for change in connection state
 *				and check for errors.
 * @scenario		Unregisters the callback function to be invoked when the connection state is changed.
 */
int utc_bluetooth_bt_device_unset_connection_state_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_connection_state_changed_cb(bt_connection_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_device_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_device_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}
