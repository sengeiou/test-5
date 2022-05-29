//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include "assert_common.h"

#include <cion.h>
#include <dlog.h>
#include <glib.h>

#define LOG_TAG "NativeTCT"

//& set: Cion

static GMainLoop *main_loop;
static guint source_id;
static gboolean __timeout_cb(gpointer data)
{
	g_main_loop_quit(main_loop);
	return FALSE;
}

static void __run_polling_loop(void) {
	main_loop = g_main_loop_new(NULL, FALSE);
	source_id = g_timeout_add(60000, __timeout_cb, NULL);\
	g_main_loop_run(main_loop);\
	g_source_remove(source_id);
	main_loop = NULL;
}

static void __stop_polling_loop(void) {
	sleep(1);
	g_source_remove(source_id);
	g_main_loop_quit(main_loop);
}

void utc_cion_server_startup(void)
{
}

void utc_cion_server_cleanup(void)
{
}

/**
 * @testcase		utc_cion_server_create_p
 * @since_tizen		6.5
 * @description		Creates a cion server.
 */
int utc_cion_server_create_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server, "utc_cion_server_create_p",
			"utc_cion_server_create_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_create_n
 * @since_tizen		6.5
 * @description		Creates a cion server for negative case.
 */
int utc_cion_server_create_n(void)
{
	int ret;
	cion_server_h server = NULL;

	ret = cion_server_create(NULL, "utc_cion_server_create_n",
			"utc_cion_server_create_n", NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_create(&server, NULL,
			"utc_cion_server_create_n", NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_server_destroy_p
 * @since_tizen		6.5
 * @description		Destroys a cion server.
 */
int utc_cion_server_destroy_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server, "utc_cion_server_destroy_p",
			"utc_cion_server_destroy_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_destroy(server);
	assert_eq(ret, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_server_destroy_n
 * @since_tizen		6.5
 * @description		Destroys a cion server for negative case.
 */
int utc_cion_server_destroy_n(void)
{
	int ret;

	ret = cion_server_destroy(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __server_connection_request_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
}

/**
 * @testcase		utc_cion_server_listen_p
 * @since_tizen		6.5
 * @description		Listens connection request from client.
 */
int utc_cion_server_listen_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server, "utc_cion_server_listen_p",
			"utc_cion_server_listen_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_listen(server, __server_connection_request_cb, NULL);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_listen_n
 * @since_tizen		6.5
 * @description		Listens connection request from client for negative case.
 */
int utc_cion_server_listen_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;

	ret = cion_server_listen(NULL, __server_connection_request_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_listen(server, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_server_stop_p
 * @since_tizen		6.5
 * @description		Stops a cion server.
 */
int utc_cion_server_stop_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server, "utc_cion_server_stop_p",
			"utc_cion_server_stop_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_listen(server, __server_connection_request_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_stop(server);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_stop_n
 * @since_tizen		6.5
 * @description		Stops a cion server for negative case.
 */
int utc_cion_server_stop_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;

	ret = cion_server_stop(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_create(&server, "utc_cion_server_stop_n",
			"utc_cion_server_stop_n", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_stop(server);
	assert_eq(ret, CION_ERROR_INVALID_OPERATION);

	cion_server_destroy(server);

	return 0;
}

struct cbdata {
	cion_server_h server;
	cion_peer_info_h peer;
};

static void __server_connection_result_cb(const char *service_name,
		const cion_peer_info_h peer_info,
		const cion_connection_result_h result, void *user_data)
{
	int ret;
	cion_connection_status_e status;

	ret = cion_connection_result_get_status(result, &status);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"[%s] Failed to get connection result", __func__);
		return;
	}

	dlog_print(DLOG_INFO, LOG_TAG,
			"[server] %s connection result: %s", service_name,
			status == CION_CONNECTION_STATUS_OK ? "OK" : "FAIL");
	__stop_polling_loop();
}

static void __server_connection_request_cb2(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	struct cbdata *data = (struct cbdata *)user_data;

	ret = cion_peer_info_clone(peer_info, &(data->peer));
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to clone peer info");
	ret = cion_server_accept(data->server, peer_info);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to accept client");

	dlog_print(DLOG_INFO, LOG_TAG, "[%s] accept client", __func__);
}

static void __client_server_discovered_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_client_h client = (cion_client_h)user_data;

	if (peer_info == NULL)
		dlog_print(DLOG_ERROR, LOG_TAG, "peer info is NULL");

	ret = cion_client_connect(client, peer_info);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to connect to server");
}

/**
 * @testcase		utc_cion_server_disconnect_p
 * @since_tizen		6.5
 * @description		Disconnects from a cion client.
 */
int utc_cion_server_disconnect_p(void)
{
	int ret;
	cion_client_h client;
	cion_server_h server;
	struct cbdata data;

	ret = cion_server_create(&server, "utc_cion_server_disconnect_p",
			"utc_cion_server_disconnect_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_add_connection_result_cb(server, __server_connection_result_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client, "utc_cion_server_disconnect_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	data.server = server;
	data.peer = NULL;

	ret = cion_server_listen(server, __server_connection_request_cb2,
			&data);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb,
			client);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG, "[%s] Wait for connecting to server",
			__func__);
	__run_polling_loop();

	ret = cion_server_disconnect(server, data.peer);
	assert_eq(ret, CION_ERROR_NONE);

	cion_peer_info_destroy(data.peer);
	cion_client_destroy(client);
	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_disconnect_n
 * @since_tizen		6.5
 * @description		Disconnects from a cion client for negative case.
 */
int utc_cion_server_disconnect_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;
	cion_peer_info_h peer = (cion_peer_info_h)1;

	ret = cion_server_disconnect(NULL, peer);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_disconnect(server, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_server_send_payload_async_p
 * @since_tizen		6.5
 * @description		Sends payload asynchronously.
 */
int utc_cion_server_send_payload_async_p(void)
{
	int ret;
	cion_server_h server;
	cion_client_h client;
	cion_payload_h payload;
	struct cbdata data;
	unsigned char payload_data[] = "utc_cion_server_send_payload_async_p";

	ret = cion_server_create(&server,
			"utc_cion_server_send_payload_async_p",
			"utc_cion_server_send_payload_async_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_add_connection_result_cb(server, __server_connection_result_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client,
			"utc_cion_server_send_payload_async_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	data.server = server;
	data.peer = NULL;

	ret = cion_server_listen(server, __server_connection_request_cb2, &data);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb,
			client);
	dlog_print(DLOG_INFO, LOG_TAG, "[%s] Wait for connecting to server", __func__);
	__run_polling_loop();

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_DATA);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_data(payload, payload_data,
			sizeof(payload_data));
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_send_payload_async(server, data.peer, payload, NULL,
			NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_payload_destroy(payload);
	cion_peer_info_destroy(data.peer);
	cion_client_destroy(client);
	cion_server_destroy(server);

	return 0;
}

static void __server_payload_async_result_cb(
		const cion_payload_async_result_h result, void *user_data)
{
}

/**
 * @testcase		utc_cion_server_send_payload_async_n
 * @since_tizen		6.5
 * @description		Sends payload asynchronously for negative case.
 */
int utc_cion_server_send_payload_async_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;
	cion_peer_info_h peer = (cion_peer_info_h)1;
	cion_payload_h payload = (cion_payload_h)1;

	ret = cion_server_send_payload_async(NULL, peer, payload,
			__server_payload_async_result_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_send_payload_async(server, peer, NULL,
			__server_payload_async_result_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool __server_connected_peer_info_cb(const cion_peer_info_h peer_info,
		void *user_data)
{
	return true;
}

/**
 * @testcase		utc_cion_server_foreach_connected_peer_info_p
 * @since_tizen		6.5
 * @description		Gets the information of connected peers.
 */
int utc_cion_server_foreach_connected_peer_info_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_foreach_connected_peer_info_p",
			"utc_cion_server_foreach_connected_peer_info_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_foreach_connected_peer_info(server,
			__server_connected_peer_info_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_foreach_connected_peer_info_n
 * @since_tizen		6.5
 * @description		Gets the information of connected peers for negative case.
 */
int utc_cion_server_foreach_connected_peer_info_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;

	ret = cion_server_foreach_connected_peer_info(NULL,
			__server_connected_peer_info_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_foreach_connected_peer_info(server, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_server_add_connection_result_cb_p
 * @since_tizen		6.5
 * @description		Adds callback function for connection result.
 */
int utc_cion_server_add_connection_result_cb_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_add_connection_result_cb_p",
			"utc_cion_server_add_connection_result_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_add_connection_result_cb(server,
			__server_connection_result_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_add_connection_result_cb_n
 * @since_tizen		6.5
 * @description		Adds callback function for connection result for negative case.
 */
int utc_cion_server_add_connection_result_cb_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;

	ret = cion_server_add_connection_result_cb(NULL,
			__server_connection_result_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_add_connection_result_cb(server, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_server_remove_connection_result_cb_p
 * @since_tizen		6.5
 * @description		Removes callback function for connection result.
 */
int utc_cion_server_remove_connection_result_cb_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_remove_connection_result_cb_p",
			"utc_cion_server_remove_connection_result_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_add_connection_result_cb(server,
			__server_connection_result_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_remove_connection_result_cb(server,
			__server_connection_result_cb);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_remove_connection_result_cb_n
 * @since_tizen		6.5
 * @description		Removes callback function for connection result for negative case.
 */
int utc_cion_server_remove_connection_result_cb_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;

	ret = cion_server_remove_connection_result_cb(NULL,
			__server_connection_result_cb);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_remove_connection_result_cb(server, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __server_payload_received_cb(const char *service_name,
		const cion_peer_info_h peer_info, const cion_payload_h payload,
		cion_payload_transfer_status_e status,
		void *user_data)
{
}

/**
 * @testcase		utc_cion_server_add_payload_received_cb_p
 * @since_tizen		6.5
 * @description		Adds callback function to receive payload.
 */
int utc_cion_server_add_payload_received_cb_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_add_payload_received_cb_p",
			"utc_cion_server_add_payload_received_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_add_payload_received_cb(server,
			__server_payload_received_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_add_payload_received_cb_n
 * @since_tizen		6.5
 * @description		Adds callback function to receive payload for negative case.
 */
int utc_cion_server_add_payload_received_cb_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;

	ret = cion_server_add_payload_received_cb(NULL,
			__server_payload_received_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_add_payload_received_cb(server, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_server_remove_payload_received_cb_p
 * @since_tizen		6.5
 * @description		Removes callback function to receive payload.
 */
int utc_cion_server_remove_payload_received_cb_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_remove_payload_received_cb_p",
			"utc_cion_server_remove_payload_received_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_add_payload_received_cb(server,
			__server_payload_received_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_remove_payload_received_cb(server,
			__server_payload_received_cb);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_remove_payload_received_cb_n
 * @since_tizen		6.5
 * @description		Removes callback function to receive payload for negative case.
 */
int utc_cion_server_remove_payload_received_cb_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;

	ret = cion_server_remove_payload_received_cb(NULL,
				__server_payload_received_cb);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_remove_payload_received_cb(server,
			NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __server_data_received_cb(const char *service_name,
		const cion_peer_info_h peer_info, const unsigned char *data,
		unsigned int data_size, unsigned char **return_data,
		unsigned int *return_data_size, void *user_data)
{
}

/**
 * @testcase		utc_cion_server_set_data_received_cb_p
 * @since_tizen		6.5
 * @description		Sets callback function to receive data.
 */
int utc_cion_server_set_data_received_cb_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_set_data_received_cb_p",
			"utc_cion_server_set_data_received_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_set_data_received_cb(server,
			__server_data_received_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_set_data_received_cb_n
 * @since_tizen		6.5
 * @description		Sets callback function to receive data for negative case.
 */
int utc_cion_server_set_data_received_cb_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;

	ret = cion_server_set_data_received_cb(NULL, __server_data_received_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_set_data_received_cb(server, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_server_unset_data_received_cb_p
 * @since_tizen		6.5
 * @description		Unsets callback function to receive data.
 */
int utc_cion_server_unset_data_received_cb_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_unset_data_received_cb_p",
			"utc_cion_server_unset_data_received_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_set_data_received_cb(server,
			__server_data_received_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_unset_data_received_cb(server);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_unset_data_received_cb_n
 * @since_tizen		6.5
 * @description		Unsets callback function to receive data for negative case.
 */
int utc_cion_server_unset_data_received_cb_n(void)
{
	int ret;

	ret = cion_server_unset_data_received_cb(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __server_disconnected_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
}

/**
 * @testcase		utc_cion_server_add_disconnected_cb_p
 * @since_tizen		6.5
 * @description		Adds callback function to get disconnected info.
 */
int utc_cion_server_add_disconnected_cb_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_add_disconnected_cb_p",
			"utc_cion_server_add_disconnected_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_add_disconnected_cb(server,
			__server_disconnected_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_add_disconnected_cb_n
 * @since_tizen		6.5
 * @description		Adds callback function to get disconnected info for negative case.
 */
int utc_cion_server_add_disconnected_cb_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;

	ret = cion_server_add_disconnected_cb(NULL,
			__server_disconnected_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_add_disconnected_cb(server, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_server_remove_disconnected_cb_p
 * @since_tizen		6.5
 * @description		Removes callback function to get disconnected info.
 */
int utc_cion_server_remove_disconnected_cb_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_remove_disconnected_cb_p",
			"utc_cion_server_remove_disconnected_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_add_disconnected_cb(server,
			__server_disconnected_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_remove_disconnected_cb(server,
			__server_disconnected_cb);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_remove_disconnected_cb_n
 * @since_tizen		6.5
 * @description		Removes callback function to get disconnected info for negative case.
 */
int utc_cion_server_remove_disconnected_cb_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;

	ret = cion_server_remove_disconnected_cb(NULL,
			__server_disconnected_cb);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_remove_disconnected_cb(server, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __client_server_discovered_cb2(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_peer_info_h *peer = (cion_peer_info_h *)user_data;

	ret = cion_peer_info_clone(peer_info, peer);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to clone peer info");

	__stop_polling_loop();
}

static void __server_connection_request_cb3(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_peer_info_h *peer = (cion_peer_info_h *)user_data;

	dlog_print(DLOG_ERROR, LOG_TAG, "Get connection request from client");

	ret = cion_peer_info_clone(peer_info, peer);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to clone peer info");

	__stop_polling_loop();
}

/**
 * @testcase		utc_cion_server_accept_p
 * @since_tizen		6.5
 * @description		Accepts connection.
 */
int utc_cion_server_accept_p(void)
{
	int ret;
	cion_server_h server;
	cion_client_h client;
	cion_peer_info_h peer_client = NULL;
	cion_peer_info_h peer_server = NULL;

	ret = cion_server_create(&server, "utc_cion_server_accept_p",
			"utc_cion_server_accept_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client, "utc_cion_server_accept_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_listen(server, __server_connection_request_cb3,
			&peer_client);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb2,
			&peer_server);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG, "[%s] Wait for discovering server", __func__);
	__run_polling_loop();

	assert_neq(peer_server, NULL);
	dlog_print(DLOG_INFO, LOG_TAG, "[%s] Server found, try connect",
			__func__);

	ret = cion_client_connect(client, peer_server);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for server get connection request", __func__);
	__run_polling_loop();

	ret = cion_server_accept(server, peer_client);
	assert_eq(ret, CION_ERROR_NONE);

	cion_peer_info_destroy(peer_server);
	cion_peer_info_destroy(peer_client);
	cion_client_destroy(client);
	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_accept_n
 * @since_tizen		6.5
 * @description		Accepts connection for negative case.
 */
int utc_cion_server_accept_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;
	cion_peer_info_h peer = (cion_peer_info_h)1;

	ret = cion_server_accept(NULL, peer);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_accept(server, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __client_server_discovered_cb3(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_peer_info_h *peer = (cion_peer_info_h *)user_data;

	ret = cion_peer_info_clone(peer_info, peer);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to clone peer info");

	__stop_polling_loop();
}

static void __server_connection_request_cb4(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_peer_info_h *peer = (cion_peer_info_h *)user_data;

	dlog_print(DLOG_ERROR, LOG_TAG, "Get connection request from client");

	ret = cion_peer_info_clone(peer_info, peer);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to clone peer info");

	__stop_polling_loop();
}

/**
 * @testcase		utc_cion_server_reject_p
 * @since_tizen		6.5
 * @description		Rejects connection.
 */
int utc_cion_server_reject_p(void)
{
	int ret;
	cion_server_h server;
	cion_client_h client;
	cion_peer_info_h peer_client = NULL;
	cion_peer_info_h peer_server = NULL;

	ret = cion_server_create(&server, "utc_cion_server_reject_p",
			"utc_cion_server_reject_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client, "utc_cion_server_reject_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_listen(server, __server_connection_request_cb4,
			&peer_client);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb3,
			&peer_server);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG, "[%s] Wait for discovering server", __func__);
	__run_polling_loop();

	assert_neq(peer_server, NULL);
	dlog_print(DLOG_INFO, LOG_TAG, "[%s] Server found, try connect",
			__func__);

	ret = cion_client_connect(client, peer_server);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for server get connection request", __func__);
	__run_polling_loop();

	ret = cion_server_reject(server, peer_client, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_peer_info_destroy(peer_server);
	cion_peer_info_destroy(peer_client);
	cion_client_destroy(client);
	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_reject_n
 * @since_tizen		6.5
 * @description		Rejects connection for negative case.
 */
int utc_cion_server_reject_n(void)
{
	int ret;
	cion_server_h server = (cion_server_h)1;
	cion_peer_info_h peer = (cion_peer_info_h)1;

	ret = cion_server_reject(NULL, peer, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_server_reject(server, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_server_set_display_name_p
 * @since_tizen		6.5
 * @description		Sets display name.
 */
int utc_cion_server_set_display_name_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_set_display_name_p",
			"utc_cion_server_set_display_name_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_set_display_name(server, "display_name");
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_set_display_name_n
 * @since_tizen		6.5
 * @description		Sets display name for negative case.
 */
int utc_cion_server_set_display_name_n(void)
{
	int ret;

	ret = cion_server_set_display_name(NULL,
			"utc_cion_server_set_display_name_n");
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_server_set_on_demand_launch_enabled_p
 * @since_tizen		6.5
 * @description		Sets on-demand launch enabled state.
 */
int utc_cion_server_set_on_demand_launch_enabled_p(void)
{
	int ret;
	cion_server_h server;

	ret = cion_server_create(&server,
			"utc_cion_server_set_on_demand_launch_enabled_p",
			"utc_cion_server_set_on_demand_launch_enabled_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_set_on_demand_launch_enabled(server, false);
	assert_eq(ret, CION_ERROR_NONE);

	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_server_set_on_demand_launch_enabled_n
 * @since_tizen		6.5
 * @description		Sets on-demand launch enabled state for negative case.
 */
int utc_cion_server_set_on_demand_launch_enabled_n(void)
{
	int ret;

	ret = cion_server_set_on_demand_launch_enabled(NULL, true);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}
