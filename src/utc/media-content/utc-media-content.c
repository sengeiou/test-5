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
static char *g_file_path = NULL;
static char *g_dir_path = NULL;
static int cb_result = MEDIA_CONTENT_ERROR_NONE;

static void _scan_folder_cb(media_content_error_e error, void *user_data)
{
	cb_result = error;

	g_main_loop_quit(g_loop);
}

/**
 * @function		utc_media_content_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_content_startup(void)
{
	if (storage_get_root_directory(0, &g_dir_path) == STORAGE_ERROR_NONE)
		g_file_path = g_strdup_printf("%s/res/image.jpg", g_dir_path);

	if (media_content_connect() != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
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
	FREE_MEMORY(g_file_path);
	FREE_MEMORY(g_dir_path);

	media_content_disconnect();
	g_loop = NULL;
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
	assert_eq(media_content_disconnect(), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_content_connect(), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_connect_n
 * @since_tizen		2.3
 * @description		Negative test case of media_content_connect()
 */
int utc_media_content_connect_n(void)
{
	assert_eq(media_content_disconnect(), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_content_connect(), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_disconnect_p
 * @since_tizen		2.3
 * @description		Positive test case of media_content_disconnect()
 */
int utc_media_content_disconnect_p(void)
{
	assert_eq(media_content_disconnect(), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_content_connect(), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_disconnect_n
 * @since_tizen		2.3
 * @description		Negative test case of media_content_disconnect()
 */
int utc_media_content_disconnect_n(void)
{
	assert_eq(media_content_disconnect(), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_content_connect(), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_scan_file_n
 * @since_tizen		2.3
 * @description		Negative test case of media_content_scan_file()
 */
int utc_media_content_scan_file_n(void)
{
	assert_eq(media_content_scan_file(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_content_scan_file_p
 * @since_tizen		2.3
 * @description		Positive test case of media_content_scan_file()
 */
int utc_media_content_scan_file_p(void)
{
	assert_eq(media_content_scan_file(g_file_path), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_scan_folder_n
 * @since_tizen		2.3
 * @description		Negative test case of media_content_scan_folder()
 */
int utc_media_content_scan_folder_n(void)
{
	assert_eq(media_content_scan_folder(NULL, FALSE, _scan_folder_cb, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_content_scan_folder(g_dir_path, FALSE, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

static gboolean _scan_folder_start_cb(gpointer data)
{
	cb_result = media_content_scan_folder(g_dir_path, FALSE, _scan_folder_cb, NULL);
	if (cb_result != MEDIA_CONTENT_ERROR_NONE)
		g_main_loop_quit(g_loop);

	return G_SOURCE_REMOVE;
}

/**
 * @testcase		utc_media_content_scan_folder_p
 * @since_tizen		2.3
 * @description		Positive test case of media_content_scan_folder()
 */
int utc_media_content_scan_folder_p(void)
{
	g_loop = g_main_loop_new(NULL, FALSE);
	g_idle_add(_scan_folder_start_cb, NULL);
	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	assert_eq(cb_result, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_cancel_scan_folder_n
 * @since_tizen		2.3
 * @description		Negative test case of media_content_cancel_scan_folder()
 */
int utc_media_content_cancel_scan_folder_n(void)
{
	assert_eq(media_content_cancel_scan_folder(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_content_cancel_scan_folder_p
 * @since_tizen		2.3
 * @description		Positive test case of media_content_cancel_scan_folder()
 */
int utc_media_content_cancel_scan_folder_p(void)
{
	assert_eq(media_content_scan_folder(g_dir_path, FALSE, _scan_folder_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_content_cancel_scan_folder(g_dir_path), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_add_db_updated_cb_n
 * @since_tizen		3.0
 * @description		Negative test case of media_content_add_db_updated_cb()
 */
int utc_media_content_add_db_updated_cb_n(void)
{
	media_content_noti_h noti = NULL;

	assert_eq(media_content_add_db_updated_cb(NULL, NULL, &noti), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_content_add_db_updated_cb(_noti_cb, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
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
	media_content_noti_h noti = NULL;

	assert_eq(media_content_add_db_updated_cb(_noti_cb, NULL, &noti), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_content_remove_db_updated_cb(noti), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_content_remove_db_updated_cb_n
 * @since_tizen		3.0
 * @description		Negative test case of media_content_remove_db_updated_cb()
 */
int utc_media_content_remove_db_updated_cb_n(void)
{
	assert_eq(media_content_remove_db_updated_cb(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_content_remove_db_updated_cb_p
 * @since_tizen		3.0
 * @description		Positive test case of media_content_remove_db_updated_cb()
 */
int utc_media_content_remove_db_updated_cb_p(void)
{
	media_content_noti_h noti = NULL;

	assert_eq(media_content_add_db_updated_cb(_noti_cb, NULL, &noti), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_content_remove_db_updated_cb(noti), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
