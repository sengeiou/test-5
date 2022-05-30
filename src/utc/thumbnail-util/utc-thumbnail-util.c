/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tct_common.h"
#include <glib.h>
#include <thumbnail_util.h>

#define THUMB_WIDTH 320
#define THUMB_HEIGHT 240

static int _retv = 0;

static char *g_image_path;
static char *g_video_path;
static char *g_unsupported_image_path;
static char *g_thumb_path;
static char *g_unsupported_thumb_path;

GMainLoop *g_loop = NULL;

/**
 * @function		utc_thumbnail_util_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_thumbnail_util_startup(void)
{
	char pszValue[CONFIG_VALUE_LEN_MAX] = { 0, };

	if (!GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, "[THUMBNAIL-UTIL]")) {
		FPRINTF("[Line : %d] GetValueForTCTSetting failed\\n", __LINE__);
		return;
	}

	g_image_path = g_strdup_printf("%s/res/sample.jpg", pszValue);
	g_video_path = g_strdup_printf("%s/res/sample.mp4", pszValue);
	g_unsupported_image_path = g_strdup_printf("%s/res/sample.tif", pszValue);
	g_thumb_path = g_strdup_printf("%s/res/thumbnail.jpg", pszValue);
	g_unsupported_thumb_path = g_strdup_printf("%s/res/thumbnail.png", pszValue);
}

/**
 * @function		utc_thumbnail_util_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_thumbnail_util_cleanup(void)
{
	FREE_MEMORY(g_image_path);
	FREE_MEMORY(g_video_path);
	FREE_MEMORY(g_unsupported_image_path);
	FREE_MEMORY(g_thumb_path);
	FREE_MEMORY(g_unsupported_thumb_path);
}

/**
 * @testcase		utc_thumbnail_util_create_n
 * @since_tizen		2.4
 * @description		Negative test case of thumbnail_util_create()
 */
int utc_thumbnail_util_create_n(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;

	ret = thumbnail_util_create(NULL);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_create_p
 * @since_tizen		2.4
 * @description		Positive test case of thumbnail_util_create()
 */
int utc_thumbnail_util_create_p(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_h thumb = NULL;

	ret = thumbnail_util_create(&thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_destroy(thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

static void __completed_cb(thumbnail_util_error_e e, const char *id, int width, int height, unsigned char *data, int size, void *user_data)
{
	_retv = e;
	g_main_loop_quit(g_loop);
}

static gboolean __extract_cb(gpointer data)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	char *request_id = NULL;
	thumbnail_h test_info = NULL;

	ret = thumbnail_util_create(&test_info);
	if (ret != THUMBNAIL_UTIL_ERROR_NONE)
		goto FINALIZE;

	ret = thumbnail_util_set_path(test_info, (const char *)data);
	if (ret != THUMBNAIL_UTIL_ERROR_NONE)
		goto FINALIZE;

	ret = thumbnail_util_set_size(test_info, THUMB_WIDTH, THUMB_HEIGHT);
	if (ret != THUMBNAIL_UTIL_ERROR_NONE)
		goto FINALIZE;

	ret = thumbnail_util_extract(test_info, __completed_cb, NULL, &request_id);
	FREE_MEMORY(request_id);

 FINALIZE:
	if (test_info)
		thumbnail_util_destroy(test_info);

	_retv = ret;
	if (_retv != THUMBNAIL_UTIL_ERROR_NONE)
		g_main_loop_quit(g_loop);

	return FALSE;
}

/**
 * @testcase		utc_thumbnail_util_extract_n1
 * @since_tizen		2.4
 * @description		Negative test case of thumbnail_util_extract()
 */
int utc_thumbnail_util_extract_n1(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	char *request_id = NULL;
	thumbnail_h test_info = NULL;

	ret = thumbnail_util_create(&test_info);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_extract(test_info, __completed_cb, NULL, &request_id);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);
	FREE_MEMORY(request_id);

	ret = thumbnail_util_destroy(test_info);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_n2
 * @since_tizen		4.0
 * @description		Negative test case of thumbnail_util_extract()
 */
int utc_thumbnail_util_extract_n2(void)
{
	g_loop = g_main_loop_new(NULL, FALSE);
	g_idle_add(__extract_cb, (gpointer) g_unsupported_image_path);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	g_loop = NULL;

	assert_eq(_retv, THUMBNAIL_UTIL_ERROR_UNSUPPORTED_CONTENT);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_p
 * @since_tizen		2.4
 * @description		Positive test case of thumbnail_util_extract()
 */
int utc_thumbnail_util_extract_p(void)
{
	g_loop = g_main_loop_new(NULL, FALSE);
	g_idle_add(__extract_cb, (gpointer) g_image_path);

	g_main_loop_run(g_loop);
	g_main_loop_unref(g_loop);

	g_loop = NULL;

	assert_eq(_retv, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_set_path_n
 * @since_tizen		2.4
 * @description		Negative test case of thumbnail_util_set_path()
 */
int utc_thumbnail_util_set_path_n(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_h thumb = NULL;

	ret = thumbnail_util_set_path(NULL, g_image_path);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	ret = thumbnail_util_create(&thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_set_path(thumb, NULL);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	ret = thumbnail_util_destroy(thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_set_path_p
 * @since_tizen		2.4
 * @description		Positive test case of thumbnail_util_set_path()
 */
int utc_thumbnail_util_set_path_p(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_h thumb = NULL;

	ret = thumbnail_util_create(&thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_set_path(thumb, g_image_path);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_destroy(thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_set_size_n
 * @since_tizen		2.4
 * @description		Negative test case of thumbnail_util_set_des_size()
 */
int utc_thumbnail_util_set_size_n(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_h thumb = NULL;

	ret = thumbnail_util_set_size(NULL, THUMB_WIDTH, THUMB_HEIGHT);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	ret = thumbnail_util_create(&thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_set_size(thumb, 0, 0);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	ret = thumbnail_util_destroy(thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_set_size_p
 * @since_tizen		2.4
 * @description		Positive test case of thumbnail_util_set_des_size()
 */
int utc_thumbnail_util_set_size_p(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_h thumb = NULL;

	ret = thumbnail_util_create(&thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_set_size(thumb, THUMB_WIDTH, THUMB_HEIGHT);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_destroy(thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_cancel_n
 * @since_tizen		2.4
 * @description		Negative test case of thumbnail_util_cancel()
 */
int utc_thumbnail_util_cancel_n(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_h thumb = NULL;

	ret = thumbnail_util_cancel(NULL, "0");
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	ret = thumbnail_util_create(&thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_cancel(thumb, NULL);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	ret = thumbnail_util_destroy(thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

static void __cancel_cb(thumbnail_util_error_e e, const char *id, int width, int height, unsigned char *data, int size, void *user_data)
{
}

/**
 * @testcase		utc_thumbnail_util_cancel_p
 * @since_tizen		2.4
 * @description		Positive test case of thumbnail_util_cancel()
 */
int utc_thumbnail_util_cancel_p(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	char *request_id = NULL;
	thumbnail_h test_info = NULL;

	thumbnail_util_create(&test_info);
	thumbnail_util_set_path(test_info, g_image_path);
	thumbnail_util_set_size(test_info, THUMB_WIDTH, THUMB_HEIGHT);

	ret = thumbnail_util_extract(test_info, __cancel_cb, NULL, &request_id);
	FREE_MEMORY(request_id);

	ret = thumbnail_util_extract(test_info, __cancel_cb, NULL, &request_id);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_cancel(test_info, request_id);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);
	FREE_MEMORY(request_id);

	return 0;

}

/**
 * @testcase		utc_thumbnail_util_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of thumbnail_util_destroy()
 */
int utc_thumbnail_util_destroy_n(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;

	ret = thumbnail_util_destroy(NULL);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of thumbnail_util_destroy()
 */
int utc_thumbnail_util_destroy_p(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	thumbnail_h thumb = NULL;

	ret = thumbnail_util_create(&thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	ret = thumbnail_util_destroy(thumb);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_to_file_n1
 * @since_tizen		5.0
 * @description		Negative test case of thumbnail_util_extract_to_file()
 */
int utc_thumbnail_util_extract_to_file_n1(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;

	ret = thumbnail_util_extract_to_file(NULL, THUMB_WIDTH, THUMB_HEIGHT, g_thumb_path);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_to_file_n2
 * @since_tizen		5.0
 * @description		Negative test case of thumbnail_util_extract_to_file()
 */
int utc_thumbnail_util_extract_to_file_n2(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;

	ret = thumbnail_util_extract_to_file(g_unsupported_image_path, THUMB_WIDTH, THUMB_HEIGHT, g_thumb_path);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_UNSUPPORTED_CONTENT);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_to_file_n3
 * @since_tizen		5.0
 * @description		Negative test case of thumbnail_util_extract_to_file()
 */
int utc_thumbnail_util_extract_to_file_n3(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;

	ret = thumbnail_util_extract_to_file(g_video_path, THUMB_WIDTH, THUMB_HEIGHT, g_unsupported_thumb_path);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_to_file_p1
 * @since_tizen		5.0
 * @description		Positive test case of thumbnail_util_extract_to_file()
 */
int utc_thumbnail_util_extract_to_file_p1(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;

	ret = thumbnail_util_extract_to_file(g_image_path, THUMB_WIDTH, THUMB_HEIGHT, g_thumb_path);
	if (g_file_test(g_thumb_path, G_FILE_TEST_IS_REGULAR)) {
		unlink(g_thumb_path);
	} else {
		ret = THUMBNAIL_UTIL_ERROR_INVALID_OPERATION;
	}

	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_to_file_p2
 * @since_tizen		5.0
 * @description		Positive test case of thumbnail_util_extract_to_file()
 */
int utc_thumbnail_util_extract_to_file_p2(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;

	ret = thumbnail_util_extract_to_file(g_video_path, THUMB_WIDTH, THUMB_HEIGHT, g_thumb_path);
	if (g_file_test(g_thumb_path, G_FILE_TEST_IS_REGULAR)) {
		unlink(g_thumb_path);
	} else {
		ret = THUMBNAIL_UTIL_ERROR_INVALID_OPERATION;
	}

	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_to_buffer_n1
 * @since_tizen		5.0
 * @description		Negative test case of thumbnail_util_extract_to_buffer()
 */
int utc_thumbnail_util_extract_to_buffer_n1(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	unsigned char *buf = NULL;
	unsigned int width = 0;
	unsigned int height = 0;
	size_t size = 0;

	ret = thumbnail_util_extract_to_buffer(NULL, THUMB_WIDTH, THUMB_HEIGHT, &buf, &size, &width, &height);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_to_buffer_n2
 * @since_tizen		5.0
 * @description		Negative test case of thumbnail_util_extract_to_buffer()
 */
int utc_thumbnail_util_extract_to_buffer_n2(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	unsigned char *buf = NULL;
	unsigned int width = 0;
	unsigned int height = 0;
	size_t size = 0;

	ret = thumbnail_util_extract_to_buffer(g_unsupported_image_path, THUMB_WIDTH, THUMB_HEIGHT, &buf, &size, &width, &height);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_UNSUPPORTED_CONTENT);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_to_buffer_p1
 * @since_tizen		5.0
 * @description		Positive test case of thumbnail_util_extract_to_buffer()
 */
int utc_thumbnail_util_extract_to_buffer_p1(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	unsigned char *buf = NULL;
	unsigned int width = 0;
	unsigned int height = 0;
	size_t size = 0;

	ret = thumbnail_util_extract_to_buffer(g_image_path, THUMB_WIDTH, THUMB_HEIGHT, &buf, &size, &width, &height);
	FREE_MEMORY(buf);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_thumbnail_util_extract_to_buffer_p2
 * @since_tizen		5.0
 * @description		Positive test case of thumbnail_util_extract_to_buffer()
 */
int utc_thumbnail_util_extract_to_buffer_p2(void)
{
	int ret = THUMBNAIL_UTIL_ERROR_NONE;
	unsigned char *buf = NULL;
	unsigned int width = 0;
	unsigned int height = 0;
	size_t size = 0;

	ret = thumbnail_util_extract_to_buffer(g_video_path, THUMB_WIDTH, THUMB_HEIGHT, &buf, &size, &width, &height);
	FREE_MEMORY(buf);
	assert_eq(ret, THUMBNAIL_UTIL_ERROR_NONE);

	return 0;
}