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

//& set: BluetoothServiceSearchNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool bt_supported = false;

/**
 * @function		utc_bluetooth_service_search_negative_startup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then intialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_service_search_negative_startup(void)
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
 * @function		utc_bluetooth_service_search_negative_cleanup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then deintialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_service_search_negative_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_device_set_service_searched_cb_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the service
 *				searched callback and check for error. If bluetooth is initialized, deinitialize bluetooth and set the service searched callback.
 * @senario		Check if BT is supported and then deinitialize bluetooth and set bt_device_set_service_searched_cb on the device.
 *				Check result BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_device_set_service_searched_cb_n(void)
{
    if(!bt_supported) {
        ret = bt_device_set_service_searched_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_device_set_service_searched_cb(NULL, NULL);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_set_service_searched_cb_n1
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the service
 *				searched callback and check for error. If bluetooth is initialized, set the service searched callback.
 * @senario		Check if BT is supported and then set bt_device_set_service_searched_cb with NULL parameters on the device.
 *				Check result BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_device_set_service_searched_cb_n1(void)
{
    if(!bt_supported) {
        ret = bt_device_set_service_searched_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_device_set_service_searched_cb(NULL, NULL);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_unset_service_searched_cb_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, unset the service
 *				searched callback and check for error. If bluetooth is initialized, deinitialize bluetooth and unset the service searched callback.
 * @senario		Check if BT is supported and then call bt_device_unset_service_searched_cb on the device.
 *				Check result BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_device_unset_service_searched_cb_n(void)
{
    if(!bt_supported) {
        ret = bt_device_unset_service_searched_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_device_unset_service_searched_cb();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_start_service_search_n
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, start the service
 *				search on the device and check for error. If bluetooth is initialized, deinitialize bluetooth and call bt_device_start_service_search().
 * @senario		Check if BT is supported and then call bt_device_unset_service_searched_cb on the device.
 *				Check result BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_device_start_service_search_n(void)
{
    if(!bt_supported) {
        ret = bt_device_start_service_search(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_device_start_service_search(NULL);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}
