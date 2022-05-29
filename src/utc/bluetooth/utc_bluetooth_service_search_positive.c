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

//& set: BluetoothServiceSearchPositive

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool bt_supported = false;

static void service_searched_cb_for_service_search_p(int result,
                            bt_device_sdp_info_s *sdp_info,
                            void *user_data)
{

}

/**
 * @function		utc_bluetooth_service_search_positive_startup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then intialize the bluetooth on the device successfully and retrieve the adapter state.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_service_search_positive_startup(void)
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

    if(bt_supported) {
        ret = bt_initialize();
        if(BT_ERROR_NONE != ret) {
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
 * @function		utc_bluetooth_service_search_positive_cleanup
 * @description	Get system information to check for the support of Bluetooth. If BT is supported on the device,
 *				then deintialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_service_search_positive_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_device_set_service_searched_cb_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, set the service
 *				searched callback and check for error. If bluetooth is initialized, set and unset the service searched callback successfully.
 * @senario		Check if BT is supported and then set bt_device_set_service_searched_cb on the device and check for expected result.
 */
int utc_bluetooth_bt_device_set_service_searched_cb_p(void)
{
    if(!bt_supported) {
        ret = bt_device_set_service_searched_cb(service_searched_cb_for_service_search_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_device_set_service_searched_cb(service_searched_cb_for_service_search_p, NULL);
    assert_eq(ret, BT_ERROR_NONE);

    bt_device_unset_service_searched_cb();

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_device_unset_service_searched_cb_p
 * @since_tizen	2.3
 * @description	Get system information to check for the support of Bluetooth. If BT is not supported on the device, unset the service
 *				searched callback and check for error. If bluetooth is initialized, set and unset the service searched callback successfully.
 * @senario		Check if BT is supported and then set bt_device_unset_service_searched_cb on the device and check for expected result.
 */
int utc_bluetooth_bt_device_unset_service_searched_cb_p(void)
{
    if(!bt_supported) {
        ret = bt_device_unset_service_searched_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_device_set_service_searched_cb(service_searched_cb_for_service_search_p, NULL);
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_device_unset_service_searched_cb();
    assert_eq(ret, BT_ERROR_NONE);

    return 0;
}
