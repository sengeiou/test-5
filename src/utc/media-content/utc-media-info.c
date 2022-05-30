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
#include <glib.h>
#include <storage.h>
#include <limits.h>

#define MEDIA_BATCH_SIZE 3
//& set: MediaInfo

static GMainLoop *g_loop = NULL;

static media_info_h g_image = NULL;
static media_info_h g_image_sub = NULL;
static media_info_h g_video = NULL;
static media_info_h g_audio = NULL;
static media_info_h g_book = NULL;

static char *g_media_id = NULL;

static char *g_image_path;
static char *g_move_path;
static char *g_image_path_list[MEDIA_BATCH_SIZE];

static char *g_val_str = NULL;
static int g_val_int = 0;
static time_t g_val_time;
static bool g_val_bool = false;
static double g_val_double = 0;

static int cb_result = MEDIA_CONTENT_ERROR_NONE;
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool g_isFaceRecognitionSupported = FALSE;

static bool sub_item_cb(media_info_h media, void *user_data)
{
	return true;
}

/**
 * @function		utc_media_info_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_info_startup(void)
{
	int i = 0;
	char *root_path = NULL;
	char sub_image_path[PATH_MAX + 1] = { 0, };
	char audio_path[PATH_MAX + 1] = { 0, };
	char video_path[PATH_MAX + 1] = { 0, };
	char book_path[PATH_MAX + 1] = { 0, };

	system_info_get_platform_bool("http://tizen.org/feature/vision.face_recognition", &g_isFaceRecognitionSupported);

	if (storage_get_root_directory(0, &root_path) == STORAGE_ERROR_NONE) {
		g_image_path = g_strdup_printf("%s/res/image.jpg", root_path);
		g_move_path = g_strdup_printf("%s/res/move.jpg", root_path);

		for (i = 0; i < MEDIA_BATCH_SIZE; i++)
			g_image_path_list[i] = g_strdup_printf("%s/res/batch_%02d.jpg", root_path, i);

		snprintf(audio_path, PATH_MAX, "%s/res/sound.mp3", root_path);
		snprintf(video_path, PATH_MAX, "%s/res/movie.mp4", root_path);
		snprintf(book_path, PATH_MAX, "%s/res/utc_test.epub", root_path);
		snprintf(sub_image_path, PATH_MAX, "%s/res/test/test.jpg", root_path);
		FREE_MEMORY(root_path);
	}

	startup_ret = media_content_connect();
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_info_get_media_from_db_by_path(audio_path, &g_audio);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(audio_path, &g_audio);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}
	}

	startup_ret = media_info_get_media_from_db_by_path(g_image_path, &g_image);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(g_image_path, &g_image);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}
	}

	startup_ret = media_info_get_media_id(g_image, &g_media_id);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_info_get_media_id failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_info_get_media_from_db_by_path(video_path, &g_video);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(video_path, &g_video);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}
	}

	startup_ret = media_info_get_media_from_db_by_path(book_path, &g_book);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(book_path, &g_book);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}
	}

	startup_ret = media_info_get_media_from_db_by_path(sub_image_path, &g_image_sub);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(sub_image_path, &g_image_sub);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}
	}
}

/**
 * @function		utc_media_info_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_info_cleanup(void)
{
	int i;

	media_content_disconnect();

	FREE_MEMORY(g_media_id);

	FREE_MEMORY(g_image_path);
	FREE_MEMORY(g_move_path);

	for (i = 0; i < MEDIA_BATCH_SIZE; i++) {
		FREE_MEMORY(g_image_path_list[i]);
	}

	if (g_image) {
		media_info_destroy(g_image);
		g_image = NULL;
	}
	if (g_image_sub) {
		media_info_destroy(g_image_sub);
		g_image_sub = NULL;
	}
	if (g_video) {
		media_info_destroy(g_video);
		g_video = NULL;
	}
	if (g_audio) {
		media_info_destroy(g_audio);
		g_audio = NULL;
	}
	if (g_book) {
		media_info_destroy(g_book);
		g_book = NULL;
	}
}

/**
 * @testcase		utc_media_info_insert_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_insert_to_db()
 */
int utc_media_info_insert_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_info_h media = NULL;

	assert_eq(media_info_insert_to_db(g_image_path, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_insert_to_db(NULL, &media), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_insert_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_insert_to_db()
 */
int utc_media_info_insert_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_info_h media = NULL;

	assert_eq(media_info_insert_to_db(g_image_path, &media), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_destroy(media), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

static void _insert_batch_cb(media_content_error_e error, void *user_data)
{
	cb_result = error;
	g_main_loop_quit(g_loop);
}

static gboolean _insert_batch_start(gpointer data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *copy_cmd = NULL;
	int i = 0;

	for (i = 0; i < MEDIA_BATCH_SIZE; i++) {
		copy_cmd = g_strdup_printf("/bin/cp %s %s", g_image_path, g_image_path_list[i]);
		system(copy_cmd);
		g_free(copy_cmd);
	}

	ret = media_info_insert_batch_to_db(g_image_path_list, MEDIA_BATCH_SIZE, _insert_batch_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		g_main_loop_quit(g_loop);
		cb_result = ret;
	}

	return false;
}

/**
 * @testcase		utc_media_info_insert_batch_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_insert_batch_to_db()
 */
int utc_media_info_insert_batch_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_insert_batch_to_db(NULL, 0, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_insert_batch_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_insert_batch_to_db()
 */
int utc_media_info_insert_batch_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int i = 0;

	g_loop = g_main_loop_new(NULL, FALSE);
	g_idle_add(_insert_batch_start, NULL);
	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	for (i = 0; i < MEDIA_BATCH_SIZE; i++)
		unlink(g_image_path_list[i]);

	assert_eq(cb_result, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_set_favorite_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_set_favorite()
 */
int utc_media_info_set_favorite_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_set_favorite(NULL, true), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_set_favorite_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_set_favorite()
 */
int utc_media_info_set_favorite_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_info_h media = NULL;

	assert_eq(media_info_set_favorite(g_image, true), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_update_to_db(g_image), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_media_from_db(g_media_id, &media), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_favorite(media, &g_val_bool), MEDIA_CONTENT_ERROR_NONE);
	media_info_destroy(media);

	assert(g_val_bool);

	return 0;
}

/**
 * @testcase		utc_media_info_update_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_update_to_db()
 */
int utc_media_info_update_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_update_to_db(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_update_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_update_to_db()
 */
int utc_media_info_update_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_update_to_db(g_image), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

static void thumb_cb(media_content_error_e error, const char *path, void *user_data)
{
	cb_result = error;
	g_main_loop_quit(g_loop);
}

static gboolean _create_thumbnail_start(gpointer data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_create_thumbnail(g_image, thumb_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		g_main_loop_quit(g_loop);
		cb_result = ret;
	}

	return G_SOURCE_REMOVE;
}

static gboolean _create_cancel_thumbnail_start(gpointer data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_create_thumbnail(g_image, thumb_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		g_main_loop_quit(g_loop);
		cb_result = ret;
	}

	ret = media_info_create_thumbnail(g_image_sub, thumb_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		g_main_loop_quit(g_loop);
		cb_result = ret;
	}

	ret = media_info_cancel_thumbnail(g_image_sub);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		g_main_loop_quit(g_loop);
		cb_result = ret;
	}

	return G_SOURCE_REMOVE;
}

/**
 * @testcase		utc_media_info_create_thumbnail_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_create_thumbnail()
 */
int utc_media_info_create_thumbnail_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_create_thumbnail(NULL, thumb_cb, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_create_thumbnail(g_image, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_create_thumbnail_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_create_thumbnail()
 */
int utc_media_info_create_thumbnail_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	g_loop = g_main_loop_new(NULL, FALSE);
	g_idle_add(_create_thumbnail_start, NULL);
	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	assert_eq(cb_result, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

static void face_detection_cb(media_content_error_e error, const int face_count, void *user_data)
{
	cb_result = error;
	if (g_loop != NULL)
		g_main_loop_quit(g_loop);
}

static gboolean _face_detection_start(gpointer data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_start_face_detection(g_image, face_detection_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		if (g_loop != NULL)
			g_main_loop_quit(g_loop);
		cb_result = ret;
	}
	return G_SOURCE_REMOVE;
}

/**
 * @testcase		utc_media_info_start_face_detection_n
 * @since_tizen		3.0
 * @description		Negative test case of media_info_start_face_detection()
 */
int utc_media_info_start_face_detection_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_start_face_detection(NULL, face_detection_cb, NULL);
	if (!g_isFaceRecognitionSupported) {
		assert_eq(ret, MEDIA_CONTENT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_media_info_start_face_detection_p
 * @since_tizen		3.0
 * @description		Positive test case of media_info_start_face_detection()
 */
int utc_media_info_start_face_detection_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	g_loop = g_main_loop_new(NULL, FALSE);
	g_idle_add(_face_detection_start, NULL);
	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	if (!g_isFaceRecognitionSupported) {
		assert_eq(cb_result, MEDIA_CONTENT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(cb_result, MEDIA_CONTENT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_media_info_move_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_move_to_db()
 */
int utc_media_info_move_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_move_to_db(NULL, g_move_path), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_move_to_db(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_move_to_db(g_image, g_move_path), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_move_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_move_to_db()
 */
int utc_media_info_move_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *copy = g_strdup_printf("/bin/cp %s %s", g_image_path, g_move_path);

	system(copy);
	g_free(copy);

	assert_eq(media_info_move_to_db(g_image, g_move_path), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_move_to_db(g_image, g_image_path), MEDIA_CONTENT_ERROR_NONE);

	unlink(g_move_path);

	return 0;
}

/**
 * @testcase		utc_media_info_delete_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_delete_from_db()
 */
int utc_media_info_delete_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_delete_from_db(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_delete_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_delete_from_db()
 */
int utc_media_info_delete_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_info_h media = NULL;

	assert_eq(media_info_delete_from_db(g_media_id), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_media_from_db(g_media_id, &media), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_foreach_media_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_foreach_media_from_db()
 */
int utc_media_info_foreach_media_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_foreach_media_from_db(NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_foreach_media_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_foreach_media_from_db()
 */
int utc_media_info_foreach_media_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	char *condition = "(MEDIA_TYPE=0 OR MEDIA_TYPE=1 OR MEDIA_TYPE=3) AND MEDIA_STORAGE_TYPE>=0";

	media_filter_create(&filter);
	media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_NOCASE);
	media_filter_set_order(filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_LOCALIZED);

	ret = media_info_foreach_media_from_db(filter, sub_item_cb, NULL);

	if (filter)
		media_filter_destroy(filter);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_destroy()
 */
int utc_media_info_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_destroy()
 */
int utc_media_info_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_destroy(g_image), MEDIA_CONTENT_ERROR_NONE);
	g_image = NULL;

	return 0;
}

/**
 * @testcase		utc_media_info_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_clone()
 */
int utc_media_info_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_info_h cloned;

	assert_eq(media_info_clone(&cloned, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_clone(NULL, g_image), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_clone()
 */
int utc_media_info_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_info_h cloned;

	assert_eq(media_info_clone(&cloned, g_image), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_destroy(cloned), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_media_id_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_media_id()
 */
int utc_media_info_get_media_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_media_id(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_media_id(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_media_id_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_media_id()
 */
int utc_media_info_get_media_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_media_id(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_file_path_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_file_path()
 */
int utc_media_info_get_file_path_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_file_path(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_file_path(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_file_path_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_file_path()
 */
int utc_media_info_get_file_path_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_file_path(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_display_name_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_display_name()
 */
int utc_media_info_get_display_name_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_display_name(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_display_name(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_display_name_p
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_display_name()
 */
int utc_media_info_get_display_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_display_name(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_media_type_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_media_type()
 */
int utc_media_info_get_media_type_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_content_type_e type = 0;

	assert_eq(media_info_get_media_type(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_media_type(NULL, &type), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_media_type_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_media_type()
 */
int utc_media_info_get_media_type_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_content_type_e type = 0;

	assert_eq(media_info_get_media_type(g_image, &type), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_mime_type_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_mime_type()
 */
int utc_media_info_get_mime_type_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_mime_type(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_mime_type(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_mime_type_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_mime_type()
 */
int utc_media_info_get_mime_type_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_mime_type(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_thumbnail_path_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_thumbnail_path()
 */
int utc_media_info_get_thumbnail_path_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_thumbnail_path(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_thumbnail_path(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_thumbnail_path_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_thumbnail_path()
 */
int utc_media_info_get_thumbnail_path_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_thumbnail_path(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_modified_time_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_modified_time()
 */
int utc_media_info_get_modified_time_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_modified_time(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_modified_time(NULL, &g_val_time), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_modified_time_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_modified_time()
 */
int utc_media_info_get_modified_time_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_modified_time(g_image, &g_val_time), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_size_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_size()
 */
int utc_media_info_get_size_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	unsigned long long size;

	assert_eq(media_info_get_size(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_size(NULL, &size), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_size_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_size()
 */
int utc_media_info_get_size_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	unsigned long long size;

	assert_eq(media_info_get_size(g_image, &size), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_storage_type_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_storage_type()
 */
int utc_media_info_get_storage_type_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_content_storage_e storage_type;

	assert_eq(media_info_get_storage_type(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_storage_type(NULL, &storage_type), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_storage_type_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_storage_type()
 */
int utc_media_info_get_storage_type_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_content_storage_e storage_type;

	assert_eq(media_info_get_storage_type(g_image, &storage_type), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_storage_id_n
 * @since_tizen		2.4
 * @description		Negative test case of media_info_get_storage_id()
 */
int utc_media_info_get_storage_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_storage_id(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_storage_id(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_storage_id_p
 * @since_tizen		2.4
 * @description		Positive test case of media_info_get_storage_id()
 */
int utc_media_info_get_storage_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_storage_id(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_is_drm_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_is_drm()
 */
int utc_media_info_is_drm_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_is_drm(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_is_drm(NULL, &g_val_bool), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_is_drm_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_is_drm()
 */
int utc_media_info_is_drm_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_is_drm(g_image, &g_val_bool), MEDIA_CONTENT_ERROR_NONE);
	assert_eq(g_val_bool, false);

	return 0;
}

/**
 * @testcase		utc_media_info_get_altitude_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_altitude()
 */
int utc_media_info_get_altitude_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_altitude(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_altitude(NULL, &g_val_double), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_altitude_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_altitude()
 */
int utc_media_info_get_altitude_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_altitude(g_image, &g_val_double), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_latitude_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_latitude()
 */
int utc_media_info_get_latitude_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_latitude(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_latitude(NULL, &g_val_double), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_latitude_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_latitude()
 */
int utc_media_info_get_latitude_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_latitude(g_image, &g_val_double), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_longitude_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_longitude()
 */
int utc_media_info_get_longitude_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_longitude(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_longitude(NULL, &g_val_double), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_longitude_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_longitude()
 */
int utc_media_info_get_longitude_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_longitude(g_image, &g_val_double), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_description_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_description()
 */
int utc_media_info_get_description_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_description(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_description(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_description_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_description()
 */
int utc_media_info_get_description_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_description(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_rating_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_rating()
 */
int utc_media_info_get_rating_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_rating(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_rating(NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_rating_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_rating()
 */
int utc_media_info_get_rating_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_rating(g_image, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_added_time_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_added_time()
 */
int utc_media_info_get_added_time_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_added_time(NULL, &g_val_time), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_added_time(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_added_time_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_added_time()
 */
int utc_media_info_get_added_time_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_added_time(g_image, &g_val_time), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_favorite_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_favorite()
 */
int utc_media_info_get_favorite_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_favorite(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_favorite(NULL, &g_val_bool), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_favorite_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_favorite()
 */
int utc_media_info_get_favorite_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_favorite(g_image, &g_val_bool), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_media_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_media_from_db()
 */
int utc_media_info_get_media_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_info_h media = NULL;

	assert_eq(media_info_get_media_from_db(g_media_id, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_media_from_db(NULL, &media), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_media_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_media_from_db()
 */
int utc_media_info_get_media_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_info_h handle = NULL;

	assert_eq(media_info_get_media_from_db(g_media_id, &handle), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_destroy(handle), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_media_from_db_by_path_n
 * @since_tizen		6.5
 * @description		Negative test case of media_info_get_media_from_db_by_path()
 */
int utc_media_info_get_media_from_db_by_path_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_info_h handle = NULL;

	assert_eq(media_info_get_media_from_db_by_path(g_image_path, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_media_from_db_by_path(NULL, &handle), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_media_from_db_by_path_p
 * @since_tizen		6.5
 * @description		Positive test case of media_info_get_media_from_db_by_path()
 */
int utc_media_info_get_media_from_db_by_path_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	media_info_h handle = NULL;

	assert_eq(media_info_get_media_from_db_by_path(g_image_path, &handle), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_destroy(handle), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_image_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_image()
 */
int utc_media_info_get_image_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	image_meta_h image = NULL;

	assert_eq(media_info_get_image(NULL, &image), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_image(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_image_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_image()
 */
int utc_media_info_get_image_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	image_meta_h image = NULL;

	assert_eq(media_info_get_image(g_image, &image), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(image_meta_destroy(image), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_video_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_video()
 */
int utc_media_info_get_video_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	video_meta_h video = NULL;

	assert_eq(media_info_get_video(NULL, &video), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_video(g_video, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_video_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_video()
 */
int utc_media_info_get_video_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	video_meta_h video = NULL;

	assert_eq(media_info_get_video(g_video, &video), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(video_meta_destroy(video), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_audio_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_audio()
 */
int utc_media_info_get_audio_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	audio_meta_h audio = NULL;

	assert_eq(media_info_get_audio(NULL, &audio), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_audio(g_audio, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_audio_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_audio()
 */
int utc_media_info_get_audio_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	audio_meta_h audio = NULL;

	assert_eq(media_info_get_audio(g_audio, &audio), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(audio_meta_destroy(audio), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_book_n
 * @since_tizen		6.5
 * @description		Negative test case of media_info_get_book()
 */
int utc_media_info_get_book_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	book_meta_h book = NULL;

	assert_eq(media_info_get_book(g_book, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_book(NULL, &book), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_book_p
 * @since_tizen		6.5
 * @description		Positive test case of media_info_get_book()
 */
int utc_media_info_get_book_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	book_meta_h book = NULL;

	assert_eq(media_info_get_book(g_book, &book), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(book_meta_destroy(book), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

static bool sub_tag_cb(media_tag_h tag, void *user_data)
{
	return false;
}

static bool sub_bookmark_cb(media_bookmark_h bookmark, void *user_data)
{
	return false;
}

/**
 * @testcase		utc_media_info_foreach_tag_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_foreach_tag_from_db()
 */
int utc_media_info_foreach_tag_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_foreach_tag_from_db(g_media_id, NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_foreach_tag_from_db(NULL, NULL, sub_tag_cb, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_foreach_tag_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_foreach_tag_from_db()
 */
int utc_media_info_foreach_tag_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_foreach_tag_from_db(g_media_id, NULL, sub_tag_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_foreach_bookmark_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_foreach_bookmark_from_db()
 */
int utc_media_info_foreach_bookmark_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_foreach_bookmark_from_db(g_media_id, NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_foreach_bookmark_from_db(NULL, NULL, sub_bookmark_cb, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_foreach_bookmark_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_foreach_bookmark_from_db()
 */
int utc_media_info_foreach_bookmark_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_foreach_bookmark_from_db(g_media_id, NULL, sub_bookmark_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_bookmark_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_bookmark_count_from_db()
 */
int utc_media_info_get_bookmark_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_bookmark_count_from_db(g_media_id, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_bookmark_count_from_db(NULL, NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_bookmark_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_bookmark_count_from_db()
 */
int utc_media_info_get_bookmark_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_bookmark_count_from_db(g_media_id, NULL, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_media_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_media_count_from_db()
 */
int utc_media_info_get_media_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_media_count_from_db(NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_media_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_media_count_from_db()
 */
int utc_media_info_get_media_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_media_count_from_db(NULL, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_tag_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_tag_count_from_db()
 */
int utc_media_info_get_tag_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_tag_count_from_db(NULL, NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_tag_count_from_db(g_media_id, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_tag_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_tag_count_from_db()
 */
int utc_media_info_get_tag_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_tag_count_from_db(g_media_id, NULL, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_timeline_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_timeline()
 */
int utc_media_info_get_timeline_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_timeline(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_timeline(NULL, &g_val_time), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_timeline_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_timeline()
 */
int utc_media_info_get_timeline_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_timeline(g_image, &g_val_time), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_get_title_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_get_title()
 */
int utc_media_info_get_title_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_title(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_title(NULL, &g_val_str), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_title_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_get_title()
 */
int utc_media_info_get_title_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_title(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_is_360_content_n
 * @since_tizen		3.0
 * @description		Negative test case of media_info_is_360_content()
 */
int utc_media_info_is_360_content_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_is_360_content(g_image, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_is_360_content(NULL, &g_val_bool), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_is_360_content_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_is_360_content()
 */
int utc_media_info_is_360_content_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_is_360_content(g_image, &g_val_bool), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_cancel_thumbnail_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_cancel_thumbnail()
 */
int utc_media_info_cancel_thumbnail_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_cancel_thumbnail(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_cancel_thumbnail_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_cancel_thumbnail()
 */
int utc_media_info_cancel_thumbnail_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	g_loop = g_main_loop_new(NULL, FALSE);
	g_idle_add(_create_cancel_thumbnail_start, NULL);
	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);
	g_loop = NULL;

	assert_eq(cb_result, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_cancel_face_detection_n
 * @since_tizen		3.0
 * @description		Negative test case of media_info_cancel_face_detection()
 */
int utc_media_info_cancel_face_detection_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_cancel_face_detection(NULL);
	if (!g_isFaceRecognitionSupported) {
		assert_eq(ret, MEDIA_CONTENT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_media_info_cancel_face_detection_p
 * @since_tizen		3.0
 * @description		Positive test case of media_info_cancel_face_detection()
 */
int utc_media_info_cancel_face_detection_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_start_face_detection(g_image, face_detection_cb, NULL);
	if (!g_isFaceRecognitionSupported) {
		assert_eq(ret, MEDIA_CONTENT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	}

	ret = media_info_cancel_face_detection(g_image);
	if (!g_isFaceRecognitionSupported) {
		assert_eq(ret, MEDIA_CONTENT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_media_info_get_face_count_from_db_n
 * @since_tizen		3.0
 * @description		Negative test case of media_info_get_face_count_from_db()
 */
int utc_media_info_get_face_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_face_count_from_db(NULL, NULL, &g_val_int), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_info_get_face_count_from_db(g_media_id, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_get_face_count_from_db_p
 * @since_tizen		3.0
 * @description		Positive test case of media_info_get_face_count_from_db()
 */
int utc_media_info_get_face_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_face_count_from_db(g_media_id, NULL, &g_val_int), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

static bool face_cb(media_face_h face, void *user_data)
{
	return false;
}

/**
 * @testcase		utc_media_info_foreach_face_from_db_n
 * @since_tizen		3.0
 * @description		Negative test case of media_info_foreach_face_from_db()
 */
int utc_media_info_foreach_face_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_foreach_face_from_db(NULL, NULL, face_cb, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_foreach_face_from_db_p
 * @since_tizen		3.0
 * @description		Positive test case of media_info_foreach_face_from_db()
 */
int utc_media_info_foreach_face_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_foreach_face_from_db(g_media_id, NULL, face_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_info_generate_thumbnail_n
 * @since_tizen		5.0
 * @description		Negative test case of media_info_generate_thumbnail()
 */
int utc_media_info_generate_thumbnail_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_generate_thumbnail(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_generate_thumbnail_p
 * @since_tizen		5.0
 * @description		Positive test case of media_info_generate_thumbnail()
 */
int utc_media_info_generate_thumbnail_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_generate_thumbnail(g_image), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_info_get_thumbnail_path(g_image, &g_val_str), MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
