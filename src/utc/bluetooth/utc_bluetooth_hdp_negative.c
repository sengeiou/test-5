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

//& set: BluetoothHDPNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool hdp_supported = false;
static bool bt_supported = false;


/**
 * @function		utc_bluetooth_hdp_negative_startup
 * @description 	check if bluetooth is supported and HDP is supported, initialize bluetooth 
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_hdp_negative_startup(void)
{
    bt_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

    hdp_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.health", &hdp_supported);

    if(bt_supported) {
        startup_flag = BT_ERROR_NONE;
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
 * @function		utc_bluetooth_hdp_negative_cleanup
 * @description 	If bluetooth is supported and release all the bluetooth resources.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_hdp_negative_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_hdp_set_data_received_cb_n
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then de-initialize the bluetooth and register a callback
 *				that will be invoked when you receive the data and check for errors.
 * @scenario		Try to register a callback function that will be invoked when you receive the data, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hdp_set_data_received_cb_n(void)
{
    if(hdp_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_hdp_set_data_received_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_hdp_set_data_received_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_set_data_received_cb_n1
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then register a callback,
 *				that will be invoked when you receive the data, by using invalid parameters and check for errors.
 * @scenario		Try to register a callback function that will be invoked when you receive the data by using invalid parameters.
 */
int utc_bluetooth_bt_hdp_set_data_received_cb_n1(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_set_data_received_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hdp_set_data_received_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_set_connection_state_changed_cb_n
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then de-initialize the bluetooth and register a callback
 *				that will be invoked when HDP connection state is changed and check for errors.
 * @scenario		Try to register a callback function that will be invoked when the HDP connection state is changed, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hdp_set_connection_state_changed_cb_n(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_set_connection_state_changed_cb(NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_hdp_set_connection_state_changed_cb(NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_set_connection_state_changed_cb_n1
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then register a callback,
 *				that will be invoked when HDP connection state is changed, by using invalid parameters and check for errors.
 * @scenario		Try to register a callback function that will be invoked when the HDP connection state is changed, by using invalid parameters.
 */
int utc_bluetooth_bt_hdp_set_connection_state_changed_cb_n1(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_set_connection_state_changed_cb(NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hdp_set_connection_state_changed_cb(NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_disconnect_n
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then de-initialize the bluetooth and disconnect
 *				HDP connection and check for errors.
 * @scenario		Try to disconnect the remote device, asynchronously. after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hdp_disconnect_n(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_disconnect(NULL, 1);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_hdp_disconnect(NULL, 1);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_connect_to_source_n
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then disconnect HDP connection
 *				by using invalid parameters. and check for errors.
 * @scenario		Try to disconnect the remote device, asynchronously by using invalid parameters.
 */
int utc_bluetooth_bt_hdp_connect_to_source_n(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_connect_to_source(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);

#ifdef WEARABLE
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);
#endif
        ret = bt_hdp_connect_to_source(NULL, NULL);
#ifdef WEARABLE
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
#else
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
#endif
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_connect_to_source_n2
 * @since_tizen		2.3
 * @description		
 */
int utc_bluetooth_bt_hdp_connect_to_source_n2(void)
{
	if(!hdp_supported) {
		ret = bt_hdp_connect_to_source(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_hdp_connect_to_source(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_register_sink_app_n
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then de-initialize the bluetooth and register
 *				HDP app with sink role and check for errors.
 * @scenario		Try to register an application that acts as the @a Sink role of HDP(Health Device Profile), after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hdp_register_sink_app_n(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_register_sink_app(1, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_hdp_register_sink_app(1, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_unregister_sink_app_n
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then de-initialize the bluetooth and unregister
 *				HDP app with sink role and check for errors.
 * @scenario		Try to unregister an application that acts as the @a Sink role of HDP(Health Device Profile), after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hdp_unregister_sink_app_n(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_unregister_sink_app(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_hdp_unregister_sink_app(NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_unregister_sink_app_n1
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, unregister HDP app with sink role
 *				by using invalid parameters and check for errors.
 * @scenario		Try to unregister an application that acts as the @a Sink role of HDP(Health Device Profile) by using invalid parameters.
 */
int utc_bluetooth_bt_hdp_unregister_sink_app_n1(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_unregister_sink_app(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hdp_unregister_sink_app(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_hdp_send_data_n
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then send HDP data to remote device
 *				by using invalid parameters and check for errors.
 * @scenario		Try to send the data to the remote device by using invalid parameters.
 */
int utc_bluetooth_bt_hdp_send_data_n(void)
{
#ifdef WEARABLE
	const char *data = "dts_test";
#else
    char *data = "dts_test";
#endif
	if(!hdp_supported) {
#ifdef WEARABLE
        ret = bt_hdp_send_data(1, data, strlen(data));
#else
		ret = bt_hdp_send_data(1, data, sizeof(data));
#endif
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_deinitialize();
		assert_eq(ret,BT_ERROR_NONE);

#ifdef WEARABLE
        ret = bt_hdp_send_data(1, data, strlen(data));
#else
		ret = bt_hdp_send_data(1, data, sizeof(data));
#endif
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	}

	return 0;


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
 * @testcase		utc_bluetooth_bt_hdp_unset_connection_state_changed_cb_n
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then de-initialize the bluetooth and unregister the callback set
 *				for HDP connection state change and check for errors.
 * @scenario		Try to unregister a callback function that will be invoked when the HDP connection state is changed, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hdp_unset_connection_state_changed_cb_n(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hdp_set_connection_state_changed_cb(connected_cb_for_hdp_p,disconnected_cb_for_hdp_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_hdp_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

        bt_deinitialize();
        bt_hdp_unset_connection_state_changed_cb();
    }

    return 0;
}

static void data_received_cb_for_hdp_p(unsigned int channel, const char *data,
                    unsigned int size, void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_hdp_unset_data_received_cb_n
 * @since_tizen		2.3
 * @description 	check if HDP is supported and startup_flag is asserted, then de-initialize the bluetooth and unregister the callback
 *				set for receiving the data and check for errors.
 * @scenario		Try to unregister a callback function that will be invoked when you receive the data, after bluetooth de-initialization.
 */
int utc_bluetooth_bt_hdp_unset_data_received_cb_n(void)
{
    if(!hdp_supported) {
        ret = bt_hdp_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    } else {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_hdp_set_data_received_cb(data_received_cb_for_hdp_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_hdp_unset_data_received_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

        bt_deinitialize();
        bt_hdp_unset_data_received_cb();
    }

    return 0;
}
