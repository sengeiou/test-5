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

//& set: BluetoothOpp-serverNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static const char *dest = "/tmp";
static bool opp_supported = false;
static bool bt_supported = false;


static void transfer_finished_cb_for_opp_server_p(int result, const char *file,
                                            long long size, void *user_data)
{

}

static void transfer_progress_cb_for_opp_server(const char *file, long long size,
                                                int percent, void *user_data)
{

}

static void transfer_finished_cb_for_opp_server(int result, const char *file,
                                            long long size, void *user_data)
{

}

/**
 * @function		utc_bluetooth_bt_opp_server_negative_startup
 * @description	Get system information to check for the support of Bluetooth and OPP feature. If BT is supported on the device,
 *				then intialize the bluetooth on the device successfully.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_bt_opp_server_negative_startup(void)
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
    }
}

/**
 * @function		utc_bluetooth_bt_opp_server_negative_cleanup
 * @description	Check if bluetooth and OPP features are supported. If OPP is supported then deinitialize opp server.
 *				If BT is supported then deinitialize bluetooth. Check for expected result.
 * @parameter       NA
 * @return          NA
 */
void utc_bluetooth_bt_opp_server_negative_cleanup(void)
{
#ifndef TV
    if(opp_supported)
        bt_opp_server_deinitialize();

    if(bt_supported)
        bt_deinitialize();
#endif
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_accept_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call opp server accept api.
 *				If BT is initialized then deinitialize bluetooth and call bt_opp_server_accept. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then deinitialize the bluetooth and call bt_opp_server_accept.
 *				Verify the result as BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_accept_n(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_accept(transfer_progress_cb_for_opp_server,
                            transfer_finished_cb_for_opp_server, NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_server_accept(transfer_progress_cb_for_opp_server,
                        transfer_finished_cb_for_opp_server, NULL, NULL, NULL);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_accept_n1
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call opp server accept api.
 *				If BT is initialized then  call bt_opp_server_accept. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_accept.
 *				verify for error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_accept_n1(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_accept(transfer_progress_cb_for_opp_server,
                            transfer_finished_cb_for_opp_server, NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_server_accept(transfer_progress_cb_for_opp_server,
                        transfer_finished_cb_for_opp_server, NULL, NULL, NULL);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_accept_n2
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call opp server accept api.
 *				If BT is initialized then  call bt_opp_server_accept. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_accept.
 *				verify for error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_accept_n2(void)
{
    int tid = 0;
    const char *name = "abc";

    if(!opp_supported) {
        ret = bt_opp_server_accept(transfer_progress_cb_for_opp_server,
                transfer_finished_cb_for_opp_server_p, name, NULL, &tid);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_server_accept(transfer_progress_cb_for_opp_server,
            transfer_finished_cb_for_opp_server_p, name, NULL, &tid);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_reject_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call bt_opp_server_reject().
 *				If BT is initialized then deinitialize bluetooth and call bt_opp_server_reject. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_reject.
 *				verify for error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_reject_n(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_reject();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_server_reject();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_reject_n1
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call bt_opp_server_reject().
 *				If BT is initialized then call bt_opp_server_reject. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_reject.
 *				verify for error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_reject_n1(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_reject();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_server_reject();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_set_destination_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call bt_opp_server_set_destination().
 *				If BT is initialized then deinitialize bluetooth and set the destination for opp server with NULL parameters. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_set_destination.
 *				verify for error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_set_destination_n(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_set_destination(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_server_set_destination(NULL);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_set_destination_n1
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call bt_opp_server_set_destination().
 *				If BT is initialized then set the destination for opp server with NULL parameters. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_set_destination.
 *				verify for error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_set_destination_n1(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_set_destination(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_server_set_destination(NULL);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_set_destination_n2
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call bt_opp_server_set_destination().
 *				If BT is initialized then set the destination for opp server with valid parameters. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_set_destination.
 *				verify for error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_set_destination_n2(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_set_destination(dest);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_server_set_destination(dest);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_initialize_by_connection_request_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call bt_opp_server_initialize_by_connection_request().
 *				If BT is initialized then deinitialize bluetooth and initialize opp server by connect request. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_initialize_by_connection_request.
 *				verify for error BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_initialize_by_connection_request_n(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_initialize_by_connection_request(NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_server_initialize_by_connection_request(NULL, NULL, NULL);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_initialize_by_connection_request_n1
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call bt_opp_server_initialize_by_connection_request().
 *				If BT is initialized then initialize opp server by connect request with NULL parameters. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_initialize_by_connection_request with NULL params.
 *				Verify for error BT_ERROR_INVALID_PARAMETER.
 */
int utc_bluetooth_bt_opp_server_initialize_by_connection_request_n1(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_initialize_by_connection_request(NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_server_initialize_by_connection_request(NULL, NULL, NULL);
    assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_deinitialize_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then deinitialize opp server.
 *				If BT is initialized then deinitialize bluetooth and deinitialize opp server. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_deinitialize.
 *				Verify result as BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_deinitialize_n(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_deinitialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_server_deinitialize();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_deinitialize_n1
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then deinitialize opp server.
 *				If BT is initialized then deinitialize opp server. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_deinitialize.
 *				Verify result as BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_deinitialize_n1(void)
{
    if(!opp_supported) {
        ret = bt_opp_server_deinitialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_server_deinitialize();
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_cancel_transfer_n
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call bt_opp_server_cancel_transfer().
 *				If BT is initialized then deinitialize bluetooth and cancel the transfer of data from opp server. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_cancel_transfer.
 *				Verify result as BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_cancel_transfer_n(void)
{
    int tid = 0;

    if(!opp_supported) {
        ret = bt_opp_server_cancel_transfer(tid);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_deinitialize();
    assert_eq(ret,BT_ERROR_NONE);

    ret = bt_opp_server_cancel_transfer(tid);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_opp_server_cancel_transfer_n1
 * @since_tizen	2.3
 * @description	Check if bluetooth and OPP features are supported. If OPP is not supported then call bt_opp_server_cancel_transfer().
 *				If BT is initialized then cancel the transfer of data from opp server. Check for expected result.
 * @senario		Check if BT and OPP features are supported and then call bt_opp_server_cancel_transfer.
 *				Verify result as BT_ERROR_NOT_INITIALIZED.
 */
int utc_bluetooth_bt_opp_server_cancel_transfer_n1(void)
{
    int tid = 0;

    if(!opp_supported) {
        ret = bt_opp_server_cancel_transfer(tid);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
        return 0;
    }

    assert_eq(startup_flag, BT_ERROR_NONE);

    ret = bt_opp_server_cancel_transfer(tid);
    assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

    return 0;
}
