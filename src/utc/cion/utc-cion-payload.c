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

#include <app_common.h>
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
cion_payload_h payload;

void utc_cion_payload_startup(void)
{
	int ret;

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_DATA);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create payload");
}

void utc_cion_payload_cleanup(void)
{
	cion_payload_destroy(payload);
	payload = NULL;
}

/**
 * @testcase		utc_cion_payload_create_p
 * @since_tizen		6.5
 * @description		Creates payload.
 */
int utc_cion_payload_create_p(void)
{
    int ret;
    cion_payload_h datapayload = NULL;

    ret = cion_payload_create(&datapayload, CION_PAYLOAD_TYPE_DATA);
    assert_eq(ret, CION_ERROR_NONE);

    cion_payload_destroy(datapayload);

    return 0;
}

/**
 * @testcase		utc_cion_payload_create_n
 * @since_tizen		6.5
 * @description		Creates payload for negative case.
 */
int utc_cion_payload_create_n(void)
{
	int ret;

	ret = cion_payload_create(NULL, CION_PAYLOAD_TYPE_DATA);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_payload_destroy_p
 * @since_tizen		6.5
 * @description		Destroys payload.
 */
int utc_cion_payload_destroy_p(void)
{
	int ret;
	cion_payload_h datapayload = NULL;

	ret = cion_payload_create(&datapayload, CION_PAYLOAD_TYPE_DATA);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_destroy(datapayload);
	assert_eq(ret, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_payload_destroy_p
 * @since_tizen		6.5
 * @description		Destroys payload for negative case.
 */
int utc_cion_payload_destroy_n(void)
{
	int ret;

	ret = cion_payload_destroy(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_payload_get_type_p
 * @since_tizen		6.5
 * @description		Gets payload type.
 */
int utc_cion_payload_get_type_p(void)
{
	int ret;
	cion_payload_type_e type;

	ret = cion_payload_get_type(payload, &type);
	assert_eq(ret, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_payload_get_type_n
 * @since_tizen		6.5
 * @description		Gets payload type for negative case.
 */
int utc_cion_payload_get_type_n(void)
{
	int ret;
	cion_payload_type_e type;

	ret = cion_payload_get_type(NULL, &type);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_get_type(payload, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_payload_get_data_p
 * @since_tizen		6.5
 * @description		Gets data.
 */
int utc_cion_payload_get_data_p(void)
{
	int ret;
	unsigned char data[] = "utc_cion_payload_get_data_p";
	unsigned char *get_data = NULL;
	unsigned int data_size = 0;

	ret = cion_payload_set_data(payload, data, sizeof(data));
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_get_data(payload, &get_data, &data_size);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(get_data, NULL);
	assert_eq(data_size, sizeof(data));

	return 0;
}

/**
 * @testcase		utc_cion_payload_get_data_n
 * @since_tizen		6.5
 * @description		Gets data for negative case.
 */
int utc_cion_payload_get_data_n(void)
{
	int ret;
	unsigned char *data;
	unsigned int data_size;

	ret = cion_payload_get_data(NULL, &data, &data_size);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_get_data(payload, NULL, &data_size);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_get_data(payload, &data, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_payload_set_data_p
 * @since_tizen		6.5
 * @description		Sets data.
 */
int utc_cion_payload_set_data_p(void)
{
	int ret;
	unsigned char data[] = "utc_cion_payload_set_data_p";

	ret = cion_payload_set_data(payload, data, sizeof(data));
	assert_eq(ret, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_payload_set_data_n
 * @since_tizen		6.5
 * @description		Sets data for negative case.
 */
int utc_cion_payload_set_data_n(void)
{
	int ret;
	unsigned char data[] = "utc_cion_payload_set_data_n";

	ret = cion_payload_set_data(NULL, data, sizeof(data));
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_set_data(payload, NULL, sizeof(data));
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_set_data(payload, data, 0);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

struct cbdata {
	cion_client_h client;
	bool connected;
};

static void __server_connection_request_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_server_h server = (cion_server_h)user_data;
	ret = cion_server_accept(server, peer_info);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to accept client");
}

static void __client_server_discovered_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;
	cion_client_h client = (cion_client_h)user_data;

	ret = cion_client_connect(client, peer_info);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to connect server");
}

static void __connection_result_cb(const char *service_name,
		const cion_peer_info_h peer_info,
		const cion_connection_result_h result, void *user_data)
{
	int ret;
	cion_connection_status_e status = CION_CONNECTION_STATUS_ERROR;
	bool *connected = (bool *)user_data;

	ret = cion_connection_result_get_status(result, &status);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG,	"Failed to get connection result");

	if (status == CION_CONNECTION_STATUS_OK) {
		dlog_print(DLOG_INFO, LOG_TAG, "CONNECTED");
		*connected = true;
	} else {
		dlog_print(DLOG_INFO, LOG_TAG, "NOT CONNECTED");
		*connected = false;
	}

	__stop_polling_loop();
}

static void __server_payload_received_cb(const char *service_name,
		const cion_peer_info_h peer_info, const cion_payload_h payload,
		cion_payload_transfer_status_e status, void *user_data)
{
	char *data_path;
	char save_as[PATH_MAX];
	int *result = (int *)user_data;

	if (status == CION_PAYLOAD_TRANSFER_STATUS_FAILURE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
		"Payload transfer status failure");
		return;
	}

	if (status == CION_PAYLOAD_TRANSFER_STATUS_IN_PROGRESS) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Payload transfer is in progress");
		return;
	}

	data_path = app_get_data_path();
	snprintf(save_as, sizeof(save_as), "%s/download.png", data_path);
	free(data_path);

	*result = cion_payload_save_as_file(payload, save_as);

	__stop_polling_loop();
}

/**
 * @testcase		utc_cion_payload_save_as_file_p
 * @since_tizen		6.5
 * @description		Saves a received file payload as a file.
 */
int utc_cion_payload_save_as_file_p(void)
{
	int ret;
	cion_client_h client;
	cion_server_h server;
	bool connected = false;
	cion_payload_h payload;
	char icon_path[PATH_MAX];
	char *shared_res_path;
	int result = CION_ERROR_OPERATION_FAILED;

	ret = cion_server_create(&server,
			"utc_cion_payload_save_as_file_p",
			"utc_cion_payload_save_as_file_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client,
			"utc_cion_payload_save_as_file_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_connection_result_cb(client,
			__connection_result_cb, &connected);

	ret = cion_server_listen(server, __server_connection_request_cb, server);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb, client);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for discovering & connecting to server", __func__);
	__run_polling_loop();

	ret = cion_server_add_payload_received_cb(server,
			__server_payload_received_cb, &result);
	assert_eq(ret, CION_ERROR_NONE);

	shared_res_path = app_get_shared_resource_path();
	snprintf(icon_path, sizeof(icon_path), "%s/cion-native-utc.png",
	shared_res_path);
	free(shared_res_path);

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_FILE);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_file_path(payload, icon_path);

	ret = cion_client_send_payload_async(client, payload, NULL, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for sending file to server",	__func__);
	__run_polling_loop();

	cion_client_destroy(client);
	cion_server_destroy(server);

	assert_eq(result, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_payload_save_as_file_n
 * @since_tizen		6.5
 * @description		Saves a received file payload as a file for negative case.
 */
int utc_cion_payload_save_as_file_n(void)
{
	int ret;

	ret = cion_payload_save_as_file(NULL, "path");
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_save_as_file(payload, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __server_payload_received_cb2(const char *service_name,
		const cion_peer_info_h peer_info, const cion_payload_h payload,
		cion_payload_transfer_status_e status, void *user_data)
{
	int *result = (int *)user_data;
	char *file_name;

	if (status == CION_PAYLOAD_TRANSFER_STATUS_FAILURE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Payload transfer status failure");
		return;
	}

	if (status == CION_PAYLOAD_TRANSFER_STATUS_IN_PROGRESS) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Payload transfer is in progress");
		return;
	}

	*result = cion_payload_get_received_file_name(payload, &file_name);
	dlog_print(DLOG_INFO, LOG_TAG, "Received file name: %s", file_name);
	free(file_name);
	__stop_polling_loop();
}

/**
 * @testcase		utc_cion_payload_get_received_file_name_p
 * @since_tizen		6.5
 * @description		Gets a received file name.
 */
int utc_cion_payload_get_received_file_name_p(void)
{
	int ret;
	cion_client_h client;
	cion_server_h server;
	bool connected = false;
	cion_payload_h payload;
	char icon_path[PATH_MAX];
	char *shared_res_path;
	int result = CION_ERROR_OPERATION_FAILED;

	ret = cion_server_create(&server,
			"utc_cion_payload_get_received_file_name_p",
			"utc_cion_payload_get_received_file_name_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client,
			"utc_cion_payload_get_received_file_name_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_connection_result_cb(client,
			__connection_result_cb, &connected);

	ret = cion_server_listen(server, __server_connection_request_cb, server);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb, client);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for discovering & connecting to server", __func__);
	__run_polling_loop();

	ret = cion_server_add_payload_received_cb(server,
			__server_payload_received_cb2, &result);
	assert_eq(ret, CION_ERROR_NONE);

	shared_res_path = app_get_shared_resource_path();
	snprintf(icon_path, sizeof(icon_path), "%s/cion-native-utc.png",
	shared_res_path);
	free(shared_res_path);

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_FILE);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_file_path(payload, icon_path);

	ret = cion_client_send_payload_async(client, payload, NULL, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for sending file to server", __func__);
	__run_polling_loop();

	cion_client_destroy(client);
	cion_server_destroy(server);

	assert_eq(result, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_payload_get_received_file_name_n
 * @since_tizen		6.5
 * @description		Gets a received file name for negative case.
 */
int utc_cion_payload_get_received_file_name_n(void)
{
	int ret;
	char *file_name;

	ret = cion_payload_get_received_file_name(NULL, &file_name);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_get_received_file_name(payload, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

static void __server_payload_received_cb3(const char *service_name,
		const cion_peer_info_h peer_info, const cion_payload_h payload,
		cion_payload_transfer_status_e status, void *user_data)
{
	int *result = (int *)user_data;
	uint64_t bytes;

	if (status == CION_PAYLOAD_TRANSFER_STATUS_FAILURE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Payload transfer status failure");
		return;
	}

	if (status == CION_PAYLOAD_TRANSFER_STATUS_IN_PROGRESS) {
		dlog_print(DLOG_ERROR, LOG_TAG,	"Payload transfer is in progress");
		return;
	}

	*result = cion_payload_get_received_bytes(payload, &bytes);
	dlog_print(DLOG_INFO, LOG_TAG, "Received bytes: %llu", bytes);
	__stop_polling_loop();
}

/**
 * @testcase		utc_cion_payload_get_received_bytes_p
 * @since_tizen		6.5
 * @description		Gets received file bytes.
 */
int utc_cion_payload_get_received_bytes_p(void)
{
	int ret;
	cion_client_h client;
	cion_server_h server;
	bool connected = false;
	cion_payload_h payload;
	char icon_path[PATH_MAX];
	char *shared_res_path;
	int result = CION_ERROR_OPERATION_FAILED;

	ret = cion_server_create(&server,
			"utc_cion_payload_get_received_bytes_p",
			"utc_cion_payload_get_received_bytes_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client,
			"utc_cion_payload_get_received_bytes_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_connection_result_cb(client,
			__connection_result_cb, &connected);

	ret = cion_server_listen(server, __server_connection_request_cb, server);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb,
			client);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for discovering & connecting to server", __func__);
	__run_polling_loop();

	ret = cion_server_add_payload_received_cb(server,
			__server_payload_received_cb3, &result);
	assert_eq(ret, CION_ERROR_NONE);

	shared_res_path = app_get_shared_resource_path();
	snprintf(icon_path, sizeof(icon_path), "%s/cion-native-utc.png",
			shared_res_path);
	free(shared_res_path);

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_FILE);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_file_path(payload, icon_path);

	ret = cion_client_send_payload_async(client, payload, NULL, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for sending file to server", __func__);
	__run_polling_loop();

	cion_client_destroy(client);
	cion_server_destroy(server);

	assert_eq(result, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_payload_get_received_bytes_n
 * @since_tizen		6.5
 * @description		Gets received file bytes for negative case.
 */
int utc_cion_payload_get_received_bytes_n(void)
{
    int ret;
    uint64_t bytes;

    ret = cion_payload_get_received_bytes(NULL, &bytes);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    ret = cion_payload_get_received_bytes(payload, NULL);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    return 0;
}

static void __server_payload_received_cb4(const char *service_name,
		const cion_peer_info_h peer_info, const cion_payload_h payload,
		cion_payload_transfer_status_e status, void *user_data)
{
	int *result = (int *)user_data;
	uint64_t bytes;

	if (status == CION_PAYLOAD_TRANSFER_STATUS_FAILURE) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Payload transfer status failure");
		return;
	}

	if (status == CION_PAYLOAD_TRANSFER_STATUS_IN_PROGRESS) {
		dlog_print(DLOG_ERROR, LOG_TAG,
				"Payload transfer is in progress");
		return;
	}

	*result = cion_payload_get_total_bytes(payload, &bytes);
	dlog_print(DLOG_INFO, LOG_TAG, "Total bytes: %llu", bytes);
	__stop_polling_loop();
}

/**
 * @testcase		utc_cion_payload_get_total_bytes_p
 * @since_tizen		6.5
 * @description		Gets total bytes of received file.
 */
int utc_cion_payload_get_total_bytes_p(void)
{
	int ret;
	cion_client_h client;
	cion_server_h server;
	bool connected = false;
	cion_payload_h payload;
	char icon_path[PATH_MAX];
	char *shared_res_path;
	int result = CION_ERROR_OPERATION_FAILED;

	ret = cion_server_create(&server,
			"utc_cion_payload_get_total_bytes_p",
			"utc_cion_payload_get_total_bytes_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_create(&client,
			"utc_cion_payload_get_total_bytes_p", NULL);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_add_connection_result_cb(client,
			__connection_result_cb, &connected);

	ret = cion_server_listen(server, __server_connection_request_cb, server);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_client_try_discovery(client, __client_server_discovered_cb, client);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for discovering & connecting to server", __func__);
	__run_polling_loop();

	ret = cion_server_add_payload_received_cb(server,
			__server_payload_received_cb4, &result);
	assert_eq(ret, CION_ERROR_NONE);

	shared_res_path = app_get_shared_resource_path();
	snprintf(icon_path, sizeof(icon_path), "%s/cion-native-utc.png",
			shared_res_path);
	free(shared_res_path);

	ret = cion_payload_create(&payload, CION_PAYLOAD_TYPE_FILE);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_file_path(payload, icon_path);

	ret = cion_client_send_payload_async(client, payload, NULL, NULL);
	assert_eq(ret, CION_ERROR_NONE);

	dlog_print(DLOG_INFO, LOG_TAG,
			"[%s] Wait for sending file to server", __func__);
	__run_polling_loop();

	cion_client_destroy(client);
	cion_server_destroy(server);

	assert_eq(result, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_payload_get_total_bytes_n
 * @since_tizen		6.5
 * @description		Gets total bytes of received file for negative case.
 */
int utc_cion_payload_get_total_bytes_n(void)
{
	int ret;
	uint64_t bytes;

	ret = cion_payload_get_total_bytes(NULL, &bytes);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_get_total_bytes(payload, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_payload_set_file_path_p
 * @since_tizen		6.5
 * @description		Sets file path.
 */
int utc_cion_payload_set_file_path_p(void)
{
	int ret;
	cion_payload_h file_payload;
	char *res_path;
	char path[PATH_MAX];

	res_path = app_get_shared_resource_path();

	snprintf(path, sizeof(path), "%s/cion-native-utc.png", res_path);
	free(res_path);

	ret = cion_payload_create(&file_payload, CION_PAYLOAD_TYPE_FILE);
	assert_eq(ret, CION_ERROR_NONE);

	ret = cion_payload_set_file_path(file_payload, path);
	assert_eq(ret, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_payload_set_file_path_n
 * @since_tizen		6.5
 * @description		Sets file path for negative case.
 */
int utc_cion_payload_set_file_path_n(void)
{
	int ret;

	ret = cion_payload_set_file_path(NULL, "path");
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_set_file_path(payload, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_payload_get_payload_id_p
 * @since_tizen		6.5
 * @description		Gets payload id.
 */
int utc_cion_payload_get_payload_id_p(void)
{
	int ret;
	char *payload_id = NULL;

	ret = cion_payload_get_payload_id(payload, &payload_id);
	assert_eq(ret, CION_ERROR_NONE);

	free(payload_id);

	return 0;
}

/**
 * @testcase		utc_cion_payload_get_payload_id_n
 * @since_tizen		6.5
 * @description		Gets payload id for negative case.
 */
int utc_cion_payload_get_payload_id_n(void)
{
	int ret;
	char *payload_id;

	ret = cion_payload_get_payload_id(NULL, &payload_id);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_payload_get_payload_id(payload, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}
