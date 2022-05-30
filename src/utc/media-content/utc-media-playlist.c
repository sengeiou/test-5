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

#define TEST_SET_PLAYLIST_SUB_1 "test_playlist_123"
#define TEST_SET_PLAYLIST_SUB_2 "test_playlist_234"
#define TEST_SET_PLAYLIST_SUB_3 "test_playlist_345"

//& set: MediaPlaylist
static const char *img_file = "image.jpg";
static char *img_path = NULL;
static const char *playlist_file = "playlist.m3u";
static char *playlist_path = NULL;
static const char *create_file = "temp.m3u";
static char *create_path = NULL;
static const char *copy_file = "copy.m3u";
static char *copy_path = NULL;

static media_playlist_h g_playlist;
static media_playlist_h g_playlist_dst;

static filter_h g_filter;
static char *g_media_id = NULL;
static int g_playlist_id = 0;
static int g_playlist_member_id = 0;

static media_content_error_e startup_ret = MEDIA_CONTENT_ERROR_NONE;

static bool __storage_device_supported_cb(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
	if (type == STORAGE_TYPE_INTERNAL) {
		img_path = (char *)malloc(strlen(path) + strlen(img_file) + 6);
		memset(img_path, 0x00, strlen(path) + strlen(img_file) + 6);
		snprintf(img_path, strlen(path) + strlen(img_file) + 6, "%s/res/%s", path, img_file);

		playlist_path = (char *)malloc(strlen(path) + strlen(playlist_file) + 6);
		memset(playlist_path, 0x00, strlen(path) + strlen(playlist_file) + 6);
		snprintf(playlist_path, strlen(path) + strlen(playlist_file) + 6, "%s/res/%s", path, playlist_file);

		create_path = (char *)malloc(strlen(path) + strlen(create_file) + 6);
		memset(create_path, 0x00, strlen(path) + strlen(create_file) + 6);
		snprintf(create_path, strlen(path) + strlen(create_file) + 6, "%s/res/%s", path, create_file);

		copy_path = (char *)malloc(strlen(path) + strlen(copy_file) + 6);
		memset(copy_path, 0x00, strlen(path) + strlen(copy_file) + 6);
		snprintf(copy_path, strlen(path) + strlen(copy_file) + 6, "%s/res/%s", path, copy_file);
		return false;
	}
	return true;
}

static bool media_item_cb(media_info_h media, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_info_get_media_id(media, &g_media_id);

	if ((ret != MEDIA_CONTENT_ERROR_NONE) || (g_media_id == NULL)) {
		fprintf(stderr, "CB error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_info_get_media_id failed (code: %d)\n", ret);
		return false;
	}

	return true;
}

static bool playlist_item_cb(int playlist_member_id, media_info_h media, void *user_data)
{
	fprintf(stderr, "member id: %d", playlist_member_id);
	g_playlist_member_id = playlist_member_id;

	return true;
}

static bool playlist_cb(media_playlist_h playlist, void *user_data)
{
	int playlist_id = 0;
	char *name = NULL;
	if (playlist != NULL) {
		media_playlist_get_playlist_id(g_playlist, &playlist_id);
		media_playlist_get_name(g_playlist, &name);
	}

	FREE_MEMORY(name);

	return true;
}

/**
 * @function		utc_media_playlist_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_playlist_startup(void)
{
	/* start of TC */

	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;
	if (storage_foreach_device_supported(__storage_device_supported_cb, NULL) != STORAGE_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
	}

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	char *condition = "MEDIA_TYPE=3 AND MEDIA_STORAGE_TYPE=0";	//Music and internal storage

	media_filter_create(&g_filter);
	media_filter_set_condition(g_filter, condition, MEDIA_CONTENT_COLLATE_DEFAULT);

	if (g_filter == NULL) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "g_filter is NULL");
		startup_ret = ret;
		return;
	}

	ret = media_info_foreach_media_from_db(g_filter, media_item_cb, NULL);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_info_foreach_media_from_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}
	//media_playlist_get_playlist_id(g_playlist, &g_playlist_id);
	//media_playlist_delete_from_db(g_playlist_id);

	// to check if the same date has been already inserted
	ret = media_playlist_insert_to_db(TEST_SET_PLAYLIST_SUB_1, &g_playlist);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_playlist_insert_to_db failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	ret = media_playlist_get_playlist_id(g_playlist, &g_playlist_id);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_playlist_get_playlist_id failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	char test_copy[256] = { 0, };
	snprintf(test_copy, sizeof(test_copy), "/bin/cp %s %s", create_path, copy_path);

	ret = system(test_copy);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_playlist_get_playlist_id failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}
}

/**
 * @function		utc_media_playlist_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_playlist_cleanup(void)
{
	/* end of TC */
	FREE_MEMORY(g_media_id);

	if (g_filter != NULL) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}

	if (g_playlist != NULL) {
		media_playlist_destroy(g_playlist);
		g_playlist = NULL;
	}

	media_playlist_delete_from_db(g_playlist_id);
	media_content_disconnect();
	FREE_MEMORY(img_path);
	FREE_MEMORY(playlist_path);
	FREE_MEMORY(create_path);
	FREE_MEMORY(copy_path);
}

/**
 * @testcase		utc_media_playlist_insert_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_insert_to_db()
 */
int utc_media_playlist_insert_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_insert_to_db(NULL, &g_playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_insert_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_insert_to_db()
 */
int utc_media_playlist_insert_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;
	int playlist_id = 0;

	media_playlist_delete_from_db(g_playlist_id);

	/* precondition */
	ret = media_playlist_destroy(g_playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	/* actual test */
	ret = media_playlist_insert_to_db(TEST_SET_PLAYLIST_SUB_2, &g_playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_get_name(g_playlist, &name);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (strcmp(name, TEST_SET_PLAYLIST_SUB_2) == 0)
		ret = MEDIA_CONTENT_ERROR_NONE;
	else
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

	FREE_MEMORY(name);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_get_playlist_id(g_playlist, &playlist_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_delete_from_db(playlist_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_delete_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_delete_from_db()
 */
int utc_media_playlist_delete_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_delete_from_db(-1);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_delete_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_delete_from_db()
 */
int utc_media_playlist_delete_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_delete_from_db(g_playlist_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_playlist_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_get_playlist_count_from_db()
 */
int utc_media_playlist_get_playlist_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_get_playlist_count_from_db(g_filter, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_playlist_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_get_playlist_count_from_db()
 */
int utc_media_playlist_get_playlist_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int playlist_count = 0;

	ret = media_playlist_get_playlist_count_from_db(g_filter, &playlist_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_foreach_playlist_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_foreach_playlist_from_db()
 */
int utc_media_playlist_foreach_playlist_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_foreach_playlist_from_db(g_filter, NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_foreach_playlist_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_foreach_playlist_from_db()
 */
int utc_media_playlist_foreach_playlist_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_foreach_playlist_from_db(g_filter, playlist_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_media_count_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_get_media_count_from_db()
 */
int utc_media_playlist_get_media_count_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_get_media_count_from_db(0, g_filter, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_media_count_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_get_media_count_from_db()
 */
int utc_media_playlist_get_media_count_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = 0;

	ret = media_playlist_get_media_count_from_db(g_playlist_id, g_filter, &media_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_foreach_media_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_foreach_media_from_db()
 */
int utc_media_playlist_foreach_media_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_foreach_media_from_db(0, g_filter, playlist_item_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_foreach_media_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_foreach_media_from_db()
 */
int utc_media_playlist_foreach_media_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_foreach_media_from_db(g_playlist_id, g_filter, playlist_item_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_destroy_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_destroy()
 */
int utc_media_playlist_destroy_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_destroy(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_destroy_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_destroy()
 */
int utc_media_playlist_destroy_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_clone(&g_playlist_dst, g_playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_destroy(g_playlist_dst);
	g_playlist_dst = NULL;

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_clone_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_clone()
 */
int utc_media_playlist_clone_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_clone(&g_playlist_dst, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_clone_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_clone()
 */
int utc_media_playlist_clone_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *org_name = NULL;
	char *dst_name = NULL;

	ret = media_playlist_clone(&g_playlist_dst, g_playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_get_name(g_playlist, &org_name);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_get_name(g_playlist_dst, &dst_name);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (org_name != NULL && dst_name != NULL) {
		if (strcmp(org_name, dst_name))
			ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;

		FREE_MEMORY(org_name);
		FREE_MEMORY(dst_name);
	} else {
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;
	}
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_destroy(g_playlist_dst);
	g_playlist_dst = NULL;

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_playlist_from_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_get_playlist_from_db()
 */
int utc_media_playlist_get_playlist_from_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_playlist_h playlist;

	ret = media_playlist_get_playlist_from_db(0, &playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_playlist_from_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_get_playlist_from_db()
 */
int utc_media_playlist_get_playlist_from_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_playlist_h playlist = NULL;

	ret = media_playlist_get_playlist_from_db(g_playlist_id, &playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (playlist) {
		media_playlist_destroy(playlist);
		playlist = NULL;
	}

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_playlist_id_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_get_playlist_id()
 */
int utc_media_playlist_get_playlist_id_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_get_playlist_id(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_playlist_id_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_get_playlist_id()
 */
int utc_media_playlist_get_playlist_id_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int playlist_id = 0;

	ret = media_playlist_get_playlist_id(g_playlist, &playlist_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_name_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_get_name()
 */
int utc_media_playlist_get_name_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_playlist_get_name(NULL, &name);
	FREE_MEMORY(name);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_name_p
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_get_name()
 */
int utc_media_playlist_get_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;

	ret = media_playlist_get_name(g_playlist, &name);
	FREE_MEMORY(name);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_play_order_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_get_play_order()
 */
int utc_media_playlist_get_play_order_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_get_play_order(NULL, g_playlist_member_id, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_play_order_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_get_play_order()
 */
int utc_media_playlist_get_play_order_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int playlist_order = 0;

	ret = media_playlist_get_play_order(g_playlist, g_playlist_member_id, &playlist_order);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_update_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_update_to_db()
 */
int utc_media_playlist_update_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_update_to_db(NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_update_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_update_to_db()
 */
int utc_media_playlist_update_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_update_to_db(g_playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_set_name_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_set_name()
 */
int utc_media_playlist_set_name_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_set_name(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool _set_name_cb(media_playlist_h playlist, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *name = NULL;
	int playlist_id = 0;

	ret = media_playlist_get_playlist_id(playlist, &playlist_id);

	if (playlist_id == g_playlist_id) {
		ret = media_playlist_get_name(playlist, &name);

		if (strcmp(name, "myPlaylist") != 0)
			ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	FREE_MEMORY(name);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return true;
}

/**
 * @testcase		utc_media_playlist_set_name_p
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_set_name()
 */
int utc_media_playlist_set_name_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_set_name(g_playlist, "myPlaylist");

	ret = media_playlist_update_to_db(g_playlist);

	ret = media_playlist_foreach_playlist_from_db(g_filter, _set_name_cb, NULL);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_add_media_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_add_media()
 */
int utc_media_playlist_add_media_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_add_media(NULL, g_media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_add_media_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_add_media()
 */
int utc_media_playlist_add_media_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	int media_count = -1;
	int playlist_id;

	ret = media_playlist_add_media(g_playlist, g_media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_update_to_db(g_playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_get_playlist_id(g_playlist, &playlist_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_get_media_count_from_db(playlist_id, g_filter, &media_count);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	if (media_count > 0)
		ret = MEDIA_CONTENT_ERROR_NONE;
	else
		ret = MEDIA_CONTENT_ERROR_INVALID_OPERATION;
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_set_play_order_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_set_play_order()
 */
int utc_media_playlist_set_play_order_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_set_play_order(NULL, g_playlist_member_id, 3);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool _set_play_order_cb(media_playlist_h playlist, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	int playlist_order = 0;
	int playlist_id = 0;

	ret = media_playlist_get_playlist_id(playlist, &playlist_id);

	if (playlist_id == g_playlist_id) {
		ret = media_playlist_get_play_order(playlist, g_playlist_member_id, &playlist_order);

		if (playlist_order != 1)
			ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return true;
}

/**
 * @testcase		utc_media_playlist_set_play_order_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_set_play_order()
 */
int utc_media_playlist_set_play_order_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	media_playlist_add_media(g_playlist, g_media_id);
	media_playlist_update_to_db(g_playlist);

	media_playlist_foreach_media_from_db(g_playlist_id, g_filter, playlist_item_cb, NULL);
	fprintf(stderr, "member id: %d", g_playlist_member_id);
	ret = media_playlist_set_play_order(g_playlist, g_playlist_member_id, 1);

	media_playlist_update_to_db(g_playlist);

	ret = media_playlist_foreach_playlist_from_db(g_filter, _set_play_order_cb, NULL);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_media_playlist_remove_media_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_remove_media()
 */
int utc_media_playlist_remove_media_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_remove_media(NULL, g_playlist_member_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_remove_media_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_remove_media()
 */
int utc_media_playlist_remove_media_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_add_media(g_playlist, g_media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_update_to_db(g_playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_foreach_media_from_db(g_playlist_id, g_filter, playlist_item_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	fprintf(stderr, "member id: %d", g_playlist_member_id);

	ret = media_playlist_remove_media(g_playlist, g_playlist_member_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_update_to_db(g_playlist);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_thumbnail_path_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_get_thumbnail_path()
 */
int utc_media_playlist_get_thumbnail_path_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_get_thumbnail_path(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_get_thumbnail_path_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_get_thumbnail_path()
 */
int utc_media_playlist_get_thumbnail_path_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	char *thumbnail_path = NULL;
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_get_thumbnail_path(g_playlist, &thumbnail_path);
	FREE_MEMORY(thumbnail_path);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_set_thumbnail_path_n
 * @since_tizen		2.3
 * @description		Negative test case of media_playlist_set_thumbnail_path()
 */
int utc_media_playlist_set_thumbnail_path_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_set_thumbnail_path(NULL, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

static bool _set_thumbnail_path_cb(media_playlist_h playlist, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	char *get_thumb_path = NULL;
	int playlist_id = 0;

	ret = media_playlist_get_playlist_id(playlist, &playlist_id);

	if (playlist_id == g_playlist_id) {
		ret = media_playlist_get_thumbnail_path(playlist, &get_thumb_path);

		if (get_thumb_path) {
			if (strcmp(get_thumb_path, img_path) != 0)
				ret = MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		} else {
			ret = MEDIA_CONTENT_ERROR_DB_FAILED;
		}
	}
	FREE_MEMORY(get_thumb_path);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return true;
}

/**
 * @testcase		utc_media_playlist_set_thumbnail_path_p
 * @since_tizen		2.3
 * @description		Positive test case of media_playlist_set_thumbnail_path()
 */
int utc_media_playlist_set_thumbnail_path_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	char *thumbnail_path = img_path;

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_set_thumbnail_path(g_playlist, thumbnail_path);

	ret = media_playlist_update_to_db(g_playlist);

	ret = media_playlist_foreach_playlist_from_db(g_filter, _set_thumbnail_path_cb, NULL);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_import_from_file_n
 * @since_tizen		2.4
 * @description		Negative test case of media_playlist_import_from_file()
 */
int utc_media_playlist_import_from_file_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_import_from_file(NULL, TEST_SET_PLAYLIST_SUB_3, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_import_from_file_p
 * @since_tizen		2.4
 * @description		Positive test case of media_playlist_import_from_file()
 */
int utc_media_playlist_import_from_file_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;
	media_playlist_h playlist;
	int playlist_id = 0;

	ret = media_playlist_add_media(g_playlist, g_media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_update_to_db(g_playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_export_to_file(g_playlist, copy_path);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_import_from_file(copy_path, TEST_SET_PLAYLIST_SUB_3, &playlist);

	if (playlist != NULL) {
		media_playlist_get_playlist_id(playlist, &playlist_id);
		media_playlist_delete_from_db(playlist_id);
		media_playlist_destroy(playlist);
		playlist = NULL;
	}

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_media_playlist_export_to_file_n
 * @since_tizen		2.4
 * @description		Negative test case of media_playlist_export_to_file()
 */
int utc_media_playlist_export_to_file_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_export_to_file(NULL, NULL);

	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_playlist_export_to_file_p
 * @since_tizen		2.4
 * @description		Positive test case of media_playlist_export_to_file()
 */
int utc_media_playlist_export_to_file_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_playlist_add_media(g_playlist, g_media_id);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_update_to_db(g_playlist);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_playlist_export_to_file(g_playlist, copy_path);

	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
