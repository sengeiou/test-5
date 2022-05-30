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


//& set: BluetoothDeviceDiscoveryPositive

static int startup_flag = BT_ERROR_NONE;
static GMainLoop *mainloop = NULL;
static int ret = BT_ERROR_NONE;
static bool callback_result = false;
static bool bt_supported = false;


static void device_discovery_state_changed_cb_for_discovery_p(int result,
                    bt_adapter_device_discovery_state_e discovery_state,
                    bt_adapter_device_discovery_info_s *discovery_info,
                    void *user_data)
{
}

static gboolean timeout_func(gpointer data)
{
    g_main_loop_quit((GMainLoop *) data);
    return FALSE;
}

static void wait_for_async()
{
    int timeout_id = 0;
    mainloop = g_main_loop_new(NULL, FALSE);

    timeout_id = g_timeout_add(3000, timeout_func, mainloop);
    g_main_loop_run(mainloop);
    g_source_remove(timeout_id);
}

/**
 * @function		utc_bluetooth_device_discovery_positive_startup
 * @description 	check if bluetooth is supported, initialize bluetooth and check the adapter state and
 *				store adapter state for further use.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_device_discovery_positive_startup(void)
{
    bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;
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

        callback_result = false;
        ret = bt_adapter_get_state(&adapter_state);
        if (adapter_state != BT_ADAPTER_ENABLED) {
                fprintf(stdout, "BT is not enabled!!");
                startup_flag = BT_ERROR_NOT_ENABLED;
        }
    }
}

/**
 * @function		utc_bluetooth_device_discovery_positive_cleanup
 * @description 	check if bluetooth is supported and release all the bluetooth resources.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_device_discovery_positive_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_adapter_is_discovering_p
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted, then check the satuts of device discovery,
 *				and check for errors.
 * @scenario		Checks for the device discovery is in progress or not.
 */
int utc_bluetooth_bt_adapter_is_discovering_p(void)
{
    bool status = false;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_is_discovering(&status);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_is_discovering(&status);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_set_device_discovery_state_changed_cb_p
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then register a callback that
 *				will be invoked when device discovery state changes and check for errors.
 * @scenario		Registers a callback function to be invoked when the device discovery state changes.
 */
int utc_bluetooth_bt_adapter_set_device_discovery_state_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_device_discovery_state_changed_cb(device_discovery_state_changed_cb_for_discovery_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_set_device_discovery_state_changed_cb(device_discovery_state_changed_cb_for_discovery_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_start_device_discovery_p
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted, start the device discovery
 *				and check for errors.
 * @scenario		Starts the device discovery, asynchronously.
 */
int utc_bluetooth_bt_adapter_start_device_discovery_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_stop_device_discovery();
        assert(BT_ERROR_NONE == ret || BT_ERROR_NOT_IN_PROGRESS == ret);
        if(BT_ERROR_NONE == ret) {
            wait_for_async();
        }

        ret = bt_adapter_start_device_discovery();
        assert_eq(ret, BT_ERROR_NONE);

        wait_for_async();
        ret = bt_adapter_stop_device_discovery();
        wait_for_async();
    } else {
        ret = bt_adapter_start_device_discovery();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_unset_device_discovery_state_changed_cb_p
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted then unregister the callback set
 *				for device discovery state changes and check for errors.
 * @scenario		Unregisters a callback function to be invoked when the device discovery state changes.
 */
int utc_bluetooth_bt_adapter_unset_device_discovery_state_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_unset_device_discovery_state_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_unset_device_discovery_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_adapter_stop_device_discovery_p
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported and startup_flag is asserted, then stop the device discovery
 *				and check for errors.
 * @scenario		Stops the device discovery, asynchronously.
 */
int utc_bluetooth_bt_adapter_stop_device_discovery_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_stop_device_discovery();
        assert(BT_ERROR_NONE == ret || BT_ERROR_NOT_IN_PROGRESS == ret);
        if(BT_ERROR_NONE == ret) {
            wait_for_async();
        }

        ret = bt_adapter_start_device_discovery();
        assert_eq(ret, BT_ERROR_NONE);
        wait_for_async();

        ret = bt_adapter_stop_device_discovery();
        assert_eq(ret, BT_ERROR_NONE);
        wait_for_async();
    } else {
        ret = bt_adapter_stop_device_discovery();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}
