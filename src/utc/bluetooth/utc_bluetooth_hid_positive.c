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

//& set: BluetoothHIDPositive

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool hid_supported = false;
static bool hid_device_supported = false;
static bool bt_supported = false;


static void host_connection_state_changed_cb_for_hid_p(int result,
                bool connected, const char *remote_address, void *user_data)
{
}

static void device_connection_state_changed_cb_for_hid_p(int result,
      bool connected, const char *remote_address, void *user_data)
{

}

#ifdef WEARABLE
static void device_data_received_cb_for_hid_p(const bt_hid_device_received_data_s *data,
      void *user_data)
{

}
#endif

/**
 * @function		utc_bluetooth_hid_positive_startup
 * @description	Get system information to check for the support of Bluetooth and HID feature. If BT is supported on the device,
 *			then intialize the bluetooth on the device successfully and retrieve the adapter state.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_hid_positive_startup(void)
{

#ifdef TV
#ifndef TV_PRODUCT
	bt_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

	hid_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.hid", &hid_supported);
#else
	bt_supported = true;
	hid_supported = true;
#endif
#else
    bt_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

    hid_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.hid", &hid_supported);
#ifdef WEARABLE
    hid_device_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.hid_device", &hid_device_supported);
#endif
#endif

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
        }
    }
}

/**
 * @function		utc_bluetooth_hid_positive_cleanup
 * @description	Check the system if HID feature is supported and if so deinitialize the hid support on the device.
 *				Check if BT is supported on the system and then deinitliaze the bluetooth. All resources should be cleaned up.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_hid_positive_cleanup(void)
{
    if(hid_supported)
        bt_hid_host_deinitialize();

    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_hid_host_initialize_p
 * @since_tizen	2.3
 * @description	Check the system if HID feature is supported and if so initialize the HID host on the device. Check for expected result.
 *				Check if BT is supported on the system and then initliaze the HID host. Check for expected result.
 * @senario		Check for the support of BT and HID features and then initialze the HID host.
 */
int utc_bluetooth_bt_hid_host_initialize_p(void)
{
    if(!hid_supported) {
        ret = bt_hid_host_initialize(host_connection_state_changed_cb_for_hid_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hid_host_initialize(host_connection_state_changed_cb_for_hid_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hid_host_deinitialize_p
 * @since_tizen	2.3
 * @description	Check if HID feature is supported and if so deinitialize the HID host on the device. Check for expected result.
 *				Check if BT is supported on the system and then initliaze and deinitalize the HID host. Check for expected result.
 * @senario		Check for the support of BT and HID features then initialze and deinitlaize the HID host.
 */
int utc_bluetooth_bt_hid_host_deinitialize_p(void)
{
    if(!hid_supported) {
        ret = bt_hid_host_deinitialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hid_host_initialize(host_connection_state_changed_cb_for_hid_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_hid_host_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);
    }

    return 0;
}

#ifdef WEARABLE
/**
 * @testcase	utc_bluetooth_hid_device_activate_p
 * @since_tizen	3.0
 * @description	Check for the support of HID DEVICE feature and activate the Bluetooth HID(Human Interface Device) DEVICE with registering call back.
 *				Check to activate the HID device. Check for expected error.
 * @senario		Activate the HID Device when HID DEVICE feature is supported. After finish to activate hid device successfully and deactivate hid device.
 */
int utc_bluetooth_bt_hid_device_activate_p(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_activate(device_connection_state_changed_cb_for_hid_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_hid_device_activate(device_connection_state_changed_cb_for_hid_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_hid_device_deactivate();
    }

    return 0;
}

/**
 * @testcase	utc_bluetooth_bt_hid_device_deactivate_p
 * @since_tizen	3.0
 * @description	Check for the support of HID DEVICE feature and perform HID device deactivate.
 *		Confirm the bluetooth is initialized and perform HID device activate and deactivate. Check for expected error.
 * @senario	Perform the HID Device activate and deactivate operations and for check for expected result.
 */
int utc_bluetooth_bt_hid_device_deactivate_p(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_deactivate();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_hid_device_activate(device_connection_state_changed_cb_for_hid_p, NULL);

        ret = bt_hid_device_deactivate();
        assert_eq(ret, BT_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hid_device_set_data_received_cb_p
 * @since_tizen		3.0
 * @description 	check if HID Device is supported and startup_flag is asserted then register a callback
 *				 that will be invoked when you receive the data and check for errors.
 * @scenario		Try to register a callback function that will be invoked when you receive the data, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hid_device_set_data_received_cb_p(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_set_data_received_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_hid_device_set_data_received_cb(device_data_received_cb_for_hid_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_hid_device_unset_data_received_cb();
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hid_device_unset_data_received_cb_p
 * @since_tizen		3.0
 * @description 	check if HID Device is supported and startup_flag is asserted then unregister a callback
 *				 that will be invoked when you receive the data and check for errors.
 * @scenario		Registers a callback function that will be invoked when you receive the data.
 */
int utc_bluetooth_bt_hid_device_unset_data_received_cb_p(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_hid_device_set_data_received_cb(device_data_received_cb_for_hid_p, NULL);

        ret = bt_hid_device_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NONE);
    }

    return 0;
}
#endif
