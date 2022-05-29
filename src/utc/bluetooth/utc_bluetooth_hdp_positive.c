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


//& set: BluetoothHDPPositive

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool hdp_supported = false;
static bool bt_supported = false;


static void data_received_cb_for_hdp_p(unsigned int channel, const char *data,
                    unsigned int size, void *user_data)
{

}

static void connected_cb_for_hdp_p(int result, const char *remote_address,
                    const char *app_id,
                    bt_hdp_channel_type_e type, unsigned int channel, void *user_data)
{

}

static void disconnected_cb_for_hdp_p(int result, const char *remote_address,
                    unsigned int channel, void *user_data)
{

}

/**
 * @function		utc_bluetooth_hdp_positive_startup
 * @description 	check if bluetooth is supported and HDP is supported, Initialize bluetooth and check the adapter state and
 *				store adapter state for further use.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_hdp_positive_startup(void)
{
    bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;
    startup_flag = BT_ERROR_NONE;

    bt_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

    hdp_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.health", &hdp_supported);

    if(bt_supported) {
        ret = bt_initialize();
        if(BT_ERROR_NONE != ret) {
            fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
            fprintf(stderr, "bt_initialize failed (code: %d)\n", ret);
            startup_flag = ret;
            return;
        }

        ret = bt_adapter_get_state(&adapter_state);
        if (adapter_state != BT_ADAPTER_ENABLED) {
                fprintf(stdout, "BT is not enabled!!");
                startup_flag = BT_ERROR_NOT_ENABLED;
        }
    }
}

/**
 * @function		utc_bluetooth_hdp_positive_cleanup
 * @description 	check If bluetooth is supported release all the bluetooth resources.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_hdp_positive_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_hdp_set_data_received_cb_p
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted then register a callback
 *				 that will be invoked when you receive the data and check for errors.
 * @scenario		Registers a callback function that will be invoked when you receive the data.
 */
int utc_bluetooth_bt_hdp_set_data_received_cb_p(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_set_data_received_cb(data_received_cb_for_hdp_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hdp_set_data_received_cb(data_received_cb_for_hdp_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_hdp_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_unset_data_received_cb_p
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted then unregister a callback
 *				 that will be invoked when you receive the data and check for errors.
 * @scenario		unregisters a callback function that will be invoked when you receive the data.
 */
int utc_bluetooth_bt_hdp_unset_data_received_cb_p(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hdp_set_data_received_cb(data_received_cb_for_hdp_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_hdp_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_set_connection_state_changed_cb_p
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted then register a callback that will be
 *				called when HDP connection state is changed and check for errors.
 * scenario 		Registers a callback function that will be invoked when the HDP connection state is changed.
 */
int utc_bluetooth_bt_hdp_set_connection_state_changed_cb_p(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_set_connection_state_changed_cb(connected_cb_for_hdp_p,disconnected_cb_for_hdp_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hdp_set_connection_state_changed_cb(connected_cb_for_hdp_p,disconnected_cb_for_hdp_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_hdp_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_unset_connection_state_changed_cb_p
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted then unregister the callback set for
 *				HDP connection state change and check for errors.
 * scenario 		Unregisters a callback function that will be invoked when the HDP connection state is changed.
 */
int utc_bluetooth_bt_hdp_unset_connection_state_changed_cb_p(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hdp_set_connection_state_changed_cb(connected_cb_for_hdp_p,disconnected_cb_for_hdp_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_hdp_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_unregister_sink_app_p
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted then unregister the app 
 *				that acts as sink role for HDP and checked for errors.
 * scenario 		Unregisters the given application that acts as the @a Sink role of HDP(Health Device Profile).
 */
int utc_bluetooth_bt_hdp_unregister_sink_app_p(void)
{
    char *app_id = NULL;

    if(!hdp_supported) {
        ret = bt_hdp_unregister_sink_app(app_id);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
#ifdef WEARABLE
        ret = bt_hdp_register_sink_app(1, &app_id);
        assert_eq(ret, BT_ERROR_NONE);
#else
        bt_hdp_register_sink_app(1, &app_id);
#endif

        ret = bt_hdp_unregister_sink_app(app_id);
        assert_eq(ret, BT_ERROR_NONE);

        free(app_id);
        app_id = NULL;
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_register_sink_app_p
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted then register the app 
 *				that acts as sink role for HDP and checked for errors.
 * scenario 		Registers the given application that acts as the @a Sink role of HDP(Health Device Profile).
 */
int utc_bluetooth_bt_hdp_register_sink_app_p(void)
{
    char *app_id = NULL;

    if(!hdp_supported) {
        ret = bt_hdp_register_sink_app(1, &app_id);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hdp_register_sink_app(1, &app_id);
        assert_eq(ret, BT_ERROR_NONE);

#ifdef WEARABLE
        ret = bt_hdp_unregister_sink_app(app_id);
        assert_eq(ret, BT_ERROR_NONE);
#else
		bt_hdp_unregister_sink_app(app_id);
#endif

        free(app_id);
        app_id = NULL;
    }

    return 0;
}
