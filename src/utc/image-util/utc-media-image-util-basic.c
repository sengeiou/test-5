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
#include "assert.h"
#include <stdio.h>
#include <glib.h>
#include <image_util.h>
#include <storage.h>
#include "tct_common.h"
#include "utc-image-util-common.h"

#define API_NAMESPACE			"[IMAGE-UTIL]"


#define LAST_COLORSPACE IMAGE_UTIL_COLORSPACE_BGRX8888
#define UNSUPPORTED_COLORSPACE IMAGE_UTIL_COLORSPACE_NV61+1

#define RESIZE_WIDTH	320
#define RESIZE_HEIGHT	240

static transformation_h g_transform = NULL;
static media_format_h fmt = NULL;
static media_packet_h src = NULL;
static char* img_file1 = "sample.jpg";
static char* img_path1 = NULL;
static image_util_colorspace_e supported_colorspace = 0;
static gboolean g_startup_ret = FALSE;
static gboolean g_async_result = FALSE;

typedef struct {
	unsigned char *buffer;
	unsigned long long size;
	unsigned long width;
	unsigned long height;
} utc_decoded_image;
static utc_decoded_image decoded_image = {NULL, 0, 0, 0};
static image_util_image_h g_image = NULL;

static GMainLoop *g_image_util_mainloop = NULL;
static int g_timeout_id = 0;

static gboolean timeout_func(gpointer data)
{
	fprintf(stderr, "Timeout! Test case failed!\n");
	g_main_loop_quit((GMainLoop *) data);
	return FALSE;
}

static void signal_for_async()
{
	fprintf(stderr, "[%s][Line : %d] Invoked completed callback!\n", __FILE__, __LINE__);
	if (g_timeout_id > 0)
		g_source_remove(g_timeout_id);
	if (g_image_util_mainloop != NULL)
		g_main_loop_quit(g_image_util_mainloop);
}

static void wait_for_async()
{
	g_timeout_id = 0;

	fprintf(stderr, "[%s][Line : %d]\n", __FILE__, __LINE__);

	g_image_util_mainloop = g_main_loop_new(NULL, FALSE);

	g_timeout_id = g_timeout_add(5000, timeout_func, g_image_util_mainloop);
	g_main_loop_run(g_image_util_mainloop);

	g_main_loop_unref(g_image_util_mainloop);
	g_image_util_mainloop = NULL;
}

/* Start callback function declarations */
static bool __utc_supported_colorspace_cb( image_util_colorspace_e colorspace, void * user_data)
{
	FPRINTF("[%s:%d] invoked (colorspace: %d)\\n", __FILE__, __LINE__, colorspace);

	supported_colorspace = colorspace;

	return false;
}

static void __utc_transform_completed_cb(media_packet_h *packet, int error, void *user_param)
{
	FPRINTF("[%s:%d] invoked (error: %d)\\n", __FILE__, __LINE__, error);

	if(error == IMAGE_UTIL_ERROR_NONE)
		g_async_result = TRUE;
	else
		g_async_result = FALSE;

	signal_for_async();
}

static void __utc_transform_completed2_cb(image_util_image_h dst, int error_code, void *user_data)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned int width  = 0;
	unsigned int height  = 0;
	image_util_colorspace_e color = IMAGE_UTIL_COLORSPACE_I420;
	unsigned char *buffer = NULL;
	size_t buffer_size = 0;

	FPRINTF("[%s:%d] invoked (error_code: %d)\\n", __FILE__, __LINE__, error_code);

	ret = image_util_get_image(dst, &width, &height, &color, &buffer, &buffer_size);
	if (ret != IMAGE_UTIL_ERROR_NONE) {
		g_async_result = FALSE;
		goto EXIT;
	}

	FPRINTF("[%s:%d] image (w: %u, h: %u, color: %d, buf: %p, buf_size: %zu)\\n", __FILE__, __LINE__,
			width, height, color, buffer, buffer_size);

	/* compare values with original values */
	if (buffer == NULL || buffer_size == 0) {
		g_async_result = FALSE;
		goto EXIT;
	}

	if (width != RESIZE_WIDTH && height != RESIZE_HEIGHT) {
		g_async_result = FALSE;
		goto EXIT;
	}

	g_async_result = TRUE;

EXIT:
	IMAGEUTIL_SAFE_FREE(buffer);

	signal_for_async();
}
/* End callback function declarations */

static int __utc_decode_jpeg(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_decode_h _decoder = NULL;

	ret = image_util_decode_create(&_decoder);
	if (ret != IMAGE_UTIL_ERROR_NONE) goto out;
	ret = image_util_decode_set_input_path(_decoder, img_path1);
	if (ret != IMAGE_UTIL_ERROR_NONE) goto out;
	ret = image_util_decode_set_colorspace(_decoder, supported_colorspace);
	if (ret != IMAGE_UTIL_ERROR_NONE) goto out;
	ret = image_util_decode_set_output_buffer(_decoder, &decoded_image.buffer);
	if (ret != IMAGE_UTIL_ERROR_NONE) goto out;
	ret = image_util_decode_run(_decoder, &decoded_image.width, &decoded_image.height, &decoded_image.size);
	if (ret != IMAGE_UTIL_ERROR_NONE) goto out;

out:
	image_util_decode_destroy(_decoder);

	return ret;
}

static int __utc_create_media_packet()
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = media_format_create(&fmt);
	retval_if_neq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = media_format_set_video_mime(fmt, MEDIA_FORMAT_RGB888);
	retval_if_neq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = media_format_set_video_width(fmt, 320);
	retval_if_neq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = media_format_set_video_height(fmt, 240);
	retval_if_neq(ret, MEDIA_FORMAT_ERROR_NONE);

	ret = media_packet_create_alloc(fmt, (media_packet_finalize_cb)NULL, NULL, &src);
	retval_if_neq(ret, MEDIA_PACKET_ERROR_NONE);

	return ret;
}

/**
 * @function		utc_media_image_util_basic_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_image_util_basic_startup(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

	g_startup_ret = FALSE;

	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		img_path1 = _utc_get_test_path(pszValue, img_file1);
		FPRINTF("[%d:%s] IMAGE PATH [Basic: %s] \\n", __LINE__, __FUNCTION__, img_path1);

		if (!img_path1)
			FPRINTF("[%d:%s] Get UTC Path error! \\n", __LINE__, __FUNCTION__);
	}
	else
	{
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	image_util_foreach_supported_colorspace(IMAGE_UTIL_JPEG, __utc_supported_colorspace_cb, NULL);

	ret = __utc_decode_jpeg();
	if (ret != IMAGE_UTIL_ERROR_NONE) {
		FPRINTF("[%s:%d] __utc_decode_jpeg failed (ret: %d)\\n", __FILE__, __LINE__, ret);
		return;
	}

	ret = image_util_transform_create(&g_transform);
	if (ret != IMAGE_UTIL_ERROR_NONE) {
		FPRINTF("[%s:%d] image_util_transform_create failed (ret: %d)\\n", __FILE__, __LINE__, ret);
		return;
	}

	g_async_result = FALSE;
	g_startup_ret = TRUE;
}

/**
 * @function		utc_media_image_util_basic_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_media_image_util_basic_cleanup(void)
{
	if (g_image) {
		image_util_destroy_image(g_image);
		g_image = NULL;
	}
	IMAGEUTIL_SAFE_FREE (decoded_image.buffer);
	IMAGEUTIL_SAFE_G_FREE(img_path1);
	if(g_transform) {
		image_util_transform_destroy(g_transform);
		g_transform = NULL;
	}
	if(fmt) {
		media_format_unref(fmt);
		fmt = NULL;
	}
	if(src) {
		media_packet_destroy(src);
		src = NULL;
	}
}

/**
 * @testcase		utc_image_util_calculate_buffer_size_p1
 * @since_tizen		2.3
 * @description		Positive test case of image_util_calculate_buffer_size()
 */
int utc_image_util_calculate_buffer_size_p1(void)
{
	int width = 100, height = 20;
	unsigned int size = 0;

	int err = image_util_calculate_buffer_size(width, height, IMAGE_UTIL_COLORSPACE_RGB888, &size);
	assert_eq(err, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_calculate_buffer_size_p2
 * @since_tizen		2.3
 * @description		Positive test case of image_util_calculate_buffer_size()
 */
int utc_image_util_calculate_buffer_size_p2(void)
{
	assert(g_startup_ret);

	unsigned int size_calc = 0;

	// decoded buffers
	image_util_calculate_buffer_size(decoded_image.width, decoded_image.height, supported_colorspace, &size_calc);

	assert_eq((int)size_calc, decoded_image.size);

	return 0;
}

/**
 * @testcase		utc_image_util_calculate_buffer_size_n1
 * @since_tizen		2.3
 * @description		Negative test case of image_util_calculate_buffer_size()
 */
int utc_image_util_calculate_buffer_size_n1(void)
{
	int width = 100, height = 20;
	unsigned int size = 0;
	const int colorspace = IMAGE_UTIL_COLORSPACE_NV61 + 1; // after last one

	int err = image_util_calculate_buffer_size(width, height, colorspace, &size);
	assert_neq(err, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_calculate_buffer_size_n2
 * @since_tizen		2.3
 * @description		Negative test case of image_util_calculate_buffer_size()
 */
int utc_image_util_calculate_buffer_size_n2(void)
{
	int width = -100, height = 20; // wrong parameter
	unsigned int size = 0;
	const int colorspace = IMAGE_UTIL_COLORSPACE_BGRX8888;

	int err = image_util_calculate_buffer_size(width, height, colorspace, &size);
	assert_neq(err, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_calculate_buffer_size_n3
 * @since_tizen		2.3
 * @description		Negative test case of image_util_calculate_buffer_size()
 */
int utc_image_util_calculate_buffer_size_n3(void)
{
	int width = 0, height = 0; // wrong parameter
	unsigned int size = 0;
	const int colorspace = IMAGE_UTIL_COLORSPACE_BGRX8888;

	int err = image_util_calculate_buffer_size(width, height, colorspace, &size);
	assert_neq(err, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_create_n
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_create()
 */
int utc_image_util_transform_create_n(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_create(NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_create_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_create()
 */
int utc_image_util_transform_create_p(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_destroy(g_transform);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_create(&g_transform);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_hardware_acceleration_n
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_set_hardware_acceleration()
 */
int utc_image_util_transform_set_hardware_acceleration_n(void)
{
	int ret = image_util_transform_set_hardware_acceleration(NULL, false);

	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_hardware_acceleration_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_set_hardware_acceleration()
 */
int utc_image_util_transform_set_hardware_acceleration_p(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_hardware_acceleration(g_transform, false);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_colorspace_n
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_set_colorspace()
 */
int utc_image_util_transform_set_colorspace_n(void)
{
	int ret = image_util_transform_set_colorspace(NULL, IMAGE_UTIL_COLORSPACE_RGB888);

	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_colorspace_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_set_colorspace()
 */
int utc_image_util_transform_set_colorspace_p(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_colorspace(g_transform, IMAGE_UTIL_COLORSPACE_RGB888);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_colorspace_n1
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_get_colorspace()
 */
int utc_image_util_transform_get_colorspace_n1(void)
{
	image_util_colorspace_e colorspace;
	int ret = image_util_transform_get_colorspace(NULL, &colorspace);

	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_colorspace_n2
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_get_colorspace()
 */
int utc_image_util_transform_get_colorspace_n2(void)
{
	assert_neq(g_transform, NULL);

	image_util_colorspace_e colorspace;
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_get_colorspace(g_transform, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_get_colorspace(g_transform, &colorspace);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_colorspace_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_get_colorspace()
 */
int utc_image_util_transform_get_colorspace_p(void)
{
	assert_neq(g_transform, NULL);

	image_util_colorspace_e colorspace;
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_colorspace(g_transform, IMAGE_UTIL_COLORSPACE_RGB888);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_get_colorspace(g_transform, &colorspace);

	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	assert_eq(colorspace, IMAGE_UTIL_COLORSPACE_RGB888);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_resolution_n1
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_set_resolution()
 */
int utc_image_util_transform_set_resolution_n1(void)
{
	int ret = image_util_transform_set_resolution(NULL, 320, 240);

	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_resolution_n2
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_set_resolution()
 */
int utc_image_util_transform_set_resolution_n2(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_resolution(g_transform, 0, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_set_resolution(g_transform, 320, 0);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_resolution_n3
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_set_resolution()
 */
int utc_image_util_transform_set_resolution_n3(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_crop_area(g_transform, 0, 0, 320, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_set_resolution(g_transform, 320, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_resolution_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_set_resolution()
 */
int utc_image_util_transform_set_resolution_p(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_resolution(g_transform, 320, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_resolution_n1
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_get_resolution()
 */
int utc_image_util_transform_get_resolution_n1(void)
{
	unsigned int width = 0, height = 0;
	int ret = image_util_transform_get_resolution(NULL, &width, &height);

	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_resolution_n2
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_get_resolution()
 */
int utc_image_util_transform_get_resolution_n2(void)
{
	assert_neq(g_transform, NULL);

	unsigned int width = 0, height = 0;
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_get_resolution(g_transform, NULL, &height);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_get_resolution(g_transform, &width, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_get_resolution(g_transform, &width, &height);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_resolution_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_get_resolution()
 */
int utc_image_util_transform_get_resolution_p(void)
{
	assert_neq(g_transform, NULL);

	unsigned int width = 0;
	unsigned int height = 0;
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_resolution(g_transform, 320, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_get_resolution(g_transform, &width, &height);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	assert_eq(width, 320);
	assert_eq(height, 240);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_rotation_n
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_set_rotation()
 */
int utc_image_util_transform_set_rotation_n(void)
{
	int ret = image_util_transform_set_rotation(NULL, IMAGE_UTIL_ROTATION_NONE);

	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}


/**
 * @testcase		utc_image_util_transform_set_rotation_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_set_rotation()
 */
int utc_image_util_transform_set_rotation_p(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_rotation(g_transform, IMAGE_UTIL_ROTATION_90);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_rotation_n1
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_get_rotation()
 */
int utc_image_util_transform_get_rotation_n1(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_rotation_e rotation = IMAGE_UTIL_ROTATION_NONE;

	ret = image_util_transform_get_rotation(NULL, &rotation);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_rotation_n2
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_get_rotation()
 */
int utc_image_util_transform_get_rotation_n2(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_rotation_e rotation = IMAGE_UTIL_ROTATION_NONE;

	ret = image_util_transform_get_rotation(g_transform, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_get_rotation(g_transform, &rotation);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_rotation_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_get_rotation()
 */
int utc_image_util_transform_get_rotation_p(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_rotation_e rotation = IMAGE_UTIL_ROTATION_NONE;

	ret = image_util_transform_set_rotation(g_transform, IMAGE_UTIL_ROTATION_90);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_get_rotation(g_transform, &rotation);

	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	assert_eq(rotation, IMAGE_UTIL_ROTATION_90);

	return 0;
}


/**
 * @testcase		utc_image_util_transform_run_n1
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_run()
 */
int utc_image_util_transform_run_n1(void)
{
	int ret = image_util_transform_run(NULL, src, (image_util_transform_completed_cb) __utc_transform_completed_cb, NULL);

	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_run_n2
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_run()
 */
int utc_image_util_transform_run_n2(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_run(g_transform, NULL, (image_util_transform_completed_cb) __utc_transform_completed_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_run_n3
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_run()
 */
int utc_image_util_transform_run_n3(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = __utc_create_media_packet();
	assert_eq(ret, 0);

	ret = image_util_transform_run(g_transform, src, (image_util_transform_completed_cb) NULL, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_run_n4
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_run()
 */
int utc_image_util_transform_run_n4(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = __utc_create_media_packet();
	assert_eq(ret, 0);

	ret = image_util_transform_run(g_transform, src, (image_util_transform_completed_cb) __utc_transform_completed_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_run_p1
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_run()
 */
int utc_image_util_transform_run_p1(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = __utc_create_media_packet();
	assert_eq(ret, 0);

	ret = image_util_transform_set_resolution(g_transform, 176, 144);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	g_async_result = FALSE;
	ret = image_util_transform_run(g_transform, src, (image_util_transform_completed_cb) __utc_transform_completed_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	wait_for_async();
	assert_eq(g_async_result, TRUE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_run_p2
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_run()
 */
int utc_image_util_transform_run_p2(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = __utc_create_media_packet();
	assert_eq(ret, 0);

	ret = image_util_transform_set_resolution(g_transform, 176, 144);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_set_rotation(g_transform, IMAGE_UTIL_ROTATION_90);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	g_async_result = FALSE;
	ret = image_util_transform_run(g_transform, src, (image_util_transform_completed_cb) __utc_transform_completed_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	wait_for_async();
	assert_eq(g_async_result, TRUE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_run_p3
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_run()
 */
int utc_image_util_transform_run_p3(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = __utc_create_media_packet();
	assert_eq(ret, 0);

	ret = image_util_transform_set_crop_area(g_transform, 0, 0, 176, 144);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_set_rotation(g_transform, IMAGE_UTIL_ROTATION_90);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	g_async_result = FALSE;
	ret = image_util_transform_run(g_transform, src, (image_util_transform_completed_cb) __utc_transform_completed_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	wait_for_async();
	assert_eq(g_async_result, TRUE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_crop_area_n1
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_set_crop_area()
 */
int utc_image_util_transform_set_crop_area_n1(void)
{
	int ret = image_util_transform_set_crop_area(NULL, 0, 0, 320, 240);

	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_crop_area_n2
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_set_crop_area()
 */
int utc_image_util_transform_set_crop_area_n2(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_crop_area(g_transform, 100, 0, 100, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_set_crop_area(g_transform, 0, 100, 320, 100);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_crop_area_n3
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_set_crop_area()
 */
int utc_image_util_transform_set_crop_area_n3(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_resolution(g_transform, 320, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_set_crop_area(g_transform, 0, 0, 320, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_set_crop_area_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_set_crop_area()
 */
int utc_image_util_transform_set_crop_area_p(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_crop_area(g_transform, 0, 0, 320, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_crop_area_n1
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_get_crop_area()
 */
int utc_image_util_transform_get_crop_area_n1(void)
{
	unsigned int startX = 0, startY = 0, endX = 0, endY = 0;
	int ret = image_util_transform_get_crop_area(NULL, &startX, &startY, &endX, &endY);

	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_crop_area_n2
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_get_crop_area()
 */
int utc_image_util_transform_get_crop_area_n2(void)
{
	assert_neq(g_transform, NULL);

	unsigned int start_x = 0;
	unsigned int start_y = 0;
	unsigned int end_x = 0;
	unsigned int end_y = 0;
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_get_crop_area(g_transform, NULL, NULL, NULL, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_get_crop_area(g_transform, &start_x, &start_y, &end_x, &end_y);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_OPERATION);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_get_crop_area_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_get_crop_area()
 */
int utc_image_util_transform_get_crop_area_p(void)
{
	assert_neq(g_transform, NULL);

	unsigned int start_x = 0;
	unsigned int start_y = 0;
	unsigned int end_x = 0;
	unsigned int end_y = 0;
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_set_crop_area(g_transform, 100, 100, 320, 240);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_get_crop_area(g_transform, &start_x, &start_y, &end_x, &end_y);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);
	assert_eq(start_x, 100);
	assert_eq(start_y, 100);
	assert_eq(end_x, 320);
	assert_eq(end_y, 240);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_destory_n
 * @since_tizen		2.3
 * @description		Negative test case of image_util_transform_destory()
 */
int utc_image_util_transform_destory_n(void)
{
	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_destroy(NULL);
	assert_neq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_destory_p
 * @since_tizen		2.3
 * @description		Positive test case of image_util_transform_destory()
 */
int utc_image_util_transform_destory_p(void)
{
	assert_neq(g_transform, NULL);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_transform_destroy(g_transform);
	g_transform = NULL;
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_extract_color_from_memory_p
 * @since_tizen		3.0
 * @description		Extract color from a given memory
 */
int utc_image_util_extract_color_from_memory_p(void)
{
	assert(g_startup_ret);

	int r;

	unsigned char rgb_r;
	unsigned char rgb_g;
	unsigned char rgb_b;

	r = image_util_extract_color_from_memory(decoded_image.buffer, decoded_image.width, decoded_image.height, &rgb_r, &rgb_g, &rgb_b);

	assert_eq(r, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_extract_color_from_memory_n
 * @since_tizen		3.0
 * @description		Extract color from a given memory,
 * 					but fail because the memory address is NULL
 */
int utc_image_util_extract_color_from_memory_n(void)
{
	int r;

	unsigned char rgb_r;
	unsigned char rgb_g;
	unsigned char rgb_b;

	r = image_util_extract_color_from_memory(NULL, decoded_image.width, decoded_image.height, &rgb_r, &rgb_g, &rgb_b);

	assert_eq(r, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_create_image_p
 * @since_tizen		5.5
 * @description		Creates image handle from a decoded memory
 */
int utc_image_util_create_image_p(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_create_image_n
 * @since_tizen		5.5
 * @description		Creates image handle from a decoded memory,
 * 					but fail because a width, a height or a size are zero or memory address is NULL
 */
int utc_image_util_create_image_n(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_create_image(0, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_create_image(decoded_image.width, 0, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_create_image(decoded_image.width, decoded_image.height, -1,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			NULL, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, 0, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_clone_image_p
 * @since_tizen		5.5
 * @description		Clones image handle
 */
int utc_image_util_clone_image_p(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_image_h clone_image = NULL;
	unsigned int width  = 0;
	unsigned int height  = 0;
	image_util_colorspace_e color = IMAGE_UTIL_COLORSPACE_I420;
	unsigned char *buffer = NULL;
	size_t buffer_size = 0;

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_clone_image(g_image, &clone_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_get_image(clone_image, &width, &height, &color, &buffer, &buffer_size);
	image_util_destroy_image(clone_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	/* compare clone image with original image */
	assert_neq(buffer, NULL);
	free(buffer);
	assert_eq(buffer_size, decoded_image.size);
	assert_eq(width, decoded_image.width);
	assert_eq(height, decoded_image.height);
	assert_eq(color, supported_colorspace);

	return 0;
}

/**
 * @testcase		utc_image_util_clone_image_n
 * @since_tizen		5.5
 * @description		Clones image handle, but fail because handle is NULL
 */
int utc_image_util_clone_image_n(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_image_h clone_image = NULL;

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_clone_image(NULL, &clone_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_clone_image(g_image, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_get_image_p
 * @since_tizen		5.5
 * @description		Gets image information from given image handle
 */
int utc_image_util_get_image_p(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;
	unsigned int width  = 0;
	unsigned int height  = 0;
	image_util_colorspace_e color = IMAGE_UTIL_COLORSPACE_I420;
	unsigned char *buffer = NULL;
	size_t buffer_size = 0;

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_get_image(g_image, &width, &height, &color, &buffer, &buffer_size);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	/* compare values with original values */
	assert_neq(buffer, NULL);
	free(buffer);
	assert_eq(buffer_size, decoded_image.size);
	assert_eq(width, decoded_image.width);
	assert_eq(height, decoded_image.height);
	assert_eq(color, supported_colorspace);

	return 0;
}

/**
 * @testcase		utc_image_util_get_image_n
 * @since_tizen		5.5
 * @description		Gets image information from given image handle, but fail because given handle is NULL
 */
int utc_image_util_get_image_n(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_get_image(NULL, NULL, NULL, NULL, NULL, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_destroy_image_p
 * @since_tizen		5.5
 * @description		Destroyes image handle
 */
int utc_image_util_destroy_image_p(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_destroy_image(g_image);
	g_image = NULL;
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_destroy_image_n
 * @since_tizen		5.5
 * @description		Destroyes image handle, but fail because a handle is NULL
 */
int utc_image_util_destroy_image_n(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_destroy_image(NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_run2_p
 * @since_tizen		5.5
 * @description		Transforms image handle
 */
int utc_image_util_transform_run2_p(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_image_h transformed_image = NULL;

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_set_resolution(g_transform, RESIZE_WIDTH, RESIZE_HEIGHT);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_run2(g_transform, g_image, &transformed_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_destroy_image(transformed_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_run2_n
 * @since_tizen		5.5
 * @description		Transforms image handle, but fail because a handle is NULL
 */
int utc_image_util_transform_run2_n(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_image_h transformed_image = NULL;

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_set_resolution(g_transform, RESIZE_WIDTH, RESIZE_HEIGHT);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_run2(NULL, g_image, &transformed_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_run2(g_transform, NULL, &transformed_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_run2(g_transform, g_image, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_run2_async_p
 * @since_tizen		5.5
 * @description		Transforms image handle
 */
int utc_image_util_transform_run2_async_p(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_set_resolution(g_transform, RESIZE_WIDTH, RESIZE_HEIGHT);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	g_async_result = FALSE;
	ret = image_util_transform_run2_async(g_transform, g_image, __utc_transform_completed2_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	wait_for_async();
	assert_eq(g_async_result, TRUE);

	return 0;
}

/**
 * @testcase		utc_image_util_transform_run2_async_n
 * @since_tizen		5.5
 * @description		Transforms image handle, but fail because a handle is NULL
 */
int utc_image_util_transform_run2_async_n(void)
{
	assert(g_startup_ret);

	int ret = IMAGE_UTIL_ERROR_NONE;

	ret = image_util_create_image(decoded_image.width, decoded_image.height, supported_colorspace,
			decoded_image.buffer, decoded_image.size, &g_image);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_set_resolution(g_transform, RESIZE_WIDTH, RESIZE_HEIGHT);
	assert_eq(ret, IMAGE_UTIL_ERROR_NONE);

	ret = image_util_transform_run2_async(NULL, g_image, __utc_transform_completed2_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_run2_async(g_transform, NULL, __utc_transform_completed2_cb, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

	ret = image_util_transform_run2_async(g_transform, g_image, NULL, NULL);
	assert_eq(ret, IMAGE_UTIL_ERROR_INVALID_PARAMETER);

    return 0;
}
