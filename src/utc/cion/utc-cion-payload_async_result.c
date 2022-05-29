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

cion_server_h server;
cion_client_h client;
bool connected = false;

static void __connection_request_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;

	ret = cion_server_accept(server, peer_info);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to accept client");
}

static void __server_discovered_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;

	ret = cion_client_connect(client, peer_info);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to connect to server1");

	dlog_print(DLOG_INFO, LOG_TAG, "Found server and try connect");
}

static void __connection_result_cb(const char *service_name,
		const cion_peer_info_h peer_info,
		const cion_connection_result_h result, void *user_data)
{
	cion_connection_status_e status;

	int ret = cion_connection_result_get_status(result, &status);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get connection status");
	if (status == CION_CONNECTION_STATUS_OK) {
		dlog_print(DLOG_INFO, LOG_TAG, "Connection established");
		connected = true;
	}
	__stop_polling_loop();
}

void utc_cion_payload_async_result_startup(void)
{
	int ret;

	if (connected)
		return;

	ret = cion_server_create(&server,
			"utc_cion_payload_async_result_startup",
			"utc_cion_payload_async_result_startup", NULL);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create server");
		return;
	}

	ret = cion_client_create(&client,
			"utc_cion_payload_async_result_startup", NULL);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client");
		return;
	}

	ret = cion_server_listen(server, __connection_request_cb, NULL);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to listen");
		return;
	}

	ret = cion_client_add_connection_result_cb(client,
			__connection_result_cb, NULL);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
		"Failed to add connection result cb");
		return;
	}

	ret = cion_client_try_discovery(client, __server_discovered_cb, NULL);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to try discovery");
		return;
	}

	dlog_print(DLOG_INFO, LOG_TAG, "[%s] Wait for discovering server", __func__);
	__run_polling_loop();
}

void utc_cion_payload_async_result_cleanup(void)
{

	int ret;

	connected = false;

	if (client) {
		ret = cion_client_destroy(client);
		if (ret != CION_ERROR_NONE)
			dlog_print(DLOG_ERROR, LOG_TAG, "Failed to destroy client");
		client = NULL;
	}

	if (server) {
		ret = cion_server_destroy(server);
		if (ret != CION_ERROR_NONE)
			dlog_print(DLOG_ERROR, LOG_TAG,	"Failed to destroy server");
		server = NULL;
	}

}

void __payload_async_result_cb(const cion_payload_async_result_h result,
		void *user_data)
{
	int ret;
	cion_payload_async_result_h *clone = (cion_payload_async_result_h *)user_data;

	ret = cion_payload_async_result_clone(result, clone);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to clone payload async result");

	__stop_polling_loop();
}

/**
 * @testcase		utc_cion_payload_async_result_clone_p
 * @since_tizen		6.5
 * @description		Creates a clone of payload async result .
 */
int utc_cion_payload_async_result_clone_p(void)
{
	int ret;
	cion_payload_h payload;
	cion_payload_async_result_h result = NULL;
	unsigned char data[] = "utc_cion_payload_async_result_clone_p";

	if (!connected) {
		dlog_print(DLOG_ERROR, LOG_TAG,	"Connection is not established");
		return 1;
	}

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_DATA);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_data(payload, data, sizeof(data));
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_send_payload_async(client, payload,
			__payload_async_result_cb, &result);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for send payload async result", __func__);
	__run_polling_loop();

	assert_neq(result, NULL);

	cion_payload_destroy(payload);
	cion_payload_async_result_destroy(result);

	return 0;
}

/**
 * @testcase		utc_cion_payload_async_result_clone_p
 * @since_tizen		6.5
 * @description		Creates a clone of payload async result for negative case.
 */
int utc_cion_payload_async_result_clone_n(void)
{
    int ret;
    cion_payload_async_result_h result = (cion_payload_async_result_h)1;
    cion_payload_async_result_h clone;

    ret = cion_payload_async_result_clone(NULL, &clone);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    ret = cion_payload_async_result_clone(result, NULL);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_cion_payload_async_result_destroy_p
 * @since_tizen		6.5
 * @description		Destroys a payload async result.
 */
int utc_cion_payload_async_result_destroy_p(void)
{
	int ret;
	cion_payload_h payload;
	cion_payload_async_result_h result = NULL;
	unsigned char data[] = "utc_cion_payload_async_result_destroy_p";

	if (!connected) {
		dlog_print(DLOG_ERROR, LOG_TAG,	"Connection is not established");
		return 1;
	}

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_DATA);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_data(payload, data, sizeof(data));
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_send_payload_async(client, payload,
			__payload_async_result_cb, &result);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for send payload async result", __func__);
	__run_polling_loop();

	assert_neq(result, NULL);
	cion_payload_destroy(payload);

	ret = cion_payload_async_result_destroy(result);
	assert_eq(ret, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_payload_async_result_destroy_n
 * @since_tizen		6.5
 * @description		Destroys a payload async result for negative case.
 */
int utc_cion_payload_async_result_destroy_n(void)
{
	int ret;

	ret = cion_payload_async_result_destroy(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_payload_async_result_get_peer_info_p
 * @since_tizen		6.5
 * @description		Gets peer info from payload async result.
 */
int utc_cion_payload_async_result_get_peer_info_p(void)
{
	int ret;
	cion_payload_h payload;
	cion_payload_async_result_h result = NULL;
	unsigned char data[] = "utc_cion_payload_async_result_get_peer_info_p";
	cion_peer_info_h peer = NULL;

	if (!connected) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Connection is not established");
		return 1;
	}

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_DATA);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_data(payload, data, sizeof(data));
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_send_payload_async(client, payload,
			__payload_async_result_cb, &result);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for send payload async result", __func__);
	__run_polling_loop();

	assert_neq(result, NULL);

	ret = cion_payload_async_result_get_peer_info(result, &peer);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(peer, NULL);

	cion_peer_info_destroy(peer);
	cion_payload_destroy(payload);

	cion_payload_async_result_destroy(result);

	return 0;
}

/**
 * @testcase		utc_cion_payload_async_result_get_peer_info_n
 * @since_tizen		6.5
 * @description		Gets peer info from payload async result for negative case.
 */
int utc_cion_payload_async_result_get_peer_info_n(void)
{
	int ret;
	cion_payload_async_result_h result = (cion_payload_async_result_h)1;
	cion_peer_info_h peer;

	ret = cion_payload_async_result_get_peer_info(NULL, &peer);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_async_result_get_peer_info(result, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_payload_async_result_get_payload_id_p
 * @since_tizen		6.5
 * @description		Gets payload id from payload async result.
 */
int utc_cion_payload_async_result_get_payload_id_p(void)
{
	int ret;
	cion_payload_h payload;
	cion_payload_async_result_h result = NULL;
	unsigned char data[] = "utc_cion_payload_async_result_get_payload_id_p";
	char *payload_id = NULL;

	if (!connected) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Connection is not established");
		return 1;
	}

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_DATA);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_data(payload, data, sizeof(data));
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_send_payload_async(client, payload,
			__payload_async_result_cb, &result);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for send payload async result", __func__);
	__run_polling_loop();

	assert_neq(result, NULL);

	ret = cion_payload_async_result_get_payload_id(result, &payload_id);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(payload_id, NULL);

	free(payload_id);
	cion_payload_destroy(payload);

	cion_payload_async_result_destroy(result);

	return 0;
}

/**
 * @testcase		utc_cion_payload_async_result_get_payload_id_n
 * @since_tizen		6.5
 * @description		Gets payload id from payload async result for negative case.
 */
int utc_cion_payload_async_result_get_payload_id_n(void)
{
	int ret;
	cion_payload_async_result_h result = (cion_payload_async_result_h)1;
	char *payload_id = NULL;

	ret = cion_payload_async_result_get_payload_id(NULL, &payload_id);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_async_result_get_payload_id(result, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}
