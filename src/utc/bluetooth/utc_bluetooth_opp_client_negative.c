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

//& set: BluetoothOpp-clientNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool opp_supported = false;
static bool bt_supported = false;


/**
 * @function		utc_bluetooth_opp_client_negative_startup
 * @description	Get system information to check for the support of Bluetooth and OPP feature. If BT is supported on the device,
 *			then intialize the bluetooth on the device successfully. If OPP is supported, initialize opp client.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_opp_client_negative_startup(void)
{
    startup_flag = BT_ERROR_NONE;

    bt_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

    opp_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.opp", &opp_supported);

    if(bt_supported) {
        ret = bt_initialize();
        if(BT_ERROR_NONE != ret) {
            fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
            fprintf(stderr, "bt_initialize failed (code: %d)\n", ret);
            startup_flag = ret;
            return;
        }
    }

    if(opp_supported) {
        ret = bt_opp_client_initialize();
        if(BT_ERROR_NONE != ret) {
            fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
            fprintf(stderr, "bt_opp_client_initialize failed (code: %d)\n", ret);
            startup_flag = ret;
        }
    }
}

/**
 * @function		utc_bluetooth_opp_client_negative_cleanup
 * @description	Check if bluetooth and OPP featurse are supported. If OPP is supported then deinitialize opp client.
 *				If BT is supported then deinitialize bluetooth. Check for expected result.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_opp_client_negative_cleanup(void)
{
    if(opp_supported)
        bt_opp_client_deinitialize();

    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_opp_client_initialize_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP featurse are supported. If OPP is supported then  try to initialize opp client.
 *				If BT is supported then deinitialize bluetooth. Now try to initialize the opp client. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then deinitialize bluetooth and initialize opp on the device.
 *				Should get error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_client_initialize_n(void)
{
    if(!opp_supported) {
        ret = bt_opp_client_initialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_opp_client_initialize();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_client_deinitialize_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then  try to deinitialize opp client.
 *				If BT is supported then deinitialize bluetooth. Now try to deinitialize the opp client. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then deinitialize opp client and bluetooth on the device.
 *				Should get error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_client_deinitialize_n(void)
{
    if(!opp_supported) {
        ret = bt_opp_client_deinitialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_opp_client_deinitialize();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_client_add_file_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then do bt_opp_client_add_file().
 *				If BT is supported then deinitialize bluetooth. Now try to call bt_opp_client_add_file(). Check for expected result.
 * @senario		Check if BT and OPP features are supported and deinitialize bluetooth on the device and call bt_opp_client_add_file ().
 *				Should get error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_client_add_file_n(void)
{
    const char *file = "/tmp/image16.jpg";

    if(!opp_supported) {
        ret = bt_opp_client_add_file(file);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_client_add_file(file);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_client_add_file_n1
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then do bt_opp_client_add_file().
 *				If BT is initialzed then try to call bt_opp_client_add_file() with NULL parameter. Check for result BT_ERROR_INVALID_PARAMETER.
 * @senario		Check if BT is initalized and OPP features is supported and call bt_opp_client_add_file () with NULL parameters.
 */
int utc_bluetooth_bt_opp_client_add_file_n1(void)
{
    if(!opp_supported) {
        ret = bt_opp_client_add_file(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_client_add_file(NULL);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_client_clear_files_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP feature are supported. If OPP is not supported then do bt_opp_client_clear_files().
 *				If BT is initialized, then deinitalize bluetooth and call bt_opp_client_clear_files(). Check for result BT_ERROR_NOT_INITIALIZED.
 * @senario		Check if BT and OPP features are supported and call bt_opp_client_clear_files () after deinitializing the bluetooth.
 */
int utc_bluetooth_bt_opp_client_clear_files_n(void)
{
    if(!opp_supported) {
        ret = bt_opp_client_clear_files();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_client_clear_files();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_client_push_files_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP feature are supported. If OPP is not supported then call bt_opp_client_push_files().
 *				If BT is initialized, then deinitalize bluetooth and call bt_opp_client_push_files(). Check for result BT_ERROR_NOT_INITIALIZED.
 * @senario		Check if BT and OPP features are supported and call bt_opp_client_push_files () after deinitializing the bluetooth.
 */
int utc_bluetooth_bt_opp_client_push_files_n(void)
{
    if(!opp_supported) {
        ret = bt_opp_client_push_files(NULL, NULL, NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_client_push_files(NULL, NULL, NULL, NULL, NULL);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_client_cancel_push_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP feature are supported. If OPP is not supported then call bt_opp_client_cancel_push().
 *				If BT is initialized, then deinitalize bluetooth and call bt_opp_client_cancel_push(). Check for result BT_ERROR_NOT_INITIALIZED.
 * @senario		Check if BT and OPP features are supported and call bt_opp_client_cancel_push () after deinitializing the bluetooth.
 */
int utc_bluetooth_bt_opp_client_cancel_push_n(void)
{
    if(!opp_supported) {
        ret = bt_opp_client_cancel_push();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_client_cancel_push();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}
