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


//& set: BluetoothDeviceNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static const char *remote_address = "B8:5E:7B:E7:92:7D";
static bool bt_supported = false;


static void bt_connection_state_changed_cb(bool connected, bt_device_connection_info_s *conn_info,
        void *user_data)
{

}

static bool bonded_device_cb_for_device_p(bt_device_info_s *dev_info, void *user_data)
{
    return false;
}

/**
 * @function		utc_bluetooth_device_negative_startup
 * @description     check if bluetooth is supported, Initialialize bluetooth. Here adapter state is not checked.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_device_negative_startup(void)
{
    startup_flag = BT_ERROR_NONE;

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
 * @function		utc_bluetooth_device_negative_cleanup
 * @description 	check if bluetooth is supported release all the bluetooth resources.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_device_negative_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_device_set_bond_created_cb_n
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then deinitialize  the bluetooth and
 *				register a callback for bond creation with invalid paramters else check for errors.
 * @scenario		Try to register a callback function with invalid paramters for bond creation after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_set_bond_created_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_set_bond_created_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_set_bond_created_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_bond_created_cb_n1
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then register a callback
 *				for bond creation with invalid paramters and check for errors.
 * @scenario		Registers a callback function with invalid paramters for bond creation.
 */
int utc_bluetooth_bt_device_set_bond_created_cb_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_bond_created_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_device_set_bond_created_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_bond_destroyed_cb_n
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then deinitialize  the bluetooth and
 *				register a callback for bond destroy with invalid paramters and check for errors.
 * @scenario		Try to register a callback function with invalid paramters for bond destroy after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_set_bond_destroyed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_set_bond_destroyed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_set_bond_destroyed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_authorization_changed_cb_n
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register a callback for change in device authorization with invalid paramters and check for errors.
 * @scenario		Try to register a callback function with invalid paramters for change in device authorizationafter bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_set_authorization_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_set_authorization_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_set_authorization_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_authorization_changed_cb_n1
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then register a callback for change
 *				in device authorization with invalid paramters and check for errors.
 * @scenario		Registers a callback function with invalid paramters for change in device authorization.
 */
int utc_bluetooth_bt_device_set_authorization_changed_cb_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_authorization_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_device_set_authorization_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_unset_bond_created_cb_n
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then deinitialize  the bluetooth and
 *				the callback is unregistered for bond creation and check for errors.
 * @scenario		Try to unregister the callback function for bond creation after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_unset_bond_created_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_unset_bond_created_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_unset_bond_created_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_unset_bond_destroyed_cb_n
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then deinitialize  the bluetooth and
 *				the callback is unregistered for bond destroy and check for errors.
 * @scenario		Try to unregister the callback function for bond destroyafter bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_unset_bond_destroyed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_unset_bond_destroyed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_unset_bond_destroyed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_unset_authorization_changed_cb_n
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then deinitialize  the bluetooth and
 *				the callback is unregistered for change in device authorization and check for errors.
 * @scenario		Try to unregisters the callback function for change in device authorization, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_unset_authorization_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_unset_authorization_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_unset_authorization_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_create_bond_n
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				initiate bond creation to remote device and check for errors.
 * @scenario		Try to create a bond with a remote Bluetooth device, asynchronously after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_create_bond_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_create_bond(remote_address);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_create_bond(remote_address);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_create_bond_n1
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then initiate bond creation
 *				with invalid paramters and check for errors.
 * @scenario		Creates a bond with invalid parameters.
 */
int utc_bluetooth_bt_device_create_bond_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_create_bond(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_device_create_bond(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_cancel_bonding_n
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				cancel the bond creation to remote device and check for errors.
 * @scenario		Try to cancel the bonding process after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_cancel_bonding_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_cancel_bonding();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_cancel_bonding();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_destroy_bond_n
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				initiate bond destroy procedure to remote device and check for errors.
 * @scenario		Try to destroy the bond, asynchronously after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_destroy_bond_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_destroy_bond(remote_address);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_destroy_bond(remote_address);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_foreach_bonded_device_n1
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and all bonded
 *				device information is listed from the device list else all bonded device information is listed from the device list and checked for errors.
 * scenario		Try to retriev the device information of all bonded devices after bluetooth de-initialization.
 */
int utc_bluetooth_bt_adapter_foreach_bonded_device_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_foreach_bonded_device(bonded_device_cb_for_device_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_foreach_bonded_device(bonded_device_cb_for_device_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_foreach_bonded_device_n2
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then all bonded device information
 *				is listed from the device list with invalid parameters and checked for errors.
 * scenario 		Try to retriev the device information of all bonded devices with invalid parameters.
 */
int utc_bluetooth_bt_adapter_foreach_bonded_device_n2(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_foreach_bonded_device(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_foreach_bonded_device(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_alias_n
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				set device alias name and check for errors.
 * scenario		Try to sets an alias for the bonded device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_set_alias_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_set_alias(remote_address, "dts_alias");
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_set_alias(remote_address, "dts_alias");
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_alias_n2
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then set device alias name
 *				with invalid parameters and check for errors.
 * scenario		Try to sets an alias for the bonded device with invalid parameter.
 */
int utc_bluetooth_bt_device_set_alias_n2(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_alias(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_device_set_alias(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_authorization_n
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				set device authoriazation and check for errors.
 * scenario		Try to set the authorization of a bonded device, asynchronously after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_set_authorization_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_set_authorization(remote_address, BT_DEVICE_AUTHORIZED);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_set_authorization(remote_address, BT_DEVICE_AUTHORIZED);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_authorization_n2
 * @since_tizen		2.3
 * @description	check if bluetooth is supported and startup_flag is asserted then set device authoriazation
 *				with invalid parameters and check for errors.
 * scenario		Try to set authoriazation of a bonded device, asynchronously with invalid parameter.
 */
int utc_bluetooth_bt_device_set_authorization_n2(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_authorization(NULL, BT_DEVICE_AUTHORIZED);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_device_set_authorization(NULL, BT_DEVICE_AUTHORIZED);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_get_service_mask_from_uuid_list_n
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				retrive the service class of the uuid from uuid list a and check for errors.
 * @scenario		Try to get the service mask from the uuid list after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_get_service_mask_from_uuid_list_n(void)
{
#if defined(MOBILE) || defined(TIZENIOT) 
    char* uuid = "00001101-0000-1000-8000-00805f9b34fb";
    int no_of_service = 1;
    bt_service_class_t service_mask_list;
#endif
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

#if defined(MOBILE) || defined(TIZENIOT) 
        ret = bt_device_get_service_mask_from_uuid_list(&uuid, no_of_service,
					&service_mask_list);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
#else
        ret = bt_device_get_service_mask_from_uuid_list(NULL, 1, NULL);

        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
#endif
    } else {
#if defined(MOBILE) || defined(TIZENIOT) 
        ret = bt_device_get_service_mask_from_uuid_list(&uuid, no_of_service,
					&service_mask_list);
#else
        ret = bt_device_get_service_mask_from_uuid_list(NULL, 1, NULL);
#endif
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_is_profile_connected_n
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				retrive the profile connection state with respect to remote address and profile and check for errors
 * @scenario		Try to gets the profile connected status after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_is_profile_connected_n(void)
{
    bt_profile_e bt_profile = BT_PROFILE_RFCOMM;
    bool is_connected;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_device_is_profile_connected(remote_address, bt_profile, &is_connected);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_is_profile_connected(remote_address, bt_profile, &is_connected);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_connection_state_changed_cb_n
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register a callback for change in connection state and check for errors.
 * scenario 		Try to register a callback function to be invoked when the connection state is changed after bluetooth de-initialization.
 */
int utc_bluetooth_bt_device_set_connection_state_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_device_set_connection_state_changed_cb(bt_connection_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_set_connection_state_changed_cb(bt_connection_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_unset_connection_state_changed_cb_n
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				the callback is unregistered for change in connection state and check for errors.
 * scenario 		Try to unregister a callback function to be invoked when the connection state is changed after bluetooth de-initialization.

 */
int utc_bluetooth_bt_device_unset_connection_state_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_set_connection_state_changed_cb(bt_connection_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_device_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_device_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

static bool bt_device_connected_profiles_cb(bt_profile_e profile, void *user_data)
{
	return false;
}

/**
 * @testcase		utc_bluetooth_bt_device_foreach_connected_profiles_n
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then retrive the profile connection state
 *				with respect to remote address and profile for all devices with invalid parameters and check for errors
 * @scenario		Try to gets the profile connected status with invalid parameters.
 */
int utc_bluetooth_bt_device_foreach_connected_profiles_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_device_foreach_connected_profiles(NULL, bt_device_connected_profiles_cb, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_device_foreach_connected_profiles(NULL, bt_device_connected_profiles_cb, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_update_le_connection_mode_n
 * @since_tizen	3.0
 * @description	check if bluetooth is supported and startup_flag is asserted then update device le connection mode
 *				with invalid parameters and check for errors.
 * scenario		Try to update device le connection mode with invalid parameter.
 */
int utc_bluetooth_bt_device_update_le_connection_mode_n(void)
{
	if (bt_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_device_update_le_connection_mode(NULL, BT_DEVICE_LE_CONNECTION_MODE_BALANCED);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_device_update_le_connection_mode(NULL, BT_DEVICE_LE_CONNECTION_MODE_BALANCED);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

