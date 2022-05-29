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


//& set: BluetoothHIDNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool hid_supported = false;
static bool hid_device_supported = false;
static bool bt_supported = false;
static char *remote_address = "D8:90:E8:EE:2B:3A";

static void host_connection_state_changed_cb_for_hid_p(int result,
                bool connected, const char *remote_address, void *user_data)
{

}

/**
 * @function		utc_bluetooth_hid_negative_startup
 * @description	Check for the support of BT and HID features on the device and initialize the Bluetooth
 *				and HID(Human Interface Device) Host on the device.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_hid_negative_startup(void)
{
    startup_flag = BT_ERROR_NONE;

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
    }

    if(hid_supported)
        ret = bt_hid_host_initialize(host_connection_state_changed_cb_for_hid_p, NULL);
}

/**
 * @function		utc_bluetooth_hid_negative_cleanup
 * @description	Check for the support of BT and HID features on the device and deinitialize the HID(Human Interface Device) Host.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_hid_negative_cleanup(void)
{
    if(hid_supported)
        bt_hid_host_deinitialize();

    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_hid_host_initialize_n
 * @since_tizen	2.3
 * @description	Check for the support of HID feature and initialize the Bluetooth HID(Human Interface Device) Host with NULL parameters.
 *				Check bt is initialized and deinitialize the bluetooth and initialize the HID host on the device. Check for expected error.
 * @senario		Initialize the HID host when HID feature is not supported. Denitialize the bt adapter and re-initialize hid host and check status.
 */
int utc_bluetooth_bt_hid_host_initialize_n(void)
{
    if(!hid_supported) {
        ret = bt_hid_host_initialize(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_hid_host_initialize(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    }
    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hid_host_initialize_n1
 * @since_tizen	2.3
 * @description	Check for the support of HID feature and initialize the Bluetooth HID(Human Interface Device) Host with NULL parameters.
 *				Confirm the bluetooth is initialzed and then initialize the HID host on the device. Check for expected error.
 * @senario		Initialize the HID host when HID feature is not supported. Ensure bt is initlaized and initialize HID host and check status.
 */
int utc_bluetooth_bt_hid_host_initialize_n1(void)
{
    if(!hid_supported) {
        ret = bt_hid_host_initialize(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hid_host_initialize(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase	utc_bluetooth_bt_hid_host_connect_n
 * @since_tizen	2.3
 * @description	Check for the support of HID feature and perform connect operation from HID(Human Interface Device) Host with NULL parameter.
 *		Confirm the bluetooth is initialized and  perform connect operation from HID host with NULL parameter. Check for expected error.
 * @senario	 Perform the connect operation from HID Host when HID feature is not supported. Ensure bt is initialized and perform HID host connect and check status.
 */
int utc_bluetooth_bt_hid_host_connect_n(void)
{
	if(!hid_supported) {
		ret = bt_hid_host_connect(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(startup_flag, BT_ERROR_NONE);

#ifdef TV
        ret = bt_hid_host_connect(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
#else
		ret = bt_deinitialize();
		assert_eq(ret,BT_ERROR_NONE);

		ret = bt_hid_host_connect(NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
#endif
	}

	return 0;
}

/**
 * @testcase	utc_bluetooth_bt_hid_host_disconnect_n
 * @since_tizen	2.3
 * @description	Check for the support of HID feature and perform disconnect operation from HID(Human Interface Device) Host with NULL parameter.
 *		Confirm the bluetooth is initialized and  perform disconnect operation from HID host with NULL parameter. Check for expected error.
 * @senario	 Perform the disconnect operation from HID Host when HID feature is not supported. Ensure bt is initialized and perform HID host disconnect and check status.
 */
int utc_bluetooth_bt_hid_host_disconnect_n(void)
{
	if(!hid_supported) {
		ret = bt_hid_host_disconnect(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(startup_flag, BT_ERROR_NONE);

#ifdef TV
        ret = bt_hid_host_disconnect(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
#else
		ret = bt_deinitialize();
		assert_eq(ret,BT_ERROR_NONE);

		ret = bt_hid_host_disconnect(NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
#endif
	}

	return 0;
}

/**
 * @testcase	utc_bluetooth_bt_hid_host_deinitialize_n
 * @since_tizen	2.3
 * @description	Check for the support of HID feature and perform HID host deinitialize.
 *		Confirm the bluetooth is initialized and perform HID host initialize and deinitialize and then deinitialize again. Check for expected error.
 * @senario	 Perform the HID Host initialize and deinitialize operations mutiple times and for check for expected result.
 */
int utc_bluetooth_bt_hid_host_deinitialize_n(void)
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

        ret = bt_hid_host_deinitialize();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    }

    return 0;
}

#ifdef WEARABLE
/**
 * @testcase	utc_bluetooth_hid_device_activate_n
 * @since_tizen	3.0
 * @description	Check for the support of HID DEVICE feature and initialize the Bluetooth HID(Human Interface Device) DEVICE with NULL parameters.
 *				Check bt is initialized and deinitialize the bluetooth and initialize the HID device on the device. Check for expected error.
 * @senario		Activate the HID Device when HID DEVICE feature is not supported. Denitialize the bt adapter and re-activate hid device and check status.
 */
int utc_bluetooth_bt_hid_device_activate_n(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_activate(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_hid_device_activate(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase	utc_bluetooth_bt_hid_device_deactivate_n
 * @since_tizen	3.0
 * @description	Check for the support of HID DEVICE feature and perform HID device deactivate.
 *		Confirm the bluetooth is initialized and perform HID device activate and deactivate and then deactivate again. Check for expected error.
 * @senario	Perform the HID Device activate and deactivate operations mutiple times and for check for expected result.
 */
int utc_bluetooth_bt_hid_device_deactivate_n(void)
{
    if(!hid_device_supported) {
		ret = bt_hid_device_deactivate();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret,BT_ERROR_NONE);

		ret = bt_hid_device_deactivate();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    }

    return 0;
}

/**
 * @testcase	utc_bluetooth_bt_hid_device_connect_n
 * @since_tizen	3.0
 * @description	Check for the support of HID DEVICE feature and perform connect operation from HID(Human Interface Device) Device with NULL parameter.
 *		Confirm the bluetooth is initialized and  perform connect operation from HID device with NULL parameter. Check for expected error.
 * @senario		Perform the connect operation from HID Device when HID DEVICE feature is not supported. Ensure bt is initialized and perform HID Device connect and check status.
 */
int utc_bluetooth_bt_hid_device_connect_n(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_connect(remote_address);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_hid_device_connect(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase	utc_bluetooth_bt_hid_device_disconnect_n
 * @since_tizen	3.0
 * @description	Check for the support of HID DEVICE feature and perform disconnect operation from HID(Human Interface Device) Device with NULL parameter.
 *		Confirm the bluetooth is initialized and  perform disconnect operation from HID Device with NULL parameter. Check for expected error.
 * @senario		Perform the disconnect operation from HID Device when HID Device feature is not supported. Ensure bt is initialized and perform HID Device disconnect and check status.
 */
int utc_bluetooth_bt_hid_device_disconnect_n(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_disconnect(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_hid_device_disconnect(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_bt_hid_device_send_mouse_event_n
 * @since_tizen		3.0
 * @description		check if HID is supported and startup_flag is asserted, then send the mouse event's data to remote device
 *					by using invalid parameters and check for errors.
 * @scenario		Try to send the data to the remote device by using invalid parameters.
 */
int utc_bluetooth_bt_hid_device_send_mouse_event_n(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_send_mouse_event(remote_address, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_hid_device_send_mouse_event(remote_address, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_bt_hid_device_send_key_event_n
 * @since_tizen		3.0
 * @description 	check if HID is supported and startup_flag is asserted, then send the key event's data to remote device
 *				by using invalid parameters and check for errors.
 * @scenario		Try to send the data to the remote device by using invalid parameters.
 */
int utc_bluetooth_bt_hid_device_send_key_event_n(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_send_key_event(remote_address, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_hid_device_send_key_event(remote_address, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hid_device_reply_to_report_n
 * @since_tizen		3.0
 * @description 	check if HID is supported and startup_flag is asserted, then de-initialize the bluetooth and register a callback
 *				that will be invoked when you respose reports and check for errors.
 * @scenario		Try to respose to reports from HID host, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hid_device_reply_to_report_n(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_reply_to_report(remote_address, 0x01,
					 0x01, "reply", 8);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();

        ret = bt_hid_device_reply_to_report(remote_address, 0x01,
					0x01, "reply", 8);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hid_device_set_data_received_cb_n
 * @since_tizen		3.0
 * @description 	check if HID is supported and startup_flag is asserted, then de-initialize the bluetooth and register a callback
 * 				that will be invoked when you receive the data and check for errors.
 * @scenario		Try to register a callback function that will be invoked when you receive the data, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hid_device_set_data_received_cb_n(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_set_data_received_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();

        ret = bt_hid_device_set_data_received_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hid_device_unset_data_received_cb_n
 * @since_tizen		3.0
 * @description 	check if HID is supported and startup_flag is asserted, then de-initialize the bluetooth and unregister the callback
 *					set for receiving the data and check for errors.
 * @scenario		Try to unregister a callback function that will be invoked when you receive the data, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hid_device_unset_data_received_cb_n(void)
{
    if(!hid_device_supported) {
        ret = bt_hid_device_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();

        ret = bt_hid_device_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    }

    return 0;
}
#endif
