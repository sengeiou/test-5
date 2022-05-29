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
#include "assert.h"

#include <dlog.h>
#include <service_app.h>
#include <rpc-port-parcel.h>
#include <rpc-port.h>

#include "tct_app_common.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "NativeTCT"

#define normal_exit(result) do { \
	__result = result; \
	service_app_exit(); \
} while (0)

#define assert_streq(var, ref) \
    do { \
	if (strcmp(var, ref)) { \
	    fprintf(stderr, \
		"\\n[TCT][%s][Line : %d] Assert fail; Values (%s == %s) is not equal to (%s == %s)\\n", \
		__FILE__, __LINE__,  #var, var, #ref, ref); \
	    return 1; \
	} \
    } while (0)

enum Message_method_e {
	Message_METHOD_Result,
	Message_METHOD_Callback,
	Message_METHOD_Send,
};

static const char __service_app_id[] = "org.example.stubsample";
static const char __port_name[] = "Message";

static char __createtest[] = "create_from_port";
static char __sendtest[] = "send";
static char __setgetseqnumtest[] = "set_get_seq_num";
static char __setgettagtest[] = "set_get_tag";

int __result;
static rpc_port_proxy_h proxy_handle;
static rpc_port_h received_port;
static rpc_port_parcel_h parcel;

void utc_rpc_port_parcel_startup(void)
{
	rpc_port_proxy_create(&proxy_handle);
	parcel = NULL;
}

void utc_rpc_port_parcel_cleanup(void)
{
	if (proxy_handle) {
		rpc_port_proxy_destroy(proxy_handle);
	}
	if (parcel) {
		rpc_port_parcel_destroy(parcel);
	}
}

void parcel_to(rpc_port_parcel_h h, void *data)
{
	return;
}

void parcel_from(rpc_port_parcel_h h, void *data)
{
	return;
}

static void __Message_on_connected(const char *endpoint, const char *port_name, rpc_port_h port, void *data)
{
	int ret;

	dlog_print(DLOG_INFO, LOG_TAG, "%s connected", endpoint);
	if (strcmp(endpoint, __service_app_id)) {
		normal_exit(1);
		return;
	}

	if (data == __createtest) {
		received_port = port;
		rpc_port_parcel_h parcel;

		rpc_port_parcel_create(&parcel);
		rpc_port_parcel_write_int32(parcel, Message_METHOD_Send);
		rpc_port_parcel_write_string(parcel, "receive");

		rpc_port_parcel_send(parcel, port);
		rpc_port_parcel_destroy(parcel);
		return;
	} else if (data == __sendtest) {
		received_port = NULL;
		rpc_port_parcel_header_h header;
		ret = rpc_port_parcel_create(&parcel);
		if (ret != RPC_PORT_ERROR_NONE) {
			normal_exit(1);
			return;
		}

		ret = rpc_port_parcel_get_header(parcel, &header);
		if (ret != RPC_PORT_ERROR_NONE) {
			normal_exit(1);
			return;
		}

		ret = rpc_port_parcel_header_set_tag(header, "1.5.0");
		if (ret != RPC_PORT_ERROR_NONE) {
			rpc_port_parcel_destroy(parcel);
			normal_exit(1);
		}
		ret = rpc_port_parcel_header_set_seq_num(header, 100);
		if (ret != RPC_PORT_ERROR_NONE) {
			rpc_port_parcel_destroy(parcel);
			normal_exit(1);
		}
		rpc_port_parcel_write_int32(parcel, Message_METHOD_Send);
		rpc_port_parcel_write_string(parcel, "receive");

		rpc_port_parcel_send(parcel, port);
	}
	normal_exit(0);
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
	rpc_port_parcel_header_h header;
	rpc_port_parcel_header_h received_header;


	rpc_port_proxy_get_port(proxy_handle, RPC_PORT_PORT_CALLBACK, &callback_port);

	if (data == __setgettagtest) {
		char *tag;
		char *received_tag;
		rpc_port_parcel_create_from_port(&parcel_received, callback_port);

		rpc_port_parcel_get_header(parcel, &header);
		ret = rpc_port_parcel_header_get_tag(header, &tag);
		if (ret != RPC_PORT_ERROR_NONE) {
			normal_exit(1);
			return;
		}

		rpc_port_parcel_get_header(parcel_received, &received_header);
		ret = rpc_port_parcel_header_get_tag(header, &received_tag);
		if (ret != RPC_PORT_ERROR_NONE) {
			normal_exit(1);
			return;
		}
		if (strcmp(received_tag, tag) != 0) {
			normal_exit(1);
			return;
		}

		rpc_port_parcel_destroy(parcel_received);
		normal_exit(0);
		return;
	} else if (data == __setgetseqnumtest) {
		int seq_num;
		int received_seq_num;
		rpc_port_parcel_create_from_port(&parcel_received, callback_port);

		rpc_port_parcel_get_header(parcel, &header);
		rpc_port_parcel_header_get_seq_num(header, &seq_num);
		if (ret != RPC_PORT_ERROR_NONE) {
			normal_exit(1);
			return;
		}

		rpc_port_parcel_get_header(parcel_received, &received_header);
		ret = rpc_port_parcel_header_get_seq_num(received_header, &received_seq_num);
		if (ret != RPC_PORT_ERROR_NONE) {
			normal_exit(1);
			return;
		}

		if (seq_num != received_seq_num) {
			normal_exit(1);
			return;
		}

		rpc_port_parcel_destroy(parcel_received);
		normal_exit(0);
		return;
	}

	ret = rpc_port_parcel_create_from_port(&parcel_received, callback_port);
	if (ret != 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Invalid protocol");
		rpc_port_parcel_destroy(parcel_received);
		return;
	}

	ret = rpc_port_parcel_destroy(parcel_received);
	if (ret != RPC_PORT_ERROR_NONE) {
		normal_exit(1);
		return;
	}

	normal_exit(0);
}

/**
 * @function    utc_rpc_port_parcel_create_p
 * @since_tizen 4.0
 * @description Creates the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_create_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_create_from_port_p
 * @since_tizen 4.0
 * @description Creates the rpc port parcel handle from rpc port handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_create_from_port_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __Message_on_connected, __createtest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_add_received_event_cb(proxy_handle, __Message_on_received, NULL);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

    return 1;
}

/**
 * @function    utc_rpc_port_parcel_create_from_port_n
 * @since_tizen 4.0
 * @description Creates the rpc port parcel handle from rpc port handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_create_from_port_n1(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create_from_port(&h, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_create_from_port_n
 * @since_tizen 4.0
 * @description Creates the rpc port parcel handle from rpc port handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_create_from_port_n2(void)
{
	int ret;
	int len = 1;
	char data[] = "test";
	rpc_port_h port = NULL;

	rpc_port_write(port, &len, 4);
	rpc_port_write(port, data, len);

	ret = rpc_port_parcel_create_from_port(NULL, port);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_send_p
 * @since_tizen 4.0
 * @description Sends the rpc port parcel data to rpc port handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_send_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle, __Message_on_connected, __sendtest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_connect(proxy_handle, __service_app_id, __port_name);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

    return 1;
}

/**
 * @function    utc_rpc_port_parcel_send_n1
 * @since_tizen 4.0
 * @description Sends the rpc port parcel data to rpc port handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_send_n1(void)
{
	int ret;
	rpc_port_h port = NULL;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);

	ret = rpc_port_parcel_write_string(h, "test");
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_send(NULL, port);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_send_n2
 * @since_tizen 4.0
 * @description Sends the rpc port parcel data to rpc port handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_send_n2(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);

	ret = rpc_port_parcel_write_string(h, "test");
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_send(h, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_destroy_p
 * @since_tizen 4.0
 * @description Destroys the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_destroy_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_destroy_n
 * @since_tizen 4.0
 * @description Destroys the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_destroy_n(void)
{
	int ret;

	ret = rpc_port_parcel_destroy(NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_byte_p
 * @since_tizen 4.0
 * @description Writes byte data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_byte_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_byte(h, 'a');
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_byte_n
 * @since_tizen 4.0
 * @description Writes byte data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_byte_n(void)
{
	int ret;

	ret = rpc_port_parcel_write_byte(NULL, 'a');
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_int16_p
 * @since_tizen 4.0
 * @description Writes int16 data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_int16_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_int16(h, 16);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_int16_n
 * @since_tizen 4.0
 * @description Writes int16 data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_int16_n(void)
{
	int ret;

	ret = rpc_port_parcel_write_byte(NULL, 16);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_int32_p
 * @since_tizen 4.0
 * @description Writes int32 data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_int32_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_int32(h, 32);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_int32_n
 * @since_tizen 4.0
 * @description Writes int32 data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_int32_n(void)
{
	int ret;

	ret = rpc_port_parcel_write_byte(NULL, 32);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_int64_p
 * @since_tizen 4.0
 * @description Writes int64 data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_int64_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_int64(h, 64);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_int64_n
 * @since_tizen 4.0
 * @description Writes int64 data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_int64_n(void)
{
	int ret;

	ret = rpc_port_parcel_write_byte(NULL, 64);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_float_p
 * @since_tizen 4.0
 * @description Writes float data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_float_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_float(h, 64);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_float_n
 * @since_tizen 4.0
 * @description Writes float data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_float_n(void)
{
	int ret;

	ret = rpc_port_parcel_write_float(NULL, 64);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}


/**
 * @function    utc_rpc_port_parcel_write_double_p
 * @since_tizen 4.0
 * @description Writes double data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_double_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_double(h, 64);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_double_n
 * @since_tizen 4.0
 * @description Writes double data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_double_n(void)
{
	int ret;

	ret = rpc_port_parcel_write_double(NULL, 64);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_string_p
 * @since_tizen 4.0
 * @description Writes string data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_string_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_string(h, "test");
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_string_n
 * @since_tizen 4.0
 * @description Writes string data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_string_n(void)
{
	int ret;

	ret = rpc_port_parcel_write_string(NULL, "test");
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_bool_p
 * @since_tizen 4.0
 * @description Writes bool data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_bool_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_bool(h, true);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_bool_n
 * @since_tizen 4.0
 * @description Writes bool data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_bool_n(void)
{
	int ret;

	ret = rpc_port_parcel_write_bool(NULL, true);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_bundle_p
 * @since_tizen 4.0
 * @description Writes bundle data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_bundle_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	bundle *b;

	b = bundle_create();

	bundle_add_str(b, "key", "test key");

	ret = rpc_port_parcel_create(&h);
	if (ret != RPC_PORT_ERROR_NONE) {
		bundle_free(b);
	}
	assert_eq(ret, RPC_PORT_ERROR_NONE);


	ret = rpc_port_parcel_write_bundle(h, b);
	if (ret != RPC_PORT_ERROR_NONE) {
		bundle_free(b);
	}
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	if (ret != RPC_PORT_ERROR_NONE) {
		bundle_free(b);
	}
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	bundle_free(b);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_bundle_n
 * @since_tizen 4.0
 * @description Writes bundle data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_bundle_n(void)
{
	int ret;

	ret = rpc_port_parcel_write_bundle(NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_array_count_p
 * @since_tizen 4.0
 * @description Writes array count data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_array_count_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_array_count(h, 1);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_array_count_n
 * @since_tizen 4.0
 * @description Writes array count data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_array_count_n(void)
{
	int ret;

	ret = rpc_port_parcel_write_array_count(NULL, 1);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_p
 * @since_tizen 4.0
 * @description Writes data to the rpc port parcel handle using parcelable.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_write_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	rpc_port_parcelable_t parcelable = {
		.to = parcel_to,
		.from = parcel_from
	};

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write(h, &parcelable, NULL);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_n1
 * @since_tizen 4.0
 * @description Writes data to the rpc port parcel handle using parcelable.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_n1(void)
{
	int ret;

	rpc_port_parcelable_t parcelable = {
		.to = parcel_to,
		.from = parcel_from
	};

	ret = rpc_port_parcel_write(NULL, &parcelable, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_write_n2
 * @since_tizen 4.0
 * @description Writes data to the rpc port parcel handle using parcelable.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_write_n2(void)
{
	int ret;

	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write(h, NULL, NULL);
	if (ret != RPC_PORT_ERROR_INVALID_PARAMETER)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_byte_p
 * @since_tizen 4.0
 * @description Reads byte data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_byte_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	char data;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_byte(h, 'a');
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_byte(h, &data);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_byte_n
 * @since_tizen 4.0
 * @description Reads byte data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_byte_n(void)
{
	int ret;
	char data;

	ret = rpc_port_parcel_read_byte(NULL, &data);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_int16_p
 * @since_tizen 4.0
 * @description Reads int16 data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_int16_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	short data;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_int16(h, 16);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_int16(h, &data);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_int16_n
 * @since_tizen 4.0
 * @description Reads int16 data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_int16_n(void)
{
	int ret;
	short data;

	ret = rpc_port_parcel_read_int16(NULL, &data);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_int32_p
 * @since_tizen 4.0
 * @description Reads int32 data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_int32_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	int data;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_int32(h, 16);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_int32(h, &data);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_int32_n
 * @since_tizen 4.0
 * @description Reads int32 data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_int32_n(void)
{
	int ret;
	int data;

	ret = rpc_port_parcel_read_int32(NULL, &data);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_int64_p
 * @since_tizen 4.0
 * @description Reads int64 data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_int64_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	long long data;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_int64(h, 16);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_int64(h, &data);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_int64_n
 * @since_tizen 4.0
 * @description Reads int64 data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_int64_n(void)
{
	int ret;
	long long data;

	ret = rpc_port_parcel_read_int64(NULL, &data);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_float_p
 * @since_tizen 4.0
 * @description Reads float data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_float_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	float data;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_float(h, 16);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_float(h, &data);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_float_n
 * @since_tizen 4.0
 * @description Reads float data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_float_n(void)
{
	int ret;
	float data;

	ret = rpc_port_parcel_read_float(NULL, &data);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_double_p
 * @since_tizen 4.0
 * @description Reads double data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_double_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	double data;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_double(h, 16);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_double(h, &data);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_double_n
 * @since_tizen 4.0
 * @description Reads double data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_double_n(void)
{
	int ret;
	double data;

	ret = rpc_port_parcel_read_double(NULL, &data);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_string_p
 * @since_tizen 4.0
 * @description Reads string data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_string_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	char *data;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_string(h, "test");
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_string(h, &data);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_string_n
 * @since_tizen 4.0
 * @description Reads string data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_string_n(void)
{
	int ret;
	char *data;

	ret = rpc_port_parcel_read_string(NULL, &data);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_bool_p
 * @since_tizen 4.0
 * @description Reads bool data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_bool_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	bool data;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_bool(h, true);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_bool(h, &data);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_bool_n
 * @since_tizen 4.0
 * @description Reads bool data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_bool_n(void)
{
	int ret;
	bool data;

	ret = rpc_port_parcel_read_bool(NULL, &data);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_bundle_p
 * @since_tizen 4.0
 * @description Reads bundle data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_bundle_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	bundle *b;
	bundle *data;

	b = bundle_create();
	bundle_add_str(b, "key", "test key");

	ret = rpc_port_parcel_create(&h);
	if (ret != RPC_PORT_ERROR_NONE)
		bundle_free(b);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_bundle(h, b);
	if (ret != RPC_PORT_ERROR_NONE) {
		rpc_port_parcel_destroy(h);
		bundle_free(b);
	}
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_bundle(h, &data);
	if (ret != RPC_PORT_ERROR_NONE) {
		bundle_free(b);
		rpc_port_parcel_destroy(h);
	}
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_bundle_n
 * @since_tizen 4.0
 * @description Reads bundle data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_bundle_n(void)
{
	int ret;
	bundle *data;

	ret = rpc_port_parcel_read_bundle(NULL, &data);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_array_count_p
 * @since_tizen 4.0
 * @description Reads array count data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_array_count_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	int data;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_array_count(h, 15);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_array_count(h, &data);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_array_count_n
 * @since_tizen 4.0
 * @description Reads array count data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_array_count_n(void)
{
	int ret;
	int data;

	ret = rpc_port_parcel_read_array_count(NULL, &data);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_p
 * @since_tizen 4.0
 * @description Reads data from the rpc port parcel handle using parcelable.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_read_p(void)
{
	int ret;
	rpc_port_parcel_h h;

	rpc_port_parcelable_t parcelable = {
		.to = parcel_to,
		.from = parcel_from
	};

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read(h, &parcelable, NULL);
	if (ret != RPC_PORT_ERROR_NONE)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_n1
 * @since_tizen 4.0
 * @description Writes data to the rpc port parcel handle using parcelable.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_n1(void)
{
	int ret;

	rpc_port_parcelable_t parcelable = {
		.to = parcel_to,
		.from = parcel_from
	};

	ret = rpc_port_parcel_read(NULL, &parcelable, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_read_n2
 * @since_tizen 4.0
 * @description Writes data to the rpc port parcel handle using parcelable.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_read_n2(void)
{
	int ret;

	rpc_port_parcel_h h;

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read(h, NULL, NULL);
	if (ret != RPC_PORT_ERROR_INVALID_PARAMETER)
		rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_burst_read_p
 * @since_tizen 4.0
 * @description Reads data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_burst_read_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	unsigned char buf[] = { 0, 1, 'a', 'b', 3 };
	unsigned char buf2[] = { 0, };

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_burst_write(h, buf, sizeof(buf));
	if (ret != RPC_PORT_ERROR_NONE) {
		rpc_port_parcel_destroy(h);
	}
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_burst_read(h, (unsigned char *)&buf2,
			sizeof(buf));
	if (ret != RPC_PORT_ERROR_NONE) {
		rpc_port_parcel_destroy(h);
	}
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_burst_read_n
 * @since_tizen 4.0
 * @description Reads data from the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_burst_read_n(void)
{
	int ret;
	unsigned char buf[] = { 0, 1, 'a', 'b', 3 };

	ret = rpc_port_parcel_burst_read(NULL, (unsigned char *)&buf,
			sizeof(buf));
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_burst_write_p
 * @since_tizen 4.0
 * @description Writes data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_NONE or NOT.
 */
int utc_rpc_port_parcel_burst_write_p(void)
{
	int ret;
	rpc_port_parcel_h h;
	unsigned char buf[] = { 0, 1, 'a', 'b', 3 };
	unsigned char buf2[5] = { 0, };

	ret = rpc_port_parcel_create(&h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_burst_write(h, buf, sizeof(buf));
	if (ret != RPC_PORT_ERROR_NONE) {
		rpc_port_parcel_destroy(h);
	}
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_burst_read(h, buf2, sizeof(buf));
	if (ret != RPC_PORT_ERROR_NONE) {
		rpc_port_parcel_destroy(h);
	}
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG, "buf(%s), buf2(%s)", buf, buf2);
	for (int i = 0; i < 5; i++) {
		if (buf[i] != buf2[i]) {
			ret = rpc_port_parcel_destroy(h);
			assert_eq(ret, RPC_PORT_ERROR_NONE);

			normal_exit(1);
			return 1;
		}
	}

	ret = rpc_port_parcel_destroy(h);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	normal_exit(0);
    return 0;
}

/**
 * @function    utc_rpc_port_parcel_burst_write_n
 * @since_tizen 4.0
 * @description Writes data to the rpc port parcel handle.
 * @scenario    Check whether the result is RPC_PORT_ERROR_INVALID_PARAMETER or NOT.
 */
int utc_rpc_port_parcel_burst_write_n(void)
{
	int ret;
	unsigned char buf[] = { 0, 1, 'a', 'b', 3 };

	ret = rpc_port_parcel_burst_write(NULL, (unsigned char *)&buf,
			sizeof(buf));
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
    return 0;
}

/*
 * @testcase utc_rpc_port_parcel_get_header_p
 * @since_tizen 6.5
 * @description Gets the header handle from the rpc port parcel handle
 * @apicovered rpc_port_parcel_get_header
 */
int utc_rpc_port_parcel_get_header_p(void)
{
	int ret;
	rpc_port_parcel_h parcel;
	rpc_port_parcel_header_h header = NULL;

	ret = rpc_port_parcel_create(&parcel);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_get_header(parcel, &header);
	assert_eq(ret, RPC_PORT_ERROR_NONE);
	assert_neq(header, NULL);

	rpc_port_parcel_destroy(parcel);

	normal_exit(0);
	return 0;
}

/*
 * @testcase utc_rpc_port_parcel_get_header_n
 * @since_tizen 6.5
 * @description Gets the header handle from the rpc port parcel handle
 * @apicovered rpc_port_parcel_get_header
 */
int utc_rpc_port_parcel_get_header_n(void)
{
	int ret;

	ret = rpc_port_parcel_get_header(NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/*
 * @testcase utc_rpc_port_parcel_header_set_get_tag_p
 * @since_tizen 6.5
 * @description Sets and gets the tag
 * @apicovered rpc_port_parcel_header_set_tag, rpc_port_parcel_header_get_tag
 */
int utc_rpc_port_parcel_header_set_get_tag_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle,
			__Message_on_connected, __sendtest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_add_received_event_cb(proxy_handle,
			__Message_on_received, __setgettagtest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	rpc_port_proxy_connect_sync(proxy_handle, __service_app_id, __port_name);

	return 1;
}

/*
 * @testcase utc_rpc_port_parcel_header_set_get_tag_n
 * @since_tizen 6.5
 * @description Sets and gets the tag
 * @apicovered rpc_port_parcel_header_set_tag, rpc_port_parcel_header_get_tag
 */
int utc_rpc_port_parcel_header_set_get_tag_n(void)
{
	int ret;
	ret = rpc_port_parcel_header_set_tag(NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/*
 * @testcase utc_rpc_port_parcel_header_set_get_seq_num_p
 * @since_tizen 6.5
 * @description Sets and gets the sequence number
 * @apicovered rpc_port_parcel_header_set_seq_num, rpc_port_parcel_header_get_seq_num
 */
int utc_rpc_port_parcel_header_set_get_seq_num_p(void)
{
	int ret;

	ret = rpc_port_proxy_add_connected_event_cb(proxy_handle,
			__Message_on_connected, __sendtest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_proxy_add_received_event_cb(proxy_handle,
			__Message_on_received, __setgetseqnumtest);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	rpc_port_proxy_connect_sync(proxy_handle, __service_app_id, __port_name);

	return 1;
}

/*
 * @testcase utc_rpc_port_parcel_header_set_get_seq_num_n
 * @since_tizen 6.5
 * @description Sets and gets the sequence number
 * @apicovered rpc_port_parcel_header_set_seq_num, rpc_port_parcel_header_get_seq_num
 */
int utc_rpc_port_parcel_header_set_get_seq_num_n(void)
{
	int ret;

	ret = rpc_port_parcel_header_set_seq_num(NULL, -1);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	ret = rpc_port_parcel_header_get_seq_num(NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/*
 * @testcase utc_rpc_port_parcel_header_get_timestamp_p
 * @since_tizen 6.5
 * @description Gets the timestamp from the header handle of the rpc port parcel
 * @apicovered rpc_port_parcel_header_get_timestamp
 */
int utc_rpc_port_parcel_header_get_timestamp_p(void)
{
	int ret;
	rpc_port_parcel_h parcel = NULL;
	rpc_port_parcel_header_h header = NULL;
	struct timespec timestamp = { 0, };

	ret = rpc_port_parcel_create(&parcel);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_get_header(parcel, &header);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_header_get_timestamp(header, &timestamp);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	rpc_port_parcel_destroy(parcel);

	normal_exit(0);
	return 0;
}

/*
 * @testcase utc_rpc_port_parcel_header_get_timestamp_n
 * @since_tizen 6.5
 * @description Gets the timestamp from the header handle of the rpc port parcel
 * @apicovered rpc_port_parcel_header_get_timestamp
 */
int utc_rpc_port_parcel_header_get_timestamp_n(void)
{
	int ret;

	ret = rpc_port_parcel_header_get_timestamp(NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/*
 * @testcase utc_rpc_port_parcel_get_raw_p
 * @since_tizen 6.5
 * @description Gets the raw data of the parcel.
 * @apicoverered rpc_port_parcel_get_raw
 */
int utc_rpc_port_parcel_get_raw_p(void)
{
	rpc_port_parcel_h parcel_from_raw;
	rpc_port_parcel_h parcel;
	unsigned int size = 0;
	char *str = NULL;
	void *raw = NULL;
	int ret;

	ret = rpc_port_parcel_create(&parcel);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_string(parcel, "test");
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_get_raw(parcel, &raw, &size);
	assert_eq(ret, RPC_PORT_ERROR_NONE);
	assert_neq(raw, NULL);
	assert_neq(size, 0);

	ret = rpc_port_parcel_create_from_raw(&parcel_from_raw, raw, size);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_string(parcel_from_raw, &str);
	assert_eq(ret, RPC_PORT_ERROR_NONE);
	assert_neq(str, NULL);

	if (strcmp(str, "test") != 0)
		ret = 1;

	free(str);
	rpc_port_parcel_destroy(parcel_from_raw);
	rpc_port_parcel_destroy(parcel);
	normal_exit(ret);

	return ret;
}

/*
 * @testcase utc_rpc_port_parcel_get_raw_n
 * @since_tizen 6.5
 * @description Gets the raw data of the parcel.
 * @apicoverered rpc_port_parcel_get_raw
 */
int utc_rpc_port_parcel_get_raw_n(void)
{
	int ret;

	ret = rpc_port_parcel_get_raw(NULL, NULL, NULL);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);

	return 0;
}

/*
 * @testcase utc_rpc_port_parcel_create_from_raw_p
 * @since_tizen 6.5
 * @description Creates the parcel handle with the raw data.
 * @apicoverered rpc_port_parcel_create_from_raw
 */
int utc_rpc_port_parcel_create_from_raw_p(void)
{
	rpc_port_parcel_h parcel_from_raw;
	rpc_port_parcel_h parcel;
	unsigned int size = 0;
	char *str = NULL;
	void *raw = NULL;
	int ret;

	ret = rpc_port_parcel_create(&parcel);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_write_string(parcel, "test_create_from_raw");
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_get_raw(parcel, &raw, &size);
	assert_eq(ret, RPC_PORT_ERROR_NONE);
	assert_neq(raw, NULL);
	assert_neq(size, 0);

	ret = rpc_port_parcel_create_from_raw(&parcel_from_raw, raw, size);
	assert_eq(ret, RPC_PORT_ERROR_NONE);

	ret = rpc_port_parcel_read_string(parcel_from_raw, &str);
	assert_eq(ret, RPC_PORT_ERROR_NONE);
	assert_neq(str, NULL);

	if (strcmp(str, "test_create_from_raw") != 0)
		ret = 1;

	free(str);
	rpc_port_parcel_destroy(parcel_from_raw);
	rpc_port_parcel_destroy(parcel);
	normal_exit(ret);

	return ret;
}

/*
 * @testcase utc_rpc_port_parcel_create_from_raw_n
 * @since_tizen 6.5
 * @description Creates the parcel handle with the raw data.
 * @apicoverered rpc_port_parcel_create_from_raw
 */
int utc_rpc_port_parcel_create_from_raw_n(void)
{
	int ret;

	ret = rpc_port_parcel_create_from_raw(NULL, NULL, 0);
	assert_eq(ret, RPC_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);

	return 0;
}
