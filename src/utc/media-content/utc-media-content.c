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
#include <media_content.h>
#include <tct_common.h>
#include <storage.h>
#include <glib.h>

//& set: MediaContent

static GMainLoop *g_loop = NULL;
static const char *g_insert_file = "test.jpg";
static const char *g_origin_file = "image.jpg";
static char *g_insert_path = NULL;
static char *g_origin_path = NULL;
static char *dir_path = NULL;

static media_content_error_e cb_result = MEDIA_CONTENT_ERROR_NONE;
static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool __storage_device_supported_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
	if (type == STORAGE_TYPE_INTERNAL) {
		g_origin_path = (char *)malloc(strlen(path) + strlen(g_origin_file) + 6);
		memset(g_origin_path, 0x00, strlen(path) + strlen(g_origin_file) + 6);
		snprintf(g_origin_path, strlen(path) + strlen(g_origin_file) + 6, "%s/res/%s", path, g_origin_file);

		g_insert_path = (char *)malloc(strlen(path) + strlen(g_insert_file) + 6);
		memset(g_insert_path, 0x00, strlen(path) + strlen(g_insert_file) + 6);
		snprintf(g_insert_path, strlen(path) + strlen(g_insert_file) + 6, "%s/res/%s", path, g_insert_file);

		dir_path = strdup(path);

		return false;
	}
	return true;
}

static void _scan_folder_cb(media_content_error_e error, void *user_data)
{
	cb_result = error;
}

static gboolean _startup_scan_start(gpointer data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_scan_folder(dir_path, TRUE, _scan_folder_cb, NULL);
	if (ret < 1) {
		g_main_loop_quit(g_loop);
		cb_result = ret;
	}
	return false;
}

/**
 * @function		utc_media_content_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_content_startup(void)
{
	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;
	GSource *source = NULL;
	GMainContext *context = NULL;

	if (storage_foreach_device_supported(__storage_device_supported_cb, NULL) != STORAGE_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	g_loop = g_main_loop_new(NULL, FALSE);
	context = g_main_loop_get_context(g_loop);
	source = g_idle_source_new();
	g_source_set_callback(source, _startup_scan_start, NULL, NULL);
	g_source_attach(source, context);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	g_loop = NULL;
	if (cb_result != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
		startup_ret = cb_result;
		return;
	}

	if (!g_file_test(g_insert_path, G_FILE_TEST_EXISTS)) {
		char test_copy[256] = { 0, };
		snprintf(test_copy, sizeof(test_copy), "/bin/cp %s %s", g_origin_path, g_insert_path);

		if (system(test_copy) < 0) {
			fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
			fprintf(stderr, "\"%s\" failed (code: %d)\n", test_copy, ret);
			startup_ret = -1;
			return;
		}
	}
}

/**
 * @function		utc_media_content_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_content_cleanup(void)
{
	if (g_insert_path != NULL) {
		free(g_insert_path);
		g_insert_path = NULL;
	}
	if (g_origin_path != NULL) {
		free(g_origin_path);
		g_origin_path = NULL;
	}
	if (dir_path != NULL) {
		free(dir_path);
		dir_path = NULL;
	}
	g_loop = NULL;
	media_content_disconnect();
}

static void _noti_cb(media_content_error_e error, int pid, media_content_db_update_item_type_e update_item, media_content_db_update_type_e update_type, media_content_type_e media_type, char *uuid, char *path, char *mime_type, void *user_data)
{
}

/**
 * @testcase		utc_media_content_connect_p
 * @since_tizen		2.3
 * @description		Positive test case of media_content_connect()
 */
int utc_media_content_connect_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	ret = media_content_disconnect();
	ret = media_content_connect();
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_connect_n
 * @since_tizen		2.3
 * @description		Negative test case of media_content_connect()
 */
int utc_media_content_connect_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_disconnect();
	ret = media_content_connect();
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_disconnect_p
 * @since_tizen		2.3
 * @description		Positive test case of media_content_disconnect()
 */
int utc_media_content_disconnect_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_disconnect();
	ret = media_content_connect();
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_disconnect_n
 * @since_tizen		2.3
 * @description		Negative test case of media_content_disconnect()
 */
int utc_media_content_disconnect_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_disconnect();
	ret = media_content_connect();
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_scan_file_n
 * @since_tizen		2.3
 * @description		Negative test case of media_content_scan_file()
 */
int utc_media_content_scan_file_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_scan_file(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_content_scan_file_p
 * @since_tizen		2.3
 * @description		Positive test case of media_content_scan_file()
 */
int utc_media_content_scan_file_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_scan_file(g_insert_path);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_scan_folder_n
 * @since_tizen		2.3
 * @description		Negative test case of media_content_scan_folder()
 */
int utc_media_content_scan_folder_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_scan_folder(NULL, FALSE, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

static gboolean _scan_folder_start(gpointer data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_scan_folder(dir_path, FALSE, _scan_folder_cb, NULL);

	if (ret < 1) {
		g_main_loop_quit(g_loop);
		cb_result = ret;
	}
	return false;
}

/**
 * @testcase		utc_media_content_scan_folder_p
 * @since_tizen		2.3
 * @description		Positive test case of media_content_scan_folder()
 */
int utc_media_content_scan_folder_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	GSource *source = NULL;
	GMainContext *context = NULL;

	g_loop = g_main_loop_new(NULL, FALSE);
	context = g_main_loop_get_context(g_loop);
	source = g_idle_source_new();
	g_source_set_callback(source, _scan_folder_start, NULL, NULL);
	g_source_attach(source, context);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	g_loop = NULL;

	assert_eq(cb_result, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_cancel_scan_folder_n
 * @since_tizen		2.3
 * @description		Negative test case of media_content_cancel_scan_folder()
 */
int utc_media_content_cancel_scan_folder_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_cancel_scan_folder(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_content_cancel_scan_folder_p
 * @since_tizen		2.3
 * @description		Positive test case of media_content_cancel_scan_folder()
 */
int utc_media_content_cancel_scan_folder_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_cancel_scan_folder(dir_path);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_add_db_updated_cb_n
 * @since_tizen		3.0
 * @description		Negative test case of media_content_add_db_updated_cb()
 */
int utc_media_content_add_db_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_noti_h noti = NULL;

	ret = media_content_add_db_updated_cb(NULL, NULL, &noti);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
	noti = NULL;

	return 0;
}

/**
 * @testcase		utc_media_content_add_db_updated_cb_p
 * @since_tizen		2.3
 * @description		Positive test case of media_content_add_db_updated_cb()
 */
int utc_media_content_add_db_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_noti_h noti = NULL;

	ret = media_content_add_db_updated_cb(_noti_cb, NULL, &noti);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_content_remove_db_updated_cb(noti);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	noti = NULL;

	return 0;
}

/**
 * @testcase		utc_media_content_remove_db_updated_cb_n
 * @since_tizen		3.0
 * @description		Negative test case of media_content_remove_db_updated_cb()
 */
int utc_media_content_remove_db_updated_cb_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_remove_db_updated_cb(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_content_remove_db_updated_cb_p
 * @since_tizen		3.0
 * @description		Positive test case of media_content_remove_db_updated_cb()
 */
int utc_media_content_remove_db_updated_cb_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_noti_h noti = NULL;

	ret = media_content_add_db_updated_cb(_noti_cb, NULL, &noti);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_content_remove_db_updated_cb(noti);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	noti = NULL;

	return 0;
}
