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
#include "bluetooth.h"
#include "assert.h"
#include <glib.h>
#include <system_info.h>

//& set: BluetoothCommonPositive

static int ret = BT_ERROR_NONE;
static bool supported = false;

/**
 * @function		utc_bluetooth_common_startup
 * @description 	initialize bluetooth and check the adapter state and store adapter state for further use.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_common_startup(void)
{
    ret = bt_initialize();
    supported = false;

#ifdef TV
#ifndef TV_PRODUCT
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &supported);
#else
	supported = true;
#endif
#else
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &supported);
#endif
}

/**
 * @function		utc_bluetooth_common_cleanup
 * @description 	release all the bluetooth resources.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_common_cleanup(void)
{
	bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_initialize_p
 * @since_tizen		2.3
 * @description 	check if bluetooth is supported or not and check for errors.
 * @scenario		 Check if bluetooth is supported or not.
 */
int utc_bluetooth_bt_initialize_p(void)
{
    ret = bt_initialize();

    if(!supported) {
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(ret, BT_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_deinitialize_p
 * @since_tizen		2.3
 * @description 	de-initialize the bluetooth and check if bluetooth is supported or not and check for errors.
 * @scenario		Releases all resources of the Bluetooth API, after bluetooth de-initialization.

 */
int utc_bluetooth_bt_deinitialize_p(void)
{
    ret = bt_deinitialize();

    if(!supported) {
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }  else {
        assert_eq(ret, BT_ERROR_NONE);
    }

    return 0;
}

