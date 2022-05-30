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
#include <limits.h>

//& set: MediaFace

static media_face_h g_face = NULL;
static media_face_h g_face_dst = NULL;
static char *g_media_id = NULL;
static char *g_face_id = NULL;
static char g_image_path[PATH_MAX + 1] = { 0, };
static int startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool __face_cb(media_face_h face, void *user_data)
{
	if (media_face_clone(&g_face, face) != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_face_clone failed.\\n", __LINE__);
		return false;
	}

	if (media_face_get_face_id(g_face, &g_face_id) != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_face_get_face_id failed.\\n", __LINE__);
		return false;
	}

	return false;
}

static bool __sub_face_cb(media_face_h face, void *user_data)
{
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
	char *root_path = NULL;
	media_info_h media = NULL;

	if (storage_get_root_directory(0, &root_path) == STORAGE_ERROR_NONE) {
		snprintf(g_image_path, PATH_MAX, "%s/res/image.jpg", root_path);
		FREE_MEMORY(root_path);
	}

	startup_ret = media_content_connect();
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_content_connect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_info_get_media_from_db_by_path(g_image_path, &media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		startup_ret = media_info_insert_to_db(g_image_path, &media);
		if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
			FPRINTF("[Line : %d] media_info_insert_to_db failed.\\n", __LINE__);
			return;
		}
	}

	startup_ret = media_info_get_media_id(media, &g_media_id);
	media_info_destroy(media);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_info_get_media_id failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_face_create(g_media_id, &g_face);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_face_create failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_face_set_face_rect(g_face, 10, 10, 10, 10);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_face_set_face_rect failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_face_set_tag(g_face, "Test");
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_face_set_tag failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_face_insert_to_db(g_face);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_face_insert_to_db failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_face_destroy(g_face);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_face_destroy failed.\\n", __LINE__);
		return;
	}

	startup_ret = media_info_foreach_face_from_db(g_media_id, NULL, __face_cb, NULL);
	if (startup_ret != MEDIA_CONTENT_ERROR_NONE) {
		FPRINTF("[Line : %d] media_info_foreach_face_from_db failed.\\n", __LINE__);
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
	FREE_MEMORY(g_media_id);

	if (g_face_id) {
		media_face_delete_from_db(g_face_id);
		FREE_MEMORY(g_face_id);
	}

	if (g_face) {
		media_face_destroy(g_face);
		g_face = NULL;
	}

	if (g_face_dst) {
		media_face_destroy(g_face_dst);
		g_face_dst = NULL;
	}

	memset(&g_image_path, 0, PATH_MAX + 1);

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

	assert_eq(media_face_clone(&g_face_dst, g_face), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_face_clone(&g_face_dst, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_face_clone(NULL, g_face), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_face_clone(&g_face_dst, g_face), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_face_destroy(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	char *face_id = NULL;

	assert_eq(media_face_get_face_id(g_face, &face_id), MEDIA_CONTENT_ERROR_NONE);
	FREE_MEMORY(face_id);

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

	char *face_id = NULL;

	assert_eq(media_face_get_face_id(NULL, &face_id), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_face_get_face_id(g_face, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	char *media_id = NULL;

	assert_eq(media_face_get_media_id(g_face, &media_id), MEDIA_CONTENT_ERROR_NONE);
	FREE_MEMORY(media_id);

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

	char *media_id = NULL;

	assert_eq(media_face_get_media_id(NULL, &media_id), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_face_get_media_id(g_face, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	unsigned int rect_x = 0;
	unsigned int rect_y = 0;
	unsigned int rect_w = 0;
	unsigned int rect_h = 0;

	assert_eq(media_face_get_face_rect(g_face, &rect_x, &rect_y, &rect_w, &rect_h), MEDIA_CONTENT_ERROR_NONE);
	assert_eq(rect_x, 10);
	assert_eq(rect_y, 10);
	assert_eq(rect_w, 10);
	assert_eq(rect_h, 10);

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

	unsigned int rect_x = 0;
	unsigned int rect_y = 0;
	unsigned int rect_w = 0;
	unsigned int rect_h = 0;

	assert_eq(media_face_get_face_rect(NULL, &rect_x, &rect_y, &rect_w, &rect_h), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_face_get_face_rect(g_face, NULL, &rect_y, &rect_w, &rect_h), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_face_get_face_rect(g_face, &rect_x, NULL, &rect_w, &rect_h), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_face_get_face_rect(g_face, &rect_x, &rect_y, NULL, &rect_h), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_face_get_face_rect(g_face, &rect_x, &rect_y, &rect_w, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	media_content_orientation_e orient = MEDIA_CONTENT_ORIENTATION_NOT_AVAILABLE;

	assert_eq(media_face_get_orientation(g_face, &orient), MEDIA_CONTENT_ERROR_NONE);

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

	media_content_orientation_e orient = MEDIA_CONTENT_ORIENTATION_NOT_AVAILABLE;

	assert_eq(media_face_get_orientation(NULL, &orient), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_face_get_orientation(g_face, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	char *tag = NULL;

	assert_eq(media_face_get_tag(g_face, &tag), MEDIA_CONTENT_ERROR_NONE);
	FREE_MEMORY(tag);

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

	char *tag = NULL;

	assert_eq(media_face_get_tag(NULL, &tag), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_face_get_tag(g_face, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_face_create(g_media_id, &g_face_dst), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_face_create(NULL, &g_face_dst), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	assert_eq(media_face_create(g_face, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_set_face_rect_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_set_face_rect()
 */
int utc_media_face_set_face_rect_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_set_face_rect(g_face, 20, 20, 20, 20), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_update_to_db(g_face), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_face_set_face_rect(NULL, 20, 20, 20, 20), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_set_orientation_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_set_orientation()
 */
int utc_media_face_set_orientation_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_set_orientation(g_face, MEDIA_CONTENT_ORIENTATION_NORMAL), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_update_to_db(g_face), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_face_set_orientation(NULL, MEDIA_CONTENT_ORIENTATION_NORMAL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_face_set_tag_p
 * @since_tizen		3.0
 * @description		Positive test case of media_face_set_tag()
 */
int utc_media_face_set_tag_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_set_tag(g_face, "new_tag"), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_update_to_db(g_face), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_face_set_tag(NULL, "new_tag"), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_face_clone(&g_face_dst, g_face), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_set_face_rect(g_face_dst, 15, 15, 15, 15), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_insert_to_db(g_face_dst), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_get_face_id(g_face_dst, &face_id), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_delete_from_db(face_id), MEDIA_CONTENT_ERROR_NONE);
	FREE_MEMORY(face_id);

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

	assert_eq(media_face_insert_to_db(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_face_update_to_db(g_face), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_face_update_to_db(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_face_clone(&g_face_dst, g_face), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_set_face_rect(g_face_dst, 15, 15, 15, 15), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_insert_to_db(g_face_dst), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_get_face_id(g_face_dst, &face_id), MEDIA_CONTENT_ERROR_NONE);

	assert_eq(media_face_delete_from_db(face_id), MEDIA_CONTENT_ERROR_NONE);
	FREE_MEMORY(face_id);

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

	assert_eq(media_face_delete_from_db(NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	int face_cnt = 0;

	assert_eq(media_face_get_face_count_from_db(NULL, &face_cnt), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_face_get_face_count_from_db(NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

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

	assert_eq(media_face_foreach_face_from_db(NULL, __sub_face_cb, NULL), MEDIA_CONTENT_ERROR_NONE);

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

	assert_eq(media_face_foreach_face_from_db(NULL, NULL, NULL), MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}
