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

//& set: BluetoothAdapterNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool le_supported = false;
static bool bt_supported = false;
static bool oob_supported = false;
static bool le_50_supported = false;


/**
 * @function            utc_bluetooth_adapter_negative_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_bluetooth_adapter_negative_startup(void)
{
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
    }
}

/**
 * @function            utc_bluetooth_adapter_negative_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_bluetooth_adapter_negative_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

 /**
 * @testcase		utc_bluetooth_bt_deinitialize_n
 * @since_tizen		2.3
 * @description		Call to de-initialize Bluetooth and related resources twice if BT is supported
 *					otherwise just call to de-initialize Bluetooth once. check the "ret" flag with BT_ERROR_NOT_INITIALIZED
 *					if BT is already supported otherwise check with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to de-Initialize Bluetooth and to release related resources.
 */
int utc_bluetooth_bt_deinitialize_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_is_discovering_n
 * @since_tizen		2.3
 * @description		Call to check whether LE device discovery is in progress or not. check the "ret" flag with
 *					BT_ERROR_INVALID_PARAMETER if LE is supported otherwise check with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to check whether LE device discovery is in progress.
 */
int utc_bluetooth_bt_adapter_le_is_discovering_n(void)
{
    if(le_supported) {
       assert_eq(startup_flag, BT_ERROR_NONE);
       ret = bt_adapter_le_is_discovering(NULL);
       assert_eq(ret,BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_le_is_discovering(NULL);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }

       return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_state_changed_cb_n
 * @since_tizen		2.3
 * @description		Call to register callback as "NULL"; to be invoked when bluetooth adapter's state changes and check the "ret"
 *					flag with BT_ERROR_INVALID_PARAMETER if LE is supported otherwise just call to register the adapter's state
 *					change callback as "NULL" and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set bluetooth adapter's state change callback with "NULL".
 */
int utc_bluetooth_bt_adapter_set_state_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_state_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_set_state_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_state_changed_cb_n1
 * @since_tizen		2.3
 * @description		Call to register callback as "NULL"; to be invoked when bluetooth adapter's state
 *					changes after de-initializing Bluetooth and check the "ret" flag with BT_ERROR_NOT_INITIALIZED
 *					if LE is supported otherwise just call to register the callback with "NULL" and check the "ret" flag
 *					with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set bluetooth adapter's state change callback with "NULL" after deinitializng Bluetooth.
 */
int utc_bluetooth_bt_adapter_set_state_changed_cb_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_set_state_changed_cb(NULL, NULL);
        assert_eq(ret,BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_set_state_changed_cb(NULL, NULL);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_name_changed_cb_n
 * @since_tizen		2.3
 * @description		Call to set local bluetooth adapter's friendly name changed callback as "NULL"
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise
 *					just set the callback with "NULL" and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set bluetooth adapter's friendly name with "NULL".
 */
int utc_bluetooth_bt_adapter_set_name_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_name_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_set_name_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_name_changed_cb_n1
 * @since_tizen		2.3
 * @description		Call to set local bluetooth adapter's friendly name changed callback as "NULL" after de-initializing
 *					Bluetooth and check the "ret" flag with BT_ERROR_NOT_INITIALIZED if le is supported otherwise
 *					just set the callback with "NULL" and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set bluetooth adapter's friendly name with "NULL" after de-initializing BT(if supported).
 */
int utc_bluetooth_bt_adapter_set_name_changed_cb_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_set_name_changed_cb(NULL, NULL);
        assert_eq(ret,BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_set_name_changed_cb(NULL, NULL);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_visibility_mode_changed_cb_n
 * @since_tizen		2.3
 * @description		Call to set local bluetooth adapter's visibility mode changed callback as "NULL" and
 *					check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise
 *					just set the callback with "NULL" and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set bluetooth adapter's visibility mode changed callback with "NULL".
 */
int utc_bluetooth_bt_adapter_set_visibility_mode_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_visibility_mode_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_set_visibility_mode_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_visibility_mode_changed_cb_n1
 * @since_tizen		2.3
 * @description		Call to set local bluetooth adapter's visibility mode changed callback as "NULL" after de-initializing
 *					bluetooth and check the "ret" flag with BT_ERROR_NOT_INITIALIZED if le is supported otherwise
 *					just set the callback with "NULL" and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set bluetooth adapter's visibility mode changed callback with "NULL" after de-initializing BT.
 */
int utc_bluetooth_bt_adapter_set_visibility_mode_changed_cb_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_set_visibility_mode_changed_cb(NULL, NULL);
        assert_eq(ret,BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_set_visibility_mode_changed_cb(NULL, NULL);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_state_n
 * @since_tizen		2.3
 * @description		Call to get local bluetooth adapter's current state and check the "ret" flag
 *					with BT_ERROR_INVALID_PARAMETER if le is supported otherwise call to get
 *					local bluetooth adapter's current state and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get current state of local Bluetooth adapter.
 */
int utc_bluetooth_bt_adapter_get_state_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_get_state(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_get_state(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_state_n1
 * @since_tizen		2.3
 * @description		Call to get local bluetooth adapter's current state after de-initializing Bluetooth and check the "ret" flag
 *					with BT_ERROR_NOT_INITIALIZED if le is supported otherwise call to get
 *					local bluetooth adapter's current state and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get current state of local Bluetooth adapter after de-initializing Bluetooth.
 */
int utc_bluetooth_bt_adapter_get_state_n1(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_get_state(NULL);
        assert_eq(ret,BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_get_state(NULL);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_address_n
 * @since_tizen		2.3
 * @description		Call to get local bluetooth adapter's address and check the "ret" flag with
 *					BT_ERROR_INVALID_PARAMETER	if le is supported otherwise call to get the adapter's address
 *					and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get local Bluetooth adapter's address.
 */
int utc_bluetooth_bt_adapter_get_address_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_get_address(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_get_address(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_address_n1
 * @since_tizen		2.3
 * @description		Call to get local bluetooth adapter's address after de-initializing Bluetooth and check the "ret" flag with
 *					BT_ERROR_NOT_INITIALIZED if le is supported otherwise just call to get the adapter's address
 *					and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get local Bluetooth adapter's address after de-initializing Bluetooth.
 */
int utc_bluetooth_bt_adapter_get_address_n1(void)
{
    char *address = NULL;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_get_address(&address);
        assert_eq(ret,BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_get_address(&address);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_name_n
 * @since_tizen		2.3
 * @description		Call to get local bluetooth adapter's friendly name associated with and check the "ret" flag with
 *					BT_ERROR_INVALID_PARAMETER if le is supported otherwise just call to get the adapter's friendly name
 *					and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get local Bluetooth adapter's friendly name.
 */
int utc_bluetooth_bt_adapter_get_name_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_get_name(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_get_name(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_name_n1
 * @since_tizen		2.3
 * @description		Call to get local bluetooth adapter's friendly name associated with after de-initializing Bluetooth
 *					and check the "ret" flag with	BT_ERROR_NOT_INITIALIZED if le is supported otherwise just call
 *					to get the adapter's friendly name and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get local Bluetooth adapter's friendly name after de-initializing Bluetooth.
 */
int utc_bluetooth_bt_adapter_get_name_n1(void)
{
    char *name = NULL;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_get_name(&name);
        assert_eq(ret,BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_get_name(&name);
        assert_eq(ret,BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_visibility_n
 * @since_tizen		2.3
 * @description		Call to get local Bluetooth adapter's current visibility mode and check the "ret" flag
 *					with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just call to get the
 *					adapter's current visibility mode and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get local Bluetooth adapter's current visibility mode.
 */
int utc_bluetooth_bt_adapter_get_visibility_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_get_visibility(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_get_visibility(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_visibility_n1
 * @since_tizen		2.3
 * @description		Call to get local Bluetooth adapter's current visibility mode after de-initializing Bluetooth and
 *					check the "ret" flag with BT_ERROR_NOT_INITIALIZED if le is supported otherwise just call to get the
 *					adapter's current visibility mode and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get local Bluetooth adapter's current visibility mode after de-initializing Bluetooth.
 */
int utc_bluetooth_bt_adapter_get_visibility_n1(void)
{
    int dur = 10;
    bt_adapter_visibility_mode_e mode =
        BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE;

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_get_visibility(&mode, &dur);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_get_visibility(&mode, &dur);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_name_n
 * @since_tizen		2.3
 * @description		Call to set local bluetooth adapter's friendly name with "NULL" and check the "ret" flag with
 *					BT_ERROR_INVALID_PARAMETER if le is supported otherwise just call to set local bluetooth adapter's
 *					friendly name with "NULL" and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set local bluetooth adapter's friendly name with "NULL".
 */
int utc_bluetooth_bt_adapter_set_name_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_name(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_set_name(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_name_n1
 * @since_tizen		2.3
 * @description		Call to set local bluetooth adapter's friendly name with "NULL" after de-initializing bluetooth and check
 *					the "ret" flag with BT_ERROR_NOT_INITIALIZED if le is supported otherwise just call to set local
 *					bluetooth adapter's friendly name with "NULL" and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set local bluetooth adapter's friendly name with "NULL" after de-initializing bluetooth.
 */
int utc_bluetooth_bt_adapter_set_name_n1(void)
{
    char *name = "Test name";

    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_set_name(name);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_set_name(name);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_unset_state_changed_cb_n
 * @since_tizen		2.3
 * @description		Call to unset local bluetooth adapter's state changed callback and check the "ret" flag with
 *					BT_ERROR_NOT_INITIALIZED if le is supported otherwise just unset local bluetooth adapter's
 *					state changed callback and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to unset local bluetooth adapter's state change callback.
 */
int utc_bluetooth_bt_adapter_unset_state_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_unset_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_unset_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_unset_name_changed_cb_n
 * @since_tizen		2.3
 * @description		Call to unset local bluetooth adapter's name changed callback after de-initializing Bluetooth and
 *					check the "ret" flag with BT_ERROR_NOT_INITIALIZED if le is supported otherwise just call to unset local
 *					bluetooth adapter's name changed callback and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to unset local bluetooth adapter's name change callback after de-initializing Bluetooth.
 */
int utc_bluetooth_bt_adapter_unset_name_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_unset_name_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_unset_name_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_unset_visibility_mode_changed_cb_n
 * @since_tizen		2.3
 * @description		Call to unset local bluetooth adapter's visibility mode changed callback after de-initializing Bluetooth and
 *					check the "ret" flag with BT_ERROR_NOT_INITIALIZED if le is supported otherwise just call to unset local
 *					bluetooth adapter's visibility mode changed callback and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to unset local bluetooth adapter's visibility changed callback after de-initializing Bluetooth.
 */
int utc_bluetooth_bt_adapter_unset_visibility_mode_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_adapter_unset_visibility_mode_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_unset_visibility_mode_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_local_oob_data_n
 * @since_tizen		2.3
 * @description		Call to get the Hash and Randmoizer value, synchronously by setting out param as "NULL" and
 *					check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just call to
 *					get the Hash and Randmoizer value, synchronously by setting out param as "NULL" and check the
 *					"ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get the Hash and Randmoizer value, synchronously by setting out param as "NULL".
 */
int utc_bluetooth_bt_adapter_get_local_oob_data_n(void)
{
    if(bt_supported && oob_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_get_local_oob_data(NULL, NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_get_local_oob_data(NULL, NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;

}

 /**
 * @testcase		utc_bluetooth_bt_adapter_is_service_used_n
 * @since_tizen		2.3
 * @description		Call to check whether the UUID of service is used or not setting service_uuid as "NULL" and check the "ret"
 *					flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just call to check whether the
 *					UUID of service is used by setting service_uuid as "NULL" check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to check whether the UUID of service is used by setting the service_uuid as "NULL".
 */
int utc_bluetooth_bt_adapter_is_service_used_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_is_service_used(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_is_service_used(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_visibility_duration_changed_cb_n
 * @since_tizen		2.3
 * @description		Call to set visibility duration changed callback as "NULL" and check the "ret" flag with
 *					BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to set visibility duration
 *					changed callback as "NULL" and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set visibility duration changed callback as "NULL".
 */
int utc_bluetooth_bt_adapter_set_visibility_duration_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_visibility_duration_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_set_visibility_duration_changed_cb(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_create_advertiser_n
 * @since_tizen		2.3
 * @description		Call to create advertiser to advertise device's existence after de-initializing Bluetooth and
 *					check the "ret" flag with BT_ERROR_NOT_INITIALIZED if le is supported otherwise just try
 *					to create advertiser to advertise device's existence and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to create advertiser to advertise device's existence or respond to LE scanning reqeust.
 */
int utc_bluetooth_bt_adapter_le_create_advertiser_n(void)
{
    bt_advertiser_h advertiser = NULL;

    if(le_supported) {

        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_le_create_advertiser(&advertiser);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_le_create_advertiser(&advertiser);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_destroy_advertiser_n
 * @since_tizen		2.3
 * @description		Call to destroy advertiser after de-initializing Bluetooth after de-initializing bluetooth and
 *					check the "ret" flag with BT_ERROR_NOT_INITIALIZED if le is supported otherwise just try
 *					to destroy advertiser and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to destroy advertiser.
 */
int utc_bluetooth_bt_adapter_le_destroy_advertiser_n(void)
{
    bt_advertiser_h advertiser = NULL;

    if(le_supported) {

        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_le_destroy_advertiser(&advertiser);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_le_destroy_advertiser(&advertiser);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_stop_advertising_n
 * @since_tizen		2.3
 * @description		Call to to stop advertising after de-initializing bluetooth and check the "ret" flag with
 *					BT_ERROR_NOT_INITIALIZED if le is supported otherwise just try to stop advertising
 *					and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to stop advertising after de-initializing Bluetooth.
 */
int utc_bluetooth_bt_adapter_le_stop_advertising_n(void)
{
    bt_advertiser_h advertiser = NULL;

    if(le_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_le_stop_advertising(advertiser);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_le_stop_advertising(advertiser);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_clear_advertising_data_n
 * @since_tizen		2.3
 * @description		Call to clear all data to be advertised or responded to scan request from LE scanning device after
 *					de-initializing bluetooth and check the "ret" flag with BT_ERROR_NOT_INITIALIZED if le is supported
 *					otherwise just try clear the advertising data and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to clear all advertising data after de-initializing Bluetooth.
 */
int utc_bluetooth_bt_adapter_le_clear_advertising_data_n(void)
{
    bt_advertiser_h advertiser = NULL;

    if(le_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_le_clear_advertising_data(advertiser, BT_ADAPTER_LE_PACKET_ADVERTISING);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_le_clear_advertising_data(advertiser, BT_ADAPTER_LE_PACKET_ADVERTISING);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

static void bt_adapter_vd_changed_cb(int duration, void *user_data)
{

}

 /**
 * @testcase		utc_bluetooth_bt_adapter_unset_visibility_duration_changed_cb_n
 * @since_tizen		2.3
 * @description		Call to unset visibility duration changed callback after setting the callback and de-initializing bluetooth
 *					and then check the "ret" flag with BT_ERROR_NOT_INITIALIZED if le is supported
 *					otherwise just try to unsetthe callback and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to unset the visibility duration changed callback after de-initializing Bluetooth.
 */
int utc_bluetooth_bt_adapter_unset_visibility_duration_changed_cb_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_visibility_duration_changed_cb(bt_adapter_vd_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_adapter_unset_visibility_duration_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_adapter_unset_visibility_duration_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_bonded_device_info_n
 * @since_tizen		2.3
 * @description		Call to get device information of a bonded device with "NULL" params and check the "ret" flag
 *					with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to get the device info with "NULL"
 *					and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get device information of a bonded device by setting the input device info param as "NULL".
 */
int utc_bluetooth_bt_adapter_get_bonded_device_info_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_get_bonded_device_info(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_get_bonded_device_info(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }
	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_free_device_info_n
 * @since_tizen		2.3
 * @description		Call to free device information by setting the device info param as "NULL" and check the "ret" flag
 *					with BT_ERROR_INVALID_PARAMETER if le	is supported otherwise just try to free device information
 *					by setting the device info param as "NULL" and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to free device information with "NULL" parameter.
 */
int utc_bluetooth_bt_adapter_free_device_info_n(void)
{
    if(bt_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_free_device_info(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_free_device_info(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_remote_oob_data_n
 * @since_tizen		2.3
 * @description		Call to set the Hash and Randmoizer value, synchronously by setting the input parameters "NULL"
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le	is supported otherwise just try
 *					set the value with "NULL" parameters and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set the Hash and Randmoizer value, synchronously with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_set_remote_oob_data_n(void)
{
    if(bt_supported && oob_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_set_remote_oob_data(NULL, NULL, NULL, 0,0);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_set_remote_oob_data(NULL, NULL, NULL, 0,0);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_remove_remote_oob_data_n
 * @since_tizen		2.3
 * @description		Call to delete the Hash and Randmoizer value, synchronously by setting the input parameter "NULL"
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le	is supported otherwise just try
 *					to delete the value with "NULL" parameter and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to delete the Hash and Randmoizer value, synchronously with "NULL" parameter.
 */
int utc_bluetooth_bt_adapter_remove_remote_oob_data_n(void)
{
    if(bt_supported && oob_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_adapter_remove_remote_oob_data(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_adapter_remove_remote_oob_data(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_start_scan_n
 * @since_tizen		2.3
 * @description		Call to start scanning to find LE advertisement with "NULL" parameters and check the "ret" flag
 *					with BT_ERROR_INVALID_PARAMETER if le	is supported otherwise just try to start scanning with
 *					"NULL" parameters and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to start scanning with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_start_scan_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_start_scan(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_start_scan(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_stop_scan_n
 * @since_tizen		2.3
 * @description		Call to stop scanning after de-initializing Bluetooth and check the "ret" flag
 *					with BT_ERROR_NOT_INITIALIZED if le is supported otherwise just try to stop scanning
 *					and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to stop scanning.
 */
int utc_bluetooth_bt_adapter_le_stop_scan_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_stop_scan();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_adapter_le_stop_scan();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_get_scan_result_service_uuids_n
 * @since_tizen		2.3
 * @description		Call to get the service UUID list from the scan result information with "NULL" parameters
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise
 *					just try to get the service UUID list from the scan result with "NULL" parameters and check the
 *					"ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get the service UUID list from the scan result information with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_get_scan_result_service_uuids_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_get_scan_result_service_uuids(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_get_scan_result_service_uuids(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_get_scan_result_device_name_n
 * @since_tizen		2.3
 * @description		Call to get the device name from the scan result information with "NULL" parameters
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise
 *					just try to get the device name from the scan result information with "NULL" parameters
 *					and check the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get the device name from the scan result information with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_get_scan_result_device_name_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_get_scan_result_device_name(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_get_scan_result_device_name(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_get_scan_result_tx_power_level_n
 * @since_tizen		2.3
 * @description		Call to get the transmission power level from the scan result information with "NULL" parameters
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise
 *					just try to get the transmission power level from the scan result information with "NULL" parameters
 *					and check the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get the transmission power level from the scan result information with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_get_scan_result_tx_power_level_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_get_scan_result_tx_power_level(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

	} else {
		ret = bt_adapter_le_get_scan_result_tx_power_level(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_get_scan_result_service_solicitation_uuids_n
 * @since_tizen		2.3
 * @description		Call to get the service solicitation UUID list from the scan result information with "NULL" parameters
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise
 *					just try to get the service solicitation UUID list from the scan result information with "NULL" parameters
 *					and check the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get the service solicitation UUID list from the scan result information with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_get_scan_result_service_solicitation_uuids_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_get_scan_result_service_solicitation_uuids(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_get_scan_result_service_solicitation_uuids(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_get_scan_result_service_data_list_n
 * @since_tizen		2.3
 * @description		Call to get the service data list from the scan result information with "NULL" parameters
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise
 *					just try to get the service data list from the scan result information with "NULL" parameters
 *					and check the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get the service data list from the scan result information with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_get_scan_result_service_data_list_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_get_scan_result_service_data_list(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_get_scan_result_service_data_list(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_free_service_data_list_n
 * @since_tizen		2.3
 * @description		Call to free service data list with "NULL" data_list parameter and check the "ret" flag with
 *					BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to free service data list
 *					with "NULL" data_list parameter and check the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to free service data list with "NULL" data_list parameter.
 */
int utc_bluetooth_bt_adapter_le_free_service_data_list_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_free_service_data_list(NULL, 0);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_free_service_data_list(NULL, 0);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_get_scan_result_appearance_n
 * @since_tizen		2.3
 * @description		Call to get the appearance from the scan result information with "NULL" parameters and check
 *					the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to get
 *					the appearance from the scan result information with "NULL" parameters and check the "ret" flag
 *					with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get the appearance from the scan result information with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_get_scan_result_appearance_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_get_scan_result_appearance(NULL,
						BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_get_scan_result_appearance(NULL,
						BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_get_scan_result_manufacturer_data_n
 * @since_tizen		2.3
 * @description		Call to get the manufacturer data from the scan result information with "NULL" parameters and check
 *					the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to get
 *					the manufacturer data from the scan result information with "NULL" parameters and check the "ret" flag
 *					with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get the manufacturer data from the scan result information with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_get_scan_result_manufacturer_data_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_get_scan_result_manufacturer_data(NULL,
					BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_get_scan_result_manufacturer_data(NULL,
					BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_add_advertising_service_uuid_n
 * @since_tizen		2.3
 * @description		Call to add a service UUID to advertise or scan response data with "NULL" parameters and check
 *					the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to
 *					add a service UUID to advertise or scan response data with "NULL" parameters and check the "ret" flag
 *					with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to add a service UUID to advertise or scan response data with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_add_advertising_service_uuid_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_add_advertising_service_uuid(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_add_advertising_service_uuid(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_add_advertising_service_solicitation_uuid_n
 * @since_tizen		2.3
 * @description		Call to add a service solicitation UUID to advertise or scan response data with "NULL" parameters
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to
 *					add a service solicitation UUID to advertise or scan response data with "NULL" parameters and check
 *					the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to add a service solicitation UUID to advertise or scan response data with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_add_advertising_service_solicitation_uuid_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_add_advertising_service_solicitation_uuid(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_add_advertising_service_solicitation_uuid(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_add_advertising_service_data_n
 * @since_tizen		2.3
 * @description		Call to add service data to advertise or scan response data with "NULL" parameters
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to
 *					add service data to advertise or scan response data with "NULL" parameters and check
 *					the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to add service data to advertise or scan response data with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_add_advertising_service_data_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_add_advertising_service_data(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL, NULL, 0);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_add_advertising_service_data(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, NULL, NULL, 0);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_advertising_appearance_n
 * @since_tizen		2.3
 * @description		Call to set the external appearance of local device to advertise or scan response data with
 *					"NULL" advertiser parameter and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is
 *					supported otherwise just try to set the external appearance of this device to advertise or scan response
 *					data with "NULL"advertiser parameter and check the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set the external appearance of local device to advertise with "NULL" parameter.
 */
int utc_bluetooth_bt_adapter_le_set_advertising_appearance_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_appearance(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, 0);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_set_advertising_appearance(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, 0);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_add_advertising_manufacturer_data_n
 * @since_tizen		2.3
 * @description		Call to add manufacturer specific data to advertise or scan response data with "NULL" parameters
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to
 *					add manufacturer specific data to advertise or scan response data with "NULL" parameters and check
 *					the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to add manufacturer specific data to advertise or scan response data with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_add_advertising_manufacturer_data_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_add_advertising_manufacturer_data(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, 0, NULL, 0);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_add_advertising_manufacturer_data(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, 0, NULL, 0);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_advertising_device_name_n
 * @since_tizen		2.3
 * @description		Call to set the device name in advertising data or scan response data with "NULL" and "FALSE"
 *					parameters and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported
 *					otherwise just try to set the device name in advertising data or scan response data with
 *					"NULL" and "FALSE" parameters and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set the device name in advertising data or scan response data with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_set_advertising_device_name_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_device_name(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, false);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_set_advertising_device_name(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, false);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_advertising_tx_power_level_n
 * @since_tizen		2.3
 * @description		Call to set whether the transmission power level should be included in advertise or scan response data
 *					with "NULL" parameters	and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported
 *					otherwise just try to set transmission power level data in advertise or scan response data with "NULL"
 *					parameters and check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set whether the transmission power level should be included in advertise data with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_set_advertising_tx_power_level_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_tx_power_level(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, false);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_set_advertising_tx_power_level(NULL,
						BT_ADAPTER_LE_PACKET_ADVERTISING, false);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_start_advertising_new_n
 * @since_tizen		2.3
 * @description		Call to start advertising with "NULL" parameters and check the "ret" flag with BT_ERROR_INVALID_PARAMETER
 *					if le is supported otherwise just try to	start advertising with "NULL" parameters with "NULL" parameters
 *					and check the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to start advertising with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_start_advertising_new_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_start_advertising_new(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_start_advertising_new(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_advertising_mode_n
 * @since_tizen		2.3
 * @description		Call to set advertising mode to control the advertising power and latency with "NULL" advertiser parameter
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to
 *					set advertising mode to control the advertising power and latency with "NULL" parameter and check
 *					the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set advertising mode to control the advertising power and latency with "NULL" parameter.
 */
int utc_bluetooth_bt_adapter_le_set_advertising_mode_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_mode(NULL,
						BT_ADAPTER_LE_ADVERTISING_MODE_BALANCED);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_set_advertising_mode(NULL,
						BT_ADAPTER_LE_ADVERTISING_MODE_BALANCED);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_advertising_connectable_n
 * @since_tizen		2.3
 * @description		Call to set whether the advertising type should be connectable or non-connectable with "NULL" parameters
 *					and check the "ret" flag with BT_ERROR_INVALID_PARAMETER if le is supported otherwise just try to
 *					set whether the advertising type should be connectable or non-connectable with "NULL" parameters and check
 *					the "ret" flag with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set whether the advertising type should be connectable or
 *				non-connectable with "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_le_set_advertising_connectable_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_set_advertising_connectable(NULL, false);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_set_advertising_connectable(NULL, false);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		 utc_bluetooth_bt_get_uuid_name_n
 * @since_tizen 3.0
 * @description		Call to get uuid name with "NULL" parameters and check the "ret" flag with BT_ERROR_INVALID_PARAMETER
 *					if le is supported otherwise just try to get uuid name with "NULL" parameters and check the "ret" flag
 *					with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get uuid name "NULL" parameters.
 */
int utc_bluetooth_bt_get_uuid_name_n(void)
{
	if (bt_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_get_uuid_name(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_get_uuid_name(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_le_set_scan_mode_n
 * @since_tizen		3.0
 * @description		Call to set LE scan mode after deinitializing Bluetooth and check the "ret"
 *					flag with BT_ERROR_NOT_INITIALIZED if LE is supported otherwise just try to set LE scan mode
 *					check the "ret" flag with BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set LE scan mode.

 */
int utc_bluetooth_bt_adapter_le_set_scan_mode_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_adapter_le_set_scan_mode(BT_ADAPTER_LE_SCAN_MODE_BALANCED);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_adapter_le_set_scan_mode(BT_ADAPTER_LE_SCAN_MODE_BALANCED);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_get_local_oob_ext_data_n
 * @since_tizen		3.0
 * @description		Call to get local oob ext data with "NULL" parameters and check the "ret" flag with BT_ERROR_INVALID_PARAMETER
 *					if le is supported otherwise just try to get uuid name with "NULL" parameters and check the "ret" flag
 *					with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to get local oob ext data "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_get_local_oob_ext_data_n(void)
{
	if (bt_supported && oob_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_get_local_oob_ext_data(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_get_local_oob_ext_data(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

 /**
 * @testcase		utc_bluetooth_bt_adapter_set_remote_oob_ext_data_n
 * @since_tizen		3.0
 * @description		Call to set remotel oob ext data with "NULL" parameters and check the "ret" flag with BT_ERROR_INVALID_PARAMETER
 *					if le is supported otherwise just try to get uuid name with "NULL" parameters and check the "ret" flag
 *					with	BT_ERROR_NOT_SUPPORTED.
 * @scenario		Negative scenario to set remote oob ext data "NULL" parameters.
 */
int utc_bluetooth_bt_adapter_set_remote_oob_ext_data_n(void)
{
	if (bt_supported && oob_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_adapter_set_remote_oob_ext_data(NULL, NULL, NULL, 0, 0, NULL, NULL, 0, 0);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_set_remote_oob_ext_data(NULL, NULL, NULL, 0, 0, NULL, NULL, 0, 0);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_create_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_create(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_create(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_destroy_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_destroy(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_destroy(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_device_address_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_device_address(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_device_address(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_device_name_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_device_name(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_device_name(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_service_uuid_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_service_uuid(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_service_uuid(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_service_uuid_with_mask_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_service_uuid_with_mask(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_service_uuid_with_mask(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_service_solicitation_uuid_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_service_solicitation_uuid(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_service_solicitation_uuid(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask_n(void)
{
	if(le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_service_data_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_service_data(NULL, NULL, NULL, 0);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_service_data(NULL, NULL, NULL, 0);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_service_data_with_mask_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_service_data_with_mask(NULL,
				NULL, NULL, 8, NULL, 8);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_service_data_with_mask(NULL,
				NULL, NULL, 8, NULL, 8);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_manufacturer_data_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_manufacturer_data(NULL,
				0, NULL, 8);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_manufacturer_data(NULL,
				0, NULL, 8);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_manufacturer_data_with_mask_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_manufacturer_data_with_mask(NULL,
				0, NULL, 8, NULL, 8);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_manufacturer_data_with_mask(NULL,
				0, NULL, 8, NULL, 8);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_register_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_register(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_register(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_unregister_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_unregister(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_unregister(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_unregister_all_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret,BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_unregister_all();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_adapter_le_scan_filter_unregister_all();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_scan_filter_set_type_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_scan_filter_set_type(NULL,
					BT_ADAPTER_LE_SCAN_FILTER_TYPE_IBEACON);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_scan_filter_set_type(NULL,
					BT_ADAPTER_LE_SCAN_FILTER_TYPE_IBEACON);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_get_scan_result_ibeacon_report_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_get_scan_result_ibeacon_report(NULL, BT_ADAPTER_LE_PACKET_ADVERTISING, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_get_scan_result_ibeacon_report(NULL, BT_ADAPTER_LE_PACKET_ADVERTISING, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_free_ibeacon_report_n(void)
{
	if (le_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_free_ibeacon_report(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_free_ibeacon_report(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_is_2m_phy_supported_n(void)
{
	if (le_50_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_is_2m_phy_supported(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_is_2m_phy_supported(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_adapter_le_is_coded_phy_supported_n(void)
{
	if (le_50_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_adapter_le_is_coded_phy_supported(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_adapter_le_is_coded_phy_supported(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

