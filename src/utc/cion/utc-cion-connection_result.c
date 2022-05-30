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
cion_peer_info_h peer;
int get_status_test_result;
int get_reason_test_result;
cion_connection_status_e status = CION_CONNECTION_STATUS_ERROR;
bool connected;

static void __connection_request_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;

	ret = cion_server_reject(server, peer_info, "test reason");
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to accept client");
}

static void __server_discovered_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;

	ret = cion_client_connect(client, peer_info);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to connect");
	    return;
	}

	dlog_print(DLOG_INFO, LOG_TAG, "Found server and connect");
}

static void __connection_result_cb(const char * service_name,
                const cion_peer_info_h peer_info,
                const cion_connection_result_h result, void * user_data)
{
	char *reason = NULL;

	get_status_test_result = cion_connection_result_get_status(result, &status);

	get_reason_test_result = cion_connection_result_get_reason(result, &reason);
	if (reason)
		free(reason);

	connected = true;
	__stop_polling_loop();
}

void utc_cion_connection_result_startup(void)
{
	int ret;

	if (connected)
	return;

	ret = cion_server_create(&server,
			"utc_cion_connection_result_startup",
			"utc_cion_connection_result_startup", NULL);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create server");
		return;
	}

	ret = cion_client_create(&client, "utc_cion_connection_result_startup",	NULL);
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

void utc_cion_connection_result_cleanup(void)
{
	int ret;

	connected = false;
	if (peer) {
		ret = cion_peer_info_destroy(peer);
		if (ret != CION_ERROR_NONE)
			dlog_print(DLOG_ERROR, LOG_TAG, "Failed to destroy peer info");
		peer = NULL;
	}

	if (client) {
		ret = cion_client_destroy(client);
		if (ret != CION_ERROR_NONE)
			dlog_print(DLOG_ERROR, LOG_TAG, "Failed to destroy client");
		client = NULL;
	}

	if (server) {
		ret = cion_server_destroy(server);
		if (ret != CION_ERROR_NONE)
			dlog_print(DLOG_ERROR, LOG_TAG, "Failed to destroy server");
		server = NULL;
	}

}

/**
 * @testcase		utc_cion_connection_result_get_status_p
 * @since_tizen		6.5
 * @description		Gets connection result status.
 */
int utc_cion_connection_result_get_status_p(void)
{
	int ret;

	assert_eq(get_status_test_result, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_connection_result_get_status_n
 * @since_tizen		6.5
 * @description		Gets connection result status for negative case.
 */
int utc_cion_connection_result_get_status_n(void)
{
	int ret;
	cion_connection_result_h result = (cion_connection_result_h)1;
	cion_connection_status_e status;

	ret = cion_connection_result_get_status(NULL, &status);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_connection_result_get_status(&result, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_connection_result_get_reason_p
 * @since_tizen		6.5
 * @description		Gets connection result reason.
 */
int utc_cion_connection_result_get_reason_p(void)
{
	int ret;

	assert_eq(get_reason_test_result, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_connection_result_get_reason_n
 * @since_tizen		6.5
 * @description		Gets connection result reason for negative case.
 */
int utc_cion_connection_result_get_reason_n(void)
{
	int ret;
	cion_connection_result_h result = (cion_connection_result_h)1;
	char *reason = NULL;

	ret = cion_connection_result_get_reason(NULL, &reason);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_connection_result_get_reason(&result, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}
