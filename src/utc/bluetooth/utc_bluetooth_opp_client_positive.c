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

//& set: BluetoothOpp-client_Positive

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool opp_supported = false;
static bool bt_supported = false;


/**
 * @function		utc_bluetooth_opp_client_positive_startup
 * @description	Get system information to check for the support of Bluetooth and OPP feature. If BT is supported on the device,
 *				then intialize the bluetooth on the device successfully and retrieve the adapter state. If OPP is supported, initialize opp client.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_opp_client_positive_startup(void)
{
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

        bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;
        ret = bt_adapter_get_state(&adapter_state);
        if (adapter_state != BT_ADAPTER_ENABLED) {
                fprintf(stdout, "BT is not enabled!!");
                startup_flag = BT_ERROR_NOT_ENABLED;
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
 * @function		utc_bluetooth_opp_client_positive_cleanup
 * @description	Check if bluetooth and OPP feature is supported. If OPP is supported then deinitialize opp client.
 *				If BT is supported then deinitialize bluetooth. Check for expected result.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_opp_client_positive_cleanup(void)
{
    if(opp_supported)
        bt_opp_client_deinitialize();

    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_opp_client_initialize_p
 * @since_tizen	2.3
 * @description	Check if OPP feature is supported. If OPP is non-supported then initialize OPP client. If bluetooth is initialized,
 *				deinitialize the opp client and then re-initialize the opp client. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then initialize and deinitialize the OPP client
 */
int utc_bluetooth_bt_opp_client_initialize_p(void)
{
    if(!opp_supported) {
        ret = bt_opp_client_initialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_client_deinitialize();
    assert_eq(ret, BT_ERROR_NONE);

	ret = bt_opp_client_initialize();
	assert_eq(ret, BT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_client_deinitialize_p
 * @since_tizen	2.3
 * @description	Check if OPP feature is supported. If OPP is not supported then de-initialize the OPP client. If bluetooth is initialized,
 *				then deinitialize the opp client. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then deinitialize the OPP client
 */
int utc_bluetooth_bt_opp_client_deinitialize_p(void)
{
    if(!opp_supported) {
        ret = bt_opp_client_deinitialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_opp_client_deinitialize();
	assert_eq(ret, BT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_client_clear_files_p
 * @since_tizen	2.3
 * @description	Check for support of OPP feature and then clear all files received by the OPP client. If bluetooth is initialized,
 *				then clear all files received by the opp client. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_client_clear_files() from OPP client
 */
int utc_bluetooth_bt_opp_client_clear_files_p(void)
{
    if(!opp_supported) {
        ret = bt_opp_client_clear_files();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_client_clear_files();
	assert_eq(ret, BT_ERROR_NONE);

	return 0;
}
