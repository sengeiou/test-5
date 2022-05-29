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

#define TEST_SET_SVALUE "new text"
#define TEST_SET_IVALUE 1000.0
//& set: MediaInfo

static GMainLoop *g_loop = NULL;

static media_info_h g_item = NULL;
static media_info_h g_item_sub = NULL;
static media_info_h g_vitem = NULL;
static media_info_h g_aitem = NULL;
static media_info_h g_bitem = NULL;
static media_info_h g_inserted_media_handle = NULL;
static media_info_h g_inserted_audio_handle = NULL;

static filter_h g_filter = NULL;

static char *g_item_media_id = NULL;
static char *g_inserted_media_id = NULL;
static char *g_inserted_audio_id = NULL;

static const char *g_insert_file = "test.jpg";
static const char *g_origin_file = "image.jpg";
static const char *g_move_dst_file = "test1.jpg";
static const char *g_copy_dst_file = "image_copy.jpg";
static const char *g_audio_file = "sound.mp3";
static const char *g_insert_audio_file = "test_sound.mp3";

static char *g_insert_path = NULL;
static char *g_origin_path = NULL;
static char *g_move_dst_path = NULL;
static char *g_copy_dst_path = NULL;
static char *g_audio_path = NULL;
static char *g_insert_audio_path = NULL;
static char *g_insert_path_list[3];
static char *g_burst_path_list[3];

static media_content_error_e foreach_cb_result = MEDIA_CONTENT_ERROR_NONE;
static media_content_error_e insert_batch_cb_result = MEDIA_CONTENT_ERROR_NONE;
static media_content_error_e thumb_cb_result = MEDIA_CONTENT_ERROR_NONE;
static media_content_error_e face_detection_cb_result = MEDIA_CONTENT_ERROR_NONE;
static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;
static media_content_error_e g_cb_ret = MEDIA_CONTENT_ERROR_NONE;

static bool g_isFaceRecognitionSupported = FALSE;

static bool __storage_device_supported_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
	int i;
	char temp[500] = { 0, };

	if (type == STORAGE_TYPE_INTERNAL) {
		g_insert_path = (char *)malloc(strlen(path) + strlen(g_insert_file) + 6);
		memset(g_insert_path, 0x00, strlen(path) + strlen(g_insert_file) + 6);
		snprintf(g_insert_path, strlen(path) + strlen(g_insert_file) + 6, "%s/res/%s", path, g_insert_file);

		g_origin_path = (char *)malloc(strlen(path) + strlen(g_origin_file) + 6);
		memset(g_origin_path, 0x00, strlen(path) + strlen(g_origin_file) + 6);
		snprintf(g_origin_path, strlen(path) + strlen(g_origin_file) + 6, "%s/res/%s", path, g_origin_file);

		g_move_dst_path = (char *)malloc(strlen(path) + strlen(g_move_dst_file) + 6);
		memset(g_move_dst_path, 0x00, strlen(path) + strlen(g_move_dst_file) + 6);
		snprintf(g_move_dst_path, strlen(path) + strlen(g_move_dst_file) + 6, "%s/res/%s", path, g_move_dst_file);

		g_copy_dst_path = (char *)malloc(strlen(path) + strlen(g_copy_dst_file) + 6);
		memset(g_copy_dst_path, 0x00, strlen(path) + strlen(g_copy_dst_file) + 6);
		snprintf(g_copy_dst_path, strlen(path) + strlen(g_copy_dst_file) + 6, "%s/res/%s", path, g_copy_dst_file);

		g_audio_path = (char *)malloc(strlen(path) + strlen(g_audio_file) + 6);
		memset(g_audio_path, 0x00, strlen(path) + strlen(g_audio_file) + 6);
		snprintf(g_audio_path, strlen(path) + strlen(g_audio_file) + 6, "%s/res/%s", path, g_audio_file);

		g_insert_audio_path = (char *)malloc(strlen(path) + strlen(g_insert_audio_file) + 6);
		memset(g_insert_audio_path, 0x00, strlen(path) + strlen(g_insert_audio_file) + 6);
		snprintf(g_insert_audio_path, strlen(path) + strlen(g_insert_audio_file) + 6, "%s/res/%s", path, g_insert_audio_file);

		for (i = 0; i < 3; i++) {
			memset(temp, 0x00, sizeof(temp));
			snprintf(temp, sizeof(temp), "%s/res/batch%02d.jpg", path, i);
			g_insert_path_list[i] = strndup(temp, sizeof(temp));

			memset(temp, 0x00, sizeof(temp));
			snprintf(temp, sizeof(temp), "%s/res/burst%02d.jpg", path, i);
			g_burst_path_list[i] = strndup(temp, sizeof(temp));
		}

		return false;
	}
	return true;
}

static bool sub_item_cb(media_info_h media, void *user_data)
{
	media_content_type_e type = 0;
	char *name = NULL;

	media_info_get_media_type(media, &type);
	media_info_get_display_name(media, &name);

	if (g_item == NULL && g_strcmp0(name, g_insert_file) == 0)
		media_info_clone(&g_item, media);

	if (g_item_sub == NULL && g_strcmp0(name, g_origin_file) == 0) {
		media_info_clone(&g_item_sub, media);

		if (!g_item_media_id)
			media_info_get_media_id(media, &g_item_media_id);
	}

	if (g_vitem == NULL && type == MEDIA_CONTENT_TYPE_VIDEO)
		media_info_clone(&g_vitem, media);
	else if (g_aitem == NULL && type == MEDIA_CONTENT_TYPE_MUSIC)
		media_info_clone(&g_aitem, media);
	else if (g_bitem == NULL && type == MEDIA_CONTENT_TYPE_BOOK)
		media_info_clone(&g_bitem, media);

	free(name);
	return true;
}

static bool foreach_cb(media_info_h media, void *user_data)
{

	char *id = NULL;
	if (media != NULL) {
		media_info_get_media_id(media, &id);
		if (id != NULL) {
			if (!strcmp(id, g_inserted_media_id)) {
				fprintf(stderr, " file path : %s \n", id);
				foreach_cb_result = MEDIA_CONTENT_ERROR_DB_FAILED;
			}
			free(id);
		}
	}

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
	/* start of TC */
	g_item = NULL;
	g_item_sub = NULL;
	g_vitem = NULL;
	g_aitem = NULL;
	g_inserted_media_handle = NULL;
	g_inserted_audio_handle = NULL;
	g_filter = NULL;

	system_info_get_platform_bool("http://tizen.org/feature/vision.face_recognition", &g_isFaceRecognitionSupported);

	if (storage_foreach_device_supported(__storage_device_supported_cb, NULL) != STORAGE_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	char test_copy[256] = { 0, };
	snprintf(test_copy, sizeof(test_copy), "/bin/cp %s %s", g_origin_path, g_insert_path);
	system(test_copy);

	memset(test_copy, 0, sizeof(test_copy));
	snprintf(test_copy, sizeof(test_copy), "/bin/cp %s %s", g_audio_path, g_insert_audio_path);
	system(test_copy);

	ret = media_info_insert_to_db(g_insert_path, &g_inserted_media_handle);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_insert_to_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_info_insert_to_db(g_insert_audio_path, &g_inserted_audio_handle);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_insert_to_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_info_get_media_id(g_inserted_media_handle, &g_inserted_media_id);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_get_media_id failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_info_get_media_id(g_inserted_audio_handle, &g_inserted_audio_id);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_get_media_id failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	media_filter_create(&g_filter);
	media_filter_set_condition(g_filter, "MEDIA_STORAGE_TYPE=0 AND MEDIA_TYPE IN (0, 1, 3, 5)", MEDIA_CONTENT_COLLATE_NOCASE);
	media_filter_set_storage(g_filter, "media");
	if (g_filter == NULL) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "filter is NULL");
		startup_ret = ret;
		return;
	}

	ret = media_info_foreach_media_from_db(g_filter, sub_item_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_foreach_media_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}
	//media_info_clone(&g_item, g_inserted_media_handle);
	//media_info_get_media_id(g_inserted_media_handle, &g_item_media_id);
}

/**
 * @function		utc_media_info_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_info_cleanup(void)
{
	/* end of TC */
	int i;

	media_info_delete_from_db(g_inserted_media_id);
	media_info_delete_from_db(g_inserted_audio_id);

	media_content_disconnect();

	if (g_item_media_id) {
		free(g_item_media_id);
		g_item_media_id = NULL;
	}

	if (g_inserted_media_id) {
		free(g_inserted_media_id);
		g_inserted_media_id = NULL;
	}

	if (g_inserted_audio_id) {
		free(g_inserted_audio_id);
		g_inserted_audio_id = NULL;
	}

	if (g_filter) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}

	if (g_insert_path != NULL) {
		free(g_insert_path);
		g_insert_path = NULL;
	}
	if (g_origin_path != NULL) {
		free(g_origin_path);
		g_origin_path = NULL;
	}
	if (g_move_dst_path != NULL) {
		free(g_move_dst_path);
		g_move_dst_path = NULL;
	}
	if (g_copy_dst_path != NULL) {
		free(g_copy_dst_path);
		g_copy_dst_path = NULL;
	}
	if (g_audio_path != NULL) {
		free(g_audio_path);
		g_audio_path = NULL;
	}
	if (g_insert_audio_path != NULL) {
		free(g_insert_audio_path);
		g_insert_audio_path = NULL;
	}

	for (i = 0; i < 3; i++) {
		if (g_burst_path_list[i]) {
			free(g_burst_path_list[i]);
			g_burst_path_list[i] = NULL;
		}
		if (g_insert_path_list[i]) {
			free(g_insert_path_list[i]);
			g_insert_path_list[i] = NULL;
		}
	}

	if (g_item) {
		media_info_destroy(g_item);
		g_item = NULL;
	}
	if (g_item_sub) {
		media_info_destroy(g_item_sub);
		g_item_sub = NULL;
	}
	if (g_vitem) {
		media_info_destroy(g_vitem);
		g_vitem = NULL;
	}
	if (g_aitem) {
		media_info_destroy(g_aitem);
		g_aitem = NULL;
	}
	if (g_bitem) {
		media_info_destroy(g_bitem);
		g_bitem = NULL;
	}
	if (g_inserted_media_handle) {
		media_info_destroy(g_inserted_media_handle);
		g_inserted_media_handle = NULL;
	}
	if (g_inserted_audio_handle) {
		media_info_destroy(g_inserted_audio_handle);
		g_inserted_audio_handle = NULL;
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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_insert_to_db(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	media_info_delete_from_db(g_insert_path);

	ret = media_info_insert_to_db(g_insert_path, &g_inserted_media_handle);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

static void _insert_batch_cb(media_content_error_e error, void *user_data)
{
	insert_batch_cb_result = error;
	g_main_loop_quit(g_loop);
}

static gboolean _insert_batch_start(gpointer data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char test_copy[256] = { 0, };
	int i = 0;

	for (i = 0; i < 3; i++) {
		memset(test_copy, 0x0, sizeof(test_copy));
		snprintf(test_copy, sizeof(test_copy), "/bin/cp %s %s", g_origin_path, g_insert_path_list[i]);

		ret = system(test_copy);
	}

	ret = media_info_insert_batch_to_db(g_insert_path_list, sizeof(g_insert_path_list) / sizeof(*g_insert_path_list), _insert_batch_cb, NULL);
	if (ret < 0) {
		g_main_loop_quit(g_loop);
		insert_batch_cb_result = ret;
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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_insert_batch_to_db(NULL, 3, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	GSource *source = NULL;
	GMainContext *context = NULL;

	g_loop = g_main_loop_new(NULL, FALSE);
	context = g_main_loop_get_context(g_loop);
	source = g_idle_source_new();
	g_source_set_callback(source, _insert_batch_start, NULL, NULL);
	g_source_attach(source, context);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	g_loop = NULL;

	assert_eq(insert_batch_cb_result, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_set_favorite(NULL, true);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool _favorite_cb(media_info_h media, void *user_data)
{
	g_cb_ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;
	bool fav = false;
	char *path = NULL;

	media_info_get_file_path(media, &path);

	if (path) {
		if (strcmp(path, g_insert_path) == 0) {
			media_info_get_favorite(media, &fav);

			if (fav == false)
				g_cb_ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
			else
				g_cb_ret = MEDIA_CONTENT_ERROR_NONE;

			free(path);
			path = NULL;

			return false;
		}
		free(path);
		path = NULL;
	} else {
		g_cb_ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

		return false;
	}

	return true;
}

/**
 * @testcase		utc_media_info_set_favorite_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_set_favorite()
 */
int utc_media_info_set_favorite_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	g_cb_ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

	ret = media_info_set_favorite(g_inserted_media_handle, true);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_update_to_db(g_inserted_media_handle);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_foreach_media_from_db(g_filter, _favorite_cb, NULL);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	assert_eq(g_cb_ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_update_to_db(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_update_to_db(g_inserted_media_handle);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

static void thumb_cb(media_content_error_e error, const char *path, void *user_data)
{
	thumb_cb_result = error;
	g_main_loop_quit(g_loop);
}

static gboolean _create_thumbnail_start(gpointer data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_create_thumbnail(g_inserted_media_handle, thumb_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		g_main_loop_quit(g_loop);
		thumb_cb_result = ret;
	}

	return false;
}

static gboolean _create_cancel_thumbnail_start(gpointer data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_create_thumbnail(g_item, thumb_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		g_main_loop_quit(g_loop);
		thumb_cb_result = ret;
	}

	ret = media_info_create_thumbnail(g_item_sub, thumb_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		g_main_loop_quit(g_loop);
		thumb_cb_result = ret;
	}

	ret = media_info_cancel_thumbnail(g_item_sub);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		g_main_loop_quit(g_loop);
		thumb_cb_result = ret;
	}

	return false;
}

/**
 * @testcase		utc_media_info_create_thumbnail_n
 * @since_tizen		2.3
 * @description		Negative test case of media_info_create_thumbnail()
 */
int utc_media_info_create_thumbnail_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_create_thumbnail(NULL, thumb_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	GSource *source = NULL;
	GMainContext *context = NULL;

	g_loop = g_main_loop_new(NULL, FALSE);
	context = g_main_loop_get_context(g_loop);
	source = g_idle_source_new();
	g_source_set_callback(source, _create_thumbnail_start, NULL, NULL);
	g_source_attach(source, context);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	g_loop = NULL;

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(thumb_cb_result, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

static void face_detection_cb(media_content_error_e error, const int face_count, void *user_data)
{
	face_detection_cb_result = error;
	if (g_loop != NULL)
		g_main_loop_quit(g_loop);
}

static gboolean _face_detection_start(gpointer data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	ret = media_info_start_face_detection(g_inserted_media_handle, face_detection_cb, NULL);

	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		if (g_loop != NULL)
			g_main_loop_quit(g_loop);
		face_detection_cb_result = ret;
	}
	return false;
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

	GSource *source = NULL;
	GMainContext *context = NULL;

	g_loop = g_main_loop_new(NULL, FALSE);
	context = g_main_loop_get_context(g_loop);
	source = g_idle_source_new();
	g_source_set_callback(source, _face_detection_start, NULL, NULL);
	g_source_attach(source, context);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	g_loop = NULL;

	if (!g_isFaceRecognitionSupported) {
		assert_eq(face_detection_cb_result, MEDIA_CONTENT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(face_detection_cb_result, MEDIA_CONTENT_ERROR_NONE);
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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_move_to_db(NULL, g_move_dst_path);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_info_move_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_info_move_to_db()
 */
int utc_media_info_move_to_db_p(void)
{
	char *m_id = NULL;
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char test_copy[256] = { 0, };

	snprintf(test_copy, sizeof(test_copy), "/bin/cp %s %s", g_origin_path, g_move_dst_path);

	ret = system(test_copy);

	ret = media_info_move_to_db(g_inserted_media_handle, g_move_dst_path);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_delete_from_db(g_inserted_media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	free(m_id);

	unlink(g_move_dst_path);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_delete_from_db(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_delete_from_db(g_inserted_media_id);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_foreach_media_from_db(NULL, foreach_cb, NULL);

	assert_eq(foreach_cb_result, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	filter_h filter = NULL;
	media_filter_create(&filter);
	media_filter_set_condition(filter, "MEDIA_TYPE=0 OR MEDIA_TYPE=1", MEDIA_CONTENT_COLLATE_NOCASE);

	ret = media_info_foreach_media_from_db(NULL, NULL, NULL);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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
	char *condition = "(MEDIA_TYPE=0 OR MEDIA_TYPE=1 OR MEDIA_TYPE=3) AND MEDIA_STORAGE_TYPE>=0 AND MEDIA_MODIFIED_TIME>=0";

	media_filter_create(&filter);
	media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_NOCASE);
	media_filter_set_order(filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_TITLE, MEDIA_CONTENT_COLLATE_LOCALIZED);

	ret = media_info_foreach_media_from_db(filter, sub_item_cb, NULL);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_destroy(g_item);
	g_item = NULL;
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_info_h dst;

	ret = media_info_clone(&dst, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_info_h dst;

	ret = media_info_clone(&dst, g_item);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_destroy(dst);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = media_info_get_media_id(NULL, &media_id);

	if (media_id) {
		free(media_id);
		media_id = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = media_info_get_media_id(g_item, &media_id);
	if (media_id) {
		free(media_id);
		media_id = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *path = NULL;

	ret = media_info_get_file_path(NULL, &path);

	if (path) {
		free(path);
		path = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *path = NULL;

	ret = media_info_get_file_path(g_item, &path);

	if (path) {
		free(path);
		path = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_info_get_display_name(NULL, &name);

	if (name) {
		free(name);
		name = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_info_get_display_name(g_item, &name);

	if (name) {
		free(name);
		name = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_type_e type = 0;

	ret = media_info_get_media_type(NULL, &type);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_type_e type = 0;

	ret = media_info_get_media_type(g_item, &type);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *mime_type = NULL;

	ret = media_info_get_mime_type(NULL, &mime_type);

	if (mime_type) {
		free(mime_type);
		mime_type = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *mime_type = NULL;

	ret = media_info_get_mime_type(g_item, &mime_type);
	if (mime_type) {
		free(mime_type);
		mime_type = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *thumbnail_path = NULL;

	ret = media_info_get_thumbnail_path(NULL, &thumbnail_path);

	if (thumbnail_path) {
		free(thumbnail_path);
		thumbnail_path = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *thumbnail_path = NULL;

	ret = media_info_get_thumbnail_path(g_item, &thumbnail_path);

	if (thumbnail_path) {
		free(thumbnail_path);
		thumbnail_path = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t date_modi;

	ret = media_info_get_modified_time(NULL, &date_modi);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t date_modi;

	ret = media_info_get_modified_time(g_item, &date_modi);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	unsigned long long size;

	ret = media_info_get_size(NULL, &size);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	unsigned long long size;

	ret = media_info_get_size(g_item, &size);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_storage_e storage_type;

	ret = media_info_get_storage_type(NULL, &storage_type);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_storage_e storage_type;

	ret = media_info_get_storage_type(g_item, &storage_type);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_id = NULL;

	ret = media_info_get_storage_id(NULL, &storage_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *storage_id = NULL;

	ret = media_info_get_storage_id(g_item, &storage_id);

	if (storage_id) {
		free(storage_id);
		storage_id = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	bool is_drm = false;

	ret = media_info_is_drm(NULL, &is_drm);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	bool is_drm = false;

	ret = media_info_is_drm(g_item, &is_drm);
	if (is_drm)
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	double altitude;

	ret = media_info_get_altitude(NULL, &altitude);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	double altitude;

	ret = media_info_get_altitude(g_item, &altitude);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	double latitude;

	ret = media_info_get_latitude(NULL, &latitude);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	double latitude;

	ret = media_info_get_latitude(g_item, &latitude);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	double longitude;

	ret = media_info_get_longitude(NULL, &longitude);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	double longitude;

	ret = media_info_get_longitude(g_item, &longitude);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *description = NULL;

	ret = media_info_get_description(NULL, &description);

	if (description) {
		free(description);
		description = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *description = NULL;

	ret = media_info_get_description(g_item, &description);

	if (description) {
		free(description);
		description = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int rating;

	ret = media_info_get_rating(NULL, &rating);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int rating;

	ret = media_info_get_rating(g_item, &rating);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t added_time;

	ret = media_info_get_added_time(NULL, &added_time);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	time_t added_time;

	ret = media_info_get_added_time(g_item, &added_time);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	bool fav;

	ret = media_info_get_favorite(NULL, &fav);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	bool fav;

	ret = media_info_get_favorite(g_item, &fav);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_info_h media = NULL;

	ret = media_info_get_media_from_db(NULL, &media);

	if (media) {
		media_info_destroy(media);
		media = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_info_h media = NULL;

	ret = media_info_get_media_from_db(g_item_media_id, &media);

	if (media) {
		media_info_destroy(media);
		media = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_media_from_db_by_path(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_info_h handle = NULL;

	ret = media_info_get_media_from_db_by_path(g_insert_path, &handle);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_destroy(handle);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	image_meta_h image = NULL;

	ret = media_info_get_image(NULL, &image);

	if (image) {
		image_meta_destroy(image);
		image = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	image_meta_h image = NULL;

	ret = media_info_get_image(g_item, &image);

	if (image) {
		image_meta_destroy(image);
		image = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	video_meta_h video = NULL;

	ret = media_info_get_video(NULL, &video);

	if (video) {
		video_meta_destroy(video);
		video = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	video_meta_h video = NULL;

	ret = media_info_get_video(g_vitem, &video);

	if (video) {
		video_meta_destroy(video);
		video = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_h audio = NULL;

	ret = media_info_get_audio(NULL, &audio);

	if (audio) {
		audio_meta_destroy(audio);
		audio = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	audio_meta_h audio = NULL;

	ret = media_info_get_audio(g_aitem, &audio);

	if (audio) {
		audio_meta_destroy(audio);
		audio = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	book_meta_h book = NULL;

	ret = media_info_get_book(NULL, &book);

	if (book)
		book_meta_destroy(book);

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	book_meta_h book = NULL;

	ret = media_info_get_book(g_bitem, &book);

	if (book) {
		book_meta_destroy(book);
		book = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

static bool sub_tag_cb(media_tag_h tag, void *user_data)
{
	char *name = NULL;
	if (tag) {
		media_tag_get_name(tag, &name);
	}

	return false;
}

static bool sub_bookmark_cb(media_bookmark_h bookmark, void *user_data)
{
	int bm_id;

	if (bookmark) {
		media_bookmark_get_bookmark_id(bookmark, &bm_id);
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	ret = media_info_foreach_tag_from_db(NULL, filter, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	media_filter_create(&filter);

	ret = media_info_foreach_tag_from_db(g_item_media_id, filter, sub_tag_cb, NULL);
	media_filter_destroy(filter);
	filter = NULL;
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	ret = media_info_foreach_bookmark_from_db(NULL, filter, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	ret = media_filter_create(&filter);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_foreach_bookmark_from_db(g_item_media_id, filter, sub_bookmark_cb, NULL);
	media_filter_destroy(filter);
	filter = NULL;
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	ret = media_info_get_bookmark_count_from_db(NULL, filter, &count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	media_filter_create(&filter);

	ret = media_info_get_bookmark_count_from_db(g_item_media_id, filter, &count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	ret = media_info_get_media_count_from_db(filter, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	media_filter_create(&filter);

	ret = media_info_get_media_count_from_db(filter, &count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	ret = media_info_get_tag_count_from_db(NULL, filter, &count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	media_filter_create(&filter);

	ret = media_info_get_tag_count_from_db(g_item_media_id, filter, &count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_timeline(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	time_t t_value = 0;
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_timeline(g_item, &t_value);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_title(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	char *title = NULL;
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_title(g_item, &title);

	if (title) {
		free(title);
		title = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_is_360_content(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	bool is_360 = 0;
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_is_360_content(g_item, &is_360);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_cancel_thumbnail(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	GSource *source = NULL;
	GMainContext *context = NULL;

	g_loop = g_main_loop_new(NULL, FALSE);
	context = g_main_loop_get_context(g_loop);
	source = g_idle_source_new();
	g_source_set_callback(source, _create_cancel_thumbnail_start, NULL, NULL);
	g_source_attach(source, context);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	g_loop = NULL;

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(thumb_cb_result, MEDIA_CONTENT_ERROR_NONE);

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

	ret = media_info_start_face_detection(g_item, face_detection_cb, NULL);
	if (!g_isFaceRecognitionSupported) {
		assert_eq(ret, MEDIA_CONTENT_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	}

	ret = media_info_cancel_face_detection(g_item);
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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	ret = media_info_get_face_count_from_db(NULL, filter, &count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	int count;

	media_filter_create(&filter);

	ret = media_info_get_face_count_from_db(g_item_media_id, filter, &count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

	return 0;
}

static bool face_cb(media_face_h face, void *user_data)
{
	char *face_id = NULL;

	if (face) {
		media_face_get_face_id(face, &face_id);
	}

	if (face_id) {
		free(face_id);
		face_id = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	ret = media_info_foreach_face_from_db(NULL, filter, face_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;

	media_filter_create(&filter);

	ret = media_info_foreach_face_from_db(g_item_media_id, filter, face_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (filter) {
		media_filter_destroy(filter);
		filter = NULL;
	}

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

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_generate_thumbnail(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *thumb_path = NULL;

	ret = media_info_generate_thumbnail(g_inserted_media_handle);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_get_thumbnail_path(g_inserted_media_handle, &thumb_path);
	if (strlen(thumb_path) > 0) {
		free(thumb_path);
		thumb_path = NULL;
	} else {
		ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
