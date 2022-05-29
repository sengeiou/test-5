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

//& set: MediaFace

static media_face_h g_face = NULL;
static media_face_h g_face_dst = NULL;
static char *g_media_id = NULL;
static char *g_face_id = NULL;

static char *img_path = NULL;
static const char *img_file = "image.jpg";

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool __storage_device_supported_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
	if (type == STORAGE_TYPE_INTERNAL) {
		img_path = (char *)malloc(strlen(path) + strlen(img_file) + 6);
		memset(img_path, 0x00, strlen(path) + strlen(img_file) + 6);
		snprintf(img_path, strlen(path) + strlen(img_file) + 6, "%s/res/%s", path, img_file);
		return false;
	}
	return true;
}

static bool face_cb(media_face_h face, void *user_data)
{
	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_clone(&g_face, face);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = ret;
		return false;
	}

	ret = media_face_get_face_id(g_face, &g_face_id);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = ret;
		return false;
	}

	return false;
}

static bool sub_face_cb(media_face_h face, void *user_data)
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

static bool media_item_cb(media_info_h media, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_media_id(media, &g_media_id);
	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_media_id == NULL)) {
		return false;
	}

	return false;
}

/**
 * @function		utc_media_face_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_face_startup(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	char condition[50] = { 0, };

	g_face = NULL;
	g_face_dst = NULL;
	g_media_id = NULL;
	g_face_id = NULL;

	if (storage_foreach_device_supported(__storage_device_supported_cb, NULL) != STORAGE_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_content_scan_file(img_path);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = ret;
		return;
	}

	snprintf(condition, sizeof(condition), "MEDIA_DISPLAY_NAME='%s'", img_file);

	media_filter_create(&filter);
	media_filter_set_condition(filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);
	media_filter_set_order(filter, MEDIA_CONTENT_ORDER_ASC, MEDIA_DISPLAY_NAME, MEDIA_CONTENT_COLLATE_DEFAULT);
	if (filter == NULL) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_filter_create failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_info_foreach_media_from_db(filter, media_item_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_foreach_media_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	media_filter_destroy(filter);
	filter = NULL;

	ret = media_face_create(g_media_id, &g_face);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_face_create failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_face_set_face_rect(g_face, 10, 10, 10, 10);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_face_set_face_rect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_face_set_tag(g_face, "Test");
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_face_set_tag failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_face_insert_to_db(g_face);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_face_insert_to_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_face_destroy(g_face);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_face_destroy failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_info_foreach_face_from_db(g_media_id, NULL, face_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, " media_info_foreach_face_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}
}

/**
 * @function		utc_media_face_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_face_cleanup(void)
{
	if (g_media_id) {
		free(g_media_id);
		g_media_id = NULL;
	}

	if (g_face_id) {
		media_face_delete_from_db(g_face_id);
		free(g_face_id);
		g_face_id = NULL;
	}

	if (g_face) {
		media_face_destroy(g_face);
		g_face = NULL;
	}

	if (g_face_dst) {
		media_face_destroy(g_face_dst);
		g_face_dst = NULL;
	}

	if (img_path) {
		free(img_path);
		img_path = NULL;
	}
	media_content_disconnect();
}

/**
 * @testcase		utc_media_face_clone_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_clone()
 */
int utc_media_face_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *face_id = NULL;

	ret = media_face_clone(&g_face_dst, g_face);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	media_face_get_face_id(g_face_dst, &face_id);
	if (strncmp(g_face_id, face_id, strlen(face_id)) == 0) {
		ret = MEDIA_CONTENT_ERROR_NONE;
	} else {
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;
	}
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (face_id) {
		free(face_id);
		face_id = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_face_clone_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_clone()
 */
int utc_media_face_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_clone(&g_face_dst, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_destroy_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_destroy()
 */
int utc_media_face_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_clone(&g_face_dst, g_face);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_face_destroy_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_destroy()
 */
int utc_media_face_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_get_face_id_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_get_face_id()
 */
int utc_media_face_get_face_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *face_id = NULL;

	ret = media_face_get_face_id(g_face, &face_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (face_id) {
		free(face_id);
		face_id = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_face_get_face_id_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_get_face_id()
 */
int utc_media_face_get_face_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *face_id = NULL;

	ret = media_face_get_face_id(NULL, &face_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_get_media_id_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_get_media_id()
 */
int utc_media_face_get_media_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = media_face_get_media_id(g_face, &media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (media_id) {
		free(media_id);
		media_id = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_face_get_media_id_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_get_media_id()
 */
int utc_media_face_get_media_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *media_id = NULL;

	ret = media_face_get_media_id(NULL, &media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_get_face_rect_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_get_face_rect()
 */
int utc_media_face_get_face_rect_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	unsigned int rect_x = -1;
	unsigned int rect_y = -1;
	unsigned int rect_w = -1;
	unsigned int rect_h = -1;

	ret = media_face_get_face_rect(g_face, &rect_x, &rect_y, &rect_w, &rect_h);
	if (rect_x <= 0 || rect_y <= 0 || rect_w <= 0 || rect_h <= 0)
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_face_get_face_rect_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_get_face_rect()
 */
int utc_media_face_get_face_rect_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	unsigned int rect_x = -1;
	unsigned int rect_y = -1;
	unsigned int rect_w = -1;
	unsigned int rect_h = -1;

	ret = media_face_get_face_rect(NULL, &rect_x, &rect_y, &rect_w, &rect_h);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_get_orientation_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_get_orientation()
 */
int utc_media_face_get_orientation_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_orientation_e orient;

	ret = media_face_get_orientation(g_face, &orient);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_face_get_orientation_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_get_orientation()
 */
int utc_media_face_get_orientation_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_orientation_e orient;

	ret = media_face_get_orientation(NULL, &orient);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_get_tag_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_get_tag()
 */
int utc_media_face_get_tag_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *tag = NULL;

	ret = media_face_get_tag(g_face, &tag);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (tag) {
		free(tag);
		tag = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_face_get_tag_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_get_tag()
 */
int utc_media_face_get_tag_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *tag = NULL;

	ret = media_face_get_tag(NULL, &tag);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_create_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_create()
 */
int utc_media_face_create_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_create(g_media_id, &g_face_dst);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_face_create_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_create()
 */
int utc_media_face_create_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool _set_face_rect_cb(media_face_h face, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	unsigned int rect_x = -1;
	unsigned int rect_y = -1;
	unsigned int rect_w = -1;
	unsigned int rect_h = -1;

	ret = media_face_get_face_rect(g_face, &rect_x, &rect_y, &rect_w, &rect_h);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (rect_x != 20 || rect_y != 20 || rect_w != 20 || rect_h != 20) {
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;
		assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	}

	return false;
}

/**
 * @testcase		utc_media_face_set_face_rect_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_set_face_rect()
 */
int utc_media_face_set_face_rect_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	ret = media_face_set_face_rect(g_face, 20, 20, 20, 20);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_update_to_db(g_face);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_foreach_face_from_db(g_media_id, NULL, _set_face_rect_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_face_set_face_rect_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_set_face_rect()
 */
int utc_media_face_set_face_rect_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_set_face_rect(NULL, 20, 20, 20, 20);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool _set_orientation_cb(media_face_h face, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_content_orientation_e orient;

	ret = media_face_get_orientation(g_face, &orient);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (orient != MEDIA_CONTENT_ORIENTATION_NORMAL) {
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;
		assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	}

	return false;
}

/**
 * @testcase		utc_media_face_set_orientation_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_set_orientation()
 */
int utc_media_face_set_orientation_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	ret = media_face_set_orientation(g_face, MEDIA_CONTENT_ORIENTATION_NORMAL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_update_to_db(g_face);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_foreach_face_from_db(g_media_id, NULL, _set_orientation_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_face_set_orientation_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_set_orientation()
 */
int utc_media_face_set_orientation_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_set_orientation(NULL, MEDIA_CONTENT_ORIENTATION_NORMAL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool _set_tag_cb(media_face_h face, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *tag = NULL;

	ret = media_face_get_tag(g_face, &tag);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (strncmp(tag, "new_tag", strlen("new_tag")) != 0) {
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;
		assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	}

	return false;
}

/**
 * @testcase		utc_media_face_set_tag_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_set_tag()
 */
int utc_media_face_set_tag_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	ret = media_face_set_tag(g_face, "new_tag");
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_update_to_db(g_face);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_foreach_face_from_db(g_media_id, NULL, _set_tag_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_face_set_tag_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_set_tag()
 */
int utc_media_face_set_tag_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_set_tag(NULL, "new_tag");
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_insert_to_db_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_insert_to_db()
 */
int utc_media_face_insert_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	char *face_id = NULL;

	int ret = MEDIA_CONTENT_ERROR_NONE;
	ret = media_face_clone(&g_face_dst, g_face);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_set_face_rect(g_face_dst, 15, 15, 15, 15);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_insert_to_db(g_face_dst);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_get_face_id(g_face_dst, &face_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_delete_from_db(face_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (face_id) {
		free(face_id);
		face_id = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_face_insert_to_db_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_insert_to_db()
 */
int utc_media_face_insert_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_insert_to_db(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_update_to_db_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_update_to_db()
 */
int utc_media_face_update_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	ret = media_face_update_to_db(g_face);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_face_update_to_db_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_update_to_db()
 */
int utc_media_face_update_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_update_to_db(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_delete_from_db_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_delete_from_db()
 */
int utc_media_face_delete_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);
	char *face_id = NULL;

	int ret = MEDIA_CONTENT_ERROR_NONE;
	ret = media_face_clone(&g_face_dst, g_face);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_set_face_rect(g_face_dst, 15, 15, 15, 15);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_insert_to_db(g_face_dst);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_get_face_id(g_face_dst, &face_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_face_delete_from_db(face_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (face_id) {
		free(face_id);
		face_id = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_face_delete_from_db_n
 * @since_tizen		3.0
 * @description		Negative test case of media_face_delete_from_db()
 */
int utc_media_face_delete_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_delete_from_db(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_get_face_count_from_db_p
 * @since_tizen		4.0
 * @description		Positive test case of media_face_get_face_count_from_db()
 */
int utc_media_face_get_face_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int face_cnt = 0;

	ret = media_face_get_face_count_from_db(NULL, &face_cnt);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_face_get_face_count_from_db_n
 * @since_tizen		4.0
 * @description		Negative test case of media_face_get_face_count_from_db()
 */
int utc_media_face_get_face_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_get_face_count_from_db(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_foreach_face_from_db_p
 * @since_tizen		4.0
 * @description		Positive test case of media_face_foreach_face_from_db()
 */
int utc_media_face_foreach_face_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_foreach_face_from_db(NULL, sub_face_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_face_foreach_face_from_db_n
 * @since_tizen		4.0
 * @description		Negative test case of media_face_foreach_face_from_db()
 */
int utc_media_face_foreach_face_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_face_foreach_face_from_db(NULL, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}
