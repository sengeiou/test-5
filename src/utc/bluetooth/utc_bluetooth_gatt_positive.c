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


//& set: BluetoothGattPositive

static int startup_flag = BT_ERROR_NONE;
static int ret = BT_ERROR_NONE;
static bool le_supported = false;
static bool gatt_client_supported = false;
static bool gatt_server_supported = false;
static bool bt_supported = false;
static bool ipsp_supported = false;

static void gatt_connection_state_changed_cb_p(int result, bool connected,
				const char *remote_address, void *user_data)
{
	if (connected)
		fprintf(stderr,"Device is connected with remote address.");
	else
		fprintf(stderr,"Device is disconnected from remote address.");
}

void __bt_ipsp_connection_state_changed_cb(int result,
	bool connected, const char *remote_address, const char *iface_name, void *user_data)
{

}

static void __bt_gatt_client_att_mtu_changed_cb(bt_gatt_client_h client, const bt_gatt_client_att_mtu_info_s *mtu_info, void *user_data)
{

}

static void __bt_gatt_server_read_value_requested_cb_p(const char *remote_address, int request_id,
			bt_gatt_server_h server, bt_gatt_h gatt_handle, int offset, void *user_data)
{
	fprintf(stderr, "__bt_gatt_server_read_value_requested_cb");
}

static void __bt_gatt_server_notification_state_change_cb_p(bool notify, bt_gatt_server_h server, bt_gatt_h gatt_handle, void *user_data)
{
	fprintf(stderr, "__bt_gatt_server_notification_state_change_cb");
}

static void __bt_gatt_server_write_value_requested_cb_p(const char *remote_address, int request_id, bt_gatt_server_h server,
			bt_gatt_h gatt_handle, bool response_needed, int offset, const char *value, int len, void *user_data)
{
	fprintf(stderr, "__bt_gatt_server_write_value_requested_cb");
}

static bool __bt_gatt_server_foreach_svc_cb_p(int total, int index, bt_gatt_h svc_handle, void *data)
{
	fprintf(stderr, "__bt_gatt_server_foreach_svc_cb");
}

/**
 * @function		utc_bluetooth_gatt_positive_startup
 * @description 	check if bluetooth is supported and LE is supported, Initialize bluetooth and check the adapter state and
 *				store adapter state for further use.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_gatt_positive_startup(void)
{
    bt_adapter_state_e adapter_state = BT_ADAPTER_DISABLED;

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

        ret = bt_adapter_get_state(&adapter_state);
        if (adapter_state != BT_ADAPTER_ENABLED) {
                fprintf(stdout, "BT is not enabled!!");
                startup_flag = BT_ERROR_NOT_ENABLED;
        }
    }
}

/**
 * @function		utc_bluetooth_gatt_positive_cleanup
 * @description 	check If bluetooth is supported and LE is supported, release all the bluetooth resources.
 * @parameter		NA
 * @return			NA
 */
void utc_bluetooth_gatt_positive_cleanup(void)
{
    if(bt_supported)
        bt_deinitialize();
}

/**
 * @testcase		utc_bluetooth_bt_gatt_set_connection_state_changed_cb_p
 * @since_tizen		2.3
 * @description 	check if bluetooth LE is supported and startup_flag is asserted then register a callback for change
 *				in LE connection state and checked for errors.
 * scenario 		Registers a callback function that will be invoked when the LE connection state is changed.
 */
int utc_bluetooth_bt_gatt_set_connection_state_changed_cb_p(void)
{
    if(gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_gatt_set_connection_state_changed_cb(gatt_connection_state_changed_cb_p, NULL);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_gatt_set_connection_state_changed_cb(gatt_connection_state_changed_cb_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_unset_connection_state_changed_cb_p
 * @since_tizen		2.3
 * @description 	check if bluetooth LE is supported and startup_flag is asserted then the callback is unregistered for change
 *				in LE connection state and checked for errors.
 * scenario 		Unregisters a callback function that will be invoked when the connection state is changed.
 */
int utc_bluetooth_bt_gatt_unset_connection_state_changed_cb_p(void)
{
    if(gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_gatt_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_gatt_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_destroy_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted then the GATT service handle is destroyed
 *				and checked for errors.
 * scenario 		Call to destroy GATT service handle.
 */
int utc_bluetooth_bt_gatt_service_destroy_p(void)
{
	bt_gatt_h service = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

	if (gatt_client_supported || gatt_server_supported) {
		assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_create(service_uuid, service_type, &service);
		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_destroy(service);
		assert_eq(ret, BT_ERROR_NONE);
	} else {
		ret = bt_gatt_service_destroy(service);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_destroy_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted then the GATT characteristic handle is destroyed
 *				and checked for errors.
 * scenario 		Call to destroy GATT characteristic handle.
 */
int utc_bluetooth_bt_gatt_characteristic_destroy_p(void)
{
	bt_gatt_h characteristic = NULL;
	char *char_uuid = "2a19"; /* Battery Level */
	char char_value[1] = {80}; /* 80% */
	bt_gatt_property_e properties = BT_GATT_PROPERTY_READ | BT_GATT_PROPERTY_NOTIFY;
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ;

    if (gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_gatt_characteristic_create(char_uuid, permissions, properties, char_value, sizeof(char_value), &characteristic);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_destroy(characteristic);
		assert_eq(ret, BT_ERROR_NONE);
    } else {
		ret = bt_gatt_characteristic_destroy(characteristic);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_descriptor_destroy_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted then the GATT descriptor handle is destroyed
 *				and checked for errors.
 * scenario 		Call to destroy GATT descriptor handle.
 */
int utc_bluetooth_bt_gatt_descriptor_destroy_p(void)
{
	bt_gatt_h descriptor = NULL;
	char *desc_uuid = "2902";
	char desc_value[2] = {0, 0}; /* Notification & Indication */
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ | BT_GATT_PERMISSION_WRITE;

    if (gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_descriptor_create(desc_uuid, permissions, desc_value, sizeof(desc_value), &descriptor);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_descriptor_destroy(descriptor);
		assert_eq(ret, BT_ERROR_NONE);
    } else {
		ret = bt_gatt_descriptor_destroy(descriptor);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_get_permissions_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted. If yes, create characteristic's handle and get characteristic's permission then ensure there is no error.
 *              And then, destroy the characteristic's handle.
 *				Else, get characteristic's permission and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_characteristic_get_permissions and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_characteristic_get_permissions_p(void)
{
	bt_gatt_h characteristic = NULL;
	char *char_uuid = "2a19"; /* Battery Level */
	char char_value[1] = {80}; /* 80% */
	bt_gatt_property_e properties = BT_GATT_PROPERTY_READ | BT_GATT_PROPERTY_NOTIFY;
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ;

    if (gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_create(char_uuid, permissions, properties, char_value, sizeof(char_value), &characteristic);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_get_permissions(characteristic, &permissions);
		if (ret != BT_ERROR_NONE)
			bt_gatt_characteristic_destroy(characteristic);

		assert_eq(ret, BT_ERROR_NONE);
		bt_gatt_characteristic_destroy(characteristic);
    } else {
		ret = bt_gatt_characteristic_get_permissions(characteristic, &permissions);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_descriptor_get_permissions_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted. If yes, create descriptor's handle and get descriptor's permission then ensure there is no error.
 *              And then, destroy the descriptor's handle.
 *				Else, get descriptor's permission and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_descriptor_get_permissions and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_descriptor_get_permissions_p(void)
{
	bt_gatt_h descriptor = NULL;
	char *desc_uuid = "2902";
	char desc_value[2] = {0, 0}; /* Notification & Indication */
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ | BT_GATT_PERMISSION_WRITE;

    if (gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_descriptor_create(desc_uuid, permissions, desc_value, sizeof(desc_value), &descriptor);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_descriptor_get_permissions(descriptor, &permissions);
		if (ret != BT_ERROR_NONE)
			bt_gatt_descriptor_destroy(descriptor);

		assert_eq(ret, BT_ERROR_NONE);
		bt_gatt_descriptor_destroy(descriptor);
    } else {
		ret = bt_gatt_descriptor_get_permissions(descriptor, &permissions);
		assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_create_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted then the GATT service is created
 *				for specific UUID/type and checked for errors.
 * scenario 		Create the GATT service for specific UUID and service type.
 */
int utc_bluetooth_bt_gatt_service_create_p(void)
{
	bt_gatt_h service = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

    if (gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_gatt_service_create(service_uuid, service_type, &service);
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_service_destroy(service);
    } else {
		ret = bt_gatt_service_create(service_uuid, service_type, &service);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_add_characteristic_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted. If yes, create GATT service handle and characteristic handle.
 *              Then, add the characteristic's handle to serivce's handle and ensure there is no error.
 *				Else, add the characteristic's handle to serivce's handle and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_service_add_characteristic and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_service_add_characteristic_p(void)
{
	bt_gatt_h service = NULL;
	bt_gatt_h characteristic = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	char *char_uuid = "2a19"; /* Battery Level */
	char char_value[1] = {80}; /* 80% */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;
	bt_gatt_property_e properties = BT_GATT_PROPERTY_READ | BT_GATT_PROPERTY_NOTIFY;
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_service_create(service_uuid, service_type, &service);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_create(char_uuid, permissions, properties, char_value, sizeof(char_value), &characteristic);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_add_characteristic(service, characteristic);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_characteristic_destroy(characteristic);
			bt_gatt_service_destroy(service);
		}
		assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_characteristic_destroy(characteristic);
		bt_gatt_service_destroy(service);
    } else {
		ret = bt_gatt_service_add_characteristic(service, characteristic);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_add_included_service_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted. If yes, create GATT service handle and included service handle.
 *              Then, add the included service handle to service handle and ensure there is no error.
 *				Else, add the included service handle to service handle and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_service_add_included_service and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_service_add_included_service_p(void)
{
	bt_gatt_h service = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

	bt_gatt_h included_service = NULL;
	char *included_service_uuid = "180d"; /* Heart Rate Service */
	bt_gatt_service_type_e included_service_type = BT_GATT_SERVICE_TYPE_SECONDARY;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_gatt_service_create(service_uuid, service_type, &service);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_create(included_service_uuid, included_service_type, &included_service);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_add_included_service(service, included_service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_service_destroy(included_service);
		}
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_service_destroy(service);
		bt_gatt_service_destroy(included_service);
    } else {
		ret = bt_gatt_service_add_included_service(service, included_service);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_service_get_server_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted.
 *					If yes, create GATT server's handle and GATT service. Then, register service to server and get server from service and ensure there is no error.
 *					Else, get GATT server handle from service and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_service_get_server on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_service_get_server_p(void)
{
	bt_gatt_server_h server = NULL;
	bt_gatt_server_h get_server = NULL;
	bt_gatt_h service = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_create(&server);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_create(service_uuid, service_type, &service);
		if (ret != BT_ERROR_NONE)
			bt_gatt_server_destroy(server);

        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_register_service(server, service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_get_server(service, &get_server);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_service_destroy(service);
		bt_gatt_server_destroy(server);
		bt_gatt_server_deinitialize();
    } else {
		ret = bt_gatt_service_get_server(service, &get_server);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_create_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted then the GATT characteristic is created
 *				for specific UUID/property and checked for errors.
 * scenario 		Create the GATT characteristic for specific UUID and property.
 */
int utc_bluetooth_bt_gatt_characteristic_create_p(void)
{
	bt_gatt_h characteristic = NULL;
	char *char_uuid = "2a19"; /* Battery Level */
	char char_value[1] = {80}; /* 80% */
	bt_gatt_property_e properties = BT_GATT_PROPERTY_READ | BT_GATT_PROPERTY_NOTIFY;
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ;

    if (gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_gatt_characteristic_create(char_uuid, permissions, properties, char_value, sizeof(char_value), &characteristic);
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_characteristic_destroy(characteristic);
    } else {
		ret = bt_gatt_characteristic_create(char_uuid, permissions, properties, char_value, sizeof(char_value), &characteristic);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_characteristic_add_descriptor_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted. If yes, create GATT characteristic's handle and descriptor's handle.
 *              Then, add the descriptor's handle to characteristic's handle and ensure there is no error.
 *				Else, add the descriptor's handle to characteristic's handle and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_characteristic_add_descriptor and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_characteristic_add_descriptor_p(void)
{
	bt_gatt_h characteristic = NULL;
	bt_gatt_h descriptor = NULL;
	char *char_uuid = "2a19"; /* Battery Level */
	char *desc_uuid = "2902";
	char char_value[1] = {80}; /* 80% */
	char desc_value[2] = {0, 0}; /* Notification & Indication */
	bt_gatt_property_e properties = BT_GATT_PROPERTY_READ | BT_GATT_PROPERTY_NOTIFY;
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_create(char_uuid, permissions, properties, char_value, sizeof(char_value), &characteristic);
        assert_eq(ret, BT_ERROR_NONE);

		permissions = BT_GATT_PERMISSION_READ | BT_GATT_PERMISSION_WRITE;
		ret = bt_gatt_descriptor_create(desc_uuid, permissions, desc_value, sizeof(desc_value), &descriptor);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_characteristic_add_descriptor(characteristic, descriptor);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_descriptor_destroy(descriptor);
			bt_gatt_characteristic_destroy(characteristic);
		}
		assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_descriptor_destroy(descriptor);
		bt_gatt_characteristic_destroy(characteristic);
    } else {
		ret = bt_gatt_characteristic_add_descriptor(characteristic, descriptor);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_descriptor_create_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted then the GATT descriptor is created
 *				for specific UUID/permissions and checked for errors.
 * scenario 		Create the GATT descriptor for specific UUID and permissions.
 */
int utc_bluetooth_bt_gatt_descriptor_create_p(void)
{
	bt_gatt_h descriptor = NULL;
	char *desc_uuid = "2902";
	char desc_value[2] = {0, 0}; /* Notification & Indication */
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ | BT_GATT_PERMISSION_WRITE;

    if (gatt_client_supported || gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_gatt_descriptor_create(desc_uuid, permissions, desc_value, sizeof(desc_value), &descriptor);
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_descriptor_destroy(descriptor);
    } else {
        ret = bt_gatt_descriptor_create(desc_uuid, permissions, desc_value, sizeof(desc_value), &descriptor);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_initialize_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted. If yes, deinitialize the GATT server and initialize the GATT server and ensure there is no error.
 *				Else, initialize the GATT server and verify the result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_initialize on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_initialize_p(void)
{
    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_deinitialize_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted. If yes, deinitialize the GATT server and ensure there is no error.
 *				Else, deinitialize the GATT server and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_deinitialize on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_deinitialize_p(void)
{
    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_deinitialize();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
		ret = bt_gatt_server_deinitialize();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_create_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted. If yes, create GATT server's handle and ensure there is no error.
 *				Else, create GATT server's handle and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_create on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_create_p(void)
{
	bt_gatt_server_h server = NULL;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_create(&server);
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_server_destroy(server);
    } else {
		ret = bt_gatt_server_create(&server);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_destroy_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted. If yes, create GATT server's handle and destroy GATT server's handle then ensure there is no error.
 *				Else, destroy GATT server's handle and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_destroy on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_destroy_p(void)
{
	bt_gatt_server_h server = NULL;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_create(&server);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_destroy(server);
        assert_eq(ret, BT_ERROR_NONE);
    } else {
		ret = bt_gatt_server_destroy(server);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_set_read_value_requested_cb_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted.
 *					If yes, create GATT characteristic handle. Then, register a callback function to invoked when a read request
 *						for a specified characteristic is issued and ensure there is no error.
 *					Else, register a callback function and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_set_read_value_requested_cb on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_set_read_value_requested_cb_p(void)
{
	bt_gatt_h characteristic = NULL;
	char *char_uuid = "2a19"; /* Battery Level */
	char char_value[1] = {80}; /* 80% */
	bt_gatt_property_e properties = BT_GATT_PROPERTY_READ | BT_GATT_PROPERTY_NOTIFY;
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_gatt_characteristic_create(char_uuid, permissions, properties, char_value, sizeof(char_value), &characteristic);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_set_read_value_requested_cb(characteristic, __bt_gatt_server_read_value_requested_cb_p, NULL);
		if (ret != BT_ERROR_NONE)
			bt_gatt_characteristic_destroy(characteristic);

		assert_eq(ret, BT_ERROR_NONE);
		bt_gatt_characteristic_destroy(characteristic);
		bt_gatt_server_deinitialize();
    } else {
		ret = bt_gatt_server_set_read_value_requested_cb(characteristic, __bt_gatt_server_read_value_requested_cb_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_set_characteristic_notification_state_change_cb_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted.
 *					If yes, create GATT characteristic handle. Then, register a callback function to invoked when the remote device
 *						enables or disables the Notification/Indication for particular characteristics and ensure there is no error.
 *					Else, register a callback function and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_set_characteristic_notification_state_change_cb on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_set_characteristic_notification_state_change_cb_p(void)
{
	bt_gatt_h characteristic = NULL;
	char *char_uuid = "2a19"; /* Battery Level */
	char char_value[1] = {80}; /* 80% */
	bt_gatt_property_e properties = BT_GATT_PROPERTY_READ | BT_GATT_PROPERTY_NOTIFY;
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_gatt_characteristic_create(char_uuid, permissions, properties, char_value, sizeof(char_value), &characteristic);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_set_characteristic_notification_state_change_cb(characteristic, __bt_gatt_server_notification_state_change_cb_p, NULL);
		if (ret != BT_ERROR_NONE)
			bt_gatt_characteristic_destroy(characteristic);

		assert_eq(ret, BT_ERROR_NONE);
		bt_gatt_characteristic_destroy(characteristic);
		bt_gatt_server_deinitialize();
    } else {
		ret = bt_gatt_server_set_characteristic_notification_state_change_cb(characteristic, __bt_gatt_server_notification_state_change_cb_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_set_write_value_requested_cb_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted.
 *					If yes, create GATT characteristic handle. Then, register a callback function to invoked when a value of
 *						characteristic has been changed cnd ensure there is no error.
 *					Else, register a callback function and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_set_write_value_requested_cb on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_set_write_value_requested_cb_p(void)
{
	bt_gatt_h characteristic = NULL;
	char *char_uuid = "2a19"; /* Battery Level */
	char char_value[1] = {80}; /* 80% */
	bt_gatt_property_e properties = BT_GATT_PROPERTY_READ | BT_GATT_PROPERTY_NOTIFY;
	bt_gatt_permission_e permissions = BT_GATT_PERMISSION_READ;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_gatt_characteristic_create(char_uuid, permissions, properties, char_value, sizeof(char_value), &characteristic);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_set_write_value_requested_cb(characteristic, __bt_gatt_server_write_value_requested_cb_p, NULL);
		if (ret != BT_ERROR_NONE)
			bt_gatt_characteristic_destroy(characteristic);

		assert_eq(ret, BT_ERROR_NONE);
		bt_gatt_characteristic_destroy(characteristic);
		bt_gatt_server_deinitialize();
    } else {
		ret = bt_gatt_server_set_write_value_requested_cb(characteristic, __bt_gatt_server_write_value_requested_cb_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_get_service_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted.
 *					If yes, create GATT server's handle and GATT service. Then, register service to server and get service from servere and ensure there is no error.
 *					Else, get GATT service handle from server and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_get_service on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_get_service_p(void)
{
	bt_gatt_server_h server = NULL;
	bt_gatt_server_h get_server = NULL;
	bt_gatt_h service = NULL;
	bt_gatt_h get_service = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_create(&server);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_create(service_uuid, service_type, &service);
		if (ret != BT_ERROR_NONE)
			bt_gatt_server_destroy(server);

        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_register_service(server, service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_get_service(server, service_uuid, &get_service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_service_destroy(service);
		bt_gatt_server_destroy(server);
		bt_gatt_server_deinitialize();
    } else {
		ret = bt_gatt_server_get_service(server, service_uuid, &get_service);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_foreach_services_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted.
 *					If yes, create GATT server's handle and GATT service. 
 *						Then, register service to server and invokes a callback function on each service that belongs to the GATT server and ensure there is no error.
 *					Else, invokes a callback function on each service and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_foreach_services on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_foreach_services_p(void)
{
	bt_gatt_server_h server = NULL;
	bt_gatt_server_h get_server = NULL;
	bt_gatt_h service = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_create(&server);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_create(service_uuid, service_type, &service);
		if (ret != BT_ERROR_NONE)
			bt_gatt_server_destroy(server);

        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_register_service(server, service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_foreach_services(server, __bt_gatt_server_foreach_svc_cb_p, NULL);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_service_destroy(service);
		bt_gatt_server_destroy(server);
		bt_gatt_server_deinitialize();
    } else {
		ret = bt_gatt_server_foreach_services(server, __bt_gatt_server_foreach_svc_cb_p, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_register_service_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted.
 *					If yes, create GATT server's handle and GATT service. Then, register service to server and ensure there is no error.
 *					Else, register service to server and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_register_service on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_register_service_p(void)
{
	bt_gatt_server_h server = NULL;

	bt_gatt_h service = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_create(&server);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_create(service_uuid, service_type, &service);
		if (ret != BT_ERROR_NONE)
			bt_gatt_server_destroy(server);

        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_register_service(server, service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_service_destroy(service);
		bt_gatt_server_destroy(server);
		bt_gatt_server_deinitialize();
    } else {
		ret = bt_gatt_server_register_service(server, service);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_unregister_service_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted.
 *					If yes, create GATT server's handle and GATT service. Then, register service to server and unregister service and ensure there is no error.
 *					Else, unregister service from server and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_unregister_service on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_unregister_service_p(void)
{
	bt_gatt_server_h server = NULL;

	bt_gatt_h service = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_create(&server);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_create(service_uuid, service_type, &service);
		if (ret != BT_ERROR_NONE)
			bt_gatt_server_destroy(server);

        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_register_service(server, service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_unregister_service(server, service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_service_destroy(service);
		bt_gatt_server_destroy(server);
		bt_gatt_server_deinitialize();
    } else {
		ret = bt_gatt_server_unregister_service(server, service);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_unregister_all_services_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted.
 *					If yes, create GATT server's handle and GATT service. Then, register service to server and unregister all services and ensure there is no error.
 *					Else, unregister services from server and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_unregister_all_services on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_unregister_all_services_p(void)
{
	bt_gatt_server_h server = NULL;

	bt_gatt_h service = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_create(&server);
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_create(service_uuid, service_type, &service);
		if (ret != BT_ERROR_NONE)
			bt_gatt_server_destroy(server);

        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_register_service(server, service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_unregister_all_services(server);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
		}
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_service_destroy(service);
		bt_gatt_server_destroy(server);
		bt_gatt_server_deinitialize();
    } else {
		ret = bt_gatt_server_unregister_all_services(server);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_gatt_server_start_p
 * @since_tizen		3.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted.
 *					If yes, create GATT server's handle and GATT service. Then, register service to server and start server and ensure there is no error.
 *					Else, start server and verify result as BT_ERROR_NOT_SUPPORTED.
 * scenario 		Check if bluetooth LE is supported and startup_flag is asserted. Then, call bt_gatt_server_start on the device and check for BT_ERROR_NOE.
 */
int utc_bluetooth_bt_gatt_server_start_p(void)
{
	bt_gatt_server_h server = NULL;

	bt_gatt_h service = NULL;
	char *service_uuid = "180f"; /* Battery Service */
	bt_gatt_service_type_e service_type = BT_GATT_SERVICE_TYPE_PRIMARY;

    if (gatt_server_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_server_initialize();
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_create(&server);
		if (ret != BT_ERROR_NONE)
			bt_gatt_server_deinitialize();

		assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_service_create(service_uuid, service_type, &service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_server_destroy(server);
			bt_gatt_server_deinitialize();
		}
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_register_service(server, service);
		if (ret != BT_ERROR_NONE) {
			bt_gatt_service_destroy(service);
			bt_gatt_server_destroy(server);
			bt_gatt_server_deinitialize();
		}
        assert_eq(ret, BT_ERROR_NONE);

		ret = bt_gatt_server_start();
        assert_eq(ret, BT_ERROR_NONE);

		bt_gatt_service_destroy(service);
		bt_gatt_server_destroy(server);
		bt_gatt_server_deinitialize();
    } else {
		ret = bt_gatt_server_start();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_ipsp_set_connection_state_changed_cb_p
 * @since_tizen	4.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted then register a callback for change
 *				in IPSP connection state and checked for errors.
 * scenario 		Registers a callback function that will be invoked when the IPSP connection state is changed.
 */
int utc_bluetooth_bt_ipsp_set_connection_state_changed_cb_p(void)
{
    if (ipsp_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_ipsp_set_connection_state_changed_cb(__bt_ipsp_connection_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_ipsp_unset_connection_state_changed_cb();
    } else {
        ret = bt_ipsp_set_connection_state_changed_cb(__bt_ipsp_connection_state_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_bluetooth_bt_ipsp_unset_connection_state_changed_cb_p
 * @since_tizen	4.0
 * @description 	check if bluetooth LE is supported and startup_flag is asserted then the callback is unregistered for change
 *				in IPSP connection state and checked for errors.
 * scenario 		Unregisters a callback function that will be invoked when the IPSP connection state is changed.
 */
int utc_bluetooth_bt_ipsp_unset_connection_state_changed_cb_p(void)
{
    if (ipsp_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

        ret = bt_ipsp_set_connection_state_changed_cb(__bt_ipsp_connection_state_changed_cb, NULL);

        ret = bt_ipsp_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_ipsp_unset_connection_state_changed_cb();
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

int utc_bluetooth_bt_gatt_client_set_att_mtu_changed_cb_p(void)
{
	bt_gatt_client_h client = NULL;
	static const char *remote_addr = "E4:32:CB:41:1F:A6";

    if (gatt_client_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_client_create(remote_addr, &client);
		assert_eq(ret, BT_ERROR_NONE);

        ret = bt_gatt_client_set_att_mtu_changed_cb(client, __bt_gatt_client_att_mtu_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NONE);

        ret = bt_gatt_client_unset_att_mtu_changed_cb(client);

		bt_gatt_client_destroy(client);
    } else {
        ret = bt_gatt_client_set_att_mtu_changed_cb(client, __bt_gatt_client_att_mtu_changed_cb, NULL);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

int utc_bluetooth_bt_gatt_client_unset_att_mtu_changed_cb_p(void)
{
	bt_gatt_client_h client = NULL;
	static const char *remote_addr = "E4:32:CB:41:1F:A6";

    if (gatt_client_supported) {
        assert_eq(startup_flag, BT_ERROR_NONE);

		ret = bt_gatt_client_create(remote_addr, &client);
		assert_eq(ret, BT_ERROR_NONE);

        ret = bt_gatt_client_set_att_mtu_changed_cb(client, __bt_gatt_client_att_mtu_changed_cb, NULL);

        ret = bt_gatt_client_unset_att_mtu_changed_cb(client);
		bt_gatt_client_destroy(client);

        assert_eq(ret, BT_ERROR_NONE);
    } else {
        ret = bt_gatt_client_unset_att_mtu_changed_cb(client);
        assert_eq(ret, BT_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

