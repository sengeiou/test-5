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


//& set: BluetoothDeviceDiscoveryNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool bt_supported = false;


/**
 * @function		utc_bluetooth_device_discovery_negative_startup
 * @description 	check if bluetooth is supported, Initialialize bluetooth.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_device_discovery_negative_startup(void)
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
 * @function		utc_bluetooth_device_discovery_negative_cleanup
 * @description 	check if bluetooth is supported release all the bluetooth resources.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_device_discovery_negative_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_adapter_stop_device_discovery_n1
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted, then de-initialize the bluetooth and
 *				stop the device discovery and check for errors.
 * @scenario		Try to stop the device discovery, asynchronously, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_adapter_stop_device_discovery_n1(void)
{

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_stop_device_discovery();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_stop_device_discovery();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_unset_device_discovery_state_changed_cb_n1
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted, then de-initialize the bluetooth and
 *				unregister the callback set for device discovery state changes and check for errors.
 * @scenario		Try to unregister a callback function to be invoked when the device discovery state changes, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_adapter_unset_device_discovery_state_changed_cb_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_unset_device_discovery_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_unset_device_discovery_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

static void device_discovery_state_changed_cb_for_discovery_p(int result,
                    bt_adapter_device_discovery_state_e discovery_state,
                    bt_adapter_device_discovery_info_s *discovery_info,
                    void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_adapter_set_device_discovery_state_changed_cb_n
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted, then de-initialize the bluetooth and
 *				register a callback that will be invoked when device discovery state changes and check for errors.
 * @scenario		Try to register a callback function, to be invoked when the device discovery state changes, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_adapter_set_device_discovery_state_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_set_device_discovery_state_changed_cb(device_discovery_state_changed_cb_for_discovery_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_set_device_discovery_state_changed_cb(device_discovery_state_changed_cb_for_discovery_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_set_device_discovery_state_changed_cb_n1
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted, then register a callback that will be
 *				invoked when device discovery state changes, by using invalid parameters and check for errors.
 * @scenario		Try to register a callback function, to be invoked when the device discovery state changes, by using invalid parameters.
 */
int utc_bluetooth_bt_adapter_set_device_discovery_state_changed_cb_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_device_discovery_state_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_set_device_discovery_state_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_start_device_discovery_n1
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted, then de-initialize the bluetooth and
 *				start the device discovery and check for errors.
 * @scenario		Try to start the device discovery, asynchronously, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_adapter_start_device_discovery_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_start_device_discovery();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_start_device_discovery();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_is_discovering_n1
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted, then de-initialize the bluetooth and
 *				check the satuts of device discovery and check for errors.
 * @scenario		Try to check for the device discovery is in progress or not after bluetooth de-initialization.
 */
int utc_bluetooth_bt_adapter_is_discovering_n1(void)
{
    bool status = false;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_is_discovering(&status);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_is_discovering(&status);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_is_discovering_n2
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted, then check the satuts of
 *				device discovery by using invalid parameters and check for errors.
 * @scenario		Try to check for the device discovery is in progress or not after bluetooth de-initialization, by using invalid parameters.
 */
int utc_bluetooth_bt_adapter_is_discovering_n2(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_is_discovering(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_is_discovering(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}
