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
bool discovered;

static void __connection_request_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
}

static void __server_discovered_cb(const char *service_name,
		const cion_peer_info_h peer_info, void *user_data)
{
	int ret;

	ret = cion_peer_info_clone(peer_info, &peer);
	if (ret != CION_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to clone peer info");

	dlog_print(DLOG_INFO, LOG_TAG, "Found server");
	discovered = true;

	__stop_polling_loop();
}

void utc_cion_peer_info_startup(void)
{
	int ret;

	if (discovered)
		return;

	ret = cion_server_create(&server, "utc_cion_peer_info_startup",
			"utc_cion_peer_info_startup", NULL);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create server");
		return;
	}

	ret = cion_client_create(&client, "utc_cion_peer_info_startup", NULL);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client");
		return;
	}

	ret = cion_server_listen(server, __connection_request_cb, NULL);
	if (ret != CION_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to listen");
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

void utc_cion_peer_info_cleanup(void)
{
	int ret;

	if (peer) {
		ret = cion_peer_info_destroy(peer);
		if (ret != CION_ERROR_NONE)
			dlog_print(DLOG_ERROR, LOG_TAG,	"Failed to destroy peer info");
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

	discovered = false;

}

/**
 * @testcase		utc_cion_peer_info_clone_p
 * @since_tizen		6.5
 * @description		Creates a clone of peer info.
 */
int utc_cion_peer_info_clone_p(void)
{
	int ret;
	cion_peer_info_h clone;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG, "precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_clone(peer, &clone);
	assert_eq(ret, CION_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_clone_n
 * @since_tizen		6.5
 * @description		Creates a clone of peer info for negative case.
 */
int utc_cion_peer_info_clone_n(void)
{
    int ret;
    cion_peer_info_h clone;

    ret = cion_peer_info_clone(NULL, &clone);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    ret = cion_peer_info_clone(peer, NULL);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_cion_peer_info_destroy_p
 * @since_tizen		6.5
 * @description		Destroys a peer info.
 */
int utc_cion_peer_info_destroy_p(void)
{
	int ret;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG, "precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_destroy(peer);
	assert_eq(ret, CION_ERROR_NONE);

	peer = NULL;

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_destroy_n
 * @since_tizen		6.5
 * @description		Destroys a peer info for negative case.
 */
int utc_cion_peer_info_destroy_n(void)
{
	int ret;

	ret = cion_peer_info_destroy(NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_device_id_p
 * @since_tizen		6.5
 * @description		Gets device id.
 */
int utc_cion_peer_info_get_device_id_p(void)
{
	int ret;
	char *device_id = NULL;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG, "precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_get_device_id(peer, &device_id);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(device_id, NULL);

	free(device_id);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_device_id_n
 * @since_tizen		6.5
 * @description		Gets device id for negative case.
 */
int utc_cion_peer_info_get_device_id_n(void)
{
    int ret;
    char *device_id;

    ret = cion_peer_info_get_device_id(NULL, &device_id);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    ret = cion_peer_info_get_device_id(peer, NULL);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_device_name_p
 * @since_tizen		6.5
 * @description		Gets device name.
 */
int utc_cion_peer_info_get_device_name_p(void)
{
	int ret;
	char *device_name = NULL;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG, "precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_get_device_name(peer, &device_name);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(device_name, NULL);

	free(device_name);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_device_name_n
 * @since_tizen		6.5
 * @description		Gets device name for negative case.
 */
int utc_cion_peer_info_get_device_name_n(void)
{
    int ret;
    char *device_name;

    ret = cion_peer_info_get_device_name(NULL, &device_name);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    ret = cion_peer_info_get_device_name(peer, NULL);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_device_platform_p
 * @since_tizen		6.5
 * @description		Gets device platform.
 */
int utc_cion_peer_info_get_device_platform_p(void)
{
	int ret;
	char *device_platform = NULL;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG, "precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_get_device_platform(peer, &device_platform);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(device_platform, NULL);

	free(device_platform);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_device_platform_n
 * @since_tizen		6.5
 * @description		Gets device platform.
 */
int utc_cion_peer_info_get_device_platform_n(void)
{
    int ret;
    char *device_platform;

    ret = cion_peer_info_get_device_platform(NULL, &device_platform);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    ret = cion_peer_info_get_device_platform(peer, NULL);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_device_platform_version_p
 * @since_tizen		6.5
 * @description		Gets device platform version.
 */
int utc_cion_peer_info_get_device_platform_version_p(void)
{
	int ret;
	char *device_platform_version = NULL;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG, "precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_get_device_platform_version(peer,
	&device_platform_version);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(device_platform_version, NULL);

	free(device_platform_version);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_device_platform_version_n
 * @since_tizen		6.5
 * @description		Gets device platform version for negative case.
 */
int utc_cion_peer_info_get_device_platform_version_n(void)
{
	int ret;
	char *device_platform_version;

	ret = cion_peer_info_get_device_platform_version(NULL, &device_platform_version);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_peer_info_get_device_platform_version(peer, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_device_type_p
 * @since_tizen		6.5
 * @description		Gets device type.
 */
int utc_cion_peer_info_get_device_type_p(void)
{
	int ret;
	char *device_type = NULL;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG, "precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_get_device_type(peer, &device_type);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(device_type, NULL);

	free(device_type);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_device_type_n
 * @since_tizen		6.5
 * @description		Gets device type for negative case.
 */
int utc_cion_peer_info_get_device_type_n(void)
{
	int ret;
	char *device_type;

	ret = cion_peer_info_get_device_type(NULL, &device_type);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	ret = cion_peer_info_get_device_type(peer, NULL);
	assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_app_id_p
 * @since_tizen		6.5
 * @description		Gets application id.
 */
int utc_cion_peer_info_get_app_id_p(void)
{
	int ret;
	char *app_id = NULL;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG, "precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_get_app_id(peer, &app_id);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(app_id, NULL);

	free(app_id);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_app_id_n
 * @since_tizen		6.5
 * @description		Gets application id for negative case.
 */
int utc_cion_peer_info_get_app_id_n(void)
{
    int ret;
    char *app_id;

    ret = cion_peer_info_get_app_id(NULL, &app_id);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    ret = cion_peer_info_get_app_id(peer, NULL);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_app_version_p
 * @since_tizen		6.5
 * @description		Gets application version.
 */
int utc_cion_peer_info_get_app_version_p(void)
{
	int ret;
	char *app_version = NULL;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG, "precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_get_app_version(peer, &app_version);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(app_version, NULL);

	free(app_version);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_app_version_n
 * @since_tizen		6.5
 * @description		Gets application version for negative case.
 */
int utc_cion_peer_info_get_app_version_n(void)
{
    int ret;
    char *app_version;

    ret = cion_peer_info_get_app_version(NULL, &app_version);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    ret = cion_peer_info_get_app_version(peer, NULL);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_uuid_p
 * @since_tizen		6.5
 * @description		Gets uuid.
 */
int utc_cion_peer_info_get_uuid_p(void)
{
	int ret;
	char *uuid = NULL;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG, "precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_get_uuid(peer, &uuid);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(uuid, NULL);

	free(uuid);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_uuid_n
 * @since_tizen		6.5
 * @description		Gets uuid for negative case.
 */
int utc_cion_peer_info_get_uuid_n(void)
{
    int ret;
    char *uuid;

    ret = cion_peer_info_get_uuid(NULL, &uuid);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    ret = cion_peer_info_get_uuid(peer, NULL);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_display_name_p
 * @since_tizen		6.5
 * @description		Gets display name.
 */
int utc_cion_peer_info_get_display_name_p(void)
{
	int ret;
	char *display_name = NULL;

	if (!discovered)
		dlog_print(DLOG_ERROR, LOG_TAG,	"precondition failed. server not discovered");
	assert_eq(discovered, true);

	ret = cion_peer_info_get_display_name(peer, &display_name);
	assert_eq(ret, CION_ERROR_NONE);
	assert_neq(display_name, NULL);

	free(display_name);

	return 0;
}

/**
 * @testcase		utc_cion_peer_info_get_display_name_n
 * @since_tizen		6.5
 * @description		Gets display name for negative case.
 */
int utc_cion_peer_info_get_display_name_n(void)
{
    int ret;
    char *display_name;

    ret = cion_peer_info_get_display_name(NULL,
			&display_name);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    ret = cion_peer_info_get_display_name(peer, NULL);
    assert_eq(ret, CION_ERROR_INVALID_PARAMETER);

    return 0;
}
