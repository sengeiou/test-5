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

//& set: MediaBookmarkInsert

static media_bookmark_h g_bookmark;
static char *g_media_id = NULL;
static filter_h g_filter;
static int g_bookmark_id;

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

static bool bookmark_cb(media_bookmark_h bookmark, void *user_data)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_bookmark_clone(&g_bookmark, bookmark);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "CB error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_bookmark_clone failed (code: %d)\n", ret);
		return false;
	}

	ret = media_bookmark_get_bookmark_id(bookmark, &g_bookmark_id);
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "CB error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_bookmark_get_bookmark_id failed (code: %d)\n", ret);
		return false;
	}

	return false;
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

	return false;
}

/**
 * @function		utc_media_bookmark_insert_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_bookmark_insert_startup(void)
{
	media_content_error_e ret = MEDIA_CONTENT_ERROR_NONE;

	if (storage_foreach_device_supported(__storage_device_supported_cb, NULL) != STORAGE_ERROR_NONE)
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);

	ret = media_content_connect();
	if (ret != MEDIA_CONTENT_ERROR_NONE) {
		fprintf(stderr, "Startup error at %s:%d\n", __FILE__, __LINE__);
		fprintf(stderr, "media_content_connect failed (code: %d)\n", ret);
		startup_ret = ret;
		return;
	}

	char *condition = "MEDIA_TYPE=1 AND MEDIA_STORAGE_TYPE=0";	//Video

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
}

/**
 * @function		utc_media_bookmark_insert_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_bookmark_insert_cleanup(void)
{

	if (g_media_id != NULL) {
		free(g_media_id);
		g_media_id = NULL;
	}

	if (g_filter != NULL) {
		media_filter_destroy(g_filter);
		g_filter = NULL;
	}

	if (g_bookmark != NULL) {
		media_bookmark_delete_from_db(g_bookmark_id);
		media_bookmark_destroy(g_bookmark);
		g_bookmark = NULL;
	}

	media_content_disconnect();

	if (img_path != NULL) {
		free(img_path);
		img_path = NULL;
	}
}

/**
 * @testcase		utc_media_bookmark_insert_to_db_n
 * @since_tizen		2.3
 * @description		Negative test case of media_bookmark_insert_to_db()
 */
int utc_media_bookmark_insert_to_db_n(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_bookmark_insert_to_db(NULL, 0, img_file);
	assert_eq(ret, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_media_bookmark_insert_to_db_p
 * @since_tizen		2.3
 * @description		Positive test case of media_bookmark_insert_to_db()
 */
int utc_media_bookmark_insert_to_db_p(void)
{
	assert_eq(startup_ret, MEDIA_CONTENT_ERROR_NONE);

	int ret = MEDIA_CONTENT_ERROR_NONE;

	time_t stTime = { 0 };
	time(&stTime);
	fprintf(stderr, "%s:%d	img_path = %s\n", __FILE__, __LINE__, img_path);
	ret = media_bookmark_insert_to_db(g_media_id, stTime, img_path);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	ret = media_info_foreach_bookmark_from_db(g_media_id, NULL, bookmark_cb, NULL);
	assert_eq(ret, MEDIA_CONTENT_ERROR_NONE);

	return 0;
}
