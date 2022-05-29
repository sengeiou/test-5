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

struct cbdata {
	cion_client_h client;
	bool connected;
};

struct send_data {
	cion_client_h client;
	unsigned char *return_data;
	unsigned int return_data_size;
	int ret;
};

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

static void __client_connection_result_cb(const char *service_name,
		const cion_peer_info_h peer_info,
		const cion_connection_result_h result, void *user_data)
{
}

static void __client_connection_result_cb1(const char *service_name,
		const cion_peer_info_h peer_info,
		const cion_connection_result_h result, void *user_data)
{
	sleep(2);
	__stop_polling_loop();
}

void utc_cion_client_startup(void)
{
}

void utc_cion_client_cleanup(void)
{
}

/**
 * @testcase		utc_cion_client_create_p
 * @since_tizen		6.5
 * @description		Creates a cion client.
 */
int utc_cion_client_create_p(void)
{
	int ret;
	cion_client_h client;

	ret = cion_client_create(&client, "utc_cion_client_create_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_client_destroy(client);

	return 0;
}

/**
 * @testcase		utc_cion_client_create_n
 * @since_tizen		6.5
 * @description		Creates a cion client for negative case.
 */
int utc_cion_client_create_n(void)
{
	int ret;
	cion_client_h client = NULL;

	ret = cion_client_create(NULL, "utc_cion_client_create_n", NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_create(&client, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_client_destroy_p
 * @since_tizen		6.5
 * @description		Destroys a cion client.
 */
int utc_cion_client_destroy_p(void)
{
	int ret;
	cion_client_h client;

	ret = cion_client_create(&client, "utc_cion_client_destroy_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_destroy(client);
	assert_eq(ret, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_client_destroy_n
 * @since_tizen		6.5
 * @description		Destroys a cion client for negative case.
 */
int utc_cion_client_destroy_n(void)
{
	int ret;

	ret = cion_client_destroy(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __client_server_discovered_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
}

/**
 * @testcase		utc_cion_client_try_discovery_p
 * @since_tizen		6.5
 * @description		Tries to discovery cion server.
 */
int utc_cion_client_try_discovery_p(void)
{
	int ret;
	cion_client_h client;

	ret = cion_client_create(&client, "utc_cion_client_try_discovery_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_client_destroy(client);

	return 0;
}

/**
 * @testcase		utc_cion_client_try_discovery_n
 * @since_tizen		6.5
 * @description		Tries to discovery cion server for negative case.
 */
int utc_cion_client_try_discovery_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;

	ret = cion_client_try_discovery(NULL, __client_server_discovered_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_try_discovery(client, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_client_stop_discovery_p
 * @since_tizen		6.5
 * @description		Stops to discovery cion server.
 */
int utc_cion_client_stop_discovery_p(void)
{
	int ret;
	cion_client_h client;

	ret = cion_client_create(&client, "utc_cion_client_stop_discovery_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_stop_discovery(client);
	assert_eq(ret, CION_ERROR_NONE);

	cion_client_destroy(client);

	return 0;
}

/**
 * @testcase		utc_cion_client_stop_discovery_n
 * @since_tizen		6.5
 * @description		Stops to discovery cion server for nagative case.
 */
int utc_cion_client_stop_discovery_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;

	ret = cion_client_stop_discovery(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_create(&client, "utc_cion_client_stop_discovery_n", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_stop_discovery(client);
	assert_eq(ret, CION_ERROR_INVALID_OPERATION);

	cion_client_destroy(client);

	return 0;
}

static void __server_connection_request_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_server_h server = (cion_server_h)user_data;

	ret = cion_server_accept(server, peer_info);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "[%s] Failed to accept client", __func__);
}

static void __client_server_discovered_cb2(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_peer_info_h *peer = (cion_peer_info_h *)user_data;

	dlog_print(DLOG_INFO, LOG_TAG, "[%s] server discovered", __func__);
	ret = cion_peer_info_clone(peer_info, peer);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG,
				"[%s] Failed to clone peer info", __func__);

	__stop_polling_loop();
}

/**
 * @testcase		utc_cion_client_connect_p
 * @since_tizen		6.5
 * @description		Connects to a cion server.
 */
int utc_cion_client_connect_p(void)
{
	int ret;
	cion_client_h client;
	cion_server_h server;
	cion_peer_info_h peer = NULL;

	ret = cion_server_create(&server, "utc_cion_client_connect_p",
			"utc_cion_client_connect_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client, "utc_cion_client_connect_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_connection_result_cb(client,
			__client_connection_result_cb1, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_listen(server, __server_connection_request_cb, server);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb2,
			&peer);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG, "[%s] Wait for discovering server", __func__);
	__run_polling_loop();

	assert_neq(peer, NULL);

	ret = cion_client_connect(client, peer);
	assert_eq(ret, CION_ERROR_NONE);

	__run_polling_loop();

	cion_peer_info_destroy(peer);
	cion_client_destroy(client);
	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_client_connect_n
 * @since_tizen		6.5
 * @description		Connects to a cion server for negative case.
 */
int utc_cion_client_connect_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;
	cion_peer_info_h peer = (cion_peer_info_h)1;

	ret = cion_client_connect(NULL, peer);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_connect(client, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __client_server_discovered_cb3(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	struct cbdata *cbdata = (struct cbdata *)user_data;

	ret = cion_client_connect(cbdata->client, peer_info);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG,
				"[%s] Failed to connect to server", __func__);
	else
		cbdata->connected = true;

	__stop_polling_loop();
}


static void __client_server_discovered_cb4(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	struct cbdata *cbdata = (struct cbdata *)user_data;

	ret = cion_client_connect(cbdata->client, peer_info);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG,
				"[%s] Failed to connect to server", __func__);
	else
		cbdata->connected = true;
}

void __server_data_received_cb(const char *service_name,
		const cion_peer_info_h peer_info, const unsigned char *data,
		unsigned int data_size, unsigned char **return_data,
		unsigned int *return_data_size, void *user_data) {
	char str[] ="data_result";
	*return_data = (unsigned char *)strdup(str);
	*return_data_size = strlen(str);
}

static gpointer __send_data_thread(gpointer data)
{
	unsigned char str[] = "data_test";
	struct send_data *send_data = (struct send_data *)data;

	send_data->ret = cion_client_send_data(send_data->client, str,
			strlen((const char*)str), 5000,
			&send_data->return_data, &send_data->return_data_size);

	__stop_polling_loop();

	return NULL;
}

/**
 * @testcase		utc_cion_client_disconnect_p
 * @since_tizen		6.5
 * @description		Disonnects to a cion server.
 */
int utc_cion_client_disconnect_p(void)
{
	int ret;
	cion_server_h server;
	struct cbdata cbdata = { 0 };

	ret = cion_server_create(&server, "utc_cion_client_disconnect_p",
			"utc_cion_client_disconnect_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&cbdata.client, "utc_cion_client_disconnect_p",
			NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_connection_result_cb(cbdata.client,
			__client_connection_result_cb1, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_listen(server, __server_connection_request_cb, server);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(cbdata.client, __client_server_discovered_cb3,
			&cbdata);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for discovering to server", __func__);
	__run_polling_loop();

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for connecting to server", __func__);
	__run_polling_loop();

	assert_eq(cbdata.connected, true);

	ret = cion_client_disconnect(cbdata.client);
	assert_eq(ret, CION_ERROR_NONE);

	cion_client_destroy(cbdata.client);
	cion_server_destroy(server);

	return 0;
}

/**
 * @testcase		utc_cion_client_disconnect_n
 * @since_tizen		6.5
 * @description		Disonnects to a cion server for negative case.
 */
int utc_cion_client_disconnect_n(void)
{
	int ret;

	ret = cion_client_disconnect(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_client_send_data_p
 * @since_tizen		6.5
 * @description		Sends data to a cion server.
 */
int utc_cion_client_send_data_p(void)
{
	int ret;
	cion_client_h client;
	cion_server_h server;
	GThread *thread;
	struct send_data cbdata = { 0 };
	struct send_data send_data = { 0 };

	ret = cion_server_create(&server,
			"utc_cion_client_send_data_p",
			"utc_cion_client_send_data_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client,
			"utc_cion_client_send_data_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_set_data_received_cb(server, __server_data_received_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_listen(server, __server_connection_request_cb, server);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_connection_result_cb(client,
			__client_connection_result_cb1, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cbdata.client = client;
	ret = cion_client_try_discovery(client, __client_server_discovered_cb4,
			&cbdata);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for discovering & connecting to server", __func__);

	__run_polling_loop();

	send_data.client = client;
	thread = g_thread_new("send_data", __send_data_thread, &send_data);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for send data result", __func__);

	__run_polling_loop();

	assert_eq(send_data.ret, CION_ERROR_NONE);
	assert_eq(strncmp((const char *)send_data.return_data, "data_result",
			send_data.return_data_size), 0);

	free(send_data.return_data);
	g_thread_unref(thread);
	cion_client_destroy(client);
	cion_server_destroy(server);

	/* cannot test sync API */
	return 0;
}

/**
 * @testcase		utc_cion_client_send_data_n
 * @since_tizen		6.5
 * @description		Sends data to a cion server for negative case.
 */
int utc_cion_client_send_data_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;
	unsigned char data[] = { 0 };
	unsigned char *return_data;
	unsigned int return_data_size;

	ret = cion_client_send_data(NULL, data, sizeof(data), 5, &return_data,
			&return_data_size);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_send_data(client, NULL, sizeof(data), 5, &return_data,
			&return_data_size);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_send_data(client, data, 0, 5, &return_data,
			&return_data_size);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_send_data(client, data, sizeof(data), 5, NULL,
			&return_data_size);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_send_data(client, data, sizeof(data), 5, &return_data,
			NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_client_send_payload_async_p
 * @since_tizen		6.5
 * @description		Sends payload to a cion server asynchronously.
 */
int utc_cion_client_send_payload_async_p(void)
{
	int ret;
	cion_client_h client;
	cion_server_h server;
	cion_payload_h payload;
	unsigned char data[] = "utc_cion_client_send_payload_async_p";
	struct cbdata cbdata;

	ret = cion_server_create(&server,
			"utc_cion_client_send_payload_async_p",
			"utc_cion_client_send_payload_async_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client,
			"utc_cion_client_send_payload_async_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_connection_result_cb(client,
			__client_connection_result_cb1, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_server_listen(server, __server_connection_request_cb, server);
	assert_eq(ret, CION_ERROR_NONE);

	cbdata.client = client;
	cbdata.connected = false;

	ret = cion_client_try_discovery(client, __client_server_discovered_cb3,
			&cbdata);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for discovering to server", __func__);
	__run_polling_loop();

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for connecting to server", __func__);
	__run_polling_loop();

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_DATA);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_data(payload, data, sizeof(data));
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_send_payload_async(client, payload, NULL, NULL);
	assert_eq(ret, CION_ERROR_NONE);
	cion_payload_destroy(payload);
	cion_client_destroy(client);
	cion_server_destroy(server);

	return 0;
}

static void __client_payload_async_result_cb(
		const cion_payload_async_result_h result, void *user_data)
{
}

/**
 * @testcase		utc_cion_client_send_payload_async_n
 * @since_tizen		6.5
 * @description		Sends payload to a cion server asynchronously for negative case.
 */
int utc_cion_client_send_payload_async_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;
	cion_payload_h payload = (cion_payload_h)1;

	ret = cion_client_send_payload_async(NULL, payload,
			__client_payload_async_result_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_send_payload_async(client, NULL,
			__client_payload_async_result_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_client_add_connection_result_cb_p
 * @since_tizen		6.5
 * @description		Adds a connection result callback function.
 */
int utc_cion_client_add_connection_result_cb_p(void)
{
	int ret;
	cion_client_h client;

	ret = cion_client_create(&client,
			"utc_cion_client_add_connection_result_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_connection_result_cb(client,
			__client_connection_result_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_client_destroy(client);

	return 0;
}

/**
 * @testcase		utc_cion_client_add_connection_result_cb_n
 * @since_tizen		6.5
 * @description		Adds a connection result callback function for negative case.
 */
int utc_cion_client_add_connection_result_cb_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;

	ret = cion_client_add_connection_result_cb(NULL,
			__client_connection_result_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_add_connection_result_cb(client, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_client_remove_connection_result_cb_p
 * @since_tizen		6.5
 * @description		Removes a connection result callback function.
 */
int utc_cion_client_remove_connection_result_cb_p(void)
{
	int ret;
	cion_client_h client;

	ret = cion_client_create(&client,
			"utc_cion_client_remove_connection_result_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_connection_result_cb(client,
			__client_connection_result_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_remove_connection_result_cb(client,
			__client_connection_result_cb);
	assert_eq(ret, CION_ERROR_NONE);

	cion_client_destroy(client);

	return 0;
}

/**
 * @testcase		utc_cion_client_remove_connection_result_cb_n
 * @since_tizen		6.5
 * @description		Removes a connection result callback function for negative case.
 */
int utc_cion_client_remove_connection_result_cb_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;

	ret = cion_client_remove_connection_result_cb(NULL,
			__client_connection_result_cb);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_remove_connection_result_cb(client, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __client_payload_received_cb(const char *service_name,
		const cion_peer_info_h peer_info, const cion_payload_h payload,
		cion_payload_transfer_status_e status,
		void *user_data)
{
}

/**
 * @testcase		utc_cion_client_add_payload_received_cb_p
 * @since_tizen		6.5
 * @description		Adds a callback function to receive payload.
 */
int utc_cion_client_add_payload_received_cb_p(void)
{
	int ret;
	cion_client_h client;

	ret = cion_client_create(&client,
			"utc_cion_client_add_payload_received_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_payload_received_cb(client,
			__client_payload_received_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_client_destroy(client);

	return 0;
}

/**
 * @testcase		utc_cion_client_add_payload_received_cb_n
 * @since_tizen		6.5
 * @description		Adds a callback function to receive payload for negative case.
 */
int utc_cion_client_add_payload_received_cb_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;

	ret = cion_client_add_payload_received_cb(NULL,
			__client_payload_received_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_add_payload_received_cb(client, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_client_remove_payload_received_cb_p
 * @since_tizen		6.5
 * @description		Removes a callback function to receive payload.
 */
int utc_cion_client_remove_payload_received_cb_p(void)
{
	int ret;
	cion_client_h client;

	ret = cion_client_create(&client,
			"utc_cion_client_remove_payload_received_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_payload_received_cb(client,
			__client_payload_received_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_remove_payload_received_cb(client,
			__client_payload_received_cb);
	assert_eq(ret, CION_ERROR_NONE);

	cion_client_destroy(client);

	return 0;
}

/**
 * @testcase		utc_cion_client_remove_payload_received_cb_n
 * @since_tizen		6.5
 * @description		Removes a callback function to receive payload for negative case.
 */
int utc_cion_client_remove_payload_received_cb_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;

	ret = cion_client_remove_payload_received_cb(NULL,
			__client_payload_received_cb);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_remove_connection_result_cb(client, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __client_disconnected_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
}

/**
 * @testcase		utc_cion_client_add_disconnected_cb_p
 * @since_tizen		6.5
 * @description		Adds a callback function to get disconnected info.
 */
int utc_cion_client_add_disconnected_cb_p(void)
{
	int ret;
	cion_client_h client;

	ret = cion_client_create(&client,
			"utc_cion_client_add_disconnected_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_disconnected_cb(client,
			__client_disconnected_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	cion_client_destroy(client);

	return 0;
}

/**
 * @testcase		utc_cion_client_add_disconnected_cb_n
 * @since_tizen		6.5
 * @description		Adds a callback function to get disconnected info for nagative case.
 */
int utc_cion_client_add_disconnected_cb_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;

	ret = cion_client_add_disconnected_cb(NULL,
			__client_disconnected_cb, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_add_disconnected_cb(client, NULL, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_cion_client_remove_disconnected_cb_p
 * @since_tizen		6.5
 * @description		Removes a callback function to get disconnected info.
 */
int utc_cion_client_remove_disconnected_cb_p(void)
{
	int ret;
	cion_client_h client;

	ret = cion_client_create(&client,
			"utc_cion_client_remove_disconnected_cb_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_disconnected_cb(client,
			__client_disconnected_cb, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_remove_disconnected_cb(client, __client_disconnected_cb);
	assert_eq(ret, CION_ERROR_NONE);

	cion_client_destroy(client);

	return 0;
}

/**
 * @testcase		utc_cion_client_remove_disconnected_cb_n
 * @since_tizen		6.5
 * @description		Removes a callback function to get disconnected info for negative case.
 */
int utc_cion_client_remove_disconnected_cb_n(void)
{
	int ret;
	cion_client_h client = (cion_client_h)1;

	ret = cion_client_remove_disconnected_cb(NULL,
			__client_disconnected_cb);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_client_remove_disconnected_cb(client, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}
