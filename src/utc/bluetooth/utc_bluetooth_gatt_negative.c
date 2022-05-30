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

//& set: BluetoothGattNegative

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static const char *remote_addr = "E4:32:CB:41:1F:A6";
static bool le_supported = false;
static bool bt_supported = false;
static bool gatt_client_supported = false;
static bool gatt_server_supported = false;
static bool ipsp_supported = false;


static void gatt_connection_state_changed_cb_p(int result, bool connected,
				const char *remote_address, void *user_data)
{
	if (connected)
		fprintf(stderr,"Device is connected with remote address.");
	else
		fprintf(stderr,"Device is disconnected from remote address.");
}

/**
 * @function		utc_bluetooth_gatt_negative_startup
 * @description 	if bluetooth is supported and LE is supported, initialize bluetooth.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_gatt_negative_startup(void)
{
    bt_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth", &bt_supported);

    le_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.le", &le_supported);

    gatt_client_supported = false;
    system_info_get_platform_bool("tizen.org/feature/network.bluetooth.le.gatt.client", &gatt_client_supported);

    gatt_server_supported = false;
    system_info_get_platform_bool("tizen.org/feature/network.bluetooth.le.gatt.server", &gatt_server_supported);

	ipsp_supported = false;
    system_info_get_platform_bool("http://tizen.org/feature/network.bluetooth.le.ipsp", &ipsp_supported);

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
 * @function		utc_bluetooth_gatt_negative_cleanup
 * @description 	If bluetooth is supported and LE is supported, release all the bluetooth resources.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_gatt_negative_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_gatt_connect_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				connect to the remote device and check for errors.
 * @scenario		Try to connect to a specific LE based service on a remote bluetooth dievice address,
 *				asynchronously after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_connect_n(void)
{
    bool auto_connect = FALSE;

    if(gatt_client_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_gatt_connect(remote_addr, auto_connect);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else{
        ret = bt_gatt_connect(remote_addr, auto_connect);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/*
 * @brief Negative test case of bt_gatt_disconnect()
 */
/**
 * @testcase		utc_bluetooth_bt_gatt_disconnect_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				disconnect connection to the remote device and check for errors.
 * @scenario		Try to disconnect to a specific LE based service on a remote bluetooth dievice address,
 *				asynchronously after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_disconnect_n(void)
{
    if(gatt_client_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_gatt_disconnect(remote_addr);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_gatt_disconnect(remote_addr);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/*
 * @brief Negative test case of bt_gatt_connect()
 */
/**
 * @testcase		utc_bluetooth_bt_gatt_connect_n1
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then connect to the remote device
 *				with invalid parameters and check for errors.
 * @scenario		Try to connect to a specific LE based service on a remote bluetooth dievice address,
 *				asynchronously with invalid parameters.
 */
int utc_bluetooth_bt_gatt_connect_n1(void)
{
    bool auto_connect = FALSE;

    if(gatt_client_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_initialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_gatt_connect(NULL, auto_connect);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_gatt_connect(NULL, auto_connect);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/*
 * @brief Negative test case of bt_gatt_disconnect()
 */
/**
 * @testcase		utc_bluetooth_bt_gatt_disconnect_n1
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then disconnect the connection to the remote device
 *				with invalid parameters and check for errors.
 * @scenario		Try to disconnect to a specific LE based service on a remote bluetooth dievice address,
 *				asynchronously with invalid parameters.
 */
int utc_bluetooth_bt_gatt_disconnect_n1(void)
{
    if(gatt_client_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_initialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_gatt_disconnect(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret = bt_gatt_disconnect(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_set_connection_state_changed_cb_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth  and
 *				register a callback for LE connection change and check for errors.
 * @scenario		Registers a callback function that will be invoked when a LE connection state is changed
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_set_connection_state_changed_cb_n(void)
{
    if(gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_gatt_set_connection_state_changed_cb(
        	gatt_connection_state_changed_cb_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_gatt_set_connection_state_changed_cb(
        	gatt_connection_state_changed_cb_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_unset_connection_state_changed_cb_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth  and
 *				unregister the callback for LE connection change and check for errors.
 * @scenario		Try to unregister the callback function that will be invoked when a LE connection state is changed
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_unset_connection_state_changed_cb_n(void)
{
    if(gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);
        ret = bt_deinitialize();
        assert_eq(ret,BT_ERROR_NONE);

        ret = bt_gatt_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
    } else {
        ret = bt_gatt_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_get_value_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the value of a
 *				characteristic or descriptor's GATT handle  by using the invalid parameters and check for errors.
 * @scenario		Try to get the value of a characteristic or descriptor's GATT handle  by using the invalid parameters.
 */
int utc_bluetooth_bt_gatt_get_value_n(void)
{
	bt_gatt_h gatt_handle = NULL;
	char *value = NULL;
	int len = 0;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_get_value(gatt_handle, &value, &len);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_get_value(gatt_handle, &value, &len);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_get_int_value_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the value of a
 *				characteristic or descriptor's GATT handle of interger type  by using the invalid parameters and check for errors.
 * @scenario		Try to get the value of a characteristic or descriptor's GATT handle as an integer type  by using the invalid parameters.
 */
int utc_bluetooth_bt_gatt_get_int_value_n(void)
{
	bt_gatt_h gatt_handle = NULL;
	char *value = NULL;
	int offset = 0;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_get_int_value(gatt_handle, BT_DATA_TYPE_SINT16, offset, value);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_get_int_value(gatt_handle, BT_DATA_TYPE_SINT16, offset, value);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_get_float_value_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the value of a
 *				characteristic or descriptor's GATT handle of float type  by using the invalid parameters and check for errors.
 * @scenario		Try to get the value of a characteristic or descriptor's GATT handle as an float type  by using the invalid parameters.
 */
int utc_bluetooth_bt_gatt_get_float_value_n(void)
{
	bt_gatt_h gatt_handle = NULL;
	float *value = NULL;
	int offset = 0;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_get_float_value(gatt_handle, BT_DATA_TYPE_FLOAT, offset, value);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_get_float_value(gatt_handle, BT_DATA_TYPE_FLOAT, offset, value);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_set_value_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then set the value of a
 *				characteristic or descriptor's GATT handle  by using the invalid parameters and check for errors.
 * @scenario		Try to set the value of a characteristic or descriptor's GATT handle  by using the invalid parameters.
 */
int utc_bluetooth_bt_gatt_set_value_n(void)
{
	bt_gatt_h gatt_handle = NULL;
	const char *value = NULL;
	int value_length = 0;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_set_value(gatt_handle, value, value_length);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_set_value(gatt_handle, value, value_length);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_set_int_value_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then update the value of a
 *				characteristic or descriptor's GATT handle of interger type  by using the invalid parameters and check for errors.
 * @scenario		Try to update the value of a characteristic or descriptor's GATT handle as an integer type  by using the invalid parameters.
 */
int utc_bluetooth_bt_gatt_set_int_value_n(void)
{
	bt_gatt_h gatt_handle = NULL;
	const char *value = NULL;
	int value_length = 0;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_set_int_value(gatt_handle, 0x02, value, value_length);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_set_int_value(gatt_handle, 0x02, value, value_length);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_set_float_value_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then update the value of a
 *				characteristic or descriptor's GATT handle of float type  by using the invalid parameters and check for errors.
 * @scenario		Try to update the value of a characteristic or descriptor's GATT handle as an float type  by using the invalid parameters.
 */
int utc_bluetooth_bt_gatt_set_float_value_n(void)
{
	bt_gatt_h gatt_handle = NULL;
	const char *value = NULL;
	int mantissa = 0;
	int exponent = 0;
	int offset = 0;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_set_float_value(gatt_handle,
						BT_DATA_TYPE_FLOAT, mantissa, exponent, offset);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_set_float_value(gatt_handle,
						BT_DATA_TYPE_FLOAT, mantissa, exponent, offset);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_get_uuid_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the uuid of given
 *				GATT attribute handle  by using the invalid parameters and check for errors.
 * @scenario		Try to get the UUID of a service, characteristic or descriptor's GATT handle  by using the invalid parameters.
 */
int utc_bluetooth_bt_gatt_get_uuid_n(void)
{
	bt_gatt_h gatt_handle = NULL;
	char *uuid = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_get_uuid(gatt_handle, &uuid);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_get_uuid(gatt_handle, &uuid);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_get_type_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the attribute type
 *				of given GATT attribute handle  by using the invalid parameters and check for errors.
 * @scenario		Try to get the type of GATT handle  by using the invalid parameters.
 */
int utc_bluetooth_bt_gatt_get_type_n(void)
{
	bt_gatt_h gatt_handle = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_get_type(gatt_handle, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_get_type(gatt_handle, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_get_client_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the client handle
 *				of given GATT attribute handle  by using the invalid parameters and check for errors.
 * @scenario		Try to get the GATT client handle which the specified service belongs to, using invalid paramters.
 */
int utc_bluetooth_bt_gatt_service_get_client_n(void)
{
	bt_gatt_h gatt_handle = NULL;
	bt_gatt_client_h *client = NULL;

	if(gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_get_client(gatt_handle, client);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_service_get_client(gatt_handle, client);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_get_characteristic_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the characteristic's GATT handle
 *				of the given UUID by using invalid paramters and check for errors.
 * @scenario		Try to get a characteristic's GATT handle which has specific UUID by using invalid paramters.
 */
int utc_bluetooth_bt_gatt_service_get_characteristic_n(void)
{
	bt_gatt_h service = NULL;
	const char *uuid = NULL;
	bt_gatt_h *characteristic = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_get_characteristic(service, uuid, characteristic);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_service_get_characteristic(service, uuid, characteristic);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_gatt_client_foreach_chr_cb(int total, int index, bt_gatt_h chr_handle, void *data)
{

}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_foreach_characteristics_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get all of the characterisitcs those
 *				belong to a specific service by using the invalid parameters and check for errors.
 * @scenario		Try to invoke callback function on each characteristic that belongs to the specified service
 * 				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_service_foreach_characteristics_n(void)
{
	int test_id = 0;
	bt_gatt_h service = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_foreach_characteristics(service,
						__bt_gatt_client_foreach_chr_cb, (void *)test_id);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_service_foreach_characteristics(service,
						__bt_gatt_client_foreach_chr_cb, (void *)test_id);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_get_included_service_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the included service's GATT handle
 *				of the given specific UUID by using the invalid parameters. and check for errors.
 * @scenario		Try to get a included service's GATT handle which has specific UUID, where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_service_get_included_service_n(void)
{
	bt_gatt_h service = NULL;
	const char *uuid = NULL;
	bt_gatt_h *included_service = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_get_included_service(service, uuid, included_service);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_service_get_included_service(service, uuid, included_service);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_bluetooth_bt_gatt_service_foreach_included_services_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get all of the included services those
 *				belong to a specific service by using the invalid parameters and check for errors.
 * @scenario		Try to invoke callback function on each included services that belongs to the specified service
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_service_foreach_included_services_n(void)
{
	bt_gatt_h service = NULL;
	const char *uuid = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_foreach_included_services(service, __bt_gatt_client_foreach_chr_cb, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_service_foreach_included_services(service, __bt_gatt_client_foreach_chr_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_get_service_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the service handle
 *				of the given characteristics handle using invalid paramters and check for errors.
 * @scenario		Try to get the service's GATT handle which the specified characteristic belongs to using invalid paramters.
 */
int utc_bluetooth_bt_gatt_characteristic_get_service_n(void)
{
	bt_gatt_h characteristic = NULL;
	bt_gatt_h *service = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_get_service(characteristic, service);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_characteristic_get_service(characteristic, service);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_get_properties_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the properties of the given
 *				characteristics handle by using the invalid parameters. and check for errors.
 * @scenario		Try to get the properties which a characteristic's GATT handle has, where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_characteristic_get_properties_n(void)
{
	bt_gatt_h characteristic = NULL;
	int *properties = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_get_properties(characteristic, properties);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_characteristic_get_properties(characteristic, properties);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_get_write_type_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the attribute write type of the given
 *				characteristics handle by using the invalid parameters. and check for errors.
 * @scenario		Try to get the write type of the specified characteristic, where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_characteristic_get_write_type_n(void)
{
	bt_gatt_h characteristic = NULL;
	bt_gatt_write_type_e *write_type = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_get_write_type(characteristic, write_type);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);

	} else {
		ret = bt_gatt_characteristic_get_write_type(characteristic, write_type);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_set_write_type_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then set the attribute write type of the given
 *				characteristics handle by using the invalid parameters. and check for errors.
 * @scenario		Try to set the write type of the specified characteristic, where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_characteristic_set_write_type_n(void)
{
	bt_gatt_h characteristic = NULL;
	bt_gatt_write_type_e write_type = BT_GATT_WRITE_TYPE_WRITE_NO_RESPONSE;


	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_set_write_type(characteristic, write_type);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_characteristic_set_write_type(characteristic, write_type);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_get_descriptor_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the descriptor's GATT handle
 *				of the given specific UUID by using the invalid parameters. and check for errors.
 * @scenario		Try to get a descriptor's GATT handle which has specific UUID, where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_characteristic_get_descriptor_n(void)
{
	bt_gatt_h characteristic = NULL;
	const char *uuid = NULL;
	bt_gatt_h *descriptor = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_get_descriptor(characteristic, uuid, descriptor);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_characteristic_get_descriptor(characteristic, uuid, descriptor);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_foreach_descriptors_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get all of the descriptors those
 *				belong to a specific characteristic by using the invalid parameters and check for errors.
 * @scenario		Try to invoke callback function on each characteristic that belongs to the specified characteristic
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_characteristic_foreach_descriptors_n(void)
{
	bt_gatt_h characteristic = NULL;
	const char *uuid = NULL;
	bt_gatt_h *descriptor = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_foreach_descriptors(characteristic,
							__bt_gatt_client_foreach_chr_cb, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_characteristic_foreach_descriptors(characteristic,
							__bt_gatt_client_foreach_chr_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_descriptor_get_characteristic_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the characteristic's handle
 *				of the given descriptor handle by using the invalid parameters and check for errors.
 * @scenario		Try to get the characteristic's GATT handle which the specified descriptor belongs to by using the invalid parameters.
 */
int utc_bluetooth_bt_gatt_descriptor_get_characteristic_n(void)
{
	bt_gatt_h descriptor = NULL;
	bt_gatt_h *characteristic = NULL;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_descriptor_get_characteristic(descriptor,	characteristic);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_descriptor_get_characteristic(descriptor, characteristic);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_client_create_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				create the client for given remote device and check for errors.
 * scenario 		Try to create the GATT client handle after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_client_create_n(void)
{
	const char *remote_address = "00:19:0E:01:61:17";
	bt_gatt_client_h client = NULL;

	if(gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_deinitialize();
		assert_eq(ret,BT_ERROR_NONE);

		ret = bt_gatt_client_create(remote_address,	&client);
		if(ret == BT_ERROR_NONE)
			bt_gatt_client_destroy(client);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_client_create(remote_address, client);
		if(ret == BT_ERROR_NONE)
			bt_gatt_client_destroy(client);

		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_client_destroy_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				destroy the client for given remote device and check for errors.
 * scenario 		Try to destroy the GATT client handle after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_client_destroy_n(void)
{
	const char *remote_address = "00:19:0E:01:61:17";
	bt_gatt_client_h client = NULL;

	if(gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_deinitialize();
		assert_eq(ret,BT_ERROR_NONE);

		ret = bt_gatt_client_create(remote_address,	&client);
		ret = bt_gatt_client_destroy(client);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_client_destroy(client);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_client_get_remote_address_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				get the device address for given remote device for which client is create and check for errors.
 * scenario 		Try to get the address of remote device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_client_get_remote_address_n(void)
{
	bt_gatt_client_h client = NULL;
	char *remote_address = "00:19:0E:01:61:17";

	if(gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);
		ret = bt_deinitialize();
		assert_eq(ret,BT_ERROR_NONE);

		bt_gatt_client_create(remote_address, &client);

		ret = bt_gatt_client_get_remote_address(client, &remote_address);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);

		if(ret == BT_ERROR_NONE)
			bt_gatt_client_destroy(client);
	} else {
		ret = bt_gatt_client_get_remote_address(client, &remote_address);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_gatt_client_read_complete_cb(int result, bt_gatt_h gatt_handle, void *data)
{

}

/**
 * @testcase		utc_bluetooth_bt_gatt_client_read_value_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then read the value of a
 *				characteristic or descriptor's GATT handle by using the invalid parameters and check for errors.
 * @scenario		Try to read the value of a characteristic or descriptor from the remote device asynchronously,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_client_read_value_n(void)
{
	bt_gatt_h gatt_handle = NULL;

	if(gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_client_read_value(gatt_handle,
						__bt_gatt_client_read_complete_cb, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_client_read_value(gatt_handle,
						__bt_gatt_client_read_complete_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_gatt_client_request_completed_cb(int result, bt_gatt_h request_handle, void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_gatt_client_write_value_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then update the value of a
 *				characteristic or descriptor's GATT handle by using the invalid parameters and check for errors.
 * @scenario		Try to write the value of a characteristic or descriptor from the remote device asynchronously,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_client_write_value_n(void)
{
	bt_gatt_h client = NULL;
	void *user_data = NULL;

	if(gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_client_write_value(client, __bt_gatt_client_request_completed_cb, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_client_write_value(client, __bt_gatt_client_read_complete_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_gatt_client_value_changed_cb(bt_gatt_h chr, char *value, int len, void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_gatt_client_set_characteristic_value_changed_cb_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then register a callback for characterisitc value is changed
 *				on the remote device by using the invalid parameters and check for errors.
 * @scenario		Try to unregister a callback function to be invoked when the characteristic value is changed on the remote device,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_client_set_characteristic_value_changed_cb_n(void)
{
	bt_gatt_h characteristic = NULL;

	if(gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_client_set_characteristic_value_changed_cb(characteristic,
				__bt_gatt_client_value_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_client_set_characteristic_value_changed_cb(characteristic,
				__bt_gatt_client_value_changed_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_bluetooth_bt_gatt_client_unset_characteristic_value_changed_cb_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then unregister a callback for characterisitc value is changed
 *				on the remote device by using the invalid parameters and check for errors.
 * @scenario		Try to unregister a callback function to be invoked when the characteristic value is changed on the remote device,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_client_unset_characteristic_value_changed_cb_n(void)
{
	bt_gatt_h characteristic = NULL;

	if(gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_client_unset_characteristic_value_changed_cb(characteristic);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_client_unset_characteristic_value_changed_cb(characteristic);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_client_get_service_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get the service's handle
 *				of the given specific UUId from the client created by using the invalid parameters and check for errors.
 * @scenario		Try to get a service's GATT handle which has specific UUID, where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_client_get_service_n(void)
{
	bt_gatt_client_h client = NULL;
	const char *uuid = NULL;
	bt_gatt_h *service = NULL;

	if(gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_client_get_service(client, uuid, service);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_client_get_service(client, uuid, service);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void __bt_gatt_foreach_cb(int total, int index, bt_gatt_h gatt_handle, void *user_data)
{

}

/**
 * @testcase		utc_bluetooth_bt_gatt_client_foreach_services_n
 * @since_tizen		2.3
 * @description 	if bluetooth LE is supported and startup_flag is asserted then get all of the service those
 *				belong to a specific GATT client device by using the invalid parameters and check for errors.
 * @scenario		Try to invoke callback function on each service that belongs to the specified GATT client
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_client_foreach_services_n(void)
{
	bt_gatt_client_h client = NULL;

	if(gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_client_foreach_services(client, __bt_gatt_foreach_cb, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_client_foreach_services(client, __bt_gatt_foreach_cb, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_destroy_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then destroy the service handle,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to destroy the service handle,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_service_destroy_n(void)
{
	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_destroy(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_service_destroy(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_destroy_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then destroy the characteristic handle,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to destroy the characteristic handle,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_characteristic_destroy_n(void)
{
	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_destroy(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_characteristic_destroy(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_descriptor_destroy_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then destroy the descriptor handle,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to destroy the descriptor handle,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_descriptor_destroy_n(void)
{
	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_descriptor_destroy(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_descriptor_destroy(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_get_permissions_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then get the characteristic's permission,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to get the characteristic's permission,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_characteristic_get_permissions_n(void)
{
	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_get_permissions(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_characteristic_get_permissions(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_descriptor_get_permissions_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then get the descriptor's permission,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to get the descriptor's permission,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_descriptor_get_permissions_n(void)
{
	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_descriptor_get_permissions(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_descriptor_get_permissions(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_create_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then create the GATT service,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to create the GATT service,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_service_create_n(void)
{
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_create(NULL, service_type, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_service_create(NULL, service_type, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_add_characteristic_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then add the characteristic to the service,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to add the characteristic to the service,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_service_add_characteristic_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_add_characteristic(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_service_add_characteristic(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_add_included_service_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then add the service to the specified service as included service,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to add the service to the specified service,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_service_add_included_service_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_add_included_service(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_service_add_included_service(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_get_server_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then get the GATT server handle from the specified service,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to get the GATT server handle from the specified service,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_service_get_server_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_get_server(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_service_get_server(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_create_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then create the GATT characteristic,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to create the GATT characteristic,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_characteristic_create_n(void)
{
	int permissions = BT_GATT_PERMISSION_READ;
	int properties = BT_GATT_PROPERTY_READ | BT_GATT_PROPERTY_NOTIFY;
	char char_value[1] = {80};

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_create(NULL, permissions, properties, char_value, sizeof(char_value), NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_characteristic_create(NULL, permissions, properties, char_value, sizeof(char_value), NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_add_descriptor_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then add the descriptor to the characteristic,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to add the descriptor to the characteristic,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_characteristic_add_descriptor_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_add_descriptor(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_characteristic_add_descriptor(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_descriptor_create_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then create the GATT descriptor,
 *				by using the invalid parameters and check for errors.
 * @scenario		Try to create the GATT descriptor,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_descriptor_create_n(void)
{
	char desc_value[2] = {0, 0};
	int permissions = BT_GATT_PERMISSION_READ | BT_GATT_PERMISSION_WRITE;

	if(gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_descriptor_create(NULL, permissions, desc_value, sizeof(desc_value), NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_descriptor_create(NULL, permissions, desc_value, sizeof(desc_value), NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_initialize_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						initialize the GATT server and check for errors.
 * @scenario		Try to initialize the GATT server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_initialize_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_initialize();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_deinitialize_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						deinitialize the GATT server and check for errors.
 * @scenario		Try to deinitialize the GATT server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_deinitialize_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_create_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						create the GATT server and check for errors.
 * @scenario		Try to create the GATT server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_create_n(void)
{
	bt_gatt_server_h server = NULL;

	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_create(&server);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_create(&server);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_destroy_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						destroy the GATT server and check for errors.
 * @scenario		Try to destroy the GATT server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_destroy_n(void)
{
	bt_gatt_server_h server = NULL;

	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_destroy(server);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_destroy(server);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_set_read_value_requested_cb_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						register a callback function to be invoked when a read request is issued and check for errors.
 * @scenario		Try to register a callback function to be invoked when a read request is issued after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_set_read_value_requested_cb_n(void)
{
	bt_gatt_h characteristic = NULL;

	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_set_read_value_requested_cb(characteristic, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_set_read_value_requested_cb(characteristic, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_bluetooth_bt_gatt_server_set_characteristic_notification_state_change_cb_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, i
 *					then deinitialize the bluetooth and register a callback function to be invoked
 *					when the remote device enables or disables the Notification/Indication for particular characteristics and check for errors.
 * @scenario		Try to register a callback function to be invoked
 *					when the remote device enables or disables the Notification/Indication for particular characteristics and check for errors
 *					after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_set_characteristic_notification_state_change_cb_n(void)
{
	bt_gatt_h characteristic = NULL;

	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_set_characteristic_notification_state_change_cb(characteristic, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_set_characteristic_notification_state_change_cb(characteristic, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_set_write_value_requested_cb_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *						register a callback function to be invoked when a write request is issued and check for errors.
 * @scenario		Try to register a callback function to be invoked when a write request is issued after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_set_write_value_requested_cb_n(void)
{
	bt_gatt_h characteristic = NULL;

	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_set_write_value_requested_cb(characteristic, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_set_write_value_requested_cb(characteristic, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_notify_characteristic_changed_value_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *						notify value change of the characteristic to the remote device and check for errors.
 * @scenario		Try to notify value change of the characteristic to the remote device after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_notify_characteristic_changed_value_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_notify_characteristic_changed_value(NULL, NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_notify_characteristic_changed_value(NULL, NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_get_service_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						get a service's GATT handle which has a specific UUID and check for errors.
 * @scenario		Try to get a service's GATT handle which has a specific UUID after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_get_service_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_get_service(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_get_service(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_get_device_mtu_n
 * @since_tizen		5.5
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *					get the remote deivce's MTU value and check for errors.
 * @scenario		Try to get the remote deivce's MTU value after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_get_device_mtu_n(void)
{
	if (gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_get_device_mtu(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_get_device_mtu(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_foreach_services_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *						invoke a callback function on each service that belongs to be specified GATT server and check for errors.
 * @scenario		Try to invoke a callback function on each service that belongs to be specified GATT server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_foreach_services_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_foreach_services(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_foreach_services(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_register_service_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						register a GATT service handle to GATT server and check for errors.
 * @scenario		Try to register a GATT service handle to GATT server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_register_service_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_register_service(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_register_service(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_unregister_service_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						unregister a GATT service handle from the GATT server and check for errors.
 * @scenario		Try to unregister a GATT service handle from the GATT server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_unregister_service_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_unregister_service(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_unregister_service(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_unregister_all_services_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						unregister the all GATT services handle from the GATT server and check for errors.
 * @scenario		Try to unregister the all GATT services handle from the GATT server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_unregister_all_services_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_unregister_all_services(NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_unregister_all_services(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_start_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						start a server and check for errors.
 * @scenario		Try to start a server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_start_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_start();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_start();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_send_response_n
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and 
 *						send response and check for errors.
 * @scenario		Try to send response after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_server_send_response_n(void)
{
	if(gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_send_response(0, 0, 0, 0, NULL, -1);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_server_send_response(0, 0, 0, 0, NULL, -1);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_client_set_service_changed_cb_n
 * @since_tizen	3.0
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				register a callback for service change and check for errors.
 * @scenario		Registers a callback function that will be invoked when a service is changed after bluetooth de-initialization.
 */
int utc_bluetooth_bt_gatt_client_set_service_changed_cb_n(void)
{
	if (gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_deinitialize();
		assert_eq(ret,BT_ERROR_NONE);

		ret = bt_gatt_client_set_service_changed_cb(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_gatt_client_set_service_changed_cb(NULL, NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_client_unset_service_changed_cb_n
 * @since_tizen	3.0
 * @description 	if bluetooth LE is supported and startup_flag is asserted then unregister a callback for service is changed
 *				on the remote device by using the invalid parameters and check for errors.
 * @scenario		Try to unregister a callback function to be invoked when the service is changed on the remote device,
 *				where the parameters passed are invalid.
 */
int utc_bluetooth_bt_gatt_client_unset_service_changed_cb_n(void)
{
	if (gatt_client_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_client_unset_service_changed_cb(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_gatt_client_unset_service_changed_cb(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_ipsp_initialize_n
 * @since_tizen	4.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				initialize the IPSP server and check for errors.
 * @scenario		Try to initialize the IPSP server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_ipsp_initialize_n(void)
{
	if (ipsp_supported) {
		ret = bt_ipsp_initialize(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_ipsp_initialize(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_ipsp_deinitialize_n
 * @since_tizen	4.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted, then deinitialize the bluetooth and
 *				deinitialize the IPSP server and check for errors.
 * @scenario		Try to deinitialize the IPSP server after bluetooth de-initialization.
 */
int utc_bluetooth_bt_ipsp_deinitialize_n(void)
{
	if (ipsp_supported) {
		ret = bt_deinitialize();

		ret = bt_ipsp_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_ipsp_deinitialize();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_ipsp_connect_n
 * @since_tizen	4.0
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				connect to the remote device and check for errors.
 * @scenario		Try to connect to the IPSP service on a remote bluetooth dievice address,
 *				asynchronously after bluetooth de-initialization.
 */
int utc_bluetooth_bt_ipsp_connect_n(void)
{
	if (ipsp_supported) {
		ret = bt_ipsp_connect(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_ipsp_connect(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_ipsp_disconnect_n
 * @since_tizen	4.0
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth and
 *				disconnect connection to the remote device and check for errors.
 * @scenario		Try to disconnect to the IPSP service on a remote bluetooth dievice address,
 *				asynchronously after bluetooth de-initialization.
 */
int utc_bluetooth_bt_ipsp_disconnect_n(void)
{
	if (ipsp_supported) {
		ret = bt_ipsp_disconnect(NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_ipsp_disconnect(NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_ipsp_set_connection_state_changed_cb_n
 * @since_tizen	4.0
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth  and
 *				register a callback for IPSP connection change and check for errors.
 * @scenario		Registers a callback function that will be invoked when a IPSP connection state is changed
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_ipsp_set_connection_state_changed_cb_n(void)
{
	if (ipsp_supported) {
		ret = bt_ipsp_set_connection_state_changed_cb(NULL, NULL);
		assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
	} else {
		ret = bt_ipsp_set_connection_state_changed_cb(NULL, NULL);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_ipsp_unset_connection_state_changed_cb_n
 * @since_tizen	4.0
 * @description 	if bluetooth LE is supported and startup_flag is asserted then deinitialize the bluetooth  and
 *				unregister the callback for IPSP connection change and check for errors.
 * @scenario		Try to unregister the callback function that will be invoked when a IPSP connection state is changed
 *				after bluetooth de-initialization.
 */
int utc_bluetooth_bt_ipsp_unset_connection_state_changed_cb_n(void)
{
	if (ipsp_supported) {
		ret = bt_deinitialize();

		ret = bt_ipsp_unset_connection_state_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_INITIALIZED);
	} else {
		ret = bt_ipsp_unset_connection_state_changed_cb();
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

int utc_bluetooth_bt_gatt_client_request_att_mtu_change_n(void)
{
    if (gatt_client_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret =  bt_gatt_client_request_att_mtu_change(NULL, 0);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret =  bt_gatt_client_request_att_mtu_change(NULL, 0);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

int utc_bluetooth_bt_gatt_client_get_att_mtu_n(void)
{
    if (gatt_client_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret =  bt_gatt_client_get_att_mtu(NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret =  bt_gatt_client_get_att_mtu(NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

int utc_bluetooth_bt_gatt_client_set_att_mtu_changed_cb_n(void)
{
    if (gatt_client_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret =  bt_gatt_client_set_att_mtu_changed_cb(NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret =  bt_gatt_client_set_att_mtu_changed_cb(NULL, NULL, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

int utc_bluetooth_bt_gatt_client_unset_att_mtu_changed_cb_n(void)
{
    if (gatt_client_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret =  bt_gatt_client_unset_att_mtu_changed_cb(NULL);
        assert_eq(ret, BT_ERROR_INVALID_PARAMETER);
    } else {
        ret =  bt_gatt_client_unset_att_mtu_changed_cb(NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

