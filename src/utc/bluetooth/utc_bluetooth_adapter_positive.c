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
#include <time.h>
#include <string.h>
#include <system_info.h>

//& set: BluetoothAdapterPositive

static int startup_flag = BT_ERROR_NONE;
static GMainLoop *mainloop = NULL;
static int ret = BT_ERROR_NONE;
static bool callback_result = false;
static char adapter_name[128] = "dts_test";
static bool le_supported = false;
static bool bt_supported = false;
static bool oob_supported = false;
static bool le_50_supported = false;

static int adv_data_type = 3;
static int manufacturer_id = 117;
static char *manufacture = NULL;
static char manufacture_0[] = {0x0, 0x0, 0x0, 0x0};
static char manufacture_1[] = {0x01, 0x01, 0x01, 0x01};
static char manufacture_2[] = {0x02, 0x02, 0x02, 0x02};
static char manufacture_3[] = {0x03, 0x03, 0x03, 0x03};
static char service_data[] = {0x01, 0x02, 0x03};
static const char *time_svc_uuid_16 = "1805";
static const char *battery_svc_uuid_16 = "180f";
static const char *heart_rate_svc_uuid_16 = "180d";
static const char *lmmediate_alert_svc_uuid_16 = "1802";
static const char *ancs_uuid_128 = "7905F431-B5CE-4E99-A40F-4B1E122D00D0";
static int appearance = 192;  // 192 is generic watch

static void adapter_state_changed_cb_for_adapter_p(int result,
                        bt_adapter_state_e adapter_state,
                        void *user_data)
{
    if(user_data != NULL) {
        if(!strcmp((char *)user_data, "enable")) {
            if(BT_ADAPTER_ENABLED == adapter_state) {
                callback_result = true;
            }
        } else if(!strcmp((char *)user_data, "disable")) {
            if(BT_ADAPTER_DISABLED == adapter_state) {
                callback_result = true;
            }
        }
    }

    if (mainloop) {
        g_main_loop_quit(mainloop);
    }
}

static void adapter_name_changed_cb_for_adapter_p(char *device_name, void *user_data)
{
    if (user_data != NULL && !strcmp((char *)user_data, "set_name")) {
        if (!strcmp(device_name, adapter_name)) {
             callback_result = true;
        } else {
            fprintf(stderr,"device_name: %s \n", device_name);
            fprintf(stderr,"adapter_name: %s \n", adapter_name);
        }
    }

    if (mainloop) {
        g_main_loop_quit(mainloop);
    }
}

static void adapter_visibility_mode_changed_cb_for_adpater_p(int result,
                    bt_adapter_visibility_mode_e visibility_mode,
                    void *user_data)
{
    fprintf(stderr, "adapter_visibility_mode_changed_cb_for_adpater_p was called.\n");

    callback_result = true;

    if (mainloop) {
         g_main_loop_quit(mainloop);
    }
}

static gboolean timeout_func(gpointer data)
{
    g_main_loop_quit((GMainLoop *)data);
    return FALSE;
}

static void wait_for_async()
{
    int timeout_id = 0;
    mainloop = g_main_loop_new(NULL, FALSE);

    timeout_id = g_timeout_add(5000, timeout_func, mainloop);
    g_main_loop_run(mainloop);
    g_source_remove(timeout_id);
}


/**
 * @function            utc_bluetooth_adapter_positive_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_bluetooth_adapter_positive_startup(void)
{
    bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;
    startup_flag = BT_ERROR_NONE;

#ifdef TV
    bt_supported = true;
    le_supported = true;
#else
    bt_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

    le_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.le", &le_supported);

    oob_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.oob", &oob_supported);

    le_50_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.le.5_0", &le_50_supported);
#endif

    if(bt_supported) {
        ret = bt_initialize();
        if(BT_ERROR_NONE != ret) {
            fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
            fprintf(stderr, "bt_initialize failed (code: %d)\n", ret);
            startup_flag = ret;
            return;
        }

        callback_result = false;

        ret = bt_adapter_get_state(&adapter_state);
        if (adapter_state != BT_ADAPTER_ENABLED) {
                fprintf(stdout, "BT is not enabled!!");
                startup_flag = BT_ERROR_NOT_ENABLED;
        }
    }
}

/**
 * @function            utc_bluetooth_adapter_positive_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_bluetooth_adapter_positive_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_is_discovering_p
 * @since_tizen		2.3
 * @description		Does assert check for startup_flag before checking LE device discovery
 *					(is in progress or not) when le is supported otherwise just check for the
 *					LE device discovery status.
 * @scenario		Checks for the LE device discovery status; is in progress or not.
 */
int utc_bluetooth_bt_adapter_le_is_discovering_p(void)
{
	bool is_discovery = FALSE;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_is_discovering(&is_discovery);
		assert_eq(ret,BT_ERROR_NONE);
	} else {
		ret = bt_adapter_le_is_discovering(&is_discovery);
		assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_state_changed_cb_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then set the callback function to be invoked
 *					when Bluetooth adapter state changes if le is supported otherwise just set the
 *					callback.
 * @scenario		Registers a callback function to be invoked when the Bluetooth adapter state changes.
 */
int utc_bluetooth_bt_adapter_set_state_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_adapter_set_state_changed_cb(adapter_state_changed_cb_for_adapter_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_set_state_changed_cb(adapter_state_changed_cb_for_adapter_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_name_changed_cb_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then Registers a callback function to be
 *					invoked when the name of Bluetooth adapter changes; then unset the callback
 *					if le is supported otherwise just registers the callback function.
 * @scenario		Set a callback function to be invoked when the name of Bluetooth adapter changes.
 */
int utc_bluetooth_bt_adapter_set_name_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
    	ret = bt_adapter_set_name_changed_cb(adapter_name_changed_cb_for_adapter_p, NULL);
    	assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_unset_name_changed_cb();
        assert_eq(ret,BT_ERROR_NONE);
    } else {
    	ret = bt_adapter_set_name_changed_cb(adapter_name_changed_cb_for_adapter_p, NULL);
    	assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_name_changed_cb_p1
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then Registers a callback function to be
 *					invoked when the name of Bluetooth adapter changes if le is supported otherwise
 *					just registers the callback function.
 * @scenario		Set a callback function to be invoked when the name of Bluetooth adapter changes.
 */
int utc_bluetooth_bt_adapter_set_name_changed_cb_p1(void)
{
	if(bt_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

#if defined(MOBILE) || defined(TIZENIOT) 
		char name[128] = "test";
		snprintf(name, 128, "%s_1", adapter_name);
		strncpy(adapter_name, name, 128);
#endif
		ret = bt_adapter_set_name_changed_cb(adapter_name_changed_cb_for_adapter_p, "set_name");
		assert_eq(ret,BT_ERROR_NONE);
	} else {
		ret = bt_adapter_set_name_changed_cb(adapter_name_changed_cb_for_adapter_p, "set_name");
		assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_visibility_mode_changed_cb_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then Registers a callback function to be
 *					invoked when the visibility mode of Bluetooth adapter changes and unset the
 *					callback if le is supported otherwise just registers the callback function.
 * @scenario		Set a callback function to be invoked when visibility mode of Bluetooth adapter changes.
 */
int utc_bluetooth_bt_adapter_set_visibility_mode_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_visibility_mode_changed_cb(
        		adapter_visibility_mode_changed_cb_for_adpater_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_unset_visibility_mode_changed_cb();
        assert_eq(ret,BT_ERROR_NONE);
    } else {
        ret = bt_adapter_set_visibility_mode_changed_cb(
        		adapter_visibility_mode_changed_cb_for_adpater_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_visibility_mode_changed_cb_p1
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then Registers a callback function to be
 *					invoked when the visibility mode of Bluetooth adapter changes if le is supported
 *					otherwise just registers the callback function.
 * @scenario		Set a callback function to be invoked when visibility mode of Bluetooth adapter changes.
 */
int utc_bluetooth_bt_adapter_set_visibility_mode_changed_cb_p1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_adapter_set_visibility_mode_changed_cb(adapter_visibility_mode_changed_cb_for_adpater_p, NULL);
        assert_eq(ret,BT_ERROR_NONE);
    } else {
        ret = bt_adapter_set_visibility_mode_changed_cb(adapter_visibility_mode_changed_cb_for_adpater_p, NULL);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_state_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then get the current state of Adapter
 *					if le is supported otherwise just get the current state of Adapter.
 * @scenario		Call to get the current state of adapter.
 */
int utc_bluetooth_bt_adapter_get_state_p(void)
{
    bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_get_state(&adapter_state);
        assert_eq(ret,BT_ERROR_NONE);
    } else {
        ret = bt_adapter_get_state(&adapter_state);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_address_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then gets the address of local Bluetooth adapter
 *					if le is supported otherwise just gets the address of local Bluetooth adapter.
 * @scenario		Call to get the bluetooth address of local adapter.
 */
int utc_bluetooth_bt_adapter_get_address_p(void)
{
    char *address = NULL;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_get_address(&address);
        assert_eq(ret, BT_ERROR_NONE);

        free(address);
        address = NULL;
    } else {
        ret = bt_adapter_get_address(&address);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_name_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then gets the friendly name
 *					of local Bluetooth Adapter if le is supported otherwise just gets the
 *					name of local Bluetooth adapter.
 * @scenario		Call to get the friendly name associated with local adapter.
 */
int utc_bluetooth_bt_adapter_get_name_p(void)
{
    char *name = NULL;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_get_name(&name);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_get_name(&name);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_visibility_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then gets the visibility mode
 *					of local Bluetooth Adapter if le is supported otherwise just gets the
 *					the visibility mode of local Bluetooth adapter.
 * @scenario		Call to get the visibility mode of local bluetooth adapter.
 */
int utc_bluetooth_bt_adapter_get_visibility_p(void)
{
    int dur = 1;
    bt_adapter_visibility_mode_e mode = BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_get_visibility(&mode, &dur);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_get_visibility(&mode, &dur);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_name_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then sets the name of local Bluetooth adapter
 *					if le is supported otherwise just sets the name of local Bluetooth adapter.
 * @scenario		Call to set the friendly name for local bluetooth adapter.
 */
int utc_bluetooth_bt_adapter_set_name_p(void)
{
#if defined(MOBILE) || defined(TIZENIOT) 
	char name[128] = "";
#endif
	if(bt_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
#if defined(MOBILE) || defined(TIZENIOT) 
		snprintf(name, 128, "%s_1", adapter_name);
		strncpy(adapter_name, name, 128);
#endif
		ret = bt_adapter_set_name(adapter_name);
		assert_eq(ret,BT_ERROR_NONE);
	} else {
		ret = bt_adapter_set_name(adapter_name);
		assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
	}

	return 0;


}

 /**
 * @testcase		utc_bluetooth_bt_adapter_unset_state_changed_cb_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then register the adapter state change callback
 *					and unregister it if le is supported otherwise just unregister the callback.
 * @scenario		Call to unset the adapter's state changed callback.
 */
int utc_bluetooth_bt_adapter_unset_state_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_state_changed_cb(adapter_state_changed_cb_for_adapter_p, NULL);
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_unset_state_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_unset_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_unset_name_changed_cb_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then register the name changed callback
 *					and unregister it if le is supported otherwise just unregister the callback.
 * @scenario		Call to unset the adapter's name changed callback.
 */
int utc_bluetooth_bt_adapter_unset_name_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_name_changed_cb(adapter_name_changed_cb_for_adapter_p, NULL);
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_unset_name_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_unset_name_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_unset_visibility_mode_changed_cb_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag" then register the visibility mode changed callback
 *					and unregister it if le is supported otherwise just unregister the callback.
 * @scenario		Call to unset the adapter's visibility mode changed callback.
 */
int utc_bluetooth_bt_adapter_unset_visibility_mode_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_visibility_mode_changed_cb(adapter_visibility_mode_changed_cb_for_adpater_p, NULL);
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_unset_visibility_mode_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_unset_visibility_mode_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_local_oob_data_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag". Gets the Hash and Randmoizer value,
 *					synchronously when le is supported or not supported.
 * @scenario		Call to get the Hash and Randmoizer value, synchronously.
 */
int utc_bluetooth_bt_adapter_get_local_oob_data_p(void)
{
    assert_eq(startup_flag, BT_ERROR_NONE);

    unsigned char *hash = NULL;
    unsigned char *randomizer = NULL;
    int hash_len = 0;
    int randomizer_len = 0;

    if(bt_supported && oob_supported) {
        ret = bt_adapter_get_local_oob_data(&hash, &randomizer, &hash_len, &randomizer_len);

        free(hash);
        hash = NULL;

        free(randomizer);
        randomizer = NULL;

        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_get_local_oob_data(&hash, &randomizer, &hash_len, &randomizer_len);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_is_service_used_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag". Checks whether the UUID of service is
 *					used or not when le is supported or not supported.
 * @scenario		Call to check whether the UUID of service is used or not.
 */
int utc_bluetooth_bt_adapter_is_service_used_p(void)
{
    assert_eq(startup_flag, BT_ERROR_NONE);

    bool used = false;
    const char *service_uuid = "00001105-0000-1000-8000-00805f9b34fb";

    if(bt_supported) {
        ret = bt_adapter_is_service_used(service_uuid, &used);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_is_service_used(service_uuid, &used);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_clear_advertising_data_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence or respond to LE scanning reqeust then clear all data to be advertised
 *					or responded to scan request from LE scanning device and then destroy the advertiser
 *					if le is supported otherwise just create advertiser to advertise device's
 *					existence or respond to LE scanning reqeust.
 * @scenario		Call to clear all data to be advertised or responded to scan request from LE scanning device.
 */
int utc_bluetooth_bt_adapter_le_clear_advertising_data_p(void)
{
	bt_advertiser_h advertiser = NULL;

    if(le_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_adapter_le_create_advertiser(&advertiser);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_le_clear_advertising_data(advertiser, BT_ADAPTER_LE_PACKET_ADVERTISING);

        bt_adapter_le_destroy_advertiser(advertiser);

        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_le_create_advertiser(&advertiser);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

static void bt_adapter_vd_changed_cb(int duration, void *user_data)
{

}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_visibility_duration_changed_cb_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", registers a callback function to be invoked
 *					every second untill the visibility mode is changed and then unregister the callback
 *					if le is supported otherwise just registers the callback function.
 * @scenario		Call to set visibility duration changed callback for local adapter.
 */
int utc_bluetooth_bt_adapter_set_visibility_duration_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_visibility_duration_changed_cb(bt_adapter_vd_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        bt_adapter_unset_visibility_duration_changed_cb();
    } else {
        ret = bt_adapter_set_visibility_duration_changed_cb(bt_adapter_vd_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_create_advertiser_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence or respond to LE scanning reqeust then destroy the advertiser
 *					if le is supported otherwise just create the advertiser.
 * @scenario		Call to create advertiser to advertise device's existence for local adapter.
 */
int utc_bluetooth_bt_adapter_le_create_advertiser_p(void)
{
    bt_advertiser_h advertiser = NULL;

    if(le_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_le_create_advertiser(&advertiser);
        assert_eq(ret, BT_ERROR_NONE);

        bt_adapter_le_destroy_advertiser(advertiser);
    } else {
        ret = bt_adapter_le_create_advertiser(&advertiser);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_destroy_advertiser_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence or respond to LE scanning reqeust then destroy the advertiser
 *					if le is supported otherwise just destroy the advertiser.
 * @scenario		Call to destroy advertiser for local adapter.
 */
int utc_bluetooth_bt_adapter_le_destroy_advertiser_p(void)
{
    bt_advertiser_h second_advertiser = NULL;

    if(le_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_le_create_advertiser(&second_advertiser);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_le_destroy_advertiser(second_advertiser);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_le_destroy_advertiser(second_advertiser);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

static void __bt_adapter_le_advertising_state_changed_cb(int result,
								bt_advertiser_h advertiser,
								bt_adapter_le_advertising_state_e adv_state,
								void *user_data)
{

}

#if defined(MOBILE) || defined(TIZENIOT) 
 /**
 * @testcase		utc_bluetooth_bt_adapter_le_stop_advertising_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence or respond to LE scanning reqeust then start advertising then
 *					stop advertsing and then destroy the advertiser if le is supported otherwise
 *					just stop advertising.
 * @scenario		Call to stop advertising for the remote BLE scanning devices.
 */
int utc_bluetooth_bt_adapter_le_stop_advertising_p(void)
{
    bt_advertiser_h advertiser = NULL;

    if(le_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_adapter_le_create_advertiser(&advertiser);
        assert_eq(ret, BT_ERROR_NONE);

        /* add advertising data start */
        ret = bt_adapter_le_add_advertising_service_uuid(advertiser,
                                BT_ADAPTER_LE_PACKET_ADVERTISING, time_svc_uuid_16);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_le_add_advertising_service_uuid(advertiser,
                        BT_ADAPTER_LE_PACKET_ADVERTISING,  battery_svc_uuid_16);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_le_add_advertising_service_data(advertiser,
                        BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, time_svc_uuid_16,
                        service_data, sizeof(service_data));

        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_le_set_advertising_device_name(advertiser,
                        BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, true);

        assert_eq(ret, BT_ERROR_NONE);

        manufacture = manufacture_0;
        ret = bt_adapter_le_add_advertising_manufacturer_data(advertiser,
                        BT_ADAPTER_LE_PACKET_SCAN_RESPONSE,
                        manufacturer_id,
                        manufacture, sizeof(manufacture_0));

        assert_eq(ret, BT_ERROR_NONE);
        /* add advertising data end */

        ret = bt_adapter_le_start_advertising_new(advertiser,
				__bt_adapter_le_advertising_state_changed_cb, NULL);
        if (ret != BT_ERROR_NONE)
        	bt_adapter_le_destroy_advertiser(advertiser);

        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_le_stop_advertising(advertiser);
        if (ret != BT_ERROR_NONE)
        	bt_adapter_le_destroy_advertiser(advertiser);

        assert_eq(ret, BT_ERROR_NONE);

        bt_adapter_le_destroy_advertiser(advertiser);
    } else {
        ret = bt_adapter_le_stop_advertising(advertiser);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}
#endif

 /**
 * @testcase		utc_bluetooth_bt_adapter_unset_visibility_duration_changed_cb_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", set the visibility duration changed
 *					callback then unset the callback if le is supported otherwise
 *					just unset the visibility duration changed callback.
 * @scenario		Call to unregister visibility duration changed callback for local adapter.
 */
int utc_bluetooth_bt_adapter_unset_visibility_duration_changed_cb_p(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_visibility_duration_changed_cb(bt_adapter_vd_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_unset_visibility_duration_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_adapter_unset_visibility_duration_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

static void __bt_adapter_le_scan_result_cb(int result,
			bt_adapter_le_device_scan_result_info_s *info, void *user_data)
{

}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_start_scan_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", start scanning the advertising devices
 *					if le is supported otherwise just start scanning the advertising devices.
 *					Stop the scanning process.
 * @scenario		Call to start LE scan to find LE advertisement of remote advertising devices.
 */
int utc_bluetooth_bt_adapter_le_start_scan_p(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_start_scan(__bt_adapter_le_scan_result_cb, NULL);
		wait_for_async();

		assert_eq(ret, BT_ERROR_NONE);
		ret = bt_adapter_le_stop_scan();
	} else {
		ret = bt_adapter_le_start_scan(__bt_adapter_le_scan_result_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	if(ret == BT_ERROR_NONE)
		bt_adapter_le_stop_scan();

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_stop_scan_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", start scanning the advertising devices
 *					then stop scanning if le is supported otherwise just stop scanning.
 * @scenario		Call to stop LE scan.
 */
int utc_bluetooth_bt_adapter_le_stop_scan_p(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		bt_adapter_le_start_scan(__bt_adapter_le_scan_result_cb, NULL);
		wait_for_async();

		ret = bt_adapter_le_stop_scan();
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_adapter_le_stop_scan();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_add_advertising_service_uuid_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence then add a service UUID to advertise or scan response data (The maximum
 *					advertised or responded data size is 31 bytes including data type and system wide data)
 *					then clear the advertsing data and destroy the advertiser if le is supported otherwise
 *					just add a service UUID to advertise or scan response data and clear the adv data.
 * @scenario		Call to add a service UUID to advertise.
 */
int utc_bluetooth_bt_adapter_le_add_advertising_service_uuid_p(void)
{
	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_packet_type_e pkt_type = BT_ADAPTER_LE_PACKET_ADVERTISING;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_create_advertiser(&advertiser);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_add_advertising_service_uuid(advertiser,
						pkt_type, time_svc_uuid_16);
		assert_eq(ret, BT_ERROR_NONE);
		if(ret == BT_ERROR_NONE) {
			bt_adapter_le_clear_advertising_data(advertiser, pkt_type);
			bt_adapter_le_destroy_advertiser(advertiser);
		}
	} else {
		ret = bt_adapter_le_add_advertising_service_uuid(advertiser,
						pkt_type, time_svc_uuid_16);

		if(ret == BT_ERROR_NONE)
			bt_adapter_le_clear_advertising_data(advertiser, pkt_type);

		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_add_advertising_service_solicitation_uuid_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence then add a service solicitation UUID to advertise data (The maximum
 *					advertised or responded data size is 31 bytes including data type and system wide data)
 *					then clear the advertsing data and destroy the advertiser if le is supported otherwise
 *					add a service solicitation UUID to advertise data and clear the adv data.
 * @scenario		Call to add a service solicitation UUID to advertise.
 */
int utc_bluetooth_bt_adapter_le_add_advertising_service_solicitation_uuid_p(void)
{
	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_packet_type_e pkt_type = BT_ADAPTER_LE_PACKET_ADVERTISING;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_create_advertiser(&advertiser);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_add_advertising_service_solicitation_uuid(advertiser,
						pkt_type, heart_rate_svc_uuid_16);
		assert_eq(ret, BT_ERROR_NONE);
		if(ret == BT_ERROR_NONE) {
			bt_adapter_le_clear_advertising_data(advertiser, pkt_type);
			bt_adapter_le_destroy_advertiser(advertiser);
		}
	} else {
		ret = bt_adapter_le_add_advertising_service_solicitation_uuid(advertiser,
						pkt_type, heart_rate_svc_uuid_16);

		if(ret == BT_ERROR_NONE)
			bt_adapter_le_clear_advertising_data(advertiser, pkt_type);

		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_add_advertising_service_data_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence then add service data to advertise (The maximum
 *					advertised or responded data size is 31 bytes including data type and system wide data)
 *					then clear the advertsing data and destroy the advertiser if le is supported otherwise
 *					add service data to advertise and clear the advertising data.
 * @scenario		Call to add the service data to advertise.
 */
int utc_bluetooth_bt_adapter_le_add_advertising_service_data_p(void)
{
	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_packet_type_e pkt_type = BT_ADAPTER_LE_PACKET_SCAN_RESPONSE;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_create_advertiser(&advertiser);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_add_advertising_service_data(advertiser,
									pkt_type, time_svc_uuid_16,
									service_data, sizeof(service_data));
		assert_eq(ret, BT_ERROR_NONE);
		if(ret == BT_ERROR_NONE) {
			bt_adapter_le_clear_advertising_data(advertiser, pkt_type);
			bt_adapter_le_destroy_advertiser(advertiser);
		}
	} else {
		ret = bt_adapter_le_add_advertising_service_data(advertiser,
								pkt_type, time_svc_uuid_16,
								service_data, sizeof(service_data));
		if(ret == BT_ERROR_NONE)
			bt_adapter_le_clear_advertising_data(advertiser, pkt_type);

		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_advertising_appearance_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence then sets the external appearance of local device to advertise
 *					then clear the advertsing data and destroy the advertiser if le is supported otherwise
 *					sets the external appearance of local device to advertise and clear the advertising data.
 * @scenario		Call to add the external appearance of local device to advertise.
 */
int utc_bluetooth_bt_adapter_le_set_advertising_appearance_p(void)
{
	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_packet_type_e pkt_type = BT_ADAPTER_LE_PACKET_SCAN_RESPONSE;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_create_advertiser(&advertiser);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_appearance(advertiser,
									pkt_type, 4);
		assert_eq(ret, BT_ERROR_NONE);
		if(ret == BT_ERROR_NONE) {
			bt_adapter_le_clear_advertising_data(advertiser, pkt_type);
			bt_adapter_le_destroy_advertiser(advertiser);
		}
	} else {
		ret = bt_adapter_le_set_advertising_appearance(advertiser,
								pkt_type, 4);
		if(ret == BT_ERROR_NONE)
			bt_adapter_le_clear_advertising_data(advertiser, pkt_type);

		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_add_advertising_manufacturer_data_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence then add manufacturer specific data to advertise
 *					then clear the advertsing data and destroy the advertiser if le is supported otherwise
 *					just add manufacturer specific data to advertise and clear the advertising data.
 * @scenario		Call to add manufacturer specific data to advertise.
 */
int utc_bluetooth_bt_adapter_le_add_advertising_manufacturer_data_p(void)
{
	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_packet_type_e pkt_type = BT_ADAPTER_LE_PACKET_SCAN_RESPONSE;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		bt_adapter_le_create_advertiser(&advertiser);
		manufacture = manufacture_3;
		ret = bt_adapter_le_add_advertising_manufacturer_data(advertiser,
								pkt_type,
								manufacturer_id,
								manufacture, sizeof(manufacture_0));
		assert_eq(ret, BT_ERROR_NONE);
		if(ret == BT_ERROR_NONE) {
			bt_adapter_le_clear_advertising_data(advertiser, pkt_type);
			bt_adapter_le_destroy_advertiser(advertiser);
		}
		manufacture = NULL;
	} else {
		ret = bt_adapter_le_add_advertising_manufacturer_data(advertiser,
							pkt_type,
							manufacturer_id,
							manufacture, sizeof(manufacture_0));
		if(ret == BT_ERROR_NONE)
			bt_adapter_le_clear_advertising_data(advertiser, pkt_type);

		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_advertising_device_name_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence then add local device name to advertise (The maximum advertised
 *					or responded data size is 31 bytes including data type and system wide data)
 *					and then destroy the advertiser if le is supported otherwise
 *					just add add device name to advertising data.
 * @scenario		Call to add device advertise name to advertise.
 */
int utc_bluetooth_bt_adapter_le_set_advertising_device_name_p(void)
{
	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_packet_type_e pkt_type = BT_ADAPTER_LE_PACKET_SCAN_RESPONSE;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_create_advertiser(&advertiser);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_device_name(advertiser, pkt_type, true);
		assert_eq(ret, BT_ERROR_NONE);
		if(ret == BT_ERROR_NONE)
			bt_adapter_le_destroy_advertiser(advertiser);
	} else {
		ret = bt_adapter_le_set_advertising_device_name(advertiser, pkt_type, true);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_advertising_tx_power_level_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence then add transmission power level to advertise then destroy the advertiser
 *					if le is supported otherwise just add transmission power level to advertsing data.
 * @scenario		Call to add transmission power level to advertise.
 */
int utc_bluetooth_bt_adapter_le_set_advertising_tx_power_level_p(void)
{
	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_packet_type_e pkt_type = BT_ADAPTER_LE_PACKET_ADVERTISING;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_create_advertiser(&advertiser);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_tx_power_level(advertiser,
				pkt_type, true);
		assert_eq(ret, BT_ERROR_NONE);
		if(ret == BT_ERROR_NONE)
			bt_adapter_le_destroy_advertiser(advertiser);
	} else {
		ret = bt_adapter_le_set_advertising_tx_power_level(advertiser, pkt_type, true);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_start_advertising_new_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence then start advertising with passed advertiser and advertising parameters
 *					then destroy the advertiser if le is supported otherwise just Start and stop advertising.
 * @scenario		Call to start advertising with passed advertiser and advertising parameters.
 */
int utc_bluetooth_bt_adapter_le_start_advertising_new_p(void)
{
	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_advertising_state_changed_cb cb;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		bt_adapter_le_create_advertiser(&advertiser);

		cb = __bt_adapter_le_advertising_state_changed_cb;

		/* add advertising data start*/
		ret = bt_adapter_le_add_advertising_service_uuid(advertiser,
								BT_ADAPTER_LE_PACKET_ADVERTISING, time_svc_uuid_16);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_add_advertising_service_uuid(advertiser,
						BT_ADAPTER_LE_PACKET_ADVERTISING,  battery_svc_uuid_16);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_add_advertising_service_data(advertiser,
						BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, time_svc_uuid_16,
						service_data, sizeof(service_data));

		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_device_name(advertiser,
						BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, true);

		assert_eq(ret, BT_ERROR_NONE);

		manufacture = manufacture_0;
		ret = bt_adapter_le_add_advertising_manufacturer_data(advertiser,
						BT_ADAPTER_LE_PACKET_SCAN_RESPONSE,
						manufacturer_id,
						manufacture, sizeof(manufacture_0));

		assert_eq(ret, BT_ERROR_NONE);
		 /* add advertising data end */

		ret = bt_adapter_le_start_advertising_new(advertiser, cb, NULL);
		wait_for_async();
		assert_eq(ret, BT_ERROR_NONE);

		if(ret == BT_ERROR_NONE)
			bt_adapter_le_destroy_advertiser(advertiser);
	} else {
		cb = __bt_adapter_le_advertising_state_changed_cb;
		ret = bt_adapter_le_start_advertising_new(advertiser, cb, NULL);

		if(ret == BT_ERROR_NONE)
			bt_adapter_le_stop_advertising(advertiser);

		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_advertising_mode_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence then set advertising mode to control the advertising power and latency
 *					then destroy the advertiser if le is supported otherwise just Set advertising mode
 *					to control the advertising power and latency.
 * @scenario		Call to set advertising mode to control the advertising power and latency.
 */
int utc_bluetooth_bt_adapter_le_set_advertising_mode_p(void)
{
	bt_advertiser_h advertiser = NULL;
	int mode = BT_ADAPTER_LE_ADVERTISING_MODE_BALANCED;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_create_advertiser(&advertiser);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_mode(advertiser, mode);
		assert_eq(ret, BT_ERROR_NONE);

		if(ret == BT_ERROR_NONE)
			bt_adapter_le_destroy_advertiser(advertiser);
	} else {
		ret = bt_adapter_le_set_advertising_mode(advertiser, mode);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_advertising_connectable_p
 * @since_tizen		2.3
 * @description		Does assert check for "startup_flag", create advertiser to advertise device's
 *					existence then set whether the advertising type should be connectable or non-connectable
 *					then destroy the advertiser if le is supported otherwise just set whether the advertising
 *					type should be connectable or non-connectable.
 * @scenario		Call to set whether the advertising type should be connectable or non-connectable.
 */
int utc_bluetooth_bt_adapter_le_set_advertising_connectable_p(void)
{
	bt_advertiser_h advertiser = NULL;
	int type = 0x00;

	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_create_advertiser(&advertiser);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_connectable(advertiser, type);
		assert_eq(ret, BT_ERROR_NONE);
		if(ret == BT_ERROR_NONE)
			bt_adapter_le_destroy_advertiser(advertiser);
	} else {
		ret = bt_adapter_le_set_advertising_connectable(advertiser, type);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		 utc_bluetooth_bt_get_uuid_name_p
 * @since_tizen 3.0
 * @description	Does assert check for "startup_flag" then gets the uuid name if bt is supported
 *				otherwise just gets the uuid name.
 * @scenario		Call to get the uuid name.
 */
int utc_bluetooth_bt_get_uuid_name_p(void)
{
	char *uuid = NULL;
	char *name = NULL;

	uuid = g_strdup("00001101-0000-1000-8000-00805F9B7777");

	if (bt_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_get_uuid_name(uuid, &name);
		g_free(uuid);
		g_free(name);
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_get_uuid_name(uuid, &name);
		g_free(uuid);
		g_free(name);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		 utc_bluetooth_bt_adapter_le_set_scan_mode_p
 * @since_tizen 3.0
 * @description	Does assert check for "startup_flag" then set the scan mode if bt is supported
 *				otherwise just sets the scan mode.
 * @scenario		Call to set the scan mode.
 */
int utc_bluetooth_bt_adapter_le_set_scan_mode_p(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_le_set_scan_mode(BT_ADAPTER_LE_SCAN_MODE_BALANCED);
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_adapter_le_set_scan_mode(BT_ADAPTER_LE_SCAN_MODE_BALANCED);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		 utc_bluetooth_bt_adapter_get_local_oob_ext_data_p
 * @since_tizen 3.0
 * @description	Does assert check for "startup_flag" then gets the uuid name if bt is supported
 *				otherwise just gets the uuid name.
 * @scenario		Call to get the uuid name.
 */
int utc_bluetooth_bt_adapter_get_local_oob_ext_data_p(void)
{
	unsigned char *data[4];
	int len[4];
	int i;

	if (bt_supported && oob_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_get_local_oob_ext_data(
						&data[0], &data[1], &len[0], &len[1],
						&data[2], &data[3], &len[2], &len[3]);

		if (ret == BT_ERROR_NONE) {
			for (i = 0; i < 4; i++)
				g_free(data[i]);
		}

		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_adapter_get_local_oob_ext_data(
						&data[0], &data[1], &len[0], &len[1],
						&data[2], &data[3], &len[2], &len[3]);

		if (ret == BT_ERROR_NONE) {
			for (i = 0; i < 4; i++)
				g_free(data[i]);
		}

		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_type_p(void)
{
	bt_scan_filter_h scan_filter = NULL;
	int result = BT_ERROR_NONE;

    if (le_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		result = bt_adapter_le_scan_filter_create(&scan_filter);

        result = bt_adapter_le_scan_filter_set_type(scan_filter,
						BT_ADAPTER_LE_SCAN_FILTER_TYPE_IBEACON);

		result = bt_adapter_le_scan_filter_destroy(scan_filter);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        result = bt_adapter_le_scan_filter_set_type(scan_filter,
						BT_ADAPTER_LE_SCAN_FILTER_TYPE_IBEACON);
        assert_eq(result, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

static bt_adapter_le_device_scan_result_info_s* __bt_create_le_device_scan_info_s(void)
{
	bt_adapter_le_device_scan_result_info_s *scan_info = NULL;

	scan_info = (bt_adapter_le_device_scan_result_info_s *)malloc(sizeof(bt_adapter_le_device_scan_result_info_s));
	if (scan_info == NULL)
		return NULL;

	memset(scan_info, 0x00, sizeof(bt_adapter_le_device_scan_result_info_s));

	scan_info->remote_address = g_strdup("00:1B:66:01:23:1C");
	scan_info->address_type = BT_DEVICE_PUBLIC_ADDRESS;
	scan_info->rssi = -31;
	scan_info->adv_data_len = 31;
	scan_info->adv_data = malloc(scan_info->adv_data_len);
	if (scan_info->adv_data) {

		scan_info->adv_data[0] = 28;
		scan_info->adv_data[1] = 0xff;

		/* Company ID 0x004C */
		scan_info->adv_data[2] = 0x4c;
		scan_info->adv_data[3] = 0x00;

		/* UUID */
		scan_info->adv_data[4] = 0x01;
		scan_info->adv_data[5] = 0x01;
		scan_info->adv_data[6] = 0x01;
		scan_info->adv_data[7] = 0x01;
		scan_info->adv_data[8] = 0x01;
		scan_info->adv_data[9] = 0x01;
		scan_info->adv_data[10] = 0x01;
		scan_info->adv_data[11] = 0x01;
		scan_info->adv_data[12] = 0x01;
		scan_info->adv_data[13] = 0x01;
		scan_info->adv_data[14] = 0x01;
		scan_info->adv_data[15] = 0x01;
		scan_info->adv_data[16] = 0x01;
		scan_info->adv_data[17] = 0x01;
		scan_info->adv_data[18] = 0x01;
		scan_info->adv_data[19] = 0x01;

		/* Major ID */
		scan_info->adv_data[20] = 0x02;
		scan_info->adv_data[21] = 0x01;

		/* Minor ID */
		scan_info->adv_data[22] = 0x02;
		scan_info->adv_data[23] = 0x01;

		/* Power */
		scan_info->adv_data[24] = -31;
	}

	return scan_info;
}

static void __bt_free_le_device_scan_info_s(bt_adapter_le_device_scan_result_info_s *scan_info)
{
	if (scan_info == NULL)
		return;

	if (scan_info->remote_address != NULL)
		free(scan_info->remote_address);

	if (scan_info->adv_data != NULL)
		free(scan_info->adv_data);

	free(scan_info);
	scan_info = NULL;
}

int utc_bluetooth_bt_adapter_le_get_scan_result_ibeacon_report_p(void)
{
	bt_adapter_le_device_scan_result_info_s *info = NULL;
	bt_adapter_le_ibeacon_scan_result_info_s *ibeacon_info = NULL;
	int result = BT_ERROR_NONE;

    if (le_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

	info = __bt_create_le_device_scan_info_s();

        result = bt_adapter_le_get_scan_result_ibeacon_report(info,
									BT_ADAPTER_LE_PACKET_ADVERTISING,
									&ibeacon_info);

		__bt_free_le_device_scan_info_s(info);
		result = bt_adapter_le_free_ibeacon_report(ibeacon_info);
        assert_eq(result, BT_ERROR_NONE);
    } else {
        result = bt_adapter_le_get_scan_result_ibeacon_report(info,
									BT_ADAPTER_LE_PACKET_ADVERTISING,
									&ibeacon_info);
        assert_eq(result, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

int utc_bluetooth_bt_adapter_le_free_ibeacon_report_p(void)
{
	bt_adapter_le_device_scan_result_info_s *info = NULL;
	bt_adapter_le_ibeacon_scan_result_info_s *ibeacon_info = NULL;
	int result = BT_ERROR_NONE;

    if (le_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		info = __bt_create_le_device_scan_info_s();

        result = bt_adapter_le_get_scan_result_ibeacon_report(info,
									BT_ADAPTER_LE_PACKET_ADVERTISING,
									&ibeacon_info);

		__bt_free_le_device_scan_info_s(info);
		result = bt_adapter_le_free_ibeacon_report(ibeacon_info);
        assert_eq(result, BT_ERROR_NONE);
    } else {
        result = bt_adapter_le_free_ibeacon_report(ibeacon_info);
        assert_eq(result, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

int utc_bluetooth_bt_adapter_le_is_2m_phy_supported_p(void)
{
    bool is_supported = false;

    if(le_50_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_le_is_2m_phy_supported(&is_supported);
        assert_eq(ret,BT_ERROR_NONE);
    } else {
        ret = bt_adapter_le_is_2m_phy_supported(&is_supported);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

int utc_bluetooth_bt_adapter_le_is_coded_phy_supported_p(void)
{
    bool is_supported = false;

    if(le_50_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_le_is_coded_phy_supported(&is_supported);
        assert_eq(ret,BT_ERROR_NONE);
    } else {
        ret = bt_adapter_le_is_coded_phy_supported(&is_supported);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

