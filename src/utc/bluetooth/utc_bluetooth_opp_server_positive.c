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

//& set: BluetoothOpp-serverPositive

static bool startup_flag = true;
static int ret = BT_ERROR_NONE;
static const char *dest = "/tmp";
static bool opp_supported = false;
static bool bt_supported = false;


static void push_requested_cb_for_opp_server_p(const char *remote_address,
                                                            void *user_data)
{

}

/**
 * @function		utc_bluetooth_opp_server_positive_startup
 * @description	Get system information to check for the support of Bluetooth and OPP feature. If BT is supported on the device,
 *				then intialize the bluetooth on the device successfully and retrieve the adapter state.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_opp_server_positive_startup(void)
{
    bt_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

    opp_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.opp", &opp_supported);

    startup_flag = BT_ERROR_NONE;

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
 * @function		utc_bluetooth_opp_server_positive_cleanup
 * @description	If BT is supported on the device, then deintialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_opp_server_positive_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_initialize_by_connection_request_p
 * @since_tizen	2.3
 * @description	Check if OPP feature is supported. If OPP is non-supported then try to initialize the opp server.
 * @senario		Check if BT is initialized and then call bt_opp_server_initialize_by_connection_request().
 * @senario		check if BT and OPP support is available on the device. Then call bt_opp_server_initialize_by_connection_request()
 *				and check for expected result.
 */
int utc_bluetooth_bt_opp_server_initialize_by_connection_request_p(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_initialize_by_connection_request(dest, push_requested_cb_for_opp_server_p, NULL);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_server_initialize_by_connection_request(dest, push_requested_cb_for_opp_server_p, NULL);
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_server_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_deinitialize_p
 * @since_tizen	2.3
 * @description	Check if OPP feature is supported. If OPP is non-supported then try to deinitialize the opp server (bt_opp_server_deinitialize).
 * @senario		Check if BT is initialized and then call bt_opp_server_initialize_by_connection_request(). Then deinitialize opp server.
 * @senario		Check if BT and OPP support is available on the device. Then call bt_opp_server_initialize_by_connection_request()
 *				and bt_opp_server_deinitialize() and check for expected result.
 */
int utc_bluetooth_bt_opp_server_deinitialize_p(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_deinitialize();
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

	ret = bt_opp_server_initialize_by_connection_request(dest, push_requested_cb_for_opp_server_p, NULL);

    ret = bt_opp_server_deinitialize();
    assert_eq(ret, BT_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_set_destination_p
 * @since_tizen	2.3
 * @description	Check if OPP feature is supported. If OPP is non-supported then try to intialize the opp server.
 * @senario		Check if BT is initialized and then call bt_opp_server_initialize_by_connection_request(). Then set destination for opp server.
 * @senario		Check if BT and OPP support is available on the device. Then call bt_opp_server_initialize_by_connection_request() and
 * 				then set destination(bt_opp_server_set_destination) and check for expected result.
 */
int utc_bluetooth_bt_opp_server_set_destination_p(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_initialize_by_connection_request(dest, push_requested_cb_for_opp_server_p, NULL);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_server_initialize_by_connection_request(dest, push_requested_cb_for_opp_server_p, NULL);
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_opp_server_set_destination(dest);
    assert_eq(ret, BT_ERROR_NONE);

    ret = bt_opp_server_deinitialize();
    assert_eq(ret, BT_ERROR_NONE);

    return 0;
}
