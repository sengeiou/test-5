//
// Copyright (c) 2018 - 2021 Samsung Electronics Co., Ltd.
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

#include <app_manager.h>
#include <dlog.h>
#include <linux/limits.h>
#include <rpc-port-parcel.h>
#include <rpc-port.h>
#include <service_app.h>
#include <stdio.h>

#include "assert.h"
#include "tct_app_common.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "NativeTCT"

#define normal_exit(result) do { \
	__result = result; \
	service_app_exit(); \
} while (0)

enum Message_method_e {
	Message_METHOD_Result,
	Message_METHOD_Callback,
	Message_METHOD_Send,
};


static const char __service_app_id[] = "org.example.stubsample";
static const char __invalid_cert_service_app_id[] = "org.example.invalidcertstub";
static const char __invalid_privilege_service_app_id[] = "org.example.invalidprivilegestub";
static const char __proxy_app_id[] = "org.example.proxyrpcport";

static const char __port_name[] = "Message";
static const char __port_name_for_stubtest[] = "Message2";

static char __disconnecttest[] = "disconnecttest";
static char __receivetest[] = "receivetest";
static char __porttest[] = "porttest";

static char __proxygetporttest[] = "proxygetporttest";
static char __stubgetporttest[] = "stubgetporttest";

int __result;

static rpc_port_proxy_h proxy_handle;
static rpc_port_stub_h stub_handle;
static rpc_port_h received_port;

int return_value_for_rpc_port_read_p;
int return_value_for_rpc_port_write_p;

static bool touch_connected_event_cb;
static int return_value_for_rpc_port_set_private_sharing_array_p;
static int return_value_for_rpc_port_set_private_sharing_p;
static int return_value_for_rpc_port_unset_private_sharing_p;
static char *data_path;

void __run_proxy_app() {
	bool is_running = false;
	int counter = 30;
	app_control_h ac;
	int ret = app_control_create(&ac);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_control_create error");
		__result = 1;
		service_app_exit();
		return;
	}

	ret = app_control_set_app_id(ac, __proxy_app_id);
	if (ret != APP_CONTROL_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_control_set_app_id error ");
		__result = 1;
		service_app_exit();
		return;
	}

	do {
		ret = app_control_send_launch_request(ac, NULL, NULL);
		if (ret != APP_CONTROL_ERROR_NONE)
			sleep(1);
		app_manager_is_running(__proxy_app_id, &is_running);
	} while (--counter > 0 && !is_running);
	sleep(1);
}

static void __Message_on_connected(const char *endpoint, const char *port_name, rpc_port_h port, void *data)
{
	if (data == __disconnecttest) {
		rpc_port_parcel_h parcel;
		dlog_print(DLOG_INFO, LOG_TAG, "%s connected to test disconnect", endpoint);

		rpc_port_parcel_create(&parcel);
		rpc_port_parcel_write_int32(parcel, Message_METHOD_Send);
		rpc_port_parcel_write_string(parcel, "disconnect");

		rpc_port_parcel_send(parcel, port);
		rpc_port_parcel_destroy(parcel);
		return;

	} else if (data == __receivetest) {
		received_port = port;
		rpc_port_parcel_h parcel;
		dlog_print(DLOG_INFO, LOG_TAG, "%s connected to test receive data", endpoint);

		rpc_port_parcel_create(&parcel);
		rpc_port_parcel_write_int32(parcel, Message_METHOD_Send);
		rpc_port_parcel_write_string(parcel, "receive");

		rpc_port_parcel_send(parcel, port);
		rpc_port_parcel_destroy(parcel);
		return;

	} else if (data == __porttest) {
		received_port = port;
		rpc_port_parcel_h parcel;
		dlog_print(DLOG_INFO, LOG_TAG, "%s connected to test port read and write", endpoint);

		rpc_port_parcel_create(&parcel);
		rpc_port_parcel_write_int32(parcel, Message_METHOD_Send);
		rpc_port_parcel_write_string(parcel, "write");

		return_value_for_rpc_port_write_p = rpc_port_parcel_send(parcel, port);
		rpc_port_parcel_destroy(parcel);
		return;
	} else if (data == __proxygetporttest) {
		rpc_port_h callback_port;
		int ret;

		ret = rpc_port_proxy_get_port(proxy_handle, RPC_PORT_PORT_CALLBACK, &callback_port);
		if (ret != RPC_PORT_ERROR_NONE) {
			dlog_print(DLOG_INFO, LOG_TAG, "rpc_port_proxy_get_port failed");
			normal_exit(1);
			return;
		} else {
			normal_exit(0);
			return;
		}
	}

	dlog_print(DLOG_INFO, LOG_TAG, "%s connected", endpoint);
	if (strcmp(endpoint, __service_app_id)) {
		normal_exit(1);
		return;
	}

	normal_exit(0);
}

static void __Message_on_disconnected(const char *endpoint, const char *port_name, void *data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "%s disconnected", endpoint);
	if (strcmp(endpoint, __service_app_id)) {
		normal_exit(1);
		return;
	}

	normal_exit(0);
}

static void __Message_on_rejected(const char *endpoint, const char *port_name, void *data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "%s rejected", endpoint);
	if (!strcmp(endpoint, __invalid_cert_service_app_id)) {
		normal_exit(0);
		return;
	}

	if (!strcmp(endpoint, __invalid_privilege_service_app_id)) {
		normal_exit(0);
		return;
	}

	normal_exit(1);
}

static void __Message_on_received(const char *endpoint, const char *port_name, void *data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "%s received", endpoint);
	if (strcmp(endpoint, __service_app_id)) {
		normal_exit(1);
		return;
	}

	int ret = -1;
	rpc_port_parcel_h parcel_received;
	rpc_port_h callback_port;

	rpc_port_proxy_get_port(proxy_handle, RPC_PORT_PORT_CALLBACK, &callback_port);

	return_value_for_rpc_port_read_p = rpc_port_parcel_create_from_port(&parcel_received, callback_port);
	rpc_port_parcel_read_int32(parcel_received, &ret);
	if (ret != 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Invalid protocol");
		rpc_port_parcel_destroy(parcel_received);
		return;
	}

	rpc_port_parcel_destroy(parcel_received);
	dlog_print(DLOG_INFO, LOG_TAG, "endpoint(%s), port_name(%s)", endpoint, port_name);

	if (data == __porttest &&
			return_value_for_rpc_port_read_p != RPC_PORT_ERROR_NONE) {
		dlog_print(DLOG_INFO, LOG_TAG, "rpc_port_read_p(%d)", return_value_for_rpc_port_read_p);
		normal_exit(1);
		return;
	}

	normal_exit(0);
}

static void __Message_on_connected_stub(const char *sender, const char *instance, void *data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "%s connected", sender);

	if (data == __stubgetporttest) {
		rpc_port_h callback_port;
		int ret;

		ret = rpc_port_stub_get_port(stub_handle, RPC_PORT_PORT_CALLBACK, instance, &callback_port);
		if (ret != RPC_PORT_ERROR_NONE) {
			dlog_print(DLOG_INFO, LOG_TAG, "rpc_port_stub_get_port failed");
			normal_exit(1);
			return;
		} else {
			normal_exit(0);
			return;
		}
	} else if (data == __disconnecttest) {
		int ret;

		ret = rpc_port_stub_get_port(stub_handle, RPC_PORT_PORT_CALLBACK, instance, &received_port);
		if (ret != RPC_PORT_ERROR_NONE) {
			dlog_print(DLOG_INFO, LOG_TAG, "rpc_port_stub_get_port failed");
			normal_exit(1);
			return;
		}
		ret = rpc_port_disconnect(received_port);
		if (ret != RPC_PORT_ERROR_NONE) {
			normal_exit(1);
			return;
		}
	}

	if (strcmp(sender, __proxy_app_id)) {
		normal_exit(1);
	}

	return;
}

static void __Message_on_disconnected_stub(const char *sender, const char *instance, void *data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "%s disconnected", sender);
	if (strcmp(sender, __proxy_app_id)) {
		normal_exit(1);
		return;
	}

	normal_exit(0);
}

static int __Message_on_received_stub(const char *sender, const char *instance, rpc_port_h port, void *data)
{
	dlog_print(DLOG_INFO, LOG_TAG, "%s received", sender);
	if (strcmp(sender, __proxy_app_id)) {
		normal_exit(1);
		return 0;
	}

	rpc_port_parcel_h parcel_received;
	int ret = -1;
	int rep = 0;
	char *msg = NULL;


	if (data == __disconnecttest) {
		rep = -1;
	}

	rpc_port_parcel_create_from_port(&parcel_received, port);
	rpc_port_parcel_read_int32(parcel_received, &ret);
	rpc_port_parcel_read_string(parcel_received, &msg);
	if (ret != Message_METHOD_Send) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Invalid protocol");
		rpc_port_parcel_destroy(parcel_received);
		normal_exit(1);
		return 0;
	}

	dlog_print(DLOG_ERROR, LOG_TAG, "msg from %s : %s", sender, msg);
	rpc_port_parcel_destroy(parcel_received);

	rpc_port_parcel_h parcel;
	rpc_port_parcel_create(&parcel);
	rpc_port_parcel_write_int32(parcel, Message_METHOD_Result);
	rpc_port_parcel_write_int32(parcel, rep);
	rpc_port_parcel_send(parcel, port);
	rpc_port_parcel_destroy(parcel);

	if (data == __disconnecttest) {
		return 0;
	}

	normal_exit(0);
	return 0;
}

void utc_rpc_port_proxy_startup(void)
{
	rpc_port_proxy_create(&proxy_handle);
}

static void __get_file_path(const char *file_name, char *buf, unsigned int size)
{
	if (!data_path)
		data_path = app_get_data_path();

	snprintf(buf, size, "%s%s", data_path, file_name);
}

static void __delete_file(const char *path)
{
	int ret;

	ret = access(path, F_OK);
	if (ret != 0)
		return;

	ret = unlink(path);
	if (ret != 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "unlink() is failed. errno(%d)",
				errno);
	}
}

void utc_rpc_port_proxy_cleanup(void)
{
	char path[PATH_MAX];

	if (proxy_handle)
		rpc_port_proxy_destroy(proxy_handle);

	__get_file_path("file_name1.txt", path, sizeof(path));
	__delete_file(path);
	__get_file_path("file_name2.txt", path, sizeof(path));
	__delete_file(path);
	__get_file_path("file_name.txt", path, sizeof(path));
	__delete_file(path);

	free(data_path);
	data_path = NULL;
}

void utc_rpc_port_stub_startup(void)
{
	rpc_port_stub_create(&stub_handle, __port_name_for_stubtest);
}

void utc_rpc_port_stub_cleanup(void)
{
	if (stub_handle) {
		rpc_port_stub_destroy(stub_handle);
	}
}

/**
 * @function    utc_rpc_port_proxy_create_p
 * @since_tizen 4.0
 * @description Creates the rpc port proxy handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_proxy_create_p(void)
{
	int ret;
	rpc_port_proxy_h _h;

	ret = rpc_port_proxy_create(&_h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	rpc_port_proxy_destroy(_h);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_create_n
 * @since_tizen 4.0
 * @description Creates the rpc port proxy handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_create_n(void)
{
	int ret;

	ret = rpc_port_proxy_create(NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_destroy_p
 * @since_tizen 4.0
 * @description Destroys the rpc port proxy handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_proxy_destroy_p(void)
{
	int ret;
	rpc_port_proxy_h _h;

	ret = rpc_port_proxy_create(&_h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_destroy(_h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_destroy_n
 * @since_tizen 4.0
 * @description Destroys the rpc port proxy handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_destroy_n(void)
{
	int ret;

	ret = rpc_port_proxy_destroy(NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_connect_p
 * @since_tizen 4.0
 * @description Connects to rpc port.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if connected callback is called.
 */
int utc_rpc_port_proxy_connect_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __Message_on_connected, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

    return 1;
}

/**
 * @function    utc_rpc_port_proxy_connect_n
 * @since_tizen 4.0
 * @description Connects the rpc port.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_connect_n(void)
{
	int ret;

	ret = rpc_port_proxy_connect(NULL, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_add_connected_event_cb_p
 * @since_tizen 4.0
 * @description Adds connected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if connected callback is called.
 */
int utc_rpc_port_proxy_add_connected_event_cb_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __Message_on_connected, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

    return 1;
}

/**
 * @function    utc_rpc_port_proxy_add_connected_event_cb_n1
 * @since_tizen 4.0
 * @description Adds connected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_add_connected_event_cb_n1(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(NULL, __Message_on_connected, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_add_connected_event_cb_n2
 * @since_tizen 4.0
 * @description Adds connected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_add_connected_event_cb_n2(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_add_disconnected_event_cb_p
 * @since_tizen 4.0
 * @description Adds disconnected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if disconnected callback is called.
 */
int utc_rpc_port_proxy_add_disconnected_event_cb_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __Message_on_connected, __disconnecttest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_add_disconnected_event_cb(proxy_handle, __Message_on_disconnected, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

    return 1;
}

/**
 * @function    utc_rpc_port_proxy_add_disconnected_event_cb_n1
 * @since_tizen 4.0
 * @description Adds disconnected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_add_disconnected_event_cb_n1(void)
{
	int ret;

	ret = rpc_port_proxy_add_disconnected_event_cb(NULL, __Message_on_disconnected, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_add_disconnected_event_cb_n2
 * @since_tizen 4.0
 * @description Adds disconnected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_add_disconnected_event_cb_n2(void)
{
	int ret;

	ret = rpc_port_proxy_add_disconnected_event_cb(proxy_handle, NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_add_rejected_event_cb_p1
 * @since_tizen 4.0
 * @description Adds rejected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if rejected callback is called.
 */
int utc_rpc_port_proxy_add_rejected_event_cb_p1(void)
{
	int ret;

	ret = rpc_port_proxy_add_rejected_event_cb(proxy_handle, __Message_on_rejected, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect(proxy_handle, __invalid_cert_service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

    return 1;
}


/**
 * @function    utc_rpc_port_proxy_add_rejected_event_cb_p2
 * @since_tizen 4.0
 * @description Adds rejected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if rejected callback is called.
 */
int utc_rpc_port_proxy_add_rejected_event_cb_p2(void)
{
	int ret;

	ret = rpc_port_proxy_add_rejected_event_cb(proxy_handle, __Message_on_rejected, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect(proxy_handle, __invalid_privilege_service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

    return 1;
}

/**
 * @function    utc_rpc_port_proxy_add_rejected_event_cb_n1
 * @since_tizen 4.0
 * @description Adds rejected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_add_rejected_event_cb_n1(void)
{
	int ret;

	ret = rpc_port_proxy_add_rejected_event_cb(NULL, __Message_on_rejected, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_add_rejected_event_cb_n2
 * @since_tizen 4.0
 * @description Adds rejected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_add_rejected_event_cb_n2(void)
{
	int ret;

	ret = rpc_port_proxy_add_rejected_event_cb(proxy_handle, NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_add_received_event_cb_p
 * @since_tizen 4.0
 * @description Adds received event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if receied callback is called.
 */
int utc_rpc_port_proxy_add_received_event_cb_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __Message_on_connected, __receivetest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_add_received_event_cb(proxy_handle, __Message_on_received, __receivetest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

    return 1;
}

/**
 * @function    utc_rpc_port_proxy_add_received_event_cb_n1
 * @since_tizen 4.0
 * @description Adds receiveed event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_add_received_event_cb_n1(void)
{
	int ret;

	ret = rpc_port_proxy_add_received_event_cb(NULL, __Message_on_received, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_add_received_event_cb_n2
 * @since_tizen 4.0
 * @description Adds received event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_proxy_add_received_event_cb_n2(void)
{
	int ret;

	ret = rpc_port_proxy_add_received_event_cb(proxy_handle, NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_create_p
 * @since_tizen 4.0
 * @description Creates the rpc port stub handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_stub_create_p(void)
{
	int ret;
	rpc_port_stub_h _h;

	ret = rpc_port_stub_create(&_h, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	rpc_port_stub_destroy(_h);
	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_create_n
 * @since_tizen 4.0
 * @description Creates the rpc port stub handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_create_n(void)
{
	int ret;

	ret = rpc_port_stub_create(NULL, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_destroy_p
 * @since_tizen 4.0
 * @description Destroys the rpc port stub handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_stub_destroy_p(void)
{
	int ret;
	rpc_port_stub_h _h;

	ret = rpc_port_stub_create(&_h, "port");
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_destroy(_h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_destroy_n
 * @since_tizen 4.0
 * @description Destroys the rpc port stub handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_destroy_n(void)
{
	int ret;

	ret = rpc_port_stub_destroy(NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_listen_p
 * @since_tizen 4.0
 * @description Listens to rpc port.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_stub_listen_p(void)
{
	int ret;

	ret = rpc_port_stub_listen(stub_handle);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_listen_n
 * @since_tizen 4.0
 * @description Listens the rpc port.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_listen_n(void)
{
	int ret;

	ret = rpc_port_stub_listen(NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_add_privilege_p
 * @since_tizen 4.0
 * @description Adds privilege to rpc port.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_stub_add_privilege_p(void)
{
	int ret;

	ret = rpc_port_stub_add_privilege(stub_handle, "http://tizen.org/alarm.set");
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_add_privilege_n
 * @since_tizen 4.0
 * @description Adds privilege the rpc port.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_add_privilege_n(void)
{
	int ret;

	ret = rpc_port_stub_add_privilege(NULL, "http://tizen.org/alarm.set");
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_set_trusted_p
 * @since_tizen 4.0
 * @description Sets trusted to rpc port.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_stub_set_trusted_p(void)
{
	int ret;

	ret = rpc_port_stub_set_trusted(stub_handle, true);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_set_trusted_n
 * @since_tizen 4.0
 * @description Sets trusted the rpc port.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_set_trusted_n(void)
{
	int ret;

	ret = rpc_port_stub_set_trusted(NULL, true);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_add_connected_event_cb_p
 * @since_tizen 4.0
 * @description Adds connected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if connected callback is called.
 */
int utc_rpc_port_stub_add_connected_event_cb_p(void)
{
	int ret;

	ret = rpc_port_stub_add_connected_event_cb(stub_handle, __Message_on_connected_stub, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_add_received_event_cb(stub_handle, __Message_on_received_stub, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_listen(stub_handle);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	__run_proxy_app();

    return 1;
}

/**
 * @function    utc_rpc_port_stub_add_connected_event_cb_n1
 * @since_tizen 4.0
 * @description Adds connected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_add_connected_event_cb_n1(void)
{
	int ret;

	ret = rpc_port_stub_add_connected_event_cb(NULL, __Message_on_connected_stub, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_add_connected_event_cb_n2
 * @since_tizen 4.0
 * @description Adds connected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_add_connected_event_cb_n2(void)
{
	int ret;

	ret = rpc_port_stub_add_connected_event_cb(stub_handle, NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_add_received_event_cb_p
 * @since_tizen 4.0
 * @description Adds received event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if receied callback is called.
 */
int utc_rpc_port_stub_add_received_event_cb_p(void)
{
	int ret;

	ret = rpc_port_stub_add_connected_event_cb(stub_handle, __Message_on_connected_stub, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_add_received_event_cb(stub_handle, __Message_on_received_stub, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_listen(stub_handle);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	__run_proxy_app();

    return 1;
}

/**
 * @function    utc_rpc_port_stub_add_received_event_cb_n1
 * @since_tizen 4.0
 * @description Adds receiveed event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_add_received_event_cb_n1(void)
{
	int ret;

	ret = rpc_port_stub_add_received_event_cb(NULL, __Message_on_received_stub, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_add_received_event_cb_n2
 * @since_tizen 4.0
 * @description Adds received event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_add_received_event_cb_n2(void)
{
	int ret;

	ret = rpc_port_stub_add_received_event_cb(stub_handle, NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_add_disconnected_event_cb_p
 * @since_tizen 4.0
 * @description Adds disconnected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if disconnected callback is called.
 */
int utc_rpc_port_stub_add_disconnected_event_cb_p(void)
{
	int ret;

	ret = rpc_port_stub_add_connected_event_cb(stub_handle, __Message_on_connected_stub, __disconnecttest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_add_received_event_cb(stub_handle, __Message_on_received_stub, __disconnecttest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_add_disconnected_event_cb(stub_handle, __Message_on_disconnected_stub, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_listen(stub_handle);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	__run_proxy_app();

    return 1;
}

/**
 * @function    utc_rpc_port_stub_add_disconnected_event_cb_n1
 * @since_tizen 4.0
 * @description Adds disconnected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_add_disconnected_event_cb_n1(void)
{
	int ret;

	ret = rpc_port_stub_add_disconnected_event_cb(NULL, __Message_on_disconnected, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_stub_add_disconnected_event_cb_n2
 * @since_tizen 4.0
 * @description Adds disconnected event callback to handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_stub_add_disconnected_event_cb_n2(void)
{
	int ret;

	ret = rpc_port_stub_add_disconnected_event_cb(stub_handle, NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_read_p
 * @since_tizen 4.0
 * @description Reads data from rpc_port handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_read_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __Message_on_connected, __porttest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_add_received_event_cb(proxy_handle, __Message_on_received, __porttest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

    return 1;
}

/**
 * @function    utc_rpc_port_read_n
 * @since_tizen 4.0
 * @description Reads data from rpc_port handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_read_n(void)
{
	int ret;
	char data[] = "read";
	char buf[256];

	ret = rpc_port_read(NULL, buf, sizeof(data));
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_write_p
 * @since_tizen 4.0
 * @description Writes data from rpc_port handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_write_p(void)
{
	assert_eq(return_value_for_rpc_port_write_p, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_write_n
 * @since_tizen 4.0
 * @description Writes data from rpc_port handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_write_n(void)
{
	int ret;
	char data[] = "read";

	ret = rpc_port_write(NULL, data, sizeof(data));
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_proxy_get_port_p
 * @since_tizen 4.0
 * @description Gets a port from proxy handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if connected callback is called.
 */
int utc_rpc_port_proxy_get_port_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __Message_on_connected, __proxygetporttest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

    return 1;
}

/**
 * @function    utc_rpc_port_proxy_get_port_n1
 * @since_tizen 4.0
 * @description Gets a port from proxy handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT
 *              and check if connected callback is called.
 */
int utc_rpc_port_proxy_get_port_n1(void)
{
	int ret;
	rpc_port_h callback_port;

	ret = rpc_port_proxy_get_port(NULL, RPC_PORT_PORT_CALLBACK, &callback_port);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 1;
}

/**
 * @function    utc_rpc_port_proxy_get_port_n2
 * @since_tizen 4.0
 * @description Gets a port from proxy handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT
 *              and check if connected callback is called.
 */
int utc_rpc_port_proxy_get_port_n2(void)
{
	int ret;

	ret = rpc_port_proxy_get_port(proxy_handle, RPC_PORT_PORT_CALLBACK, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 1;
}

/**
 * @function    utc_rpc_port_proxy_stub_port_p
 * @since_tizen 4.0
 * @description Gets a port from stub handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT
 *              and check if connected callback is called.
 */
int utc_rpc_port_stub_get_port_p(void)
{
	int ret;

	ret = rpc_port_stub_add_connected_event_cb(stub_handle, __Message_on_connected_stub, __stubgetporttest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_add_received_event_cb(stub_handle, __Message_on_received_stub, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_listen(stub_handle);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	__run_proxy_app();

    return 1;

}

/**
 * @function    utc_rpc_port_stub_get_port_n1
 * @since_tizen 4.0
 * @description Gets a port from stub handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT
 *              and check if connected callback is called.
 */
int utc_rpc_port_stub_get_port_n1(void)
{
	int ret;
	char *instance = "instance";
	rpc_port_h callback_port;

	ret = rpc_port_stub_get_port(NULL, RPC_PORT_PORT_CALLBACK, instance, &callback_port);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 1;
}

/**
 * @function    utc_rpc_port_stub_get_port_n2
 * @since_tizen 4.0
 * @description Gets a port from stub handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT
 *              and check if connected callback is called.
 */
int utc_rpc_port_stub_get_port_n2(void)
{
	int ret;
	rpc_port_h callback_port;

	ret = rpc_port_stub_get_port(stub_handle, RPC_PORT_PORT_CALLBACK, NULL, &callback_port);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 1;
}

/**
 * @function    utc_rpc_port_stub_get_port_n3
 * @since_tizen 4.0
 * @description Gets a port from stub handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT
 *              and check if connected callback is called.
 */
int utc_rpc_port_stub_get_port_n3(void)
{
	int ret;
	char *instance = "temp";

	ret = rpc_port_stub_get_port(stub_handle, RPC_PORT_PORT_CALLBACK,
			instance, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 1;
}

static bool touch_connected_event_cb;
static int return_value_for_rpc_port_set_private_sharing_array_p;
static int return_value_for_rpc_port_set_private_sharing_p;
static int return_value_for_rpc_port_unset_private_sharing_p;

static void __create_file(const char *path, const char *message)
{
	FILE *fp;

	fp = fopen(path, "w+");
	if (!fp) {
		dlog_print(DLOG_ERROR, LOG_TAG, "fopen() is failed");
		return;
	}

	fprintf(fp, message);
	fclose(fp);
}

static void __message_connected_event_cb(const char *endpoint, const char *port_name,
		rpc_port_h port, void *user_data)
{
	const char *test_case = (const char *)user_data;
	char file1[PATH_MAX];
	char file2[PATH_MAX];
	const char *files[3] = { NULL, };

	if (!strcmp(test_case, "utc_rpc_port_proxy_connect_sync_p")) {
		touch_connected_event_cb = true;
	} else if (!strcmp(test_case, "utc_rpc_port_set_private_sharing_array_p")) {
		__get_file_path("file_name1.txt", file1, sizeof(file1));
		__get_file_path("file_name2.txt", file2, sizeof(file2));
		__create_file(file1, "test1");
		__create_file(file2, "test2");

		files[0] = file1;
		files[1] = file2;
		return_value_for_rpc_port_set_private_sharing_array_p = rpc_port_set_private_sharing_array(port, files, 2);
		rpc_port_unset_private_sharing(port);
	} else  if (!strcmp(test_case, "utc_rpc_port_set_private_sharing_p")) {
		__get_file_path("file_name.txt", file1, sizeof(file1));
		__create_file(file1, "test3");

		return_value_for_rpc_port_set_private_sharing_p = rpc_port_set_private_sharing(port, file1);
		rpc_port_unset_private_sharing(port);
	} else if (!strcmp(test_case, "utc_rpc_port_unset_private_sharing_p")) {
		return_value_for_rpc_port_unset_private_sharing_p = rpc_port_unset_private_sharing(port);
	}
}

/**
 * @function    utc_rpc_port_proxy_connect_sync_p
 * @since_tizen 6.0
 * @description Connects to rpc port synchronously.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or not
 *              and check if connected callback is called.
 */
int utc_rpc_port_proxy_connect_sync_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __message_connected_event_cb,
			(void *)__FUNCTION__);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect_sync(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);
	assert_eq(touch_connected_event_cb, true);

	normal_exit(0);
	return 0;
}

/**
 * @function    utc_rpc_port_proxy_connect_sync_n
 * @since_tizen 6.0
 * @description Connects to rpc port synchronously.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or not
 */
int utc_rpc_port_proxy_connect_sync_n(void)
{
	int ret;

	ret = rpc_port_proxy_connect(NULL, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @function    utc_rpc_port_set_private_sharing_array_p
 * @since_tizen 6.0
 * @description Shares files for the stub application.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or not.
 */
int utc_rpc_port_set_private_sharing_array_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __message_connected_event_cb,
			(void *)__FUNCTION__);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect_sync(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);
	assert_eq(return_value_for_rpc_port_set_private_sharing_array_p, RPC_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @function    utc_rpc_port_set_private_sharing_array_n
 * @since_tizen 6.0
 * @description Shares files for the stub application.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or not.
 */
int utc_rpc_port_set_private_sharing_array_n(void)
{
	int ret;

	ret = rpc_port_set_private_sharing_array(NULL, NULL, 0);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @function    utc_rpc_port_set_private_sharing_p
 * @since_tizen 6.0
 * @description Shares a file for the stub application.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or not.
 */
int utc_rpc_port_set_private_sharing_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __message_connected_event_cb,
			(void *)__FUNCTION__);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect_sync(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);
	assert_eq(return_value_for_rpc_port_set_private_sharing_p, RPC_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @function    utc_rpc_port_set_private_sharingy_n
 * @since_tizen 6.0
 * @description Shares a file for the stub application.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or not.
 */
int utc_rpc_port_set_private_sharing_n(void)
{
	int ret;

	ret = rpc_port_set_private_sharing(NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @function    utc_rpc_port_unset_private_sharing_p
 * @since_tizen 6.0
 * @description Unshares files.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or not.
 */
int utc_rpc_port_unset_private_sharing_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __message_connected_event_cb,
			(void *)__FUNCTION__);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect_sync(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);
	assert_eq(return_value_for_rpc_port_unset_private_sharing_p, RPC_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @function    utc_rpc_port_unset_private_sharing_n
 * @since_tizen 6.0
 * @description Unshares files.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or not.
 */
int utc_rpc_port_unset_private_sharing_n(void)
{
	int ret;

	ret = rpc_port_unset_private_sharing(NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @function    utc_rpc_port_disconnect_p
 * @since_tizen 6.5
 * @description Disconnects the port connection.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or not.
 */
int utc_rpc_port_disconnect_p(void)
{
	int ret;

	ret = rpc_port_stub_add_connected_event_cb(stub_handle,
			__Message_on_connected_stub, __disconnecttest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_add_received_event_cb(stub_handle,
			__Message_on_received_stub, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_add_disconnected_event_cb(stub_handle,
			__Message_on_disconnected_stub, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_stub_listen(stub_handle);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	__run_proxy_app();

	return 1;
}

/**
 * @function    utc_rpc_port_disconnect_n
 * @since_tizen 6.5
 * @description Disconnects the port connection.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or not.
 */
int utc_rpc_port_disconnect_n(void)
{
	int ret;

	ret = rpc_port_disconnect(NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}
